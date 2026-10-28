"""Generate a placeholder "open base ROM" that tools/extractor.py can consume.

The output is NOT a game and contains no Nintendo data. It is an 8 MiB file in
which every region listed in database.json is filled with procedurally
generated, format-valid placeholder content (CC0-1.0), at the same offset and
with exactly the same size as the original region. Everything outside those
regions is zero. Code is never taken from here: the extractor only copies
data regions, the program itself is built from this repository.

Usage:
    python3 tools/open_assets/build_open_rom.py      # generate + build, two passes
    python3 tools/open_assets/make_open_baserom.py -o open_baserom.gba [--map mf_us.map]

A few tables hold addresses of our own functions (interrupt vectors); they
are filled from the linker map of a previous build (--map), which is why
build_open_rom.py builds twice.

The output starts with a marker (OPEN_MARKER). An existing file is only
overwritten if it carries that marker, or with --force, so a real or
synthetic baserom is never clobbered by accident.

Status: the resulting ROM boots in mGBA (HLE BIOS) through the title intro,
title screen, file select and new-file intro into the first room; see
docs/emu_tests.md for the emulator tests that check this.
"""

from __future__ import annotations

import argparse
import hashlib
import re
import struct
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import formats  # noqa: E402
from inventory import ROOT, Region, load_regions  # noqa: E402

ROM_SIZE = 0x800000
ROM_BASE = 0x08000000

BGCNT_BYTES = {
    "BGCNT_SIZE_256x256": 0x800,
    "BGCNT_SIZE_512x256": 0x1000,
    "BGCNT_SIZE_256x512": 0x1000,
    "BGCNT_SIZE_512x512": 0x2000,
}

# Region handling that needs knowledge of a specific Blob (see the doc).
VOICEGROUP_BLOB = "Blob_a5710_a8cdc.bin"      # m4a voicegroups (12 byte entries)
TEXT_BLOB = "Blob_6b2fac_72eee0.bin"          # strings for every language
TEXT_POINTER_BLOB = "Blob_79c5c0_79cdd8.bin"  # message/location pointer tables
CHAR_TERMINATOR = 0xFF00                      # include/constants/text.h
CLIPDATA_SOLID = 16                           # include/constants/clipdata.h


OPEN_MARKER = b"OPEN-BASEROM placeholder data, not a game (CC0)\0"


def is_open_baserom(path: Path) -> bool:
    """True if ``path`` is an open baserom written by this script."""
    with open(path, "rb") as f:
        return f.read(len(OPEN_MARKER)) == OPEN_MARKER


def seed_of(path: str) -> int:
    return int.from_bytes(hashlib.sha1(path.encode()).digest()[:4], "little")


# ---------------------------------------------------------------------------
# Metadata that lives in C next to each INCBIN (BG size, room dimensions)
# ---------------------------------------------------------------------------

INCBIN_RE = re.compile(r'INCBIN_\w+\("data/([^"]+)"\)')


def scan_c_metadata() -> dict[str, dict]:
    meta: dict[str, dict] = {}
    for p in (ROOT / "src").rglob("*.c"):
        text = p.read_text(errors="replace")
        for m in INCBIN_RE.finditer(text):
            start = text.rfind("{", 0, m.start())
            prefix = text[start:m.start()] if start != -1 else ""
            info: dict = {}
            bg = re.search(r"BGCNT_SIZE_\d+x\d+", prefix)
            if bg:
                info["decomp_size"] = BGCNT_BYTES[bg.group(0)]
            w = re.search(r"(\d+),\s*//\s*Room width", prefix)
            h = re.search(r"(\d+),\s*//\s*Room height", prefix)
            if w and h:
                info["width"], info["height"] = int(w.group(1)), int(h.group(1))
            if info:
                meta[m.group(1)] = info
    return meta


# ---------------------------------------------------------------------------
# Per category generators. Each returns (bytes, note); bytes may be shorter
# than the region (the rest stays zero) but never longer.
# ---------------------------------------------------------------------------


def fit_lz(make, size: int, region: int, min_size: int = 32):
    """Compress make(size) halving size until it fits in the region."""
    while size >= min_size:
        stream = formats.lz77_compress(make(size))
        if len(stream) <= region:
            return stream, size
        size //= 2
    return None, 0


def gen_gfx_lz(r: Region, meta: dict, args) -> tuple[bytes, str]:
    stream, size = fit_lz(lambda n: formats.placeholder_gfx_4bpp(n, seed_of(r.path)),
                          args.gfx_lz_size, r.size)
    if stream is None:
        return b"", "does not fit"
    return stream, f"lz {size}B"


def tilemap_bytes(n: int, uniform: bool) -> bytes:
    out = bytearray()
    for i in range(n // 2):
        x, y = i % 32, (i // 32) % 32
        tile = 1 if uniform else 1 + ((x // 2 + y // 2) % 4)
        out += struct.pack("<H", tile)
    return bytes(out)


def gen_tilemap_lz(r: Region, meta: dict, args) -> tuple[bytes, str]:
    want = meta.get("decomp_size", 0x800)
    for uniform in (False, True):
        stream = formats.lz77_compress(tilemap_bytes(want, uniform))
        if len(stream) <= r.size:
            return stream, f"lz {want}B" + (" uniform" if uniform else "")
    stream, size = fit_lz(lambda n: tilemap_bytes(n, True), want // 2, r.size)
    if stream is None:
        return b"", "does not fit"
    return stream, f"lz {size}B SHORTER than expected {want}B"


def gen_tilemap_raw(r: Region, meta: dict, args) -> tuple[bytes, str]:
    if r.path.endswith(".tm.rle"):
        # RoomRleDecompress type 0: leading size code byte (0 -> 0x800)
        return bytes([0]) + formats.room_rle_compress([0] * 0x400), "rle type0"
    return b"", "zero"


def gen_tileset_metatiles(r: Region, meta: dict, args) -> tuple[bytes, str]:
    words = [0]
    for i in range((r.size - 2) // 2):
        block = i // 4
        if block == 0:
            words.append(0)
        else:
            tile = 1 + (block % 31)
            pal = 2 + (block % 12)
            words.append((pal << 12) | tile)
    return struct.pack(f"<{len(words)}H", *words)[:r.size], "metatiles"


def room_layer(meta: dict, value: int, shape: str) -> list[int]:
    """'box': solid border; 'floor': solid top and bottom rows only."""
    w, h = meta["width"], meta["height"]
    if shape == "box":
        return [value if x in (0, w - 1) or y in (0, h - 1) else 0
                for y in range(h) for x in range(w)]
    return [value if y in (0, h - 1) else 0 for y in range(h) for x in range(w)]


def gen_room_rle(r: Region, meta: dict, args, value: int) -> tuple[bytes, str]:
    if "width" not in meta:
        return b"", "no dims in C"
    for v, note in ((value, "box"), (value, "floor"), (0, "empty")):
        stream = formats.room_rle_compress(room_layer(meta, v, note))
        if len(stream) <= r.size:
            return stream, note
    return b"", "does not fit"


def gen_room_bg(r: Region, meta: dict, args):
    return gen_room_rle(r, meta, args, 1 if r.path.endswith("_bg1.rle") else 0)


def gen_room_clip(r: Region, meta: dict, args):
    return gen_room_rle(r, meta, args, CLIPDATA_SOLID)


def gen_sound(r: Region, meta: dict, args):
    if args.silent:
        return formats.silent_wave(r.size), "silent"
    return formats.square_wave(r.size, period=16 + seed_of(r.path) % 48), "square"


def gen_blob(r: Region, meta: dict, args, first_sample_addr: int):
    name = r.path
    if name == VOICEGROUP_BLOB:
        voice = struct.pack("<BBBBI4B", 0, 60, 0, 0, ROM_BASE + first_sample_addr, 0xFF, 0, 0xFF, 0xA5)
        return voice * (r.size // 12), "voicegroups -> sample 0"
    if name == TEXT_BLOB:
        out = bytearray(struct.pack("<H", CHAR_TERMINATOR) * (r.size // 2))
        # Monologues (new file intro) advance on A at a "next page" arrow.
        # Some scenes wait for "more text follows" and then "end", others
        # only for "end"; two pages serve both: arrow, arrow, one character,
        # arrow, terminator.
        page = struct.pack("<5H", CHAR_NEXT_PAGE_ARROW, CHAR_NEXT_PAGE_ARROW, PLACEHOLDER_CHAR,
                           CHAR_NEXT_PAGE_ARROW, CHAR_TERMINATOR)
        addrs = sorted(set(monologue_text_addresses()))
        for a, nxt in zip(addrs, addrs[1:] + [ROM_BASE + r.addr + r.size]):
            o = a - ROM_BASE - r.addr
            assert 0 <= o and a + len(page) <= nxt, hex(a)
            out[o:o + len(page)] = page
        return bytes(out), "text terminators"
    if name == TEXT_POINTER_BLOB:
        return struct.pack("<I", ROM_BASE + TEXT_ADDR[0]) * (r.size // 4), "ptrs -> terminator"
    return b"", "zero (unknown)"


TEXT_ADDR = [0]
CHAR_NEXT_PAGE_ARROW = 0xFC00                 # include/constants/text.h
PLACEHOLDER_CHAR = 0x0040


def monologue_text_addresses() -> list[int]:
    """String addresses listed in sMonologueTextPointers* (src/new_file_intro.c)."""
    text = (ROOT / "src" / "new_file_intro.c").read_text()
    addrs = []
    for m in re.finditer(r"sMonologueTextPointers\w+\[\d+\]\s*=\s*\{(.*?)\};", text, re.S):
        addrs += [int(x, 16) for x in re.findall(r"\(u16\*\)(0x[0-9a-fA-F]+)", m.group(1))]
    if not addrs:
        raise SystemExit("could not find sMonologueTextPointers* in src/new_file_intro.c")
    return addrs

# Blobs that are tables of pointers into our own code. Their values depend on
# where the linker put each function, so they are resolved from the .map file
# of a previous build (see --map). Entries are symbol names; a trailing "|1"
# marks a Thumb function (bit 0 set so that `bx` switches to Thumb).
SYMBOL_TABLES: dict[str, list[str]] = {
    # Interrupt vector table read by InterruptCode (asm/intr_main.s), in the
    # order it tests the IF bits: DMA2, VBlank, HBlank, VCount, Timer0-3,
    # DMA0, DMA1, DMA3, Keypad, Gamepak/other.
    "Blob_a5224_a5258.bin": [
        "Dma2IntrCode|1", "CallbackCallVblank|1", "CallbackCallHBlank|1", "CallbackCallVCount|1",
    ] + ["Callback_Empty|1"] * 9,
}


# Cutscene/intro blobs that mix compressed graphics with OAM animation data
# (`struct FrameData` arrays, OAM frames, tables of FrameData pointers) that
# the code reaches through literal addresses. Zero-filled, an animation
# pointer would lead the OAM drawing code to read a huge part count and write
# past the OAM buffer. So these blobs are filled with one 32-bit word,
# OAM_SAFE_WORD, repeated. It is the address of a 64 KiB aligned word inside
# such a blob, so whatever 4-aligned spot the code reads it from:
#   - as a FrameData array: pFrame = OAM_SAFE_WORD, timer = 0 (terminator),
#   - as an OAM frame:      part count = low half = 0 (nothing drawn),
#   - as a pointer table:   points to a valid FrameData array again.
# The offsets listed per blob are LZ77 sources passed to LZ77UncompVram
# (from the asm literals); their 4-byte header is zeroed so they decompress
# to nothing instead of a huge size read from the pattern.
OAM_SAFE_BLOBS: dict[str, list[int]] = {
    "Blob_6094d0_60b148.bin": [],
    "Blob_6131c8_63a19c.bin": [
        0x0, 0x1f20, 0x54dc, 0x86d4, 0xe5e0, 0x1072c, 0x13570, 0x1842c, 0x24070,
        0x24630, 0x24bf0, 0x2548c, 0x25a4c, 0x260d4, 0x263f0, 0x269fc],
    "Blob_64e470_662804.bin": [0xa770, 0xaf74, 0x116ec],
    "Blob_662cfc_663820.bin": [0x89c],
    "Blob_6638a0_682fac.bin": [
        0xec20, 0x11238, 0x117f8, 0x14074, 0x143f0, 0x148bc, 0x15b80, 0x19f2c,
        0x1e17c, 0x1e804, 0x1ef08, 0x1f35c],
    # file select screen (asm/disasm_0x0809deb4.s)
    "Blob_73421e_7478a0.bin": [
        0xe, 0x585a, 0x84c6, 0x8a8a, 0x8d8e, 0x9162, 0x93ce, 0x9a02, 0xed96, 0x12ec2],
    "Blob_74dc48_74e620.bin": [],
    "Blob_74e650_74eb50.bin": [],
    # 0x0c: per-language LZ77 graphics; 0x400/0x41c: per-language pointers
    # to string tables. The rest are FrameData pointers.
    "Blob_79e868_79eca0.bin": [(0xc, "lzptr", 7), (0x400, "textptr", 14)],
    # tables of FrameData pointers used by the title intro
    "Blob_79c394_79c3c8.bin": [],
    "Blob_79c448_79c5a4.bin": [],
}
OAM_SAFE_WORD = ROM_BASE + 0x620000  # inside Blob_6131c8_63a19c
# An LZ77 source with a zeroed header (see the lists above): decompresses to
# nothing. Used for tables of pointers to graphics.
LZ_EMPTY = ROM_BASE + 0x73421e + 0xe
TEXT_POINTER_ADDR = [0]


def gen_oam_safe_blob(r: Region) -> tuple[bytes, str]:
    # Aligned to absolute addresses (some blobs start at odd halfwords).
    word = struct.pack("<I", OAM_SAFE_WORD)
    out = bytearray(word[(r.addr + i) % 4] for i in range(r.size))
    for item in OAM_SAFE_BLOBS[r.path]:
        if isinstance(item, int):
            out[item:item + 4] = bytes(4)
            continue
        o, kind, n = item
        target = {"lzptr": LZ_EMPTY, "textptr": ROM_BASE + TEXT_POINTER_ADDR[0]}[kind]
        out[o:o + 4 * n] = struct.pack("<I", target) * n
    return bytes(out), "oam-safe"


def check_oam_safe_word(rom: bytes) -> None:
    off = OAM_SAFE_WORD - ROM_BASE
    assert struct.unpack_from("<I", rom, off)[0] == OAM_SAFE_WORD, "OAM_SAFE_WORD not in place"
    assert struct.unpack_from("<I", rom, LZ_EMPTY - ROM_BASE)[0] == 0, "LZ_EMPTY not zero"


def load_map(path: str | None) -> dict[str, int]:
    syms: dict[str, int] = {}
    if not path:
        return syms
    sym_re = re.compile(r"^\s+0x([0-9a-fA-F]+)\s+([A-Za-z_][\w.$]*)(?:\s*=\s*\.)?\s*$")
    for line in Path(path).read_text(errors="replace").splitlines():
        m = sym_re.match(line)
        if m and int(m.group(1), 16) >= 0x02000000:
            syms.setdefault(m.group(2), int(m.group(1), 16))
    return syms


def gen_symbol_table(r: Region, syms: dict[str, int]):
    entries = SYMBOL_TABLES[r.path]
    if not syms:
        return b"", "needs --map"
    words = []
    for e in entries:
        name, _, thumb = e.partition("|")
        if name not in syms:
            raise SystemExit(f"{r.path}: symbol {name} not found in the map file")
        words.append(syms[name] | (1 if thumb else 0))
    data = struct.pack(f"<{len(words)}I", *words)
    assert len(data) == r.size, (r.path, len(data), r.size)
    return data, "code pointers"


def generate(args) -> int:
    regions = load_regions()
    meta = scan_c_metadata()
    syms = load_map(args.map)

    samples = sorted(r.addr for r in regions if r.category == "sound_sample")
    for r in regions:
        if r.path == TEXT_BLOB:
            TEXT_ADDR[0] = r.addr
        if r.path == TEXT_POINTER_BLOB:
            TEXT_POINTER_ADDR[0] = r.addr

    rom = bytearray(ROM_SIZE)
    notes: Counter = Counter()
    failures: list[str] = []
    for r in regions:
        m = meta.get(r.path, {})
        c = r.category
        if c == "gfx_lz":
            data, note = gen_gfx_lz(r, m, args)
        elif c in ("gfx_raw", "gfx_samus", "font"):
            data, note = formats.placeholder_gfx_4bpp(r.size, seed_of(r.path)), "tiles"
        elif c == "palette":
            data, note = formats.placeholder_palette(r.size // 2, seed_of(r.path)), "palette"
        elif c == "tilemap_lz":
            data, note = gen_tilemap_lz(r, m, args)
        elif c == "tilemap_raw":
            data, note = gen_tilemap_raw(r, m, args)
        elif c == "tileset_metatiles":
            data, note = gen_tileset_metatiles(r, m, args)
        elif c == "room_bg_rle":
            data, note = gen_room_bg(r, m, args)
        elif c == "room_clipdata_rle":
            data, note = gen_room_clip(r, m, args)
        elif c == "sound_sample":
            data, note = gen_sound(r, m, args)
        elif r.path in SYMBOL_TABLES:
            data, note = gen_symbol_table(r, syms)
        elif r.path in OAM_SAFE_BLOBS:
            data, note = gen_oam_safe_blob(r)
        elif c == "blob":
            data, note = gen_blob(r, m, args, samples[0])
        else:
            data, note = b"", "zero"
        if len(data) > r.size:
            raise AssertionError(f"{r.path}: generated {len(data)} > {r.size}")
        if note in ("does not fit", "no dims in C", "needs --map") or "SHORTER" in note:
            failures.append(f"{r.path} ({r.size}B): {note}")
        notes[(c, note.split(" ")[0])] += 1
        rom[r.addr:r.addr + len(data)] = data

    validate(rom, regions, meta)
    check_oam_safe_word(rom)
    # No database region starts below 0xa5224, and the extractor never reads
    # the header, so the first bytes carry a marker identifying the file.
    assert all(r.addr >= len(OPEN_MARKER) for r in regions)
    rom[:len(OPEN_MARKER)] = OPEN_MARKER

    out = Path(args.output)
    if out.exists() and not args.force and not is_open_baserom(out):
        print(f"refusing to overwrite {out}: it is not an open baserom made by this "
              "script (use --force)", file=sys.stderr)
        return 1
    out.write_bytes(rom)
    print(f"wrote {out} ({len(rom)} bytes, {len(regions)} regions)")
    for (c, n), k in sorted(notes.items()):
        print(f"  {c:20} {n:12} {k}")
    if failures:
        print(f"{len(failures)} regions could not get their ideal placeholder:")
        for f in failures[:20]:
            print("  " + f)
    return 0


def validate(rom: bytes, regions: list[Region], meta: dict) -> None:
    """Decode every compressed region again to prove the streams are valid."""
    for r in regions:
        blob = bytes(rom[r.addr:r.addr + r.size])
        if r.category in ("gfx_lz", "tilemap_lz") and blob[:1] == b"\x10":
            formats.lz77_decompress(blob, vram=True)
        elif r.category in ("room_bg_rle", "room_clipdata_rle") and "width" in meta.get(r.path, {}):
            if any(blob):
                m = meta[r.path]
                out = formats.room_rle_decompress(blob)
                assert len(out) == m["width"] * m["height"], r.path


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("-o", "--output", required=True, help="output file (never overwritten without --force)")
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--silent", action="store_true", help="silent samples instead of square waves")
    ap.add_argument("--map", help="linker map of a previous build, used to fill tables of code "
                                  "pointers (needed for the ROM to boot; see build_open_rom.sh)")
    ap.add_argument("--gfx-lz-size", type=lambda s: int(s, 0), default=0x800,
                    help="decompressed size for LZ77 graphics placeholders (default 0x800)")
    return generate(ap.parse_args())


if __name__ == "__main__":
    sys.exit(main())
