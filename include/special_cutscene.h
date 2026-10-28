#ifndef SPECIAL_CUTSCENE_H
#define SPECIAL_CUTSCENE_H

#include "types.h"

#include "structs/cutscene.h"
#include "structs/intro.h"

/**
 * @brief Text parameter to wait the amount of frames in the low byte before showing the next character
 * 
 */
#define CHAR_DELAY C_16_2_8(0xE1, 0)

/**
 * @brief Length (in tiles) of a monologue text line
 * 
 */
#define MONOLOGUE_LINE_LENGTH 28

// Per tile fade in state of the monologue text (MONOLOGUE_LINE_LENGTH tiles per row), overlaid on the intro data
#define INTRO_TEXT_TILE_DELAY (INTRO_DATA.unk_14)
#define INTRO_TEXT_TILE_TIMER (&INTRO_DATA.unk_110)

// Arrays overlaid on the intro data (struct IntroData), starting at 0x110
struct IntroDataArrays {
    u8 unk_0[0x110];
    u8 unk_110[28];
    u8 unk_12C[28];
    u8 unk_148[28];
    u8 unk_164[28];
};

#define INTRO_DATA_ARRAYS (*(struct IntroDataArrays*)&INTRO_DATA)

typedef void (*SpecialCutsceneOamFunc_T)(struct SpecialCutsceneOam*);

extern u8 gUnk_3001238;

extern u16 gSpecialCutsceneRandomSeed;
#define SPECIAL_CUTSCENE_RANDOM_SEED_HIGH (((u8*)&gSpecialCutsceneRandomSeed)[1])

boolu32 NewFileIntroCheckMonologueEnded(void);
boolu32 EndingCheckMonologueEnded(void);
void SpecialCutsceneProcessMonologue(void);
void unk_98158(void);
boolu32 EndingProcessAdamText(void);
boolu32 IntroProcessText(void);
boolu32 NewFileIntroProcessAdamText(void);
void Dma3Transfer_Unused1(const u8* src, u8* dst, u32 size, u16 nbrRows);
void Dma3Transfer_Unused2(const u8* src, u8* dst, u32 size, u16 nbrRows);
void Dma3Clear_Unused(u8* dst, u32 size, u16 nbrRows);
void unk_98a04(void);
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
void unk_99940(void);

#endif /* SPECIAL_CUTSCENE_H */
