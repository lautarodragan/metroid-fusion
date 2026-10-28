# Placeholder sprites in the open base ROM

The open base ROM (`tools/open_assets/`, see
[Generated test baserom](test_baserom_research.md)) is a test fixture: its
data only has to make the emulator tests and their screenshots meaningful.
This page describes the placeholder **sprite** graphics: Samus, the HUD,
projectiles, effects and enemies/objects. Rooms, tilesets and text are
generated elsewhere.

The goal is readability, not looks: a screenshot should show *what is
going on* (Samus' pose, where she aims, a shot, an explosion, an enemy).

| Module | What it draws |
| --- | --- |
| `oam_art.py` | Shared helpers: parser for the OAM data in C, drawing canvas, tile cutting, palettes, PNG debug views |
| `samus_gfx.py` | Samus (body, legs, arm cannon), SA-X, all their palettes |
| `hud_gfx.py` | Energy digits and tanks, ammo digits, weapon icons, minimap frame, escape timer |
| `sprite_gfx.py` | Common sprite sheet (effects, missile parts, bombs, X parasites, HUD tiles), beams and missiles, every sprite in `src/data/sprites/`, spritesets |

`make_open_baserom.py` calls `samus_gfx.apply`, `hud_gfx.apply` and
`sprite_gfx.apply` after its own placeholders.

## How the pictures are made: draw, then cut through the OAM frames

Sprite graphics in the base ROM are plain 4bpp tile blocks. Which tile is
shown where is decided by the OAM frames defined in C
(`OAM_ENTRY(x, y, dims, flip, tile, palette, priority)`, grouped into
`struct FrameData` animations). Every generator therefore:

1. takes an OAM frame and the name of the animation it belongs to (and its
   frame number);
2. draws a picture on a canvas in object coordinates (origin = the object's
   position), fitted to the area the frame's pieces cover;
3. *cuts* the canvas through the frame: each pixel covered by an entry is
   copied into the tile (and pixel, honouring flips) that entry displays
   there, in a sheet addressed like OBJ VRAM (2D mapping, 32 tiles per row);
4. copies the tiles that belong to each base ROM region out of the sheet.

Tiles are often shared by several frames; the first frame that paints a
tile keeps it (the order is chosen so the most representative frame comes
first).

Debug views (no emulator needed):

```sh
python3 tools/open_assets/samus_gfx.py --preview out.png --anim 'Running_.*_Right' --anim Spinning
python3 tools/open_assets/sprite_gfx.py --sheet common.png
python3 tools/open_assets/sprite_gfx.py --sprite hornoad --sprite save_pad --out DIR   # DIR/<name>_frames.png
```

## Samus

Samus' graphics are streamed every frame (`TransferSamusGraphics` in
`src/in_game.c`). Each animation frame (`struct SamusAnimData` in
`src/data/samus/samus_graphics.c`) names:

- a **top** block (body): `n1` tiles copied to OBJ tile 0 (first tile row)
  and `n2` tiles to tile 32 (second row); `n1, n2` are the two bytes before
  the `INCBIN` in C;
- a **bottom** block (legs): the same, at tiles 20 and 52;
- an OAM frame placing 8x8..32x32 pieces of those two rows.

The arm cannon is separate: the arm cannon direction picks a 6x2 tile block
(`sArmCannonGfxPointers_*[acd]`, tile rows 2-3) and the arm cannon animation
(`struct ArmCannonAnimData`, paired with Samus' animation through the
`sSamusAnimPointers_*` / `sArmCannonAnimPointers_*` tables) places three
16x16 pieces of it.

For every animation frame `samus_gfx.py`:

- works out the pose from the animation name: pose (`Running`, `Spinning`,
  `MorphBall`, `Crouching`, `MidAir`, `HangingOnLedge`, `FacingForeground`...),
  aim (`Forward`, `Up`, `DiagonalUp`, `DiagonalDown`, `Down`, `None`) and
  side (`Left`/`Right`);
- fits a skeleton to the pieces: head at the top of the body pieces, feet at
  the bottom of the leg pieces, hips at "head + torso" (22 px) below the top
  so legs shorten when crouching or tucking; running swings the legs with
  the frame number; jumping raises the front knee; the figure leans with
  running, skidding and shinesparking;
- draws a side view (helmet with visor on the facing side, shoulder pads,
  belt, knee pads, boots, back arm), a front/back view (save/navigation/
  recharge pads, turning, elevator, ladders, dying...), a tucked spinning
  figure rotating with the frame number (spin jump, space jump, screw
  attack, wall jump) or a ball with a rotating seam (morph ball);
- leaves the cannon arm out when the frame has arm cannon pieces, otherwise
  draws it on the body (pointing down when not aiming).

Each block is drawn from the frame that shows the most of its tiles,
preferring animations named like the block (blocks are reused by other
poses). The arm cannon blocks are drawn once per direction as a cannon
from the figure's shoulder (median over the frames that use the layout)
along the aim direction, as far as the three pieces reach; the "armed"
blocks (missiles selected) have an open, glowing muzzle.

SA-X uses one block per frame (top row at OBJ tile 512, bottom at 544) and
the same drawing with the arm cannon on the body and a grey/red palette.

### Palettes

All Samus palettes share one layout (`samus_gfx.py`, `OUTLINE`, `SUIT_*`,
`ACC_*`, `VIS_*`, `MET_*`, `GLOW`, `WHITE`): outline, three suit shades,
three armour plate shades, three visor shades, three metal shades (arm
cannon), glow and white. Suits differ by colour (Fusion: blue with amber
plates, Varia: orange, Gravity: purple, SA-X: grey with red); the effect
palettes are tints of the suit palette: flashing (white), screw attack
(green), speed booster (blue), freeze (cyan), death fade (towards white,
row by row), charge beam pulses (per beam colour), save/load fades.

## HUD

See the docstring of `hud_gfx.py` for where each block goes. In short: the
energy counter (two 32x16 sprites) shows a 3x5 pixel "ENERGY" label, an
energy cell icon, two 5x7 digits and the tank rows (two tank slots per
tile, empty = grey outline, full = blue); missiles and power bombs have
16x8 icons (normal and selected) and 4 pixel wide digits; the minimap gets
a frame on its static top row and right column and a blinking marker.

`src/hud.c` only copies an energy digit when it changes, starting from
9999, so a new game (99 energy) never copies "99": the common sheet itself
holds "99" at those tiles.

## Common sprite sheet, projectiles and effects

`sCommonSpritesGfx` (OBJ tiles 64-511) is shared by particles, projectile
parts, X parasites and the HUD. Its frames come from
`src/data/particle_data.c`, `src/data/projectile_data.c` and any sprite
frame that uses those tiles; the HUD tiles are placed first. What is
drawn depends on the animation name:

| Name contains | Picture |
| --- | --- |
| `Beam` | an energy bolt along the frame's direction (unflipped projectiles move left, up-left or up): bigger when charged, two/three lanes for wide/double, a wave for the wave beam, a crystal for ice |
| `Missile` | a missile pointing in its direction: body, coloured nose, fins, exhaust (ice = blue, diffusion = green); tumbling rotates it |
| `Bomb`, `PowerBomb` | a ball with a blinking core |
| `Explosion`, `Killed`, `Hit`, `Fire` | a spiky burst that grows and breaks up with the frame number (ice: blue) |
| `Smoke`, `Dust`, `Cloud`, `Debris` | grey puffs |
| `Water`, `Splash`, `Drop`, `Bubble` | blue drops and bubbles |
| `XParasite`, `Absorb`, `XTrail` | an X parasite: wobbling membrane with a bright nucleus (green for health X, blue for missile/ice X) |
| `Trail`, anything else | sparkles |

Beams have their own blocks (two rows of 20 tiles at OBJ tile row 4, loaded
when the beam is equipped) and palettes (only colours 0-4 are loaded, so
the beam colour ramp lives there); missiles have 4x2 tile blocks at column
28. The effects palette layout is shared by all of them (`oam_art.FX_*`):
energy ramp (per palette row: yellow, orange, cyan, green, green, magenta),
black, blue, green and grey ramps, white.

## Sprites (enemies, pads, objects)

Each `sXxxGfx` in `src/data/sprites/*.c` is drawn from the frames of the
same file (tiles 512 + 64 * slot; frames are written for slot 0):

- **pads and machines** (`*pad*`, stabilizers, elevator): a base with a
  glowing plate, and a console/arch when the frame is tall; the glow colour
  tells the pad type (save: green, recharge: cyan, navigation: amber, data:
  violet, security: red);
- **gunship**: hull, canopy, wings and engine lights (and a glow for its
  beam parts);
- **gates and hatches**: a metal bar with blinking lights;
- **X parasites and core X**: the X picture above;
- **any other sprite**: a creature made of one rounded plate per OAM piece,
  an eye on the front-most top piece (sprites face left when not flipped)
  and the lowest pieces in a secondary colour (legs, shell, base). Frames
  reuse the same tiles in different arrangements (a head piece moves, a leg
  is flipped), so pictures that span several pieces would come out cut in
  the wrong places; self-contained plates always make a consistent cluster.

Sprite palettes follow the creature layout (`sprite_gfx.CR_*`): outline,
body ramp, secondary ramp, eye white and pupil, glow ramp, grey ramp; the
hue comes from a hash of the sprite's name, so different enemies get
different colours.

## Data that had to be filled in for Samus to show up

- **Spriteset 8** (`sSpriteset8`, the first room's spriteset, a blob in
  `src/data/sprite_data.c`) lists the gunship (`PSPRITE_GUNSHIP`, slot 0). A
  new game starts with `gDisableDrawingSamusAndScrollingFlag` set; only the
  gunship's AI clears it, so without it Samus was never drawn. Other
  spritesets are still empty (`sprite_gfx.SPRITESETS`).
- **Empty room tiles are transparent**: metatile 0 points to BG tile 0,
  which `AnimatedGraphicsLoad` fills from the first animated tiles entry,
  and the empty BG0 uses the first common tile; both are cleared
  (`EMPTY_BG_TILES` in `make_open_baserom.py`). Opaque, they covered all
  sprites (BG0/BG1 have a higher priority than Samus).
- **Button assignments** of a new file (`sSramUnk_5822c8`): R arms
  missiles, L aims diagonally, SELECT swaps, START pauses (they were zero).

## Tests

`tests/emu/test_sprites.py` (see [Emulator tests](emu_tests.md)) checks that
Samus' sprites are on screen and visible, compares 9 scripted poses with
`tests/emu/reference/samus_<pose>.png` (rendered from OAM + OBJ VRAM + OBJ
palettes by `tests/emu/oam_view.py`, so the room and camera don't matter),
requires the poses to differ, and checks the beam sprite and the energy
counter. After an intended change, refresh the references with
`tests/run_emu_tests.sh --update-references` and look at them.

## Known limitations

- Pictures are fitted per frame, so a few frames that reuse tiles in an
  unusual arrangement look odd (for example one running frame places the
  arm cannon pieces differently and the barrel disappears).
- Only spriteset 8 is filled; enemies only appear in rooms whose
  spritesets list them.
- New games start without missiles, so missile graphics are only checked
  with the debug views, not in the emulator tests.
- Creature drawings are generic; specific enemies of the first playable
  rooms can get dedicated drawings in `sprite_gfx.draw_sprite_frame`.
