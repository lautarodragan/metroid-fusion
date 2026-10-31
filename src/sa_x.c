#include "sa_x.h"

#include "globals.h"
#include "macros.h"

#include "data/particle_data.h"
#include "data/sprites/sa_x.h"

#include "constants/audio.h"
#include "constants/samus.h"

#include "structs/samus.h"
#include "structs/scroll.h"

/**
 * @brief cbb8 | 64 | SA-X running gfx handler
 *
 * @return u8 New pose
 */
u8 SaXRunningGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_Running_Left[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (gSaXData.screenFlag != SA_X_SCREEN_FLAG_NOT_PRESENT &&
        (gSaXData.currentAnimationFrame == 4 || gSaXData.currentAnimationFrame == 9))
        SoundPlay(SOUND_SA_X_RUN_FOOTSTEP);

    if (sSaXAnim_Running_Left[gSaXData.currentAnimationFrame].timer == 0)
        gSaXData.currentAnimationFrame = 0;

    return SA_X_POSE_NONE;
}

/**
 * @brief cc1c | 60 | SA-X walking gfx handler
 *
 * @return u8 New pose
 */
u8 SaXWalkingGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_Walking_Left[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (gSaXData.screenFlag != SA_X_SCREEN_FLAG_NOT_PRESENT &&
        (gSaXData.currentAnimationFrame == 1 || gSaXData.currentAnimationFrame == 6))
        SoundPlay(SOUND_SA_X_WALK_FOOTSTEP);

    if (sSaXAnim_Walking_Left[gSaXData.currentAnimationFrame].timer == 0)
        gSaXData.currentAnimationFrame = 0;

    return SA_X_POSE_NONE;
}

/**
 * @brief cc7c | 44 | SA-X standing gfx handler
 *
 * @return u8 New pose
 */
u8 SaXStandingGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_Standing_Left[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_Standing_Left[gSaXData.currentAnimationFrame].timer == 0)
        gSaXData.currentAnimationFrame = 0;

    return SA_X_POSE_NONE;
}

/**
 * @brief ccc0 | 48 | SA-X shooting gfx handler
 *
 * @return u8 New pose
 */
u8 SaXShootingGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_Shooting_Left[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_Shooting_Left[gSaXData.currentAnimationFrame].timer != 0)
        return SA_X_POSE_NONE;

    return SA_X_POSE_STANDING;
}

/**
 * @brief cd08 | 48 | SA-X turning gfx handler
 *
 * @return u8 New pose
 */
u8 SaXTurningGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_Turning_Right[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_Turning_Right[gSaXData.currentAnimationFrame].timer != 0)
        return SA_X_POSE_NONE;

    return SA_X_POSE_STANDING;
}

/**
 * @brief cd50 | 4c | SA-X mid air gfx handler
 *
 * @return u8 New pose
 */
u8 SaXMidAirGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_MidAir_Left[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_MidAir_Left[gSaXData.currentAnimationFrame].timer == 0)
    {
        gSaXData.currentAnimationFrame = 0;
        SoundPlay(SOUND_SA_X_SCREW_ATTACK);
    }

    return SA_X_POSE_NONE;
}

/**
 * @brief cd9c | 48 | SA-X landing gfx handler
 *
 * @return u8 New pose
 */
u8 SaXLandingGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_Landing_Right[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_Landing_Right[gSaXData.currentAnimationFrame].timer != 0)
        return SA_X_POSE_NONE;

    return SA_X_POSE_STANDING;
}

/**
 * @brief cde4 | 44 | SA-X shooting restricted laboratory gfx handler
 *
 * @return u8 New pose
 */
u8 SaXShootingRestrictedLaboratoryGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_ShootingRestrictedLaboratory[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_ShootingRestrictedLaboratory[gSaXData.currentAnimationFrame].timer == 0)
        gSaXData.currentAnimationFrame = 0;

    return SA_X_POSE_NONE;
}

/**
 * @brief ce28 | 44 | SA-X covered by metroids gfx handler
 *
 * @return u8 New pose
 */
u8 SaXCoveredByMetroidsGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_CoveredByMetroids[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_CoveredByMetroids[gSaXData.currentAnimationFrame].timer == 0)
        gSaXData.currentAnimationFrame = 0;

    return SA_X_POSE_NONE;
}

/**
 * @brief ce6c | 50 | SA-X kneeling gfx handler
 *
 * @return u8 New pose
 */
u8 SaXKneelingGfx(void)
{
    if (gSaXData.animationDurationCounter == 1 && gSaXData.currentAnimationFrame == 0)
        SoundPlay(0x9D);

    if (gSaXData.animationDurationCounter < sSaXAnim_Kneeling_Right[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_Kneeling_Right[gSaXData.currentAnimationFrame].timer == 0)
        gSaXData.currentAnimationFrame = 0;

    return SA_X_POSE_NONE;
}

/**
 * @brief cebc | 44 | SA-X transforming into monster gfx handler
 *
 * @return u8 New pose
 */
u8 SaXTransformingIntoMonsterGfx(void)
{
    if (gSaXData.animationDurationCounter <
        sSaXAnim_TransformingIntoMonster_Right[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_TransformingIntoMonster_Right[gSaXData.currentAnimationFrame].timer == 0)
        gSaXData.currentAnimationFrame--;

    return SA_X_POSE_NONE;
}

/**
 * @brief cf00 | 50 | SA-X morphing gfx handler
 *
 * @return u8 New pose
 */
u8 SaXMorphingGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_Morphing_Left[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_Morphing_Left[gSaXData.currentAnimationFrame].timer != 0)
        return SA_X_POSE_NONE;

    SoundPlay(SOUND_SA_X_MORPH);
    return SA_X_POSE_MORPH_BALL;
}

/**
 * @brief cf50 | 50 | SA-X unmorphing gfx handler
 *
 * @return u8 New pose
 */
u8 SaXUnmorphingGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_Unmorphing_Left[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_Unmorphing_Left[gSaXData.currentAnimationFrame].timer != 0)
        return SA_X_POSE_NONE;

    return SA_X_POSE_STANDING;
}

/**
 * @brief cf98 | 44 | SA-X morph ball gfx handler
 *
 * @return u8 New pose
 */
u8 SaXMorphBallGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_MorphBall_Left[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_MorphBall_Left[gSaXData.currentAnimationFrame].timer == 0)
        gSaXData.currentAnimationFrame = 0;

    return SA_X_POSE_NONE;
}

/**
 * @brief cfdc | 44 | SA-X swag walk gfx handler
 *
 * @return u8 New pose
 */
u8 SaXSwagWalkGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_SwagWalk_Left[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_SwagWalk_Left[gSaXData.currentAnimationFrame].timer == 0)
        gSaXData.currentAnimationFrame = 0;

    return SA_X_POSE_NONE;
}

/**
 * @brief d020 | 5d | SA-X turning towards camera gfx handler
 *
 * @return u8 New pose
 */
u8 SaXTurningTowardsCameraGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_TurningTowardsCamera[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_TurningTowardsCamera[gSaXData.currentAnimationFrame].timer != 0)
        return SA_X_POSE_NONE;

    gPauseScreenFlag = 0x6;
    gSubGameMode1 = 0x3;
    return SA_X_POSE_TURNING_AWAY_FROM_CAMERA;
}

/**
 * @brief d07c | 48 | SA-X turning away from camera gfx handler
 *
 * @return u8 New pose
 */
u8 SaXTurningAwayFromCameraGfx(void)
{
    if (gSaXData.animationDurationCounter < sSaXAnim_TurningAwayFromCamera[gSaXData.currentAnimationFrame].timer)
        return SA_X_POSE_NONE;

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame++;

    if (sSaXAnim_TurningAwayFromCamera[gSaXData.currentAnimationFrame].timer != 0)
        return SA_X_POSE_NONE;

    return SA_X_POSE_STANDING;
}

/**
 * @brief d0c4 | ac | Sets the SA-X pose
 *
 * @param pose Pose
 */
void SaXSetPose(u8 pose)
{
    if (gSaXData.turning)
    {
        gSaXData.direction ^= (KEY_RIGHT | KEY_LEFT);
        gSaXData.turning = FALSE;
    }

    gSaXData.xVelocity = 0;
    gSaXData.yVelocity = 0;
    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame = 0;

    switch (pose)
    {
        case SA_X_POSE_TURNING:
            gSaXData.turning = TRUE;
            break;

        case SA_X_POSE_MID_AIR:
            SoundPlay(SOUND_SA_X_SCREW_ATTACK);
            gSaXData.diagonalAim = DIAG_AIM_NONE;
            break;

        case SA_X_POSE_LANDING:
            SoundPlay(SOUND_SA_X_LAND);
            gSaXData.diagonalAim = DIAG_AIM_NONE;
            break;

        case SA_X_POSE_TRANSFORMING_INTO_MONSTER:
            SoundPlay_3b1c(0x9E);
            gSaXData.diagonalAim = DIAG_AIM_NONE;
            break;

        case SA_X_POSE_STANDING:
        case SA_X_POSE_SHOOTING:
            break;

        default:
            gSaXData.diagonalAim = DIAG_AIM_NONE;
            break;
    }

    gSaXData.pose = pose;
}

/**
 * @brief d170 | 50 | Updates the position of the SA-X (applies the velocity)
 *
 */
void SaXUpdatePosition(void)
{
    s16 yVelocity;
    s16 xVelocity;

    if (gSaXData.pose == SA_X_POSE_MID_AIR)
    {
        if (gSaXData.yVelocity < -SUB_PIXEL_TO_VELOCITY(QUARTER_BLOCK_SIZE))
            yVelocity = SUB_PIXEL_TO_VELOCITY(-PIXEL_SIZE / 2);
        else
            yVelocity = VELOCITY_TO_SUB_PIXEL(gSaXData.yVelocity);

        gSaXData.yVelocity -= SUB_PIXEL_TO_VELOCITY(ONE_SUB_PIXEL - ONE_SUB_PIXEL / 4.f);
        gSaXData.yPosition -= yVelocity;
    }

    xVelocity = VELOCITY_TO_SUB_PIXEL(gSaXData.xVelocity);
    ;
    gSaXData.xPosition += xVelocity;
}

/**
 * @brief d1c0 | 234 | Updates the graphics of the SA-X and draws it
 *
 */
void SaXUpdateGraphicsAndDraw(void)
{
    s32 direction;
    const struct SaXAnimationData* pAnim;
    const u8* pGfx;
    const u16* pPalette;
    s32 priority;
    s32 yPosition;
    s32 xPosition;
    s32 currSlot;
    s32 prevSlot;
    const u16* src;
    u16* dst;
    u16 part1;
    u16 part2;

    gSaXData.animationDurationCounter++;

    if (gSaXData.screenFlag == SA_X_SCREEN_FLAG_NOT_PRESENT || gSaXData.screenFlag == SA_X_SCREEN_FLAG_OFF_SCREEN)
        return;

    if (gSaXData.direction & KEY_RIGHT)
        direction = FALSE;
    else
        direction = TRUE;

    switch (gSaXData.pose)
    {
        case SA_X_POSE_STANDING:
            if (gSaXData.missilesArmed)
                pAnim = sSaXOamDataPointers_Standing_Armed[gSaXData.diagonalAim][direction];
            else
                pAnim = sSaXOamDataPointers_Standing[gSaXData.diagonalAim][direction];
            break;

        case SA_X_POSE_SHOOTING:
            if (gSaXData.missilesArmed)
                pAnim = sSaXOamDataPointers_Shooting_Armed[gSaXData.diagonalAim][direction];
            else
                pAnim = sSaXOamDataPointers_Shooting[gSaXData.diagonalAim][direction];
            break;

        case SA_X_POSE_TURNING:
            pAnim = sSaXOamDataPointers_Turning[gSaXData.diagonalAim][direction];
            break;

        default:
            pAnim = sSaXOamDataPointers[gSaXData.pose][direction];
            break;
    }

    pAnim = &pAnim[gSaXData.currentAnimationFrame];

    gSaXData.pOamFrame = pAnim->pOamFrame;

    pGfx = pAnim->pGraphics;

    gSaXData.topGfxLength = *pGfx++ * 32;
    gSaXData.bottomGfxLength = *pGfx++ * 32;
    gSaXData.pTopGfx = pGfx;
    gSaXData.pBottomGfx = gSaXData.pTopGfx + gSaXData.topGfxLength;

    if (gSaXData.pose == SA_X_POSE_MID_AIR)
    {
        pPalette = &sSaXPalette_MidAir[MOD_AND(gSaXData.currentAnimationFrame, 4) * 16];
    }
    else if (gSaXData.pose == SA_X_POSE_TRANSFORMING_INTO_MONSTER)
    {
        switch (gSaXData.currentAnimationFrame)
        {
            case 24:
            case 26:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
                pPalette = sSaXPalette_TransformingIntoMonster;
                break;

            default:
                pPalette = sSaXPalette_Default;
                break;
        }
    }
    else
    {
        pPalette = sSaXPalette_Default;
    }

    SamusSetPalette(pPalette, 0, 16, TRUE);

    priority = 2;
    if (gSamusOnTopOfBackgrounds)
        priority = 1;

    if (gSaXData.pose == SA_X_POSE_TRANSFORMING_INTO_MONSTER)
        priority = gIoRegisters.bg1Cnt & 3;

    dst = (u16*)gOamData;
    dst = (u16*)&gOamData[gNextOamSlot];

    currSlot = gNextOamSlot;
    prevSlot = gNextOamSlot;

    xPosition = SUB_PIXEL_TO_PIXEL(gSaXData.xPosition) - SUB_PIXEL_TO_PIXEL(gBg1XPosition);
    yPosition = SUB_PIXEL_TO_PIXEL(gSaXData.yPosition) - SUB_PIXEL_TO_PIXEL(gBg1YPosition) +
        SUB_PIXEL_TO_PIXEL(QUARTER_BLOCK_SIZE / 2);

    src = gSaXData.pOamFrame;
    currSlot += *src++;

    for (; prevSlot < currSlot; prevSlot++)
    {
        part1 = *src++;
        *dst++ = part1;
        gOamData[prevSlot].split.y = part1 + yPosition;
        gOamData[prevSlot].split.mosaic = gSaXData.mosaic;

        part2 = *src++;
        *dst++ = part2;
        gOamData[prevSlot].split.x = MOD_AND(part2 + xPosition, 512);

        *dst++ = *src++;

        gOamData[prevSlot].split.paletteNum += gSaXData.paletteRow;
        gOamData[prevSlot].split.priority = priority;

        dst++;
    }

    gNextOamSlot = currSlot;
}
