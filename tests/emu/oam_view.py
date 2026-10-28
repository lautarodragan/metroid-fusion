"""Read the sprites the game put in OAM and draw them without the background.

Used by test_sprites.py to look at Samus' pose independently of the room
and camera: the selected OAM entries are drawn from the current OBJ VRAM
tiles (2D mapping, 4bpp) and OBJ palettes onto a plain image.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass

OAM = 0x07000000
OBJ_VRAM = 0x06010000
OBJ_PAL = 0x05000200
SHAPE_SIZE = {(0, 0): (8, 8), (0, 1): (16, 16), (0, 2): (32, 32), (0, 3): (64, 64),
              (1, 0): (16, 8), (1, 1): (32, 8), (1, 2): (32, 16), (1, 3): (64, 32),
              (2, 0): (8, 16), (2, 1): (8, 32), (2, 2): (16, 32), (2, 3): (32, 64)}
BACKGROUND = (40, 44, 56)


@dataclass(frozen=True)
class Sprite:
    x: int
    y: int
    w: int
    h: int
    tile: int
    palette: int
    hflip: bool
    vflip: bool


def read_oam(emu, onscreen: bool = True) -> list[Sprite]:
    """Enabled, non affine OAM entries (only those overlapping the screen
    unless ``onscreen`` is false)."""
    data = emu.read(OAM, 1024)
    out = []
    for i in range(128):
        a0, a1, a2 = struct.unpack_from("<HHH", data, i * 8)
        if a0 & 0x300 == 0x200:          # disabled
            continue
        if (a0 & 0xFF, a1 & 0x1FF, a2) == (0xFF, 0xFF, 0):   # how the game parks unused entries
            continue
        if a0 & 0x100:                   # affine: not used by these tests
            continue
        if (a0 >> 14) == 3:
            continue
        w, h = SHAPE_SIZE[(a0 >> 14, a1 >> 14)]
        y = a0 & 0xFF
        if y >= 192:
            y -= 256
        x = a1 & 0x1FF
        if x >= 512 - 64:
            x -= 512
        if onscreen and (y + h <= 0 or y >= 160 or x + w <= 0 or x >= 240):
            continue
        out.append(Sprite(x, y, w, h, a2 & 0x3FF, a2 >> 12, bool(a1 & 0x1000), bool(a1 & 0x2000)))
    return out


def obj_palettes(emu) -> list[list[tuple[int, int, int]]]:
    raw = struct.unpack("<256H", emu.read(OBJ_PAL, 512))
    pals = []
    for r in range(16):
        row = []
        for v in raw[r * 16:(r + 1) * 16]:
            c = (v & 31, (v >> 5) & 31, (v >> 10) & 31)
            row.append(tuple((k << 3) | (k >> 2) for k in c))
        pals.append(row)
    return pals


def sprite_pixels(emu, s: Sprite):
    """Yield (screen x, screen y, colour index) for the opaque pixels of ``s``."""
    vram = emu.read(OBJ_VRAM, 0x8000)
    cols, rows = s.w // 8, s.h // 8
    for ty in range(rows):
        for tx in range(cols):
            t = (s.tile + tx + ty * 32) & 0x3FF
            tile = vram[t * 32:(t + 1) * 32]
            for py in range(8):
                for px in range(8):
                    b = tile[py * 4 + px // 2]
                    c = (b >> 4) if px & 1 else (b & 15)
                    if not c:
                        continue
                    x = tx * 8 + px
                    y = ty * 8 + py
                    if s.hflip:
                        x = s.w - 1 - x
                    if s.vflip:
                        y = s.h - 1 - y
                    yield s.x + x, s.y + y, c


def is_samus(s: Sprite) -> bool:
    """Samus' body (OBJ palette 0, tile rows 0-1) and arm cannon (palette 1, rows 2-3)."""
    return (s.palette == 0 and s.tile < 0x40) or (s.palette == 1 and 0x40 <= s.tile < 0x80)


def render(emu, sprites: list[Sprite], width: int = 96, height: int = 80):
    """Draw ``sprites`` (in OAM order: lower index in front) centred
    horizontally on their bounding box, feet ``height - 8`` pixels down."""
    pals = obj_palettes(emu)
    img = bytearray(bytes(BACKGROUND) * (width * height))
    if not sprites:
        return width, height, bytes(img)
    x0 = min(s.x for s in sprites)
    x1 = max(s.x + s.w for s in sprites)
    y1 = max(s.y + s.h for s in sprites)
    ox = width // 2 - (x0 + x1) // 2
    oy = height - 8 - y1
    for s in reversed(sprites):
        for x, y, c in sprite_pixels(emu, s):
            X, Y = x + ox, y + oy
            if 0 <= X < width and 0 <= Y < height:
                i = (Y * width + X) * 3
                img[i:i + 3] = bytes(pals[s.palette][c])
    return width, height, bytes(img)
