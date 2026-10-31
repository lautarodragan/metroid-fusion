#ifndef SA_X_STRUCTS_H
#define SA_X_STRUCTS_H

#include "types.h"
#include "oam.h"

struct SaXData {
    u8 screenFlag;
    u8 pose;
    u8 turning;
    u8 diagonalAim;
    u8 missilesArmed;
    u8 paletteRow;
    u8 mosaic;
    u16 direction;
    u16 xPosition;
    u16 yPosition;
    s16 xVelocity;
    s16 yVelocity;
    u8 animationDurationCounter;
    u8 currentAnimationFrame;
    const u8* pTopGfx;
    const u8* pBottomGfx;
    u16 topGfxLength;
    u16 bottomGfxLength;
    const u16* pOamFrame;
};

struct SaXVision {
    u8 diagonalAim;
    u8 detectedSamusOnRight;
    u8 inYRange;
    u8 samusBelow;
    u8 samusOnRight;
    u8 inXRange;
};

ASSERT_SIZE(struct SaXVision, 0x8);

struct SaXAnimationData {
    const u8* pGraphics;
    const u16* pOamFrame;
    u8 timer;
};

struct SaXElevatorSprite {
    u8 status; // 0 = inactive, 1 = waiting for delayTimer, 2+ = active (updated and drawn)
    u8 type;
    u8 delayTimer;
    u16 xPosition;
    u16 yPosition;
    s16 xVelocity;
    s16 yVelocity;
    u8 animationDurationCounter;
    u8 currentAnimationFrame;
    const u16* pOamFrame;
};

struct SaXElevatorData {
    u8 active;
    u8 cutsceneId; // Index in sSaXElevatorFunctionPointers
    u8 stage;
    u8 unk_3;
    u8 effect; // Background/blending effect (1 = fade to white, 2 = fade back and scroll, 3 = fade out bg0/bg3 and scroll)
    u8 effectTimer;
    u16 timer;
};

typedef u8 (*SaXGfxFunc_T)(void);
typedef u8 (*SaXElevatorFunc_T)(void);

#define MAX_AMOUNT_OF_SA_X_ELEVATOR_SPRITES 11

extern struct SaXData gSaXData;
extern struct SaXVision gSaXVision;
extern struct RawCoordsX gSaXSpawnPosition;
extern struct SaXElevatorData gSaXElevatorData;
extern u16 gSaXElevatorBgCnt[4];
extern struct SaXElevatorSprite gSaXElevatorSprites[MAX_AMOUNT_OF_SA_X_ELEVATOR_SPRITES];
extern u16 gSaXPalette[2 * 16];

#endif /* SA_X_STRUCTS_H */
