#include "globals.h"
#include "special_cutscene.h"
#include "text.h"
#include "init_helpers.h"
#include "oam.h"

#include "constants/text.h"

#include "data/haze_data.h"

#include "structs/intro.h"

// Declared without a prototype, the character argument isn't truncated
void PlayCharacterAppearingSound();

/**
 * @brief 98158 | 134 | Fades in the monologue text tiles that are still appearing
 *
 */
void unk_98158(void)
{
    u16 col;
    u16 end;
    u16* pTop;
    u16* pBottom;
    u16 top;
    u16 bottom;
    u16 palTop;
    u16 palBottom;
    // Declared last: the pseudo register numbering affects which spill slots gcse's temporaries get
    u16 row;

    col = INTRO_DATA.unk_10;

    row = INTRO_DATA.unk_12 / 2;
    while (row <= INTRO_DATA.unk_E / 2)
    {
        if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
        {
            if (INTRO_DATA.unk_C < MONOLOGUE_LINE_LENGTH)
                end = INTRO_DATA.unk_C + 1;
            else
                end = MONOLOGUE_LINE_LENGTH;
        }
        else if (row == INTRO_DATA.unk_E / 2)
        {
            if (INTRO_DATA.unk_C < MONOLOGUE_LINE_LENGTH)
                end = INTRO_DATA.unk_C;
            else
                end = MONOLOGUE_LINE_LENGTH;
        }
        else
        {
            end = MONOLOGUE_LINE_LENGTH;
        }

        for (; col < end; col++)
        {
            if (INTRO_DATA_ARRAYS.unk_110[col + row * MONOLOGUE_LINE_LENGTH] == 5)
            {
                INTRO_DATA_ARRAYS.unk_110[col + row * MONOLOGUE_LINE_LENGTH] = 0;
                INTRO_TEXT_TILE_DELAY[col + row * MONOLOGUE_LINE_LENGTH]--;

                if ((s8)INTRO_TEXT_TILE_DELAY[col + row * MONOLOGUE_LINE_LENGTH] > 0)
                {
                    pTop = VRAM_BASE + 0x4842 + (col * 2 + row * 128);
                    pBottom = VRAM_BASE + 0x4882 + (col * 2 + row * 128);

                    top = *pTop;
                    bottom = *pBottom;
                    palTop = top >> 12;
                    palBottom = bottom >> 12;
                    palTop--;
                    palBottom--;

                    *pTop = palTop << 12 | (top & 0xFFF);
                    *pBottom = palBottom << 12 | (bottom & 0xFFF);
                }
                else if ((s8)INTRO_TEXT_TILE_DELAY[col + row * MONOLOGUE_LINE_LENGTH] == 0)
                {
                    INTRO_DATA.unk_10 = col;
                    INTRO_DATA.unk_12 = row * 2;
                }
                else
                {
                    INTRO_TEXT_TILE_DELAY[col + row * MONOLOGUE_LINE_LENGTH] |= UCHAR_MAX;
                    break;
                }
            }
            else
            {
                INTRO_DATA_ARRAYS.unk_110[col + row * MONOLOGUE_LINE_LENGTH]++;
            }
        }

        col = 0;
        row++;
    }
}

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

/**
 * @brief 98940 | 40 | Transfers rows of graphics (unused)
 * 
 * @param src Source
 * @param dst Destination
 * @param size Size of a row (in tiles)
 * @param nbrRows Number of rows
 */
void Dma3Transfer_Unused1(const u8* src, u8* dst, u32 size, u16 nbrRows)
{
    u16 i;
    u16 rowSize;

    rowSize = size * 32;
    for (i = 0; i < nbrRows; i++)
    {
        DMA3_COPY_32(src, dst, rowSize / sizeof(u32));
        src += 0x400;
        dst += 0x400;
    }
}

/**
 * @brief 98980 | 3c | Transfers rows of a tilemap (unused)
 * 
 * @param src Source
 * @param dst Destination
 * @param size Size of a row (in tiles)
 * @param nbrRows Number of rows
 */
void Dma3Transfer_Unused2(const u8* src, u8* dst, u32 size, u16 nbrRows)
{
    u16 i;
    u16 rowSize;

    rowSize = size * 2;
    for (i = 0; i < nbrRows; i++)
    {
        DMA3_COPY_16(src, dst, rowSize / sizeof(u16));
        src += 0x40;
        dst += 0x40;
    }
}

/**
 * @brief 989bc | 48 | Clears rows of graphics (unused)
 * 
 * @param dst Destination
 * @param size Size of a row (in tiles)
 * @param nbrRows Number of rows
 */
void Dma3Clear_Unused(u8* dst, u32 size, u16 nbrRows)
{
    u16 i;
    u16 rowSize;

    rowSize = size * 32;
    for (i = 0; i < nbrRows; i++)
    {
        DMA3_FILL_32(0, dst, rowSize);
        dst += 0x400;
    }
}

/**
 * @brief 98a04 | 9c | Updates palette animation timers
 * 
 */
void unk_98a04(void)
{
    u8 i;

    for (i = 0; i < 4; i++)
    {
        if (INTRO_DATA_ARRAYS.unk_110[i] <= INTRO_DATA_ARRAYS.unk_12C[i])
        {
            INTRO_DATA_ARRAYS.unk_12C[i] = 0;
            INTRO_DATA_ARRAYS.unk_164[i] = 1;

            if (INTRO_DATA_ARRAYS.unk_148[i] < 38)
                INTRO_DATA_ARRAYS.unk_148[i]++;
            else
                INTRO_DATA_ARRAYS.unk_148[i] = 0;
        }
        else
        {
            INTRO_DATA_ARRAYS.unk_12C[i]++;
        }
    }

    if (INTRO_DATA_ARRAYS.unk_110[10] <= INTRO_DATA_ARRAYS.unk_12C[10])
    {
        INTRO_DATA_ARRAYS.unk_12C[10] = 0;
        INTRO_DATA_ARRAYS.unk_164[10] = 1;

        if (INTRO_DATA_ARRAYS.unk_148[10] < 15)
            INTRO_DATA_ARRAYS.unk_148[10]++;
        else
            INTRO_DATA_ARRAYS.unk_148[10] = 0;
    }
    else
    {
        INTRO_DATA_ARRAYS.unk_12C[10]++;
    }
}

/**
 * @brief 98aa0 | 12c | Sets up the window in the Samus getting cured cutscene
 * 
 */
void NewFileIntroSamusGettingCuredSetupWindow(void)
{
    const s16* src;
    u16* dst;
    s16 i;
    s16 top;
    s16 bottom;
    u16 subSlice;
    s16 left;
    s16 right;

    DMA3_COPY_32(EWRAM_BASE + 0x1000, EWRAM_BASE + 0x2000, 0x160 / sizeof(u32));

    top = INTRO_DATA.unk_1F5 - INTRO_DATA.unk_1F3;
    bottom = INTRO_DATA.unk_1F5 + INTRO_DATA.unk_1F3;

    if (top < 0)
    {
        subSlice = -top;
        if (subSlice > INTRO_DATA.unk_1F3 * 2)
            top = SCREEN_SIZE_Y + 1;
        else
            top = 0;
    }
    else
    {
        subSlice = 0;
    }

    if (bottom >= SCREEN_SIZE_Y)
        bottom = SCREEN_SIZE_Y;

    src = sHaze_PowerBomb_WindowValuesPointers[INTRO_DATA.unk_1F3];
    dst = EWRAM_BASE + 0x1000;

    for (i = 0; i < top; i++)
        *dst++ = 0;

    for (; i <= bottom; subSlice++, i++)
    {
        left = INTRO_DATA.unk_1F4 + src[subSlice * 2 + 1];
        right = INTRO_DATA.unk_1F4 + src[subSlice * 2 + 0];

        if (left < 0)
            left = 0;

        if (right > SCREEN_SIZE_X)
            right = SCREEN_SIZE_X;

        *dst++ = C_16_2_8(left, right);
    }

    for (; i < SCREEN_SIZE_Y; i++)
        *dst++ = 0;
}

/**
 * @brief 98bcc | 20 | Fades in a special cutscene
 * 
 */
void SpecialCutsceneFadeIn(void)
{
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    if (gWrittenToBldy != 0)
        gWrittenToBldy--;
}

/**
 * @brief 98bec | 20 | Fades out a special cutscene
 * 
 */
void SpecialCutsceneFadOut(void)
{
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    if (gWrittenToBldy < BLDY_MAX_VALUE)
        gWrittenToBldy++;
}

/**
 * @brief 98c0c | 2c | Processes the text cursor in the new file intro
 * 
 * @param pOam Special cutscene OAM pointer
 */
void NewFileIntroProcessTextCursor(struct SpecialCutsceneOam* pOam)
{
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        pOam->xPosition = 235;
        pOam->yPosition = 152;
    }
    else
    {
        pOam->xPosition = 260;
    }
}

/**
 * @brief 98c38 | 34 | Disables the drawing of every special cutscene OAM
 * 
 */
void SpecialCutsceneClearOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(INTRO_DATA.oam); i++)
        INTRO_DATA.oam[i].unk_18_0 = 0;
}

/**
 * @brief 98c6c | 3c | Enables the drawing of every active special cutscene OAM
 * 
 */
void SpecialCutsceneEnableOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(INTRO_DATA.oam); i++)
    {
        if (INTRO_DATA.oam[i].type != 0)
            INTRO_DATA.oam[i].unk_18_0 = 1;
    }
}

/**
 * @brief 98ca8 | 4c | Destroys the first special cutscene OAM of a type
 * 
 * @param type Type
 */
void SpecialCutsceneDestroyOamOfType(u8 type)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(INTRO_DATA.oam); i++)
    {
        if (INTRO_DATA.oam[i].type == type)
        {
            INTRO_DATA.oam[i].type = 0;
            INTRO_DATA.oam[i].unk_18_0 = 0;
            break;
        }
    }
}

/**
 * @brief 98cf4 | 58 | Processes every special cutscene OAM
 * 
 */
void SpecialCutsceneProcessOam(void)
{
    u8 i;

    INTRO_DATA.unk_215 = 0;

    for (i = 0; i < ARRAY_SIZE(INTRO_DATA.oam); i++)
    {
        if (INTRO_DATA.oam[i].type != 0)
        {
            ((SpecialCutsceneOamFunc_T)INTRO_DATA.oam[i].pFunction)(&INTRO_DATA.oam[i]);
            INTRO_DATA.unk_215++;
        }
    }
}

/**
 * @brief 98d4c | 54 | Draws every special cutscene OAM
 * 
 */
void SpecialCutsceneDrawAllOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(INTRO_DATA.oam); i++)
    {
        if (INTRO_DATA.oam[i].unk_18_0)
            SpecialCutsceneDrawOam(&INTRO_DATA.oam[i]);
    }

    ResetFreeOam();
    gNextOamSlot = 0;
    gUnk_3001238 = 0;
}
