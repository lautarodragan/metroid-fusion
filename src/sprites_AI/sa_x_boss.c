#include "sprites_AI/sa_x_boss.h"
#include "sprites_AI/sa_x.h"
#include "macros.h"
#include "gba.h"
#include "globals.h"

#include "data/sprites/sa_x.h"
#include "data/sprite_data.h"
#include "data/sprite_pointers.h"

#include "constants/audio.h"
#include "constants/clipdata.h"
#include "constants/sprite.h"
#include "constants/samus.h"
#include "constants/sa_x.h"

#include "structs/sprite.h"
#include "structs/samus.h"
#include "structs/sa_x.h"

/**
 * @brief 19e34 | 460 | Checks the running collisions for the SA-X (boss)
 * 
 */
void SaXBossCheckCollisionRunning(void)
{
    u8 var_0;
    u8 var_1;

    var_0 = FALSE;
    var_1 = FALSE;
    gCurrentSprite.work2 = DIAG_AIM_NONE;

    SpriteUtilAlignYPositionOnSlopeAtOrigin();

    if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
    {
        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            SpriteUtilCheckVerticalCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition - QUARTER_BLOCK_SIZE);

            if (gPreviousVerticalCollisionCheck == COLLISION_AIR)
            {
                gCurrentSprite.pose = SA_X_BOSS_POSE_SPIN_JUMPING_INIT;
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
                gCurrentSprite.pose = SA_X_BOSS_POSE_SPIN_JUMPING_INIT;
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
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
                gCurrentSprite.xPosition + (BLOCK_SIZE * 4 + HALF_BLOCK_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                var_0 = TRUE;
            }
            else
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2),
                    gCurrentSprite.xPosition + (BLOCK_SIZE * 4 + HALF_BLOCK_SIZE));

                if (gPreviousCollisionCheck == COLLISION_SOLID)
                    var_0 = TRUE;
            }

            if (var_0)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_SIZE * 4,
                    gCurrentSprite.xPosition + (BLOCK_SIZE * 2 + HALF_BLOCK_SIZE));
    
                if (gPreviousCollisionCheck == COLLISION_AIR)
                {
                    if (gSamusData.yPosition < gCurrentSprite.yPosition + (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2))
                    {
                        if (gCurrentSprite.work3 < 20)
                            gCurrentSprite.work3 = 20;
    
                        gCurrentSprite.work2 = 0x2;
                    }
                }
            }
    
            gCurrentSprite.pose = SA_X_BOSS_POSE_SPIN_JUMPING_INIT;
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
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return;
            }
        }

        if (gCurrentSprite.workY >= 60 * 3)
            return;

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 3 - PIXEL_SIZE),
            gCurrentSprite.xPosition + (BLOCK_SIZE * 3));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 5 - QUARTER_BLOCK_SIZE / 2),
                gCurrentSprite.xPosition + BLOCK_SIZE * 3);

            if (gPreviousCollisionCheck != COLLISION_AIR)
                return;

            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE - PIXEL_SIZE),
                gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

            if (gPreviousCollisionCheck == COLLISION_AIR)
            {
                if (gSamusData.yPosition < gCurrentSprite.yPosition - (BLOCK_SIZE * 4 - QUARTER_BLOCK_SIZE))
                {
                    if (gCurrentSprite.work3 < 8)
                        gCurrentSprite.work3 = 8;

                    gCurrentSprite.work2 = 0x2;
                    gCurrentSprite.pose = SA_X_BOSS_POSE_SPIN_JUMPING_INIT;
                }
            }
        }
    }
    else
    {
        if (!(gPreviousVerticalCollisionCheck & 0xF0))
            return;

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

        if (gPreviousCollisionCheck == COLLISION_AIR)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
                gCurrentSprite.xPosition - (BLOCK_SIZE * 4 + HALF_BLOCK_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                var_0 = TRUE;
            }
            else
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2),
                    gCurrentSprite.xPosition - (BLOCK_SIZE * 4 + HALF_BLOCK_SIZE));

                if (gPreviousCollisionCheck == COLLISION_SOLID)
                    var_0 = TRUE;
            }

            if (var_0)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_SIZE * 4,
                    gCurrentSprite.xPosition - (BLOCK_SIZE * 2 + HALF_BLOCK_SIZE));

                if (gPreviousCollisionCheck == COLLISION_AIR)
                {
                    if (gSamusData.yPosition > gCurrentSprite.yPosition - (BLOCK_SIZE * 7 - QUARTER_BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2))
                    {
                        if (gSamusData.yPosition < gCurrentSprite.yPosition + (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2))
                        {
                            if (gCurrentSprite.work3 < 20)
                                gCurrentSprite.work3 = 20;
    
                            gCurrentSprite.work2 = 0x2;
                        }
                    }
                    else
                        var_1++;
                }
            }

            if (!var_1)
            {
                gCurrentSprite.pose = SA_X_BOSS_POSE_SPIN_JUMPING_INIT;
                return;
            }
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE),
            gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition - (BLOCK_SIZE - PIXEL_SIZE));

            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return;
            }
        }

        if (gCurrentSprite.workY >= 60 * 3)
            return;

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 3 - PIXEL_SIZE),
            gCurrentSprite.xPosition - (BLOCK_SIZE * 3));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 5 - QUARTER_BLOCK_SIZE / 2),
                gCurrentSprite.xPosition - BLOCK_SIZE * 3);

            if (gPreviousCollisionCheck == COLLISION_AIR)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE - PIXEL_SIZE),
                    gCurrentSprite.xPosition - HALF_BLOCK_SIZE);
    
                if (gPreviousCollisionCheck == COLLISION_AIR)
                {
                    if (gSamusData.yPosition < gCurrentSprite.yPosition - (BLOCK_SIZE * 4 - QUARTER_BLOCK_SIZE))
                    {
                        if (gCurrentSprite.work3 < 8)
                            gCurrentSprite.work3 = 8;
    
                        gCurrentSprite.work2 = 0x2;
                        gCurrentSprite.pose = SA_X_BOSS_POSE_SPIN_JUMPING_INIT;
                        return;
                    }
                }
            }
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + PIXEL_SIZE), gCurrentSprite.xPosition - (BLOCK_SIZE * 4 - QUARTER_BLOCK_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 7 + PIXEL_SIZE), gCurrentSprite.xPosition - (BLOCK_SIZE * 3));
            if (gPreviousCollisionCheck == COLLISION_AIR)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + PIXEL_SIZE), gCurrentSprite.xPosition - (HALF_BLOCK_SIZE));

                if (gPreviousCollisionCheck == COLLISION_AIR)
                {
                    if (gSamusData.yPosition < gCurrentSprite.yPosition - (BLOCK_SIZE * 4 - QUARTER_BLOCK_SIZE))
                    {
                        if (gCurrentSprite.work3 < 8)
                            gCurrentSprite.work3 = 8;
    
                        gCurrentSprite.work2 = 0x3;
                        gCurrentSprite.pose = SA_X_BOSS_POSE_SPIN_JUMPING_INIT;
                        return;
                    }
                }
            }
        }

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 3 + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition - (BLOCK_SIZE * 4 + QUARTER_BLOCK_SIZE));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 7 - QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition - (BLOCK_SIZE * 4 + QUARTER_BLOCK_SIZE));
            if (gPreviousCollisionCheck == COLLISION_SOLID)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 8 + QUARTER_BLOCK_SIZE / 2), gCurrentSprite.xPosition - (BLOCK_SIZE * 4 + QUARTER_BLOCK_SIZE));
                if (gPreviousCollisionCheck == COLLISION_AIR)
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE * 4 + PIXEL_SIZE), gCurrentSprite.xPosition - (HALF_BLOCK_SIZE));
    
                    if (gPreviousCollisionCheck == COLLISION_AIR)
                    {
                        if (gSamusData.yPosition < gCurrentSprite.yPosition - (BLOCK_SIZE * 6 + QUARTER_BLOCK_SIZE))
                        {
                            if (gCurrentSprite.work3 < 8)
                                gCurrentSprite.work3 = 8;
        
                            gCurrentSprite.work2 = 0x5;
                            gCurrentSprite.pose = SA_X_BOSS_POSE_SPIN_JUMPING_INIT;
                            return;
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief 1a294 | 2d0 | Handles the SA-X (boss) tracking samus
 * 
 * @return u8 bool, pose changed
 */
u8 SaXBossTrackSamus(void)
{
    u32 nslr;

    if (gSaXVision.inYRange == TRUE)
    {
        gCurrentSprite.workY = 0;

        if (SpriteUtilCheckSamusHangingOnLedge())
        {
            nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 11 + HALF_BLOCK_SIZE,
                BLOCK_SIZE * 9 + QUARTER_BLOCK_SIZE + PIXEL_SIZE);
        }
        else
        {
            nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 7 + HALF_BLOCK_SIZE,
                BLOCK_SIZE * 5 + QUARTER_BLOCK_SIZE + PIXEL_SIZE);
        }

        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (nslr == NSLR_RIGHT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
                gCurrentSprite.work2 = gSaXVision.diagonalAim;
                return TRUE;
            }
        }
        else
        {
            if (nslr == NSLR_LEFT)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
                gCurrentSprite.work2 = gSaXVision.diagonalAim;
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

        return FALSE;
    }

    nslr = FALSE;

    if (gCurrentSprite.workY < 60 * 3)
    {
        gCurrentSprite.workY++;

        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
        {
            if (gSaXVision.samusOnRight == FALSE && gSaXVision.inXRange != FALSE)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return TRUE;
            }
        }
        else
        {
            if (gSaXVision.samusOnRight == TRUE && gSaXVision.inXRange != FALSE)
            {
                gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
                return TRUE;
            }
        }

        return FALSE;
    }

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (gSamusData.yPosition < gCurrentSprite.yPosition - (BLOCK_SIZE * 11))
        {
            if (gSamusData.xPosition < gCurrentSprite.xPosition + (BLOCK_SIZE * 12 + HALF_BLOCK_SIZE) &&
                gSamusData.xPosition > gCurrentSprite.xPosition + (BLOCK_SIZE * 9 + HALF_BLOCK_SIZE))
            {
                nslr = TRUE;
            }
        }

        if (nslr)
        {
            gSaXVision.diagonalAim = DIAG_AIM_UP;
            gSaXVision.detectedSamusOnRight = TRUE;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
            gCurrentSprite.work2 = gSaXVision.diagonalAim;
            return TRUE;
        }
    }
    else
    {
        if (gSamusData.yPosition < gCurrentSprite.yPosition - (BLOCK_SIZE * 18))
        {
            if (gSamusData.xPosition > gCurrentSprite.xPosition - (BLOCK_SIZE * 20) &&
                gSamusData.xPosition < gCurrentSprite.xPosition - (BLOCK_SIZE * 17))
            {
                nslr = TRUE;
            }
        }

        if (nslr)
        {
            gSaXVision.diagonalAim = DIAG_AIM_UP;
            gSaXVision.detectedSamusOnRight = FALSE;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
            gCurrentSprite.work2 = gSaXVision.diagonalAim;
            return TRUE;
        }

        if (gSamusData.yPosition < gCurrentSprite.yPosition - (BLOCK_SIZE * 11) &&
            gSamusData.yPosition > gCurrentSprite.yPosition - (BLOCK_SIZE * 13 + QUARTER_BLOCK_SIZE / 2))
        {
            if (gSamusData.xPosition > gCurrentSprite.xPosition - (BLOCK_SIZE * 12 + HALF_BLOCK_SIZE) &&
                gSamusData.xPosition < gCurrentSprite.xPosition - (BLOCK_SIZE * 9 + HALF_BLOCK_SIZE))
            {
                nslr = TRUE;
            }
        }

        if (nslr)
        {
            gSaXVision.diagonalAim = DIAG_AIM_UP;
            gSaXVision.detectedSamusOnRight = FALSE;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
            gCurrentSprite.work2 = gSaXVision.diagonalAim;
            return TRUE;
        }

        if (gSamusData.yPosition < gCurrentSprite.yPosition - (BLOCK_SIZE * 10) &&
            gSamusData.yPosition > gCurrentSprite.yPosition - (BLOCK_SIZE * 11 - PIXEL_SIZE))
        {
            if (gSamusData.xPosition > gCurrentSprite.xPosition - (BLOCK_SIZE * 11 + HALF_BLOCK_SIZE) &&
                gSamusData.xPosition < gCurrentSprite.xPosition - (BLOCK_SIZE * 8 + HALF_BLOCK_SIZE))
            {
                nslr = TRUE;
            }
        }

        if (nslr)
        {
            gSaXVision.diagonalAim = DIAG_AIM_UP;
            gSaXVision.detectedSamusOnRight = FALSE;
            gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT;
            gCurrentSprite.work2 = gSaXVision.diagonalAim;
            return TRUE;
        }

        if (gSamusData.yPosition < gCurrentSprite.yPosition - (BLOCK_SIZE * 4 - PIXEL_SIZE) &&
            gSamusData.yPosition > gCurrentSprite.yPosition - (BLOCK_SIZE * 6 + QUARTER_BLOCK_SIZE))
        {
            if (gSamusData.xPosition > gCurrentSprite.xPosition - (BLOCK_SIZE * 6) &&
                gSamusData.xPosition < gCurrentSprite.xPosition - (BLOCK_SIZE * 4))
            {
                if (gCurrentSprite.work3 < 8)
                    gCurrentSprite.work3 = 8;

                gCurrentSprite.work2 = 0x3;
                gCurrentSprite.pose = SA_X_BOSS_POSE_SPIN_JUMPING_INIT;
                return TRUE;
            }
        }
    }

    if (SpriteUtilCheckSamusHangingOnLedge())
    {
        if (gSamusData.yPosition < gCurrentSprite.yPosition)
            gSaXVision.diagonalAim = DIAG_AIM_UP;
        else
            gSaXVision.diagonalAim = DIAG_AIM_DOWN;

        if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
            gSaXVision.detectedSamusOnRight = TRUE;
        else
            gSaXVision.detectedSamusOnRight = FALSE;

        gCurrentSprite.workY -= 70;
        gCurrentSprite.pose = SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_MISSILE_INIT;
        gCurrentSprite.work2 = gSaXVision.diagonalAim;

        SaXSetPose(SA_X_POSE_STANDING);
        return TRUE;
    }

    return FALSE;
}

/**
 * @brief 1a564 | 34 | Initializes the SA-X (boss) to be running
 * 
 */
void SaXBossRunningInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING;
    gCurrentSprite.work3 = 0;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    if (!SaXCheckShootOrTurnTowardsSamus())
        SaXSetPose(SA_X_POSE_RUNNING);
}

/**
 * @brief 1a598 | 4c | Handles the SA-X (boss) running
 * 
 */
void SaXBossRunning(void)
{
    if (SaXBossTrackSamus())
        return;

    SaXBossCheckCollisionRunning();

    if (gCurrentSprite.pose != SA_X_SPRITE_POSE_RUNNING)
        return;

    SpriteUtilMoveXPosForwardOnSlopeDirection(sSaXRunningSpeed[gCurrentSprite.work3 / 8]);

    if (gCurrentSprite.work3 < ARRAY_SIZE(sSaXRunningSpeed) * 8 - 1)
        gCurrentSprite.work3++;
}

/**
 * @brief 1a5e4 | 3c | Initializes the SA-X (boss) to spin jump
 * 
 */
void SaXBossSpinJumpingInit(void)
{
    gCurrentSprite.pose = SA_X_BOSS_POSE_SPIN_JUMPING;
    gCurrentSprite.work4 = 0;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE + QUARTER_BLOCK_SIZE);
    gCurrentSprite.yPosition -= HALF_BLOCK_SIZE;

    SaXSetPose(SA_X_POSE_MID_AIR);

    gCurrentSprite.work0 = 0;
}

/**
 * @brief 1a620 | 228 | Handles the SA-X (boss) spin jumping
 * 
 */
void SaXBossSpinJumping(void)
{
    u8 offset;
    s16 movement;
    s32 blockTop;

    // ?
    if (gSaXVision.diagonalAim)
        ;

    if (gCurrentSprite.workY < 60 * 3)
        gCurrentSprite.workY++;

    if (gCurrentSprite.work0 != 0)
    {
        if (gSaXData.pose != SA_X_POSE_STANDING)
            return;

        if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
            {
                if (gCurrentSprite.workY < 60 * 3 && gSaXVision.samusOnRight == FALSE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            }
            else
            {
                if (gCurrentSprite.workY < 60 * 3 && gSaXVision.samusOnRight == TRUE)
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
        movement = sSaXRunningSpeed[gCurrentSprite.work3 / 8];
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

    if (gCurrentSprite.work2 == 1)
    {
        movement = sSaXJumpYVelocity_1[DIV_SHIFT(gCurrentSprite.work4, 4)];

        if (gCurrentSprite.work4 < ARRAY_SIZE(sSaXJumpYVelocity_1) * 4 - 1)
            gCurrentSprite.work4++;
    }
    else if (gCurrentSprite.work2 == 2)
    {
        movement = sSaXBossSpinJumpYVelocity_2[DIV_SHIFT(gCurrentSprite.work4, 4)];

        if (gCurrentSprite.work4 < ARRAY_SIZE(sSaXBossSpinJumpYVelocity_2) * 4 - 1)
            gCurrentSprite.work4++;
    }
    else if (gCurrentSprite.work2 == 3)
    {
        movement = sSaXJumpYVelocity_3[DIV_SHIFT(gCurrentSprite.work4, 4)];

        if (gCurrentSprite.work4 < ARRAY_SIZE(sSaXJumpYVelocity_3) * 4 - 1)
            gCurrentSprite.work4++;
    }
    else if (gCurrentSprite.work2 == 4)
    {
        movement = sSaXJumpYVelocity_4[DIV_SHIFT(gCurrentSprite.work4, 4)];

        if (gCurrentSprite.work4 < ARRAY_SIZE(sSaXJumpYVelocity_4) * 4 - 1)
            gCurrentSprite.work4++;
    }
    else if (gCurrentSprite.work2 == 5)
    {
        movement = sSaXBossSpinJumpYVelocity_5[DIV_SHIFT(gCurrentSprite.work4, 4)];

        if (gCurrentSprite.work4 < ARRAY_SIZE(sSaXBossSpinJumpYVelocity_5) * 4 - 1)
            gCurrentSprite.work4++;
    }
    else
    {
        movement = sSaXJumpYVelocity_0[DIV_SHIFT(gCurrentSprite.work4, 4)];

        if (gCurrentSprite.work4 < ARRAY_SIZE(sSaXJumpYVelocity_0) * 4 - 1)
            gCurrentSprite.work4++;
    }

    gCurrentSprite.yPosition += movement;

    if (movement > 0)
    {
        blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition, gCurrentSprite.xPosition);

        if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
        {
            gCurrentSprite.yPosition = blockTop;
            gCurrentSprite.work0 = 1;
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
 * @brief 1a848 | 30 | Initializes the SA-X (boss) to be waiting to appear
 * 
 */
void SaXBossWaitingToAppearInit(void)
{
    gCurrentSprite.status |= SPRITE_STATUS_HIDDEN;
    gCurrentSprite.pose = SA_X_BOSS_POSE_WAITING_TO_APPEAR;

    SaXSetPose(SA_X_POSE_FALLING);

    gCurrentSprite.work1 = 0;
}

/**
 * @brief 1a878 | 9c | Handles the SA-X (boss) waiting to appear
 * 
 */
void SaXBossWaitingToAppear(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (gCurrentSprite.work1 == 0)
    {
        if (gSamusData.yPosition < gCurrentSprite.yPosition - (BLOCK_SIZE * 5 + HALF_BLOCK_SIZE))
        {
            if (gSamusData.xPosition > gCurrentSprite.xPosition - (BLOCK_SIZE * 23) && gSamusData.xPosition < gCurrentSprite.xPosition - (BLOCK_SIZE * 20))
            {
                ScreenShakeStartHorizontal(60, 0x80 | 1);
                gCurrentSprite.work1 = 80;
                FadeMusic(0);
                SoundPlay_3b1c(0x9B);
            }
        }
    }
    else
    {
        gCurrentSprite.work1--;
        if (gCurrentSprite.work1 == 0)
        {
            gCurrentSprite.pose = SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_1_INIT;
            gCurrentSprite.work3 = 8;
            gCurrentSprite.status &= ~SPRITE_STATUS_HIDDEN;
            PlayMusic(MUSIC_SA_X_BATTLE, 7);
        }
    }
}

/**
 * @brief 1a914 | 70 | Initializes the SA-X (boss)
 * 
 */
void SaXBossInit(void)
{
    if (!EventCheckOn_EnteredOperationsDeck())
    {
        gCurrentSprite.status = 0;
        return;
    }

    SaXInit();

    gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;

    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    gCurrentSprite.workY = 0;
    
    gCurrentSprite.status &= ~SPRITE_STATUS_FACING_RIGHT;
    SaXSetDirection();

    gCurrentSprite.work3 = 8;

    SaXBossWaitingToAppearInit();

    gBossWork2 = 0;
    gBossWork3 = 0;
    gSaXData.mosaic = FALSE;
}

/**
 * @brief 1a984 | 34 | Initializes the SA-X (boss) to be falling
 * 
 */
void SaXBossFallingInit(void)
{
    gCurrentSprite.pose = SPRITE_POSE_FALLING;
    gCurrentSprite.work4 = 0;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_FALLING);

    gCurrentSprite.work0 = 0;
}

/**
 * @brief 1a9b8 | bc | Handles the SA-X (boss) falling
 * 
 */
void SaXBossFalling(void)
{
    u8 offset;
    s16 movement;
    s32 blockTop;

    if (gCurrentSprite.work0 != 0)
    {
        if (gSaXData.pose != SA_X_POSE_STANDING)
            return;

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

        return;
    }

    blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition, gCurrentSprite.xPosition);

    if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
    {
        gCurrentSprite.yPosition = blockTop;
        gCurrentSprite.work0 = 1;
        SaXSetPose(SA_X_POSE_LANDING);
        return;
    }

    offset = gCurrentSprite.work4;
    movement = sSpritesFallingSpeed[offset];

    if (movement == SHORT_MAX)
    {
        movement = sSpritesFallingSpeed[offset - 1];
        gCurrentSprite.yPosition += movement;
    }
    else
    {
        gCurrentSprite.work4++;
        gCurrentSprite.yPosition += movement;
    }
}

/**
 * @brief 1aa74 | 24 | Initializes the SA-X (boss) to be turning around during a chase
 * 
 */
void SaXBossTurningAroundChaseInit(void)
{
    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_TURNING);
}

/**
 * @brief 1aa98 | 50 | Handles the SA-X (boss) turning around during a chase
 * 
 */
void SaXBossTurningAroundChase(void)
{
    if (gSaXData.pose != SA_X_POSE_STANDING)
        return;

    gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
    SaXSetDirection();

    if (gSamusData.pose == SPOSE_SCREW_ATTACKING)
    {
        gCurrentSprite.pose = SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_1_INIT;
        gCurrentSprite.work3 = 8;
    }
    else
    {
        gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
    }
}

/**
 * @brief 1aae8 | 34 | Initializes the SA-X (boss) to be falling from a knockback
 * 
 */
void SaxBossFallingFromKnockbackInit(void)
{
    gCurrentSprite.pose = SA_X_BOSS_POSE_FALLING_FROM_KNOCKBACK;
    gCurrentSprite.work4 = 0;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);

    SaXSetPose(SA_X_POSE_FALLING);

    gCurrentSprite.work0 = 0;
}

/**
 * @brief 1ab1c | e0 | Handles the SA-X (boss) falling from a knockback
 * 
 */
void SaxBossFallingFromKnockback(void)
{
    u8 offset;
    s16 movement;
    s32 blockTop;

    if (gCurrentSprite.work0 != 0)
    {
        if (gSaXData.pose != SA_X_POSE_STANDING)
            return;

        if (gCurrentSprite.health == 0)
        {
            gCurrentSprite.pose = SA_X_BOSS_POSE_KNEELING_INIT;
            return;
        }

        gCurrentSprite.status &= ~SPRITE_STATUS_IGNORE_PROJECTILES;
        gCurrentSprite.properties |= SP_IMMUNE_TO_PROJECTILES;

        if (MOD_AND(gSpriteRandomNumber, 2))
        {
            gCurrentSprite.pose = SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_2_INIT;
            gCurrentSprite.work3 = 40;
        }
        else
        {
            gCurrentSprite.pose = SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_3_INIT;
            gCurrentSprite.work3 = 62;
        }

        return;
    }

    blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition, gCurrentSprite.xPosition);

    if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
    {
        gCurrentSprite.yPosition = blockTop;
        gCurrentSprite.work0 = 1;
        SaXSetPose(SA_X_POSE_LANDING);
        return;
    }

    offset = gCurrentSprite.work4;
    movement = sSpritesFallingSpeed[offset];

    if (movement == SHORT_MAX)
    {
        movement = sSpritesFallingSpeed[offset - 1];
        gCurrentSprite.yPosition += movement;
    }
    else
    {
        gCurrentSprite.work4++;
        gCurrentSprite.yPosition += movement;
    }
}

/**
 * @brief 1abfc | 94 | Initializes the SA-X (boss) to do a variable jump height
 * 
 */
void SaXBossVariableJumpHeightInit(void)
{
    if (gCurrentSprite.pose == SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_3_INIT)
        gCurrentSprite.pose = SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_3;
    else if (gCurrentSprite.pose == SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_2_INIT)
        gCurrentSprite.pose = SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_2;
    else
        gCurrentSprite.pose = SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_1;

    gCurrentSprite.work4 = 0;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE + QUARTER_BLOCK_SIZE);
    gCurrentSprite.yPosition -= HALF_BLOCK_SIZE;

    SaXSetPose(SA_X_POSE_MID_AIR);

    if (gSamusData.xPosition < gCurrentSprite.xPosition)
    {
        gCurrentSprite.status &= ~SPRITE_STATUS_FACING_RIGHT;
        gSaXData.direction = KEY_LEFT;
    }
    else
    {
        gCurrentSprite.status |= SPRITE_STATUS_FACING_RIGHT;
        gSaXData.direction = KEY_RIGHT;
    }

    gCurrentSprite.work0 = 0;
}

/**
 * @brief 1ac90 | 25c | Handles the SA-X (boss) doing a variable jump height
 * 
 */
void SaXBossVariableJumpHeight(void)
{
    s16 yMovement;
    s16 xMovement;
    s32 blockTop;

    if (gCurrentSprite.work0 != 0)
    {
        if (gSaXData.pose == SA_X_POSE_STANDING)
        {
            gCurrentSprite.pose = SA_X_SPRITE_POSE_RUNNING_INIT;
            if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
            {
                if (gCurrentSprite.workY < 60 * 3 && gSaXVision.samusOnRight == FALSE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            }
            else
            {
                if (gCurrentSprite.workY < 60 * 3 && gSaXVision.samusOnRight == TRUE)
                    gCurrentSprite.pose = SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT;
            }
        }

        return;
    }

    xMovement = sSaXRunningSpeed[gCurrentSprite.work3 / 8] + MOD_AND(gSpriteRandomNumber, 4);

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2),
            gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

        if (gPreviousCollisionCheck != COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

            if (gPreviousCollisionCheck != COLLISION_SOLID)
                gCurrentSprite.xPosition += xMovement;
        }
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2),
            gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

        if (gPreviousCollisionCheck != COLLISION_SOLID)
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
                gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

            if (gPreviousCollisionCheck != COLLISION_SOLID)
                gCurrentSprite.xPosition -= xMovement;
        }
    }

    if (gCurrentSprite.pose == SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_3)
    {
        xMovement = sSaXBossJumpYVelocity_3[gCurrentSprite.work4 / 4];
    }
    else if (gCurrentSprite.pose == SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_2)
    {
        xMovement = sSaXBossJumpYVelocity_2[gCurrentSprite.work4 / 4];
    }
    else
    {
        xMovement = sSaXBossJumpYVelocity_1[gCurrentSprite.work4 / 4];
    }

    if (gCurrentSprite.work4 < ARRAY_SIZE(sSaXBossJumpYVelocity_1) * 4 - 1)
        gCurrentSprite.work4++;

    gCurrentSprite.yPosition += xMovement;

    if (xMovement > 0)
    {
        blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition, gCurrentSprite.xPosition);

        if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
        {
            gCurrentSprite.yPosition = blockTop;
            gCurrentSprite.work0 = 1;
            SaXSetPose(SA_X_POSE_LANDING);
            return;
        }

        if (gCurrentSprite.work4 > 32)
        {
            gCurrentSprite.work3 = 8;

            if (gSamusData.yPosition < gCurrentSprite.yPosition)
            {
                if (gCurrentSprite.pose == SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_2)
                    gCurrentSprite.pose = SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_1;

                gCurrentSprite.work4 = 0;
            }

            if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
            {
                if (gSamusData.xPosition + (BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE) < gCurrentSprite.xPosition)
                {
                    gCurrentSprite.status &= ~SPRITE_STATUS_FACING_RIGHT;
                    gSaXData.direction = KEY_LEFT;
                }
            }
            else
            {
                if (gSamusData.xPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE + PIXEL_SIZE) > gCurrentSprite.xPosition)
                {
                    gCurrentSprite.status |= SPRITE_STATUS_FACING_RIGHT;
                    gSaXData.direction = KEY_RIGHT;
                }
            }
        }
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2),
            gCurrentSprite.xPosition);

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.yPosition -= xMovement;

            if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + QUARTER_BLOCK_SIZE,
                    gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

                if (gPreviousCollisionCheck == COLLISION_SOLID)
                    gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
            }
            else
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + QUARTER_BLOCK_SIZE,
                    gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

                if (gPreviousCollisionCheck == COLLISION_SOLID)
                    gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
            }
        }
    }
}

/**
 * @brief 1aeec | 70 | Updates the mosaic for the SA-X boss
 * 
 */
void SaXBossUpdateMosaic(void)
{
    if (!gSaXData.mosaic)
        return;

    if (gSaXData.pose == SA_X_POSE_MID_AIR)
    {
        gWrittenToMosaic_H = 0;
        return;
    }

    gBossWork2++;
    if (gBossWork2 >= ARRAY_SIZE(sSaXMosaicValues))
    {
        gBossWork3--;
        if (gBossWork3 == 0)
        {
            gSaXData.mosaic = FALSE;
            return;
        }

        gBossWork2 = 0;
    }

    gWrittenToMosaic_H = sSaXMosaicValues[gBossWork2];
}

/**
 * @brief 1af5c | e8 | Initializes the SA-X (boss) to be knockbacked
 * 
 */
void SaXBossKnockbackInit(void)
{
    u16 spawnHealth;
    u16 currentHealth;
    
    gCurrentSprite.pose = SA_X_BOSS_POSE_KNOCKBACK;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);
    gCurrentSprite.work4 = 0;
    gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;

    SaXSetPose(SA_X_POSE_GETTING_HURT);

    if (gSamusData.xPosition > gCurrentSprite.xPosition)
    {
        gCurrentSprite.status |= SPRITE_STATUS_FACING_RIGHT;
        gSaXData.direction = KEY_RIGHT;
    }
    else
    {
        gCurrentSprite.status &= ~SPRITE_STATUS_FACING_RIGHT;
        gSaXData.direction = KEY_LEFT;
    }

    spawnHealth = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    currentHealth = gCurrentSprite.health;
    if (currentHealth > spawnHealth / 2)
        return;

    if (currentHealth < spawnHealth / 6)
    {
        gBossWork3 = 3;
    }
    else if (currentHealth < spawnHealth * 2 / 3)
    {
        gBossWork3 = 2;
    }
    else
    {
        gBossWork3 = 1;
    }

    gBossWork2 = 0;
    gSaXData.mosaic = TRUE;
}

/**
 * @brief 1b044 | 98 | Handles the SA-X (boss) getting knocked back
 * 
 */
void SaXBossKnockback(void)
{
    u8 offset;
    s16 movement;

    offset = gCurrentSprite.work4;
    movement = sSaXBossKnockbackYMovement[offset];

    if (movement == SHORT_MAX)
    {
        gCurrentSprite.pose = SA_X_BOSS_POSE_FALLING_FROM_KNOCKBACK_INIT;
    }
    else
    {
        gCurrentSprite.work4++;
        gCurrentSprite.yPosition += movement;
    }

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2), 
            gCurrentSprite.xPosition - HALF_BLOCK_SIZE);

        if (gPreviousCollisionCheck == COLLISION_AIR)
            gCurrentSprite.xPosition -= QUARTER_BLOCK_SIZE / 2;
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE / 2), 
            gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

        if (gPreviousCollisionCheck == COLLISION_AIR)
            gCurrentSprite.xPosition += QUARTER_BLOCK_SIZE / 2;
    }
}

/**
 * @brief 1b0dc | 54 | Initializes the SA-X (boss) to be kneeling
 * 
 */
void SaXBossKneelingInit(void)
{
    gSaXData.mosaic = FALSE;

    gCurrentSprite.pose = SA_X_BOSS_POSE_KNEELING;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.hitboxTop = -(BLOCK_SIZE * 2 - QUARTER_BLOCK_SIZE / 2);
    gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;

    SaXSetPose(SA_X_POSE_KNEELING);

    gCurrentSprite.work1 = 60 * 2;
    gCurrentSprite.work2 = 60 * 2;
    gCurrentSprite.yPosition -= PIXEL_SIZE;
}

/**
 * @brief 1b130 | 40 | Handles the SA-X (boss) kneeling
 * 
 */
void SaXBossKneeling(void)
{
    if (gCurrentSprite.work1 != 0)
    {
        gCurrentSprite.work1--;
        if (gCurrentSprite.work1 == 0)
            SaXSetPose(SA_X_POSE_TRANSFORMING_INTO_MONSTER);

        return;
    }

    gCurrentSprite.work2--;
    if (gCurrentSprite.work2 == 0)
        gCurrentSprite.pose = SA_X_BOSS_POSE_TRANSFORMING_INTO_MONSTER_INIT;
}

/**
 * @brief 1b170 | 18 | Initializes the SA-X (boss) 
 * 
 */
void SaXBossTransformingIntoMonsterInit(void)
{
    gCurrentSprite.pose = SA_X_BOSS_POSE_TRANSFORMING_INTO_MONSTER;
    gCurrentSprite.work1 = 29;
}

/**
 * @brief 1b188 | bc | Handles the SA-X (boss) transforming into the monster
 * 
 */
void SaXBossTransformingIntoMonster(void)
{
    u8 offset;
    
    gCurrentSprite.work1--;

    if (gCurrentSprite.work1 < 28)
    {
        offset = gCurrentSprite.work1;
        DMA3_COPY_16(&sSpritesGraphicsPointers[PSPRITE_SA_X_MONSTER - 0x10][0x200 + offset * 0x80], VRAM_OBJ + 0x4800 + offset * 0x200, 0x200 / 2);

        if (gCurrentSprite.work1 == 0)
        {
            SpriteSpawnPrimary(PSPRITE_SA_X_MONSTER, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot, 0x10,
                gCurrentSprite.yPosition + PIXEL_SIZE, gCurrentSprite.xPosition, gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT);

            gCurrentSprite.pose = SA_X_BOSS_POSE_AFTER_TRANSFORMATION;
        }

        return;
    }

    if (gCurrentSprite.work1 == 28)
    {
        DMA3_COPY_16(sSpritesPalettePointers[PSPRITE_SA_X_MONSTER - 0x10] + 16 * 2, PALRAM_OBJ + 0x120, 0x70);
    }
}

/**
 * @brief 1b244 | c | Handles the SA-X (boss) after the transformation
 * 
 */
void SaXBossAfterTransformation(void)
{
    gCurrentSprite.status = 0;
}

/**
 * @brief 1b250 | 2c8 | SA-X (boss) AI
 * 
 */
void SaXBoss(void)
{
    if (gCurrentSprite.pose < SA_X_BOSS_POSE_KNEELING_INIT)
    {
        if (SaXUpdateFreezeTimer())
            return;

        SaXSeeAndLocateSamus();

        if (SPRITE_GET_ISFT(gCurrentSprite) == 0x10)
        {
            gCurrentSprite.pose = SA_X_BOSS_POSE_KNOCKBACK_INIT;
            SoundPlay(0x9C);
        }
    }

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            SaXBossInit();
            break;

        case SPRITE_POSE_FALLING_INIT:
            SaXBossFallingInit();

        case SPRITE_POSE_FALLING:
            SaXBossFalling();
            break;

        case SA_X_SPRITE_POSE_RUNNING_INIT:
            SaXBossRunningInit();

        case SA_X_SPRITE_POSE_RUNNING:
            SaXBossRunning();
            break;

        case SA_X_BOSS_POSE_SPIN_JUMPING_INIT:
            SaXBossSpinJumpingInit();

        case SA_X_BOSS_POSE_SPIN_JUMPING:
            SaXBossSpinJumping();
            break;

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT:
            SaXBossTurningAroundChaseInit();

        case SA_X_SPRITE_POSE_TURNING_AROUND_CHASE:
            SaXBossTurningAroundChase();
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

        case SA_X_BOSS_POSE_WAITING_TO_APPEAR_INIT:
            SaXBossWaitingToAppearInit();

        case SA_X_BOSS_POSE_WAITING_TO_APPEAR:
            SaXBossWaitingToAppear();
            break;

        case SA_X_BOSS_POSE_FALLING_FROM_KNOCKBACK_INIT:
            SaxBossFallingFromKnockbackInit();

        case SA_X_BOSS_POSE_FALLING_FROM_KNOCKBACK:
            SaxBossFallingFromKnockback();
            break;

        case SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_1_INIT:
        case SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_2_INIT:
        case SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_3_INIT:
            SaXBossVariableJumpHeightInit();

        case SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_1:
        case SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_2:
        case SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_3:
            SaXBossVariableJumpHeight();
            break;

        case SA_X_BOSS_POSE_KNOCKBACK_INIT:
            SaXBossKnockbackInit();

        case SA_X_BOSS_POSE_KNOCKBACK:
            SaXBossKnockback();
            break;

        case SA_X_BOSS_POSE_KNEELING_INIT:
            SaXBossKneelingInit();

        case SA_X_BOSS_POSE_KNEELING:
            SaXBossKneeling();
            break;

        case SA_X_BOSS_POSE_TRANSFORMING_INTO_MONSTER_INIT:
            SaXBossTransformingIntoMonsterInit();

        case SA_X_BOSS_POSE_TRANSFORMING_INTO_MONSTER:
            SaXBossTransformingIntoMonster();
            break;

        case SA_X_BOSS_POSE_AFTER_TRANSFORMATION:
            SaXBossAfterTransformation();
    }

    if (gSaXData.pose == SA_X_POSE_MID_AIR)
        gCurrentSprite.properties |= SP_IMMUNE_TO_PROJECTILES;
    else
        gCurrentSprite.properties &= ~SP_IMMUNE_TO_PROJECTILES;

    SaXBossUpdateMosaic();
    SaXUpdateGraphics();
}
