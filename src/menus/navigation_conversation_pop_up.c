#include "menus/navigation_conversation.h"

#include "gba.h"
#include "globals.h"
#include "macros.h"
#include "dma.h"
#include "syscalls.h"
#include "audio_wrappers.h"

#include "constants/audio.h"

/**
 * @brief 7bc98 | f8 | Loads the graphics of the pop ups of a navigation conversation
 *
 */
void NavigationConversationLoadPopUpGraphics(void)
{
    s32 i;
    void* dst;

    for (i = ARRAY_SIZE(sNavConversationUnk_57bcc8); i > 0; i--)
    {
        if (PAUSE_SCREEN_DATA.conversationNumber == sNavConversationUnk_57bcc8[i - 1].conversation)
            break;
    }

    if (i == 0)
        return;

    i--;

    if (sNavConversationUnk_57bcc8[i].popUps[0] != 0)
        LZ77UncompVram(sNavConversationUnk_57bc50[sNavConversationUnk_57bcc8[i].popUps[0]].pGraphics, EWRAM_BASE);

    if (sNavConversationUnk_57bcc8[i].popUps[1] != 0)
        LZ77UncompVram(sNavConversationUnk_57bc50[sNavConversationUnk_57bcc8[i].popUps[1]].pGraphics, EWRAM_BASE + 0x4000);

    if (sNavConversationUnk_57bcc8[i].popUps[2] != 0)
        LZ77UncompVram(sNavConversationUnk_57bc50[sNavConversationUnk_57bcc8[i].popUps[2]].pGraphics, EWRAM_BASE + 0x8000);

    for (i = 5, dst = VRAM_OBJ + 0x5700; i >= 0; dst -= 0x400, i--)
        BitFill(3, -1, dst, 0x100, 32);

    DMA3_FILL_32(0, PALRAM_OBJ + 0x1E0, 0x20);
}

/**
 * @brief 7bd90 | 50 | Updates the current pop up of a navigation conversation
 *
 */
void NavigationConversationUpdatePopUp(void)
{
    if (PAUSE_SCREEN_DATA.currentPopUp == 0)
        return;

    PAUSE_SCREEN_DATA.unk_21B++;
    sNavConversationUnk_79c170[PAUSE_SCREEN_DATA.currentPopUp - 1]();

    if (PAUSE_SCREEN_DATA.unk_21D)
        NavigationConversationFadeInPopUpPalette();
}

/**
 * @brief 7bde0 | 1f4 | Initializes a pop up of a navigation conversation
 *
 */
void unk_7bde0(void)
{
    s32 i;
    s32 count;
    u8 conversation;
    struct NavConversationPopUpTiles tiles;

    PAUSE_SCREEN_DATA.unk_21A = UCHAR_MAX;

    i = ARRAY_SIZE(sNavConversationUnk_57bcc8);
    conversation = PAUSE_SCREEN_DATA.conversationNumber;
    for (; i > 0; i--)
    {
        if (conversation == sNavConversationUnk_57bcc8[i - 1].conversation)
            break;
    }

    i--;
    if (i == UCHAR_MAX)
    {
        PAUSE_SCREEN_DATA.currentPopUp = 0;
        return;
    }

    if (PAUSE_SCREEN_DATA.unk_219 == 1)
        PAUSE_SCREEN_DATA.unk_21A = sNavConversationUnk_57bcc8[i].popUps[1];
    else if (PAUSE_SCREEN_DATA.unk_219 == 2)
        PAUSE_SCREEN_DATA.unk_21A = sNavConversationUnk_57bcc8[i].popUps[2];
    else
        PAUSE_SCREEN_DATA.unk_21A = sNavConversationUnk_57bcc8[i].popUps[0];

    if (PAUSE_SCREEN_DATA.unk_21A == 0)
    {
        PAUSE_SCREEN_DATA.currentPopUp = 0;
        return;
    }

    PAUSE_SCREEN_DATA.unk_229 = 0;
    PAUSE_SCREEN_DATA.unk_228 = 0;

    if (PAUSE_SCREEN_DATA.unk_219 == 1)
        PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE + 0x4000;
    else if (PAUSE_SCREEN_DATA.unk_219 == 2)
        PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE + 0x8000;
    else
        PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE;

    if (sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].unk_12_0 == 8)
    {
        tiles = sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].tiles;
        for (count = tiles.count; count > 0;)
        {
            count--;
            DMA3_COPY_16(&PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer[count * 0x100],
                VRAM_OBJ + 0x4300 + count * 0x400 + sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].tiles.slot * 0x400, 0x80);
        }
    }
    else if (sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].unk_12_0 == 4)
    {
        tiles = sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].tiles;
        for (count = tiles.count; count > 0;)
        {
            count--;
            DMA3_COPY_16(&PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer[count * 0x100],
                VRAM_OBJ + 0x4300 + count * 0x400 + sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].tiles.slot * 0x400 + 0x40, 0x40);
        }
    }

    if (PAUSE_SCREEN_DATA.unk_21A == 3)
        SoundPlay(SOUND_125);

    PAUSE_SCREEN_DATA.unk_21D = TRUE;
    PAUSE_SCREEN_DATA.currentPopUp++;
    PAUSE_SCREEN_DATA.unk_21B = 0;
}

/**
 * @brief 7bfd4 | fc | Fades in the palette of the current pop up of a navigation conversation
 *
 */
void NavigationConversationFadeInPopUpPalette(void)
{
    const u16* src;
    u16* dst;
    s32 i;
    s32 j;
    u8 target[3];
    u8 current[3];

    src = sNavConversationUnk_57bc50[PAUSE_SCREEN_DATA.unk_21A].pPalette;
    dst = PALRAM_OBJ + 0x1E0;

    for (i = 0; i < 16; i++, src++, dst++)
    {
        target[0] = RED(*src);
        target[1] = GREEN(*src);
        target[2] = BLUE(*src);

        current[0] = RED(*dst);
        current[1] = GREEN(*dst);
        current[2] = BLUE(*dst);

        for (j = 0; j < 3; j++)
        {
            if (target[j] > current[j])
                current[j]++;
            else if (target[j] < current[j])
                current[j]--;
        }

        *dst = current[0] | current[1] << 5 | current[2] << 10;
    }

    if (PAUSE_SCREEN_DATA.unk_21D > 0x20)
        PAUSE_SCREEN_DATA.unk_21D = 0;
    else
        PAUSE_SCREEN_DATA.unk_21D++;
}
