#ifndef CUTSCENE_DATA_STRUCT_H
#define CUTSCENE_DATA_STRUCT_H

#include "types.h"
#include "oam.h"

struct CutsceneOam;

typedef void (*CutsceneOamFunc_T)(struct CutsceneOam*);

struct CutsceneOam {
    s16 xPosition;                  // 0x0
    s16 yPosition;                  // 0x2
    s16 scaling;                    // 0x4
    s16 unk_6;                      // 0x6
    s16 unk_8;                      // 0x8
    s16 unk_A;                      // 0xA
    s16 unk_C;                      // 0xC
    u16 timer;                      // 0xE
    u8 type;                        // 0x10
    u8 currentAnimationFrame;       // 0x11
    u8 animationDurationCounter;    // 0x12
    u8 unk_13;                      // 0x13
    u8 stage;                       // 0x14
    u8 rotation;                    // 0x15
    u8 exists:1;                    // 0x16
    u8 drawMode:2;
    u8 objMode:2;
    u8 unk_16_5:1;
    u8 xFlip:1;
    u8 yFlip:1;
    u16 tileOffset:10;              // 0x17 (straddles 0x17 and 0x18)
    u16 priority:2;                 // 0x18
    u16 paletteOffset:4;
    u8 unk_19;
    u8 unk_1A;
    u8 unk_1B;
    const struct FrameData* pOam;   // 0x1C
    CutsceneOamFunc_T pFunction;    // 0x20
};

struct CutsceneData {
    u16 stage;                      // 0x0
    u8 unk_2[6];
    u16 timer;                      // 0x8
    s16 paletteUpdate;              // 0xA, the V-blank copies frame paletteFrame of the BG fade palette when set to 1
    s16 paletteFrame;               // 0xC
    s16 unk_E;                      // 0xE
    // CutsceneComputeCircleWindow (unused) uses 0xA as the radius, 0xC and 0xE as the X and Y position of the circle
    u8 subStage;                    // 0x10
    u8 animatedPaletteTimer;        // 0x11
    u8 activeOamCount;              // 0x12
    u8 unk_13[5];
    struct CutsceneOam oam[16];     // 0x18
};

struct CutsceneMonologueOam;

typedef void (*CutsceneMonologueOamFunc_T)(struct CutsceneMonologueOam*);

struct CutsceneMonologueOam {
    s16 xPosition;                  // 0x0
    s16 yPosition;                  // 0x2
    u8 type;                        // 0x4
    u8 exists;                      // 0x5
    u8 currentAnimationFrame;       // 0x6
    u8 animationDurationCounter;    // 0x7
    u8 unk_8;                       // 0x8
    u8 stage;                       // 0x9
    u8 objMode;                     // 0xA
    u8 priority;                    // 0xB
    u8 xFlip;                       // 0xC
    u8 paletteOffset;               // 0xD
    u16 tileOffset;                 // 0xE
    const struct FrameData* pOam;   // 0x10
    CutsceneMonologueOamFunc_T pFunction; // 0x14
};

#define CUTSCENE_MONOLOGUE_LINE_LENGTH 28

struct CutsceneMonologueData {
    u16 currentColumn;              // 0x0
    u16 currentLine;                // 0x2
    u16 fadeColumn;                 // 0x4
    u16 fadeLine;                   // 0x6
    u16 stage;                      // 0x8
    u16 monologueId;                // 0xA
    const u16* pText;               // 0xC
    u16 timer;                      // 0x10
    u16 bg2YPosition;               // 0x12
    u16 bg1YPosition;               // 0x14
    u8 fadeTimer;                   // 0x16, delay between the screen fade steps
    u8 textUpdateState;             // 0x17, 1: draw the next character, 100: idle
    u8 indent;                      // 0x18
    u8 unk_19[3];
    u8 tilesFadeStage[9][CUTSCENE_MONOLOGUE_LINE_LENGTH];  // 0x1C
    u8 tilesFadeTimer[9][CUTSCENE_MONOLOGUE_LINE_LENGTH];  // 0x118
    struct CutsceneMonologueOam oam[5]; // 0x214
};

#define CUTSCENE_DATA (*(struct CutsceneData*)&gNonGameplayRam)
// Next free OAM affine matrix (0-31, bits 3-4 go in the xFlip/yFlip bits of the OAM entry), reset after drawing.
// Accessed through its literal address in CutsceneDrawAllOam (needed to match)
#define NEXT_OAM_MATRIX_SLOT_RAW (*(u8*)0x03001238)

// Same IWRAM byte as NEXT_OAM_MATRIX_SLOT_RAW, through its linker symbol
extern u8 gNextOamMatrixSlot;

#define CUTSCENE_MONOLOGUE_DATA gNonGameplayRam.cutsceneMonologue

#endif /* CUTSCENE_DATA_STRUCT_H */
