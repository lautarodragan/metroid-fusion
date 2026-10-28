#ifndef ERASE_SRAM_DATA_H
#define ERASE_SRAM_DATA_H

#include "types.h"
#include "oam.h"

// Defined in src/data/sram_pointers.c

// Object palette
extern const u8 sEraseSramUnk_5822f0[];
// Background palette
extern const u8 sEraseSramUnk_5823d0[];
// Object graphics
extern const u8 sEraseSramUnk_582bbc[];
// Background graphics
extern const u8 sEraseSramUnk_58340c[];
// Tilemaps
extern const u8 sEraseSramUnk_58abe4[];
extern const u8 sEraseSramUnk_58adf0[];
// Cursor OAM ids for each option
extern const u8 sEraseSramUnk_58b3b0[4];
// Sounds
extern const u16 sEraseSramUnk_58b3b4[5];
// Base positions of the cursor (x, y)
extern const u8 sEraseSramUnk_58b3be[2][2];
// Offsets of the cursor for each option (x, y)
extern const u8 sEraseSramUnk_58b3c2[4][2];

// Defined in src/text.c

// Text graphics for each language
extern const u32* const sEraseSramUnk_79c228[][2];
// OAM frame data pointers
extern const struct FrameData* const sEraseSramUnk_79c260[];

#endif /* ERASE_SRAM_DATA_H */
