# Emulator tests (without the original ROM)

The tests in `tests/emu/` run the ROM built from the **open base ROM**
(`tools/open_assets/`, a generated placeholder baserom used as a test
fixture, see [Generated test baserom](test-baserom-research.md)) in a
windowless GBA emulator driven from Python. They don't need, read or download
the original ROM or the official BIOS, so they run in CI.

## Requirements

- The same as for building (agbcc, `binutils-arm-none-eabi`, `python3`).
- The mGBA libretro core: `sudo apt install libretro-mgba` (Ubuntu 24.04
  ships 0.10.2). It is looked up in `/usr/lib/<arch>/libretro/mgba_libretro.so`;
  set a different path with `MGBA_LIBRETRO_CORE=/path/mgba_libretro.so`.
- `pytest` (`sudo apt install python3-pytest` or `pip install pytest`).

Without the core or without the ROM, every test is marked as *skipped* with a
message saying what is missing.

## How to run them

```sh
tests/run_emu_tests.sh                       # clean build in a temp dir + pytest
tests/run_emu_tests.sh -k ingame -v          # extra arguments go to pytest
tests/run_emu_tests.sh --no-shift            # without the second run (shifted ROM)
EMU_BUILD_DIR=/tmp/mf-open tests/run_emu_tests.sh   # reuse the build (incremental)
```

`run_emu_tests.sh` copies the repo's files (tracked and not ignored) to
another directory, generates the open base ROM there and builds with
`tools/open_assets/build_open_rom.py`. **It never touches the working tree**:
any real or synthetic `mf_us_baserom.gba` you have is left intact.

It then repeats everything with the *shift* test ROM (`make SHIFT=1`,
`mf_us_shifted.gba`, see [Shiftability](shiftability.md)): the same code and data
with padding inserted, so almost every address changes. The same tests
(screenshots included) have to pass; this is the run-time proof that the
build is *shiftable*, which `check_shift.py` only verifies statically. It
takes ~70 s in total (two builds of ~25 s and two runs of ~8 s).

If you already built the open ROM by hand,
`python3 -m pytest tests/emu [--emu-rom path/mf_us.gba]` is enough. The tests
are skipped if the `mf_us_baserom.gba` next to the ROM is not an open base ROM
(it has a marker at the start), because the references are only valid for
that ROM.

`build_open_rom.py [--shift]` builds in two passes: some of the base ROM's
data are build addresses (interrupt vector, pointer tables) and are filled in
from the ELF of the previous pass. Since the Makefile doesn't know that an
object depends on the files it includes with `INCBIN`, the script deletes the
objects whose data changed.

## What they verify

| File | Test |
| --- | --- |
| `test_boot.py` | The first 600 frames run (PC always in code, increasing frame counter). The scripted walkthrough goes through the modes in order: title intro → title screen → file select → new file intro → map → in game. No invalid PC and no resets during the whole walkthrough. |
| `test_screenshots.py` | Screenshots at 8 points (`title_intro`, `title_screen`, `file_select`, `new_file_intro`, `in_game`, and `room_0`, `room_3`, `room_6` from the room walk) compared against `tests/emu/reference/*.png`. A pixel differs if any channel differs by more than 24; the test fails if more than 0.5 % of the pixels differ. On failure, `<name>.actual.png` and `<name>.diff.png` are saved to `tests/emu/output/` (or `--emu-output` / `$MF_EMU_OUTPUT`; in CI they are uploaded as an artifact). |
| `test_rooms.py` | The scripted walk after reaching the game (`ROOM_WALK` in `scenario.py`) goes through the first three rooms of the generated baserom: room 0 → left hatch → room 3 → upper left door → room 6. `gCurrentArea`/`gCurrentRoom` at each checkpoint must be (0, 0), (0, 3), (0, 6), and Samus must stand on the expected floor on arrival. See [the rooms](open-assets-rooms.md). |
| `test_ingame.py` | In the first room (`gCurrentArea` = 0, `gCurrentRoom` = 0): holding right increases `gSamusData.xPosition` and left decreases it; A makes Samus jump (`yPosition` goes down) and Samus lands back on the floor. Determinism: same state + same input → same RAM/VRAM/OAM hash and same image; two power-ons give the same RAM. |
| `test_sprites.py` | Placeholder sprites are really drawn: Samus' sprites are on screen and visible (not hidden behind the background); for 9 scripted poses (standing, running, jumping, spin jump, aiming up, aiming diagonally, crouching, shooting, facing left) Samus is rendered from OAM + OBJ VRAM + OBJ palettes (`oam_view.py`, without the room behind) and compared with `tests/emu/reference/samus_<pose>.png`, and the poses must all look different; shooting puts a beam sprite on screen; the energy counter is visible. See [Placeholder sprites](open-assets-sprites.md). |

The walkthrough (`tests/emu/scenario.py`) runs only once per session: the
tests read what was recorded (mode transitions, screenshots, *save states*)
and the in-game ones start from the state saved on reaching the room.

### Updating the references

When a change alters the image on purpose (for example, different placeholder
content in `make_open_baserom.py`):

```sh
tests/run_emu_tests.sh --update-references
```

Look at the new PNGs and commit them along with the change. The references
only show generated placeholder content.

## Determinism

- Core options fixed in the harness (HLE BIOS, no *frameskip*, no color
  correction or frame blending, no *idle loop* optimization), independent of
  any local configuration.
- Empty, temporary system/save directory: a user BIOS or `.sav` is never
  loaded. SRAM starts empty on every power-on.
- Metroid Fusion has no RTC and doesn't read anything clock-dependent; the
  game's random number comes from frame counters, which are deterministic.
- Input is given per frame; the script uses fixed frame counts.

The two determinism tests check this within the same process, and comparing
screenshots against references generated in another run checks it across
processes.

## The harness (`tests/emu/harness.py`)

A minimal libretro frontend using `ctypes` (no pip dependencies):

```python
from harness import Emulator
emu = Emulator("mf_us.gba", "mf_us.map")      # only one Emulator per process
emu.run(60)                                   # 60 frames
emu.run(30, "RIGHT+B"); emu.press("START")    # per-frame input
emu.s16("gMainGameMode"); emu.u16("gSamusData+0x16")   # symbols from the .map
emu.read(0x06000000, 32)                      # any mapped region
emu.save_png("shot.png")                      # screenshot (PNG without Pillow)
st = emu.save_state(); emu.load_state(st)
emu.cpu_registers()["pc"]; emu.symbolize(pc)  # PC from the mGBA save state
```

Memory is read through the memory map the core publishes
(`RETRO_ENVIRONMENT_SET_MEMORY_MAPS`): EWRAM, IWRAM, I/O, palettes, VRAM, OAM
and ROM. Symbols are resolved only from the `.map`. The CPU registers are not
part of the libretro API; `cpu_registers()` extracts them from mGBA's *save
state* format and is meant for debugging.

### Debugging a hang

1. With the harness, locate the frame (modes, `cpu_registers()`, `symbolize`).
2. Save a state right before it (`open("x.ss","wb").write(emu.save_state()[:-8])`;
   the last 8 bytes are the harness's frame counter).
3. Open it in mGBA's command-line debugger (`apt install
   mgba-sdl`):
   `SDL_VIDEODRIVER=dummy /usr/games/mgba -d -t x.ss mf_us.gba`, with
   `b <addr>`, `watch/w <addr>`, `trace <n>`, `c`.

## What it took for the open ROM to boot

Nothing in `src/` or `asm/`: only placeholder data, in `apply_known_layouts` in
`tools/open_assets/make_open_baserom.py`.

1. **Interrupt vector** (`sInterruptHandlers`): 13 pointers to
   `Dma2IntrCode`, `CallbackCallVblank`, `CallbackCallHBlank`,
   `CallbackCallVCount` and `Callback_Empty`. When zeroed, the first DMA2 IRQ
   jumped to 0 and the console reset in a loop during boot.
2. **OAM data for cutscenes, the ending and file select**: when zeroed, the
   animation pointers (`struct FrameData`) led to reading a huge part count
   and writing past the OAM buffer, overwriting `gVBlankCallback`. They are
   filled with a repeated word that is the (build) address of a 64 KiB-aligned
   copy of itself: read as `FrameData` it is a terminator pointing to an empty
   frame, as a frame it has 0 parts, and as a pointer table it points to
   something valid again. The regions the code passes to `LZ77UncompVram/Wram`
   get a 0 header (they decompress to nothing).
3. **File select tables**: per-language pointers to graphics (→ empty LZ77)
   and to text tables (→ empty texts).
4. **Text**: a readable font fitted to `sCharacterWidths` and short
   placeholder strings for every table, with the tilemaps/palettes of the
   text layers (`tools/open_assets/font.py`, see
   [Text and font](test-baserom-font.md)). Each monologue is "page 1,
   arrow, arrow, page 2, arrow, end", so that both the scenes that wait for
   "more text" and the ones that wait for "end" advance with A.
5. **Voicegroups** (`sVoicegroup_*`): every voice plays the first sample.
6. **Samus visible in the first room**: spriteset 8 lists the gunship (its
   AI clears `gDisableDrawingSamusAndScrollingFlag` on a new game), empty
   room BG tiles are transparent, and new files get button assignments.
   See [Placeholder sprites](open-assets-sprites.md#data-that-had-to-be-filled-in-for-samus-to-show-up).

### How that data is located

So that changes to the decomp or the layout don't break it silently:

- Regions are recognized by the **symbol** the code includes them with
  (`INCBIN`/`.incbin`, see `tools/open_assets/layout.py`), not by the file name
  in `database.json`. If a rule doesn't find any region, the generator fails
  with an error.
- LZ77 sources are detected by searching `src/` and `asm/` for which symbols
  are passed to `LZ77UncompVram/Wram` (in C and in asm).
- What is only known by its original location (the OAM data ranges, three
  file select tables, the text range) is given as an offset in the **base
  ROM**, which has the original ROM's layout and doesn't change even if the
  build shifts or `database.json` is split into more pieces.
- The **values** that point into the build (functions, other data) come from
  the ELF of the previous pass, so they follow the code and data when they
  move. The run with the shifted ROM checks this.

## Known limitations

- The file select screen shows up black (its graphics decompress to
  nothing). The art is placeholder (Samus, HUD, projectiles, effects and
  sprites: see [Placeholder sprites](open-assets-sprites.md)).
- Screenshots depend on the mGBA version; CI pins `ubuntu-24.04`
  (libretro-mgba 0.10.2). With another version the references may need to be
  regenerated.
- When one of these regions gets decompiled (turned into C/asm with symbols),
  it no longer comes from the base ROM and its rule stops applying; if it was
  the only region of a rule, the generator reports an error and the rule has
  to be removed or adjusted.
- The script presses A every 30 frames during the intro; if the length of
  any scene changes, it may need more presses (`BOOT_SCRIPT` in `scenario.py`).
