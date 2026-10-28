"""Minimal ELF32 (little endian) reader for the ROM tools: sections and symbols.

Only the standard library is used, so the tools that import this do not need
pyelftools or binutils.
"""

import struct
from dataclasses import dataclass
from pathlib import Path
from typing import List

SHT_SYMTAB = 2
SHT_NOBITS = 8
SHF_ALLOC = 0x2
STT_OBJECT = 1
STT_FUNC = 2


@dataclass(frozen=True)
class Section:
    name: str
    addr: int
    size: int
    type: int
    flags: int


@dataclass(frozen=True)
class Symbol:
    name: str
    value: int
    size: int
    type: int
    bind: int
    shndx: int

    @property
    def is_mapping(self) -> bool:
        """ARM mapping symbols ($a, $t, $d) mark code and data inside sections."""
        return self.name[:2] in ("$a", "$t", "$d") and (len(self.name) == 2 or self.name[2] == ".")


class Elf:
    def __init__(self, path):
        data = Path(path).read_bytes()
        if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
            raise ValueError(f"{path}: not a 32-bit little endian ELF file")
        shoff, = struct.unpack_from("<I", data, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 0x2E)
        raw = [struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize) for i in range(shnum)]

        def cstr(off: int) -> str:
            return data[off:data.index(b"\0", off)].decode()

        shstr = raw[shstrndx][4]
        self.sections: List[Section] = [
            Section(cstr(shstr + s[0]), s[3], s[5], s[1], s[2]) for s in raw]
        self.symbols: List[Symbol] = []
        for s in raw:
            if s[1] != SHT_SYMTAB:
                continue
            strtab = raw[s[6]][4]
            for off in range(s[4], s[4] + s[5], 16):
                name, value, size, info, _, shndx = struct.unpack_from("<IIIBBH", data, off)
                if name == 0:
                    continue
                self.symbols.append(Symbol(cstr(strtab + name), value, size, info & 0xF, info >> 4, shndx))

    def alloc_sections(self) -> List[Section]:
        return [s for s in self.sections if s.flags & SHF_ALLOC and s.type != SHT_NOBITS and s.size]
