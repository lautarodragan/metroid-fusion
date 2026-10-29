#!/usr/bin/env python3
"""Fix the calls made from functions placed in IWRAM (OPTIMIZE_IWRAM builds).

Usage: tools/iwram_calls.py file.s   (rewrites it in place)

Functions marked IWRAM_CODE (include/optimize.h) are emitted in the
.iwram_code section, linked to run from IWRAM. A Thumb bl reaches +-4 MB, so
from IWRAM it cannot reach ROM: the files that contain such functions are
compiled with -mlong-calls, which turns calls into "bl _call_via_rX" (a libgcc
stub that does "bx rX"); inside .iwram_code those become calls to the IWRAM
copies of the stubs (asm/iwram_call_via.s). Any other bl left in .iwram_code
that does not go to a local label or to another function of the same section
cannot be linked, and is reported as an error.
"""

import re
import sys

path = sys.argv[1]
lines = open(path).read().split("\n")
section = "text"
iwram_funcs = set()
for line in lines:
    s = line.strip()
    if s.startswith(".section"):
        section = "iwram" if ".iwram_code" in s else "other"
    elif s in (".text", ".data") or s.startswith(".text") or s.startswith(".data"):
        section = "text"
    m = re.match(r"^([A-Za-z_]\w*):", s)
    if m and section == "iwram":
        iwram_funcs.add(m.group(1))

out = []
errors = []
section = "text"
for line in lines:
    s = line.strip()
    if s.startswith(".section"):
        section = "iwram" if ".iwram_code" in s else "other"
    elif s in (".text", ".data") or s.startswith(".text") or s.startswith(".data"):
        section = "text"
    if section == "iwram":
        m = re.match(r"^(\s*bl\s+)(\S+)(.*)$", line)
        if m:
            target = m.group(2)
            if target.startswith("_call_via_"):
                line = m.group(1) + "_iwram" + target + m.group(3)
            elif not target.startswith(".") and target not in iwram_funcs:
                errors.append(f"{path}: bl {target} from .iwram_code cannot reach ROM")
    out.append(line)

if errors:
    sys.stderr.write("\n".join(errors) + "\n")
    sys.exit(1)
open(path, "w").write("\n".join(out))
