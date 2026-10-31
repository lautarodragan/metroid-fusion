# Measuring lag on real hardware (LAGMETER build)

All the lag numbers in [Performance](performance.md) come from emulators, and emulators do not
agree on how much Metroid Fusion lags (see *Emulator accuracy* there). The only way to know is to
measure on a Game Boy Advance. `make LAGMETER=1` builds `mf_us_lagmeter.gba`, the game with a lag
meter: you play it on a console from a flash cart, and it records how many frames were lost in
every room into the save file. A script turns the save file into tables.

It is measurement tooling, like `PROFILE`: a separate, non-matching ROM. The normal build is not
changed (`make check` still matches), and nothing about the game is changed except a few hundred
CPU cycles per frame (see *Cost* below).

## What it records

- **Lag frames.** The V-blank interrupt counts video frames; once per logic frame the main loop
  checks how many went by. A logic frame that took *n* video frames lagged *n* − 1 frames: the
  same definition as `tests/emu/lag.py` (an emulated frame in which the game's frame counter does
  not advance).
- **Load.** Every logic frame is timed with timers 2 and 3 chained into a cycle counter (from the
  start of the main loop to the V-blank wait, interrupts included, like `PROFILE=1`). The log
  keeps the highest load per room, in percent of a frame (280,896 cycles). Above 100%, the frame
  lagged.
- **Per room**, for the frames where Samus is playing (game mode *in game*, sub mode *playing*):
  logic frames, lag frames, the longest run of consecutive lagging logic frames, the highest load.
  The totals of a room are added to the log when Samus leaves it (door, elevator, pause, map
  screen, death, cutscene), so the current room is not counted yet if the console is switched
  off: **pause before switching off**.
- **Totals**: frames played, lag frames played, logic frames that lagged, and the frames and lag
  frames of everything else (menus, pause screen, room loads and door transitions, cutscenes),
  plus the number of power-ons.

## The on-screen counter

Press **L+R+SELECT** while playing to cycle through:

1. hidden (the default),
2. `room/total`: lag frames in this room since you entered it / lag frames played in total (all
   sessions, from the log),
3. the same and the highest load of the last second, in percent.

The counter is drawn with two sprites in the bottom left corner, in tiles at the end of sprite
VRAM that are free in most rooms. Where the game uses them (some boss rooms, the area name banner,
the escape timer), the counter stays hidden; the log still counts. SELECT also switches between
missiles and the beam, as usual.

Showing the counter costs a little time every frame, enough to add a few lag frames in the worst
fights (in mGBA, Nightmare with missiles nonstop: 11 instead of 7). **Leave it hidden for the
measurements that count**, and show it to look.

## Saves

The game's saves work as usual in this build: save at save stations and load the file, the same
as in the original game. The log lives in two areas of the 32 KB SRAM that the game never uses
(`0x7180`–`0x77FF` and `0x7C00`–`0x7FDF`, see `include/lagmeter.h`), next to the three files and
their backups, and keeps adding up across sessions, saves, loads and soft resets (A+B+START+SELECT).

- Use the LAGMETER ROM with its own save file. A flash cart keeps one save file per ROM name, so
  this happens by itself if the ROM file has its own name (`mf_us_lagmeter.gba`).
- The game's menu that erases all save data erases the log too.
- To start a new log, delete the `.sav` (or erase all data) and start again.
- A save file from the normal game also works with this build (the log is added to it), and a
  save file of this build works with the normal game (which ignores the log).

## Building it

You need the build environment of this repository ([Setup and build](setup.md)) and your own
dump of the US ROM as `mf_us_baserom.gba`:

```sh
python3 tools/extractor.py   # once, extracts the data from your ROM
make check                   # optional: the normal build, must say "mf_us.gba: OK"
make LAGMETER=1              # builds mf_us_lagmeter.gba
```

(Switching between the normal build and a variant rebuilds the C files, about 15 seconds.)

## Playing it on a console

Tested on mGBA only so far; this is how to use it with a flash cart (written for the EverDrive
GBA, other carts work the same way):

1. Copy `mf_us_lagmeter.gba` to the SD card.
2. Start it from the cart menu. The save type is SRAM, the same as the original game (the ROM
   still has the original's SRAM signature, so the cart detects it).
3. Play. Pause (START) before switching off, so that the room you are in is written to the log.
4. Flash carts keep the save in the cart's memory while you play and copy it to the SD card
   later; EverDrive carts do it the next time their menu starts, so start the console once more
   into the menu before taking the SD card out (check your cart's manual). The file is in the
   cart's save folder (a `SAVE` folder inside `GBASYS` on EverDrive GBA carts), named after the
   ROM: `mf_us_lagmeter.sav`.
5. Copy the `.sav` to your computer.

## The report

```sh
python3 tools/lagmeter_report.py mf_us_lagmeter.sav              # rooms with lag, worst first
python3 tools/lagmeter_report.py mf_us_lagmeter.sav --all --sort room
python3 tools/lagmeter_report.py mf_us_lagmeter.sav --markdown   # tables to paste
python3 tools/lagmeter_report.py mf_us_lagmeter.sav --csv rooms.csv
```

It prints the totals, a table per area and a table per room (area, room number, logic frames
played, lag frames, lag in percent of the frames shown, longest lag streak, highest load). Room
numbers are the game's (`gCurrentRoom`); [Performance](performance.md) has the names of the rooms
where the emulators see the most load. Logic frames per room are stored in units of 16 frames,
so short visits are rounded.

## Checked in mGBA

`lag/lagmeter_check.py` in the private test repository (it needs the original ROM) checks the
build in mGBA:

- In the Nightmare fight and the two nonstop-shooting stress scenarios (11,596 logic frames), the
  lag counted by the build is the lag measured from outside by `tests/emu/lag.py` for every
  single logic frame (0 differences), and the record that the report reads from the SRAM after a
  pause has the same totals.
- With the counter hidden, the build lags as much as the original game (2, 7 and 8 lag frames,
  against 2, 7 and 6 for the original; the probes cost about 100 cycles per frame).
- Save at a save station, soft reset, load the file: the game comes back exactly as the original
  game does with the same input (same room, same Samus, same equipment, and the game's part of
  the SRAM identical to the original's), and the log survives the reset and goes on counting.

## Cost

| | Cycles per logic frame | ROM | RAM |
| --- | --- | --- | --- |
| Counter hidden | about 100 (V-blank count, two timer reads, the per-frame accounting) | about 2.5 KB of code and data | about 100 bytes of IWRAM at `0x3007000` |
| Counter shown | about 100 more on average (2 OAM entries every frame, one tile checked and redrawn every 4 frames, the text rebuilt at most twice per second) | | |
| Leaving a room | a few thousand once (SRAM writes, 8-bit) | | |

The cost is small, but Nightmare's frames are so close to the limit that even this is visible
when the counter is shown. With it hidden, the measured lag matched the original's in mGBA.
