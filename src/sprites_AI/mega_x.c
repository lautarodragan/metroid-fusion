#include "data/sprites/mega_x.h"

#include "gba.h"
#include "globals.h"

#include "data/generic_data.h"
#include "data/sprite_data.h"
#include "data/sprites/message_banner.h"
#include "data/sprites/x_parasite.h"

#include "constants/audio.h"
#include "constants/event.h"
#include "constants/particle.h"
#include "constants/samus.h"

#include "structs/samus.h"
#include "structs/sprite.h"

#define VARIA_ABILITY_HIT_TIMER work0 // Flashing and immune after a hit, set by the mega X and the core X shell
#define VARIA_ABILITY_GROWN work1 // Spawning, set once fully scaled
#define VARIA_ABILITY_GFX_PART work1 // Turning into the core X, graphics part being loaded
#define VARIA_ABILITY_TIMER work2 // Spawning, after growing
#define VARIA_ABILITY_X_MOVEMENT_IDX work3 // Spawning
#define VARIA_ABILITY_Y_MOVEMENT_IDX work4 // Spawning
#define VARIA_ABILITY_SPAWN_Y workY // Written but never read
#define VARIA_ABILITY_SPAWN_X workX // Written but never read
#define MEGA_X_MOSAIC_IDX workY // Turning into an X (unused), also the graphics part loaded

#define MEGA_X_SHIELD_ANGLE work2
#define MEGA_X_SHIELD_GROWING work3

#define MEGA_X_TIMER work1

void MegaXUpdatePalette(void)
{
    boolu32 update;
    u16 health;
    u16 maxHealth;
    const u16* pPal;

    update = FALSE;
    health = gCurrentSprite.health;
    maxHealth = GET_SSPRITE_HEALTH(gCurrentSprite.spriteId);

    switch (gBossWork1)
    {
        case 0:
            if (health <= maxHealth * 2 / 3)
            {
                pPal = sMegaXPal + 5 * PAL_ROW;
                gBossWork1 = 1;
                update = TRUE;
            }
            break;

        case 1:
            if (health <= maxHealth / 3)
            {
                pPal = sMegaXPal + 6 * 16;
                gBossWork1 = 2;
                update = TRUE;
            }
            break;
    }

    if (update)
        DMA3_COPY_16(pPal, PALRAM_OBJ + 12 * PAL_ROW_SIZE, 1 * PAL_ROW);
}

void MegaXDestroyShields(void)
{
    u8 i;

    for (i = 0; i < MAX_AMOUNT_OF_SPRITES; i++)
    {
        if (gSpriteData[i].status & SPRITE_STATUS_EXISTS && gSpriteData[i].properties & SP_SECONDARY_SPRITE &&
            gSpriteData[i].spriteId == SSPRITE_MEGA_X_SHIELD)
        {
            // Checking health here is unnecessary
            if (gSpriteData[i].health > 0)
                gSpriteData[i].health = 0;
        }
    }
}

void MegaXTurningIntoX_Unused(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (--gCurrentSprite.MEGA_X_MOSAIC_IDX != 0)
    {
        gWrittenToMosaic_H = sXParasiteMosaicValues[gCurrentSprite.MEGA_X_MOSAIC_IDX];
    }
    else
    {
        gCurrentSprite.pose = 0x1b;
        gCurrentSprite.status &= ~SPRITE_STATUS_MOSAIC;
        gCurrentSprite.bgPriority = gIoRegisters.bg1Cnt & 3;
    }

    if (gCurrentSprite.MEGA_X_MOSAIC_IDX < sizeof(sMessageBannerGfx) / 512)
        SpriteLoadGfx(PSPRITE_MESSAGE_BANNER, 6, gCurrentSprite.MEGA_X_MOSAIC_IDX);
    else if (gCurrentSprite.MEGA_X_MOSAIC_IDX == sizeof(sMessageBannerGfx) / 512)
        SpriteLoadPal(PSPRITE_MESSAGE_BANNER, 6, ARRAY_SIZE(sMessageBannerPal) / 16);
}

void VariaSuitAbilityInit(void)
{
    if (gEquipment.suitMiscStatus & SMF_VARIA_SUIT)
    {
        gCurrentSprite.status = 0;
        return;
    }

    gBossWork1 = 0;

    gCurrentSprite.ignoreSamusCollisionTimer = 1;
    gCurrentSprite.yPosition -= BLOCK_TO_SUB_PIXEL(4.0f);
    gCurrentSprite.xPosition -= BLOCK_TO_SUB_PIXEL(2.0f);
    gCurrentSprite.VARIA_ABILITY_SPAWN_Y = gCurrentSprite.yPosition;
    gCurrentSprite.VARIA_ABILITY_SPAWN_X = gCurrentSprite.xPosition;
    gCurrentSprite.pose = 0x37;
    gCurrentSprite.status |= SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.health = GET_PSPRITE_HEALTH(gCurrentSprite.spriteId);
    gCurrentSprite.drawOrder = 6;
    gCurrentSprite.bgPriority = gIoRegisters.bg1Cnt & 3;
    gCurrentSprite.samusCollision = SSC_NONE;
    gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);
    gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(0.5f);
    gCurrentSprite.hitboxBottom = BLOCK_TO_SUB_PIXEL(0.5f);
    gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(0.5f);
    gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(0.5f);
    gCurrentSprite.pOam = sMegaXOam_3a59b0;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.rotation = 0;
    gCurrentSprite.scaling = Q_8_8(1.f / 16);
    gCurrentSprite.VARIA_ABILITY_HIT_TIMER = 0;

    SpriteSpawnSecondary(SSPRITE_MEGA_X, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
    SpriteSpawnSecondary(SSPRITE_CORE_X_SHELL_VARIA, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
    SpriteSpawnSecondary(SSPRITE_ABILITY_AURA, 0, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
        gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
    SpriteSpawnSecondary(SSPRITE_ABILITY_AURA, 1, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
        gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
    SpriteSpawnSecondary(SSPRITE_ABILITY_AURA, 2, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
        gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
}

void VariaSuitAbilityWaitingToSpawn(void)
{
    if (SpriteUtilCheckSamusNearSpriteLeftRight(BLOCK_TO_SUB_PIXEL(4.f), BLOCK_TO_SUB_PIXEL(4.f)) != NSLR_OUT_OF_RANGE)
    {
        gCurrentSprite.VARIA_ABILITY_GROWN = 0;
        gCurrentSprite.VARIA_ABILITY_X_MOVEMENT_IDX = 0;
        gCurrentSprite.VARIA_ABILITY_Y_MOVEMENT_IDX = 0;
        gCurrentSprite.pose = 0x38;

        PlayMusic(MUSIC_VARIA_CORE_X_BATTLE, 7);
    }
}

void VariaSuitAbilitySpawning(void)
{
    u8 yOffset;
    u8 xOffset;
    s16 yMovement;
    s16 xMovement;

    yOffset = gCurrentSprite.VARIA_ABILITY_Y_MOVEMENT_IDX;
    yMovement = sVariaSuitAbilitySpawningYMovement[yOffset];
    if (yMovement == SHORT_MAX)
    {
        yMovement = sVariaSuitAbilitySpawningYMovement[gCurrentSprite.VARIA_ABILITY_Y_MOVEMENT_IDX - 1];
        gCurrentSprite.yPosition += yMovement;
    }
    else
    {
        yOffset++;
        gCurrentSprite.VARIA_ABILITY_Y_MOVEMENT_IDX = yOffset;
        gCurrentSprite.yPosition += yMovement;
    }

    xOffset = gCurrentSprite.VARIA_ABILITY_X_MOVEMENT_IDX;
    xMovement = sVariaSuitAbilitySpawningXMovement[xOffset];
    if (xMovement == SHORT_MAX)
    {
        xMovement = sVariaSuitAbilitySpawningXMovement[gCurrentSprite.VARIA_ABILITY_X_MOVEMENT_IDX - 1];
        gCurrentSprite.xPosition += xMovement;
    }
    else
    {
        xOffset++;
        gCurrentSprite.VARIA_ABILITY_X_MOVEMENT_IDX = xOffset;
        gCurrentSprite.xPosition += xMovement;
    }

    if (gCurrentSprite.VARIA_ABILITY_GROWN == 0)
    {
        if (gCurrentSprite.scaling < Q_8_8(2))
        {
            gCurrentSprite.scaling = gCurrentSprite.scaling + Q_8_8(1.f / 16);
        }
        else
        {
            gCurrentSprite.VARIA_ABILITY_GROWN = 1;
            gCurrentSprite.VARIA_ABILITY_TIMER = 60;
        }
    }
    else
    {
        if (--gCurrentSprite.VARIA_ABILITY_TIMER == 0)
        {
            gCurrentSprite.pose = 0x39;

            SpriteSpawnSecondary(SSPRITE_MEGA_X_SHIELD, 0, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            SpriteSpawnSecondary(SSPRITE_MEGA_X_SHIELD, 1, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            SpriteSpawnSecondary(SSPRITE_MEGA_X_SHIELD, 2, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            SpriteSpawnSecondary(SSPRITE_MEGA_X_SHIELD, 3, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            SpriteSpawnSecondary(SSPRITE_MEGA_X_SHIELD, 4, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            SpriteSpawnSecondary(SSPRITE_MEGA_X_SHIELD, 5, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            SpriteSpawnSecondary(SSPRITE_MEGA_X_SHIELD, 6, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
            SpriteSpawnSecondary(SSPRITE_MEGA_X_SHIELD, 7, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
        }
    }
}

void VariaSuitAbilityMovingInit(void)
{
    gCurrentSprite.pose = 0x3a;
    gCurrentSprite.SPRITE_X_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_X_SPEED_INC = 1;
    gCurrentSprite.SPRITE_Y_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
}

void VariaSuitAbilityMoving(void)
{
    u16 targetY;

    if ((gFrameCounter8Bit & 128) != 0)
        targetY = gSamusData.yPosition - BLOCK_TO_SUB_PIXEL(5.0f);
    else
        targetY = gSamusData.yPosition - BLOCK_TO_SUB_PIXEL(1.125f);

    XParasiteMoveWithSound(targetY, gSamusData.xPosition, BLOCK_TO_SUB_PIXEL(0.21875f) * 4,
        BLOCK_TO_SUB_PIXEL(0.3125f) * 4, LOG2(4), SOUND_CORE_X_MOVING);
}

void VariaSuitAbilityShrinking(void)
{
    if (gCurrentSprite.scaling > Q_8_8(1))
    {
        gCurrentSprite.scaling -= Q_8_8(1.f / 16);
    }
    else
    {
        gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
        gCurrentSprite.pose = 0x3c;
        gCurrentSprite.VARIA_ABILITY_GFX_PART = 9;
    }
}

void VariaSuitAbilityShrunk(void)
{
    // Empty
}

void VariaSuitAbilityTurningIntoCoreX(void)
{
    if (--gCurrentSprite.VARIA_ABILITY_GFX_PART == 0)
        gCurrentSprite.pose = 0x3f;

    if (gCurrentSprite.VARIA_ABILITY_GFX_PART < sizeof(sMessageBannerGfx) / 512)
        SpriteLoadGfx(PSPRITE_MESSAGE_BANNER, 6, gCurrentSprite.VARIA_ABILITY_GFX_PART);
    else if (gCurrentSprite.VARIA_ABILITY_GFX_PART == sizeof(sMessageBannerGfx) / 512)
        SpriteLoadPal(PSPRITE_MESSAGE_BANNER, 6, ARRAY_SIZE(sMessageBannerPal) / 16);
}

void VariaSuitAbilityCoreXMovingInit(void)
{
    gCurrentSprite.pose = 0x40;
    gCurrentSprite.SPRITE_X_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_X_SPEED_INC = 1;
    gCurrentSprite.SPRITE_Y_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
}

void VariaSuitAbilityCoreXMoving(void)
{
    XParasiteMoveWithSound((u16)(gSamusData.yPosition - BLOCK_TO_SUB_PIXEL(1.125f)), gSamusData.xPosition,
        BLOCK_TO_SUB_PIXEL(0.109375f) * 4, BLOCK_TO_SUB_PIXEL(0.15625f) * 4, LOG2(4), SOUND_CORE_X_MOVING);
}

void VariaSuitAbilityCoreXMovingInit_Unused(void)
{
    gCurrentSprite.pose = 0x42;
    gCurrentSprite.SPRITE_X_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_X_SPEED_INC = 1;
    gCurrentSprite.SPRITE_Y_SPEED_DEC = 0;
    gCurrentSprite.SPRITE_Y_SPEED_INC = 1;
}

void VariaSuitAbilityCoreXMoving_Unused(void)
{
    XParasiteMoveWithSound((u16)(gSamusData.yPosition - BLOCK_TO_SUB_PIXEL(1.125f)), gSamusData.xPosition,
        BLOCK_TO_SUB_PIXEL(0.109375f) * 4, BLOCK_TO_SUB_PIXEL(0.15625f) * 4, LOG2(4), SOUND_CORE_X_MOVING);
}

void MegaXShieldInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.drawOrder = 3;
    gCurrentSprite.bgPriority = gIoRegisters.bg1Cnt & 3;
    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(.75f);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.75f);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(.75f);
    gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(0.5f);
    gCurrentSprite.hitboxBottom = BLOCK_TO_SUB_PIXEL(0.5f);
    gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(0.5f);
    gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(0.5f);
    gCurrentSprite.pOam = sMegaXOam_3a5ef8;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.samusCollision = SSC_HURTS_SAMUS;
    gCurrentSprite.health = GET_SSPRITE_HEALTH(gCurrentSprite.spriteId);
    gCurrentSprite.pose = 2;
    gCurrentSprite.scaling = 0x100;
    gCurrentSprite.MEGA_X_SHIELD_GROWING = FALSE;
    gCurrentSprite.MEGA_X_SHIELD_ANGLE = gCurrentSprite.roomSlot * Q_8_8(1.f / 8);
}

void MegaXShieldIdle(void)
{
    s16 distance;
    u32 angle;
    s16 sin;
    s16 cos;
    u16 yOffset;
    u16 xOffset;
    u8 primarySlot;

    if (gCurrentSprite.health == 0)
    {
        ParticleSet(gCurrentSprite.yPosition, gCurrentSprite.xPosition, PE_EXPLOSION_2);
        gCurrentSprite.status = 0;
        return;
    }

    gCurrentSprite.MEGA_X_SHIELD_ANGLE += Q_8_8(3.f / 256);

    if (gCurrentSprite.MEGA_X_SHIELD_GROWING)
    {
        if (gCurrentSprite.scaling < 0x140)
            gCurrentSprite.scaling += 2;
        else
            gCurrentSprite.MEGA_X_SHIELD_GROWING = FALSE;
    }
    else
    {
        if (gCurrentSprite.scaling > 0xc0)
            gCurrentSprite.scaling -= 2;
        else
            gCurrentSprite.MEGA_X_SHIELD_GROWING = TRUE;
    }

    primarySlot = gCurrentSprite.primarySpriteRamSlot;
    distance = gCurrentSprite.scaling;
    angle = gCurrentSprite.MEGA_X_SHIELD_ANGLE;

    sin = SIN(angle);
    if (sin < 0)
    {
        yOffset = Q_8_8_TO_INT(-sin * distance);
        gCurrentSprite.yPosition = gSpriteData[primarySlot].yPosition - yOffset;
    }
    else
    {
        yOffset = Q_8_8_TO_INT(sin * distance);
        gCurrentSprite.yPosition = gSpriteData[primarySlot].yPosition + yOffset;
    }

    cos = COS(angle);
    if (cos < 0)
    {
        xOffset = Q_8_8_TO_INT(-cos * distance);
        gCurrentSprite.xPosition = gSpriteData[primarySlot].xPosition - xOffset;
    }
    else
    {
        xOffset = Q_8_8_TO_INT(cos * distance);
        gCurrentSprite.xPosition = gSpriteData[primarySlot].xPosition + xOffset;
    }
}

void VariaSuitAbility(void)
{
    switch (gCurrentSprite.pose)
    {
        case 0:
            VariaSuitAbilityInit();
            break;

        case 0x37:
            VariaSuitAbilityWaitingToSpawn();
            break;

        case 0x38:
            VariaSuitAbilitySpawning();
            break;

        case 0x39:
            VariaSuitAbilityMovingInit();
            break;

        case 0x3a:
            VariaSuitAbilityMoving();
            break;

        case 0x3b:
            VariaSuitAbilityShrinking();
            break;

        case 0x3c:
            VariaSuitAbilityShrunk();
            break;

        case 0x3d:
            VariaSuitAbilityTurningIntoCoreX();
            break;

        case 0x3f:
            VariaSuitAbilityCoreXMovingInit();
            break;

        case 0x40:
            VariaSuitAbilityCoreXMoving();
            break;

        case 0x5c:
            CoreXAbilityMovingToTargetInit();
            break;

        case 0x5d:
            CoreXAbilityMovingToTarget();
            break;

        case 0x5e:
            CoreXAbilityWaitingAtTarget();
            break;

        case 0x5f:
            CoreXAbilityGettingAbsorbed();
            break;
    }
}

void MegaX(void)
{
    u8 primaryRamSlot;
    u8 tmp;

    primaryRamSlot = gCurrentSprite.primarySpriteRamSlot;

    switch (gCurrentSprite.pose)
    {
        case 0x18:
            gCurrentSprite.ignoreSamusCollisionTimer = 1;
            gCurrentSprite.status ^= SPRITE_STATUS_NOT_DRAWN;
            if (--gCurrentSprite.MEGA_X_TIMER == 0)
            {
                gSpriteData[primaryRamSlot].pose = 0x3d;
                gCurrentSprite.status = 0;
            }
            return;

        case SPRITE_POSE_UNINITIALIZED:
            gCurrentSprite.status |= SPRITE_STATUS_IGNORE_PROJECTILES;
            gCurrentSprite.frozenPaletteRowOffset = 4;
            gCurrentSprite.drawOrder = 3;
            gCurrentSprite.bgPriority = gIoRegisters.bg1Cnt & 3;
            gCurrentSprite.health = GET_SSPRITE_HEALTH(gCurrentSprite.spriteId);
            gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(3);
            gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(3);
            gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(3);
            gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(2.25f);
            gCurrentSprite.hitboxBottom = BLOCK_TO_SUB_PIXEL(2.25f);
            gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(2.25f);
            gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(2.25f);
            gCurrentSprite.pOam = sMegaXOam_3a5e70;
            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;
            gCurrentSprite.samusCollision = SSC_RIDLEY_TAIL_SERRIS_SEGMENT;
            gCurrentSprite.pose = SPRITE_POSE_IDLE;
            gCurrentSprite.status |= SPRITE_STATUS_DOUBLE_SIZE | SPRITE_STATUS_ROTATION_SCALING_WHOLE;
            gCurrentSprite.scaling = 0x10;
            gCurrentSprite.rotation = 0;
            break;
    }

    gCurrentSprite.yPosition = gSpriteData[primaryRamSlot].yPosition;
    gCurrentSprite.xPosition = gSpriteData[primaryRamSlot].xPosition;

    switch (gSpriteData[primaryRamSlot].pose)
    {
        case 0x37:
            gCurrentSprite.ignoreSamusCollisionTimer = 1;
            break;

        case 0x38:
            gCurrentSprite.ignoreSamusCollisionTimer = 1;
            gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
            gCurrentSprite.scaling = gSpriteData[primaryRamSlot].scaling;
            break;

        case 0x3b:
            gCurrentSprite.ignoreSamusCollisionTimer = 1;
            if (MOD_AND(gFrameCounter8Bit, 4) == 0)
            {
                if ((gFrameCounter8Bit & 4) != 0)
                    SPRITE_SET_ABSOLUTE_PALETTE_ROW(gCurrentSprite, OBJ_PAL_ROW_FLASHING_SPRITE);
                else
                    gCurrentSprite.paletteRow = 0;
            }

            gCurrentSprite.scaling = gSpriteData[primaryRamSlot].scaling;
            if (gCurrentSprite.scaling <= Q_8_8(1))
            {
                gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1.5f);
                gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1.5f);
                gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1.5f);
                gCurrentSprite.status &= ~(SPRITE_STATUS_DOUBLE_SIZE | SPRITE_STATUS_ROTATION_SCALING_WHOLE);
                gCurrentSprite.pose = 0x18;
                gCurrentSprite.MEGA_X_TIMER = 60;
                gCurrentSprite.paletteRow = 0;
                ParticleSet(gCurrentSprite.yPosition + BLOCK_TO_SUB_PIXEL(0.375f), gCurrentSprite.xPosition, PE_EXPLOSION_10);
            }
            else if (gCurrentSprite.scaling < Q_8_8(1.5f))
            {
                gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(2.125f);
                gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(2.125f);
                gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(2.125f);
            }
            break;

        case 0x39:
            gCurrentSprite.status &= ~SPRITE_STATUS_IGNORE_PROJECTILES;
        case 0x3a:
            if (SPRITE_GET_ISFT(gCurrentSprite) == 16)
            {
                SoundPlay(SOUND_MEGA_X_HURT);
                gCurrentSprite.properties |= SP_IMMUNE_TO_PROJECTILES;
                gCurrentSprite.pOam = sMegaXOam_3a5ed0;
                gCurrentSprite.animationDurationCounter = 0;
                gCurrentSprite.currentAnimationFrame = 0;
                if (gCurrentSprite.health == 0)
                {
                    gCurrentSprite.samusCollision = SSC_NONE;
                    gSpriteData[primaryRamSlot].pose = 0x3b;
                    MegaXDestroyShields();
                    return;
                }

                gSpriteData[primaryRamSlot].VARIA_ABILITY_HIT_TIMER = 60;

                if (gCurrentSprite.yPosition > gSamusData.yPosition - BLOCK_SIZE)
                    gSpriteData[primaryRamSlot].status |= SPRITE_STATUS_FACING_DOWN;
                else
                    gSpriteData[primaryRamSlot].status &= ~SPRITE_STATUS_FACING_DOWN;

                if (gCurrentSprite.xPosition > gSamusData.xPosition)
                    gSpriteData[primaryRamSlot].status |= SPRITE_STATUS_FACING_RIGHT;
                else
                    gSpriteData[primaryRamSlot].status &= ~SPRITE_STATUS_FACING_RIGHT;

                gSpriteData[primaryRamSlot].SPRITE_X_SPEED_DEC = 0x50;
                gSpriteData[primaryRamSlot].SPRITE_X_SPEED_INC = 0x50;
                gSpriteData[primaryRamSlot].SPRITE_Y_SPEED_DEC = 0x38;
                gSpriteData[primaryRamSlot].SPRITE_Y_SPEED_INC = 0x38;
            }

            tmp = gSpriteData[primaryRamSlot].VARIA_ABILITY_HIT_TIMER;
            if (tmp > 0)
            {
                if (MOD_AND(tmp, 4) == 0)
                {
                    if ((tmp & 4) != 0)
                        SPRITE_SET_ABSOLUTE_PALETTE_ROW(gCurrentSprite, OBJ_PAL_ROW_FLASHING_SPRITE);
                    else
                        gCurrentSprite.paletteRow = 0;
                }

                if (--gSpriteData[primaryRamSlot].VARIA_ABILITY_HIT_TIMER == 0)
                {
                    gCurrentSprite.properties &= ~SP_IMMUNE_TO_PROJECTILES;
                    gCurrentSprite.paletteRow = 0;
                }
            }
            break;
    }

    MegaXUpdatePalette();
}

void CoreXShellVaria(void)
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
            gCurrentSprite.drawOrder = 5;
            gCurrentSprite.bgPriority = gIoRegisters.bg1Cnt & 3;
            gCurrentSprite.health = maxHealth;
            gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(3);
            gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(3);
            gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(3);
            gCurrentSprite.hitboxTop = -BLOCK_TO_SUB_PIXEL(1.25f);
            gCurrentSprite.hitboxBottom = BLOCK_TO_SUB_PIXEL(1.25f);
            gCurrentSprite.hitboxLeft = -BLOCK_TO_SUB_PIXEL(1.25f);
            gCurrentSprite.hitboxRight = BLOCK_TO_SUB_PIXEL(1.25f);
            gCurrentSprite.pOam = sMegaXOam_3a5e40;
            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;
            gCurrentSprite.samusCollision = SSC_NONE;
            gCurrentSprite.pose = SPRITE_POSE_IDLE;
            gCurrentSprite.status |= SPRITE_STATUS_DOUBLE_SIZE | SPRITE_STATUS_ROTATION_SCALING_WHOLE;
            gCurrentSprite.scaling = 0x10;
            gCurrentSprite.rotation = 0;
            break;
    }

    gCurrentSprite.yPosition = gSpriteData[primaryRamSlot].yPosition;
    gCurrentSprite.xPosition = gSpriteData[primaryRamSlot].xPosition;

    switch (gSpriteData[primaryRamSlot].pose)
    {
        case 0x37:
            gCurrentSprite.ignoreSamusCollisionTimer = 1;
            break;

        case 0x38:
            gCurrentSprite.ignoreSamusCollisionTimer = 1;
            gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
            gCurrentSprite.scaling = gSpriteData[primaryRamSlot].scaling;
            break;

        case 0x3b:
            gCurrentSprite.ignoreSamusCollisionTimer = 1;
            gCurrentSprite.scaling = gSpriteData[primaryRamSlot].scaling;
            if (gCurrentSprite.scaling <= Q_8_8(1))
            {
                gCurrentSprite.status &= ~(SPRITE_STATUS_DOUBLE_SIZE | SPRITE_STATUS_ROTATION_SCALING_WHOLE);
                gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(1.5f);
                gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(1.5f);
                gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1.5f);
            }
            else if (gCurrentSprite.scaling < Q_8_8(1.5f))
            {
                gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(2.125f);
                gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(2.125f);
                gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(2.125f);
            }
            break;

        case 0x3f:
            gCurrentSprite.status &= ~SPRITE_STATUS_IGNORE_PROJECTILES;
            gCurrentSprite.samusCollision = SSC_RIDLEY_TAIL_SERRIS_SEGMENT;
        case 0x40: {
            if (gCurrentSprite.health == 0)
            {
                gCurrentSprite.samusCollision = SSC_NONE;
                gCurrentSprite.pOam = sMegaXOam_3a5b68;
                gCurrentSprite.animationDurationCounter = 0;
                gCurrentSprite.currentAnimationFrame = 0;
                gCurrentSprite.pose = 0x18;
                gSpriteData[primaryRamSlot].pose = 0x5c;

                SoundPlay(SOUND_CORE_X_SHELL_BURST);
            }
            else
            {
                if (gCurrentSprite.health <= maxHealth / 3)
                {
                    gCurrentSprite.pOam = sMegaXOam_3a5e60;
                    gCurrentSprite.frozenPaletteRowOffset = 3;
                }
                else if (gCurrentSprite.health <= maxHealth * 2 / 3)
                {
                    gCurrentSprite.pOam = sMegaXOam_3a5e50;
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
                    gSpriteData[primaryRamSlot].VARIA_ABILITY_HIT_TIMER = 180;

                    if (gCurrentSprite.yPosition > gSamusData.yPosition - BLOCK_SIZE)
                        gSpriteData[primaryRamSlot].status |= SPRITE_STATUS_FACING_DOWN;
                    else
                        gSpriteData[primaryRamSlot].status &= ~SPRITE_STATUS_FACING_DOWN;

                    if (gCurrentSprite.xPosition > gSamusData.xPosition)
                        gSpriteData[primaryRamSlot].status |= SPRITE_STATUS_FACING_RIGHT;
                    else
                        gSpriteData[primaryRamSlot].status &= ~SPRITE_STATUS_FACING_RIGHT;

                    gSpriteData[primaryRamSlot].SPRITE_X_SPEED_DEC = BLOCK_TO_SUB_PIXEL(0.15625f) * 4;
                    gSpriteData[primaryRamSlot].SPRITE_X_SPEED_INC = BLOCK_TO_SUB_PIXEL(0.15625f) * 4;
                    gSpriteData[primaryRamSlot].SPRITE_Y_SPEED_DEC = BLOCK_TO_SUB_PIXEL(0.109375f) * 4;
                    gSpriteData[primaryRamSlot].SPRITE_Y_SPEED_INC = BLOCK_TO_SUB_PIXEL(0.109375f) * 4;
                }

                tmp = gSpriteData[primaryRamSlot].VARIA_ABILITY_HIT_TIMER;

                if (tmp != 0)
                {
                    if (MOD_AND(tmp, 4) == 0)
                    {
                        if ((tmp & 4) != 0)
                            SPRITE_SET_ABSOLUTE_PALETTE_ROW(gCurrentSprite, OBJ_PAL_ROW_FLASHING_SPRITE);
                        else
                            gCurrentSprite.paletteRow = 0;
                    }

                    if (--gSpriteData[primaryRamSlot].VARIA_ABILITY_HIT_TIMER == 0)
                    {
                        gCurrentSprite.properties &= ~SP_IMMUNE_TO_PROJECTILES;
                        gCurrentSprite.paletteRow = 0;
                    }
                }
            }
        }
    }
}

void MegaXShield(void)
{
    switch (gCurrentSprite.pose)
    {
        case 0:
            MegaXShieldInit();
            break;

        case 2:
            MegaXShieldIdle();
            break;
    }
}
