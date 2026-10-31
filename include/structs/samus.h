#ifndef SAMUS_STRUCTS_H
#define SAMUS_STRUCTS_H

#include "types.h"
#include "oam.h"

struct SamusData {
    u8 unk_0;
    u8 pose;
    u8 turning;
    u8 forcedMovement;
    u8 walljumpTimer;
    u8 invincibilityTimer;
    u8 speedboostingCounter;
    u8 armCannonDirection;
    u8 weaponHighlighted;
    u8 newProjectile;
    u8 cooldownTimer;
    u8 unk_B;
    u8 chargeBeamCounter;
    u8 diagonalAim;
    u8 armRunningFlag;
    u8 counter;
    u16 lastWallTouchedMidAir;
    u16 direction;
    u16 elevatorOrClimbingDirection;
    u16 xPosition;
    u16 yPosition;
    s16 xVelocity;
    s16 yVelocity;
    u16 slopeType;
    u8 standingStatus;
    u8 animationDurationCounter;
    u8 currentAnimationFrame;
    u8 shooting;
    s16 drawDistanceLeft;
    s16 drawDistanceTop;
    s16 drawDistanceRight;
    s16 drawDistanceBottom;
};

struct Equipment {
    u16 currentEnergy;
    u16 maxEnergy;
    u16 currentMissiles;
    u16 maxMissiles;
    u8 currentPowerBombs;
    u8 maxPowerBombs;
    u8 beamStatus;
    u8 weaponsStatus;
    u8 suitMiscStatus;
    u8 securityHatchLevel;
    u8 downloadedMaps;
    u8 lowHealth;
};

struct SamusGraphicsInfo {
    const u16* pSamusOamFrame;

    const u8* pBodyTopHalfGfx;
    u16 bodyTopHalfGfxLength;

    const u8* pBodyBottomHalfGfx;
    u16 bodyBottomHalfGfxLength;

    const u8* pLegsTopHalfGfx;
    u16 legsTopHalfGfxLength;

    const u8* pLegsBottomHalfGfx;
    u16 legsBottomHalfGfxLength;

    u16 armCannonXOffset;
    u16 armCannonYOffset;
    u16 armCannonDrawFlags; // ARM_CANNON_DRAW_*, same format as the first halfword of an OAM frame

    const u16* pArmCannonOamFrame;

    const u8* pArmCannonTopHalfGfx;
    u16 armCannonTopHalfGfxLength;

    const u8* pArmCannonBottomHalfGfx;
    u16 armCannonBottomHalfGfxLength;
};

struct SamusAnimationInfo {
    u8 loadingSave;
    u8 paletteAnimationCounter;
    u8 currentPaletteRow;
    u8 spaceJumpSpinCounter;
    u8 shinesparkTimer;
    u8 unk_6[7];
};

struct SamusPhysics {
    u8 slowed;
    s16 yAcceleration;
    s16 yVelocityCap;
    s16 midAirXAcceleration;
    s16 midAirXVelocityCap;
    s16 midAirMorphedXVelocityCap;
    s16 xAcceleration;
    s16 xVelocityCap;
};

struct SamusEnvironmentalEffect {
    u8 effect;
    u8 animationDurationCounter;
    u8 currentAnimationFrame;
    u8 externalTimer;
    u8 timer1;
    u8 timer2;
    u8 effectStarted; // Incremented when a new effect starts this frame
    u16 xPosition;
    u16 yPosition;
    const u16* pOamFrame;
};

struct SamusCollisionData {
    u16 horizontalMovingDirection;
    u16 verticalMovingDirection;
    u8 forwardSide; // SAMUS_HITBOX_LEFT/RIGHT, side Samus is moving/facing towards
    u8 backwardSide; // SAMUS_HITBOX_LEFT/RIGHT, opposite of forwardSide
    s16 forwardWallAlignOffset; // Offset added to a block position to align Samus against a wall on the forward side
    u8 standingStatus;
    u8 collisionType;
    u8 aboveCollisionType; // Index in sSamusCollisionOffsetsAbove
    u8 secondaryCollisionType; // Always the same as collisionType
    u8 touchingSideBlock;
    u8 touchingTopBlock;
    u8 unk_E;
};

struct SamusEcho {
    u8 active;
    u8 timer;
    u8 position;
    u8 unk_4[9];
};

struct SamusAnimData {
    const u8* pTopGfx;
    const u8* pBottomGfx;
    const u16* pOam;
    u8 timer;
};

struct ArmCannonAnimData {
    const s16* pOffset;
    const u16* pOam;
};

extern struct SamusData gSamusData;
extern struct SamusData gSamusDataCopy;
extern struct SamusGraphicsInfo gSamusGraphicsInfo;
extern struct SamusAnimationInfo gSamusAnimationInfo;
extern struct SamusEnvironmentalEffect gSamusEnvironmentalEffects[2];
extern struct Equipment gEquipment;
extern struct SamusCollisionData gSamusCollisionData;
extern struct SamusPhysics gSamusPhysics;
extern struct SamusEcho gSamusEcho;

extern u16 gSamusPalette[3 * 16];
extern u16 gSamusPaletteLength;

extern u8 gPreviousSamusField0;
extern u16 gPreviousXPosition;
extern u16 gPreviousYPosition;
extern u8 gPoseLock;
extern u8 gSamusUnderwaterFlag;
extern u16 gPreventMovementTimer;
extern u8 gDisableDrawingSamusAndScrollingFlag;
extern s16 gPreviousPositionCounter;

extern u8 gSamusUseYVelocityForX;
extern s8 gSamusSkipCollisionAbove; // Skips the collision check above Samus when jumping, never set
extern s8 gPrevious64PositionsFilled; // Set once gPrevious64Positions has been filled, allows drawing the echoes from older positions
extern u8 gSamusDoorExitVelocityLock; // Set when exiting a door: timer (low bits) and 0x80/0x40 (prevent moving left/right, back into the door)

extern u16 gPrevious64Positions[2][64];

#endif /* SAMUS_STRUCTS_H */
