#include "cutscenes/cutscene_common.h"

#include "fixed_point.h"
#include "gba.h"
#include "globals.h"
#include "init_helpers.h"
#include "macros.h"
#include "oam.h"
#include "text.h"

#include "data/cutscenes_data.h"
#include "data/generic_data.h"
#include "data/haze_data.h"

#include "structs/cutscene_data.h"

/**
 * @brief 9cd80 | 58 | Handles the fading in of a monologue cutscene
 *
 */
void CutsceneMonologueFadeIn(void)
{
    CutsceneMonologueProcessOam();
    CutsceneMonologueDrawAllOam();

    if (gWrittenToBldy == 0)
        return;

    if (gWrittenToBldy > 11)
    {
        CUTSCENE_MONOLOGUE_DATA.unk_16++;
        if (CUTSCENE_MONOLOGUE_DATA.unk_16 == 3)
        {
            CUTSCENE_MONOLOGUE_DATA.unk_16 = 0;
            gWrittenToBldy--;
        }
    }
    else if (gWrittenToBldy > 6)
    {
        CUTSCENE_MONOLOGUE_DATA.unk_16++;
        if (CUTSCENE_MONOLOGUE_DATA.unk_16 == 2)
        {
            CUTSCENE_MONOLOGUE_DATA.unk_16 = 0;
            gWrittenToBldy--;
        }
    }
    else
    {
        gWrittenToBldy--;
    }
}

/**
 * @brief 9cdd8 | 58 | Handles the fading out of a monologue cutscene
 *
 */
void CutsceneMonologueFadeOut(void)
{
    CutsceneMonologueProcessOam();
    CutsceneMonologueDrawAllOam();

    if (gWrittenToBldy >= BLDY_MAX_VALUE)
        return;

    if (gWrittenToBldy < 6)
    {
        CUTSCENE_MONOLOGUE_DATA.unk_16++;
        if (CUTSCENE_MONOLOGUE_DATA.unk_16 == 3)
        {
            CUTSCENE_MONOLOGUE_DATA.unk_16 = 0;
            gWrittenToBldy++;
        }
    }
    else if (gWrittenToBldy < 11)
    {
        CUTSCENE_MONOLOGUE_DATA.unk_16++;
        if (CUTSCENE_MONOLOGUE_DATA.unk_16 == 2)
        {
            CUTSCENE_MONOLOGUE_DATA.unk_16 = 0;
            gWrittenToBldy++;
        }
    }
    else
    {
        gWrittenToBldy++;
    }
}

/**
 * @brief 9ce30 | 44 | Processes the OAM objects of a monologue cutscene
 *
 */
void CutsceneMonologueProcessOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam); i++)
    {
        if (CUTSCENE_MONOLOGUE_DATA.oam[i].type)
            CUTSCENE_MONOLOGUE_DATA.oam[i].pFunction(&CUTSCENE_MONOLOGUE_DATA.oam[i]);
    }
}

/**
 * @brief 9ce74 | 4c | Draws the OAM objects of a monologue cutscene
 *
 */
void CutsceneMonologueDrawAllOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam); i++)
    {
        if (CUTSCENE_MONOLOGUE_DATA.oam[i].exists)
            CutsceneMnologueDrawOam(&CUTSCENE_MONOLOGUE_DATA.oam[i]);
    }

    ResetFreeOam();
    gNextOamSlot = 0;
}

/**
 * @brief 9cec0 | 188 | Draws an OAM object of a monologue cutscene
 *
 * @param pOam Cutscene monologue OAM data pointer
 */
void CutsceneMnologueDrawOam(struct CutsceneMonologueOam* pOam)
{
    u16* dst;
    const u16* src;
    const struct FrameData* pFrame;
    s32 partCount;
    s32 i;
    u16 part1;
    u16 part2;
    u32 slot;
    u32 x;
    u32 y;
    u32 xOffset;

    dst = (u16*)&gOamData[gNextOamSlot];

    pFrame = &pOam->pOam[pOam->currentAnimationFrame];
    if (pFrame->timer == pOam->animationDurationCounter)
    {
        pOam->currentAnimationFrame++;
        pOam->animationDurationCounter = 0;
        pFrame++;
    }

    if (pFrame->timer == 0)
    {
        pFrame -= pOam->currentAnimationFrame;
        pOam->currentAnimationFrame = 0;
    }

    src = pFrame->pFrame;
    partCount = *src++;

    for (i = 0; i < partCount; i++)
    {
        part1 = *src++;
        part2 = *src++;
        *dst++ = part1;
        *dst++ = part2;
        *dst++ = *src++;

        slot = gNextOamSlot + i;

        if (pOam->xFlip == TRUE)
        {
            gOamData[slot].split.xFlip ^= TRUE;
            xOffset = part2 + sCutsceneOamTileWidths[gOamData[slot].split.shape][gOamData[slot].split.size] * 8;
            x = MOD_AND((u16)pOam->xPosition - xOffset, 512);
            y = MOD_AND(part1 + (u16)pOam->yPosition, 256);
        }
        else
        {
            y = MOD_AND(part1 + (u16)pOam->yPosition, 256);
            x = MOD_AND(part2 + (u16)pOam->xPosition, 512);
        }

        gOamData[slot].split.y = y;
        gOamData[slot].split.x = x;
        gOamData[slot].split.priority = pOam->priority;
        gOamData[slot].split.paletteNum += pOam->paletteOffset;
        gOamData[slot].split.tileNum += pOam->tileOffset;
        gOamData[slot].split.objMode = pOam->objMode;

        dst++;
    }

    gNextOamSlot += partCount;
    pOam->animationDurationCounter++;
}

/**
 * @brief 9d048 | 54 | Resets an OAM object of a monologue cutscene
 *
 * @param slot Slot
 */
void CutsceneMonologueResetOam(u8 slot)
{
    CUTSCENE_MONOLOGUE_DATA.oam[slot].currentAnimationFrame = 0;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].animationDurationCounter = 0;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].stage = 0;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].objMode = 0;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].priority = 0;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].xFlip = 0;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].paletteOffset = 0;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].tileOffset = 0;
}

/**
 * @brief 9d09c | 4 | Empty function
 *
 */
void unk_9d09c(void)
{
    return;
}

/**
 * @brief 9d0a0 | 124 | Computes the window values of a circle (into the EWRAM buffer)
 *
 */
void unk_9d0a0(void)
{
    const s16* src;
    u16* dst;
    s16 top;
    s16 bottom;
    s16 i;
    u16 subSlice;
    s16 left;
    s16 right;

    DMA3_COPY_32(EWRAM_BASE + 0x1000, EWRAM_BASE + 0x2000, 0x150 / sizeof(u32));

    top = CUTSCENE_DATA.unk_E - CUTSCENE_DATA.unk_A;
    bottom = CUTSCENE_DATA.unk_E + CUTSCENE_DATA.unk_A;

    if (top < 0)
    {
        subSlice = -top;
        if (subSlice > CUTSCENE_DATA.unk_A * 2)
            top = SCREEN_SIZE_Y + 1;
        else
            top = 0;
    }
    else
    {
        subSlice = 0;
    }

    if (bottom > SCREEN_SIZE_Y - 1)
        bottom = SCREEN_SIZE_Y;

    src = sHaze_PowerBomb_WindowValuesPointers[CUTSCENE_DATA.unk_A];
    dst = EWRAM_BASE + 0x1000;

    for (i = 0; i < top; i++)
        *dst++ = 0;

    for (; i <= bottom; subSlice++, i++)
    {
        left = CUTSCENE_DATA.unk_C + src[subSlice * 2 + 1];
        right = CUTSCENE_DATA.unk_C + src[subSlice * 2 + 0];

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
 * @brief 9d1c4 | 20 | H-blank code for the circle window effect
 *
 */
void unk_9d1c4(void)
{
    s16 line;

    line = READ_16(REG_VCOUNT);
    WRITE_16(REG_WIN0H, ((u16*)(EWRAM_BASE + 0x2000))[line]);
}

/**
 * @brief 9d1e4 | 44 | Destroys a cutscene OAM object of the specified type
 *
 * @param type Type
 */
void CutsceneMonologueDestroyOamOfType(u8 type)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_DATA.oam); i++)
    {
        if (CUTSCENE_DATA.oam[i].type == type)
        {
            CUTSCENE_DATA.oam[i].type = 0;
            CUTSCENE_DATA.oam[i].exists = FALSE;
            break;
        }
    }
}

/**
 * @brief 9d228 | 20 | Handles the fading in of a cutscene
 * 
 */
void CutsceneFadeIn(void)
{
    CutsceneProcessOam();
    CutsceneDrawAllOam();

    if (gWrittenToBldy != 0)
        gWrittenToBldy--;
}

/**
 * @brief 9d248 | 20 | Handles the fading out of a cutscene
 * 
 */
void CutsceneFadeOut(void)
{
    CutsceneProcessOam();
    CutsceneDrawAllOam();

    if (gWrittenToBldy < BLDY_MAX_VALUE)
        gWrittenToBldy++;
}

/**
 * @brief 9d268 | 44 | Destroys a cutscene OAM object of the specified type
 * 
 * @param type Type
 */
void CutsceneDestroyOamOfType(u8 type)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_DATA.oam); i++)
    {
        if (CUTSCENE_DATA.oam[i].type == type)
        {
            CUTSCENE_DATA.oam[i].type = 0;
            CUTSCENE_DATA.oam[i].exists = FALSE;
            break;
        }
    }
}

/**
 * @brief 9d2ac | 48 | Processes the OAM objects of a cutscene
 * 
 */
void CutsceneProcessOam(void)
{
    u8 i;

    CUTSCENE_DATA.activeOamCount = 0;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_DATA.oam); i++)
    {
        if (CUTSCENE_DATA.oam[i].type)
        {
            CUTSCENE_DATA.oam[i].pFunction(&CUTSCENE_DATA.oam[i]);
            CUTSCENE_DATA.activeOamCount++;
        }
    }
}

/**
 * @brief 9d2f4 | 4c | Draws the OAM objects of a cutscene
 * 
 */
void CutsceneDrawAllOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_DATA.oam); i++)
    {
        if (CUTSCENE_DATA.oam[i].exists)
            CutsceneDrawOam(&CUTSCENE_DATA.oam[i]);
    }

    ResetFreeOam();
    gNextOamSlot = 0;
    CUTSCENE_UNK_3001238 = 0;
}

/**
 * @brief 9d340 | 830 | Draws a cutscene OAM object
 * 
 * @param pOam Cutscene OAM data pointer
 */
void CutsceneDrawOam(struct CutsceneOam* pOam)
{
    u32 slot;
    const u16* src;
    u16 xPosition;
    const struct FrameData* pFrame;
    u16 yPosition;
    s16 scaledX;
    s16 unk_3;
    u16 part1;
    s16 xScaling;
    u16 part2;
    u32 flip;
    u16* dst;
    s16 yScaling;
    s32 i;
    s32 partCount;
    s16 tmpY;
    u8 matrixSlot;
    s16 scaledY;
    s16 x;
    s16 tmpX;
    s16 unk_2;
    s16 y;
    s8 drawMode;

    dst = (u16*)&gOamData[gNextOamSlot];

    pFrame = &pOam->pOam[pOam->currentAnimationFrame];
    if (pFrame->timer == pOam->animationDurationCounter)
    {
        pOam->currentAnimationFrame++;
        pOam->animationDurationCounter = 0;
        pFrame++;
    }

    if (pFrame->timer == 0)
    {
        pFrame -= pOam->currentAnimationFrame;
        pOam->currentAnimationFrame = 0;
    }

    src = pFrame->pFrame;
    partCount = *src++;

    drawMode = pOam->drawMode;
    if (drawMode == 0)
    {
        for (i = 0; i < partCount; i++)
        {
            part1 = *src++;
            part2 = *src++;
            *dst++ = part1;
            *dst++ = part2;
            *dst++ = *src++;

            slot = gNextOamSlot + i;

            flip = pOam->xFlip;
            if (flip == TRUE)
            {
                gOamData[slot].split.xFlip ^= flip;
                xPosition = MOD_AND(-(part2 + sCutsceneOamXFlipOffsets[gOamData[slot].split.shape][gOamData[slot].split.size] * 8) + pOam->xPosition, 512);
                yPosition = MOD_AND(part1 + pOam->yPosition, 256);
            }
            else
            {
                yPosition = MOD_AND(part1 + pOam->yPosition, 256);
                xPosition = MOD_AND(part2 + pOam->xPosition, 512);
            }

            gOamData[slot].split.y = yPosition;
            gOamData[slot].split.x = xPosition;
            gOamData[slot].split.priority = pOam->priority;
            gOamData[slot].split.paletteNum += pOam->paletteOffset;
            gOamData[slot].split.tileNum += pOam->tileOffset;
            gOamData[slot].split.objMode = pOam->objMode;

            dst++;
        }
    }
    else if (drawMode == 1)
    {
        xPosition = pOam->xPosition + BLOCK_SIZE;
        yPosition = pOam->yPosition + BLOCK_SIZE;

        flip = pOam->xFlip;
        if (!flip)
            xScaling = pOam->scaling;
        else
            xScaling = -pOam->scaling;

        flip = pOam->yFlip;
        if (!flip)
            yScaling = pOam->scaling;
        else
            yScaling = -pOam->scaling;

        for (i = 0; i < partCount; i++)
        {
            s16 xOffset;
            s16 yOffset;

            part1 = *src++;
            part2 = *src++;
            *dst++ = part1;
            *dst++ = part2;
            *dst++ = *src++;

            slot = gNextOamSlot + i;

            xOffset = PIXEL_TO_SUB_PIXEL(sCutsceneOamXFlipOffsets[gOamData[slot].split.shape][gOamData[slot].split.size]);
            yOffset = PIXEL_TO_SUB_PIXEL(sCutsceneOamYFlipOffsets[gOamData[slot].split.shape][gOamData[slot].split.size]);

            y = MOD_AND(part1 + yPosition, 256);
            x = MOD_AND(part2 + xPosition, 512);

            tmpX = (x - xPosition) + xOffset;
            tmpY = (y - yPosition) + yOffset;

            scaledX = (tmpX * xScaling >> 8) - tmpX;
            scaledY = (tmpY * yScaling >> 8) - tmpY;

            if (gOamData[slot].split.xFlip)
            {
                gOamData[slot].split.xFlip = FALSE;
                xScaling = -xScaling;
            }

            if (gOamData[slot].split.yFlip)
            {
                gOamData[slot].split.yFlip = FALSE;
                yScaling = -yScaling;
            }

            x += scaledX;
            y += scaledY;

            unk_2 = xOffset + (x - xPosition);
            unk_3 = yOffset + (y - yPosition);

            x = (unk_2 * COS(pOam->rotation) - unk_3 * SIN(pOam->rotation)) >> 8;
            y = (unk_2 * SIN(pOam->rotation) + unk_3 * COS(pOam->rotation)) >> 8;

            x -= xOffset;
            y -= yOffset;

            gOamData[slot].split.y = MOD_AND(y + yPosition - BLOCK_SIZE, 256);
            gOamData[slot].split.x = MOD_AND(x + xPosition - BLOCK_SIZE, 512);
            gOamData[slot].split.affineMode = 1;

            if (gUnk_3001238 & 0x10)
                gOamData[slot].split.yFlip = TRUE;
            if (gUnk_3001238 & 0x8)
                gOamData[slot].split.xFlip = TRUE;
            gOamData[slot].split.matrixNum = gUnk_3001238 & 7;

            gOamData[slot].split.priority = pOam->priority;
            gOamData[slot].split.paletteNum += pOam->paletteOffset;
            gOamData[slot].split.tileNum += pOam->tileOffset;
            gOamData[slot].split.objMode = pOam->objMode;

            dst++;
        }

        matrixSlot = gUnk_3001238 * 4;
        gOamData[matrixSlot + 0].all.affineParam = FixedMultiplication(COS(pOam->rotation), FixedInverse(xScaling));
        gOamData[matrixSlot + 1].all.affineParam = FixedMultiplication(SIN(pOam->rotation), FixedInverse(xScaling));
        gOamData[matrixSlot + 2].all.affineParam = FixedMultiplication(-SIN(pOam->rotation), FixedInverse(yScaling));
        gOamData[matrixSlot + 3].all.affineParam = FixedMultiplication(COS(pOam->rotation), FixedInverse(yScaling));
        gUnk_3001238++;
    }
    else if (drawMode == 3)
    {
        xPosition = pOam->xPosition + BLOCK_SIZE;
        yPosition = pOam->yPosition + BLOCK_SIZE;

        flip = pOam->xFlip;
        if (!flip)
            xScaling = pOam->scaling;
        else
            xScaling = -pOam->scaling;

        flip = pOam->yFlip;
        if (!flip)
            yScaling = pOam->scaling;
        else
            yScaling = -pOam->scaling;

        for (i = 0; i < partCount; i++)
        {
            s16 xOffset;
            s16 yOffset;

            part1 = *src++;
            part2 = *src++;
            *dst++ = part1;
            *dst++ = part2;
            *dst++ = *src++;

            slot = gNextOamSlot + i;

            xOffset = PIXEL_TO_SUB_PIXEL(sCutsceneOamXFlipOffsets[gOamData[slot].split.shape][gOamData[slot].split.size]);
            yOffset = PIXEL_TO_SUB_PIXEL(sCutsceneOamYFlipOffsets[gOamData[slot].split.shape][gOamData[slot].split.size]);

            y = MOD_AND(part1 + yPosition, 256);
            x = MOD_AND(part2 + xPosition, 512);

            tmpX = (x - xPosition) + xOffset;
            tmpY = (y - yPosition) + yOffset;

            scaledX = (tmpX * xScaling >> 8) - tmpX;
            scaledY = (tmpY * yScaling >> 8) - tmpY;

            if (gOamData[slot].split.xFlip)
            {
                gOamData[slot].split.xFlip = FALSE;
                xScaling = -xScaling;
            }

            if (gOamData[slot].split.yFlip)
            {
                gOamData[slot].split.yFlip = FALSE;
                yScaling = -yScaling;
            }

            x += scaledX;
            y += scaledY;

            unk_2 = xOffset + (x - xPosition);
            unk_3 = yOffset + (y - yPosition);

            x = (unk_2 * COS(pOam->rotation) - unk_3 * SIN(pOam->rotation)) >> 8;
            y = (unk_2 * SIN(pOam->rotation) + unk_3 * COS(pOam->rotation)) >> 8;

            x -= xOffset * 2;
            y -= yOffset * 2;

            gOamData[slot].split.y = MOD_AND(y + yPosition - BLOCK_SIZE, 256);
            gOamData[slot].split.x = MOD_AND(x + xPosition - BLOCK_SIZE, 512);
            gOamData[slot].split.affineMode = 3;

            if (gUnk_3001238 & 0x10)
                gOamData[slot].split.yFlip = TRUE;
            if (gUnk_3001238 & 0x8)
                gOamData[slot].split.xFlip = TRUE;
            gOamData[slot].split.matrixNum = gUnk_3001238 & 7;

            gOamData[slot].split.priority = pOam->priority;
            gOamData[slot].split.paletteNum += pOam->paletteOffset;
            gOamData[slot].split.tileNum += pOam->tileOffset;
            gOamData[slot].split.objMode = pOam->objMode;

            dst++;
        }

        matrixSlot = gUnk_3001238 * 4;
        gOamData[matrixSlot + 0].all.affineParam = FixedMultiplication(COS(pOam->rotation), FixedInverse(xScaling));
        gOamData[matrixSlot + 1].all.affineParam = FixedMultiplication(SIN(pOam->rotation), FixedInverse(xScaling));
        gOamData[matrixSlot + 2].all.affineParam = FixedMultiplication(-SIN(pOam->rotation), FixedInverse(yScaling));
        gOamData[matrixSlot + 3].all.affineParam = FixedMultiplication(COS(pOam->rotation), FixedInverse(yScaling));
        gUnk_3001238++;
    }

    gNextOamSlot += partCount;
    pOam->animationDurationCounter++;
}

/**
 * @brief 9db70 | 4 | Empty cutscene OAM function
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9db70(struct CutsceneOam* pOam)
{
    return;
}
