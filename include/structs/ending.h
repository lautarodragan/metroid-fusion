#ifndef ENDING_STRUCT_H
#define ENDING_STRUCT_H

#include "types.h"

#include "constants/ending.h"

struct CreditsEntry {
    CreditLineType type;
    u8 text[35];
};

// Per-part meanings of the EndingData overlay fields
// Credits: tile rows scrolled
#define ENDING_CREDITS_ROWS_SCROLLED unk_2
// Samus posing/transforming: the alpha blending is fading (one step every 3 frames, see ENDING_FADE_TIMER)
#define ENDING_BLEND_FADING unk_2
// Ending image: the backgrounds are scrolling up
#define ENDING_IMAGE_SCROLLING unk_2
// Credits/Samus posing: delay counter of the BLDY fade in and the alpha blending fade
#define ENDING_FADE_TIMER unk_97
// Ending image: the letters of the text OAM are spawning
#define ENDING_IMAGE_LETTERS_SPAWNING unk_97

struct EndingData {
    u8 creditLineTilemapUpdate;     // 0x0, the V-blank copies the credit line tilemaps when set
    u8 stage;
    u16 unk_2;                      // 0x2, overlay, see the ENDING_* accessors above
    u16 lineRow;                    // 0x4, tilemap row of the next credit line
    u16 currentCreditLine;
    u16 scrollAccumulator;          // 0x8, a tile row has scrolled when it goes over 127
    u16 creditLineTilemap_1[32];
    u16 creditLineTilemap_2[32];
    u32 creditLineTilemapOffset_1;  // 0x8C, VRAM offset of the credit line tilemaps
    u32 creditLineTilemapOffset_2;  // 0x90
    u16 timer;
    u8 bg0WaveActive;               // 0x96, advances the BG0 wave of the H-blank code (currentCreditLine is its phase)
    u8 unk_97;                      // 0x97, overlay, see the ENDING_* accessors above
    u8 subStage;                    // 0x98, index in the Samus posing and ending image function pointers
    u8 clearTimeRank;               // 0x99, 2: under 2 hours, 1: under 4 hours, 0: otherwise
    u8 completionPercentage;
    u8 oamCount;                    // 0x9B, number of ending image text OAM, or whether the Samus OAM is drawn
    u8 samusOamObjMode;             // 0x9C, Samus transforming her suit
    u8 samusOamPriority;            // 0x9D
    u16* pSamusOamFrame;            // 0xA0
    u8 samusPosingBg0Offsets[0x80]; // 0xA4, BG0 X offsets used by the H-blank code (sine table)
    u8 letterStates[30];            // 0x124, ending image text OAM: 0 hidden, 1 waiting for its spawn delay, 2 drawn
    u8 letterSpawnDelays[30];       // 0x142
    u8 letterTimers[0x1D];          // 0x160, fade in timer
    u16 oamXPositions[30]; // 17E
    u16 oamYPositions[30]; // 1BA
    u16* oamFramePointers[30]; // 1F8
    u8 hBlankCode[64]; // 270, FIXME find actual length
};

ASSERT_OFFSET(struct EndingData, pSamusOamFrame, 0xA0);
ASSERT_OFFSET(struct EndingData, oamFramePointers, 0x1F8);
ASSERT_SIZE(struct EndingData, 0x2B0);

struct EndingImageTextOam {
    u8 state;
    u8 spawnDelay;
    u8 timer;
    u16 xPosition;
    u16 yPosition;
    u16* pFrame;
};

#endif /* ENDING_STRUCT_H */
