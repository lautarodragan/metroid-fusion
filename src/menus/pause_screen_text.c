#include "menus/pause_screen_text.h"
#include "menus/navigation_conversation.h"

#include "gba.h"
#include "globals.h"
#include "dma.h"
#include "text.h"
#include "new_file_intro.h"

#include "data/event_data.h"

#include "structs/event.h"

/**
 * @brief 7b8d4 | 11c | Draws the text of the pause screen (current objective)
 *
 */
void ProcessPauseScreenText(void)
{
    s32 indent;
    u16* pText;
    u32 width;
    s32 offset;
    void* dst;
    s32 temp;

    BitFill(3, 0, EWRAM_BASE + 0xC000, 0x1000, 16);

    indent = 0;
    dst = EWRAM_BASE + 0xC000;
    pText = sPauseScreenTextPointers[gLanguage][gEventCounter];

    while (*pText != 0xFF00)
    {
        // Doubles as the "should draw" flag
        temp = TRUE;

        if ((*pText & 0xFF00) == 0x8000)
        {
            width = *pText & 0xFF;
            temp = FALSE;
        }
        else if ((*pText & 0xFF00) == 0x8300)
        {
            width = 0;
            indent = *pText & 0xFF;
            temp = FALSE;
        }
        else if (*pText == 0xFE00)
        {
            width = 0;
            if (indent > 0xE0)
                break;

            indent = 0xE0;
            temp = FALSE;
        }

        if (temp)
        {
            width = TextGetCharacterWidth(*pText);
            temp = indent + width;

            if (temp > 0xE0 && indent < 0xE0)
                indent = 0xE0;
            else if (temp > 0x1C0)
                break;

            if (indent >= 0xE0)
            {
                temp = 0x800;
                offset = indent - 0xE0;
            }
            else
            {
                temp = 0;
                offset = indent;
            }

            temp += (offset >> 3) * 32;
            offset &= 7;
            TextDrawCharacter(*pText, dst + temp, width, offset, 0);
        }

        pText++;
        indent += width;

        if (indent >= 0x1C0)
            break;
    }
}

/**
 * @brief 7b9f0 | 200 | Draws the text of the easy sleep menu
 *
 */
void ProcessEasySleepText(void)
{
    s32 indent;
    u16* pText;
    u32 width;
    s32 offset;
    void* dst;
    // Doubles as the "should draw" flag
    s32 temp;
    s32 i;

    BitFill(3, 0, EWRAM_BASE + 0xD000, 0x1000, 16);
    BitFill(3, 0, EWRAM_BASE + 0xE000, 0x1000, 16);
    BitFill(3, 0, EWRAM_BASE + 0xF000, 0x800, 16);

    for (i = 0; i < 2; i++)
    {
        dst = EWRAM_BASE + 0xE000;
        if (i == 0)
            dst = EWRAM_BASE + 0xD000;

        pText = sMessageTextPointers[gLanguage][i + 45];
        indent = 0;

        while (*pText != 0xFF00)
        {
            temp = TRUE;

            if ((*pText & 0xFF00) == 0x8000)
            {
                width = *pText & 0xFF;
                temp = FALSE;
            }
            else if ((*pText & 0xFF00) == 0x8300)
            {
                width = 0;
                indent = *pText & 0xFF;
                temp = FALSE;
            }
            else if (*pText == 0xFE00)
            {
                width = 0;
                if (indent > 0xE0)
                    break;

                indent = 0xE0;
                temp = FALSE;
            }

            if (temp)
            {
                width = TextGetCharacterWidth(*pText);
                temp = indent + width;

                if (temp > 0xE0 && indent < 0xE0)
                    indent = 0xE0;
                else if (temp > 0x1C0)
                    break;

                if (indent >= 0xE0)
                {
                    temp = 0x800;
                    offset = indent - 0xE0;
                }
                else
                {
                    temp = 0;
                    offset = indent;
                }

                temp += (offset >> 3) * 32;
                offset &= 7;
                TextDrawCharacter(*pText, dst + temp, width, offset, 0);
            }

            pText++;
            indent += width;

            if (indent >= 0x1C0)
                break;
        }
    }

    dst = EWRAM_BASE + 0xF000;
    pText = sMessageTextPointers[gLanguage][47];
    indent = 0;

    while (*pText != 0xFF00)
    {
        temp = TRUE;

        if (*pText == 0xFE00)
        {
            width = 0;
            if (indent <= 0x70)
                indent = 0x70;
            else
                break;
            temp = FALSE;
        }
        else if (*pText & 0x8000)
        {
            width = 0;
            temp = FALSE;
        }

        if (temp)
        {
            width = TextGetCharacterWidth(*pText);
            temp = indent + width;

            if (temp > 0x1C0)
                break;

            temp = (indent >> 3) * 32;
            offset = indent & 7;
            TextDrawCharacter(*pText, dst + temp, width, offset, 0);
        }

        pText++;
        indent += width;

        if (indent >= 0x1C0)
            break;
    }
}

/**
 * @brief 7bbf0 | a8 | Gets the number of the sector that should be flashing
 *
 * @return u8 Sector number
 */
u8 GetFlashingSectorNumber(void)
{
    s32 i;
    u32 found;

    gFlashingSectorNumber = 0;

    for (i = gEventCounter; i > 0; i--)
    {
        if (sEventLocationAndNavigationInfo[i].navConversation != 0)
            break;
    }

    found = sEventLocationAndNavigationInfo[i].navConversation;
    if (gPreviousNavigationConversation != found)
        return gFlashingSectorNumber;

    found = FALSE;
    for (i = 0; i < sizeof(sNavConversationUnk_5766e4) / sizeof(sNavConversationUnk_5766e4[0]); i++)
    {
        if (gPreviousNavigationConversation == sNavConversationUnk_5766e4[i].conversation)
        {
            found = TRUE;
            break;
        }
    }

    if (!found)
        return gFlashingSectorNumber;

    i = sNavConversationUnk_5766e4[i].location;
    gFlashingSectorNumber = sNavigationTargetLocationAreas[i];
    return gFlashingSectorNumber;
}
