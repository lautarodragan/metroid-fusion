#include "sprites_AI/gunship_end.h"
#include "globals.h"
#include "macros.h"
#include "gba.h"

#include "data/sprites/gunship.h"
#include "data/sprites/gunship_end.h"
#include "data/samus_data.h"

#include "constants/audio.h"
#include "constants/event.h"
#include "constants/samus.h"
#include "constants/sprite.h"

#include "structs/samus.h"
#include "structs/sprite.h"

/**
 * @brief 56140 | 138 | Spawns the gunship (end) beams
 *
 */
void GunshipEndSpawnBeams(void)
{
    u16 yPosition;
    u16 xPosition;

    yPosition = gCurrentSprite.yPosition + (BLOCK_SIZE * 4 + HALF_BLOCK_SIZE);
    xPosition = gCurrentSprite.xPosition;

    switch (gCurrentSprite.work2)
    {
        case 6:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 0, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                yPosition - (BLOCK_SIZE * 3 + QUARTER_BLOCK_SIZE - PIXEL_SIZE), xPosition, 0);
            SoundPlay(0xFD);
            break;

        case 9:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 1, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                yPosition - (BLOCK_SIZE * 3 - QUARTER_BLOCK_SIZE), xPosition, 0);
            break;

        case 12:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 3, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                yPosition - (BLOCK_SIZE * 2 + QUARTER_BLOCK_SIZE + EIGHTH_BLOCK_SIZE), xPosition, 0);
            break;

        case 15:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 5, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                yPosition - BLOCK_SIZE * 2, xPosition, 0);
            break;

        case 18:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 7, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                yPosition - (BLOCK_SIZE + HALF_BLOCK_SIZE + EIGHTH_BLOCK_SIZE), xPosition, 0);
            break;

        case 21:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 9, gCurrentSprite.spritesetGfxSlot, gCurrentSprite.primarySpriteRamSlot,
                yPosition - (BLOCK_SIZE + QUARTER_BLOCK_SIZE), xPosition, 0);
            break;
    }
}

/**
 * @brief 56278 | 8c | Initializes a gunship (end)
 *
 */
void GunshipEndInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.drawOrder = 12;
    gCurrentSprite.bgPriority = 3;
    gCurrentSprite.status |= SPRITE_STATUS_ROTATION_SCALING_WHOLE;
    gCurrentSprite.scaling = Q_8_8(.5625f);
    gCurrentSprite.rotation = 0;
    gCurrentSprite.work4 = 0;
    gCurrentSprite.work3 = 0;
    gCurrentSprite.work1 = 60;

    gCurrentSprite.samusCollision = SSC_NONE;

    gCurrentSprite.drawDistanceTop = 0x7F;
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(4);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(11);

    gCurrentSprite.hitboxTop = -PIXEL_SIZE;
    gCurrentSprite.hitboxBottom = PIXEL_SIZE;
    gCurrentSprite.hitboxLeft = -PIXEL_SIZE;
    gCurrentSprite.hitboxRight = PIXEL_SIZE;

    gCurrentSprite.pose = SPRITE_POSE_IDLE_INIT;

    gCurrentSprite.pOam = (const struct FrameData*)sGunshipEndOam_Flying;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
}

/**
 * @brief 56304 | 34 | Handles a gunship (end) waiting before moving up
 *
 */
void GunshipEndWaiting(void)
{
    if (--gCurrentSprite.work1 == 0)
    {
        gCurrentSprite.pose = SPRITE_POSE_IDLE;
        PlayMusic(MUSIC_FINAL_ORDER, 14);
        gCurrentSprite.work1 = 30;
    }
}

/**
 * @brief 56338 | b0 | Handles a gunship (end) moving up into the screen
 *
 */
void GunshipEndMovingUp(void)
{
    u8 inPosition;
    u16 offset;

    if (gCurrentSprite.work1 != 0)
    {
        if (--gCurrentSprite.work1 == 0)
            SoundPlay_3b1c(0x249);
    }

    inPosition = 0;

    offset = SUB_PIXEL_TO_PIXEL(gCurrentSprite.xPosition) - SUB_PIXEL_TO_PIXEL(gBg1XPosition);
    if (offset < 0x70)
        gCurrentSprite.xPosition++;
    else if (offset > 0x80)
        gCurrentSprite.xPosition--;
    else
        inPosition = 1;

    offset = SUB_PIXEL_TO_PIXEL(gCurrentSprite.yPosition) - SUB_PIXEL_TO_PIXEL(gBg1YPosition);
    if (offset < 0x2C)
        gCurrentSprite.yPosition++;
    else if (offset > 0x3C)
        gCurrentSprite.yPosition--;
    else
        inPosition++;

    if (inPosition > 1)
    {
        gCurrentSprite.bgPriority = 2;
        gCurrentSprite.pose = 0x17;
        gCurrentSprite.work1 = 60;
        gCurrentSprite.work4 = 0;
        gCurrentSprite.work3 = 0;
    }
}

/**
 * @brief 563e8 | 5c | Handles a gunship (end) waiting before entering
 *
 */
void GunshipEndWaitingToEnter(void)
{
    u8 offset;
    s16 movement;

    offset = gCurrentSprite.work4;
    movement = sGunshipEndIdleYMovement[offset];

    if (movement == SHORT_MAX)
    {
        movement = sGunshipEndIdleYMovement[0];
        offset = 0;
    }

    gCurrentSprite.work4 = offset + 1;
    gCurrentSprite.yPosition += movement;

    if (--gCurrentSprite.work1 == 0)
    {
        gCurrentSprite.pose = 0x18;
        gCurrentSprite.work1 = 0;
    }
}

/**
 * @brief 56444 | 158 | Handles a gunship (end) entering the foreground
 *
 */
void GunshipEndEntering(void)
{
    u8 offset;
    s16 movement;
    u8 ramSlot;
    u32 timer;

    offset = gCurrentSprite.work4;
    movement = sGunshipEndIdleYMovement[offset];

    if (movement == SHORT_MAX)
    {
        movement = sGunshipEndIdleYMovement[0];
        offset = 0;
    }

    gCurrentSprite.work4 = offset + 1;
    gCurrentSprite.yPosition += movement;

    // (timer << 24 >> 26) is (u8)timer / 4, written this way to match
    gCurrentSprite.scaling = sGunshipEndEnteringScaling[(timer = gCurrentSprite.work1) << 24 >> 26];

    if ((u8)timer < 0x70)
    {
        gCurrentSprite.work1 = timer + 1;
        if (MOD_AND(timer + 1, 2))
            gCurrentSprite.yPosition++;
        return;
    }

    gCurrentSprite.status &= ~SPRITE_STATUS_ROTATION_SCALING_WHOLE;
    gCurrentSprite.pose = 0x1A;

    gCurrentSprite.pOam = (const struct FrameData*)sGunshipEndOam_Landed;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.work2 = 0;
    gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;

    ramSlot = SpriteSpawnSecondary(SSPRITE_7A, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
    gCurrentSprite.work4 = ramSlot;

    gSpriteData[ramSlot].status &= ~SPRITE_STATUS_NOT_DRAWN;

    gSpriteData[ramSlot].pOam = (const struct FrameData*)sGunshipEndBottomOam_Idle;
    gSpriteData[ramSlot].animationDurationCounter = 0;
    gSpriteData[ramSlot].currentAnimationFrame = 0;

    gSpriteData[ramSlot].properties |= SP_ALWAYS_ACTIVE;
    gSpriteData[ramSlot].drawOrder = 14;
    gSpriteData[ramSlot].samusCollision = SSC_NONE;

    gSpriteData[ramSlot].drawDistanceTop = BLOCK_TO_PIXEL(.25f);
    gSpriteData[ramSlot].drawDistanceBottom = BLOCK_TO_PIXEL(3.5f);
    gSpriteData[ramSlot].drawDistanceHorizontal = BLOCK_TO_PIXEL(3);

    gSpriteData[ramSlot].hitboxTop = -PIXEL_SIZE;
    gSpriteData[ramSlot].hitboxBottom = PIXEL_SIZE;
    gSpriteData[ramSlot].hitboxLeft = -PIXEL_SIZE;
    gSpriteData[ramSlot].hitboxRight = PIXEL_SIZE;

    gSpriteData[ramSlot].pose = SPRITE_POSE_IDLE;
    gSpriteData[ramSlot].work1 = 0;
    gSpriteData[ramSlot].work2 = 0;
    gSpriteData[ramSlot].work3 = 0;
}

/**
 * @brief 5659c | a8 | Handles a gunship (end) waiting for samus to board
 *
 */
void GunshipEndWaitingForSamus(void)
{
    if (gCurrentSprite.work2 < 36)
    {
        gCurrentSprite.work2++;
        GunshipEndSpawnBeams();
        return;
    }

    if (gCurrentSprite.xPosition - HALF_BLOCK_SIZE < gSamusData.xPosition &&
        gCurrentSprite.xPosition + HALF_BLOCK_SIZE > gSamusData.xPosition &&
        gSamusData.yPosition == 0x2BF && !SpriteUtilCheckSamusMorphed())
    {
        if (gSamusData.invincibilityTimer != 0)
            gSamusData.invincibilityTimer = 0;

        SAMUS_SET_POSE(SPOSE_ON_SAVE_PAD);

        gSamusData.yPosition = gCurrentSprite.yPosition + (BLOCK_SIZE * 4 + HALF_BLOCK_SIZE);
        gSamusData.xPosition = gCurrentSprite.xPosition;

        gCurrentSprite.pose = 0x37;
        gCurrentSprite.work1 = 30;
        gCurrentSprite.drawOrder = 4;

        EventCheckAdvance(EVENT_ESCAPED_ON_SHIP);
    }
    else
    {
        gCurrentSprite.drawOrder = 12;
    }
}

/**
 * @brief 56644 | 28 | Handles a gunship (end) locking samus
 *
 */
void GunshipEndLockingSamus(void)
{
    if (--gCurrentSprite.work1 == 0)
    {
        gCurrentSprite.pose = 0x38;
        gCurrentSprite.work1 = 60 - 1;
    }
}

/**
 * @brief 5666c | 3c | Handles a gunship (end) pulling samus up
 *
 */
void GunshipEndMovingSamusUp(void)
{
    if (--gCurrentSprite.work1 == 0)
    {
        gCurrentSprite.pose = 0x39;
        gDisableDrawingSamusAndScrollingFlag = TRUE;
    }
    else
    {
        gSamusData.yPosition -= PIXEL_SIZE;
    }
}

/**
 * @brief 566a8 | 90 | Handles the first part of a gunship (end) starting its engine
 *
 */
void GunshipEndStartingEngine1(void)
{
    u8 ramSlot;
    const u16* pal;

    ramSlot = gCurrentSprite.work4;

    if (!SpriteUtilHasCurrentAnimationEnded())
        return;

    gCurrentSprite.pose = 0x3A;

    gCurrentSprite.pOam = (const struct FrameData*)sGunshipEndOam_Flying;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.work1 = 60;
    gCurrentSprite.work2 = 0;
    gCurrentSprite.work4 = 0;

    gCurrentSprite.status |= SPRITE_STATUS_ROTATION_SCALING_WHOLE;
    gCurrentSprite.scaling = Q_8_8(1.f);
    gCurrentSprite.rotation = 0;

    gSpriteData[ramSlot].status = 0;

    pal = &sGunshipFlashingPal[11];
    DMA3_COPY_16(pal, PALRAM_OBJ + 0x136, 5);
    SoundPlay_3b1c(0x24A);
}

/**
 * @brief 56738 | cc | Handles the second part of a gunship (end) starting its engine
 *
 */
void GunshipEndStartingEngine2(void)
{
    u8 offset;
    s16 movement;

    offset = gCurrentSprite.work4;
    movement = sGunshipEndEngineYMovement[offset];

    if (movement == SHORT_MAX)
    {
        movement = sGunshipEndEngineYMovement[0];
        offset = 0;
    }

    gCurrentSprite.work4 = offset + 1;
    gCurrentSprite.yPosition += movement;

    if (gCurrentSprite.work2 == 0)
    {
        if (--gCurrentSprite.work1 == 0)
        {
            gCurrentSprite.pOam = (const struct FrameData*)sGunshipEndOam_StartingEngine;
            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;

            gCurrentSprite.work1 = 60;
            gCurrentSprite.work2 = 1;
        }
    }
    else if (gCurrentSprite.work2 == 1)
    {
        if (--gCurrentSprite.work1 == 0)
        {
            gCurrentSprite.pOam = (const struct FrameData*)sGunshipEndOam_TakingOff;
            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;

            gCurrentSprite.work1 = 90;
            gCurrentSprite.work2 = 2;
        }
    }
    else
    {
        if (--gCurrentSprite.work1 == 0)
        {
            gCurrentSprite.pose = 0x3B;
            gCurrentSprite.work1 = 0;
            gCurrentSprite.work2 = 0;
            gCurrentSprite.work3 = 0;
            gCurrentSprite.status |= SPRITE_STATUS_DOUBLE_SIZE;
        }
    }
}

/**
 * @brief 56804 | 94 | Handles a gunship (end) taking off
 *
 */
void GunshipEndTakingOff(void)
{
    u8 offset;

    if (gCurrentSprite.work1 >= 0x40)
    {
        gCurrentSprite.yPosition -= EIGHTH_BLOCK_SIZE;
        gCurrentSprite.pose = 0x3C;
        ColorFadingStartFinalEscape();
    }
    else if (gCurrentSprite.work1 >= 0x38)
    {
        gCurrentSprite.yPosition -= EIGHTH_BLOCK_SIZE;
        gCurrentSprite.work1 += 4;
    }
    else if (gCurrentSprite.work1 >= 0x30)
    {
        gCurrentSprite.yPosition -= PIXEL_SIZE / 2;
        gCurrentSprite.work1 += 4;
    }
    else if (gCurrentSprite.work1 >= 0x20)
    {
        gCurrentSprite.yPosition -= ONE_SUB_PIXEL;
        gCurrentSprite.work1 += 2;
    }
    else
    {
        gCurrentSprite.work1++;
    }

    gCurrentSprite.scaling = sGunshipEndTakingOffScaling[gCurrentSprite.work1];

    if (gCurrentSprite.work1 >= 0x20)
    {
        offset = (gCurrentSprite.work1 - 0x20) >> 2;
        gCurrentSprite.rotation = sGunshipEndTakingOffRotation[offset];
    }
}

/**
 * @brief 56898 | 4 | Handles a gunship (end) being done
 *
 */
void GunshipEndDone(void)
{
    return;
}

/**
 * @brief 5689c | 74 | Handles the bottom of a gunship (end) being idle (flashing palette)
 *
 */
void GunshipEndBottomIdle(void)
{
    u32 offset;
    const u16* pal;

    gCurrentSprite.work3++;

    if (MOD_AND(gCurrentSprite.work3, 8) != 0)
        return;

    offset = gCurrentSprite.work1 * 16;
    pal = &sGunshipFlashingPal[offset + 11];
    DMA3_COPY_16(pal, PALRAM_OBJ + 0x136, 5);

    if (gCurrentSprite.work2 != 0)
    {
        if (gCurrentSprite.work1 != 0)
        {
            gCurrentSprite.work1--;
        }
        else
        {
            gCurrentSprite.work2 = 0;
            gCurrentSprite.work1 = 1;
        }
    }
    else
    {
        if (gCurrentSprite.work1 > 5)
        {
            gCurrentSprite.work2 = 1;
            gCurrentSprite.work1 = 5;
        }
        else
        {
            gCurrentSprite.work1++;
        }
    }
}

/**
 * @brief 56910 | 74 | Initializes a gunship (end) beam
 *
 */
void GunshipEndBeamInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;

    gCurrentSprite.samusCollision = SSC_NONE;

    gCurrentSprite.drawDistanceTop = BLOCK_TO_PIXEL(.25f);
    gCurrentSprite.drawDistanceBottom = BLOCK_TO_PIXEL(.25f);
    gCurrentSprite.drawDistanceHorizontal = BLOCK_TO_PIXEL(1);

    gCurrentSprite.hitboxTop = -PIXEL_SIZE;
    gCurrentSprite.hitboxBottom = PIXEL_SIZE;
    gCurrentSprite.hitboxLeft = -PIXEL_SIZE;
    gCurrentSprite.hitboxRight = PIXEL_SIZE;

    gCurrentSprite.pOam = (const struct FrameData*)sGunshipEndBeamOam_Idle;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.pose = SPRITE_POSE_IDLE;
    gCurrentSprite.drawOrder = 13;
    gCurrentSprite.work1 = 9;
}

/**
 * @brief 56984 | 70 | Handles a gunship (end) beam moving down
 *
 */
void GunshipEndBeamMovingDown(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    if (gCurrentSprite.roomSlot != 0)
    {
        gCurrentSprite.roomSlot--;
        gCurrentSprite.yPosition += PIXEL_SIZE;
        return;
    }

    if (--gCurrentSprite.work1 != 0)
    {
        gCurrentSprite.yPosition += PIXEL_SIZE;
    }
    else
    {
        gCurrentSprite.yPosition -= HALF_BLOCK_SIZE;
        gCurrentSprite.work1 = 9;
    }

    if (gSpriteData[ramSlot].pose == 0x37)
    {
        gCurrentSprite.pose = 0x18;
        gCurrentSprite.drawOrder = 5;
    }
}

/**
 * @brief 569f4 | 54 | Handles a gunship (end) beam moving up
 *
 */
void GunshipEndBeamMovingUp(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    gCurrentSprite.work1++;

    if (gCurrentSprite.work1 > 8)
    {
        gCurrentSprite.work1 = 0;
        gCurrentSprite.yPosition += HALF_BLOCK_SIZE;
    }
    else
    {
        gCurrentSprite.yPosition -= PIXEL_SIZE;
    }

    if (gSpriteData[ramSlot].pose == 0x39)
        gCurrentSprite.status = 0;
}

/**
 * @brief 56a48 | 168 | Gunship (end) AI
 *
 */
void GunshipEnd(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            GunshipEndInit();
            break;

        case SPRITE_POSE_IDLE_INIT:
            GunshipEndWaiting();
            break;

        case SPRITE_POSE_IDLE:
            GunshipEndMovingUp();
            break;

        case 0x17:
            GunshipEndWaitingToEnter();
            break;

        case 0x18:
            GunshipEndEntering();
            break;

        case 0x1A:
            GunshipEndWaitingForSamus();
            break;

        case 0x37:
            GunshipEndLockingSamus();
            break;

        case 0x38:
            GunshipEndMovingSamusUp();
            break;

        case 0x39:
            GunshipEndStartingEngine1();
            break;

        case 0x3A:
            GunshipEndStartingEngine2();
            break;

        case 0x3B:
            GunshipEndTakingOff();
            break;

        case 0x3C:
            GunshipEndDone();
            break;
    }
}

/**
 * @brief 56bb0 | 20 | Gunship (end) bottom AI
 *
 */
void GunshipEndBottom(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (gCurrentSprite.pose == SPRITE_POSE_IDLE)
        GunshipEndBottomIdle();
}

/**
 * @brief 56bd0 | 54 | Gunship (end) beam AI
 *
 */
void GunshipEndBeam(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case SPRITE_POSE_UNINITIALIZED:
            GunshipEndBeamInit();

        case SPRITE_POSE_IDLE:
            GunshipEndBeamMovingDown();
            break;

        case 0x18:
            GunshipEndBeamMovingUp();
            break;
    }

    if (gCurrentSprite.roomSlot == 0 && gCurrentSprite.status == 0)
        SoundStop(0xFD);
}
