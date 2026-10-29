#!/usr/bin/env python3
"""Compare a normal build with a shifted build (make SHIFT=1) to find pointers
that do not follow the code or data they point to.

The shifted build links the same objects with padding inserted in the middle
of the code and at the start of the data, so most symbols move. For every
word that, in the normal build, points to a symbol, the word at the same
place in the shifted build must point to the same symbol at its new address.
A word that keeps its old value is a hardcoded address.

Only places where the build (not the baserom) decides the bytes are checked,
so the result does not depend on the baserom contents:
- literal pools and other data inside code ($d mapping symbols)
- .rodata/.data, except the ranges extracted from the baserom
  (database.json), whose content is unknown (see tools/find_blob_pointers.py)
- inside the extracted ranges, the words that differ between the two builds:
  data included piece by piece around pointers written as symbols (the
  voicegroups in sound/voicegroups.s). Each such word must point to a symbol
  and follow it.

A word "points to a symbol" when it equals the address of a symbol, the
address of a Thumb function plus one, or an address inside a sized object.
Other words that happen to be in the ROM address range are counted and can be
listed with -v; they are not errors.
"""

import argparse
import bisect
import json
import sys
from collections import Counter
from pathlib import Path

sys.dont_write_bytecode = True
sys.path.insert(0, str(Path(__file__).resolve().parent))
from elfsyms import Elf, STT_FUNC, STT_OBJECT  # noqa: E402

ROM_START = 0x08000000
ROM_END = 0x0A000000
STT_SECTION, STT_FILE = 3, 4
SHN_ABS = 0xFFF1


def rom_symbols(elf):
    out = []
    for s in elf.symbols:
        if s.is_mapping or s.type in (STT_SECTION, STT_FILE) or s.shndx in (0, SHN_ABS):
            continue
        if s.name.startswith(".") or not ROM_START <= s.value < ROM_END:
            continue
        out.append(s)
    return out


class Delta:
    """Piecewise constant address translation from the normal to the shifted build."""

    def __init__(self, base_syms, shifted_syms):
        def unique(syms):
            count = Counter(s.name for s in syms)
            return {s.name: s.value for s in syms if count[s.name] == 1}

        a, b = unique(base_syms), unique(shifted_syms)
        pairs = sorted((a[n], b[n] - a[n]) for n in a.keys() & b.keys())
        if not pairs:
            raise SystemExit("no common symbols between the builds")
        self.addrs = [p[0] for p in pairs]
        self.deltas = [p[1] for p in pairs]

    def __call__(self, addr):
        i = bisect.bisect_right(self.addrs, addr) - 1
        return self.deltas[max(i, 0)]

    def nonzero(self):
        return sum(1 for d in self.deltas if d)


class Targets:
    """Answers "does this value point to a symbol of the normal build"."""

    def __init__(self, syms, code_sections):
        self.starts = {}
        self.labels = set()  # untyped labels inside code (branch targets, literal pools)
        self.thumb = set()
        for s in syms:
            self.starts.setdefault(s.value, s.name)
            if s.type not in (STT_OBJECT, STT_FUNC) and s.shndx in code_sections:
                self.labels.add(s.value)
            if s.type == STT_FUNC and s.value & 1:
                self.thumb.add(s.value)  # Thumb function symbols have bit 0 set
        sized = sorted((s.value, s.value + s.size, s.name) for s in syms
                       if s.size and s.type in (STT_OBJECT, STT_FUNC))
        self.sized_starts = [s[0] for s in sized]
        self.sized = sized

    def container(self, p):
        """The sized object that contains address p, as (start, end, name), or None."""
        i = bisect.bisect_right(self.sized_starts, p) - 1
        for start, end, name in reversed(self.sized[max(i - 7, 0):i + 1]):
            if start <= p < end:
                return start, end, name
        return None

    def resolve(self, v, inside=True):
        """Return (address used for translation, description) or None.

        inside=False (used for data) only accepts the start of an object or
        function, so that bytes of data tables that happen to look like an
        address are not mistaken for pointers."""
        if not inside and (v in self.labels or (v & 1 and v - 1 in self.labels)):
            return None
        if v in self.starts:
            return v, self.starts[v]
        if v in self.thumb:
            return v - 1, self.starts.get(v - 1, "thumb function")
        if v & 1 and (v - 1) in self.starts:
            return v - 1, self.starts[v - 1] + "|1"
        if inside:
            c = self.container(v)
            if c and c[0] < v:
                return c[0], f"{c[2]}+{v - c[0]:#x}"
        return None


def code_data_ranges(elf, section):
    """[start, end) ranges marked as data ($d) inside an executable section."""
    idx = elf.sections.index(section)
    maps = sorted((s.value, s.name[:2]) for s in elf.symbols
                  if s.is_mapping and s.shndx == idx)
    out = []
    for i, (addr, kind) in enumerate(maps):
        if kind != "$d":
            continue
        end = maps[i + 1][0] if i + 1 < len(maps) else section.addr + section.size
        if end > addr:
            out.append((addr, end))
    return out


def extracted_ranges(region):
    out = []
    for e in json.loads(Path("database.json").read_text()):
        addr = e["addr"].get(region)
        if addr is None:
            continue
        count = e["count"][region] if isinstance(e["count"], dict) else e["count"]
        start = ROM_START + int(addr, 16)
        out.append((start, start + int(count, 16) * e["size"]))
    return sorted(out)


def subtract(ranges, holes):
    out = []
    holes = sorted(holes)
    for start, end in ranges:
        cur = start
        i = bisect.bisect_right([h[1] for h in holes], cur)
        while cur < end:
            while i < len(holes) and holes[i][1] <= cur:
                i += 1
            if i >= len(holes) or holes[i][0] >= end:
                out.append((cur, end))
                break
            if holes[i][0] > cur:
                out.append((cur, holes[i][0]))
            cur = max(cur, holes[i][1])
    return out


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("-r", "--region", default="us")
    parser.add_argument("--base", help="normal build prefix (default mf_<region>)")
    parser.add_argument("--shifted", help="shifted build prefix (default mf_<region>_shifted)")
    parser.add_argument("-v", "--verbose", action="store_true",
                        help="also list in-range words that do not point to a symbol")
    args = parser.parse_args()
    base = args.base or f"mf_{args.region}"
    shifted = args.shifted or f"mf_{args.region}_shifted"

    elf_a, elf_b = Elf(base + ".elf"), Elf(shifted + ".elf")
    rom_a, rom_b = Path(base + ".gba").read_bytes(), Path(shifted + ".gba").read_bytes()
    syms_a = rom_symbols(elf_a)
    delta = Delta(syms_a, rom_symbols(elf_b))
    if not delta.nonzero():
        print("check_shift: the shifted build is not shifted", file=sys.stderr)
        return 1
    code_sections = {i for i, sec in enumerate(elf_a.sections) if sec.flags & 0x4}
    targets = Targets(syms_a, code_sections)
    rom_end = ROM_START + len(rom_a)

    code, data = [], []
    for sec in elf_a.alloc_sections():
        if not ROM_START <= sec.addr < ROM_END:
            continue
        if sec.flags & 0x4:  # SHF_EXECINSTR: only data inside code
            code += code_data_ranges(elf_a, sec)
        else:
            data.append((sec.addr, sec.addr + sec.size))
    extracted = extracted_ranges(args.region)
    ranges = [(s, e, True) for s, e in subtract(sorted(code), extracted)]
    ranges += [(s, e, False) for s, e in subtract(sorted(data), extracted)]

    checked = scanned = 0
    bad, unresolved = [], []
    for start, end, in_code in ranges:
        for p in range((start + 3) & ~3, end - 3, 4):
            scanned += 1
            v = int.from_bytes(rom_a[p - ROM_START:p - ROM_START + 4], "little")
            if not ROM_START <= v < rom_end:
                continue
            if not in_code:
                # A pointer in data is word aligned within a word aligned object
                c = targets.container(p)
                if c and (c[0] & 3 or (p - c[0]) & 3):
                    continue
            hit = targets.resolve(v, inside=in_code)
            if hit is None:
                unresolved.append((p, v))
                continue
            checked += 1
            q = p + delta(p) - ROM_START
            got = int.from_bytes(rom_b[q:q + 4], "little")
            want = v + delta(hit[0])
            if got != want:
                bad.append((p, v, got, want, hit[1]))

    # Extracted ranges: words the build changed (pointers written as symbols between .incbin pieces)
    extracted_checked = 0
    for start, end in extracted:
        if not any(s <= start and end <= e for s, e in data):
            continue
        for p in range((start + 3) & ~3, end - 3, 4):
            q = p + delta(p) - ROM_START
            v = int.from_bytes(rom_a[p - ROM_START:p - ROM_START + 4], "little")
            got = int.from_bytes(rom_b[q:q + 4], "little")
            if got == v:
                continue
            hit = targets.resolve(v) if ROM_START <= v < rom_end else None
            if hit is None:
                bad.append((p, v, got, None, "not a pointer, but differs in the shifted build"))
                continue
            extracted_checked += 1
            want = v + delta(hit[0])
            if got != want:
                bad.append((p, v, got, want, hit[1]))
    checked += extracted_checked

    def where(addr):
        hit = targets.resolve(addr)
        return hit[1] if hit else "?"

    print(f"shift check: {len(ranges)} ranges, {scanned} words scanned, {checked} pointers checked "
          f"({extracted_checked} inside extracted data), {len(bad)} not shifted, "
          f"{len(unresolved)} other in-range words")
    for p, v, got, want, name in bad[:100]:
        expected = f"expected {want:#010x}" if want is not None else "expected the same value"
        print(f"  {p:#010x} ({where(p)}): {v:#010x} -> {name}; shifted build has {got:#010x}, {expected}")
    if len(bad) > 100:
        print(f"  ... and {len(bad) - 100} more")
    if args.verbose:
        for p, v in unresolved:
            print(f"  other: {p:#010x} ({where(p)}): {v:#010x}")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
