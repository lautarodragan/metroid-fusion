# Metroid Fusion Decomp

This is a work in progress decompilation of Metroid Fusion.

Documentation: https://lautarodragan.github.io/metroid-fusion/ (sources in [book/](book/))

3601/3607 functions decompiled (99.83%, 6 left)

0x5dca90/0x6f9d24 bytes of data not in blobs (84.03%, 0x11d294 left)

These numbers are computed by `python3 tools/progress.py` (see its docstring for the method).

Progress can be seen here: https://docs.google.com/spreadsheets/d/1HvJ-jynb-4P9tfEBVJmkQFpIg6mJRDRUBvDIBiLxQIo/

**Shiftability:** code and C data reference everything by symbol, and `make check-shift` verifies that a shifted build keeps every pointer it emits correct. Pointer tables stored inside extracted blobs (data still copied from the baserom) are not converted yet, so moving data can still break the ROM at run time. `tools/find_blob_pointers.py` lists them using the real baserom. See [book/src/shiftability.md](book/src/shiftability.md).

This repository can be used to build multiple ROMs. The ROMs are named like this: `mf_{region}.gba` (or `mf_{region}_debug.gba`)

Region indicates which region the ROM targets:
- us: USA, North America `sha1: ca33f4348c2c05dd330d37b97e2c5a69531dfe87`
- eu: Europe **(Not yet supported)**
- jp: Japan **(Not yet supported)**
- cn: China **(Not yet supported)**
- eu_beta: Europe beta version **(Not yet supported)**

Debug simply indicates whether the ROM contains the debug features, it is optional.

**Debug is not supported yet**

The default built ROM is mf_us.gba

**Discords**:
- https://discord.gg/2MGB9Xbr9y Metroidret
- https://discord.gg/WtekHKb MAGConst

## Dependencies

- [agbcc](https://github.com/pret/agbcc)
- `binutils-arm-none-eabi`
- A baserom for each ROM desired to be built (i.e.`mf_us_baserom.gba` if you wish to build `mf_us.gba`).
- `python3`
- `g++`

## Setup

- **WINDOWS ONLY**: Install and setup [WSL](https://docs.microsoft.com/en-us/windows/wsl/install)
- Run `sudo apt update` just in case
- Install `binutils-arm-none-eabi` by running this command: `sudo apt-get install binutils-arm-none-eabi`
- Install `git` by running this command: `sudo apt-get install git`
- Install `make` by running this command: `sudo apt-get install make`

- Alternatively, `tools/setup_toolchain.sh` clones, builds and installs agbcc in one step (to `/opt/agbcc`, with symlinks in `/usr/local/bin`; see the script for options)
- Clone [agbcc](https://github.com/pret/agbcc) by running this command: `git clone https://github.com/pret/agbcc`
- Enter the agbcc folder (run `cd agbcc`) and build it (run `./build.sh`)
- Add agbcc to your path (`export PATH="<agbcc_path>:$PATH"`, where `<agbcc_path>` is the full path to the agbcc directory)
- Either:
  - Install agbcc into this project (by using its `./install.sh <path>` script, where `<path>` is the path to the root of this repository), or
  - Add agbcc to your path (`export PATH="<agbcc_path>:$PATH"`, where `<agbcc_path>` is the full path to the agbcc directory)

## Build

- Run `make clean` if necessary
  - Use `make clean DATA=1` to remove data as well
- Run the data extractor if necessary: `python3 tools/extractor.py`
  - Use the `-r` flag to specify a region other than `us` (ex: `-r jp`)
  - Use the `-d` flag to extract only debug data from the US beta ROM (required for building a ROM with debug features)
- Run `make` (using the `-j` option is recommended to speed up the process)
- To build another version of the ROM you can do either of the following:
  - Specify it directly (ex: `make us_debug` for the US ROM with debug features)
  - Specify the flags, REGION (takes the region name, defaults to `us`) and DEBUG (takes 0 or 1, defaults to 0)
- Optionally, you can combine the commands to make it easier: `python3 tools/extractor.py && make -j`

## Checking without a baserom

`make check-synthetic` builds the ROM from a deterministic synthetic baserom and compares it with the golden sha1 in `mf_us_synthetic.sha1`. It catches code changes that would break matching without needing the real ROM. See [book/src/synthetic-check.md](book/src/synthetic-check.md) for what it covers and when the golden value may be updated.

## Checking shiftability

`make check-shift` fails on hardcoded ROM addresses in the sources, then links a second ROM with padding inserted in the code and data (`make SHIFT=1`, `mf_us_shifted.gba`) and checks that every pointer follows what it points to. It needs extracted data (from the real or the synthetic baserom). See [book/src/shiftability.md](book/src/shiftability.md).

## Emulator tests

`tests/run_emu_tests.sh` builds the ROM from the open placeholder baserom (`tools/open_assets/`, a generated test fixture that needs no original ROM) in a scratch directory and runs pytest tests in a headless mGBA (libretro core, HLE BIOS): boot sequence up to the first room, screenshot regression and RAM checks. Needs `libretro-mgba` and `pytest`. See [book/src/emu-tests.md](book/src/emu-tests.md).

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md)
