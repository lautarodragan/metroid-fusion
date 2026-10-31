#!/usr/bin/env python3
"""Fail if a source file contains a raw compiler matching trick.

Matching tricks (no-op statements and register pinning that only exist to make
agbcc emit the original instructions) must go through the FAKE_MATCH_* macros
of include/compiler_tricks.h, so that they are visible and greppable. See the
"Matching tricks" page of the book.

Flagged in src/ and include/ (except include/compiler_tricks.h), comments
ignored:
- an empty asm statement: asm("") / asm("" : ...)
- a register variable pinned with asm("rN")
- a no-op compound assignment: x |= 0, x += 0, x -= 0, x ^= 0
- a self-assignment: x = x
- an increment immediately undone: x++, x-- / x++; x--
- a "while (0)" outside a #define (a do { } while (0) wrapper written
  inline; the multi-statement macro idiom inside a #define is fine)
"""

import re
import sys
from pathlib import Path

EXEMPT = {Path("include/compiler_tricks.h")}

LVALUE = r"[A-Za-z_][\w.\[\]>-]*"

CHECKS = [
    (re.compile(r'\basm\s*(?:volatile\s*)?\(\s*""'), "empty asm statement"),
    (re.compile(r'\bregister\b[^;]*\basm\s*\('), "register variable pinned with asm()"),
    (re.compile(r'(?<![=!<>])(?:\|=|\+=|-=|\^=)\s*0[uUlL]*\s*[;,)]'), "no-op compound assignment"),
    (re.compile(r'(?<![\w.>\]])(' + LVALUE + r')\s*=\s*\1\s*;'), "self-assignment"),
    (re.compile(r'(?<![\w.>\]])(' + LVALUE + r')\+\+\s*[,;]\s*\1--'), "increment then decrement"),
]

WHILE_ZERO = re.compile(r'\bwhile\s*\(\s*0\s*\)')


def strip_comments(text):
    """Remove comments, keeping line numbers."""
    out = []
    i, n = 0, len(text)
    while i < n:
        if text.startswith("//", i):
            j = text.find("\n", i)
            j = n if j < 0 else j
            i = j
        elif text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append("\n" * text.count("\n", i, j))
            i = j
        else:
            out.append(text[i])
            i += 1
    return "".join(out)


def logical_lines(text):
    """Yield (line number, line, inside #define) for each physical line."""
    in_define = False
    for num, line in enumerate(text.split("\n"), 1):
        starts_define = re.match(r"\s*#\s*define\b", line) is not None
        yield num, line, in_define or starts_define
        in_define = (in_define or starts_define) and line.rstrip().endswith("\\")


def main():
    errors = []
    files = [p for root in ("src", "include") for p in sorted(Path(root).rglob("*"))
             if p.suffix in (".c", ".h") and p not in EXEMPT]
    for path in files:
        text = strip_comments(path.read_text(encoding="utf-8", errors="replace"))
        for num, line, in_define in logical_lines(text):
            for regex, what in CHECKS:
                if regex.search(line):
                    errors.append(f"{path}:{num}: {what}: {line.strip()}")
            if not in_define and WHILE_ZERO.search(line):
                errors.append(f"{path}:{num}: inline do {{ }} while (0) wrapper: {line.strip()}")

    for e in errors:
        print(e)
    if errors:
        print(f"\n{len(errors)} raw matching trick(s) found. Use the FAKE_MATCH_* macros of "
              "include/compiler_tricks.h (see the \"Matching tricks\" page of the book).",
              file=sys.stderr)
        return 1
    print("No raw matching tricks found.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
