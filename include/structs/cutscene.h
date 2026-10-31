#ifndef CUTSCENE_STRUCT_H
#define CUTSCENE_STRUCT_H

#include "types.h"

struct SpecialCutsceneOam {
    s16 spawnX;
    s16 spawnY;
    s16 unk_4;
    s16 scaling;
    s16 unk_8;
    u16 unk_A;
    s16 xPosition;                // 0xC
    s16 yPosition;                // 0xE
    u8 type;                       // 0x10
    u8 currentAnimationFrame;      // 0x11
    u8 animationDurationCounter;   // 0x12
    u8 timer;                      // 0x13
    u8 stage;                      // 0x14
    u8 rotation;
    UNUSED(2);
    u32 exists : 1;                // 0x18, drawn
    u32 affineMode : 2;
    u32 objMode : 2;
    u32 mosaic : 1;
    u32 xFlip : 1;
    u32 yFlip : 1;
    u32 tileOffset : 10;           // 0x19
    u32 priority : 2;              // 0x1A
    u32 paletteOffset : 4;
    const struct FrameData* pOam;  // 0x1C
    void* pFunction;               // 0x20
};

ASSERT_OFFSET(struct SpecialCutsceneOam, pOam, 0x1C);
ASSERT_SIZE(struct SpecialCutsceneOam, 0x24);

#endif /* CUTSCENE_STRUCT_H */
