"""Readable text for the open baserom: an open font and placeholder strings.

What the game expects (see book/src/test-baserom-font.md):

- ``sCharactersGfx`` (``text_characters.gfx``, 192 KiB) is one sheet of 4bpp
  8x8 tiles. Character ``c`` is a 16x16 cell: its top half is tile ``c`` (and
  tile ``c + 1`` for glyphs wider than 8 px), its bottom half is 32 tiles
  later (``c * 32 + 0x400`` bytes). So character codes come in rows of 64
  where only the first 32 are usable; single-byte codes map like Shift-JIS
  bytes, ``((b & 0xE0) << 1) | (b & 0x1F)``: ASCII ``0x20-0x7F`` is
  ``0x40-0x5F``, ``0x80-0x9F`` and ``0xC0-0xDF``.
- ``sCharacterWidths`` (C, ``src/data/menus/pause_screen_misc_data.c``) is
  the advance width of codes ``0..1183``; others advance 10 px.
- Pixels: 0 = background, 2 = ink, 3 = shadow (the draw routines recolour 2
  and 3 with a ``color`` argument as ``2 + 2 * color`` / ``3 + 2 * color``;
  1 is left alone). Message boxes turn 0 into 15.

The glyphs are Spleen 6x12 (BSD 2-Clause, vendored in third_party/spleen)
fitted into each character's original advance width, with a drop shadow.
Only printable ASCII is drawn; every other cell stays empty.

The strings are original placeholders that say what each text is for
(``[Message: missiles]``), written into the text blob together with the
pointer tables that reference them. Control codes keep cutscenes advancing.

``--font-from-rom`` (make_open_baserom.py) instead copies the font regions
from your own baserom, a local option (the output, like every .gba, is gitignored).
"""

from __future__ import annotations

import hashlib
import re
import struct
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE / "third_party" / "spleen"))

import formats  # noqa: E402
import spleen_6x12 as base_font  # noqa: E402
from inventory import ROOT, Region  # noqa: E402

FONT_PATH = "text_characters.gfx"
FONT_SIZE = 192 * 1024
CELL = 16                       # glyph cells are 16x16 pixels
HALF_OFFSET = 0x400             # bytes from a cell's top half to its bottom half
DEFAULT_WIDTH = 10              # TextGetCharacterWidth for codes past the table

PAPER, INK, SHADOW = 1, 2, 3
GLYPH_TOP = 2                   # first row of the 12-row Spleen bitmap in the cell

# include/constants/text.h
CHAR_WIDTH_MASK = 0x8000
CHAR_NEXT_PAGE_ARROW = 0xFC00
CHAR_NEW_PAGE = 0xFD00
CHAR_NEW_LINE = 0xFE00
CHAR_TERMINATOR = 0xFF00
CHAR_SPACE = 0x40

# The real ROM the font regions may be copied from (README: mf_us baserom)
REAL_ROM_SHA1 = "ca33f4348c2c05dd330d37b97e2c5a69531dfe87"
REAL_ROM_SIZE = 0x800000
# Regions holding glyphs of the text font (database.json paths)
FONT_REGION_PATHS = (FONT_PATH,)


# ---------------------------------------------------------------------------
# Character codes
# ---------------------------------------------------------------------------


def char_code(byte: int) -> int:
    """Character code of a single-byte (ASCII / JIS X 0201) character."""
    return ((byte & 0xE0) << 1) | (byte & 0x1F)


TOKENS = {
    "{ARROW}": CHAR_NEXT_PAGE_ARROW,
    "{PAGE}": CHAR_NEW_PAGE,
}


def encode(text: str, terminate: bool = True) -> list[int]:
    """Encode placeholder text: printable ASCII, "\\n" and {ARROW}/{PAGE}."""
    out: list[int] = []
    i = 0
    while i < len(text):
        for tok, code in TOKENS.items():
            if text.startswith(tok, i):
                out.append(code)
                i += len(tok)
                break
        else:
            ch = text[i]
            if ch == "\n":
                out.append(CHAR_NEW_LINE)
            elif 0x20 <= ord(ch) < 0x7F:
                out.append(char_code(ord(ch)))
            else:
                raise ValueError(f"unsupported character {ch!r} in {text!r}")
            i += 1
    if terminate:
        out.append(CHAR_TERMINATOR)
    return out


def pack(codes: list[int]) -> bytes:
    return struct.pack(f"<{len(codes)}H", *codes)


# ---------------------------------------------------------------------------
# Width table (game data, in C)
# ---------------------------------------------------------------------------

WIDTHS_RE = re.compile(r"sCharacterWidths\s*\[\s*(\d+)\s*\]\s*=\s*\{([^}]*)\}", re.S)


def load_widths(root: Path = ROOT) -> list[int]:
    text = (root / "src" / "data" / "menus" / "pause_screen_misc_data.c").read_text()
    m = WIDTHS_RE.search(text)
    if not m:
        raise SystemExit("sCharacterWidths not found in pause_screen_misc_data.c")
    values = [int(v) for v in re.findall(r"\d+", m.group(2))]
    if len(values) != int(m.group(1)):
        raise SystemExit(f"sCharacterWidths: {len(values)} values for [{m.group(1)}]")
    return values


def width_of(widths: list[int], code: int) -> int:
    return widths[code] if code < len(widths) else DEFAULT_WIDTH


def text_width(widths: list[int], codes: list[int]) -> int:
    """Pixel width of the first line of ``codes``."""
    w = 0
    for c in codes:
        if c in (CHAR_NEW_LINE, CHAR_TERMINATOR):
            break
        if (c & 0xFF00) == CHAR_WIDTH_MASK:
            w += c & 0xFF
        elif c < 0x8000:
            w += width_of(widths, c)
    return w


# ---------------------------------------------------------------------------
# Glyph fitting
# ---------------------------------------------------------------------------


def _columns(rows: list[str]) -> list[str]:
    return ["".join(r[x] for r in rows) for x in range(len(rows[0]))]


def _rows(cols: list[str], height: int) -> list[str]:
    return ["".join(c[y] for c in cols) for y in range(height)] if cols else [""] * height


def fit_glyph(rows: list[str], advance: int) -> list[list[int]]:
    """Fit a base glyph into ``advance`` pixels: a 16x16 grid of pixel values.

    The ink keeps one free column at the right (letter spacing) and gets a
    one pixel shadow to the lower right. If it does not fit, duplicated
    columns are merged first, then the shadow is dropped on the right edge,
    then the emptiest inner columns are removed.

    The whole advance is painted with PAPER (colour 1, which the draw
    routines never recolour) so a line of text sits on a dark band and stays
    readable over any background. Columns past the advance stay 0: the
    routines OR whole tiles together, and the next glyph starts there.
    """
    height = len(rows)
    cols = _columns(rows)
    ink = [i for i, c in enumerate(cols) if "#" in c]
    paper = min(advance, CELL)
    grid = [[PAPER] * paper + [0] * (CELL - paper) for _ in range(CELL)]
    if not ink:
        return grid
    cols = cols[ink[0]:ink[-1] + 1]
    room = max(1, advance - 1)          # pixels the ink + shadow may use
    # merge adjacent identical columns (keeps strokes, narrows bowls)
    while len(cols) + 1 > room:
        for i in range(len(cols) - 1):
            if cols[i] == cols[i + 1] and "#" in cols[i]:
                del cols[i]
                break
        else:
            break
    while len(cols) > room:              # last resort: drop the emptiest inner column
        inner = range(1, len(cols) - 1) if len(cols) > 2 else range(len(cols))
        i = min(inner, key=lambda k: cols[k].count("#"))
        del cols[i]
    shadow_w = 1 if len(cols) + 1 <= room else 0
    x0 = max(0, (room - len(cols) - shadow_w) // 2)
    bitmap = _rows(cols, height)
    for y, row in enumerate(bitmap):
        for x, px in enumerate(row):
            if px != "#":
                continue
            gx, gy = x0 + x, GLYPH_TOP + y
            grid[gy][gx] = INK
            sx, sy = gx + 1, gy + 1
            if sy < CELL and sx < x0 + len(cols) + shadow_w and grid[sy][sx] == PAPER:
                grid[sy][sx] = SHADOW
    # a shadow pixel may have been written before the ink that covers it
    for y, row in enumerate(bitmap):
        for x, px in enumerate(row):
            if px == "#":
                grid[GLYPH_TOP + y][x0 + x] = INK
    return grid


def tile_bytes(grid: list[list[int]], tx: int, ty: int) -> bytes:
    """4bpp tile (tx, ty) of a pixel grid, low nibble = left pixel."""
    out = bytearray()
    for y in range(ty * 8, ty * 8 + 8):
        row = grid[y]
        for x in range(tx * 8, tx * 8 + 8, 2):
            out.append((row[x] & 0xF) | ((row[x + 1] & 0xF) << 4))
    return bytes(out)


def put_glyph(sheet: bytearray, code: int, grid: list[list[int]], advance: int) -> None:
    tiles = 2 if advance > 8 else 1
    for half in range(2):
        for tx in range(tiles):
            off = code * 32 + half * HALF_OFFSET + tx * 32
            sheet[off:off + 32] = tile_bytes(grid, tx, half)


def build_font(widths: list[int]) -> bytes:
    """The whole ``sCharactersGfx`` sheet: printable ASCII, the rest empty."""
    sheet = bytearray(FONT_SIZE)
    for byte, rows in base_font.GLYPHS.items():
        code = char_code(byte)
        advance = width_of(widths, code)
        put_glyph(sheet, code, fit_glyph(rows, advance), advance)
    return bytes(sheet)


def render_text(sheet: bytes, widths: list[int], codes: list[int], palette=None):
    """Render one line like TextDrawCharacter does (for previews and tests).

    Returns (width, height, rgb bytes)."""
    palette = palette or {0: (60, 140, 60), PAPER: (24, 32, 64), INK: (255, 255, 255),
                          SHADOW: (40, 48, 88)}
    total = text_width(widths, codes) + 8
    img = [[0] * total for _ in range(CELL)]
    x = 0
    for c in codes:
        if c in (CHAR_NEW_LINE, CHAR_TERMINATOR):
            break
        if (c & 0xFF00) == CHAR_WIDTH_MASK:
            x += c & 0xFF
            continue
        adv = width_of(widths, c)
        tiles = 2 if adv > 8 else 1
        for half in range(2):
            for tx in range(tiles):
                off = c * 32 + half * HALF_OFFSET + tx * 32
                t = sheet[off:off + 32]
                for py in range(8):
                    for px in range(8):
                        if tx == 1 and px >= adv - 8:
                            continue
                        b = t[py * 4 + px // 2]
                        v = (b >> 4) if px & 1 else (b & 0xF)
                        if v and x + tx * 8 + px < total:
                            img[half * 8 + py][x + tx * 8 + px] |= v
        x += adv
    rgb = bytearray()
    for row in img:
        for v in row:
            rgb += bytes(palette.get(v, (255, 0, 255)))
    return total, CELL, bytes(rgb)


# ---------------------------------------------------------------------------
# Palettes and tilemaps for the text layers
# ---------------------------------------------------------------------------


def bgr555(r: int, g: int, b: int) -> int:
    return (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10)


# index: 2 + 2 * color = ink, 3 + 2 * color = shadow (color 0..6)
TEXT_COLORS = [
    ((255, 255, 255), (0, 0, 16)),       # 0: white
    ((255, 232, 96), (88, 64, 16)),      # 1: yellow
    ((120, 232, 255), (16, 56, 88)),     # 2: cyan
    ((144, 255, 136), (16, 72, 24)),     # 3: green
    ((255, 168, 72), (96, 40, 8)),       # 4: orange
    ((255, 128, 168), (96, 16, 48)),     # 5: pink
    ((255, 240, 160), (120, 72, 0)),     # 6: highlight
]
TEXT_BACKGROUND = (8, 16, 40)


def text_palette_row(brightness: float = 1.0) -> bytes:
    """16 colours for a text layer: 0 transparent, ink/shadow pairs from 2.

    ``brightness`` < 1 fades the ink towards the shadow (monologue fade in)."""
    def mix(a, b):
        return tuple(round(y + (x - y) * brightness) for x, y in zip(a, b))
    entries = [bgr555(*TEXT_BACKGROUND), bgr555(24, 32, 64)]
    for ink, shadow in TEXT_COLORS:
        entries += [bgr555(*mix(ink, TEXT_BACKGROUND)), bgr555(*shadow)]
    assert len(entries) == 16
    return struct.pack("<16H", *entries)


def text_tilemap(rows: dict[int, int], cols: range, pal: int, blank: int,
                 size: int = 0x800) -> bytes:
    """A 32-wide BG map showing a text area laid out 32 tiles per row.

    ``rows`` maps screen row -> first tile of the text row shown there;
    screen column ``x`` in ``cols`` shows tile ``first + x - cols.start``.
    Everything else is the ``blank`` tile.
    """
    words = [blank | (pal << 12)] * (size // 2)
    for y, first in rows.items():
        for x in cols:
            words[y * 32 + x] = (first + x - cols.start) | (pal << 12)
    return struct.pack(f"<{len(words)}H", *words)


# Cutscene monologue (SpecialCutsceneProcessMonologue): line L (0-8) is drawn
# into tiles L * 64 + col (top half) and L * 64 + 32 + col (bottom half),
# col < 28, character base 0, map sIntroTilemap_662804, palette rows 12-15
# (sIntroPal_663820). Each tile fades in: the code decrements the palette
# number of its map entry three times, so entries start at row 15 (faint)
# and end at row 12 (full).
MONOLOGUE_PAL_ROWS = 4


def monologue_tilemap() -> bytes:
    rows = {}
    for line in range(9):
        rows[1 + 2 * line] = line * 64
        rows[2 + 2 * line] = line * 64 + 32
    return text_tilemap(rows, range(1, 29), pal=15, blank=63)


def monologue_palette() -> bytes:
    """Rows 12 (full) to 15 (faint)."""
    return b"".join(text_palette_row(1 - i / MONOLOGUE_PAL_ROWS) for i in range(MONOLOGUE_PAL_ROWS))


# Subtitles in the new-file intro and the ending (NewFileIntroProcessAdamText,
# EndingProcessAdamText): two lines at VRAM 0xD000 (tile 0x280 of character
# base 2) and 0xD800, 32 tiles per row, shown by BG0 with the map
# sIntroSamusShipFlyingTextTilemap (VRAM 0xE000) and palette row 15
# (sPal_598a8c, and row 15 of the scene palettes loaded whole).
SUBTITLE_FIRST_TILE = 0x280
SUBTITLE_PAL = 15
SUBTITLE_BLANK = 0x2FF              # last tile of the second line, never reached
SUBTITLE_TOP_ROW = 15
# (palette, its row that lands in BG palette row 15)
SUBTITLE_PALETTES = (
    ("sPal_598a8c", 0),                 # loaded alone into row 15
    ("sIntroBslSpaceBgPal", 7),         # loaded into rows 8-15
    ("sSr388SpaceAndSurfacePal", 15), ("sPal_5a8e44", 15), ("sIntroMetroidVaccineBgPal", 15),
    ("sIntroSamusNervousSystemBgPal", 15), ("sIntroSamusFoundPal", 15),
    ("sIntroSamusRebornBgPal", 15), ("sIntroArrivingAtBslSpaceMapPal", 15),
    ("sIntroLandingOnBslBgPal", 15), ("sIntroSamusSittingPal", 15),
)


def subtitle_tilemap() -> bytes:
    rows = {}
    for line in range(2):
        rows[SUBTITLE_TOP_ROW + 2 * line] = SUBTITLE_FIRST_TILE + line * 64
        rows[SUBTITLE_TOP_ROW + 2 * line + 1] = SUBTITLE_FIRST_TILE + line * 64 + 32
    # BG0 is scrolled 8 px to the right (HOFS -8): map column 0 is screen column 1
    return text_tilemap(rows, range(0, 30), pal=SUBTITLE_PAL, blank=SUBTITLE_BLANK)


# ---------------------------------------------------------------------------
# Placeholder strings
# ---------------------------------------------------------------------------

LANGUAGES = ["Japanese", "Hiragana", "English", "German", "French", "Italian", "Spanish"]

# sMonologueTextPointers index -> where it is shown (from the code that
# selects it: enum Cutscene in include/globals.h and new_file_intro.c)
MONOLOGUES = {
    0: "intro / arrival",
    1: "elevator: reminder",
    2: "elevator: trust",
    3: "elevator: SA-X",
    4: "elevator: animals",
    5: "elevator: incident",
    6: "Federation",
    7: "ending, in the ship",
    8: "SR388 preview",
    9: "on SR388",
    10: "after the fall",
    11: "fainting",
    12: "found, part 1",
    13: "found, part 2",
    14: "found, part 3",
    15: "found, part 4",
    16: "surgery",
    17: "cured",
    18: "Adam panel",
}


def monologue_text(index: int, max_codes: int = 1 << 16) -> list[int]:
    """Two pages; some scenes wait for "more text" (two arrows) before the
    end, others only for the end, and this serves both (as before):
    page 1, arrow, arrow, page 2, arrow, terminator. The longest variant
    that fits ``max_codes`` (the original region holds the string)."""
    what = MONOLOGUES.get(index, "cutscene")
    variants = [
        (f"[Monologue {index}: {what}]", "\n(next page)"),
        (f"[Monologue {index}]", "\n(2)"),
    ]
    for page1, page2 in variants:
        codes = encode(page1 + "{ARROW}{ARROW}" + page2 + "{ARROW}")
        if len(codes) <= max_codes:
            return codes
    raise ValueError(f"no monologue placeholder fits in {max_codes} characters")


ABILITY_RE = re.compile(r"\[ABILITY_COUNT_(\w+)\]\s*=\s*\{[^}]*?\.messageNumber\s*=\s*(\d+)", re.S)
LOCATION_RE = re.compile(r"enum LocationText\s*\{([^}]*)\}", re.S)


def message_names(root: Path = ROOT) -> dict[int, str]:
    """sMessageTextPointers index -> short description, from the C sources."""
    names = {i: f"security level {i + 1}" for i in range(4)}
    text = (root / "src" / "data" / "event_data.c").read_text()
    for name, number in ABILITY_RE.findall(text):
        if name != "NONE":
            names.setdefault(int(number), name.lower().replace("_", " "))
    return names


def location_names(root: Path = ROOT) -> list[str]:
    m = LOCATION_RE.search((root / "include" / "location_text.h").read_text())
    if not m:
        return []
    names = re.findall(r"\bLT_(\w+)", m.group(1))
    return [n.lower().replace("_", " ") for n in names if n != "END"]


def table_strings(kind: str, count: int, root: Path = ROOT) -> list[str]:
    """Placeholder strings for one per-language pointer table."""
    if kind == "Message":
        names = message_names(root)
        out = []
        for i in range(count):
            if i < 21:
                out.append(f"[Message: {names.get(i, f'item {i}')}]")
            elif i < 43:
                out.append(f"[Banner {i - 21}]")
            else:
                out.append(f"[Message {i}: Navigation]\nPlaceholder text.")
        return out
    if kind == "Location":
        names = location_names(root)
        return [f"[Location: {names[i] if i < len(names) else i}]" for i in range(count)]
    if kind == "NavConversation":
        return [f"[Navigation briefing {i}]\nPlaceholder text." for i in range(count)]
    if kind == "PauseScreen":
        return [f"[Pause text {i}]" for i in range(count)]
    return [f"[Text {i}]" for i in range(count)]


# sFileSelectUnk_79ec68[language][i]; drawn by FileSelectDrawText, i = 0
# header, 1 file menu, 2-4 and 24 prompts, 5-10 corrupted file notices.
FILE_SELECT_TEXTS = {
    0: "  SELECT A FILE",
    1: "START   COPY   ERASE",
    2: "[Prompt: start this file?]",
    3: "[Prompt: copy to which file?]",
    4: "[Prompt: erase this file?]",
}
FILE_SELECT_TEXT_COUNT = 32
FILE_SELECT_EMPTY = " [empty file]"   # sFileSelectUnk_79ec84[language][0]


def file_select_strings() -> list[str]:
    out = []
    for i in range(FILE_SELECT_TEXT_COUNT):
        if i in FILE_SELECT_TEXTS:
            out.append(FILE_SELECT_TEXTS[i])
        elif 5 <= i <= 10:
            out.append(f"[Notice: file {'ABC'[(i - 5) % 3]} damaged]")
        else:
            out.append(f"[File select text {i}]")
    return out


# ---------------------------------------------------------------------------
# Writing it into the baserom
# ---------------------------------------------------------------------------

TEXT_POINTERS_RE = re.compile(r"^s(\w+?)TextPointers(" + "|".join(LANGUAGES) + r")$")
TEXT_BLOB_START = 0x6b2fac          # baserom offset of the (unused) start of the text blob


class Arena:
    """Sequential allocator inside one baserom region we own entirely."""

    def __init__(self, rom: bytearray, region: Region, build_address: int, start: int = 0):
        self.rom, self.r, self.base, self.pos = rom, region, build_address, start
        self.cache: dict[bytes, int] = {}

    def alloc(self, data: bytes, align: int = 2) -> int:
        """Store ``data``; returns its build address (aligned there)."""
        key = bytes([align]) + data
        if key in self.cache:
            return self.cache[key]
        while (self.base + self.pos) % align:
            self.pos += 1
        if self.pos + len(data) > self.r.size:
            raise SystemExit(f"text arena {self.r.path} full")
        off = self.r.addr + self.pos
        self.rom[off:off + len(data)] = data
        addr = self.base + self.pos
        self.pos += len(data)
        self.cache[key] = addr
        return addr

    def string(self, text: str) -> int:
        return self.alloc(pack(encode(text)))

    def table(self, addresses: list[int]) -> int:
        return self.alloc(struct.pack(f"<{len(addresses)}I", *addresses), align=4)


def apply_text(rom: bytearray, regions: list[Region], layout, widths: list[int]) -> list[str]:
    """Strings, pointer tables and text layers; runs after apply_known_layouts."""
    sym = {r.path: layout.symbol_of(r) for r in regions}
    by_sym = {s: r for r in regions if (s := sym[r.path])}
    notes = []

    def region(symbol: str) -> Region:
        if symbol not in by_sym:
            raise SystemExit(f"font.py: no region INCBINed as {symbol}")
        return by_sym[symbol]

    def put(r: Region, data: bytes) -> None:
        assert len(data) <= r.size, (r.path, len(data), r.size)
        rom[r.addr:r.addr + len(data)] = data

    blob = next(r for r in regions if r.addr <= TEXT_BLOB_START < r.addr + r.size)
    # the first u16 stays a terminator: apply_known_layouts points empty texts there
    arena = Arena(rom, blob, layout.region_address(blob), start=TEXT_BLOB_START - blob.addr + 2)

    # monologues: in place, they are pointed to from C
    mono_re = re.compile(r"^sMonologueText(" + "|".join(LANGUAGES) + r")_(\d+)$")
    n = 0
    for r in regions:
        m = mono_re.match(sym[r.path] or "")
        if m:
            data = pack(monologue_text(int(m.group(2)), r.size // 2))
            put(r,data + pack([CHAR_TERMINATOR]) * ((r.size - len(data)) // 2))
            n += 1
    notes.append(f"text: {n} monologues")

    # per-language pointer tables
    n = 0
    for r in regions:
        m = TEXT_POINTERS_RE.match(sym[r.path] or "")
        if not m:
            continue
        strings = table_strings(m.group(1), r.size // 4)
        put(r, struct.pack(f"<{len(strings)}I", *(arena.string(s) for s in strings)))
        n += 1
    notes.append(f"text: {n} pointer tables")

    # file select: string tables and per-line tile offsets
    fs_table = arena.table([arena.string(s) for s in file_select_strings()])
    empty_table = arena.table([arena.string(FILE_SELECT_EMPTY)] * 4)
    zeros = arena.alloc(bytes(16), align=4)
    offsets_table = arena.table([zeros] * FILE_SELECT_TEXT_COUNT)
    for symbol, target in (("sFileSelectUnk_79ec68", fs_table),
                           ("sFileSelectUnk_79ec84", empty_table),
                           ("sFileSelectUnk_79e928", offsets_table)):
        r = region(symbol)
        put(r, struct.pack("<I", target) * (r.size // 4))
    notes.append(f"text: arena {arena.pos} of {blob.size} bytes used")

    # text layers: monologue tilemap + palette
    put_lz(rom, region("sIntroTilemap_662804"), monologue_tilemap())
    pal = region("sIntroPal_663820")
    put(pal, monologue_palette()[:pal.size])
    put_lz(rom, region("sIntroSamusShipFlyingTextTilemap"), subtitle_tilemap())
    for symbol, row in SUBTITLE_PALETTES:
        r = region(symbol)
        assert (row + 1) * 32 <= r.size, symbol
        rom[r.addr + row * 32:r.addr + row * 32 + 32] = text_palette_row()
    notes.append(f"text: monologue and subtitle maps, {len(SUBTITLE_PALETTES)} palettes")
    notes += file_select_layers(rom, region)
    return notes


def put_lz(rom: bytearray, r: Region, data: bytes) -> None:
    stream = formats.lz77_compress(data)
    if len(stream) > r.size:
        raise SystemExit(f"{r.path}: compressed text tilemap {len(stream)} > {r.size}")
    formats.lz77_decompress(stream, vram=True)
    rom[r.addr:r.addr + r.size] = stream + bytes(r.size - len(stream))


# File select (src/menus/file_select.c, FileSelectInit): BG0/1/2 use
# character base 2 (VRAM 0x8000) where the text is drawn 32 tiles per row:
# header at tile 0, file info at rows 2/4/6 (col 6), the menu at row 12
# (0xB000) and the prompts at row 18 (0xC800). The maps show those rows in
# place; the palette row 1 gets the text colours.
FS_BLANK_TILE = 0x2FF            # 0xDFE0, never written
FS_PAL = 1


def file_select_layers(rom: bytearray, region) -> list[str]:
    def rows(*ys):
        return {y: y * 32 for y in ys}

    upper = text_tilemap(rows(0, 1, 2, 3, 4, 5, 6, 7), range(1, 31), FS_PAL, FS_BLANK_TILE)
    lower = text_tilemap(rows(12, 13, 18, 19, 20, 21), range(1, 31), FS_PAL, FS_BLANK_TILE)
    menu = text_tilemap(rows(12, 13, 18, 19), range(1, 31), FS_PAL, FS_BLANK_TILE)
    put_lz(rom, region("sFileSelectUnk_73cfac"), upper)     # BG2, always shown
    put_lz(rom, region("sFileSelectUnk_73d5ec"), lower)     # BG0, prompts
    put_lz(rom, region("sFileSelectUnk_73d380"), menu)      # BG1 (through EWRAM), file menu
    row = text_palette_row()
    full = region("sFileSelectUnk_7476a0")                  # whole BG palette
    rom[full.addr:full.addr + full.size] = (row * (full.size // 32 + 1))[:full.size]
    for symbol in ("sFileSelectUnk_73db84", "sFileSelectUnk_73dac4"):  # row 0 overrides
        r = region(symbol)
        rom[r.addr:r.addr + r.size] = (row * (r.size // 32 + 1))[:r.size]
    return ["text: file select maps and palette"]


# ---------------------------------------------------------------------------
# --font-from-rom: copy the font glyphs from your own baserom (local option)
# ---------------------------------------------------------------------------

FONT_FROM_ROM_NOTE = (
    "note: --font-from-rom: font glyphs in {out} were read from your own baserom;\n"
    "      the reference screenshots of tests/emu assume the open font, so expect\n"
    "      differences there. Keep the file local (*.gba is gitignored)."
)


def check_real_rom(data: bytes, expected_sha1: str = REAL_ROM_SHA1,
                   expected_size: int = REAL_ROM_SIZE) -> None:
    if len(data) != expected_size:
        raise SystemExit(f"--font-from-rom: expected a {expected_size:#x} byte ROM, got {len(data):#x}")
    digest = hashlib.sha1(data).hexdigest()
    if digest != expected_sha1:
        raise SystemExit(f"--font-from-rom: sha1 {digest} is not the expected {expected_sha1} "
                         "(Metroid Fusion USA)")


def copy_font_regions(rom: bytearray, real: bytes, regions: list[Region],
                      expected_sha1: str = REAL_ROM_SHA1,
                      expected_size: int = REAL_ROM_SIZE) -> list[Region]:
    """Copy the font regions (and nothing else) from ``real`` into ``rom``.

    Both are laid out like the original ROM (database.json offsets)."""
    check_real_rom(real, expected_sha1, expected_size)
    copied = [r for r in regions if r.path in FONT_REGION_PATHS]
    if len(copied) != len(FONT_REGION_PATHS):
        raise SystemExit(f"--font-from-rom: font regions missing from database.json: "
                         f"{set(FONT_REGION_PATHS) - {r.path for r in copied}}")
    for r in copied:
        rom[r.addr:r.addr + r.size] = real[r.addr:r.addr + r.size]
    return copied


# ---------------------------------------------------------------------------
# Entry point for make_open_baserom.py
# ---------------------------------------------------------------------------


def apply(rom: bytearray, regions: list[Region], layout, font_from_rom: str | None = None) -> list[str]:
    """Font, strings and text layers. Call after apply_known_layouts."""
    widths = load_widths()
    if font_from_rom:
        copied = copy_font_regions(rom, Path(font_from_rom).read_bytes(), regions)
        notes = [f"font: COPIED from {font_from_rom} ({', '.join(r.path for r in copied)}) "
                 "(local option)"]
    else:
        r = next((r for r in regions if r.path == FONT_PATH), None)
        if r is None or r.size != FONT_SIZE:
            raise SystemExit(f"font.py: region {FONT_PATH} ({FONT_SIZE} bytes) not found")
        rom[r.addr:r.addr + r.size] = build_font(widths)
        notes = [f"font: Spleen {base_font.WIDTH}x{base_font.HEIGHT} fitted to sCharacterWidths"]
    return notes + apply_text(rom, regions, layout, widths)
