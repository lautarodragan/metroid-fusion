#!/usr/bin/env python3
"""List the ROM pointers stored inside extracted data of unknown structure.

The build gives every pointer in code and in C data a symbol, but the bytes
extracted from the baserom (database.json) are copied as they are. If such a
blob holds a pointer table, the pointers keep their old values when code or
data moves, and the shifted ROM breaks. This can only be found with the real
ROM (the synthetic baserom is random), so run this with your baserom:

    python3 tools/find_blob_pointers.py            # mf_us_baserom.gba
    python3 tools/find_blob_pointers.py --json pointers.json

Every 4-byte aligned word in 0x08000000..end of ROM inside the scanned
entries is reported, grouped by entry, with the symbol (from the ELF of a
build, which has the same addresses as the baserom) or database.json entry
that contains the target. By default the Blob_* entries and the other
entries without a known format (.bin files and files without extension,
except the direct sound samples) are scanned; --all scans every entry.

Graphics and other binary data contain words that look like addresses by
chance. A word is marked "*" when it points exactly to the start of a
symbol, of a database.json entry or (with bit 0 set) of a function; runs of
such words are most likely pointer tables. The others are probably not
pointers.

To fix a pointer table, turn it into C (an array of symbols), or split the
blob around it and replace each pointer word, for example with
tools/split_blob.py and a small .s or C file. tools/check_shift.sh then
covers it.
"""

import argparse
import bisect
import json
import sys
from pathlib import Path

sys.dont_write_bytecode = True
sys.path.insert(0, str(Path(__file__).resolve().parent))
from elfsyms import Elf, STT_FUNC, STT_OBJECT  # noqa: E402

ROM_START = 0x08000000
KNOWN_TITLES = (b"METROID4USA", b"METROID4EUR", b"METROID4JPN", b"METFUSIONCHN", b"METROIDAGBJ")


def db_entries(region):
    out = []
    for e in json.loads(Path("database.json").read_text()):
        addr = e["addr"].get(region)
        if addr is None:
            continue
        count = e["count"][region] if isinstance(e["count"], dict) else e["count"]
        start = int(addr, 16)
        out.append((start, start + int(count, 16) * e["size"], e["path"]))
    return sorted(out)


def unknown_format(path: str) -> bool:
    name = Path(path).name
    if path.startswith("direct_sound_samples/"):
        return False
    return path.startswith("Blob_") or name.endswith(".bin") or "." not in name


class Lookup:
    def __init__(self, entries, elf_path):
        self.entries = entries
        self.entry_starts = [e[0] for e in entries]
        self.syms = []
        self.funcs = set()
        labels = set()  # untyped labels inside code: branch targets, not pointer targets
        if elf_path and Path(elf_path).exists():
            elf = Elf(elf_path)
            for s in elf.symbols:
                if s.is_mapping or s.name.startswith(".") or s.type not in (0, STT_OBJECT, STT_FUNC):
                    continue
                if not ROM_START <= s.value < ROM_START + 0x2000000 or s.shndx in (0, 0xFFF1):
                    continue
                value = s.value & ~1 if s.type == STT_FUNC else s.value
                if s.type == STT_FUNC:
                    self.funcs.add(value)
                elif s.type == 0 and elf.sections[s.shndx].flags & 0x4:
                    labels.add(value)
                self.syms.append((value, s.size, s.name))
        self.syms.sort()
        self.sym_starts = [s[0] for s in self.syms]
        self.exact = ({s[0] for s in self.syms} - labels) | {ROM_START + e[0] for e in entries}

    def symbol(self, addr):
        """Name of the symbol at or before addr, as name+offset (sized symbols only if inside)."""
        i = bisect.bisect_right(self.sym_starts, addr) - 1
        if i < 0:
            return None
        value, size, name = self.syms[i]
        if value == addr:
            return name
        if not size or addr < value + size:
            return f"{name}+{addr - value:#x}"
        return None

    def entry(self, offset):
        i = bisect.bisect_right(self.entry_starts, offset) - 1
        if i >= 0 and offset < self.entries[i][1]:
            start, _, path = self.entries[i]
            return path if offset == start else f"{path}+{offset - start:#x}"
        return None

    def describe(self, v):
        thumb = bool(v & 1) and (v - 1) in self.funcs
        target = v - 1 if thumb else v
        likely = thumb or v in self.exact
        parts = [p for p in (self.symbol(target), self.entry(target - ROM_START)) if p]
        desc = " / ".join(parts) if parts else "?"
        return likely, ("thumb " if thumb else "") + desc


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("-r", "--region", default="us")
    parser.add_argument("--baserom", help="default: mf_<region>_baserom.gba")
    parser.add_argument("--elf", help="ELF of a build, for symbol names (default: mf_<region>.elf if present)")
    parser.add_argument("--all", action="store_true", help="scan every database.json entry")
    parser.add_argument("--likely", action="store_true", help="only report words marked *")
    parser.add_argument("--json", metavar="FILE", help="also write the results as JSON")
    args = parser.parse_args()

    rom = Path(args.baserom or f"mf_{args.region}_baserom.gba").read_bytes()
    if rom[0xA0:0xAC].rstrip(b"\0") not in KNOWN_TITLES:
        print("warning: the baserom has no known game title; with the synthetic baserom every "
              "result is noise", file=sys.stderr)
    rom_end = ROM_START + len(rom)
    entries = db_entries(args.region)
    look = Lookup(entries, args.elf or f"mf_{args.region}.elf")

    results = []
    total = likely_total = 0
    for start, end, path in entries:
        if not args.all and not unknown_format(path):
            continue
        words = []
        for off in range((start + 3) & ~3, end - 3, 4):
            v = int.from_bytes(rom[off:off + 4], "little")
            if not ROM_START <= v < rom_end:
                continue
            likely, desc = look.describe(v)
            if args.likely and not likely:
                continue
            words.append({"offset": off, "value": v, "likely": likely, "target": desc,
                          "where": look.symbol(ROM_START + off)})
        if not words:
            continue
        total += len(words)
        likely_total += sum(w["likely"] for w in words)
        results.append({"path": path, "start": start, "end": end, "words": words})
        print(f"{path} ({start:#x}-{end:#x}): {len(words)} word(s), "
              f"{sum(w['likely'] for w in words)} likely")
        for w in words:
            mark = "*" if w["likely"] else " "
            print(f"  {mark} {w['offset']:#08x} {w['where'] or '':<40} {w['value']:#010x} -> {w['target']}")

    print(f"\n{total} word(s) in ROM range in {len(results)} entries, {likely_total} likely pointers (*)")
    if args.json:
        Path(args.json).write_text(json.dumps(results, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
