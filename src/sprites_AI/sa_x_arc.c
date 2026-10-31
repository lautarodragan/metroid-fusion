#include "sprites_AI/sa_x_arc.h"
#include "sprites_AI/sa_x.h"
#include "macros.h"
#include "globals.h"

#include "data/sprites/sa_x.h"

#include "constants/audio.h"
#include "constants/connection.h"
#include "constants/clipdata.h"
#include "constants/sprite.h"
#include "constants/samus.h"
#include "constants/sa_x.h"

#include "structs/connection.h"
#include "structs/sprite.h"
#include "structs/samus.h"
#include "structs/sa_x.h"

/**
 * @brief 18f50 | 158 | Checks the walking collisions for the SA-X (arc)
 * 
 */
void SaXArcCheckCollisionWalking(void)
{
    gCurrentSprite.SA_X_DIAG_AIM = DIAG_AIM_NONE;

    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition - QUARTER_BLOCK_SIZE);

            if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                return;
            }

            if (gPreviousVerticalCollisionCheck == COLLISION_LEFT_STEEP_FLOOR_SLOPE)
                gCurrentSprite.yPosition = SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition);
            else if (gPreviousVerticalCollisionCheck == COLLISION_LEFT_SLIGHT_FLOOR_SLOPE)
                gCurrentSprite.yPosition = SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition);
        }
        else
        {
            SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition + QUARTER_BLOCK_SIZE);

            if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                return;
            }

            if (gPreviousVerticalCollisionCheck == COLLISION_RIGHT_STEEP_FLOOR_SLOPE)
                gCurrentSprite.yPosition = SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition);
            else if (gPreviousVerticalCollisionCheck == COLLISION_RIGHT_SLIGHT_FLOOR_SLOPE)
                gCurrentSprite.yPosition = SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition);
        }

        return;
    }

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (!(gPreviousVerticalCollisionCheck & 0xF0))
            return;

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

        if (gPreviousCollisionCheck == COLLISION_AIR)
        {
            gCurrentSprite.SA_X_JUMP_TYPE = 0x1;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE),
            gCurrentSprite.xPosition + (BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition + (BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.pose = SA_X_ARC_POSE_STOPPED_AT_PILLAR_INIT;
                return;
            }
            
            gCurrentSprite.SA_X_JUMP_TYPE = 0x2;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE, gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.SA_X_JUMP_TYPE = 0x1;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
        }
    }
    else
    {
        if (!(gPreviousVerticalCollisionCheck & 0xF0))
            return;

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

        if (gPreviousCollisionCheck == COLLISION_AIR)
        {
            gCurrentSprite.SA_X_JUMP_TYPE = 0x1;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE),
            gCurrentSprite.xPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.pose = SA_X_ARC_POSE_STOPPED_AT_PILLAR_INIT;
                return;
            }

            gCurrentSprite.SA_X_JUMP_TYPE = 0x2;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE, gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.SA_X_JUMP_TYPE = 0x1;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
        }
    }
}

/**
 * @brief 19098 | 32c | Checks the walking to lay power bomb collisions for the SA-X (arc)
 * 
 */
void SaXArcCheckCollisionRunning(void)
{
    gCurrentSprite.SA_X_DIAG_AIM = DIAG_AIM_NONE;

    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition - QUARTER_BLOCK_SIZE);

            if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                return;
            }

            if (gPreviousVerticalCollisionCheck == COLLISION_LEFT_STEEP_FLOOR_SLOPE)
                gCurrentSprite.yPosition = SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition);
            else if (gPreviousVerticalCollisionCheck == COLLISION_LEFT_SLIGHT_FLOOR_SLOPE)
                gCurrentSprite.yPosition = SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition);
        }
        else
        {
            SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition + QUARTER_BLOCK_SIZE);

            if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                return;
            }

            if (gPreviousVerticalCollisionCheck == COLLISION_RIGHT_STEEP_FLOOR_SLOPE)
                gCurrentSprite.yPosition = SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition);
            else if (gPreviousVerticalCollisionCheck == COLLISION_RIGHT_SLIGHT_FLOOR_SLOPE)
                gCurrentSprite.yPosition = SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition);
        }

        return;
    }
    
    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (!(gPreviousVerticalCollisionCheck & 0xF0))
            return;

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition + HALF_BLOCK_SIZE);
        if (gPreviousCollisionCheck == COLLISION_AIR)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE),
                gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

            if (gPreviousCollisionCheck == COLLISION_AIR)
                gCurrentSprite.SA_X_JUMP_TYPE = 0x1;
            else
                gCurrentSprite.SA_X_JUMP_TYPE = 0x4;

            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE),
            gCurrentSprite.xPosition + (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition + (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 5 + HALF_BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2),
                    gCurrentSprite.xPosition + (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

                if (gPreviousCollisionCheck == COLLISION_SOLID)
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 7 + QUARTER_BLOCK_SIZE - PIXEL_SIZE),
                        gCurrentSprite.xPosition + (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

                    if (gPreviousCollisionCheck == COLLISION_AIR)
                    {
                        gCurrentSprite.SA_X_JUMP_TYPE = 0x3;
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                        gCurrentSprite.SA_X_X_SPEED_IDX = 0x8;
                    }
                    else
                    {
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                    }
                }
                else
                {
                    gCurrentSprite.SA_X_JUMP_TYPE = 0x2;;
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                }
            }
            else
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + PIXEL_SIZE),
                    gCurrentSprite.xPosition);

                if (gPreviousCollisionCheck == COLLISION_SOLID)
                {
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_MORPHING_INIT;
                    return;
                }

                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE),
                    gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));

                if (gPreviousCollisionCheck == COLLISION_SOLID)
                {
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_MORPHING_INIT;
                    return;
                }

                gCurrentSprite.SA_X_JUMP_TYPE = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }
        }
        else
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.SA_X_JUMP_TYPE = 0x1;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }
        }
    }
    else
    {
        if (!(gPreviousVerticalCollisionCheck & 0xF0))
            return;

        if (gCurrentRoom == 43 && gCurrentSprite.xPosition < BLOCK_SIZE * 44)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 7 + QUARTER_BLOCK_SIZE - PIXEL_SIZE),
                gCurrentSprite.xPosition - (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

            if (gPreviousCollisionCheck != COLLISION_AIR && gSaXVision.samusOnRight == FALSE)
            {
                gCurrentSprite.pose = SA_X_ARC_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
                gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
                return;
            }
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition - HALF_BLOCK_SIZE);
        if (gPreviousCollisionCheck == COLLISION_AIR)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE),
                gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

            if (gPreviousCollisionCheck == COLLISION_AIR)
                gCurrentSprite.SA_X_JUMP_TYPE = 0x1;
            else
                gCurrentSprite.SA_X_JUMP_TYPE = 0x4;

            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE),
            gCurrentSprite.xPosition - (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition - (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 5 + HALF_BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2),
                    gCurrentSprite.xPosition - (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

                if (gPreviousCollisionCheck == COLLISION_SOLID)
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 7 + QUARTER_BLOCK_SIZE - PIXEL_SIZE),
                        gCurrentSprite.xPosition - (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

                    if (gPreviousCollisionCheck == COLLISION_AIR)
                    {
                        gCurrentSprite.SA_X_JUMP_TYPE = 0x3;
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                        gCurrentSprite.SA_X_X_SPEED_IDX = 0x8;
                    }
                    else
                    {
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                    }
                }
                else
                {
                    gCurrentSprite.SA_X_JUMP_TYPE = 0x2;
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                }
            }
            else
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + PIXEL_SIZE),
                    gCurrentSprite.xPosition);

                if (gPreviousCollisionCheck == COLLISION_SOLID)
                {
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_MORPHING_INIT;
                    return;
                }

                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE),
                    gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));

                if (gPreviousCollisionCheck == COLLISION_SOLID)
                {
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_MORPHING_INIT;
                    return;
                }

                gCurrentSprite.SA_X_JUMP_TYPE = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }
        }
        else
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.SA_X_JUMP_TYPE = 0x1;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }
        }
    }
}

/**
 * @brief 193c4 | 96 | Initializes the SA-X (arc)
 * 
 */
void SaXArcInit(void)
{
    gCurrentSprite.yPosition = gSaXSpawnPosition.y;
    gCurrentSprite.xPosition = gSaXSpawnPosition.x;

    SaXInit();

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        gCurrentSprite.xPosition -= (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2);
    else
        gCurrentSprite.xPosition += (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2);

    gCurrentSprite.samusCollision = SSC_NONE;

    if (EventCheckOn_PowerBombsDownloaded())
    {
        gCurrentSprite.status |= SPRITE_STATUS_HIDDEN;
        gCurrentSprite.pose = SA_X_ARC_POSE_WAITING_IN_DOOR;
        SaXSetPose(SA_X_POSE_WALKING);
    }
    else if (EventCheckOn_EngagedSaXArc())
    {
        gCurrentSprite.status |= SPRITE_STATUS_HIDDEN;
        gCurrentSprite.pose = SA_X_ARC_POSE_WAITING_IN_DOOR_DURING_CHASE;
        gCurrentSprite.SA_X_TIMER = 60;
        SaXSetPose(SA_X_POSE_RUNNING);
    }
    else
    {
        gCurrentSprite.status = 0;
    }
}

/**
 * @brief 1945c | 84 | Handles the SA-X (arc) waiting in a door during a chase
 * 
 */
void SaXArcWaitingInDoorDuringChase(void)
{
    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER != 0)
        return;

    gCurrentSprite.pose = SA_X_ARC_POSE_OPENING_DOOR_DURING_CHASE;
    gCurrentSprite.SA_X_TIMER = 30;

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, 0x80, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition, SPRITE_STATUS_X_FLIP);
    }
    else
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, 0x80, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition, 0);
    }
}

/**
 * @brief 194e0 | 40 | Handles the SA-X (arc) opening a door during a chase
 * 
 */
void SaXArcOpeningDoorDuringChase(void)
{
    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER != 0)
        return;

    SaXRunningInit();
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;

    gCurrentSprite.status &= ~SPRITE_STATUS_HIDDEN;
    gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
}

/**
 * @brief 19520 | 7c | Handles the SA-X (arc) waiting in a door
 * 
 */
void SaXArcWaitingInDoor(void)
{
    if (!EventCheckOn_EngagedSaXArc())
        return;

    gCurrentSprite.pose = SA_X_ARC_POSE_OPENING_DOOR;
    gCurrentSprite.SA_X_TIMER = 30;

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, 0x80, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition, SPRITE_STATUS_X_FLIP);
    }
    else
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, 0x80, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition, 0);
    }
}

/**
 * @brief 1959c | 3c | Handles the SA-X (arc) opening a door
 * 
 */
void SaXArcOpeningDoor(void)
{
    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER != 0)
        return;

    SaXWalkingInit();

    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    gCurrentSprite.status &= ~SPRITE_STATUS_HIDDEN;

    SoundEventUpdateForSaXEncounter();
}

/**
 * @brief 195d8 | 88 | Handles the SA-X (arc) walking
 * 
 */
void SaXArcWalking(void)
{
    if (SaXCheckStartChasing())
        return;

    SaXArcCheckCollisionWalking();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_WALKING)
        return;

    if (gSamusData.newProjectile != 0x0)
    {
        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (gSaXVision.samusOnRight == FALSE)
            {
                gCurrentSprite.pose = SA_X_ARC_POSE_TURNING_AROUND_AFTER_HEARING_WEAPON_INIT;
            }
        }
        else
        {
            if (gSaXVision.samusOnRight == TRUE)
            {
                gCurrentSprite.pose = SA_X_ARC_POSE_TURNING_AROUND_AFTER_HEARING_WEAPON_INIT;
            }
        }
    }

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXWalkingSpeed[gCurrentSprite.SA_X_X_SPEED_IDX / 8]);

    if (gCurrentSprite.SA_X_X_SPEED_IDX < ARRAY_SIZE(sSaXWalkingSpeed) * 8 - 1)
        gCurrentSprite.SA_X_X_SPEED_IDX++;
}

/**
 * @brief 19660 | 28 | Initializes the SA-X (arc) to be stopped at the pillar
 * 
 */
void SaXArcStoppedAtPillarInit(void)
{
    gCurrentSprite.pose = SA_X_ARC_POSE_STOPPED_AT_PILLAR;
    gCurrentSprite.SA_X_TIMER = 60 * 2;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 19688 | 24 | Handles the SA-X (arc) being stopped at the pillar
 * 
 */
void SaXArcStoppedAtPillar(void)
{
    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER == 0)
        gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
}

/**
 * @brief 196ac | 28 | Initializes the SA-X (arc) to be idle after hearing a weapon
 * 
 */
void SaXArcIdleAfterHearingWeaponInit(void)
{
    gCurrentSprite.pose = SA_X_ARC_POSE_IDLE_AFTER_HEARING_WEAPON;
    gCurrentSprite.SA_X_TIMER = 60 * 2;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 196d4 | 24 | Handles the SA-X (arc) being idle after hearing a weapon
 * 
 */
void SaXArcIdleAfterHearingWeapon(void)
{
    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER == 0)
        gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING_INIT;
}

/**
 * @brief 196f8 | 24 | Initializes the SA-X (arc) to be turning after hearing a weapon
 * 
 */
void SaXArcTurningAroundAfterHearingWeaponInit(void)
{
    gCurrentSprite.pose = SA_X_ARC_POSE_TURNING_AROUND_AFTER_HEARING_WEAPON;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_TURNING);
}

/**
 * @brief 1971c | 50 | Handles the SA-X (arc) turning around after hearing a weapon
 * 
 */
void SaXArcTurningAroundAfterHearingWeapon(void)
{
    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
        return;
    }

    if (gSaXData.pose == SA_X_POSE_STANDING)
    {
        gCurrentSprite.pose = SA_X_ARC_POSE_IDLE_AFTER_HEARING_WEAPON_INIT;
        gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
        SaXSetDirection();
    }
}

/**
 * @brief 1976c | 4c | Handles the SA-X (arc) running
 * 
 */
void SaXArcRunning(void)
{
    if (SaXCheckShootOrTurnTowardsSamus())
        return;

    SaXArcCheckCollisionRunning();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_RUNNING)
        return;

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXRunningSpeed[gCurrentSprite.SA_X_X_SPEED_IDX / 8]);

    if (gCurrentSprite.SA_X_X_SPEED_IDX < ARRAY_SIZE(sSaXRunningSpeed) * 8 - 1)
        gCurrentSprite.SA_X_X_SPEED_IDX++;
}

/**
 * @brief 197b8 | 50 | Handles the SA-X (arc) turning around during a chase
 * 
 */
void SaXArcTurningAroundChase(void)
{
    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
        return;
    }

    if (gSaXData.pose == SA_X_POSE_STANDING)
    {
        gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
        SaXSetDirection();
        gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
    }
}

/**
 * @brief 19808 | 4c | Initializes the SA-X (arc) to be idle before shooting a beam
 * 
 */
void SaXArcDelayBeforeShootingBeamInit(void)
{
    gCurrentSprite.pose = SA_X_ARC_POSE_DELAY_BEFORE_SHOOTING_BEAM;
    gCurrentSprite.SA_X_TIMER = 32;

    if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_NONE)
        gSaXData.diagonalAim = DIAG_AIM_NONE;
    else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_UP)
        gSaXData.diagonalAim = DIAG_AIM_UP;
    else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_DOWN)
        gSaXData.diagonalAim = DIAG_AIM_DOWN;

    gCurrentSprite.status &= ~SPRITE_STATUS_FACING_RIGHT;
    SaXSetDirection();
    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 19854 | 40 | Handles the SA-X (arc) being idle before shooting a beam
 * 
 */
void SaXArcDelayBeforeShootingBeam(void)
{
    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
        return;
    }

    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER == 0)
        gCurrentSprite.pose = SA_X_ARC_POSE_SHOOTING_BEAM_INIT;
}

/**
 * @brief 19894 | a8 | Handles the SA-X (arc) shooting a beam
 * 
 */
void SaXArcShootingBeamInit(void)
{
    gCurrentSprite.pose = SA_X_ARC_POSE_SHOOTING_BEAM;

    if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_NONE)
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_NONE, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition - (BLOCK_SIZE + PIXEL_SIZE), 0);
    }
    else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_UP)
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_UP, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition - (BLOCK_SIZE + PIXEL_SIZE), 0);
    }
    else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_DOWN)
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_DOWN, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition - (BLOCK_SIZE - QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition - (BLOCK_SIZE + PIXEL_SIZE), 0);
    }

    gSaXData.missilesArmed = FALSE;
    SaXSetPose(SA_X_POSE_SHOOTING);
}

/**
 * @brief 1993c | 6c | Handles the SA-X (arc) shooting a beam
 * 
 */
void SaXArcShootingBeam(void)
{
    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
        return;
    }

    if (gSaXData.pose == SA_X_POSE_STANDING)
    {
        if (gPreviousCollisionCheck != COLLISION_AIR && gSaXVision.samusOnRight == FALSE)
        {
            gCurrentSprite.pose = SA_X_ARC_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
            gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
        }
        else
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
        }
    }
}

/**
 * @brief 199a8 | 280 | SA-X (arc) AI
 * 
 */
void SaXArc(void)
{
    if (SaXUpdateFreezeTimer())
        return;

    SaXSeeAndLocateSamus();

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SaXArcInit();
            break;

        case SA_X_ARC_POSE_WAITING_IN_DOOR:
            SaXArcWaitingInDoor();
            break;

        case SA_X_ARC_POSE_OPENING_DOOR:
            SaXArcOpeningDoor();
            break;

        case SA_X_SPRITE_POSE_WALKING_INIT:
            SaXWalkingInit();
            break;

        case SA_X_SPRITE_POSE_WALKING:
            SaXArcWalking();
            break;

        case SA_X_ARC_POSE_STOPPED_AT_PILLAR_INIT:
            SaXArcStoppedAtPillarInit();

        case SA_X_ARC_POSE_STOPPED_AT_PILLAR:
            SaXArcStoppedAtPillar();
            break;

        case SA_X_ARC_POSE_IDLE_AFTER_HEARING_WEAPON_INIT:
            SaXArcIdleAfterHearingWeaponInit();

        case SA_X_ARC_POSE_IDLE_AFTER_HEARING_WEAPON:
            SaXArcIdleAfterHearingWeapon();
            break;

        case SA_X_ARC_POSE_TURNING_AROUND_AFTER_HEARING_WEAPON_INIT:
            SaXArcTurningAroundAfterHearingWeaponInit();

        case SA_X_ARC_POSE_TURNING_AROUND_AFTER_HEARING_WEAPON:
            SaXArcTurningAroundAfterHearingWeapon();
            break;

        case SA_X_ARC_POSE_WAITING_IN_DOOR_DURING_CHASE:
            SaXArcWaitingInDoorDuringChase();
            break;

        case SA_X_ARC_POSE_OPENING_DOOR_DURING_CHASE:
            SaXArcOpeningDoorDuringChase();
            break;

        case SA_X_SPRITE_POSE_RUNNING_INIT:
            SaXRunningInit();

        case SA_X_SPRITE_POSE_RUNNING:
            SaXArcRunning();
            break;

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT:
            SaXTurningAroundChaseInit();

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE:
            SaXArcTurningAroundChase();
            break;

        case SA_X_ARC_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT:
            SaXArcDelayBeforeShootingBeamInit();

        case SA_X_ARC_POSE_DELAY_BEFORE_SHOOTING_BEAM:
            SaXArcDelayBeforeShootingBeam();
            break;

        case SA_X_ARC_POSE_SHOOTING_BEAM_INIT:
            SaXArcShootingBeamInit();

        case SA_X_ARC_POSE_SHOOTING_BEAM:
            SaXArcShootingBeam();
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

        case SA_X_SPRITE_POSE_MID_AIR_INIT:
            SaXMidAirInit();

        case SA_X_SPRITE_POSE_MID_AIR:
            SaXMidAir();
            break;

        case SA_X_SPRITE_POSE_MORPHING_INIT:
            SaXMorphingInit();

        case SA_X_SPRITE_POSE_MORPHING:
            SaXMorphing();
            break;

        case SA_X_SPRITE_POSE_ROLLING_INIT:
            SaXRollingInit();

        case SA_X_SPRITE_POSE_ROLLING:
            SaXRolling();
            break;

        case SA_X_SPRITE_POSE_UNMORPHING_INIT:
            SaXUnmorphingInit();

        case SA_X_SPRITE_POSE_UNMORPHING:
            SaXUnmorphing();
    }

    if (gSaXData.pose == SA_X_POSE_MID_AIR)
        gCurrentSprite.properties |= SP_IMMUNE_TO_PROJECTILES;
    else
        gCurrentSprite.properties &= ~SP_IMMUNE_TO_PROJECTILES;

    SaXUpdateGraphics();

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
        PlayMusic(MUSIC_SA_X_CHASE, 0x9);
}
