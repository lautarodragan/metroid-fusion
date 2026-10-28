"""Room layouts for the open base ROM (test fixtures for the emulator tests).

Rooms are drawn as ASCII maps in ``tools/open_assets/maps/*.txt`` (format and
legend in docs/open_assets_rooms.md). One character per block gives both the
collision (clipdata) and the look (BG1 metatile, chosen by tiles.py from the
collision type and the neighbours); a second grid gives the background layer
(BG2). The maps reuse the slots (width, height, byte budget) of the original
rooms, so the doors defined in C (src/data/rooms_data.c) line up.

Every other room gets a generated box in the same semantic tileset, so any
room at least reads as walls around open space.
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path

import formats
import tiles
from inventory import ROOT

MAPS_DIR = Path(__file__).resolve().parent / "maps"


# ---------------------------------------------------------------------------
# enum Clipdata, read from the header so the values never drift
# ---------------------------------------------------------------------------

def clipdata_enum() -> dict[str, int]:
    text = (ROOT / "include/constants/clipdata.h").read_text()
    start = text.index("MAKE_ENUM(u16, Clipdata)")
    body = text[text.index("{", start) + 1:text.index("};", start)]
    values, cur = {}, -1
    for line in body.splitlines():
        line = line.split("//")[0].strip().rstrip(",")
        if not line:
            continue
        m = re.match(r"(CLIPDATA_\w+)(?:\s*=\s*(\w+))?$", line)
        if not m:
            continue
        cur = int(m.group(2), 0) if m.group(2) else cur + 1
        values[m.group(1)[len("CLIPDATA_"):]] = cur
    return values


CLIP = clipdata_enum()


# ---------------------------------------------------------------------------
# Legend
# ---------------------------------------------------------------------------
# foreground character -> (clipdata, kind). "kind" selects the metatile:
# "solid" is autotiled from the neighbours, other kinds name a metatile or a
# rule below.

FG_LEGEND: dict[str, tuple[str, str]] = {
    ".": ("AIR", "air"),
    " ": ("AIR", "air"),
    "#": ("SOLID", "solid"),
    "=": ("PASS_THROUGH_BOTTOM", "platform"),
    "T": ("CEILING_RUNGS", "ladder_ceiling"),
    "D": ("DOOR_TRANSITION", "door"),
    "O": ("AIR", "jamb"),
    "G": ("GRAY_DOOR", "hatch"),          # lockable hatch, drawn by the game
    "s": ("SHOT_BLOCK_REFORM", "break_shot"),
    "b": ("BOMB_BLOCK_REFORM", "break_bomb"),
    "m": ("MISSILE_BLOCK_NEVER_REFORM", "break_missile"),
    "p": ("POWER_BOMB_BLOCK_NEVER_REFORM", "break_power_bomb"),
    ">": ("SPEEDBOOST_BLOCK_REFORM", "break_speed"),
    "*": ("SCREW_ATTACK_NO_REFORM", "break_screw"),
    "c": ("CRUMBLE", "break_crumble"),
    "~": ("WATER", "water_surface"),
    "w": ("WATER", "water"),
}

# blocks that count as "wall" when deciding which edges of a solid are lit
WALLISH = set("#Tsbmp>*c")

BG_LEGEND: dict[str, str] = {
    ".": "air",
    " ": "air",
    "p": "back_panel",
    "v": "back_vent",
    "-": "back_pipe_h",
    "|": "back_pipe_v",
    "+": "back_pipe_x",
    "L": "back_light",
    "w": "back_window",
    "g": "back_girder",
}


# ---------------------------------------------------------------------------
# Maps
# ---------------------------------------------------------------------------

@dataclass
class RoomMap:
    name: str
    area: str            # symbol prefix, e.g. "MainDeck"
    room: int
    width: int
    height: int
    fg: list[str]
    bg: list[str]
    path: Path | None = None


def parse_map(path: Path) -> RoomMap:
    meta: dict[str, str] = {}
    grids: dict[str, list[str]] = {}
    cur = None
    for raw in path.read_text().splitlines():
        if raw.startswith(";"):
            continue
        m = re.match(r"\[(\w+)\]\s*$", raw)
        if m:
            cur = m.group(1)
            grids[cur] = []
            continue
        if cur is None:
            line = raw.strip()
            if ":" in line:
                k, v = line.split(":", 1)
                meta[k.strip()] = v.strip()
            continue
        if raw.strip() == "" and not grids[cur]:
            continue
        grids[cur].append(raw.rstrip("\n"))
    w, h = (int(v) for v in meta["size"].split("x"))
    out = {}
    for key in ("fg", "bg"):
        rows = [r for r in grids.get(key, [])]
        while rows and rows[-1].strip() == "":
            rows.pop()
        if len(rows) != h:
            raise SystemExit(f"{path}: [{key}] has {len(rows)} rows, expected {h}")
        for i, r in enumerate(rows):
            if len(r) != w:
                raise SystemExit(f"{path}: [{key}] row {i} has {len(r)} columns, expected {w}")
        out[key] = rows
    return RoomMap(path.stem, meta["area"], int(meta["room"]), w, h, out["fg"], out["bg"], path)


def load_maps() -> list[RoomMap]:
    return [parse_map(p) for p in sorted(MAPS_DIR.glob("*.txt"))]


# ---------------------------------------------------------------------------
# Map -> layers
# ---------------------------------------------------------------------------

def render(rm: RoomMap, ts: tiles.Tileset) -> tuple[list[int], list[int], list[int]]:
    """(clipdata, bg1, bg2) block arrays, row major."""
    w, h = rm.width, rm.height
    fg = rm.fg

    def at(x: int, y: int) -> str:
        if 0 <= x < w and 0 <= y < h:
            return fg[y][x]
        return "#"

    clip, bg1, bg2 = [], [], []
    for y in range(h):
        for x in range(w):
            ch = fg[y][x]
            if ch not in FG_LEGEND:
                raise SystemExit(f"{rm.path}: unknown character {ch!r} at {x},{y}")
            clip_name, kind = FG_LEGEND[ch]
            clip.append(CLIP[clip_name])
            if kind == "solid":
                mask = 0
                for bit, (dx, dy) in ((tiles.N, (0, -1)), (tiles.E, (1, 0)),
                                      (tiles.S, (0, 1)), (tiles.W, (-1, 0))):
                    if at(x + dx, y + dy) not in WALLISH:
                        mask |= bit
                meta = tiles.solid_index(mask)
            elif kind in ("air", "hatch"):
                meta = 0
            elif kind == "door":
                meta = ts.names["door_left" if x < w // 2 else "door_right"]
            elif kind == "jamb":
                side = "left" if x < w // 2 else "right"
                up, down = at(x, y - 1) == "O", at(x, y + 1) == "O"
                part = "mid" if up and down else ("top" if down else "bot")
                meta = ts.names[f"jamb_{side}_{part}"]
            else:
                meta = ts.names[kind]
            bg1.append(meta)
            b = rm.bg[y][x]
            if b not in BG_LEGEND:
                raise SystemExit(f"{rm.path}: unknown background character {b!r} at {x},{y}")
            bg2.append(ts.names.get(BG_LEGEND[b], 0) if BG_LEGEND[b] != "air" else 0)
    return clip, bg1, bg2


def encode(blocks: list[int]) -> bytes:
    return formats.room_rle_compress(blocks)


# ---------------------------------------------------------------------------
# Generated rooms (everything without a map)
# ---------------------------------------------------------------------------

def box_map(w: int, h: int) -> list[str]:
    """Solid border two blocks thick (one if the room is tiny) around air."""
    t = 2 if w > 6 and h > 6 else 1
    return ["".join("#" if x < t or x >= w - t or y < t or y >= h - t else "." for x in range(w))
            for y in range(h)]


def generic_layers(w: int, h: int, ts: tiles.Tileset):
    rm = RoomMap("generic", "", 0, w, h, box_map(w, h), ["." * w] * h)
    return render(rm, ts)


# ---------------------------------------------------------------------------
# Writing the regions
# ---------------------------------------------------------------------------

ROOM_LAYER_RE = re.compile(r"^s(\w+?)_(\d+)_(Clipdata|Bg0|Bg1|Bg2)$")
LAYER_INDEX = {"Clipdata": 0, "Bg1": 1, "Bg2": 2}


def apply_rooms(rom: bytearray, regions, layout, meta: dict) -> list[str]:
    """Write the mapped rooms and a box in the semantic tileset for every
    other room layer. Returns notes; fails if a map does not fit its slot."""
    ts = tiles.build_tileset()
    maps = {(m.area, m.room): m for m in load_maps()}
    rendered = {k: render(m, ts) for k, m in maps.items()}
    generic_cache: dict[tuple[int, int], tuple] = {}
    used: dict[tuple[str, int], list[str]] = {k: [] for k in maps}
    fallbacks = 0
    for r in regions:
        if r.category not in ("room_bg_rle", "room_clipdata_rle"):
            continue
        sym = tiles.symbol_of(layout, r) or ""
        m = ROOM_LAYER_RE.match(sym)
        dims = meta.get(r.path, {})
        if not m or "width" not in dims:
            continue
        area, room, layer = m.group(1), int(m.group(2)), m.group(3)
        w, h = dims["width"], dims["height"]
        if (area, room) in maps:
            rm = maps[(area, room)]
            if (rm.width, rm.height) != (w, h):
                raise SystemExit(f"{rm.path}: size {rm.width}x{rm.height}, but {sym} is {w}x{h}")
            blocks = rendered[(area, room)][LAYER_INDEX[layer]] if layer in LAYER_INDEX else [0] * (w * h)
            stream = encode(blocks)
            if len(stream) > r.size:
                raise SystemExit(f"{rm.path}: the {layer} layer needs {len(stream)} bytes, "
                                 f"the slot ({sym}) has {r.size}; simplify the map")
            used[(area, room)].append(f"{layer} {len(stream)}/{r.size}")
            tiles.put_region(rom, r, stream)
            continue
        if (w, h) not in generic_cache:
            generic_cache[(w, h)] = generic_layers(w, h, ts)
        clip, bg1, _ = generic_cache[(w, h)]
        if layer == "Clipdata":
            options = [clip, [16 if v else 0 for v in clip]]
        elif layer == "Bg1":
            options = [bg1, [1 if v else 0 for v in bg1]]
        else:
            options = []
        options.append([0] * (w * h))
        for i, blocks in enumerate(options):
            stream = encode(blocks)
            if len(stream) <= r.size:
                fallbacks += i > 0 and i == len(options) - 1
                tiles.put_region(rom, r, stream)
                break
        else:
            raise SystemExit(f"{sym}: not even an empty layer fits in {r.size} bytes")
    notes = []
    for (area, room), layers in sorted(used.items()):
        if not layers:
            raise SystemExit(f"map {maps[(area, room)].path}: no room layers named s{area}_{room}_*")
        notes.append(f"room {area} {room} ({maps[(area, room)].path.name}): " + ", ".join(layers))
    notes.append(f"other rooms: generated boxes ({fallbacks} layers left empty, too small)")
    return notes
