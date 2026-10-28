#include "cutscenes/restricted_lab_detaching.h"
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
#include "data/sprite_data.h"

#include "structs/cutscene_data.h"

/**
 * @brief 9ae18 | 8c | Main handler for the restricted lab detaching cutscene
 *
 * @return boolu32 Ended
 */
boolu32 CutsceneRestrictedLabDetaching(void)
{
    boolu32 ended;

    ended = FALSE;

    switch (CUTSCENE_DATA.stage)
    {
        case 0:
            CUTSCENE_DATA.stage = 1;
            CutsceneRestrictedLabDetachingInit();
            break;

        case 1:
            if (gWrittenToBldy == BLDY_MAX_VALUE)
                SoundPlay_3b1c(0x248);

            CutsceneFadeIn();

            if (gWrittenToBldy == 0)
                CUTSCENE_DATA.stage++;
            break;

        case 2:
            if (CutsceneRestrictedLabDetachingProcess())
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
 * @brief 9aea4 | 15c | Initializes the restricted lab detaching cutscene
 *
 */
void CutsceneRestrictedLabDetachingInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_9c1bc);
    unk_36c4();

    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sCutsceneBslSpaceObjGfx, VRAM_OBJ);
    DMA3_COPY_32(sCutsceneBslSpaceObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sCutsceneBslSpaceBgGfx, VRAM_BASE);
    LZ77UncompVram(sCutsceneBslSpaceTilemap_6820a4, VRAM_BASE + 0xE000);
    LZ77UncompVram(sCutsceneBslSpaceTilemap_681a1c, VRAM_BASE + 0xE800);

    DMA3_COPY_32(sCutsceneBslSpaceBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    WRITE_16(PALRAM_BASE, 0);

    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 29, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 28, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_DISPCNT, DCNT_BG3 | DCNT_OBJ);
    gWrittenToBldy = BLDY_MAX_VALUE;

    CutsceneRestrictedLabDetachingSetupOam(1, 150, 90);
    CutsceneRestrictedLabDetachingSetupOam(3, 150, 90);
    CutsceneRestrictedLabDetachingSetupOam(2, 150, 90);
    CutsceneRestrictedLabDetachingSetupOam(4, 120, 0);
    CutsceneProcessOam();
    CutsceneDrawAllOam();

    CUTSCENE_DATA.unk_A = 0;
    CUTSCENE_DATA.unk_C = 0;
    DMA3_COPY_32(&sCutsceneBslSpaceBgFadePal[CUTSCENE_DATA.unk_C * PAL_ROW], PALRAM_BASE + 9 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));

    CallbackSetVBlank(CutsceneRestrictedLabDetachingVblank);
}

/**
 * @brief 9b000 | 370 | Processes the restricted lab detaching cutscene
 *
 * @return boolu32 Ended
 */
boolu32 CutsceneRestrictedLabDetachingProcess(void)
{
    boolu32 ended;
    s16 xPosition;
    s16 yPosition;

    ended = FALSE;

    switch (CUTSCENE_DATA.subStage)
    {
        case 0:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.timer == 1)
            {
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 1;
            }
            break;

        case 1:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.timer == 1)
            {
                CutsceneRestrictedLabDetachingGetPositionOfOamByType(2, &xPosition, &yPosition);
                unk_9c0b4(17, xPosition - 20, yPosition - 20, -2, 6);
                unk_9c0b4(17, xPosition - 70, yPosition - 26, -1, 4);
            }
            else if (CUTSCENE_DATA.timer == 16)
            {
                CutsceneRestrictedLabDetachingGetPositionOfOamByType(2, &xPosition, &yPosition);
                unk_9c0b4(17, xPosition - 30, yPosition - 30, -2, 8);
                unk_9c0b4(17, xPosition - 50, yPosition - 8, -1, 8);
            }
            else if (CUTSCENE_DATA.timer == 20)
            {
                CutsceneRestrictedLabDetachingGetPositionOfOamByType(2, &xPosition, &yPosition);
                unk_9c0b4(17, xPosition - 80, yPosition - 14, -3, 6);
                unk_9c0b4(17, xPosition - 10, yPosition - 18, -2, 2);
            }
            else if (CUTSCENE_DATA.timer == 170)
            {
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 2;
                gWrittenToBldy = 0;
            }
            break;

        case 2:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy += 2;
            }
            else
            {
                gWrittenToBldy = BLDY_MAX_VALUE;
                DMA3_FILL_32(0, CUTSCENE_DATA.oam, sizeof(CUTSCENE_DATA.oam));
                CUTSCENE_DATA.subStage = 5;
            }
            break;

        case 5:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy += 2;
            }
            else
            {
                DMA3_FILL_32(0, CUTSCENE_DATA.oam, sizeof(CUTSCENE_DATA.oam));
                CUTSCENE_DATA.timer = 0;
                CutsceneRestrictedLabDetachingSetupOam(4, 0, 0);
                CutsceneRestrictedLabDetachingSetupOam(30, 205, 10);
                CutsceneRestrictedLabDetachingSetupOam(12, 140, 80);
                WRITE_16(REG_BG2HOFS, 0);
                WRITE_16(REG_BG2VOFS, 0);
                CUTSCENE_DATA.subStage = 6;
            }
            break;

        case 6:
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy -= 2;
            }
            else
            {
                gWrittenToBldy = 0;
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 7;
            }
            break;

        case 7:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.timer == 149)
            {
                gWrittenToBldalpha_Eva = 10;
                gWrittenToBldalpha_Evb = 10;
            }
            else if (CUTSCENE_DATA.timer == 150)
            {
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 8;
            }
            break;

        case 8:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.timer == 1)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT |
                    BLDCNT_BG2_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);

                CutsceneRestrictedLabDetachingGetPositionOfOamByType(12, &xPosition, &yPosition);
                CutsceneDestroyOamOfType(12);
                unk_9c0b4(16, xPosition, yPosition, 0, 0);

                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 9;
            }
            break;

        case 9:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.unk_C < 15)
            {
                if (CUTSCENE_DATA.timer == 4)
                {
                    CUTSCENE_DATA.timer = 0;
                    CUTSCENE_DATA.unk_A = 1;
                    CUTSCENE_DATA.unk_C++;
                }
            }
            else if (CUTSCENE_DATA.timer == 15)
            {
                CUTSCENE_DATA.timer = 0;
                gWrittenToBldy = BLDY_MAX_VALUE;
                CUTSCENE_DATA.subStage = 10;
            }
            break;

        case 10:
            CUTSCENE_DATA.timer++;
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
                    DMA3_FILL_32(0, CUTSCENE_DATA.oam, sizeof(CUTSCENE_DATA.oam));
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
 * @brief 9b370 | cc | Processes the falling restricted lab
 *
 * @param pOam Cutscene OAM data pointer
 */
void CutsceneRestrictedLabDetachingProcessFallingLab(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->xPosition = pOam->unk_6 + (pOam->timer >> 1);
        pOam->yPosition = pOam->unk_8 - (pOam->timer >> 2);
    }

    pOam->unk_13++;
    if (pOam->unk_13 == 10)
    {
        pOam->unk_13 = 0;

        if (pOam->timer < 220)
            pOam->scaling += 2;
        else if (pOam->timer < 440)
            pOam->scaling += 4;
        else
            pOam->scaling += 6;

        if (pOam->scaling > 0x1FF)
            pOam->scaling = 0x200;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 6)
    {
        pOam->unk_A = 0;
        pOam->unk_C++;
        if (pOam->unk_C > 15)
            pOam->unk_C = 0;
    }

    if ((u16)(pOam->xPosition + 16) > 306 || pOam->yPosition < -50 || pOam->yPosition > 176)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9b43c | 470 | Sets up an OAM object for the restricted lab detaching cutscene
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot
 */
u8 CutsceneRestrictedLabDetachingSetupOam(u8 type, s16 xPosition, s16 yPosition)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_DATA.oam); i++)
    {
        if (!CUTSCENE_DATA.oam[i].type)
            break;
    }

    if (i >= ARRAY_SIZE(CUTSCENE_DATA.oam))
        return ARRAY_SIZE(CUTSCENE_DATA.oam);

    DMA3_FILL_32(0, &CUTSCENE_DATA.oam[i], sizeof(CUTSCENE_DATA.oam[i]));

    CUTSCENE_DATA.oam[i].xPosition = xPosition;
    CUTSCENE_DATA.oam[i].yPosition = yPosition;
    CUTSCENE_DATA.oam[i].type = type;
    CUTSCENE_DATA.oam[i].exists = TRUE;

    if (type == 1)
    {
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].scaling = 0x180;
        CUTSCENE_DATA.oam[i].drawMode = 3;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680d54;
        CUTSCENE_DATA.oam[i].pFunction = CutsceneRestrictedLabDetachingProcessBslPart;
    }
    else if (type == 2)
    {
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].scaling = 0x180;
        CUTSCENE_DATA.oam[i].drawMode = 3;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680d64;
        CUTSCENE_DATA.oam[i].pFunction = CutsceneRestrictedLabDetachingProcessBslPart;
    }
    else if (type == 3)
    {
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].scaling = 0x180;
        CUTSCENE_DATA.oam[i].drawMode = 3;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680d74;
        CUTSCENE_DATA.oam[i].pFunction = CutsceneRestrictedLabDetachingProcessBslPart;
    }
    else if (type == 4)
    {
        CUTSCENE_DATA.oam[i].exists = FALSE;
        CUTSCENE_DATA.oam[i].pFunction = CutsceneRestrictedLabDetachingProcessScrolling;
    }
    else if (type == 5)
    {
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680e2c;
        CUTSCENE_DATA.oam[i].pFunction = unk_9ba50;
    }
    else if (type == 6)
    {
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680e3c;
        CUTSCENE_DATA.oam[i].pFunction = unk_9ba50;
    }
    else if (type == 7)
    {
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680da4;
        CUTSCENE_DATA.oam[i].pFunction = unk_9bac0;
    }
    else if (type == 8)
    {
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680d94;
        CUTSCENE_DATA.oam[i].pFunction = unk_9bb30;
    }
    else if (type == 9)
    {
        CUTSCENE_DATA.oam[i].scaling = 0x100;
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].drawMode = 1;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680d84;
        CUTSCENE_DATA.oam[i].pFunction = unk_9bc04;
    }
    else if (type == 10)
    {
        CUTSCENE_DATA.oam[i].exists = FALSE;
        CUTSCENE_DATA.oam[i].pFunction = unk_9bcdc;
    }
    else if (type == 11)
    {
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680dcc;
        CUTSCENE_DATA.oam[i].pFunction = unk_9bac0;
    }
    else if (type == 12)
    {
        CUTSCENE_DATA.oam[i].scaling = 0x100;
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].drawMode = 1;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680fec;
        CUTSCENE_DATA.oam[i].pFunction = unk_9bd24;
    }
    else if (type == 13)
    {
        CUTSCENE_DATA.oam[i].scaling = 0x100;
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].drawMode = 1;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680fc4;
        CUTSCENE_DATA.oam[i].pFunction = unk_9bdf8;
    }
    else if (type == 14)
    {
        CUTSCENE_DATA.oam[i].exists = FALSE;
        CUTSCENE_DATA.oam[i].pFunction = unk_9be8c;
    }
    else if (type == 15)
    {
        CUTSCENE_DATA.oam[i].exists = FALSE;
        CUTSCENE_DATA.oam[i].pFunction = unk_9bf54;
    }
    else if (type == 16)
    {
        CUTSCENE_DATA.oam[i].objMode = 1;
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680f9c;
        CUTSCENE_DATA.oam[i].pFunction = unk_9bfb8;
    }
    else if (type == 17)
    {
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680f74;
        CUTSCENE_DATA.oam[i].pFunction = unk_9bfb8;
    }
    else if (type == 18)
    {
        CUTSCENE_DATA.oam[i].exists = FALSE;
        CUTSCENE_DATA.oam[i].pFunction = unk_9c04c;
    }
    else if (type == 30)
    {
        CUTSCENE_DATA.oam[i].scaling = 0x1A0;
        CUTSCENE_DATA.oam[i].priority = 1;
        CUTSCENE_DATA.oam[i].drawMode = 3;
        CUTSCENE_DATA.oam[i].pOam = (const struct FrameData*)sCutsceneUnk_680f2c;
        CUTSCENE_DATA.oam[i].pFunction = CutsceneRestrictedLabDetachingProcessFallingLab;
    }

    return i;
}

/**
 * @brief 9b8ac | 178 | Processes a part of the BSL station
 *
 * @param pOam Cutscene OAM data pointer
 */
void CutsceneRestrictedLabDetachingProcessBslPart(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_13++;
        if (pOam->unk_13 == 9)
        {
            pOam->unk_13 = 0;
            pOam->xPosition--;
        }

        pOam->timer++;
        switch (pOam->unk_6)
        {
            case 0:
                if (pOam->timer == 4)
                {
                    pOam->timer = 0;
                    pOam->scaling += 2;
                    if (pOam->scaling > 0x17F)
                        pOam->unk_6 = 1;
                }
                break;

            case 1:
                if (pOam->timer == 5)
                {
                    pOam->timer = 0;
                    pOam->scaling += 2;
                    if (pOam->scaling > 0x19F)
                        pOam->unk_6 = 2;
                }
                break;

            case 2:
                if (pOam->timer == 6)
                {
                    pOam->timer = 0;
                    pOam->scaling += 2;
                    if (pOam->scaling > 0x1BF)
                        pOam->unk_6 = 3;
                }
                break;

            default:
                if (pOam->timer == 7)
                {
                    pOam->timer = 0;
                    pOam->scaling += 2;
                }
        }

        if (pOam->scaling > 0x200)
            pOam->scaling = 0x200;

        if (CUTSCENE_DATA.subStage == 1)
        {
            pOam->stage = 1;
            pOam->unk_13 = 0;
            pOam->unk_6 = 0;
            pOam->timer = 0;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_13++;
        if (pOam->unk_13 == 9)
        {
            pOam->unk_13 = 0;
            pOam->xPosition--;
        }

        if (pOam->type == 3)
        {
            pOam->yPosition += 6;
            pOam->unk_8 = pOam->yPosition;
        }

        pOam->timer = 0;
        pOam->unk_A = 0;
        pOam->stage = 2;
    }
    else if (pOam->stage == 2)
    {
        pOam->unk_13++;
        if (pOam->unk_13 == 9)
        {
            pOam->unk_13 = 0;
            pOam->xPosition--;
        }

        pOam->unk_A++;
        if (pOam->unk_A == 7)
        {
            pOam->unk_A = 0;
            pOam->scaling += 2;
            if (pOam->scaling > 0x200)
                pOam->scaling = 0x200;
        }

        pOam->timer++;
        if (pOam->type == 3)
            pOam->yPosition = (pOam->timer * pOam->timer >> 10) + pOam->unk_8;
    }
}

/**
 * @brief 9ba24 | 2c | Processes the background scrolling in the restricted lab detaching cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void CutsceneRestrictedLabDetachingProcessScrolling(struct CutsceneOam* pOam)
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
 * @brief 9ba50 | 70 | Moves a cutscene OAM object using its velocity
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9ba50(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->xPosition = (pOam->unk_C * pOam->timer >> 6) + pOam->unk_6;
        pOam->yPosition = (pOam->unk_A * pOam->timer >> 6) + pOam->unk_8;
    }

    if ((u16)(pOam->xPosition + 16) > 272 || pOam->yPosition < -16 || pOam->yPosition > 176)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9bac0 | 70 | Moves a cutscene OAM object using its velocity
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9bac0(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->xPosition = (pOam->unk_C * pOam->timer >> 6) + pOam->unk_6;
        pOam->yPosition = (pOam->unk_A * pOam->timer >> 6) + pOam->unk_8;
    }

    if ((u16)(pOam->xPosition + 16) > 272 || pOam->yPosition < -16 || pOam->yPosition > 176)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9bb30 | d4 | To document
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9bb30(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->xPosition = pOam->unk_6 - pOam->timer * 3u / 16;
        pOam->yPosition = pOam->timer / 8 + pOam->unk_8;
    }

    pOam->unk_13++;
    if (pOam->unk_13 == 12)
    {
        pOam->unk_13 = 0;
        pOam->scaling -= 2;
        if (pOam->scaling <= 0)
            pOam->scaling = 2;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 16)
    {
        pOam->unk_A = 0;
        pOam->unk_C++;
        if (pOam->unk_C > 3)
            pOam->unk_C = 0;

        DMA3_COPY_32(&sCutsceneRestrictedLabDetachingObjRow1CyclePal[pOam->unk_C * PAL_ROW], PALRAM_OBJ + 1 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
    }

    if ((u16)(pOam->xPosition + 16) > 272 || pOam->yPosition < -16 || pOam->yPosition > 176)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9bc04 | d8 | To document
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9bc04(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->xPosition = (pOam->timer * 11 >> 6) + pOam->unk_6;
        pOam->yPosition = pOam->unk_8 - (pOam->timer * 9 >> 6);
    }

    pOam->unk_13++;
    if (pOam->unk_13 == 12)
    {
        pOam->unk_13 = 0;
        pOam->scaling -= 2;
        if (pOam->scaling <= 0)
            pOam->scaling = 2;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 6)
    {
        pOam->unk_A = 0;
        pOam->unk_C++;
        if (pOam->unk_C > 3)
            pOam->unk_C = 0;

        DMA3_COPY_32(&sCutsceneRestrictedLabDetachingObjRow0CyclePal[pOam->unk_C * PAL_ROW], PALRAM_OBJ, PAL_ROW_SIZE / sizeof(u32));
    }

    if ((u16)(pOam->xPosition + 16) > 272 || pOam->yPosition < -16 || pOam->yPosition > 176)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9bcdc | 48 | Scrolls background 2 in the restricted lab detaching cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9bcdc(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        WRITE_16(REG_BG2HOFS, pOam->xPosition);
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        WRITE_16(REG_BG2HOFS, (pOam->unk_C * pOam->timer >> 7) + pOam->xPosition);
    }
}

/**
 * @brief 9bd24 | d4 | To document
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9bd24(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->xPosition = pOam->unk_6 - pOam->timer / 8;
        pOam->yPosition = pOam->timer / 16 + pOam->unk_8;
    }

    pOam->unk_13++;
    if (pOam->unk_13 == 3)
    {
        pOam->unk_13 = 0;
        pOam->scaling -= 4;
        if (pOam->scaling <= 2)
            pOam->scaling = 2;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 15)
    {
        pOam->unk_A = 0;
        pOam->unk_C++;
        if (pOam->unk_C > 3)
            pOam->unk_C = 0;

        DMA3_COPY_32(&sCutsceneRestrictedLabDetachingObjRow3CyclePal[pOam->unk_C * PAL_ROW], PALRAM_OBJ + 3 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
    }

    if ((u16)(pOam->xPosition + 16) > 272 || pOam->yPosition < -16 || pOam->yPosition > 176)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9bdf8 | 94 | To document
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9bdf8(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->xPosition = (pOam->unk_C * pOam->timer >> 6) + pOam->unk_6;
        pOam->yPosition = (pOam->unk_A * pOam->timer >> 6) + pOam->unk_8;
    }

    pOam->unk_13++;
    if (pOam->unk_13 == 5)
    {
        pOam->unk_13 = 0;
        pOam->scaling -= 4;
        if (pOam->scaling <= 2)
            pOam->scaling = 2;
    }

    if ((u16)(pOam->xPosition + 16) > 272 || pOam->yPosition < -16 || pOam->yPosition > 176)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9be8c | c8 | Fades the background palette and blending in the restricted lab detaching cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9be8c(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        DMA3_COPY_32(sCutsceneBslSpaceBgFadePal, PALRAM_BASE + 9 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_13++;
        if (pOam->unk_13 == 8)
        {
            pOam->unk_13 = 0;
            pOam->unk_C++;
            if (pOam->unk_C > 14)
            {
                pOam->unk_C = 15;
                pOam->stage = 2;
            }

            DMA3_COPY_32(&sCutsceneBslSpaceBgFadePal[pOam->unk_C * PAL_ROW], PALRAM_BASE + 9 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->unk_13++;
        if (pOam->unk_13 == 6)
        {
            pOam->unk_13 = 0;
            if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
            {
                gWrittenToBldalpha_Eva++;
                if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
                    gWrittenToBldalpha_Evb++;
            }
        }
    }
}

/**
 * @brief 9bf54 | 64 | Shakes background 1 in the restricted lab detaching cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9bf54(struct CutsceneOam* pOam)
{
    pOam->unk_13++;
    if (pOam->unk_13 == 1)
    {
        pOam->unk_13 = 0;
        CUTSCENE_DATA.unk_A += 2;
        if (CUTSCENE_DATA.unk_A > 160)
            CUTSCENE_DATA.unk_A = 160;
    }

    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == ARRAY_SIZE(sRandomNumberTable))
        pOam->animationDurationCounter = 0;

    WRITE_16(REG_BG1HOFS, sRandomNumberTable[pOam->animationDurationCounter]);
    WRITE_16(REG_BG1VOFS, sRandomNumberTable[pOam->animationDurationCounter]);
}

/**
 * @brief 9bfb8 | 94 | Moves a cutscene OAM object using its velocity, and destroys it once its animation ended
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9bfb8(struct CutsceneOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->xPosition = (pOam->unk_C * pOam->timer >> 6) + pOam->unk_6;
        pOam->yPosition = (pOam->unk_A * pOam->timer >> 6) + pOam->unk_8;
    }

    if ((u16)(pOam->xPosition + 16) > 272 || pOam->yPosition < -16 || pOam->yPosition > 176)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }

    pFrame = &pOam->pOam[pOam->currentAnimationFrame];
    if (pFrame[0].timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9c04c | 34 | Scrolls background 2 in the restricted lab detaching cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9c04c(struct CutsceneOam* pOam)
{
    pOam->unk_13++;
    if (pOam->unk_13 == 40)
    {
        pOam->unk_13 = 0;
        if (pOam->xPosition > 0)
            pOam->xPosition--;
    }

    WRITE_16(REG_BG2HOFS, pOam->xPosition);
}

/**
 * @brief 9c080 | 34 | Sets up an OAM object for the restricted lab detaching cutscene, with an X velocity
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param xVelocity X velocity
 * @return u8 Slot
 */
u8 unk_9c080(u8 type, s16 xPosition, s16 yPosition, s16 xVelocity)
{
    u8 slot;

    slot = CutsceneRestrictedLabDetachingSetupOam(type, xPosition, yPosition);
    CUTSCENE_DATA.oam[slot].unk_C = xVelocity;

    return slot;
}

/**
 * @brief 9c0b4 | 3c | Sets up an OAM object for the restricted lab detaching cutscene, with a velocity
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param xVelocity X velocity
 * @param yVelocity Y velocity
 * @return u8 Slot
 */
u8 unk_9c0b4(u8 type, s16 xPosition, s16 yPosition, s16 xVelocity, s16 yVelocity)
{
    u8 slot;

    slot = CutsceneRestrictedLabDetachingSetupOam(type, xPosition, yPosition);
    CUTSCENE_DATA.oam[slot].unk_A = yVelocity;
    CUTSCENE_DATA.oam[slot].unk_C = xVelocity;

    return slot;
}

/**
 * @brief 9c0f0 | 48 | Gets the position of an OAM object of the restricted lab detaching cutscene
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 */
void CutsceneRestrictedLabDetachingGetPositionOfOamByType(u8 type, s16* pXPosition, s16* pYPosition)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_DATA.oam); i++)
    {
        if (CUTSCENE_DATA.oam[i].type == type)
        {
            *pXPosition = CUTSCENE_DATA.oam[i].xPosition;
            *pYPosition = CUTSCENE_DATA.oam[i].yPosition;
            return;
        }
    }

    // Default values if not found
    *pXPosition = 300;
    *pYPosition = 200;
}

/**
 * @brief 9c138 | 84 | V-blank code for the restricted lab detaching cutscene
 *
 */
void CutsceneRestrictedLabDetachingVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    if (CUTSCENE_DATA.unk_A == 1)
    {
        CUTSCENE_DATA.unk_A = 0;
        DMA3_COPY_32(&sCutsceneBslSpaceBgFadePal[CUTSCENE_DATA.unk_C * PAL_ROW], PALRAM_BASE + 9 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
    }
}

/**
 * @brief 9c1bc | c | Loading V-blank code for the restricted lab detaching cutscene
 *
 */
void unk_9c1bc(void)
{
    UpdateAudio();
}
