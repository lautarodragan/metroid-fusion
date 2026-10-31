# Performance: lag in boss fights

Metroid Fusion is known to slow down in some boss fights, Nightmare in
particular. This chapter measures how much the game lags there, what the CPU
time goes to, and what two small changes to the code do about it. The changes
are in a separate, non-matching build (`make OPTIMIZE=1`); the normal build is
untouched and still matches the ROM.

**Short version.** In mGBA, the original game drops a frame only rarely in
these fights (2 lag frames in a full Nightmare fight of 3,596 logic frames, 6
to 7 per 4,000 frames when Samus shoots nonstop, none in the BOX fights), but
Nightmare's frames are right at the limit: on average 78% of the frame
budget, with peaks above 100%. Two changes to how sprites are visited
(projectile hit checks and the drawing passes) take 16% of the frame budget
off every frame, in every room; with them no measured fight lags, and
Nightmare peaks at 81%. The game state is the same at every logic frame.

Across the whole game (all 393 rooms, see [Lag map](#lag-map-of-the-whole-game)),
ordinary rooms do not lag in mGBA; the heaviest ones run at 80-95% of the
budget at their peaks (Sector 4's flooded rooms, Zazabi's lair, the haze rooms
of Sectors 3 and 5), and only Nightmare and Ridley actually cross it. But mGBA
is not cycle-exact: NanoBoyAdvance, a more accurate emulator, runs the same
code 1.3% slower per frame, and because so many frames sit just under the
limit, it shows 5 times as many lag frames in the Nightmare fights (11 instead
of 2). Real hardware is probably closer to NanoBoyAdvance; the
[LAGMETER build](lag-meter.md) measures it on a console.

## Lag frames

The main loop (`AgbMain`, `src/agbmain.c`) runs one *logic frame* per
iteration: it increments `gFrameCounter8Bit`/`gFrameCounter16Bit`, runs the
handler of the game mode, clears bit 0 of `gVBlankRequestFlag` and halts
until the V-blank interrupt sets it again. A video frame is 280,896 CPU
cycles (228 lines of 1,232 cycles). When a logic frame takes longer, the
V-blank it waits for has already passed, the game waits for the next one, and
the screen shows the same picture twice: a **lag frame**, an emulated frame in
which the frame counter does not advance. The game slows down (it does not
skip logic to catch up).

`tests/emu/lag.py` measures this from outside the game, with any build (or
the original ROM, given the map of a matching build):

- `count_lag_frames(emu, frames)`: run emulated frames and count the ones in
  which `gFrameCounter16Bit` did not change.
- `LogicStepper`: run the game one logic frame at a time. The mGBA core ends
  `retro_run` when the video frame ends, before the V-blank interrupt is
  serviced, so when bit 0 of `gVBlankRequestFlag` is clear at the end of an
  emulated frame, the game has finished its logic frame and is halted: a
  *logic-frame boundary*. `step(keys)` runs from one boundary to the next and
  returns the lag frames of that logic frame. The game reads the buttons
  once per logic frame (`UpdateInput`, just before the counter is
  incremented), so the keys set before a step are the keys that logic frame
  sees.

```python
from harness import Emulator
from lag import LogicStepper
emu = Emulator("mf_us.gba", "mf_us.map")
stepper = LogicStepper(emu)
stepper.sync()
lag = sum(stepper.step(["RIGHT"]) for _ in range(600))   # lag frames in 600 logic frames
```

Driving builds in logic frames is what makes it possible to compare an
optimized build with the original once one of them lags (see Correctness
below).

## The fights

The measurements below use scripted fights against the original ROM. They
need the original game, so the scripts and the recorded input are not in this
repository; this is how they are set up, starting from a new game in the
docking bay:

- **What makes the bosses spawn.** Nightmare is in the default spriteset of
  Sector 5 room 20; `NightmareInit` deletes it if Samus has the Gravity Suit.
  BOX (Sector 3 room 23, default spriteset) only stays if
  `gEventCounter == EVENT_TRIGGERED_BOX_RUMBLE` (`BoxInit`,
  `EventCheckOn_BoxRumble`). BOX 2 (Sector 6 room 16) deletes itself if Samus
  has the Wave Beam (`Box2Init`).
- **Why they did not show up after a warp.** A warp that imitates an area
  connection leaves Samus in `SPOSE_FACING_FOREGROUND`, one of the poses for
  which `SpriteUtilCheckSamusStopSpritesPose` freezes every sprite that is
  past its first pose. Nightmare sits in its "waiting to appear" pose until
  Samus moves.
- **Setup**, written at a logic-frame boundary: the equipment (1999 energy so
  that Samus survives, missiles, Charge/Wide/Plasma Beam, Varia Suit), the
  event counter, then the warp (`gCurrentArea`, `gLastDoorUsed`, a black fade,
  `SUB_GAME_MODE_LOADING_ROOM`).
- **Fights.** A policy reads the game state on the original ROM (where the
  boss's weak part is) and walks and shoots at it; its input per logic frame
  is recorded once and replayed on every build. When the target has not been
  hit for 240 logic frames, the policy takes a third of its health with a RAM
  write at a boundary (also recorded), so that every fight goes through all
  of its phases in a bounded time. Nightmare: appearing, phase 1, phase 2
  (gravity generator on), phase 3 (face), death. BOX and BOX 2: from the
  start to the boss's exit.
- **Stress**: fixed input, Samus at Nightmare's arrival point shooting up
  nonstop (missiles every 16 logic frames, or the beam every 6) for 4,000
  logic frames, and the beam during BOX 2.
- **Control**: walking and shooting in the docking bay.

## Baseline

Lag frames in the measured part (the fight; room loads excluded), emulated by
mGBA 0.10.2 (libretro core, the emulator harness):

| Scenario | Logic frames | Lag frames, original |
| --- | ---: | ---: |
| Control (docking bay) | 1,200 | 0 |
| Nightmare, full fight | 3,596 | 2 |
| BOX, full fight | 2,075 | 0 |
| BOX 2, full fight | 3,228 | 0 |
| Nightmare, missiles nonstop | 4,000 | 7 |
| Nightmare, beam nonstop | 4,000 | 6 |
| BOX 2, beam nonstop | 4,000 | 0 |

The normal build of this repository is the same ROM and gives the same
numbers.

### Where the cycles go

`make PROFILE=1` builds `mf_us_profile.gba`, which times the whole logic
frame (main loop start to the V-blank wait, interrupts included), the sound
update, the in-game handler and the V-blank handler with timers 2 and 3
chained into a 32-bit cycle counter (the game only uses timer 0). The counts
of the last logic frame are in `gProfile` (free IWRAM at `0x3005630`, see
`include/profile.h`), and `lag.ProfileReader` reads them at every boundary.
The probes cost a few hundred cycles per frame, so this build lags a little
more than the original (9 lag frames instead of 2 in the Nightmare fight; in
the room sweep below, where the original lags only once, it lags exactly as
often),
but its frame totals are those of the original code:

| Scenario | Mean | Max | Frames > 95% | Frames > 100% |
| --- | ---: | ---: | ---: | ---: |
| Control | 46.0% | 68.0% | 0 | 0 |
| Nightmare | 77.9% | 108.3% | 19 | 4 |
| BOX | 70.8% | 88.2% | 0 | 0 |
| BOX 2 | 76.0% | 90.7% | 0 | 0 |
| Nightmare, missiles nonstop | 86.1% | 104.2% | 40 | 2 |
| Nightmare, beam nonstop | 82.6% | 104.3% | 34 | 4 |
| BOX 2, beam nonstop | 70.9% | 85.1% | 0 | 0 |

(Percent of the 280,896-cycle frame, per logic frame. A frame above 100% does
not always lag: the cycles of the V-blank handler that runs before the logic
frame starts count here too.)

`make PROFILE=2` (`mf_us_profile2.gba`) also times every subsystem of the
in-game handler and every sprite. Its probes sit inside the loops, cost
cycles and registers (the loops spill to the stack), and raise the totals by
about 10%, so its numbers are for proportions. Mean cycles per logic frame in
Nightmare's phase 2 (gravity generator on, 546 logic frames), original code
and with `OPTIMIZE=1`:

| Region | Original | OPTIMIZE=1 |
| --- | ---: | ---: |
| Whole logic frame | 271,968 | 215,210 |
| `UpdateAudio` (sound engine and mixer) | 54,196 | 51,761 |
| `InGameHandler` | 216,048 | 162,893 |
| &nbsp;&nbsp;`SpriteUpdate` (AI 13.8k, copies to/from `gCurrentSprite` 9.1k, animation and on-screen checks 8.3k, Samus collision 5.5k) | 50,092 | 50,083 |
| &nbsp;&nbsp;`ProjectileUpdate` | 37,162 | 6,760 |
| &nbsp;&nbsp;&nbsp;&nbsp;`ProjectileCheckHittingSprite` | 34,701 | 4,286 |
| &nbsp;&nbsp;`RoomUpdate` (tilemap streaming 17.6k, haze 17.5k) | 39,357 | 39,351 |
| &nbsp;&nbsp;`unk_eb04` + `SpriteDrawAll` + `unk_ec38` (sprite drawing passes) | 48,979 | 26,257 |
| &nbsp;&nbsp;&nbsp;&nbsp;of which `SpriteDraw` | 14,206 | 14,300 |
| &nbsp;&nbsp;`ParticleUpdate` | 9,222 | 9,265 |
| &nbsp;&nbsp;`HudDraw` | 7,449 | 7,443 |
| &nbsp;&nbsp;Samus physics | 6,786 | 6,764 |
| V-blank handler | 9,923 | 8,629 |

What stands out:

- **`ProjectileCheckHittingSprite`** (`src/projectile.c`) visits sprites in
  draw order by scanning the 24 sprite slots once for each of the 16 draw
  orders (384 iterations), and for every sprite found, the 16 projectile
  slots, every frame, whether or not a projectile exists. That is 13% of the
  frame for a handful of hit checks.
- **The three drawing passes** do the same: 24 slots for each of 8 draw
  orders, three times per frame. Without counting the sprites they draw, they
  cost about 12% of the frame.
- The **sound mixer** (`SoundCodeA/B/C`) is already ARM code copied to IWRAM
  by the original programmers, as is the haze code (copied into
  `gNonGameplayRam`).
- `FixedInverse`, a software division that `SpriteDraw` calls up to 16 times
  per rotated or scaled sprite, is never called in these fights (no sprite
  there is rotated or scaled), so it does not matter here.
- The prefetch buffer is already enabled (`REG_WAITCNT`, bit 14; the header
  `include/gba/waitstate.h` had the bit names off by one, now fixed).

## The optimizations

`make OPTIMIZE=1` builds `mf_us_opt.gba` with the changes below, each behind
its own define (`include/optimize.h`); `make OPTIMIZE="PROJ_HIT"` enables some
of them only. They can be combined with `PROFILE=1|2`
(`mf_us_profile_opt.gba`).

- **`OPTIMIZE_PROJ_HIT`**: `ProjectileCheckHittingSprite` lists the projectiles
  that can hit (returns early when there is none: nothing else spawns
  projectiles during the check), sorts the sprites by draw order once
  (insertion sort of at most 24 slots, stable, so the order is the
  original's: by draw order, then by slot) and checks each sprite against the
  listed projectiles only. After every hit the list is built again and the
  loop goes on with the projectiles after the current one, since a hit can
  remove projectiles or spawn new ones (diffusion missile flakes), exactly as
  the original loop would see them.
- **`OPTIMIZE_DRAW_ORDER`**: the three drawing passes draw from the same kind
  of sorted list (`SpriteDrawSorted`). `gSpriteDrawOrder` is filled as before.
- **`OPTIMIZE_IWRAM`** (opt-in, not in `OPTIMIZE=1`): the functions marked
  `IWRAM_CODE` (`SpriteDraw`, `SpriteUpdateAnimation`, `ProjectileDraw`,
  `ParticleDraw`) are linked to run at `0x3005900` and copied there by
  `InitializeGame`. A Thumb `bl` cannot reach between ROM and IWRAM, so their
  files are compiled with `-mlong-calls` and `tools/iwram_calls.py` points the
  calls made from IWRAM to IWRAM copies of libgcc's `_call_via_rX` stubs
  (`asm/iwram_call_via.s`). Same code, faster memory.

Measured with `PROFILE=1` (frame totals), percent of the frame budget, mean /
max per logic frame:

| Scenario | Original | PROJ_HIT | DRAW_ORDER | IWRAM | PROJ_HIT + DRAW_ORDER | all three |
| --- | --- | --- | --- | --- | --- | --- |
| Control | 46.0 / 68.0 | 38.4 / 60.4 | 38.8 / 60.7 | 44.8 / 67.4 | 31.3 / 53.2 | 30.2 / 52.7 |
| Nightmare | 77.9 / 108.3 | 68.4 / 88.0 | 70.7 / 90.9 | 77.0 / 95.7 | 61.2 / 81.1 | 60.3 / 78.9 |
| BOX | 70.8 / 88.2 | 61.8 / 79.5 | 63.8 / 81.2 | 69.6 / 86.5 | 54.8 / 72.5 | 53.7 / 70.9 |
| BOX 2 | 76.0 / 90.7 | 67.2 / 81.4 | 69.0 / 83.9 | 74.4 / 88.6 | 60.3 / 74.6 | 58.7 / 72.5 |
| Nightmare, missiles | 86.1 / 104.2 | | | 84.6 / 103.1 | 69.6 / 80.7 | 68.1 / 79.5 |
| Nightmare, beam | 82.6 / 104.3 | | | 82.2 / 103.7 | 66.8 / 84.0 | 66.4 / 83.1 |
| BOX 2, beam | 70.9 / 85.1 | | | 69.7 / 83.8 | 54.9 / 69.4 | 53.7 / 68.1 |

Lag frames (builds without the profiler):

| Scenario | Original | OPTIMIZE=1 | OPTIMIZE=1 + IWRAM |
| --- | ---: | ---: | ---: |
| Nightmare, full fight | 2 | 0 | 0 |
| Nightmare, missiles nonstop | 7 | 0 | 0 |
| Nightmare, beam nonstop | 6 | 0 | 0 |
| Control, BOX, BOX 2, BOX 2 beam | 0 | 0 | 0 |

Cost:

| Change | ROM | IWRAM | Gain (mean, % of the frame) |
| --- | --- | --- | --- |
| `PROJ_HIT` | +184 bytes of code | none (the lists are on the stack) | 7.6 to 9.5 |
| `DRAW_ORDER` | +0 bytes (a new function, three smaller ones) | none | 7.0 to 7.2 |
| `IWRAM` | +3,860 bytes (the 3,148-byte image of the IWRAM code, and long calls) | 3,148 bytes of code | 0.4 to 1.6 |

The two sorted-list changes are worth having: cheap, local, and they help in
every room where Samus shoots (the docking bay goes from 46% to 31%). Moving
functions to IWRAM barely helps: the prefetch buffer already makes straight
Thumb code from ROM almost as fast, and the long calls cost back part of the
gain. Of what is left, the sound engine (18%, already optimized), the sprite
update (18%, a third of it the 56-byte copies of every sprite to and from
`gCurrentSprite`), the tilemap streaming and the haze (6% each) are the next
candidates, all larger changes.

## Correctness

The optimized build must behave like the original except for lag. A
frame-by-frame comparison cannot check that once the original lags, so a
second comparison runs both ROMs in lockstep **in logic frames**
(`LogicStepper`), with the same input and RAM writes per logic frame, and
compares them at every logic-frame boundary:

- EWRAM and IWRAM at every boundary, ROM pointers held in RAM translated
  between the two builds' symbols (the optimized build moves code), the
  stacks left out;
- VRAM, OAM and palette at boundaries where neither ROM lagged during that
  logic frame (when a logic frame lags, the V-blank in the middle of it
  copies a half-built frame to OAM and VRAM: that is the lag itself).

Things that legitimately depend on timing, already in the original:

- **The sound mixer follows real time.** The interrupt of the sound DMA
  (DMA 2) advances the playback position (`gMusicInfo.unk_10`) as the samples
  are played, and `UpdateMusic` mixes as many samples as were played since it
  last ran. After a lag frame
  the original mixes more samples at once, which moves every channel's sample
  position (and a sample that ends a logic frame sooner or later feeds back
  into the tracks). The sound state is therefore compared until the lag of
  the two ROMs first differs, and left out after that. Builds whose start-up
  code takes a different number of cycles (`PROFILE`, `OPTIMIZE_IWRAM`) start
  the sound timer with a slightly different phase relative to the frames, and
  their mixer state can differ by one block of samples even without lag: for
  them the mixer state is never compared (the music tracks still are).
- **VRAM written while the screen is drawn.** The HUD and the minimap are
  written to VRAM during the frame, not in V-blank; a build that gets there
  sooner moves the tear by a few lines. VRAM itself is identical at the
  boundaries; screenshots differ in those lines only.
- **The backdrop entry of the fade palettes.** In rooms whose haze rewrites the
  backdrop color on every line with an H-blank DMA, a fade that copies palette
  RAM into `gBackgroundPalette1/2` copies whichever color the current line
  has. It is overwritten on the next frame.

Results for `OPTIMIZE=1` (`PROJ_HIT` and `DRAW_ORDER`): identical at every
boundary in the 7 fight scenarios, walk, menus, the save, navigation and
elevator scenarios and the 393 rooms of the room sweep of the parity suite
(405 scenarios; the sound state was left out only after the lag first
differed: in the three Nightmare scenarios, where the original lags and the
optimized build does not, in the save scenario and in two rooms of the sweep,
where one frame lags in the original only). In the
frame-by-frame parity suite (stacks left out), boot, walk, menus, the
navigation room and the elevator ride are identical frame by frame; the save
station differs from the frame where the original has its extra lag frame.
`OPTIMIZE_IWRAM` was checked on the fights in the same way. There is no
intentional difference.

## Lag map of the whole game

The fights above are where the game is known to slow down. To see where else
it runs close to the limit, every room was played the same way and measured
(scripts in the private test repository, `lag/lagmap/`, since they need the
original game).

**Method.**

- **Rooms**: the 393 rooms of the parity suite's room sweep, entered with the
  same warp (an imitated area connection, see *The fights*), from the end of
  the boot script, with most of the equipment (1999 energy, missiles, super,
  ice, diffusion missiles, power bombs, Charge/Wide/Plasma Beam, Varia Suit,
  Morph Ball, High Jump, Space Jump).
- **Input**: after the room loads (150 logic frames), a fixed cycle of 128
  logic frames for 1,200 logic frames: walk right and left (Samus moves first,
  so the sprites are not frozen by the "facing the screen" pose), jump, shoot
  the beam, fire missiles, aim up. Walking takes Samus through doors, so some
  neighbouring rooms get frames too: every logic frame counts for the room
  Samus is in, and only the frames where she is playing (game mode *in game*,
  sub mode *playing*) count for the room; door transitions, room loads and
  menus are counted apart.
- **Events**: twice, with the event counter right after the start of a new
  game (0) and late in the game (89, `EVENT_RESTRICTED_ZONE_WARNING`): rooms
  get other enemies (and more X parasites) as the story goes on
  (`firstSpritesetEvent`/`secondSpritesetEvent` of each room). The table keeps
  the run with the higher load for each room.
- **Measurements**: lag frames with the original ROM, cycles with the
  `PROFILE=1` build (frame totals, the probes cost a few hundred cycles per
  frame). The profile build replays the same input and lags exactly as often
  as the original in the sweep (1 lag frame in each, the same frame), which is
  the check that its timing is close enough. Load is `LOOP` (main loop start
  to the V-blank wait, interrupts included) in percent of the 280,896-cycle
  frame; p95/p99 are percentiles over the room's logic frames.

**Result.** In about 400,000 logic frames of play per run, the original game
lagged **once** while playing, in mGBA, in both runs the same frame: Sector 4
room 10 (the room with the hatch to Serris), one logic frame at 107% six
seconds into the input. The heaviest ordinary
rooms reach 90-95% at their peaks but stay under the limit. Lag outside play is
another matter: the frames that load a room during a door transition lag in
every transition (about 4,000 of 45,000 logic frames in transitions), as do
opening and closing the map screen (a single logic frame of up to 9 video
frames while it loads), which is expected and not seen as slowdown (the
screen is black or still).

### Hotspot rooms

The 25 rooms with the highest 99th percentile of load (rooms with at least 60
logic frames played; "late game": the event-89 run had the higher load):

| # | Room | Contents | Logic frames | Lag (original) | Mean | p95 | p99 | Max | > 90% | > 95% | > 100% |
| ---: | --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 1 | Sector 4 (AQA) 15 (late game) | water, 1 X, 13 sprites | 1,200 | 0 | 83.3 | 90.3 | 92.8 | 95.2 | 73 | 1 | 0 |
| 2 | Sector 2 (TRO) 17 | gadora_zazabi, 1 X, 13 sprites | 2,953 | 0 | 80.5 | 87.4 | 90.4 | 93.5 | 39 | 0 | 0 |
| 3 | Sector 2 (TRO) 44 (late game) | 1 X, 10 sprites | 337 | 0 | 72.9 | 84.6 | 88.6 | 89.6 | 0 | 0 | 0 |
| 4 | Sector 5 (ARC) 20 (late game) | haze BG1-3, nightmare, 1 sprites | 1,369 | 0 | 76.3 | 85.5 | 88.4 | 94.8 | 4 | 0 | 0 |
| 5 | Sector 4 (AQA) 7 (late game) | 1 X, 13 sprites | 447 | 0 | 76.5 | 84.9 | 88.1 | 89.9 | 0 | 0 | 0 |
| 6 | Sector 5 (ARC) 47 (late game) | 10 sprites | 906 | 0 | 75.8 | 86.2 | 87.9 | 89.6 | 0 | 0 | 0 |
| 7 | Sector 3 (PYR) 36 (late game) | heat haze BG2+BG3, 9 sprites | 392 | 0 | 76.1 | 84.9 | 87.5 | 89.5 | 0 | 0 | 0 |
| 8 | Main Deck 47 (late game) | 12 sprites | 486 | 0 | 78.7 | 86.0 | 87.3 | 88.3 | 0 | 0 | 0 |
| 9 | Sector 3 (PYR) 15 (late game) | lava + heat haze, 12 sprites | 466 | 0 | 76.6 | 85.4 | 87.2 | 91.3 | 2 | 0 | 0 |
| 10 | Sector 5 (ARC) 7 | snow (knockback), 1 X, 16 sprites | 2,233 | 0 | 76.1 | 84.5 | 87.2 | 90.8 | 6 | 0 | 0 |
| 11 | Sector 6 (NOC) 16 (late game) | water, box_2, 1 sprites | 2,269 | 0 | 74.5 | 83.9 | 87.1 | 91.3 | 3 | 0 | 0 |
| 12 | Sector 4 (AQA) 34 (late game) | water, 3 X, 17 sprites | 524 | 0 | 78.8 | 85.5 | 87.0 | 87.8 | 0 | 0 | 0 |
| 13 | Main Deck 49 (late game) | gradient BG3, 1 X, 14 sprites | 1,200 | 0 | 74.7 | 83.3 | 86.3 | 89.6 | 0 | 0 | 0 |
| 14 | Sector 3 (PYR) 12 (late game) | lava + heat haze, 8 sprites | 240 | 0 | 75.7 | 84.5 | 86.2 | 92.0 | 3 | 0 | 0 |
| 15 | Sector 6 (NOC) 33 (late game) | 1 X, 13 sprites | 1,620 | 0 | 76.0 | 83.6 | 86.1 | 90.0 | 0 | 0 | 0 |
| 16 | Sector 5 (ARC) 19 (late game) | gadora_nightmare, 17 sprites | 1,200 | 0 | 75.6 | 83.1 | 85.6 | 87.2 | 0 | 0 | 0 |
| 17 | Sector 4 (AQA) 23 (late game) | water, 1 X, 12 sprites | 1,647 | 0 | 75.8 | 83.1 | 85.2 | 89.4 | 0 | 0 | 0 |
| 18 | Sector 4 (AQA) 12 (late game) | water, 1 X, 10 sprites | 1,200 | 0 | 76.0 | 83.8 | 85.0 | 86.2 | 0 | 0 | 0 |
| 19 | Sector 1 (SRX) 15 (late game) | 6 sprites | 3,305 | 0 | 71.2 | 78.8 | 84.4 | 91.3 | 1 | 0 | 0 |
| 20 | Sector 6 (NOC) 8 (late game) | 1 X, 14 sprites | 1,626 | 0 | 73.0 | 80.6 | 84.3 | 88.8 | 0 | 0 | 0 |
| 21 | Sector 3 (PYR) 7 | heat haze BG2+BG3, 10 sprites | 1,418 | 0 | 74.2 | 81.4 | 84.1 | 88.3 | 0 | 0 | 0 |
| 22 | Sector 4 (AQA) 14 (late game) | water, 3 X, 18 sprites | 619 | 0 | 74.4 | 81.1 | 84.0 | 85.2 | 0 | 0 | 0 |
| 23 | Sector 4 (AQA) 19 (late game) | water, 1 X, 9 sprites | 1,200 | 0 | 75.6 | 82.0 | 84.0 | 85.7 | 0 | 0 | 0 |
| 24 | Sector 3 (PYR) 17 | heat haze BG2+BG3, 8 sprites | 1,255 | 0 | 71.9 | 80.6 | 83.2 | 87.3 | 0 | 0 | 0 |
| 25 | Sector 2 (TRO) 14 | 10 sprites | 1,769 | 0 | 74.6 | 80.5 | 82.9 | 85.7 | 0 | 0 | 0 |

"Contents" is what the room's sprite data holds at that event (bosses, number
of X parasites, number of sprites) and its visual effect. Room numbers are the
game's (`gCurrentRoom`, `include/structs/connection.h`); the rooms have no
names in the code.

### Per area

Rooms with at least 60 logic frames played:

| Area | Rooms | Logic frames | Lag frames | Mean load | Room means (min-max) | Worst room p99 | Max | Rooms with p99 > 80% | Frames > 90% | Frames > 95% |
| --- | ---: | ---: | ---: | ---: | --- | ---: | ---: | ---: | ---: | ---: |
| Main Deck | 71 | 87,416 | 0 | 58.4 | 49.5-78.7 | 87.3 | 89.6 | 2 | 0 | 0 |
| Sector 1 (SRX) | 50 | 54,700 | 0 | 62.1 | 52.5-71.8 | 84.4 | 91.3 | 3 | 1 | 0 |
| Sector 2 (TRO) | 57 | 62,745 | 0 | 63.4 | 51.7-80.5 | 90.4 | 93.5 | 7 | 39 | 0 |
| Sector 3 (PYR) | 39 | 37,406 | 0 | 63.5 | 52.5-76.6 | 87.5 | 92.0 | 7 | 5 | 0 |
| Sector 4 (AQA) | 46 | 49,369 | 1 | 65.4 | 52.1-83.3 | 92.8 | 107.1 | 11 | 75 | 2 |
| Sector 5 (ARC) | 47 | 52,324 | 0 | 62.2 | 51.5-76.3 | 88.4 | 94.8 | 7 | 10 | 0 |
| Sector 6 (NOC) | 39 | 44,631 | 0 | 63.9 | 52.5-76.0 | 87.1 | 91.3 | 5 | 3 | 0 |

### Heat map

One cell per room (room 0 first, groups of ten), by the 99th percentile of
load; blank: not entered, or fewer than 60 logic frames played:

```
  . < 60%   - 60-70%   o 70-80%   O 80-90%   # > 90%
Main Deck       - -- .---  o-----o -- ---------- -o-- -.--o ---.  -O-O --  --o---  ---- ---o - -.- --o   o- ---
Sector 1 (SRX)  o--ooo-Ooo  --o-O---- --o--oo--O --o--oo--- ---o -o---  -- 
Sector 2 (TRO)  o--o-ooo-o OoooO--#-- o- o---oo- -OOo o---- ----O-o -- o----- -Oo o
Sector 3 (PYR)  o--o--oO-o -oOO-OoO-o --o-o--O-o ---oo-O--
Sector 4 (AQA)  -- ---OOOo --OoO#OooO oO-Ooo--o- -- oO-ooo- o-o---o-
Sector 5 (ARC)  O--o--oOo  -o---O-ooO O-o----o-- o -o.-o--o  -O oooO-- - 
Sector 6 (NOC)  o--OooooO- o-o-OoO--o o----o -o- oooO.---o  o
```

What makes a room heavy, from the `PROFILE=2` breakdown of the fights and the
rooms above:

- **Many sprites at once**: every sprite's AI and the copies to and from
  `gCurrentSprite`, the drawing passes over all 24 slots, and the projectile
  hit checks over all slots (the two passes `OPTIMIZE=1` fixes). Sector 4's
  flooded rooms with fish and X parasites, Zazabi's lair with its Zoros and
  the Nightmare and Ridley fights are all sprite-heavy.
- **Haze and heat effects**: `HazeProcess` (about 17,500 cycles, 6% of the
  frame, in Nightmare's room), in the rooms with heat haze or the Nightmare
  haze, plus the H-blank DMA that rewrites a register on every line.
- The visual effects by themselves (water, lava, heat, cold, acid) are not
  what makes a room heavy: the test suite's environment scenarios, one per
  effect, stay at 78-85% at the 99th percentile; the heaviest rooms combine an
  effect with many sprites.

### Bosses, stress and other modes

Boss fights, chases, the escape and the other scenarios of the private test
suite's scenario library (`tests/library.py`: equipment and event set by RAM
writes, a warp, then a fixed input; some fights take part of the boss's
health by RAM writes at fixed points to stay short), and the fights of this
chapter (*The fights*, and minimal boss scenarios of the lag map that walk to
and shoot the sprite with the most health). Lag of the original ROM in mGBA
and in NanoBoyAdvance (see *Emulator accuracy*), load from the `PROFILE=1`
build in mGBA, over the logic frames played; the ten heaviest, then the
others that lag:

| Scenario | Logic frames played | Lag, mGBA | Lag, NanoBoyAdvance | Mean | p99 | Max | > 95% | > 100% |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| bosses/nightmare (suite) | 3,060 | 83 | 184 | 87.0 | 100.0 | 111.2 | 212 | 31 |
| Nightmare, missiles nonstop | 4,000 | 7 | 37 | 86.1 | 95.0 | 104.2 | 40 | 2 |
| Nightmare, beam nonstop | 4,000 | 6 | 23 | 82.6 | 94.7 | 104.3 | 34 | 4 |
| Ridley (lag map) | 3,000 | 3 | 9 | 80.7 | 94.4 | 103.5 | 24 | 3 |
| Nightmare (this chapter) | 3,596 | 2 | 11 | 77.5 | 93.5 | 108.3 | 19 | 4 |
| bosses/ridley (suite) | 5,116 | 2 | 2 | 75.6 | 91.5 | 104.6 | 5 | 2 |
| sequences/lab_escape (suite) | 5,908 | 2 | 2 | 72.8 | 90.4 | 115.1 | 6 | 2 |
| bosses/serris (suite) | 5,606 | 0 | 0 | 74.2 | 88.9 | 95.4 | 1 | 0 |
| BOX 2 (this chapter) | 3,228 | 0 | 0 | 74.3 | 87.4 | 90.7 | 0 | 0 |
| environments/underwater (suite) | 606 | 0 |  | 71.4 | 85.2 | 86.3 | 0 | 0 |
| *others with lag frames* | | | | | | | | |
| weapons/ice_beam (suite) | 646 | 2 |  | 64.4 | 84.3 | 139.5 | 2 | 2 |
| weapons/wave_beam (suite) | 646 | 2 |  | 62.0 | 82.4 | 138.3 | 2 | 2 |
| weapons/bombs_power_bombs (suite) | 603 | 2 | 2 | 61.1 | 77.6 | 139.8 | 2 | 2 |
| system/game_over_continue (suite) | 2,321 | 1 |  | 57.1 | 72.9 | 102.9 | 2 | 1 |
| items/tanks (suite) | 380 | 1 |  | 47.1 | 58.3 | 103.1 | 1 | 1 |
| system/save_load_reset (suite) | 1,612 | 1 |  | 45.3 | 53.0 | 102.9 | 2 | 1 |

The other 70 scenarios (the remaining bosses, among them Arachnus, Zazabi, BOX, Yakuza, Nettori, SA-X and Omega Metroid, the SA-X chases, the environments, weapons, abilities, navigation rooms, pause maps, transitions) do not lag while playing in mGBA; the heaviest of them reaches 84.8% at the 99th percentile.

- **Nightmare** is by far the worst, and it depends on how it is fought: the
  test suite's fight, which keeps Samus under the boss and shooting, lags 83
  times in 3,060 logic frames in mGBA (31 frames above 100%) and 184 times in
  NanoBoyAdvance, against 2 and 11 in this chapter's fight.
- **Ridley** is the second fight that crosses the limit (2 to 3 lag frames per
  fight in mGBA; NanoBoyAdvance: 9 in the lag map's fight, 2 in the test
  suite's).
- **The lab escape** (the sequence with the timer) peaks at 115% and lags
  twice while playing (two consecutive logic frames); its other lag frames are
  in transitions.
- **Isolated frames above 100%** in light scenarios: two consecutive logic
  frames at about 139% at one moment of the ice beam, wave beam and power bomb
  scenarios, one frame at about 103% when a tank is picked up, in the game
  over screen and in the save scenario. They are single events, with light
  frames around them, not slowdown.
- Every other boss, chase and environment stays under 90% at the 99th
  percentile and does not lag in mGBA.

Other parts of the game (original ROM, mGBA, lag frames per game mode):

| Scenario | Playing: logic frames / lag | Load while playing, mean / max | Other modes: lag |
| --- | --- | --- | --- |
| Pause screen and menus (map, objective, status, sleep) | 165 / 0 | 43.8 / 47.8 | map screen 8 (while it loads), door transition 3 |
| Navigation room conversation | 1,275 / 0 | 45.4 / 55.8 | map screen 8, door transition 7 |
| Elevator ride | 1,352 / 0 | 45.5 / 51.0 | door transition 11 |
| Save station | 1,078 / 1 | 45.2 / 102.4 | door transition 4 |
| Power bombs (10, docking bay) | 1,670 / 0 | 53.4 / 72.4 | |
| Diffusion missiles and charged beam nonstop (docking bay) | 2,910 / 0 | 53.3 / 62.5 | |

The menus and conversations are light (under 60%); their lag is in the logic
frames that load a screen (black or frozen picture). The save station's one
lag frame is the frame that writes the save.

## Emulator accuracy

All the numbers above come from mGBA 0.10.2 (the libretro core of Ubuntu
24.04, with mGBA's HLE BIOS). How much can they be trusted?

### How mGBA times the hardware

From the source of mGBA 0.10.2 (`src/gba/memory.c`) and its developer's notes:

- **Wait states**: mGBA charges every memory access the wait states of its
  region, set from `REG_WAITCNT` (Fusion sets ROM bank 0 to 3 cycles for
  non-sequential and 1 for sequential accesses, SRAM to 4, prefetch on). This
  part is straightforward.
- **Game Pak prefetch**: approximated. `GBAMemoryStall` assumes that while
  the CPU waits on a data access, the prefetch unit fetches up to 8
  sequential halfwords of code, and removes their wait states from the
  following instruction fetches. It does not simulate the buffer cycle by
  cycle (fetches during internal cycles, a fetch in progress when the CPU
  accesses ROM, the buffer state across branches). The developer wrote in
  2015 that "to date, no emulator has ever come close to emulating prefetch
  accurately", and that prefetch emulation had caused regressions in mGBA
  ([mGBA blog, cycle counting and prefetch][mgba-prefetch]).
- **Video memory contention**: on the console, a CPU access to VRAM, OAM or
  palette RAM waits while the PPU is using the same memory (GBATEK: one more
  cycle when the display reads it at the same time) ([GBATEK][gbatek]).
  mGBA 0.10.2 only models this in one case (`GBAMemoryStallVRAM`, marked
  `TODO`: VRAM blocked during the drawing of a line in mode 2 with BG2 and
  BG3); Fusion uses mode 0, so mGBA never adds it here.
  NanoBoyAdvance models it (`Bus::ReadVRAM` and the others wait for the PPU).
- **DMA, timers, interrupts**: modelled with cycle counts; DMA blocks the CPU
  for its transfer, interrupts are taken between instructions.
- **Test results**: SkyEmu's comparison ([SkyEmu accuracy][skyemu]) lists mGBA
  0.9.3 at 1,708/2,020 on the timing tests of the mGBA test suite
  ([suite][mgba-suite]), 1,232/1,256 on the DMA tests, and failing the AGS
  aging cartridge (Nintendo's factory test cartridge, which includes timing
  tests), while NanoBoyAdvance 1.5 passes all of them; NanoBoyAdvance
  describes itself as cycle-accurate for the CPU, DMA, timers, PPU and Game
  Pak prefetch and as the first emulator to pass all AGS tests
  ([NanoBoyAdvance][nba]).
- **Other games**: people comparing TAS movies with consoles report that mGBA
  runs games faster than the console: a Shrek 2 TAS ran about 18 seconds
  ahead on mGBA and about 79 frames ahead on NanoBoyAdvance
  ([NanoBoyAdvance issue 312][nba-312]), and a TAS console verifier wrote that
  mGBA "does not insert nearly enough lag frames"
  ([TASVideos forum][tasvideos]).

So the error is expected in one direction: mGBA running the code a little
faster than the console.

### Measured: the same scenarios in other emulators

Emulators that could run here, headless, with the same harness (only mGBA is
packaged in Ubuntu among GBA emulators; the others were built from their
public sources):

- **mGBA 0.10.2** (Ubuntu package), HLE BIOS: the reference of this chapter.
- **mGBA 0.10.2 with a BIOS**: the [Cult-of-GBA BIOS][cultbios] (an
  open-source replacement BIOS, MIT licence) instead of the HLE BIOS, to see
  what the BIOS changes (the interrupt entry and the BIOS calls are BIOS
  code).
- **mGBA git master** (October 2026), built as a libretro core.
- **NanoBoyAdvance** (git, June 2026), the most accurate emulator available
  as source. It has no libretro core or headless mode, so a small libretro
  wrapper around its core library (about 200 lines: memory map, input, save
  states, and `retro_run` stopping at the start of V-blank like mGBA's core,
  so that `LogicStepper` works the same way) runs it under
  `tests/emu/harness.py`. It needs a BIOS: the same Cult-of-GBA BIOS.
- **NanoBoyAdvance without video memory contention**: the same, with the CPU
  waits on VRAM/OAM/palette accesses removed, to see what they cost.

The wrapper and the variant runner are in the private repository
(`lag/lagmap/nba_libretro/`, `lag/lagmap/variant.py`). NanoBoyAdvance's save
states do not restore every timing detail: a fight started from a saved state
lagged like mGBA (2 lag frames in Nightmare), the same fight emulated in one go
from power-on lagged 11 times, so every NanoBoyAdvance number here comes from
a run in one go (power-on, the boot script, the scenario). The game logic is
the same as in mGBA: the sprites, Samus and the equipment are identical at
every one of the 3,596 logic frames of the Nightmare fight.

Lag frames, original ROM:

| Scenario | Logic frames | mGBA 0.10.2 | mGBA 0.10.2 + BIOS | mGBA master | NanoBoyAdvance |
| --- | ---: | ---: | ---: | ---: | ---: |
| Control (docking bay) | 1,200 | 0 | 0 | 0 | 0 |
| Nightmare, full fight | 3,596 | 2 | 1 | 2 | 11 |
| Nightmare, missiles nonstop | 4,000 | 7 | 7 | 7 | 37 |
| Nightmare, beam nonstop | 4,000 | 6 | 6 | 6 | 23 |
| BOX, full fight | 2,075 | 0 | 0 | 0 | 0 |
| BOX 2, full fight | 3,228 | 0 | 0 | 0 | 0 |
| BOX 2, beam nonstop | 4,000 | 0 | 0 | 0 | 0 |
| Ridley | 3,000 | 3 | – | – | 9 |
| Nettori | 3,000 | 0 | – | – | 0 |
| Serris | 3,000 | 0 | – | – | 0 |
| Yakuza | 3,000 | 0 | – | – | 0 |
| SA-X | 3,000 | 0 | – | – | 0 |
| Omega Metroid | 3,000 | 0 | – | – | 0 |
| Nightmare, test suite's fight | 3,060 | 83 | – | – | 184 |
| Ridley, test suite's fight | 5,116 | 2 | – | – | 2 |
| Lab escape, test suite (playing) | 5,908 | 2 | – | – | 2 |

Cycles per logic frame, `PROFILE=1` build, Nightmare fight (3,596 logic
frames, each emulator against mGBA 0.10.2 frame by frame):

| Emulator | Mean load | Ratio to mGBA (median) | 5th-95th percentile | Lag frames (profile build) |
| --- | ---: | ---: | ---: | ---: |
| mGBA 0.10.2 | 77.47% | 1 | | 9 |
| mGBA 0.10.2 + BIOS | 77.48% | 1.0003 | 0.9992-1.0013 | 7 |
| NanoBoyAdvance | 78.45% | 1.0126 | 1.0104-1.0145 | 19 |
| NanoBoyAdvance, no video memory contention | 78.44% | 1.0125 | 1.0103-1.0145 | 18 |

- **NanoBoyAdvance runs the same frames 1.26% slower**, very consistently
  (about 2,700 cycles per frame), and that is enough for 2 to 5 times as many
  lag frames wherever mGBA already lags (the Nightmare fights, Ridley); in the
  test suite's Nightmare fight, 184 instead of 83.
- It is not the BIOS (0.03%) nor video memory contention (0.01%: the game
  builds OAM and most VRAM updates in RAM and copies them with DMA during
  V-blank). The difference is in the CPU and bus timing (prefetch, wait
  states, DMA, interrupt entry), which NanoBoyAdvance emulates cycle by cycle
  and mGBA approximates.
- mGBA master gives the same lag as 0.10.2 in every scenario.
- The fights that stay under 95% (BOX, BOX 2, the other bosses, the chases)
  do not lag while playing in any emulator.

## How much slower can the console be?

The lag of a logic frame is decided by its length: in the `PROFILE=1` runs,
in both mGBA and NanoBoyAdvance, a logic frame lags when the V-blank handler
before it plus its `LOOP` cycles exceed about 99.35% of the frame (the rest,
about 1,800 cycles, is the interrupt entry and the other interrupts before the
loop starts). With that threshold, the frames measured in mGBA, scaled by
1 + X, give the logic frames that would lag on a console X% slower (each one
loses one frame; a frame would need to be twice as long to lose two):

| Scenario | Logic frames | Lag measured, mGBA (profile build) | +0% | +1.26% (NanoBoyAdvance) | +2% | +5% | +10% |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| Nightmare, full fight | 3,596 | 9 | 7 | 19 | 26 | 129 | 582 |
| Nightmare, missiles nonstop | 4,000 | 16 | 16 | 41 | 61 | 379 | 1919 |
| Nightmare, beam nonstop | 4,000 | 15 | 15 | 33 | 53 | 203 | 844 |
| Ridley | 3,000 | 4 | 4 | 12 | 16 | 40 | 242 |
| BOX 2, full fight | 3,228 | 0 | 0 | 0 | 0 | 0 | 7 |
| Nettori | 3,000 | 0 | 0 | 0 | 0 | 0 | 1 |
| Nightmare, test-suite fight (more aggressive) | 3,060 | 120 | 121 | 209 | 279 | 741 | 1706 |
| Ridley, test-suite fight | 5,116 | 2 | 2 | 3 | 3 | 7 | 191 |
| Lab escape (test suite) | 5,908 | 2 | 2 | 2 | 2 | 14 | 86 |
| Room sweep, early game (393 rooms) | 399,083 | 1 | 1 | 1 | 2 | 13 | 223 |
| Room sweep, late game (393 rooms) | 396,869 | 1 | 1 | 1 | 2 | 13 | 182 |

- At +0%, the model gives back the lag measured in mGBA (Nightmare 7
  against 9 measured, the stress scenarios, Ridley and the test suite's
  fights within one). At +1.26% it gives 19 for this chapter's Nightmare
  fight, what NanoBoyAdvance measured (19, profile build), and 209 for the
  test suite's fight, where NanoBoyAdvance measured 237: the model slightly
  underestimates when many frames lag in a row.
- The fights grow fast: at +5% the Nightmare fight loses about 4% of its
  frames, at +10% 16%, the nonstop-shooting stress up to 48%; the test
  suite's Nightmare fight, already at 4% in mGBA, goes to 7% at +1.26% and
  24% at +5%. Ridley follows, further behind.
- Ordinary rooms stay clean up to about +2%; at +5%, 13 frames of the
  400,000 of each sweep would lag (Sector 4 room 15, Sector 5 room 20, Sector
  4 room 10); at +10%, about 200 (0.05%), mostly in Sector 4 room 15, Sector 2
  room 17 and the haze rooms of Sectors 3 and 5.
- The optimized build (`OPTIMIZE=1`) keeps every measured fight of this
  chapter under 85% of the frame, so it would not lag in them on a console
  10% slower than mGBA.

## Real hardware

The deciding measurement is a console. `make LAGMETER=1` builds the game
with a lag counter and a per-room log in the save file, for a flash cart; see
[Measuring lag on real hardware](lag-meter.md). The most useful things to
play with it: the Nightmare fight (and the same with missiles nonstop), the
Ridley fight, Sector 4 room 15 and Zazabi's lair (Sector 2 room 17). If the
console shows about 11 lag frames in a Nightmare fight like the one above, it
behaves like NanoBoyAdvance.

[mgba-prefetch]: https://github.com/mgba-emu/mgba-news/blob/master/2015-06-27-cycle-counting-prefetch.markdown
[gbatek]: https://problemkaputt.de/gbatek.htm
[skyemu]: https://github.com/skylersaleh/SkyEmu/blob/dev/docs/Accuracy.md
[mgba-suite]: https://github.com/mgba-emu/suite
[nba]: https://github.com/nba-emu/NanoBoyAdvance
[nba-312]: https://github.com/nba-emu/NanoBoyAdvance/issues/312
[tasvideos]: https://tasvideos.org/Forum/Posts/401122
[cultbios]: https://github.com/Cult-of-GBA/BIOS

## Limitations

- **Emulator timing.** The cycle counts and lag frames come from mGBA
  0.10.2, which approximates the prefetch buffer and is not cycle-exact.
  NanoBoyAdvance runs the same frames 1.3% slower and lags 3 to 5 times as
  often in the Nightmare and Ridley fights (see *Emulator accuracy*); the
  console has not been measured yet (see *Real hardware*). The optimized build
  keeps a margin of about 15% of the frame.
- **Scripted play.** The fights are played by a simple policy, with some
  health taken by RAM writes; a human hits more often and causes more
  explosions and particles. The nonstop-shooting scenarios are the closest to
  the worst case measured here. The room sweep walks, jumps and shoots with a
  fixed input for 20 seconds per room: it finds the rooms that are heavy by
  themselves, not the worst moment a player can create in them.
- The profiler does not time H-blank handlers: in a cutscene whose H-blank
  handler runs on every line, the extra cycles starve the main loop.

## Building and measuring

```sh
make PROFILE=1      # mf_us_profile.gba: frame totals in gProfile
make PROFILE=2      # mf_us_profile2.gba: every subsystem and sprite slot
make OPTIMIZE=1     # mf_us_opt.gba: PROJ_HIT and DRAW_ORDER
make OPTIMIZE="PROJ_HIT DRAW_ORDER IWRAM"
make PROFILE=1 OPTIMIZE=1   # mf_us_profile_opt.gba
make LAGMETER=1     # mf_us_lagmeter.gba: lag counter and per-room log, for a console
make check          # the normal build, which these flags do not change
```

The objects of C files depend on the variant flags (`.build_flags`), so
switching between the normal build and a variant rebuilds them (about 15
seconds).

From Python, with the emulator harness: `lag.LogicStepper` to drive a build,
`lag.ProfileReader(emu)` to read `gProfile.last` at each boundary (field names
come from `enum ProfileRegion` in `include/profile.h`).
