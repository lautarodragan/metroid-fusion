#include "data/sa_x_close_up.h"
#include "macros.h"
#include "gba/memory.h"
#include "constants/game_state.h"
#include "oam.h"

const u16 sSaXCloseUpPal[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette.pal");
const u16 sSaXCloseUpPalGrayscale[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette_grayscale.pal");
const u32 sSaXCloseUpGfx[4472] = INCBIN_U32("data/sa_x_close_up/graphics.gfx.lz");
const u32 sSaXCloseUpTileTable1[294] = INCBIN_U32("data/sa_x_close_up/first.tt.lz");
const u32 sSaXCloseUpTileTable2[305] = INCBIN_U32("data/sa_x_close_up/second.tt.lz");

const u8 sSaXCloseUpDurations[2] = { 25, 60 };

static const u8 sBlob_73421e_734220[] = INCBIN_U8("data/Blob_73421e_734220.bin");
const u8 sGameOverOamXFlipOffsets[3][4] = INCBIN_U8("data/menus/game_over/oam_x_flip_offsets.bin"); // OAM width in tiles per shape and size, as sOamXFlipOffsets
const u32 sGameOverBgGfx[5651] = INCBIN_U32("data/menus/game_over/bg.gfx.lz");
const u32 sGameOverObjGfx[184] = INCBIN_U32("data/menus/game_over/obj.gfx.lz");
const u8 sGameOverTextGfxJapanese[1752] = INCBIN_U8("data/menus/game_over/text_japanese.gfx.lz");
const u8 sGameOverTextGfxGerman[1784] = INCBIN_U8("data/menus/game_over/text_german.gfx.lz");
const u8 sGameOverTextGfxFrench[2016] = INCBIN_U8("data/menus/game_over/text_french.gfx.lz");
const u8 sGameOverTextGfxItalian[1956] = INCBIN_U8("data/menus/game_over/text_italian.gfx.lz");
const u8 sGameOverTextGfxSpanish[1900] = INCBIN_U8("data/menus/game_over/text_spanish.gfx.lz");
const u16 sOamFrame_73c218[4] = INCBIN_U16("data/oam_frames/73c218.bin");
const u16 sOamFrame_73c220[4] = INCBIN_U16("data/oam_frames/73c220.bin");
const u16 sOamFrame_73c228[4] = INCBIN_U16("data/oam_frames/73c228.bin");
const u16 sOamFrame_73c230[4] = INCBIN_U16("data/oam_frames/73c230.bin");
const u16 sOamFrame_73c238[7] = INCBIN_U16("data/oam_frames/73c238.bin");
const u16 sOamFrame_73c246[7] = INCBIN_U16("data/oam_frames/73c246.bin");
const u16 sOamFrame_73c254[7] = INCBIN_U16("data/oam_frames/73c254.bin");
const u16 sOamFrame_73c262[4] = INCBIN_U16("data/oam_frames/73c262.bin");
const u16 sOamFrame_73c26a[5] = INCBIN_U16("data/oam_frames/73c26a.bin");
const struct FrameData sGameOverCursorOverlayOam[5] = {
    { sOamFrame_73c218, 14 },
    { sOamFrame_73c262, 14 },
    { sOamFrame_73c26a, 14 },
    { sOamFrame_73c262, 14 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sGameOverCursorOverlayOam_73c29c[9] = {
    { sOamFrame_73c218, 8 },
    { sOamFrame_73c220, 4 },
    { sOamFrame_73c228, 4 },
    { sOamFrame_73c230, 8 },
    { sOamFrame_73c238, 5 },
    { sOamFrame_73c246, 5 },
    { sOamFrame_73c254, 5 },
    { sOamFrame_73c230, 255 },
    FRAME_DATA_TERMINATOR
};
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
const u16 sFileSelectTextTileOffsets_73dbcc[] = INCBIN_U16("data/menus/file_select/text_tile_offsets_73dbcc.bin");
const u16 sFileSelectTextTileOffsets_73dbd8[] = INCBIN_U16("data/menus/file_select/text_tile_offsets_73dbd8.bin");
const u16 sFileSelectTextTileOffsets_73dbde[] = INCBIN_U16("data/menus/file_select/text_tile_offsets_73dbde.bin");
const u16 sFileSelectTextTileOffsets_73dbe4[] = INCBIN_U16("data/menus/file_select/text_tile_offsets_73dbe4.bin");
const u16 sFileSelectTextTileOffsets_73dbea[] = INCBIN_U16("data/menus/file_select/text_tile_offsets_73dbea.bin");
const u16 sFileSelectTextTileOffsets_73dbf6[] = INCBIN_U16("data/menus/file_select/text_tile_offsets_73dbf6.bin");
const u16 sFileSelectTextTileOffsets_73dbfc[] = INCBIN_U16("data/menus/file_select/text_tile_offsets_73dbfc.bin");
const u16 sFileSelectTextTileOffsets_73dc02[] = INCBIN_U16("data/menus/file_select/text_tile_offsets_73dc02.bin");
const u16 sFileSelectTextTileOffsets_73dc08[] = INCBIN_U16("data/menus/file_select/text_tile_offsets_73dc08.bin");
const u16 sFileSelectTextTileOffsets_73dc14[] = INCBIN_U16("data/menus/file_select/text_tile_offsets_73dc14.bin");
const u32 sFileSelectObjGfx[1413] = INCBIN_U32("data/menus/file_select/obj.gfx.lz");
const u16 sOamFrame_73f234[31] = INCBIN_U16("data/oam_frames/73f234.bin");
const u16 sOamFrame_73f272[31] = INCBIN_U16("data/oam_frames/73f272.bin");
const u16 sOamFrame_73f2b0[31] = INCBIN_U16("data/oam_frames/73f2b0.bin");
const u16 sOamFrame_73f2ee[31] = INCBIN_U16("data/oam_frames/73f2ee.bin");
const u16 sOamFrame_73f32c[31] = INCBIN_U16("data/oam_frames/73f32c.bin");
const u16 sOamFrame_73f36a[7] = INCBIN_U16("data/oam_frames/73f36a.bin");
const u16 sOamFrame_73f378[7] = INCBIN_U16("data/oam_frames/73f378.bin");
const u16 sOamFrame_73f386[7] = INCBIN_U16("data/oam_frames/73f386.bin");
const u16 sOamFrame_73f394[7] = INCBIN_U16("data/oam_frames/73f394.bin");
const u16 sOamFrame_73f3a2[7] = INCBIN_U16("data/oam_frames/73f3a2.bin");
const u16 sOamFrame_73f3b0[13] = INCBIN_U16("data/oam_frames/73f3b0.bin");
const u16 sOamFrame_73f3ca[19] = INCBIN_U16("data/oam_frames/73f3ca.bin");
const u16 sOamFrame_73f3f0[13] = INCBIN_U16("data/oam_frames/73f3f0.bin");
const u16 sOamFrame_73f40a[19] = INCBIN_U16("data/oam_frames/73f40a.bin");
const u16 sOamFrame_73f430[34] = INCBIN_U16("data/oam_frames/73f430.bin");
const u16 sOamFrame_73f474[10] = INCBIN_U16("data/oam_frames/73f474.bin");
const u16 sOamFrame_73f488[10] = INCBIN_U16("data/oam_frames/73f488.bin");
const u16 sOamFrame_73f49c[4] = INCBIN_U16("data/oam_frames/73f49c.bin");
const u16 sOamFrame_73f4a4[4] = INCBIN_U16("data/oam_frames/73f4a4.bin");
const u16 sOamFrame_73f4ac[4] = INCBIN_U16("data/oam_frames/73f4ac.bin");
const u16 sOamFrame_73f4b4[4] = INCBIN_U16("data/oam_frames/73f4b4.bin");
const u16 sOamFrame_73f4bc[4] = INCBIN_U16("data/oam_frames/73f4bc.bin");
const u16 sOamFrame_73f4c4[79] = INCBIN_U16("data/oam_frames/73f4c4.bin");
const u16 sOamFrame_73f562[22] = INCBIN_U16("data/oam_frames/73f562.bin");
const u16 sOamFrame_73f58e[22] = INCBIN_U16("data/oam_frames/73f58e.bin");
const u16 sOamFrame_73f5ba[7] = INCBIN_U16("data/oam_frames/73f5ba.bin");
const u16 sOamFrame_73f5c8[7] = INCBIN_U16("data/oam_frames/73f5c8.bin");
const u16 sOamFrame_73f5d6[13] = INCBIN_U16("data/oam_frames/73f5d6.bin");
const u16 sOamFrame_73f5f0[19] = INCBIN_U16("data/oam_frames/73f5f0.bin");
const u16 sOamFrame_73f616[13] = INCBIN_U16("data/oam_frames/73f616.bin");
const u16 sOamFrame_73f630[13] = INCBIN_U16("data/oam_frames/73f630.bin");
const u16 sOamFrame_73f64a[7] = INCBIN_U16("data/oam_frames/73f64a.bin");
const u16 sOamFrame_73f658[13] = INCBIN_U16("data/oam_frames/73f658.bin");
const u16 sOamFrame_73f672[19] = INCBIN_U16("data/oam_frames/73f672.bin");
const u16 sOamFrame_73f698[28] = INCBIN_U16("data/oam_frames/73f698.bin");
const u16 sOamFrame_73f6d0[4] = INCBIN_U16("data/oam_frames/73f6d0.bin");
const u16 sOamFrame_73f6d8[7] = INCBIN_U16("data/oam_frames/73f6d8.bin");
const u16 sOamFrame_73f6e6[7] = INCBIN_U16("data/oam_frames/73f6e6.bin");
const u16 sOamFrame_73f6f4[7] = INCBIN_U16("data/oam_frames/73f6f4.bin");
const u16 sOamFrame_73f702[7] = INCBIN_U16("data/oam_frames/73f702.bin");
const u16 sOamFrame_73f710[7] = INCBIN_U16("data/oam_frames/73f710.bin");
const u16 sOamFrame_73f71e[7] = INCBIN_U16("data/oam_frames/73f71e.bin");
const u16 sOamFrame_73f72c[7] = INCBIN_U16("data/oam_frames/73f72c.bin");
const u16 sOamFrame_73f73a[4] = INCBIN_U16("data/oam_frames/73f73a.bin");
const u16 sOamFrame_73f742[4] = INCBIN_U16("data/oam_frames/73f742.bin");
const u16 sOamFrame_73f74a[4] = INCBIN_U16("data/oam_frames/73f74a.bin");
const u16 sOamFrame_73f752[4] = INCBIN_U16("data/oam_frames/73f752.bin");
const u16 sOamFrame_73f75a[7] = INCBIN_U16("data/oam_frames/73f75a.bin");
const u16 sOamFrame_73f768[7] = INCBIN_U16("data/oam_frames/73f768.bin");
const u16 sOamFrame_73f776[14] = INCBIN_U16("data/oam_frames/73f776.bin");
const u16 sOamFrame_73f792[79] = INCBIN_U16("data/oam_frames/73f792.bin");
const u16 sOamFrame_73f830[79] = INCBIN_U16("data/oam_frames/73f830.bin");
const u16 sOamFrame_73f8ce[91] = INCBIN_U16("data/oam_frames/73f8ce.bin");
const u16 sOamFrame_73f984[13] = INCBIN_U16("data/oam_frames/73f984.bin");
const u16 sOamFrame_73f99e[13] = INCBIN_U16("data/oam_frames/73f99e.bin");
const u16 sOamFrame_73f9b8[4] = INCBIN_U16("data/oam_frames/73f9b8.bin");
const u16 sOamFrame_73f9c0[4] = INCBIN_U16("data/oam_frames/73f9c0.bin");
const u16 sOamFrame_73f9c8[4] = INCBIN_U16("data/oam_frames/73f9c8.bin");
const u16 sOamFrame_73f9d0[4] = INCBIN_U16("data/oam_frames/73f9d0.bin");
const u16 sOamFrame_73f9d8[4] = INCBIN_U16("data/oam_frames/73f9d8.bin");
const u16 sOamFrame_73f9e0[82] = INCBIN_U16("data/oam_frames/73f9e0.bin");
const u16 sOamFrame_73fa84[82] = INCBIN_U16("data/oam_frames/73fa84.bin");
const u16 sOamFrame_73fb28[82] = INCBIN_U16("data/oam_frames/73fb28.bin");
const u16 sOamFrame_73fbcc[82] = INCBIN_U16("data/oam_frames/73fbcc.bin");
const u16 sOamFrame_73fc70[82] = INCBIN_U16("data/oam_frames/73fc70.bin");
const u16 sOamFrame_73fd14[82] = INCBIN_U16("data/oam_frames/73fd14.bin");
const u16 sOamFrame_73fdb8[82] = INCBIN_U16("data/oam_frames/73fdb8.bin");
const u16 sOamFrame_73fe5c[82] = INCBIN_U16("data/oam_frames/73fe5c.bin");
const u16 sOamFrame_73ff00[82] = INCBIN_U16("data/oam_frames/73ff00.bin");
const u16 sOamFrame_73ffa4[82] = INCBIN_U16("data/oam_frames/73ffa4.bin");
const u16 sOamFrame_740048[82] = INCBIN_U16("data/oam_frames/740048.bin");
const u16 sOamFrame_7400ec[82] = INCBIN_U16("data/oam_frames/7400ec.bin");
const u16 sOamFrame_740190[82] = INCBIN_U16("data/oam_frames/740190.bin");
const u16 sOamFrame_740234[82] = INCBIN_U16("data/oam_frames/740234.bin");
const u16 sOamFrame_7402d8[82] = INCBIN_U16("data/oam_frames/7402d8.bin");
const u16 sOamFrame_74037c[82] = INCBIN_U16("data/oam_frames/74037c.bin");
const u16 sOamFrame_740420[82] = INCBIN_U16("data/oam_frames/740420.bin");
const u16 sOamFrame_7404c4[82] = INCBIN_U16("data/oam_frames/7404c4.bin");
const u16 sOamFrame_740568[4] = INCBIN_U16("data/oam_frames/740568.bin");
const u16 sOamFrame_740570[7] = INCBIN_U16("data/oam_frames/740570.bin");
const u16 sOamFrame_74057e[7] = INCBIN_U16("data/oam_frames/74057e.bin");
const u16 sOamFrame_74058c[7] = INCBIN_U16("data/oam_frames/74058c.bin");
const u16 sOamFrame_74059a[7] = INCBIN_U16("data/oam_frames/74059a.bin");
const u16 sOamFrame_7405a8[7] = INCBIN_U16("data/oam_frames/7405a8.bin");
const u16 sOamFrame_7405b6[7] = INCBIN_U16("data/oam_frames/7405b6.bin");
const u16 sOamFrame_7405c4[7] = INCBIN_U16("data/oam_frames/7405c4.bin");
const u16 sOamFrame_7405d2[10] = INCBIN_U16("data/oam_frames/7405d2.bin");
const u16 sOamFrame_7405e6[10] = INCBIN_U16("data/oam_frames/7405e6.bin");
const u16 sOamFrame_7405fa[10] = INCBIN_U16("data/oam_frames/7405fa.bin");
const u16 sOamFrame_74060e[10] = INCBIN_U16("data/oam_frames/74060e.bin");
const u16 sOamFrame_740622[10] = INCBIN_U16("data/oam_frames/740622.bin");
const u16 sOamFrame_740636[10] = INCBIN_U16("data/oam_frames/740636.bin");
const u16 sOamFrame_74064a[4] = INCBIN_U16("data/oam_frames/74064a.bin");
const u16 sOamFrame_740652[10] = INCBIN_U16("data/oam_frames/740652.bin");
const u16 sOamFrame_740666[10] = INCBIN_U16("data/oam_frames/740666.bin");
const u16 sOamFrame_74067a[10] = INCBIN_U16("data/oam_frames/74067a.bin");
const u16 sOamFrame_74068e[10] = INCBIN_U16("data/oam_frames/74068e.bin");
const u16 sOamFrame_7406a2[10] = INCBIN_U16("data/oam_frames/7406a2.bin");
const u16 sOamFrame_7406b6[10] = INCBIN_U16("data/oam_frames/7406b6.bin");
const u16 sOamFrame_7406ca[7] = INCBIN_U16("data/oam_frames/7406ca.bin");
const u16 sOamFrame_7406d8[7] = INCBIN_U16("data/oam_frames/7406d8.bin");
const u16 sOamFrame_7406e6[4] = INCBIN_U16("data/oam_frames/7406e6.bin");
const u16 sOamFrame_7406ee[5] = INCBIN_U16("data/oam_frames/7406ee.bin");
const struct FrameData sFileSelectOam_7406f8[25] = {
    { sOamFrame_73f234, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f272, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f2b0, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f2ee, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f32c, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f36a, 4 },
    { sOamFrame_73f6d0, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f378, 4 },
    { sOamFrame_73f6d0, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f386, 4 },
    { sOamFrame_73f6d0, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f394, 4 },
    { sOamFrame_73f6d0, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f3a2, 4 },
    { sOamFrame_73f6d0, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectAudioLogosOam1[2] = {
    { sOamFrame_73f3ca, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectAudioLogosOam2[2] = {
    { sOamFrame_73f3f0, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectAudioLogosOam3[2] = {
    { sOamFrame_73f40a, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectAudioLogosOam4[2] = {
    { sOamFrame_73f430, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectAudioLogosOam4_740800[4] = {
    { sOamFrame_73f9e0, 8 },
    { sOamFrame_73fa84, 8 },
    { sOamFrame_73fb28, 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectAudioLogosOam4_740820[4] = {
    { sOamFrame_73fbcc, 8 },
    { sOamFrame_73fc70, 8 },
    { sOamFrame_73fd14, 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectAudioLogosOam4_740840[8] = {
    { sOamFrame_73fdb8, 8 },
    { sOamFrame_73fe5c, 8 },
    { sOamFrame_73ff00, 8 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f474, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f488, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectOam_740880[8] = {
    { sOamFrame_73f49c, 8 },
    { sOamFrame_73f4a4, 8 },
    { sOamFrame_73f4ac, 8 },
    { sOamFrame_73f4a4, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_73f4b4, 4 },
    { sOamFrame_73f4bc, 20 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_7408c0[2] = {
    { sOamFrame_73f4c4, 16 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectOam_7408d0[2] = {
    { sOamFrame_73f562, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectOam_7408e0[2] = {
    { sOamFrame_73f58e, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectAudioSelectOam[5] = {
    { sOamFrame_73f3b0, 10 },
    { sOamFrame_73f984, 10 },
    { sOamFrame_73f99e, 10 },
    { sOamFrame_73f984, 10 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectFileActionPanelOam1[5] = {
    { sOamFrame_73f5ba, 1 },
    { sOamFrame_73f5c8, 1 },
    { sOamFrame_73f5d6, 2 },
    { sOamFrame_73f5f0, 2 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectFileActionPanelOam2[2] = {
    { sOamFrame_73f616, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectFileActionPanelOam3[5] = {
    { sOamFrame_73f5f0, 2 },
    { sOamFrame_73f5d6, 2 },
    { sOamFrame_73f5c8, 1 },
    { sOamFrame_73f5ba, 1 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectFilePanelOam1[5] = {
    { sOamFrame_73f630, 1 },
    { sOamFrame_73f64a, 1 },
    { sOamFrame_73f658, 2 },
    { sOamFrame_73f672, 2 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectFilePanelOam2[2] = {
    { sOamFrame_73f698, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectFilePanelOam3[5] = {
    { sOamFrame_73f672, 2 },
    { sOamFrame_73f658, 2 },
    { sOamFrame_73f64a, 1 },
    { sOamFrame_73f630, 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectFilePanelOam3_7409d8[2] = {
    { sOamFrame_73f6d8, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectFilePanelOam3_7409e8[2] = {
    { sOamFrame_73f6e6, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectFilePanelOam3_7409f8[2] = {
    { sOamFrame_73f6f4, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectFilePanelOam3_740a08[2] = {
    { sOamFrame_73f702, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectFilePanelOam3_740a18[2] = {
    { sOamFrame_73f710, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectFilePanelOam3_740a28[2] = {
    { sOamFrame_73f71e, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectFilePanelOam3_740a38[2] = {
    { sOamFrame_73f72c, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectSamusHeadOam1[5] = {
    { sOamFrame_73f73a, 14 },
    { sOamFrame_7406e6, 14 },
    { sOamFrame_7406ee, 14 },
    { sOamFrame_7406e6, 14 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectSamusHeadOam2[9] = {
    { sOamFrame_73f73a, 8 },
    { sOamFrame_73f742, 4 },
    { sOamFrame_73f74a, 4 },
    { sOamFrame_73f752, 8 },
    { sOamFrame_73f75a, 5 },
    { sOamFrame_73f768, 5 },
    { sOamFrame_73f776, 5 },
    { sOamFrame_73f752, 30 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectDeleteArrowIdleOam[2] = {
    { sOamFrame_73f792, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectDeleteArrowIdleOam_740ac8[2] = {
    { sOamFrame_73f830, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectDeleteArrowIdleOam_740ad8[2] = {
    { sOamFrame_73f8ce, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectDeleteArrowIdleOam_740ae8[4] = {
    { sOamFrame_73ffa4, 8 },
    { sOamFrame_740048, 8 },
    { sOamFrame_7400ec, 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectDeleteArrowIdleOam_740b08[4] = {
    { sOamFrame_740190, 8 },
    { sOamFrame_740234, 8 },
    { sOamFrame_7402d8, 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectDeleteArrowIdleOam_740b28[4] = {
    { sOamFrame_74037c, 8 },
    { sOamFrame_740420, 8 },
    { sOamFrame_7404c4, 8 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectCursorOam1[5] = {
    { sOamFrame_73f9b8, 8 },
    { sOamFrame_73f9c0, 8 },
    { sOamFrame_73f9c8, 8 },
    { sOamFrame_73f9c0, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectCursorOam2[5] = {
    { sOamFrame_73f9d0, 4 },
    { sOamFrame_73f9d8, 4 },
    { sOamFrame_73f9d0, 4 },
    { sOamFrame_73f9d8, 20 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sFileSelectOam_740b98[2] = {
    { sOamFrame_740568, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740ba8[2] = {
    { sOamFrame_740570, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740bb8[2] = {
    { sOamFrame_74057e, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740bc8[2] = {
    { sOamFrame_74058c, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740bd8[2] = {
    { sOamFrame_74059a, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740be8[2] = {
    { sOamFrame_7405a8, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740bf8[2] = {
    { sOamFrame_7405b6, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740c08[2] = {
    { sOamFrame_7405c4, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740c18[2] = {
    { sOamFrame_7405d2, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740c28[2] = {
    { sOamFrame_7405e6, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740c38[2] = {
    { sOamFrame_7405fa, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740c48[2] = {
    { sOamFrame_74060e, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740c58[2] = {
    { sOamFrame_740622, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740c68[2] = {
    { sOamFrame_740636, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740c78[2] = {
    { sOamFrame_74064a, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740c88[2] = {
    { sOamFrame_740652, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740c98[2] = {
    { sOamFrame_740666, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740ca8[2] = {
    { sOamFrame_74067a, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740cb8[2] = {
    { sOamFrame_74068e, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740cc8[2] = {
    { sOamFrame_7406a2, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740cd8[2] = {
    { sOamFrame_7406b6, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740ce8[2] = {
    { sOamFrame_7406ca, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFileSelectOam_740cf8[2] = {
    { sOamFrame_7406d8, 4 },
    FRAME_DATA_TERMINATOR
};
const u16 sFileSelectObjPal[16 * PAL_ROW] = INCBIN_U16("data/menus/file_select/obj.pal");
const u16 sFileSelectTextJapanese_0[] = INCBIN_U16("data/text/japanese/file_select_0.bin");
const u16 sFileSelectTextJapanese_1[] = INCBIN_U16("data/text/japanese/file_select_1.bin");
const u16 sFileSelectTextJapanese_2[] = INCBIN_U16("data/text/japanese/file_select_2.bin");
const u16 sFileSelectTextJapanese_3[] = INCBIN_U16("data/text/japanese/file_select_3.bin");
const u16 sFileSelectTextJapanese_4[] = INCBIN_U16("data/text/japanese/file_select_4.bin");
const u16 sFileSelectTextJapanese_5[] = INCBIN_U16("data/text/japanese/file_select_5.bin");
const u16 sFileSelectTextJapanese_6[] = INCBIN_U16("data/text/japanese/file_select_6.bin");
const u16 sFileSelectTextJapanese_7[] = INCBIN_U16("data/text/japanese/file_select_7.bin");
const u16 sFileSelectTextJapanese_8[] = INCBIN_U16("data/text/japanese/file_select_8.bin");
const u16 sFileSelectTextJapanese_9[] = INCBIN_U16("data/text/japanese/file_select_9.bin");
const u16 sFileSelectTextJapanese_10[] = INCBIN_U16("data/text/japanese/file_select_10.bin");
const u16 sFileSelectTextJapanese_11[] = INCBIN_U16("data/text/japanese/file_select_11.bin");
const u16 sFileSelectTextJapanese_12[] = INCBIN_U16("data/text/japanese/file_select_12.bin");
const u16 sFileSelectTextJapanese_13[] = INCBIN_U16("data/text/japanese/file_select_13.bin");
const u16 sFileSelectTextJapanese_14[] = INCBIN_U16("data/text/japanese/file_select_14.bin");
const u16 sFileSelectTextJapanese_15[] = INCBIN_U16("data/text/japanese/file_select_15.bin");
const u16 sFileSelectTextJapanese_16[] = INCBIN_U16("data/text/japanese/file_select_16.bin");
const u16 sFileSelectTextJapanese_17[] = INCBIN_U16("data/text/japanese/file_select_17.bin");
const u16 sFileSelectTextJapanese_18[] = INCBIN_U16("data/text/japanese/file_select_18.bin");
const u16 sFileSelectTextJapanese_19[] = INCBIN_U16("data/text/japanese/file_select_19.bin");
const u16 sFileSelectTextJapanese_20[] = INCBIN_U16("data/text/japanese/file_select_20.bin");
const u16 sFileSelectTextJapanese_21[] = INCBIN_U16("data/text/japanese/file_select_21.bin");
const u16 sFileSelectTextJapanese_22[] = INCBIN_U16("data/text/japanese/file_select_22.bin");
const u16 sFileSelectTextJapanese_23[] = INCBIN_U16("data/text/japanese/file_select_23.bin");
const u16 sFileSelectTextJapanese_24[] = INCBIN_U16("data/text/japanese/file_select_24.bin");
const u16 sFileSelectTextEnglish_0[] = INCBIN_U16("data/text/english/file_select_0.bin");
const u16 sFileSelectTextEnglish_1[] = INCBIN_U16("data/text/english/file_select_1.bin");
const u16 sFileSelectTextEnglish_2[] = INCBIN_U16("data/text/english/file_select_2.bin");
const u16 sFileSelectTextEnglish_3[] = INCBIN_U16("data/text/english/file_select_3.bin");
const u16 sFileSelectTextEnglish_4[] = INCBIN_U16("data/text/english/file_select_4.bin");
const u16 sFileSelectTextEnglish_5[] = INCBIN_U16("data/text/english/file_select_5.bin");
const u16 sFileSelectTextEnglish_6[] = INCBIN_U16("data/text/english/file_select_6.bin");
const u16 sFileSelectTextEnglish_7[] = INCBIN_U16("data/text/english/file_select_7.bin");
const u16 sFileSelectTextEnglish_8[] = INCBIN_U16("data/text/english/file_select_8.bin");
const u16 sFileSelectTextEnglish_9[] = INCBIN_U16("data/text/english/file_select_9.bin");
const u16 sFileSelectTextEnglish_10[] = INCBIN_U16("data/text/english/file_select_10.bin");
const u16 sFileSelectTextEnglish_11[] = INCBIN_U16("data/text/english/file_select_11.bin");
const u16 sFileSelectTextEnglish_12[] = INCBIN_U16("data/text/english/file_select_12.bin");
const u16 sFileSelectTextEnglish_13[] = INCBIN_U16("data/text/english/file_select_13.bin");
const u16 sFileSelectTextEnglish_14[] = INCBIN_U16("data/text/english/file_select_14.bin");
const u16 sFileSelectTextEnglish_15[] = INCBIN_U16("data/text/english/file_select_15.bin");
const u16 sFileSelectTextEnglish_16[] = INCBIN_U16("data/text/english/file_select_16.bin");
const u16 sFileSelectTextEnglish_17[] = INCBIN_U16("data/text/english/file_select_17.bin");
const u16 sFileSelectTextEnglish_18[] = INCBIN_U16("data/text/english/file_select_18.bin");
const u16 sFileSelectTextEnglish_19[] = INCBIN_U16("data/text/english/file_select_19.bin");
const u16 sFileSelectTextEnglish_20[] = INCBIN_U16("data/text/english/file_select_20.bin");
const u16 sFileSelectTextEnglish_21[] = INCBIN_U16("data/text/english/file_select_21.bin");
const u16 sFileSelectTextEnglish_22[] = INCBIN_U16("data/text/english/file_select_22.bin");
const u16 sFileSelectTextEnglish_23[] = INCBIN_U16("data/text/english/file_select_23.bin");
const u16 sFileSelectTextEnglish_24[] = INCBIN_U16("data/text/english/file_select_24.bin");
const u16 sFileSelectTextGerman_0[] = INCBIN_U16("data/text/german/file_select_0.bin");
const u16 sFileSelectTextGerman_1[] = INCBIN_U16("data/text/german/file_select_1.bin");
const u16 sFileSelectTextGerman_2[] = INCBIN_U16("data/text/german/file_select_2.bin");
const u16 sFileSelectTextGerman_3[] = INCBIN_U16("data/text/german/file_select_3.bin");
const u16 sFileSelectTextGerman_4[] = INCBIN_U16("data/text/german/file_select_4.bin");
const u16 sFileSelectTextGerman_5[] = INCBIN_U16("data/text/german/file_select_5.bin");
const u16 sFileSelectTextGerman_6[] = INCBIN_U16("data/text/german/file_select_6.bin");
const u16 sFileSelectTextGerman_7[] = INCBIN_U16("data/text/german/file_select_7.bin");
const u16 sFileSelectTextGerman_8[] = INCBIN_U16("data/text/german/file_select_8.bin");
const u16 sFileSelectTextGerman_9[] = INCBIN_U16("data/text/german/file_select_9.bin");
const u16 sFileSelectTextGerman_10[] = INCBIN_U16("data/text/german/file_select_10.bin");
const u16 sFileSelectTextGerman_11[] = INCBIN_U16("data/text/german/file_select_11.bin");
const u16 sFileSelectTextGerman_12[] = INCBIN_U16("data/text/german/file_select_12.bin");
const u16 sFileSelectTextGerman_13[] = INCBIN_U16("data/text/german/file_select_13.bin");
const u16 sFileSelectTextGerman_14[] = INCBIN_U16("data/text/german/file_select_14.bin");
const u16 sFileSelectTextGerman_15[] = INCBIN_U16("data/text/german/file_select_15.bin");
const u16 sFileSelectTextGerman_16[] = INCBIN_U16("data/text/german/file_select_16.bin");
const u16 sFileSelectTextGerman_17[] = INCBIN_U16("data/text/german/file_select_17.bin");
const u16 sFileSelectTextGerman_18[] = INCBIN_U16("data/text/german/file_select_18.bin");
const u16 sFileSelectTextGerman_19[] = INCBIN_U16("data/text/german/file_select_19.bin");
const u16 sFileSelectTextGerman_20[] = INCBIN_U16("data/text/german/file_select_20.bin");
const u16 sFileSelectTextGerman_21[] = INCBIN_U16("data/text/german/file_select_21.bin");
const u16 sFileSelectTextGerman_22[] = INCBIN_U16("data/text/german/file_select_22.bin");
const u16 sFileSelectTextGerman_23[] = INCBIN_U16("data/text/german/file_select_23.bin");
const u16 sFileSelectTextGerman_24[] = INCBIN_U16("data/text/german/file_select_24.bin");
const u16 sFileSelectTextFrench_0[] = INCBIN_U16("data/text/french/file_select_0.bin");
const u16 sFileSelectTextFrench_1[] = INCBIN_U16("data/text/french/file_select_1.bin");
const u16 sFileSelectTextFrench_2[] = INCBIN_U16("data/text/french/file_select_2.bin");
const u16 sFileSelectTextFrench_3[] = INCBIN_U16("data/text/french/file_select_3.bin");
const u16 sFileSelectTextFrench_4[] = INCBIN_U16("data/text/french/file_select_4.bin");
const u16 sFileSelectTextFrench_5[] = INCBIN_U16("data/text/french/file_select_5.bin");
const u16 sFileSelectTextFrench_6[] = INCBIN_U16("data/text/french/file_select_6.bin");
const u16 sFileSelectTextFrench_7[] = INCBIN_U16("data/text/french/file_select_7.bin");
const u16 sFileSelectTextFrench_8[] = INCBIN_U16("data/text/french/file_select_8.bin");
const u16 sFileSelectTextFrench_9[] = INCBIN_U16("data/text/french/file_select_9.bin");
const u16 sFileSelectTextFrench_10[] = INCBIN_U16("data/text/french/file_select_10.bin");
const u16 sFileSelectTextFrench_11[] = INCBIN_U16("data/text/french/file_select_11.bin");
const u16 sFileSelectTextFrench_12[] = INCBIN_U16("data/text/french/file_select_12.bin");
const u16 sFileSelectTextFrench_13[] = INCBIN_U16("data/text/french/file_select_13.bin");
const u16 sFileSelectTextFrench_14[] = INCBIN_U16("data/text/french/file_select_14.bin");
const u16 sFileSelectTextFrench_15[] = INCBIN_U16("data/text/french/file_select_15.bin");
const u16 sFileSelectTextFrench_16[] = INCBIN_U16("data/text/french/file_select_16.bin");
const u16 sFileSelectTextFrench_17[] = INCBIN_U16("data/text/french/file_select_17.bin");
const u16 sFileSelectTextFrench_18[] = INCBIN_U16("data/text/french/file_select_18.bin");
const u16 sFileSelectTextFrench_19[] = INCBIN_U16("data/text/french/file_select_19.bin");
const u16 sFileSelectTextFrench_20[] = INCBIN_U16("data/text/french/file_select_20.bin");
const u16 sFileSelectTextFrench_21[] = INCBIN_U16("data/text/french/file_select_21.bin");
const u16 sFileSelectTextFrench_22[] = INCBIN_U16("data/text/french/file_select_22.bin");
const u16 sFileSelectTextFrench_23[] = INCBIN_U16("data/text/french/file_select_23.bin");
const u16 sFileSelectTextFrench_24[] = INCBIN_U16("data/text/french/file_select_24.bin");
const u16 sFileSelectTextItalian_0[] = INCBIN_U16("data/text/italian/file_select_0.bin");
const u16 sFileSelectTextItalian_1[] = INCBIN_U16("data/text/italian/file_select_1.bin");
const u16 sFileSelectTextItalian_2[] = INCBIN_U16("data/text/italian/file_select_2.bin");
const u16 sFileSelectTextItalian_3[] = INCBIN_U16("data/text/italian/file_select_3.bin");
const u16 sFileSelectTextItalian_4[] = INCBIN_U16("data/text/italian/file_select_4.bin");
const u16 sFileSelectTextItalian_5[] = INCBIN_U16("data/text/italian/file_select_5.bin");
const u16 sFileSelectTextItalian_6[] = INCBIN_U16("data/text/italian/file_select_6.bin");
const u16 sFileSelectTextItalian_7[] = INCBIN_U16("data/text/italian/file_select_7.bin");
const u16 sFileSelectTextItalian_8[] = INCBIN_U16("data/text/italian/file_select_8.bin");
const u16 sFileSelectTextItalian_9[] = INCBIN_U16("data/text/italian/file_select_9.bin");
const u16 sFileSelectTextItalian_10[] = INCBIN_U16("data/text/italian/file_select_10.bin");
const u16 sFileSelectTextItalian_11[] = INCBIN_U16("data/text/italian/file_select_11.bin");
const u16 sFileSelectTextItalian_12[] = INCBIN_U16("data/text/italian/file_select_12.bin");
const u16 sFileSelectTextItalian_13[] = INCBIN_U16("data/text/italian/file_select_13.bin");
const u16 sFileSelectTextItalian_14[] = INCBIN_U16("data/text/italian/file_select_14.bin");
const u16 sFileSelectTextItalian_15[] = INCBIN_U16("data/text/italian/file_select_15.bin");
const u16 sFileSelectTextItalian_16[] = INCBIN_U16("data/text/italian/file_select_16.bin");
const u16 sFileSelectTextItalian_17[] = INCBIN_U16("data/text/italian/file_select_17.bin");
const u16 sFileSelectTextItalian_18[] = INCBIN_U16("data/text/italian/file_select_18.bin");
const u16 sFileSelectTextItalian_19[] = INCBIN_U16("data/text/italian/file_select_19.bin");
const u16 sFileSelectTextItalian_20[] = INCBIN_U16("data/text/italian/file_select_20.bin");
const u16 sFileSelectTextItalian_21[] = INCBIN_U16("data/text/italian/file_select_21.bin");
const u16 sFileSelectTextItalian_22[] = INCBIN_U16("data/text/italian/file_select_22.bin");
const u16 sFileSelectTextItalian_23[] = INCBIN_U16("data/text/italian/file_select_23.bin");
const u16 sFileSelectTextItalian_24[] = INCBIN_U16("data/text/italian/file_select_24.bin");
const u16 sFileSelectTextSpanish_0[] = INCBIN_U16("data/text/spanish/file_select_0.bin");
const u16 sFileSelectTextSpanish_1[] = INCBIN_U16("data/text/spanish/file_select_1.bin");
const u16 sFileSelectTextSpanish_2[] = INCBIN_U16("data/text/spanish/file_select_2.bin");
const u16 sFileSelectTextSpanish_3[] = INCBIN_U16("data/text/spanish/file_select_3.bin");
const u16 sFileSelectTextSpanish_4[] = INCBIN_U16("data/text/spanish/file_select_4.bin");
const u16 sFileSelectTextSpanish_5[] = INCBIN_U16("data/text/spanish/file_select_5.bin");
const u16 sFileSelectTextSpanish_6[] = INCBIN_U16("data/text/spanish/file_select_6.bin");
const u16 sFileSelectTextSpanish_7[] = INCBIN_U16("data/text/spanish/file_select_7.bin");
const u16 sFileSelectTextSpanish_8[] = INCBIN_U16("data/text/spanish/file_select_8.bin");
const u16 sFileSelectTextSpanish_9[] = INCBIN_U16("data/text/spanish/file_select_9.bin");
const u16 sFileSelectTextSpanish_10[] = INCBIN_U16("data/text/spanish/file_select_10.bin");
const u16 sFileSelectTextSpanish_11[] = INCBIN_U16("data/text/spanish/file_select_11.bin");
const u16 sFileSelectTextSpanish_12[] = INCBIN_U16("data/text/spanish/file_select_12.bin");
const u16 sFileSelectTextSpanish_13[] = INCBIN_U16("data/text/spanish/file_select_13.bin");
const u16 sFileSelectTextSpanish_14[] = INCBIN_U16("data/text/spanish/file_select_14.bin");
const u16 sFileSelectTextSpanish_15[] = INCBIN_U16("data/text/spanish/file_select_15.bin");
const u16 sFileSelectTextSpanish_16[] = INCBIN_U16("data/text/spanish/file_select_16.bin");
const u16 sFileSelectTextSpanish_17[] = INCBIN_U16("data/text/spanish/file_select_17.bin");
const u16 sFileSelectTextSpanish_18[] = INCBIN_U16("data/text/spanish/file_select_18.bin");
const u16 sFileSelectTextSpanish_19[] = INCBIN_U16("data/text/spanish/file_select_19.bin");
const u16 sFileSelectTextSpanish_20[] = INCBIN_U16("data/text/spanish/file_select_20.bin");
const u16 sFileSelectTextSpanish_21[] = INCBIN_U16("data/text/spanish/file_select_21.bin");
const u16 sFileSelectTextSpanish_22[] = INCBIN_U16("data/text/spanish/file_select_22.bin");
const u16 sFileSelectTextSpanish_23[] = INCBIN_U16("data/text/spanish/file_select_23.bin");
const u16 sFileSelectTextSpanish_24[] = INCBIN_U16("data/text/spanish/file_select_24.bin");
const u16 sFileSelectEmptyFileText_0[] = INCBIN_U16("data/text/empty_file_0.bin");
const u16 sFileSelectEmptyFileText_1[] = INCBIN_U16("data/text/empty_file_1.bin");
const u32 sFileSelectBgGfx[4171] = INCBIN_U32("data/menus/file_select/bg.gfx.lz");
const u32 sFileSelectBg3Tilemap[368] = INCBIN_U32("data/menus/file_select/bg3.tm.lz");
const u16 sFileSelectBgPal[16 * PAL_ROW] = INCBIN_U16("data/menus/file_select/bg.pal");
