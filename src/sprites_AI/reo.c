#include "data/sprites/reo.h"

#include "globals.h"

#include "data/generic_data.h"
#include "data/samus_data.h"
#include "data/sprite_data.h"
#include "data/sprites/x_parasite.h"

#include "constants/audio.h"
#include "constants/clipdata.h"
#include "constants/samus.h"
#include "constants/sprite.h"

#include "structs/clipdata.h"
#include "structs/samus.h"
#include "structs/sprite.h"

#define REO_TIMER work1
#define REO_SLOWING_DOWN work1 // Going up, set once back near the home Y position
#define REO_WINGS_SLOT work2
#define REO_IDLE_TIMER work3 // Frames moving horizontally while idle
#define REO_Y_SPEED_IDX work4 // Also the index in the idle Y movement table
#define REO_HOME_Y workX // Y position it goes back up to

void ReoPlaySound(void)
{
    if (MOD_AND(gFrameCounter8Bit, 32) == 0)
        SoundPlayNotAlreadyPlaying(SOUND_REO_MOVING);
}

u8 ReoCheckFall(void)
{
    if (SPRITE_GET_ISFT(gCurrentSprite) >= 5 && gCurrentSprite.status & SPRITE_STATUS_ONSCREEN)
    {
        gCurrentSprite.pose = 0x37;
        return TRUE;
    }

    return FALSE;
}

u8 ReoXMovement(u16 movement)
{
    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(0.5f),
            gCurrentSprite.xPosition + BLOCK_TO_SUB_PIXEL(1.0f));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
            return TRUE;
        gCurrentSprite.xPosition += movement;
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(0.5f),
            gCurrentSprite.xPosition - BLOCK_TO_SUB_PIXEL(1.0f));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
            return TRUE;
        gCurrentSprite.xPosition -= movement;
    }

    return FALSE;
}

void ReoInit(void)
{
    u8 ramSlot;

    SpriteUtilTrySetAbsorbXFlag();
    if (gCurrentSprite.properties & SP_CAN_ABSORB_X)
    {
        if (!(gCurrentSprite.status & SPRITE_STATUS_HIDDEN))
        {
            gCurrentSprite.status = 0;
            return;
        }

        gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(1.0f);
        gCurrentSprite.hitboxBottom = BLOCK_TO_SUB_PIXEL(0.625f);
        gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(1.0f);
        gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(1.0f);
    }
    else
    {
        gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(0.875f);
        gCurrentSprite.hitboxBottom = BLOCK_TO_SUB_PIXEL(0.375f);
        gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(0.625f);
        gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(0.625f);
    }

    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1.5f);
    gCurrentSprite.pOam = sReoOam_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.REO_TIMER = 0;
    gCurrentSprite.REO_Y_SPEED_IDX = 0;
    gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    SpriteUtilMakeSpriteFaceSamusDirection();

    if (gCurrentSprite.pose == SPRITE_POSE_SPAWNING_FROM_X_INIT)
    {
        gCurrentSprite.pose = SPRITE_POSE_SPAWNING_FROM_X;
        gCurrentSprite.SPRITE_X_SPAWN_MOSAIC_IDX = X_PARASITE_MOSAIC_MAX_INDEX;
        return;
    }

    gCurrentSprite.pose = SPRITE_POSE_IDLE_INIT;
    gCurrentSprite.REO_HOME_Y = gCurrentSprite.yPosition;

    ramSlot = SpriteSpawnSecondary(SSPRITE_REO_WING, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition,
        gCurrentSprite.status & SPRITE_STATUS_X_FLIP);
    if (ramSlot == UCHAR_MAX)
        gCurrentSprite.status = 0;

    gCurrentSprite.REO_WINGS_SLOT = ramSlot;
}

void ReoFallInit(void)
{
    gCurrentSprite.pose = 0x38;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.pOam = sReoOam_Falling;
    gCurrentSprite.REO_Y_SPEED_IDX = 0;

    gSpriteData[gCurrentSprite.REO_WINGS_SLOT].status |= SPRITE_STATUS_NOT_DRAWN;
}

void ReoFalling(void)
{
    u8 collision;
    u32 blockTop;
    u8 offset;
    s16 movement;

    collision = FALSE;
    blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition, gCurrentSprite.xPosition);
    if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
    {
        collision++;
    }
    else
    {
        blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition,
            gCurrentSprite.xPosition + gCurrentSprite.hitboxRight);
        if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
        {
            collision++;
        }
        else
        {
            blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition,
                gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft);
            if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
                collision++;
        }
    }

    if (collision)
    {
        gCurrentSprite.yPosition = blockTop;
        gCurrentSprite.pose = 0x3a;
        gCurrentSprite.REO_TIMER = 60;
    }
    else
    {
        offset = gCurrentSprite.REO_Y_SPEED_IDX;
        movement = sSpritesFallingSpeedQuickAcceleration[offset];
        if (movement == SHORT_MAX)
        {
            movement = sSpritesFallingSpeedQuickAcceleration[offset - 1];
            gCurrentSprite.yPosition += movement;
        }
        else
        {
            offset++;
            gCurrentSprite.REO_Y_SPEED_IDX = offset;
            gCurrentSprite.yPosition += movement;
        }
    }
}

void ReoLanding(void)
{
    if (--gCurrentSprite.REO_TIMER == 0)
    {
        gCurrentSprite.pose = 0x2d;
        gCurrentSprite.pOam = sReoOam_Idle;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;

        gSpriteData[gCurrentSprite.REO_WINGS_SLOT].status &= ~SPRITE_STATUS_NOT_DRAWN;
    }
}

void ReoIdleInit(void)
{
    gCurrentSprite.pose = SPRITE_POSE_IDLE;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.pOam = sReoOam_Idle;
    gCurrentSprite.REO_IDLE_TIMER = 0;
    gCurrentSprite.REO_Y_SPEED_IDX = 0;
}

void ReoIdle(void)
{
    u8 offset;
    s16 movement;
    u16 targetY;
    u16 spriteY;
    u8 nslr;

    if (gCurrentSprite.status & SPRITE_STATUS_HIDDEN)
        return;
    if (ReoCheckFall())
        return;

    gCurrentSprite.REO_IDLE_TIMER += 1;

    offset = gCurrentSprite.REO_Y_SPEED_IDX;
    movement = sReoIdleYMovement[offset];
    if (movement == SHORT_MAX)
    {
        movement = sReoIdleYMovement[0];
        offset = 0;
    }

    offset++;
    gCurrentSprite.REO_Y_SPEED_IDX = offset;
    gCurrentSprite.yPosition += movement;

    if (ReoXMovement(2) || gCurrentSprite.REO_IDLE_TIMER > 32)
    {
        gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
        gCurrentSprite.REO_IDLE_TIMER = 0;
    }

    if (gCurrentSprite.REO_Y_SPEED_IDX == ARRAY_SIZE(sReoIdleYMovement) - 2)
    {
        targetY = gSamusData.yPosition;
        spriteY = gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(1.5f);
        nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_TO_SUB_PIXEL(10.0f), BLOCK_TO_SUB_PIXEL(15.0f));

        if (targetY < spriteY)
            nslr = NSLR_OUT_OF_RANGE;

        if (nslr != NSLR_OUT_OF_RANGE)
        {
            if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
            {
                if (gCurrentSprite.xPosition > gSamusData.xPosition)
                    gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
            }
            else
            {
                if (gCurrentSprite.xPosition < gSamusData.xPosition)
                    gCurrentSprite.status ^= SPRITE_STATUS_FACING_RIGHT;
            }

            gCurrentSprite.pose = 0x29;
        }
    }
}

void ReoGoingDownInit(void)
{
    gCurrentSprite.REO_TIMER = 8;
    gCurrentSprite.REO_Y_SPEED_IDX = 0;
    gCurrentSprite.pose = 0x2a;
}

void ReoGoingDown(void)
{
    u16 xMovement;
    u8 offset;
    s16 yMovement;

    if (ReoCheckFall())
        return;

    ReoPlaySound();

    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(0.5f), gCurrentSprite.xPosition);
    if (gPreviousCollisionCheck == COLLISION_SOLID)
    {
        if (ReoXMovement(3))
            gCurrentSprite.pose = 0x2d;

        if (--gCurrentSprite.REO_TIMER == 0)
            gCurrentSprite.pose = 0x2d;
    }
    else
    {
        xMovement = DIV_SHIFT(gCurrentSprite.REO_Y_SPEED_IDX, 4);
        if (xMovement > 4)
            xMovement = 6;

        ReoXMovement(xMovement);

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(2.0f),
            gCurrentSprite.xPosition);
        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            gCurrentSprite.pose = 0x2b;
        }
        else
        {
            offset = gCurrentSprite.REO_Y_SPEED_IDX;
            yMovement = sReoGoingDownYSpeed[offset];
            if (yMovement == SHORT_MAX)
            {
                yMovement = sReoGoingDownYSpeed[offset - 1];
                gCurrentSprite.yPosition += yMovement;
            }
            else
            {
                offset++;
                gCurrentSprite.REO_Y_SPEED_IDX = offset;
                gCurrentSprite.yPosition += yMovement;
            }
        }
    }
}

void ReoSlidingInit(void)
{
    gCurrentSprite.REO_TIMER = 8;
    gCurrentSprite.REO_Y_SPEED_IDX = 0;
    gCurrentSprite.pose = 0x2c;
}

void ReoSliding(void)
{
    u8 hitWall;
    u8 offset;
    s16 yMovement;

    if (ReoCheckFall())
        return;

    ReoPlaySound();

    hitWall = ReoXMovement(6);
    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(0.5f), gCurrentSprite.xPosition);
    if (gPreviousCollisionCheck == COLLISION_SOLID)
    {
        if (hitWall)
            gCurrentSprite.pose = 0x2d;

        if (--gCurrentSprite.REO_TIMER == 0)
            gCurrentSprite.pose = 0x2d;
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(2.0f),
            gCurrentSprite.xPosition);
        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            offset = gCurrentSprite.REO_Y_SPEED_IDX;
            yMovement = sReoSlidingYSpeed[offset];
            if (yMovement == SHORT_MAX)
            {
                yMovement = sReoSlidingYSpeed[offset - 1];
                gCurrentSprite.yPosition += yMovement;
            }
            else
            {
                offset++;
                gCurrentSprite.REO_Y_SPEED_IDX = offset;
                gCurrentSprite.yPosition += yMovement;
            }
        }
        else
        {
            gCurrentSprite.REO_TIMER = 0;
            gCurrentSprite.REO_Y_SPEED_IDX = 0;
            gCurrentSprite.pose = 0x2a;
        }
    }
}

void ReoGoingUpInit(void)
{
    gCurrentSprite.REO_SLOWING_DOWN = 0;
    gCurrentSprite.REO_Y_SPEED_IDX = 0;
    gCurrentSprite.pose = 0x2e;
}

void ReoGoingUp(void)
{
    if (ReoCheckFall())
        return;

    ReoPlaySound();

    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(1.0f), gCurrentSprite.xPosition);
    if (gPreviousCollisionCheck != COLLISION_SOLID)
    {
        if (gCurrentSprite.REO_SLOWING_DOWN == 0)
        {
            ReoXMovement(6);
            if (gCurrentSprite.REO_HOME_Y + BLOCK_TO_SUB_PIXEL(1.5f) < gCurrentSprite.yPosition)
            {
                u8 offset = gCurrentSprite.REO_Y_SPEED_IDX;
                s16 yMovement = sReoGoingUpAcceleratingYSpeed[offset];
                if (yMovement == SHORT_MAX)
                {
                    yMovement = sReoGoingUpAcceleratingYSpeed[offset - 1];
                    gCurrentSprite.yPosition += yMovement;
                }
                else
                {
                    offset++;
                    gCurrentSprite.REO_Y_SPEED_IDX = offset;
                    gCurrentSprite.yPosition += yMovement;
                }
            }
            else
            {
                gCurrentSprite.REO_SLOWING_DOWN = 1;
                gCurrentSprite.REO_Y_SPEED_IDX = 0;
            }
        }
        else
        {
            ReoXMovement(3);
            if (gCurrentSprite.REO_HOME_Y < gCurrentSprite.yPosition)
            {
                u8 offset = gCurrentSprite.REO_Y_SPEED_IDX;
                s16 yMovement = sReoGoingUpDeceleratingYSpeed[offset];
                if (yMovement == SHORT_MAX)
                {
                    yMovement = sReoGoingUpDeceleratingYSpeed[offset - 1];
                    gCurrentSprite.yPosition += yMovement;
                }
                else
                {
                    offset++;
                    gCurrentSprite.REO_Y_SPEED_IDX = offset;
                    gCurrentSprite.yPosition += yMovement;
                }
            }
            else
            {
                gCurrentSprite.pose = SPRITE_POSE_IDLE_INIT;
            }
        }
    }
    else
    {
        gCurrentSprite.pose = SPRITE_POSE_IDLE_INIT;
    }
}

void ReoWingsInit(void)
{
    u8 primary;

    primary = gCurrentSprite.primarySpriteRamSlot;
    if (gSpriteData[primary].status & SPRITE_STATUS_MOSAIC)
        gCurrentSprite.status |= SPRITE_STATUS_MOSAIC;

    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1.5f);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(0);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);
    gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(0.0625f);
    gCurrentSprite.hitboxBottom = BLOCK_TO_SUB_PIXEL(0.0625f);
    gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(0.0625f);
    gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(0.0625f);
    gCurrentSprite.pose = SPRITE_POSE_IDLE;
    gCurrentSprite.drawOrder = 5;
    gCurrentSprite.pOam = sReoWingsOam_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
}

void ReoWingsIdle(void)
{
    u8 primary;

    primary = gCurrentSprite.primarySpriteRamSlot;
    gCurrentSprite.yPosition = gSpriteData[primary].yPosition;
    gCurrentSprite.xPosition = gSpriteData[primary].xPosition;

    if (gSpriteData[primary].pose == SPRITE_POSE_DYING_INIT || gSpriteData[primary].pose == SPRITE_POSE_DYING)
    {
        SpriteDyingInit();
        SpriteDying();
    }
    else
    {
        if (gSpriteData[primary].status & SPRITE_STATUS_MOSAIC)
            gCurrentSprite.status |= SPRITE_STATUS_MOSAIC;
        else
            gCurrentSprite.status &= ~SPRITE_STATUS_MOSAIC;

        if (gSpriteData[primary].status & SPRITE_STATUS_X_FLIP)
            gCurrentSprite.status |= SPRITE_STATUS_X_FLIP;
        else
            gCurrentSprite.status &= ~SPRITE_STATUS_X_FLIP;

        if (gSpriteData[primary].status & SPRITE_STATUS_HIDDEN)
            gCurrentSprite.status |= SPRITE_STATUS_HIDDEN;
        else
            gCurrentSprite.status &= ~SPRITE_STATUS_HIDDEN;
    }
}

void Reo(void)
{
    if (SPRITE_GET_ISFT(gCurrentSprite) == 4)
        SoundPlayNotAlreadyPlaying(SOUND_REO_HURT);

    if (gCurrentSprite.freezeTimer > 0)
    {
        SpriteUtilUpdateFreezeTimer();
        SpriteUtilUpdateSecondarySpriteFreezeTimerOfCurrent(SSPRITE_REO_WING, gCurrentSprite.primarySpriteRamSlot);
        return;
    }

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            ReoInit();
            break;

        case SPRITE_POSE_IDLE_INIT:
            ReoIdleInit();

        case SPRITE_POSE_IDLE:
            ReoIdle();
            break;

        case 0x37:
            ReoFallInit();

        case 0x38:
            ReoFalling();
            break;

        case 0x3a:
            ReoLanding();
            break;

        case 0x29:
            ReoGoingDownInit();

        case 0x2a:
            ReoGoingDown();
            break;

        case 0x2b:
            ReoSlidingInit();

        case 0x2c:
            ReoSliding();
            break;

        case 0x2d:
            ReoGoingUpInit();

        case 0x2e:
            ReoGoingUp();
            break;

        case SPRITE_POSE_DYING_INIT:
            SpriteUtilUnfreezeSecondarySprites(SSPRITE_REO_WING, gCurrentSprite.primarySpriteRamSlot);
            SpriteDyingInit();

        case SPRITE_POSE_DYING:
            SpriteDying();
            break;

        case SPRITE_POSE_SPAWNING_FROM_X_INIT:
            ReoInit();

        case SPRITE_POSE_SPAWNING_FROM_X:
            SpriteSpawningFromX();
            break;

        case SPRITE_POSE_TURNING_INTO_X:
            XParasiteInit();
            gCurrentSprite.yPosition -= BLOCK_TO_SUB_PIXEL(0.5f);
            break;
    }
}

void ReoWings(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (gCurrentSprite.freezeTimer > 0)
    {
        SpriteUtilUpdateFreezeTimer();
        return;
    }

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_DYING:
            SpriteDying();
            break;

        case SPRITE_POSE_UNINITIALIZED:
            ReoWingsInit();

        default:
            ReoWingsIdle();
            break;
    }
}
