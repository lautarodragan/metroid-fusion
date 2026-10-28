#include "menus/navigation_conversation.h"

#include "gba.h"
#include "globals.h"
#include "audio_wrappers.h"
#include "syscalls.h"

#include "constants/audio.h"
#include "constants/event.h"

#include "data/sa_x_close_up.h"

/**
 * @brief 7c318 | 9c | Clears the graphics of the pop ups of a navigation conversation
 *
 */
void NavigationConversationClearPopUpGraphics(void)
{
    s32 i;
    void* dst;

    for (i = 5, dst = VRAM_OBJ + 0x5700; i >= 0; dst -= 0x400, i--)
        BitFill(3, -1, dst, 0x100, 32);

    DMA3_FILL_32(0, PALRAM_OBJ + 0x1E0, 0x20);

    if (PAUSE_SCREEN_DATA.unk_21A == 3)
        SoundStop(SOUND_125);

    PAUSE_SCREEN_DATA.currentPopUp = 0;
    PAUSE_SCREEN_DATA.unk_21C = 0;
    PAUSE_SCREEN_DATA.unk_21B = 0;
    PAUSE_SCREEN_DATA.unk_21D = 0;
    PAUSE_SCREEN_DATA.unk_219++;
}

/**
 * @brief 7c3b4 | 8c | Updates the palette cycle of the current pop up of a navigation conversation
 *
 */
void unk_7c3b4(void)
{
    const u16* pPalette;

    if (sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].unk_10 == 0)
        return;

    PAUSE_SCREEN_DATA.unk_229++;
    if (PAUSE_SCREEN_DATA.unk_229 < sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].unk_10)
        return;

    PAUSE_SCREEN_DATA.unk_229 = 0;

    pPalette = &sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].pCyclePalette[PAUSE_SCREEN_DATA.unk_228];
    if (*pPalette == 0)
    {
        PAUSE_SCREEN_DATA.unk_228 = 0;
        pPalette = sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].pCyclePalette;
    }

    *(u16*)(PALRAM_OBJ + 0x1FE) = *pPalette;

    PAUSE_SCREEN_DATA.unk_228++;
    if (PAUSE_SCREEN_DATA.unk_228 > 15)
        PAUSE_SCREEN_DATA.unk_228 = 0;
}

/**
 * @brief 7c440 | 174 | Updates the palette animations of a navigation conversation
 *
 */
void unk_7c440(void)
{
    u16 i;
    u16 j;
    u16* dst;

    PAUSE_SCREEN_DATA.unk_225++;
    if (PAUSE_SCREEN_DATA.unk_225 >= sUnk_57beb4[PAUSE_SCREEN_DATA.unk_224])
    {
        PAUSE_SCREEN_DATA.unk_225 = 0;
        PAUSE_SCREEN_DATA.unk_224++;
        if (PAUSE_SCREEN_DATA.unk_224 > 3)
            PAUSE_SCREEN_DATA.unk_224 = 0;

        dst = PALRAM_BASE;
        dst[0x12] = sUnk_57bcd4[PAUSE_SCREEN_DATA.unk_224];
        dst[0x13] = sUnk_57bcd4[PAUSE_SCREEN_DATA.unk_224];
        dst[0x22] = sUnk_57bcf4[PAUSE_SCREEN_DATA.unk_224];
        dst[0x23] = sUnk_57bcf4[PAUSE_SCREEN_DATA.unk_224];
    }

    if (PAUSE_SCREEN_DATA.unk_0 == 0)
        return;

    if (PAUSE_SCREEN_DATA.unk_0 == 1)
    {
        PAUSE_SCREEN_DATA.unk_22D++;
        if (PAUSE_SCREEN_DATA.unk_22D >= sUnk_57beb8[PAUSE_SCREEN_DATA.unk_22C])
        {
            PAUSE_SCREEN_DATA.unk_22D = 0;
            PAUSE_SCREEN_DATA.unk_22C++;
            if (PAUSE_SCREEN_DATA.unk_22C > 3)
                PAUSE_SCREEN_DATA.unk_22C = 0;

            dst = PALRAM_BASE + 0x138;
            j = PAUSE_SCREEN_DATA.unk_22C * 16 + 12;
            for (i = 0; i < 4; i++, j++, dst++)
                *dst = sUnk_57bd34[j];
        }
    }
    else if (PAUSE_SCREEN_DATA.unk_0 == 2)
    {
        PAUSE_SCREEN_DATA.unk_22D++;
        if (PAUSE_SCREEN_DATA.unk_22D >= sUnk_57bebc[PAUSE_SCREEN_DATA.unk_22C])
        {
            PAUSE_SCREEN_DATA.unk_22D = 0;
            PAUSE_SCREEN_DATA.unk_22C++;
            if (PAUSE_SCREEN_DATA.unk_22C > 7)
                PAUSE_SCREEN_DATA.unk_22C = 0;

            dst = PALRAM_BASE + 0x194;
            j = PAUSE_SCREEN_DATA.unk_22C * 16 + 10;
            for (i = 0; i < 6; i++, j++, dst++)
                *dst = sUnk_57bdb4[j];
        }
    }
}

/**
 * @brief 7c5b4 | 7c | Loads the special graphics of a navigation conversation
 *
 */
void NavigationConversationLoadSpecialGraphics(void)
{
    if (PAUSE_SCREEN_DATA.conversationNumber == NAV_CONVO_GO_TO_OPERATIONS_ROOM)
    {
        LZ77UncompVram(sNavConversationUnk_57c0c4, EWRAM_BASE);
        LZ77UncompVram(sNavConversationUnk_57fca0, EWRAM_BASE + 0x6000);
        LZ77UncompVram(sNavConversationUnk_580238, EWRAM_BASE + 0x6800);
        LZ77UncompVram(sNavConversationUnk_5807d0, EWRAM_BASE + 0x7000);
        LZ77UncompVram(sNavConversationUnk_580d68, EWRAM_BASE + 0x7800);
    }
    else if (PAUSE_SCREEN_DATA.conversationNumber == NAV_CONVO_FIND_SECURITY_ROOM_AND_DOWNLOAD_BOMBS)
    {
        LZ77UncompVram(sSaXCloseUpGfx, EWRAM_BASE);
    }
}
