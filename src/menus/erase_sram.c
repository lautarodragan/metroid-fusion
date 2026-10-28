#include "menus/erase_sram.h"
#include "audio_wrappers.h"
#include "callbacks.h"
#include "globals.h"
#include "gba.h"
#include "init_helpers.h"
#include "io.h"
#include "oam.h"
#include "sram_misc.h"
#include "syscalls.h"

#include "audio/track_internal.h"

#include "data/menus/erase_sram_data.h"

#include "constants/game_state.h"

#include "structs/menus/pause_screen.h"

enum EraseSramOption {
    ERASE_SRAM_OPTION_NO,
    ERASE_SRAM_OPTION_YES,
    ERASE_SRAM_OPTION_CONFIRM_NO,
    ERASE_SRAM_OPTION_CONFIRM_YES
};

#define ERASE_SRAM_OPTION_CHANGING 0x80

struct EraseSramData {
    u8 currentOption;
    u8 nextOption;
    u8 language;
    u8 unk_3;
    u16 timer;
    u16 bldcnt;
    u8 targetBldy;
    u8 unk_9;
    u8 unk_A;
    u8 unk_B;
    struct MenuOam oam[3];
};

#define ERASE_SRAM_DATA (*(struct EraseSramData*)&gNonGameplayRam)

/**
 * @brief 809f0 | 11c | Handles the erase SRAM menu
 *
 * @return u32 bool, ended
 */
u32 EraseSramMenuHandler(void)
{
    u32 ended;

    ended = FALSE;
    ERASE_SRAM_DATA.timer++;

    switch (gSubGameMode1)
    {
        case 0:
            EraseSramMenuInit();
            gSubGameMode1++;
            break;

        case 1:
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy--;
                break;
            }

            ERASE_SRAM_DATA.bldcnt = 0xEF;
            ERASE_SRAM_DATA.targetBldy = gWrittenToBldy;
            gSubGameMode1++;
            ERASE_SRAM_DATA.timer = 0;
            break;

        case 2:
            gSubGameMode2 = EraseSramProcessInput();
            if (gSubGameMode2 != 0)
            {
                ERASE_SRAM_DATA.timer = 0;
                if (gSubGameMode2 == 1)
                    gSubGameMode1 = 5;
                else
                    gSubGameMode1 = 3;
            }
            break;

        case 3:
            if (ERASE_SRAM_DATA.timer > 40)
            {
                ERASE_SRAM_DATA.bldcnt = 0xFF;
                ERASE_SRAM_DATA.timer = 0;
                gSubGameMode1++;
            }
            break;

        case 4:
            if (gWrittenToBldy < 16)
                gWrittenToBldy++;
            else
                ended = TRUE;
            break;

        case 5:
            if (ERASE_SRAM_DATA.timer > 40)
            {
                ERASE_SRAM_DATA.bldcnt = 0xBF;
                ERASE_SRAM_DATA.timer = 0;
                gSubGameMode1++;
            }
            break;

        case 6:
            if (gWrittenToBldy < 16)
            {
                gWrittenToBldy++;
            }
            else
            {
                EraseSram();
                ended = TRUE;
            }
            break;
    }

    EraseSramProcessOam();
    ResetFreeOam();

    return ended;
}

/**
 * @brief 80b0c | 50 | Processes the input of the erase SRAM menu
 *
 * @return s32 Result (0 = none, 1 = erase, 2 = exit)
 */
s32 EraseSramProcessInput(void)
{
    s32 result;

    result = 0;

    if (ERASE_SRAM_DATA.nextOption & ERASE_SRAM_OPTION_CHANGING)
        EraseSramApplyInput();
    else
        result = EraseSramCheckForInput();

    if (ERASE_SRAM_DATA.targetBldy != gWrittenToBldy)
    {
        if (ERASE_SRAM_DATA.targetBldy > gWrittenToBldy)
            gWrittenToBldy++;
        else
            gWrittenToBldy--;
    }

    EraseSramUpdateCursorPosition();

    return result;
}

/**
 * @brief 80b5c | 90 | Applies the input of the erase SRAM menu
 *
 */
void EraseSramApplyInput(void)
{
    if (ERASE_SRAM_DATA.oam[0].oamId == 2)
        return;

    ERASE_SRAM_DATA.currentOption = ERASE_SRAM_DATA.nextOption &= ~ERASE_SRAM_OPTION_CHANGING;

    switch (ERASE_SRAM_DATA.nextOption)
    {
        case ERASE_SRAM_OPTION_NO:
            ERASE_SRAM_DATA.oam[2].oamId = *(sEraseSramUnk_58b3b0 + ERASE_SRAM_OPTION_NO);
            ERASE_SRAM_DATA.oam[1].oamId = 0;
            break;

        case ERASE_SRAM_OPTION_YES:
            ERASE_SRAM_DATA.oam[2].oamId = *(sEraseSramUnk_58b3b0 + ERASE_SRAM_OPTION_YES);
            ERASE_SRAM_DATA.oam[1].oamId = 0;
            break;

        case ERASE_SRAM_OPTION_CONFIRM_NO:
            ERASE_SRAM_DATA.oam[1].oamId = *(sEraseSramUnk_58b3b0 + ERASE_SRAM_OPTION_CONFIRM_NO);
            break;

        case ERASE_SRAM_OPTION_CONFIRM_YES:
            ERASE_SRAM_DATA.oam[1].oamId = *(sEraseSramUnk_58b3b0 + ERASE_SRAM_OPTION_CONFIRM_YES);
            break;
    }

    ERASE_SRAM_DATA.oam[1].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[1].currentAnimationFrame = 0;
    ERASE_SRAM_DATA.oam[2].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[2].currentAnimationFrame = 0;

    ERASE_SRAM_DATA.oam[0].oamId = 1;
    ERASE_SRAM_DATA.oam[0].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[0].currentAnimationFrame = 0;
}

/**
 * @brief 80bec | 10c | Checks for input on the erase SRAM menu
 *
 * @return s32 Result (0 = none, 1 = erase, 2 = exit)
 */
s32 EraseSramCheckForInput(void)
{
    s32 result;
    s32 sound;
    s32 updateCursor;

    result = 0;
    sound = 0;
    updateCursor = FALSE;

    switch (ERASE_SRAM_DATA.currentOption)
    {
        case ERASE_SRAM_OPTION_NO:
            if (gChangedInput & KEY_RIGHT)
            {
                ERASE_SRAM_DATA.nextOption = ERASE_SRAM_OPTION_CHANGING | ERASE_SRAM_OPTION_YES;
                sound = 4;
            }
            else if (gChangedInput & KEY_A)
            {
                result = 2;
                sound = 1;
                updateCursor = TRUE;
            }
            break;

        case ERASE_SRAM_OPTION_YES:
            if (gChangedInput & KEY_LEFT)
            {
                ERASE_SRAM_DATA.nextOption = ERASE_SRAM_OPTION_CHANGING | ERASE_SRAM_OPTION_NO;
                sound = 4;
            }
            else if (gChangedInput & KEY_A)
            {
                ERASE_SRAM_DATA.nextOption = ERASE_SRAM_OPTION_CHANGING | ERASE_SRAM_OPTION_CONFIRM_NO;
                sound = 1;
                ERASE_SRAM_DATA.targetBldy = 4;
            }
            break;

        case ERASE_SRAM_OPTION_CONFIRM_NO:
            if (gChangedInput & KEY_RIGHT)
            {
                ERASE_SRAM_DATA.nextOption = ERASE_SRAM_OPTION_CHANGING | ERASE_SRAM_OPTION_CONFIRM_YES;
                sound = 4;
            }
            else if (gChangedInput & (KEY_A | KEY_B))
            {
                ERASE_SRAM_DATA.nextOption = ERASE_SRAM_OPTION_CHANGING | ERASE_SRAM_OPTION_NO;
                ERASE_SRAM_DATA.targetBldy = 0;

                if (gChangedInput & KEY_A)
                    sound = 1;
                else
                    sound = 3;
            }
            break;

        case ERASE_SRAM_OPTION_CONFIRM_YES:
            if (gChangedInput & KEY_LEFT)
            {
                ERASE_SRAM_DATA.nextOption = ERASE_SRAM_OPTION_CHANGING | ERASE_SRAM_OPTION_CONFIRM_NO;
                sound = 4;
            }
            else if (gChangedInput & KEY_A)
            {
                result = 1;
                sound = 2;
                updateCursor = TRUE;
            }
            else if (gChangedInput & KEY_B)
            {
                ERASE_SRAM_DATA.nextOption = ERASE_SRAM_OPTION_CHANGING | ERASE_SRAM_OPTION_NO;
                sound = 3;
                ERASE_SRAM_DATA.targetBldy = 0;
            }
            break;
    }

    if (updateCursor)
    {
        ERASE_SRAM_DATA.oam[0].oamId = 2;
        ERASE_SRAM_DATA.oam[0].animationDurationCounter = 0;
        ERASE_SRAM_DATA.oam[0].currentAnimationFrame = 0;
    }

    if (sEraseSramUnk_58b3b4[sound] != 0)
        SoundPlay(sEraseSramUnk_58b3b4[sound]);

    return result;
}

/**
 * @brief 80cf8 | 200 | Initializes the erase SRAM menu
 *
 */
void EraseSramMenuInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(EraseSramLoadingVBlank);

    WRITE_16(REG_BLDCNT, 0xBF);
    gWrittenToBldy = 16;
    WRITE_16(REG_BLDY, 16);

    DMA_FILL(3, 0, &gNonGameplayRam, sizeof(gNonGameplayRam), 32);

    ClearGfxRam();
    gNextOamSlot = 0;
    ResetFreeOam();

    ERASE_SRAM_DATA.language = gLanguage;
    if ((u8)(gLanguage - LANGUAGE_ENGLISH) > LANGUAGE_SPANISH - LANGUAGE_ENGLISH)
    {
        ERASE_SRAM_DATA.language = LANGUAGE_ENGLISH;
        gLanguage = LANGUAGE_JAPANESE;
    }

    while ((u16)(READ_16(REG_VCOUNT) - 21) < 140);

    DMA3_COPY_16(sEraseSramUnk_5823d0, PALRAM_BASE, 0x200 / 2);
    DMA3_COPY_16(sEraseSramUnk_5822f0, PALRAM_OBJ, 0xE0 / 2);

    LZ77UncompVram(sEraseSramUnk_58340c, VRAM_BASE + 0x1000);
    LZ77UncompVram(sEraseSramUnk_582bbc, VRAM_BASE + 0x12000);
    LZ77UncompVram(sEraseSramTextGfxPointers[ERASE_SRAM_DATA.language][0], VRAM_BASE);
    LZ77UncompVram(sEraseSramTextGfxPointers[ERASE_SRAM_DATA.language][1], VRAM_BASE + 0x11000);
    LZ77UncompVram(sEraseSramTextGfxPointers[ERASE_SRAM_DATA.language][0], VRAM_BASE + 0x10000);
    LZ77UncompVram(sEraseSramUnk_58abe4, VRAM_BASE + 0xD000);
    LZ77UncompVram(sEraseSramUnk_58adf0, VRAM_BASE + 0xF000);

    WRITE_16(REG_BG0CNT, 0);
    WRITE_16(REG_BG2CNT, 0);
    WRITE_16(REG_BG1CNT, 0x1A01);
    WRITE_16(REG_BG3CNT, 0x1E03);

    gWrittenToBldalpha_Evb = 0;
    WRITE_16(REG_BLDALPHA, 0);

    gUnk_3000be3 = FALSE;
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    EraseSramResetOam();
    EraseSramProcessOam();

    WRITE_16(REG_DISPCNT, DCNT_BG1 | DCNT_BG3 | DCNT_OBJ);
    CallbackSetVBlank(EraseSramVBlank);
}

/**
 * @brief 80ef8 | 5c | Resets the OAM of the erase SRAM menu
 *
 */
void EraseSramResetOam(void)
{
    ERASE_SRAM_DATA.currentOption = ERASE_SRAM_OPTION_NO;
    ERASE_SRAM_DATA.nextOption = ERASE_SRAM_OPTION_CHANGING | ERASE_SRAM_OPTION_NO;

    ERASE_SRAM_DATA.oam[2].oamId = sEraseSramUnk_58b3b0[ERASE_SRAM_OPTION_NO];
    ERASE_SRAM_DATA.oam[2].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[2].currentAnimationFrame = 0;
    ERASE_SRAM_DATA.oam[2].yPosition = sEraseSramUnk_58b3be[0][1];
    ERASE_SRAM_DATA.oam[2].xPosition = sEraseSramUnk_58b3be[0][0];

    ERASE_SRAM_DATA.oam[0].oamId = 1;
    ERASE_SRAM_DATA.oam[0].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[0].currentAnimationFrame = 0;

    ERASE_SRAM_DATA.oam[1].oamId = 0;
    ERASE_SRAM_DATA.oam[1].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[1].currentAnimationFrame = 0;
    ERASE_SRAM_DATA.oam[1].yPosition = sEraseSramUnk_58b3be[1][1];
    ERASE_SRAM_DATA.oam[1].xPosition = sEraseSramUnk_58b3be[1][0];

    EraseSramUpdateCursorPosition();
}

/**
 * @brief 80f54 | 4c | Updates the position of the cursor of the erase SRAM menu
 *
 */
void EraseSramUpdateCursorPosition(void)
{
    u8 row;

    // The volatile read is needed to match
    ERASE_SRAM_DATA.oam[0].yPosition = sEraseSramUnk_58b3be[row = ERASE_SRAM_DATA.currentOption / 2][1] +
        (s8)sEraseSramUnk_58b3c2[*(vu8*)&ERASE_SRAM_DATA.currentOption][1];
    ERASE_SRAM_DATA.oam[0].xPosition = sEraseSramUnk_58b3be[row][0] +
        (s8)sEraseSramUnk_58b3c2[ERASE_SRAM_DATA.currentOption][0];
}

/**
 * @brief 80fa0 | 78 | V-blank code for the erase SRAM menu
 *
 */
void EraseSramVBlank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);

    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);

    if (ERASE_SRAM_DATA.bldcnt != 0)
    {
        WRITE_16(REG_BLDCNT, ERASE_SRAM_DATA.bldcnt);
        ERASE_SRAM_DATA.bldcnt = 0;
    }
}

/**
 * @brief 81018 | c | V-blank code for the erase SRAM menu while loading
 *
 */
void EraseSramLoadingVBlank(void)
{
    UpdateAudio();
}

/**
 * @brief 81024 | 148 | Processes the OAM of the erase SRAM menu
 *
 */
void EraseSramProcessOam(void)
{
    s32 nextSlot;
    s32 currSlot;
    s16 yPosition;
    s16 xPosition;
    u16* dst;
    const u16* src;
    u16 part;
    const struct FrameData* pFrame;
    s32 i;

    gNextOamSlot = 0;
    dst = (u16*)gOamData;
    nextSlot = 0;
    currSlot = 0;

    for (i = 0; i < ARRAY_SIZE(ERASE_SRAM_DATA.oam); i++)
    {
        if (ERASE_SRAM_DATA.oam[i].oamId == 0)
            continue;

        switch (ERASE_SRAM_DATA.oam[i].oamId)
        {
            case 0:
                break;

            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                pFrame = sEraseSramOam[ERASE_SRAM_DATA.oam[i].oamId];

                if (ERASE_SRAM_DATA.oam[i].animationDurationCounter >= pFrame[ERASE_SRAM_DATA.oam[i].currentAnimationFrame].timer)
                {
                    ERASE_SRAM_DATA.oam[i].animationDurationCounter = 0;
                    ERASE_SRAM_DATA.oam[i].currentAnimationFrame++;

                    if (pFrame[ERASE_SRAM_DATA.oam[i].currentAnimationFrame].timer == 0)
                        ERASE_SRAM_DATA.oam[i].currentAnimationFrame = 0;
                }
                break;
        }

        ERASE_SRAM_DATA.oam[i].animationDurationCounter++;

        yPosition = (u16)(ERASE_SRAM_DATA.oam[i].yPosition - gBg1YPosition);
        xPosition = (u16)(ERASE_SRAM_DATA.oam[i].xPosition - gBg1XPosition);

        pFrame += ERASE_SRAM_DATA.oam[i].currentAnimationFrame;
        src = pFrame->pFrame;

        nextSlot += *src++;

        for (; currSlot < nextSlot; currSlot++)
        {
            part = *src++;
            *dst++ = part;
            gOamData[currSlot].split.y = part + yPosition;

            part = *src++;
            *dst++ = part;
            gOamData[currSlot].split.x = (part + xPosition) & 0x1FF;

            *dst++ = *src++;

            gOamData[currSlot].split.priority = 1;

            dst++;
        }
    }

    gNextOamSlot = nextSlot;
}
