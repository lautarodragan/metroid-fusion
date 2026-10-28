# Research: "open base ROM" with original assets

> Status: low-priority research + minimal prototype (`tools/open_assets/`).
> Nothing described here needs, reads or downloads the Nintendo ROM.
> The clean room rules in [CONTRIBUTING.md](../CONTRIBUTING.md) still apply.
> **This is not legal advice.** Section 3 summarizes general principles for
> deciding whether it is worth continuing; before any public distribution it
> is advisable to consult a lawyer.

## 0. Summary

- **Goal:** replace `mf_us_baserom.gba` with a file we generate (our own or
  procedural content, under CC0 or similar) so that `tools/extractor.py`
  consumes it just like the original ROM and `make` produces a ROM that boots
  and can be played with placeholder graphics, sound, text and levels.
- **Technical feasibility:** high for "compiles and produces a ROM", medium for
  "boots without hanging" and low-to-medium for "playable end to end". The
  extractor only copies `size` bytes from `addr` for 3492 regions, so an "open
  base ROM" is simply an 8 MiB file with valid content at those positions. The
  prototype already generates one (with valid LZ77 and RLE, verified by
  decoding) and the extractor consumes it without errors.
- **Main blockers:**
  1. The build is **not shiftable** (the README says so; there are 684 literal
     ROM addresses in `src/`). Each replacement must fit in **exactly** the
     size of the original region. Original art that is more complex than the
     original may not compress within that budget.
  2. **48 `Blob_*` regions (1.11 MiB, 18 %)** are not understood; several hold
     absolute pointers (audio voicegroups, text pointer tables) and the text
     one (496 KiB) contains every language.
  3. Much of the expressive content is **not in the base ROM but in the
     repo**: 661 music sequences (`sound/tracks/*.s`), ~37 300 OAM entries
     (3 984 sprite frames), enemy placement, doors, events, demos.
     A "100 % Nintendo-material-free" ROM requires replacing that too.
  4. **Legal:** an open base ROM solves the *assets* problem, but not the
     *code* one: the decompilation is still a derivative work of Nintendo's
     program (see §3).
- **Recommended next step:** phase A (§4): get agbcc in a controlled
  environment, build with the prototype's open base ROM, run it in mGBA
  (HLE BIOS) and note where it hangs. In parallel, put together the emulation
  harness (§4.4), which is also useful for tests with the real ROM.

## 1. `database.json` inventory

`database.json` is a list of 3492 `{path, dir?, addr.us, count,
size}` entries. The extractor writes `count * size` bytes from `addr` to
`<dir|data>/<path>`. `size` is the element size (1 = bytes, 2 = u16
palettes, 4 = u32 streams, and odd values such as 20-58 that are SA-X frame
sizes); it doesn't affect the content format.

Table generated with `python3 tools/open_assets/inventory.py`:

| Category | Kind | Regions | Bytes | KiB | % |
|---|---|---:|---:|---:|---:|
| `sound_sample`: DirectSound samples (WaveData header + s8 PCM) | asset | 385 | 1 762 059 | 1720.8 | 27.1 % |
| `gfx_lz`: LZ77-compressed 4bpp graphics | asset | 210 | 1 544 128 | 1507.9 | 23.8 % |
| `blob`: regions not understood (`Blob_*`) | logic/mixed | 48 | 1 168 020 | 1140.6 | 18.0 % |
| `gfx_raw`: uncompressed 4bpp graphics (sprites, HUD, projectiles…) | asset | 161 | 727 776 | 710.7 | 11.2 % |
| `gfx_samus`: per-frame Samus/SA-X tiles (counts in C) | asset | 866 | 294 528 | 287.6 | 4.5 % |
| `room_bg_rle`: room BG0/1/2 layouts (room RLE) | layout | 844 | 282 897 | 276.3 | 4.4 % |
| `font`: text glyphs (`text_characters.gfx`) | asset | 1 | 196 608 | 192.0 | 3.0 % |
| `tileset_metatiles`: 16x16 block -> 4 tile entries (`tilesets/*.tm`) | layout | 63 | 192 116 | 187.6 | 3.0 % |
| `tilemap_lz`: LZ77-compressed tilemaps (screens, room BG3/BG0, `.tt.lz`) | asset | 144 | 163 362 | 159.5 | 2.5 % |
| `palette`: BGR555 palettes | asset | 378 | 84 384 | 82.4 | 1.3 % |
| `room_clipdata_rle`: collision/behavior layer (room RLE) | logic | 387 | 61 082 | 59.7 | 0.9 % |
| `misc`: `rooms/background_empty.bin`, `new_file_intro/space_map_bg` | logic | 2 | 8 764 | 8.6 | 0.1 % |
| `tilemap_raw`: `logo.tt`, `common_tilemap.tt`, `door_transition.tm.rle` | asset | 3 | 6 272 | 6.1 | 0.1 % |
| **total extracted** | | **3492** | **6 491 996** | **6339.8** | 100 % |

Aggregated by kind: pure assets 73.6 % (4.56 MiB), level layout 7.3 %,
logic/structure (clipdata + blobs + misc) 19.1 %.

Notes:

- There are no "BIOS" RLE graphics: the `.rle` files use the game's own RLE
  (`RoomRleDecompress`, `src/room.c`). Everything compressed in
  graphics/tilemaps is BIOS LZ77 (`LZ77UncompVram`/`LZ77UncompWram`, 23 calls
  in `src/`).
- There are no extracted "music data" regions: the sequences are already in
  the repo as asm (see §1.2). The PCM samples and the voicegroups (in a blob)
  are extracted.
- Pointer and animation tables barely show up in `database.json`: they are
  already defined in C (see §1.2). The remaining ones are inside blobs.
- Only `Blob_79bec0_79c128.bin` (616 B) has no `INCBIN` consuming it
  (`inventory.py` reports it); it remains to be confirmed whether it is
  included some other way or whether it is a gap.
- The original request mentioned 47 blobs; `database.json` has **48**
  (including two whose address lacks the `0x` prefix, e.g. `Blob_5766D4_5766e0`),
  and their sum (0x11d294) matches the README figure.

### 1.1 The 48 `Blob_*` regions

Grouped by the file that includes them (`inventory.py --blobs` gives the details):

| Group (consumer) | Blobs | Bytes | What it probably is / risk with a placeholder |
|---|---:|---:|---|
| `src/data/text_data.c` (`0x6B2FAC`) | 1 | 507 700 | Strings for every language (u16 per character, control codes in `include/constants/text.h`; `CHAR_TERMINATOR = 0xFF00`). The monologue pointers (`src/new_file_intro.c`) point **into** this blob with literal addresses. |
| `src/data/new_file_intro_data.c` | 12 | 411 888 | Intro cutscene data (probably graphics/tilemaps/OAM not yet split). Medium risk. |
| `src/new_file_intro.c` | 5 | 9 840 | Includes `0x79C5C0` = the `sMessageTextPointers`/`sLocationTextPointers` tables (absolute pointers to strings). With zeros, text would be read from address 0. |
| `src/data/sa_x_close_up.c` | 1 | 79 490 | Data for the SA-X close-up cutscene. |
| `src/data/menus/pause_screen_misc_data.c` | 6 | 44 926 | Pause screen / maps (the 44 302 B one is probably minimap data). |
| `src/data/sram_pointers.c` | 1 | 37 188 | Unknown (default save data?). |
| tilesets (`tilesets_set1/4/7.c`, `common_pals.c`) | 11 | 33 608 | They sit right next to `sTileset_N_Tilemap`; probably more tileset tilemaps or animated data not yet split. |
| sprites (`generic_data.c`, `sprite_data.c`, `sprites/target.c`, `sprites/omega_metroid.c`) | 4 | 22 404 | Sprite tables (possibly with pointers). |
| `src/data/audio.c` (`0xA5710`) | 1 | 13 772 | m4a **voicegroups** (12-byte entries = `struct Voice`, with an absolute pointer to the sample). The tracks reference them with `.word 0x80a5710` etc. |
| `src/data/ending_data.c` | 4 | 6 320 | Ending/credits data. |
| `src/text.c` | 1 | 268 | Unknown (text table). |
| no consumer | 1 | 616 | `Blob_79bec0_79c128`. |
| **total** | **48** | **1 168 020** | |

For the open base ROM, each blob needs one of three strategies:
(a) understand it and move it to C/a known format (which the decomp is after
anyway), (b) a specific "safe" placeholder (the prototype does this for
voicegroups, text and text pointer tables), or (c) zeros, accepting the
risk. On the GBA, reading address 0 doesn't "segfault" (it returns the BIOS
open bus), so the typical failure modes are **infinite loops**
(waiting for a terminator), **jumps to null function pointers** (= BIOS
reset, reboot loop) and **DMA with garbage sizes**.

### 1.2 What is already in C/asm (not extracted)

According to the README, there are 0x6f9d24 bytes of data in total; 6 491 996
are extracted, so about **~803 KiB of data are already defined in the repo**:

| Data | Where | Kind |
|---|---|---|
| Music and SFX sequences (661 files, ~143 600 `.byte` lines) and the 747-sound table | `sound/tracks/*.s`, `sound/sound_entries.s` (generated from the ROM with `tools/trackExtractor.py`) | asset (composition) |
| OAM frames for sprites/Samus/menus: ~37 300 `OAM_ENTRY` in ~3 984 frames | `src/data/sprites/*.c`, `src/data/samus/*`, menus | asset/layout (sprite shape) |
| Animation and pointer tables (frames, timers, per-frame Samus graphics with tile counts) | `frame_data_pointers.c`, `sprite_pointers.c`, `samus_graphics.c`, `samus_animation_pointers.c` | structure |
| Room headers (`RoomEntryRom`: tileset, BG props, music, effects…), 394 rooms | `src/data/rooms_data.c` | logic/layout |
| Width/height of each RLE layer, BGCNT size of each LZ77 BG3 | `src/data/rooms/**/*.c` (bytes before the `INCBIN`) | structure |
| Enemies per room (spritesets), doors/connections, events, demos (recorded inputs) | `rooms/**/*.c`, `connection_data.c`, `event_data.c`, `demo_data.c` | logic/level design |
| Samus physics, AI tables (e.g. Hornoad jump velocities), projectiles, particles, haze, scroll | `samus_data.c`, `sprites/*.c`, `projectile_data.c`, `particle_data.c`, `haze_data.c`, `scroll_data.c` | logic |
| Clipdata and block behavior tables | `clipdata_data.c`, `block_data.c` | logic |
| m4a sound engine and not-yet-decompiled code (~45 000 lines) | `asm/*.s` | code |

Consequence: the open base ROM replaces the ~73 % of "pure assets" among what
is extracted, but **the music, the sprite shapes (OAM) and the high-level
level design (doors, enemies, events) would still be the original ones**
unless they are also replaced in the repo (see §3 and phase C).

## 2. Formats and what a replacement needs

Cross-cutting constraint: as long as the build is not shiftable, **each
replacement must be exactly the same size as the region** (the extractor
copies fixed sizes and the C arrays have explicit sizes; a larger `INCBIN`
doesn't compile, and changing the array size shifts every following address,
breaking the 684 literal pointers). Smaller works: it is padded with zeros and
the space is wasted.

| Category | Format | What a valid replacement needs | Procedural | By hand |
|---|---|---|---|---|
| `gfx_lz` | u32 header `0x10 \| (size << 8)`, blocks with an MSB-first flag byte; reference = 2 bytes (length 3-18, distance 1-4096). | A valid LZ77 stream **≤ region size** that decompresses to a size that doesn't overwrite neighboring memory (VRAM/EWRAM destination; the original size is not known without the ROM and has to be inferred from the consuming code). For VRAM, **no references with distance 1** (the BIOS writes 16 bits at a time). | Easy (the prototype does it). | Medium: 4bpp/16-color art; the compressed budget limits complexity. |
| `gfx_raw`, `gfx_samus`, `font` | 8x8 4bpp tiles (32 bytes, low nibble = left pixel). For Samus/SA-X the per-row tile counts are in C. | Exactly the same size. Tile indices must match what the OAM frames in C use (tile N of the sheet = part of the sprite). | Trivial (placeholder), medium if you want "the silhouette to show" (it can be rasterized from the `OAM_ENTRY`s in C). | High: hundreds of sprites and 866 Samus/SA-X frames. |
| `palette` | u16 BGR555 (bit 15 ignored), rows of 16; index 0 transparent. | Same size; for animated palettes/fades the code interpolates, any value is valid. | Trivial. | Easy. |
| `tilemap_lz` | LZ77 of u16 BG entries (10-bit tile, H/V flip, 4-bit palette). For room BGs the BG size (BGCNT) is in C right before the stream. | Stream ≤ region, decompressing to 0x800/0x1000/0x2000 depending on BGCNT. The smallest regions (252 B) only allow almost uniform maps. | Easy. | Medium (screen design). |
| `tilemap_raw` | `.tt` (tile tables; format to be confirmed), `door_transition.tm.rle` (type 0 room RLE, with a leading size byte). | Same size. | Easy. | Easy. |
| `tileset_metatiles` | Leading u16 + 4 u16 entries per 16x16 block (`room.c` uses `pTilemap + 1`). | Same size; reference existing tiles of the tileset. | Easy. | Medium. |
| `room_bg_rle` | Custom two-pass RLE (low byte, then high byte of each u16); each pass: mode 1 = 8-bit counters, otherwise 16-bit; high bit of the counter = repeat. Width/height in C. | Exactly `width*height` blocks; stream ≤ region. There are 12-byte (empty) layers that only allow "all the same" in 16-bit mode. | Easy. | High (level design), and limited by the budget. |
| `room_clipdata_rle` | Same as above; values = `enum Clipdata` (`CLIPDATA_SOLID = 16`, slopes, doors, elevators…). | Consistent with doors (`connection_data.c`), spawn positions, enemies and BG1. Otherwise Samus falls out of the room or gets stuck. | Medium (boxes/floors); consistency with doors requires reading C. | High. |
| `sound_sample` | MP2K WaveData: `u16 type, u16 status (0x4000 = loop), u32 frequency*1024, u32 loop start, u32 number of samples`, then s8 PCM. (Standard engine layout; confirm against `src/audio.c`.) | Header consistent with the size. | Trivial (square/sine/noise wave) or simple additive/FM synthesis. | Medium: record/synthesize 385 instruments/SFX under a free license. |
| Voicegroups (blob `0xA5710`) | 12-byte `struct Voice`: type, base key, length, pan/sweep, pointer to a sample or CGB wave, ADSR envelope. Keysplits (type 0x40) point to sub-tables. | Valid pointers to samples (fixed addresses, can be computed from `database.json`). | Easy (the prototype points everything to sample 0). | Medium. |
| Music (`sound/tracks/*.s`) | m4a/"Sappy" sequences with the macros from `sound/m_play_def.s`. | New tracks in the same format, same number of entries in `sound_entries.s`. There is no hard fixed size limit if the whole block of tracks in asm is replaced, but the data that follows would shift: it has to be checked whether anything after that area is pointed to with a literal address. | Medium: generate procedural MIDI and convert it (a mid2agb-like converter is missing, or one has to be written). | High: 661 tracks. |
| Text (blob `0x6B2FAC` + pointers) | u16 per character with control codes (`0xFC00` arrow, `0xFD00` new page, `0xFE00` line break, `0xFF00` end). `charmap.txt` is still empty. | Strings at the exact addresses the tables point to (or rewrite the tables, which are in a blob). | Easy for "everything empty"; medium for readable placeholder text (requires mapping the charset). | Medium (writing + 6-7 languages). |
| Remaining blobs | Unknown. | Understand them or fill them with something safe. | — | — |

## 3. Legal analysis (general framing, not advice)

### 3.1 Assets vs. code

- Copyright protects **expression**, not ideas, methods or mechanics
  (US: 17 U.S.C. §102(b); EU: Directive 2009/24/EC art. 1.2 for software;
  in Argentina, Law 11.723 follows the same general logic). Graphics, music
  (composition and recordings/samples), text and probably the level design
  (selection and arrangement) are protected works. Purely functional tables
  (physics, velocities, sine tables) have weak or no protection for lack of
  originality, but **taken together** they can form part of the program's
  expression; it is not wise to assume that "the data is free".
- A base ROM made of assets **created by us** (or generated by our own code)
  is our work and we can license it freely. This removes the dependency on
  the commercial ROM **for the assets**.
- **The code is another story.** A *matching* decompilation reproduces, by
  design, the behavior and form of Nintendo's compiled program; even if it is
  written "fresh" (as CONTRIBUTING.md requires, forbidding looking at leaked
  code), it is obtained by studying the binary, and the result is plausibly a
  **derivative work** of the program. The classic clean room methodology
  (Phoenix BIOS) separates whoever analyzes from whoever implements and only
  passes along specifications; that doesn't happen here.
- Relevant exceptions and their limits:
  - US: *Sega v. Accolade* (9th Cir. 1992) and *Sony v. Connectix* (9th Cir.
    2000) held **intermediate** copying during reverse engineering to achieve
    interoperability to be *fair use*, with a non-infringing final product.
    Distributing a nearly identical reimplementation of the same game is not
    the case analyzed in those rulings.
  - EU: art. 6 of Directive 2009/24/EC allows decompiling for the
    interoperability of an *independently created* program, and forbids
    using the information for a "substantially similar" program.
  - DMCA §1201 (US) and equivalents: the GBA has no encryption; the header
    logo is a separate topic (below).
- Besides the C code, the repo already contains **expressive data derived
  from the ROM** outside the base ROM (music in `sound/tracks`, OAM frames,
  room design in C). Today it has the same status as the code; an "open"
  variant should be buildable without it (phase C).
- **Practical conclusion:** the open base ROM (a) removes the need to obtain
  a ROM to build/test, (b) makes it possible to distribute **the assets**
  under a free license and (c) enables CI with screenshots without Nintendo
  material in the *data* artifacts. It does **not** make the resulting binary
  free: distributing the built ROM (which contains the derived code) is still
  risky. Recommendation: don't publish built ROMs; publish only the asset
  generator and, as today, the source code.
- The tolerance precedents (Nintendo has not gone after pret-style
  decompilation repos, although it did act against distributions of
  ports/binaries and ROM hacks with their own content) are **de facto, not de
  jure**.

### 3.2 Trademarks

- "Metroid", "Metroid Fusion", "Samus", the title logo and the name
  "Nintendo" are trademarks. Trademark risk arises when **presenting** the
  product (title, logo, file name, description), not from the code itself.
- In the ROM header, the Makefile sets `GAME_TITLE = METROID4USA` and
  `GAME_CODE = AMTE`. For an "open" variant it is better to use our own title
  and code (e.g. an `OPEN_ASSETS=1` variable that changes
  `GAME_TITLE`/`GAME_CODE`) and to make sure the placeholder art/text doesn't
  use the names or the logo.
- `tools/gbafix` (GPLv3, from devkitPro) copies the **Nintendo logo** that the
  real BIOS requires in order to boot. *Sega v. Accolade* held that using a
  lock-out mechanism based on a trademark doesn't give the owner a right to
  exclude (in the US); all GBA homebrew does the same. For emulator CI with an
  HLE BIOS (mGBA) the logo is not checked, so an "open" build could leave it
  empty and remove the issue entirely from test artifacts (to be verified
  empirically that mGBA boots without the logo).
- Never use the Nintendo BIOS: mGBA ships an HLE BIOS, which also implements
  `LZ77UnComp*`.

### 3.3 "Engine + free assets" precedents

| Project | Engine | Free assets | Lesson |
|---|---|---|---|
| **Freedoom** | Doom (code released by id under the GPL) | Full IWAD under BSD-3 | The ideal case: free code + free assets = a 100 % distributable game. The IWAD is *drop-in*, just like our base ROM. |
| **OpenTTD + OpenGFX/OpenSFX/OpenMSX** | Reimplementation that grew out of reverse engineering/decompiling TTD | GPLv2 graphics, sounds and music | Very similar to this case: the free sets make it possible to play without the original game, but the code always had the decompilation as its background (tolerated de facto). The free sets were made following the original's sprite layout so they would be *drop-in*. |
| **OpenRCT2** | Reimplementation from the RCT2 binary | Still requires (largely) the original assets; partial replacement projects exist | Shows how much it takes to cover 100 % of a commercial game's assets. |
| **LibreQuake, OpenArena, FreeDM** | Quake/Quake III/Doom (GPL) | Free assets | Same pattern as Freedoom. |
| **GBA homebrew** (devkitPro/libtonc/butano) | Own code | Own assets | Free tools (gbafix, grit, mid2agb-like) and using the logo in the header are standard practice. |
| N64 decomp ports (sm64, OoT/Ship of Harkinian) | Decompilation | They do **not** distribute assets: they extract them from the user's ROM | This is the current model of this repo. The open base ROM would add a "no ROM" option. |

### 3.4 Suggested licenses

- **CC0-1.0** for everything procedurally generated and for the data
  generator (or MIT, like the repo). Maximum compatibility; the prototype
  declares CC0 for its output.
- For hand-made art/music contributions: **CC0** (preferred, no friction) or
  **CC-BY 4.0** / **CC-BY-SA 4.0** if the authors want attribution/copyleft.
  CC-BY-SA 4.0 is one-way compatible with GPLv3; mixing with MIT is fine as
  long as the assets stay as separate files with their own license.
- Avoid CC-NC/ND (they are not free and complicate redistribution in CI).
- Fonts: draw our own or use a CC0/OFL pixel font; with OFL, its reserved
  font name conditions must be respected.
- Record provenance: each asset with author, license and "not derived from
  Nintendo material" (an `ASSETS_LICENSE.md`/manifest), and explicitly forbid
  tracing over screenshots of the original game.

## 4. Phased plan

### 4.0 Included prototype (`tools/open_assets/`)

- `inventory.py`: categories and sizes from `database.json` + which file in
  `src/`/`sound/` consumes each region (generates the tables in §1).
- `formats.py`: BIOS-compatible, VRAM-safe LZ77 encoder/decoder (no
  distance-1 references), room RLE encoder/decoder (picks 8 or 16 bits per
  pass), placeholder palettes/tiles/waves.
- `make_open_baserom.py -o open_baserom.gba`: generates the 8 MiB file. It
  reads from C the BGCNT size of each LZ77 BG and the width/height of each RLE
  layer; it generates "box" rooms (or floor/ceiling if a box doesn't fit),
  voicegroups pointing to a valid sample, text full of terminators and text
  pointer tables pointing to a terminator; it validates everything by decoding
  it. It never overwrites an existing file without `--force`.
- `test_formats.py`: round-trip tests (`python3 tools/open_assets/test_formats.py`).

Current result: all 3492 regions get content; 209 of the 210
`gfx_lz` fit with 2 KiB decompressed (only one with 256 B), the 144
`tilemap_lz` fit with the expected BGCNT size; 122 clipdata layers only
allow "floor and ceiling" (not a full box) because of the budget;
`tools/extractor.py` consumes the file unchanged and produces the 3492 files
(6 491 996 bytes).
**The ROM was not built or run** (there is no agbcc in this environment and
no external code was installed).

### 4.1 Phase A: "boots into something" (estimate: 3-10 days)

> **Update:** done without touching `src/`/`asm/`. The open ROM reaches the
> game (first room, Samus moves with input), going through the intro, title,
> file select and new file intro. What it took and the emulator tests that
> verify it are in [emu_tests.md](emu_tests.md).

1. Build with the open base ROM (`cp open_baserom.gba mf_us_baserom.gba;
   python3 tools/extractor.py && make`). Expected: it builds just as with the
   real ROM (the sizes are identical); `make check` obviously fails.
2. Run it in mGBA with the HLE BIOS and trace: does it reach the title? Does
   the intro finish? Likely hang points: intro/cutscene blobs
   (`new_file_intro_data.c`, 412 KiB), text, pause/minimap, sram.
3. For each hang: understand the blob (moves the decomp forward) or give it a
   safe placeholder. Acceptable shortcut: a build flag (`OPEN_ASSETS`) that
   skips the intro/cutscenes and goes straight to a room (our own code in the
   fork; it doesn't change the matching build).
4. Our own header (title/code) under that flag.
5. Exit criterion: reaches gameplay in the starting room without hanging for
   10 000 frames with random input.

### 4.2 Phase B: one playable test room (estimate: 1-3 weeks)

1. Pick a small room (the `test*` rooms in `rooms/test` or the first one in
   the Main Deck) and generate: a tileset with 4-8 readable blocks (floor,
   wall, background, door), clipdata consistent with the doors in
   `connection_data.c` and the entry position, a visible BG1 matching the
   clipdata.
2. Placeholder Samus: rasterize her 866 frames **from the `OAM_ENTRY`s in
   C** (one colored rectangle per piece, with a border), so that each
   animation shows a silhouette that moves correctly without copying art.
   The same works for every sprite (phase C).
3. Readable (high-contrast) palettes and a minimal custom font (digits + A-Z)
   for the HUD.
4. A couple of synthesized samples and a custom test track in
   `sound/tracks` (optional in this phase).
5. Exit criterion: an automated test that enters the room, walks, jumps,
   shoots and goes through a door, with stable screenshots.

### 4.3 Phase C: full coverage with placeholders (estimate: 4-8 weeks of procedural placeholders; months for "nice" art)

- All tilesets (63) and their metatiles, room BG3s, menu screens, our own
  title (without the trademark), endings.
- Clipdata for the 394 rooms: generate it automatically from the geometry of
  the doors and elevators defined in C (connected boxes), guaranteeing that it
  can be traversed, or design new levels (requires a shiftable build to go
  beyond the byte budget).
- Placeholder text for every message (requires mapping the charset and the
  structure of the text blob).
- Sound: 385 synthesized samples and **replacing the 661 sequences** (for
  example, a melody generator + a converter to m4a macros).
- Optional for a fully free build: replace the OAM frames/room design in C
  with generated versions, and make the build shiftable with assets in source
  formats (PNG/MIDI/JSON) converted at build time, as the pret projects do
  (`gbagfx`, `mid2agb`). This removes the exact-size constraint, which is the
  biggest obstacle for original art.

### 4.4 Emulator test harness controllable from Python

Requirements: headless, advance frames, inject input, read memory (IWRAM/EWRAM
for variables such as `gCurrentArea` = `0x0300002C`, `gCurrentRoom` =
`0x0300002D`, taken from `linker.ld`/`.map`), screenshots, HLE BIOS.

| Option | Installation | Frames / input / memory / screenshot | Comment |
|---|---|---|---|
| **Official mGBA Python bindings** (`mgba.core`, `mgba.image`) | Not on PyPI: build mGBA with `-DBUILD_PYTHON=ON` (uses cffi); Ubuntu has `libmgba-dev` 0.10.2 but not the Python module | Yes / yes (`set_keys`) / yes (`core.memory`) / yes (`Image.to_pil()`) | The most direct and faithful option. Cost: a build in CI (cacheable). |
| **pygba** (PyPI 0.2.9, MIT) | `pip install pygba`, but it depends on the `mgba` module above | Convenient wrapper + gymnasium environment | Useful as an API reference. |
| **libretro.py** (PyPI 0.12.0, Python ≥ 3.12) + `mgba_libretro.so` core | `pip install libretro.py`; the core comes from `apt install libretro-mgba` (0.10.2 on Ubuntu noble) or from the stable-retro wheel | Designed precisely for testing cores: frames, input, memory via the libretro API, framebuffer | Nothing to build; a good option for CI. |
| **stable-retro** (PyPI 1.0.1, Farama) | `pip install stable-retro` (~120 MB wheel with `mgba_libretro.so` included) | `env.step`, RAM, observation = screen | Requires registering the ROM as a custom "integration" (hash + `data.json`); designed for RL, more rigid. |
| mGBA CLI + Lua scripting (0.10+) | `apt install mgba-sdl`/`mgba-qt` | Lua can read memory, take screenshots and control input | Good for debugging; for headless CI one of the options above is better. mGBA also has its own screenshot regression test system ("CInema"). |

Recommendation: **libretro.py + `libretro-mgba`** for CI without building the
emulator; the official mGBA bindings if something is needed that libretro
doesn't expose. Test outline:

```python
# pseudo-code
core = load("mgba_libretro.so"); core.load_game("mf_open.gba")
for frame, keys in script:            # script = list of (frame, buttons)
    core.set_input(keys); core.run()
assert read_u8(0x0300002C) == AREA_MAIN_DECK
save_png(core.framebuffer(), f"out/{frame}.png")   # compare with golden PNG (tolerance)
```

The "goldens" are generated with the open ROM, so they can be versioned in the
repo without Nintendo material. The same harness runs locally with the real
ROM for behavior tests (without committing its screenshots).

## 5. Effort and risks

| Work | Estimate |
|---|---|
| Generator prototype (done) | ~1 day |
| Phase A (boot) | 3-10 days, dominated by how many blobs need to be understood |
| Python harness + CI | 2-4 days |
| Phase B (playable room + OAM-based Samus) | 1-3 weeks |
| Phase C full procedural placeholders | 4-8 weeks |
| Phase C with quality original art/music | months, depends on contributors |
| Shiftable build + assets in source formats | weeks to months (it is also a goal of the decomp) |

Risks:

1. **Fixed byte budget** per region as long as there is no shiftable build:
   limits original art/levels; the simple placeholder does fit.
2. **Unknown blobs** with pointers or structures the code assumes
   (infinite loops/null jumps). Mitigation: advance the decomp of those
   areas; specific placeholders; a flag to skip cutscenes.
3. **Unknown decompression sizes** for `gfx_lz` (they can't be read
   without the ROM): pick conservative sizes and validate against the
   consuming code (VRAM/EWRAM destinations) so as not to overwrite memory.
4. **Level consistency**: clipdata/doors/enemies/events have to agree; with
   inconsistent data the game doesn't "crash" but becomes unplayable.
5. **Legal**: the open base ROM doesn't change the status of the code or of
   the derived content already in the repo (music, OAM, room layout). Don't
   distribute built ROMs; keep names/logo out of the assets.
6. **Contamination**: "inspired" art contributions that actually trace or
   reproduce the original's sprites. Mitigation: a provenance manifest and
   review; prefer procedural generation.
7. **Maintenance**: every time the decomp splits a blob into new regions, the
   generator has to learn the format (the inventory detects it: a new
   category or a region without a generator).
