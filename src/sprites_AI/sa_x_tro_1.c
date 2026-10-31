#include "sprites_AI/sa_x_tro_1.h"
#include "sprites_AI/sa_x.h"
#include "macros.h"

#include "data/sprites/sa_x.h"

#include "constants/audio.h"
#include "constants/clipdata.h"
#include "constants/sprite.h"
#include "constants/samus.h"
#include "constants/sa_x.h"

#include "structs/sprite.h"
#include "structs/sa_x.h"

/**
 * @brief 17f50 | 68 | Checks for the blocks in front of the SA-X (tro 1)
 * 
 */
void SaXTro1CheckBlockInFront(void)
{
    gCurrentSprite.work2 = DIAG_AIM_NONE;

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
            gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
            gCurrentSprite.xPosition - (BLOCK_SIZE * 4));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
            gCurrentSprite.pose = SA_X_SPRITE_POSE_IDLE_BEFORE_SHOOTING_DOOR_INIT;
    }
}

/**
 * @brief 17fb8 | 50 | Checks if the SA-X (tro 1) should start the chase
 * 
 */
void SaXTro1CheckBlockInFrontChase(void)
{
    gCurrentSprite.work2 = DIAG_AIM_NONE;

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
            gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
            gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
    }
}

/**
 * @brief 18008 | 30 | Initializes the SA-X (tro 1)
 * 
 */
void SaXTro1Init(void)
{
    if (!EventCheckOn_HighJumpRecovered())
    {
        gCurrentSprite.status = 0;
        return;
    }

    SaXInit();
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    SoundEventUpdateForSaXEncounter();
}

/**
 * @brief 18038 | f4 | Handles the SA-X (tro 1) walking
 * 
 */
void SaXTro1Walking(void)
{
    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (gSaXVision.inYRange == TRUE)
        {
            gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
            gCurrentSprite.workY = 0;

            if (gSaXVision.detectedSamusOnRight == TRUE)
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            else
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;

            return;
        }
        
        if (SPRITE_GET_ISFT(gCurrentSprite))
        {
            gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
            gCurrentSprite.workY = 0;

            if (gSaXVision.samusOnRight == FALSE)
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            else
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;

            return;
        }
    }
    else
    {
        if (gSaXVision.inYRange == TRUE)
        {
            gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
            gCurrentSprite.workY = 0;

            if (gSaXVision.detectedSamusOnRight == FALSE)
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            else
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;

            return;
        }
        
        if (SPRITE_GET_ISFT(gCurrentSprite))
        {
            gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
            gCurrentSprite.workY = 0;

            if (gSaXVision.samusOnRight == TRUE)
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            else
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;

            return;
        }
    }

    SaXTro1CheckBlockInFront();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_WALKING)
        return;

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXWalkingSpeed[gCurrentSprite.work3 / 8]);

    if (gCurrentSprite.work3 < ARRAY_SIZE(sSaXWalkingSpeed) * 8 - 1)
        gCurrentSprite.work3++;
}

/**
 * @brief 1812c | e4 | Handles the SA-X (tro 1) running
 * 
 */
void SaXTro1Running(void)
{
    u32 nslr;

    if (gSaXVision.inYRange == TRUE)
    {
        nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 7 + HALF_BLOCK_SIZE,
            BLOCK_SIZE * 5 + QUARTER_BLOCK_SIZE + PIXEL_SIZE);

        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (nslr == NSLR_RIGHT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
                gCurrentSprite.work2 = gSaXVision.diagonalAim;
                return;
            }
        }
        else
        {
            if (nslr == NSLR_LEFT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
                gCurrentSprite.work2 = gSaXVision.diagonalAim;
                return;
            }
        }

        nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 4, BLOCK_SIZE * 10);

        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (nslr == NSLR_LEFT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return;
            }
        }
        else
        {
            if (nslr == NSLR_RIGHT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return;
            }
        }
    }
    else
    {
        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (gSaXVision.samusOnRight == FALSE && gSaXVision.inXRange)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return;
            }
        }
        else
        {
            if (gSaXVision.samusOnRight == TRUE && gSaXVision.inXRange)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return;
            }
        }
    }

    SaXTro1CheckBlockInFrontChase();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_RUNNING)
        return;

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXRunningSpeed[gCurrentSprite.work3 / 8]);

    if (gCurrentSprite.work3 < ARRAY_SIZE(sSaXRunningSpeed) * 8 - 1)
        gCurrentSprite.work3++;
}

/**
 * @brief 18210 | 54 | Handles the SA-X (tro 1) turning around (chase start)
 * 
 */
void SaXTro1TurningAroundChase(void)
{
    if (gSaXData.pose == SA_X_POSE_STANDING)
    {
        gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
        SaXSetDirection();

        if (gSaXVision.inYRange == TRUE)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        }
        else
        {
            gCurrentSprite.status &= ~SPRITE_STATUS_SAMUS_DETECTED;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_STANDING_INIT;
        }
    }
}

/**
 * @brief 18264 | 27c | SA-X (tro 1) AI
 * 
 */
void SaXTro1(void)
{
    if (SaXUpdateFreezeTimer())
        return;

    SaXSeeAndLocateSamus();

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
    {
        if (gSaXVision.inYRange == TRUE)
        {
            gCurrentSprite.workY = 0;
        }
        else
        {
            if (gCurrentSprite.workY >= 60 * 20)
            {
                gCurrentSprite.status &= ~SPRITE_STATUS_SAMUS_DETECTED;
            }
            else
            {
                if (gCurrentSprite.status & SPRITE_STATUS_ONSCREEN)
                    gCurrentSprite.workY += 4;
                else
                    gCurrentSprite.workY += 1;
            }
        }
    }

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SaXTro1Init();

        case SA_X_SPRITE_POSE_WALKING_INIT:
            SaXWalkingInit();
            break;

        case SA_X_SPRITE_POSE_WALKING:
            SaXTro1Walking();
            break;

        case SA_X_SPRITE_POSE_RUNNING_INIT:
            SaXRunningInit();

        case SA_X_SPRITE_POSE_RUNNING:
            SaXTro1Running();
            break;

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT:
            SaXTurningAroundChaseInit();

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE:
            SaXTro1TurningAroundChase();
            break;

        case SA_X_SPRITE_POSE_IDLE_BEFORE_SHOOTING_DOOR_INIT:
            SaXIdleBeforeShootingDoorInit();

        case SA_X_SPRITE_POSE_IDLE_BEFORE_SHOOTING_DOOR:
            SaXIdleBeforeShootingDoor();
            break;

        case SA_X_SPRITE_POSE_SHOOTING_DOOR_INIT:
            SaXShootingDoorInit();

        case SA_X_SPRITE_POSE_SHOOTING_DOOR:
            SaXShootingDoor();
            break;

        case SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_DOOR_INIT:
            SaXIdleAfterShootingDoorInit();

        case SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_DOOR:
            SaXIdleAfterShootingDoor();
            break;

        case SA_X_SPRITE_POSE_WALKING_TO_DOOR_INIT:
            SaXWalkingToDoorInit();

        case SA_X_SPRITE_POSE_WALKING_TO_DOOR:
            SaXWalkingToDoor();
            
            if (gCurrentSprite.status == 0)
                unk_372c(0xC8, 3, 8);
            break;

        case SA_X_SPRITE_POSE_TURNING_AROUND_INIT:
            SaXTurningAroundInit();

        case SA_X_SPRITE_POSE_TURNING_AROUND:
            SaXTurningAround();
            break;

        case SPRITE_POSE_FALLING_INIT:
            SaXFallingInit();

        case SPRITE_POSE_FALLING:
            SaXFalling();
            break;

        case SA_X_SPRITE_POSE_STANDING_INIT:
            SaXStandingInit();

        case SA_X_SPRITE_POSE_STANDING:
            SaXStanding();
            break;

        case SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT:
            SaXDelayBeforeShootingBeamInit();

        case SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM:
            SaXDelayBeforeShootingBeam();
            break;

        case SA_X_SPRITE_POSE_SHOOTING_BEAM_INIT:
            SaXShootingBeamInit();

        case SA_X_SPRITE_POSE_SHOOTING_BEAM:
            SaXShootingBeam();
            break;

        case SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_MISSILE_INIT:
            SaXDelayBeforeShootingMissileInit();

        case SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_MISSILE:
            SaXDelayBeforeShootingMissile();
            break;

        case SA_X_SPRITE_POSE_SHOOTING_MISSILE_INIT:
            SaXShootingMissileInit();

        case SA_X_SPRITE_POSE_SHOOTING_MISSILE:
            SaXShootingMissile();
            break;

        case SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_MISSILE_INIT:
            SaXIdleAfterShootingMissileInit();

        case SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_MISSILE:
            SaXIdleAfterShootingMissile();
            break;
    }

    SaXUpdateGraphics();

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
        PlayMusic(MUSIC_SA_X_CHASE, 0x9);
}
