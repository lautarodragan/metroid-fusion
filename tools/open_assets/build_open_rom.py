"""Build mf_us.gba from an open (placeholder) baserom, in two passes.

Some placeholder regions hold pointers into the build (interrupt handlers,
pointer tables; see apply_known_layouts in make_open_baserom.py), so the
baserom depends on where the linker places code and data:

1. generate the open baserom (pointers at their database offsets, or taken
   from an existing build), extract and build;
2. regenerate it with the resulting ``mf_us.elf``/``.map``; if anything changed,
   re-extract, rebuild the objects that include the changed files and link
   again. Repeat until the baserom is stable.

The Makefile does not track INCBIN dependencies, so this script deletes the
objects whose sources reference a data file that changed.

Usage (from the repository root, or with -C):
    python3 tools/open_assets/build_open_rom.py [-C DIR] [-j N] [--shift [AMOUNT]]

--shift builds the shift test ROM instead (``make SHIFT=1``,
mf_us_shifted.gba, see book/src/shiftability.md), with the baserom's pointers
taken from that build: running it checks that the open ROM still works when
code and data move.

Refuses to run if mf_us_baserom.gba exists and is not an open baserom.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

from make_open_baserom import is_open_baserom  # noqa: E402

BASEROM = "mf_us_baserom.gba"


def run(cmd: list[str], cwd: Path, quiet: bool = True) -> None:
    out = subprocess.DEVNULL if quiet else None
    subprocess.run(cmd, cwd=cwd, check=True, stdout=out)


def data_files(root: Path) -> dict[Path, tuple[str, int]]:
    db = json.loads((root / "database.json").read_text())
    files = {}
    for e in db:
        p = root / e.get("dir", "data") / e["path"]
        if p.exists():
            files[p] = (hashlib.sha1(p.read_bytes()).hexdigest(), p.stat().st_mtime_ns)
    return files


def extract(root: Path, quiet: bool) -> int:
    """Run the extractor, keeping the mtime of files whose content is unchanged."""
    before = data_files(root)
    run([sys.executable, "tools/extractor.py", "-q"], root, quiet)
    changed = 0
    for p, (digest, _) in data_files(root).items():
        old = before.get(p)
        if old and old[0] == digest:
            os.utime(p, ns=(old[1], old[1]))
        else:
            changed += 1
    return changed


INCLUDE_RE = re.compile(r'"((?:data|sound/direct_sound_samples)/[^"]+\.[A-Za-z0-9.]+)"')


def invalidate(root: Path) -> int:
    """Delete objects older than a data file their source includes.

    The Makefile does not know that an object depends on the files it
    INCBINs, so without this a changed data file would not be picked up.
    """
    removed = 0
    for pattern in ("src/**/*.c", "asm/**/*.s", "sound/**/*.s"):
        for src in root.glob(pattern):
            if src.suffix == ".s" and src.with_suffix(".c").exists():
                continue  # generated from the .c
            # preproc inlines INCBIN data into the .s compiled from a .c
            outs = [src.with_suffix(".o")] + ([src.with_suffix(".s")] if src.suffix == ".c" else [])
            outs = [o for o in outs if o.exists()]
            if not outs:
                continue
            t = min(o.stat().st_mtime_ns for o in outs)
            for rel in INCLUDE_RE.findall(src.read_text(errors="replace")):
                d = root / rel
                if d.exists() and d.stat().st_mtime_ns > t:
                    for o in outs:
                        o.unlink()
                    removed += 1
                    break
    return removed


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("-C", "--directory", default=".", help="repository root to build in")
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    ap.add_argument("-v", "--verbose", action="store_true")
    ap.add_argument("--shift", nargs="?", const="0x100", default=None, metavar="AMOUNT",
                    help="build mf_us_shifted.gba with `make SHIFT=1 SHIFT_AMOUNT=AMOUNT`")
    args = ap.parse_args()
    root = Path(args.directory).resolve()
    baserom = root / BASEROM
    if baserom.exists() and not is_open_baserom(baserom):
        print(f"error: {baserom} exists and is not an open baserom; refusing to touch it "
              "(build in a separate checkout)", file=sys.stderr)
        return 1

    # the generator of the tree being built (it reads that tree's sources)
    gen = [sys.executable, str(root / "tools" / "open_assets" / "make_open_baserom.py"), "-o", BASEROM]
    make = ["make", f"-j{args.jobs}"]
    rom = "mf_us.gba"
    if args.shift:
        make += ["SHIFT=1", f"SHIFT_AMOUNT={args.shift}"]
        rom = "mf_us_shifted.gba"
    rom_map = rom.replace(".gba", ".map")
    quiet = not args.verbose
    prev = None
    for attempt in range(4):
        cmd = gen + (["--map", rom_map] if (root / rom_map).exists() else [])
        run(cmd, root, quiet)
        cur = baserom.read_bytes()
        if cur == prev:
            print(f"* open ROM built: {root / rom} (baserom stable after {attempt} rebuilds)")
            return 0
        changed = extract(root, quiet)
        n = invalidate(root)
        print(f"* pass {attempt + 1}: {changed} data files changed, {n} objects invalidated")
        run(make, root, quiet)
        prev = cur
    print("error: the open baserom did not converge", file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
