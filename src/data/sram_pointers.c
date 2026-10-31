#include "data/sram_pointers.h"
#include "gba/memory.h"
#include "structs/save_file.h"
#include "macros.h"
#include "oam.h"

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

const void* const sWorldDataEwramPointers[3] = {
    EWRAM_SRAM + 0x500 + sizeof(struct SaveFile) * 0,
    EWRAM_SRAM + 0x500 + sizeof(struct SaveFile) * 2,
    EWRAM_SRAM + 0x500 + sizeof(struct SaveFile) * 4
};

const void* const sLanguageDataEwramPointers[2] = {
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
// OAM frame with 22 parts, not referenced by code (no FrameData array uses it)
const u16 sOamFrame_5825d0[OAM_DATA_SIZE(22)] = INCBIN_U16("data/oam_frames/5825d0.bin");
// OAM frames of the erase SRAM FrameData arrays below (used through sEraseSramOam)
const u16 sOamFrame_582656[] = INCBIN_U16("data/oam_frames/582656.bin");
const u16 sOamFrame_582706[] = INCBIN_U16("data/oam_frames/582706.bin");
const u16 sOamFrame_5827b6[] = INCBIN_U16("data/oam_frames/5827b6.bin");
const u16 sOamFrame_5827ca[] = INCBIN_U16("data/oam_frames/5827ca.bin");
const u16 sOamFrame_5827de[] = INCBIN_U16("data/oam_frames/5827de.bin");
const u16 sOamFrame_5827f2[] = INCBIN_U16("data/oam_frames/5827f2.bin");
const u16 sOamFrame_582806[] = INCBIN_U16("data/oam_frames/582806.bin");
const u16 sOamFrame_58281a[] = INCBIN_U16("data/oam_frames/58281a.bin");
const u16 sOamFrame_58282e[] = INCBIN_U16("data/oam_frames/58282e.bin");
const u16 sOamFrame_582842[] = INCBIN_U16("data/oam_frames/582842.bin");
const u16 sOamFrame_582856[] = INCBIN_U16("data/oam_frames/582856.bin");
const u16 sOamFrame_58286a[] = INCBIN_U16("data/oam_frames/58286a.bin");
const u16 sOamFrame_582878[] = INCBIN_U16("data/oam_frames/582878.bin");
const u16 sOamFrame_582892[] = INCBIN_U16("data/oam_frames/582892.bin");
const u16 sOamFrame_5828ac[] = INCBIN_U16("data/oam_frames/5828ac.bin");
const u16 sOamFrame_5828c0[] = INCBIN_U16("data/oam_frames/5828c0.bin");
const u16 sOamFrame_5828d4[] = INCBIN_U16("data/oam_frames/5828d4.bin");
const u16 sOamFrame_5828e8[] = INCBIN_U16("data/oam_frames/5828e8.bin");
const u16 sOamFrame_5828fc[] = INCBIN_U16("data/oam_frames/5828fc.bin");
const u16 sOamFrame_582910[] = INCBIN_U16("data/oam_frames/582910.bin");
const u16 sOamFrame_582924[] = INCBIN_U16("data/oam_frames/582924.bin");
const u16 sOamFrame_582938[] = INCBIN_U16("data/oam_frames/582938.bin");
const u16 sOamFrame_58294c[] = INCBIN_U16("data/oam_frames/58294c.bin");
const u16 sOamFrame_582960[] = INCBIN_U16("data/oam_frames/582960.bin");
const u16 sOamFrame_582974[] = INCBIN_U16("data/oam_frames/582974.bin");
const u16 sOamFrame_582988[] = INCBIN_U16("data/oam_frames/582988.bin");
const u16 sOamFrame_58299c[] = INCBIN_U16("data/oam_frames/58299c.bin");
const u16 sOamFrame_5829b0[] = INCBIN_U16("data/oam_frames/5829b0.bin");
const u16 sOamFrame_5829c4[] = INCBIN_U16("data/oam_frames/5829c4.bin");
const u16 sOamFrame_5829d8[] = INCBIN_U16("data/oam_frames/5829d8.bin");
const u16 sOamFrame_5829ec[] = INCBIN_U16("data/oam_frames/5829ec.bin");
const u16 sOamFrame_582a00[] = INCBIN_U16("data/oam_frames/582a00.bin");
const u16 sOamFrame_582a14[] = INCBIN_U16("data/oam_frames/582a14.bin");
const u16 sOamFrame_582a28[] = INCBIN_U16("data/oam_frames/582a28.bin");
const struct FrameData sEraseSramOam_582a3c[29] = {
    { sOamFrame_5828fc, 4 },
    { sOamFrame_582910, 4 },
    { sOamFrame_582924, 4 },
    { sOamFrame_582938, 4 },
    { sOamFrame_58294c, 4 },
    { sOamFrame_582960, 4 },
    { sOamFrame_582974, 4 },
    { sOamFrame_582988, 4 },
    { sOamFrame_58299c, 4 },
    { sOamFrame_5829b0, 4 },
    { sOamFrame_5829c4, 4 },
    { sOamFrame_5829d8, 4 },
    { sOamFrame_5828ac, 4 },
    { sOamFrame_5828c0, 4 },
    { sOamFrame_5828d4, 4 },
    { sOamFrame_5828e8, 4 },
    { sOamFrame_5828ac, 4 },
    { sOamFrame_5828c0, 4 },
    { sOamFrame_5828d4, 4 },
    { sOamFrame_5828e8, 4 },
    { sOamFrame_5828ac, 4 },
    { sOamFrame_5828c0, 4 },
    { sOamFrame_5828d4, 4 },
    { sOamFrame_5828e8, 4 },
    { sOamFrame_5829ec, 4 },
    { sOamFrame_582a00, 4 },
    { sOamFrame_582a14, 4 },
    { sOamFrame_582a28, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sEraseSramOam_582b24[11] = {
    { sOamFrame_5827b6, 2 },
    { sOamFrame_5827ca, 2 },
    { sOamFrame_5827de, 1 },
    { sOamFrame_5827f2, 1 },
    { sOamFrame_582806, 2 },
    { sOamFrame_58281a, 2 },
    { sOamFrame_58282e, 2 },
    { sOamFrame_582842, 2 },
    { sOamFrame_582856, 1 },
    { sOamFrame_58286a, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sEraseSramOam_582b7c[2] = {
    { sOamFrame_582878, 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sEraseSramOam_582b8c[2] = {
    { sOamFrame_582892, 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sEraseSramOam_582b9c[2] = {
    { sOamFrame_582656, 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sEraseSramOam_582bac[2] = {
    { sOamFrame_582706, 255 },
    FRAME_DATA_TERMINATOR
};
const u32 sEraseSramObjGfx[532] = INCBIN_U32("data/menus/erase_sram/obj.gfx.lz");
const u32 sEraseSramBgGfx[5147] = INCBIN_U32("data/menus/erase_sram/bg.gfx.lz");
const u32 sEraseSramTextGfxEnglish_0[185] = INCBIN_U32("data/menus/erase_sram/text_english_0.gfx.lz");
const u32 sEraseSramTextGfxFrench_0[187] = INCBIN_U32("data/menus/erase_sram/text_french_0.gfx.lz");
const u32 sEraseSramTextGfxGerman_0[205] = INCBIN_U32("data/menus/erase_sram/text_german_0.gfx.lz");
const u32 sEraseSramTextGfxItalian_0[221] = INCBIN_U32("data/menus/erase_sram/text_italian_0.gfx.lz");
const u32 sEraseSramTextGfxJapanese_0[245] = INCBIN_U32("data/menus/erase_sram/text_japanese_0.gfx.lz");
const u32 sEraseSramTextGfxSpanish_0[208] = INCBIN_U32("data/menus/erase_sram/text_spanish_0.gfx.lz");
const u32 sEraseSramTextGfxEnglish_1[191] = INCBIN_U32("data/menus/erase_sram/text_english_1.gfx.lz");
const u32 sEraseSramTextGfxFrench_1[209] = INCBIN_U32("data/menus/erase_sram/text_french_1.gfx.lz");
const u32 sEraseSramTextGfxGerman_1[222] = INCBIN_U32("data/menus/erase_sram/text_german_1.gfx.lz");
const u32 sEraseSramTextGfxItalian_1[201] = INCBIN_U32("data/menus/erase_sram/text_italian_1.gfx.lz");
const u32 sEraseSramTextGfxJapanese_1[245] = INCBIN_U32("data/menus/erase_sram/text_japanese_1.gfx.lz");
const u32 sEraseSramTextGfxSpanish_1[204] = INCBIN_U32("data/menus/erase_sram/text_spanish_1.gfx.lz");
const u32 sEraseSramTilemap_D000[131] = INCBIN_U32("data/menus/erase_sram/bg_d000.tm.lz");
const u32 sEraseSramTilemap_F000[368] = INCBIN_U32("data/menus/erase_sram/bg_f000.tm.lz");
const u8 sEraseSramCursorOamIds[4] = INCBIN_U8("data/menus/erase_sram/cursor_oam_ids.bin");
const u16 sEraseSramSounds[5] = INCBIN_U16("data/menus/erase_sram/sounds.bin");
const u8 sEraseSramCursorBasePositions[2][2] = INCBIN_U8("data/menus/erase_sram/cursor_base_positions.bin");
const u8 sEraseSramCursorOffsets[5][2] = INCBIN_U8("data/menus/erase_sram/cursor_offsets.bin");
