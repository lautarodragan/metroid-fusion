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
- Pointers stored inside data extracted from the baserom are symbols too.
  The tables that were extracted as raw bytes are now C or asm that names
  what they point to, and the data they point into is split so that every
  target has a symbol:
  - `sInterruptHandlers`, `sNavConversationPopUpFunctions`: arrays of
    functions.
  - the per-language message, location, navigation conversation, pause
    screen and file select text tables: arrays of strings. The text blob is
    split into one region per string (`text/<language>/<table>_<index>.bin`).
  - the `struct FrameData` arrays of the intro, cutscenes, ending, menus and
    gunship, and the OAM pointer tables that use them: C, pointing to OAM
    frames split out of the blobs and LZ77 files that held them
    (`oam_frames/<offset>.bin`, `sOamFrame_<offset>`).
  - graphics, palette and tilemap pointer tables (erase SRAM, game over,
    ship alert, elevator monologues), `sNavConversationPopUps`, the ending
    image text OAM: C, their targets split out the same way.
  - the voicegroups (`sound/voicegroups.s`): each voice is included from
    `data/voicegroups/<offset>.bin` with `.incbin`, except its sample, wave,
    drum kit or keysplit pointers, written as symbols (macros in
    `asm/voicegroup.inc`).

  Run side by side with the original ROM and compared every frame (screen
  and RAM, ROM pointers in RAM translated between the layouts), the shifted
  build (`make SHIFT=1`) of the real data behaves like the original through
  boot, title, file select, the intro, the menus, a save, a navigation
  conversation, an elevator ride and all 393 rooms.

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
is what `find_blob_pointers.py` is for. The exception are the words of
extracted ranges that differ between the two builds: data included piece by
piece around pointers written as symbols (the voicegroups). Each of them
must point to a symbol (or inside a sized object) and follow it.

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

`tools/find_blob_pointers.py` looks for pointers that are still raw bytes in
extracted data. It needs the real baserom (it warns when it gets the
synthetic one, whose results are noise):

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
looks like an address by chance. When `mf_us.gba` and `mf_us_shifted.gba`
are both built, words that differ between them are pointers the source
already writes as symbols (inside data included piece by piece, like the
voicegroups) and are left out.

With the conversions above, `--likely` reports nothing. The last word it
used to report, `0x0800eb05` at `0x608460` (the address of `unk_eb04` + 1),
was inside the LZ77 stream of `sTitleScreenSpaceBackgroundGfx`, which the
decompressor reads as compressed data: a coincidence. Without `--likely`,
the remaining in-range words are in graphics, palettes, tilemaps, samples
and text (values that look like addresses by chance).

To convert a pointer table, replace its bytes with C (an array of the
symbols it points to) or asm (`.4byte symbol`), splitting the blob around it
first if needed, and give targets inside other blobs a symbol by splitting
those. Then `make check-shift` covers the new pointers too.

## Splitting a blob

`tools/split_blob.py` splits a `database.json` entry and the `INCBIN` array
that includes it into consecutive pieces, so the bytes stay where they are:

```sh
python3 tools/split_blob.py Blob_6b2fac_71e20c.bin 0x6c0000=sFoo 0x6c1000=sBar
python3 tools/split_blob.py Blob_6b2fac_71e20c.bin @splits.txt   # "ADDR NAME [TYPE [PATH]]" per line
python3 tools/split_blob.py menus/game_over/obj.gfx.lz 0x739d58=sGameOverTextGfxJapanese:u8:menus/game_over/text_japanese.gfx.lz
```

Each named piece is a non-static array. Its element type is the type of the
original array when its address and size allow it, else the largest of
u16/u8 that fits (or the TYPE given), so splitting never adds padding. A
piece of a `Blob_*` entry is stored as `Blob_<start>_<end>.bin` by default,
so it still counts as a blob in `tools/extractor.py -b`; give it a PATH
once its content is identified (`text/english/message_3.bin`,
`oam_frames/<offset>.bin`, `....gfx.lz`). In a blob, the name `-` starts an
unnamed piece (the rest of the blob after a named one). The bytes before the
first split point keep the original declaration (a `Blob_*` entry gets the
static `sBlob_<start>_<end>` name of its new range). Declare the piece where
C code uses it and replace the literal with its name. Pieces referenced from
asm only need no declaration.

No `Blob_*` entry is left. The last ones turned out to be the ends of
LZ77 streams cut short at extraction (an `.lz` entry must end where its
stream ends, rounded up to 4; decompress it to find that point), unused
palette rows, OAM frames and movement tables next to used ones, a CGB
wave, and padding. Zero padding between objects is not extracted: the
compiler aligns u16/u32 arrays by itself, and `ALIGN_2()` (4-byte
alignment, zero fill) goes before a u8 array that starts 4-aligned in the
original.

Names given so far follow the code that uses the address: a descriptive name
where it is clear (`sSpriteset<N>`, `sVoicegroup_<offset>`,
`sMonologueText<Language>_<N>`, `sMessageText<Language>_<N>`,
`sOamFrame_<offset>`, `sGunshipEndGfx`, ...), otherwise
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
