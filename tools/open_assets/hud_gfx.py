"""Placeholder HUD graphics: energy counter, tanks, ammo counters, minimap frame.

In game the HUD is drawn with sprites (HudDrawOam in src/hud.c), using tiles
of the common sprites sheet (``sCommonSpritesGfx``, OBJ tiles 64-511, see
sprite_gfx.py) and small blocks that src/hud.c copies over parts of it:

- energy: two 32x16 sprites at tiles 0x50 / 0x54. Tiles 0x50-0x52 and 0x70
  come from the sheet (label and icon), the two energy digits (tens, ones)
  are copied to 0x71/0x72 from ``sEnergyDigitsGfx`` and the tank rows to
  0x53-0x57 / 0x73-0x77 from ``sEnergyTanksGfx_*`` (two tanks per tile);
- missiles / power bombs: 16x16 sprites at 0x58 / 0x5A; the top row is the
  icon (``sMissileIconGfx``, ``sPowerBombIconGfx``, normal and selected),
  the bottom row is built from ``sAmmoDigitsGfx`` (4 pixel wide digits, three
  digits and an end cap per two tiles);
- minimap: a 32x32 sprite at tile 0xDC whose inner 3x3 tiles are rebuilt
  from the map; its top row and right column come from the sheet; the
  8x8 sprite at 0xC5 / 0xC6 is the blinking "you are here" marker;
- escape timer: ``sEscapeDigitsGfx`` (8x16 digits) and its palette.

All glyphs below are drawn for this placeholder set.
"""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import oam_art as A  # noqa: E402
from oam_art import FX_BLACK, FX_B1, FX_B2, FX_B3, FX_E2, FX_E3, FX_E4, FX_G2, FX_G3, FX_K1, FX_K2, FX_K3, FX_WHITE  # noqa: E402,F401

# 3x5 glyphs ('#' = ink), used for the ammo digits and the HUD label
FONT3 = {
    "0": ["###", "#.#", "#.#", "#.#", "###"],
    "1": [".#.", "##.", ".#.", ".#.", "###"],
    "2": ["###", "..#", "###", "#..", "###"],
    "3": ["###", "..#", ".##", "..#", "###"],
    "4": ["#.#", "#.#", "###", "..#", "..#"],
    "5": ["###", "#..", "###", "..#", "###"],
    "6": ["###", "#..", "###", "#.#", "###"],
    "7": ["###", "..#", ".#.", ".#.", ".#."],
    "8": ["###", "#.#", "###", "#.#", "###"],
    "9": ["###", "#.#", "###", "..#", "###"],
    "E": ["###", "#..", "##.", "#..", "###"],
    "N": ["#.#", "###", "###", "###", "#.#"],
    "R": ["##.", "#.#", "##.", "#.#", "#.#"],
    "G": [".##", "#..", "#.#", "#.#", ".##"],
    "Y": ["#.#", "#.#", ".#.", ".#.", ".#."],
}

# 5x7 digits for the energy counter
FONT5 = {
    "0": [".###.", "#...#", "#..##", "#.#.#", "##..#", "#...#", ".###."],
    "1": ["..#..", ".##..", "..#..", "..#..", "..#..", "..#..", ".###."],
    "2": [".###.", "#...#", "....#", "...#.", "..#..", ".#...", "#####"],
    "3": ["####.", "....#", "....#", ".###.", "....#", "....#", "####."],
    "4": ["...#.", "..##.", ".#.#.", "#..#.", "#####", "...#.", "...#."],
    "5": ["#####", "#....", "####.", "....#", "....#", "#...#", ".###."],
    "6": [".###.", "#....", "#....", "####.", "#...#", "#...#", ".###."],
    "7": ["#####", "....#", "...#.", "..#..", ".#...", ".#...", ".#..."],
    "8": [".###.", "#...#", "#...#", ".###.", "#...#", "#...#", ".###."],
    "9": [".###.", "#...#", "#...#", ".####", "....#", "....#", ".###."],
}


def blank():
    return [0] * 64


def glyph(px, g, x0, y0, ink, w=8, shadow=None):
    """Draw glyph rows ``g`` into a ``w``-wide pixel list at (x0, y0)."""
    h = len(px) // w
    for y, row in enumerate(g):
        for x, ch in enumerate(row):
            if ch == "#":
                if shadow is not None and 0 <= y0 + y + 1 < h and 0 <= x0 + x + 1 < w:
                    i = (y0 + y + 1) * w + x0 + x + 1
                    if px[i] == 0:
                        px[i] = shadow
                if 0 <= y0 + y < h and 0 <= x0 + x < w:
                    px[(y0 + y) * w + x0 + x] = ink


def split_tiles(px, w):
    """A w x 8 pixel strip -> list of 8x8 tiles."""
    return [[px[y * w + tx * 8 + x] for y in range(8) for x in range(8)] for tx in range(w // 8)]


# ---------------------------------------------------------------------------
# Tiles placed in the common sheet (tile number -> 64 pixels)
# ---------------------------------------------------------------------------

def hud_sheet_tiles() -> dict:
    tiles = {}
    # "ENERGY" label across 0x50-0x52, under it nothing (tanks follow)
    strip = [0] * (24 * 8)
    for i, ch in enumerate("ENERGY"):
        glyph(strip, FONT3[ch], i * 4, 1, FX_WHITE, w=24, shadow=FX_BLACK)
    for i, t in enumerate(split_tiles(strip, 24)):
        tiles[0x50 + i] = t
    # 0x70: energy icon (a small charged cell) left of the digits
    px = blank()
    for y in range(1, 7):
        for x in range(1, 6):
            edge = x in (1, 5) or y in (1, 6)
            px[y * 8 + x] = FX_BLACK if edge else (FX_E3 if y > 2 else FX_E4)
    px[0 * 8 + 3] = FX_BLACK
    px[0 * 8 + 2] = px[0 * 8 + 4] = 0
    tiles[0x70] = px
    # minimap frame: top row (0xDC-0xDF) and right column (0xFF, 0x11F, 0x13F)
    for c in range(4):
        px = blank()
        for x in range(8):
            px[0 * 8 + x] = FX_K3
            px[1 * 8 + x] = FX_K1
        if c == 0:
            for y in range(8):
                px[y * 8 + 0] = FX_K3
        if c == 3:
            for y in range(8):
                px[y * 8 + 7] = FX_K3
                px[y * 8 + 6] = FX_K1
        tiles[0xDC + c] = px
    for t in (0xFF, 0x11F, 0x13F):
        px = blank()
        for y in range(8):
            px[y * 8 + 7] = FX_K3
            px[y * 8 + 6] = FX_K1
        if t == 0x13F:
            for x in range(8):
                px[7 * 8 + x] = FX_K3
        tiles[t] = px
    # "you are here" marker: bright and dim
    for t, col in ((0xC5, FX_WHITE), (0xC6, FX_E3)):
        px = blank()
        for y in range(2, 6):
            for x in range(2, 6):
                px[y * 8 + x] = col if 2 < x < 5 or 2 < y < 5 else FX_BLACK
        tiles[t] = px
    return tiles


# ---------------------------------------------------------------------------
# Blocks copied by src/hud.c
# ---------------------------------------------------------------------------

def energy_digits() -> bytes:
    out = []
    for d in "0123456789":
        px = blank()
        glyph(px, FONT5[d], 1, 0, FX_WHITE, shadow=FX_BLACK)
        out.append(px)
    return A.tiles_to_bytes(out)


def tank_tile(left, right):
    """One 8x8 tile with two tank slots: None (no tank), 'empty' or 'full'."""
    px = blank()
    for slot, state in ((0, left), (4, right)):
        if state is None:
            continue
        for y in range(1, 7):
            for x in range(slot, slot + 3):
                edge = x in (slot, slot + 2) or y in (1, 6)
                if state == "full":
                    px[y * 8 + x] = FX_B3 if edge else FX_B2
                else:
                    px[y * 8 + x] = FX_K2 if edge else FX_BLACK
    return px


def energy_tanks(full: bool, entries: int) -> bytes:
    """``entries`` blocks of 8 tiles (256 bytes) of which 5 are copied.

    Empty[n]: n empty tanks (two per tile). Full[k]: k + 1 tiles of full
    tanks (the code copies k + 1 tiles over the empty row).
    """
    out = []
    for n in range(entries):
        tiles = []
        for t in range(8):
            if full:
                tiles.append(tank_tile("full", "full"))
            else:
                k = n - 2 * t if n < 10 else n - 10 - 2 * t
                tiles.append(tank_tile("empty" if k > 0 else None, "empty" if k > 1 else None))
        out += tiles
    return A.tiles_to_bytes(out)


def ammo_digits() -> bytes:
    """36 tiles; a digit uses the left 4 pixels of its tile.

    0-9 digits, 10 blank, 11 end cap; 24-35 the same when the weapon is
    selected (src/hud.c adds 0x300 bytes = 24 tiles).
    """
    tiles = []
    for hl in (False, True):
        ink = FX_G3 if hl else FX_WHITE
        for i in range(12):
            px = blank()
            if i < 10:
                glyph(px, FONT3[str(i)], 0, 2, ink)
                for y in range(2, 8):     # shadow on the right column
                    if px[y * 8 + 3] == 0 and px[y * 8 + 2] == ink:
                        px[y * 8 + 3] = FX_BLACK
            elif i == 11:  # end cap: a small bracket
                for y in range(1, 8):
                    px[y * 8 + 1] = ink if hl else FX_K2
                px[1 * 8 + 0] = px[7 * 8 + 0] = ink if hl else FX_K2
            tiles.append(px)
        tiles += [blank() for _ in range(12)] if not hl else []
    return A.tiles_to_bytes(tiles[:36])


def missile_icon() -> bytes:
    out = []
    for hl in (False, True):
        strip = [0] * (16 * 8)
        body = FX_G2 if hl else FX_K3
        for x in range(3, 13):
            for y in (3, 4):
                strip[y * 16 + x] = body
            strip[2 * 16 + x] = FX_BLACK
            strip[5 * 16 + x] = FX_BLACK
        for x, y in ((13, 3), (13, 4), (14, 3), (14, 4)):
            strip[y * 16 + x] = FX_E3 if not hl else FX_G3
        strip[3 * 16 + 15] = strip[4 * 16 + 15] = FX_BLACK
        for y in (1, 2, 5, 6):  # fins
            strip[y * 16 + 3] = FX_E2
            strip[y * 16 + 4] = FX_E2
        out += split_tiles(strip, 16)
    return A.tiles_to_bytes(out)


def power_bomb_icon() -> bytes:
    out = []
    for hl in (False, True):
        cv = A.Canvas(32)
        cv.disc(8, 4, 3.4, FX_G2 if hl else FX_K3)
        cv.disc(7, 3, 1.2, FX_WHITE)
        cv.outline(FX_BLACK)
        strip = [cv.get(x, y) for y in range(8) for x in range(16)]
        out += split_tiles(strip, 16)
    return A.tiles_to_bytes(out)


def escape_digits() -> bytes:
    """64 tiles: 8x16 digits in columns 0-9 (top row, bottom row 32 tiles
    below) and the separators at columns 10 (':') and 42 ('.')."""
    tiles = [blank() for _ in range(64)]
    big = {d: [r for row in FONT5[d] for r in (row, row)] for d in FONT5}  # stretched 5x14
    for i, d in enumerate("0123456789"):
        px = [0] * (8 * 16)
        glyph(px, big[d], 1, 1, FX_E3, shadow=FX_BLACK)
        tiles[i] = px[:64]
        tiles[32 + i] = px[64:]
    colon = blank()
    for y in (2, 5):
        colon[y * 8 + 3] = colon[y * 8 + 4] = FX_E3
    tiles[10] = colon
    dot = blank()
    dot[6 * 8 + 3] = dot[6 * 8 + 4] = FX_E3
    tiles[42] = dot
    return A.tiles_to_bytes(tiles)


def blocks() -> dict:
    """{region path: bytes} for the HUD regions (not the common sheet)."""
    return {
        "hud/energy_digits.gfx": energy_digits(),
        "hud/energy_tanks_full.gfx": energy_tanks(True, 5),
        "hud/energy_tanks_empty.gfx": energy_tanks(False, 11),
        "hud/energy_tank_one_full.gfx": A.tiles_to_bytes([tank_tile("full", None)]),
        "hud/energy_tank_one_full_one_empty.gfx": A.tiles_to_bytes([tank_tile("full", "empty")]),
        "hud/ammo_digits.gfx": ammo_digits(),
        "hud/missile_icon.gfx": missile_icon(),
        "hud/power_bomb_icon.gfx": power_bomb_icon(),
        "hud/escape_timer_digits.gfx": escape_digits(),
        "hud/escape_timer_digits.pal": A.pal_bytes(A.fx_palette("orange") + A.fx_palette("red") + A.fx_palette("yellow")),
    }


def apply(rom: bytearray, regions, layout) -> list[str]:
    by_path = {r.path: r for r in regions}
    n = 0
    for path, data in blocks().items():
        r = by_path[path]
        assert len(data) <= r.size, (path, len(data), r.size)
        rom[r.addr:r.addr + r.size] = data + bytes(r.size - len(data))
        n += 1
    return [f"hud: {n} blocks"]
