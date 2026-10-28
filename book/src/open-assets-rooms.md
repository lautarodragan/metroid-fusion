# Rooms of the generated test baserom

The generated test baserom ([research notes](test-baserom-research.md),
[emulator tests](emu-tests.md)) fills every room with placeholder data. To
make the emulator tests and their screenshots meaningful, the rooms use a
small **semantic tileset**: what Samus collides with looks like it, so a
person reading a screenshot can tell floors, walls, platforms, ladders,
doors, breakable blocks and background apart. The first three rooms a new
game reaches have hand-made layouts; every other room is a generated box.

Code:

| File | What it does |
| --- | --- |
| `tools/open_assets/tiles.py` | Draws the tileset (pixel art made in code), its palette and metatile table, the common tiles (hatches, revealed blocks, tanks), the far background (BG3) and writes them to every tileset slot. |
| `tools/open_assets/rooms.py` | Reads the maps, picks the metatile of each block from its collision type and its neighbours, encodes the layers (room RLE) and checks them against the slot sizes; draws a box for every other room. |
| `tools/open_assets/maps/*.txt` | The hand-made rooms. |

`make_open_baserom.py` calls `tiles.apply_tilesets` and `rooms.apply_rooms`
after its own generators, so these replace the generic placeholders.

## The first three rooms

A new game starts in Main Deck room 0: `SaveFileMiscResetNewFile`
(`src/save_file_misc.c`) sets area 0, room 0, door 0 and places Samus from
door 0 (block 25, 7.5). The door table (`sMainDeckDoors` in
`src/data/rooms_data.c`) gives the rest:

| Room | Map | Size | Doors used | What it is |
| --- | --- | --- | --- | --- |
| Main Deck 0 | `main_deck_00.txt` | 34x14 | 1 (left, open hatch) -> room 3 | Docking bay: landing platform under the start position, one exit on the left. |
| Main Deck 3 | `main_deck_03.txt` | 34x14 | 2 (right) <- room 0; 7 (upper left, open hatch) -> room 6 | Corridor: lower floor on the right, a one block step and a ledge up to the left door. The upper back wall is open and shows the far background. |
| Main Deck 6 | `main_deck_06.txt` | 19x44 | 8 (bottom right, lockable hatch) <- room 3; also 10, 12, 13, 15, 17 | Shaft: girder platforms up to the ledges in front of the six doors. |

Every platform and ledge of room 6 can be reached with a normal jump
(about 4.4 blocks high): checked in the emulator, from the arrival floor up
to the top ledge and out through door 17. The other rooms behind doors 10,
12, 13, 15 and 17 are generated boxes, so Samus can enter them but not
leave.

The doors only work where the map agrees with the door table: the door
transition blocks (`D`) must cover the door's `xStart..xEnd`,
`yStart..yEnd` rectangle (at least the rows Samus touches), the floor in
front of a door is at row `yEnd + 1`, where the game places Samus on
arrival, and room sizes come from C (`src/data/rooms/**`). The camera hides
the outer two rows and columns of every room.

### Byte budgets

The layers live in the baserom at the original offsets and sizes, which
the C arrays fix (`sMainDeck_0_Clipdata[56]`, ...), so a map must encode
within the slot. `rooms.py` fails with the layer and its size when it does
not. Current use:

| Room | Clipdata | BG1 | BG2 |
| --- | --- | --- | --- |
| 0 | 54/54 | 94/100 | 100/374 |
| 3 | 58/58 | 102/251 | 108/176 |
| 6 | 230/231 | 350/552 | 36/146 |

The clipdata slots of rooms 0 and 3 are full: each row with an opening
costs two runs (2 bytes each), a door block or a platform one or two more.
Rows of identical blocks are almost free, so background bands are drawn
as full-width rows (BG2 behind solid blocks is never visible anyway).

## Map format

```
; comment
area: MainDeck          # symbol prefix of the room's layers (sMainDeck_0_Bg1, ...)
room: 0
size: 34x14             # must match the room in C

[fg]
<height rows of width characters: collision and look>

[bg]
<height rows of width characters: the BG2 background layer>
```

### Foreground legend (`[fg]`, BG1 + clipdata)

| Char | Clipdata | Look |
| --- | --- | --- |
| `.` | `CLIPDATA_AIR` | nothing (background shows) |
| `#` | `CLIPDATA_SOLID` | steel plates; the sides facing open space are lit: floors (open above) get a bright walkway with an amber hazard stripe, ceilings (open below) a dark underside with cyan lamps, walls a bright edge |
| `=` | `CLIPDATA_PASS_THROUGH_BOTTOM` | amber girder, open below: jump up through it, stand on it |
| `T` | `CLIPDATA_CEILING_RUNGS` | ceiling plate with yellow bars to hang from |
| `D` | `CLIPDATA_DOOR_TRANSITION` | dark doorway with a chevron pointing out of the room |
| `O` | `CLIPDATA_AIR` | cyan door jamb (an always open hatch); next to `D` |
| `G` | `CLIPDATA_GRAY_DOOR` | lockable hatch: drawn by the game from the common tiles (see below), open on arrival |
| `s` | `CLIPDATA_SHOT_BLOCK_REFORM` | rust plate with cracks |
| `b` | `CLIPDATA_BOMB_BLOCK_REFORM` | rust plate with a bomb |
| `m` | `CLIPDATA_MISSILE_BLOCK_NEVER_REFORM` | rust plate with a missile |
| `p` | `CLIPDATA_POWER_BOMB_BLOCK_NEVER_REFORM` | rust plate with a ring |
| `>` | `CLIPDATA_SPEEDBOOST_BLOCK_REFORM` | rust plate with chevrons |
| `*` | `CLIPDATA_SCREW_ATTACK_NO_REFORM` | rust plate with a star |
| `c` | `CLIPDATA_CRUMBLE` | loose rubble |
| `~` / `w` | `CLIPDATA_WATER` | water surface / water |

`D` points left in the left half of the room and right in the right half;
`O` picks its top, middle and bottom pieces from the `O` above and below.
For `#`, the blocks `#`, `T` and the breakables count as wall, everything
else as open space. The clipdata values are read from
`include/constants/clipdata.h`, so they follow the enum.

Slopes and wall ladders are not in the legend yet (their orientation in
the clipdata enum has not been checked in the emulator).

### Background legend (`[bg]`, BG2)

| Char | Look |
| --- | --- |
| `.` | nothing: the far background (BG3) shows through |
| `p` | dark panel |
| `v` | vent grille |
| `-` `\|` `+` | pipe: horizontal, vertical, junction |
| `L` | light strip |
| `w` | window frame (open in the middle) |
| `g` | girder column |

## The tileset

One tileset (45 metatiles, 85 tiles) goes into all 63 tileset slots, so the
same metatile index means the same thing in every room; index 0 is air and
1-16 are the solid block for each combination of open sides (`1 + mask`,
N=1, E=2, S=4, W=8). The regions differ in size: metatile tables are
padded with air, and the one tileset graphics slot too small for the full
art (`sTileset_2_Gfx`, 924 bytes) gets a flat-shaded version with the same
tile slots.

Palette rows (hardware numbering; the tileset palette is loaded to rows
2-15, then the common palette to rows 0-2, and animated palettes overwrite
row 15):

| Row | Use |
| --- | --- |
| 0-2 | common tiles: blocks; hatch frames and colours (row 1, colours 6-10 = security levels 0-4, cycled by `RoomUpdateHatchFlashingAnimation`); locked hatch lights (row 2, colours 13-15) |
| 3 | steel structure (walls, floors, ceilings, ladders) |
| 4 | girder platforms |
| 5 | doorways and jambs |
| 6 | breakable blocks |
| 7 | water |
| 8 | background panels (BG2) |
| 9 | far background (BG3) |

Foreground blocks are bright and saturated, BG2 is dark and desaturated
and BG3 darker still, so the layers separate at a glance.

### Common tiles (hatches, revealed blocks, tanks)

`sCommonTilesGfx` (tiles 64-191), `sCommonTilemap` (indexed by
`enum ClipdataTilemap`) and `sCommonTilesPal` are what the game draws
hatches, revealed or reforming blocks and tanks with. Hatches are colour
coded by security level: white (0), blue (1), green (2), yellow (3), red
(4); lockable hatches are grey with purple lights, and all of them have a
four frame opening animation. Tiles 80-95 are the three tank animations
(`sAnimatedTankGfx`). `sHatchFlashingPal` and `sUnlockedHatchFlashingPal`
pulse the hatch colours and blink the lock lights.

### Far background (BG3)

Eight tiles of an abstract circuit pattern in every `sTileset_*_Bg_Gfx`
slot, and every room BG3 map (`s*Bg3*`) repeats a 64x64 pixel motif of
them (a plain grid where the slot is too small). Room BG0 overlay maps
(LZ77) are made transparent.

## Generated rooms

Every room without a map gets a box: solid border two blocks thick (one for
tiny rooms), autotiled like `#`, air inside, an empty BG2. Where the slot is
too small for that, plain solid blocks, and as a last resort an empty
layer. There are no door blocks, so these rooms can be entered but not
left.

## Sprites in these rooms

The rooms' sprite data is in C, but which sprite a spriteset slot means
comes from the spriteset tables (`sSpriteset<N>`, blobs filled by the
generator), which the sprite work has to provide:

| Room | Spriteset in use at the start | Sprites |
| --- | --- | --- |
| Main Deck 0 | 8 (`defaultSpriteset`) | slot 0 at block (25, 10), `SSP_UNINFECTED_OR_BOSS`: the gunship (`PSPRITE_GUNSHIP`, which spawns `SSPRITE_GUNSHIP_PART`). Samus starts standing on it. |
| Main Deck 3 | 0, no sprites (`sMainDeck_3_Spriteset0` is empty) | none |
| Main Deck 6 | 0, no sprites until `EVENT_ENTERED_SHIP` | later: spriteset 30 (slot 2 at (11, 30), X parasite-absorbable slot 5 at (9, 35)), then spriteset 61 (slot 2 at (10, 24)) |

The gunship clears `gDisableDrawingSamusAndScrollingFlag` when Samus steps
out; until it exists, Samus is not drawn and the camera does not follow
her. The room walk in the emulator tests clears the flag itself (see
`ROOM_WALK` in `tests/emu/scenario.py`), so its screenshots show Samus and
a camera that scrolls. The HUD and Samus' beams are drawn in
these rooms too.

The minimap is not covered here.
