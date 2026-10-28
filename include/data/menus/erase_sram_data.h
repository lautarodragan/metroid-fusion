#ifndef ERASE_SRAM_DATA_H
#define ERASE_SRAM_DATA_H

#include "types.h"
#include "oam.h"

// Defined in src/data/sram_pointers.c

// Object palette
extern const u16 sEraseSramObjPal[7 * 16];
// Background palette
extern const u16 sEraseSramBgPal[16 * 16];
// Object graphics
extern const u32 sEraseSramObjGfx[532];
// Background graphics
extern const u32 sEraseSramBgGfx[7670];
// Tilemaps
extern const u32 sEraseSramTilemap_D000[131];
extern const u32 sEraseSramTilemap_F000[368];
// Cursor OAM ids for each option
extern const u8 sEraseSramCursorOamIds[4];
// Sounds
extern const u16 sEraseSramSounds[5];
// Base positions of the cursor (x, y)
extern const u8 sEraseSramCursorBasePositions[2][2];
// Offsets of the cursor for each option (x, y)
extern const u8 sEraseSramCursorOffsets[5][2];

// Defined in src/text.c

// Text graphics for each language
extern const u32* const sEraseSramTextGfxPointers[][2];
// OAM frame data pointers
extern const struct FrameData* const sEraseSramOam[];

#endif /* ERASE_SRAM_DATA_H */
