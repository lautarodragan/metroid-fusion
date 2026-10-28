#include "data/sa_x_close_up.h"
#include "macros.h"

const u16 sSaXCloseUpPal[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette.pal");
const u16 sSaXCloseUpPalGrayscale[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette_grayscale.pal");
const u32 sSaXCloseUpGfx[4472] = INCBIN_U32("data/sa_x_close_up/graphics.gfx.lz");
const u32 sSaXCloseUpTileTable1[294] = INCBIN_U32("data/sa_x_close_up/first.tt.lz");
const u32 sSaXCloseUpTileTable2[305] = INCBIN_U32("data/sa_x_close_up/second.tt.lz");

const u8 sSaXCloseUpDurations[2] = { 25, 60 };

static const u8 sBlob_73421e_734220[] = INCBIN_U8("data/Blob_73421e_734220.bin");
const u8 sGameOverUnk_734220[] = INCBIN_U8("data/Blob_734220_73422c.bin");
const u8 sGameOverUnk_73422c[] = INCBIN_U8("data/Blob_73422c_739a78.bin");
const u8 sGameOverUnk_739a78[] = INCBIN_U8("data/Blob_739a78_73c274.bin");
const u8 sGameOverUnk_73c274[] = INCBIN_U8("data/Blob_73c274_73c2e4.bin");
const u8 sGameOverUnk_73c2e4[] = INCBIN_U8("data/Blob_73c2e4_73c4e4.bin");
const u8 sGameOverUnk_73c4e4[] = INCBIN_U8("data/Blob_73c4e4_73c6e4.bin");
const u8 sGameOverUnk_73c6e4[] = INCBIN_U8("data/Blob_73c6e4_73cca8.bin");
const u8 sGameOverUnk_73cca8[] = INCBIN_U8("data/Blob_73cca8_73cfac.bin");
const u8 sFileSelectUnk_73cfac[] = INCBIN_U8("data/Blob_73cfac_73d380.bin");
const u8 sFileSelectUnk_73d380[] = INCBIN_U8("data/Blob_73d380_73d5ec.bin");
const u8 sFileSelectUnk_73d5ec[] = INCBIN_U8("data/Blob_73d5ec_73dac4.bin");
const u8 sFileSelectUnk_73dac4[] = INCBIN_U8("data/Blob_73dac4_73dae4.bin");
const u8 sFileSelectUnk_73dae4[] = INCBIN_U8("data/Blob_73dae4_73db04.bin");
const u8 sFileSelectUnk_73db04[] = INCBIN_U8("data/Blob_73db04_73db24.bin");
const u8 sFileSelectUnk_73db24[] = INCBIN_U8("data/Blob_73db24_73db44.bin");
const u8 sFileSelectUnk_73db44[] = INCBIN_U8("data/Blob_73db44_73db64.bin");
const u8 sFileSelectUnk_73db64[] = INCBIN_U8("data/Blob_73db64_73db84.bin");
const u8 sFileSelectUnk_73db84[] = INCBIN_U8("data/Blob_73db84_73dba4.bin");
const u8 sFileSelectUnk_73dba4[] = INCBIN_U8("data/Blob_73dba4_73dbb0.bin");
const u8 sFileSelectUnk_73dbb0[] = INCBIN_U8("data/Blob_73dbb0_73dbbe.bin");
const u8 sFileSelectUnk_73dbbe[] = INCBIN_U8("data/Blob_73dbbe_73dc20.bin");
const u8 sFileSelectUnk_73dc20[] = INCBIN_U8("data/Blob_73dc20_7407c0.bin");
const u8 sFileSelectUnk_7407c0[] = INCBIN_U8("data/Blob_7407c0_7407d0.bin");
const u8 sFileSelectUnk_7407d0[] = INCBIN_U8("data/Blob_7407d0_7407e0.bin");
const u8 sFileSelectUnk_7407e0[] = INCBIN_U8("data/Blob_7407e0_7407f0.bin");
const u8 sFileSelectUnk_7407f0[] = INCBIN_U8("data/Blob_7407f0_740880.bin");
const u8 sFileSelectUnk_740880[] = INCBIN_U8("data/Blob_740880_7408d0.bin");
const u8 sUnk_7408d0[] = INCBIN_U8("data/Blob_7408d0_7408e0.bin");
const u8 sFileSelectUnk_7408e0[] = INCBIN_U8("data/Blob_7408e0_7408f0.bin");
const u8 sFileSelectUnk_7408f0[] = INCBIN_U8("data/Blob_7408f0_740918.bin");
const u8 sFileSelectUnk_740918[] = INCBIN_U8("data/Blob_740918_740940.bin");
const u8 sFileSelectUnk_740940[] = INCBIN_U8("data/Blob_740940_740950.bin");
const u8 sFileSelectUnk_740950[] = INCBIN_U8("data/Blob_740950_740978.bin");
const u8 sFileSelectUnk_740978[] = INCBIN_U8("data/Blob_740978_7409a0.bin");
const u8 sFileSelectUnk_7409a0[] = INCBIN_U8("data/Blob_7409a0_7409b0.bin");
const u8 sFileSelectUnk_7409b0[] = INCBIN_U8("data/Blob_7409b0_740a48.bin");
const u8 sFileSelectUnk_740a48[] = INCBIN_U8("data/Blob_740a48_740a70.bin");
const u8 sFileSelectUnk_740a70[] = INCBIN_U8("data/Blob_740a70_740ab8.bin");
const u8 sFileSelectUnk_740ab8[] = INCBIN_U8("data/Blob_740ab8_740b48.bin");
const u8 sFileSelectUnk_740b48[] = INCBIN_U8("data/Blob_740b48_740b70.bin");
const u8 sFileSelectUnk_740b70[] = INCBIN_U8("data/Blob_740b70_740b98.bin");
const u8 sFileSelectUnk_740b98[] = INCBIN_U8("data/Blob_740b98_740d08.bin");
const u8 sFileSelectUnk_740d08[] = INCBIN_U8("data/Blob_740d08_742fb4.bin");
const u8 sFileSelectUnk_742fb4[] = INCBIN_U8("data/Blob_742fb4_7470e0.bin");
const u8 sFileSelectUnk_7470e0[] = INCBIN_U8("data/Blob_7470e0_7476a0.bin");
const u8 sFileSelectUnk_7476a0[] = INCBIN_U8("data/Blob_7476a0_7478a0.bin");
