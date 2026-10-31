#include "globals.h"
#include "special_cutscene.h"
#include "callbacks.h"
#include "init_helpers.h"
#include "oam.h"

#include "audio/track_internal.h"

#include "data/sprite_data.h"

/**
 * @brief 997a4 | 108 | Initializes the new file intro
 *
 */
void NewFileIntroInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gNextOamSlot = 0;
    ResetFreeOam();

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
    DMA3_FILL_32(COLOR_WHITE, PALRAM_BASE, PALRAM_SIZE / 2);
    WRITE_16(PALRAM_BASE, 0);
    DMA3_FILL_32(0, VRAM_BASE, 0x10000);

    WRITE_16(REG_BG3CNT, 0);
    WRITE_16(REG_BG2CNT, 0);
    WRITE_16(REG_BG1CNT, 0);
    WRITE_16(REG_BG0CNT, 0);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_DISPCNT, 0);

    CallbackSetVBlank(NewFileIntroVblank);
}

/**
 * @brief 998ac | 48 | Generates a random number for a special cutscene
 *
 * @return u8 Random number
 */
u8 SpecialCutsceneGetRandomNumber(void)
{
    gSpecialCutsceneRandomSeed = gSpecialCutsceneRandomSeed + gSpecialCutsceneRandomSeed * 4 + (u16)(0x3573 + gFrameCounter8Bit);
    SPECIAL_CUTSCENE_RANDOM_SEED_HIGH += sRandomNumberTable[MOD_AND(gFrameCounter16Bit, ARRAY_SIZE(sRandomNumberTable))];

    return SPECIAL_CUTSCENE_RANDOM_SEED_HIGH;
}

/**
 * @brief 998f4 | 4c | V-blank for the new file intro
 *
 */
void NewFileIntroVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 99940 | c | V-blank for the special cutscenes while they're loading
 *
 */
void SpecialCutsceneLoadingVblank(void)
{
    UpdateAudio();
}
