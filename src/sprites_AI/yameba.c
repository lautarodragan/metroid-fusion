#include "sprites_AI/yameba.h"
#include "globals.h"
#include "macros.h"
#include "gba.h"

#include "data/sprites/yameba.h"
#include "data/sprites/x_parasite.h"
#include "data/samus_data.h"
#include "data/sprite_data.h"

#include "constants/samus.h"
#include "constants/sprite.h"
#include "constants/clipdata.h"

#include "structs/samus.h"
#include "structs/sprite.h"

#define YAMEBA_SIZE work0 // 0 (small, can absorb X) to 3, increased when spawning from X
#define YAMEBA_X_MOVEMENT_IDX work3 // Idle
#define YAMEBA_Y_MOVEMENT_IDX work4 // Idle
#define YAMEBA_MOVEMENT_STAGE workX // Chasing, incremented (mod 4) when changing X direction, offsets the target

/**
 * @brief 20578 | a4 | Handles a yameba turning into an X
 * 
 */
void YamebaTurningIntoX(void)
{
    if (gCurrentSprite.status & SPRITE_STATUS_ROTATION_SCALING_SINGLE)
        gCurrentSprite.status &= ~SPRITE_STATUS_ROTATION_SCALING_SINGLE;

    switch (gCurrentSprite.YAMEBA_SIZE)
    {
        case 2:
            SpriteSpawnNewXParasite(PSPRITE_X_PARASITE, gCurrentSprite.spriteId, 0, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.spritesetSlotAndProperties, gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition, 0);
            break;

        case 3:
            SpriteSpawnNewXParasite(PSPRITE_X_PARASITE, gCurrentSprite.spriteId, 0, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.spritesetSlotAndProperties, gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition + BLOCK_SIZE, 0);

            SpriteSpawnNewXParasite(PSPRITE_X_PARASITE, gCurrentSprite.spriteId, 0, gCurrentSprite.primarySpriteRamSlot,
                gCurrentSprite.spritesetSlotAndProperties, gCurrentSprite.yPosition + BLOCK_SIZE, gCurrentSprite.xPosition - BLOCK_SIZE, 0);
    }
}

/**
 * @brief 2061c | 1d8 | Initializes a yameba
 * 
 */
void YamebaInit(void)
{
    u8 properties;

    if (gCurrentSprite.pose == SPRITE_POSE_UNINITIALIZED)
    {
        properties = gCurrentSprite.spritesetSlotAndProperties - 0x20;
        if (properties < 0x30)
            gCurrentSprite.YAMEBA_SIZE = 1;
        else
            gCurrentSprite.YAMEBA_SIZE = 0;

        gCurrentSprite.pose = SPRITE_POSE_IDLE_INIT;
        gCurrentSprite.yPosition -= HALF_BLOCK_SIZE;
    }
    else
    {
        gCurrentSprite.YAMEBA_SIZE++;
        gCurrentSprite.pose = SPRITE_POSE_SPAWNING_FROM_X;
        gCurrentSprite.SPRITE_X_SPAWN_MOSAIC_IDX = X_PARASITE_MOSAIC_MAX_INDEX;
    }

    if (gCurrentSprite.YAMEBA_SIZE == 0)
    {
        gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
        gCurrentSprite.drawOrder = 12;
        gCurrentSprite.samusCollision = SSC_NONE;
        gCurrentSprite.pOam = sYamebaOam_Small;
    }
    else
    {
        gCurrentSprite.drawOrder = 4;
        gCurrentSprite.samusCollision = SSC_YAMEBA;
        gCurrentSprite.pOam = sYamebaOam_Big;
    }

    gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    gCurrentSprite.rotation = 0;

    switch (gCurrentSprite.YAMEBA_SIZE)
    {
        case 0:
            gCurrentSprite.properties |= SP_CAN_ABSORB_X;
            gCurrentSprite.status |= SPRITE_STATUS_ROTATION_SCALING_SINGLE;

            gCurrentSprite.scaling = Q_8_8(.625f);

            gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(.5f);
            gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.5f);
            gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(.5f);

            gCurrentSprite.hitboxTop = -(QUARTER_BLOCK_SIZE + EIGHTH_BLOCK_SIZE);
            gCurrentSprite.hitboxBottom = (QUARTER_BLOCK_SIZE + EIGHTH_BLOCK_SIZE);
            gCurrentSprite.hitboxLeft = -(QUARTER_BLOCK_SIZE + EIGHTH_BLOCK_SIZE);
            gCurrentSprite.hitboxRight = (QUARTER_BLOCK_SIZE + EIGHTH_BLOCK_SIZE);
            break;

        case 1:
            gCurrentSprite.properties |= SP_CAN_ABSORB_X;
            gCurrentSprite.status |= SPRITE_STATUS_ROTATION_SCALING_SINGLE;

            gCurrentSprite.scaling = Q_8_8(.5f);

            gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(.5f);
            gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.5f);
            gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(.5f);

            gCurrentSprite.hitboxTop = -(QUARTER_BLOCK_SIZE + EIGHTH_BLOCK_SIZE);
            gCurrentSprite.hitboxBottom = (QUARTER_BLOCK_SIZE + EIGHTH_BLOCK_SIZE);
            gCurrentSprite.hitboxLeft = -(QUARTER_BLOCK_SIZE + EIGHTH_BLOCK_SIZE);
            gCurrentSprite.hitboxRight = (QUARTER_BLOCK_SIZE + EIGHTH_BLOCK_SIZE);
            break;

        case 2:
            gCurrentSprite.properties |= SP_CAN_ABSORB_X;
            gCurrentSprite.status |= SPRITE_STATUS_ROTATION_SCALING_SINGLE;

            gCurrentSprite.scaling = Q_8_8(1.f);

            gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1);
            gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1);
            gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);

            gCurrentSprite.hitboxTop = -HALF_BLOCK_SIZE;
            gCurrentSprite.hitboxBottom = HALF_BLOCK_SIZE;
            gCurrentSprite.hitboxLeft = -HALF_BLOCK_SIZE;
            gCurrentSprite.hitboxRight = HALF_BLOCK_SIZE;

            gCurrentSprite.health *= 3;
            break;

        default:
            gCurrentSprite.properties &= ~SP_CAN_ABSORB_X;
            gCurrentSprite.status |= (SPRITE_STATUS_ROTATION_SCALING_SINGLE | SPRITE_STATUS_DOUBLE_SIZE);

            gCurrentSprite.scaling = Q_8_8(1.999f);

            gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(2);
            gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(2);
            gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(2);

            gCurrentSprite.hitboxTop = -HALF_BLOCK_SIZE;
            gCurrentSprite.hitboxBottom = BLOCK_SIZE * 2 + EIGHTH_BLOCK_SIZE;
            gCurrentSprite.hitboxLeft = -HALF_BLOCK_SIZE;
            gCurrentSprite.hitboxRight = BLOCK_SIZE * 2 + EIGHTH_BLOCK_SIZE;

            gCurrentSprite.health *= 9;
    }

    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;

    if (gCurrentSprite.properties & SP_CAN_ABSORB_X)
        gCurrentSprite.numberOfXToForm = 1;
}

/**
 * @brief 207f4 | 48 | Initializes a yameba to be idle
 * 
 */
void YamebaIdleInit(void)
{
    u8 rng;

    gCurrentSprite.pose = SPRITE_POSE_IDLE;

    if (gCurrentSprite.YAMEBA_SIZE == 0)
    {
        rng = gSpriteRandomNumber * 4;

        gCurrentSprite.YAMEBA_X_MOVEMENT_IDX = rng;
        gCurrentSprite.YAMEBA_Y_MOVEMENT_IDX = rng;
    }
    else
    {
        gCurrentSprite.bgPriority = gIoRegisters.bg1Cnt & 3; // TODO macro
    }
}

/**
 * @brief 2083c | 88 | Handles a yameba being idle
 * 
 */
void YamebaIdle(void)
{
    u8 offset;
    s16 yMovement;
    s16 xMovement;

    if (gCurrentSprite.YAMEBA_SIZE == 0)
    {
        offset = gCurrentSprite.YAMEBA_Y_MOVEMENT_IDX;
        yMovement = sYamebaIdleYMovement[offset];

        if (yMovement == SHORT_MAX)
        {
            yMovement = sYamebaIdleYMovement[0];
            offset = 0;
        }

        offset++;
        gCurrentSprite.YAMEBA_Y_MOVEMENT_IDX = offset;
        gCurrentSprite.yPosition += yMovement;

        offset = gCurrentSprite.YAMEBA_X_MOVEMENT_IDX;
        xMovement = sYamebaIdleXMovement[offset];

        if (xMovement == SHORT_MAX)
        {
            xMovement = sYamebaIdleXMovement[0];
            offset = 0;
        }

        offset++;
        gCurrentSprite.YAMEBA_X_MOVEMENT_IDX = offset;
        gCurrentSprite.xPosition += xMovement;
    }
    else
    {
        if (SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_SIZE * 10, BLOCK_SIZE * 10))
            gCurrentSprite.pose = 0x17;
    }
}

/**
 * @brief 208c4 | 60 | Initializes a yameba to be chasing samus
 * 
 */
void YamebaChasingSamusInit(void)
{
    gCurrentSprite.SPRITE_X_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_X_SPEED_INC = 1;
    gCurrentSprite.SPRITE_Y_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_Y_SPEED_INC = 1;

    gCurrentSprite.YAMEBA_MOVEMENT_STAGE = 0;
    gCurrentSprite.pose = 0x18;

    SpriteUtilMakeSpriteFaceSamusDirection();

    if (gCurrentSprite.yPosition > gSamusData.yPosition + gSamusData.drawDistanceTop)
        gCurrentSprite.status &= ~SPRITE_STATUS_SAMUS_DETECTED;
    else
        gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
}

/**
 * @brief 20924 | 300 | Handles a yameba chasing samus
 * 
 */
void YamebaChasingSamus(void)
{
    u16 yPosition;
    u16 xPosition;
    u16 otherY;
    u16 otherX;
    u16 size;
    u8 velocityCap;
    u8 i;

    yPosition = gCurrentSprite.yPosition;
    xPosition = gCurrentSprite.xPosition;
    size = QUARTER_BLOCK_SIZE;

    for (i = gCurrentSprite.primarySpriteRamSlot + 1; i < MAX_AMOUNT_OF_SPRITES; i++)
    {
        if (!(gSpriteData[i].status & SPRITE_STATUS_EXISTS))
            continue;

        if (gSpriteData[i].properties & SP_SECONDARY_SPRITE)
            continue;

        if (gSpriteData[i].spriteId != PSPRITE_YAMEBA)
            continue;

        if (gSpriteData[i].YAMEBA_SIZE == 0)
            continue;

        otherY = gSpriteData[i].yPosition;
        otherX = gSpriteData[i].xPosition;

        if (yPosition + size <= otherY - size)
            continue;

        if (yPosition - size >= otherY + size)
            continue;

        if (xPosition + size <= otherX - size)
            continue;

        if (xPosition - size >= otherX + size)
            continue;

        if (gSpriteData[i].freezeTimer == 0)
        {
            if (yPosition > otherY)
                gSpriteData[i].yPosition -= PIXEL_SIZE;
            else
                gSpriteData[i].yPosition += PIXEL_SIZE;

            if (xPosition > otherX)
                gSpriteData[i].xPosition -= PIXEL_SIZE;
            else
                gSpriteData[i].xPosition += PIXEL_SIZE;

            gSpriteData[i].status ^= SPRITE_STATUS_FACING_RIGHT;
            gSpriteData[i].status ^= SPRITE_STATUS_SAMUS_DETECTED;
        }

        break;
    }

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_COLLIDING)
    {
        gCurrentSprite.SPRITE_X_SPEED_DEC = 0;
        gCurrentSprite.SPRITE_X_SPEED_INC = 1;
        gCurrentSprite.SPRITE_Y_SPEED_DEC = 0;
        gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
        return;
    }

    if (gCurrentSprite.YAMEBA_SIZE == 3)
    {
        otherY = gSamusData.yPosition - (BLOCK_SIZE * 2 + EIGHTH_BLOCK_SIZE);
        otherX = gSamusData.xPosition - BLOCK_SIZE;
    }
    else
    {
        otherY = gSamusData.yPosition - (BLOCK_SIZE + EIGHTH_BLOCK_SIZE);
        otherX = gSamusData.xPosition;
    }

    velocityCap = HALF_BLOCK_SIZE - PIXEL_SIZE / 2;

    if (gCurrentSprite.status & SPRITE_STATUS_FACING_RIGHT)
    {
        if (gCurrentSprite.SPRITE_X_SPEED_DEC == 0)
        {
            if (gCurrentSprite.xPosition > otherX - PIXEL_SIZE)
            {
                gCurrentSprite.SPRITE_X_SPEED_DEC = gCurrentSprite.SPRITE_X_SPEED_INC;
            }
            else
            {
                if (gCurrentSprite.SPRITE_X_SPEED_INC < velocityCap)
                    gCurrentSprite.SPRITE_X_SPEED_INC++;

                gCurrentSprite.xPosition += DIV_SHIFT(gCurrentSprite.SPRITE_X_SPEED_INC, 4);
            }
        }
        else
        {
            if (--gCurrentSprite.SPRITE_X_SPEED_DEC != 0)
            {
                gCurrentSprite.xPosition += DIV_SHIFT(gCurrentSprite.SPRITE_X_SPEED_DEC, 4);
            }
            else
            {
                gCurrentSprite.status &= ~SPRITE_STATUS_FACING_RIGHT;
                gCurrentSprite.SPRITE_X_SPEED_INC = 1;
                gCurrentSprite.YAMEBA_MOVEMENT_STAGE++;

                if (gCurrentSprite.YAMEBA_MOVEMENT_STAGE > 3)
                    gCurrentSprite.YAMEBA_MOVEMENT_STAGE = 0;
            }
        }
    }
    else
    {
        if (gCurrentSprite.SPRITE_X_SPEED_DEC == 0)
        {
            if (gCurrentSprite.xPosition < otherX + PIXEL_SIZE)
            {
                gCurrentSprite.SPRITE_X_SPEED_DEC = gCurrentSprite.SPRITE_X_SPEED_INC;
            }
            else
            {
                if (gCurrentSprite.SPRITE_X_SPEED_INC < velocityCap)
                    gCurrentSprite.SPRITE_X_SPEED_INC++;

                gCurrentSprite.xPosition -= DIV_SHIFT(gCurrentSprite.SPRITE_X_SPEED_INC, 4);
            }
        }
        else
        {
            if (--gCurrentSprite.SPRITE_X_SPEED_DEC != 0)
            {
                gCurrentSprite.xPosition -= DIV_SHIFT(gCurrentSprite.SPRITE_X_SPEED_DEC, 4);
            }
            else
            {
                gCurrentSprite.status |= SPRITE_STATUS_FACING_RIGHT;
                gCurrentSprite.SPRITE_X_SPEED_INC = 1;
                gCurrentSprite.YAMEBA_MOVEMENT_STAGE++;

                if (gCurrentSprite.YAMEBA_MOVEMENT_STAGE > 3)
                    gCurrentSprite.YAMEBA_MOVEMENT_STAGE = 0;
            }
        }
    }

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_DETECTED)
    {
        if (gCurrentSprite.SPRITE_Y_SPEED_DEC == 0)
        {
            if (gCurrentSprite.yPosition > otherY - PIXEL_SIZE)
            {
                gCurrentSprite.SPRITE_Y_SPEED_DEC = gCurrentSprite.SPRITE_Y_SPEED_INC;
            }
            else
            {
                if (gCurrentSprite.SPRITE_Y_SPEED_INC < velocityCap)
                    gCurrentSprite.SPRITE_Y_SPEED_INC++;

                gCurrentSprite.yPosition += DIV_SHIFT(gCurrentSprite.SPRITE_Y_SPEED_INC, 4);
            }
        }
        else
        {
            if (--gCurrentSprite.SPRITE_Y_SPEED_DEC != 0)
            {
                gCurrentSprite.yPosition += DIV_SHIFT(gCurrentSprite.SPRITE_Y_SPEED_DEC, 4);
            }
            else
            {
                gCurrentSprite.status &= ~SPRITE_STATUS_SAMUS_DETECTED;
                gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
            }
        }
    }
    else
    {
        if (gCurrentSprite.SPRITE_Y_SPEED_DEC == 0)
        {
            if (gCurrentSprite.yPosition < otherY + PIXEL_SIZE)
            {
                gCurrentSprite.SPRITE_Y_SPEED_DEC = gCurrentSprite.SPRITE_Y_SPEED_INC;
            }
            else
            {
                if (gCurrentSprite.SPRITE_Y_SPEED_INC < velocityCap)
                    gCurrentSprite.SPRITE_Y_SPEED_INC++;

                gCurrentSprite.yPosition -= DIV_SHIFT(gCurrentSprite.SPRITE_Y_SPEED_INC, 4);
            }
        }
        else
        {
            if (--gCurrentSprite.SPRITE_Y_SPEED_DEC != 0)
            {
                gCurrentSprite.yPosition -= DIV_SHIFT(gCurrentSprite.SPRITE_Y_SPEED_DEC, 4);
            }
            else
            {
                gCurrentSprite.status |= SPRITE_STATUS_SAMUS_DETECTED;
                gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
            }
        }
    }
}

/**
 * @brief 20c24 | 218 | Yameba AI
 * 
 */
void Yameba(void)
{
    if (SPRITE_GET_ISFT(gCurrentSprite) == 0x4)
        SoundPlayNotAlreadyPlaying(0x15F);

    if (gCurrentSprite.freezeTimer != 0)
    {
        SpriteUtilUpdateFreezeTimer();
        return;
    }

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            YamebaInit();
            break;

        case SPRITE_POSE_IDLE_INIT:
            YamebaIdleInit();
            break;

        case SPRITE_POSE_IDLE:
            YamebaIdle();
            break;

        case 0x17:
            YamebaChasingSamusInit();

        case 0x18:
            YamebaChasingSamus();
            break;

        case SPRITE_POSE_DYING_INIT:
            SpriteDyingInit();

        case SPRITE_POSE_DYING:
            SpriteDying();
            break;

        case SPRITE_POSE_SPAWNING_FROM_X_INIT:
            YamebaInit();

        case SPRITE_POSE_SPAWNING_FROM_X:
            SpriteSpawningFromX();
            break;

        case SPRITE_POSE_TURNING_INTO_X:
            YamebaTurningIntoX();
            XParasiteInit();
    }

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_COLLIDING)
        gCurrentSprite.status &= ~SPRITE_STATUS_SAMUS_COLLIDING;
}
