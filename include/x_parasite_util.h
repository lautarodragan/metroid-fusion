#ifndef X_PARASITE_UTIL_H
#define X_PARASITE_UTIL_H

#include "types.h"

// X parasite work variables
#define X_PARASITE_MOSAIC_IDX workY // Appearing (and forming a sprite or a core X)
#define X_PARASITE_TIMER workY // Idle and flying, it flies away at 0
#define X_PARASITE_TARGET_Y workY // Waiting for enough X to form the sprite
#define X_PARASITE_TARGET_X workX
#define X_PARASITE_TARGET_SLOT work2 // Ram slot of the sprite the X is forming
#define X_PARASITE_WAITING_MOSAIC_IDX work1 // Waiting for enough X to form the sprite
#define X_PARASITE_MOVEMENT_STAGE workX // Incremented (mod 4) when changing X direction in XParasiteMove, offsets the target
#define X_PARASITE_X_MOVEMENT_IDX work3 // Idle floating
#define X_PARASITE_Y_MOVEMENT_IDX work4
#define X_PARASITE_X_SPEED work3 // Flying away
#define X_PARASITE_Y_SPEED work4

enum XParasiteType {
    X_PARASITE_TYPE_IN_ROOM,
    X_PARASITE_TYPE_FROM_SPRITE,
    X_PARASITE_TYPE_FROM_CORE_X
};

enum XParasiteFlyingStage {
    X_PARASITE_FLYING_STAGE_FREE_FLOATING,
    X_PARASITE_FLYING_STAGE_FLYING_TO_SPRITE,
    X_PARASITE_FLYING_STAGE_TOUCHED_SPRITE
};

u32 CheckSpritesThatCantAbsorbX(void);
s32 CountPrimarySpritesThatCantAbsorbX(void);
void XParasiteMove(u16 dstY, u16 dstX, u8 ySpeedCap, u8 xSpeedCap, u8 speedDivisor);
void XParasiteMoveWithSound(u16 dstY, u16 dstX, u8 ySpeedCap, u8 xSpeedCap, u8 speedDivisor, u16 sound);
void SamusAbsorbX(void);
void XParasiteGettingAbsorbedInit(void);
void SpriteDyingInit(void);
void SpriteDying(void);
void XParasiteSpawningInit(void);
void XParasiteDetermineColor(u8 unk, u8 spriteId);
void XParasiteInit(void);
void XParasiteFlyingInit(void);
void XParasiteIdleFloating(void);
void XParasiteFlying(void);
void XParasiteGettingAbsorbed(void);
u8 XParasiteFlyingMovement(void);
void XParasiteFlyingAway(void);
void XParasiteWaitingForEnoughXToFormInit(void);
void XParasiteWaitingForEnoughXToForm(void);
void XParasiteFormingInit(void);
void XParasiteForming(void);
void SpriteSpawningFromX(void);
void XParasiteMoveTowardsSamus_Unused(void);
void XParasiteStickToSamus(void);

#endif /* X_PARASITE_UTIL_H */
