#ifndef SPECIAL_CUTSCENE_H
#define SPECIAL_CUTSCENE_H

#include "types.h"
#include "macros.h"

#include "constants/text.h"

#include "structs/cutscene.h"
#include "structs/intro.h"

/**
 * @brief Length (in tiles) of a monologue text line
 * 
 */
#define MONOLOGUE_LINE_LENGTH 28

// Per tile fade in state of the monologue text (MONOLOGUE_LINE_LENGTH tiles per row), overlaid on the intro data
#define INTRO_TEXT_TILE_DELAY (INTRO_DATA.tilesFadeStage)
// The per tile fade timers start at 0x110, overlaid on the palette animation fields
#define INTRO_TEXT_TILE_TIMER (&INTRO_DATA.paletteUpdate1)

// Per tile fade timers of the monologue text, overlaid on the intro data (struct IntroData)
struct IntroTextTilesFade {
    PADDING(0x110);
    u8 tilesFadeTimer[9 * MONOLOGUE_LINE_LENGTH];
};

ASSERT_OFFSET(struct IntroTextTilesFade, tilesFadeTimer, OFFSET_OF(struct IntroData, paletteUpdate1));

#define INTRO_TEXT_TILES_FADE (*(struct IntroTextTilesFade*)&INTRO_DATA)

// Palette animation arrays overlaid on the intro data (struct IntroData), starting at 0x110
// (only used by SpecialCutsceneUpdatePaletteAnimations_Unused)
struct IntroDataArrays {
    PADDING(0x110);
    u8 paletteAnimDelay[28];
    u8 paletteAnimTimer[28];
    u8 paletteAnimFrame[28];
    u8 paletteAnimUpdate[28];
};

ASSERT_OFFSET(struct IntroDataArrays, paletteAnimDelay, OFFSET_OF(struct IntroData, paletteUpdate1));

#define INTRO_DATA_ARRAYS (*(struct IntroDataArrays*)&INTRO_DATA)

typedef void (*SpecialCutsceneOamFunc_T)(struct SpecialCutsceneOam*);

extern u8 gNextOamMatrixSlot;

extern u16 gSpecialCutsceneRandomSeed;
#define SPECIAL_CUTSCENE_RANDOM_SEED_HIGH (((u8*)&gSpecialCutsceneRandomSeed)[1])

boolu32 NewFileIntroCheckMonologueEnded(void);
boolu32 EndingCheckMonologueEnded(void);
void SpecialCutsceneProcessMonologue(void);
void SpecialCutsceneUpdateTextTilesFade(void);
boolu32 EndingProcessAdamText(void);
boolu32 IntroProcessText(void);
boolu32 NewFileIntroProcessAdamText(void);
void Dma3Transfer_Unused1(const u8* src, u8* dst, u32 size, u16 nbrRows);
void Dma3Transfer_Unused2(const u8* src, u8* dst, u32 size, u16 nbrRows);
void Dma3Clear_Unused(u8* dst, u32 size, u16 nbrRows);
void SpecialCutsceneUpdatePaletteAnimations_Unused(void);
void NewFileIntroSamusGettingCuredSetupWindow(void);
void SpecialCutsceneFadeIn(void);
void SpecialCutsceneFadOut(void);
void NewFileIntroProcessTextCursor(struct SpecialCutsceneOam* pOam);
void SpecialCutsceneClearOam(void);
void SpecialCutsceneEnableOam(void);
void SpecialCutsceneDestroyOamOfType(u8 type);
void SpecialCutsceneProcessOam(void);
void SpecialCutsceneDrawAllOam(void);
void SpecialCutsceneDrawOam(struct SpecialCutsceneOam* pOam);
void NewFileIntroInit(void);
u8 SpecialCutsceneGetRandomNumber(void);
void NewFileIntroVblank(void);
void SpecialCutsceneLoadingVblank(void);

#endif /* SPECIAL_CUTSCENE_H */
