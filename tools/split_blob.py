#!/usr/bin/env python3
"""Split a Blob_* entry of database.json into smaller pieces.

    tools/split_blob.py Blob_6b2fac_71e20c.bin 0x6c0000=sFoo 0x6c1000=sBar
    tools/split_blob.py Blob_6b2fac_71e20c.bin @splits.txt   # "ADDR NAME" per line

Each ADDR=NAME starts a new piece at ROM offset ADDR (a 0x08xxxxxx address is
accepted too) named NAME. Bytes before the first split point stay in a piece
that keeps the original static sBlob_<start>_<end> style name. The pieces
are written as consecutive INCBIN_U8 arrays in the source file that included
the blob, and as consecutive Blob_<start>_<end>.bin entries in database.json,
so the bytes and their addresses do not change. Named pieces are not static,
so asm and other C files can reference them (declare them where needed).

Only blobs included as u8 arrays can be split (u8 arrays have no alignment,
so splitting them never adds padding).
"""

import argparse
import json
import re
import sys
from pathlib import Path

DATABASE = Path("database.json")
SOURCE_DIRS = ("src",)

DECL = re.compile(
    r'^(?P<indent>[ \t]*)(?P<static>static\s+)?(?P<const>const\s+)?u8\s+(?P<name>\w+)\s*\[[^\]]*\]\s*='
    r'\s*INCBIN_U8\("data/(?P<path>[^"]+)"\);(?P<rest>.*)$')


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


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("blob", help="database.json path of the blob, e.g. Blob_a5710_a8cdc.bin")
    parser.add_argument("splits", nargs="+", metavar="ADDR=NAME", help="split point, or @FILE with one \"ADDR NAME\" per line")
    parser.add_argument("-r", "--region", default="us")
    args = parser.parse_args()

    db = json.loads(DATABASE.read_text())
    idx = next((i for i, e in enumerate(db) if e["path"] == args.blob), None)
    if idx is None:
        sys.exit(f"{args.blob} is not in {DATABASE}")
    entry = db[idx]
    if entry.get("size", 1) != 1 or isinstance(entry["count"], dict) or set(entry["addr"]) != {args.region}:
        sys.exit(f"{args.blob}: only single-region byte blobs are supported")
    start = int(entry["addr"][args.region], 16)
    end = start + int(entry["count"], 16)

    splits = []
    for s in args.splits:
        if s.startswith("@"):
            for line in Path(s[1:]).read_text().splitlines():
                if line.strip() and not line.startswith("#"):
                    splits.append("=".join(line.split()[:2]))
        else:
            splits.append(s)

    points = {}
    for s in splits:
        addr, _, name = s.partition("=")
        addr = parse_addr(addr)
        if not name or not re.fullmatch(r"[A-Za-z_]\w*", name):
            sys.exit(f"bad split {s!r}")
        if not start <= addr < end:
            sys.exit(f"{addr:#x} is outside {args.blob} ({start:#x}-{end:#x})")
        if addr in points and points[addr] != name:
            sys.exit(f"{addr:#x} given two names: {points[addr]}, {name}")
        points[addr] = name

    src, text = find_source(args.blob)
    if src is None:
        sys.exit(f"no source file includes data/{args.blob}")
    lines = text.split("\n")
    line_idx = next(i for i, l in enumerate(lines) if f'"data/{args.blob}"' in l)
    m = DECL.match(lines[line_idx])
    if not m:
        sys.exit(f"{src}:{line_idx + 1}: not a plain u8 INCBIN_U8 declaration")

    bounds = sorted(points)
    if bounds[0] != start:
        bounds.insert(0, start)
    bounds.append(end)

    new_entries = []
    new_lines = []
    for a, b in zip(bounds, bounds[1:]):
        path = blob_name(a, b) + ".bin"
        e = {"path": path, "count": f"0x{b - a:X}", "addr": {args.region: f"0x{a:X}"}, "size": 1}
        if "dir" in entry:
            e = {"path": path, "dir": entry["dir"], "count": e["count"], "addr": e["addr"], "size": 1}
        new_entries.append(e)
        if a in points:
            name, static = points[a], ""
        else:
            name, static = "s" + blob_name(a, b), m["static"] or ""
        new_lines.append(f'{m["indent"]}{static}{m["const"] or ""}u8 {name}[] = INCBIN_U8("data/{path}");')
    if m["rest"].strip():
        new_lines[0] += m["rest"]

    old_name = m["name"]
    if re.search(rf"\b{re.escape(old_name)}\b", "\n".join(lines[:line_idx] + lines[line_idx + 1:])):
        print(f"warning: {old_name} is referenced elsewhere in {src}", file=sys.stderr)

    lines[line_idx:line_idx + 1] = new_lines
    src.write_text("\n".join(lines))
    db[idx:idx + 1] = new_entries
    DATABASE.write_text(json.dumps(db, indent=2) + "\n")
    print(f"{args.blob}: split into {len(new_entries)} pieces in {src}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
