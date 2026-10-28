"""Headless GBA emulator harness driven from Python.

A minimal libretro frontend written with ctypes. It loads the mGBA libretro
core (Debian/Ubuntu package ``libretro-mgba``) and exposes what the tests need:

* load a ROM, run N frames, set the pressed buttons per frame,
* read memory by GBA address (EWRAM, IWRAM, I/O, palette, VRAM, OAM, ROM),
  with symbols resolved from the linker ``.map`` file,
* take a screenshot (RGB888) and write/read PNG files (no Pillow needed),
* save and restore emulator state (to share a booted game between tests).

No Nintendo BIOS is used: the core runs with its built-in HLE BIOS
(``mgba_use_bios=OFF``), and the system directory handed to it is an empty
temporary directory, so a stray ``gba_bios.bin`` can never be picked up.

The libretro API is a C ABI with global state, so only one :class:`Emulator`
can be alive per process.
"""

from __future__ import annotations

import ctypes
import os
import re
import struct
import tempfile
import zlib
from pathlib import Path
from typing import Iterable

# ---------------------------------------------------------------------------
# Core discovery
# ---------------------------------------------------------------------------

CORE_ENV = "MGBA_LIBRETRO_CORE"
CORE_CANDIDATES = (
    "/usr/lib/x86_64-linux-gnu/libretro/mgba_libretro.so",
    "/usr/lib/aarch64-linux-gnu/libretro/mgba_libretro.so",
    "/usr/lib/libretro/mgba_libretro.so",
    "/usr/local/lib/libretro/mgba_libretro.so",
    os.path.expanduser("~/.config/retroarch/cores/mgba_libretro.so"),
)


def find_core() -> str | None:
    """Return the path of the mGBA libretro core, or None if not installed."""
    env = os.environ.get(CORE_ENV)
    if env:
        return env if Path(env).is_file() else None
    for c in CORE_CANDIDATES:
        if Path(c).is_file():
            return c
    return None


# ---------------------------------------------------------------------------
# libretro ABI
# ---------------------------------------------------------------------------

ENV_GET_CAN_DUPE = 3
ENV_SET_PERFORMANCE_LEVEL = 8
ENV_GET_SYSTEM_DIRECTORY = 9
ENV_SET_PIXEL_FORMAT = 10
ENV_SET_INPUT_DESCRIPTORS = 11
ENV_GET_VARIABLE = 15
ENV_SET_VARIABLES = 16
ENV_GET_VARIABLE_UPDATE = 17
ENV_GET_LOG_INTERFACE = 27
ENV_GET_SAVE_DIRECTORY = 31
ENV_SET_CONTROLLER_INFO = 35
ENV_EXPERIMENTAL = 0x10000
ENV_SET_MEMORY_MAPS = 36 | ENV_EXPERIMENTAL
ENV_SET_SUPPORT_ACHIEVEMENTS = 42 | ENV_EXPERIMENTAL

PIXEL_0RGB1555, PIXEL_XRGB8888, PIXEL_RGB565 = 0, 1, 2

RETRO_DEVICE_JOYPAD = 1
RETRO_MEMORY_SAVE_RAM = 0

# libretro joypad ids for the GBA buttons (mGBA maps them 1:1)
BUTTONS = {
    "B": 0, "SELECT": 2, "START": 3, "UP": 4, "DOWN": 5,
    "LEFT": 6, "RIGHT": 7, "A": 8, "L": 10, "R": 11,
}

# Core options. Fixed values keep runs deterministic and independent of any
# user configuration.
CORE_OPTIONS = {
    b"mgba_use_bios": b"OFF",          # HLE BIOS, never a real one
    b"mgba_skip_bios": b"ON",
    b"mgba_idle_optimization": b"Don't Remove",
    b"mgba_frameskip": b"disabled",
    b"mgba_color_correction": b"OFF",
    b"mgba_interframe_blending": b"OFF",
    b"mgba_audio_low_pass_filter": b"disabled",
    b"mgba_solar_sensor_level": b"0",
    b"mgba_force_gbp": b"OFF",
    b"mgba_allow_opposing_directions": b"no",
}


class GameInfo(ctypes.Structure):
    _fields_ = [("path", ctypes.c_char_p), ("data", ctypes.c_void_p),
                ("size", ctypes.c_size_t), ("meta", ctypes.c_char_p)]


class Geometry(ctypes.Structure):
    _fields_ = [("base_width", ctypes.c_uint), ("base_height", ctypes.c_uint),
                ("max_width", ctypes.c_uint), ("max_height", ctypes.c_uint),
                ("aspect_ratio", ctypes.c_float)]


class Timing(ctypes.Structure):
    _fields_ = [("fps", ctypes.c_double), ("sample_rate", ctypes.c_double)]


class AvInfo(ctypes.Structure):
    _fields_ = [("geometry", Geometry), ("timing", Timing)]


class Variable(ctypes.Structure):
    _fields_ = [("key", ctypes.c_char_p), ("value", ctypes.c_char_p)]


class MemoryDescriptor(ctypes.Structure):
    _fields_ = [("flags", ctypes.c_uint64), ("ptr", ctypes.c_void_p),
                ("offset", ctypes.c_size_t), ("start", ctypes.c_size_t),
                ("select", ctypes.c_size_t), ("disconnect", ctypes.c_size_t),
                ("len", ctypes.c_size_t), ("addrspace", ctypes.c_char_p)]


class MemoryMap(ctypes.Structure):
    _fields_ = [("descriptors", ctypes.POINTER(MemoryDescriptor)),
                ("num_descriptors", ctypes.c_uint)]


ENV_CB = ctypes.CFUNCTYPE(ctypes.c_bool, ctypes.c_uint, ctypes.c_void_p)
VIDEO_CB = ctypes.CFUNCTYPE(None, ctypes.c_void_p, ctypes.c_uint, ctypes.c_uint, ctypes.c_size_t)
AUDIO_CB = ctypes.CFUNCTYPE(None, ctypes.c_int16, ctypes.c_int16)
AUDIO_BATCH_CB = ctypes.CFUNCTYPE(ctypes.c_size_t, ctypes.c_void_p, ctypes.c_size_t)
POLL_CB = ctypes.CFUNCTYPE(None)
STATE_CB = ctypes.CFUNCTYPE(ctypes.c_int16, ctypes.c_uint, ctypes.c_uint, ctypes.c_uint, ctypes.c_uint)


# ---------------------------------------------------------------------------
# Symbols from the GNU ld map file
# ---------------------------------------------------------------------------

MAP_SYMBOL_RE = re.compile(r"^\s+0x([0-9a-fA-F]+)\s+([A-Za-z_][\w.$]*)(?:\s*=\s*\.)?\s*$")


def load_map_symbols(map_path: str | os.PathLike) -> dict[str, int]:
    """Parse ``name -> address`` from a GNU ld ``.map`` file."""
    syms: dict[str, int] = {}
    for line in Path(map_path).read_text(errors="replace").splitlines():
        m = MAP_SYMBOL_RE.match(line)
        if m:
            addr = int(m.group(1), 16)
            if addr >= 0x02000000:  # skip section-relative ". = 0x.." values
                syms.setdefault(m.group(2), addr)
    return syms


# ---------------------------------------------------------------------------
# PNG (RGB8, no external dependencies)
# ---------------------------------------------------------------------------


def write_png(path: str | os.PathLike, width: int, height: int, rgb: bytes) -> None:
    raw = b"".join(b"\x00" + rgb[y * width * 3:(y + 1) * width * 3] for y in range(height))

    def chunk(tag: bytes, data: bytes) -> bytes:
        return struct.pack(">I", len(data)) + tag + data + struct.pack(">I", zlib.crc32(tag + data))

    png = (b"\x89PNG\r\n\x1a\n"
           + chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0))
           + chunk(b"IDAT", zlib.compress(raw, 9))
           + chunk(b"IEND", b""))
    Path(path).write_bytes(png)


def read_png(path: str | os.PathLike) -> tuple[int, int, bytes]:
    """Read an 8-bit RGB or RGBA PNG; returns (width, height, rgb bytes)."""
    data = Path(path).read_bytes()
    if data[:8] != b"\x89PNG\r\n\x1a\n":
        raise ValueError(f"{path}: not a PNG")
    pos, idat = 8, b""
    width = height = channels = 0
    while pos < len(data):
        (n,) = struct.unpack(">I", data[pos:pos + 4])
        tag, body = data[pos + 4:pos + 8], data[pos + 8:pos + 8 + n]
        pos += 12 + n
        if tag == b"IHDR":
            width, height, depth, ctype, _, _, interlace = struct.unpack(">IIBBBBB", body)
            if depth != 8 or ctype not in (2, 6) or interlace:
                raise ValueError(f"{path}: only 8-bit non-interlaced RGB/RGBA PNG supported")
            channels = 3 if ctype == 2 else 4
        elif tag == b"IDAT":
            idat += body
        elif tag == b"IEND":
            break
    raw = zlib.decompress(idat)
    stride = width * channels
    out = bytearray()
    prev = bytearray(stride)
    p = 0
    for _ in range(height):
        ftype, line = raw[p], bytearray(raw[p + 1:p + 1 + stride])
        p += 1 + stride
        for i in range(stride):
            a = line[i - channels] if i >= channels else 0
            b = prev[i]
            c = prev[i - channels] if i >= channels else 0
            if ftype == 1:
                line[i] = (line[i] + a) & 0xFF
            elif ftype == 2:
                line[i] = (line[i] + b) & 0xFF
            elif ftype == 3:
                line[i] = (line[i] + ((a + b) >> 1)) & 0xFF
            elif ftype == 4:
                pa, pb, pc = abs(b - c), abs(a - c), abs(a + b - 2 * c)
                pred = a if pa <= pb and pa <= pc else (b if pb <= pc else c)
                line[i] = (line[i] + pred) & 0xFF
        prev = line
        if channels == 3:
            out += line
        else:
            for i in range(0, stride, 4):
                out += line[i:i + 3]
    return width, height, bytes(out)


def image_diff(a: bytes, b: bytes, threshold: int = 24) -> float:
    """Fraction of pixels whose max channel difference exceeds ``threshold``."""
    if len(a) != len(b):
        return 1.0
    bad = 0
    for i in range(0, len(a), 3):
        if (abs(a[i] - b[i]) > threshold or abs(a[i + 1] - b[i + 1]) > threshold
                or abs(a[i + 2] - b[i + 2]) > threshold):
            bad += 1
    return bad / (len(a) // 3)


# ---------------------------------------------------------------------------
# Emulator
# ---------------------------------------------------------------------------


class EmulatorError(RuntimeError):
    pass


class Emulator:
    """One mGBA libretro core instance (only one per process)."""

    _alive = False

    def __init__(self, rom: str | os.PathLike, map_file: str | os.PathLike | None = None,
                 core: str | None = None):
        if Emulator._alive:
            raise EmulatorError("only one Emulator per process (libretro cores are global)")
        core = core or find_core()
        if not core:
            raise EmulatorError("mGBA libretro core not found (apt install libretro-mgba, "
                                f"or set {CORE_ENV})")
        self.rom_path = Path(rom)
        self.symbols = load_map_symbols(map_file) if map_file else {}
        self._tmp = tempfile.TemporaryDirectory(prefix="emu-")
        self._sysdir = ctypes.create_string_buffer(self._tmp.name.encode())
        self._sysdir_ptr = ctypes.c_char_p(ctypes.addressof(self._sysdir))
        self._option_values = {k: ctypes.create_string_buffer(v) for k, v in CORE_OPTIONS.items()}
        self.options_requested: set[bytes] = set()
        self.pixel_format = PIXEL_0RGB1555
        self.regions: list[tuple[int, int, int]] = []  # (start, length, host pointer)
        self._frame: bytes | None = None
        self._frame_geom = (240, 160, 480)
        self._keys = 0
        self.frame_count = 0

        self.lib = ctypes.CDLL(core)
        lib = self.lib
        lib.retro_api_version.restype = ctypes.c_uint
        lib.retro_load_game.argtypes = [ctypes.POINTER(GameInfo)]
        lib.retro_load_game.restype = ctypes.c_bool
        lib.retro_get_memory_data.argtypes = [ctypes.c_uint]
        lib.retro_get_memory_data.restype = ctypes.c_void_p
        lib.retro_get_memory_size.argtypes = [ctypes.c_uint]
        lib.retro_get_memory_size.restype = ctypes.c_size_t
        lib.retro_serialize_size.restype = ctypes.c_size_t
        lib.retro_serialize.argtypes = [ctypes.c_void_p, ctypes.c_size_t]
        lib.retro_serialize.restype = ctypes.c_bool
        lib.retro_unserialize.argtypes = [ctypes.c_void_p, ctypes.c_size_t]
        lib.retro_unserialize.restype = ctypes.c_bool
        lib.retro_get_system_av_info.argtypes = [ctypes.POINTER(AvInfo)]

        # Keep references to the callbacks for the life of the core.
        self._cbs = (ENV_CB(self._env), VIDEO_CB(self._video), AUDIO_CB(lambda l, r: None),
                     AUDIO_BATCH_CB(lambda d, n: n), POLL_CB(lambda: None), STATE_CB(self._input))
        lib.retro_set_environment(self._cbs[0])
        lib.retro_init()
        lib.retro_set_video_refresh(self._cbs[1])
        lib.retro_set_audio_sample(self._cbs[2])
        lib.retro_set_audio_sample_batch(self._cbs[3])
        lib.retro_set_input_poll(self._cbs[4])
        lib.retro_set_input_state(self._cbs[5])

        self._rom_data = ctypes.create_string_buffer(self.rom_path.read_bytes())
        info = GameInfo(str(self.rom_path).encode(), ctypes.cast(self._rom_data, ctypes.c_void_p),
                        len(self._rom_data) - 1, None)
        if not lib.retro_load_game(ctypes.byref(info)):
            lib.retro_deinit()
            raise EmulatorError(f"core refused to load {self.rom_path}")
        av = AvInfo()
        lib.retro_get_system_av_info(ctypes.byref(av))
        self.fps = av.timing.fps
        Emulator._alive = True
        if not self.regions:
            raise EmulatorError("core did not publish a memory map")

    # -- callbacks ---------------------------------------------------------

    def _env(self, cmd: int, data: int) -> bool:
        try:
            if cmd == ENV_GET_CAN_DUPE:
                ctypes.cast(data, ctypes.POINTER(ctypes.c_bool))[0] = True
                return True
            if cmd in (ENV_GET_SYSTEM_DIRECTORY, ENV_GET_SAVE_DIRECTORY):
                ctypes.cast(data, ctypes.POINTER(ctypes.c_char_p))[0] = self._sysdir_ptr
                return True
            if cmd == ENV_SET_PIXEL_FORMAT:
                fmt = ctypes.cast(data, ctypes.POINTER(ctypes.c_int))[0]
                if fmt in (PIXEL_0RGB1555, PIXEL_XRGB8888, PIXEL_RGB565):
                    self.pixel_format = fmt
                    return True
                return False
            if cmd == ENV_GET_VARIABLE:
                var = ctypes.cast(data, ctypes.POINTER(Variable))[0]
                key = var.key
                self.options_requested.add(key)
                buf = self._option_values.get(key)
                if buf is None:
                    return False
                ctypes.cast(data, ctypes.POINTER(Variable))[0].value = ctypes.addressof(buf)
                return True
            if cmd == ENV_GET_VARIABLE_UPDATE:
                ctypes.cast(data, ctypes.POINTER(ctypes.c_bool))[0] = False
                return True
            if cmd == ENV_SET_MEMORY_MAPS:
                mmap = ctypes.cast(data, ctypes.POINTER(MemoryMap))[0]
                self.regions = []
                for i in range(mmap.num_descriptors):
                    d = mmap.descriptors[i]
                    if d.ptr and d.len:
                        self.regions.append((d.start, d.len, d.ptr + d.offset))
                return True
            if cmd in (ENV_SET_PERFORMANCE_LEVEL, ENV_SET_INPUT_DESCRIPTORS, ENV_SET_VARIABLES,
                       ENV_SET_CONTROLLER_INFO, ENV_SET_SUPPORT_ACHIEVEMENTS):
                return True
        except Exception:  # never let a Python exception cross the C boundary
            return False
        return False

    def _video(self, data: int, width: int, height: int, pitch: int) -> None:
        if data:
            self._frame = ctypes.string_at(data, pitch * height)
            self._frame_geom = (width, height, pitch)

    def _input(self, port: int, device: int, index: int, ident: int) -> int:
        if port == 0 and device == RETRO_DEVICE_JOYPAD and index == 0:
            return (self._keys >> ident) & 1
        return 0

    # -- control -----------------------------------------------------------

    def close(self) -> None:
        if Emulator._alive:
            self.lib.retro_unload_game()
            self.lib.retro_deinit()
            Emulator._alive = False
            self._tmp.cleanup()

    def __enter__(self) -> "Emulator":
        return self

    def __exit__(self, *exc) -> None:
        self.close()

    @staticmethod
    def keymask(buttons: Iterable[str] | str | None) -> int:
        if not buttons:
            return 0
        if isinstance(buttons, str):
            buttons = buttons.replace("+", " ").split()
        mask = 0
        for b in buttons:
            mask |= 1 << BUTTONS[b.upper()]
        return mask

    def set_input(self, buttons: Iterable[str] | str | None) -> None:
        """Set the buttons held from the next frame on (e.g. ``"A"``, ``["RIGHT", "B"]``)."""
        self._keys = self.keymask(buttons)

    def run(self, frames: int = 1, buttons: Iterable[str] | str | None = None) -> None:
        """Run ``frames`` frames; if ``buttons`` is given, hold them meanwhile."""
        if buttons is not None:
            self.set_input(buttons)
        for _ in range(frames):
            self.lib.retro_run()
            self.frame_count += 1

    def press(self, buttons: Iterable[str] | str, hold: int = 2, release: int = 2) -> None:
        """Press and release ``buttons``."""
        self.run(hold, buttons)
        self.run(release, [])

    def run_until(self, predicate, max_frames: int, buttons=None, step: int = 1) -> int:
        """Run until ``predicate(self)`` is true; return frames run or raise TimeoutError."""
        if buttons is not None:
            self.set_input(buttons)
        n = 0
        while not predicate(self):
            if n >= max_frames:
                raise TimeoutError(f"condition not met after {max_frames} frames")
            self.run(step)
            n += step
        return n

    # -- state -------------------------------------------------------------

    def save_state(self) -> bytes:
        size = self.lib.retro_serialize_size()
        buf = ctypes.create_string_buffer(size)
        if not self.lib.retro_serialize(buf, size):
            raise EmulatorError("retro_serialize failed")
        return buf.raw + struct.pack("<Q", self.frame_count)

    def load_state(self, state: bytes) -> None:
        body, (frames,) = state[:-8], struct.unpack("<Q", state[-8:])
        buf = ctypes.create_string_buffer(body, len(body))
        if not self.lib.retro_unserialize(buf, len(body)):
            raise EmulatorError("retro_unserialize failed")
        self.frame_count = frames

    def cpu_registers(self) -> dict[str, int]:
        """Best-effort CPU registers taken from an mGBA save state.

        mGBA's ``GBASerializedState`` stores r0-r15 at offset 0x20 and CPSR at
        0x60. The stored PC is the prefetch address (instruction + 4 in Thumb,
        + 8 in ARM); ``pc`` here is already corrected. Meant for debugging:
        the layout belongs to mGBA, not to the libretro API.
        """
        st = self.save_state()
        regs = struct.unpack_from("<16I", st, 0x20)
        (cpsr,) = struct.unpack_from("<I", st, 0x60)
        thumb = bool(cpsr & 0x20)
        out = {f"r{i}": v for i, v in enumerate(regs)}
        out.update(sp=regs[13], lr=regs[14], cpsr=cpsr, thumb=int(thumb),
                   pc=regs[15] - (4 if thumb else 8))
        return out

    def symbolize(self, addr: int) -> str:
        """``name+0xoff`` for a ROM/IWRAM address, using the map file."""
        if not hasattr(self, "_sorted_syms"):
            self._sorted_syms = sorted((a, n) for n, a in self.symbols.items())
        import bisect
        keys = [a for a, _ in self._sorted_syms]
        i = bisect.bisect_right(keys, addr & ~1) - 1
        if i < 0:
            return f"0x{addr:08x}"
        a, n = self._sorted_syms[i]
        return f"{n}+0x{(addr & ~1) - a:x}"

    # -- memory ------------------------------------------------------------

    def addr(self, sym: str | int) -> int:
        if isinstance(sym, int):
            return sym
        base, _, off = sym.partition("+")
        try:
            a = self.symbols[base.strip()]
        except KeyError:
            raise KeyError(f"symbol {base!r} not in map file") from None
        return a + (int(off, 0) if off else 0)

    def _host(self, addr: int, size: int) -> int:
        for start, length, ptr in self.regions:
            if start <= addr and addr + size <= start + length:
                return ptr + (addr - start)
        raise EmulatorError(f"address 0x{addr:08x} (+{size}) not mapped by the core")

    def read(self, sym: str | int, size: int) -> bytes:
        a = self.addr(sym)
        return ctypes.string_at(self._host(a, size), size)

    def write(self, sym: str | int, data: bytes) -> None:
        a = self.addr(sym)
        ctypes.memmove(self._host(a, len(data)), data, len(data))

    def _int(self, sym, fmt: str) -> int:
        return struct.unpack(fmt, self.read(sym, struct.calcsize(fmt)))[0]

    def u8(self, sym) -> int: return self._int(sym, "<B")
    def s8(self, sym) -> int: return self._int(sym, "<b")
    def u16(self, sym) -> int: return self._int(sym, "<H")
    def s16(self, sym) -> int: return self._int(sym, "<h")
    def u32(self, sym) -> int: return self._int(sym, "<I")
    def s32(self, sym) -> int: return self._int(sym, "<i")

    # -- video -------------------------------------------------------------

    def screenshot(self) -> tuple[int, int, bytes]:
        """Return (width, height, RGB888 bytes) of the last frame."""
        if self._frame is None:
            raise EmulatorError("no frame rendered yet")
        w, h, pitch = self._frame_geom
        fb, out = self._frame, bytearray(w * h * 3)
        o = 0
        if self.pixel_format == PIXEL_XRGB8888:
            for y in range(h):
                row = fb[y * pitch:y * pitch + w * 4]
                for x in range(0, w * 4, 4):
                    out[o], out[o + 1], out[o + 2] = row[x + 2], row[x + 1], row[x]
                    o += 3
        else:
            rgb565 = self.pixel_format == PIXEL_RGB565
            for y in range(h):
                for (v,) in struct.iter_unpack("<H", fb[y * pitch:y * pitch + w * 2]):
                    if rgb565:
                        r, g, b = v >> 11, (v >> 5) & 0x3F, v & 0x1F
                        out[o], out[o + 1], out[o + 2] = (r << 3) | (r >> 2), (g << 2) | (g >> 4), (b << 3) | (b >> 2)
                    else:
                        r, g, b = (v >> 10) & 0x1F, (v >> 5) & 0x1F, v & 0x1F
                        out[o], out[o + 1], out[o + 2] = (r << 3) | (r >> 2), (g << 3) | (g >> 2), (b << 3) | (b >> 2)
                    o += 3
        return w, h, bytes(out)

    def save_png(self, path: str | os.PathLike) -> None:
        w, h, rgb = self.screenshot()
        write_png(path, w, h, rgb)
