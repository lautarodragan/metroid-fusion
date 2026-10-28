#!/usr/bin/env python3
"""Print the decompilation progress numbers shown in README.md.

Run from anywhere: python3 tools/progress.py [--elf mf_us.elf]

Functions
---------
The total, 3607, is the function count upstream has always used in the README
(it is constant across its history, and a full `mf_us.elf` has exactly 3607
distinct function symbol names: C + other asm + disassembly). A function is
"left" while it is still in compiler-generated disassembly, that is, for every
`thumb_func_start` / `arm_func_start` / `non_word_aligned_thumb_func_start`
in asm/disasm_*.s. Everything else counts as done:

    decompiled = 3607 - (function starts in asm/disasm_*.s)

The other asm files (crt0, intr_main, sound_code, audio_internal, syscalls,
romheader) are hand-written or library code that is not meant to be turned
into C, so, as upstream did, their 36 functions count as done.

Upstream's README numbers were always exactly one less than this count
(0c2a5e7: 352 starts vs "351 left"; 446ccaf: 377 vs 376; 9138ef9: 415 vs 414),
which comes from the spreadsheet it was taken from. This script counts the
files as they are and applies no correction.

With --elf, the function symbols of a built ELF are also split into C, other
asm and disassembly, as a cross-check.

Data
----
Reuses `python3 tools/extractor.py -b`: every database.json entry whose path
starts with "Blob" is data still copied from the baserom as an opaque chunk;
everything else out of the 0x6f9d24 bytes of data is "not in blobs".
"""

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))

import extractor  # noqa: E402

TOTAL_FUNCTIONS = 3607
FUNC_START = re.compile(r"^\s*(?:non_word_aligned_thumb|thumb|arm)_func_start\s+(\S+)", re.M)


def asm_functions(pattern: str) -> list:
    names = []
    for path in sorted((ROOT / "asm").glob(pattern)):
        names += FUNC_START.findall(path.read_text())
    return names


def disasm_functions() -> list:
    return asm_functions("disasm_*.s")


def function_progress_line() -> str:
    left = len(disasm_functions())
    done = TOTAL_FUNCTIONS - left
    return f"{done}/{TOTAL_FUNCTIONS} functions decompiled ({done / TOTAL_FUNCTIONS:.2%}, {left} left)"


def data_progress_line() -> str:
    return extractor.blob_progress_line(str(ROOT / extractor.DATABASE_PATH))


def elf_breakdown(elf_path: str) -> str:
    from elfsyms import STT_FUNC, Elf

    funcs = {s.name for s in Elf(elf_path).symbols if s.type == STT_FUNC and not s.is_mapping}
    disasm = set(disasm_functions())
    other = set(asm_functions("*.s")) - disasm
    in_c = funcs - disasm - other
    return (f"{elf_path}: {len(funcs)} function symbols: {len(in_c)} from C, "
            f"{len(funcs & other)} from hand-written/library asm, "
            f"{len(funcs & disasm)} still in asm/disasm_*.s")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n", 1)[0])
    parser.add_argument("--elf", help="also break down the function symbols of this ELF")
    args = parser.parse_args()
    print(function_progress_line())
    print(data_progress_line())
    if args.elf:
        print(elf_breakdown(args.elf))


if __name__ == "__main__":
    main()
