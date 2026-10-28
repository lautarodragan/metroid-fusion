#!/usr/bin/env python3
"""Check that every extracted data file ends up at its database.json address.

For a matching build, each data file listed in database.json must be emitted
at exactly the ROM offset it was extracted from. With the synthetic
baserom each region holds unique pseudo-random bytes, so comparing the built
ROM against the baserom at those offsets catches misplaced data and reports
which file moved. Entries that no source file references are skipped (they
are stale and their bytes are not part of the build).
"""

import argparse
import json
import sys
from pathlib import Path

SOURCE_DIRS = ("src", "asm", "sound", "include")
SOURCE_EXTS = (".c", ".h", ".s", ".inc")


def referenced_text() -> str:
    parts = []
    for root in SOURCE_DIRS:
        for p in Path(root).rglob("*"):
            if p.suffix not in SOURCE_EXTS or not p.is_file():
                continue
            # Skip compiler output for C files
            if p.suffix == ".s" and p.with_suffix(".c").exists():
                continue
            parts.append(p.read_text(errors="ignore"))
    return "\n".join(parts)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("-r", "--region", default="us")
    parser.add_argument("--baserom", default=None)
    parser.add_argument("--rom", default=None)
    args = parser.parse_args()

    baserom = Path(args.baserom or f"mf_{args.region}_baserom.gba").read_bytes()
    rom = Path(args.rom or f"mf_{args.region}.gba").read_bytes()
    db = json.loads(Path("database.json").read_text())
    text = referenced_text()

    checked = skipped = 0
    bad = []
    for entry in db:
        addr = entry["addr"].get(args.region)
        if addr is None:
            continue
        if entry["path"] not in text:
            skipped += 1
            continue
        count = entry["count"]
        if isinstance(count, dict):
            count = count[args.region]
        start = int(addr, 16)
        end = start + int(count, 16) * entry["size"]
        checked += 1
        if rom[start:end] != baserom[start:end]:
            found = rom.find(baserom[start:end])
            where = f"found at {found:#x}" if found >= 0 else "not found"
            bad.append(f"  {entry['path']} expected at {start:#x} ({where})")

    print(f"data placement: {checked} entries checked, {skipped} unreferenced skipped, "
          f"{len(bad)} misplaced")
    if bad:
        print("\n".join(bad[:50]))
        if len(bad) > 50:
            print(f"  ... and {len(bad) - 50} more")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
