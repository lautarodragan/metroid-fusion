#ifndef GAME_OVER_DATA_H
#define GAME_OVER_DATA_H

#include "types.h"
#include "oam.h"
#include "gba/memory.h"

// Defined in src/data/sa_x_close_up.c

extern const u8 sGameOverOamXFlipOffsets[3][4];
extern const u32 sGameOverBgGfx[5651];
extern const u32 sGameOverObjGfx[184];
extern const struct FrameData sGameOverCursorOverlayOam[];
extern const u16 sGameOverBgPal[16 * PAL_ROW];
extern const u16 sGameOverObjPal[16 * PAL_ROW];
extern const u32 sGameOverBg3Tilemap[369];
extern const u32 sGameOverBg1Tilemap[193];

// Defined in src/new_file_intro.c

extern const struct FrameData* const sGameOverCursorOam[3];
extern const u8* const sGameOverTextGfxPointers[7];

#endif /* GAME_OVER_DATA_H */
