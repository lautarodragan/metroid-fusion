#include "cutscenes/cutscene_common.h"

#include "gba.h"
#include "globals.h"
#include "init_helpers.h"
#include "macros.h"
#include "oam.h"
#include "text.h"

#include "data/cutscenes_data.h"
#include "data/haze_data.h"

#include "structs/cutscene_data.h"

/**
 * @brief 9c938 | c0 | Processes the cursor of a monologue cutscene
 *
 * @param pOam Cutscene monologue OAM data pointer
 */
void CutsceneMonologueProcessCursor(struct CutsceneMonologueOam* pOam)
{
    if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFF00)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
    else if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFE00)
    {
        pOam->xPosition = CUTSCENE_MONOLOGUE_DATA.currentColumn * 8 + (CUTSCENE_MONOLOGUE_DATA.indent + 12);
        pOam->yPosition = CUTSCENE_MONOLOGUE_DATA.currentLine * 8 + 12;
    }
    else if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFD00)
    {
        pOam->pOam = sCutsceneMonologueCursorHiddenOam;
        pOam->xPosition = 290;
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->stage = 0;
    }
    else if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFC00)
    {
        if (pOam->stage == 0)
        {
            if (gChangedInput & KEY_A)
            {
                pOam->xPosition = 290;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
            }
            else
            {
                pOam->pOam = sCutsceneMonologueCursorNextPageOam;
                pOam->xPosition = 118;
                pOam->yPosition = CUTSCENE_MONOLOGUE_DATA.currentLine * 8 + 24;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 1;
            }
        }
        else if (pOam->stage == 1)
        {
            if (gChangedInput & KEY_A)
            {
                pOam->pOam = sCutsceneMonologueCursorHiddenOam;
                pOam->xPosition = 290;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 0;
            }
        }
    }
    else
    {
        pOam->xPosition = CUTSCENE_MONOLOGUE_DATA.currentColumn * 8 + (CUTSCENE_MONOLOGUE_DATA.indent + 12);
        pOam->yPosition = CUTSCENE_MONOLOGUE_DATA.currentLine * 8 + 12;
    }
}

/**
 * @brief 9c9f8 | a4 | Processes the special characters of the text of a monologue cutscene
 *
 * @return boolu32 Ended
 */
boolu32 CutsceneMonologueProcessSpecialTextCharacters(void)
{
    boolu32 ended;

    ended = FALSE;

    if (gButtonInput & KEY_A)
        CUTSCENE_MONOLOGUE_DATA.timer += 2;
    else
        CUTSCENE_MONOLOGUE_DATA.timer++;

    if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFF00)
    {
        CUTSCENE_MONOLOGUE_DATA.timer = 0;
        CUTSCENE_MONOLOGUE_DATA.textUpdateState = 100;
        ended = TRUE;
    }
    else if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFC00)
    {
        if (gChangedInput & KEY_A)
        {
            CUTSCENE_MONOLOGUE_DATA.textUpdateState = 1;
            CUTSCENE_MONOLOGUE_DATA.timer = 0;
        }
        else
        {
            CUTSCENE_MONOLOGUE_DATA.timer = 0;
        }
    }
    else if ((*CUTSCENE_MONOLOGUE_DATA.pText & 0xFF00) == 0xE100)
    {
        if ((*CUTSCENE_MONOLOGUE_DATA.pText & 0xFF) <= CUTSCENE_MONOLOGUE_DATA.timer)
        {
            CUTSCENE_MONOLOGUE_DATA.textUpdateState = 1;
            CUTSCENE_MONOLOGUE_DATA.timer = 0;
        }
    }
    else if (CUTSCENE_MONOLOGUE_DATA.timer > 2)
    {
        CUTSCENE_MONOLOGUE_DATA.textUpdateState = 1;
        CUTSCENE_MONOLOGUE_DATA.timer = 0;
    }

    return ended;
}

/**
 * @brief 9ca9c | 1b0 | Processes (draws) the text of a monologue cutscene
 *
 */
void CutsceneMonologueProcessText(void)
{
    u16 i;
    u32* dst;
    u32 width;

    if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFF00)
    {
        return;
    }
    else if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFE00)
    {
        for (i = CUTSCENE_MONOLOGUE_DATA.currentColumn + 1; i < CUTSCENE_MONOLOGUE_LINE_LENGTH; i++)
            CUTSCENE_MONOLOGUE_DATA.tilesFadeStage[CUTSCENE_MONOLOGUE_DATA.currentLine / 2][i] |= 0xFF;

        CUTSCENE_MONOLOGUE_DATA.currentColumn = 0;
        CUTSCENE_MONOLOGUE_DATA.currentLine += 2;
        CUTSCENE_MONOLOGUE_DATA.pText++;
        CUTSCENE_MONOLOGUE_DATA.indent = 0;
    }
    else if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFD00)
    {
        DMA3_FILL_32(0, VRAM_BASE + 0x8000, 0x4800);

        CUTSCENE_MONOLOGUE_DATA.fadeLine = 0;
        CUTSCENE_MONOLOGUE_DATA.fadeColumn = 0;
        CUTSCENE_MONOLOGUE_DATA.currentLine = 0;
        CUTSCENE_MONOLOGUE_DATA.currentColumn = 0;
        CUTSCENE_MONOLOGUE_DATA.pText++;
        CUTSCENE_MONOLOGUE_DATA.indent = 0;

        DMA3_FILL_32(0, CUTSCENE_MONOLOGUE_DATA.tilesFadeStage, sizeof(CUTSCENE_MONOLOGUE_DATA.tilesFadeStage));
        DMA3_FILL_32(0, CUTSCENE_MONOLOGUE_DATA.tilesFadeTimer, sizeof(CUTSCENE_MONOLOGUE_DATA.tilesFadeTimer));
        DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xC800, 0x200);
    }
    else if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFC00 || (*CUTSCENE_MONOLOGUE_DATA.pText & 0xFF00) == 0xE100)
    {
        CUTSCENE_MONOLOGUE_DATA.pText++;
    }
    else
    {
        dst = VRAM_BASE + 0x8000 + (CUTSCENE_MONOLOGUE_DATA.currentColumn * 32 + CUTSCENE_MONOLOGUE_DATA.currentLine * 0x400);
        width = TextGetCharacterWidth(*CUTSCENE_MONOLOGUE_DATA.pText);
        TextDrawCharacter(*CUTSCENE_MONOLOGUE_DATA.pText, dst, width, CUTSCENE_MONOLOGUE_DATA.indent, 0);

        if (CUTSCENE_MONOLOGUE_DATA.currentColumn < CUTSCENE_MONOLOGUE_LINE_LENGTH)
        {
            CUTSCENE_MONOLOGUE_DATA.tilesFadeStage[CUTSCENE_MONOLOGUE_DATA.currentLine / 2][CUTSCENE_MONOLOGUE_DATA.currentColumn] = 4;
            CUTSCENE_MONOLOGUE_DATA.indent += width;

            while (CUTSCENE_MONOLOGUE_DATA.indent >= 8)
            {
                CUTSCENE_MONOLOGUE_DATA.indent -= 8;
                CUTSCENE_MONOLOGUE_DATA.currentColumn++;
                if (CUTSCENE_MONOLOGUE_DATA.currentColumn >= CUTSCENE_MONOLOGUE_LINE_LENGTH)
                    break;

                if (CUTSCENE_MONOLOGUE_DATA.indent != 0)
                    CUTSCENE_MONOLOGUE_DATA.tilesFadeStage[CUTSCENE_MONOLOGUE_DATA.currentLine / 2][CUTSCENE_MONOLOGUE_DATA.currentColumn] = 4;
            }
        }

        CUTSCENE_MONOLOGUE_DATA.pText++;
    }
}

/**
 * @brief 9cc4c | 134 | Updates the fading in of the text tiles of a monologue cutscene
 *
 */
void CutsceneMonologueUpdateTextTilesFade(void)
{
    u16 line;
    u16 column;
    u16 end;
    u16* pTile1;
    u16* pTile2;
    u16 tile1;
    u16 tile2;
    u16 palette1;
    u16 palette2;

    column = CUTSCENE_MONOLOGUE_DATA.fadeColumn;

    line = CUTSCENE_MONOLOGUE_DATA.fadeLine / 2;
    while (line <= CUTSCENE_MONOLOGUE_DATA.currentLine / 2)
    {
        if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFC00)
        {
            if (CUTSCENE_MONOLOGUE_DATA.currentColumn < CUTSCENE_MONOLOGUE_LINE_LENGTH)
                end = CUTSCENE_MONOLOGUE_DATA.currentColumn + 1;
            else
                end = CUTSCENE_MONOLOGUE_LINE_LENGTH;
        }
        else if (line == CUTSCENE_MONOLOGUE_DATA.currentLine / 2)
        {
            if (CUTSCENE_MONOLOGUE_DATA.currentColumn < CUTSCENE_MONOLOGUE_LINE_LENGTH)
                end = CUTSCENE_MONOLOGUE_DATA.currentColumn;
            else
                end = CUTSCENE_MONOLOGUE_LINE_LENGTH;
        }
        else
        {
            end = CUTSCENE_MONOLOGUE_LINE_LENGTH;
        }

        for (; column < end; column++)
        {
            if (CUTSCENE_MONOLOGUE_DATA.tilesFadeTimer[line][column] == 5)
            {
                CUTSCENE_MONOLOGUE_DATA.tilesFadeTimer[line][column] = 0;
                CUTSCENE_MONOLOGUE_DATA.tilesFadeStage[line][column]--;

                if ((s8)CUTSCENE_MONOLOGUE_DATA.tilesFadeStage[line][column] > 0)
                {
                    pTile1 = VRAM_BASE + 0xC842 + (column * 2 + line * 128);
                    pTile2 = VRAM_BASE + 0xC882 + (column * 2 + line * 128);

                    tile1 = *pTile1;
                    tile2 = *pTile2;
                    palette1 = tile1 >> 12;
                    palette2 = tile2 >> 12;
                    palette1--;
                    palette2--;

                    *pTile1 = palette1 << 12 | (tile1 & 0xFFF);
                    *pTile2 = palette2 << 12 | (tile2 & 0xFFF);
                }
                else if ((s8)CUTSCENE_MONOLOGUE_DATA.tilesFadeStage[line][column] == 0)
                {
                    CUTSCENE_MONOLOGUE_DATA.fadeLine = line * 2;
                    CUTSCENE_MONOLOGUE_DATA.fadeColumn = column;
                }
                else
                {
                    CUTSCENE_MONOLOGUE_DATA.tilesFadeStage[line][column] |= UCHAR_MAX;
                    break;
                }
            }
            else
            {
                CUTSCENE_MONOLOGUE_DATA.tilesFadeTimer[line][column]++;
            }
        }

        column = 0;
        line++;
    }
}

