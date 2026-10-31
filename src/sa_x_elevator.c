#include "sa_x.h"

#include "globals.h"
#include "macros.h"

#include "data/particle_data.h"
#include "data/sprites/sa_x.h"

#include "structs/samus.h"

/**
 * @brief d3f4 | 170 | Updates an SA-X elevator sprite
 *
 * @param spriteSlot Sprite slot
 */
void SaXUpdateElevatorSprite(s32 spriteSlot)
{
    const struct FrameData* pOam;

    if (gSaXElevatorSprites[spriteSlot].unk_0 != 0 && gSaXElevatorSprites[spriteSlot].unk_2 != 0)
    {
        gSaXElevatorSprites[spriteSlot].unk_2--;
        if (gSaXElevatorSprites[spriteSlot].unk_2 == 0)
            gSaXElevatorSprites[spriteSlot].unk_0++;
    }

    if (gSaXElevatorSprites[spriteSlot].unk_0 == 0 || gSaXElevatorSprites[spriteSlot].unk_0 == 1)
        return;

    switch (gSaXElevatorSprites[spriteSlot].type)
    {
        case 0:
        case 1:
            gSaXElevatorSprites[spriteSlot].animationDurationCounter++;

            if (gSaXElevatorSprites[spriteSlot].animationDurationCounter <
                sParticleOam_Explosion7[gSaXElevatorSprites[spriteSlot].currentAnimationFrame].timer)
                break;

            gSaXElevatorSprites[spriteSlot].animationDurationCounter = 0;
            gSaXElevatorSprites[spriteSlot].currentAnimationFrame++;

            if (sParticleOam_Explosion7[gSaXElevatorSprites[spriteSlot].currentAnimationFrame].timer == 0)
                gSaXElevatorSprites[spriteSlot].unk_0 = 0;
            break;

        case 2:
            gSaXElevatorSprites[spriteSlot].animationDurationCounter++;

            if (gSaXElevatorSprites[spriteSlot].animationDurationCounter <
                sParticleOam_Explosion8[gSaXElevatorSprites[spriteSlot].currentAnimationFrame].timer)
                break;

            gSaXElevatorSprites[spriteSlot].animationDurationCounter = 0;
            gSaXElevatorSprites[spriteSlot].currentAnimationFrame++;

            if (sParticleOam_Explosion8[gSaXElevatorSprites[spriteSlot].currentAnimationFrame].timer == 0)
                gSaXElevatorSprites[spriteSlot].unk_0 = 0;
            break;

        case 3:
        case 4:
        case 5:
        case 6:
            gSaXElevatorSprites[spriteSlot].yPosition -=
                VELOCITY_TO_SUB_PIXEL(gSaXElevatorSprites[spriteSlot].yVelocity);
            gSaXElevatorSprites[spriteSlot].yVelocity -= SUB_PIXEL_TO_VELOCITY(ONE_SUB_PIXEL - ONE_SUB_PIXEL / 4.f);

            if (gSaXElevatorSprites[spriteSlot].yPosition > BLOCK_SIZE * 7 + ONE_SUB_PIXEL)
                gSaXElevatorSprites[spriteSlot].unk_0 = 0;

        case 7:
        case 8:
            gSaXElevatorSprites[spriteSlot].xPosition +=
                VELOCITY_TO_SUB_PIXEL(gSaXElevatorSprites[spriteSlot].xVelocity);
            break;

        case 9:
            gSaXElevatorSprites[spriteSlot].animationDurationCounter++;

            if (gSaXElevatorSprites[spriteSlot].animationDurationCounter >=
                sSaXElevatorOam_2e8038[gSaXElevatorSprites[spriteSlot].currentAnimationFrame].timer)
            {
                gSaXElevatorSprites[spriteSlot].animationDurationCounter = 0;
                gSaXElevatorSprites[spriteSlot].currentAnimationFrame++;

                if (sSaXElevatorOam_2e8038[gSaXElevatorSprites[spriteSlot].currentAnimationFrame].timer == 0)
                    gSaXElevatorSprites[spriteSlot].currentAnimationFrame = 0;
            }

            gSaXElevatorSprites[spriteSlot].xPosition +=
                VELOCITY_TO_SUB_PIXEL(gSaXElevatorSprites[spriteSlot].xVelocity);
            break;
    }

    pOam = sSaXElevatorSpritesOamPointers[gSaXElevatorSprites[spriteSlot].type];
    pOam = &pOam[gSaXElevatorSprites[spriteSlot].currentAnimationFrame];

    gSaXElevatorSprites[spriteSlot].pOamFrame = pOam->pFrame;
}

/**
 * @brief d564 | d4 | Draws the elevator sprites
 *
 */
void SaXDrawElevatorSprites(void)
{
    s32 i;
    s32 j;
    u16 yPosition;
    u16 xPosition;
    s32 currSlot;
    s32 prevSlot;
    const u16* src;
    u16* dst;
    u16 part1;
    u16 part2;

    dst = (u16*)gOamData;
    dst = (u16*)&gOamData[gNextOamSlot];

    currSlot = gNextOamSlot;
    prevSlot = gNextOamSlot;

    for (i = 0; i < MAX_AMOUNT_OF_SA_X_ELEVATOR_SPRITES; i++)
    {
        if (gSaXElevatorSprites[i].unk_0 <= 1)
            continue;

        src = gSaXElevatorSprites[i].pOamFrame;
        currSlot += *src++;

        xPosition = SUB_PIXEL_TO_PIXEL(gSaXElevatorSprites[i].xPosition);
        yPosition = SUB_PIXEL_TO_PIXEL(gSaXElevatorSprites[i].yPosition);

        for (; prevSlot < currSlot; prevSlot++)
        {
            part1 = *src++;
            *dst++ = part1;
            gOamData[prevSlot].split.y = part1 + yPosition;

            part2 = *src++;
            *dst++ = part2;
            gOamData[prevSlot].split.x = MOD_AND(part2 + xPosition, 512);

            *dst++ = *src++;

            gOamData[prevSlot].split.priority = 0;

            dst++;
        }
    }

    gNextOamSlot = currSlot;
}

/**
 * @brief d638 | 5c | To document
 *
 */
void unk_d638(void)
{
    gSaXElevatorData.unk_0 = 1;
    gNextOamSlot = 0;

    if (sSaXElevatorFunctionPointers[gSaXElevatorData.unk_1]())
    {
        gSaXElevatorData.stage = 0;
        gSaXElevatorData.unk_3 = 0;
        gSaXElevatorData.unk_4 = 0;
        gSaXElevatorData.unk_5 = 0;
        gSaXElevatorData.timer = 0;

        gDisableDrawingSamusAndScrollingFlag = FALSE;

        gSaXData.screenFlag = SA_X_SCREEN_FLAG_NOT_PRESENT;
        gSubGameMode1 = SUB_GAME_MODE_LOADING_ROOM;
    }
}

/**
 * @brief d694 | 15c | To document
 *
 * @return u8 bool, ended
 */
u8 unk_d694(void)
{
    s32 i;
    u32 ended;
    u8 newPose;
    u8 bldalpha;
    u32 tmp;

    ended = FALSE;

    if (sSaXElevatorHandlerPointers[gSaXElevatorData.stage]())
    {
        gSaXElevatorData.stage++;
        gSaXElevatorData.timer = 0;
    }

    for (i = 0; i < MAX_AMOUNT_OF_SA_X_ELEVATOR_SPRITES - 1; i++)
        SaXUpdateElevatorSprite(i);

    switch (gSaXElevatorData.unk_4)
    {
        case 1:
            if (gWrittenToBldy < 16)
            {
                gWrittenToBldy++;
                WRITE_16(REG_BLDY, gWrittenToBldy);
            }
            break;

        case 2:
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy--;
                WRITE_16(REG_BLDY, gWrittenToBldy);
            }

            gSaXElevatorData.unk_5++;
            if (MOD_AND(gSaXElevatorData.unk_5, 8) == 0)
                gBackgroundPositions.bg[3].x--;
            break;

        case 3:
            bldalpha = gSaXElevatorData.unk_5++ / 4;
            tmp = 16 - bldalpha;
            WRITE_16(REG_BLDALPHA, C_16_2_8(16 - tmp, tmp));

            if (MOD_AND(gSaXElevatorData.unk_5, 4) == 0)
                gBackgroundPositions.bg[3].x--;

            if (tmp == 0)
            {
                gSaXElevatorData.unk_4 = 0;
                gSaXElevatorData.unk_5 = 0;

                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~(DCNT_BG0 | DCNT_BG3));
                ;
                WRITE_16(REG_BLDCNT, 0);
            }
            else if (tmp == 1)
            {
                gSaXElevatorSprites[4].unk_0 = 0;
                gSaXElevatorSprites[5].unk_0 = 0;
            }
            break;
    }

    if (gSaXElevatorData.stage >= ARRAY_SIZE(sSaXElevatorHandlerPointers))
        ended++;

    newPose = sSaXPoseGfxFunctionPointers[gSaXData.pose]();
    if (newPose != SA_X_POSE_NONE)
        SaXSetPose(newPose);

    SaXUpdatePosition();

    if (gSubGameMode1 != 0x3)
    {
        SaXDrawElevatorSprites();
        SaXUpdateGraphicsAndDraw();
    }

    return ended;
}

/**
 * @brief d7f0 | cc | Handles the before blowing up the wall part of the SA-X elevator cutscene
 *
 * @return u8 bool, ended
 */
u8 SaXElevatorBeforeBlowingUpWall(void)
{
    u8 ended;
    s32 i;

    ended = FALSE;

    switch (gSaXElevatorData.timer++)
    {
        case 0:
            DMA3_COPY_16(sSaXElevatorRocksAndCloudPal, PALRAM_OBJ + 0x120, ARRAY_SIZE(sSaXElevatorRocksAndCloudPal));
            gDisableDrawingSamusAndScrollingFlag++;
            break;

        case 1:
            DMA3_COPY_16(sSaXElevatorGraphics_RocksTop, VRAM_OBJ + 0x4A60, ARRAY_SIZE(sSaXElevatorGraphics_RocksTop) / 2);
            break;

        case 2:
            DMA3_COPY_16(sSaXElevatorGraphics_RocksBottom, VRAM_OBJ + 0x4E60, ARRAY_SIZE(sSaXElevatorGraphics_RocksBottom) / 2);
            break;

        case 3:
            for (i = 0; i < MAX_AMOUNT_OF_SA_X_ELEVATOR_SPRITES - 1; i++)
                gSaXElevatorSprites[i] = sSaXElevatorSpritesBlowingUpWall[i];

            gSaXElevatorData.timer = 0;
            ended = TRUE;
            break;
    }

    return ended;
}

/**
 * @brief d8bc | 23c | Handles the blowing up wall part of the SA-X elevator cutscene
 *
 * @return u8 bool, ended
 */
u8 SaXElevatorBlowingUpWall(void)
{
    u8 ended;

    ended = FALSE;

    switch (gSaXElevatorData.timer++)
    {
        case 1:
            gSaXElevatorBgCnt[0] = READ_16(REG_BG0CNT);
            gSaXElevatorBgCnt[1] = READ_16(REG_BG1CNT);
            gSaXElevatorBgCnt[3] = READ_16(REG_BG3CNT);

            DMA3_COPY_16(sSaXElevatorGraphics_CloudsTop, VRAM_OBJ + 0x5000, sizeof(sSaXElevatorGraphics_CloudsTop) / 2);
            break;

        case 2:
            DMA3_COPY_16(sSaXElevatorGraphics_CloudsBottom, VRAM_OBJ + 0x5400, sizeof(sSaXElevatorGraphics_CloudsBottom) / 2);
            break;

        case 3:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~(DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3));
            SET_BACKDROP_COLOR(COLOR_WHITE);
            break;

        case 9:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | (DCNT_BG1 | DCNT_BG2 | DCNT_BG3));
            SET_BACKDROP_COLOR(COLOR_BLACK);
            break;

        case 25:
            ScreenShakeStartHorizontal(60, 0x1);
            SoundPlay_3b1c(0x226);
            break;

        case 40:
            BgClipUpdateSaXElevatorCutscene(FALSE);
            break;

        case 52:
            gWrittenToBldy = 0;
            WRITE_16(REG_BLDY, 0);
            WRITE_16(REG_BLDCNT,
                BLDCNT_BG0_FIRST_TARGET_PIXEL | BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_BG2_FIRST_TARGET_PIXEL |
                    BLDCNT_BG3_FIRST_TARGET_PIXEL | BLDCNT_BACKDROP_FIRST_TARGET_PIXEL |
                    BLDCNT_BRIGHTNESS_INCREASE_EFFECT);

            gSaXElevatorData.unk_4++;
            break;

        case 100:
            WRITE_16(REG_BG0CNT, BGCNT_SET_PRIORITY(gSaXElevatorBgCnt[0], 3));
            WRITE_16(REG_BG1CNT, BGCNT_SET_PRIORITY(gSaXElevatorBgCnt[1], 1));
            WRITE_16(REG_BG3CNT, BGCNT_SET_PRIORITY(gSaXElevatorBgCnt[3], 0));

            gDisableScrolling = TRUE;

            gBackgroundPositions.bg[3].x = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE);
            gBackgroundPositions.bg[3].y = SUB_PIXEL_TO_PIXEL(BLOCK_SIZE * 2);

            gSaXElevatorSprites[4] = sSaXElevatorSpritesBlowingUpWall[10];
            gSaXElevatorSprites[5] = sSaXElevatorSpritesBlowingUpWall[11];
            break;

        case 120:
            WRITE_16(REG_BLDCNT,
                BLDCNT_BG0_FIRST_TARGET_PIXEL | BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_BG2_FIRST_TARGET_PIXEL |
                    BLDCNT_BACKDROP_FIRST_TARGET_PIXEL | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);

            gSaXElevatorSprites[4].xVelocity = -SUB_PIXEL_TO_VELOCITY(PIXEL_SIZE / 2);
            gSaXElevatorSprites[5].xVelocity = SUB_PIXEL_TO_VELOCITY(PIXEL_SIZE / 2);

            gSaXElevatorData.unk_5 = 0;
            gSaXElevatorData.unk_4++;
            break;

        case 140:
            WRITE_16(REG_BLDCNT, 0x3F48);
            WRITE_16(REG_BLDALPHA, 16);

            gSaXElevatorData.unk_5 = 0;
            gSaXElevatorData.unk_4++;
            break;

        case 160:
            gSaXData = sSaXData_Empty;

            gSaXData.screenFlag = SA_X_SCREEN_FLAG_ON_SCREEN;
            gSaXData.pose = SA_X_POSE_WALKING;

            gSaXData.xPosition = gBg1XPosition + (BLOCK_SIZE * 3 - QUARTER_BLOCK_SIZE + PIXEL_SIZE);
            gSaXData.yPosition = gBg1YPosition + BLOCK_SIZE * 7;

            gSaXData.xVelocity = SUB_PIXEL_TO_VELOCITY(ONE_SUB_PIXEL + ONE_SUB_PIXEL / 2.f);

            gSaXElevatorData.timer = 0;
            ended = TRUE;
            break;
    }

    return ended;
}

/**
 * @brief daf8 | 5c | Handles the SA-X walking part of the SA-X elevator cutscene
 *
 * @return u8 bool, ended
 */
u8 SaXElevatorWalkingBeforeTurningToCamera(void)
{
    u8 ended;

    ended = FALSE;

    switch (gSaXData.pose)
    {
        case SA_X_POSE_WALKING:
            if (gSaXData.xPosition >= gBg1XPosition + (BLOCK_SIZE * 5 + HALF_BLOCK_SIZE - PIXEL_SIZE / 2))
                SaXSetPose(SA_X_POSE_STANDING);
            break;

        case SA_X_POSE_STANDING:
            if (gSaXElevatorData.timer++ >= 30)
            {
                SaXSetPose(SA_X_POSE_TURNING_TOWARDS_CAMERA);
                gSaXElevatorData.timer = 0;
                ended = TRUE;
            }
            break;
    }

    return ended;
}

/**
 * @brief db54 | 40 | Handles the SA-X waiting to jump part of the SA-X elevator cutscene
 *
 * @return u8 bool, ended
 */
u8 SaXElevatorBeforeJumping(void)
{
    u8 ended;

    ended = FALSE;

    switch (gSaXData.pose)
    {
        case SA_X_POSE_STANDING:
            if (gSaXElevatorData.timer++ >= 60)
            {
                SaXSetPose(SA_X_POSE_MID_AIR);

                gSaXData.xVelocity = SUB_PIXEL_TO_VELOCITY(PIXEL_SIZE + PIXEL_SIZE / 2);
                gSaXData.yVelocity = SUB_PIXEL_TO_VELOCITY(QUARTER_BLOCK_SIZE);

                gSaXElevatorData.timer = 0;
                ended = TRUE;
            }
            break;
    }

    return ended;
}

u8 SaXElevatorBeforeShootingDoor(void)
{
    // https://decomp.me/scratch/LIK2p

    s32 ended;
    s32 i;

    ended = FALSE;

    if (gSaXData.pose == SA_X_POSE_MID_AIR)
    {
        if (gSaXData.yPosition > gBg1YPosition + (BLOCK_SIZE * 7))
        {
            SaXSetPose(SA_X_POSE_LANDING);
            gSaXData.yPosition = gBg1YPosition + (BLOCK_SIZE * 7);
        }
    }
    else
    {
        gSaXElevatorData.timer++;
    }

    switch (gSaXElevatorData.timer)
    {
        case 30:
            gSaXData.missilesArmed = TRUE;
            SoundPlay(0x228);
            break;

        case 68:
            SaXSetPose(SA_X_POSE_SHOOTING);

            gSaXElevatorSprites[0] = sSaXElevatorSpritesBlowingUpWall[12];
            gSaXElevatorSprites[0].xPosition = gSaXData.xPosition + BLOCK_SIZE - gBg1XPosition;
            gSaXElevatorSprites[0].yPosition =
                gSaXData.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2) - gBg1YPosition;
            break;

        case 80:
            for (i = 0; i < 7; i++)
                gSaXElevatorSprites[i] = sSaXElevatorSpritesShootingDoor[i];

            gSaXElevatorData.timer = 0;
            ended++;
            break;
    }

    return ended;
}

/**
 * @brief dc94 | 90 | Handles the SA-X walking out part of the SA-X elevator cutscene
 *
 * @return u8 bool, ended
 */
u8 SaXElevatorWalkingOut(void)
{
    s32 ended;

    ended = FALSE;

    switch (gSaXElevatorData.timer++)
    {
        case 5:
            ScreenShakeStartHorizontal(60, 1);
            SoundPlay_3b1c(0x227);
            break;

        case 35:
            BgClipUpdateSaXElevatorCutscene(TRUE);
            break;

        case 50:
            gSaXData.missilesArmed = FALSE;
            break;

        case 100:
            SaXSetPose(SA_X_POSE_WALKING);
            gSaXData.xVelocity = SUB_PIXEL_TO_VELOCITY(PIXEL_SIZE / 2 + ONE_SUB_PIXEL / 2.f);
            break;
    }

    if (gSaXData.pose == SA_X_POSE_WALKING)
    {
        if (gSaXData.xPosition > gBg1XPosition + (BLOCK_SIZE * 15))
            ended++;
    }

    return ended;
}
