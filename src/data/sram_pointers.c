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

const u8 sSramUnk_582288[] = INCBIN_U8("data/Blob_582288_5822a8.bin");
const u8 sSramUnk_5822a8[] = INCBIN_U8("data/Blob_5822a8_5822c8.bin");
const u8 sSramUnk_5822c8[] = INCBIN_U8("data/Blob_5822c8_5822d4.bin");
const u8 sSramUnk_5822d4[] = INCBIN_U8("data/Blob_5822d4_5822e4.bin");
const u8 sSramUnk_5822e4[] = INCBIN_U8("data/Blob_5822e4_5822f0.bin");
const u8 sEraseSramUnk_5822f0[] = INCBIN_U8("data/Blob_5822f0_5823d0.bin");
const u8 sEraseSramUnk_5823d0[] = INCBIN_U8("data/Blob_5823d0_582bbc.bin");
const u8 sEraseSramUnk_582bbc[] = INCBIN_U8("data/Blob_582bbc_58340c.bin");
const u8 sEraseSramUnk_58340c[] = INCBIN_U8("data/Blob_58340c_58abe4.bin");
const u8 sEraseSramUnk_58abe4[] = INCBIN_U8("data/Blob_58abe4_58adf0.bin");
const u8 sEraseSramUnk_58adf0[] = INCBIN_U8("data/Blob_58adf0_58b3b0.bin");
const u8 sEraseSramUnk_58b3b0[] = INCBIN_U8("data/Blob_58b3b0_58b3b4.bin");
const u8 sEraseSramUnk_58b3b4[] = INCBIN_U8("data/Blob_58b3b4_58b3be.bin");
const u8 sEraseSramUnk_58b3be[] = INCBIN_U8("data/Blob_58b3be_58b3c2.bin");
const u8 sEraseSramUnk_58b3c2[] = INCBIN_U8("data/Blob_58b3c2_58b3cc.bin");
