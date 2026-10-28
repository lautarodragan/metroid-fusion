#include "menus/navigation_conversation.h"

#include "gba.h"
#include "globals.h"
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
