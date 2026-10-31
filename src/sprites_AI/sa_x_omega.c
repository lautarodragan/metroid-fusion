#include "sprites_AI/sa_x_omega.h"
#include "sprites_AI/sa_x.h"
#include "macros.h"
#include "globals.h"
#include "sprite_util.h"

#include "data/sprite_data.h"
#include "data/sprites/x_parasite.h"
#include "data/sprites/sa_x.h"

#include "constants/clipdata.h"
#include "constants/event.h"
#include "constants/sprite.h"
#include "constants/samus.h"
#include "constants/sa_x.h"

#include "structs/sprite.h"
#include "structs/samus.h"
#include "structs/sa_x.h"

#define SA_X_OMEGA_MOSAIC_IDX work1 // Forming from and reverting to the X
#define SA_X_OMEGA_RUN_TIMER work4 // After shooting the omega

/**
 * @brief 1b518 | 4c | Initializes the SA-X (omega) sprite
 * 
 */
void SaXOmegaInit(void)
{
    SaXInit();
    SpriteUtilMakeSpriteFaceAwayFromSamusDirection();
    SaXSetDirection();

    gCurrentSprite.health = 0;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.SA_X_LANDED = 0;

    gCurrentSprite.pose = SPRITE_POSE_SPAWNING_FROM_X;
    gCurrentSprite.SA_X_OMEGA_MOSAIC_IDX = X_PARASITE_MOSAIC_MAX_INDEX;
    gCurrentSprite.yPosition += (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_FALLING);
    gSaXData.mosaic = TRUE;
}

/**
 * @brief 1b564 | 54 | Handles the SA-X (omega) forming
 * 
 */
void SaXOmegaForming(void)
{
    gCurrentSprite.SA_X_OMEGA_MOSAIC_IDX--;

    if (gCurrentSprite.SA_X_OMEGA_MOSAIC_IDX != 0)
    {
        gWrittenToMosaic_H = sXParasiteMosaicValues[gCurrentSprite.SA_X_OMEGA_MOSAIC_IDX];
        return;
    }

    gCurrentSprite.pose = SPRITE_POSE_FALLING;
    gCurrentSprite.SA_X_Y_SPEED_IDX = 0;
    gSaXData.mosaic = FALSE;
}

/**
 * @brief 1b5b8 | 90 | Handles the SA-X (omega) falling
 * 
 */
void SaXOmegaFalling(void)
{
    u32 blockTop;
    u8 offset;
    s16 movement;

    if (gCurrentSprite.SA_X_LANDED)
    {
        if (gSaXData.pose == SA_X_POSE_STANDING)
            gCurrentSprite.pose = SA_X_OMEGA_POSE_STANDING_INIT;

        return;
    }

    blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition, gCurrentSprite.xPosition);

    if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
    {
        gCurrentSprite.yPosition = blockTop;
        gCurrentSprite.SA_X_LANDED = TRUE;
        SaXSetPose(SA_X_POSE_LANDING);
        return;
    }

    offset = gCurrentSprite.SA_X_Y_SPEED_IDX;
    movement = sSpritesFallingSpeed[offset];

    if (movement == SHORT_MAX)
    {
        movement = sSpritesFallingSpeed[offset - 1];
        gCurrentSprite.yPosition += movement;
    }
    else
    {
        gCurrentSprite.SA_X_Y_SPEED_IDX++;
        gCurrentSprite.yPosition += movement;
    }
}

/**
 * @brief 1b648 | 18 | Initializes the SA-X (omega) to be standing
 * 
 */
void SaXOmegaStandingInit(void)
{
    gCurrentSprite.pose = SA_X_OMEGA_POSE_STANDING;
    gCurrentSprite.SA_X_TIMER = 24;
}

/**
 * @brief 1b660 | 24 | Handles the SA-X (omega) standing
 * 
 */
void SaXOmegaStanding(void)
{
    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER == 0)
        gCurrentSprite.pose = SA_X_OMEGA_POSE_RUNNING_INIT;
}

/**
 * @brief 1b684 | 2c | Initializes the SA-X (omega) to be running
 * 
 */
void SaXOmegaRunningInit(void)
{
    gCurrentSprite.pose = SA_X_OMEGA_POSE_RUNNING;
    gCurrentSprite.SA_X_X_SPEED_IDX = 0;

    SaXSetPose(SA_X_POSE_RUNNING);

    gCurrentSprite.SA_X_TIMER = 30;
}

/**
 * @brief 1b6b0 | 48 | Handles the SA-X (omega) running
 * 
 */
void SaXOmegaRunning(void)
{
    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXRunningSpeed[gCurrentSprite.SA_X_X_SPEED_IDX / 8]);

    if (gCurrentSprite.SA_X_X_SPEED_IDX < ARRAY_SIZE(sSaXRunningSpeed) * 8 - 1)
        gCurrentSprite.SA_X_X_SPEED_IDX++;

    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER == 0)
        gCurrentSprite.pose = SA_X_OMEGA_POSE_DELAY_BEFORE_SHOOTING_OMEGA_INIT;
}

/**
 * @brief 1b6f8 | 2c | Initializes the SA-X (omega) to have a delay before shooting at the omega
 * 
 */
void SaXOmegaDelayBeforeShootingOmegaInit(void)
{
    gCurrentSprite.pose = SA_X_OMEGA_POSE_DELAY_BEFORE_SHOOTING_OMEGA;
    gCurrentSprite.SA_X_TIMER = 16;
    gSaXData.diagonalAim = DIAG_AIM_UP;

    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 1b724 | 24 | Handles the SA-X (omega) having a delay before shooting the omega
 * 
 */
void SaXOmegaDelayBeforeShootingOmega(void)
{
    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER == 0)
        gCurrentSprite.pose = SA_X_OMEGA_POSE_SHOOTING_OMEGA_INIT;
}

/**
 * @brief 1b748 | 50 | Initializes the SA-X (omega) to be shooting at the omega
 * 
 */
void SaXOmegaShootingOmegaInit(void)
{
    gCurrentSprite.pose = SA_X_OMEGA_POSE_SHOOTING_OMEGA;

    SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_UP, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
        gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition + (BLOCK_SIZE + PIXEL_SIZE), SPRITE_STATUS_X_FLIP);

    gSaXData.missilesArmed = FALSE;
    SaXSetPose(SA_X_POSE_SHOOTING);
}

/**
 * @brief 1b798 | 20 | Handles the SA-X (omega) shooting the omega
 * 
 */
void SaXOmegaShootingOmega(void)
{
    if (gSaXData.pose == SA_X_POSE_STANDING)
        gCurrentSprite.pose = SA_X_OMEGA_POSE_AFTER_SHOOTING_OMEGA_INIT;
}

/**
 * @brief 1b7b8 | 30 | Initializes the SA-X (omega) after shooting the omega
 * 
 */
void SaXOmegaAfterShootingOmegaInit(void)
{
    gCurrentSprite.pose = SA_X_OMEGA_POSE_AFTER_SHOOTING_OMEGA;
    gCurrentSprite.SA_X_TIMER = 50;
    gCurrentSprite.SA_X_OMEGA_RUN_TIMER = 0;

    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 1b7e8 | d4 | Handles the SA-X (omega) after shooting the omega
 * 
 */
void SaXOmegaAfterShootingOmega(void)
{
    switch (gCurrentSprite.SA_X_OMEGA_RUN_TIMER)
    {
        case 26:
            if (gSaXData.pose == SA_X_POSE_STANDING)
            {
                gSaXData.diagonalAim = SSC_NONE;
                SaXSetPose(SA_X_POSE_RUNNING);
                gCurrentSprite.SA_X_X_SPEED_IDX = 0;
                gCurrentSprite.SA_X_OMEGA_RUN_TIMER--;
            }
            break;

        default:
            SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXRunningSpeed[gCurrentSprite.SA_X_X_SPEED_IDX / 8]);

            if (gCurrentSprite.SA_X_X_SPEED_IDX < ARRAY_SIZE(sSaXRunningSpeed) * 8 - 1)
                gCurrentSprite.SA_X_X_SPEED_IDX++;

            gCurrentSprite.SA_X_OMEGA_RUN_TIMER--;
            if (gCurrentSprite.SA_X_OMEGA_RUN_TIMER == 0)
            {
                gCurrentSprite.SA_X_TIMER = 0x7;
                gSaXData.diagonalAim = DIAG_AIM_UP;
                SaXSetPose(SA_X_POSE_STANDING);
            }
            break;

        case 0: 
            gCurrentSprite.SA_X_TIMER--;
            if (gCurrentSprite.SA_X_TIMER == 0)
            {
                gCurrentSprite.SA_X_TIMER = 40;

                SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_UP, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                    gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition + (BLOCK_SIZE + PIXEL_SIZE), SPRITE_STATUS_X_FLIP);

                gSaXData.missilesArmed = FALSE;
                SaXSetPose(SA_X_POSE_SHOOTING);
            }
            break;
    }
}

/**
 * @brief 1b8bc | 28 | Initializes the SA-X (omega) to be hit by the omega
 * 
 */
void SaXOmegaHitByOmegaInit(void)
{
    gCurrentSprite.pose = SA_X_OMEGA_POSE_HIT_BY_OMEGA;
    gCurrentSprite.SA_X_TIMER = 0;
    gCurrentSprite.SA_X_Y_SPEED_IDX = 0;

    SaXSetPose(SA_X_POSE_GETTING_HURT);
}

/**
 * @brief 1b8e4 | 4c | Handles the SA-X (omega) getting hit by the omega
 * 
 */
void SaXOmegaHitByOmega(void)
{
    u8 offset;
    s16 movement;

    offset = gCurrentSprite.SA_X_Y_SPEED_IDX;
    movement = sSaXBossKnockbackYMovement[offset];

    if (movement == SHORT_MAX)
    {
        gCurrentSprite.pose = SA_X_OMEGA_POSE_REVERTING_TO_X_INIT;
    }
    else
    {
        gCurrentSprite.SA_X_Y_SPEED_IDX++;
        gCurrentSprite.yPosition += movement;
    }

    gCurrentSprite.xPosition -= QUARTER_BLOCK_SIZE;
}

/**
 * @brief 1b930 | 2c | Initializes the SA-X (omega) to be reverting to an X
 * 
 */
void SaXOmegaRevertingToXInit(void)
{
    gCurrentSprite.pose = SA_X_OMEGA_POSE_REVERTING_TO_X;
    gCurrentSprite.SA_X_OMEGA_MOSAIC_IDX = X_PARASITE_MOSAIC_MAX_INDEX;
    gSaXData.mosaic = TRUE;

    EventCheckAdvance(EVENT_SA_X_KILLED_BY_OMEGA_METROID);
}

/**
 * @brief 1b95c | 44 | Handles the SA-X (omega) reverting to an X
 * 
 */
void SaXOmegaRevertingToX(void)
{
    gWrittenToMosaic_H = sXParasiteMosaicValues[gCurrentSprite.SA_X_OMEGA_MOSAIC_IDX];
    gCurrentSprite.SA_X_OMEGA_MOSAIC_IDX--;

    if (gCurrentSprite.SA_X_OMEGA_MOSAIC_IDX == 0)
    {
        gCurrentSprite.pose = SPRITE_POSE_SPAWNING_FROM_X_INIT;
        gCurrentSprite.spriteId = PSPRITE_ICE_BEAM_ABILITY;
    }
}

/**
 * @brief 1b9a0 | 1f8 | SA-X (omega) AI
 * 
 */
void SaXOmega(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_SPAWNING_FROM_X_INIT:
            SaXOmegaInit();
            break;

        case SPRITE_POSE_SPAWNING_FROM_X:
            SaXOmegaForming();
            break;

        case SPRITE_POSE_FALLING_INIT:
            SaXFallingInit();

        case SPRITE_POSE_FALLING:
            SaXOmegaFalling();
            break;

        case SA_X_OMEGA_POSE_STANDING_INIT:
            SaXOmegaStandingInit();

        case SA_X_OMEGA_POSE_STANDING:
            SaXOmegaStanding();
            break;

        case SA_X_OMEGA_POSE_RUNNING_INIT:
            SaXOmegaRunningInit();

        case SA_X_OMEGA_POSE_RUNNING:
            SaXOmegaRunning();
            break;

        case SA_X_OMEGA_POSE_DELAY_BEFORE_SHOOTING_OMEGA_INIT:
            SaXOmegaDelayBeforeShootingOmegaInit();

        case SA_X_OMEGA_POSE_DELAY_BEFORE_SHOOTING_OMEGA:
            SaXOmegaDelayBeforeShootingOmega();
            break;

        case SA_X_OMEGA_POSE_SHOOTING_OMEGA_INIT:
            SaXOmegaShootingOmegaInit();

        case SA_X_OMEGA_POSE_SHOOTING_OMEGA:
            SaXOmegaShootingOmega();
            break;

        case SA_X_OMEGA_POSE_AFTER_SHOOTING_OMEGA_INIT:
            SaXOmegaAfterShootingOmegaInit();

        case SA_X_OMEGA_POSE_AFTER_SHOOTING_OMEGA:
            SaXOmegaAfterShootingOmega();
            break;

        case SA_X_OMEGA_POSE_HIT_BY_OMEGA_INIT:
            SaXOmegaHitByOmegaInit();

        case SA_X_OMEGA_POSE_HIT_BY_OMEGA:
            SaXOmegaHitByOmega();
            break;

        case SA_X_OMEGA_POSE_REVERTING_TO_X_INIT:
            SaXOmegaRevertingToXInit();

        case SA_X_OMEGA_POSE_REVERTING_TO_X:
            SaXOmegaRevertingToX();
    }

    if (gCurrentSprite.spriteId == PSPRITE_ICE_BEAM_ABILITY)
    {
        gSaXData.screenFlag = SA_X_SCREEN_FLAG_NOT_PRESENT;
        gSaXData.mosaic = FALSE;
    }
    else
    {
        SaXUpdateGraphics();
    }
}
