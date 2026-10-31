#ifndef INTRO_STRUCT_H
#define INTRO_STRUCT_H

#include "types.h"

#include "structs/cutscene.h"

#define INTRO_DATA gNonGameplayRam.intro

struct IntroData {
    const u16* pText;
    const u16* pText2;
    u16 stage;
    UNUSED(2);
    u16 currentColumn;          // 0xC, text cursor column (in tiles)
    u16 currentLine;            // 0xE, text cursor line (in tiles, 2 per text line)
    u16 fadeColumn;             // 0x10, first text tile still fading in
    u16 fadeLine;               // 0x12
    u8 tilesFadeStage[252];     // 0x14, per tile fade in stage of the monologue text (see INTRO_TEXT_TILE_DELAY)
    // From 0x110, the monologue text uses the area for its per tile fade timers (see INTRO_TEXT_TILE_TIMER),
    // the other cutscenes for palette animations : the V-blank copies frame N of a palette when the update flag is set
    u8 paletteUpdate1;          // 0x110
    u8 paletteFrame1;           // 0x111
    u8 unk_112[26];
    u8 paletteUpdate2;          // 0x12C
    u8 paletteFrame2;           // 0x12D
    u8 unk_12E[26];
    u8 paletteUpdate3;          // 0x148
    u8 paletteFrame3;           // 0x149
    u8 unk_14A[166];
    u8 paletteUpdate4;          // 0x1F0, set by the ship in the landing on BSL cutscene, never read
    u8 paletteFrame4;           // 0x1F1
    u8 unk_1F2;
    u8 windowRadius;            // 0x1F3, circle window (Samus getting cured cutscene)
    u8 windowCenterX;           // 0x1F4
    u8 windowCenterY;           // 0x1F5
    u8 unk_1F6[22];
    u16 textTimer;              // 0x20C, frames since the last text character
    u16 handlerTimer;           // 0x20E, timer used by the main handlers between cutscenes
    u16 timer;
    u8 indent;                  // 0x212, text pixel offset in the current tile
    u8 unk_213;                 // 0x213, text update state (1: draw the next character, 100: idle), also a generic counter in some cutscenes
    u8 subStage;
    u8 activeOamCount;          // 0x215, number of OAM objects processed this frame
    s8 bg2XVelocity;            // 0x216, added to the BG2 X position, OAM objects scroll with it
    s8 bg2YVelocity;            // 0x217
    u8 textAdvanceState;        // 0x218, set to 1 when A is pressed on a next page arrow, then 2 (new page), 3 (end), 4 (next arrow) or 0
    struct SpecialCutsceneOam oam[20];
    u8 hBlankCode[80];
    u8* hBlankCodePointer;
};

ASSERT_OFFSET(struct IntroData, currentColumn, 0xC);
ASSERT_OFFSET(struct IntroData, oam, 0x21C);
ASSERT_SIZE(struct IntroData, 0x540);

#endif /* INTRO_STRUCT_H */
