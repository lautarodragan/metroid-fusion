# Introduction

This is a work-in-progress decompilation of **Metroid Fusion** (Game Boy
Advance): C and assembly code that, when compiled, produces a ROM that is
byte-for-byte identical to the original.

## Progress

The up-to-date status is in the repository's
[README](https://github.com/lautarodragan/metroid-fusion/blob/main/README.md).
At the time of writing:

- 3601/3607 functions decompiled (99.83%, 6 left).
- 0x5dca90/0x6f9d24 bytes of data outside blobs (84.03%, 0x11d294 left).

`python3 tools/progress.py` computes both numbers from the current tree.

There is a spreadsheet with detailed progress:
<https://docs.google.com/spreadsheets/d/1HvJ-jynb-4P9tfEBVJmkQFpIg6mJRDRUBvDIBiLxQIo/>

> **Warning:** the decompilation is **not shiftable** yet (see
> [Shiftability](shiftability.md)). Don't use it as a base for other
> work.

## ROMs and regions

The repository can build several ROMs, named `mf_{region}.gba` (or
`mf_{region}_debug.gba`). The region indicates which version the ROM
targets:

| Region    | Version              | Status                                                       |
|-----------|----------------------|--------------------------------------------------------------|
| `us`      | USA, North America   | Supported (`sha1: ca33f4348c2c05dd330d37b97e2c5a69531dfe87`) |
| `eu`      | Europe               | Not supported yet                                            |
| `jp`      | Japan                | Not supported yet                                            |
| `cn`      | China                | Not supported yet                                            |
| `eu_beta` | European beta        | Not supported yet                                            |

The `_debug` suffix indicates whether the ROM includes the debug functions; it
is optional and **not supported yet**. The ROM built by default is
`mf_us.gba`.

## Community

- [Metroidret](https://discord.gg/2MGB9Xbr9y) (Discord)
- [MAGConst](https://discord.gg/WtekHKb) (Discord)
