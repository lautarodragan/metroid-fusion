#ifndef CLIPDATA_STRUCT_H
#define CLIPDATA_STRUCT_H

#include "types.h"

#include "constants/clipdata.h"

struct CollisionData {
    u32 type;
    s32 subPixelX;
    s32 subPixelY;
    UNUSED(8);
    s32 actor;
    u16 tileX;
    u16 tileY;
};

ASSERT_OFFSET(struct CollisionData, actor, 0x14);
ASSERT_SIZE(struct CollisionData, 0x1C);

struct TilemapAndClipPointers {
    u16* pTilemap;
    const u8* pClipCollisions;
    const u16* pClipBehaviors;
};

struct CurrentAffectingClipdata {
    u16 movement;
    u16 hazard;
};


typedef u32 (*CollisionFunc_T)(struct CollisionData*);

extern CollisionFunc_T gClipdataCodePointer;
extern struct CurrentAffectingClipdata gCurrentAffectingClipdata;
extern struct TilemapAndClipPointers gTilemapAndClipPointers;
extern u8 gLastElevatorUsed;
extern u8 gElevatorDirection;
extern u8 gCurrentClipdataAffectingAction;
// Unused feature: shows the hidden breakable blocks on screen in BG1, see ClipdataUpdateBlockReveal
// [0] = stage (0 = inactive, 0x80 = restore BG1), [1] = current row
extern u8 gBlockReveal[2];

#endif /* CLIPDATA_STRUCT_H */
