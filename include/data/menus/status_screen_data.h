#ifndef STATUS_SCREEN_DATA_H
#define STATUS_SCREEN_DATA_H

#include "types.h"

// Defined in src/data/menus/pause_screen_misc_data.c

// Destination tilemap info for each status screen section
extern const u8 sStatusScreenSectionDstInfo[][5];
// Source tilemap info for each item section
extern const u8 sStatusScreenItemSrcInfo[][5];
// Tilemap info for the ammo headers
extern const u8 sStatusScreenAmmoHeaderInfo[][4];

#define STATUS_SCREEN_DST_TOP(section) (sStatusScreenSectionDstInfo[(section)][0])
#define STATUS_SCREEN_DST_LEFT(section) (sStatusScreenSectionDstInfo[(section)][2])
#define STATUS_SCREEN_DST_RIGHT(section) (sStatusScreenSectionDstInfo[(section)][3])

#define STATUS_SCREEN_SRC_TOP(section) (sStatusScreenItemSrcInfo[(section)][0])
#define STATUS_SCREEN_SRC_BOTTOM(section) (sStatusScreenItemSrcInfo[(section)][1])
#define STATUS_SCREEN_SRC_LEFT(section) (sStatusScreenItemSrcInfo[(section)][2])

#define STATUS_SCREEN_HEADER_TOP(header) (sStatusScreenAmmoHeaderInfo[(header)][0])
#define STATUS_SCREEN_HEADER_LEFT(header) (sStatusScreenAmmoHeaderInfo[(header)][2])
#define STATUS_SCREEN_HEADER_RIGHT(header) (sStatusScreenAmmoHeaderInfo[(header)][3])

// Defined in src/menus/pause_screen.c
extern const u8* sPauseDebugItemFlagsPointers[5];

#endif /* STATUS_SCREEN_DATA_H */
