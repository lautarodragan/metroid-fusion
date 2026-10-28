#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

#include "types.h"
#include "constants/sprite.h"

#define GET_PSPRITE_HEALTH(id) sPrimarySpriteStats[(id)][0]
#define GET_SSPRITE_HEALTH(id) sSecondarySpriteStats[(id)][0]

#define GET_PSPRITE_DAMAGE(id) sPrimarySpriteStats[(id)][1]
#define GET_SSPRITE_DAMAGE(id) sSecondarySpriteStats[(id)][1]

#define GET_PSPRITE_SUIT_REDUCTION(id) sPrimarySpriteStats[(id)][2]
#define GET_SSPRITE_SUIT_REDUCTION(id) sSecondarySpriteStats[(id)][2]

#define GET_PSPRITE_WEAKNESS(id) sPrimarySpriteStats[(id)][3]
#define GET_SSPRITE_WEAKNESS(id) sSecondarySpriteStats[(id)][3]

#define SPRITE_GFX_SIZE(nbrRows) ((nbrRows) * 32 * 256 / 4)

extern const u8 sOamXFlipOffsets[3][4];
extern const u8 sOamYFlipOffsets[3][4];

extern const u8 sRandomNumberTable[32];
extern const u16 sSuitDamageReductionPercent[SDRT_END][SDR_END];

extern const s16 sSpritesFallingSpeedHovering[20];
extern const s16 sSpritesFallingSpeedMissileHatchDebris[16];
extern const s16 sSpritesFallingSpeed_2e499c[18];
extern const s16 sSpritesFallingSpeedCeiling[16];
extern const s16 sSpritesFallingSpeed[16];
extern const s16 sSpritesFallingSpeedQuickAcceleration[8];
extern const s16 sSpritesFallingSpeedSlow[16];
extern const s16 sSpritesFallingSpeedFast[16];

extern const u32 sSpritesGraphicsLength[PSPRITE_END - 0x10];

extern const u16 sPrimarySpriteStats[PSPRITE_END][7];
extern const u16 sSecondarySpriteStats[SSPRITE_END][4];

extern const u8 sSpriteset0[];
extern const u8 sSpriteset1[];
extern const u8 sSpriteset2[];
extern const u8 sSpriteset3[];
extern const u8 sSpriteset4[];
extern const u8 sSpriteset5[];
extern const u8 sSpriteset6[];
extern const u8 sSpriteset7[];
extern const u8 sSpriteset8[];
extern const u8 sSpriteset9[];
extern const u8 sSpriteset10[];
extern const u8 sSpriteset11[];
extern const u8 sSpriteset12[];
extern const u8 sSpriteset13[];
extern const u8 sSpriteset14[];
extern const u8 sSpriteset15[];
extern const u8 sSpriteset16[];
extern const u8 sSpriteset17[];
extern const u8 sSpriteset18[];
extern const u8 sSpriteset19[];
extern const u8 sSpriteset20[];
extern const u8 sSpriteset21[];
extern const u8 sSpriteset22[];
extern const u8 sSpriteset23[];
extern const u8 sSpriteset24[];
extern const u8 sSpriteset25[];
extern const u8 sSpriteset26[];
extern const u8 sSpriteset27[];
extern const u8 sSpriteset28[];
extern const u8 sSpriteset29[];
extern const u8 sSpriteset30[];
extern const u8 sSpriteset31[];
extern const u8 sSpriteset32[];
extern const u8 sSpriteset33[];
extern const u8 sSpriteset34[];
extern const u8 sSpriteset35[];
extern const u8 sSpriteset36[];
extern const u8 sSpriteset37[];
extern const u8 sSpriteset38[];
extern const u8 sSpriteset39[];
extern const u8 sSpriteset40[];
extern const u8 sSpriteset41[];
extern const u8 sSpriteset42[];
extern const u8 sSpriteset43[];
extern const u8 sSpriteset44[];
extern const u8 sSpriteset45[];
extern const u8 sSpriteset46[];
extern const u8 sSpriteset47[];
extern const u8 sSpriteset48[];
extern const u8 sSpriteset49[];
extern const u8 sSpriteset50[];
extern const u8 sSpriteset51[];
extern const u8 sSpriteset52[];
extern const u8 sSpriteset53[];
extern const u8 sSpriteset54[];
extern const u8 sSpriteset55[];
extern const u8 sSpriteset56[];
extern const u8 sSpriteset57[];
extern const u8 sSpriteset58[];
extern const u8 sSpriteset59[];
extern const u8 sSpriteset60[];
extern const u8 sSpriteset61[];
extern const u8 sSpriteset62[];
extern const u8 sSpriteset63[];
extern const u8 sSpriteset64[];
extern const u8 sSpriteset65[];
extern const u8 sSpriteset66[];
extern const u8 sSpriteset67[];
extern const u8 sSpriteset68[];
extern const u8 sSpriteset69[];
extern const u8 sSpriteset70[];
extern const u8 sSpriteset71[];
extern const u8 sSpriteset72[];
extern const u8 sSpriteset73[];
extern const u8 sSpriteset74[];
extern const u8 sSpriteset75[];
extern const u8 sSpriteset76[];
extern const u8 sSpriteset77[];
extern const u8 sSpriteset78[];
extern const u8 sSpriteset79[];
extern const u8 sSpriteset80[];
extern const u8 sSpriteset81[];
extern const u8 sSpriteset82[];
extern const u8 sSpriteset83[];
extern const u8 sSpriteset84[];
extern const u8 sSpriteset85[];
extern const u8 sSpriteset86[];
extern const u8 sSpriteset87[];
extern const u8 sSpriteset88[];
extern const u8 sSpriteset89[];
extern const u8 sSpriteset90[];
extern const u8 sSpriteset91[];
extern const u8 sSpriteset92[];
extern const u8 sSpriteset93[];
extern const u8 sSpriteset94[];
extern const u8 sSpriteset95[];
extern const u8 sSpriteset96[];
extern const u8 sSpriteset97[];
extern const u8 sSpriteset98[];
extern const u8 sSpriteset99[];
extern const u8 sSpriteset100[];
extern const u8 sSpriteset101[];
extern const u8 sSpriteset102[];
extern const u8 sSpriteset103[];
extern const u8 sSpriteset104[];
extern const u8 sSpriteset105[];
extern const u8 sSpriteset106[];
extern const u8 sSpriteset107[];
extern const u8 sSpriteset108[];
extern const u8 sSpriteset109[];
extern const u8 sSpriteset110[];
extern const u8 sSpriteset111[];
extern const u8 sSpriteset112[];
extern const u8 sSpriteset113[];
extern const u8 sSpriteset114[];
extern const u8 sSpriteset115[];
extern const u8 sSpriteset116[];
extern const u8 sSpriteset117[];
extern const u8 sSpriteset118[];
extern const u8 sSpriteset119[];
extern const u8 sSpriteset120[];
extern const u8 sSpriteset121[];
extern const u8 sSpriteset122[];
extern const u8 sSpriteset123[];
extern const u8 sSpriteset124[];
extern const u8 sSpriteset125[];
extern const u8 sSpriteset126[];
extern const u8 sSpriteset127[];
extern const u8 sSpriteset128[];
extern const u8 sSpriteset129[];

#endif /* SPRITE_DATA_H */
