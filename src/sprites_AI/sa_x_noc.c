#include "sprites_AI/sa_x_noc.h"
#include "sprites_AI/sa_x.h"
#include "macros.h"

#include "data/sprites/sa_x.h"

#include "constants/audio.h"
#include "constants/clipdata.h"
#include "constants/event.h"
#include "constants/sprite.h"
#include "constants/samus.h"
#include "constants/sa_x.h"

#include "structs/sprite.h"
#include "structs/sa_x.h"

/**
 * @brief 184e0 | 164 | Checks the walking collisions for the SA-X (noc)
 * 
 */
void SaXNocCheckCollisionWalking(void)
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
            gCurrentSprite.work2 = 0x1;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE),
            gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + PIXEL_SIZE),
                    gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));
    
                if (gPreviousCollisionCheck == COLLISION_SOLID)
                {
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
                    return;
                }
    
                gCurrentSprite.work2 = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                return;
            }
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE, gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.work2 = 0x1;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
        }
    }
    else
    {
        if (!(gPreviousVerticalCollisionCheck & 0xF0))
            return;

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE, gCurrentSprite.xPosition - (BLOCK_SIZE * 4));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_IDLE_BEFORE_SHOOTING_DOOR_INIT;
        }
    }
}

/**
 * @brief 18644 | 200 | Checks the running collisions for the SA-X (noc)
 * 
 */
void SaXNocCheckCollisionRunning(void)
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
            gCurrentSprite.work2 = 0x1;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE),
            gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + PIXEL_SIZE),
                    gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));
    
                if (gPreviousCollisionCheck == COLLISION_SOLID)
                {
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                    return;
                }
    
                gCurrentSprite.work2 = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                return;
            }

            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + PIXEL_SIZE),
                gCurrentSprite.xPosition);
    
            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MORPHING_INIT;
                return;
            }

            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE), gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));
            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MORPHING_INIT;
                return;
            }
        
            gCurrentSprite.work2 = 0x2;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }
    
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE, gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.work2 = 0x1;
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
            gCurrentSprite.work2 = 0x1;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
            return;
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE),
            gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + PIXEL_SIZE),
                    gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));
    
                if (gPreviousCollisionCheck == COLLISION_SOLID)
                {
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                    return;
                }
    
                gCurrentSprite.work2 = 0x2;
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
                return;
            }

            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + PIXEL_SIZE), gCurrentSprite.xPosition);
    
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
            return;
        }
    
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE, gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.work2 = 0x1;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR_INIT;
        }
    }
}

/**
 * @brief 18844 | 4c | Checks the walking to lay power bomb collisions for the SA-X (noc)
 * 
 */
void SaXNocCheckCollisionWalkingToLayPowerBomb(void)
{
    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
            gCurrentSprite.xPosition + (BLOCK_SIZE * 5));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
            gCurrentSprite.pose = SA_X_NOC_POSE_IDLE_BEFORE_LAYING_POWER_BOMB_INIT;
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
            gCurrentSprite.xPosition - (BLOCK_SIZE * 5));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
            gCurrentSprite.pose = SA_X_NOC_POSE_IDLE_BEFORE_LAYING_POWER_BOMB_INIT;
    }
}

/**
 * @brief 18890 | 98 | Initializes the SA-X (noc)
 * 
 */
void SaXNocInit(void)
{
    gCurrentSprite.yPosition = gSaXSpawnPosition.y;
    gCurrentSprite.xPosition = gSaXSpawnPosition.x;

    SaXInit();

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        gCurrentSprite.xPosition -= (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2);
    else
        gCurrentSprite.xPosition += (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2);

    gCurrentSprite.samusCollision = SSC_NONE;

    if (EventCheckOn_NavigationRoomEnteringNoc())
    {
        gCurrentSprite.status |= SPRITE_STATUS_HIDDEN;
        gCurrentSprite.pose = SA_X_NOC_POSE_WAITING_IN_DOOR_TO_LAY_POWER_BOMB;
        SaXSetPose(SA_X_POSE_WALKING);
    }
    else if (EventCheckOn_EngagedSaXNoc())
    {
        gCurrentSprite.status |= SPRITE_STATUS_HIDDEN;
        gCurrentSprite.pose = SA_X_NOC_POSE_WAITING_IN_DOOR_DURING_CHASE;
        gCurrentSprite.work1 = 60;
        SaXSetPose(SA_X_POSE_RUNNING);
    }
    else
    {
        gCurrentSprite.status = 0;
    }
}

/**
 * @brief 18928 | 84 | Handles the SA-X (noc) waiting in a door during a chase
 * 
 */
void SaXNocWaitingInDoorDuringChase(void)
{
    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 != 0)
        return;

    gCurrentSprite.pose = SA_X_NOC_POSE_OPENING_DOOR_DURING_CHASE;
    gCurrentSprite.work1 = 30;

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
 * @brief 189ac | 40 | Handles the SA-X (noc) opening a door during a chase
 * 
 */
void SaXNocOpeningDoorDuringChase(void)
{
    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 != 0)
        return;

    SaXRunningInit();
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;

    gCurrentSprite.status &= ~SPRITE_STATUS_HIDDEN;
    gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
}

/**
 * @brief 189ec | 98 | Handles the SA-X (noc) waiting in a door to lay a power bomb
 * 
 */
void SaXNocWaitingInDoorToLayPowerBomb(void)
{
    if (!EventCheckOn_EngagedSaXNoc())
        return;

    SaXWalkingInit();

    gCurrentSprite.pose = SA_X_NOC_POSE_WALKING_TO_LAY_POWER_BOMB;
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    gCurrentSprite.status &= ~SPRITE_STATUS_HIDDEN;

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

    gCurrentSprite.work1 = 30;
}

/**
 * @brief 18a84 | 64 | Handles the SA-X (noc) walking to lay a power bomb
 * 
 */
void SaXNocWalkingToLayPowerBomb(void)
{
    if (gCurrentSprite.work1 != 0)
    {
        gCurrentSprite.work1--;
        if (gCurrentSprite.work1 == 0)
            SoundEventUpdateForSaXEncounter();

        return;
    }

    if (SaXCheckStartChasing())
        return;

    SaXNocCheckCollisionWalkingToLayPowerBomb();
    if (gCurrentSprite.pose == SA_X_NOC_POSE_WALKING_TO_LAY_POWER_BOMB)
    {
        SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXWalkingSpeed[gCurrentSprite.work3 / 8]);

        if (gCurrentSprite.work3 < ARRAY_SIZE(sSaXWalkingSpeed) * 8 - 1)
            gCurrentSprite.work3++;
    }
}

/**
 * @brief 18ae8 | 28 | Initializes the SA-X (noc) to be idle before laying a power bomb
 * 
 */
void SaXNocIdleBeforeLayingPowerBombInit(void)
{
    gCurrentSprite.pose = SA_X_NOC_POSE_IDLE_BEFORE_LAYING_POWER_BOMB;

    gCurrentSprite.work1 = 24;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - PIXEL_SIZE * 2);

    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 18b10 | 24 | Handles the SA-X (noc) being idle before laying a power bomb
 * 
 */
void SaXNocIdleBeforeLayingPowerBomb(void)
{
    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 == 0)
        gCurrentSprite.pose = SA_X_NOC_POSE_MORPHING_TO_LAY_POWER_BOMB_INIT;
}

/**
 * @brief 18b34 | 24 | Initializes the SA-X (noc) to be morphing after laying a power bomb
 * 
 */
void SaXNocMorphingToLayPowerBombInit(void)
{
    gCurrentSprite.pose = SA_X_NOC_POSE_MORPHING_TO_LAY_POWER_BOMB;

    gCurrentSprite.hitboxTop = -(BLOCK_SIZE + QUARTER_BLOCK_SIZE);

    SaXSetPose(SA_X_POSE_MORPHING);
}

/**
 * @brief 18b58 | 20 | Handles the SA-X (noc) morphing to lay a power bomb
 * 
 */
void SaXNocMorphingToLayPowerBomb(void)
{
    if (gSaXData.pose == SA_X_POSE_MORPH_BALL)
        gCurrentSprite.pose = SA_X_NOC_POSE_LAYING_POWER_BOMB_INIT;
}

/**
 * @brief 18b78 | 20 | Initializes the SA-X (noc) laying a power bomb
 * 
 */
void SaXNocLayingPowerBombInit(void)
{
    gCurrentSprite.pose = SA_X_NOC_POSE_LAYING_POWER_BOMB;
    gCurrentSprite.hitboxTop = -(HALF_BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2);
    gCurrentSprite.work1 = 60 * 4;
}

/**
 * @brief 18b98 | 4c | Handles the SA-X (noc) laying a power bomb
 * 
 */
void SaXNocLayingPowerBomb(void)
{
    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 == 0)
    {
        gCurrentSprite.pose = SA_X_SPRITE_POSE_UNMORPHING_INIT;
        return;
    }

    if (gCurrentSprite.work1 == 60 * 3 + 60 / 6)
    {
        SpriteSpawnSecondary(SSPRITE_SA_X_POWER_BOMB, 0, 0, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
    }
}

/**
 * @brief 18be4 | 4c | Handles the SA-X (noc) walking
 * 
 */
void SaXNocWalking(void)
{
    if (SaXCheckStartChasing())
        return;

    SaXNocCheckCollisionWalking();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_WALKING)
        return;

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXWalkingSpeed[gCurrentSprite.work3 / 8]);

    if (gCurrentSprite.work3 < ARRAY_SIZE(sSaXWalkingSpeed) * 8 - 1)
        gCurrentSprite.work3++;
}

/**
 * @brief 18c30 | 4c | Handles the SA-X (noc) running
 * 
 */
void SaXNocRunning(void)
{
    if (SaXCheckShootOrTurnTowardsSamus())
        return;

    SaXNocCheckCollisionRunning();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_RUNNING)
        return;

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXRunningSpeed[gCurrentSprite.work3 / 8]);

    if (gCurrentSprite.work3 < ARRAY_SIZE(sSaXRunningSpeed) * 8 - 1)
        gCurrentSprite.work3++;
}

void SaXNocTurningAroundChase(void)
{
    if (gSaXData.pose == SA_X_POSE_STANDING)
    {
        gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
        SaXSetDirection();
        gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
    }
}

/**
 * @brief 18cac | 2a4 | SA-X (noc) AI
 * 
 */
void SaXNoc(void)
{
    if (SaXUpdateFreezeTimer())
        return;

    SaXSeeAndLocateSamus();

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SaXNocInit();
            break;

        case SA_X_NOC_POSE_WAITING_IN_DOOR_TO_LAY_POWER_BOMB:
            SaXNocWaitingInDoorToLayPowerBomb();
            break;

        case SA_X_NOC_POSE_WALKING_TO_LAY_POWER_BOMB:
            SaXNocWalkingToLayPowerBomb();
            break;

        case SA_X_NOC_POSE_IDLE_BEFORE_LAYING_POWER_BOMB_INIT:
            SaXNocIdleBeforeLayingPowerBombInit();

        case SA_X_NOC_POSE_IDLE_BEFORE_LAYING_POWER_BOMB:
            SaXNocIdleBeforeLayingPowerBomb();
            break;

        case SA_X_NOC_POSE_MORPHING_TO_LAY_POWER_BOMB_INIT:
            SaXNocMorphingToLayPowerBombInit();

        case SA_X_NOC_POSE_MORPHING_TO_LAY_POWER_BOMB:
            SaXNocMorphingToLayPowerBomb();
            break;

        case SA_X_NOC_POSE_LAYING_POWER_BOMB_INIT:
            SaXNocLayingPowerBombInit();

        case SA_X_NOC_POSE_LAYING_POWER_BOMB:
            SaXNocLayingPowerBomb();
            break;

        case SA_X_SPRITE_POSE_WALKING_INIT:
            SaXWalkingInit();
            break;

        case SA_X_SPRITE_POSE_WALKING:
            SaXNocWalking();
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
            {
                FadeMusicThenPlay(0x50, 3, 8);
                EventCheckAdvance(EVENT_ESCAPED_NOC_SA_X);
            }
            break;

        case SA_X_NOC_POSE_WAITING_IN_DOOR_DURING_CHASE:
            SaXNocWaitingInDoorDuringChase();
            break;

        case SA_X_NOC_POSE_OPENING_DOOR_DURING_CHASE:
            SaXNocOpeningDoorDuringChase();
            break;

        case SA_X_SPRITE_POSE_RUNNING_INIT:
            SaXRunningInit();

        case SA_X_SPRITE_POSE_RUNNING:
            SaXNocRunning();
            break;

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT:
            SaXTurningAroundChaseInit();

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE:
            SaXNocTurningAroundChase();
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

    SaXUpdateGraphics();

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
        PlayMusic(MUSIC_SA_X_CHASE, 0x9);
}
