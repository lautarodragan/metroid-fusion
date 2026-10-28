"""Where database.json regions and code symbols end up in a build.

The open baserom is laid out like the original ROM (database.json offsets),
but values *inside* it that point somewhere (interrupt handlers, pointer
tables, ...) must hold addresses of the build that will consume it, which
can differ once code or data shifts. This module answers:

- which symbol a region is INCBINed as (scanning src/, asm/, sound/),
- where that symbol (or a function) is in a previous build (its ELF, or the
  linker map for global symbols only),
- which symbols the code passes to the LZ77 decompression routines.

Without a previous build every address falls back to the database offset,
which is what a non-shifted build produces; build_open_rom.py then rebuilds
with the real addresses.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

from inventory import ROOT, Region

sys.path.insert(0, str(ROOT / "tools"))

ROM_BASE = 0x08000000

C_INCBIN_RE = re.compile(r'(\w+)\s*\[[^\]]*\]\s*=\s*INCBIN_\w+\(\s*"([^"]+)"\s*\)')
ASM_INCBIN_RE = re.compile(r'^(\w+):[^\n]*\n(?:\s*(?:@[^\n]*)?\n)*?\s*\.incbin\s+"([^"]+)"', re.M)
MAP_SYMBOL_RE = re.compile(r"^\s+0x([0-9a-fA-F]+)\s+([A-Za-z_][\w.$]*)(?:\s*=\s*\.)?\s*$")
# C: LZ77UncompVram(sym, ...), CallLZ77UncompWram((const u8*)sym, ...)
C_LZ_RE = re.compile(r"\b(?:Call)?LZ77Uncomp(?:Vram|Wram)\s*\(\s*(?:\([^()]*\)\s*)?&?\s*([A-Za-z_]\w*)")
# asm: ldr r0, _label @ =sym ... bl LZ77UncompVram (r0 is the source)
ASM_LDR_R0_RE = re.compile(r"ldr r0, (?:_\w+ @ )?=([A-Za-z_]\w*)")


def _sources():
    for pattern in ("src/**/*.c", "src/**/*.h", "include/**/*.h", "asm/**/*.s", "sound/**/*.s"):
        for p in ROOT.glob(pattern):
            if p.suffix == ".s" and p.with_suffix(".c").exists():
                continue  # compiler output
            yield p


def scan_incbin_symbols() -> dict[str, str]:
    """``"data/<path>" -> symbol`` for every named INCBIN / .incbin."""
    out: dict[str, str] = {}
    for p in _sources():
        text = p.read_text(errors="replace")
        rx = ASM_INCBIN_RE if p.suffix == ".s" else C_INCBIN_RE
        for m in rx.finditer(text):
            out.setdefault(m.group(2), m.group(1))
    return out


def scan_lz_sources() -> set[str]:
    """Symbols the code passes as source to LZ77UncompVram/Wram."""
    found: set[str] = set()
    for p in _sources():
        text = p.read_text(errors="replace")
        if p.suffix != ".s":
            found.update(C_LZ_RE.findall(text))
            continue
        lines = text.splitlines()
        for i, line in enumerate(lines):
            m = ASM_LDR_R0_RE.search(line)
            if not m:
                continue
            for nxt in lines[i + 1:i + 5]:
                code = nxt.split("@")[0]
                if re.search(r"\bbl\s+(?:Call)?LZ77Uncomp(?:Vram|Wram)\b", code):
                    found.add(m.group(1))
                    break
                if re.match(r"\s*(?:b\w*|pop|\w+\s+r0\b)", code) and not re.match(r"\s*\w+\s+r[1-9]", code):
                    break  # branch, or r0 overwritten
    return found


class Layout:
    def __init__(self, elf: str | None = None, map_file: str | None = None):
        self.symbols: dict[str, int] = {}
        self.functions: dict[str, int] = {}  # with the Thumb bit
        self.source = "none"
        if elf and Path(elf).is_file():
            from elfsyms import STT_FUNC, STT_OBJECT, Elf
            for s in Elf(elf).symbols:
                if s.type == STT_FUNC:
                    self.functions.setdefault(s.name, s.value)
                    self.symbols.setdefault(s.name, s.value & ~1)
                elif s.type == STT_OBJECT or (s.type == 0 and s.value >= 0x02000000 and not s.is_mapping):
                    self.symbols.setdefault(s.name, s.value)
            self.source = f"elf {elf}"
        elif map_file and Path(map_file).is_file():
            for line in Path(map_file).read_text(errors="replace").splitlines():
                m = MAP_SYMBOL_RE.match(line)
                if m and int(m.group(1), 16) >= 0x02000000:
                    self.symbols.setdefault(m.group(2), int(m.group(1), 16))
            self.source = f"map {map_file}"
        self.incbin = scan_incbin_symbols()
        self.unresolved: set[str] = set()

    @property
    def have_build(self) -> bool:
        return bool(self.symbols)

    def symbol_of(self, r: Region) -> str | None:
        return self.incbin.get(f"{r.dir}/{r.path}")

    def region_address(self, r: Region) -> int:
        """Address of region ``r`` in the build (database offset if unknown)."""
        sym = self.symbol_of(r)
        if sym and sym in self.symbols:
            return self.symbols[sym]
        if self.have_build:
            self.unresolved.add(r.path)
        return ROM_BASE + r.addr

    def address(self, regions: list[Region], baserom_offset: int) -> int:
        """Build address of the byte at ``baserom_offset`` (inside some region)."""
        for r in regions:
            if r.addr <= baserom_offset < r.addr + r.size:
                return self.region_address(r) + (baserom_offset - r.addr)
        raise KeyError(f"no database region contains {baserom_offset:#x}")

    def function(self, name: str, thumb: bool = True) -> int:
        """Address of a function, with bit 0 set for Thumb code."""
        if name in self.functions:
            return self.functions[name]
        if name in self.symbols:
            return self.symbols[name] | (1 if thumb else 0)
        raise SystemExit(f"function {name} not found in the previous build ({self.source})")
