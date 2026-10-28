"""Shared helpers to draw placeholder sprite art through the OAM data in C.

Sprite graphics in the base ROM are plain 4bpp tile sheets; *which* tile
ends up where on screen is decided by the OAM frames defined in this
repository's C sources (``OAM_ENTRY(x, y, dims, flip, tile, palette,
priority)``). To draw a readable placeholder, the generators in
samus_gfx.py, hud_gfx.py and sprite_gfx.py paint a picture in sprite-local
coordinates (origin = the object's position) on a :class:`Canvas`, then
"cut" it into tiles through the OAM entries of a frame: every pixel covered
by an entry is copied into the tile (and pixel) that entry displays there.

The pictures are procedural placeholders for the emulator tests.

Contents:
- a small parser for the C data (OAM frames, ``struct FrameData`` arrays,
  other struct arrays and pointer tables, INCBIN'd arrays),
- :class:`Canvas`: drawing primitives with palette indices and an outline pass,
- :class:`TileSheet`: a 2D (32 tiles wide) 4bpp sheet that canvases are cut
  into, and conversion to bytes,
- palette helpers.
"""

from __future__ import annotations

import math
import re
import struct
from dataclasses import dataclass
from pathlib import Path

from inventory import ROOT

# ---------------------------------------------------------------------------
# C parsing
# ---------------------------------------------------------------------------

# OAM_DIMS_<w>x<h> -> (width, height)
DIMS = {f"OAM_DIMS_{w}x{h}": (w, h) for w, h in
        [(8, 8), (16, 16), (32, 32), (64, 64), (16, 8), (32, 8), (32, 16), (64, 32),
         (8, 16), (8, 32), (16, 32), (32, 64)]}
FLIPS = {"OAM_NO_FLIP": 0, "OAM_X_FLIP": 1, "OAM_Y_FLIP": 2, "OAM_XY_FLIP": 3}
# shape/size bits of attr0/attr1 -> (width, height)
SHAPE_SIZE = {(0, 0): (8, 8), (0, 1): (16, 16), (0, 2): (32, 32), (0, 3): (64, 64),
              (1, 0): (16, 8), (1, 1): (32, 8), (1, 2): (32, 16), (1, 3): (64, 32),
              (2, 0): (8, 16), (2, 1): (8, 32), (2, 2): (16, 32), (2, 3): (32, 64)}


@dataclass(frozen=True)
class OamEntry:
    x: int
    y: int
    w: int
    h: int
    flip: int        # bit 0 = X flip, bit 1 = Y flip
    tile: int        # 10 bit tile number (2D mapping: 32 tiles per row)
    palette: int
    priority: int

    def tiles(self):
        """(dx, dy, tile) for each 8x8 tile of the entry, in screen order."""
        cols, rows = self.w // 8, self.h // 8
        for ty in range(rows):
            for tx in range(cols):
                sx = cols - 1 - tx if self.flip & 1 else tx
                sy = rows - 1 - ty if self.flip & 2 else ty
                yield tx * 8, ty * 8, self.tile + sx + sy * 32


DECL_RE = re.compile(
    r"^(?:static\s+)?const\s+(?P<type>(?:struct\s+)?\w+)\s*\*?\s*(?:const\s+)?(?P<name>\w+)"
    r"(?P<dims>(?:\s*\[[^\]]*\])+)\s*=\s*", re.M)
INCBIN_ARG_RE = re.compile(r'INCBIN_\w+\(\s*"([^"]+)"\s*\)')
COMMENT_RE = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)


def _balanced(text: str, start: int) -> int:
    """Index just past the brace block that starts at text[start] == '{'."""
    depth = 0
    for i in range(start, len(text)):
        c = text[i]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return i + 1
    raise ValueError("unbalanced braces")


def _int(expr: str) -> int:
    expr = expr.strip()
    expr = re.sub(r"\b(OAM_[A-Z_0-9x]+)\b", lambda m: str(FLIPS.get(m.group(1), m.group(1))), expr)
    return int(eval(expr, {"__builtins__": {}}, {}))  # numbers and + - * | only


def _split_args(s: str) -> list[str]:
    out, depth, cur = [], 0, ""
    for c in s:
        if c == "(" or c == "{":
            depth += 1
        elif c == ")" or c == "}":
            depth -= 1
        if c == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += c
    if cur.strip():
        out.append(cur)
    return [a.strip() for a in out]


OAM_CALL_RE = re.compile(r"OAM_ENTRY(_MODE)?\s*\(")


def parse_oam_body(body: str) -> list[OamEntry] | None:
    """Entries of a ``u16 X[OAM_DATA_SIZE(n)] = {n, OAM_ENTRY(...), ...}`` body."""
    if "OAM_ENTRY" not in body:
        return None
    entries = []
    for m in OAM_CALL_RE.finditer(body):
        end = m.end()
        depth = 1
        while depth:
            depth += {"(": 1, ")": -1}.get(body[end], 0)
            end += 1
        a = _split_args(body[m.end():end - 1])
        w, h = DIMS[a[2]]
        entries.append(OamEntry(_int(a[0]), _int(a[1]), w, h, FLIPS.get(a[3], None) if a[3] in FLIPS else _int(a[3]),
                                _int(a[4]), _int(a[5]), _int(a[6])))
    return entries


@dataclass
class CData:
    """Everything parsed from a set of C files, by symbol name."""
    oam: dict            # name -> [OamEntry]
    frames: dict         # name -> [(frame name, timer)]  (struct FrameData arrays)
    structs: dict        # name -> [ {field: value} ]     (other designated struct arrays)
    pointers: dict       # name -> [symbol, ...]           (pointer tables, flattened)
    incbin: dict         # name -> (data path, [leading numbers before the INCBIN])
    types: dict          # name -> C type


def parse_c(paths) -> CData:
    d = CData({}, {}, {}, {}, {}, {})
    for p in paths:
        text = COMMENT_RE.sub("", Path(p).read_text(errors="replace"))
        # drop #ifdef BUGFIX blocks (the build without BUGFIX is the reference)
        text = re.sub(r"#ifdef BUGFIX.*?#(?:else|endif)[^\n]*", "", text, flags=re.S)
        for m in DECL_RE.finditer(text):
            name, ctype = m.group("name"), m.group("type")
            pos = m.end()
            if pos < len(text) and text[pos] != "{":
                inc = INCBIN_ARG_RE.match(text, pos)
                if inc:
                    d.incbin[name] = (inc.group(1), [])
                    d.types[name] = ctype
                continue
            end = _balanced(text, pos)
            body = text[pos + 1:end - 1]
            d.types[name] = ctype
            inc = INCBIN_ARG_RE.search(body)
            if inc:
                lead = [_int(v) for v in _split_args(body[:inc.start()].rstrip().rstrip(","))
                        if v and re.fullmatch(r"[-+0-9a-fA-Fx ]+", v)]
                d.incbin[name] = (inc.group(1), lead)
                continue
            if ctype == "u16":
                e = parse_oam_body(body)
                if e is not None:
                    d.oam[name] = e
                continue
            if ctype == "struct FrameData":
                fr = []
                for item in re.finditer(r"\{([^{}]*)\}", body):
                    f = dict(_fields(item.group(1), ["pFrame", "timer"]))
                    if f.get("pFrame") and f["pFrame"] != "NULL":
                        fr.append((f["pFrame"], _int(f.get("timer", "0").replace("UCHAR_MAX", "255"))))
                d.frames[name] = fr
                continue
            if "*" in text[m.start():m.end()]:
                d.pointers[name] = re.findall(r"(?<![\w.])([A-Za-z_]\w*)(?=\s*(?:,|\}|$))", body)
                continue
            if ctype.startswith("struct"):
                d.structs[name] = [dict(_fields(item.group(1), [])) for item in re.finditer(r"\{([^{}]*)\}", body)]
                continue
    return d


def _fields(s: str, positional: list[str]):
    parts = _split_args(s)
    for i, part in enumerate(parts):
        if part.startswith("."):
            k, _, v = part[1:].partition("=")
            yield k.strip(), v.strip()
        elif i < len(positional):
            yield positional[i], part


def c_files(*globs: str) -> list[Path]:
    out = []
    for g in globs:
        out += sorted(ROOT.glob(g))
    return out


# ---------------------------------------------------------------------------
# Canvas
# ---------------------------------------------------------------------------


class Canvas:
    """Palette-index image in sprite-local coordinates (origin at the centre)."""

    def __init__(self, size: int = 256):
        self.size = size
        self.o = size // 2
        self.px = bytearray(size * size)

    def get(self, x: int, y: int) -> int:
        x += self.o
        y += self.o
        if 0 <= x < self.size and 0 <= y < self.size:
            return self.px[y * self.size + x]
        return 0

    def set(self, x: int, y: int, c: int) -> None:
        x += self.o
        y += self.o
        if 0 <= x < self.size and 0 <= y < self.size:
            self.px[y * self.size + x] = c

    # -- primitives (all coordinates may be floats) ----------------------

    def disc(self, cx, cy, r, c, shade=None):
        """Filled circle. ``shade``: (light, dark) colours for a lit edge."""
        r2 = r * r
        for y in range(math.floor(cy - r), math.ceil(cy + r) + 1):
            for x in range(math.floor(cx - r), math.ceil(cx + r) + 1):
                dx, dy = x + 0.5 - cx, y + 0.5 - cy
                if dx * dx + dy * dy <= r2:
                    col = c
                    if shade:
                        k = (dx + dy) / max(r, 0.5)
                        col = shade[0] if k < -0.7 else shade[1] if k > 0.7 else c
                    self.set(x, y, col)

    def ellipse(self, cx, cy, rx, ry, c, angle=0.0):
        ca, sa = math.cos(angle), math.sin(angle)
        R = max(rx, ry)
        for y in range(math.floor(cy - R), math.ceil(cy + R) + 1):
            for x in range(math.floor(cx - R), math.ceil(cx + R) + 1):
                dx, dy = x + 0.5 - cx, y + 0.5 - cy
                u, v = dx * ca + dy * sa, -dx * sa + dy * ca
                if (u / rx) ** 2 + (v / ry) ** 2 <= 1:
                    self.set(x, y, c)

    def capsule(self, x0, y0, x1, y1, r, c, r1=None):
        """Thick line with round ends (radius r at the start, r1 at the end)."""
        r1 = r if r1 is None else r1
        R = max(r, r1)
        lx, ly = x1 - x0, y1 - y0
        L2 = lx * lx + ly * ly or 1e-9
        for y in range(math.floor(min(y0, y1) - R), math.ceil(max(y0, y1) + R) + 1):
            for x in range(math.floor(min(x0, x1) - R), math.ceil(max(x0, x1) + R) + 1):
                px, py = x + 0.5 - x0, y + 0.5 - y0
                t = max(0.0, min(1.0, (px * lx + py * ly) / L2))
                dx, dy = px - t * lx, py - t * ly
                rr = r + (r1 - r) * t
                if dx * dx + dy * dy <= rr * rr:
                    self.set(x, y, c)

    def rect(self, x0, y0, x1, y1, c):
        """Filled rectangle, inclusive integer bounds."""
        for y in range(int(y0), int(y1) + 1):
            for x in range(int(x0), int(x1) + 1):
                self.set(x, y, c)

    def poly(self, pts, c):
        """Filled polygon (even-odd rule)."""
        ys = [p[1] for p in pts]
        n = len(pts)
        for y in range(math.floor(min(ys)), math.ceil(max(ys)) + 1):
            yc = y + 0.5
            xs = []
            for i in range(n):
                (xa, ya), (xb, yb) = pts[i], pts[(i + 1) % n]
                if (ya <= yc < yb) or (yb <= yc < ya):
                    xs.append(xa + (yc - ya) * (xb - xa) / (yb - ya))
            xs.sort()
            for a, b in zip(xs[::2], xs[1::2]):
                for x in range(math.ceil(a - 0.5), math.floor(b - 0.5) + 1):
                    self.set(x, y, c)

    def line(self, x0, y0, x1, y1, c):
        n = int(max(abs(x1 - x0), abs(y1 - y0))) + 1
        for i in range(n + 1):
            t = i / n
            self.set(round(x0 + (x1 - x0) * t), round(y0 + (y1 - y0) * t), c)

    def outline(self, c: int, keep=()):
        """Paint ``c`` on transparent pixels 4-adjacent to the figure."""
        s, src = self.size, self.px
        out = bytearray(src)
        for y in range(1, s - 1):
            row = y * s
            for x in range(1, s - 1):
                i = row + x
                if src[i] == 0 and (src[i - 1] or src[i + 1] or src[i - s] or src[i + s]):
                    out[i] = c
        self.px = out

    def recolor(self, mapping: dict):
        self.px = bytearray(mapping.get(v, v) for v in self.px)

    def bbox(self):
        s = self.size
        xs = [i % s for i, v in enumerate(self.px) if v]
        ys = [i // s for i, v in enumerate(self.px) if v]
        if not xs:
            return None
        return min(xs) - self.o, min(ys) - self.o, max(xs) - self.o, max(ys) - self.o


# ---------------------------------------------------------------------------
# Tile sheets
# ---------------------------------------------------------------------------


class TileSheet:
    """4bpp tiles addressed like 2D-mapped OBJ VRAM (32 tiles per row)."""

    def __init__(self, n_tiles: int = 1024):
        self.tiles = [None] * n_tiles      # None = never written
        self.owner = [None] * n_tiles

    def tile(self, t: int) -> bytearray:
        if self.tiles[t] is None:
            self.tiles[t] = bytearray(64)
        return self.tiles[t]

    def cut(self, canvas: Canvas, entries, ox: int = 0, oy: int = 0, owner=None, overwrite=False,
            tile_filter=None) -> int:
        """Copy the canvas pixels each entry covers into the tiles it shows.

        Tiles already written by another owner are left alone unless
        ``overwrite``. Returns the number of tiles written.
        """
        n = 0
        for e in entries:
            for dx, dy, t in e.tiles():
                if t >= len(self.tiles) or (tile_filter and not tile_filter(t)):
                    continue
                if self.owner[t] is not None and self.owner[t] != owner and not overwrite:
                    continue
                self.owner[t] = owner
                px = self.tile(t)
                for y in range(8):
                    for x in range(8):
                        # pixel (x, y) of the tile appears at screen (sx, sy)
                        sx = 7 - x if e.flip & 1 else x
                        sy = 7 - y if e.flip & 2 else y
                        px[y * 8 + x] = canvas.get(ox + e.x + dx + sx, oy + e.y + dy + sy)
                n += 1
        return n

    @staticmethod
    def tile_bytes(px) -> bytes:
        if px is None:
            return bytes(32)
        return bytes(px[i] | (px[i + 1] << 4) for i in range(0, 64, 2))

    def to_bytes(self, first: int, count: int) -> bytes:
        return b"".join(self.tile_bytes(self.tiles[t]) for t in range(first, first + count))

    def rows_to_bytes(self, first: int, rows: int) -> bytes:
        """``rows`` rows of 32 tiles starting at tile ``first``."""
        return self.to_bytes(first, rows * 32)


def tiles_to_bytes(tiles) -> bytes:
    return b"".join(TileSheet.tile_bytes(t) for t in tiles)


# ---------------------------------------------------------------------------
# Palettes
# ---------------------------------------------------------------------------


def bgr555(rgb) -> int:
    r, g, b = (max(0, min(255, int(v))) for v in rgb)
    return (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10)


def hexrgb(h: str):
    h = h.lstrip("#")
    return tuple(int(h[i:i + 2], 16) for i in (0, 2, 4))


def mix(a, b, t: float):
    return tuple(a[i] + (b[i] - a[i]) * t for i in range(3))


def pal_bytes(colors) -> bytes:
    """16 (or more) RGB tuples / '#rrggbb' strings -> BGR555 bytes."""
    out = bytearray()
    for c in colors:
        if isinstance(c, str):
            c = hexrgb(c)
        out += struct.pack("<H", bgr555(c))
    return bytes(out)


def ramp(dark, light, n: int):
    """n colours from dark to light (inclusive)."""
    dark, light = hexrgb(dark) if isinstance(dark, str) else dark, hexrgb(light) if isinstance(light, str) else light
    return [mix(dark, light, i / max(1, n - 1)) for i in range(n)]
