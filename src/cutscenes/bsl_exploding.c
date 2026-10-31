#include "cutscenes/bsl_exploding.h"
#include "cutscenes/cutscene_common.h"

#include "callbacks.h"
#include "gba.h"
#include "globals.h"
#include "macros.h"
#include "music_wrappers.h"
#include "oam.h"
#include "syscalls.h"

#include "audio/track_internal.h"

#include "data/cutscenes_data.h"

#include "structs/cutscene_data.h"

/**
 * @brief 9c1c8 | 8c | Main handler for the BSL exploding cutscene
 *
 * @return boolu32 Ended
 */
boolu32 CutsceneBslExploding(void)
{
    boolu32 ended;

    ended = FALSE;

    switch (CUTSCENE_DATA.stage)
    {
        case 0:
            CUTSCENE_DATA.stage = 1;
            CutsceneBslExplodingInit();
            break;

        case 1:
            if (gWrittenToBldy == BLDY_MAX_VALUE)
                SoundPlayOnUnusedMusicTrack(0x247);

            CutsceneFadeIn();

            if (gWrittenToBldy == 0)
                CUTSCENE_DATA.stage++;
            break;

        case 2:
            if (CutsceneBslExplodingProcess())
            {
                CUTSCENE_DATA.stage = 3;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);
            }
            break;

        case 3:
            CutsceneFadeOut();
            if (gWrittenToBldy == BLDY_MAX_VALUE)
                ended = TRUE;
            break;
    }

    return ended;
}

/**
 * @brief 9c254 | 190 | Initializes the BSL exploding cutscene
 *
 */
void CutsceneBslExplodingInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(CutsceneBslExplodingLoadingVblank);

    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sCutsceneBslSpaceObjGfx, VRAM_OBJ);
    DMA3_COPY_32(sCutsceneBslSpaceObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sCutsceneBslSpaceBgGfx, VRAM_BASE);
    LZ77UncompVram(sCutsceneBslSpaceTilemap_681a1c, VRAM_BASE + 0xE000);
    LZ77UncompVram(sCutsceneBslSpaceTilemap_6820a4, VRAM_BASE + 0xE800);
    LZ77UncompVram(sCutsceneBslExplodingBg2Tilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sCutsceneBslExplodingBg3Tilemap, VRAM_BASE + 0xF800);

    DMA3_COPY_32(sCutsceneBslSpaceBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    WRITE_16(PALRAM_BASE, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(0, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 29, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_DISPCNT, DCNT_BG3 | DCNT_OBJ);

    gWrittenToBldy = BLDY_MAX_VALUE;
    gWrittenToBldalpha_Eva = 8;
    gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;

    CutsceneBslExplodingSetupOam(1, 0, 0, FALSE);
    CutsceneBslExplodingSetupOam(20, 112, 88, FALSE);

    CUTSCENE_DATA.paletteUpdate = 0;
    CUTSCENE_DATA.paletteFrame = 0;
    DMA3_COPY_32(&sCutsceneBslSpaceBgFadePal[CUTSCENE_DATA.paletteFrame * PAL_ROW], PALRAM_BASE + 9 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));

    CutsceneDrawAllOam();
    CallbackSetVBlank(CutsceneBslExplodingVblank);
}

/**
 * @brief 9c3e4 | 214 | Processes the BSL exploding cutscene
 *
 * @return boolu32 Ended
 */
boolu32 CutsceneBslExplodingProcess(void)
{
    boolu32 ended;

    ended = FALSE;

    CUTSCENE_DATA.timer++;

    switch (CUTSCENE_DATA.subStage)
    {
        case 0:
            CUTSCENE_DATA.timer = 0;
            CUTSCENE_DATA.subStage = 1;
            break;

        case 1:
            if (CUTSCENE_DATA.timer == 15)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT |
                    BLDCNT_BG2_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG2);
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 2;
            }
            break;

        case 2:
            if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
            {
                if (CUTSCENE_DATA.timer == 1)
                {
                    CUTSCENE_DATA.timer = 0;
                    gWrittenToBldalpha_Eva += 2;
                }
                gWrittenToBldy = BLDY_MAX_VALUE;
            }
            else if (CUTSCENE_DATA.timer == 40)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                WRITE_16(REG_DISPCNT, DCNT_BG1 | DCNT_OBJ);

                CutsceneDestroyOamOfType(1);
                CutsceneDestroyOamOfType(20);
                CutsceneBslExplodingSetupOam(21, 120, 90, TRUE);

                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 3;
            }
            break;

        case 3:
            if (CUTSCENE_DATA.timer == 1)
            {
                gWrittenToBldy = 0;
                gWrittenToBldalpha_Eva = 10;
                gWrittenToBldalpha_Evb = 10;
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 4;
            }
            break;

        case 4:
            if (CUTSCENE_DATA.timer == 60)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG0_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT |
                    BLDCNT_BG1_SECOND_TARGET_PIXEL | BLDCNT_BG2_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL |
                    BLDCNT_OBJ_SECOND_TARGET_PIXEL);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 5;
            }
            break;

        case 5:
            if (CUTSCENE_DATA.paletteFrame < 15)
            {
                if (CUTSCENE_DATA.timer == 4)
                {
                    CUTSCENE_DATA.timer = 0;
                    CUTSCENE_DATA.paletteUpdate = 1;
                    CUTSCENE_DATA.paletteFrame++;

                    if (CUTSCENE_DATA.paletteFrame == 1)
                    {
                        CutsceneBslExplodingSetupOam(22, 120, 96, FALSE);
                        CutsceneBslExplodingSetupOam(22, 95, 80, FALSE);
                        CutsceneBslExplodingSetupOam(22, 140, 105, FALSE);
                    }
                    else if (CUTSCENE_DATA.paletteFrame == 2)
                    {
                        CutsceneBslExplodingSetupOam(22, 120, 84, FALSE);
                        CutsceneBslExplodingSetupOam(22, 145, 85, FALSE);
                    }
                    else if (CUTSCENE_DATA.paletteFrame == 3)
                    {
                        CutsceneBslExplodingSetupOam(22, 96, 106, FALSE);
                    }
                }
            }
            else if (CUTSCENE_DATA.timer == 15)
            {
                CUTSCENE_DATA.timer = 0;
                gWrittenToBldy = BLDY_MAX_VALUE;
                CUTSCENE_DATA.subStage = 6;
            }
            break;

        case 6:
            if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
            {
                if (CUTSCENE_DATA.timer == 6)
                {
                    CUTSCENE_DATA.timer = 0;
                    gWrittenToBldalpha_Eva++;
                }
            }
            else
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);
                if (CUTSCENE_DATA.timer == 16)
                {
                    CUTSCENE_DATA.timer = 0;
                    ended = TRUE;
                }
            }
            break;
    }

    CutsceneProcessOam();
    CutsceneDrawAllOam();

    return ended;
}

/**
 * @brief 9c5f8 | 2c | Processes the background scrolling in the BSL exploding cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void CutsceneBslExplodingProcessScrolling(struct CutsceneOam* pOam)
{
    pOam->unk_13++;
    if (pOam->unk_13 == 30)
    {
        pOam->unk_13 = 0;
        pOam->xPosition--;
    }

    WRITE_16(REG_BG3HOFS, pOam->xPosition);
}

/**
 * @brief 9c624 | 5c | Processes the far BSL station in the BSL exploding cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void CutsceneBslExplodingProcessBslFar(struct CutsceneOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->stage == 0)
    {
        if (CUTSCENE_DATA.subStage == 5 && CUTSCENE_DATA.paletteFrame == 5)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sCutsceneBslExplodingExplosionsOam;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame[0].timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->exists = FALSE;
        }
    }
}

/**
 * @brief 9c680 | 2c | Processes an explosion in the BSL exploding cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void CutsceneBslExplodingProcessExplosions(struct CutsceneOam* pOam)
{
    const struct FrameData* pFrame;

    pFrame = &pOam->pOam[pOam->currentAnimationFrame];
    if (pFrame[0].timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9c6ac | 1a4 | Sets up an OAM object for the BSL exploding cutscene
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param descendingSearchOrder Search for a free slot starting from the end
 * @return u8 Slot
 */
u8 CutsceneBslExplodingSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder)
{
    s8 slot;

    if (!descendingSearchOrder)
    {
        for (slot = 0; slot < ARRAY_SIZE(CUTSCENE_DATA.oam); slot++)
        {
            if (CUTSCENE_DATA.oam[slot].type == 0)
                break;
        }

        if (slot > ARRAY_SIZE(CUTSCENE_DATA.oam) - 1)
            return ARRAY_SIZE(CUTSCENE_DATA.oam);
    }
    else
    {
        for (slot = ARRAY_SIZE(CUTSCENE_DATA.oam) - 1; slot >= 0; slot--)
        {
            if (CUTSCENE_DATA.oam[slot].type == 0)
                break;
        }

        if (slot < 0)
            return ARRAY_SIZE(CUTSCENE_DATA.oam);
    }

    DMA3_FILL_32(0, &CUTSCENE_DATA.oam[slot], sizeof(CUTSCENE_DATA.oam[slot]));

    CUTSCENE_DATA.oam[slot].xPosition = xPosition;
    CUTSCENE_DATA.oam[slot].yPosition = yPosition;
    CUTSCENE_DATA.oam[slot].type = type;
    CUTSCENE_DATA.oam[slot].exists = TRUE;

    if (type == 1)
    {
        CUTSCENE_DATA.oam[slot].exists = FALSE;
        CUTSCENE_DATA.oam[slot].pFunction = CutsceneBslExplodingProcessScrolling;
    }
    else if (type == 20)
    {
        CUTSCENE_DATA.oam[slot].priority = 2;
        CUTSCENE_DATA.oam[slot].pOam = sCutsceneBslExplodingOam_680ffc;
        CUTSCENE_DATA.oam[slot].pFunction = CutsceneOam_Empty;
    }
    else if (type == 21)
    {
        CUTSCENE_DATA.oam[slot].priority = 2;
        CUTSCENE_DATA.oam[slot].pOam = sCutsceneBslExplodingBslFarOam;
        CUTSCENE_DATA.oam[slot].pFunction = CutsceneBslExplodingProcessBslFar;
    }
    else if (type == 22)
    {
        CUTSCENE_DATA.oam[slot].priority = 2;
        CUTSCENE_DATA.oam[slot].pOam = sCutsceneBslExplodingExplosionsOam;
        CUTSCENE_DATA.oam[slot].pFunction = CutsceneBslExplodingProcessExplosions;
    }

    return slot;
}

/**
 * @brief 9c850 | 58 | Gets the position, scaling and slot of an OAM object of the BSL exploding cutscene
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 * @param pScaling Scaling pointer
 * @return u8 Slot
 */
u8 CutsceneBslExplodingGetOamInfoByType(u8 type, s16* pXPosition, s16* pYPosition, s16* pScaling)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_DATA.oam); i++)
    {
        if (CUTSCENE_DATA.oam[i].type == type)
        {
            *pXPosition = CUTSCENE_DATA.oam[i].xPosition;
            *pYPosition = CUTSCENE_DATA.oam[i].yPosition;
            *pScaling = CUTSCENE_DATA.oam[i].scaling;
            return i;
        }
    }

    // Default values if not found
    *pXPosition = 300;
    *pYPosition = 200;
    *pScaling = Q_8_8(1.f);

    return 0;
}

/**
 * @brief 9c8a8 | 84 | V-blank code for the BSL exploding cutscene
 *
 */
void CutsceneBslExplodingVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    if (CUTSCENE_DATA.paletteUpdate == 1)
    {
        CUTSCENE_DATA.paletteUpdate = 0;
        DMA3_COPY_32(&sCutsceneBslSpaceBgFadePal[CUTSCENE_DATA.paletteFrame * PAL_ROW], PALRAM_BASE + 9 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
    }
}

/**
 * @brief 9c92c | c | Loading V-blank code for the BSL exploding cutscene
 *
 */
void CutsceneBslExplodingLoadingVblank(void)
{
    UpdateAudio();
}
