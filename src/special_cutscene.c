#include "globals.h"
#include "special_cutscene.h"
#include "text.h"

#include "constants/text.h"

#include "structs/intro.h"

// Declared without a prototype, the character argument isn't truncated
void PlayCharacterAppearingSound();

/**
 * @brief 9828c | 220 | Processes Adam's text in the ending
 *
 * @return boolu32 Finished
 */
boolu32 EndingProcessAdamText(void)
{
    boolu32 finished;
    u32 width;
    u32* dst;

    finished = FALSE;
    INTRO_DATA.unk_20C++;

    if (*INTRO_DATA.pText == CHAR_TERMINATOR)
    {
        if (INTRO_DATA.unk_20C > 15)
        {
            INTRO_DATA.unk_20C = 0;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.unk_212 = 0;
            finished = TRUE;
        }
    }
    else if (*INTRO_DATA.pText == CHAR_NEW_LINE)
    {
        if (INTRO_DATA.unk_E < 2)
        {
            if (INTRO_DATA.unk_20C > 5)
            {
                INTRO_DATA.unk_20C = 0;
                INTRO_DATA.unk_E = 2;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.pText++;
            }
        }
        else if (INTRO_DATA.unk_20C > 125)
        {
            INTRO_DATA.unk_20C = 0;
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.unk_212 = 0;
            INTRO_DATA.pText++;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
        }
    }
    else if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
    {
        if (INTRO_DATA.unk_20C > 15)
        {
            INTRO_DATA.unk_20C = 0;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.pText++;
            INTRO_DATA.unk_212 = 0;
        }
    }
    else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.unk_20C = 0;

        if (INTRO_DATA.unk_218 == 1)
        {
            INTRO_DATA.pText++;

            if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
                INTRO_DATA.unk_218 = 2;
            else if (*INTRO_DATA.pText == CHAR_TERMINATOR)
                INTRO_DATA.unk_218 = 3;
            else
                INTRO_DATA.unk_218 = 0;
        }
    }
    else if ((*INTRO_DATA.pText & CHAR_MASK) == CHAR_DELAY)
    {
        if (LOW_BYTE(*INTRO_DATA.pText) <= INTRO_DATA.unk_20C)
        {
            INTRO_DATA.unk_20C = 0;
            INTRO_DATA.pText++;
        }
    }
    else if (INTRO_DATA.unk_20C > 5)
    {
        INTRO_DATA.unk_20C = 0;

        dst = VRAM_BASE + 0xD000 + (INTRO_DATA.unk_C * 32 + INTRO_DATA.unk_E * 0x400);
        width = TextGetCharacterWidth(*INTRO_DATA.pText);
        TextDrawCharacter(*INTRO_DATA.pText, dst, width, INTRO_DATA.unk_212, 0);

        if (*INTRO_DATA.pText != 0x40)
            PlayCharacterAppearingSound(*INTRO_DATA.pText, 1);

        if (INTRO_DATA.unk_C < 32)
        {
            INTRO_DATA.unk_212 += width;

            while (INTRO_DATA.unk_212 >= 8)
            {
                INTRO_DATA.unk_212 -= 8;
                INTRO_DATA.unk_C++;

                if (INTRO_DATA.unk_C >= 32)
                    break;
            }
        }

        INTRO_DATA.pText++;
    }

    return finished;
}

/**
 * @brief 984ac | 244 | Processes the text of the intro
 *
 * @return boolu32 Finished
 */
boolu32 IntroProcessText(void)
{
    boolu32 finished;
    u32 width;
    u32* dst;

    finished = FALSE;
    INTRO_DATA.unk_20C++;

    if (*INTRO_DATA.pText == CHAR_TERMINATOR)
    {
        if (INTRO_DATA.unk_20C > 12)
        {
            INTRO_DATA.unk_20C = 0;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.unk_212 = 0;
            finished = TRUE;
        }
    }
    else if (*INTRO_DATA.pText == CHAR_NEW_LINE)
    {
        if (INTRO_DATA.unk_E < 2)
        {
            if (INTRO_DATA.unk_20C > 2)
            {
                INTRO_DATA.unk_20C = 0;
                INTRO_DATA.unk_E = 2;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.pText++;
            }
        }
        else if (INTRO_DATA.unk_20C > 122)
        {
            INTRO_DATA.unk_20C = 0;
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.unk_212 = 0;
            INTRO_DATA.pText++;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
        }
    }
    else if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
    {
        if (INTRO_DATA.unk_20C > 12)
        {
            INTRO_DATA.unk_20C = 0;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.pText++;
            INTRO_DATA.unk_212 = 0;
        }
    }
    else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.unk_20C = 0;

        if (INTRO_DATA.unk_218 == 1)
        {
            INTRO_DATA.pText++;

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
                INTRO_DATA.pText++;

                if (*INTRO_DATA.pText == CHAR_TERMINATOR)
                    INTRO_DATA.unk_218 = 3;
                else
                    INTRO_DATA.unk_218 = 4;
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
            INTRO_DATA.unk_20C = 0;
            INTRO_DATA.pText++;
        }
    }
    else if (INTRO_DATA.unk_20C > 2)
    {
        INTRO_DATA.unk_20C = 0;

        dst = VRAM_BASE + 0xD000 + (INTRO_DATA.unk_C * 32 + INTRO_DATA.unk_E * 0x400);
        width = TextGetCharacterWidth(*INTRO_DATA.pText);
        TextDrawCharacter(*INTRO_DATA.pText, dst, width, INTRO_DATA.unk_212, 0);

        if (INTRO_DATA.unk_C < 32)
        {
            INTRO_DATA.unk_212 += width;

            while (INTRO_DATA.unk_212 >= 8)
            {
                INTRO_DATA.unk_212 -= 8;
                INTRO_DATA.unk_C++;

                if (INTRO_DATA.unk_C >= 32)
                    break;
            }
        }

        INTRO_DATA.pText++;
    }

    return finished;
}

/**
 * @brief 986f0 | 250 | Processes Adam's text in the new file intro
 *
 * @return boolu32 Finished
 */
boolu32 NewFileIntroProcessAdamText(void)
{
    boolu32 finished;
    u32 width;
    u32* dst;

    finished = FALSE;
    INTRO_DATA.unk_20C++;

    if (*INTRO_DATA.pText == CHAR_TERMINATOR)
    {
        if (INTRO_DATA.unk_20C > 12)
        {
            INTRO_DATA.unk_20C = 0;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.unk_212 = 0;
            finished = TRUE;
        }
    }
    else if (*INTRO_DATA.pText == CHAR_NEW_LINE)
    {
        if (INTRO_DATA.unk_E < 2)
        {
            if (INTRO_DATA.unk_20C > 2)
            {
                INTRO_DATA.unk_20C = 0;
                INTRO_DATA.unk_E = 2;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.pText++;
            }
        }
        else if (INTRO_DATA.unk_20C > 122)
        {
            INTRO_DATA.unk_20C = 0;
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.unk_212 = 0;
            INTRO_DATA.pText++;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
        }
    }
    else if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
    {
        if (INTRO_DATA.unk_20C > 12)
        {
            INTRO_DATA.unk_20C = 0;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.pText++;
            INTRO_DATA.unk_212 = 0;
        }
    }
    else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.unk_20C = 0;

        if (INTRO_DATA.unk_218 == 1)
        {
            INTRO_DATA.pText++;

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
                INTRO_DATA.pText++;

                if (*INTRO_DATA.pText == CHAR_TERMINATOR)
                    INTRO_DATA.unk_218 = 3;
                else
                    INTRO_DATA.unk_218 = 4;
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
            INTRO_DATA.unk_20C = 0;
            INTRO_DATA.pText++;
        }
    }
    else if (INTRO_DATA.unk_20C > 2)
    {
        INTRO_DATA.unk_20C = 0;

        dst = VRAM_BASE + 0xD000 + (INTRO_DATA.unk_C * 32 + INTRO_DATA.unk_E * 0x400);
        width = TextGetCharacterWidth(*INTRO_DATA.pText);
        TextDrawCharacter(*INTRO_DATA.pText, dst, width, INTRO_DATA.unk_212, 0);

        if (*INTRO_DATA.pText != 0x40)
            PlayCharacterAppearingSound(*INTRO_DATA.pText, 1);

        if (INTRO_DATA.unk_C < 32)
        {
            INTRO_DATA.unk_212 += width;

            while (INTRO_DATA.unk_212 >= 8)
            {
                INTRO_DATA.unk_212 -= 8;
                INTRO_DATA.unk_C++;

                if (INTRO_DATA.unk_C >= 32)
                    break;
            }
        }

        INTRO_DATA.pText++;
    }

    return finished;
}
