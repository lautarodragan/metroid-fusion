# Performance: lag in boss fights

Metroid Fusion is known to slow down in some boss fights, Nightmare in
particular. This chapter measures how much the game lags there, what the CPU
time goes to, and what two small changes to the code do about it. The changes
are in a separate, non-matching build (`make OPTIMIZE=1`); the normal build is
untouched and still matches the ROM.

**Short version.** In mGBA, the original game drops a frame only rarely in
these fights (2 lag frames in a full Nightmare fight of 3,355 logic frames, 6
to 7 per 4,000 frames when Samus shoots nonstop, none in the BOX fights), but
Nightmare's frames are right at the limit: on average 78% of the frame
budget, with peaks above 100%. Two changes to how sprites are visited
(projectile hit checks and the drawing passes) take 16% of the frame budget
off every frame, in every room; with them no measured fight lags, and
Nightmare peaks at 81%. The game state is the same at every logic frame.

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
| Nightmare, full fight | 3,355 | 2 |
| BOX, full fight | 1,834 | 0 |
| BOX 2, full fight | 2,987 | 0 |
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
more than the original (9 lag frames instead of 2 in the Nightmare fight),
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

### An uninitialized variable in the original

`ProjectileContactDamageHitSprite` never sets `isft` when Samus's contact
damage (Screw Attack, Speed Booster, Shinespark) destroys a sprite. The
original then compares the sprite's stun flash timer with, and stores the low
byte of, whatever its register (`r10`) still holds from the caller: in the
original `ProjectileCheckHittingSprite`, the left edge of the sprite's hitbox
(`o2Left`). The optimized caller keeps something else there, so in the first
`OPTIMIZE=1` builds a sprite killed by the Screw Attack got another
`invincibilityStunFlashTimer` (seen when Samus fell screw attacking onto a
Sidehopper, Geruta or Waver: 0x07 instead of 0xe4), and every frame after
differed. With `OPTIMIZE` defined the function now sets `isft` to that value
explicitly (8 bytes of code). The optimized build is then identical at every
logic-frame boundary in the 73 scenarios of the scenario library (bosses,
weapons, abilities, environments, menus, transitions) as well as the fights;
the cycle counts above did not change (the fix only runs when such a kill
happens).

## Limitations

- **Emulator timing.** All the cycle counts and lag frames come from mGBA
  0.10.2, which emulates the wait states and the prefetch buffer but is not
  cycle-exact. If real hardware is a few percent slower, the original's
  Nightmare frames (19 of them above 95% in one fight) lag noticeably more
  often there; the optimized build keeps a margin of about 20% of the frame.
- **Scripted play.** The fights are played by a simple policy, with some
  health taken by RAM writes; a human hits more often and causes more
  explosions and particles. The nonstop-shooting scenarios are the closest to
  the worst case measured here.
- The profiler does not time H-blank handlers: in a cutscene whose H-blank
  handler runs on every line, the extra cycles starve the main loop.

## Building and measuring

```sh
make PROFILE=1      # mf_us_profile.gba: frame totals in gProfile
make PROFILE=2      # mf_us_profile2.gba: every subsystem and sprite slot
make OPTIMIZE=1     # mf_us_opt.gba: PROJ_HIT and DRAW_ORDER
make OPTIMIZE="PROJ_HIT DRAW_ORDER IWRAM"
make PROFILE=1 OPTIMIZE=1   # mf_us_profile_opt.gba
make check          # the normal build, which these flags do not change
```

The objects of C files depend on the variant flags (`.build_flags`), so
switching between the normal build and a variant rebuilds them (about 15
seconds).

From Python, with the emulator harness: `lag.LogicStepper` to drive a build,
`lag.ProfileReader(emu)` to read `gProfile.last` at each boundary (field names
come from `enum ProfileRegion` in `include/profile.h`).
