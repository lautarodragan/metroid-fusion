# Synthetic golden build check

The real baserom is only needed by `tools/extractor.py`, which copies raw byte
ranges listed in `database.json` into `data/` and `sound/direct_sound_samples/`.
Code is built from `src/` and `asm/`, so most changes can be checked without
the real ROM.

`tools/make_synthetic_baserom.py` writes a deterministic 8 MiB
`mf_us_baserom.gba` filled with pseudo-random bytes (SHA-256 of a fixed seed in
counter mode). It contains nothing from the real game. Building from it gives a
ROM that is not playable but is always the same, and its sha1 is stored in
`mf_us_synthetic.sha1`.

## Running it

```sh
tools/setup_toolchain.sh   # once: builds agbcc and installs it to /opt/agbcc
make check-synthetic       # or: tools/check_synthetic.sh [--no-clean]
```

The check:

1. generates the synthetic baserom. It refuses to overwrite a baserom that is
   not synthetic, so a real one is never clobbered.
2. runs `make tidy DATA=1`, which `--no-clean` skips.
3. extracts the data and builds `mf_us.gba`.
4. runs `tools/check_data_placement.py`, which confirms that every
   `database.json` entry referenced by the sources is emitted at its address
   in the ROM, and names any data file that moved.
5. compares the ROM against `mf_us_synthetic.sha1`.

The check overwrites `mf_us_baserom.gba`, `data/` and
`sound/direct_sound_samples/` in the working tree. If you also work with a real
baserom, run the check in a separate checkout.

CI (`.github/workflows/build.yml`) runs this on every push and pull request.

## What it does and does not prove

- A change to code (C or asm) that keeps the real ROM matching also keeps the
  synthetic ROM matching, because code output does not depend on the baserom.
  If the synthetic sha1 changes, the real ROM would no longer match either.
- Splitting a blob into smaller `database.json` entries, renaming files, or
  moving `.incbin`/`INCBIN_*` references around keeps the sha1 the same, as
  long as the same bytes end up at the same addresses.
- Turning extracted data into C or asm literals (replacing a `.bin` with the
  real values) **changes the synthetic sha1** even when it matches the real ROM,
  because the synthetic ROM holds random bytes in that place. Such changes still
  need to be verified against the real ROM (`make check`).

## Updating the golden sha1

For matching-decomp work the output must not change, so the golden value should
almost never be updated. Update it only when a change is meant to alter the
synthetic output, such as data being converted to source as described above, or
an intentional change to the generator or seed, and only after the change has
been verified some other way:

```sh
tools/check_synthetic.sh --update
```

Commit the new `mf_us_synthetic.sha1` together with the change and explain why
it changed.
