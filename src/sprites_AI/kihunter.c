#include "data/sprites/kihunter.h"

#include "globals.h"

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

#define KIHUNTER_GROUND_IDLE_COUNTER work2 // Jump warnings done since the last turn around
#define KIHUNTER_GROUND_HIGH_JUMP work3
#define KIHUNTER_GROUND_SPIT_COUNT work3
#define KIHUNTER_Y_SPEED_IDX work4 // Also the index in the flying Y movement tables

#define KIHUNTER_FLYING_IDLE_LOOPS work1 // Idle Y movement loops done
#define KIHUNTER_FLYING_TIMER work1 // Swooping
#define KIHUNTER_FLYING_SLOWING_DOWN work1 // After swooping, set once back near the home Y position
#define KIHUNTER_FLYING_HOME_Y workX // Y position the kihunter returns to after swooping

#define KIHUNTER_WINGS_TIMER work1
#define KIHUNTER_HIVE_SPAWN_COOLDOWN workY

#define KIHUNTER_BUG_Y_MOVEMENT_IDX work4
#define KIHUNTER_BUG_X_MOVEMENT_IDX work3
#define KIHUNTER_BUG_CHASE_STAGE workX // Selects the offset of the target position, 0 to 3

enum KihunterGroundRange {
    KIHUNTER_GROUND_OUT_OF_RANGE,
    KIHUNTER_GROUND_SAMUS_IN_FRONT,
    KIHUNTER_GROUND_SAMUS_BEHIND
};

#define KIHUNTER_LOSE_WINGS_HEALTH_THRESHOLD 6 // Lose wings if less than or equal to this threshold

u8 KihunterGroundCheckInSpittingRange(void)
{
    u8 inRange;
    u32 nslr;

    inRange = FALSE;

    if (gCurrentSprite.status & SPRITE_STATUS_HIDDEN)
        return FALSE;

    if (gCurrentSprite.status & SPRITE_STATUS_ONSCREEN && gCurrentSprite.health > 0)
    {
        nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_TO_SUB_PIXEL(1.875f), BLOCK_TO_SUB_PIXEL(5.625f));
        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
        {
            if (nslr == NSLR_RIGHT)
                inRange = TRUE;
        }
        else
        {
            if (nslr == NSLR_LEFT)
                inRange = TRUE;
        }
    }

    return inRange;
}

u8 KihunterGroundDetectSamus(void)
{
    u8 result;
    u16 yRange;
    u16 xRange;
    u32 nslr;

    result = KIHUNTER_GROUND_OUT_OF_RANGE;

    if (gCurrentSprite.status & SPRITE_STATUS_HIDDEN)
        return FALSE;

    yRange = BLOCK_TO_SUB_PIXEL(3.75f);
    xRange = BLOCK_TO_SUB_PIXEL(7.8125f);
    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
    {
        xRange = BLOCK_TO_SUB_PIXEL(10.9375f);
        yRange = BLOCK_TO_SUB_PIXEL(6.875f);
        gCurrentSprite.status &= ~SPRITE_STATUS_SAMUS_DETECTED;
    }

    if (gCurrentSprite.health > 0)
    {
        nslr = SpriteUtilCheckSamusNearSpriteLeftRight(yRange, xRange);
        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
        {
            if (nslr == NSLR_RIGHT)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(2.0f),
                    gCurrentSprite.xPosition + BLOCK_TO_SUB_PIXEL(1.125f));
                if (gPreviousCollisionCheck != COLLISION_SOLID)
                    result = KIHUNTER_GROUND_SAMUS_IN_FRONT;
            }
            else if (nslr == NSLR_LEFT)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(2.0f),
                    gCurrentSprite.xPosition - BLOCK_TO_SUB_PIXEL(1.125f));
                if (gPreviousCollisionCheck != COLLISION_SOLID)
                    result = KIHUNTER_GROUND_SAMUS_BEHIND;
            }
        }
        else
        {
            if (nslr == NSLR_LEFT)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(2.0f),
                    gCurrentSprite.xPosition - BLOCK_TO_SUB_PIXEL(1.125f));
                if (gPreviousCollisionCheck != COLLISION_SOLID)
                    result = KIHUNTER_GROUND_SAMUS_IN_FRONT;
            }
            else if (nslr == NSLR_RIGHT)
            {
                SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(2.0f),
                    gCurrentSprite.xPosition + BLOCK_TO_SUB_PIXEL(1.125f));
                if (gPreviousCollisionCheck != COLLISION_SOLID)
                    result = KIHUNTER_GROUND_SAMUS_BEHIND;
            }
        }
    }

    return result;
}

void KihunterTurningIntoX(void)
{
    if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
    {
        SpriteSpawnNewXParasite(PSPRITE_X_PARASITE, gCurrentSprite.spriteId, 0, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.spritesetSlotAndProperties, gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(0.4375f),
            gCurrentSprite.xPosition - BLOCK_TO_SUB_PIXEL(0.375f), SPRITE_STATUS_X_FLIP);
        gCurrentSprite.yPosition -= BLOCK_TO_SUB_PIXEL(1.0f);
        gCurrentSprite.xPosition += BLOCK_TO_SUB_PIXEL(0.375f);
    }
    else
    {
        SpriteSpawnNewXParasite(PSPRITE_X_PARASITE, gCurrentSprite.spriteId, 0, gCurrentSprite.primarySpriteRamSlot,
            gCurrentSprite.spritesetSlotAndProperties, gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(0.4375f),
            gCurrentSprite.xPosition + BLOCK_TO_SUB_PIXEL(0.375f), SPRITE_STATUS_X_FLIP);
        gCurrentSprite.yPosition -= BLOCK_TO_SUB_PIXEL(1.0f);
        gCurrentSprite.xPosition -= BLOCK_TO_SUB_PIXEL(0.375f);
    }
}

void KihunterGroundInit(void)
{
    SpriteUtilTrySetAbsorbXFlag();
    if (gCurrentSprite.properties & SP_CAN_ABSORB_X)
    {
        gCurrentSprite.status = 0;
        return;
    }

    gCurrentSprite.KIHUNTER_GROUND_IDLE_COUNTER = 0;
    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(2);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1.5f);
    gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(1.5f);
    gCurrentSprite.hitboxBottom = 0;
    gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(0.625f);
    gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(0.625f);
    gCurrentSprite.pOam = sKihunterGroundOam_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    if (gCurrentSprite.health == 0)
        gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);

    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    SpriteUtilMakeSpriteFaceSamusXFlip();

    if (gCurrentSprite.pose == SPRITE_POSE_SPAWNING_FROM_X_INIT)
    {
        gCurrentSprite.pose = SPRITE_POSE_SPAWNING_FROM_X;
        gCurrentSprite.SPRITE_X_SPAWN_MOSAIC_IDX = X_PARASITE_MOSAIC_MAX_INDEX;
    }
    else
    {
        gCurrentSprite.pose = 1;
    }
}

void KihunterGroundJumpWarningInit(void)
{
    gCurrentSprite.pose = 2;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.KIHUNTER_GROUND_IDLE_COUNTER++;

    if (gSpriteRandomNumber & 1)
    {
        gCurrentSprite.KIHUNTER_GROUND_HIGH_JUMP = FALSE;
        gCurrentSprite.pOam = sKihunterGroundOam_StartLowJump;
    }
    else
    {
        gCurrentSprite.KIHUNTER_GROUND_HIGH_JUMP = TRUE;
        gCurrentSprite.pOam = sKihunterGroundOam_StartHighJump;
    }
}

void KihunterGroundJumpInit(void)
{
    gCurrentSprite.pose = 0x18;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = 0;

    if (gCurrentSprite.KIHUNTER_GROUND_HIGH_JUMP)
    {
        gCurrentSprite.yPosition -= BLOCK_TO_SUB_PIXEL(0.75f);
        gCurrentSprite.pOam = sKihunterGroundOam_JumpingHighOrFalling;
    }
    else
    {
        gCurrentSprite.yPosition -= BLOCK_TO_SUB_PIXEL(0.5f);
        gCurrentSprite.pOam = sKihunterGroundOam_JumpingLow;
    }

    SoundPlayNotAlreadyPlaying(SOUND_KIHUNTER_JUMPING);
}

void KihunterGroundLandingInit(void)
{
    gCurrentSprite.pose = 0x1a;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.pOam = sKihunterGroundOam_Landing;
}

void KihunterIdleInit(void)
{
    gCurrentSprite.pose = 8;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.pOam = sKihunterGroundOam_Idle;
}

void KihunterFallingInit(void)
{
    gCurrentSprite.pose = 0x16;
    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = 0;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.pOam = sKihunterGroundOam_JumpingHighOrFalling;
}

void KihunterGroundTurningAroundInit(void)
{
    gCurrentSprite.pose = 4;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.KIHUNTER_GROUND_IDLE_COUNTER = 0;
    gCurrentSprite.pOam = sKihunterFlyingOam_TurningAround1;
}

void KihunterGroundSpittingInit(void)
{
    gCurrentSprite.pose = 0x2a;
    gCurrentSprite.pOam = sKihunterGroundOam_Spitting;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    if (gSpriteRandomNumber & 1)
        gCurrentSprite.KIHUNTER_GROUND_SPIT_COUNT = 1;
    else
        gCurrentSprite.KIHUNTER_GROUND_SPIT_COUNT = 2;
}

void KihunterGroundJumpWarning(void)
{
    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition + gCurrentSprite.hitboxRight);
    if (gPreviousCollisionCheck == COLLISION_AIR)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
            gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft);
        if (gPreviousCollisionCheck == COLLISION_AIR)
        {
            KihunterFallingInit();
            return;
        }
    }

    if (SpriteUtilHasCurrentAnimationEnded())
        KihunterGroundJumpInit();
}

void KihunterGroundJumping(void)
{
    u8 colliding;
    s16 movement;
    u32 blockTop;

    colliding = FALSE;

    if (!gCurrentSprite.KIHUNTER_GROUND_HIGH_JUMP)
        movement = sKihunterGroundLowJumpSpeed[gCurrentSprite.KIHUNTER_Y_SPEED_IDX / 4];
    else
        movement = sKihunterGroundHighJumpSpeed[gCurrentSprite.KIHUNTER_Y_SPEED_IDX / 4];

    if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
            gCurrentSprite.xPosition + gCurrentSprite.hitboxRight + BLOCK_TO_SUB_PIXEL(0.0625f));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            colliding++;
            gCurrentSprite.xPosition -= BLOCK_TO_SUB_PIXEL(0.0625f);
        }
        else
        {
            gCurrentSprite.xPosition += BLOCK_TO_SUB_PIXEL(0.03125f);
        }
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - QUARTER_BLOCK_SIZE,
            gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft - BLOCK_TO_SUB_PIXEL(0.0625f));

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            colliding++;
            gCurrentSprite.xPosition += BLOCK_TO_SUB_PIXEL(0.0625f);
        }
        else
        {
            gCurrentSprite.xPosition -= BLOCK_TO_SUB_PIXEL(0.03125f);
        }
    }

    gCurrentSprite.yPosition += movement;
    if (gCurrentSprite.KIHUNTER_Y_SPEED_IDX < ARRAY_SIZE(sKihunterGroundLowJumpSpeed) * 4 - 1)
        gCurrentSprite.KIHUNTER_Y_SPEED_IDX++;

    if (movement > 0)
    {
        blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition, gCurrentSprite.xPosition);
        if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
        {
            gCurrentSprite.yPosition = blockTop;
            KihunterGroundLandingInit();
            return;
        }

        if (!colliding)
        {
            blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition,
                gCurrentSprite.xPosition + gCurrentSprite.hitboxRight);
            if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
            {
                colliding++;
            }
            else
            {
                blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition,
                    gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft);
                if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
                    colliding++;
            }

            if (colliding)
            {
                gCurrentSprite.yPosition = blockTop;
                KihunterGroundLandingInit();
            }
        }
    }
    else
    {
        colliding = FALSE;

        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxTop,
            gCurrentSprite.xPosition + gCurrentSprite.hitboxRight);

        if (gPreviousCollisionCheck == COLLISION_SOLID)
        {
            colliding++;
        }
        else
        {
            SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + gCurrentSprite.hitboxTop,
                gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft);

            if (gPreviousCollisionCheck == COLLISION_SOLID)
                colliding++;
        }

        if (colliding)
        {
            if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
                gCurrentSprite.xPosition -= BLOCK_TO_SUB_PIXEL(0.0625f);
            else
                gCurrentSprite.xPosition += BLOCK_TO_SUB_PIXEL(0.0625f);

            KihunterFallingInit();
        }
    }
}

void KihunterGroundLanding(void)
{
    u8 result;

    if (SpriteUtilHasCurrentAnimationEnded())
    {
        if (KihunterGroundCheckInSpittingRange())
        {
            KihunterGroundSpittingInit();
        }
        else
        {
            result = KihunterGroundDetectSamus();
            if (result == KIHUNTER_GROUND_SAMUS_IN_FRONT)
            {
                KihunterGroundJumpInit();
            }
            else if (result == KIHUNTER_GROUND_SAMUS_BEHIND)
            {
                KihunterGroundTurningAroundInit();
            }
            else
            {
                if (gCurrentSprite.KIHUNTER_GROUND_IDLE_COUNTER >= 3)
                    KihunterIdleInit();
                else
                    KihunterGroundJumpWarningInit();
            }
        }
    }
}

void KihunterGroundFalling(void)
{
    u8 offset;
    s16 movement;
    u8 collision;
    u32 blockTop;

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
        KihunterGroundLandingInit();
    }
    else
    {
        offset = gCurrentSprite.KIHUNTER_Y_SPEED_IDX;
        movement = sSpritesFallingSpeed[offset];
        if (movement == SHORT_MAX)
        {
            movement = sSpritesFallingSpeed[offset - 1];
            gCurrentSprite.yPosition += movement;
        }
        else
        {
            offset++;
            gCurrentSprite.KIHUNTER_Y_SPEED_IDX = offset;
            gCurrentSprite.yPosition += movement;
        }
    }
}

void KihunterGroundIdle(void)
{
    u8 result;

    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition + gCurrentSprite.hitboxRight);
    if (gPreviousCollisionCheck == COLLISION_AIR)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition,
            gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft);
        if (gPreviousCollisionCheck == COLLISION_AIR)
        {
            KihunterFallingInit();
            return;
        }
    }

    if (SpriteUtilHasCurrentAnimationEnded())
    {
        result = KihunterGroundDetectSamus();
        if (result == KIHUNTER_GROUND_SAMUS_IN_FRONT)
        {
            KihunterGroundJumpWarningInit();
        }
        else if (result == KIHUNTER_GROUND_SAMUS_BEHIND)
        {
            KihunterGroundTurningAroundInit();
        }
        else
        {
            if (gCurrentSprite.KIHUNTER_GROUND_IDLE_COUNTER >= 3)
                KihunterGroundTurningAroundInit();
            else
                KihunterGroundJumpWarningInit();
        }
    }
}

void KihunterGroundTurningAround(void)
{
    if (gCurrentSprite.currentAnimationFrame > 0)
        gCurrentSprite.yPosition -= PIXEL_SIZE;

    if (SpriteUtilHasCurrentAnimationEnded())
    {
        gCurrentSprite.status ^= SPRITE_STATUS_X_FLIP;
        gCurrentSprite.pose = 5;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.pOam = sKihunterFlyingOam_TurningAround2;
    }
}

void KihunterGroundTurningAroundSecondPart(void)
{
    if (gCurrentSprite.currentAnimationFrame > 0)
        gCurrentSprite.yPosition += PIXEL_SIZE;

    if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(0.25f),
            gCurrentSprite.xPosition + gCurrentSprite.hitboxRight + BLOCK_TO_SUB_PIXEL(0.0625f));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
            gCurrentSprite.xPosition -= PIXEL_SIZE;
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(0.25f),
            gCurrentSprite.xPosition + gCurrentSprite.hitboxLeft - BLOCK_TO_SUB_PIXEL(0.0625f));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
            gCurrentSprite.xPosition += PIXEL_SIZE;
    }

    if (SpriteUtilHasCurrentAnimationEnded())
        KihunterIdleInit();
}

void KihunterGroundSpitting(void)
{
    if (gCurrentSprite.currentAnimationFrame == 11 && gCurrentSprite.animationDurationCounter == 3)
    {
        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            SpriteSpawnSecondary(SSPRITE_KIHUNTER_SPIT, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(1.375f),
                gCurrentSprite.xPosition + BLOCK_TO_SUB_PIXEL(1.5f), SPRITE_STATUS_X_FLIP);
        else
            SpriteSpawnSecondary(SSPRITE_KIHUNTER_SPIT, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(1.375f),
                gCurrentSprite.xPosition - BLOCK_TO_SUB_PIXEL(1.5f), 0);

        SoundPlayNotAlreadyPlaying(SOUND_KIHUNTER_SPITTING);
    }

    if (SpriteUtilHasCurrentAnimationEnded())
    {
        if (--gCurrentSprite.KIHUNTER_GROUND_SPIT_COUNT == 0)
            KihunterGroundJumpWarningInit();
    }
}

u8 KihunterFlyingXMovement(u16 movement)
{
    if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(0.25f),
            gCurrentSprite.xPosition + BLOCK_TO_SUB_PIXEL(0.75f));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
            return TRUE;
        gCurrentSprite.xPosition += movement;
    }
    else
    {
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(0.25f),
            gCurrentSprite.xPosition - BLOCK_TO_SUB_PIXEL(0.75f));
        if (gPreviousCollisionCheck == COLLISION_SOLID)
            return TRUE;
        gCurrentSprite.xPosition -= movement;
    }

    return FALSE;
}

void KihunterFlyingInit(void)
{
    u8 ramSlot;

    SpriteUtilTrySetAbsorbXFlag();
    if (gCurrentSprite.properties & SP_CAN_ABSORB_X)
    {
        gCurrentSprite.status = 0;
        return;
    }

    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(2);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1.5f);
    gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(1.5f);
    gCurrentSprite.hitboxBottom = 0;
    gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(0.625f);
    gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(0.625f);
    gCurrentSprite.pOam = sKihunterFlyingOam_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.KIHUNTER_FLYING_IDLE_LOOPS = 0;
    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = 0;
    gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    SpriteUtilMakeSpriteFaceSamusXFlip();

    if (gCurrentSprite.pose == SPRITE_POSE_SPAWNING_FROM_X_INIT)
    {
        gCurrentSprite.pose = SPRITE_POSE_SPAWNING_FROM_X;
        gCurrentSprite.SPRITE_X_SPAWN_MOSAIC_IDX = X_PARASITE_MOSAIC_MAX_INDEX;
        gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    }
    else
    {
        gCurrentSprite.pose = SPRITE_POSE_IDLE_INIT;
    }

    gCurrentSprite.KIHUNTER_FLYING_HOME_Y = gCurrentSprite.yPosition;

    ramSlot = SpriteSpawnSecondary(SSPRITE_KIHUNTER_WINGS, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition,
        gCurrentSprite.status & SPRITE_STATUS_X_FLIP);
    if (ramSlot == UCHAR_MAX)
        gCurrentSprite.status = 0;
}

void KihunterFlyingIdleInit(void)
{
    gCurrentSprite.pose = SPRITE_POSE_IDLE;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.pOam = sKihunterFlyingOam_Idle;
    gCurrentSprite.KIHUNTER_FLYING_IDLE_LOOPS = 0;
    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = 0;
}

void KihunterFlyingTurningAroundInit(void)
{
    gCurrentSprite.pose = 4;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.pOam = sKihunterFlyingOam_TurningAround1;
}

void KihunterFlyingIdle(void)
{
    u16 targetY;
    u16 spriteY;
    u8 nslr;
    u8 offset;
    s16 movement;

    offset = gCurrentSprite.KIHUNTER_Y_SPEED_IDX;
    movement = sKihunterFlyingIdleYMovement[offset];
    if (movement == SHORT_MAX)
    {
        movement = sKihunterFlyingIdleYMovement[0];
        offset = 0;
    }
    offset++;
    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = offset;

    if (movement > 0)
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition, gCurrentSprite.xPosition);
    else
        SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(1.5f),
            gCurrentSprite.xPosition);

    if (gPreviousCollisionCheck != COLLISION_SOLID)
        gCurrentSprite.yPosition += movement;

    if (KihunterFlyingXMovement(PIXEL_SIZE / 2))
    {
        gCurrentSprite.pose = 3;
        return;
    }

    if (gCurrentSprite.KIHUNTER_Y_SPEED_IDX == ARRAY_SIZE(sKihunterFlyingIdleYMovement) - 2)
    {
        gCurrentSprite.KIHUNTER_FLYING_IDLE_LOOPS++;
        targetY = gSamusData.yPosition;
        spriteY = gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(1.5f);
        nslr = SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_TO_SUB_PIXEL(10.0f), BLOCK_TO_SUB_PIXEL(15.0f));
        if (targetY < spriteY)
            nslr = NSLR_OUT_OF_RANGE;

        if (nslr != NSLR_OUT_OF_RANGE)
        {
            if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            {
                if (gCurrentSprite.xPosition > gSamusData.xPosition)
                {
                    if (gCurrentSprite.KIHUNTER_FLYING_IDLE_LOOPS >= 2)
                        gCurrentSprite.pose = 3;
                }
                else
                {
                    gCurrentSprite.pose = 0x29;
                }
            }
            else
            {
                if (gCurrentSprite.xPosition < gSamusData.xPosition)
                {
                    if (gCurrentSprite.KIHUNTER_FLYING_IDLE_LOOPS >= 2)
                        gCurrentSprite.pose = 3;
                }
                else
                {
                    gCurrentSprite.pose = 0x29;
                }
            }
        }
    }
}

void KihunterTurningAround(void)
{
    if (SpriteUtilHasCurrentAnimationEnded())
    {
        gCurrentSprite.status ^= SPRITE_STATUS_X_FLIP;
        gCurrentSprite.pose = 5;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.pOam = sKihunterFlyingOam_TurningAround2;
    }
}

void KihunterFlyingTurningAroundSecondPart(void)
{
    if (SpriteUtilHasCurrentAnimationEnded())
        KihunterFlyingIdleInit();
}

void KihunterFlyingUpdateSwipeAnimation(void)
{
    if (gCurrentSprite.samusCollision == SSC_HURTS_SAMUS_DOUBLE_DAMAGE)
        return;

    if ((u8)SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_TO_SUB_PIXEL(2.5f), BLOCK_TO_SUB_PIXEL(2.0f)) !=
        NSLR_OUT_OF_RANGE)
    {
        if (gCurrentSprite.pOam != sKihunterFlyingOam_Swiping)
        {
            gCurrentSprite.pOam = sKihunterFlyingOam_Swiping;
            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;
        }
        else if (gCurrentSprite.currentAnimationFrame == 2 && gCurrentSprite.animationDurationCounter == 4)
        {
            SoundPlayNotAlreadyPlaying(SOUND_KIHUNTER_SWIPING);
        }
    }
    else
    {
        if (gCurrentSprite.pOam == sKihunterFlyingOam_Swiping)
        {
            if (gCurrentSprite.currentAnimationFrame == 2 && gCurrentSprite.animationDurationCounter == 4)
                SoundPlayNotAlreadyPlaying(SOUND_KIHUNTER_SWIPING);

            if (SpriteUtilHasCurrentAnimationEnded())
            {
                gCurrentSprite.pOam = sKihunterFlyingOam_Idle;
                gCurrentSprite.animationDurationCounter = 0;
                gCurrentSprite.currentAnimationFrame = 0;
            }
        }
    }
}

void KihunterFlyingSwoopingDownInit(void)
{
    u16 targetY;

    gCurrentSprite.KIHUNTER_FLYING_TIMER = 16;
    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = 0;
    gCurrentSprite.pose = 0x2a;
    targetY = gSamusData.yPosition + gSamusData.drawDistanceTop / 2;

    if (targetY - gCurrentSprite.yPosition > BLOCK_TO_SUB_PIXEL(5.625f) || gSpriteRandomNumber >= 11)
    {
        gCurrentSprite.pOam = sKihunterFlyingOam_LungingWithStinger;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.samusCollision = SSC_HURTS_SAMUS_DOUBLE_DAMAGE;
        SoundPlayNotAlreadyPlaying(SOUND_KIHUNTER_LUNGING_WITH_STINGER);
    }
    else
    {
        SoundPlayNotAlreadyPlaying(SOUND_KIHUNTER_SWOOPING);
    }
}

void KihunterFlyingSwoopingDown(void)
{
    u16 xMovement;
    u8 offset;
    s16 yMovement;

    KihunterFlyingUpdateSwipeAnimation();

    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(0.25f), gCurrentSprite.xPosition);
    if (gPreviousCollisionCheck == COLLISION_SOLID)
    {
        if (KihunterFlyingXMovement(PIXEL_TO_SUB_PIXEL(1.5f)))
            gCurrentSprite.pose = 0x2d;
        if (--gCurrentSprite.KIHUNTER_FLYING_TIMER == 0)
            gCurrentSprite.pose = 0x2d;
        return;
    }

    if (gCurrentSprite.samusCollision == SSC_HURTS_SAMUS_DOUBLE_DAMAGE)
    {
        xMovement = gCurrentSprite.KIHUNTER_Y_SPEED_IDX / 4;
        if (xMovement > 4)
            xMovement = 8;
    }
    else
    {
        xMovement = gCurrentSprite.KIHUNTER_Y_SPEED_IDX / 2;
        if (xMovement > 8)
            xMovement = 8;
    }

    KihunterFlyingXMovement(xMovement);

    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(2.0f), gCurrentSprite.xPosition);
    if (gPreviousCollisionCheck == COLLISION_SOLID)
    {
        gCurrentSprite.pose = 0x2b;
        return;
    }

    offset = gCurrentSprite.KIHUNTER_Y_SPEED_IDX;
    yMovement = sKihunterFlyingSwoopingDownYSpeed[offset];
    if (yMovement == SHORT_MAX)
    {
        yMovement = sKihunterFlyingSwoopingDownYSpeed[offset - 1];
        gCurrentSprite.yPosition += yMovement;
    }
    else
    {
        offset++;
        gCurrentSprite.KIHUNTER_Y_SPEED_IDX = offset;
        gCurrentSprite.yPosition += yMovement;
    }
}

void KihunterFlyingSwoopingAcrossInit(void)
{
    gCurrentSprite.KIHUNTER_FLYING_TIMER = 20;
    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = 0;
    gCurrentSprite.pose = 0x2c;
}

void KihunterFlyingSwoopingAcross(void)
{
    u8 hitWall;
    u8 offset;
    s16 yMovement;

    KihunterFlyingUpdateSwipeAnimation();

    hitWall = KihunterFlyingXMovement(BLOCK_TO_SUB_PIXEL(0.125f));

    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(0.25f), gCurrentSprite.xPosition);
    if (gPreviousCollisionCheck == COLLISION_SOLID)
    {
        if (hitWall)
            gCurrentSprite.pose = 0x2d;
        if (--gCurrentSprite.KIHUNTER_FLYING_TIMER == 0)
            gCurrentSprite.pose = 0x2d;
        return;
    }

    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(2.0f), gCurrentSprite.xPosition);
    if (gPreviousCollisionCheck == COLLISION_SOLID)
    {
        offset = gCurrentSprite.KIHUNTER_Y_SPEED_IDX;
        yMovement = sKihunterFlyingSwoopingAcrossYSpeed[offset];
        if (yMovement == SHORT_MAX)
        {
            yMovement = sKihunterFlyingSwoopingAcrossYSpeed[offset - 1];
            gCurrentSprite.yPosition += yMovement;
        }
        else
        {
            offset++;
            gCurrentSprite.KIHUNTER_Y_SPEED_IDX = offset;
            gCurrentSprite.yPosition += yMovement;
        }
    }
    else
    {
        gCurrentSprite.KIHUNTER_FLYING_TIMER = 0;
        gCurrentSprite.KIHUNTER_Y_SPEED_IDX = 0;
        gCurrentSprite.pose = 0x2a;
    }
}

void KihunterFlyingAfterSwoopingInit(void)
{
    gCurrentSprite.KIHUNTER_FLYING_SLOWING_DOWN = FALSE;
    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = 0;
    gCurrentSprite.pose = 0x2e;

    if (gCurrentSprite.samusCollision == SSC_HURTS_SAMUS_DOUBLE_DAMAGE)
    {
        gCurrentSprite.pOam = sKihunterFlyingOam_Idle;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.samusCollision = 2;
    }
}

void KihunterFlyingAfterSwooping(void)
{
    u8 finished;

    finished = FALSE;

    if (SpriteUtilHasCurrentAnimationEnded() && gCurrentSprite.pOam == sKihunterFlyingOam_Swiping)
    {
        gCurrentSprite.pOam = sKihunterFlyingOam_Idle;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
    }

    KihunterFlyingXMovement(6);

    SpriteUtilCheckCollisionAtPosition(gCurrentSprite.yPosition - BLOCK_TO_SUB_PIXEL(2.0f), gCurrentSprite.xPosition);
    if (gPreviousCollisionCheck != COLLISION_SOLID)
    {
        if (!gCurrentSprite.KIHUNTER_FLYING_SLOWING_DOWN)
        {
            if (gCurrentSprite.KIHUNTER_FLYING_HOME_Y + BLOCK_TO_SUB_PIXEL(1.0f) < gCurrentSprite.yPosition)
            {
                u8 offset = gCurrentSprite.KIHUNTER_Y_SPEED_IDX;
                s16 yMovement = sKihunterFlyingAfterSwoopingAcceleratingYSpeed[offset];

                if (yMovement == SHORT_MAX)
                {
                    yMovement = sKihunterFlyingAfterSwoopingAcceleratingYSpeed[offset - 1];
                    gCurrentSprite.yPosition += yMovement;
                }
                else
                {
                    offset++;
                    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = offset;
                    gCurrentSprite.yPosition += yMovement;
                }
            }
            else
            {
                gCurrentSprite.KIHUNTER_FLYING_SLOWING_DOWN = TRUE;
                gCurrentSprite.KIHUNTER_Y_SPEED_IDX = 0;
            }
        }
        else
        {
            if (gCurrentSprite.KIHUNTER_FLYING_HOME_Y < gCurrentSprite.yPosition)
            {
                u8 offset = gCurrentSprite.KIHUNTER_Y_SPEED_IDX;
                s16 yMovement = sKihunterFlyingAfterSwoopingDeceleratingYSpeed[offset];

                if (yMovement == SHORT_MAX)
                {
                    yMovement = sKihunterFlyingAfterSwoopingDeceleratingYSpeed[offset - 1];
                    gCurrentSprite.yPosition += yMovement;
                }
                else
                {
                    offset++;
                    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = offset;
                    gCurrentSprite.yPosition += yMovement;
                }
            }
            else
            {
                finished++;
            }
        }
    }
    else
    {
        finished++;
    }

    if (finished)
    {
        gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
        {
            if (gCurrentSprite.xPosition > gSamusData.xPosition)
                gCurrentSprite.pose = 3;
            else
                gCurrentSprite.pose = 1;
        }
        else
        {
            if (gCurrentSprite.xPosition < gSamusData.xPosition)
                gCurrentSprite.pose = 3;
            else
                gCurrentSprite.pose = 1;
        }
    }
}

void KihunterWingsInit(void)
{
    u8 primary;

    primary = gCurrentSprite.primarySpriteRamSlot;
    if (gSpriteData[primary].status & SPRITE_STATUS_MOSAIC)
        gCurrentSprite.status |= SPRITE_STATUS_MOSAIC;
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(2.5f);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1.5f);
    gCurrentSprite.hitboxTop = -4;
    gCurrentSprite.hitboxBottom = 4;
    gCurrentSprite.hitboxLeft = -4;
    gCurrentSprite.hitboxRight = 4;
    gCurrentSprite.pose = 2;
    gCurrentSprite.drawOrder = 3;
    gCurrentSprite.pOam = sKihunterWingsOam_Flapping;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
}

void KihunterWingsIdle(void)
{
    u8 primary;

    primary = gCurrentSprite.primarySpriteRamSlot;

    gCurrentSprite.yPosition = gSpriteData[primary].yPosition;
    gCurrentSprite.xPosition = gSpriteData[primary].xPosition;
    if (gSpriteData[primary].pose == SPRITE_POSE_DYING_INIT || gSpriteData[primary].pose == SPRITE_POSE_DYING)
    {
        SpriteDyingInit();
        SpriteDying();
        return;
    }

    if (gSpriteData[primary].status & SPRITE_STATUS_MOSAIC)
        gCurrentSprite.status |= SPRITE_STATUS_MOSAIC;
    else
        gCurrentSprite.status &= ~SPRITE_STATUS_MOSAIC;

    if (gSpriteData[primary].status & SPRITE_STATUS_X_FLIP)
        gCurrentSprite.status |= SPRITE_STATUS_X_FLIP;
    else
        gCurrentSprite.status &= ~SPRITE_STATUS_X_FLIP;

    if (gSpriteData[primary].health <= KIHUNTER_LOSE_WINGS_HEALTH_THRESHOLD)
    {
        gCurrentSprite.pose = 0x38;
        gCurrentSprite.pOam = sKihunterWingsOam_Falling;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.paletteRow = 0;

        gCurrentSprite.yPosition -= BLOCK_TO_SUB_PIXEL(1.5f);
        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            gCurrentSprite.xPosition -= BLOCK_TO_SUB_PIXEL(0.5f);
        else
            gCurrentSprite.xPosition += BLOCK_TO_SUB_PIXEL(0.5f);
    }
}

void KihunterWingsFalling(void)
{
    u32 blockTop;

    blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition, gCurrentSprite.xPosition);
    if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
    {
        gCurrentSprite.yPosition = blockTop;
        gCurrentSprite.pose = 0x3a;
        gCurrentSprite.KIHUNTER_WINGS_TIMER = 40;
    }
    else
    {
        gCurrentSprite.yPosition += PIXEL_SIZE / 2;
    }
}

void KihunterWingsDisappearing(void)
{
    if (MOD_AND(gFrameCounter8Bit, 4) == 0)
        gCurrentSprite.status ^= SPRITE_STATUS_NOT_DRAWN;
    if (--gCurrentSprite.KIHUNTER_WINGS_TIMER == 0)
        gCurrentSprite.status = 0;
}

void KihunterSpitInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.properties |= SP_KILL_OFF_SCREEN;
    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(0.125f);
    gCurrentSprite.hitboxBottom = BLOCK_TO_SUB_PIXEL(0.125f);
    gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(0.125f);
    gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(0.125f);
    gCurrentSprite.pOam = sKihunterSpitOam_Moving;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.KIHUNTER_Y_SPEED_IDX = 0;
    gCurrentSprite.pose = 2;
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS_DIES_WHEN_HIT;
}

void KihunterSpitMoving(void)
{
    u32 blockTop;
    u8 offset;
    s16 yMovement;

    blockTop = SpriteUtilCheckVerticalCollisionAtPositionSlopes(gCurrentSprite.yPosition, gCurrentSprite.xPosition);
    if (gPreviousVerticalCollisionCheck != COLLISION_AIR)
    {
        gCurrentSprite.yPosition = blockTop;
        gCurrentSprite.pose = SPRITE_POSE_STOPPED;
    }
    else
    {
        offset = gCurrentSprite.KIHUNTER_Y_SPEED_IDX;
        yMovement = sKihunterSpitFallingSpeed[offset];
        if (yMovement == SHORT_MAX)
        {
            yMovement = sKihunterSpitFallingSpeed[offset - 1];
            gCurrentSprite.yPosition += yMovement;
        }
        else
        {
            offset++;
            gCurrentSprite.KIHUNTER_Y_SPEED_IDX = offset;
            gCurrentSprite.yPosition += yMovement;
        }

        if (gCurrentSprite.status & SPRITE_STATUS_X_FLIP)
            gCurrentSprite.xPosition += BLOCK_TO_SUB_PIXEL(0.1875f);
        else
            gCurrentSprite.xPosition -= BLOCK_TO_SUB_PIXEL(0.1875f);
    }
}

void KihunterSpitExplodingInit(void)
{
    gCurrentSprite.pose = 0x38;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.pOam = sKihunterSpitOam_Exploding;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
}

void KihunterSpitExploding(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;
    if (SpriteUtilHasCurrentAnimationEnded())
        gCurrentSprite.status = 0;
}

void KihunterHiveInit(void)
{
    SpriteUtilTrySetAbsorbXFlag();
    if (!(gCurrentSprite.properties & SP_CAN_ABSORB_X))
    {
        gCurrentSprite.status = 0;
        return;
    }

    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);
    gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(1.0f);
    gCurrentSprite.hitboxBottom = BLOCK_TO_SUB_PIXEL(0.75f);
    gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(0.75f);
    gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(0.75f);
    gCurrentSprite.samusCollision = SSC_SOLID;
    gCurrentSprite.frozenPaletteRowOffset = 1;
    gCurrentSprite.drawOrder = 13;
    gCurrentSprite.pOam = sKihunterHiveOam;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    gCurrentSprite.pose = SPRITE_POSE_IDLE;

    SpriteSpawnSecondary(SSPRITE_KIHUNTER_BUG, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(1.5f),
        gCurrentSprite.xPosition - BLOCK_TO_SUB_PIXEL(0.5f), 0);
    SpriteSpawnSecondary(SSPRITE_KIHUNTER_BUG, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(1.5f),
        gCurrentSprite.xPosition + BLOCK_TO_SUB_PIXEL(0.5f), 0);

    SoundPlayOrResume(SOUND_KIHUNTER_HIVE_BUZZING);
}

void KihunterHiveSpawnKihunter(void)
{
    u16 flip;
    u8 ramSlot;

    gCurrentSprite.numberOfXToForm = 1;
    gCurrentSprite.spritesetSlotAndProperties = SSP_UNINFECTED_OR_BOSS;
    gCurrentSprite.status &= ~(SPRITE_STATUS_MOSAIC | SPRITE_STATUS_IGNORE_PROJECTILES);
    gCurrentSprite.pose = 0x5a;
    gCurrentSprite.KIHUNTER_HIVE_SPAWN_COOLDOWN = X_PARASITE_MOSAIC_MAX_INDEX;

    if (gCurrentSprite.xPosition > gSamusData.xPosition)
        flip = 0;
    else
        flip = SPRITE_STATUS_X_FLIP;

    ramSlot = SpriteSpawnPrimary(PSPRITE_KIHUNTER_FLYING, 0, gCurrentSprite.spritesetGfxSlot, SSP_X_ABSORBABLE_BY_SAMUS,
        gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(2.0f), gCurrentSprite.xPosition, flip);
    // BUG: Doesn't check if spawning failed, so ramSlot can go out of bounds
#ifdef BUGFIX
    if (ramSlot != UCHAR_MAX)
#endif // BUGFIX
    {
        gSpriteData[ramSlot].pose = SPRITE_POSE_SPAWNING_FROM_X_INIT;
        gSpriteData[ramSlot].status |= SPRITE_STATUS_MOSAIC | SPRITE_STATUS_IGNORE_PROJECTILES;
        gSpriteData[ramSlot].status &= ~SPRITE_STATUS_HIDDEN;
        gSpriteData[ramSlot].properties &= ~SP_CAN_ABSORB_X;
    }
}

void KihunterHiveSpawnCooldown(void)
{
    if (--gCurrentSprite.KIHUNTER_HIVE_SPAWN_COOLDOWN == 0)
    {
        gCurrentSprite.pose = SPRITE_POSE_IDLE;
        gCurrentSprite.properties |= SP_CAN_ABSORB_X;
    }
}

void KihunterBugInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(.5f);
    gCurrentSprite.hitboxTop = -PIXEL_SIZE;
    gCurrentSprite.hitboxBottom = PIXEL_SIZE;
    gCurrentSprite.hitboxLeft = -PIXEL_SIZE;
    gCurrentSprite.hitboxRight = PIXEL_SIZE;
    gCurrentSprite.pOam = sKihunterBugOam;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
#ifndef BUGFIX
    gCurrentSprite.KIHUNTER_BUG_Y_MOVEMENT_IDX = 0; // Unnecessary assignment
#endif // !BUGFIX
    gCurrentSprite.pose = SPRITE_POSE_IDLE;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.drawOrder = 12;
    gCurrentSprite.KIHUNTER_BUG_Y_MOVEMENT_IDX = gSpriteRandomNumber * 4;

    if (gSpriteRandomNumber & 1)
        gCurrentSprite.KIHUNTER_BUG_X_MOVEMENT_IDX = 20;
    else
        gCurrentSprite.KIHUNTER_BUG_X_MOVEMENT_IDX = 60;
}

void KihunterBugIdle(void)
{
    u8 offset;
    s16 movement;

    offset = gCurrentSprite.KIHUNTER_BUG_Y_MOVEMENT_IDX;
    movement = sKihunterBugIdleYMovement[offset];

    if (movement == SHORT_MAX)
    {
        movement = sKihunterBugIdleYMovement[0];
        offset = 0;
    }
    offset++;
    gCurrentSprite.KIHUNTER_BUG_Y_MOVEMENT_IDX = offset;
    gCurrentSprite.yPosition += movement;

    offset = gCurrentSprite.KIHUNTER_BUG_X_MOVEMENT_IDX;
    movement = sKihunterBugIdleXMovement[gCurrentSprite.KIHUNTER_BUG_X_MOVEMENT_IDX];
    if (movement == SHORT_MAX)
    {
        movement = sKihunterBugIdleXMovement[0];
        offset = 0;
    }
    offset++;
    gCurrentSprite.KIHUNTER_BUG_X_MOVEMENT_IDX = offset;
    gCurrentSprite.xPosition += movement;

    if (gSpriteData[gCurrentSprite.primarySpriteRamSlot].health == 0)
    {
        // Its hive is destroyed
        gCurrentSprite.pose = 0x17;
        gCurrentSprite.drawOrder = 4;
    }
}

void KihunterBugChasingSamusInit(void)
{
    gCurrentSprite.SPRITE_X_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_X_SPEED_INC = 1;
    gCurrentSprite.SPRITE_Y_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
    gCurrentSprite.KIHUNTER_BUG_CHASE_STAGE = 0;
    gCurrentSprite.pose = 0x18;

    SpriteUtilMakeSpriteFaceSamusDirection();
    if (gCurrentSprite.yPosition > gSamusData.yPosition + gSamusData.drawDistanceTop)
        gCurrentSprite.status &= ~SPRITE_STATUS_FACING_DOWN;
    else
        gCurrentSprite.status |= SPRITE_STATUS_FACING_DOWN;
}

void KihunterBugChasingSamus(void)
{
    u16 targetY;
    u16 targetX;
    u8 ySpeedCap;
    u8 xSpeedCap;

    targetY = gSamusData.yPosition + gSamusData.drawDistanceTop;
    targetX = gSamusData.xPosition;
    ySpeedCap = 30;
    xSpeedCap = 40;

    switch (gCurrentSprite.KIHUNTER_BUG_CHASE_STAGE)
    {
        case 1:
            targetY -= BLOCK_TO_SUB_PIXEL(0.5f);
            if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
                targetX += BLOCK_TO_SUB_PIXEL(0.75f);
            else
                targetX -= BLOCK_TO_SUB_PIXEL(0.75f);
            break;

        case 3:
            targetY += BLOCK_TO_SUB_PIXEL(0.5f);
            if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
                targetX -= BLOCK_TO_SUB_PIXEL(0.75f);
            else
                targetX += BLOCK_TO_SUB_PIXEL(0.75f);
            break;
    }

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        // Move right
        if (gCurrentSprite.SPRITE_X_SPEED_DEC == 0)
        {
            if (gCurrentSprite.xPosition > targetX - PIXEL_SIZE)
            {
                gCurrentSprite.SPRITE_X_SPEED_DEC = gCurrentSprite.SPRITE_X_SPEED_INC;
            }
            else
            {
                // Increase speed if below cap
                if (gCurrentSprite.SPRITE_X_SPEED_INC < xSpeedCap)
                    gCurrentSprite.SPRITE_X_SPEED_INC++;

                // Apply speed
                gCurrentSprite.xPosition += (gCurrentSprite.SPRITE_X_SPEED_INC >> 2);
            }
        }
        else
        {
            if (--gCurrentSprite.SPRITE_X_SPEED_DEC != 0)
            {
                gCurrentSprite.xPosition += (gCurrentSprite.SPRITE_X_SPEED_DEC >> 2);
            }
            else
            {
                gCurrentSprite.status &= ~SPRITE_STATUS_FACING_RIGHT;
                gCurrentSprite.SPRITE_X_SPEED_INC = 1;
                if (++gCurrentSprite.KIHUNTER_BUG_CHASE_STAGE > 3)
                    gCurrentSprite.KIHUNTER_BUG_CHASE_STAGE = 0;
            }
        }
    }
    else
    {
        // Move left
        if (gCurrentSprite.SPRITE_X_SPEED_DEC == 0)
        {
            if (gCurrentSprite.xPosition < targetX + PIXEL_SIZE)
            {
                gCurrentSprite.SPRITE_X_SPEED_DEC = gCurrentSprite.SPRITE_X_SPEED_INC;
            }
            else
            {
                // Increase speed if below cap
                if (gCurrentSprite.SPRITE_X_SPEED_INC < xSpeedCap)
                    gCurrentSprite.SPRITE_X_SPEED_INC++;

                // Apply speed
                gCurrentSprite.xPosition -= (gCurrentSprite.SPRITE_X_SPEED_INC >> 2);
            }
        }
        else
        {
            if (--gCurrentSprite.SPRITE_X_SPEED_DEC != 0)
            {
                gCurrentSprite.xPosition -= (gCurrentSprite.SPRITE_X_SPEED_DEC >> 2);
            }
            else
            {
                gCurrentSprite.status |= SPRITE_STATUS_FACING_RIGHT;
                gCurrentSprite.SPRITE_X_SPEED_INC = 1;
                if (++gCurrentSprite.KIHUNTER_BUG_CHASE_STAGE > 3)
                    gCurrentSprite.KIHUNTER_BUG_CHASE_STAGE = 0;
            }
        }
    }

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_DOWN)
    {
        // Move down
        if (gCurrentSprite.SPRITE_Y_SPEED_DEC == 0)
        {
            if (gCurrentSprite.yPosition > targetY - PIXEL_SIZE)
            {
                gCurrentSprite.SPRITE_Y_SPEED_DEC = gCurrentSprite.SPRITE_Y_SPEED_INC;
            }
            else
            {
                // Increase speed if below cap
                if (gCurrentSprite.SPRITE_Y_SPEED_INC < ySpeedCap)
                    gCurrentSprite.SPRITE_Y_SPEED_INC++;

                // Apply speed
                gCurrentSprite.yPosition += (gCurrentSprite.SPRITE_Y_SPEED_INC >> 2);
            }
        }
        else
        {
            if (--gCurrentSprite.SPRITE_Y_SPEED_DEC != 0)
            {
                gCurrentSprite.yPosition += (gCurrentSprite.SPRITE_Y_SPEED_DEC >> 2);
            }
            else
            {
                gCurrentSprite.status &= ~SPRITE_STATUS_FACING_DOWN;
                gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
            }
        }
    }
    else
    {
        // Move up
        if (gCurrentSprite.SPRITE_Y_SPEED_DEC == 0)
        {
            if (gCurrentSprite.yPosition < targetY + PIXEL_SIZE)
            {
                gCurrentSprite.SPRITE_Y_SPEED_DEC = gCurrentSprite.SPRITE_Y_SPEED_INC;
            }
            else
            {
                // Increase speed if below cap
                if (gCurrentSprite.SPRITE_Y_SPEED_INC < ySpeedCap)
                    gCurrentSprite.SPRITE_Y_SPEED_INC++;

                // Apply speed
                gCurrentSprite.yPosition -= (gCurrentSprite.SPRITE_Y_SPEED_INC >> 2);
            }
        }
        else
        {
            if (--gCurrentSprite.SPRITE_Y_SPEED_DEC != 0)
            {
                gCurrentSprite.yPosition -= (gCurrentSprite.SPRITE_Y_SPEED_DEC >> 2);
            }
            else
            {
                gCurrentSprite.status |= SPRITE_STATUS_FACING_DOWN;
                gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
            }
        }
    }
}

void KihunterGround(void)
{
    if (SPRITE_GET_ISFT(gCurrentSprite) == 4)
        SoundPlayNotAlreadyPlaying(SOUND_KIHUNTER_HURT);

    if (gCurrentSprite.freezeTimer > 0)
    {
        SpriteUtilUpdateFreezeTimer();
        return;
    }

    if (gCurrentSprite.pose < SPRITE_POSE_TURNING_INTO_X && SPRITE_GET_ISFT(gCurrentSprite) > 0 &&
        gCurrentSprite.status & SPRITE_STATUS_ONSCREEN)
        gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            KihunterGroundInit();
            break;

        case 1:
            KihunterGroundJumpWarningInit();

        case 2:
            KihunterGroundJumpWarning();
            break;

        case 0x18:
            KihunterGroundJumping();
            break;

        case 0x1a:
            KihunterGroundLanding();
            break;

        case 8:
            KihunterGroundIdle();
            break;

        case 4:
            KihunterGroundTurningAround();
            break;

        case 5:
            KihunterGroundTurningAroundSecondPart();
            break;

        case 0x2a:
            KihunterGroundSpitting();
            break;

        case SPRITE_POSE_FALLING:
            KihunterGroundFalling();
            break;

        case SPRITE_POSE_DYING_INIT:
            SpriteDyingInit();

        case SPRITE_POSE_DYING:
            SpriteDying();
            break;

        case SPRITE_POSE_SPAWNING_FROM_X_INIT:
            KihunterGroundInit();

        case SPRITE_POSE_SPAWNING_FROM_X:
            SpriteSpawningFromX();
            break;

        case SPRITE_POSE_TURNING_INTO_X:
            KihunterTurningIntoX();
            XParasiteInit();
            break;
    }
}

void KihunterFlying(void)
{
    if (SPRITE_GET_ISFT(gCurrentSprite) == 4)
        SoundPlayNotAlreadyPlaying(SOUND_KIHUNTER_HURT);

    if (gCurrentSprite.freezeTimer > 0)
    {
        SpriteUtilUpdateFreezeTimer();
        SpriteUtilUpdateSecondarySpriteFreezeTimerOfCurrent(SSPRITE_KIHUNTER_WINGS, gCurrentSprite.primarySpriteRamSlot);
        return;
    }

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            KihunterFlyingInit();
            break;

        case SPRITE_POSE_IDLE_INIT:
            KihunterFlyingIdleInit();

        case SPRITE_POSE_IDLE:
            KihunterFlyingIdle();
            break;

        case 3:
            KihunterFlyingTurningAroundInit();

        case 4:
            KihunterTurningAround();
            break;

        case 5:
            KihunterFlyingTurningAroundSecondPart();
            break;

        case 0x29:
            KihunterFlyingSwoopingDownInit();

        case 0x2a:
            KihunterFlyingSwoopingDown();
            break;

        case 0x2b:
            KihunterFlyingSwoopingAcrossInit();

        case 0x2c:
            KihunterFlyingSwoopingAcross();
            break;

        case 0x2d:
            KihunterFlyingAfterSwoopingInit();

        case 0x2e:
            KihunterFlyingAfterSwooping();
            break;

        case SPRITE_POSE_DYING_INIT:
            SpriteUtilUnfreezeSecondarySprites(SSPRITE_KIHUNTER_WINGS, gCurrentSprite.primarySpriteRamSlot);
            SpriteDyingInit();

        case SPRITE_POSE_DYING:
            SpriteDying();
            break;

        case SPRITE_POSE_SPAWNING_FROM_X_INIT:
            KihunterFlyingInit();

        case SPRITE_POSE_SPAWNING_FROM_X:
            SpriteSpawningFromX();
            break;

        case SPRITE_POSE_TURNING_INTO_X:
            KihunterTurningIntoX();
            XParasiteInit();
            break;
    }

    if (gCurrentSprite.pose < SPRITE_POSE_DYING_INIT && gCurrentSprite.health <= KIHUNTER_LOSE_WINGS_HEALTH_THRESHOLD)
    {
        gCurrentSprite.spriteId = PSPRITE_KIHUNTER_GROUND;
        gCurrentSprite.pose = SPRITE_POSE_UNINITIALIZED;
    }
}

void KihunterWings(void)
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

        case 0x38:
            KihunterWingsFalling();
            break;

        case 0x3a:
            KihunterWingsDisappearing();
            break;

        case SPRITE_POSE_UNINITIALIZED:
            KihunterWingsInit();

        default:
            KihunterWingsIdle();
            break;
    }
}

void KihunterSpit(void)
{
    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            KihunterSpitInit();

        case SPRITE_POSE_IDLE:
            KihunterSpitMoving();
            break;

        case SPRITE_POSE_EXPLODING:
            KihunterSpitExploding();
            break;

        default:
            KihunterSpitExplodingInit();
            break;
    }
}

void KihunterHive(void)
{
    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            KihunterHiveInit();
            break;

        case SPRITE_POSE_SPAWNING_FROM_X_INIT:
            KihunterHiveSpawnKihunter();
            break;

        case SPRITE_POSE_SPAWNING_FROM_X:
            KihunterHiveSpawnCooldown();
            break;
    }

    SpriteUtilUpdateHiveDeathExplosions(gCurrentSprite.yPosition, gCurrentSprite.xPosition);
}

void KihunterBug(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            KihunterBugInit();

        case SPRITE_POSE_IDLE:
            KihunterBugIdle();
            break;

        case 0x17:
            KihunterBugChasingSamusInit();

        case 0x18:
            KihunterBugChasingSamus();
            break;
    }
}
