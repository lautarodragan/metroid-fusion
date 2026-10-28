# Contributing

<!-- Based on CONTRIBUTING.md at the repository root. If the rules change
     there, update this page too. -->

> The reference version is
> [CONTRIBUTING.md](https://github.com/lautarodragan/metroid-fusion/blob/main/CONTRIBUTING.md)
> in the repository. If this page and that file differ, the original wins.

## Important: clean room

Anyone wanting to contribute **MUST** read the following and adhere to the
steps outlined, in order to not violate any copyright.

This decompile is a
[clean room design](https://en.wikipedia.org/wiki/Clean_room_design).
It **MUST NOT** incorporate any code owned by Nintendo or other third parties.

In order to achieve this, all code has to be written completely fresh, without
reference to any third party code, **no matter if leaked or not**.

Derived from this there is the following requirement for contributors:

- Contributors **MUST NOT** study or refer to any code owned by Nintendo or
  other third parties.

## Submitting a change

1. Clone this repository and follow the [setup](setup.md) instructions if you
   haven't already.
2. For any set of changes you want to submit, create a branch off of `main`
   (make sure you're on the latest commit).
3. When ready to submit your changes, make sure the ROM still compiles
   (`make`).
4. If the ROM compiles, make sure the ROM still matches the base ROM
   (`make check`).
   - Recommended: run `./check_roms.sh` to build and check ROMs for every
     supported region (may require `chmod +x check_roms.sh`). You will need a
     base ROM for each supported region.
   - Without a base ROM, use `make check-synthetic`
     ([Verifying without the ROM](docs/synthetic_check.md)).
5. Open a PR on GitHub, and add a description that summarizes your changes.
