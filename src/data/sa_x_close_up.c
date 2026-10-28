#include "data/sa_x_close_up.h"
#include "macros.h"
#include "gba/memory.h"
#include "constants/game_state.h"

const u16 sSaXCloseUpPal[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette.pal");
const u16 sSaXCloseUpPalGrayscale[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette_grayscale.pal");
const u32 sSaXCloseUpGfx[4472] = INCBIN_U32("data/sa_x_close_up/graphics.gfx.lz");
const u32 sSaXCloseUpTileTable1[294] = INCBIN_U32("data/sa_x_close_up/first.tt.lz");
const u32 sSaXCloseUpTileTable2[305] = INCBIN_U32("data/sa_x_close_up/second.tt.lz");

const u8 sSaXCloseUpDurations[2] = { 25, 60 };

static const u8 sBlob_73421e_734220[] = INCBIN_U8("data/Blob_73421e_734220.bin");
const u8 sGameOverOamXFlipOffsets[3][4] = INCBIN_U8("data/menus/game_over/oam_x_flip_offsets.bin"); // OAM width in tiles per shape and size, as sOamXFlipOffsets
const u32 sGameOverBgGfx[5651] = INCBIN_U32("data/menus/game_over/bg.gfx.lz");
const u32 sGameOverObjGfx[2559] = INCBIN_U32("data/menus/game_over/obj.gfx.lz");
const u8 sGameOverCursorOverlayOam[] = INCBIN_U8("data/menus/game_over/cursor_overlay_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u16 sGameOverBgPal[16 * PAL_ROW] = INCBIN_U16("data/menus/game_over/bg.pal");
const u16 sGameOverObjPal[16 * PAL_ROW] = INCBIN_U16("data/menus/game_over/obj.pal");
const u32 sGameOverBg3Tilemap[369] = INCBIN_U32("data/menus/game_over/bg3.tm.lz");
const u32 sGameOverBg1Tilemap[193] = INCBIN_U32("data/menus/game_over/bg1.tm.lz");
const u32 sFileSelectBg2Tilemap[245] = INCBIN_U32("data/menus/file_select/bg2.tm.lz");
const u32 sFileSelectBg1Tilemap[155] = INCBIN_U32("data/menus/file_select/bg1.tm.lz");
const u32 sFileSelectBg0Tilemap[310] = INCBIN_U32("data/menus/file_select/bg0.tm.lz");
const u16 sFileSelectBgPal_73dac4[1 * PAL_ROW] = INCBIN_U16("data/menus/file_select/bg_73dac4.pal");
const u32 sFileSelectEnergyTankOneEmptyGfx[TILE_SIZE / 4] = INCBIN_U32("data/menus/file_select/energy_tank_one_empty.gfx");
const u32 sFileSelectEnergyTankOneFullGfx[TILE_SIZE / 4] = INCBIN_U32("data/menus/file_select/energy_tank_one_full.gfx");
const u32 sFileSelectEnergyTanksEmptyGfx[TILE_SIZE / 4] = INCBIN_U32("data/menus/file_select/energy_tanks_empty.gfx");
const u32 sFileSelectEnergyTankOneFullOneEmptyGfx[TILE_SIZE / 4] = INCBIN_U32("data/menus/file_select/energy_tank_one_full_one_empty.gfx");
const u32 sFileSelectEnergyTanksFullGfx[TILE_SIZE / 4] = INCBIN_U32("data/menus/file_select/energy_tanks_full.gfx");
const u16 sFileSelectBgPal_73db84[1 * PAL_ROW] = INCBIN_U16("data/menus/file_select/bg_73db84.pal");
const u8 sFileSelectOamXFlipOffsets[3][4] = INCBIN_U8("data/menus/file_select/oam_x_flip_offsets.bin"); // OAM width in tiles per shape and size, as sOamXFlipOffsets
const u8 sFileSelectChoiceCursorXPositions_73dbb0[LANGUAGE_COUNT][2] = INCBIN_U8("data/menus/file_select/choice_cursor_x_positions_73dbb0.bin"); // X position of the cursor on each of the 2 choices, per language
const u8 sFileSelectChoiceCursorXPositions_73dbbe[LANGUAGE_COUNT][2] = INCBIN_U8("data/menus/file_select/choice_cursor_x_positions_73dbbe.bin"); // X position of the cursor on each of the 2 choices, per language
static const u8 sBlob_73dbcc_73dc20[] = INCBIN_U8("data/Blob_73dbcc_73dc20.bin");
const u32 sFileSelectObjGfx[2792] = INCBIN_U32("data/menus/file_select/obj.gfx.lz");
const u8 sFileSelectAudioLogosOam1[] = INCBIN_U8("data/menus/file_select/audio_logos_1_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectAudioLogosOam2[] = INCBIN_U8("data/menus/file_select/audio_logos_2_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectAudioLogosOam3[] = INCBIN_U8("data/menus/file_select/audio_logos_3_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectAudioLogosOam4[] = INCBIN_U8("data/menus/file_select/audio_logos_4_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectOam_740880[] = INCBIN_U8("data/menus/file_select/740880_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectOam_7408d0[] = INCBIN_U8("data/menus/file_select/7408d0_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectOam_7408e0[] = INCBIN_U8("data/menus/file_select/7408e0_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectAudioSelectOam[] = INCBIN_U8("data/menus/file_select/audio_select_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectFileActionPanelOam1[] = INCBIN_U8("data/menus/file_select/file_action_panel_1_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectFileActionPanelOam2[] = INCBIN_U8("data/menus/file_select/file_action_panel_2_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectFileActionPanelOam3[] = INCBIN_U8("data/menus/file_select/file_action_panel_3_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectFilePanelOam1[] = INCBIN_U8("data/menus/file_select/file_panel_1_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectFilePanelOam2[] = INCBIN_U8("data/menus/file_select/file_panel_2_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectFilePanelOam3[] = INCBIN_U8("data/menus/file_select/file_panel_3_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectSamusHeadOam1[] = INCBIN_U8("data/menus/file_select/samus_head_1_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectSamusHeadOam2[] = INCBIN_U8("data/menus/file_select/samus_head_2_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectDeleteArrowIdleOam[] = INCBIN_U8("data/menus/file_select/delete_arrow_idle_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectCursorOam1[] = INCBIN_U8("data/menus/file_select/cursor_1_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectCursorOam2[] = INCBIN_U8("data/menus/file_select/cursor_2_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u8 sFileSelectOam_740b98[] = INCBIN_U8("data/menus/file_select/740b98_oam.bin"); // struct FrameData [], pointers unresolved (see tools/find_blob_pointers.py)
const u16 sFileSelectObjPal[16 * PAL_ROW] = INCBIN_U16("data/menus/file_select/obj.pal");
static const u8 sBlob_740f08_742fb4[] = INCBIN_U8("data/Blob_740f08_742fb4.bin");
const u32 sFileSelectBgGfx[4171] = INCBIN_U32("data/menus/file_select/bg.gfx.lz");
const u32 sFileSelectBg3Tilemap[368] = INCBIN_U32("data/menus/file_select/bg3.tm.lz");
const u16 sFileSelectBgPal[16 * PAL_ROW] = INCBIN_U16("data/menus/file_select/bg.pal");
