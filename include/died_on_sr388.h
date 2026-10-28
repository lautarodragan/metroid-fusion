#ifndef DIED_ON_SR388_H
#define DIED_ON_SR388_H

#include "types.h"

#include "structs/cutscene.h"

extern const u8 sSr388CollisionUnk_6238f4[];
extern const u8 sSr388CollisionUnk_62b5f4[];
extern const struct FrameData sSr388CollisionUnk_636020[];
extern const struct FrameData sSr388CollisionUnk_636038[];
extern const struct FrameData sSr388CollisionUnk_636050[];
extern const struct FrameData sSr388CollisionUnk_6362b8[];
extern const u16 sSr388CollisionUnk_636a38[];
extern const u16 sSr388CollisionUnk_636c38[];
extern const u16 sSr388CollisionUnk_637038[];
extern const u8 sSr388CollisionUnk_638c14[];
extern const u8 sSr388CollisionUnk_639bc4[];

boolu32 DiedFromSr388CollisionHandler(void);
void DiedOnSr388CollisionInit(void);
boolu32 DiedOnSr388CollisionProcess(void);
boolu32 DiedOnSr388Collision(void);
void DiedOnSr388CollisionProcessFallingBsl(struct SpecialCutsceneOam* pOam);
void unk_979d0(struct SpecialCutsceneOam* pOam);
u8 DiedOnSr388CollisionSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearch);
void DiedOnSr388CollisionVblank(void);
void DiedOnSr388CollisionVblank_Unused(void);
u8 DiedOnSr388CollisionGetPositionAndSlotOfOamByType(u8 type, s16* pXPosition, s16* pYPosition);
void unk_97dcc(void);

#endif /* DIED_ON_SR388_H */
