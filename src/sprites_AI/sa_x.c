#include "sprites_AI/sa_x.h"
#include "sprites_AI/sa_x_lab.h"
#include "macros.h"
#include "globals.h"
#include "gba.h"

#include "data/sprite_data.h"
#include "data/sprites/sa_x.h"

#include "constants/clipdata.h"
#include "constants/particle.h"
#include "constants/sa_x.h"
#include "constants/samus.h"
#include "constants/sprite.h"

#include "structs/clipdata.h"
#include "structs/sprite.h"
#include "structs/samus.h"
#include "structs/sa_x.h"
#include "structs/power_bomb.h"

#ifdef BUGFIX
#include "data/samus/samus_animation_pointers.h"
#else // !BUGFIX
// Incorrectly declared here to produce matching code in SaXSeeAndLocateSamus
extern const u8 sSamusCollisionData[SPOSE_END][6];
#endif // BUGFIX

#define SA_X_LANDED work0 // Falling/mid-air, waits for the landing pose to end
#define SA_X_TIMER work1
#define SA_X_DIAG_AIM work2 // Shooting
#define SA_X_JUMP_TYPE work2 // Set by SaXCheckFallJumpOrMorph, selects the jump Y velocity table
#define SA_X_X_SPEED_IDX work3
#define SA_X_Y_SPEED_IDX work4
#define SA_X_LOST_SAMUS_TIMER workY // Increases while Samus is detected but not in Y range, she is lost at 20 seconds

#define SA_X_PROJECTILE_TIMER work1 // Beam, missile and power bomb
#define SA_X_BEAM_MOVEMENT_IDX work4

#define LAB_EXPLOSION_ALTERNATE work2 // Toggled every explosion cycle, alternates the frames the explosions spawn on

/**
 * @brief 157cc | 30 | Sets the direction of the SA-X
 * 
 */
void SaXSetDirection(void)
{
    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        gSaXData.direction = KEY_RIGHT;
    else
        gSaXData.direction = KEY_LEFT;
}

/**
 * @brief 157fc | 5d8 | Handles the SA-X locating samus
 * 
 */
void SaXSeeAndLocateSamus(void)
{
    u16 spriteY;
    u16 spriteX;
    
    u16 samusY;
    u16 samusX;
    u16 samusTop;
    u16 samusTileY;
    u16 samusTileX;
    u16 spriteTileY;
    u16 spriteTileX;

    u16 yDistance;
    u16 xDistance;
    u16 currPos;
    u16 positionOffset;

    u8 foundSamus;
    u16 blockSize;

    u8 i;

    samusY = gSamusData.yPosition + PIXEL_SIZE;
    samusX = gSamusData.xPosition;

    spriteY = gCurrentSprite.yPosition;
    spriteX = gCurrentSprite.xPosition;

    if (samusY > spriteY)
    {
        gSaXVision.samusBelow = TRUE;
        yDistance = samusY - spriteY;
    }
    else
    {
        gSaXVision.samusBelow = FALSE;
        yDistance = spriteY - samusY;
    }

    if (samusX > spriteX)
    {
        gSaXVision.samusOnRight = TRUE;
        xDistance = samusX - spriteX;
    }
    else
    {
        gSaXVision.samusOnRight = FALSE;
        xDistance = spriteX - samusX;
    }

    if (xDistance > BLOCK_SIZE * 10)
    {
        gSaXVision.inYRange = FALSE;
        gSaXVision.inXRange = TRUE;
        return;
    }

    if (yDistance > BLOCK_SIZE * 10)
    {
        gSaXVision.inYRange = FALSE;
        return;
    }

    gSaXVision.inYRange = TRUE;
    gSaXVision.inXRange = FALSE;

    samusTileY = samusY & BLOCK_POSITION_FLAG;
    samusTileX = samusX & BLOCK_POSITION_FLAG;
    spriteTileY = spriteY & BLOCK_POSITION_FLAG;
    spriteTileX = spriteX & BLOCK_POSITION_FLAG;

    samusTileY = samusTileY - BLOCK_SIZE;
    samusTop = samusTileY - BLOCK_SIZE;

    foundSamus = FALSE;
    blockSize = BLOCK_SIZE;

    if (yDistance <= BLOCK_SIZE)
    {
        currPos = spriteTileY - BLOCK_SIZE * 2;

        if (gSaXVision.samusOnRight == TRUE)
        {
            positionOffset = spriteTileX + BLOCK_SIZE;
            for (i = 0; i < 8; positionOffset += BLOCK_SIZE, i++)
            {
                SpriteUtilCheckCollisionAtPosition(currPos, positionOffset);

                if (gPreviousCollisionCheck & 0xF0)
                    break;

                SpriteUtilCheckCollisionAtPosition(currPos + BLOCK_SIZE, positionOffset);

                if (gPreviousCollisionCheck & 0xF0)
                    break;

                if (positionOffset != samusTileX)
                    continue;

                if (currPos == samusTileY || currPos + BLOCK_SIZE == samusTileY)
                {
                    foundSamus++;
                    break;
                }
                else if (sSamusCollisionData[gSamusData.pose][0] < 3 && (currPos == samusTop || currPos + BLOCK_SIZE == samusTop))
                {
                    foundSamus++;
                    break;
                }
            }

            if (foundSamus)
            {
                gSaXVision.diagonalAim = DIAG_AIM_NONE;
                gSaXVision.detectedSamusOnRight = TRUE;
                return;
            }
        }
        else
        {
            positionOffset = spriteTileX - BLOCK_SIZE;
            for (i = 0; i < 8; positionOffset -= blockSize, i++)
            {
                SpriteUtilCheckCollisionAtPosition(currPos, positionOffset);

                if (gPreviousCollisionCheck & 0xF0)
                    break;

                SpriteUtilCheckCollisionAtPosition(currPos + BLOCK_SIZE, positionOffset);

                if (gPreviousCollisionCheck & 0xF0)
                    break;

                if (positionOffset != samusTileX)
                    continue;

                if (currPos == samusTileY || currPos + BLOCK_SIZE == samusTileY)
                {
                    foundSamus++;
                    break;
                }
                else if (sSamusCollisionData[gSamusData.pose][0] < 3 && (currPos == samusTop || currPos + BLOCK_SIZE == samusTop))
                {
                    foundSamus++;
                    break;
                }
            }

            if (foundSamus)
            {
                gSaXVision.diagonalAim = DIAG_AIM_NONE;
                gSaXVision.detectedSamusOnRight = FALSE;
                return;
            }
        }
    }

    if (gSaXVision.samusBelow == FALSE)
    {
        currPos = spriteTileY - blockSize * 3;

        if (gSaXVision.samusOnRight == TRUE)
        {
            SpriteUtilCheckCollisionAtPosition(spriteY - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE - PIXEL_SIZE), spriteX + BLOCK_SIZE);

            if (!(gPreviousCollisionCheck & 0xF0))
            {
                positionOffset = spriteTileX + BLOCK_SIZE;
                for (i = 0; i < 8; positionOffset += BLOCK_SIZE, currPos -= blockSize ,i++)
                {
                    SpriteUtilCheckCollisionAtPosition(currPos, positionOffset);
    
                    if (gPreviousCollisionCheck & 0xF0)
                        break;
    
                    SpriteUtilCheckCollisionAtPosition(currPos - blockSize, positionOffset);
    
                    if (gPreviousCollisionCheck & 0xF0)
                        break;
    
                    if (positionOffset != samusTileX)
                        continue;
    
                    if (currPos == samusTileY || currPos - blockSize == samusTileY)
                    {
                        foundSamus++;
                        break;
                    }
                    else if (sSamusCollisionData[gSamusData.pose][0] < 3 && (currPos == samusTop || currPos - blockSize == samusTop))
                    {
                        foundSamus++;
                        break;
                    }
                }
    
                if (foundSamus)
                {
                    gSaXVision.diagonalAim = DIAG_AIM_UP;
                    gSaXVision.detectedSamusOnRight = TRUE;
                    return;
                }
            }
        }
        else
        {
            SpriteUtilCheckCollisionAtPosition(spriteY - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE - PIXEL_SIZE), spriteX - BLOCK_SIZE);

            if (!(gPreviousCollisionCheck & 0xF0))
            {
                positionOffset = spriteTileX - blockSize;
                for (i = 0; i < 8; positionOffset -= blockSize, currPos -= blockSize, i++)
                {
                    SpriteUtilCheckCollisionAtPosition(currPos, positionOffset);

                    if (gPreviousCollisionCheck & 0xF0)
                        break;

                    SpriteUtilCheckCollisionAtPosition(currPos - blockSize, positionOffset);

                    if (gPreviousCollisionCheck & 0xF0)
                        break;

                    if (positionOffset != samusTileX)
                        continue;

                    if (currPos == samusTileY || currPos - blockSize == samusTileY)
                    {
                        foundSamus++;
                        break;
                    }
                    else if (sSamusCollisionData[gSamusData.pose][0] < 3 && (currPos == samusTop || currPos - blockSize == samusTop))
                    {
                        foundSamus++;
                        break;
                    }
                }

                if (foundSamus)
                {
                    gSaXVision.diagonalAim = DIAG_AIM_UP;
                    gSaXVision.detectedSamusOnRight = FALSE;
                    return;
                }
            }
        }
    }
    else
    {
        currPos = spriteTileY - blockSize;

        if (gSaXVision.samusOnRight == TRUE)
        {
            SpriteUtilCheckCollisionAtPosition(spriteY, spriteX + (BLOCK_SIZE - PIXEL_SIZE));

            if (!(gPreviousCollisionCheck & 0xF0))
            {
                positionOffset = spriteTileX + BLOCK_SIZE;
                for (i = 0; i < 8; positionOffset += BLOCK_SIZE, currPos += BLOCK_SIZE, i++)
                {
                    SpriteUtilCheckCollisionAtPosition(currPos, positionOffset);
    
                    if (gPreviousCollisionCheck & 0xF0)
                        break;
    
                    SpriteUtilCheckCollisionAtPosition(currPos - blockSize, positionOffset);
    
                    if (gPreviousCollisionCheck & 0xF0)
                        break;
    
                    if (positionOffset != samusTileX)
                        continue;
    
                    if (currPos == samusTileY || currPos - blockSize == samusTileY)
                    {
                        foundSamus++;
                        break;
                    }
                    else if (sSamusCollisionData[gSamusData.pose][0] < 3 && (currPos == samusTop || currPos - blockSize == samusTop))
                    {
                        foundSamus++;
                        break;
                    }
                }
    
                if (foundSamus)
                {
                    gSaXVision.diagonalAim = DIAG_AIM_DOWN;
                    gSaXVision.detectedSamusOnRight = TRUE;
                    return;
                }
            }

        }
        else
        {
            SpriteUtilCheckCollisionAtPosition(spriteY, spriteX -  (BLOCK_SIZE - PIXEL_SIZE));

            if (!(gPreviousCollisionCheck & 0xF0))
            {
                positionOffset = spriteTileX - blockSize;
                for (i = 0; i < 8; positionOffset -= blockSize, currPos += blockSize, i++)
                {
                    SpriteUtilCheckCollisionAtPosition(currPos, positionOffset);
    
                    if (gPreviousCollisionCheck & 0xF0)
                        break;
    
                    SpriteUtilCheckCollisionAtPosition(currPos - blockSize, positionOffset);
    
                    if (gPreviousCollisionCheck & 0xF0)
                        break;
    
                    if (positionOffset != samusTileX)
                        continue;
    
                    if (currPos == samusTileY || currPos - blockSize == samusTileY)
                    {
                        foundSamus++;
                        break;
                    }
                    else if (sSamusCollisionData[gSamusData.pose][0] < 3 && (currPos == samusTop || currPos - blockSize == samusTop))
                    {
                        foundSamus++;
                        break;
                    }
                }
    
                if (foundSamus)
                {
                    gSaXVision.diagonalAim = DIAG_AIM_DOWN;
                    gSaXVision.detectedSamusOnRight = FALSE;
                    return;
                }
            }
        }
    }

    gSaXVision.inYRange = FALSE;
}

/**
 * @brief 15dd4 | b4 | Checks if the SA-X should start shooting a beam at samus (samus in front) or turn around to chase her (samus behind)
 * 
 * @return u8 bool, pose changed
 */
u8 SaXCheckShootOrTurnTowardsSamus(void)
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
                gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
                return TRUE;
            }
        }
        else
        {
            if (nslr == NSLR_LEFT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
                gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
                return TRUE;
            }
        }

        nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 4, BLOCK_SIZE * 10);

        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (nslr == NSLR_LEFT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return TRUE;
            }
        }
        else
        {
            if (nslr == NSLR_RIGHT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return TRUE;
            }
        }
    }
    else
    {
        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (gSaXVision.samusOnRight != FALSE)
            {
                return FALSE;
            }

            if (gSaXVision.inXRange != FALSE)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return TRUE;
            }
        }
        else
        {
            if (gSaXVision.samusOnRight != TRUE)
            {
                return FALSE;
            }

            if (gSaXVision.inXRange != FALSE)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return TRUE;
            }
        }
    }

    return FALSE;
}

/**
 * @brief 15e88 | cc | Checks if the SA-X should start chasing samus (samus in Y range or SA-X hit), either running or turning around towards her
 * 
 * @return u8 bool, pose changed
 */
u8 SaXCheckStartChasing(void)
{
    u8 prevPose;

    prevPose = gCurrentSprite.pose;

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (gSaXVision.inYRange == TRUE)
        {
            gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
            gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;

            if (gSaXVision.detectedSamusOnRight != TRUE)
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            else
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        }
        else
        {
            if (SPRITE_GET_ISFT(gCurrentSprite))
            {
                gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
                gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;

                if (gSaXVision.samusOnRight == FALSE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                else
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            }
        }
    }
    else
    {
        if (gSaXVision.inYRange == TRUE)
        {
            gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
            gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;

            if (gSaXVision.detectedSamusOnRight != FALSE)
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            else
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        }
        else
        {
            if (SPRITE_GET_ISFT(gCurrentSprite))
            {
                gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
                gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;

                if (gSaXVision.samusOnRight == TRUE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            else
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            }
        }
    }

    if (prevPose == gCurrentSprite.pose)
        return FALSE;

    return TRUE;
}

/**
 * @brief 15f54 | 108 | Same as SaXCheckStartChasing, but also turns around (without chasing) when samus is behind in X range
 * 
 * @return u8 bool, pose changed
 */
u8 SaXCheckStartChasingOrTurnAround(void)
{
    u8 prevPose;

    prevPose = gCurrentSprite.pose;

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (gSaXVision.inYRange == TRUE)
        {
            gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
            gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;

            if (gSaXVision.detectedSamusOnRight == TRUE)
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            else
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
        }
        else
        {
            if (gSaXVision.samusOnRight == FALSE)
            {
                if (gSaXVision.inXRange != FALSE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
            }

            if (SPRITE_GET_ISFT(gCurrentSprite))
            {
                gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
                gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;

                if (gSaXVision.samusOnRight == FALSE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                else
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            }
        }
    }
    else
    {
        if (gSaXVision.inYRange == TRUE)
        {
            gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
            gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;

            if (gSaXVision.detectedSamusOnRight == FALSE)
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            else
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
        }
        else
        {
            if (gSaXVision.samusOnRight == TRUE)
            {
                if (gSaXVision.inXRange != FALSE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
            }

            if (SPRITE_GET_ISFT(gCurrentSprite))
            {
                gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
                gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;

                if (gSaXVision.samusOnRight == TRUE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                else
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            }
        }
    }

    if (prevPose == gCurrentSprite.pose)
        return FALSE;

    return TRUE;
}

/**
 * @brief 1605c | 1c0 | Checks the terrain in front of the SA-X while on the ground, and makes it fall, jump over an obstacle (SA_X_JUMP_TYPE) or morph into a tunnel
 * 
 */
void SaXCheckFallJumpOrMorph(void)
{
    gCurrentSprite.SA_X_JUMP_TYPE = 0;
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
                gCurrentSprite.SA_X_JUMP_TYPE = 0x2;
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

            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE),
                gCurrentSprite.xPosition + (BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MORPHING_INIT;
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
                gCurrentSprite.SA_X_JUMP_TYPE = 0x2;
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

            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE),
                gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_MORPHING_INIT;
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
 * @brief 1621c | 8c | Initializes an SA-X sprite
 * 
 */
void SaXInit(void)
{
    gCurrentSprite.status |= SPRITE_STATUS_NOT_DRAWN;
    
    gCurrentSprite.drawOrder = 4;
    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(2.5f);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(0);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);

    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - PIXEL_SIZE * 2);
    gCurrentSprite.hitboxBottom = 0;
    gCurrentSprite.hitboxLeft = -QUARTER_BLOCK_SIZE;
    gCurrentSprite.hitboxRight = QUARTER_BLOCK_SIZE;

    // FIME
    // gCurrentSprite.pOam = sSaXOam_Idle;
    gCurrentSprite.pOam = sSaXOam_Placeholder;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.status &= ~SPRITE_STATUS_SAMUS_DETECTED;

    gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;
    gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);

    SpriteUtilMakeSpriteFaceSamusDirection();
    SaXSetDirection();

    gSaXData.animationDurationCounter = 0;
    gSaXData.currentAnimationFrame = 0;
    gSaXData.diagonalAim = DIAG_AIM_NONE;
    gSaXData.missilesArmed = FALSE;
    gSaXData.mosaic = FALSE;

    gCurrentSprite.SA_X_LANDED = 0;
}

/**
 * @brief 162a8 | 18 | Initializes the SA-X elevator sprite
 * 
 */
void SaXElevatorInit(void)
{
    SaXInit();
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
}

/**
 * @brief 162c0 | 34 | Initializes the SA-X to be falling
 * 
 */
void SaXFallingInit(void)
{
    gCurrentSprite.pose = SPRITE_POSE_FALLING;
    gCurrentSprite.SA_X_Y_SPEED_IDX = 0;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - PIXEL_SIZE * 2);

    SaXSetPose(SA_X_POSE_FALLING);

    gCurrentSprite.SA_X_LANDED = FALSE;
}

/**
 * @brief 162f4 | d4 | Handles the SA-X falling
 * 
 */
void SaXFalling(void)
{
    u32 blockTop;
    u8 offset;
    s16 movement;

    if (gCurrentSprite.SA_X_LANDED)
    {
        if (gSaXData.pose == SA_X_POSE_STANDING)
        {
            if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;

                if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
                {
                    if (gSaXVision.samusOnRight == FALSE)
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                }
                else
                {
                    if (gSaXVision.samusOnRight == TRUE)
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                }
            }
            else
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_STANDING_INIT;
            }
        }

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
 * @brief 163c8 | 28 | Initializes the SA-X to be standing
 * 
 */
void SaXStandingInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_STANDING;
    gCurrentSprite.SA_X_TIMER = 24;

    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - PIXEL_SIZE * 2);

    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 163f0 | a0 | Handles the SA-X standing
 * 
 */
void SaXStanding(void)
{
    u32 nslr;

    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
        return;
    }

    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER != 0)
        return;

    if (gSaXVision.inYRange == TRUE)
    {
        gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;

        nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 7 + HALF_BLOCK_SIZE,
            BLOCK_SIZE * 5 + QUARTER_BLOCK_SIZE + PIXEL_SIZE);

        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (nslr == NSLR_RIGHT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
                gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
            }
            else
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            }
        }
        else
        {
            if (nslr == NSLR_LEFT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
                gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
            }
            else
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            }
        }
    }
    else
    {
        gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING_INIT;
    }
}

/**
 * @brief 16490 | 2c | Initializes the SA-X to be walking
 * 
 */
void SaXWalkingInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING;
    gCurrentSprite.SA_X_X_SPEED_IDX = 0;

    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - PIXEL_SIZE * 2);

    SaXSetPose(SA_X_POSE_WALKING);
}

/**
 * @brief 164bc | 4c | Handles the SA-X walking
 * 
 */
void SaXWalking(void)
{
    if (SaXCheckStartChasingOrTurnAround())
        return;

    SaXCheckFallJumpOrMorph();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_WALKING)
        return;

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXWalkingSpeed[gCurrentSprite.SA_X_X_SPEED_IDX / 8]);

    if (gCurrentSprite.SA_X_X_SPEED_IDX < ARRAY_SIZE(sSaXWalkingSpeed) * 8 - 1)
        gCurrentSprite.SA_X_X_SPEED_IDX++;
}

/**
 * @brief 16508 | 24 | Initializes the SA-X to turn around
 * 
 */
void SaXTurningAroundInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND;

    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - PIXEL_SIZE * 2);

    SaXSetPose(SA_X_POSE_TURNING);
}

/**
 * @brief 1652c | 30 | Handles the SA-X turning around
 * 
 */
void SaXTurningAround(void)
{
    if (gSaXData.pose == SA_X_POSE_STANDING)
    {
        gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING_INIT;

        gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
        SaXSetDirection();
    }
}

/**
 * @brief 1655c | 24 | Initializes the SA-X to be turning around (chase start)
 * 
 */
void SaXTurningAroundChaseInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE;

    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - PIXEL_SIZE * 2);

    SaXSetPose(SA_X_POSE_TURNING);
}

/**
 * @brief 16580 | 48 | Handles the SA-X turning around (chase start)
 * 
 */
void SaXTurningAroundChase(void)
{
    if (gSaXData.pose == SA_X_POSE_STANDING)
    {
        gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
        SaXSetDirection();

        if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        else
            gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING_INIT;
    }
}

/**
 * @brief 165c8 | 34 | Initializes the SA-X to be running
 * 
 */
void SaXRunningInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING;
    gCurrentSprite.SA_X_X_SPEED_IDX = 0;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - PIXEL_SIZE * 2);

    if (!SaXCheckShootOrTurnTowardsSamus())
        SaXSetPose(SA_X_POSE_RUNNING);
}

/**
 * @brief 165fc | 4c | Handle the SA-X running
 * 
 */
void SaXRunning(void)
{
    if (SaXCheckShootOrTurnTowardsSamus())
        return;

    SaXCheckFallJumpOrMorph();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_RUNNING)
        return;

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXRunningSpeed[gCurrentSprite.SA_X_X_SPEED_IDX / 8]);

    if (gCurrentSprite.SA_X_X_SPEED_IDX < ARRAY_SIZE(sSaXRunningSpeed) * 8 - 1)
        gCurrentSprite.SA_X_X_SPEED_IDX++;
}

/**
 * @brief 16648 | 3c | Initializes the SA-X to be mid air
 * 
 */
void SaXMidAirInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_MID_AIR;
    gCurrentSprite.SA_X_Y_SPEED_IDX = 0;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE + QUARTER_BLOCK_SIZE);

    gCurrentSprite.yPosition -= HALF_BLOCK_SIZE;

    SaXSetPose(SA_X_POSE_MID_AIR);

    gCurrentSprite.SA_X_LANDED = 0;
}

/**
 * @brief 16684 | 1d8 | Handles the SA-X being mid air
 * 
 */
void SaXMidAir(void)
{
    u8 offset;
    s16 movement;
    s32 blockTop;

    if (gCurrentSprite.SA_X_LANDED != 0)
    {
        if (gSaXData.pose != SA_X_POSE_STANDING)
            return;

        if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
            {
                if (gSaXVision.samusOnRight == FALSE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            }
            else
            {
                if (gSaXVision.samusOnRight == TRUE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            }
        }
        else
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING_INIT;
        }

        return;
    }

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
    {
        movement = sSaXRunningSpeed[gCurrentSprite.SA_X_X_SPEED_IDX / 8];
    }
    else
    {
        movement = PIXEL_SIZE;
    }

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition + HALF_BLOCK_SIZE);
        if (gPreviousCollisionCheck != COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE, gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

            if (gPreviousCollisionCheck != COLLISION_SOLID)
                gCurrentSprite.xPosition += movement;
        }
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition - HALF_BLOCK_SIZE);
        if (gPreviousCollisionCheck != COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE, gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

            if (gPreviousCollisionCheck != COLLISION_SOLID)
                gCurrentSprite.xPosition -= movement;
        }
    }

    if (gCurrentSprite.SA_X_JUMP_TYPE == 1)
    {
        movement = sSaXJumpYVelocity_1[DIV_SHIFT(gCurrentSprite.SA_X_Y_SPEED_IDX, 4)];

        if (gCurrentSprite.SA_X_Y_SPEED_IDX < ARRAY_SIZE(sSaXJumpYVelocity_1) * 4 - 1)
            gCurrentSprite.SA_X_Y_SPEED_IDX++;
    }
    else if (gCurrentSprite.SA_X_JUMP_TYPE == 2)
    {
        movement = sSaXJumpYVelocity_2[DIV_SHIFT(gCurrentSprite.SA_X_Y_SPEED_IDX, 4)];

        if (gCurrentSprite.SA_X_Y_SPEED_IDX < ARRAY_SIZE(sSaXJumpYVelocity_2) * 4 - 1)
            gCurrentSprite.SA_X_Y_SPEED_IDX++;
    }
    else if (gCurrentSprite.SA_X_JUMP_TYPE == 3)
    {
        movement = sSaXJumpYVelocity_3[DIV_SHIFT(gCurrentSprite.SA_X_Y_SPEED_IDX, 4)];

        if (gCurrentSprite.SA_X_Y_SPEED_IDX < ARRAY_SIZE(sSaXJumpYVelocity_3) * 4 - 1)
            gCurrentSprite.SA_X_Y_SPEED_IDX++;
    }
    else if (gCurrentSprite.SA_X_JUMP_TYPE == 4)
    {
        movement = sSaXJumpYVelocity_4[DIV_SHIFT(gCurrentSprite.SA_X_Y_SPEED_IDX, 4)];

        if (gCurrentSprite.SA_X_Y_SPEED_IDX < ARRAY_SIZE(sSaXJumpYVelocity_4) * 4 - 1)
            gCurrentSprite.SA_X_Y_SPEED_IDX++;
    }
    else
    {
        movement = sSaXJumpYVelocity_0[DIV_SHIFT(gCurrentSprite.SA_X_Y_SPEED_IDX, 4)];

        if (gCurrentSprite.SA_X_Y_SPEED_IDX < ARRAY_SIZE(sSaXJumpYVelocity_0) * 4 - 1)
            gCurrentSprite.SA_X_Y_SPEED_IDX++;
    }

    gCurrentSprite.yPosition += movement;

    if (movement > 0)
    {
        blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition, gCurrentSprite.xPosition);

        if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
        {
            gCurrentSprite.yPosition = blockTop;
            gCurrentSprite.SA_X_LANDED = 1;
            SaXSetPose(SA_X_POSE_LANDING);
        }
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition);

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.yPosition -= movement;
        }
    }
}

/**
 * @brief 1685c | 44 | Initializes the SA-X to be aiming to shoot a beam
 * 
 */
void SaXDelayBeforeShootingBeamInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM;
    gCurrentSprite.SA_X_TIMER = 16;

    SaXSetPose(SA_X_POSE_STANDING);

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_NONE)
            gSaXData.diagonalAim = DIAG_AIM_NONE;
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_UP)
            gSaXData.diagonalAim = DIAG_AIM_UP;
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_DOWN)
            gSaXData.diagonalAim = DIAG_AIM_DOWN;
    }
    else
    {
        if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_NONE)
            gSaXData.diagonalAim = DIAG_AIM_NONE;
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_UP)
            gSaXData.diagonalAim = DIAG_AIM_UP;
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_DOWN)
            gSaXData.diagonalAim = DIAG_AIM_DOWN;
    }
}

/**
 * @brief 168a0 | b8 | Handles the SA-X aiming to shoot a beam
 * 
 */
void SaXDelayBeforeShootingBeam(void)
{
    u32 nslr;

    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
        return;
    }

    if (gCurrentSprite.SA_X_TIMER != 0)
    {
        gCurrentSprite.SA_X_TIMER--;
        return;
    }

    if (gSamusData.pose == SPOSE_FROZEN_AND_FALLING)
        return;

    if (gSamusData.pose == SPOSE_FROZEN)
    {
        nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 7 + HALF_BLOCK_SIZE,
            BLOCK_SIZE * 5 + QUARTER_BLOCK_SIZE + PIXEL_SIZE);

        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (nslr == NSLR_RIGHT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_MISSILE_INIT;
                gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
            }
            else if (nslr == NSLR_LEFT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            }
            else
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            }
        }
        else
        {
            if (nslr == NSLR_RIGHT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            }
            else if (nslr == NSLR_LEFT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_MISSILE_INIT;
                gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
            }
            else
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            }
        }
    }
    else
    {
        gCurrentSprite.pose = SA_X_SPRITE_POSE_SHOOTING_BEAM_INIT;
    }
}

void SaXShootingBeamInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_SHOOTING_BEAM;

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_NONE)
        {
            SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_NONE, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition + BLOCK_SIZE + PIXEL_SIZE, SPRITE_STATUS_X_FLIP);
        }
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_UP)
        {
            SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_UP, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition + BLOCK_SIZE + PIXEL_SIZE, SPRITE_STATUS_X_FLIP);
        }
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_DOWN)
        {
            SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_DOWN, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.yPosition - (BLOCK_SIZE - QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition + BLOCK_SIZE + PIXEL_SIZE, SPRITE_STATUS_X_FLIP);
        }
    }
    else
    {
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
    }

    gSaXData.missilesArmed = FALSE;
    SaXSetPose(SA_X_POSE_SHOOTING);
}

/**
 * @brief 16a7c | a8 | Handles the SA-X shooting a beam
 * 
 */
void SaXShootingBeam(void)
{
    u32 nslr;

    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
        return;
    }

    if (gSaXData.pose != SA_X_POSE_STANDING)
        return;

    if (gSaXVision.inYRange == FALSE)
    {
        gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        return;
    }

    nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 7 + HALF_BLOCK_SIZE,
        BLOCK_SIZE * 5 + QUARTER_BLOCK_SIZE + PIXEL_SIZE);

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (nslr == NSLR_RIGHT)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
            gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
        }
        else if (nslr == NSLR_LEFT)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
        }
        else
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        }
    }
    else
    {
        if (nslr == NSLR_RIGHT)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
        }
        else if (nslr == NSLR_LEFT)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
            gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
        }
        else
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        }
    }
}

/**
 * @brief 16b24 | 64 | Initializes the SA-X to be aiming to shoot a missile
 * 
 */
void SaXDelayBeforeShootingMissileInit(void)
{
    u8 aim;

    gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_MISSILE;
    gCurrentSprite.SA_X_TIMER = 0x28;

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_NONE)
            aim = DIAG_AIM_NONE;
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_UP)
            aim = DIAG_AIM_UP;
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_DOWN)
            aim = DIAG_AIM_DOWN;
    }
    else
    {
        if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_NONE)
            aim = DIAG_AIM_NONE;
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_UP)
            aim = DIAG_AIM_UP;
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_DOWN)
            aim = DIAG_AIM_DOWN;
    }

    if (aim != gSaXData.diagonalAim)
        gSaXData.diagonalAim = aim;
}

/**
 * @brief 16b88 | 24 | Handles the SA-X aiming to shoot a missile
 * 
 */
void SaXDelayBeforeShootingMissile(void)
{
    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER == 0)
        gCurrentSprite.pose = SA_X_SPRITE_POSE_SHOOTING_MISSILE_INIT;
}

/**
 * @brief 16bac | 104 | Initializes the SA-X to be shooting a missile
 * 
 */
void SaXShootingMissileInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_SHOOTING_MISSILE;

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_NONE)
        {
            SpriteSpawnSecondary(SSPRITE_SA_X_SUPER_MISSILE, DIAG_AIM_NONE, 0, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition + BLOCK_SIZE + PIXEL_SIZE, SPRITE_STATUS_X_FLIP);
        }
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_UP)
        {
            SpriteSpawnSecondary(SSPRITE_SA_X_SUPER_MISSILE, DIAG_AIM_UP, 0, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition + BLOCK_SIZE + PIXEL_SIZE, SPRITE_STATUS_X_FLIP);
        }
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_DOWN)
        {
            SpriteSpawnSecondary(SSPRITE_SA_X_SUPER_MISSILE, DIAG_AIM_DOWN, 0, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.yPosition - (BLOCK_SIZE - QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition + BLOCK_SIZE + PIXEL_SIZE, SPRITE_STATUS_X_FLIP);
        }
    }
    else
    {
        if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_NONE)
        {
            SpriteSpawnSecondary(SSPRITE_SA_X_SUPER_MISSILE, DIAG_AIM_NONE, 0, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition - (BLOCK_SIZE + PIXEL_SIZE), 0);
        }
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_UP)
        {
            SpriteSpawnSecondary(SSPRITE_SA_X_SUPER_MISSILE, DIAG_AIM_UP, 0, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition - (BLOCK_SIZE + PIXEL_SIZE), 0);
        }
        else if (gCurrentSprite.SA_X_DIAG_AIM == DIAG_AIM_DOWN)
        {
            SpriteSpawnSecondary(SSPRITE_SA_X_SUPER_MISSILE, DIAG_AIM_DOWN, 0, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.yPosition - (BLOCK_SIZE - QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition - (BLOCK_SIZE + PIXEL_SIZE), 0);
        }
    }

    gSaXData.missilesArmed = TRUE;
    SaXSetPose(SA_X_POSE_SHOOTING);
}

/**
 * @brief 16cb0 | 54 | Handles the SA-X shooting a missile
 * 
 */
void SaXShootingMissile(void)
{
    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
        return;
    }

    if (gSaXData.pose != SA_X_POSE_STANDING)
        return;

    if (gSaXVision.inYRange == FALSE)
        gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
    else
        gCurrentSprite.pose = SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_MISSILE_INIT;
}

/**
 * @brief 16d04 | 18 | Initializes the SA-X to be idle after shoting a missile
 * 
 */
void SaXIdleAfterShootingMissileInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_MISSILE;
    gCurrentSprite.SA_X_TIMER = 60;
}

/**
 * @brief 16d1c | 90 | Handles the SA-X being idle after shooting a missile
 * 
 */
void SaXIdleAfterShootingMissile(void)
{
    u32 nslr;

    gCurrentSprite.animationDurationCounter = 0;

    if (gCurrentSprite.SA_X_TIMER != 0)
    {
        gCurrentSprite.SA_X_TIMER--;
        return;
    }
    
    if (gSamusData.pose == SPOSE_FROZEN)
    {
        gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        return;
    }

    if (gSaXVision.inYRange == FALSE)
    {
        gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        return;
    }

    nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 7 + HALF_BLOCK_SIZE,
        BLOCK_SIZE * 5 + QUARTER_BLOCK_SIZE + PIXEL_SIZE);

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (nslr == NSLR_RIGHT)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
            gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
        }
        else if (nslr == NSLR_LEFT)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
        }
        else
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        }
    }
    else
    {
        if (nslr == NSLR_RIGHT)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
        }
        else if (nslr == NSLR_LEFT)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
            gCurrentSprite.SA_X_DIAG_AIM = gSaXVision.diagonalAim;
        }
        else
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        }
    }
}

/**
 * @brief 16dac | 24 | Initializes the SA-X to be morphing
 * 
 */
void SaXMorphingInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_MORPHING;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE + QUARTER_BLOCK_SIZE);

    SaXSetPose(SA_X_POSE_MORPHING);
}

/**
 * @brief 16dd0 | 20 | Handles the SA-X morphing
 * 
 */
void SaXMorphing(void)
{
    if (gSaXData.pose == SA_X_POSE_MORPH_BALL)
        gCurrentSprite.pose = SA_X_SPRITE_POSE_ROLLING_INIT;
}

/**
 * @brief 16df0 | 24 | Initializes the SA-X to be rolling
 * 
 */
void SaXRollingInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_ROLLING;
    gCurrentSprite.hitboxTop = -(HALF_BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_ROLLING);
}

/**
 * @brief 16e14 | b8 | Handles the SA-X rolling
 * 
 */
void SaXRolling(void)
{
    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - HALF_BLOCK_SIZE, gCurrentSprite.xPosition + (QUARTER_BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
            SaXSetDirection();
        }
        else
        {
            gCurrentSprite.xPosition += QUARTER_BLOCK_SIZE / 2;
            gCurrentSprite.rotation += Q_8_8(.065f);
        }
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - HALF_BLOCK_SIZE, gCurrentSprite.xPosition - (QUARTER_BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
            SaXSetDirection();
        }
        else
        {
            gCurrentSprite.xPosition -= QUARTER_BLOCK_SIZE / 2;
            gCurrentSprite.rotation -= Q_8_8(.065f);
        }
    }

    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition - BLOCK_SIZE);

    if (gPreviousCollisionCheck == COLLISION_AIR)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition + BLOCK_SIZE);
        if (gPreviousCollisionCheck == COLLISION_AIR)
            gCurrentSprite.pose = SA_X_SPRITE_POSE_UNMORPHING_INIT;
    }
}

/**
 * @brief 16ecc | 24 | Initializes the SA-X to be unmorphing
 * 
 */
void SaXUnmorphingInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_UNMORPHING;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE + QUARTER_BLOCK_SIZE);

    SaXSetPose(SA_X_POSE_UNMORPHING);
}

/**
 * @brief 16ef0 | 34 | Handles the SA-X unmorphing
 * 
 */
void SaXUnmorphing(void)
{
    if (gSaXData.pose != SA_X_POSE_STANDING)
        return;

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
        gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
    else
        gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING_INIT;
}

/**
 * @brief 16f24 | 2c | Initializes the SA-X to be aiming to shoot at a door
 * 
 */
void SaXIdleBeforeShootingDoorInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_IDLE_BEFORE_SHOOTING_DOOR;
    gCurrentSprite.SA_X_TIMER = 16;

    gSaXData.diagonalAim = DIAG_AIM_NONE;
    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 16f50 | 24 | Handles the SA-X aiming to shoot at a door
 * 
 */
void SaXIdleBeforeShootingDoor(void)
{
    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER == 0)
        gCurrentSprite.pose = SA_X_SPRITE_POSE_SHOOTING_DOOR_INIT;
}

/**
 * @brief 16f74 | 4c | Initializes the SA-X to be shooting a door
 * 
 */
void SaXShootingDoorInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_SHOOTING_DOOR;

    SpriteSpawnSecondary(SSPRITE_SA_X_ICE_BEAM, DIAG_AIM_NONE, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
        gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), gCurrentSprite.xPosition - (BLOCK_SIZE + PIXEL_SIZE), 0);

    gSaXData.missilesArmed = FALSE;
    SaXSetPose(SA_X_POSE_SHOOTING);
}

/**
 * @brief 16fc0 | 20 | Handles the SA-X shooting a door
 * 
 */
void SaXShootingDoor(void)
{
    if (gSaXData.pose == SA_X_POSE_STANDING)
        gCurrentSprite.pose = SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_DOOR_INIT;
}

/**
 * @brief 16fe0 | 28 | Initializes the SA-X to be idle after shooting a door
 * 
 */
void SaXIdleAfterShootingDoorInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_DOOR;
    gCurrentSprite.SA_X_TIMER = 24;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_STANDING);
}

/**
 * @brief 17008 | 24 | Handles the SA-X being idle after shooting a door
 * 
 */
void SaXIdleAfterShootingDoor(void)
{
    gCurrentSprite.SA_X_TIMER--;
    if (gCurrentSprite.SA_X_TIMER == 0)
        gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING_TO_DOOR_INIT;
}

/**
 * @brief 1702c | 2c | Initializes the SA-X to be walking to a door
 * 
 */
void SaXWalkingToDoorInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_WALKING_TO_DOOR;
    gCurrentSprite.SA_X_X_SPEED_IDX = 0;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_WALKING);
}

/**
 * @brief 17058 | b8 | Handles the SA-X walking to a door
 * 
 */
void SaXWalkingToDoor(void)
{
    if (gSaXVision.inYRange == TRUE)
    {
        gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
        gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;

        if (gSaXVision.detectedSamusOnRight == FALSE)
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
        else
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;

        return;
    }

    if (SPRITE_GET_ISFT(gCurrentSprite))
    {
        gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
        gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;

        if (gSaXVision.samusOnRight == TRUE)
            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
        else
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;

        return;
    }

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXWalkingSpeed[gCurrentSprite.SA_X_X_SPEED_IDX / 8]);

    if (gCurrentSprite.SA_X_X_SPEED_IDX < ARRAY_SIZE(sSaXWalkingSpeed) * 8 - 1)
        gCurrentSprite.SA_X_X_SPEED_IDX++;
    
    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE, gCurrentSprite.xPosition + HALF_BLOCK_SIZE);
    if (gPreviousCollisionCheck == COLLISION_SOLID)
        gCurrentSprite.status = 0;
}

/**
 * @brief 17110 | d0 | Initializes an SA-X ice beam sprite
 * 
 */
void SaXBeamInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.samusCollision = SSC_SA_X_ICE_BEAM;

    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);

    gCurrentSprite.hitboxTop = -(QUARTER_BLOCK_SIZE - PIXEL_SIZE);
    gCurrentSprite.hitboxBottom = QUARTER_BLOCK_SIZE - PIXEL_SIZE;
    gCurrentSprite.hitboxLeft = -(QUARTER_BLOCK_SIZE - PIXEL_SIZE);
    gCurrentSprite.hitboxRight = QUARTER_BLOCK_SIZE - PIXEL_SIZE;

    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.SA_X_PROJECTILE_TIMER = 60;
    gCurrentSprite.SA_X_BEAM_MOVEMENT_IDX = 0;

    gCurrentSprite.pose = 0x2;
    gCurrentSprite.drawOrder = 3;

    if (gCurrentSprite.roomSlot == DIAG_AIM_NONE)
    {
        gCurrentSprite.pOam = sSaXBeamOam_Forward;
    }
    else if (gCurrentSprite.roomSlot == DIAG_AIM_UP)
    {
        gCurrentSprite.pOam = sSaXBeamOam_Diagonal;
    }
    else if (gCurrentSprite.roomSlot == DIAG_AIM_DOWN)
    {
        gCurrentSprite.pOam = sSaXBeamOam_Diagonal;
        gCurrentSprite.status |= SPRITE_STATUS_Y_FLIP;
    }
    else if (gCurrentSprite.roomSlot == 0x80)
    {
        gCurrentSprite.status |= SPRITE_STATUS_NOT_DRAWN;
        gCurrentSprite.pOam = sSaXBeamOam_Forward;
        gCurrentSprite.samusCollision = SSC_NONE;
    }
    else
    {
        gCurrentSprite.status = 0;
        return;
    }

    SoundPlay(0x25C);
}

/**
 * @brief 171e0 | 130 | Handles an SA-X ice beam moving
 * 
 */
void SaXBeamMove(void)
{
    u8 offset;
    s16 yMovement;
    s16 xMovement;

    offset = gCurrentSprite.SA_X_BEAM_MOVEMENT_IDX;

    switch (gCurrentSprite.roomSlot)
    {
        case DIAG_AIM_UP:
            gCurrentSprite.yPosition -= (QUARTER_BLOCK_SIZE - ONE_SUB_PIXEL);

            if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            {
                gCurrentSprite.xPosition += (QUARTER_BLOCK_SIZE - ONE_SUB_PIXEL);

                yMovement = sSaXBeamDiagonalYMovement[offset];
                xMovement = yMovement;
                if (yMovement == SHORT_MAX)
                {
                    offset = 0;
                    yMovement = sSaXBeamDiagonalYMovement[0];
                    xMovement = yMovement;
                }
            }
            else
            {
                gCurrentSprite.xPosition -= (QUARTER_BLOCK_SIZE - ONE_SUB_PIXEL);

                yMovement = sSaXBeamDiagonalYMovement[offset];
                xMovement = sSaXBeamDiagonalXMovement[offset];
                if (yMovement == SHORT_MAX)
                {
                    offset = 0;
                    yMovement = sSaXBeamDiagonalYMovement[0];
                    xMovement = sSaXBeamDiagonalXMovement[0];
                }
            }

            gCurrentSprite.SA_X_BEAM_MOVEMENT_IDX = offset + 1;
            gCurrentSprite.yPosition += yMovement;
            gCurrentSprite.xPosition += xMovement;
            break;

        case DIAG_AIM_DOWN:
            gCurrentSprite.yPosition += (QUARTER_BLOCK_SIZE - ONE_SUB_PIXEL);

            if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            {
                gCurrentSprite.xPosition += (QUARTER_BLOCK_SIZE - ONE_SUB_PIXEL);

                yMovement = sSaXBeamDiagonalYMovement[offset];
                xMovement = sSaXBeamDiagonalXMovement[offset];
                if (yMovement == SHORT_MAX)
                {
                    offset = 0;
                    yMovement = sSaXBeamDiagonalYMovement[0];
                    xMovement = sSaXBeamDiagonalXMovement[0];
                }
            }
            else
            {
                gCurrentSprite.xPosition -= (QUARTER_BLOCK_SIZE - ONE_SUB_PIXEL);

                yMovement = sSaXBeamDiagonalYMovement[offset];
                xMovement = yMovement;
                if (yMovement == SHORT_MAX)
                {
                    offset = 0;
                    yMovement = sSaXBeamDiagonalYMovement[0];
                    xMovement = yMovement;
                }
            }

            gCurrentSprite.SA_X_BEAM_MOVEMENT_IDX = offset + 1;
            gCurrentSprite.yPosition += yMovement;
            gCurrentSprite.xPosition += xMovement;
            break;

        default:
            if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
                gCurrentSprite.xPosition += QUARTER_BLOCK_SIZE + PIXEL_SIZE;
            else
                gCurrentSprite.xPosition -= QUARTER_BLOCK_SIZE + PIXEL_SIZE;

            yMovement = sSaXBeamForwardYMovement[offset];
            if (yMovement == SHORT_MAX)
            {
                offset = 0;
                yMovement = sSaXBeamForwardYMovement[0];
            }

            gCurrentSprite.SA_X_BEAM_MOVEMENT_IDX = offset + 1;
            gCurrentSprite.yPosition += yMovement;
            break;
    }

    gCurrentClipdataAffectingAction = 0x6;
    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition);

    if (!(gCurrentSprite.status & SPRITE_STATUS_ONSCREEN))
    {
        gCurrentSprite.SA_X_PROJECTILE_TIMER--;
        if (gCurrentSprite.SA_X_PROJECTILE_TIMER == 0)
            gCurrentSprite.status = 0;
    }
}

/**
 * @brief 17310 | a8 | Initializes an SA-X super missile sprite
 * 
 */
void SaXMissileInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.samusCollision = SSC_SA_X_SUPER_MISSILE;

    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);

    gCurrentSprite.hitboxTop = -(QUARTER_BLOCK_SIZE - PIXEL_SIZE);
    gCurrentSprite.hitboxBottom = QUARTER_BLOCK_SIZE - PIXEL_SIZE;
    gCurrentSprite.hitboxLeft = -(QUARTER_BLOCK_SIZE - PIXEL_SIZE);
    gCurrentSprite.hitboxRight = QUARTER_BLOCK_SIZE - PIXEL_SIZE;

    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.SA_X_PROJECTILE_TIMER = 60;

    gCurrentSprite.pose = 0x2;
    gCurrentSprite.drawOrder = 3;

    if (gCurrentSprite.roomSlot == DIAG_AIM_NONE)
    {
        gCurrentSprite.pOam = sSaXMissileOam_Forward;
    }
    else if (gCurrentSprite.roomSlot == DIAG_AIM_UP)
    {
        gCurrentSprite.pOam = sSaXMissileOam_Diagonal;
    }
    else if (gCurrentSprite.roomSlot == DIAG_AIM_DOWN)
    {
        gCurrentSprite.pOam = sSaXMissileOam_Diagonal;
        gCurrentSprite.status |= SPRITE_STATUS_Y_FLIP;
    }
    else
    {
        gCurrentSprite.status = 0;
        return;
    }

    SoundPlay(0x25D);
}

/**
 * @brief 173b8 | 34 | Handles an SA-X super missile exploding
 * 
 */
void SaXMissileExploding(void)
{
    gCurrentSprite.status = 0;
    ParticleSet(gCurrentSprite.yPosition, gCurrentSprite.xPosition, PE_SUPER_MISSILE_EXPLOSION_NO_SCREEN_SHAKE);
    SoundPlay(0x25E);

    ScreenShakeStartHorizontal(40, 0x80 | 1);
    ScreenShakeStartVertical(40, 0x80 | 1);
}

/**
 * @brief 173ec | ac | Handles an SA-X super missile moving
 * 
 */
void SaXMissileMoving(void)
{
    switch (gCurrentSprite.roomSlot)
    {
        case DIAG_AIM_UP:
            gCurrentSprite.yPosition -= SA_X_MISSILE_DIAGONAL_SPEED;
            if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
                gCurrentSprite.xPosition += SA_X_MISSILE_DIAGONAL_SPEED;
            else
                gCurrentSprite.xPosition -= SA_X_MISSILE_DIAGONAL_SPEED;
            break;

        case DIAG_AIM_DOWN:
            gCurrentSprite.yPosition += SA_X_MISSILE_DIAGONAL_SPEED;
            if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
                gCurrentSprite.xPosition += SA_X_MISSILE_DIAGONAL_SPEED;
            else
                gCurrentSprite.xPosition -= SA_X_MISSILE_DIAGONAL_SPEED;
            break;

        default:
            if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
                gCurrentSprite.xPosition += SA_X_MISSILE_SPEED;
            else
                gCurrentSprite.xPosition -= SA_X_MISSILE_SPEED;
    }

    gCurrentClipdataAffectingAction = 0x8;

    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition);

    if (gPreviousCollisionCheck == COLLISION_SOLID)
    {
        SaXMissileExploding();
        return;
    }

    if (!(gCurrentSprite.status & SPRITE_STATUS_ONSCREEN))
    {
        gCurrentSprite.SA_X_PROJECTILE_TIMER--;
        if (gCurrentSprite.SA_X_PROJECTILE_TIMER == 0)
            gCurrentSprite.status = 0;
    }
}

/**
 * @brief 17498 | 74 | Initializes an SA-X power bomb sprite
 * 
 */
void SaXPowerBombInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.samusCollision = SSC_NONE;

    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(0);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);

    gCurrentSprite.hitboxTop = -PIXEL_SIZE;
    gCurrentSprite.hitboxBottom = PIXEL_SIZE;
    gCurrentSprite.hitboxLeft = -PIXEL_SIZE;
    gCurrentSprite.hitboxRight = PIXEL_SIZE;

    gCurrentSprite.pOam = sSaXPowerBombOam_SpinningSlow;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.pose = 0x2;
    gCurrentSprite.SA_X_PROJECTILE_TIMER = 60;
    gCurrentSprite.bgPriority = 1;

    SoundPlay(0x260);
}

/**
 * @brief 1750c | 40 | Handles an SA-X power bomb spinning slowly
 * 
 */
void SaXPowerBombSpinningSlowly(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;
    
    gCurrentSprite.SA_X_PROJECTILE_TIMER--;
    if (gCurrentSprite.SA_X_PROJECTILE_TIMER == 0)
    {
        gCurrentSprite.pOam = sSaXPowerBombOam_SpinningFast;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;

        gCurrentSprite.SA_X_PROJECTILE_TIMER = 60;
        gCurrentSprite.pose = 0x18;
    }
}

/**
 * @brief 1754c | 50 | Handles an SA-X power bomb spinning quickly
 * 
 */
void SaXPowerBombSpinningQuickly(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;
    
    gCurrentSprite.SA_X_PROJECTILE_TIMER--;
    if (gCurrentSprite.SA_X_PROJECTILE_TIMER == 0)
    {
        PowerBombExplosionStart(gCurrentSprite.xPosition, gCurrentSprite.yPosition, TRUE);

        gCurrentSprite.status |= SPRITE_STATUS_NOT_DRAWN;
        gCurrentSprite.samusCollision = SSC_SA_X_POWER_BOMB;
        gCurrentSprite.pose = 0x1A;

        SoundPlay(0x261);
    }
}

/**
 * @brief 1759c | 2c | Handles an SA-X power bomb spinning exploding
 * 
 */
void SaXPowerBombExploding(void)
{
    gCurrentSprite.hitboxTop = gCurrentPowerBomb.hitboxTop;
    gCurrentSprite.hitboxBottom = gCurrentPowerBomb.hitboxBottom;
    gCurrentSprite.hitboxLeft = gCurrentPowerBomb.hitboxLeft;
    gCurrentSprite.hitboxRight = gCurrentPowerBomb.hitboxRight;

    if (gCurrentPowerBomb.animationState == 0)
        gCurrentSprite.status = 0;
}

/**
 * @brief 175c8 | 6c | Initializes a lab explosion sprite
 * 
 */
void LabExplosionInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.samusCollision = SSC_NONE;

    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(3.5f);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(0);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1.5f);

    gCurrentSprite.hitboxTop = -PIXEL_SIZE;
    gCurrentSprite.hitboxBottom = PIXEL_SIZE;
    gCurrentSprite.hitboxLeft = -PIXEL_SIZE;
    gCurrentSprite.hitboxRight = PIXEL_SIZE;

    gCurrentSprite.pOam = sLabExplosionOam_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.LAB_EXPLOSION_ALTERNATE = 0;
    gCurrentSprite.pose = 0x2;
    gCurrentSprite.drawOrder = 12;
}

/**
 * @brief 17634 | 494 | Handles a lab explosion exploding
 * 
 */
void LabExplosionExploding(void)
{
    u8 var_0;
    u8 var_1;
    u8 rng;
    u8 ramSlot;
    u16 yPosition;
    u16 xPosition;

    var_0 = FALSE;
    var_1 = FALSE;
    rng = MOD_AND(gSpriteRandomNumber, 4);

    yPosition = gCurrentSprite.yPosition;
    xPosition = gCurrentSprite.xPosition;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    if (gCurrentSprite.animationDurationCounter == 2)
    {
        var_0 = TRUE;

        switch (gCurrentSprite.currentAnimationFrame)
        {
            case 2:
                yPosition -= BLOCK_SIZE * 7;
                xPosition += BLOCK_SIZE * 2;
                break;

            case 5:
                yPosition -= BLOCK_SIZE * 6;
                xPosition -= BLOCK_SIZE * 2;
                break;

            case 8:
                yPosition -= BLOCK_SIZE * 7;
                xPosition -= BLOCK_SIZE * 3;
                break;

            case 11:
                yPosition -= BLOCK_SIZE * 6;
                xPosition += BLOCK_SIZE * 3;
                break;

            case 14:
                yPosition -= BLOCK_SIZE * 5;
                xPosition += BLOCK_SIZE * 4;
                break;

            case 17:
                yPosition -= BLOCK_SIZE * 6;
                xPosition += BLOCK_SIZE * 1;
                break;

            case 20:
                yPosition -= BLOCK_SIZE * 8;
                xPosition -= BLOCK_SIZE * 1;
                break;

            case 23:
                yPosition -= BLOCK_SIZE * 5;
                xPosition -= BLOCK_SIZE * 4;
                break;

            case 26:
                yPosition -= BLOCK_SIZE * 4;
                xPosition -= BLOCK_SIZE * 5;
                break;

            case 29:
                yPosition -= BLOCK_SIZE * 3;
                xPosition -= BLOCK_SIZE * 6;
                break;

            case 32:
                yPosition -= BLOCK_SIZE * 5;
                xPosition += BLOCK_SIZE * 5;
                break;

            case 35:
                yPosition -= BLOCK_SIZE * 4;
                xPosition -= BLOCK_SIZE * 4;
                break;

            case 38:
                yPosition -= BLOCK_SIZE * 2;
                xPosition -= BLOCK_SIZE * 4;
                break;

            case 41:
                yPosition -= BLOCK_SIZE * 3;
                xPosition += BLOCK_SIZE * 3;
                break;

            case 44:
                yPosition -= BLOCK_SIZE * 2;
                xPosition += BLOCK_SIZE * 5;
                break;

            case 47:
                yPosition -= BLOCK_SIZE * 6;
                xPosition -= BLOCK_SIZE * 6;

                gCurrentSprite.LAB_EXPLOSION_ALTERNATE ^= 1;
                break;

            default:
                var_0 = FALSE;
        }
    }

    if (var_0)
    {
        if (gSpriteData[ramSlot].pose == SA_X_LAB_POSE_SHOOTING_LAB)
        {
            ParticleSet(yPosition, xPosition, PE_SUPER_MISSILE_EXPLOSION_NO_SCREEN_SHAKE);
            ParticleSet(yPosition, xPosition, PE_TAIL_EXPLOSION_SMOKE);
            SoundPlay(0x25E);
        }
        else if (gSpriteData[ramSlot].pose == SA_X_LAB_POSE_GETTING_COVERED_BY_METROIDS)
        {
            ParticleSet(yPosition, xPosition, PE_SUPER_MISSILE_EXPLOSION_NO_SCREEN_SHAKE);
            ParticleSet(yPosition, xPosition, PE_TAIL_EXPLOSION_SMOKE);
            SoundPlay(0x25E);
        }
        else if (gSpriteData[ramSlot].pose == SA_X_LAB_POSE_COVERED_BY_METROIDS_AFTER_DETACHMENT)
        {
            if (gCurrentSprite.LAB_EXPLOSION_ALTERNATE != 0)
            {
                if (MOD_AND(gCurrentSprite.currentAnimationFrame, 2) != 0)
                {
                    ParticleSet(yPosition, xPosition, PE_EXPLOSION_7);
                    SoundPlayOnUnusedMusicTrack(0x23F);
                }
            }
            else
            {
                if (MOD_AND(gCurrentSprite.currentAnimationFrame, 2) == 0)
                {
                    ParticleSet(yPosition, xPosition, PE_EXPLOSION_7);
                    SoundPlayOnUnusedMusicTrack(0x23F);
                }
            }

            ScreenShakeStartHorizontal(20, 0x80 | 1);
            ScreenShakeStartVertical(20, 0x80 | 1);
        }
    }

    if (gSpriteData[ramSlot].pose == SA_X_LAB_POSE_COVERED_BY_METROIDS_AFTER_DETACHMENT)
    {
        if (gSamusData.yPosition < gXParasiteTargetYPosition - (BLOCK_SIZE * 2 + HALF_BLOCK_SIZE))
        {
            gCurrentSprite.yPosition = gSamusData.yPosition + BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE;
            var_1++;
        }
        else
        {
            gCurrentSprite.yPosition = gXParasiteTargetYPosition;
        }

        if (!var_0 && MOD_AND(gCurrentSprite.currentAnimationFrame, 2) && gCurrentSprite.animationDurationCounter == 1 && gSpriteRandomNumber > 7)
        {
            if (!var_1)
            {
                if (gSpriteRandomNumber >= 12)
                {
                    if (MOD_AND(gSpriteRandomNumber, 2))
                    {
                        ParticleSet(yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE - PIXEL_SIZE) + gSpriteRandomNumber * 8, xPosition + (gSpriteRandomNumber << rng), PE_EXPLOSION_8);
                    }
                    else
                    {
                        ParticleSet(yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE + PIXEL_SIZE + PIXEL_SIZE / 2) + gSpriteRandomNumber * 8, xPosition + (gSpriteRandomNumber << rng), PE_TAIL_SMOKE_2);
                    }
                }
                else
                {
                    if (MOD_AND(gSpriteRandomNumber, 2))
                    {
                        ParticleSet(yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE - PIXEL_SIZE) + gSpriteRandomNumber * 8, xPosition - (gSpriteRandomNumber << rng), PE_EXPLOSION_8);
                    }
                    else
                    {
                        ParticleSet(yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE + PIXEL_SIZE + PIXEL_SIZE / 2) + gSpriteRandomNumber * 8, xPosition - (gSpriteRandomNumber << rng), PE_TAIL_SMOKE_2);
                    }
                }
            }
            else
            {
                if (gSpriteRandomNumber >= 12)
                {
                    if (MOD_AND(gSpriteRandomNumber, 2))
                    {
                        ParticleSet(yPosition - (BLOCK_SIZE * 5) + gSpriteRandomNumber * 32, xPosition + (gSpriteRandomNumber << rng), PE_EXPLOSION_8);
                    }
                    else
                    {
                        ParticleSet(yPosition - (BLOCK_SIZE * 5 + QUARTER_BLOCK_SIZE / 2 + PIXEL_SIZE / 2) + gSpriteRandomNumber * 32, xPosition + (gSpriteRandomNumber << rng), PE_TAIL_SMOKE_2);
                    }
                }
                else
                {
                    if (MOD_AND(gSpriteRandomNumber, 2))
                    {
                        ParticleSet(yPosition - (BLOCK_SIZE * 5) + gSpriteRandomNumber * 32, xPosition - (gSpriteRandomNumber << rng), PE_EXPLOSION_8);
                    }
                    else
                    {
                        ParticleSet(yPosition - (BLOCK_SIZE * 5 + QUARTER_BLOCK_SIZE / 2 + PIXEL_SIZE / 2) + gSpriteRandomNumber * 32, xPosition - (gSpriteRandomNumber << rng), PE_TAIL_SMOKE_2);
                    }
                }
            }

            if (MOD_AND(gSpriteRandomNumber, 2))
                SoundPlayNotAlreadyPlaying(0x240);
            else
                SoundPlayNotAlreadyPlaying(0x241);
        }
    }

    if (gSpriteData[ramSlot].pose == SA_X_LAB_POSE_COVERED_BY_METROIDS)
        gCurrentSprite.status |= SPRITE_STATUS_NOT_DRAWN;
}

/**
 * @brief 17ac8 | 94 | Updates the graphics of the SA-X
 * 
 */
void SaXUpdateGraphics(void)
{
    u8 newPose;
    u16 yPosition;
    u16 xPosition;

    SpriteCheckOnScreen();

    gSaXData.yPosition = gCurrentSprite.yPosition;
    gSaXData.xPosition = gCurrentSprite.xPosition;
    gSaXData.paletteRow = gCurrentSprite.paletteRow;

    newPose = sSaXPoseGfxFunctionPointers[gSaXData.pose]();
    if (newPose != SA_X_POSE_NONE)
        SaXSetPose(newPose);

    if (gCurrentSprite.status & SPRITE_STATUS_EXISTS && !(gCurrentSprite.status & SPRITE_STATUS_HIDDEN))
    {
        if (gCurrentSprite.status & SPRITE_STATUS_ONSCREEN)
            gSaXData.screenFlag = SA_X_SCREEN_FLAG_ON_SCREEN;
        else
            gSaXData.screenFlag = SA_X_SCREEN_FLAG_OFF_SCREEN;

        yPosition = gCurrentSprite.yPosition;
        xPosition = gCurrentSprite.xPosition;
    }
    else
    {
        gSaXData.screenFlag = SA_X_SCREEN_FLAG_NOT_PRESENT;
        yPosition = USHORT_MAX;
        xPosition = USHORT_MAX;
    }

    gSaXSpawnPosition.y = yPosition;
    gSaXSpawnPosition.x = xPosition;
}

/**
 * @brief 17b5c | 7c | Updates the free timer of the SA-X
 * 
 * @return u8 bool, frozen
 */
u8 SaXUpdateFreezeTimer(void)
{
    u8 freezeTimer;
    
    if (gCurrentSprite.freezeTimer != 0)
    {
        if (gCurrentSprite.freezeTimer > 3)
            gCurrentSprite.freezeTimer -= 3;
        else
            gCurrentSprite.freezeTimer = 0;

        freezeTimer = gCurrentSprite.freezeTimer;
        gSaXData.animationDurationCounter--;

        if (freezeTimer <= 90)
        {
            if (MOD_AND(freezeTimer, 4) == 0)
            {
                if (freezeTimer & 4)
                    gCurrentSprite.paletteRow = 15 - (gCurrentSprite.spritesetGfxSlot + gCurrentSprite.frozenPaletteRowOffset);
                else
                    gCurrentSprite.paletteRow = 0;
            }
        }

        SaXUpdateGraphics();
        return TRUE;
    }

    return FALSE;
}

/**
 * @brief 17bd8 | 2bc | SA-X elevator AI
 * 
 */
void SaXElevator(void)
{
    if (SaXUpdateFreezeTimer())
        return;

    SaXSeeAndLocateSamus();

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
    {
        if (gSaXVision.inYRange == TRUE)
        {
            gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 0;
        }
        else
        {
            if (gCurrentSprite.SA_X_LOST_SAMUS_TIMER >= 60 * 20)
            {
                gCurrentSprite.status &= ~SPRITE_STATUS_SAMUS_DETECTED;
            }
            else
            {
                if (gCurrentSprite.status & SPRITE_STATUS_ONSCREEN)
                    gCurrentSprite.SA_X_LOST_SAMUS_TIMER += 4;
                else
                    gCurrentSprite.SA_X_LOST_SAMUS_TIMER += 1;
            }
        }
    }

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SaXElevatorInit();

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

        case SA_X_SPRITE_POSE_WALKING_INIT:
            SaXWalkingInit();
            break;

        case SA_X_SPRITE_POSE_WALKING:
            SaXWalking();
            break;

        case SA_X_SPRITE_POSE_TURNING_AROUND_INIT:
            SaXTurningAroundInit();

        case SA_X_SPRITE_POSE_TURNING_AROUND:
            SaXTurningAround();
            break;

        case SA_X_SPRITE_POSE_RUNNING_INIT:
            SaXRunningInit();

        case SA_X_SPRITE_POSE_RUNNING:
            SaXRunning();

            if (gCurrentSprite.pose != SA_X_SPRITE_POSE_MID_AIR_INIT)
                break;

            if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
            {
                if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE), gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

                    if (gPreviousCollisionCheck != COLLISION_SOLID)
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + HALF_BLOCK_SIZE), gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

                        if (gPreviousCollisionCheck == COLLISION_SOLID)
                        {
                            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
                            gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 60 * 20;
                        }
                    }
                    else
                    {
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
                        gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 60 * 20;
                    }
                }
                else
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 3 + HALF_BLOCK_SIZE), gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

                    if (gPreviousCollisionCheck != COLLISION_SOLID)
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + HALF_BLOCK_SIZE), gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

                        if (gPreviousCollisionCheck == COLLISION_SOLID)
                        {
                            gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
                            gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 60 * 20;
                        }
                    }
                    else
                    {
                        gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
                        gCurrentSprite.SA_X_LOST_SAMUS_TIMER = 60 * 20;
                    }
                }
            }
            else
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_INIT;
            }
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

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT:
            SaXTurningAroundChaseInit();

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE:
            SaXTurningAroundChase();
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
            break;

        default:
            SaXStandingInit();
    }

    SaXUpdateGraphics();
}

/**
 * @brief 17e94 | 20 | SA-X ice beam AI
 * 
 */
void SaXBeam(void)
{
    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SaXBeamInit();
            break;

        default:
            SaXBeamMove();
    }
}

/**
 * @brief 17eb4 | 2c | SA-X super missile AI
 * 
 */
void SaXMissile(void)
{
    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SaXMissileInit();
            break;

        case 0x37:
            SaXMissileExploding();
            break;

        default:
            SaXMissileMoving();
    }
}

/**
 * @brief 17ee0 | 40 | SA-X power bomb explosion
 * 
 */
void SaXPowerBomb(void)
{
    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SaXPowerBombInit();
            break;

        case 0x2:
            SaXPowerBombSpinningSlowly();
            break;

        case 0x18:
            SaXPowerBombSpinningQuickly();
            break;

        case 0x1A:
            SaXPowerBombExploding();
            break;
    }
}

/**
 * @brief 17f20 | 30 | Lab explosion AI
 * 
 */
void LabExplosion(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            LabExplosionInit();
            break;

        case 0x2:
            LabExplosionExploding();
    }
}
