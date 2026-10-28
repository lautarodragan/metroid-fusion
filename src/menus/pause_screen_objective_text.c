#include "menus/pause_screen_text.h"

#include "gba.h"
#include "globals.h"
#include "dma.h"
#include "text.h"

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
