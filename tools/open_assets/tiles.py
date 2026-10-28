"""Semantic room tileset for the open base ROM (test fixture graphics).

Every tileset slot of the game gets the same small "semantic" tileset, so any
room reads the same way: what Samus collides with looks like it. The look of
a block follows its collision type (see docs/open_assets_rooms.md for the
legend):

- solid structure: steel plates; the side facing open space gets a bright
  edge, floors (open above) a lit walkway with a hazard stripe, ceilings
  (open below) a dark underside with lamps,
- pass-through platforms: amber girders, open below,
- ladders (wall / ceiling rungs): dark recess with yellow rails and rungs,
- door transitions: dark corridor with an arrow pointing out of the room,
  framed by a cyan door jamb,
- breakable blocks: rust coloured plates with an icon for what breaks them,
- water: blue with ripples,
- background (BG2): dark, desaturated panels, vents, pipes and windows,
- far background (BG3): an abstract circuit pattern, darker still.

Everything is drawn here procedurally, pixel by pixel, so that emulator
tests and their screenshots show a level a person can read.

VRAM layout used by the game for rooms (see RoomLoadTileset in src/room.c):
the BG0-2 character base is 0x06004000; animated tiles occupy tiles 0-63,
the common tiles (``sCommonTilesGfx``: hatches, breakable blocks, tanks)
tiles 64-191 and the tileset graphics start at tile 192 (0x06005800). The
tileset palette (14 rows) is loaded to palette rows 2-15, then the common
palette overwrites rows 0-2; row 15 is overwritten by animated palettes.
BG3 uses character base 0x06008000 and the tileset's "background graphics"
are decompressed so that they end at 0x0600FDE0.
"""

from __future__ import annotations

import re
import struct
from dataclasses import dataclass, field

import formats

# ---------------------------------------------------------------------------
# Palettes
# ---------------------------------------------------------------------------

TILESET_FIRST_TILE = 192          # 0x06005800
COMMON_FIRST_TILE = 64            # 0x06004800
COMMON_BLANK = 0x40               # first common tile, transparent (fill value of empty BGs)
TANK_FIRST_TILE = 80              # 0x06004A00, animated by AnimatedGraphicsUpdateTanks
BG3_END_TILE = (0xFDE0 - 0x8000) // 32  # BG3 tiles end right before 0x0600FDE0

# palette rows (hardware numbering)
PAL_STEEL = 3
PAL_GIRDER = 4
PAL_DOOR = 5
PAL_RUST = 6
PAL_WATER = 7
PAL_BACK = 8
PAL_FAR = 9


def _row(*colors: tuple[int, int, int]) -> list[int]:
    row = [0] + [formats.bgr555(*c) for c in colors]
    return (row + [0x7FFF] * 16)[:16]


ROWS = {
    PAL_STEEL: _row((10, 12, 20), (28, 34, 52), (44, 54, 80), (62, 76, 108), (84, 102, 140),
                    (112, 134, 172), (150, 172, 206), (205, 220, 240), (240, 196, 40),
                    (150, 110, 20), (90, 220, 255), (30, 130, 180), (255, 90, 60), (40, 40, 48)),
    PAL_GIRDER: _row((24, 14, 4), (80, 48, 10), (140, 90, 20), (200, 140, 30), (245, 200, 70),
                     (255, 240, 160)),
    PAL_DOOR: _row((4, 12, 20), (10, 40, 60), (20, 80, 110), (40, 140, 180), (90, 200, 240),
                   (190, 245, 255), (6, 8, 14), (14, 18, 30), (24, 30, 48)),
    PAL_RUST: _row((30, 14, 8), (80, 40, 20), (130, 70, 30), (180, 105, 45), (225, 150, 70),
                   (255, 210, 130), (250, 250, 250), (230, 40, 40), (60, 220, 90), (250, 230, 60),
                   (80, 230, 250), (200, 90, 240)),
    PAL_WATER: _row((4, 16, 40), (10, 40, 90), (20, 70, 140), (40, 110, 190), (90, 170, 230),
                    (190, 230, 255)),
    PAL_BACK: _row((6, 8, 14), (14, 18, 30), (22, 28, 46), (32, 40, 62), (44, 54, 80),
                   (60, 72, 100), (120, 90, 40), (40, 110, 130)),
    PAL_FAR: _row((2, 4, 9), (5, 9, 18), (8, 17, 28), (12, 28, 42), (20, 46, 60),
                  (34, 70, 86)),
}


def tileset_palette() -> bytes:
    """The 14 rows loaded to palette rows 2-15 (448 bytes)."""
    out = []
    for hw in range(2, 16):
        out += ROWS.get(hw, ROWS[PAL_STEEL])
    return struct.pack("<224H", *out)


# ---------------------------------------------------------------------------
# Pixel art helpers
# ---------------------------------------------------------------------------

class Img:
    """A 16x16 (or 8x8) image of palette indices with its palette row."""

    def __init__(self, pal: int, size: int = 16, fill: int = 0):
        self.pal = pal
        self.n = size
        self.px = [[fill] * size for _ in range(size)]

    def set(self, x: int, y: int, c: int) -> None:
        if 0 <= x < self.n and 0 <= y < self.n:
            self.px[y][x] = c

    def hline(self, y: int, x0: int, x1: int, c: int) -> None:
        for x in range(x0, x1 + 1):
            self.set(x, y, c)

    def vline(self, x: int, y0: int, y1: int, c: int) -> None:
        for y in range(y0, y1 + 1):
            self.set(x, y, c)

    def rect(self, x0: int, y0: int, x1: int, y1: int, c: int) -> None:
        for y in range(y0, y1 + 1):
            self.hline(y, x0, x1, c)

    def mirror(self) -> "Img":
        out = Img(self.pal, self.n)
        out.px = [row[::-1] for row in self.px]
        return out

    def quadrants(self) -> list[tuple[int, ...]]:
        q = []
        for oy in (0, 8):
            for ox in (0, 8):
                q.append(tuple(self.px[oy + y][ox + x] for y in range(8) for x in range(8)))
        return q


def tile_bytes(pixels: tuple[int, ...]) -> bytes:
    return bytes(pixels[i] | (pixels[i + 1] << 4) for i in range(0, 64, 2))


def _flips(p: tuple[int, ...]):
    rows = [p[y * 8:y * 8 + 8] for y in range(8)]
    h = tuple(v for r in rows for v in r[::-1])
    v = tuple(v for r in rows[::-1] for v in r)
    hv = tuple(v for r in rows[::-1] for v in r[::-1])
    return ((p, 0), (h, 1), (v, 2), (hv, 3))


class TileBank:
    """Deduplicates 8x8 tiles (also flipped copies) into BG tile entries."""

    def __init__(self, first_tile: int, blank_entry: int | None = None):
        self.first = first_tile
        self.tiles: list[tuple[int, ...]] = []
        self.index: dict[tuple[int, ...], tuple[int, int]] = {}
        self.blank_entry = blank_entry

    def entry(self, pixels: tuple[int, ...], pal: int) -> int:
        if self.blank_entry is not None and not any(pixels):
            return self.blank_entry
        for variant, flip in _flips(pixels):
            if variant in self.index:
                t, f = self.index[variant]
                break
        else:
            t = len(self.tiles)
            self.tiles.append(pixels)
            self.index[pixels] = (t, 0)
            flip = 0
        return (self.first + t) | (flip << 10) | (pal << 12)

    def metatile(self, img: Img) -> list[int]:
        return [self.entry(q, img.pal) for q in img.quadrants()]

    def gfx(self) -> bytes:
        return b"".join(tile_bytes(t) for t in self.tiles)


# ---------------------------------------------------------------------------
# Foreground (BG1) blocks
# ---------------------------------------------------------------------------

N, E, S, W = 1, 2, 4, 8          # open sides of a solid block


def draw_solid(open_mask: int, detail: bool = True) -> Img:
    """Steel plates; edges facing open space are lit (floor, wall, ceiling)."""
    im = Img(PAL_STEEL, fill=4)
    if detail:
        for y in range(16):
            for x in range(16):
                px, py = x % 8, y % 8
                if px == 0 or py == 0:
                    im.set(x, y, 5)
                elif px == 7 or py == 7:
                    im.set(x, y, 3)
        for cx, cy in ((3, 3), (11, 11)):
            im.set(cx, cy, 7)
            im.set(cx + 1, cy + 1, 2)
    if open_mask & W:
        im.vline(0, 0, 15, 7)
        im.vline(1, 0, 15, 6)
        im.vline(2, 0, 15, 2)
    if open_mask & E:
        im.vline(15, 0, 15, 2)
        im.vline(14, 0, 15, 6)
        im.vline(13, 0, 15, 7)
    if open_mask & S:
        im.hline(15, 0, 15, 1)
        im.hline(14, 0, 15, 2)
        im.hline(13, 0, 15, 3)
        if detail:
            for x in (5, 6, 13, 14):
                if not ((open_mask & W and x < 3) or (open_mask & E and x > 12)):
                    im.set(x, 14, 11)
                    im.set(x, 15, 12)
    if open_mask & N:
        im.hline(0, 0, 15, 8)
        im.hline(1, 0, 15, 7)
        for x in range(16):
            stripe = 9 if ((x + 16) // 2) % 2 == 0 else 10
            im.set(x, 2, stripe)
            im.set(x, 3, stripe if detail else 10)
        im.hline(4, 0, 15, 1)
    # round convex corners
    for mask, (x, y) in ((N | W, (0, 0)), (N | E, (15, 0)), (S | W, (0, 15)), (S | E, (15, 15))):
        if open_mask & mask == mask:
            im.set(x, y, 0)
    return im


def draw_platform() -> Img:
    """Pass-through girder: lit top, truss, open below."""
    im = Img(PAL_GIRDER)
    im.hline(0, 0, 15, 6)
    im.hline(1, 0, 15, 5)
    im.hline(2, 0, 15, 3)
    im.hline(6, 0, 15, 2)
    for y in range(3, 6):
        for x in range(16):
            if (x - y) % 6 == 0 or (x + y) % 6 == 0:
                im.set(x, y, 4)
    im.hline(7, 0, 15, 1)
    return im


def draw_wall_ladder() -> Img:
    """Wall rungs (solid, climbable): recess with yellow rails and rungs."""
    im = Img(PAL_STEEL, fill=2)
    im.vline(0, 0, 15, 1)
    im.vline(15, 0, 15, 1)
    for x in (3, 12):
        im.vline(x, 0, 15, 9)
        im.vline(x + 1, 0, 15, 10)
    for y in (2, 6, 10, 14):
        im.hline(y, 3, 13, 9)
        im.hline(y + 1, 4, 12, 10)
    return im


def draw_ceiling_ladder() -> Img:
    """Ceiling rungs (solid, hang and climb): plate above, bars below."""
    im = draw_solid(0)
    im.rect(0, 8, 15, 15, 2)
    im.hline(8, 0, 15, 1)
    for y in (10, 13):
        im.hline(y, 0, 15, 9)
        im.hline(y + 1, 0, 15, 10)
    for x in (1, 5, 9, 13):
        im.vline(x, 9, 15, 9)
    return im


def draw_doorway(points_left: bool) -> Img:
    """Door transition: dark corridor, arrow pointing out of the room."""
    im = Img(PAL_DOOR, fill=7)
    im.hline(0, 0, 15, 8)
    im.hline(15, 0, 15, 8)
    im.hline(7, 0, 15, 9)
    for i in range(5):           # chevron
        x = 5 + i
        im.set(x, 7 - i, 4)
        im.set(x, 8 + i, 4)
        im.set(x + 1, 7 - i, 3)
        im.set(x + 1, 8 + i, 3)
    return im if points_left else im.mirror()


def draw_jamb(part: str, door_on_left: bool) -> Img:
    """Open hatch frame next to a doorway; ``part`` is top, mid or bot."""
    im = Img(PAL_DOOR)
    im.vline(0, 0, 15, 1)
    im.vline(1, 0, 15, 6)
    im.vline(2, 0, 15, 5)
    im.vline(3, 0, 15, 4)
    im.vline(4, 0, 15, 2)
    for y in range(2, 16, 4):     # indicator lights
        im.set(2, y, 6)
    if part == "top":
        im.rect(0, 0, 9, 2, 3)
        im.hline(0, 0, 9, 5)
        im.hline(3, 0, 9, 1)
    elif part == "bot":
        im.rect(0, 13, 9, 15, 3)
        im.hline(13, 0, 9, 5)
        im.hline(15, 0, 9, 1)
    return im if door_on_left else im.mirror()


def _bevel(im: Img, hi: int, lo: int) -> None:
    im.hline(0, 0, 15, hi)
    im.vline(0, 0, 15, hi)
    im.hline(15, 0, 15, lo)
    im.vline(15, 0, 15, lo)


ICONS = ("shot", "bomb", "missile", "power_bomb", "speed", "screw", "crumble")


def draw_breakable(kind: str, pal: int = PAL_RUST) -> Img:
    """Breakable plate with an icon telling what breaks it."""
    im = Img(pal, fill=3)
    _bevel(im, 5, 1)
    im.rect(2, 2, 13, 13, 4)
    if kind == "shot":           # cracks
        for (x, y) in ((3, 4), (4, 5), (5, 5), (6, 6), (7, 7), (8, 7), (9, 8), (10, 9),
                       (11, 11), (12, 12), (7, 8), (6, 9), (5, 11), (9, 4), (8, 5), (10, 3)):
            im.set(x, y, 1)
    elif kind == "bomb":         # round bomb with a spark
        for y in range(16):
            for x in range(16):
                if (x - 7.5) ** 2 + (y - 8.5) ** 2 <= 14:
                    im.set(x, y, 1)
        im.set(6, 7, 7)
        im.set(6, 6, 7)
        im.set(10, 4, 10)
        im.set(11, 3, 10)
    elif kind == "missile":      # rocket pointing right
        im.hline(7, 4, 10, 7)
        im.hline(8, 4, 10, 7)
        im.set(11, 7, 8)
        im.set(11, 8, 8)
        im.set(12, 7, 8)
        im.set(12, 8, 8)
        im.set(4, 6, 1)
        im.set(4, 9, 1)
        im.set(5, 5, 1)
        im.set(5, 10, 1)
    elif kind == "power_bomb":   # ring
        for y in range(16):
            for x in range(16):
                d = (x - 7.5) ** 2 + (y - 7.5) ** 2
                if 12 <= d <= 24:
                    im.set(x, y, 12)
                elif d < 3:
                    im.set(x, y, 7)
    elif kind == "speed":        # chevrons
        for i in range(4):
            for ox in (4, 8):
                im.set(ox + i, 4 + i, 11)
                im.set(ox + i, 11 - i, 11)
    elif kind == "screw":        # four point star
        for i in range(6):
            im.set(7, 2 + i, 9)
            im.set(8, 13 - i, 9)
            im.set(2 + i, 8, 9)
            im.set(13 - i, 7, 9)
        im.rect(6, 6, 9, 9, 6)
    elif kind == "crumble":      # loose rubble
        im.rect(2, 2, 13, 13, 3)
        for (x, y) in ((3, 3), (8, 4), (12, 3), (5, 7), (10, 8), (3, 11), (7, 12), (12, 12),
                       (6, 3), (9, 10), (13, 6), (4, 9)):
            im.set(x, y, 5)
            im.set(x + 1, y + 1, 1)
    return im


def draw_water(surface: bool) -> Img:
    im = Img(PAL_WATER, fill=3)
    for y in (5, 11):
        for x in range(16):
            if (x + y) % 8 < 3:
                im.set(x, y, 4)
    if surface:
        for x in range(16):
            y = 1 if x % 8 < 4 else 2
            im.set(x, 0, 0)
            im.set(x, y, 6)
            im.set(x, y + 1, 5)
            if y == 2:
                im.set(x, 1, 0)
    return im


# ---------------------------------------------------------------------------
# Background (BG2) blocks
# ---------------------------------------------------------------------------

def draw_back(kind: str) -> Img:
    im = Img(PAL_BACK, fill=3)
    if kind == "panel":
        _bevel(im, 4, 1)
        im.rect(3, 3, 12, 12, 2)
        im.hline(3, 3, 12, 1)
        im.vline(3, 3, 12, 1)
        im.set(12, 2, 8)
    elif kind == "vent":
        _bevel(im, 4, 1)
        for y in range(2, 14, 3):
            im.hline(y, 2, 13, 1)
            im.hline(y + 1, 2, 13, 2)
    elif kind == "pipe_h":
        im = Img(PAL_BACK)
        im.hline(5, 0, 15, 2)
        im.rect(0, 6, 15, 9, 5)
        im.hline(7, 0, 15, 6)
        im.hline(10, 0, 15, 1)
        im.vline(7, 5, 10, 3)
    elif kind == "pipe_v":
        im = Img(PAL_BACK)
        im.vline(5, 0, 15, 2)
        im.rect(6, 0, 9, 15, 5)
        im.vline(7, 0, 15, 6)
        im.vline(10, 0, 15, 1)
        im.hline(7, 5, 10, 3)
    elif kind == "pipe_x":
        im = draw_back("pipe_v")
        h = draw_back("pipe_h")
        for y in range(16):
            for x in range(16):
                if h.px[y][x] and not (6 <= x <= 9):
                    im.set(x, y, h.px[y][x])
        im.rect(5, 5, 10, 10, 4)
        im.rect(6, 6, 9, 9, 6)
    elif kind == "light":
        _bevel(im, 4, 1)
        im.rect(2, 6, 13, 9, 1)
        im.hline(7, 3, 12, 7)
        im.hline(8, 3, 12, 8)
    elif kind == "window":       # frame, the far background shows through
        im = Img(PAL_BACK)
        im.rect(0, 0, 15, 2, 4)
        im.rect(0, 13, 15, 15, 2)
        im.hline(0, 0, 15, 5)
    elif kind == "girder":
        im = Img(PAL_BACK)
        im.vline(2, 0, 15, 5)
        im.vline(13, 0, 15, 5)
        im.vline(3, 0, 15, 2)
        im.vline(12, 0, 15, 2)
        for y in range(16):
            x = 4 + (y % 8)
            if x <= 11:
                im.set(x, y, 4)
                im.set(15 - x, y, 4)
    return im


# ---------------------------------------------------------------------------
# The metatile table
# ---------------------------------------------------------------------------

@dataclass
class Tileset:
    gfx: bytes
    metatiles: list[list[int]]
    names: dict[str, int] = field(default_factory=dict)

    def tm_bytes(self, size: int) -> bytes:
        """The .tm region: a leading u16 then 4 entries per metatile.

        Regions hold a different number of metatiles; the semantic set is
        repeated with air so a stray index never shows garbage.
        """
        words = [len(self.metatiles)]
        n = (size - 2) // 8
        for i in range(n):
            words += self.metatiles[i] if i < len(self.metatiles) else self.metatiles[0]
        return struct.pack(f"<{len(words)}H", *words)[:size]


# Order matters: rooms store these indices. Index 0 must be air and index 1
# the generic solid block (the placeholder rooms use 0 and 1). Indices 1-16
# are the solid block for every combination of open sides (1 + mask).
def _metatile_specs(detail: bool):
    specs: list[tuple[str, Img | None]] = [("air", None)]
    for mask in range(16):
        specs.append((f"solid_{mask}", draw_solid(mask, detail)))
    specs += [
        ("platform", draw_platform()),
        ("ladder_wall", draw_wall_ladder()),
        ("ladder_ceiling", draw_ceiling_ladder()),
        ("door_left", draw_doorway(True)),
        ("door_right", draw_doorway(False)),
    ]
    for side in ("left", "right"):
        for part in ("top", "mid", "bot"):
            specs.append((f"jamb_{side}_{part}", draw_jamb(part, side == "left")))
    for kind in ICONS:
        specs.append((f"break_{kind}", draw_breakable(kind)))
    specs += [("water_surface", draw_water(True)), ("water", draw_water(False))]
    for kind in ("panel", "vent", "pipe_h", "pipe_v", "pipe_x", "light", "window", "girder"):
        specs.append((f"back_{kind}", draw_back(kind)))
    return specs


MAX_METATILES = 70   # the smallest .tm region holds 70 metatiles


def build_tileset() -> Tileset:
    bank = TileBank(TILESET_FIRST_TILE, blank_entry=COMMON_BLANK)
    metatiles, names = [], {}
    for name, img in _metatile_specs(True):
        names[name] = len(metatiles)
        metatiles.append([COMMON_BLANK] * 4 if img is None else bank.metatile(img))
    assert len(metatiles) <= MAX_METATILES, len(metatiles)
    return Tileset(bank.gfx(), metatiles, names)


def simple_gfx(ts: Tileset) -> bytes:
    """Less detailed graphics with the same tile slots as ``ts`` (same .tm).

    For the few tileset regions too small for the detailed graphics: the
    plain drawings are written into the slots the detailed ones use, so the
    metatile table stays valid and the repeated tiles compress better.
    """
    n = len(ts.gfx) // 32
    slots: list[tuple[int, ...] | None] = [None] * n
    for (name, img), entries in zip(_metatile_specs(False), ts.metatiles):
        if img is None:
            continue
        for q, e in zip(img.quadrants(), entries):
            t = (e & 0x3FF) - TILESET_FIRST_TILE
            if e == COMMON_BLANK or not 0 <= t < n or slots[t] is not None:
                continue
            flip = (e >> 10) & 3
            slots[t] = dict((f, v) for v, f in _flips(q))[flip]
    plain = tuple([4] * 64)
    return b"".join(tile_bytes(t if t is not None else plain) for t in slots)


def flat_gfx(gfx: bytes) -> bytes:
    """Last resort for tiny regions: every opaque pixel of a tile takes the
    tile's most common colour (shapes stay, detail goes)."""
    out = bytearray()
    for t in range(len(gfx) // 32):
        px = [v for b in gfx[t * 32:t * 32 + 32] for v in (b & 15, b >> 4)]
        opaque = [v for v in px if v]
        c = max(set(opaque), key=opaque.count) if opaque else 0
        px = [c if v else 0 for v in px]
        out += bytes(px[i] | (px[i + 1] << 4) for i in range(0, 64, 2))
    return bytes(out)


def solid_index(open_mask: int) -> int:
    return 1 + open_mask


# ---------------------------------------------------------------------------
# Far background (BG3): tileset "background graphics" + LZ77 tilemaps
# ---------------------------------------------------------------------------

BG3_TILES = 8


def _far_tiles() -> list[tuple[int, ...]]:
    """Eight 8x8 tiles of a circuit-board pattern (palette PAL_FAR)."""
    def t(fn):
        return tuple(fn(x, y) for y in range(8) for x in range(8))
    base = 1
    return [
        t(lambda x, y: 2 if (x == 0 or y == 0) else base),                       # 0 grid cell
        t(lambda x, y: 4 if y in (3, 4) else (2 if x == 0 or y == 0 else base)),  # 1 trace horizontal
        t(lambda x, y: 4 if x in (3, 4) else (2 if x == 0 or y == 0 else base)),  # 2 trace vertical
        t(lambda x, y: 5 if 2 <= x <= 5 and 2 <= y <= 5 else
          (4 if x in (3, 4) or y in (3, 4) else (2 if x == 0 or y == 0 else base))),  # 3 node
        t(lambda x, y: 4 if (y in (3, 4) and x >= 3) or (x in (3, 4) and y >= 3) else
          (2 if x == 0 or y == 0 else base)),                                     # 4 corner
        t(lambda x, y: 3 if (x + y) % 4 == 0 else base),                          # 5 hatch
        t(lambda x, y: 6 if (x, y) in ((3, 3), (4, 3), (3, 4), (4, 4)) else
          (2 if x == 0 or y == 0 else base)),                                     # 6 light dot
        t(lambda x, y: base),                                                     # 7 plain
    ]


# 8x8 tile motif (64x64 px) repeated over the BG3 map: tile ids into _far_tiles
_MOTIF = [
    "31111403",
    "20000220",
    "20660220",
    "41111310",
    "05555020",
    "05775020",
    "05555046",
    "11113111",
]


def far_gfx() -> bytes:
    return b"".join(tile_bytes(t) for t in _far_tiles())


def far_tilemap(size_bytes: int) -> bytes:
    """A BG3 screen (u16 entries) for a map of ``size_bytes`` (0x800 per 32x32 screen)."""
    first = BG3_END_TILE - BG3_TILES
    words = []
    for i in range(size_bytes // 2):
        scr, rest = divmod(i, 1024)
        y, x = divmod(rest, 32)
        tid = int(_MOTIF[y % 8][x % 8])
        words.append((first + tid) | (PAL_FAR << 12))
    return struct.pack(f"<{len(words)}H", *words)


# ---------------------------------------------------------------------------
# Common tiles: hatches, breakable blocks (when revealed), tanks
# ---------------------------------------------------------------------------
#
# sCommonTilemap is indexed by enum ClipdataTilemap (include/constants/
# clipdata.h): 464 blocks of 4 entries. A hatch is one block wide and four
# tall, at indices base, base+16, base+32, base+48. The hatch code picks:
#   DOOR_{RIGHT,LEFT}_*  (17-20 / 22-25 + 16k): opening animation, 4 frames
#   26/27 + 16k: closed and locked (right / left)
#   80 + 64c + 16k + 6*left + slot: closed hatch of colour c (white, blue,
#       green, yellow, red), any of 6 slots
#   400 + ...: the opening animation and closed state of lockable hatches
# "RIGHT" hatches are on the right wall (the doorway is to their right),
# "LEFT" ones on the left wall.
#
# Palette row 1 colours 6-10 are the hatch colours of security levels 0-4
# (RoomUpdateHatchFlashingAnimation cycles them); row 2 colours 13-15 flash
# when a locked hatch unlocks.

C_PAL_BLOCK = 0
C_PAL_HATCH = 1
C_PAL_LOCK = 2

HATCH_COLORS = [(230, 230, 230), (60, 120, 255), (40, 210, 90), (250, 220, 40), (240, 50, 50)]


def common_palette() -> bytes:
    rows = []
    # row 0: blocks (same ramp as the rust breakables, plus icon colours)
    rows.append(ROWS[PAL_RUST])
    # row 1: hatch frame greys 1-5, hatch colours 6-10, light 11
    rows.append(_row((12, 14, 20), (40, 44, 56), (80, 86, 100), (130, 136, 150), (190, 196, 210),
                     *HATCH_COLORS, (255, 255, 255)))
    # row 2: locked hatch: frame greys, lock colours 13-15
    rows.append(_row((12, 14, 20), (40, 44, 56), (80, 86, 100), (130, 136, 150), (190, 196, 210),
                     (0, 0, 0), (0, 0, 0), (0, 0, 0), (0, 0, 0), (0, 0, 0), (0, 0, 0), (0, 0, 0),
                     (120, 30, 140), (200, 60, 220), (255, 160, 255)))
    for _ in range(13):
        rows.append(ROWS[PAL_STEEL])
    return struct.pack("<256H", *[c for r in rows for c in r])


def hatch_flashing_palette(n_rows: int) -> bytes:
    """Rows cycled into palette row 1, colours 6-10: hatch colours pulsing."""
    out = []
    for r in range(n_rows):
        k = 0.6 + 0.4 * abs((r % 6) - 3) / 3
        row = [0] * 16
        for i, (cr, cg, cb) in enumerate(HATCH_COLORS):
            row[6 + i] = formats.bgr555(int(cr * k), int(cg * k), int(cb * k))
        out += row
    return struct.pack(f"<{len(out)}H", *out)


def unlocked_hatch_flashing_palette(n_rows: int) -> bytes:
    """Rows cycled into palette row 2, colours 13-15: lock lights blinking."""
    out = []
    for r in range(n_rows):
        on = r % 2 == 0
        row = [0] * 16
        row[13] = formats.bgr555(*((60, 240, 120) if on else (20, 80, 40)))
        row[14] = formats.bgr555(*((140, 255, 180) if on else (30, 120, 60)))
        row[15] = formats.bgr555(*((230, 255, 240) if on else (60, 160, 90)))
        out += row
    return struct.pack(f"<{len(out)}H", *out)


def _hatch_img(color_index: int | None, opening: int, part: int, on_left: bool,
               pal: int = C_PAL_HATCH) -> Img:
    """A hatch block. ``opening`` 0 = closed .. 4 = open; ``part`` 0-3 top to bottom.

    Drawn for a hatch on the right wall (doorway to the right) and mirrored
    for the left wall.
    """
    im = Img(pal)
    # frame on the doorway side (x 12-15)
    im.rect(12, 0, 15, 15, 3)
    im.vline(12, 0, 15, 5)
    im.vline(15, 0, 15, 1)
    if part == 0:
        im.rect(4, 0, 15, 2, 3)
        im.hline(0 if opening < 4 else 4, 4, 15, 4)
        im.hline(2, 4, 15, 1)
    if part == 3:
        im.rect(4, 13, 15, 15, 3)
        im.hline(13, 4, 15, 4)
        im.hline(15, 4, 15, 1)
    # the door slab: 8 px wide when closed, retracting into the frame
    width = [8, 6, 4, 2, 0][opening]
    if width:
        x0 = 12 - width
        y0 = 3 if part == 0 else 0
        y1 = 12 if part == 3 else 15
        fill = color_index if color_index is not None else 4
        im.rect(x0, y0, 11, y1, fill)
        im.vline(x0, y0, y1, 2)
        if width >= 4:
            im.vline(x0 + 1, y0, y1, 11 if pal == C_PAL_HATCH else 15)
        if color_index is None and pal == C_PAL_LOCK and width == 8:
            # locked: lights in the lock colour
            for y in range(y0 + 2, y1, 4):
                im.rect(x0 + 3, y, x0 + 5, y + 1, 14)
    return im if not on_left else im.mirror()


def build_common() -> tuple[bytes, bytes]:
    """(sCommonTilesGfx 4096 bytes, sCommonTilemap 3712 bytes)."""
    table = [[COMMON_BLANK] * 4 for _ in range(464)]
    pending: list[tuple[int, Img]] = []

    def put(idx: int, img: Img) -> None:
        pending.append((idx, img))

    solid = draw_solid(0)
    solid.pal = C_PAL_BLOCK
    put(1, _recolor(solid, {3: 2, 4: 3, 5: 4, 6: 4, 7: 5, 8: 6}))
    for i, stage in enumerate((2, 3, 4)):        # breaking animation
        put(stage, _breaking(i))
    for idx, kind in ((5, "bomb"), (6, "missile"), (7, "power_bomb"), (8, "speed"), (9, "speed"),
                      (10, "screw"), (11, "crumble"), (12, "shot"), (13, "missile")):
        put(idx, draw_breakable(kind, pal=C_PAL_BLOCK))
    put(44, draw_water(False))
    for part in range(4):
        for left in (0, 1):
            for frame in range(4):                # opening animation
                base = (22 if left else 17) + frame + 16 * part
                put(base, _hatch_img(None, frame + 1, part, bool(left)))
                put(base + 384, _hatch_img(None, frame + 1, part, bool(left), C_PAL_LOCK))
            put(26 + left + 16 * part, _hatch_img(None, 0, part, bool(left), C_PAL_LOCK))
            put(410 + left + 16 * part, _hatch_img(None, 0, part, bool(left), C_PAL_LOCK))
            for color in range(5):
                img = _hatch_img(6 + color, 0, part, bool(left))
                for slot in range(6):
                    put(80 + 64 * color + 16 * part + 6 * left + slot, img)

    # Unique tiles, then the final order: blank, 15 tiles, the 16 tank
    # tiles (tiles 80-95, animated in place), the rest.
    bank = TileBank(0)
    raw = []
    for idx, img in pending:
        raw.append((idx, [None if not any(q) else bank.entry(q, img.pal) for q in img.quadrants()]))
    uniq = len(bank.tiles)
    reserved = TANK_FIRST_TILE - COMMON_FIRST_TILE       # 16
    order = list(range(uniq))
    slot_of = {}
    for u in order:
        s = 1 + u if 1 + u < reserved else 1 + u + 16
        slot_of[u] = s
    n_slots = max([reserved + 16] + [s + 1 for s in slot_of.values()])
    assert n_slots <= 128, f"common tiles: {n_slots} > 128"
    tiles = [tuple([0] * 64)] * n_slots
    for u, s in slot_of.items():
        tiles[s] = bank.tiles[u]
    tank = tank_gfx(3 * 4 * 128)
    gfx = bytearray(b"".join(tile_bytes(t) for t in tiles))
    for k in range(3):                     # frame 0 of each tank kind
        gfx[(reserved + 4 * k) * 32:(reserved + 4 * k + 4) * 32] = tank[k * 512:k * 512 + 128]
    for idx, entries in raw:
        out = []
        for e in entries:
            if e is None:
                out.append(COMMON_BLANK)
            else:
                u = e & 0x3FF
                out.append((e & ~0x3FF) | (COMMON_FIRST_TILE + slot_of[u]))
        table[idx] = out
    for k, idx in enumerate((28, 29, 30)):  # tanks: 2x2 animated tiles each
        t = TANK_FIRST_TILE + 4 * k
        table[idx] = [(t + i) | (C_PAL_BLOCK << 12) for i in range(4)]
    tm = struct.pack("<1856H", *[e for b in table for e in b])
    return bytes(gfx).ljust(4096, b"\0"), tm


def _recolor(im: Img, mapping: dict[int, int]) -> Img:
    out = Img(im.pal)
    out.px = [[mapping.get(c, c) for c in row] for row in im.px]
    return out


def _breaking(stage: int) -> Img:
    """Solid block crumbling away (3 frames)."""
    im = draw_breakable("crumble", pal=C_PAL_BLOCK)
    for y in range(16):
        for x in range(16):
            if (x * 7 + y * 13) % 5 <= stage:
                im.set(x, y, 0)
    return im


def tank_gfx(size: int) -> bytes:
    """sAnimatedTankGfx: 3 kinds x 4 frames x 2x2 tiles of a pulsing capsule."""
    out = bytearray()
    for kind in range(3):
        core = (7, 8, 12)[kind]
        for frame in range(4):
            im = Img(C_PAL_BLOCK)
            for y in range(16):
                for x in range(16):
                    d = (x - 7.5) ** 2 + (y - 7.5) ** 2
                    if d <= 42:
                        im.set(x, y, 1)
                    if d <= 30:
                        im.set(x, y, 3)
                    if d <= 6 + 4 * (frame % 2 if frame < 3 else 0) + 2 * frame:
                        im.set(x, y, core)
            im.set(5, 4, 6)
            im.set(4, 5, 6)
            for q in im.quadrants():
                out += tile_bytes(q)
    return bytes(out[:size]).ljust(size, b"\0")


# ---------------------------------------------------------------------------
# Writing the regions
# ---------------------------------------------------------------------------

TILE_GFX_RE = re.compile(r"^sTileset_\d+_Gfx$")
BG_GFX_RE = re.compile(r"^sTileset_\d+_Bg_Gfx$")
TILESET_PAL_RE = re.compile(r"^sTileset_\d+_Pal$")
TILESET_TM_RE = re.compile(r"^sTileset_\d+_Tilemap$")
ROOM_BG3_RE = re.compile(r"^s\w*Bg3\w*$")


BRACED_INCBIN_RE = re.compile(r'(\w+)\s*\[[^\]]*\]\s*=\s*\{[^{}]*?_INCBIN_\w+\(\s*"([^"]+)"\s*\)')
_braced: dict[str, str] | None = None


def symbol_of(layout, r) -> str | None:
    """The symbol a region is included as, also for ``sym[] = { header,
    _INCBIN_U8("...") }`` arrays (room layers, BG3 maps) that layout.py's
    scan does not cover."""
    global _braced
    sym = layout.symbol_of(r)
    if sym:
        return sym
    if _braced is None:
        from inventory import ROOT
        _braced = {}
        for p in (ROOT / "src").rglob("*.c"):
            for m in BRACED_INCBIN_RE.finditer(p.read_text(errors="replace")):
                _braced.setdefault(m.group(2), m.group(1))
    return _braced.get(f"{r.dir}/{r.path}")


def put_region(rom: bytearray, r, data: bytes) -> None:
    if len(data) > r.size:
        raise SystemExit(f"{r.path}: {len(data)} bytes do not fit in {r.size}")
    rom[r.addr:r.addr + r.size] = data.ljust(r.size, b"\0")


def _lz_fit(r, candidates) -> bytes:
    for raw in candidates:
        for effort in (32, 4096):
            stream = formats.lz77_compress(raw, max_candidates=effort)
            if len(stream) <= r.size:
                return stream
    raise SystemExit(f"{r.path}: no graphics variant fits in {r.size} bytes")


def apply_tilesets(rom: bytearray, regions, layout, meta: dict) -> list[str]:
    """Write the semantic tileset into every tileset slot, plus the common
    tiles (hatches, blocks, tanks) and the far backgrounds. Returns notes."""
    ts = build_tileset()
    detailed, simple = ts.gfx, simple_gfx(ts)
    counts: dict[str, int] = {}
    simple_used = []
    by_symbol = {}
    far = far_gfx()
    first_far = BG3_END_TILE - BG3_TILES
    lz_cache: dict[tuple, bytes] = {}

    def count(k: str) -> None:
        counts[k] = counts.get(k, 0) + 1

    for r in regions:
        sym = symbol_of(layout, r)
        if not sym:
            continue
        by_symbol.setdefault(sym, r)
        if TILE_GFX_RE.match(sym):
            stream = _lz_fit(r, [detailed, simple, flat_gfx(simple)])
            if formats.lz77_decompress(stream) != detailed:
                simple_used.append(sym)
            put_region(rom, r, stream)
            count("tileset gfx")
        elif BG_GFX_RE.match(sym):
            put_region(rom, r, _lz_fit(r, [far]))
            count("background gfx")
        elif TILESET_PAL_RE.match(sym) and r.size == 448:
            put_region(rom, r, tileset_palette())
            count("tileset palettes")
        elif TILESET_TM_RE.match(sym):
            put_region(rom, r, ts.tm_bytes(r.size))
            count("metatile tables")
        elif r.category == "tilemap_lz" and r.path.startswith(("rooms/", "common/")):
            size = meta.get(r.path, {}).get("decomp_size", 0x800)
            if ROOM_BG3_RE.match(sym):
                key = ("far", size)
                if key not in lz_cache:
                    lz_cache[key] = formats.lz77_compress(far_tilemap(size))
                stream = lz_cache[key]
                if len(stream) > r.size:      # tiny region: a plain grid
                    stream = formats.lz77_compress(
                        struct.pack("<H", first_far | (PAL_FAR << 12)) * (size // 2))
                count("BG3 far backgrounds")
            else:                             # BG0 overlays: transparent
                stream = formats.lz77_compress(struct.pack("<H", COMMON_BLANK) * (size // 2))
                count("BG0 overlays (blank)")
            put_region(rom, r, stream)

    common_gfx, common_tm = build_common()
    fixed = {
        "sCommonTilesGfx": lambda r: common_gfx,
        "sCommonTilemap": lambda r: common_tm,
        "sCommonTilesPal": lambda r: common_palette(),
        "sHatchFlashingPal": lambda r: hatch_flashing_palette(r.size // 32),
        "sUnlockedHatchFlashingPal": lambda r: unlocked_hatch_flashing_palette(r.size // 32),
        "sAnimatedTankGfx": lambda r: tank_gfx(r.size),
    }
    for sym, make in fixed.items():
        r = by_symbol.get(sym)
        if r is None:
            raise SystemExit(f"tiles.py: no region INCBINed as {sym}")
        put_region(rom, r, make(r))
    notes = [f"semantic tileset: {len(ts.metatiles)} metatiles, {len(ts.gfx) // 32} tiles; "
             + ", ".join(f"{v} {k}" for k, v in sorted(counts.items()))]
    if simple_used:
        notes.append(f"less detailed tileset graphics (small regions): {', '.join(simple_used)}")
    return notes
