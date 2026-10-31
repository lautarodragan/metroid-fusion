#ifndef CUTSCENE_STRUCT_H
#define CUTSCENE_STRUCT_H

#include "types.h"

struct SpecialCutsceneOam {
    s16 spawnX;
    s16 spawnY;
    // unk_4, unk_8 and unk_A are work variables whose meaning depends on the object type: unk_A is usually
    // a movement or animation timer, unk_8 a duration, velocity or palette frame, unk_4 a target position
    s16 unk_4;                     // 0x4
    s16 scaling;                   // 0x6
    s16 unk_8;                     // 0x8
    u16 unk_A;                     // 0xA
    s16 xPosition;                // 0xC
    s16 yPosition;                // 0xE
    u8 type;                       // 0x10
    u8 currentAnimationFrame;      // 0x11
    u8 animationDurationCounter;   // 0x12
    u8 timer;                      // 0x13
    u8 stage;                      // 0x14
    u8 rotation;
    u8 unk_16;
    u8 unk_17;
    u32 exists : 1;                // 0x18, drawn
    u32 affineMode : 2;
    u32 objMode : 2;
    u32 mosaic : 1;
    u32 xFlip : 1;
    u32 yFlip : 1;
    u32 tileOffset : 10;           // 0x19
    u32 priority : 2;              // 0x1A
    u32 paletteOffset : 4;
    u8 unk_1B;
    const struct FrameData* pOam;  // 0x1C
    void* pFunction;               // 0x20
};

#endif /* CUTSCENE_STRUCT_H */
