#include "sprites_AI/geemer.h"

#include "gba/keys.h"
#include "globals.h"
#include "macros.h"

#include "data/sprite_data.h"
#include "data/sprites/geemer.h"
#include "data/sprites/x_parasite.h"

#include "constants/audio.h"
#include "constants/clipdata.h"
#include "constants/particle.h"
#include "constants/samus.h"

#include "structs/samus.h"
#include "structs/sprite.h"

#define GEEMER_ON_WALL work0 // Crawling on a wall (vertically)
#define GEEMER_TIMER work1 // Frames without input (it only hides before 2 seconds), then the hiding delay
#define GEEMER_LIGHT_SLOT work2 // Ram slot of the flashing light
#define GEEMER_Y_SPEED_IDX work4

void GeemerCheckCollisions(void)
{
    if (gCurrentSprite.GEEMER_ON_WALL)
    {
        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition);
        else
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition - PIXEL_SIZE);
    }
    else
    {
        if (gCurrentSprite.status & SPRITE_STATUS_Y_FLIP)
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - PIXEL_SIZE, gCurrentSprite.xPosition);
        else
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition);
    }
}

void GeemerSetHitbox(void)
{
    if (gCurrentSprite.GEEMER_ON_WALL)
    {
        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
        {
            gCurrentSprite.hitboxTop = PIXEL_TO_SUB_PIXEL(-12);
            gCurrentSprite.hitboxBottom = PIXEL_TO_SUB_PIXEL(12);
            gCurrentSprite.hitboxLeft = PIXEL_TO_SUB_PIXEL(-12);
            gCurrentSprite.hitboxRight = 0;
        }
        else
        {
            gCurrentSprite.hitboxTop = PIXEL_TO_SUB_PIXEL(-12);
            gCurrentSprite.hitboxBottom = PIXEL_TO_SUB_PIXEL(12);
            gCurrentSprite.hitboxLeft = 0;
            gCurrentSprite.hitboxRight = PIXEL_TO_SUB_PIXEL(12);
        }
    }
    else
    {
        if (gCurrentSprite.status & SPRITE_STATUS_Y_FLIP)
        {
            gCurrentSprite.hitboxTop = 0;
            gCurrentSprite.hitboxBottom = PIXEL_TO_SUB_PIXEL(10);
            gCurrentSprite.hitboxLeft = PIXEL_TO_SUB_PIXEL(-12);
            gCurrentSprite.hitboxRight = PIXEL_TO_SUB_PIXEL(12);
        }
        else
        {
            gCurrentSprite.hitboxTop = PIXEL_TO_SUB_PIXEL(-10);
            gCurrentSprite.hitboxBottom = 0;
            gCurrentSprite.hitboxLeft = PIXEL_TO_SUB_PIXEL(-12);
            gCurrentSprite.hitboxRight = PIXEL_TO_SUB_PIXEL(12);
        }
    }

    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);
}

void GeemerSetCrawlingGraphics(void)
{
    if (gCurrentSprite.GEEMER_ON_WALL)
        gCurrentSprite.pOam = sGeemerOam_CrawlingVertical;
    else
        gCurrentSprite.pOam = sGeemerOam_CrawlingHorizontal;

    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
}

void GeemerSetIdleGraphics(void)
{
    if (gCurrentSprite.GEEMER_ON_WALL)
        gCurrentSprite.pOam = sGeemerOam_IdleVertical;
    else
        gCurrentSprite.pOam = sGeemerOam_IdleHorizontal;

    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
}

void GeemerCheckShouldHide(void)
{
    if (!(gCurrentSprite.properties & SP_CAN_ABSORB_X))
    {
        if (gChangedInput != KEY_NONE)
            gCurrentSprite.GEEMER_TIMER = 0;

        if (gCurrentSprite.GEEMER_TIMER <= 120)
        {
            if (SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_TO_SUB_PIXEL(5), BLOCK_TO_SUB_PIXEL(5)) !=
                NSLR_OUT_OF_RANGE)
            {
                gCurrentSprite.pose = 0x42;

                if (gCurrentSprite.GEEMER_ON_WALL)
                {
                    gCurrentSprite.pOam = sGeemerOam_HidingVertical;
                    gCurrentSprite.hitboxTop = PIXEL_TO_SUB_PIXEL(-10);
                    gCurrentSprite.hitboxBottom = PIXEL_TO_SUB_PIXEL(10);
                }
                else
                {
                    gCurrentSprite.pOam = sGeemerOam_HidingHorizontal;
                    gCurrentSprite.hitboxLeft = PIXEL_TO_SUB_PIXEL(-10);
                    gCurrentSprite.hitboxRight = PIXEL_TO_SUB_PIXEL(10);
                }

                gCurrentSprite.animationDurationCounter = 0;
                gCurrentSprite.currentAnimationFrame = 0;
                gCurrentSprite.GEEMER_TIMER = 10;

                SoundPlayNotAlreadyPlaying(SOUND_GEEMER_HIDE);
            }
        }
    }
}

void GeemerDelayBeforeHiding(void)
{
    if (--gCurrentSprite.GEEMER_TIMER == 0)
        gCurrentSprite.pose = 0x44;
}

void GeemerHiding(void)
{
    GeemerCheckCollisions();

    if (gPreviousCollisionCheck == 0)
    {
        gCurrentSprite.pose = 0x15;
    }
    else
    {
        if (gChangedInput != KEY_NONE)
            gCurrentSprite.GEEMER_TIMER = 0;
        else
            gCurrentSprite.GEEMER_TIMER++;

        if (gCurrentSprite.GEEMER_TIMER > 120)
        {
            gCurrentSprite.pose = 0x46;

            if (gCurrentSprite.GEEMER_ON_WALL)
                gCurrentSprite.pOam = sGeemerOam_UncoveringVertical;
            else
                gCurrentSprite.pOam = sGeemerOam_UncoveringHorizontal;

            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;

            SoundPlayNotAlreadyPlaying(SOUND_GEEMER_UNCOVER);
        }
    }
}

void GeemerUncovering(void)
{
    if (SpriteUtilHasCurrentAnimationNearlyEnded())
    {
        GeemerSetHitbox();
        GeemerSetIdleGraphics();
        gCurrentSprite.pose = 8;
    }
}

void GeemerTurningIntoX(void)
{
    if (gCurrentSprite.GEEMER_ON_WALL)
    {
        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            gCurrentSprite.xPosition -= PIXEL_TO_SUB_PIXEL(8);
        else
            gCurrentSprite.xPosition += PIXEL_TO_SUB_PIXEL(8);
    }
    else
    {
        if (gCurrentSprite.status & SPRITE_STATUS_Y_FLIP)
            gCurrentSprite.yPosition += PIXEL_TO_SUB_PIXEL(8);
        else
            gCurrentSprite.yPosition -= PIXEL_TO_SUB_PIXEL(8);
    }
}

void GeemerInit(void)
{
    u16 flashingLightY;
    u16 flashingLightX;
    u8 flashingLightSlot;

    SpriteUtilTrySetAbsorbXFlag();

    if ((gCurrentSprite.properties & SP_CAN_ABSORB_X) && (!(gCurrentSprite.status & SPRITE_STATUS_HIDDEN)))
    {
        gCurrentSprite.status = 0;
    }
    else
    {
        if (gCurrentSprite.pose == SPRITE_POSE_SPAWNING_FROM_X_INIT)
        {
            gCurrentSprite.pose = SPRITE_POSE_SPAWNING_FROM_X;
            gCurrentSprite.SPRITE_X_SPAWN_MOSAIC_IDX = X_PARASITE_MOSAIC_MAX_INDEX;
        }
        else
        {
            gCurrentSprite.pose = SPRITE_POSE_IDLE;
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition);

            if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F0)
            {
                // On floor
                gCurrentSprite.GEEMER_ON_WALL = FALSE;
            }
            else
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - (BLOCK_SIZE + PIXEL_SIZE),
                    gCurrentSprite.xPosition);

                if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F0)
                {
                    // On ceiling
                    gCurrentSprite.GEEMER_ON_WALL = FALSE;
                    gCurrentSprite.status |= SPRITE_STATUS_Y_FLIP;
                    gCurrentSprite.yPosition -= BLOCK_SIZE;
                }
                else
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - HALF_BLOCK_SIZE,
                        gCurrentSprite.xPosition - (HALF_BLOCK_SIZE + PIXEL_SIZE));

                    if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F0)
                    {
                        // on left wall
                        gCurrentSprite.GEEMER_ON_WALL = TRUE;
                        gCurrentSprite.yPosition -= HALF_BLOCK_SIZE;
                        gCurrentSprite.xPosition -= HALF_BLOCK_SIZE;
                    }
                    else
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - HALF_BLOCK_SIZE,
                            gCurrentSprite.xPosition + HALF_BLOCK_SIZE);

                        if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F0)
                        {
                            // on right wall
                            gCurrentSprite.GEEMER_ON_WALL = TRUE;
                            gCurrentSprite.status |= SPRITE_STATUS_X_FLIP;
                            gCurrentSprite.yPosition -= HALF_BLOCK_SIZE;
                            gCurrentSprite.xPosition += HALF_BLOCK_SIZE;
                        }
                        else
                        {
                            // can't be placed in midair
                            gCurrentSprite.status = 0;
                            return;
                        }
                    }
                }
            }
            if (gCurrentSprite.GEEMER_ON_WALL)
            {
                if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
                {
                    flashingLightY = gCurrentSprite.yPosition;
                    flashingLightX = gCurrentSprite.xPosition - PIXEL_TO_SUB_PIXEL(9);
                }
                else
                {
                    flashingLightY = gCurrentSprite.yPosition;
                    flashingLightX = gCurrentSprite.xPosition + PIXEL_TO_SUB_PIXEL(9);
                }
            }
            else
            {
                if (gCurrentSprite.status & SPRITE_STATUS_Y_FLIP)
                {
                    flashingLightY = gCurrentSprite.yPosition + PIXEL_TO_SUB_PIXEL(9);
                    flashingLightX = gCurrentSprite.xPosition;
                }
                else
                {
                    flashingLightY = gCurrentSprite.yPosition - PIXEL_TO_SUB_PIXEL(9);
                    flashingLightX = gCurrentSprite.xPosition;
                }
            }

            flashingLightSlot = SpriteSpawnSecondary(SSPRITE_GEEMER_FLASHING_LIGHT, gCurrentSprite.roomSlot,
                gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot, flashingLightY, flashingLightX,
                0);

            if (flashingLightSlot == UCHAR_MAX)
            {
                gCurrentSprite.status = 0;
                return;
            }

            gCurrentSprite.GEEMER_LIGHT_SLOT = flashingLightSlot;
        }

        GeemerSetCrawlingGraphics();
        GeemerSetHitbox();
        gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
        gCurrentSprite.GEEMER_TIMER = 0;
        gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    }
}

void GeemerCrawlingInit(void)
{
    GeemerSetCrawlingGraphics();
    gCurrentSprite.pose = SPRITE_POSE_IDLE;
}

void GeemerCrawling(void)
{
    u8 turnAround;

    turnAround = FALSE;

    GeemerCheckCollisions();

    if (gPreviousCollisionCheck == 0)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
    }
    else
    {
        if (gCurrentSprite.GEEMER_ON_WALL)
        {
            if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            {
                if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxBottom,
                        gCurrentSprite.xPosition + PIXEL_SIZE);

                    if (!(gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F0))
                    {
                        turnAround = TRUE;
                    }
                    else
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxBottom,
                            gCurrentSprite.xPosition - PIXEL_SIZE);

                        if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F)
                        {
                            turnAround = TRUE;
                        }
                        else
                        {
                            gCurrentSprite.yPosition += PIXEL_TO_SUB_PIXEL(.25f);
                            gSpriteData[gCurrentSprite.GEEMER_LIGHT_SLOT].yPosition += PIXEL_TO_SUB_PIXEL(.25f);
                        }
                    }
                }
                else
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxTop,
                        gCurrentSprite.xPosition + PIXEL_SIZE);

                    if (!(gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F0))
                    {
                        turnAround = TRUE;
                    }
                    else
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxTop,
                            gCurrentSprite.xPosition - PIXEL_SIZE);

                        if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F)
                        {
                            turnAround = TRUE;
                        }
                        else
                        {
                            gCurrentSprite.yPosition -= PIXEL_TO_SUB_PIXEL(.25f);
                            gSpriteData[gCurrentSprite.GEEMER_LIGHT_SLOT].yPosition -= PIXEL_TO_SUB_PIXEL(.25f);
                        }
                    }
                }
            }
            else
            {
                if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxBottom,
                        gCurrentSprite.xPosition - PIXEL_SIZE);

                    if (!(gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F0))
                    {
                        turnAround = TRUE;
                    }
                    else
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxBottom,
                            gCurrentSprite.xPosition + PIXEL_SIZE);

                        if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F)
                        {
                            turnAround = TRUE;
                        }
                        else
                        {
                            gCurrentSprite.yPosition += PIXEL_TO_SUB_PIXEL(.25f);
                            gSpriteData[gCurrentSprite.GEEMER_LIGHT_SLOT].yPosition += PIXEL_TO_SUB_PIXEL(.25f);
                        }
                    }
                }
                else
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxTop,
                        gCurrentSprite.xPosition - PIXEL_SIZE);

                    if (!(gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F0))
                    {
                        turnAround = TRUE;
                    }
                    else
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxTop,
                            gCurrentSprite.xPosition + PIXEL_SIZE);

                        if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F)
                        {
                            turnAround = TRUE;
                        }
                        else
                        {
                            gCurrentSprite.yPosition -= PIXEL_TO_SUB_PIXEL(.25f);
                            gSpriteData[gCurrentSprite.GEEMER_LIGHT_SLOT].yPosition -= PIXEL_TO_SUB_PIXEL(.25f);
                        }
                    }
                }
            }
        }
        else
        {
            if (gCurrentSprite.status & SPRITE_STATUS_Y_FLIP)
            {
                if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - PIXEL_SIZE,
                        gCurrentSprite.xPosition + gCurrentSprite.hitboxRight);

                    if (!(gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F))
                    {
                        turnAround = TRUE;
                    }
                    else
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
                            gCurrentSprite.xPosition + gCurrentSprite.hitboxRight);

                        if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F)
                        {
                            turnAround = TRUE;
                        }
                        else
                        {
                            gCurrentSprite.xPosition += PIXEL_TO_SUB_PIXEL(.25f);
                            gSpriteData[gCurrentSprite.GEEMER_LIGHT_SLOT].xPosition += PIXEL_TO_SUB_PIXEL(.25f);
                        }
                    }
                }
                else
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - PIXEL_SIZE,
                        gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft);

                    if (!(gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F))
                    {
                        turnAround = TRUE;
                    }
                    else
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
                            gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft);

                        if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F)
                        {
                            turnAround = TRUE;
                        }
                        else
                        {
                            gCurrentSprite.xPosition -= PIXEL_TO_SUB_PIXEL(.25f);
                            gSpriteData[gCurrentSprite.GEEMER_LIGHT_SLOT].xPosition -= PIXEL_TO_SUB_PIXEL(.25f);
                        }
                    }
                }
            }
            else
            {
                if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
                        gCurrentSprite.xPosition + gCurrentSprite.hitboxRight);

                    if (!(gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F0))
                    {
                        turnAround = TRUE;
                    }
                    else
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - PIXEL_SIZE,
                            gCurrentSprite.xPosition + gCurrentSprite.hitboxRight);

                        if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F)
                        {
                            turnAround = TRUE;
                        }
                        else
                        {
                            gCurrentSprite.xPosition += PIXEL_TO_SUB_PIXEL(.25f);
                            gSpriteData[gCurrentSprite.GEEMER_LIGHT_SLOT].xPosition += PIXEL_TO_SUB_PIXEL(.25f);
                        }
                    }
                }
                else
                {
                    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
                        gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft);

                    if (!(gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F0))
                    {
                        turnAround = TRUE;
                    }
                    else
                    {
                        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - PIXEL_SIZE,
                            gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft);

                        if (gPreviousCollisionCheck & COLLISION_FLAGS_UNKNOWN_F)
                        {
                            turnAround = TRUE;
                        }
                        else
                        {
                            gCurrentSprite.xPosition -= PIXEL_TO_SUB_PIXEL(.25f);
                            gSpriteData[gCurrentSprite.GEEMER_LIGHT_SLOT].xPosition -= PIXEL_TO_SUB_PIXEL(.25f);
                        }
                    }
                }
            }
        }

        if (turnAround)
        {
            gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
            gCurrentSprite.pose = 7;
        }

        GeemerCheckShouldHide();
    }
}

void GeemerIdleInit(void)
{
    gCurrentSprite.pose = 8;
    GeemerSetIdleGraphics();
}

void GeemerIdle(void)
{
    GeemerCheckCollisions();

    if (gPreviousCollisionCheck == 0)
    {
        gCurrentSprite.pose = SPRITE_POSE_FALLING_INIT;
    }
    else
    {
        if (SpriteUtilHasCurrentAnimationNearlyEnded())
            gCurrentSprite.pose = 1;

        GeemerCheckShouldHide();
    }
}

void GeemerFallingInit(void)
{
    gCurrentSprite.pose = SPRITE_POSE_FALLING;
    gCurrentSprite.GEEMER_Y_SPEED_IDX = 0;
    GeemerSetHitbox();
    GeemerSetIdleGraphics();
}

void GeemerFalling(void)
{
    u16 yCollisionPoint;
    u16 xCollisionPoint;
    u32 blockTop;
    u8 onWall;
    u8 offset;
    s16 movement;
    u32 flashingLightSlot;

    onWall = 0;
    yCollisionPoint = gCurrentSprite.yPosition;
    xCollisionPoint = gCurrentSprite.xPosition;

    if (gCurrentSprite.GEEMER_ON_WALL)
    {
        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            xCollisionPoint -= PIXEL_SIZE;

        yCollisionPoint += gCurrentSprite.hitboxBottom;
    }
    else
    {
        if (gCurrentSprite.status & SPRITE_STATUS_Y_FLIP)
            yCollisionPoint += gCurrentSprite.hitboxBottom;
    }

    blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(yCollisionPoint, xCollisionPoint);

    if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
    {
        gCurrentSprite.yPosition = blockTop;

        if (gCurrentSprite.GEEMER_ON_WALL)
            onWall++;

        gCurrentSprite.status &= ~SPRITE_STATUS_Y_FLIP;
        gCurrentSprite.GEEMER_ON_WALL = 0;
        GeemerSetHitbox();

        if (onWall)
        {
            if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
                gCurrentSprite.xPosition -= gCurrentSprite.hitboxRight;
            else
                gCurrentSprite.xPosition -= gCurrentSprite.hitboxLeft;
        }

        if (gCurrentSprite.properties & SP_CAN_ABSORB_X)
        {
            gCurrentSprite.pose = SPRITE_POSE_IDLE;
            GeemerSetCrawlingGraphics();
        }
        else
        {
            gCurrentSprite.pose = 8;
            GeemerSetIdleGraphics();
            flashingLightSlot = gCurrentSprite.GEEMER_LIGHT_SLOT;
            gSpriteData[flashingLightSlot].yPosition = gCurrentSprite.yPosition - PIXEL_TO_SUB_PIXEL(9);
            gSpriteData[flashingLightSlot].xPosition = gCurrentSprite.xPosition;
            gSpriteData[flashingLightSlot].hitboxTop = PIXEL_TO_SUB_PIXEL(-3);
            gSpriteData[flashingLightSlot].hitboxBottom = PIXEL_TO_SUB_PIXEL(8);
            gSpriteData[flashingLightSlot].hitboxLeft = PIXEL_TO_SUB_PIXEL(-3);
            gSpriteData[flashingLightSlot].hitboxRight = PIXEL_TO_SUB_PIXEL(3);
        }
    }
    else
    {
        offset = gCurrentSprite.GEEMER_Y_SPEED_IDX;
        movement = sSpritesFallingSpeed[offset];

        if (movement == SHORT_MAX)
        {
            movement = sSpritesFallingSpeed[offset - 1];
            gCurrentSprite.yPosition += movement;
        }
        else
        {
            offset++;
            gCurrentSprite.GEEMER_Y_SPEED_IDX = offset;
            gCurrentSprite.yPosition += movement;
        }
    }
}

void Geemer(void)
{
    if (SPRITE_GET_ISFT(gCurrentSprite) == 4)
        SoundPlayNotAlreadyPlaying(SOUND_GEEMER_HURT);

    if (gCurrentSprite.freezeTimer != 0)
    {
        SpriteUtilUpdateFreezeTimer();
        SpriteUtilUpdateSecondarySpriteFreezeTimerOfCurrent(SSPRITE_GEEMER_FLASHING_LIGHT, gCurrentSprite.primarySpriteRamSlot);
        return;
    }

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            GeemerInit();
            break;

        case SPRITE_POSE_IDLE_INIT:
            GeemerCrawlingInit();

        case SPRITE_POSE_IDLE:
            GeemerCrawling();
            break;

        case 7:
            GeemerIdleInit();

        case 8:
            GeemerIdle();
            break;

        case SPRITE_POSE_FALLING_INIT:
            GeemerFallingInit();

        case SPRITE_POSE_FALLING:
            GeemerFalling();
            break;

        case 0x42:
            GeemerDelayBeforeHiding();
            break;

        case 0x44:
            GeemerHiding();
            break;

        case 0x46:
            GeemerUncovering();
            break;

        case SPRITE_POSE_DYING_INIT:
            SpriteUtilUnfreezeSecondarySprites(SSPRITE_GEEMER_FLASHING_LIGHT, gCurrentSprite.primarySpriteRamSlot);
            SpriteDyingInit();

        case SPRITE_POSE_DYING:
            SpriteDying();
            break;

        case SPRITE_POSE_SPAWNING_FROM_X_INIT:
            GeemerInit();

        case SPRITE_POSE_SPAWNING_FROM_X:
            SpriteSpawningFromX();
            break;

        case SPRITE_POSE_TURNING_INTO_X:
            GeemerTurningIntoX();
            XParasiteInit();
            break;
    }
}

void GeemerFlashingLight(void)
{
    u32 geemerSlot;

    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (gCurrentSprite.freezeTimer != 0)
    {
        SpriteUtilUpdateFreezeTimer();
        SpriteUtilUpdatePrimarySpriteFreezeTimerOfCurrent();
        return;
    }

    geemerSlot = gCurrentSprite.primarySpriteRamSlot;

    if (gCurrentSprite.pose == 0)
    {
        gCurrentSprite.drawOrder = 3;
        gCurrentSprite.health = GET_SSPRITE_HEALTH(gCurrentSprite.spriteId);
        gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(.1875f);
        gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.1875f);
        gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(.1875f);
        gCurrentSprite.pOam = sGeemerFlashingLightOam_Idle;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.samusCollision = SSC_NONE;
        gCurrentSprite.pose = 2;

        if (gSpriteData[geemerSlot].GEEMER_ON_WALL)
        {
            if (gSpriteData[geemerSlot].status & SPRITE_STATUS_X_FLIP)
            {
                gCurrentSprite.hitboxTop = PIXEL_TO_SUB_PIXEL(-3);
                gCurrentSprite.hitboxBottom = PIXEL_TO_SUB_PIXEL(3);
                gCurrentSprite.hitboxLeft = PIXEL_TO_SUB_PIXEL(-3);
                gCurrentSprite.hitboxRight = PIXEL_TO_SUB_PIXEL(8);
            }
            else
            {
                gCurrentSprite.hitboxTop = PIXEL_TO_SUB_PIXEL(-3);
                gCurrentSprite.hitboxBottom = PIXEL_TO_SUB_PIXEL(3);
                gCurrentSprite.hitboxLeft = PIXEL_TO_SUB_PIXEL(-8);
                gCurrentSprite.hitboxRight = PIXEL_TO_SUB_PIXEL(3);
            }
        }
        else
        {
            if (gSpriteData[geemerSlot].status & SPRITE_STATUS_Y_FLIP)
            {
                gCurrentSprite.hitboxTop = PIXEL_TO_SUB_PIXEL(-8);
                gCurrentSprite.hitboxBottom = PIXEL_TO_SUB_PIXEL(3);
                gCurrentSprite.hitboxLeft = PIXEL_TO_SUB_PIXEL(-3);
                gCurrentSprite.hitboxRight = PIXEL_TO_SUB_PIXEL(3);
            }
            else
            {
                gCurrentSprite.hitboxTop = PIXEL_TO_SUB_PIXEL(-3);
                gCurrentSprite.hitboxBottom = PIXEL_TO_SUB_PIXEL(8);
                gCurrentSprite.hitboxLeft = PIXEL_TO_SUB_PIXEL(-3);
                gCurrentSprite.hitboxRight = PIXEL_TO_SUB_PIXEL(3);
            }
        }
    }

    if (gSpriteData[geemerSlot].status & SPRITE_STATUS_HIDDEN)
    {
        gCurrentSprite.status |= SPRITE_STATUS_HIDDEN;
    }
    else
    {
        gCurrentSprite.status &= ~SPRITE_STATUS_HIDDEN;

        if (gCurrentSprite.health == 0 && gSpriteData[geemerSlot].pose < SPRITE_POSE_DYING_INIT)
        {
            gSpriteData[geemerSlot].pose = SPRITE_POSE_DYING_INIT;
            gSpriteData[geemerSlot].ignoreSamusCollisionTimer = 1;
            gSpriteData[geemerSlot].health = 0;
            gSpriteData[geemerSlot].properties |= SP_DESTROYED;
            gSpriteData[geemerSlot].freezeTimer = 0;
            gSpriteData[geemerSlot].paletteRow = 0;
            gCurrentSprite.status = 0;
        }
        else
        {
            switch (gSpriteData[geemerSlot].pose)
            {
                case 0x44:
                    gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
                    break;

                default:
                    gCurrentSprite.status &= ~SPRITE_STATUS_IGNORE_PROJECTILES;
                    break;

                case SPRITE_POSE_DYING_INIT:
                case SPRITE_POSE_DYING:
                    gCurrentSprite.status = 0;
                    break;
            }
        }
    }
}
