#include "data/sram_pointers.h"
#include "gba/memory.h"
#include "structs/save_file.h"
#include "macros.h"

const void* const sSaveDataEwramPointers[3] = {
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 0,
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 2,
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 4
};

const void* const sSaveDataEwramBackupPointers[3] = {
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 1,
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 3,
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 5
};

const void* const sUnk_582274[3] = {
    EWRAM_SRAM + 0x500 + sizeof(struct SaveFile) * 0,
    EWRAM_SRAM + 0x500 + sizeof(struct SaveFile) * 2,
    EWRAM_SRAM + 0x500 + sizeof(struct SaveFile) * 4
};

const void* const sUnk_582280[2] = {
    EWRAM_SRAM + 0x7040,
    EWRAM_SRAM + 0x7080
};

const u8 sMostRecentSaveFileMagic[2][16] = INCBIN_U8("data/sram/most_recent_save_file_magic.bin");
const u8 sLanguageDataMagic[2][16] = INCBIN_U8("data/sram/language_data_magic.bin");
// The first 8 bytes are the struct ButtonAssignments that is used
const u16 sDefaultButtonAssignments[6] = INCBIN_U16("data/sram/default_button_assignments.bin");
// The first 4 bytes are the struct InGameTime that is used
const u8 sDefaultInGameTime[16] = INCBIN_U8("data/sram/default_in_game_time.bin");
// struct BootDebugOptions
const u8 sDefaultBootDebugOptions[12] = INCBIN_U8("data/sram/default_boot_debug_options.bin");
const u16 sEraseSramObjPal[7 * 16] = INCBIN_U16("data/menus/erase_sram/obj.pal");
const u16 sEraseSramBgPal[16 * 16] = INCBIN_U16("data/menus/erase_sram/bg.pal");
// Not referenced by code (the erase SRAM OAM frames are in src/text.c)
static const u8 sBlob_5825d0_582bbc[] = INCBIN_U8("data/Blob_5825d0_582bbc.bin");
const u32 sEraseSramObjGfx[532] = INCBIN_U32("data/menus/erase_sram/obj.gfx.lz");
const u32 sEraseSramBgGfx[7670] = INCBIN_U32("data/menus/erase_sram/bg.gfx.lz");
const u32 sEraseSramTilemap_D000[131] = INCBIN_U32("data/menus/erase_sram/bg_d000.tm.lz");
const u32 sEraseSramTilemap_F000[368] = INCBIN_U32("data/menus/erase_sram/bg_f000.tm.lz");
const u8 sEraseSramCursorOamIds[4] = INCBIN_U8("data/menus/erase_sram/cursor_oam_ids.bin");
const u16 sEraseSramSounds[5] = INCBIN_U16("data/menus/erase_sram/sounds.bin");
const u8 sEraseSramCursorBasePositions[2][2] = INCBIN_U8("data/menus/erase_sram/cursor_base_positions.bin");
const u8 sEraseSramCursorOffsets[5][2] = INCBIN_U8("data/menus/erase_sram/cursor_offsets.bin");
