#ifndef SRAM_DATA_H
#define SRAM_DATA_H

#include "types.h"
#include "globals.h"

#include "structs/menus/boot_debug.h"

// Defined in src/data/menus/pause_screen_misc_data.c

// Data written to SRAM to test it
extern const u8 sSramTestData[16];
// "SAVE END" string at the end of a save file
extern const u8 sSaveFileEndMagic[8];
// Magic string at the start of a save file
extern const u8 sSaveFileMagic[72];
// Magic string of the SRAM header
extern const u8 sSramHeaderMagic[20];

// Defined in src/data/sram_pointers.c

// Magic strings of the most recent save file data
extern const u8 sMostRecentSaveFileMagic[2][16];
// Magic strings of the language data
extern const u8 sLanguageDataMagic[2][16];

// Button assignments used for demos
extern const struct ButtonAssignments sDefaultButtonAssignments[];
// Default in game timer
extern const struct InGameTime sDefaultInGameTime[];
// Boot debug options used for demos
extern const struct BootDebugOptions sDefaultBootDebugOptions[];

#endif /* SRAM_DATA_H */
