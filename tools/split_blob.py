#!/usr/bin/env python3
"""Split a database.json entry (and the INCBIN array that includes it) into pieces.

    tools/split_blob.py Blob_6b2fac_71e20c.bin 0x6c0000=sFoo 0x6c1000=sBar
    tools/split_blob.py Blob_6b2fac_71e20c.bin @splits.txt   # "ADDR NAME [TYPE [PATH]]" per line
    tools/split_blob.py menus/game_over/obj.gfx.lz 0x739d58=sGameOverTextGfx:u32:menus/game_over/text.gfx.lz

Each ADDR=NAME[:TYPE[:PATH]] starts a new piece at ROM offset ADDR (a
0x08xxxxxx address is accepted too) named NAME. The pieces are written as
consecutive INCBIN arrays in the source file that included the entry, and as
consecutive entries in database.json, so the bytes and their addresses do
not change. Named pieces are not static, so asm and other C files can
reference them (declare them where needed).

Bytes before the first split point stay in a piece that keeps the original
declaration: for a Blob_* entry it gets the static sBlob_<start>_<end> style
name of its new range, for any other entry it keeps its name and path (with
the shorter size).

TYPE (u8, u16 or u32) is the element type of the piece. By default it is the
type of the original array when the piece's address and size are a multiple
of it, else the largest of u16/u8 that fits. A piece never gets a larger
alignment than its address allows, so splitting adds no padding.

PATH is the database.json path of the piece. By default a piece of a Blob_*
entry is Blob_<start>_<end>.bin (so it still counts as a blob in
tools/extractor.py -b and tools/progress.py) and a piece of another entry is
<dir>/<stem>_<addr><suffixes> next to the original file.
"""

import argparse
import json
import re
import sys
from pathlib import Path

DATABASE = Path("database.json")
SOURCE_DIRS = ("src",)
TYPE_SIZE = {"u8": 1, "u16": 2, "u32": 4, "s8": 1, "s16": 2, "s32": 4}

DECL = re.compile(
    r'^(?P<indent>[ \t]*)(?P<static>static\s+)?(?P<const>const\s+)?(?P<type>[us](?:8|16|32))\s+(?P<name>\w+)\s*'
    r'\[(?P<count>[^\]]*)\]\s*=\s*INCBIN_(?P<itype>[US](?:8|16|32))\("data/(?P<path>[^"]+)"\);(?P<rest>.*)$')


def parse_addr(text: str) -> int:
    value = int(text, 16)
    if value >= 0x08000000:
        value -= 0x08000000
    return value


def blob_name(start: int, end: int) -> str:
    return f"Blob_{start:x}_{end:x}"


def find_source(path: str):
    needle = f'"data/{path}"'
    for root in SOURCE_DIRS:
        for p in sorted(Path(root).rglob("*.c")):
            text = p.read_text()
            if needle in text:
                return p, text
    return None, None


def default_path(orig: str, addr: int) -> str:
    p = Path(orig)
    stem = p.name.split(".")[0]
    suffixes = p.name[len(stem):]
    return str(p.parent / f"{stem}_{addr:x}{suffixes}") if str(p.parent) != "." else f"{stem}_{addr:x}{suffixes}"


def piece_type(base: str, start: int, length: int, wanted: str = None) -> str:
    sign = base[0]
    if wanted:
        size = TYPE_SIZE[wanted]
        if start % size or length % size:
            sys.exit(f"{start:#x}: a {wanted} piece must start and end at a multiple of {size}")
        return wanted
    for size in (TYPE_SIZE[base], 2, 1):
        if size <= TYPE_SIZE[base] and start % size == 0 and length % size == 0:
            return f"{sign}{size * 8}"
    raise AssertionError


def parse_splits(specs, start, end):
    splits = []
    for s in specs:
        if s.startswith("@"):
            for line in Path(s[1:]).read_text().splitlines():
                parts = line.split()
                if parts and not line.startswith("#"):
                    splits.append((parts[0], parts[1], parts[2] if len(parts) > 2 else None,
                                   parts[3] if len(parts) > 3 else None))
        else:
            addr, _, rest = s.partition("=")
            fields = rest.split(":")
            splits.append((addr, fields[0], fields[1] if len(fields) > 1 and fields[1] else None,
                           fields[2] if len(fields) > 2 else None))
    points = {}
    for addr, name, typ, path in splits:
        addr = parse_addr(addr)
        if not name or not re.fullmatch(r"[A-Za-z_]\w*", name):
            sys.exit(f"bad split name {name!r}")
        if typ is not None and typ not in TYPE_SIZE:
            sys.exit(f"bad type {typ!r}")
        if not start <= addr < end:
            sys.exit(f"{addr:#x} is outside the entry ({start:#x}-{end:#x})")
        if addr in points and points[addr][0] != name:
            sys.exit(f"{addr:#x} given two names: {points[addr][0]}, {name}")
        points[addr] = (name, typ, path)
    return points


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("blob", help="database.json path of the entry, e.g. Blob_a5710_a8cdc.bin")
    parser.add_argument("splits", nargs="+", metavar="ADDR=NAME[:TYPE[:PATH]]",
                        help="split point, or @FILE with one \"ADDR NAME [TYPE [PATH]]\" per line")
    parser.add_argument("-r", "--region", default="us")
    args = parser.parse_args()

    db = json.loads(DATABASE.read_text())
    idx = next((i for i, e in enumerate(db) if e["path"] == args.blob), None)
    if idx is None:
        sys.exit(f"{args.blob} is not in {DATABASE}")
    entry = db[idx]
    if isinstance(entry["count"], dict) or set(entry["addr"]) != {args.region}:
        sys.exit(f"{args.blob}: only single-region entries are supported")
    esize = entry["size"]
    start = int(entry["addr"][args.region], 16)
    end = start + int(entry["count"], 16) * esize
    is_blob = Path(args.blob).name.startswith("Blob_")
    points = parse_splits(args.splits, start, end)

    src, text = find_source(args.blob)
    if src is None:
        sys.exit(f"no source file includes data/{args.blob}")
    lines = text.split("\n")
    line_idx = next(i for i, l in enumerate(lines) if f'"data/{args.blob}"' in l)
    m = DECL.match(lines[line_idx])
    if not m or TYPE_SIZE[m["type"]] != esize or m["itype"].lower() != m["type"]:
        sys.exit(f"{src}:{line_idx + 1}: not a plain one-dimensional INCBIN declaration of the entry's type")
    sized = m["count"].strip() != ""

    bounds = sorted(points)
    if bounds[0] != start:
        bounds.insert(0, start)
    bounds.append(end)

    new_entries = []
    new_lines = []
    paths = {e["path"] for e in db}
    for a, b in zip(bounds, bounds[1:]):
        if a in points:
            name, typ, path = points[a]
            typ = piece_type(m["type"], a, b - a, typ)
            static = ""
            path = path or (blob_name(a, b) + ".bin" if is_blob else default_path(args.blob, a))
            if path in paths and path != args.blob:
                sys.exit(f"{path} is already in {DATABASE}")
        else:
            typ = m["type"]
            if is_blob:
                name, path = "s" + blob_name(a, b), blob_name(a, b) + ".bin"
            else:
                name, path = m["name"], args.blob
            static = m["static"] or ""
        tsize = TYPE_SIZE[typ]
        e = {"path": path}
        if "dir" in entry:
            e["dir"] = entry["dir"]
        e.update({"count": f"0x{(b - a) // tsize:X}", "addr": {args.region: f"0x{a:X}"}, "size": tsize})
        new_entries.append(e)
        count = str((b - a) // tsize) if sized and not is_blob else ""
        new_lines.append(f'{m["indent"]}{static}{m["const"] or ""}{typ} {name}[{count}] = '
                         f'INCBIN_{typ.upper()}("data/{path}");')
    if m["rest"].strip():
        new_lines[0] += m["rest"]

    old_name = m["name"]
    if is_blob and re.search(rf"\b{re.escape(old_name)}\b", "\n".join(lines[:line_idx] + lines[line_idx + 1:])):
        print(f"warning: {old_name} is referenced elsewhere in {src}", file=sys.stderr)

    lines[line_idx:line_idx + 1] = new_lines
    src.write_text("\n".join(lines))
    db[idx:idx + 1] = new_entries
    DATABASE.write_text(json.dumps(db, indent=2) + "\n")
    print(f"{args.blob}: split into {len(new_entries)} pieces in {src}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
