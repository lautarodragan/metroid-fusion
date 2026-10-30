#include "macros.h"
#include "oam.h"

#include "data/ending_data.h"

#include "structs/ending.h"

#include "constants/ending.h"

#include "gba/memory.h"

const u16 sPal_7478A0[PAL_ROW * 3] = INCBIN_U16("data/ending/7478a0.pal");

const u32 sCreditsCharacterGfx[1280] = INCBIN_U32("data/ending/credits_character.gfx");
const u32 sCreditsCopyrightText1_Gfx[112] = INCBIN_U32("data/ending/copyright_text_1.gfx");
const u32 sCreditsCopyrightText2_Gfx[144] = INCBIN_U32("data/ending/copyright_text_2.gfx");
const u32 sCreditsCopyrightText3_Gfx[176] = INCBIN_U32("data/ending/copyright_text_3.gfx");
const u32 sCreditsCopyrightText4_Gfx[144] = INCBIN_U32("data/ending/copyright_text_4.gfx");

const u16 sPal_749600[PAL_ROW * 6] = INCBIN_U16("data/ending/749600.pal");
const u16 sPal_7496c0[PAL_ROW * 10] = INCBIN_U16("data/ending/7496c0.pal");

const u16 sPreResultsSamusWithoutHelmetBgPal[PAL_ROW * 10] = INCBIN_U16("data/ending/samus_without_helmet_bg.pal");
const u16 sPreResultsSamusSuitlessBgPal[PAL_ROW * 10] = INCBIN_U16("data/ending/samus_suitless_bg.pal");
const u16 sPreResultsSamusObjPal[PAL_ROW * 16] = INCBIN_U16("data/ending/samus_obj.pal");

const u16 sOamFrame_749c80[OAM_DATA_SIZE(25)] = {
    25,
    OAM_ENTRY(-18, -75, OAM_DIMS_32x32, OAM_NO_FLIP, 0x0, 2, 0),
    OAM_ENTRY(-10, -43, OAM_DIMS_16x8, OAM_NO_FLIP, 0x47, 2, 0),
    OAM_ENTRY(-34, -43, OAM_DIMS_32x16, OAM_NO_FLIP, 0x44, 3, 0),
    OAM_ENTRY(-2, -43, OAM_DIMS_32x16, OAM_NO_FLIP, 0x48, 3, 0),
    OAM_ENTRY(-34, -59, OAM_DIMS_16x16, OAM_NO_FLIP, 0x4, 1, 0),
    OAM_ENTRY(-34, -27, OAM_DIMS_16x32, OAM_NO_FLIP, 0xd, 5, 0),
    OAM_ENTRY(-26, 5, OAM_DIMS_8x16, OAM_NO_FLIP, 0x8e, 5, 0),
    OAM_ENTRY(-18, -27, OAM_DIMS_8x8, OAM_NO_FLIP, 0xf, 5, 0),
    OAM_ENTRY(14, -59, OAM_DIMS_16x16, OAM_NO_FLIP, 0xa, 1, 0),
    OAM_ENTRY(30, -51, OAM_DIMS_8x16, OAM_NO_FLIP, 0x2c, 4, 0),
    OAM_ENTRY(22, -35, OAM_DIMS_16x16, OAM_NO_FLIP, 0x6b, 3, 0),
    OAM_ENTRY(6, -27, OAM_DIMS_32x16, OAM_NO_FLIP, 0x89, 6, 0),
    OAM_ENTRY(-10, -27, OAM_DIMS_16x32, OAM_NO_FLIP, 0x10, 7, 0),
    OAM_ENTRY(-18, -19, OAM_DIMS_8x32, OAM_NO_FLIP, 0x2f, 4, 0),
    OAM_ENTRY(6, -11, OAM_DIMS_16x16, OAM_NO_FLIP, 0x90, 3, 0),
    OAM_ENTRY(-10, -3, OAM_DIMS_16x32, OAM_NO_FLIP, 0x13, 3, 0),
    OAM_ENTRY(-10, 29, OAM_DIMS_16x16, OAM_NO_FLIP, 0x93, 6, 0),
    OAM_ENTRY(-18, 13, OAM_DIMS_8x32, OAM_NO_FLIP, 0x52, 7, 0),
    OAM_ENTRY(6, 5, OAM_DIMS_16x32, OAM_NO_FLIP, 0x19, 7, 0),
    OAM_ENTRY(14, 21, OAM_DIMS_16x32, OAM_NO_FLIP, 0x5a, 7, 0),
    OAM_ENTRY(38, 69, OAM_DIMS_8x16, OAM_NO_FLIP, 0x5e, 9, 0),
    OAM_ENTRY(-18, 45, OAM_DIMS_16x32, OAM_NO_FLIP, 0x16, 9, 0),
    OAM_ENTRY(-26, 69, OAM_DIMS_8x8, OAM_NO_FLIP, 0x75, 9, 0),
    OAM_ENTRY(-26, 77, OAM_DIMS_16x8, OAM_NO_FLIP, 0x95, 8, 0),
    OAM_ENTRY(22, 53, OAM_DIMS_16x32, OAM_NO_FLIP, 0x1c, 9, 0),
};

const u16 sOamFrame_749d18[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-34, -75, OAM_DIMS_64x64, OAM_NO_FLIP, 0xc0, 1, 0),
    OAM_ENTRY(30, -75, OAM_DIMS_8x32, OAM_NO_FLIP, 0xc8, 1, 0),
    OAM_ENTRY(30, -43, OAM_DIMS_8x32, OAM_NO_FLIP, 0x148, 1, 0),
    OAM_ENTRY(-34, -11, OAM_DIMS_64x64, OAM_NO_FLIP, 0x1c0, 1, 0),
    OAM_ENTRY(-34, 53, OAM_DIMS_64x32, OAM_NO_FLIP, 0x2c0, 1, 0),
    OAM_ENTRY(30, 53, OAM_DIMS_16x32, OAM_NO_FLIP, 0x2c8, 1, 0),
};

const u16 sOamFrame_749d3e[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-30, -76, OAM_DIMS_64x64, OAM_NO_FLIP, 0xca, 1, 0),
    OAM_ENTRY(-30, -12, OAM_DIMS_64x64, OAM_NO_FLIP, 0x1ca, 1, 0),
    OAM_ENTRY(-30, 52, OAM_DIMS_64x32, OAM_NO_FLIP, 0x2ca, 1, 0),
    OAM_ENTRY(34, 52, OAM_DIMS_16x32, OAM_NO_FLIP, 0x2d2, 1, 0),
};

const u16 sEnding_0_Pal[PAL_ROW * 16] = INCBIN_U16("data/ending/ending_0.pal");
const u16 sEnding_1_Pal[PAL_ROW * 16] = INCBIN_U16("data/ending/ending_1.pal");
const u16 sEnding_2_Pal[PAL_ROW * 16] = INCBIN_U16("data/ending/ending_2.pal");
const u16 sEnding_3_Pal[PAL_ROW * 16] = INCBIN_U16("data/ending/ending_3.pal");
const u16 sEnding_4_Pal[PAL_ROW * 16] = INCBIN_U16("data/ending/ending_4.pal");
const u16 sResultsTextPal[PAL_ROW * 4] = INCBIN_U16("data/ending/results_text.pal");

const u16 sOamFrame_74a7d8[] = INCBIN_U16("data/oam_frames/74a7d8.bin");
const u16 sOamFrame_74a7f8[] = INCBIN_U16("data/oam_frames/74a7f8.bin");
const u16 sOamFrame_74a812[] = INCBIN_U16("data/oam_frames/74a812.bin");
const u16 sOamFrame_74a826[] = INCBIN_U16("data/oam_frames/74a826.bin");
const u16 sOamFrame_74a82e[] = INCBIN_U16("data/oam_frames/74a82e.bin");
const u16 sOamFrame_74a836[] = INCBIN_U16("data/oam_frames/74a836.bin");
const u16 sOamFrame_74a83e[] = INCBIN_U16("data/oam_frames/74a83e.bin");
const u16 sOamFrame_74a846[] = INCBIN_U16("data/oam_frames/74a846.bin");
const u16 sOamFrame_74a84e[] = INCBIN_U16("data/oam_frames/74a84e.bin");
const u16 sOamFrame_74a856[] = INCBIN_U16("data/oam_frames/74a856.bin");
const u16 sOamFrame_74a85e[] = INCBIN_U16("data/oam_frames/74a85e.bin");
const u16 sOamFrame_74a866[] = INCBIN_U16("data/oam_frames/74a866.bin");
const u16 sOamFrame_74a86e[] = INCBIN_U16("data/oam_frames/74a86e.bin");
const u16 sOamFrame_74a888[] = INCBIN_U16("data/oam_frames/74a888.bin");
const u16 sOamFrame_74a890[] = INCBIN_U16("data/oam_frames/74a890.bin");
const u16 sOamFrame_74a898[] = INCBIN_U16("data/oam_frames/74a898.bin");
const u16 sOamFrame_74a8a0[] = INCBIN_U16("data/oam_frames/74a8a0.bin");
const u16 sOamFrame_74a8a8[] = INCBIN_U16("data/oam_frames/74a8a8.bin");
const u16 sOamFrame_74a8b0[] = INCBIN_U16("data/oam_frames/74a8b0.bin");
const u16 sOamFrame_74a8b8[] = INCBIN_U16("data/oam_frames/74a8b8.bin");
const u16 sOamFrame_74a8c0[] = INCBIN_U16("data/oam_frames/74a8c0.bin");
const u16 sOamFrame_74a8c8[] = INCBIN_U16("data/oam_frames/74a8c8.bin");
const u16 sOamFrame_74a8d0[] = INCBIN_U16("data/oam_frames/74a8d0.bin");
const u16 sOamFrame_74a8d8[] = INCBIN_U16("data/oam_frames/74a8d8.bin");
const u16 sOamFrame_74a8e0[] = INCBIN_U16("data/oam_frames/74a8e0.bin");
const u16 sOamFrame_74a900[] = INCBIN_U16("data/oam_frames/74a900.bin");
const u16 sOamFrame_74a908[] = INCBIN_U16("data/oam_frames/74a908.bin");
const u16 sOamFrame_74a910[] = INCBIN_U16("data/oam_frames/74a910.bin");
const u16 sOamFrame_74a918[] = INCBIN_U16("data/oam_frames/74a918.bin");
const u16 sOamFrame_74a920[] = INCBIN_U16("data/oam_frames/74a920.bin");
const u16 sOamFrame_74a928[] = INCBIN_U16("data/oam_frames/74a928.bin");
const u16 sOamFrame_74a930[] = INCBIN_U16("data/oam_frames/74a930.bin");
const u16 sOamFrame_74a938[] = INCBIN_U16("data/oam_frames/74a938.bin");
const u16 sOamFrame_74a940[] = INCBIN_U16("data/oam_frames/74a940.bin");
const u16 sOamFrame_74a948[] = INCBIN_U16("data/oam_frames/74a948.bin");
const u16 sOamFrame_74a950[] = INCBIN_U16("data/oam_frames/74a950.bin");
const u16 sOamFrame_74a958[] = INCBIN_U16("data/oam_frames/74a958.bin");
const u16 sOamFrame_74a960[] = INCBIN_U16("data/oam_frames/74a960.bin");
const u16 sOamFrame_74a968[] = INCBIN_U16("data/oam_frames/74a968.bin");
const u16 sOamFrame_74a970[] = INCBIN_U16("data/oam_frames/74a970.bin");
const u16 sOamFrame_74a978[] = INCBIN_U16("data/oam_frames/74a978.bin");
const u16 sOamFrame_74a980[] = INCBIN_U16("data/oam_frames/74a980.bin");
const u16 sOamFrame_74a988[] = INCBIN_U16("data/oam_frames/74a988.bin");
const u16 sOamFrame_74a9a8[] = INCBIN_U16("data/oam_frames/74a9a8.bin");
const u16 sOamFrame_74a9c8[] = INCBIN_U16("data/oam_frames/74a9c8.bin");
const u16 sOamFrame_74a9e2[] = INCBIN_U16("data/oam_frames/74a9e2.bin");
const u16 sOamFrame_74aa02[] = INCBIN_U16("data/oam_frames/74aa02.bin");
const u16 sOamFrame_74aa0a[] = INCBIN_U16("data/oam_frames/74aa0a.bin");
const u16 sOamFrame_74aa12[] = INCBIN_U16("data/oam_frames/74aa12.bin");
const u16 sOamFrame_74aa1a[] = INCBIN_U16("data/oam_frames/74aa1a.bin");
const u16 sOamFrame_74aa22[] = INCBIN_U16("data/oam_frames/74aa22.bin");
const u16 sOamFrame_74aa2a[] = INCBIN_U16("data/oam_frames/74aa2a.bin");
const u16 sOamFrame_74aa32[] = INCBIN_U16("data/oam_frames/74aa32.bin");
const u16 sOamFrame_74aa3a[] = INCBIN_U16("data/oam_frames/74aa3a.bin");
const u16 sOamFrame_74aa42[] = INCBIN_U16("data/oam_frames/74aa42.bin");
const u16 sOamFrame_74aa4a[] = INCBIN_U16("data/oam_frames/74aa4a.bin");
const u16 sOamFrame_74aa52[] = INCBIN_U16("data/oam_frames/74aa52.bin");
const u16 sOamFrame_74aa5a[] = INCBIN_U16("data/oam_frames/74aa5a.bin");
const u16 sOamFrame_74aa62[] = INCBIN_U16("data/oam_frames/74aa62.bin");
const u16 sOamFrame_74aa6a[] = INCBIN_U16("data/oam_frames/74aa6a.bin");
const u16 sOamFrame_74aa72[] = INCBIN_U16("data/oam_frames/74aa72.bin");
const u16 sOamFrame_74aa7a[] = INCBIN_U16("data/oam_frames/74aa7a.bin");
const u16 sOamFrame_74aa82[] = INCBIN_U16("data/oam_frames/74aa82.bin");
const u16 sOamFrame_74aaae[] = INCBIN_U16("data/oam_frames/74aaae.bin");
const u16 sOamFrame_74aab6[] = INCBIN_U16("data/oam_frames/74aab6.bin");
const u16 sOamFrame_74aabe[] = INCBIN_U16("data/oam_frames/74aabe.bin");
const u16 sOamFrame_74aac6[] = INCBIN_U16("data/oam_frames/74aac6.bin");
const u16 sOamFrame_74aace[] = INCBIN_U16("data/oam_frames/74aace.bin");
const u16 sOamFrame_74aad6[] = INCBIN_U16("data/oam_frames/74aad6.bin");
const u16 sOamFrame_74aade[] = INCBIN_U16("data/oam_frames/74aade.bin");
const u16 sOamFrame_74aae6[] = INCBIN_U16("data/oam_frames/74aae6.bin");
const u16 sOamFrame_74aaee[] = INCBIN_U16("data/oam_frames/74aaee.bin");
const u16 sOamFrame_74aaf6[] = INCBIN_U16("data/oam_frames/74aaf6.bin");
const u16 sOamFrame_74aafe[] = INCBIN_U16("data/oam_frames/74aafe.bin");
const u16 sOamFrame_74ab06[] = INCBIN_U16("data/oam_frames/74ab06.bin");
const u16 sOamFrame_74ab0e[] = INCBIN_U16("data/oam_frames/74ab0e.bin");
const u16 sOamFrame_74ab16[] = INCBIN_U16("data/oam_frames/74ab16.bin");
const u16 sOamFrame_74ab1e[] = INCBIN_U16("data/oam_frames/74ab1e.bin");
const u16 sOamFrame_74ab26[] = INCBIN_U16("data/oam_frames/74ab26.bin");
const u16 sOamFrame_74ab2e[] = INCBIN_U16("data/oam_frames/74ab2e.bin");
const u16 sOamFrame_74ab36[] = INCBIN_U16("data/oam_frames/74ab36.bin");
const u16 sOamFrame_74ab3e[] = INCBIN_U16("data/oam_frames/74ab3e.bin");
const u16 sOamFrame_74ab46[] = INCBIN_U16("data/oam_frames/74ab46.bin");
const u16 sOamFrame_74ab4e[] = INCBIN_U16("data/oam_frames/74ab4e.bin");
const u16 sOamFrame_74ab62[] = INCBIN_U16("data/oam_frames/74ab62.bin");
const u16 sOamFrame_74ab82[] = INCBIN_U16("data/oam_frames/74ab82.bin");
const u16 sOamFrame_74ab9c[] = INCBIN_U16("data/oam_frames/74ab9c.bin");
const u16 sOamFrame_74abc2[] = INCBIN_U16("data/oam_frames/74abc2.bin");
const u16 sOamFrame_74abca[] = INCBIN_U16("data/oam_frames/74abca.bin");
const u16 sOamFrame_74abd2[] = INCBIN_U16("data/oam_frames/74abd2.bin");
const u16 sOamFrame_74abda[] = INCBIN_U16("data/oam_frames/74abda.bin");
const u16 sOamFrame_74abe2[] = INCBIN_U16("data/oam_frames/74abe2.bin");
const u16 sOamFrame_74abea[] = INCBIN_U16("data/oam_frames/74abea.bin");
const u16 sOamFrame_74abf2[] = INCBIN_U16("data/oam_frames/74abf2.bin");
const u16 sOamFrame_74abfa[] = INCBIN_U16("data/oam_frames/74abfa.bin");
const u16 sOamFrame_74ac02[] = INCBIN_U16("data/oam_frames/74ac02.bin");
const u16 sOamFrame_74ac0a[] = INCBIN_U16("data/oam_frames/74ac0a.bin");
const u16 sOamFrame_74ac12[] = INCBIN_U16("data/oam_frames/74ac12.bin");
const u16 sOamFrame_74ac1a[] = INCBIN_U16("data/oam_frames/74ac1a.bin");
const u16 sOamFrame_74ac22[] = INCBIN_U16("data/oam_frames/74ac22.bin");
const u16 sOamFrame_74ac2a[] = INCBIN_U16("data/oam_frames/74ac2a.bin");
const u16 sOamFrame_74ac32[] = INCBIN_U16("data/oam_frames/74ac32.bin");
const u16 sOamFrame_74ac3a[] = INCBIN_U16("data/oam_frames/74ac3a.bin");
const u16 sOamFrame_74ac42[] = INCBIN_U16("data/oam_frames/74ac42.bin");
const u16 sOamFrame_74ac4a[] = INCBIN_U16("data/oam_frames/74ac4a.bin");
const u16 sOamFrame_74ac52[] = INCBIN_U16("data/oam_frames/74ac52.bin");
const u16 sOamFrame_74ac6c[] = INCBIN_U16("data/oam_frames/74ac6c.bin");
const u16 sOamFrame_74ac74[] = INCBIN_U16("data/oam_frames/74ac74.bin");
const u16 sOamFrame_74ac7c[] = INCBIN_U16("data/oam_frames/74ac7c.bin");
const u16 sOamFrame_74ac84[] = INCBIN_U16("data/oam_frames/74ac84.bin");
const u16 sOamFrame_74ac8c[] = INCBIN_U16("data/oam_frames/74ac8c.bin");
const u16 sOamFrame_74ac94[] = INCBIN_U16("data/oam_frames/74ac94.bin");
const u16 sOamFrame_74ac9c[] = INCBIN_U16("data/oam_frames/74ac9c.bin");
const u16 sOamFrame_74aca4[] = INCBIN_U16("data/oam_frames/74aca4.bin");
const u16 sOamFrame_74acac[] = INCBIN_U16("data/oam_frames/74acac.bin");
const u16 sOamFrame_74acb4[] = INCBIN_U16("data/oam_frames/74acb4.bin");
const u16 sOamFrame_74acbc[] = INCBIN_U16("data/oam_frames/74acbc.bin");
const u16 sOamFrame_74acc4[] = INCBIN_U16("data/oam_frames/74acc4.bin");
const u16 sOamFrame_74ace4[] = INCBIN_U16("data/oam_frames/74ace4.bin");
const u16 sOamFrame_74acec[] = INCBIN_U16("data/oam_frames/74acec.bin");
const u16 sOamFrame_74acf4[] = INCBIN_U16("data/oam_frames/74acf4.bin");
const u16 sOamFrame_74acfc[] = INCBIN_U16("data/oam_frames/74acfc.bin");
const u16 sOamFrame_74ad04[] = INCBIN_U16("data/oam_frames/74ad04.bin");
const u16 sOamFrame_74ad0c[] = INCBIN_U16("data/oam_frames/74ad0c.bin");
const u16 sOamFrame_74ad14[] = INCBIN_U16("data/oam_frames/74ad14.bin");
const u16 sOamFrame_74ad1c[] = INCBIN_U16("data/oam_frames/74ad1c.bin");
const u16 sOamFrame_74ad24[] = INCBIN_U16("data/oam_frames/74ad24.bin");
const u16 sOamFrame_74ad2c[] = INCBIN_U16("data/oam_frames/74ad2c.bin");
const u16 sOamFrame_74ad34[] = INCBIN_U16("data/oam_frames/74ad34.bin");
const u16 sOamFrame_74ad3c[] = INCBIN_U16("data/oam_frames/74ad3c.bin");
const u16 sOamFrame_74ad44[] = INCBIN_U16("data/oam_frames/74ad44.bin");
const u16 sOamFrame_74ad4c[] = INCBIN_U16("data/oam_frames/74ad4c.bin");
const u16 sOamFrame_74ad54[] = INCBIN_U16("data/oam_frames/74ad54.bin");
const u16 sOamFrame_74ad5c[] = INCBIN_U16("data/oam_frames/74ad5c.bin");
const u16 sOamFrame_74ad64[] = INCBIN_U16("data/oam_frames/74ad64.bin");
const u16 sOamFrame_74ad6c[] = INCBIN_U16("data/oam_frames/74ad6c.bin");
const u16 sOamFrame_74ad8c[] = INCBIN_U16("data/oam_frames/74ad8c.bin");
const u16 sOamFrame_74adac[] = INCBIN_U16("data/oam_frames/74adac.bin");
const u16 sOamFrame_74adc6[] = INCBIN_U16("data/oam_frames/74adc6.bin");
const u16 sOamFrame_74ade6[] = INCBIN_U16("data/oam_frames/74ade6.bin");
const u16 sOamFrame_74adee[] = INCBIN_U16("data/oam_frames/74adee.bin");
const u16 sOamFrame_74adf6[] = INCBIN_U16("data/oam_frames/74adf6.bin");
const u16 sOamFrame_74adfe[] = INCBIN_U16("data/oam_frames/74adfe.bin");
const u16 sOamFrame_74ae06[] = INCBIN_U16("data/oam_frames/74ae06.bin");
const u16 sOamFrame_74ae0e[] = INCBIN_U16("data/oam_frames/74ae0e.bin");
const u16 sOamFrame_74ae16[] = INCBIN_U16("data/oam_frames/74ae16.bin");
const u16 sOamFrame_74ae1e[] = INCBIN_U16("data/oam_frames/74ae1e.bin");
const u16 sOamFrame_74ae26[] = INCBIN_U16("data/oam_frames/74ae26.bin");
const u16 sOamFrame_74ae2e[] = INCBIN_U16("data/oam_frames/74ae2e.bin");
const u16 sOamFrame_74ae36[] = INCBIN_U16("data/oam_frames/74ae36.bin");
const u16 sOamFrame_74ae3e[] = INCBIN_U16("data/oam_frames/74ae3e.bin");
const u16 sOamFrame_74ae46[] = INCBIN_U16("data/oam_frames/74ae46.bin");
const u16 sOamFrame_74ae4e[] = INCBIN_U16("data/oam_frames/74ae4e.bin");
const u16 sOamFrame_74ae56[] = INCBIN_U16("data/oam_frames/74ae56.bin");
const u16 sOamFrame_74ae5e[] = INCBIN_U16("data/oam_frames/74ae5e.bin");
const u16 sOamFrame_74ae84[] = INCBIN_U16("data/oam_frames/74ae84.bin");
const u16 sOamFrame_74ae8c[] = INCBIN_U16("data/oam_frames/74ae8c.bin");
const u16 sOamFrame_74ae94[] = INCBIN_U16("data/oam_frames/74ae94.bin");
const u16 sOamFrame_74ae9c[] = INCBIN_U16("data/oam_frames/74ae9c.bin");
const u16 sOamFrame_74aea4[] = INCBIN_U16("data/oam_frames/74aea4.bin");
const u16 sOamFrame_74aeac[] = INCBIN_U16("data/oam_frames/74aeac.bin");
const u16 sOamFrame_74aeb4[] = INCBIN_U16("data/oam_frames/74aeb4.bin");
const u16 sOamFrame_74aebc[] = INCBIN_U16("data/oam_frames/74aebc.bin");
const u16 sOamFrame_74aec4[] = INCBIN_U16("data/oam_frames/74aec4.bin");
const u16 sOamFrame_74aecc[] = INCBIN_U16("data/oam_frames/74aecc.bin");
const u16 sOamFrame_74aed4[] = INCBIN_U16("data/oam_frames/74aed4.bin");
const u16 sOamFrame_74aedc[] = INCBIN_U16("data/oam_frames/74aedc.bin");
const u16 sOamFrame_74aee4[] = INCBIN_U16("data/oam_frames/74aee4.bin");
const u16 sOamFrame_74aeec[] = INCBIN_U16("data/oam_frames/74aeec.bin");
const u16 sOamFrame_74aef4[] = INCBIN_U16("data/oam_frames/74aef4.bin");
const u16 sOamFrame_74aefc[] = INCBIN_U16("data/oam_frames/74aefc.bin");
const u16 sOamFrame_74af04[] = INCBIN_U16("data/oam_frames/74af04.bin");
const u16 sOamFrame_74af0c[] = INCBIN_U16("data/oam_frames/74af0c.bin");
const u16 sOamFrame_74af14[] = INCBIN_U16("data/oam_frames/74af14.bin");
const u16 sOamFrame_74af1c[] = INCBIN_U16("data/oam_frames/74af1c.bin");
const u16 sOamFrame_74af42[] = INCBIN_U16("data/oam_frames/74af42.bin");
const u16 sOamFrame_74af62[] = INCBIN_U16("data/oam_frames/74af62.bin");
const u16 sOamFrame_74af7c[] = INCBIN_U16("data/oam_frames/74af7c.bin");
const u16 sOamFrame_74af96[] = INCBIN_U16("data/oam_frames/74af96.bin");
const u16 sOamFrame_74af9e[] = INCBIN_U16("data/oam_frames/74af9e.bin");
const u16 sOamFrame_74afa6[] = INCBIN_U16("data/oam_frames/74afa6.bin");
const u16 sOamFrame_74afae[] = INCBIN_U16("data/oam_frames/74afae.bin");
const u16 sOamFrame_74afb6[] = INCBIN_U16("data/oam_frames/74afb6.bin");
const u16 sOamFrame_74afbe[] = INCBIN_U16("data/oam_frames/74afbe.bin");
const u16 sOamFrame_74afc6[] = INCBIN_U16("data/oam_frames/74afc6.bin");
const u16 sOamFrame_74afce[] = INCBIN_U16("data/oam_frames/74afce.bin");
const u16 sOamFrame_74afd6[] = INCBIN_U16("data/oam_frames/74afd6.bin");
const u16 sOamFrame_74afde[] = INCBIN_U16("data/oam_frames/74afde.bin");
const u16 sOamFrame_74afe6[] = INCBIN_U16("data/oam_frames/74afe6.bin");
const u16 sOamFrame_74afee[] = INCBIN_U16("data/oam_frames/74afee.bin");
const u16 sOamFrame_74aff6[] = INCBIN_U16("data/oam_frames/74aff6.bin");
const u16 sOamFrame_74affe[] = INCBIN_U16("data/oam_frames/74affe.bin");
const u16 sOamFrame_74b01e[] = INCBIN_U16("data/oam_frames/74b01e.bin");
const u16 sOamFrame_74b026[] = INCBIN_U16("data/oam_frames/74b026.bin");
const u16 sOamFrame_74b02e[] = INCBIN_U16("data/oam_frames/74b02e.bin");
const u16 sOamFrame_74b036[] = INCBIN_U16("data/oam_frames/74b036.bin");
const u16 sOamFrame_74b03e[] = INCBIN_U16("data/oam_frames/74b03e.bin");
const u16 sOamFrame_74b046[] = INCBIN_U16("data/oam_frames/74b046.bin");
const u16 sOamFrame_74b04e[] = INCBIN_U16("data/oam_frames/74b04e.bin");
const u16 sOamFrame_74b056[] = INCBIN_U16("data/oam_frames/74b056.bin");
const u16 sOamFrame_74b05e[] = INCBIN_U16("data/oam_frames/74b05e.bin");
const u16 sOamFrame_74b066[] = INCBIN_U16("data/oam_frames/74b066.bin");
const u16 sOamFrame_74b06e[] = INCBIN_U16("data/oam_frames/74b06e.bin");
const u16 sOamFrame_74b076[] = INCBIN_U16("data/oam_frames/74b076.bin");
const u16 sOamFrame_74b07e[] = INCBIN_U16("data/oam_frames/74b07e.bin");
const u16 sOamFrame_74b086[] = INCBIN_U16("data/oam_frames/74b086.bin");
const u16 sOamFrame_74b08e[] = INCBIN_U16("data/oam_frames/74b08e.bin");

const struct CreditsEntry sCredits[310] = {
	[0] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[1] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[2] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "               "
	},
	[3] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[4] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[5] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "           PRODUCER"
	},
	[6] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[7] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Izushi Takehiro"
	},
	[8] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = ""
	},
	[9] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[10] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[11] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "               "
	},
	[12] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[13] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[14] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "        CHIEF DIRECTOR"
	},
	[15] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[16] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Sakamoto Yoshio"
	},
	[17] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[18] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[19] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[20] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "               "
	},
	[21] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[22] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[23] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "        SYSTEM DIRECTOR"
	},
	[24] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[25] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Hosokawa Takehiko"
	},
	[26] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[27] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[28] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[29] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "        SCENARIO & STORY"
	},
	[30] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[31] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Sakamoto Yoshio"
	},
	[32] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[33] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[34] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[35] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "          GAME DESIGN"
	},
	[36] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[37] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Yamane Tomoyoshi"
	},
	[38] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[39] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Hosokawa Takehiko"
	},
	[40] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[41] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[42] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[43] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "         COURSE DESIGN"
	},
	[44] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[45] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "          Ueda Masani"
	},
	[46] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[47] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Nakada Ryuichi"
	},
	[48] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[49] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[50] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[51] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "        VISUAL DIRECTOR"
	},
	[52] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[53] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Yamane Tomoyoshi"
	},
	[54] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[55] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[56] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[57] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "         SAMUS DESIGN"
	},
	[58] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[59] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Sano Shinya"
	},
	[60] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[61] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[62] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[63] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "     SAMUS ORIGINAL DESIGN"
	},
	[64] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[65] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Kiyotake Hiroji"
	},
	[66] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[67] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[68] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[69] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "    ENEMY CHARACTER DESIGN"
	},
	[70] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[71] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Yamane Tomoyoshi"
	},
	[72] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[73] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Hirano Isao"
	},
	[74] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[75] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Sano Shinya"
	},
	[76] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[77] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "      Matsushita Tadashi"
	},
	[78] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[79] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[80] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[81] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "   BACKGROUND GRAPHIC DESIGN"
	},
	[82] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[83] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Morisawa Takayasu"
	},
	[84] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[85] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Miyamoto Fumiko"
	},
	[86] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[87] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[88] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[89] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "        GRAPHIC DESIGN"
	},
	[90] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[91] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Momose Hiroshi"
	},
	[92] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[93] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Sakiyama Chiharu"
	},
	[94] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[95] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[96] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[97] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "       PROGRAM DIRECTOR"
	},
	[98] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[99] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Yamano Katsuya"
	},
	[100] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[101] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[102] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[103] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "       SAMUS PROGRAMMING"
	},
	[104] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[105] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Katsuki Yoshinori"
	},
	[106] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[107] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[108] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[109] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = " ENEMY CHARACTER PROGRAMMING"
	},
	[110] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[111] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Yamano Katsuya"
	},
	[112] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[113] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[114] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[115] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "      SYSTEM PROGRAMMING"
	},
	[116] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[117] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Ozaki Nobuhiro"
	},
	[118] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[119] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[120] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[121] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "   CINEMA SCENE PROGRAMMING"
	},
	[122] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[123] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Nakae Eisaku"
	},
	[124] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[125] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[126] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[127] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "       TOOL PROGRAMMING"
	},
	[128] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[129] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Harada Takahiro"
	},
	[130] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[131] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "          Fukui Kota"
	},
	[132] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[133] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Katsuki Yoshinori"
	},
	[134] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[135] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Ozaki Nobuhiro"
	},
	[136] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[137] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Momose Hiroshi"
	},
	[138] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[139] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[140] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[141] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "        SOUND DIRECTOR"
	},
	[142] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[143] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Yamamoto Kenji"
	},
	[144] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[145] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[146] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[147] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "      MUSIC COMPOSITION"
	},
	[148] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[149] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Hamano Minako"
	},
	[150] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[151] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Fujiwara Akira"
	},
	[152] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[153] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[154] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[155] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "  SOUND EFFECTS & PROGRAMMING"
	},
	[156] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[157] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Fujii Takaya"
	},
	[158] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[159] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[160] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[161] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "        PACKAGE DESIGN"
	},
	[162] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[163] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Nakamichi Sachiko"
	},
	[164] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[165] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[166] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[167] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "        MANUAL DESIGN"
	},
	[168] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[169] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "      Nakamichi Sachiko"
	},
	[170] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[171] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Itani Kiyomi"
	},
	[172] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[173] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Takahashi Yasuko"
	},
	[174] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[175] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[176] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[177] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "         COORDINATION"
	},
	[178] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[179] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Harada Takahiro"
	},
	[180] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[181] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[182] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[183] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "  INTERNATIONAL COORDINATION"
	},
	[184] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[185] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Yamazaki Sakae"
	},
	[186] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[187] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[188] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[189] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "            DEBUG"
	},
	[190] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[191] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       SUPER MARIO CLUB"
	},
	[192] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[193] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[194] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[195] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[196] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[197] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[198] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[199] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "        SPECIAL THANKS"
	},
	[200] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[201] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Matsumura Satoshi"
	},
	[202] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[203] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "      "
	},
	[204] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[205] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[206] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[207] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[208] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "               "
	},
	[209] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[210] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[211] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "               "
	},
	[212] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[213] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[214] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "               "
	},
	[215] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "   NOA ENGLISH LOCALIZATION"
	},
	[216] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[217] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[218] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "   LOCALIZATION MANAGEMENT"
	},
	[219] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[220] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Jeff Miller"
	},
	[221] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[222] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Leslie Swan"
	},
	[223] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[224] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[225] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[226] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "         LOCALIZATION"
	},
	[227] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[228] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Scot Ritchey"
	},
	[229] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[230] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Nathan Bihldorff"
	},
	[231] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[232] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Tim O-Leary"
	},
	[233] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[234] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[235] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[236] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "       ENGINEERING DEBUG"
	},
	[237] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[238] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Raychole L'Anett"
	},
	[239] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[240] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Robert Crombie"
	},
	[241] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[242] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Kirk Buchanan"
	},
	[243] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[244] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Yoshinobu Mantani"
	},
	[245] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[246] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[247] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[248] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Scott Callahan"
	},
	[249] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[250] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Don Dillinger"
	},
	[251] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[252] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Hisako Sakauchi"
	},
	[253] = {
		.type = CREDIT_LINE_TYPE_RED,
		.text = "               "
	},
	[254] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[255] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[256] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "        SPECIAL THANKS"
	},
	[257] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[258] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "       Tatsumi Kimishima"
	},
	[259] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[260] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Mike Fukuda"
	},
	[261] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[262] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "        Hiroshi Kamada"
	},
	[263] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[264] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[265] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[266] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[267] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[268] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[269] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "               "
	},
	[270] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[271] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[272] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "               "
	},
	[273] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[274] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[275] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "               "
	},
	[276] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[277] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[278] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "      EXECUTIVE PRODUCER"
	},
	[279] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[280] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "         Iwata Satoru"
	},
	[281] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[282] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = ""
	},
	[283] = {
		.type = CREDIT_LINE_TYPE_BLUE,
		.text = "               "
	},
	[284] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[285] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[286] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[287] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[288] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[289] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[290] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[291] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[292] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[293] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[294] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[295] = {
		.type = CREDIT_LINE_TYPE_WHITE_BIG,
		.text = "               "
	},
	[296] = {
		.type = CREDIT_LINE_TYPE_ALL_RIGHTS,
		.text = ""
	},
	[297] = {
		.type = CREDIT_LINE_TYPE_THE_COPYRIGHT,
		.text = ""
	},
	[298] = {
		.type = CREDIT_LINE_TYPE_SCENARIO,
		.text = ""
	},
	[299] = {
		.type = CREDIT_LINE_TYPE_RESERVED,
		.text = ""
	},
	[300] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[301] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[302] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[303] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[304] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[305] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[306] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[307] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[308] = {
		.type = CREDIT_LINE_TYPE_BLANK,
		.text = ""
	},
	[309] = {
		.type = CREDIT_LINE_TYPE_END,
		.text = ""
	},
};

const struct EndingImageTextOam sEndingImageTextOamEnglishLines[6] = {
    { 2, 0, 0, 120, 40, (u16*)sOamFrame_74a812 },
    { 2, 0, 0, 120, 60, (u16*)sOamFrame_74a7d8 },
    { 2, 0, 0, 120, 92, (u16*)sOamFrame_74a86e },
    { 2, 0, 0, 120, 108, (u16*)sOamFrame_74a8e0 },
    { 2, 0, 0, 124, 128, (u16*)sOamFrame_74a7f8 },
    { 2, 0, 0, 120, 158, (u16*)sOamFrame_74a988 }
};
const struct EndingImageTextOam sEndingImageTextOamEnglish_0[9] = {
    { 1, 1, 0, 120, 40, (u16*)sOamFrame_74a826 },
    { 1, 5, 0, 120, 40, (u16*)sOamFrame_74a82e },
    { 1, 9, 0, 120, 40, (u16*)sOamFrame_74a836 },
    { 1, 13, 0, 120, 40, (u16*)sOamFrame_74a83e },
    { 1, 17, 0, 120, 40, (u16*)sOamFrame_74a846 },
    { 1, 21, 0, 120, 40, (u16*)sOamFrame_74a84e },
    { 1, 25, 0, 120, 40, (u16*)sOamFrame_74a856 },
    { 1, 29, 0, 120, 40, (u16*)sOamFrame_74a85e },
    { 1, 33, 0, 120, 40, (u16*)sOamFrame_74a866 }
};
const struct EndingImageTextOam sEndingImageTextOamEnglish_1[11] = {
    { 1, 1, 0, 120, 92, (u16*)sOamFrame_74a888 },
    { 1, 5, 0, 120, 92, (u16*)sOamFrame_74a890 },
    { 1, 9, 0, 120, 92, (u16*)sOamFrame_74a898 },
    { 1, 13, 0, 120, 92, (u16*)sOamFrame_74a8a0 },
    { 1, 17, 0, 120, 92, (u16*)sOamFrame_74a8a8 },
    { 1, 21, 0, 120, 92, (u16*)sOamFrame_74a8b0 },
    { 1, 25, 0, 120, 92, (u16*)sOamFrame_74a8b8 },
    { 1, 29, 0, 120, 92, (u16*)sOamFrame_74a8c0 },
    { 1, 33, 0, 120, 92, (u16*)sOamFrame_74a8c8 },
    { 1, 37, 0, 120, 92, (u16*)sOamFrame_74a8d0 },
    { 1, 41, 0, 120, 92, (u16*)sOamFrame_74a8d8 }
};
const struct EndingImageTextOam sEndingImageTextOamEnglish_2[17] = {
    { 1, 1, 0, 120, 108, (u16*)sOamFrame_74a900 },
    { 1, 5, 0, 120, 108, (u16*)sOamFrame_74a908 },
    { 1, 9, 0, 120, 108, (u16*)sOamFrame_74a910 },
    { 1, 13, 0, 120, 108, (u16*)sOamFrame_74a918 },
    { 1, 17, 0, 120, 108, (u16*)sOamFrame_74a920 },
    { 1, 21, 0, 120, 108, (u16*)sOamFrame_74a928 },
    { 1, 25, 0, 120, 108, (u16*)sOamFrame_74a930 },
    { 1, 29, 0, 120, 108, (u16*)sOamFrame_74a938 },
    { 1, 33, 0, 120, 108, (u16*)sOamFrame_74a940 },
    { 1, 37, 0, 120, 108, (u16*)sOamFrame_74a948 },
    { 1, 41, 0, 120, 108, (u16*)sOamFrame_74a950 },
    { 1, 45, 0, 120, 108, (u16*)sOamFrame_74a958 },
    { 1, 49, 0, 120, 108, (u16*)sOamFrame_74a960 },
    { 1, 53, 0, 120, 108, (u16*)sOamFrame_74a968 },
    { 1, 57, 0, 120, 108, (u16*)sOamFrame_74a970 },
    { 1, 61, 0, 120, 108, (u16*)sOamFrame_74a978 },
    { 1, 65, 0, 120, 108, (u16*)sOamFrame_74a980 }
};
const struct EndingImageTextOam sEndingImageTextOamGermanLines[6] = {
    { 2, 0, 0, 120, 40, (u16*)sOamFrame_74af7c },
    { 2, 0, 0, 120, 60, (u16*)sOamFrame_74af42 },
    { 2, 0, 0, 120, 108, (u16*)sOamFrame_74b08e },
    { 2, 0, 0, 120, 108, (u16*)sOamFrame_74affe },
    { 2, 0, 0, 124, 128, (u16*)sOamFrame_74af62 },
    { 2, 0, 0, 120, 158, (u16*)sOamFrame_74b08e }
};
const struct EndingImageTextOam sEndingImageTextOamGerman_0[13] = {
    { 1, 1, 0, 120, 40, (u16*)sOamFrame_74af96 },
    { 1, 5, 0, 120, 40, (u16*)sOamFrame_74af9e },
    { 1, 9, 0, 120, 40, (u16*)sOamFrame_74afa6 },
    { 1, 13, 0, 120, 40, (u16*)sOamFrame_74afae },
    { 1, 17, 0, 120, 40, (u16*)sOamFrame_74afb6 },
    { 1, 21, 0, 120, 40, (u16*)sOamFrame_74afbe },
    { 1, 25, 0, 120, 40, (u16*)sOamFrame_74afc6 },
    { 1, 29, 0, 120, 40, (u16*)sOamFrame_74afce },
    { 1, 33, 0, 120, 40, (u16*)sOamFrame_74afd6 },
    { 1, 37, 0, 120, 40, (u16*)sOamFrame_74afde },
    { 1, 41, 0, 120, 40, (u16*)sOamFrame_74afe6 },
    { 1, 45, 0, 120, 40, (u16*)sOamFrame_74afee },
    { 1, 49, 0, 120, 40, (u16*)sOamFrame_74aff6 }
};
const struct EndingImageTextOam sEndingImageTextOamGerman_1[14] = {
    { 1, 1, 0, 120, 108, (u16*)sOamFrame_74b01e },
    { 1, 5, 0, 120, 108, (u16*)sOamFrame_74b026 },
    { 1, 9, 0, 120, 108, (u16*)sOamFrame_74b02e },
    { 1, 13, 0, 120, 108, (u16*)sOamFrame_74b036 },
    { 1, 17, 0, 120, 108, (u16*)sOamFrame_74b03e },
    { 1, 21, 0, 120, 108, (u16*)sOamFrame_74b046 },
    { 1, 25, 0, 120, 108, (u16*)sOamFrame_74b04e },
    { 1, 29, 0, 120, 108, (u16*)sOamFrame_74b056 },
    { 1, 33, 0, 120, 108, (u16*)sOamFrame_74b05e },
    { 1, 37, 0, 120, 108, (u16*)sOamFrame_74b066 },
    { 1, 41, 0, 120, 108, (u16*)sOamFrame_74b06e },
    { 1, 45, 0, 120, 108, (u16*)sOamFrame_74b076 },
    { 1, 49, 0, 120, 108, (u16*)sOamFrame_74b07e },
    { 1, 53, 0, 120, 108, (u16*)sOamFrame_74b086 }
};
const struct EndingImageTextOam sEndingImageTextOamFrenchLines[6] = {
    { 2, 0, 0, 120, 40, (u16*)sOamFrame_74a9e2 },
    { 2, 0, 0, 120, 60, (u16*)sOamFrame_74a9a8 },
    { 2, 0, 0, 120, 108, (u16*)sOamFrame_74ab4e },
    { 2, 0, 0, 120, 108, (u16*)sOamFrame_74aa82 },
    { 2, 0, 0, 124, 128, (u16*)sOamFrame_74a9c8 },
    { 2, 0, 0, 120, 158, (u16*)sOamFrame_74ab4e }
};
const struct EndingImageTextOam sEndingImageTextOamFrench_0[16] = {
    { 1, 1, 0, 120, 40, (u16*)sOamFrame_74aa02 },
    { 1, 5, 0, 120, 40, (u16*)sOamFrame_74aa0a },
    { 1, 9, 0, 120, 40, (u16*)sOamFrame_74aa12 },
    { 1, 13, 0, 120, 40, (u16*)sOamFrame_74aa1a },
    { 1, 17, 0, 120, 40, (u16*)sOamFrame_74aa22 },
    { 1, 21, 0, 120, 40, (u16*)sOamFrame_74aa2a },
    { 1, 25, 0, 120, 40, (u16*)sOamFrame_74aa32 },
    { 1, 29, 0, 120, 40, (u16*)sOamFrame_74aa3a },
    { 1, 33, 0, 120, 40, (u16*)sOamFrame_74aa42 },
    { 1, 37, 0, 120, 40, (u16*)sOamFrame_74aa4a },
    { 1, 41, 0, 120, 40, (u16*)sOamFrame_74aa52 },
    { 1, 45, 0, 120, 40, (u16*)sOamFrame_74aa5a },
    { 1, 49, 0, 120, 40, (u16*)sOamFrame_74aa62 },
    { 1, 53, 0, 120, 40, (u16*)sOamFrame_74aa6a },
    { 1, 57, 0, 120, 40, (u16*)sOamFrame_74aa72 },
    { 1, 61, 0, 120, 40, (u16*)sOamFrame_74aa7a }
};
const struct EndingImageTextOam sEndingImageTextOamFrench_1[20] = {
    { 1, 1, 0, 120, 108, (u16*)sOamFrame_74aaae },
    { 1, 5, 0, 120, 108, (u16*)sOamFrame_74aab6 },
    { 1, 9, 0, 120, 108, (u16*)sOamFrame_74aabe },
    { 1, 13, 0, 120, 108, (u16*)sOamFrame_74aac6 },
    { 1, 17, 0, 120, 108, (u16*)sOamFrame_74aace },
    { 1, 21, 0, 120, 108, (u16*)sOamFrame_74aad6 },
    { 1, 25, 0, 120, 108, (u16*)sOamFrame_74aade },
    { 1, 29, 0, 120, 108, (u16*)sOamFrame_74aae6 },
    { 1, 33, 0, 120, 108, (u16*)sOamFrame_74aaee },
    { 1, 37, 0, 120, 108, (u16*)sOamFrame_74aaf6 },
    { 1, 41, 0, 120, 108, (u16*)sOamFrame_74aafe },
    { 1, 45, 0, 120, 108, (u16*)sOamFrame_74ab06 },
    { 1, 49, 0, 120, 108, (u16*)sOamFrame_74ab0e },
    { 1, 53, 0, 120, 108, (u16*)sOamFrame_74ab16 },
    { 1, 57, 0, 120, 108, (u16*)sOamFrame_74ab1e },
    { 1, 61, 0, 120, 108, (u16*)sOamFrame_74ab26 },
    { 1, 65, 0, 120, 108, (u16*)sOamFrame_74ab2e },
    { 1, 69, 0, 120, 108, (u16*)sOamFrame_74ab36 },
    { 1, 73, 0, 120, 108, (u16*)sOamFrame_74ab3e },
    { 1, 77, 0, 120, 108, (u16*)sOamFrame_74ab46 }
};
const struct EndingImageTextOam sEndingImageTextOamItalianLines[6] = {
    { 2, 0, 0, 120, 40, (u16*)sOamFrame_74ab9c },
    { 2, 0, 0, 120, 60, (u16*)sOamFrame_74ab62 },
    { 2, 0, 0, 120, 92, (u16*)sOamFrame_74ac52 },
    { 2, 0, 0, 120, 108, (u16*)sOamFrame_74acc4 },
    { 2, 0, 0, 124, 128, (u16*)sOamFrame_74ab82 },
    { 2, 0, 0, 120, 158, (u16*)sOamFrame_74ad6c }
};
const struct EndingImageTextOam sEndingImageTextOamItalian_0[18] = {
    { 1, 1, 0, 120, 40, (u16*)sOamFrame_74abc2 },
    { 1, 5, 0, 120, 40, (u16*)sOamFrame_74abca },
    { 1, 9, 0, 120, 40, (u16*)sOamFrame_74abd2 },
    { 1, 13, 0, 120, 40, (u16*)sOamFrame_74abda },
    { 1, 17, 0, 120, 40, (u16*)sOamFrame_74abe2 },
    { 1, 21, 0, 120, 40, (u16*)sOamFrame_74abea },
    { 1, 25, 0, 120, 40, (u16*)sOamFrame_74abf2 },
    { 1, 29, 0, 120, 40, (u16*)sOamFrame_74abfa },
    { 1, 33, 0, 120, 40, (u16*)sOamFrame_74ac02 },
    { 1, 37, 0, 120, 40, (u16*)sOamFrame_74ac0a },
    { 1, 41, 0, 120, 40, (u16*)sOamFrame_74ac12 },
    { 1, 45, 0, 120, 40, (u16*)sOamFrame_74ac1a },
    { 1, 49, 0, 120, 40, (u16*)sOamFrame_74ac22 },
    { 1, 53, 0, 120, 40, (u16*)sOamFrame_74ac2a },
    { 1, 57, 0, 120, 40, (u16*)sOamFrame_74ac32 },
    { 1, 61, 0, 120, 40, (u16*)sOamFrame_74ac3a },
    { 1, 65, 0, 120, 40, (u16*)sOamFrame_74ac42 },
    { 1, 69, 0, 120, 40, (u16*)sOamFrame_74ac4a }
};
const struct EndingImageTextOam sEndingImageTextOamItalian_1[11] = {
    { 1, 1, 0, 120, 92, (u16*)sOamFrame_74ac6c },
    { 1, 5, 0, 120, 92, (u16*)sOamFrame_74ac74 },
    { 1, 9, 0, 120, 92, (u16*)sOamFrame_74ac7c },
    { 1, 13, 0, 120, 92, (u16*)sOamFrame_74ac84 },
    { 1, 17, 0, 120, 92, (u16*)sOamFrame_74ac8c },
    { 1, 21, 0, 120, 92, (u16*)sOamFrame_74ac94 },
    { 1, 25, 0, 120, 92, (u16*)sOamFrame_74ac9c },
    { 1, 29, 0, 120, 92, (u16*)sOamFrame_74aca4 },
    { 1, 33, 0, 120, 92, (u16*)sOamFrame_74acac },
    { 1, 37, 0, 120, 92, (u16*)sOamFrame_74acb4 },
    { 1, 41, 0, 120, 92, (u16*)sOamFrame_74acbc }
};
const struct EndingImageTextOam sEndingImageTextOamItalian_2[17] = {
    { 1, 1, 0, 120, 108, (u16*)sOamFrame_74ace4 },
    { 1, 5, 0, 120, 108, (u16*)sOamFrame_74acec },
    { 1, 9, 0, 120, 108, (u16*)sOamFrame_74acf4 },
    { 1, 13, 0, 120, 108, (u16*)sOamFrame_74acfc },
    { 1, 17, 0, 120, 108, (u16*)sOamFrame_74ad04 },
    { 1, 21, 0, 120, 108, (u16*)sOamFrame_74ad0c },
    { 1, 25, 0, 120, 108, (u16*)sOamFrame_74ad14 },
    { 1, 29, 0, 120, 108, (u16*)sOamFrame_74ad1c },
    { 1, 33, 0, 120, 108, (u16*)sOamFrame_74ad24 },
    { 1, 37, 0, 120, 108, (u16*)sOamFrame_74ad2c },
    { 1, 41, 0, 120, 108, (u16*)sOamFrame_74ad34 },
    { 1, 45, 0, 120, 108, (u16*)sOamFrame_74ad3c },
    { 1, 49, 0, 120, 108, (u16*)sOamFrame_74ad44 },
    { 1, 53, 0, 120, 108, (u16*)sOamFrame_74ad4c },
    { 1, 57, 0, 120, 108, (u16*)sOamFrame_74ad54 },
    { 1, 61, 0, 120, 108, (u16*)sOamFrame_74ad5c },
    { 1, 65, 0, 120, 108, (u16*)sOamFrame_74ad64 }
};
const struct EndingImageTextOam sEndingImageTextOamSpanishLines[6] = {
    { 2, 0, 0, 120, 40, (u16*)sOamFrame_74adc6 },
    { 2, 0, 0, 120, 60, (u16*)sOamFrame_74ad8c },
    { 2, 0, 0, 120, 108, (u16*)sOamFrame_74af1c },
    { 2, 0, 0, 120, 108, (u16*)sOamFrame_74ae5e },
    { 2, 0, 0, 124, 128, (u16*)sOamFrame_74adac },
    { 2, 0, 0, 120, 158, (u16*)sOamFrame_74af1c }
};
const struct EndingImageTextOam sEndingImageTextOamSpanish_0[15] = {
    { 1, 1, 0, 120, 40, (u16*)sOamFrame_74ade6 },
    { 1, 5, 0, 120, 40, (u16*)sOamFrame_74adee },
    { 1, 9, 0, 120, 40, (u16*)sOamFrame_74adf6 },
    { 1, 13, 0, 120, 40, (u16*)sOamFrame_74adfe },
    { 1, 17, 0, 120, 40, (u16*)sOamFrame_74ae06 },
    { 1, 21, 0, 120, 40, (u16*)sOamFrame_74ae0e },
    { 1, 25, 0, 120, 40, (u16*)sOamFrame_74ae16 },
    { 1, 29, 0, 120, 40, (u16*)sOamFrame_74ae1e },
    { 1, 33, 0, 120, 40, (u16*)sOamFrame_74ae26 },
    { 1, 37, 0, 120, 40, (u16*)sOamFrame_74ae2e },
    { 1, 41, 0, 120, 40, (u16*)sOamFrame_74ae36 },
    { 1, 45, 0, 120, 40, (u16*)sOamFrame_74ae3e },
    { 1, 49, 0, 120, 40, (u16*)sOamFrame_74ae46 },
    { 1, 53, 0, 120, 40, (u16*)sOamFrame_74ae4e },
    { 1, 57, 0, 120, 40, (u16*)sOamFrame_74ae56 }
};
const struct EndingImageTextOam sEndingImageTextOamSpanish_1[19] = {
    { 1, 1, 0, 120, 108, (u16*)sOamFrame_74ae84 },
    { 1, 5, 0, 120, 108, (u16*)sOamFrame_74ae8c },
    { 1, 9, 0, 120, 108, (u16*)sOamFrame_74ae94 },
    { 1, 13, 0, 120, 108, (u16*)sOamFrame_74ae9c },
    { 1, 17, 0, 120, 108, (u16*)sOamFrame_74aea4 },
    { 1, 21, 0, 120, 108, (u16*)sOamFrame_74aeac },
    { 1, 25, 0, 120, 108, (u16*)sOamFrame_74aeb4 },
    { 1, 29, 0, 120, 108, (u16*)sOamFrame_74aebc },
    { 1, 33, 0, 120, 108, (u16*)sOamFrame_74aec4 },
    { 1, 37, 0, 120, 108, (u16*)sOamFrame_74aecc },
    { 1, 41, 0, 120, 108, (u16*)sOamFrame_74aed4 },
    { 1, 45, 0, 120, 108, (u16*)sOamFrame_74aedc },
    { 1, 49, 0, 120, 108, (u16*)sOamFrame_74aee4 },
    { 1, 53, 0, 120, 108, (u16*)sOamFrame_74aeec },
    { 1, 57, 0, 120, 108, (u16*)sOamFrame_74aef4 },
    { 1, 61, 0, 120, 108, (u16*)sOamFrame_74aefc },
    { 1, 65, 0, 120, 108, (u16*)sOamFrame_74af04 },
    { 1, 69, 0, 120, 108, (u16*)sOamFrame_74af0c },
    { 1, 73, 0, 120, 108, (u16*)sOamFrame_74af14 }
};

const u32* const sPreResultsSamusBgGfxPointers1[4] = {
    sPreResultsSamusSuitedGfx3,
    sPreResultsSamusSuitedGfx5,
    sPreResultsSamusSuitedGfx7,
    sPreResultsSamusSuitedGfx9
};

const u32* const sPreResultsSamusBgGfxPointers2[4] = {
    sPreResultsSamusSuitedGfx4,
    sPreResultsSamusSuitedGfx6,
    sPreResultsSamusSuitedGfx8,
    sPreResultsSamusSuitedGfx10
};

const u8* const sPreResultsSamusBgTilemapPointers[4] = {
    sTilemap_75de04,
    sTilemap_75e100,
    sTilemap_75e414,
    sTilemap_75e6fc
};

const u8 sEndingDigitsTopGfx[10 * 2 * TILE_SIZE] = INCBIN_U8("data/ending/digits_top.gfx"); // top halves of the digits 0-9 (2 tiles each) of the in game time and completion percentage
const u8 sEndingDigitsBottomGfx[10 * 2 * TILE_SIZE] = INCBIN_U8("data/ending/digits_bottom.gfx"); // bottom halves of the digits

const u32 sPreResultsSpaceBgGfx[4772] = INCBIN_U32("data/ending/space_bg.gfx.lz");

const u8 sTilemap_7535e0[2208] = INCBIN_U8("data/ending/7535e0.tm.lz");
const u8 sTilemap_753E80[376] = INCBIN_U8("data/ending/753e80.tm.lz");

const u32 sPreResultsSamusSuitedGfx1[853] = INCBIN_U32("data/ending/samus_suited_1.gfx.lz");
const u32 sPreResultsSamusSuitedGfx2[629] = INCBIN_U32("data/ending/samus_suited_2.gfx.lz");
const u32 sPreResultsSamusSuitedGfx3[852] = INCBIN_U32("data/ending/samus_suited_3.gfx.lz");
const u32 sPreResultsSamusSuitedGfx4[852] = INCBIN_U32("data/ending/samus_suited_4.gfx.lz");
const u32 sPreResultsSamusSuitedGfx5[848] = INCBIN_U32("data/ending/samus_suited_5.gfx.lz");
const u32 sPreResultsSamusSuitedGfx6[941] = INCBIN_U32("data/ending/samus_suited_6.gfx.lz");
const u32 sPreResultsSamusSuitedGfx7[915] = INCBIN_U32("data/ending/samus_suited_7.gfx.lz");
const u32 sPreResultsSamusSuitedGfx8[778] = INCBIN_U32("data/ending/samus_suited_8.gfx.lz");
const u32 sPreResultsSamusSuitedGfx9[923] = INCBIN_U32("data/ending/samus_suited_9.gfx.lz");
const u32 sPreResultsSamusSuitedGfx10[496] = INCBIN_U32("data/ending/samus_suited_10.gfx.lz");

const u32 sPreResultsSamusWithoutHelmetBgGfx1[897] = INCBIN_U32("data/ending/samus_without_helmet_bg_1.gfx.lz");
const u32 sPreResultsSamusWithoutHelmetBgGfx2[124] = INCBIN_U32("data/ending/samus_without_helmet_bg_2.gfx.lz");
const u32 sPreResultsSamusSuitlessBgGfx1[710] = INCBIN_U32("data/ending/samus_suitless_bg_1.gfx.lz");
const u32 sPreResultsSamusSuitlessBgGfx2[124] = INCBIN_U32("data/ending/samus_suitless_bg_2.gfx.lz");

const u8 sTilemap_75db50[692] = INCBIN_U8("data/ending/75db50.tm.lz");
const u8 sTilemap_75de04[764] = INCBIN_U8("data/ending/75de04.tm.lz");
const u8 sTilemap_75e100[788] = INCBIN_U8("data/ending/75e100.tm.lz");
const u8 sTilemap_75e414[744] = INCBIN_U8("data/ending/75e414.tm.lz");
const u8 sTilemap_75e6fc[660] = INCBIN_U8("data/ending/75e6fc.tm.lz");
const u8 sTilemap_75E990[516] = INCBIN_U8("data/ending/75e990.tm.lz");
const u8 sTilemap_75EB94[472] = INCBIN_U8("data/ending/75eb94.tm.lz");

const u32 sPreResultsSamusObjGfx[2887] = INCBIN_U32("data/ending/samus_obj.gfx.lz");

const u32 sEnding_0_GfxTop[5628] = INCBIN_U32("data/ending/ending_0_top.gfx.lz");
const u32 sEnding_0_GfxBottom[3191] = INCBIN_U32("data/ending/ending_0_bottom.gfx.lz");
const u32 sEnding_1_GfxTop[5900] = INCBIN_U32("data/ending/ending_1_top.gfx.lz");
const u32 sEnding_1_GfxBottom[2986] = INCBIN_U32("data/ending/ending_1_bottom.gfx.lz");
const u32 sEnding_2_GfxTop[5731] = INCBIN_U32("data/ending/ending_2_top.gfx.lz");
const u32 sEnding_2_GfxBottom[3293] = INCBIN_U32("data/ending/ending_2_bottom.gfx.lz");
const u32 sEnding_3_GfxTop[6364] = INCBIN_U32("data/ending/ending_3_top.gfx.lz");
const u32 sEnding_3_GfxBottom[3818] = INCBIN_U32("data/ending/ending_3_bottom.gfx.lz");
const u32 sEnding_4_GfxTop[6851] = INCBIN_U32("data/ending/ending_4_top.gfx.lz");
const u32 sEnding_4_GfxBottom[3504] = INCBIN_U32("data/ending/ending_4_bottom.gfx.lz");

const u8 sEnding_0_TilemapTop[2204] = INCBIN_U8("data/ending/ending_0_top.tm.lz");
const u8 sEnding_0_TilemapBottom[1472] = INCBIN_U8("data/ending/ending_0_bottom.tm.lz");
const u8 sEnding_1_TilemapTop[2204] = INCBIN_U8("data/ending/ending_1_top.tm.lz");
const u8 sEnding_1_TilemapBottom[1472] = INCBIN_U8("data/ending/ending_1_bottom.tm.lz");
const u8 sEnding_2_TilemapTop[2204] = INCBIN_U8("data/ending/ending_2_top.tm.lz");
const u8 sEnding_2_TilemapBottom[1472] = INCBIN_U8("data/ending/ending_2_bottom.tm.lz");
const u8 sEnding_3_TilemapTop[2204] = INCBIN_U8("data/ending/ending_3_top.tm.lz");
const u8 sEnding_3_TilemapBottom[1476] = INCBIN_U8("data/ending/ending_3_bottom.tm.lz");
const u8 sEnding_4_TilemapTop[2204] = INCBIN_U8("data/ending/ending_4_top.tm.lz");
const u8 sEnding_4_TilemapBottom[1476] = INCBIN_U8("data/ending/ending_4_bottom.tm.lz");

const u32 sResultsScreenEnglishTextGfx[1201] = INCBIN_U32("data/ending/results_english_text.gfx.lz");
const u32 sResultsScreenFrenchTextGfx[1171] = INCBIN_U32("data/ending/results_french_text.gfx.lz");
const u32 sResultsScreenItalianTextGfx[1221] = INCBIN_U32("data/ending/results_italian_text.gfx.lz");
const u32 sResultsScreenSpanishTextGfx[1197] = INCBIN_U32("data/ending/results_spanish_text.gfx.lz");
const u32 sResultsScreenGermanTextGfx[1144] = INCBIN_U32("data/ending/results_german_text.gfx.lz");

// 256 bytes of 0xFF after the last results screen graphics, not referenced by code
// (free space or an unused table filled with -1)
static const u8 sUnusedFill_79a19c[256] = { [0 ... 255] = 0xFF };
