#include "globals.h"
#include "special_cutscene.h"
#include "text.h"

#include "constants/text.h"

#include "structs/intro.h"

/**
 * @brief 97dd0 | d8 | Checks if the new file intro monologue ended
 *
 * @return boolu32 Ended
 */
boolu32 NewFileIntroCheckMonologueEnded(void)
{
    boolu32 ended;

    ended = FALSE;
    INTRO_DATA.unk_20C++;

    if (*INTRO_DATA.pText == CHAR_TERMINATOR)
    {
        INTRO_DATA.unk_20C = 0;
        INTRO_DATA.unk_213 = 100;
        ended = TRUE;
    }
    else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.unk_20C = 0;

        if (INTRO_DATA.unk_218 == 1)
        {
            INTRO_DATA.pText++;
            INTRO_DATA.unk_213 = 1;

            if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
            {
                INTRO_DATA.unk_218 = 2;
            }
            else if (*INTRO_DATA.pText == CHAR_TERMINATOR)
            {
                INTRO_DATA.unk_218 = 3;
            }
            else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
            {
                INTRO_DATA.unk_218 = 4;
                INTRO_DATA.pText++;

                if (*INTRO_DATA.pText == CHAR_TERMINATOR)
                    INTRO_DATA.unk_218 = 3;
            }
            else
            {
                INTRO_DATA.unk_218 = 0;
            }
        }
    }
    else if ((*INTRO_DATA.pText & CHAR_MASK) == CHAR_DELAY)
    {
        if (LOW_BYTE(*INTRO_DATA.pText) <= INTRO_DATA.unk_20C)
        {
            INTRO_DATA.unk_213 = 1;
            INTRO_DATA.unk_20C = 0;
        }
    }
    else if (INTRO_DATA.unk_20C > 2)
    {
        INTRO_DATA.unk_213 = 1;
        INTRO_DATA.unk_20C = 0;
    }

    return ended;
}

/**
 * @brief 97ea8 | d8 | Checks if the ending monologue ended
 *
 * @return boolu32 Ended
 */
boolu32 EndingCheckMonologueEnded(void)
{
    boolu32 ended;

    ended = FALSE;
    INTRO_DATA.unk_20C++;

    if (*INTRO_DATA.pText == CHAR_TERMINATOR)
    {
        INTRO_DATA.unk_20C = 0;
        INTRO_DATA.unk_213 = 100;
        ended = TRUE;
    }
    else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.unk_20C = 0;

        if (INTRO_DATA.unk_218 == 1)
        {
            INTRO_DATA.pText++;
            INTRO_DATA.unk_213 = 1;

            if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
            {
                INTRO_DATA.unk_218 = 2;
            }
            else if (*INTRO_DATA.pText == CHAR_TERMINATOR)
            {
                INTRO_DATA.unk_218 = 3;
            }
            else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
            {
                INTRO_DATA.unk_218 = 4;
                INTRO_DATA.pText++;

                if (*INTRO_DATA.pText == CHAR_TERMINATOR)
                    INTRO_DATA.unk_218 = 3;
            }
            else
            {
                INTRO_DATA.unk_218 = 0;
            }
        }
    }
    else if ((*INTRO_DATA.pText & CHAR_MASK) == CHAR_DELAY)
    {
        if (LOW_BYTE(*INTRO_DATA.pText) <= INTRO_DATA.unk_20C)
        {
            INTRO_DATA.unk_213 = 1;
            INTRO_DATA.unk_20C = 0;
        }
    }
    else if (INTRO_DATA.unk_20C > 3)
    {
        INTRO_DATA.unk_213 = 1;
        INTRO_DATA.unk_20C = 0;
    }

    return ended;
}

/**
 * @brief 97f80 | 1d8 | Processes the monologue text of a special cutscene
 *
 */
void SpecialCutsceneProcessMonologue(void)
{
    u16 i;
    u32 width;
    u32* dst;

    if (*INTRO_DATA.pText == CHAR_TERMINATOR)
        return;

    if (*INTRO_DATA.pText == CHAR_NEW_LINE)
    {
        for (i = INTRO_DATA.unk_C + 1; i < MONOLOGUE_LINE_LENGTH; i++)
            INTRO_TEXT_TILE_DELAY[i + INTRO_DATA.unk_E / 2 * MONOLOGUE_LINE_LENGTH] |= UCHAR_MAX;

        INTRO_DATA.unk_C = 0;
        INTRO_DATA.unk_E += 2;
        INTRO_DATA.pText++;
        INTRO_DATA.unk_212 = 0;
    }
    else if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
    {
        DMA3_FILL_32(0, VRAM_BASE, 0x4800);

        INTRO_DATA.unk_12 = 0;
        INTRO_DATA.unk_10 = 0;
        INTRO_DATA.unk_E = 0;
        INTRO_DATA.unk_C = 0;
        INTRO_DATA.pText++;
        INTRO_DATA.unk_212 = 0;

        DMA3_FILL_32(0, INTRO_DATA.unk_14, sizeof(INTRO_DATA.unk_14));
        DMA3_FILL_32(0, INTRO_TEXT_TILE_TIMER, sizeof(INTRO_DATA.unk_14));
        DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0x4800, 0x800 / sizeof(u32));
    }
    else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.unk_C++;
    }
    else if ((*INTRO_DATA.pText & CHAR_MASK) == CHAR_DELAY)
    {
        INTRO_DATA.pText++;
    }
    else
    {
        dst = VRAM_BASE + (INTRO_DATA.unk_C * 32 + INTRO_DATA.unk_E * 0x400);
        width = TextGetCharacterWidth(*INTRO_DATA.pText);
        TextDrawCharacter(*INTRO_DATA.pText, dst, width, INTRO_DATA.unk_212, 0);

        if (INTRO_DATA.unk_C < MONOLOGUE_LINE_LENGTH)
        {
            INTRO_TEXT_TILE_DELAY[INTRO_DATA.unk_E / 2 * MONOLOGUE_LINE_LENGTH + INTRO_DATA.unk_C] = 4;
            INTRO_DATA.unk_212 += width;

            while (INTRO_DATA.unk_212 >= 8)
            {
                INTRO_DATA.unk_212 -= 8;
                INTRO_DATA.unk_C++;

                if (INTRO_DATA.unk_C >= MONOLOGUE_LINE_LENGTH)
                    break;

                if (INTRO_DATA.unk_212 != 0)
                    INTRO_TEXT_TILE_DELAY[INTRO_DATA.unk_E / 2 * MONOLOGUE_LINE_LENGTH + INTRO_DATA.unk_C] = 4;
            }
        }

        INTRO_DATA.pText++;
    }
}

