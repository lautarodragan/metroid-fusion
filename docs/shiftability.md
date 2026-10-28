# Shiftability

A build is *shiftable* when code and data can grow, shrink or move and the
ROM still works, because every pointer is resolved by the linker instead of
being written as a number.

## Current state

- No source file (C, headers, asm, sound, linker script, Makefile) contains a
  hardcoded ROM address. Every former `.4byte 0x08xxxxxx`, `ldr rX, =0x8...`,
  `(Func_T)0x8...` or `.word 0x80...` now names the function or data it
  points to. Addresses that were inside a blob got a symbol by splitting the
  blob (see [Splitting a blob](#splitting-a-blob)).
- The linker script places everything in the ROM one after the other; no
  object is pinned to an address.
- `make check-shift` proves that every pointer the build emits (literal
  pools, jump tables, C data) follows what it points to.
- **Not yet covered: pointers stored inside extracted data.** The bytes
  listed in `database.json` are copied from the baserom unchanged. A blob
  that holds a pointer table keeps the old addresses when something before
  its targets moves. The synthetic baserom cannot show where these are, so
  they have to be found with the real ROM using
  [`tools/find_blob_pointers.py`](#finding-pointers-inside-blobs).

  From the code that uses them, these blobs are known to be pointer tables
  (or to contain pointers), so they will certainly need converting:
  - `sInterruptHandlers` (`src/data/generic_data.c`): interrupt handler
    function pointers
  - `sVoicegroup_*` (`src/data/audio.c`): instrument definitions, which
    point to the direct sound samples, wave data and sub-voicegroups
  - `sMessageTextPointers*`, `sLocationTextPointers*`,
    `sNavConversationTextPointers*`, `sPauseScreenTextPointers*`
    (`src/new_file_intro.c`): per-language tables of pointers into the text
    blobs

Until the internal blob pointers are converted, changes that move data
located after any of their targets will break the ROM at run time, even
though it links and the checks below pass.

## Checks

### Lint: `tools/check_hardcoded_pointers.py`

Fails if a source file contains a number in `0x08000000`-`0x09FFFFFF` (hex
with or without the leading zero, or decimal), outside comments. The few
constants that are not pointers to code or data are allowlisted in the
script with the reason:

| File | Value | Why it stays |
| --- | --- | --- |
| `include/gba/memory.h` | `0x08000000` | `ROM_BASE`, start of the cartridge address space |
| `linker.ld` | `0x08000000` | `ORIGIN` of the `rom` memory region |
| `Makefile` | `0x08800000` | `PAD_TO`, the 8 MiB size the ROM is padded to |

### Shift test: `make check-shift` / `tools/check_shift.sh`

1. runs the lint,
2. builds `mf_us.gba` as usual,
3. builds `mf_us_shifted.gba` with `make SHIFT=1`: the same objects, linked
   with `SHIFT_AMOUNT` (default `0x100`) bytes of padding after the
   interrupt handler, again before `src/sprites_AI/gunship_end.o` (mid code) and
   again at the start of `.rodata`, so almost every symbol moves, by three
   different amounts,
4. runs `tools/check_shift.py`, which compares both builds using their ELF
   symbols. For every word that, in the normal build, points to a symbol
   (its address, a Thumb function address + 1, or for literal pools an
   address inside a sized object), the word at the same place in the shifted
   build must point to the same symbol at its new address.

Only bytes the build decides are checked: the data parts of the code
sections (`$d` mapping symbols: literal pools, jump tables) and
`.rodata`/`.data` without the ranges extracted from the baserom. In data,
only words aligned within an aligned object and pointing exactly to the
start of an object or function count, so byte tables that happen to look
like addresses are not reported. The extracted ranges are skipped because
their content comes from the baserom (random with the synthetic one); that
is what `find_blob_pointers.py` is for.

The check works with the synthetic or the real baserom. It needs the data
to be extracted, so run it after `tools/check_synthetic.sh` or
`tools/extractor.py`. CI runs it after the synthetic golden check.

A failure looks like

```
0x0809222c (_0809222C): 0x0863a19c -> sCutsceneTextNone; shifted build has 0x0863a19c, expected 0x0863a39c
```

meaning the literal at `0x0809222c` is a number, not a reference to
`sCutsceneTextNone`.

## Finding pointers inside blobs

`tools/find_blob_pointers.py` needs the real baserom (it warns when it gets
the synthetic one, whose results are noise):

```sh
python3 tools/find_blob_pointers.py                    # reads mf_us_baserom.gba
python3 tools/find_blob_pointers.py --likely           # only the probable pointers
python3 tools/find_blob_pointers.py --json ptrs.json   # machine readable
```

It scans every `Blob_*` entry and the other extracted files without a known
format (`--all` scans every entry) for 4-byte aligned words in the ROM
range, and prints them per entry with the symbol they are in and the symbol
or `database.json` entry they point to (symbol names come from `mf_us.elf`
if it is built; its addresses are the same as the baserom's). Words that
point exactly to the start of an object, a `database.json` entry or a
function (+1) are marked `*`; consecutive marked words are almost certainly
a pointer table. Unmarked words are usually graphics or other data that
looks like an address by chance.

To convert a pointer table, replace its bytes with C (an array of the
symbols it points to) or asm (`.4byte symbol`), splitting the blob around it
first if needed, and give targets inside other blobs a symbol by splitting
those. Then `make check-shift` covers the new pointers too.

## Splitting a blob

`tools/split_blob.py` splits a `database.json` blob and the `INCBIN_U8`
array that includes it into consecutive pieces, so the bytes stay where they
are:

```sh
python3 tools/split_blob.py Blob_6b2fac_71e20c.bin 0x6c0000=sFoo 0x6c1000=sBar
python3 tools/split_blob.py Blob_6b2fac_71e20c.bin @splits.txt   # "ADDR NAME" per line
```

Each named piece is a non-static `u8` array (u8 arrays have no alignment, so
no padding is added) stored as `Blob_<start>_<end>.bin`, so it still counts
as a blob in `tools/extractor.py -b`. Declare the piece where C code uses it
and replace the literal with its name. Pieces referenced from asm only need
no declaration.

Names given so far follow the code that uses the address: a descriptive name
where it is clear (`sSpriteset<N>`, `sVoicegroup_<offset>`,
`sMonologueText<Language>_<N>`, `sGunshipEndGfx`, ...), otherwise
`s<Area>Unk_<offset>` (area of the asm function using it, e.g.
`sIntroUnk_6131c8`) or `sUnk_<offset>`. Literals that addressed single bytes
of one object are written as `symbol+offset` instead.

## Fixed addresses that remain, and why

- `rom : ORIGIN = 0x08000000`, the ROM header at its start and `crt0`
  right after it: required by the hardware.
- `asm/crt0.s` finds `InterruptCode` with `add r0, pc, #0x20`, so
  `asm/intr_main.o` must stay right after `asm/crt0.o` (they are the first
  objects in `linker.ld`, before any shift padding).
- `PAD_TO = 0x08800000`: the ROM is padded with `0xff` to 8 MiB. A bigger
  ROM is not truncated (objcopy only pads), but anything past 8 MiB needs a
  larger cartridge size.
- The `ewram`/`iwram` sections in `linker.ld` give every RAM variable a fixed
  address. They are RAM, so they do not move when ROM contents change, but
  adding variables means editing that layout by hand.
- `memset`, which used to be an orphan section placed after `rom` by the
  linker, is now listed at the end of the `rom` section (same address).
