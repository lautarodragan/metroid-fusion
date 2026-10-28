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

boolu32 NewFileIntroCheckMonologueEnded(void);
boolu32 EndingCheckMonologueEnded(void);
void SpecialCutsceneProcessMonologue(void);
void unk_98158(void);
boolu32 EndingProcessAdamText(void);
boolu32 IntroProcessText(void);
boolu32 NewFileIntroProcessAdamText(void);
void SpecialCutsceneFadeIn(void);
void SpecialCutsceneDestroyOamOfType(u8 type);
void SpecialCutsceneProcessOam(void);
void SpecialCutsceneDrawAllOam(void);
void unk_99940(void);

#endif /* SPECIAL_CUTSCENE_H */
