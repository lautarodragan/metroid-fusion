"""Generate a placeholder "open base ROM" that tools/extractor.py can consume.

The output is a test fixture, NOT a game, and contains no data from the
original ROM. It is an 8 MiB file in which every region listed in
database.json is filled with procedurally generated, format-valid placeholder
content, at the same offset and with exactly the same size as the original
region. Everything outside those
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
from layout import Layout, scan_lz_sources  # noqa: E402

ROM_SIZE = 0x800000
ROM_BASE = 0x08000000

BGCNT_BYTES = {
    "BGCNT_SIZE_256x256": 0x800,
    "BGCNT_SIZE_512x256": 0x1000,
    "BGCNT_SIZE_256x512": 0x1000,
    "BGCNT_SIZE_512x512": 0x2000,
}

CHAR_TERMINATOR = 0xFF00                      # include/constants/text.h
CLIPDATA_SOLID = 16                           # include/constants/clipdata.h


OPEN_MARKER = b"OPEN-BASEROM placeholder test data, not a game\0"


def is_open_baserom(path: Path) -> bool:
    """True if ``path`` is an open baserom written by this script."""
    with open(path, "rb") as f:
        # Prefix only, so files written with an older marker text still match.
        return f.read(len(b"OPEN-BASEROM")) == b"OPEN-BASEROM"


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


# ---------------------------------------------------------------------------
# Blobs the program needs to make sense of to boot.
#
# Regions are recognised by the symbol they are INCBINed as (see layout.py),
# so splitting or renaming database entries does not silently drop them; a
# rule that matches nothing is an error. Where only the original location is
# known, it is given as an offset in the baserom: the baserom has the layout
# of the original ROM, which never changes, whatever happens to the build.
# Values that point into the build (functions, other data) are taken from
# the ELF of a previous build, so they follow code and data that shift.
# ---------------------------------------------------------------------------

CHAR_NEXT_PAGE_ARROW = 0xFC00                 # include/constants/text.h
PLACEHOLDER_CHAR = 0x0040

# Interrupt vector table read by InterruptCode (asm/intr_main.s), in the order
# it tests the IF bits: DMA2, VBlank, HBlank, VCount, Timer0-3, DMA0, DMA1,
# DMA3, Keypad, Gamepak/other. Zero-filled, the first DMA2 interrupt jumps
# to 0 and the console resets in a loop.
INTERRUPT_TABLE_SYMBOL = "sInterruptHandlers"
INTERRUPT_HANDLERS = ["Dma2IntrCode", "CallbackCallVblank", "CallbackCallHBlank",
                      "CallbackCallVCount"] + ["Callback_Empty"] * 9

VOICEGROUP_RE = re.compile(r"^sVoicegroup_\w+$")       # m4a voicegroups, 12 byte voices
MONOLOGUE_RE = re.compile(r"^sMonologueText[A-Z]\w*_\d+$")
TEXT_POINTERS_RE = re.compile(r"^s\w*TextPointers\w*$")  # per-language string tables
# All the strings of every language (originally one blob). Filled with
# terminators, except the monologue pages.
TEXT_RANGE = (0x6b2fac, 0x72eee0)

# Cutscene, intro, ending and file select data that mixes LZ77 graphics with
# OAM animation data (`struct FrameData` arrays, OAM frames, tables of
# FrameData pointers). Zero-filled, an animation pointer leads the OAM
# drawing code to read a huge part count and write past the OAM buffer
# (overwriting gVBlankCallback). These ranges are filled with one 32-bit
# word, the "OAM-safe word", repeated: the build address of a 64 KiB aligned
# copy of itself. Whatever 4-aligned spot the code reads it from:
#   - as a FrameData array: pFrame = the word, timer = 0 (terminator),
#   - as an OAM frame:      part count = low half = 0 (nothing drawn),
#   - as a pointer table:   points to a valid FrameData array again.
# Regions in these ranges that the code passes to LZ77UncompVram/Wram get a
# zero header instead, so they decompress to nothing.
OAM_SAFE_RANGES = [
    (0x6094d0, 0x60b148),   # title intro OAM (IntroSpaceView*)
    (0x6131c8, 0x63a19c),   # intro / ending graphics and OAM
    (0x64e470, 0x662804),
    (0x662cfc, 0x663820),
    (0x6638a0, 0x682fac),
    (0x73421e, 0x7478a0),   # game over / file select
    (0x74dc48, 0x74e620),   # ending OAM
    (0x74e650, 0x74eb50),
    (0x79c394, 0x79c3c8),   # FrameData pointer tables (intro particles)
    (0x79c448, 0x79c5a4),
    (0x79e868, 0x79eca0),   # file select FrameData pointers and tables
]
# Tables inside the OAM-safe ranges that hold something else, by baserom
# offset: (offset, kind, words). "lz": pointers to an LZ77 source that
# decompresses to nothing; "text": pointers to an empty string table.
OAM_SAFE_OVERRIDES = [
    (0x79e874, "lz", 7),      # file select graphics, per language
    (0x79ec68, "text", 7),    # file select strings, per language
    (0x79ec84, "text", 7),
]


def in_ranges(r: Region, ranges) -> bool:
    return any(a <= r.addr and r.addr + r.size <= b for a, b in ranges)


def apply_known_layouts(rom: bytearray, regions: list[Region], layout: Layout) -> list[str]:
    """Overwrite the blobs listed above; returns notes for the summary."""
    blobs = [r for r in regions if r.category == "blob"]
    sym = {r.path: layout.symbol_of(r) for r in blobs}
    notes = []

    def put(r: Region, data: bytes) -> None:
        assert len(data) <= r.size, r.path
        rom[r.addr:r.addr + len(data)] = data

    # Interrupt handlers
    table = [r for r in blobs if sym[r.path] == INTERRUPT_TABLE_SYMBOL]
    if len(table) != 1:
        raise SystemExit(f"expected one region INCBINed as {INTERRUPT_TABLE_SYMBOL}, found {len(table)}")
    words = [layout.function(f) for f in INTERRUPT_HANDLERS] if layout.have_build else []
    put(table[0], struct.pack(f"<{len(words)}I", *words))
    notes.append("interrupt handlers: " + ("from " + layout.source if words else "EMPTY (needs a previous build)"))

    # Voicegroups: every voice plays the first direct sound sample
    samples = sorted((r for r in regions if r.category == "sound_sample"), key=lambda r: r.addr)
    sample = layout.region_address(samples[0])
    voice = struct.pack("<BBBBI4B", 0, 60, 0, 0, sample, 0xFF, 0, 0xFF, 0xA5)
    vgs = [r for r in blobs if sym[r.path] and VOICEGROUP_RE.match(sym[r.path])]
    if not vgs:
        raise SystemExit("no voicegroup regions (sVoicegroup_*) found")
    for r in vgs:
        put(r, voice * (r.size // 12))
    notes.append(f"voicegroups: {len(vgs)}")

    # Text: terminators everywhere; monologue pages advance on A at a "next
    # page" arrow. Some scenes wait for "more text follows" and then "end",
    # others only for "end"; two pages serve both: arrow, arrow, one
    # character, arrow, terminator.
    texts = [r for r in blobs if in_ranges(r, [TEXT_RANGE])]
    page = struct.pack("<5H", CHAR_NEXT_PAGE_ARROW, CHAR_NEXT_PAGE_ARROW, PLACEHOLDER_CHAR,
                       CHAR_NEXT_PAGE_ARROW, CHAR_TERMINATOR)
    pages = 0
    for r in texts:
        data = bytearray(struct.pack("<H", CHAR_TERMINATOR) * (r.size // 2))
        if sym[r.path] and MONOLOGUE_RE.match(sym[r.path]):
            assert r.size >= len(page), r.path
            data[:len(page)] = page
            pages += 1
        put(r, bytes(data))
    if not pages:
        raise SystemExit("no monologue regions (sMonologueText<Lang>_<N>) found")
    notes.append(f"text: {len(texts)} regions, {pages} monologues")
    empty_string = layout.address(regions, TEXT_RANGE[0])  # a terminator

    # Per-language string pointer tables -> empty strings
    tps = [r for r in blobs if sym[r.path] and TEXT_POINTERS_RE.match(sym[r.path])]
    for r in tps:
        put(r, struct.pack("<I", empty_string) * (r.size // 4))
    if not tps:
        raise SystemExit("no text pointer tables (s*TextPointers*) found")
    notes.append(f"text pointer tables: {len(tps)}")
    string_table = layout.region_address(tps[0])  # a table of empty strings

    # OAM-safe ranges
    oam = sorted((r for r in blobs if in_ranges(r, OAM_SAFE_RANGES)), key=lambda r: r.addr)
    lz_sources = scan_lz_sources()
    lz = [r for r in oam if sym[r.path] in lz_sources]
    built = {r.path: layout.region_address(r) for r in oam}
    # the word: a 64 KiB aligned build address inside these regions, clear
    # of the zeroed LZ77 headers
    word = None
    for r in oam:
        b = built[r.path]
        start = 4 if r in lz else 0
        cand = (b + start + 0xFFFF) & ~0xFFFF
        if cand + 4 <= b + r.size:
            word = cand
            break
    if word is None:
        raise SystemExit("no 64 KiB aligned address inside the OAM-safe ranges")
    wb = struct.pack("<I", word)
    for r in oam:
        b = built[r.path]
        put(r, bytes(wb[(b + i) % 4] for i in range(r.size)))
    lz_empty = None
    for r in lz:
        put(r, bytes(4))
        if lz_empty is None and built[r.path] % 4 == 0:
            lz_empty = built[r.path]
    if lz_empty is None:
        raise SystemExit("no LZ77 source found in the OAM-safe ranges")
    for off, kind, n in OAM_SAFE_OVERRIDES:
        target = {"lz": lz_empty, "text": string_table}[kind]
        rom[off:off + 4 * n] = struct.pack("<I", target) * n
    # self check: the word is in place at the baserom offset that maps to it
    for r in oam:
        b = built[r.path]
        if b <= word < b + r.size:
            o = r.addr + word - b
            assert struct.unpack_from("<I", rom, o)[0] == word
    notes.append(f"OAM-safe: {len(oam)} regions, word {word:#x}, {len(lz)} empty LZ77 sources")
    if layout.unresolved:
        notes.append(f"WARNING: {len(layout.unresolved)} regions not found in the build, "
                     f"assumed at their database offset: {sorted(layout.unresolved)[:5]}")
    return notes


def generate(args) -> int:
    regions = load_regions()
    meta = scan_c_metadata()
    elf = args.elf or (str(Path(args.map).with_suffix(".elf")) if args.map else None)
    layout = Layout(elf, args.map)

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
        else:
            data, note = b"", "zero" if c != "blob" else "zero/known-layout(below)"
        if len(data) > r.size:
            raise AssertionError(f"{r.path}: generated {len(data)} > {r.size}")
        if note in ("does not fit", "no dims in C") or "SHORTER" in note:
            failures.append(f"{r.path} ({r.size}B): {note}")
        notes[(c, note.split(" ")[0])] += 1
        rom[r.addr:r.addr + len(data)] = data

    layout_notes = apply_known_layouts(rom, regions, layout)
    validate(rom, regions, meta)
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
    for n in layout_notes:
        print("  " + n)
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
    ap.add_argument("--map", help="linker map of a previous build; its .elf next to it (or --elf) "
                                  "gives the addresses that pointer tables need (see build_open_rom.py)")
    ap.add_argument("--elf", help="ELF of a previous build (default: the --map path with .elf)")
    ap.add_argument("--gfx-lz-size", type=lambda s: int(s, 0), default=0x800,
                    help="decompressed size for LZ77 graphics placeholders (default 0x800)")
    return generate(ap.parse_args())


if __name__ == "__main__":
    sys.exit(main())
