#!/usr/bin/env python3
"""Fail if a source file contains a literal ROM address.

A literal such as `.4byte 0x0839EC68`, `ldr r0, =0x8605d08` or
`(const u16*)0x85dfd6c` keeps pointing to the same place when code or data
moves, so the ROM breaks as soon as anything changes size. Use the symbol of
the code or data instead (tools/split_blob.py gives a symbol to an address
inside a blob).

Checked: C and headers (src/, include/), asm (asm/, sound/, *.inc), the
linker script and the Makefile. Comments are ignored. A ROM address is any
number in 0x08000000-0x09FFFFFF, written in hex (with or without the leading
zero, any case) or in decimal.

Exceptions are listed in ALLOWED below, each with the reason it is not a
pointer that has to follow the code.
"""

import re
import sys
from pathlib import Path

ROM_START, ROM_END = 0x08000000, 0x0A000000

# (file, value): reason
ALLOWED = {
    ("include/gba/memory.h", 0x08000000): "ROM_BASE: start of the cartridge address space",
    ("linker.ld", 0x08000000): "ORIGIN of the rom memory region",
    ("Makefile", 0x08800000): "PAD_TO: size the ROM is padded to (8 MiB), not an address in it",
}

HEX = re.compile(r"(?<![\w.$])0[xX]([0-9a-fA-F]+)(?![\w.])")
DEC = re.compile(r"(?<![\w.$])([1-9][0-9]{8})(?![\w.])")


def sources():
    files = [Path("linker.ld"), Path("Makefile")]
    for root, exts in (("src", (".c", ".h")), ("include", (".h", ".inc")),
                       ("asm", (".s", ".inc")), ("sound", (".s", ".inc"))):
        for p in sorted(Path(root).rglob("*")):
            if not p.is_file() or p.suffix not in exts:
                continue
            # Compiler output of a C file
            if p.suffix == ".s" and p.with_suffix(".c").exists():
                continue
            files.append(p)
    return files


def strip_comments(text: str, kind: str) -> str:
    """Blank out comments, keeping line numbers."""
    def blank(m):
        return re.sub(r"[^\n]", " ", m.group(0))
    if kind == "c":
        # Strings first so that "//" or "/*" inside them is kept
        return re.sub(r'"(?:\\.|[^"\\\n])*"|//[^\n]*|/\*.*?\*/',
                      lambda m: m.group(0) if m.group(0).startswith('"') else blank(m), text, flags=re.S)
    if kind == "asm":
        return re.sub(r'"(?:\\.|[^"\\\n])*"|@[^\n]*|/\*.*?\*/',
                      lambda m: m.group(0) if m.group(0).startswith('"') else blank(m), text, flags=re.S)
    return re.sub(r"#[^\n]*", blank, text)  # Makefile


def main() -> int:
    bad = []
    for p in sources():
        kind = "make" if p.name == "Makefile" else "asm" if p.suffix in (".s", ".inc") else "c"
        if p.name == "linker.ld":
            kind = "c"
        text = strip_comments(p.read_text(errors="ignore"), kind)
        for n, line in enumerate(text.split("\n"), 1):
            for m in [*HEX.finditer(line), *DEC.finditer(line)]:
                v = int(m.group(1), 16 if m.re is HEX else 10)
                if ROM_START <= v < ROM_END and (str(p), v) not in ALLOWED:
                    bad.append(f"{p}:{n}: {m.group(0)}: {line.strip()}")
    if bad:
        print(f"{len(bad)} hardcoded ROM address(es); use the symbol of what they point to "
              f"(tools/split_blob.py splits a blob at an address):")
        print("\n".join(bad))
        return 1
    print("hardcoded pointers: none")
    return 0


if __name__ == "__main__":
    sys.exit(main())
