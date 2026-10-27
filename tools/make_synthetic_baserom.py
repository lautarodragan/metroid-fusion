#!/usr/bin/env python3
"""Generate a deterministic synthetic baserom for build verification.

The real baserom is only used by tools/extractor.py, which copies raw byte
ranges (listed in database.json) into data/*.bin and
sound/direct_sound_samples/*.bin. Nothing parses or decompresses those bytes
before they are embedded into the ROM (via .incbin or preproc's INCBIN_*), so
any content works for building. This script fills the whole ROM with
pseudo-random bytes derived from a fixed seed (SHA-256 in counter mode), so
that every extracted region has unique, reproducible content and a build made
from it has a stable "golden" sha1 (see mf_us_synthetic.sha1).

The output is NOT a playable ROM and contains no data from the real game.
"""

import argparse
import hashlib
import sys

# Size of the ROM image the Makefile produces (PAD_TO = 0x08800000).
ROM_SIZE = 0x800000
DEFAULT_SEED = "metroid-fusion-synthetic-baserom-v1"
DEFAULT_OUTPUT = "mf_{region}_baserom.gba"


def generate(seed: str, size: int = ROM_SIZE) -> bytes:
    key = hashlib.sha256(seed.encode("utf-8")).digest()
    out = bytearray()
    block = 0
    while len(out) < size:
        out += hashlib.sha256(key + block.to_bytes(8, "little")).digest()
        block += 1
    return bytes(out[:size])


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("-r", "--region", default="us", choices=["us"],
                        help="Region of the baserom to generate (default: us)")
    parser.add_argument("-o", "--output", default=None,
                        help="Output path (default: mf_<region>_baserom.gba)")
    parser.add_argument("-s", "--seed", default=DEFAULT_SEED,
                        help="Seed string (changing it changes the golden sha1)")
    parser.add_argument("-f", "--force", action="store_true",
                        help="Overwrite the output even if it does not look synthetic")
    args = parser.parse_args()

    output = args.output or DEFAULT_OUTPUT.format(region=args.region)
    data = generate(args.seed)

    # Refuse to clobber a file that is not a synthetic rom generated with this
    # seed (e.g. a real baserom someone placed in the repo), unless forced.
    try:
        with open(output, "rb") as f:
            existing = f.read()
    except FileNotFoundError:
        existing = None
    if existing is not None and existing != data and not args.force:
        print(f"error: {output} exists and is not the synthetic baserom; "
              "move it away or pass --force", file=sys.stderr)
        return 1

    if existing != data:
        with open(output, "wb") as f:
            f.write(data)
    print(f"{output}: sha1 {hashlib.sha1(data).hexdigest()} ({len(data):#x} bytes)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
