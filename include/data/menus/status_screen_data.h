#ifndef STATUS_SCREEN_DATA_H
#define STATUS_SCREEN_DATA_H

#include "types.h"

// Defined in src/data/menus/pause_screen_misc_data.c

// Destination tilemap info for each status screen section
extern const u8 sStatusScreenUnk_58217c[][5];
// Source tilemap info for each item section
extern const u8 sStatusScreenUnk_5821b3[][5];
// Tilemap info for the ammo headers
extern const u8 sStatusScreenUnk_5821d6[][4];

#define STATUS_SCREEN_DST_TOP(section) (sStatusScreenUnk_58217c[(section)][0])
#define STATUS_SCREEN_DST_LEFT(section) (sStatusScreenUnk_58217c[(section)][2])
#define STATUS_SCREEN_DST_RIGHT(section) (sStatusScreenUnk_58217c[(section)][3])

#define STATUS_SCREEN_SRC_TOP(section) (sStatusScreenUnk_5821b3[(section)][0])
#define STATUS_SCREEN_SRC_BOTTOM(section) (sStatusScreenUnk_5821b3[(section)][1])
#define STATUS_SCREEN_SRC_LEFT(section) (sStatusScreenUnk_5821b3[(section)][2])

#define STATUS_SCREEN_HEADER_TOP(header) (sStatusScreenUnk_5821d6[(header)][0])
#define STATUS_SCREEN_HEADER_LEFT(header) (sStatusScreenUnk_5821d6[(header)][2])
#define STATUS_SCREEN_HEADER_RIGHT(header) (sStatusScreenUnk_5821d6[(header)][3])

// Defined in src/menus/pause_screen.c
extern const u8* sPauseDebugItemFlagsPointers[5];

#endif /* STATUS_SCREEN_DATA_H */
