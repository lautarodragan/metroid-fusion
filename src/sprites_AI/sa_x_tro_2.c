#include "sprites_AI/sa_x_boss.h"
#include "sprites_AI/sa_x_tro_2.h"
#include "sprites_AI/sa_x.h"
#include "macros.h"
#include "gba.h"
#include "globals.h"

#include "data/sprites/sa_x.h"
#include "data/sprite_data.h"
#include "data/sprite_pointers.h"

#include "constants/audio.h"
#include "constants/connection.h"
#include "constants/clipdata.h"
#include "constants/event.h"
#include "constants/sprite.h"
#include "constants/samus.h"
#include "constants/sa_x.h"

#include "structs/connection.h"
#include "structs/sprite.h"
#include "structs/samus.h"
#include "structs/sa_x.h"

/**
 * @brief 1bb98 | 21c | Checks the walking collisions for the SA-X (tro 2)
 * 
 */
void SaXTro2CheckCollisionWalking(void)
{
    gCurrentSprite.work2 = DIAG_AIM_NONE;

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

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
            gCurrentSprite.xPosition + (HALF_BLOCK_SIZE + QUARTER_BLOCK_SIZE - PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_AIR)
        {
            gCurrentSprite.work2 = 0x1;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        if (gCurrentRoom == 59)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + HALF_BLOCK_SIZE),
                gCurrentSprite.xPosition + (BLOCK_SIZE * 2));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                if (gCurrentSprite.xPosition > BLOCK_SIZE * 16 + HALF_BLOCK_SIZE)
                {
                    gCurrentSprite.status = 0;
                    unk_372c(0x3C, 0x6, 0);
                    EventCheckAdvance(EVENT_ESCAPED_TRO_2_SA_X);
                }

                return;
            }

            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE),
                gCurrentSprite.xPosition + (BLOCK_SIZE + QUARTER_BLOCK_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.work2 = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }

            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + HALF_BLOCK_SIZE),
            gCurrentSprite.xPosition + (BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (QUARTER_BLOCK_SIZE),
                gCurrentSprite.xPosition + (BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.pose = SA_X_TRO_2_POSE_STOPPED_AT_DOOR_INIT;
            }
            else
            {
                gCurrentSprite.work2 = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }

            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE),
            gCurrentSprite.xPosition + (BLOCK_SIZE + QUARTER_BLOCK_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.work2 = 0x2;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
        }
    }
    else
    {
        if (!(gPreviousVerticalCollisionCheck & 0xF0))
            return;

        if (gCurrentRoom == 59)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
                gCurrentSprite.xPosition - (HALF_BLOCK_SIZE + QUARTER_BLOCK_SIZE - PIXEL_SIZE));

            if (!(gPreviousCollisionCheck & 0xF0))
            {
                gCurrentSprite.pose = SA_X_TRO_2_POSE_STOPPED_AT_DOOR_INIT;
                return;
            }
        }
        else
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
                gCurrentSprite.xPosition - (HALF_BLOCK_SIZE + QUARTER_BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_AIR)
            {
                gCurrentSprite.work2 = 0x1;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                return;
            }
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + HALF_BLOCK_SIZE),
            gCurrentSprite.xPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (QUARTER_BLOCK_SIZE),
                gCurrentSprite.xPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.pose = SA_X_TRO_2_POSE_STOPPED_AT_DOOR_INIT;
            }
            else
            {
                gCurrentSprite.work2 = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }
        }
        else
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE),
                gCurrentSprite.xPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.work2 = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                return;
            }
        }
    }
}

/**
 * @brief 1bdb4 | 334 | Checks the running collisions for the SA-X (tro 2)
 * 
 */
void SaXTro2CheckCollisionRunning(void)
{
    gCurrentSprite.work2 = DIAG_AIM_NONE;

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
                gCurrentSprite.work2 = 0x1;
            else
                gCurrentSprite.work2 = 0x4;

            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE),
            gCurrentSprite.xPosition + (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (QUARTER_BLOCK_SIZE),
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
                        gCurrentSprite.work2 = 0x3;
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                        gCurrentSprite.work3 = 0x8;
                    }
                    else
                    {
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                    }
                }
                else
                {
                    gCurrentSprite.work2 = 0x2;
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

                gCurrentSprite.work2 = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }
        }
        else
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.work2 = 0x1;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }
        }
    }
    else
    {
        if (!(gPreviousVerticalCollisionCheck & 0xF0))
            return;

        if (gCurrentRoom == 59)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition - (BLOCK_SIZE * 2 + HALF_BLOCK_SIZE));

            if (gPreviousCollisionCheck != COLLISION_AIR)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + HALF_BLOCK_SIZE),
                    gCurrentSprite.xPosition - (BLOCK_SIZE * 2 + HALF_BLOCK_SIZE));

                if (gPreviousCollisionCheck != COLLISION_AIR && gSaXVision.samusOnRight == FALSE)
                {
                    gCurrentSprite.pose = SA_X_TRO_2_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
                    gCurrentSprite.work2 = gSaXVision.diagonalAim;
                    return;
                }
            }
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition - HALF_BLOCK_SIZE);
        if (gPreviousCollisionCheck == COLLISION_AIR)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE),
                gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

            if (gPreviousCollisionCheck == COLLISION_AIR)
                gCurrentSprite.work2 = 0x1;
            else
                gCurrentSprite.work2 = 0x4;

            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE),
            gCurrentSprite.xPosition - (BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (QUARTER_BLOCK_SIZE),
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
                        gCurrentSprite.work2 = 0x3;
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                        gCurrentSprite.work3 = 0x8;
                    }
                    else
                    {
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                    }
                }
                else
                {
                    gCurrentSprite.work2 = 0x2;
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

                gCurrentSprite.work2 = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }
        }
        else
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.work2 = 0x1;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            }
        }
    }
}

/**
 * @brief 1c0e8 | d4 | Initializes the SA-X (tro 2) sprite
 * 
 */
void SaXTro2Init(void)
{
    if (EventCheckOn_NavAfterYakuza())
    {
        SaXInit();

        gCurrentSprite.status &= ~SPRITE_STATUS_FACING_RIGHT;
        SaXSetDirection();

        gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
        gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING_INIT;

        SaXSetPose(SA_X_POSE_WALKING);

        return;
    }

    if (EventCheckOn_EngagedSaXTro2())
    {
        gCurrentSprite.yPosition = gSaXSpawnPosition.y;
        gCurrentSprite.xPosition = gSaXSpawnPosition.x;

        SaXInit();

        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
            gCurrentSprite.xPosition -= (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2);
        else
            gCurrentSprite.xPosition += (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2);

        gCurrentSprite.samusCollision = SSC_NONE;
        gCurrentSprite.status |= SPRITE_STATUS_HIDDEN;

        if (gCurrentRoom == 59)
        {
            gCurrentSprite.pose = SA_X_TRO_2_POSE_WAITING_IN_DOOR_END;
            gCurrentSprite.work1 = 200;
            SaXSetPose(SA_X_POSE_WALKING);
        }
        else
        {
            gCurrentSprite.pose = SA_X_TRO_2_POSE_WAITING_IN_DOOR_DURING_CHASE;
            gCurrentSprite.work1 = 90;
            SaXSetPose(SA_X_POSE_RUNNING);
        }
    }
    else
    {
        gCurrentSprite.status = 0;
    }
}

/**
 * @brief 1c1bc | 40 | Handles the SA-X (tro 2) waiting in a door during a chase
 * 
 */
void SaXTro2WaitingInDoorDuringChase(void)
{
    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 == 0)
    {
        SaXRunningInit();
        gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;

        gCurrentSprite.status &= ~SPRITE_STATUS_HIDDEN;
        gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
    }
}

/**
 * @brief 1c1fc | 40 | Handles the SA-X (tro 2) waiting in a door to end a chase
 * 
 */
void SaXTro2WaitingInDoorEnd(void)
{
    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 == 0)
    {
        SaXWalkingInit();
        gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;

        gCurrentSprite.status &= ~SPRITE_STATUS_HIDDEN;
        gCurrentSprite.status &= ~SPRITE_STATUS_SAMUS_DETECTED;
    }
}

/**
 * @brief 1c23c | 88 | Handles the SA-X (tro 2) walking
 * 
 */
void SaXTro2Walking(void)
{
    if (SaXCheckStartChasing())
        return;

    SaXTro2CheckCollisionWalking();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_WALKING)
        return;

    if (gSamusData.newProjectile != 0x0)
    {
        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (gSaXVision.samusOnRight == FALSE)
            {
                gCurrentSprite.pose = SA_X_TRO_2_POSE_TURNING_AFTER_HEARING_WEAPON_INIT;
            }
        }
        else
        {
            if (gSaXVision.samusOnRight == TRUE)
            {
                gCurrentSprite.pose = SA_X_TRO_2_POSE_TURNING_AFTER_HEARING_WEAPON_INIT;
            }
        }
    }

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXWalkingSpeed[gCurrentSprite.work3 / 8]);

    if (gCurrentSprite.work3 < ARRAY_SIZE(sSaXWalkingSpeed) * 8 - 1)
        gCurrentSprite.work3++;
}

/**
 * @brief 1c2c4 | 28 | Initializes the SA-X (tro 2) to be stopped at a door
 * 
 */
void SaXTro2StoppedAtDoorInit(void)
{
    gCurrentSprite.pose = SA_X_TRO_2_POSE_STOPPED_AT_DOOR;
    gCurrentSprite.work1 = 90;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 1c2ec | 78 | Handles the SA-X (tro 2) stopped at a door
 * 
 */
void SaXTro2StoppedAtDoor(void)
{
    u32 nslr;

    if (SaXCheckStartChasing())
        return;

    if (gCurrentRoom == 59 && !(gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT))
    {
        nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 3, BLOCK_SIZE * 7);

        if (nslr == NSLR_LEFT)
        {
            gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
            gCurrentSprite.workY = 0;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        }
    }

    if (gCurrentSprite.pose == SA_X_TRO_2_POSE_STOPPED_AT_DOOR)
    {
        gCurrentSprite.work1--;
        if (gCurrentSprite.work1 == 0)
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
    }
}

/**
 * @brief 1c364 | 28 | Initializes the SA-X (tro 2) to be idle after hearing a weapon
 * 
 */
void SaXTro2IdleAfterHearingWeaponInit(void)
{
    gCurrentSprite.pose = SA_X_TRO_2_POSE_IDLE_AFTER_HEARING_WEAPON;
    gCurrentSprite.work1 = 90;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 1c38c | 24 | Handles the SA-X (tro 2) being idle after hearing a weapon
 * 
 */
void SaXTro2IdleAfterHearingWeapon(void)
{
    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 == 0)
        gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING_INIT;
}

/**
 * @brief 1c3b0 | 24 | Initializes the SA-X (tro 2) to turn around after hearing a weapon
 * 
 */
void SaXTro2TurningAfterHearingWeaponInit(void)
{
    gCurrentSprite.pose = SA_X_TRO_2_POSE_TURNING_AFTER_HEARING_WEAPON;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_TURNING);
}

/**
 * @brief 1c3d4 | 50 | Handles the SA-X (tro 2) to be turning around after hearing a weapon
 * 
 */
void SaXTro2TurningAfterHearingWeapon(void)
{
    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
        return;
    }

    if (gSaXData.pose == SA_X_POSE_STANDING)
    {
        gCurrentSprite.pose = SA_X_TRO_2_POSE_IDLE_AFTER_HEARING_WEAPON_INIT;
        gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
        SaXSetDirection();
    }
}

/**
 * @brief 1c424 | 4c | Handles the SA-X (tro 2) running
 * 
 */
void SaXTro2Running(void)
{
    if (SaXCheckShootOrTurnTowardsSamus())
        return;

    SaXTro2CheckCollisionRunning();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_RUNNING)
        return;

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXRunningSpeed[gCurrentSprite.work3 / 8]);

    if (gCurrentSprite.work3 < ARRAY_SIZE(sSaXRunningSpeed) * 8 - 1)
        gCurrentSprite.work3++;
}

/**
 * @brief 1c470 | 50 | Handles the SA-X (tro 2) turning around during a chase
 * 
 */
void SaXTro2TurningAroundChase(void)
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
 * @brief 1c4c0 | 4c | Initializes the SA-X (tro 2) to have a delay before shooting a beam
 * 
 */
void SaXTro2DelayBeforeShootingBeamInit(void)
{
    gCurrentSprite.pose = SA_X_TRO_2_POSE_DELAY_BEFORE_SHOOTING_BEAM;
    gCurrentSprite.work1 = 32;

    if (gCurrentSprite.work2 == DIAG_AIM_NONE)
        gSaXData.diagonalAim = DIAG_AIM_NONE;
    else if (gCurrentSprite.work2 == DIAG_AIM_UP)
        gSaXData.diagonalAim = DIAG_AIM_UP;
    else if (gCurrentSprite.work2 == DIAG_AIM_DOWN)
        gSaXData.diagonalAim = DIAG_AIM_DOWN;

    gCurrentSprite.status &= ~SPRITE_STATUS_FACING_RIGHT;
    SaXSetDirection();

    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 1c50c | 40 | Handles the SA-X (tro 2) having a delay before shooting a beam
 * 
 */
void SaXTro2DelayBeforeShootingBeam(void)
{
    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
        return;
    }

    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 == 0)
        gCurrentSprite.pose = SA_X_TRO_2_POSE_SHOOTING_BEAM_INIT;
}

/**
 * @brief 1c54c | a8 | Initializes the SA-X (tro 2) to be shooting a beam
 * 
 */
void SaXTro2ShootingBeamInit(void)
{
    gCurrentSprite.pose = SA_X_TRO_2_POSE_SHOOTING_BEAM;

    if (gCurrentSprite.work2 == DIAG_AIM_NONE)
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_NONE, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition - (BLOCK_SIZE + PIXEL_SIZE), 0);
    }
    else if (gCurrentSprite.work2 == DIAG_AIM_UP)
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_UP, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition - (BLOCK_SIZE + PIXEL_SIZE), 0);
    }
    else if (gCurrentSprite.work2 == DIAG_AIM_DOWN)
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_DOWN, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition - (BLOCK_SIZE - QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition - (BLOCK_SIZE + PIXEL_SIZE), 0);
    }

    gSaXData.missilesArmed = FALSE;
    SaXSetPose(SA_X_POSE_SHOOTING);
}

/**
 * @brief 1c5f4 | 6c | Handles the SA-X (tro 2) shooting a beam
 * 
 */
void SaXTro2ShootingBeam(void)
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
            gCurrentSprite.pose = SA_X_TRO_2_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
            gCurrentSprite.work2 = gSaXVision.diagonalAim;
        }
        else
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
        }
    }
}

/**
 * @brief 1c660 | 274 | SA-X (tro 2) AI
 * 
 */
void SaXTro2(void)
{
    if (SaXUpdateFreezeTimer())
        return;

    SaXSeeAndLocateSamus();

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SaXTro2Init();
            break;

        case SA_X_SPRITE_POSE_WALKING_INIT:
            SaXWalkingInit();
            break;

        case SA_X_SPRITE_POSE_WALKING:
            SaXTro2Walking();
            break;

        case SA_X_TRO_2_POSE_STOPPED_AT_DOOR_INIT:
            SaXTro2StoppedAtDoorInit();

        case SA_X_TRO_2_POSE_STOPPED_AT_DOOR:
            SaXTro2StoppedAtDoor();
            break;

        case SA_X_TRO_2_POSE_IDLE_AFTER_HEARING_WEAPON_INIT:
            SaXTro2IdleAfterHearingWeaponInit();

        case SA_X_TRO_2_POSE_IDLE_AFTER_HEARING_WEAPON:
            SaXTro2IdleAfterHearingWeapon();
            break;

        case SA_X_TRO_2_POSE_TURNING_AFTER_HEARING_WEAPON_INIT:
            SaXTro2TurningAfterHearingWeaponInit();

        case SA_X_TRO_2_POSE_TURNING_AFTER_HEARING_WEAPON:
            SaXTro2TurningAfterHearingWeapon();
            break;

        case SA_X_TRO_2_POSE_WAITING_IN_DOOR_DURING_CHASE:
            SaXTro2WaitingInDoorDuringChase();
            break;

        case SA_X_TRO_2_POSE_WAITING_IN_DOOR_END:
            SaXTro2WaitingInDoorEnd();
            break;

        case SA_X_SPRITE_POSE_RUNNING_INIT:
            SaXRunningInit();

        case SA_X_SPRITE_POSE_RUNNING:
            SaXTro2Running();
            break;

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT:
            SaXTurningAroundChaseInit();

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE:
            SaXTro2TurningAroundChase();
            break;

        case SA_X_TRO_2_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT:
            SaXTro2DelayBeforeShootingBeamInit();

        case SA_X_TRO_2_POSE_DELAY_BEFORE_SHOOTING_BEAM:
            SaXTro2DelayBeforeShootingBeam();
            break;

        case SA_X_TRO_2_POSE_SHOOTING_BEAM_INIT:
            SaXTro2ShootingBeamInit();

        case SA_X_TRO_2_POSE_SHOOTING_BEAM:
            SaXTro2ShootingBeam();
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
        PlayMusic(MUSIC_SA_X_CHASE, 9);
}
