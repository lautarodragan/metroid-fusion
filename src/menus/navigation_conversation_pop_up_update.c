#include "menus/navigation_conversation.h"

#include "gba.h"
#include "globals.h"
#include "macros.h"

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
