#include "globals.h"
#include "ending_dialogue.h"
#include "special_cutscene.h"
#include "music_wrappers.h"

#include "constants/audio.h"

#include "structs/intro.h"

/**
 * @brief 96b98 | 1a8 | Processes the Adam panel in the ending dialogue
 *
 * @param pOam Special cutscene OAM pointer
 */
void EndingProcessAdamPanel(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;

        if (pOam->yPosition > 128)
        {
            pOam->yPosition -= 8;
            return;
        }

        pOam->yPosition = 128;

        if (pOam->type == 7)
            SoundPlay(SOUND_20A);

        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter)
        {
            if (frame[1].timer == 0)
            {
                pOam->animationDurationCounter = 0;
                pOam->stage = 2;
            }

            if (pOam->type != 7)
                return;

            if (pOam->currentAnimationFrame == 10)
                EndingDialogueSetupOam(8, pOam->xPosition, pOam->yPosition, FALSE);
        }

        if (pOam->type == 7)
        {
            if (pOam->currentAnimationFrame == 11)
            {
                if (pOam->animationDurationCounter == 15)
                {
                    INTRO_DATA.indent = 0;
                    INTRO_DATA.currentLine = 0;
                    INTRO_DATA.currentColumn = 0;
                    INTRO_DATA.pText = sEndingDialogueTextTables[gLanguage][112];
                }
            }
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->animationDurationCounter = 0;
        pOam->timer++;
        if (pOam->timer == 1)
        {
            pOam->timer = 0;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        pOam->animationDurationCounter = 0;

        if (INTRO_DATA.subStage == 11)
        {
            pOam->currentAnimationFrame = 0;

            if (pOam->type == 7)
            {
                pOam->pOam = sEndingAdamPanel0Oam_Closing;
                SoundPlay(SOUND_20B);
            }
            else if (pOam->type == 9)
            {
                pOam->pOam = sEndingAdamPanel1Oam_Closing;
            }

            pOam->stage = 4;
        }
    }
    else if (pOam->stage == 4)
    {
        if (pOam->currentAnimationFrame == 11 && pOam->animationDurationCounter == 3)
        {
            if (pOam->type == 7)
                SpecialCutsceneDestroyOamOfType(8);

            pOam->animationDurationCounter = 0;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        pOam->animationDurationCounter = 0;

        if (pOam->yPosition < 192)
        {
            pOam->yPosition += 8;
        }
        else
        {
            if (pOam->type == 7)
                INTRO_DATA.subStage = 12;

            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

/**
 * @brief 96d40 | 88 | Processes the Adam icon in the ending dialogue
 *
 * @param pOam Special cutscene OAM pointer
 */
void EndingProcessAdamIcon(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    frame = &pOam->pOam[pOam->currentAnimationFrame];

    if (pOam->stage == 0)
    {
        if (pOam->currentAnimationFrame == 3)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingAdamIconOam_Idle;
            pOam->stage = 1;
        }

        if (INTRO_DATA.subStage == 11)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingAdamIconOam_Closing;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 1)
    {
        if (INTRO_DATA.subStage == 11)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingAdamIconOam_Closing;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief 96dc8 | 138 | Processes the animals scrolling in the ending
 *
 * @param pOam Special cutscene OAM pointer
 */
void EndingProcessAnimalsScrolling(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;

    if (pOam->stage == 0)
    {
        pOam->xPosition = gBg2XPosition;
        pOam->yPosition = gBg2YPosition;
        pOam->spawnX = gBg3XPosition;
        pOam->spawnY = gBg3YPosition;

        if (pOam->yPosition < -32)
        {
            pOam->unk_A = 0x4000;
            DMA3_FILL_32(0, VRAM_BASE + 0x8000 + pOam->unk_A, 0x1000);
        }
        else
        {
            pOam->unk_A = 0x5000;
        }

        pOam->timer = 0;
        pOam->stage = 2;
    }
    else if (pOam->stage == 1)
    {
        if (pOam->timer == 10)
        {
            pOam->timer = 0;
            pOam->stage = 2;
        }
    }
    else if (INTRO_DATA.subStage == 14)
    {
        if (pOam->timer == 2)
        {
            pOam->timer = 0;

            if (pOam->yPosition > -160)
            {
                pOam->yPosition--;
                pOam->unk_8++;
            }

            if (pOam->spawnY > 0)
                pOam->spawnY--;

            gBg2YPosition = pOam->yPosition;
            gBg3YPosition = pOam->spawnY;
        }

        if (pOam->unk_8 == 9)
        {
            pOam->unk_8 = 0;

            if (pOam->unk_A != 0)
            {
                pOam->unk_A -= 0x400;
                DMA3_FILL_32(0, VRAM_BASE + 0x8000 + pOam->unk_A, 0x400);
            }
        }
    }
    else
    {
        pOam->timer = 0;
    }
}

/**
 * @brief 96f00 | 8 | Kills a special cutscene OAM
 *
 * @param pOam Special cutscene OAM pointer
 */
void EndingDestroyOam(struct SpecialCutsceneOam* pOam)
{
    pOam->type = 0;
}

/**
 * @brief 96f08 | 380 | Spawns an OAM for the ending dialogue
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param descendingSearch Search for a free slot starting from the end
 * @return u8 Slot
 */
u8 EndingDialogueSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearch)
{
    s8 slot;

    if (!descendingSearch)
    {
        for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot >= ARRAY_SIZE(INTRO_DATA.oam))
            return ARRAY_SIZE(INTRO_DATA.oam);
    }
    else
    {
        for (slot = ARRAY_SIZE(INTRO_DATA.oam) - 1; slot >= 0; slot--)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot < 0)
            return ARRAY_SIZE(INTRO_DATA.oam);
    }

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].exists = 1;

    if (type == 1)
    {
        INTRO_DATA.oam[slot].pOam = sEndingNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessMonologueCursor;
    }
    else if (type == 2)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sEndingDialogueType2Oam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessHoldLastAnimFrame;
    }
    else if (type == 3)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sEndingSr388RadarViewOam_Opening;
        INTRO_DATA.oam[slot].pFunction = EndingProcessSr388RadarView;
    }
    else if (type == 4)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sEndingSamusViewRadarViewOam_Opening;
        INTRO_DATA.oam[slot].pFunction = EndingProcessSamusViewRadarView;
    }
    else if (type == 5)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sEndingDialogueType5Oam_Opening;
        INTRO_DATA.oam[slot].pFunction = EndingProcessDialogueType5;
    }
    else if (type == 6)
    {
        INTRO_DATA.oam[slot].pOam = sEndingTextCursorOam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessAdamTextCursor;
    }
    else if (type == 7)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sEndingAdamPanel0Oam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessAdamPanel;
    }
    else if (type == 8)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sEndingAdamIconOam_Opening;
        INTRO_DATA.oam[slot].pFunction = EndingProcessAdamIcon;
    }
    else if (type == 9)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sEndingAdamPanel1Oam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessAdamPanel;
    }
    else if (type == 20)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = EndingProcessAnimalsScrolling;
    }
    else if (type == 30)
    {
        SoundPlay(SOUND_12D);
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sEndingDialogueType30Oam;
        INTRO_DATA.oam[slot].pFunction = EndingDialogueOam_Empty;
    }
    else if (type == UCHAR_MAX)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pOam = sEndingDialogueType5Oam_Opening;
        INTRO_DATA.oam[slot].pFunction = EndingDestroyOam;
    }

    return slot;
}

/**
 * @brief 97288 | 9c | V-blank for the ending monologue
 *
 */
void EndingMonologueVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);

    SpecialCutsceneUpdateTextTilesFade();
}

/**
 * @brief 97324 | 94 | V-blank for the ending conversation and animals
 *
 */
void EndingConversationAndAnimalsVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

/**
 * @brief 973b8 | 60 | Returns slot, X and Y position of an ending OAM
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 * @return u8 Slot
 */
u8 EndingGetPositionAndSlotOfOamByType_2(u8 type, s16* pXPosition, s16* pYPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == type)
        {
            *pXPosition = INTRO_DATA.oam[slot].xPosition;
            *pYPosition = INTRO_DATA.oam[slot].yPosition;

            return slot;
        }
    }

    // Default values if not found
    *pXPosition = 300;
    *pYPosition = 200;

    return ARRAY_SIZE(INTRO_DATA.oam);
}

/**
 * @brief 97418 | 4 | Empty function
 *
 * @param pOam Special cutscene OAM pointer
 */
void EndingDialogueOam_Empty(struct SpecialCutsceneOam* pOam)
{
    return;
}
