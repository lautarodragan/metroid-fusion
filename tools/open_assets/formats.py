"""Encoders/decoders for the data formats consumed by the game.

Everything here is written from the format descriptions that can be inferred
from this repository's own C code (e.g. ``RoomRleDecompress`` in src/room.c)
and from public GBA hardware/BIOS documentation (GBATEK). Nothing here reads or
needs the original ROM.

All generated content is procedural placeholder data for test fixtures.
"""

from __future__ import annotations

import struct
from typing import Iterable

# ---------------------------------------------------------------------------
# LZ77 (GBA BIOS SWI 0x11/0x12, "type 0x10")
# ---------------------------------------------------------------------------
#
# Header: u32 little endian = 0x10 | (decompressed_size << 8)
# Then blocks: 1 flag byte (MSB first), followed by 8 tokens:
#   flag bit 0 -> 1 literal byte
#   flag bit 1 -> 2 bytes: ((len - 3) << 4) | (disp >> 8), disp & 0xFF
#                 copy `len` (3..18) bytes from `dst - disp - 1`
#
# LZ77UnCompVram writes 16 bits at a time, so a back reference with
# disp == 0 (distance 1) reads a byte that has not been written yet and
# produces garbage. Streams meant for VRAM must use distance >= 2. This
# encoder always respects that, so its output is valid for both variants.

LZ77_MIN_LEN = 3
LZ77_MAX_LEN = 18
LZ77_WINDOW = 0x1000
LZ77_MIN_DIST = 2  # VRAM safe


def lz77_compress(data: bytes, max_candidates: int = 32) -> bytes:
    """Greedy LZ77 encoder producing a BIOS compatible, VRAM safe stream.

    The returned stream is padded with zeros to a multiple of 4 bytes.
    """
    n = len(data)
    if n >= 1 << 24:
        raise ValueError("LZ77 streams can describe at most 16 MiB")
    out = bytearray(struct.pack("<I", 0x10 | (n << 8)))
    chains: dict[bytes, list[int]] = {}

    pos = 0
    while pos < n:
        flag_index = len(out)
        out.append(0)
        flags = 0
        for bit in range(8):
            if pos >= n:
                break
            best_len = 0
            best_dist = 0
            if pos + LZ77_MIN_LEN <= n:
                key = data[pos:pos + LZ77_MIN_LEN]
                for cand in reversed(chains.get(key, ())[-max_candidates:]):
                    dist = pos - cand
                    if dist > LZ77_WINDOW:
                        break
                    if dist < LZ77_MIN_DIST:
                        continue
                    length = 0
                    limit = min(LZ77_MAX_LEN, n - pos)
                    while length < limit and data[cand + length] == data[pos + length]:
                        length += 1
                    if length > best_len:
                        best_len, best_dist = length, dist
                        if length == LZ77_MAX_LEN:
                            break
            if best_len >= LZ77_MIN_LEN:
                flags |= 0x80 >> bit
                disp = best_dist - 1
                out.append(((best_len - 3) << 4) | (disp >> 8))
                out.append(disp & 0xFF)
                step = best_len
            else:
                out.append(data[pos])
                step = 1
            for p in range(pos, pos + step):
                if p + LZ77_MIN_LEN <= n:
                    chains.setdefault(data[p:p + LZ77_MIN_LEN], []).append(p)
            pos += step
        out[flag_index] = flags
    while len(out) % 4:
        out.append(0)
    return bytes(out)


def lz77_decompress(stream: bytes, vram: bool = True) -> bytes:
    """Reference decoder. With ``vram`` it rejects distance-1 references."""
    header = struct.unpack_from("<I", stream, 0)[0]
    if header & 0xFF != 0x10:
        raise ValueError(f"not an LZ77 stream (type byte 0x{header & 0xFF:02x})")
    size = header >> 8
    out = bytearray()
    src = 4
    while len(out) < size:
        flags = stream[src]
        src += 1
        for bit in range(8):
            if len(out) >= size:
                break
            if flags & (0x80 >> bit):
                b0, b1 = stream[src], stream[src + 1]
                src += 2
                length = (b0 >> 4) + 3
                dist = (((b0 & 0xF) << 8) | b1) + 1
                if vram and dist < 2:
                    raise ValueError("distance-1 reference is not VRAM safe")
                if dist > len(out):
                    raise ValueError("reference before start of output")
                for _ in range(length):
                    out.append(out[-dist])
            else:
                out.append(stream[src])
                src += 1
    return bytes(out[:size])


# ---------------------------------------------------------------------------
# Room RLE (see RoomRleDecompress in src/room.c, type == TRUE)
# ---------------------------------------------------------------------------
#
# The output is an array of u16. It is written in two passes: the first pass
# fills the low byte of every u16, the second the high byte. Each pass:
#   mode byte: 1 -> 8 bit counters, otherwise 16 bit (big endian) counters
#   repeat: counter c (0 terminates the pass)
#     c & 0x80 (or 0x8000): repeat the next byte (c & 0x7F) times
#     else: copy the next c bytes literally
# The room width/height bytes that precede the stream are defined in C.


def _rle_pass_mode(values: bytes, wide: bool) -> bytes:
    limit = 0x7FFF if wide else 0x7F
    flag = 0x8000 if wide else 0x80

    def counter(v: int) -> bytes:
        return bytes([v >> 8, v & 0xFF]) if wide else bytes([v])

    out = bytearray([0 if wide else 1])
    i = 0
    n = len(values)
    while i < n:
        run = 1
        while i + run < n and run < limit and values[i + run] == values[i]:
            run += 1
        if run >= 3:
            out += counter(flag | run) + bytes([values[i]])
            i += run
            continue
        start = i
        while i < n and i - start < limit:
            if i + 2 < n and values[i] == values[i + 1] == values[i + 2]:
                break
            i += 1
        out += counter(i - start) + values[start:i]
    out += counter(0)
    return bytes(out)


def _rle_pass(values: bytes) -> bytes:
    """Encode one pass, picking whichever counter width is smaller."""
    narrow = _rle_pass_mode(values, wide=False)
    wide = _rle_pass_mode(values, wide=True)
    return narrow if len(narrow) <= len(wide) else wide


def room_rle_compress(blocks: Iterable[int]) -> bytes:
    blocks = list(blocks)
    lo = bytes(b & 0xFF for b in blocks)
    hi = bytes((b >> 8) & 0xFF for b in blocks)
    return _rle_pass(lo) + _rle_pass(hi)


def room_rle_decompress(stream: bytes) -> list[int]:
    src = 0
    passes: list[bytearray] = []
    for _ in range(2):
        data = bytearray()
        mode = stream[src]
        src += 1
        wide = mode != 1
        while True:
            if wide:
                value = (stream[src] << 8) | stream[src + 1]
                src += 2
                rep_flag, mask = 0x8000, 0x7FFF
            else:
                value = stream[src]
                src += 1
                rep_flag, mask = 0x80, 0x7F
            if value == 0:
                break
            if value & rep_flag:
                data += bytes([stream[src]]) * (value & mask)
                src += 1
            else:
                data += stream[src:src + value]
                src += value
        passes.append(data)
    lo, hi = passes
    if len(hi) < len(lo):
        hi += bytes(len(lo) - len(hi))
    return [lo[i] | (hi[i] << 8) for i in range(len(lo))]


# ---------------------------------------------------------------------------
# Graphics / palettes
# ---------------------------------------------------------------------------


def bgr555(r: int, g: int, b: int) -> int:
    """8 bit per channel RGB -> GBA BGR555."""
    return (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10)


def placeholder_palette(n_colors: int, seed: int) -> bytes:
    """A deterministic 16 colour ramp per row: index 0 black, 1..15 a hue ramp."""
    out = bytearray()
    for i in range(n_colors):
        row, idx = divmod(i, 16)
        if idx == 0:
            color = 0
        else:
            hue = (seed * 37 + row * 53) % 360
            r, g, b = _hue_to_rgb(hue)
            k = idx / 15
            color = bgr555(int(r * k), int(g * k), int(b * k))
        out += struct.pack("<H", color)
    return bytes(out)


def _hue_to_rgb(hue: int) -> tuple[int, int, int]:
    h = hue / 60
    x = int(255 * (1 - abs(h % 2 - 1)))
    table = [(255, x, 0), (x, 255, 0), (0, 255, x), (0, x, 255), (x, 0, 255), (255, 0, x)]
    return table[int(h) % 6]


def placeholder_tile_4bpp(color: int, style: int = 0) -> bytes:
    """One 8x8 4bpp tile: a 1px border in colour 15 and a fill or diagonal."""
    rows = []
    for y in range(8):
        px = []
        for x in range(8):
            if x in (0, 7) or y in (0, 7):
                c = 15
            elif style == 1 and x == y:
                c = 15
            else:
                c = color & 0xF
            px.append(c)
        # low nibble = left pixel
        rows.append(bytes(px[i] | (px[i + 1] << 4) for i in range(0, 8, 2)))
    return b"".join(rows)


def placeholder_gfx_4bpp(size: int, seed: int) -> bytes:
    tiles = bytearray()
    i = 0
    while len(tiles) < size:
        tiles += placeholder_tile_4bpp(1 + (seed + i) % 14, style=i % 2)
        i += 1
    return bytes(tiles[:size])


# ---------------------------------------------------------------------------
# DirectSound sample (m4a/"MusicPlayer2000" WaveData)
# ---------------------------------------------------------------------------
#
# u16 type (0), u16 status (0x4000 = loop), u32 frequency (Hz * 1024),
# u32 loop start, u32 sample count, then s8 PCM samples.

WAVE_HEADER_SIZE = 16


def silent_wave(region_size: int, rate_hz: int = 13379) -> bytes:
    """A header plus silence that exactly fills ``region_size`` bytes."""
    n = max(0, region_size - WAVE_HEADER_SIZE)
    header = struct.pack("<HHIII", 0, 0, rate_hz * 1024, 0, n)
    return (header + bytes(n))[:region_size]


def square_wave(region_size: int, period: int = 32, amp: int = 48,
                rate_hz: int = 13379, loop: bool = True) -> bytes:
    n = max(0, region_size - WAVE_HEADER_SIZE)
    header = struct.pack("<HHIII", 0, 0x4000 if loop else 0, rate_hz * 1024, 0, n)
    pcm = bytes((amp if (i % period) < period // 2 else -amp) & 0xFF for i in range(n))
    return (header + pcm)[:region_size]
