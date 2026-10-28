#ifndef SRAM_DATA_H
#define SRAM_DATA_H

#include "types.h"

// Defined in src/data/menus/pause_screen_misc_data.c

// Data written to SRAM to test it
extern const u8 sSramUnk_5821e8[];
// "SAVE END" string at the end of a save file
extern const u8 sSramUnk_5821f8[];
// Magic string at the start of a save file
extern const u8 sSramUnk_582200[];
// Magic string of the SRAM header
extern const u8 sSramUnk_582248[];

#endif /* SRAM_DATA_H */
