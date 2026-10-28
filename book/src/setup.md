# Setup and build

## Dependencies

- [agbcc](https://github.com/pret/agbcc)
- `binutils-arm-none-eabi`
- A base ROM for each ROM you want to build (for example
  `mf_us_baserom.gba` to build `mf_us.gba`). If you don't have the original
  ROM, you can still verify your changes with the
  [synthetic check](synthetic-check.md).
- `python3`
- `g++`

## Setup

- **Windows only:** install and configure
  [WSL](https://docs.microsoft.com/en-us/windows/wsl/install).
- Run `sudo apt update`, just in case.
- Install `binutils-arm-none-eabi`: `sudo apt-get install binutils-arm-none-eabi`
- Install `git`: `sudo apt-get install git`
- Install `make`: `sudo apt-get install make`

### agbcc

The quickest way is to use the repository's script:

```sh
tools/setup_toolchain.sh
```

It clones, builds and installs agbcc in a single step (in `/opt/agbcc`, with
symlinks in `/usr/local/bin`; see the script for the options).

If you'd rather do it by hand:

1. Clone agbcc: `git clone https://github.com/pret/agbcc`
2. Enter the folder (`cd agbcc`) and build it (`./build.sh`).
3. Then, either:
   - Install agbcc inside this project with its `./install.sh <path>` script,
     where `<path>` is the root of this repository, or
   - Add agbcc to your `PATH` (`export PATH="<agbcc_path>:$PATH"`, where
     `<agbcc_path>` is the full path to the agbcc directory).

## Build

- Run `make clean` if needed.
  - `make clean DATA=1` also deletes the extracted data.
- Run the data extractor if needed: `python3 tools/extractor.py`
  - Use `-r` to pick a region other than `us` (for example `-r jp`).
  - Use `-d` to extract only the debug data from the USA beta ROM (needed to
    build a ROM with debug functions).
- Run `make` (`-j` is recommended to speed it up).
- To build another version of the ROM, either:
  - Name it directly (for example `make us_debug` for the USA ROM with debug
    functions).
  - Use the `REGION` (region name, `us` by default) and `DEBUG` (`0` or `1`,
    `0` by default) variables.
- For simplicity, you can chain the commands:
  `python3 tools/extractor.py && make -j`

## Verifying that the ROM matches

- `make check` compares the built ROM with the original.
- `./check_roms.sh` builds and verifies the ROMs for every supported region
  (you need a base ROM per region).
- `make check-synthetic` verifies without the original ROM; see
  [Verifying without the ROM](synthetic-check.md).
