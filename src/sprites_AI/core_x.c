#include "sprites_AI/core_x.h"
#include "globals.h"
#include "macros.h"

#include "data/sprite_data.h"
#include "data/sprites/core_x.h"
#include "data/sprites/message_banner.h"
#include "data/sprites/x_parasite.h"

#include "constants/audio.h"
#include "constants/event.h"
#include "constants/particle.h"
#include "constants/samus.h"

#include "structs/demo.h"
#include "structs/samus.h"
#include "structs/sprite.h"

#define CORE_X_POSE_MOVING_TO_SPAWN_POINT 0x18
#define CORE_X_POSE_SPAWINING_BOSS 0x1a
#define CORE_X_POSE_MOVING_INIT 0x1b
#define CORE_X_POSE_MOVING 0x1c
#define CORE_X_POSE_MOVING_TO_TARGET_INIT 0x5c
#define CORE_X_POSE_MOVING_TO_TARGET 0x5d
#define CORE_X_POSE_WAITING_AT_TARGET 0x5e
#define CORE_X_POSE_GETTING_ABSORBED 0x5f

#define CORE_X_HIT_TIMER work0 // Flashing and immune after a hit, set by the shell
#define CORE_X_TIMER work1 // Also the mosaic index and the graphics part loaded while spawning the boss
#define CORE_X_X_MOVEMENT_IDX work3 // Floating
#define CORE_X_Y_MOVEMENT_IDX work4 // Floating
#define CORE_X_SPAWN_Y workY
#define CORE_X_SPAWN_X workX
#define CORE_X_ABSORB_DELAY workY // Waiting at the target, before it can be absorbed
#define CORE_X_MOSAIC_IDX workY // Transforming into the ability, also the graphics part loaded

/**
 * @brief Makes the X parasites around a core-X flee
 *
 */
void CoreXMakeXParasitesFlee(void)
{
    u8 i;

    for (i = 0; i < MAX_AMOUNT_OF_SPRITES; i++)
    {
        if (gSpriteData[i].status & SPRITE_STATUS_EXISTS && !(gSpriteData[i].properties & SP_SECONDARY_SPRITE) &&
            gSpriteData[i].spriteId == PSPRITE_X_PARASITE_CORE_X_OR_PARASITE &&
            gSpriteData[i].pose == X_PARASITE_POSE_FLYING)
        {
            gSpriteData[i].workY = 0;
            gSpriteData[i].pose = X_PARASITE_POSE_FLYING_AWAY;
        }
    }
}

/**
 * @brief Handles a core-X transforming from a boss
 *
 */
void CoreXAbilityTransfromation(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (--gCurrentSprite.CORE_X_MOSAIC_IDX != 0)
    {
        gWrittenToMosaic_H = sXParasiteMosaicValues[gCurrentSprite.CORE_X_MOSAIC_IDX];
    }
    else
    {
        gCurrentSprite.pose = CORE_X_POSE_MOVING_INIT;
        gCurrentSprite.status &= ~SPRITE_STATUS_MOSAIC;
        gCurrentSprite.bgPriority = gIoRegisters.bg1Cnt & 3;
    }

    if (gCurrentSprite.CORE_X_MOSAIC_IDX < sizeof(sMessageBannerGfx) / 512)
        SpriteLoadGfx(PSPRITE_MESSAGE_BANNER, 6, gCurrentSprite.CORE_X_MOSAIC_IDX);
    else if (gCurrentSprite.CORE_X_MOSAIC_IDX == sizeof(sMessageBannerGfx) / 512)
        SpriteLoadPal(PSPRITE_MESSAGE_BANNER, 6, ARRAY_SIZE(sMessageBannerPal) / 16);
}

/**
 * @brief Initializes a core-X sprite
 *
 */
void CoreXAbilityInit(void)
{
    u8 tmp;
    u8 bossSpriteId;
    u8 secondarySpriteId;

    tmp = FALSE;
    bossSpriteId = PSPRITE_ARACHNUS;
    secondarySpriteId = SSPRITE_CORE_X_SHELL_MORPH_BALL;

    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (gCurrentSprite.pose == SPRITE_POSE_SPAWNING_FROM_X_INIT)
    {
        switch (gCurrentSprite.spriteId)
        {
            case PSPRITE_MORPH_BALL_ABILITY:
                gCurrentSprite.yPosition -= BLOCK_SIZE * 2;
                secondarySpriteId = SSPRITE_CORE_X_SHELL_MORPH_BALL;
                break;

            case PSPRITE_HIGH_JUMP_ABILITY:
                secondarySpriteId = SSPRITE_CORE_X_SHELL_HIGH_JUMP;
                break;

            case PSPRITE_SPEEDBOOSTER_ABILITY:
                secondarySpriteId = SSPRITE_CORE_X_SHELL_SPEEDBOOSTER;
                break;

            case PSPRITE_SPACE_JUMP_ABILITY:
                secondarySpriteId = SSPRITE_CORE_X_SHELL_SPACE_JUMP;
                break;

            case PSPRITE_GRAVITY_SUIT_ABILITY:
                gCurrentSprite.yPosition -= BLOCK_SIZE * 2;
                gCurrentSprite.xPosition -= BLOCK_SIZE;
                secondarySpriteId = SSPRITE_CORE_X_SHELL_GRAVITY;
                break;

            case PSPRITE_SCREW_ATTACK_ABILITY:
                secondarySpriteId = SSPRITE_CORE_X_SHELL_SCREW_ATTACK;
                break;
        }

        gCurrentSprite.pose = SPRITE_POSE_SPAWNING_FROM_X;
        gCurrentSprite.SPRITE_X_SPAWN_MOSAIC_IDX = X_PARASITE_MOSAIC_MAX_INDEX;
        gCurrentSprite.status |= SPRITE_STATUS_MOSAIC;
        gCurrentSprite.status &= ~(SPRITE_STATUS_SAMUS_DETECTED | SPRITE_STATUS_SAMUS_COLLIDING);
    }
    else
    {
        switch (gCurrentSprite.spriteId)
        {
            case PSPRITE_MORPH_BALL_ABILITY:
                if (gEquipment.suitMiscStatus & SMF_MORPH_BALL)
                    tmp = TRUE;
                break;

            case PSPRITE_HIGH_JUMP_ABILITY:
                if (gEquipment.suitMiscStatus & SMF_HIGH_JUMP)
                    tmp = TRUE;
                bossSpriteId = PSPRITE_ZAZABI;
                secondarySpriteId = SSPRITE_CORE_X_SHELL_HIGH_JUMP;
                break;

            default:
                tmp = TRUE;
                break;
        }

        if (tmp)
        {
            gCurrentSprite.status = 0;
            return;
        }

        gBossFormationSpriteId = bossSpriteId;
        gCoreXFormationSpriteId = gCurrentSprite.spriteId;
        gCurrentSprite.CORE_X_SPAWN_Y = gCurrentSprite.yPosition;
        gCurrentSprite.CORE_X_SPAWN_X = gCurrentSprite.xPosition;
        gCurrentSprite.yPosition -= BLOCK_SIZE * 6;
        gCurrentSprite.pose = SPRITE_POSE_IDLE_INIT;
    }

    gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    gCurrentSprite.drawOrder = 6;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);
    gCurrentSprite.hitboxTop = -HALF_BLOCK_SIZE;
    gCurrentSprite.hitboxBottom = HALF_BLOCK_SIZE;
    gCurrentSprite.hitboxLeft = -HALF_BLOCK_SIZE;
    gCurrentSprite.hitboxRight = HALF_BLOCK_SIZE;
    gCurrentSprite.pOam = sCoreXAbilityOam_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.CORE_X_X_MOVEMENT_IDX = 0;
    gCurrentSprite.CORE_X_Y_MOVEMENT_IDX = 0;

    tmp = SpriteSpawnSecondary(secondarySpriteId, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);

    if (tmp == UCHAR_MAX)
    {
        gCurrentSprite.status = 0;
        return;
    }

    tmp = SpriteSpawnSecondary(SSPRITE_ABILITY_AURA, 0, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);

    if (tmp == UCHAR_MAX)
    {
        gCurrentSprite.status = 0;
        return;
    }

    tmp = SpriteSpawnSecondary(SSPRITE_ABILITY_AURA, 1, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);

    if (tmp == UCHAR_MAX)
    {
        gCurrentSprite.status = 0;
        return;
    }

    tmp = SpriteSpawnSecondary(SSPRITE_ABILITY_AURA, 2, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);

    if (tmp == UCHAR_MAX)
    {
        gCurrentSprite.status = 0;
        return;
    }
}

/**
 * @brief Initializes a core-X to be idle before spawning a boss
 *
 */
void CoreXAbilityIdleInit(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;
    gCurrentSprite.pose = SPRITE_POSE_IDLE;
    gCurrentSprite.pOam = sCoreXAbilityOam_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
}

/**
 * @brief Handles a core-X being idle before spawning a boss
 *
 */
void CoreXAbilityIdle(void)
{
    u8 offset;
    s16 movement;
    u16 xPosOnScreen;
    u8 ramSlot;

    gCurrentSprite.ignoreSamusCollisionTimer = 1;
    gCurrentSprite.status ^= SPRITE_STATUS_NOT_DRAWN;

    offset = gCurrentSprite.CORE_X_Y_MOVEMENT_IDX;
    movement = sCoreXIdleYSpeed[offset];

    if (movement == SHORT_MAX)
    {
        movement = sCoreXIdleYSpeed[0];
        offset = 0;
    }

    offset++;
    gCurrentSprite.CORE_X_Y_MOVEMENT_IDX = offset;
    gCurrentSprite.yPosition += movement;

    offset = gCurrentSprite.CORE_X_X_MOVEMENT_IDX;
    movement = sCoreXIdleXSpeed[offset];

    if (movement == SHORT_MAX)
    {
        movement = sCoreXIdleXSpeed[0];
        offset = 0;
    }

    offset++;
    gCurrentSprite.CORE_X_X_MOVEMENT_IDX = offset;
    gCurrentSprite.xPosition += movement;

    xPosOnScreen = SUB_PIXEL_TO_PIXEL_(gCurrentSprite.xPosition) - SUB_PIXEL_TO_PIXEL_(gBg1XPosition);

    if (gCurrentSprite.yPosition < gSamusData.yPosition)
    {
        if (xPosOnScreen > 20)
        {
            if (xPosOnScreen < SCREEN_SIZE_X - 20)
            {
                ramSlot = SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_FORMATION, 0, 0,
                    gCurrentSprite.primarySpriteRamSlot, SSP_X_UNABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition + 0xb4,
                    gCurrentSprite.xPosition - 0x14, 0);

                if (ramSlot != UCHAR_MAX)
                    gSpriteData[ramSlot].workY = 180;

                ramSlot = SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_FORMATION, 1, 0,
                    gCurrentSprite.primarySpriteRamSlot, SSP_X_UNABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition - 0xc8,
                    gCurrentSprite.xPosition + 0xa, 0);

                if (ramSlot != UCHAR_MAX)
                    gSpriteData[ramSlot].workY = 180;

                ramSlot = SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_FORMATION, 2, 0,
                    gCurrentSprite.primarySpriteRamSlot, SSP_X_UNABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition + 0x82,
                    gCurrentSprite.xPosition + 0x8c, 0);

                if (ramSlot != UCHAR_MAX)
                    gSpriteData[ramSlot].workY = 180;

                ramSlot = SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_FORMATION, 3, 0,
                    gCurrentSprite.primarySpriteRamSlot, SSP_X_UNABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition - 0x82,
                    gCurrentSprite.xPosition + 0x96, 0);

                if (ramSlot != UCHAR_MAX)
                    gSpriteData[ramSlot].workY = 180;

                ramSlot = SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_FORMATION, 4, 0,
                    gCurrentSprite.primarySpriteRamSlot, SSP_X_UNABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition + 0x8c,
                    gCurrentSprite.xPosition - 0xa0, 0);

                if (ramSlot != UCHAR_MAX)
                    gSpriteData[ramSlot].workY = 180;

                ramSlot = SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_FORMATION, 5, 0,
                    gCurrentSprite.primarySpriteRamSlot, SSP_X_UNABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition - 0x96,
                    gCurrentSprite.xPosition - 0x82, 0);

                if (ramSlot != UCHAR_MAX)
                    gSpriteData[ramSlot].workY = 180;

                gCurrentSprite.pose = CORE_X_POSE_MOVING_TO_SPAWN_POINT;
                gCurrentSprite.CORE_X_TIMER = 80;
                gCurrentSprite.rotation = 190;
            }
        }
    }
}

/**
 * @brief Handles a core-X moving down to a position where it will spawn a boss
 *
 */
void CoreXAbilityMovingToSpawnPoint(void)
{
    u8 offset;
    s16 movement;

    gCurrentSprite.ignoreSamusCollisionTimer = 1;
    gCurrentSprite.status ^= SPRITE_STATUS_NOT_DRAWN;

    offset = gCurrentSprite.CORE_X_Y_MOVEMENT_IDX;
    movement = sCoreXIdleYSpeed[offset];

    if (movement == SHORT_MAX)
    {
        movement = sCoreXIdleYSpeed[0];
        offset = 0;
    }

    offset++;
    gCurrentSprite.CORE_X_Y_MOVEMENT_IDX = offset;
    gCurrentSprite.yPosition += movement;

    offset = gCurrentSprite.CORE_X_X_MOVEMENT_IDX;
    movement = sCoreXIdleXSpeed[offset];

    if (movement == SHORT_MAX)
    {
        movement = sCoreXIdleXSpeed[0];
        offset = 0;
    }

    offset++;
    gCurrentSprite.CORE_X_X_MOVEMENT_IDX = offset;
    gCurrentSprite.xPosition += movement;

    if (gBossFormationSpriteId == PSPRITE_ZAZABI)
    {
        if (gCurrentSprite.yPosition >= gCurrentSprite.CORE_X_SPAWN_Y - PIXEL_TO_SUB_PIXEL(0x50))
        {
            gCurrentSprite.yPosition = gCurrentSprite.CORE_X_SPAWN_Y - PIXEL_TO_SUB_PIXEL(0x50);

            if (gCurrentSprite.rotation == 0)
            {
                gCurrentSprite.pose = CORE_X_POSE_SPAWINING_BOSS;
                gCurrentSprite.status |= SPRITE_STATUS_MOSAIC;
                gCurrentSprite.CORE_X_TIMER = X_PARASITE_MOSAIC_MAX_INDEX;
                gWrittenToMosaic_H = sXParasiteMosaicValues[gCurrentSprite.CORE_X_TIMER];
                PlayMusic(MUSIC_ZAZABI_BATTLE, 7);
            }
        }
        else
        {
            gCurrentSprite.yPosition += PIXEL_SIZE / 4;
        }
    }
    else
    {
        if (gCurrentSprite.yPosition >= gCurrentSprite.CORE_X_SPAWN_Y - PIXEL_TO_SUB_PIXEL(0x19))
        {
            gCurrentSprite.yPosition = gCurrentSprite.CORE_X_SPAWN_Y - PIXEL_TO_SUB_PIXEL(0x19);

            if (gCurrentSprite.rotation == 0)
            {
                gCurrentSprite.pose = CORE_X_POSE_SPAWINING_BOSS;
                gCurrentSprite.status |= SPRITE_STATUS_MOSAIC;
                gCurrentSprite.CORE_X_TIMER = X_PARASITE_MOSAIC_MAX_INDEX;
                gWrittenToMosaic_H = sXParasiteMosaicValues[gCurrentSprite.CORE_X_TIMER];

                if (gDemoState == 0)
                    PlayMusic(MUSIC_ARACHNUS_BATTLE, 7);
            }
        }
        else
        {
            gCurrentSprite.yPosition += PIXEL_SIZE / 4;
        }
    }

    if (gCurrentSprite.rotation != 0)
        gCurrentSprite.rotation--;

    if (gCurrentSprite.CORE_X_TIMER == 80)
        SoundPlay(SOUND_CORE_X_MOVING_TO_SPAWN_POINT);

    if (--gCurrentSprite.CORE_X_TIMER == 0)
        gCurrentSprite.CORE_X_TIMER = 80;
}

/**
 * @brief Handles a core-X spawning a boss
 *
 */
void CoreXAbilitySpawningBoss(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;
    gCurrentSprite.status ^= SPRITE_STATUS_NOT_DRAWN;

    if (--gCurrentSprite.CORE_X_TIMER != 0)
    {
        gWrittenToMosaic_H = sXParasiteMosaicValues[gCurrentSprite.CORE_X_TIMER];
    }
    else
    {
        gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
        gCurrentSprite.pose = SPRITE_POSE_SPAWNING_FROM_X_INIT;
        gCurrentSprite.spriteId = gBossFormationSpriteId;
    }

    if (gCurrentSprite.CORE_X_TIMER < 8 * 4)
        SpriteLoadGfx(gBossFormationSpriteId, 0, gCurrentSprite.CORE_X_TIMER); // Loads 8 graphics rows
    else if (gCurrentSprite.CORE_X_TIMER == 8 * 4)
        SpriteLoadPal(gBossFormationSpriteId, 0, 4); // Only loads the first 4 palette rows
}

/**
 * @brief Initializes a core-X moving and spawns 6 X parasites around it
 *
 */
void CoreXAbilityMovingInit(void)
{
    SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_OR_PARASITE, 0, 0, gCurrentSprite.primarySpriteRamSlot,
        SSP_X_ABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition + 0x64, gCurrentSprite.xPosition, 0);
    SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_OR_PARASITE, 0, 0, gCurrentSprite.primarySpriteRamSlot,
        SSP_X_ABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition - 0x64, gCurrentSprite.xPosition, 0);
    SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_OR_PARASITE, 0, 0, gCurrentSprite.primarySpriteRamSlot,
        SSP_X_ABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition + 0x22, gCurrentSprite.xPosition + 0x64, 0);
    SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_OR_PARASITE, 0, 0, gCurrentSprite.primarySpriteRamSlot,
        SSP_X_ABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition + 0x22, gCurrentSprite.xPosition - 0x64, 0);
    SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_OR_PARASITE, 0, 0, gCurrentSprite.primarySpriteRamSlot,
        SSP_X_ABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition - 0x22, gCurrentSprite.xPosition + 0x64, 0);
    SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_OR_PARASITE, 0, 0, gCurrentSprite.primarySpriteRamSlot,
        SSP_X_ABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition - 0x22, gCurrentSprite.xPosition - 0x64, 0);

    gCurrentSprite.pose = CORE_X_POSE_MOVING;
    gCurrentSprite.SPRITE_X_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_X_SPEED_INC = 1;
    gCurrentSprite.SPRITE_Y_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
    gCurrentSprite.CORE_X_HIT_TIMER = 0;
}

/**
 * @brief Handles a core-X moving towards Samus
 *
 */
void CoreXAbilityMoving(void)
{
    XParasiteMoveWithSound((u16)(gSamusData.yPosition - PIXEL_TO_SUB_PIXEL(0x12)), gSamusData.xPosition,
        PIXEL_TO_SUB_PIXEL(1.75f) * 4, PIXEL_TO_SUB_PIXEL(2.5f) * 4, LOG2(4), SOUND_CORE_X_MOVING);
}

/**
 * @brief Initializes a core-X moving to resting position after its shell breaks
 *
 */
void CoreXAbilityMovingToTargetInit(void)
{
    gCurrentSprite.pose = 0x5d;
    gCurrentSprite.samusCollision = SSC_CORE_X_ABILITY;
    gCurrentSprite.health = 0;
    gCurrentSprite.SPRITE_X_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_X_SPEED_INC = 1;
    gCurrentSprite.SPRITE_Y_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    PlayMusic(MUSIC_BOSS_TENSION, 6);
}

/**
 * @brief Handles a core-X moving to resting position after its shell breaks
 *
 */
void CoreXAbilityMovingToTarget(void)
{
    CoreXMakeXParasitesFlee();

    if (MOD_AND(gFrameCounter8Bit, 4) == 0)
        gCurrentSprite.status ^= SPRITE_STATUS_NOT_DRAWN;

    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    XParasiteMoveWithSound(gAbilityRestingYPosition, gAbilityRestingXPosition, PIXEL_SIZE * 4,
        PIXEL_TO_SUB_PIXEL(1.5f) * 4, LOG2(4), SOUND_X_PARASITE_MOVING);

    if (gCurrentSprite.yPosition < gAbilityRestingYPosition + 6 &&
        gCurrentSprite.yPosition > gAbilityRestingYPosition - 6)
    {
        if (gCurrentSprite.xPosition < gAbilityRestingXPosition + 6 &&
            gCurrentSprite.xPosition > gAbilityRestingXPosition - 6)
        {
            gCurrentSprite.pose = 0x5e;
            gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
            gCurrentSprite.CORE_X_X_MOVEMENT_IDX = 0;
            gCurrentSprite.CORE_X_Y_MOVEMENT_IDX = 0;
        }
    }
}

/**
 * @brief Handles a core-X waiting to get absorbed by Samus
 *
 */
void CoreXAbilityWaitingAtTarget(void)
{
    u8 offset;
    s16 movement;

    offset = gCurrentSprite.CORE_X_Y_MOVEMENT_IDX;
    movement = sCoreXIdleYSpeed[offset];

    if (movement == SHORT_MAX)
    {
        movement = sCoreXIdleYSpeed[0];
        offset = 0;
    }

    offset++;
    gCurrentSprite.CORE_X_Y_MOVEMENT_IDX = offset;
    gCurrentSprite.yPosition += movement;

    offset = gCurrentSprite.CORE_X_X_MOVEMENT_IDX;
    movement = sCoreXIdleXSpeed[offset];

    if (movement == SHORT_MAX)
    {
        movement = sCoreXIdleXSpeed[0];
        offset = 0;
    }

    offset++;
    gCurrentSprite.CORE_X_X_MOVEMENT_IDX = offset;
    gCurrentSprite.xPosition += movement;

    if (gCurrentSprite.status & SPRITE_STATUS_SAMUS_COLLIDING)
    {
        gPreventMovementTimer = SAMUS_ITEM_PMT;

        gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;
        gCurrentSprite.pose = 0x5f;
        gCurrentSprite.ignoreSamusCollisionTimer = 1;
        gCurrentSprite.SPRITE_X_SPEED_DEC = 0;
        gCurrentSprite.SPRITE_X_SPEED_INC = 1;
        gCurrentSprite.SPRITE_Y_SPEED_DEC = 0;
        gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
        gCurrentSprite.status |= SPRITE_STATUS_ROTATION_SCALING_SINGLE;
        gCurrentSprite.rotation = 0;
        gCurrentSprite.scaling = Q_8_8(1);
        gCurrentSprite.CORE_X_ABSORB_DELAY = 20;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.pOam = sCoreXAbilityOam_GettingAbsorbed;

        ParticleSet(gSamusData.yPosition + gSamusData.drawDistanceTop / 2, gSamusData.xPosition, PE_ABSORB_CORE_X);

        switch (gCurrentSprite.spriteId)
        {
            case PSPRITE_MORPH_BALL_ABILITY:
                EventCheckAdvance(EVENT_MORPH_BALL_ABILITY_RECOVERED);
                break;

            case PSPRITE_HIGH_JUMP_ABILITY:
                EventCheckAdvance(EVENT_HIGH_JUMP_ABILITY_RECOVERED);
                break;

            case PSPRITE_SPEEDBOOSTER_ABILITY:
                EventCheckAdvance(EVENT_SPEED_BOOSTER_ABILITY_RECOVERED);
                break;

            case PSPRITE_VARIA_SUIT_ABILITY:
                EventCheckAdvance(EVENT_VARIA_SUIT_ABILITY_RECOVERED);
                break;

            case PSPRITE_SPACE_JUMP_ABILITY:
                EventCheckAdvance(EVENT_SPACE_JUMP_ABILITY_RECOVERED);
                break;

            case PSPRITE_GRAVITY_SUIT_ABILITY:
                EventCheckAdvance(EVENT_GRAVITY_SUIT_ABILITY_RECOVERED);
                break;

            case PSPRITE_SCREW_ATTACK_ABILITY:
                EventCheckAdvance(EVENT_SCREW_ATTACK_ABILITY_RECOVERED);
                break;
        }

        SpriteUtilRefillSamus(400, 50, 10);
        gSamusEnvironmentalEffects[0].externalTimer = 48;
        SoundPlay(0x92);
    }
    else if (MOD_AND(gFrameCounter8Bit, 64) == 0)
    {
        SoundPlay(SOUND_CORE_X_AURA);
    }
}

/**
 * @brief Handles a core-X getting absorbed by Samus
 *
 */
void CoreXAbilityGettingAbsorbed(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;
    XParasiteStickToSamus();

    if (gCurrentSprite.CORE_X_ABSORB_DELAY != 0)
    {
        gCurrentSprite.CORE_X_ABSORB_DELAY--;
    }
    else if (gCurrentSprite.scaling > Q_8_8(0.3125f))
    {
        gCurrentSprite.scaling -= Q_8_8(0.03125f);
    }
    else
    {
        gCurrentSprite.status = 0;
        SpriteSpawnPrimary(PSPRITE_MESSAGE_BANNER, 0, 6, SSP_UNINFECTED_OR_BOSS, gAbilityRestingYPosition,
            gAbilityRestingXPosition, 0);
    }
}

/**
 * @brief Core-X ability AI
 *
 */
void CoreXAbility(void)
{
    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_SPAWNING_FROM_X_INIT:
            CoreXAbilityInit();

        case SPRITE_POSE_SPAWNING_FROM_X:
            CoreXAbilityTransfromation();
            break;

        case SPRITE_POSE_UNINITIALIZED:
            CoreXAbilityInit();
            break;

        case SPRITE_POSE_IDLE_INIT:
            CoreXAbilityIdleInit();

        case SPRITE_POSE_IDLE:
            CoreXAbilityIdle();
            break;

        case CORE_X_POSE_MOVING_TO_SPAWN_POINT:
            CoreXAbilityMovingToSpawnPoint();
            break;

        case CORE_X_POSE_SPAWINING_BOSS:
            CoreXAbilitySpawningBoss();
            break;

        case CORE_X_POSE_MOVING_INIT:
            CoreXAbilityMovingInit();

        case CORE_X_POSE_MOVING:
            CoreXAbilityMoving();
            break;

        case CORE_X_POSE_MOVING_TO_TARGET_INIT:
            CoreXAbilityMovingToTargetInit();
            break;

        case CORE_X_POSE_MOVING_TO_TARGET:
            CoreXAbilityMovingToTarget();
            break;

        case CORE_X_POSE_WAITING_AT_TARGET:
            CoreXAbilityWaitingAtTarget();
            break;

        case CORE_X_POSE_GETTING_ABSORBED:
            CoreXAbilityGettingAbsorbed();
            break;
    }

    if (gCurrentSprite.pose <= CORE_X_POSE_SPAWINING_BOSS)
    {
        gXParasiteTargetYPosition = gCurrentSprite.yPosition;
        gXParasiteTargetXPosition = gCurrentSprite.xPosition;
    }
}

/**
 * @brief Core-X shell AI
 *
 */
void CoreXShell(void)
{
    u8 primaryRamSlot;
    u16 maxHealth;
    u8 tmp;

    primaryRamSlot = gCurrentSprite.primarySpriteRamSlot;
    maxHealth = GET_SSPRITE_HEALTH(gCurrentSprite.spriteId);

    switch (gCurrentSprite.pose)
    {
        case 0x18:
            gCurrentSprite.ignoreSamusCollisionTimer = 1;
            if (SpriteUtilHasCurrentAnimationEnded())
                gCurrentSprite.status = 0;
            return;

        case SPRITE_POSE_UNINITIALIZED:
            gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
            gCurrentSprite.frozenPaletteRowOffset = 1;
            gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
            gCurrentSprite.drawOrder = 5;
            gCurrentSprite.bgPriority = gIoRegisters.bg1Cnt & 3;
            gCurrentSprite.health = maxHealth;
            gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1.5f);
            gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1.5f);
            gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1.5f);
            gCurrentSprite.hitboxTop = -PIXEL_TO_SUB_PIXEL(0x14);
            gCurrentSprite.hitboxBottom = PIXEL_TO_SUB_PIXEL(0x14);
            gCurrentSprite.hitboxLeft = -PIXEL_TO_SUB_PIXEL(0x14);
            gCurrentSprite.hitboxRight = PIXEL_TO_SUB_PIXEL(0x14);
            gCurrentSprite.pOam = sCoreXShellOam_White;
            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;
            gCurrentSprite.samusCollision = SSC_RIDLEY_TAIL_SERRIS_SEGMENT;
            gCurrentSprite.pose = SPRITE_POSE_IDLE;
            break;
    }

    gCurrentSprite.yPosition = gSpriteData[primaryRamSlot].yPosition;
    gCurrentSprite.xPosition = gSpriteData[primaryRamSlot].xPosition;

    if (gSpriteData[primaryRamSlot].status & SPRITE_STATUS_MOSAIC)
        gCurrentSprite.status |= SPRITE_STATUS_MOSAIC;
    else
        gCurrentSprite.status &= ~SPRITE_STATUS_MOSAIC;

    switch (gSpriteData[primaryRamSlot].pose)
    {
        case CORE_X_POSE_SPAWINING_BOSS:
            if (gSpriteData[primaryRamSlot].CORE_X_TIMER <= 8 * 4)
                gCurrentSprite.status = 0;

        case SPRITE_POSE_IDLE_INIT:
        case SPRITE_POSE_IDLE:
        case CORE_X_POSE_MOVING_TO_SPAWN_POINT:
            gCurrentSprite.ignoreSamusCollisionTimer = 1;
            gCurrentSprite.status ^= SPRITE_STATUS_NOT_DRAWN;
            break;

        case CORE_X_POSE_MOVING_INIT:
            gCurrentSprite.status &= ~SPRITE_STATUS_IGNORE_PROJECTILES;

        case CORE_X_POSE_MOVING:
            if (gCurrentSprite.health == 0)
            {
                gCurrentSprite.samusCollision = SSC_NONE;
                gCurrentSprite.pOam = sCoreXShellOam_Breaking;
                gCurrentSprite.animationDurationCounter = 0;
                gCurrentSprite.currentAnimationFrame = 0;
                gCurrentSprite.pose = 0x18;
                gSpriteData[primaryRamSlot].pose = CORE_X_POSE_MOVING_TO_TARGET_INIT;
                SoundPlay(SOUND_CORE_X_SHELL_BURST);
            }
            else
            {
                if (gCurrentSprite.health <= maxHealth / 3)
                {
                    gCurrentSprite.pOam = sCoreXShellOam_Red;
                    gCurrentSprite.frozenPaletteRowOffset = 3;
                }
                else if (gCurrentSprite.health <= maxHealth * 2 / 3)
                {
                    gCurrentSprite.pOam = sCoreXShellOam_Yellow;
                    gCurrentSprite.frozenPaletteRowOffset = 2;
                }

                if (SPRITE_GET_ISFT(gCurrentSprite) == 1)
                {
                    tmp = SpriteUtilCountPrimarySprites(PSPRITE_X_PARASITE_CORE_X_OR_PARASITE);
                    if (tmp < 6)
                    {
                        SpriteSpawnNewXParasite(PSPRITE_X_PARASITE_CORE_X_OR_PARASITE, 0, 0,
                            gCurrentSprite.primarySpriteRamSlot, SSP_X_ABSORBABLE_BY_SAMUS, gCurrentSprite.yPosition,
                            gCurrentSprite.xPosition, 0);
                    }
                }
                else if (SPRITE_GET_ISFT(gCurrentSprite) == 16)
                {
                    SoundPlay(SOUND_CORE_X_HURT);
                    gCurrentSprite.properties |= SP_IMMUNE_TO_PROJECTILES;
                    gSpriteData[primaryRamSlot].CORE_X_HIT_TIMER = 180;

                    if (gCurrentSprite.yPosition > gSamusData.yPosition - BLOCK_SIZE)
                    {
                        gSpriteData[primaryRamSlot].status |= SPRITE_STATUS_SAMUS_DETECTED;
                    }
                    else
                    {
                        gSpriteData[primaryRamSlot].status &= ~SPRITE_STATUS_SAMUS_DETECTED;
                    }

                    if (gCurrentSprite.xPosition > gSamusData.xPosition)
                    {
                        gSpriteData[primaryRamSlot].status |= SPRITE_STATUS_FACING_RIGHT;
                    }
                    else
                    {
                        gSpriteData[primaryRamSlot].status &= ~SPRITE_STATUS_FACING_RIGHT;
                    }

                    gSpriteData[primaryRamSlot].SPRITE_X_SPEED_DEC = PIXEL_TO_SUB_PIXEL(2.5f) * 4;
                    gSpriteData[primaryRamSlot].SPRITE_X_SPEED_INC = PIXEL_TO_SUB_PIXEL(2.5f) * 4;
                    gSpriteData[primaryRamSlot].CORE_X_TIMER = PIXEL_TO_SUB_PIXEL(1.75f) * 4;
                    gSpriteData[primaryRamSlot].SPRITE_Y_SPEED_INC = PIXEL_TO_SUB_PIXEL(1.75f) * 4;
                }

                tmp = gSpriteData[primaryRamSlot].CORE_X_HIT_TIMER;
                if (tmp != 0)
                {
                    if (MOD_AND(tmp, 4) == 0)
                    {
                        if ((tmp & 4) != 0)
                            SPRITE_SET_ABSOLUTE_PALETTE_ROW(gCurrentSprite, OBJ_PAL_ROW_FLASHING_SPRITE);
                        else
                            gCurrentSprite.paletteRow = 0;
                    }

                    if (--gSpriteData[primaryRamSlot].CORE_X_HIT_TIMER == 0)
                    {
                        gCurrentSprite.properties &= ~SP_IMMUNE_TO_PROJECTILES;
                        gCurrentSprite.paletteRow = 0;
                    }
                }
            }
            break;
    }
}

/**
 * @brief Core-X static/aura AI
 *
 */
void AbilityAura(void)
{
    u8 primaryRamSlot;

    gCurrentSprite.ignoreSamusCollisionTimer = 1;
    primaryRamSlot = gCurrentSprite.primarySpriteRamSlot;

    if (gCurrentSprite.pose == SPRITE_POSE_UNINITIALIZED)
    {
        gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
        gCurrentSprite.drawOrder = 4;
        gCurrentSprite.bgPriority = gIoRegisters.bg1Cnt & 3;
        gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1);
        gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1);
        gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);
        gCurrentSprite.hitboxTop = -PIXEL_SIZE;
        gCurrentSprite.hitboxBottom = PIXEL_SIZE;
        gCurrentSprite.hitboxLeft = -PIXEL_SIZE;
        gCurrentSprite.hitboxRight = PIXEL_SIZE;
        gCurrentSprite.animationDurationCounter = 0;
        gCurrentSprite.currentAnimationFrame = 0;
        gCurrentSprite.samusCollision = SSC_NONE;
        gCurrentSprite.pose = SPRITE_POSE_IDLE;

        if (gCurrentSprite.roomSlot == 2)
            gCurrentSprite.pOam = sCoreXStaticOam_2;
        else if (gCurrentSprite.roomSlot == 1)
            gCurrentSprite.pOam = sCoreXStaticOam_1;
        else
            gCurrentSprite.pOam = sCoreXStaticOam_0;
    }

    gCurrentSprite.yPosition = gSpriteData[primaryRamSlot].yPosition;
    gCurrentSprite.xPosition = gSpriteData[primaryRamSlot].xPosition;

    if (gSpriteData[primaryRamSlot].status & SPRITE_STATUS_MOSAIC)
        gCurrentSprite.status |= SPRITE_STATUS_MOSAIC;
    else
        gCurrentSprite.status &= ~SPRITE_STATUS_MOSAIC;

    switch (gSpriteData[primaryRamSlot].pose)
    {
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3a:
        case 0x3b:
            gCurrentSprite.status |= SPRITE_STATUS_NOT_DRAWN;
            break;

        case 0x3c:
            gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
            break;

        case CORE_X_POSE_SPAWINING_BOSS:
            if (gSpriteData[primaryRamSlot].CORE_X_TIMER <= 8 * 4)
                gCurrentSprite.status = 0;

        case SPRITE_POSE_IDLE_INIT:
        case SPRITE_POSE_IDLE:
        case CORE_X_POSE_MOVING_TO_SPAWN_POINT:
            gCurrentSprite.status ^= SPRITE_STATUS_NOT_DRAWN;
            break;

        case CORE_X_POSE_MOVING_TO_TARGET_INIT:
            if (gCurrentSprite.roomSlot != 0)
            {
                gCurrentSprite.status = 0;
            }
            else
            {
                gCurrentSprite.animationDurationCounter = 0;
                gCurrentSprite.currentAnimationFrame = 0;
                gCurrentSprite.pOam = sCoreXAbilityAuraOam_Fast;
            }
            break;

        case CORE_X_POSE_MOVING_TO_TARGET:
            if (MOD_AND(gFrameCounter8Bit, 4) == 0)
                gCurrentSprite.status ^= SPRITE_STATUS_NOT_DRAWN;
            break;

        case CORE_X_POSE_WAITING_AT_TARGET:
            gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
            break;

        case CORE_X_POSE_GETTING_ABSORBED:
            gCurrentSprite.status = 0;
            break;
    }
}
