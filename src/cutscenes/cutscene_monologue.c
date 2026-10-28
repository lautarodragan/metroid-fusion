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
        pOam->pOam = (const struct FrameData*)sCutsceneUnk_663e5c;
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
                pOam->pOam = (const struct FrameData*)sCutsceneUnk_663e74;
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
                pOam->pOam = (const struct FrameData*)sCutsceneUnk_663e5c;
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
        CUTSCENE_MONOLOGUE_DATA.unk_17 = 100;
        ended = TRUE;
    }
    else if (*CUTSCENE_MONOLOGUE_DATA.pText == 0xFC00)
    {
        if (gChangedInput & KEY_A)
        {
            CUTSCENE_MONOLOGUE_DATA.unk_17 = 1;
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
            CUTSCENE_MONOLOGUE_DATA.unk_17 = 1;
            CUTSCENE_MONOLOGUE_DATA.timer = 0;
        }
    }
    else if (CUTSCENE_MONOLOGUE_DATA.timer > 2)
    {
        CUTSCENE_MONOLOGUE_DATA.unk_17 = 1;
        CUTSCENE_MONOLOGUE_DATA.timer = 0;
    }

    return ended;
}

