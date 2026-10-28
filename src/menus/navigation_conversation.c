#include "menus/navigation_conversation.h"

#include "gba.h"
#include "globals.h"
#include "audio_wrappers.h"
#include "sound_event.h"
#include "text.h"
#include "new_file_intro.h"

#include "constants/audio.h"
#include "constants/event.h"

#include "structs/event.h"

// Called without a prototype in the original code (the character isn't truncated to a u8),
// music_wrappers.h isn't included for that reason
void PlayCharacterAppearingSound();

#define NAV_TEXT_TIMER(slot) (PAUSE_SCREEN_DATA.unk_E[(slot)])
#define NAV_TEXT_POS(slot) ((&PAUSE_SCREEN_DATA.unk_E[2])[(slot)])

/**
 * @brief 7a0fc | 1e0 | Processes the text of a message during a navigation conversation
 * 
 * @param messageId Message ID
 * @return bool, ended
 */
u32 unk_7a0fc(u8 messageId)
{
    u32 ended;
    u32 secondLine;
    u16* pText;
    u8* dst;
    s32 position;

    if (!(PAUSE_SCREEN_DATA.typeFlags & 0x8))
        return FALSE;

    ended = FALSE;
    secondLine = FALSE;

    while (TRUE)
    {
        pText = sMessageTextPointers[gLanguage][messageId + 43];
        dst = VRAM_BASE + 0x7000;
        pText += PAUSE_SCREEN_DATA.unk_21;
        if (*pText == 0xFE00)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent = 0xE0;
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if ((*pText & 0xFF00) == 0x8000)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent += *(u8*)pText;
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if ((*pText & 0xFF00) == 0x8300)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            if (PAUSE_SCREEN_DATA.navConvTextIndent >= 0xE0)
                PAUSE_SCREEN_DATA.navConvTextIndent = 0xE0;
            else
                PAUSE_SCREEN_DATA.navConvTextIndent = 0;

            PAUSE_SCREEN_DATA.navConvTextIndent += *(u8*)pText;
            if (*pText == 0x83A0)
                PAUSE_SCREEN_DATA.navConvTextIndent -= 0x10;
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if (!secondLine)
        {
            if (*pText != 0x40 && PAUSE_SCREEN_DATA.navConvTextIndent < 0xE0)
            {
                if (PAUSE_SCREEN_DATA.unk_1A && !(gButtonInput & (KEY_A | KEY_B | KEY_DOWN)))
                    PAUSE_SCREEN_DATA.unk_1A = FALSE;

                PAUSE_SCREEN_DATA.unk_20++;
                if (!(gButtonInput & (KEY_A | KEY_B | KEY_DOWN)) || PAUSE_SCREEN_DATA.unk_1A)
                {
                    if (PAUSE_SCREEN_DATA.unk_20 < 8)
                        return ended;
                }
            }
            PAUSE_SCREEN_DATA.unk_20 = 0;
        }

        PAUSE_SCREEN_DATA.navConvCharacterWidth = TextGetCharacterWidth(*pText);

        if (PAUSE_SCREEN_DATA.navConvTextIndent + PAUSE_SCREEN_DATA.navConvCharacterWidth > 0xE0 &&
            PAUSE_SCREEN_DATA.navConvTextIndent < 0xE0)
            PAUSE_SCREEN_DATA.navConvTextIndent = 0xE0;

        position = PAUSE_SCREEN_DATA.navConvTextIndent;
        if (position == 0 || position == 0xE0)
            PAUSE_SCREEN_DATA.navConvTextIndent = position;

        if (*pText != 0x40)
        {
            PlayCharacterAppearingSound(*pText, 1);

            position = PAUSE_SCREEN_DATA.navConvTextIndent;
            if (PAUSE_SCREEN_DATA.navConvTextIndent >= 0xE0)
            {
                secondLine = TRUE;
                dst += 0x800;
                position -= 0xE0;
            }
            dst += (position >> 3) * 32;

            position = PAUSE_SCREEN_DATA.navConvTextIndent & 7;
            TextDrawCharacter(*pText, (u32*)dst, PAUSE_SCREEN_DATA.navConvCharacterWidth, position, 0);
        }

        PAUSE_SCREEN_DATA.navConvTextIndent += PAUSE_SCREEN_DATA.navConvCharacterWidth;
        PAUSE_SCREEN_DATA.unk_21++;

        if (pText[1] == 0xFF00)
            ended = TRUE;

        if (!secondLine || ended)
            break;
    }

    return ended;
}
