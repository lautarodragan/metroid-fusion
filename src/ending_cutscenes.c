#include "globals.h"
#include "music_wrappers.h"
#include "audio_wrappers.h"
#include "callbacks.h"
#include "syscalls.h"

#include "constants/game_state.h"
#include "constants/audio.h"
#include "constants/text.h"

#include "structs/cutscene.h"

#include "data/new_file_intro_data.h"
#include "data/cutscene_unk_data.h"
#include "data/generic_data.h"
#include "data/sprite_data.h"
#include "data/audio.h"

void SpecialCutsceneLoadingVblank(void); // For V-blank callback
void Sram_ProcessEndingSave(u8 stage);

boolu32 EndingBslCrashing(void);
boolu32 EndingInShip(void);
u8 EndingBslCrashingSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearch);
void EndingBslCrashingVblank(void);
void EndingShipFrontViewVblank(void);
u8 EndingGetPositionAndSlotOfOamByType(u8 type, s16* pXPosition, s16* pYPosition);
void EndingOam_Empty(struct SpecialCutsceneOam* pOam);
u8 EndingDialogueSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearch);
void EndingMonologueVblank(void);
void EndingConversationAndAnimalsVblank(void);
boolu32 EndingCheckMonologueEnded(void);
void EndingProcessAdamText(void);

 /**
 * @brief 94e84 | f0 | Main handler for the ending cutscenes
 *
 * @return boolu32 bool, ended
 */
boolu32 EndingHandler(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (gSubGameMode1)
    {
        case 0:
            DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
            gSubGameMode1 = 1;
            break;

        case 1:
            if (EndingBslCrashing())
                gSubGameMode1 = 2;
            break;

        case 2:
            if (EndingInShip())
            {
                INTRO_DATA.handlerTimer = 0;
                gSubGameMode1 = 3;
            }
            break;

        case 3:
            INTRO_DATA.handlerTimer++;

            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (INTRO_DATA.handlerTimer == 1)
                {
                    INTRO_DATA.handlerTimer = 0;
                    gWrittenToBldy++;
                }
            }
            else if (INTRO_DATA.handlerTimer == 1)
            {
                Sram_ProcessEndingSave(0);
            }
            else if (INTRO_DATA.handlerTimer == 2)
            {
                Sram_ProcessEndingSave(1);
            }
            else if (INTRO_DATA.handlerTimer == 3)
            {
                Sram_ProcessEndingSave(2);
            }
            else if (INTRO_DATA.handlerTimer == 4)
            {
                Sram_ProcessEndingSave(3);
                INTRO_DATA.handlerTimer = 0;
                finished = TRUE;
            }

            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 94f74 | 204 | Setup for the ending BSL crashing cutscene
 *
 */
void EndingBslCrashingInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sBslCrashingObjGfx, VRAM_OBJ);
    DMA3_COPY_32(sBslCrashingObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sBslCrashingBgGfx, VRAM_BASE);
    LZ77UncompVram(sBslCrashingBg1Tilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sBslCrashingBg3Tilemap, VRAM_BASE + 0xF800);

    DMA3_COPY_32(sBslCrashingBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    gBg1XPosition = 0;
    gBg1YPosition = 8;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 8);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 30, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gWrittenToBldalpha_Eva = 8;
    gWrittenToBldalpha_Evb = 14;

    EndingBslCrashingSetupOam(5, -40, 200, FALSE);
    EndingBslCrashingSetupOam(4, 128, 72, TRUE);
    EndingBslCrashingSetupOam(2, 164, 40, TRUE);
    EndingBslCrashingSetupOam(1, 164, 40, TRUE);
    EndingBslCrashingSetupOam(3, 134, 60, TRUE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(EndingBslCrashingVblank);
}

 /**
 * @brief 95178 | 200 | Setup for the ending ship front view cutscene
 *
 */
void EndingShipFrontViewInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
    DMA3_FILL_16(0, &INTRO_DATA.tilesFadeStage, sizeof(INTRO_DATA.tilesFadeStage));
    DMA3_FILL_16(0, &INTRO_DATA.paletteUpdate1, sizeof(INTRO_DATA.tilesFadeStage));

    LZ77UncompVram(sEndingShipFrontViewBgGfx, VRAM_BASE);
    LZ77UncompVram(sEndingShipFrontViewBg2Tilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sEndingShipFrontViewBg3Tilemap, VRAM_BASE + 0xF800);

    DMA3_COPY_32(sEndingShipFrontViewBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg2YPosition = -30;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
    gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    EndingBslCrashingSetupOam(12, 0, gBg2YPosition, FALSE);
    EndingBslCrashingSetupOam(10, 120, 106, TRUE);
    EndingBslCrashingSetupOam(11, 120, 64, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(EndingShipFrontViewVblank);
}

 /**
 * @brief 95378 | 2c4 | Processes the ending BSL crashing cutscene
 *
 * @return boolu32 bool, ended
 */
boolu32 EndingBslCrashingProcess(void)
{
    boolu32 finished;

    finished = FALSE;

    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (gWrittenToBldy != 0)
            {
                if (gWrittenToBldy == BLDY_MAX_VALUE)
                    SoundPlayOnUnusedMusicTrack(SOUND_24B);

                gWrittenToBldy--;
            }
            else
            {
                WRITE_16(REG_BLDCNT, BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            INTRO_DATA.timer = 0;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == 1)
            {
                gWrittenToBldalpha_Eva = 10;
                gWrittenToBldalpha_Evb = 10;
                INTRO_DATA.paletteUpdate1 = 1;
                INTRO_DATA.paletteFrame1 = 0;
            }
            else if (INTRO_DATA.timer == 2)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG3_SECOND_TARGET_PIXEL);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 3;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 3:
            if (INTRO_DATA.paletteFrame1 < 15)
            {
                if (INTRO_DATA.timer == 4)
                {
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.paletteUpdate1 = 1;
                    INTRO_DATA.paletteFrame1++;
                }
            }
            else if (INTRO_DATA.timer == 20)
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = BLDY_MAX_VALUE;
                INTRO_DATA.subStage = 4;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 4:
            if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
            {
                if (INTRO_DATA.timer == 6)
                {
                    INTRO_DATA.timer = 0;
                    gWrittenToBldalpha_Eva++;
                    gWrittenToBldalpha_Evb++;
                }
            }
            else
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 5;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 5:
            if (INTRO_DATA.timer == 10)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 6;
                EndingShipFrontViewInit();
            }
            break;

        case 6:
            WRITE_16(REG_BLDCNT, BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL);
            INTRO_DATA.timer = 0;
            INTRO_DATA.subStage = 7;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 7:
            if (INTRO_DATA.timer == CONVERT_SECONDS(2.8f))
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = 2;
                INTRO_DATA.subStage = 8;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 8:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Eva != 0)
                {
                    gWrittenToBldalpha_Eva--;
                    if (gWrittenToBldalpha_Eva == 0)
                        SpecialCutsceneDestroyOamOfType(10);
                }
                else
                {
                    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                    INTRO_DATA.subStage = 9;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 9:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (INTRO_DATA.timer == 4)
                {
                    gWrittenToBldy++;
                    INTRO_DATA.timer = 0;
                }
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 9563c | 88 | Main handler for the ending BSL crashing cutscene
 *
 * @return boolu32 bool, ended
 */
boolu32 EndingBslCrashing(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            EndingBslCrashingInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();

            if (gWrittenToBldy == 0)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (EndingBslCrashingProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 956c4 | d8 | Handles the BSL falling
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessFallingBsl(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->unk_A = 0;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            pOam->animationDurationCounter = 0;

        pOam->xPosition = pOam->spawnX - pOam->unk_A / 5;
        pOam->yPosition = pOam->spawnY + pOam->unk_A / 5;

        if (pOam->yPosition > 80)
        {
            pOam->unk_A = 0;
            pOam->stage = 2;
        }

        if (pOam->type == 1)
            pOam->scaling -= 1;
        else
            pOam->scaling -= 2;
    }
    else if (pOam->stage == 2)
    {
        pOam->stage = 3;

        if (pOam->type == 1)
        {
            pOam->pOam = sBslCrashingFallingBslOam_End;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            INTRO_DATA.subStage = 2;
        }
        else
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
    else if (pOam->stage == 3)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 9579c | 30 | Destroys a special cutscene OAM once its animation ended
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingBslCrashingDestroyOamWhenAnimEnded(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 957cc | 64 | Handles the small ship leaving
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessLeavingSmallShip(struct SpecialCutsceneOam* pOam)
{
    s32 timer;

    timer = pOam->unk_A + 1;
    pOam->unk_A = timer;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;

        if (pOam->unk_A == CONVERT_SECONDS(2.5f))
        {
            pOam->unk_A = 0;
            pOam->exists = 1;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->xPosition = pOam->spawnX - timer * 4;
        pOam->yPosition = pOam->spawnY + pOam->unk_A / 3;

        if (pOam->xPosition < 0)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 95830 | 64 | Handles the big ship leaving
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessLeavingBigShip(struct SpecialCutsceneOam* pOam)
{
    s32 timer;

    timer = pOam->unk_A + 1;
    pOam->unk_A = timer;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;

        if (pOam->unk_A == CONVERT_SECONDS(4.f))
        {
            pOam->unk_A = 0;
            pOam->exists = 1;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->xPosition = pOam->spawnX + timer * 4;
        pOam->yPosition = pOam->spawnY - pOam->unk_A * 3;

        if (pOam->xPosition > 280)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 95894 | 34 | Handles the thrusters of the front facing ship
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessFrontFacingShipThrusters(struct SpecialCutsceneOam* pOam)
{
    s16 xPosition;
    s16 yPosition;

    if (pOam->stage == 0)
    {
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    EndingGetPositionAndSlotOfOamByType(12, &xPosition, &yPosition);
    pOam->yPosition = pOam->spawnY - yPosition;
}

 /**
 * @brief 958c8 | 90 | Handles the front facing ship
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessFrontFacingShip(struct SpecialCutsceneOam* pOam)
{
    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        pOam->spawnY = pOam->yPosition;
        pOam->unk_A = 0;
        pOam->timer = 4;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->yPosition = (SIN(pOam->timer) >> 3) + pOam->spawnY;

        if (pOam->timer == 64)
        {
            pOam->stage = 2;
            pOam->unk_A = 0;
        }
    }
    else if (pOam->stage == 2)
    {
        if (pOam->unk_A == 2)
        {
            pOam->unk_A = 0;
            pOam->timer++;
        }

        pOam->yPosition = (SIN(pOam->timer) >> 3) + pOam->spawnY;
    }

    gBg2YPosition = pOam->yPosition;
}

 /**
 * @brief 95958 | 2fc | Spawns an OAM for the ending BSL crashing cutscene
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param descendingSearch Search for a free slot in descending order
 * @return u8 Slot
 */
u8 EndingBslCrashingSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearch)
{
    s8 slot;

    if (!descendingSearch)
    {
        for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot > 19)
            return 20;
    }
    else
    {
        for (slot = ARRAY_SIZE(INTRO_DATA.oam) - 1; slot >= 0; slot--)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot < 0)
            return 20;
    }

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].exists = 1;

    if (type == 1)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_AFFINE;
        INTRO_DATA.oam[slot].pOam = sBslCrashingFallingBslOam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessFallingBsl;
    }
    else if (type == 2)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(2);
        INTRO_DATA.oam[slot].objMode = 1;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_AFFINE;
        INTRO_DATA.oam[slot].pOam = sBslCrashingFallingBslTransparentOam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessFallingBsl;
    }
    else if (type == 3)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sBslCrashingType3Oam;
        INTRO_DATA.oam[slot].pFunction = EndingBslCrashingDestroyOamWhenAnimEnded;
    }
    else if (type == 4)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sEndingLeavingSmallShipOam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessLeavingSmallShip;
    }
    else if (type == 5)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pOam = sEndingLeavingBigShipOam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessLeavingBigShip;
    }
    else if (type == 10)
    {
        INTRO_DATA.oam[slot].objMode = 1;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sEndingFrontFacingShipOam;
        INTRO_DATA.oam[slot].pFunction = EndingOam_Empty;
    }
    else if (type == 11)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sEndingFrontFacingShipThrustersOam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessFrontFacingShipThrusters;
    }
    else if (type == 12)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pOam = sEndingFrontFacingShipOam;
        INTRO_DATA.oam[slot].pFunction = EndingProcessFrontFacingShip;
    }

    return slot;
}

 /**
 * @brief 95c54 | d8 | V-blank for the ending BSL crashing cutscene
 *
 */
void EndingBslCrashingVblank(void)
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

    if (INTRO_DATA.paletteUpdate1 == 1)
    {
        INTRO_DATA.paletteUpdate1 = 0;
        DMA3_COPY_32(&sBslCrashingAnimatedBgPal[INTRO_DATA.paletteFrame1 * PAL_ROW], PALRAM_BASE + 9 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
    }
}

 /**
 * @brief 95d2c | 94 | V-blank for the ending ship front view cutscene
 *
 */
void EndingShipFrontViewVblank(void)
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
 * @brief 95dc0 | 60 | Returns slot, X and Y position of an ending OAM
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 * @return u8 Slot
 */
u8 EndingGetPositionAndSlotOfOamByType(u8 type, s16* pXPosition, s16* pYPosition)
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
 * @brief 95e20 | 4 | Empty OAM process function
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingOam_Empty(struct SpecialCutsceneOam* pOam)
{
    return;
}

 /**
 * @brief 95e24 | 200 | Setup for the ending monologue
 *
 */
void EndingMonologueInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sEndingInShipObjGfx, VRAM_OBJ);
    DMA3_COPY_32(sEndingInShipObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sEndingMonologueBgGfx, VRAM_BASE + 0x8000);
    LZ77UncompVram(sEndingMonologueBgTilemap, VRAM_BASE + 0xF800);

    DMA3_COPY_32(sEndingInShipBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompWram(sMonologueTextTilemap, EWRAM_BASE);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0x4800, 0x800 / sizeof(u32));
    DMA3_FILL_32(0, VRAM_BASE, 0x4800);

    DMA3_COPY_32(sMonologueTextPal, PALRAM_BASE + 12 * PAL_ROW_SIZE, 4 * PAL_ROW_SIZE / sizeof(u32));

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 4);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(0, 9, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 30, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(2, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gWrittenToBldalpha_Eva = 0;
    gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;

    EndingDialogueSetupOam(1, 260, 180, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    WRITE_16(REG_DISPCNT, DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(EndingMonologueVblank);
}

 /**
 * @brief 96024 | 204 | Setup for the ending Adam conversation
 *
 */
void EndingAdamConversationInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
    DMA3_FILL_16(0, &INTRO_DATA.tilesFadeStage, sizeof(INTRO_DATA.tilesFadeStage));
    DMA3_FILL_16(0, &INTRO_DATA.paletteUpdate1, sizeof(INTRO_DATA.tilesFadeStage));

    LZ77UncompVram(sEndingAdamConversationBgGfx, VRAM_BASE + 0x8000);
    LZ77UncompVram(sEndingAdamConversationBgTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sEndingInShipBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    gBg0XPosition = -8;
    gBg0YPosition = 8;
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 8);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(2, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
    gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    EndingDialogueSetupOam(2, 112, 80, TRUE);
    EndingDialogueSetupOam(3, 112, 80, TRUE);
    EndingDialogueSetupOam(4, 112, 80, TRUE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(EndingConversationAndAnimalsVblank);
}

 /**
 * @brief 96228 | 220 | Setup for the ending animals cutscene
 *
 */
void EndingAnimalsInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
    DMA3_FILL_16(0, &INTRO_DATA.tilesFadeStage, sizeof(INTRO_DATA.tilesFadeStage));
    DMA3_FILL_16(0, &INTRO_DATA.paletteUpdate1, sizeof(INTRO_DATA.tilesFadeStage));

    LZ77UncompVram(sEndingAnimalsBg3Gfx, VRAM_BASE);
    LZ77UncompVram(sEndingAnimalsBg2Gfx, VRAM_BASE + 0x8000);
    LZ77UncompVram(sEndingAnimalsBg2Tilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sEndingAnimalsBg3Tilemap, VRAM_BASE + 0xF800);

    DMA3_COPY_32(sEndingAnimalsBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    DMA3_FILL_16(0x2FF, VRAM_BASE + 0xF500, 0x300);

    gBg0XPosition = 0;
    gBg0YPosition = 0;
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg3XPosition = 0;
    gBg2YPosition = -30;
    gBg3YPosition = 226;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 226);

    WRITE_16(REG_BG2CNT, CREATE_BGCNT(2, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
    gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    EndingDialogueSetupOam(20, 0, 0, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(EndingConversationAndAnimalsVblank);
}

 /**
 * @brief 96448 | 4e0 | Processes the ending in ship cutscene
 *
 * @return boolu32 bool, ended
 */
boolu32 EndingInShipProcess(void)
{
    boolu32 finished;

    finished = FALSE;

    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer == 7)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldy != 0)
                {
                    gWrittenToBldy--;
                }
                else
                {
                    PlayMusic(MUSIC_EPILOGUE, 14);
                    INTRO_DATA.subStage = 1;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (INTRO_DATA.timer == 70)
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
                INTRO_DATA.fadeLine = 0;
                INTRO_DATA.fadeColumn = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][7];
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.textAdvanceState == 0)
                INTRO_DATA.textAdvanceState = 1;

            INTRO_DATA.timer = 0;

            if (INTRO_DATA.textAdvanceState == 2)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 3;
            }

            if (EndingCheckMonologueEnded())
            {
                INTRO_DATA.subStage = 3;
                INTRO_DATA.textAdvanceState = 0;
            }

            if (INTRO_DATA.unk_213 == 0)
            {
                INTRO_DATA.unk_213 = 100;
            }
            else if (INTRO_DATA.unk_213 == 1)
            {
                INTRO_DATA.unk_213 = 100;
                SpecialCutsceneProcessMonologue();
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 3:
            if (INTRO_DATA.timer == 1)
            {
                gWrittenToBldalpha_Evb = 0;
                gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
            }
            else if (INTRO_DATA.timer == 20)
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_BG0_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT |
                    BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
                INTRO_DATA.subStage = 4;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 4:
            if (INTRO_DATA.timer == 4)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Evb < BLDALPHA_MAX_VALUE)
                    gWrittenToBldalpha_Evb++;

                if (gWrittenToBldalpha_Eva != 0)
                    gWrittenToBldalpha_Eva--;

                if (gWrittenToBldalpha_Evb == BLDALPHA_MAX_VALUE && gWrittenToBldalpha_Eva == 0)
                {
                    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG0);
                    INTRO_DATA.subStage = 5;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 5:
            if (INTRO_DATA.timer == 10)
            {
                EndingDialogueSetupOam(30, 120, 80, TRUE);
            }
            else if (INTRO_DATA.timer == 39)
            {
                gWrittenToBldy = BLDY_MAX_VALUE;
            }
            else if (INTRO_DATA.timer == 40)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 6;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 6:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 7;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 7:
            INTRO_DATA.timer = 0;
            EndingAdamConversationInit();
            INTRO_DATA.subStage = 8;
            break;

        case 8:
            gWrittenToBldy = 0;
            INTRO_DATA.timer = 0;
            SoundPlay(SOUND_24C);
            INTRO_DATA.subStage = 9;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 9:
            if (INTRO_DATA.timer != 10)
            {
                if (INTRO_DATA.timer == 40)
                {
                    EndingDialogueSetupOam(255, 0, 0, FALSE);
                    EndingDialogueSetupOam(6, 20, 192, FALSE);
                    EndingDialogueSetupOam(7, 128, 192, FALSE);
                    EndingDialogueSetupOam(9, 128, 192, FALSE);
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.subStage = 10;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            EndingProcessAdamText();
            break;

        case 10:
            INTRO_DATA.timer = 0;

            if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.textAdvanceState == 0)
                INTRO_DATA.textAdvanceState = 1;

            if (INTRO_DATA.textAdvanceState == 2)
            {
                INTRO_DATA.textAdvanceState = 0;
                SoundPlay(SOUND_203);
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG0);
                INTRO_DATA.textAdvanceState = 0;
                SoundPlay(SOUND_203);
                FadeMusic(10);
                INTRO_DATA.subStage = 11;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            EndingProcessAdamText();
            break;

        case 11:
            INTRO_DATA.timer = 0;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 12:
            if (INTRO_DATA.timer == 1)
            {
                ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[SOUND_24C].trackGroupNumber].pTrack, 0);
            }
            else if (INTRO_DATA.timer == 10)
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = BLDY_MAX_VALUE;
                INTRO_DATA.subStage = 13;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 13:
            EndingAnimalsInit();
            INTRO_DATA.timer = 0;
            gWrittenToBldy = 0;
            INTRO_DATA.subStage = 14;
            break;

        case 14:
            if (INTRO_DATA.timer == 1)
            {
                PlayMusic(MUSIC_EPILOGUE_END, 14);
            }
            else if (INTRO_DATA.timer == 640)
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
                INTRO_DATA.subStage = 15;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 15:
            if (INTRO_DATA.timer == 2)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldy < BLDY_MAX_VALUE)
                {
                    gWrittenToBldy++;
                }
                else
                {
                    INTRO_DATA.subStage = 0;
                    finished = TRUE;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 96928 | 88 | Main handler for the ending in ship cutscene
 *
 * @return boolu32 bool, ended
 */
boolu32 EndingInShip(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            EndingMonologueInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();

            if (gWrittenToBldy == 0)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (EndingInShipProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 969b0 | 30 | Processes the monologue cursor in the ending
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessMonologueCursor(struct SpecialCutsceneOam* pOam)
{
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        pOam->xPosition = 118;
        pOam->yPosition = INTRO_DATA.currentLine * 8 + 24;
    }
    else
    {
        pOam->xPosition = 260;
    }
}

 /**
 * @brief 969e0 | 28 | Holds a special cutscene OAM on the last frame of its animation
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessHoldLastAnimFrame(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            pOam->animationDurationCounter = 0;
    }
}

 /**
 * @brief 96a08 | 34 | Handles the SR388 radar view
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessSr388RadarView(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingSr388RadarViewOam_Idle;
            pOam->stage = 1;
        }
    }
}

 /**
 * @brief 96a3c | 34 | Handles the Samus view radar view
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessSamusViewRadarView(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingSamusViewRadarViewOam_Idle;
            pOam->stage = 1;
        }
    }
}

 /**
 * @brief 96a70 | 9c | Handles the opening and closing animations of the ending dialogue type 5 OAM
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessDialogueType5(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    frame = &pOam->pOam[pOam->currentAnimationFrame];

    if (pOam->stage == 0)
    {
        if (pOam->currentAnimationFrame == 1 && pOam->animationDurationCounter == 1)
            SoundPlay(SOUND_11C);

        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->animationDurationCounter = 0;

        if (INTRO_DATA.subStage == 11)
        {
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingDialogueType5Oam_Closing;
            SoundPlay(SOUND_11D);
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 96b0c | 8c | Processes the Adam text cursor in the ending
 *
 * @param pOam Cutscene OAM data pointer
 */
void EndingProcessAdamTextCursor(struct SpecialCutsceneOam* pOam)
{
    if (*INTRO_DATA.pText == CHAR_TERMINATOR)
    {
        pOam->xPosition = 290;
    }
    else if (*INTRO_DATA.pText != CHAR_NEW_LINE)
    {
        if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
        {
            pOam->xPosition = 290;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingTextCursorOam;
        }
        else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
        {
            pOam->xPosition = SCREEN_X_MIDDLE;
            pOam->yPosition = 154;
            pOam->pOam = sEndingNextPageArrowOam;
        }
        else
        {
            pOam->xPosition = INTRO_DATA.currentColumn * 8 + INTRO_DATA.indent + 14;
            pOam->yPosition = INTRO_DATA.currentLine * 8 + 132;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
    }
    else
    {
        pOam->xPosition = INTRO_DATA.currentColumn * 8 + INTRO_DATA.indent + 14;
        pOam->yPosition = INTRO_DATA.currentLine * 8 + 132;
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
    }
}
