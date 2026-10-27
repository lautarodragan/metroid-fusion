"""Generate a placeholder "open base ROM" that tools/extractor.py can consume.

The output is NOT a game and contains no Nintendo data. It is an 8 MiB file in
which every region listed in database.json is filled with procedurally
generated, format-valid placeholder content (CC0-1.0), at the same offset and
with exactly the same size as the original region. Everything outside those
regions is zero. Code is never taken from here: the extractor only copies
data regions, the program itself is built from this repository.

Usage:
    python3 tools/open_assets/make_open_baserom.py -o open_baserom.gba
    # then, to try a build (needs agbcc etc.), copy it to mf_us_baserom.gba
    # in a scratch checkout and run tools/extractor.py + make.

It refuses to overwrite an existing file unless --force is given, so it can
never clobber a real baserom by accident.

Status: research prototype. Boot has NOT been verified (see
docs/open_assets_research.md, phase A).
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
        return struct.pack("<H", CHAR_TERMINATOR) * (r.size // 2), "text terminators"
    if name == TEXT_POINTER_BLOB:
        return struct.pack("<I", ROM_BASE + TEXT_ADDR[0]) * (r.size // 4), "ptrs -> terminator"
    return b"", "zero (unknown)"


TEXT_ADDR = [0]


def generate(args) -> int:
    regions = load_regions()
    meta = scan_c_metadata()
    samples = sorted(r.addr for r in regions if r.category == "sound_sample")
    for r in regions:
        if r.path == TEXT_BLOB:
            TEXT_ADDR[0] = r.addr

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
        elif c == "blob":
            data, note = gen_blob(r, m, args, samples[0])
        else:
            data, note = b"", "zero"
        if len(data) > r.size:
            raise AssertionError(f"{r.path}: generated {len(data)} > {r.size}")
        if note in ("does not fit", "no dims in C") or "SHORTER" in note:
            failures.append(f"{r.path} ({r.size}B): {note}")
        notes[(c, note.split(" ")[0])] += 1
        rom[r.addr:r.addr + len(data)] = data

    validate(rom, regions, meta)

    out = Path(args.output)
    if out.exists() and not args.force:
        print(f"refusing to overwrite {out} (use --force)", file=sys.stderr)
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
    ap.add_argument("--gfx-lz-size", type=lambda s: int(s, 0), default=0x800,
                    help="decompressed size for LZ77 graphics placeholders (default 0x800)")
    return generate(ap.parse_args())


if __name__ == "__main__":
    sys.exit(main())
