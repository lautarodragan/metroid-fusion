#ifndef CUTSCENE_COMMON_H
#define CUTSCENE_COMMON_H

#include "types.h"

#include "structs/cutscene_data.h"

void CutsceneMonologueProcessCursor(struct CutsceneMonologueOam* pOam);
boolu32 CutsceneMonologueProcessSpecialTextCharacters(void);
void CutsceneMonologueProcessText(void);
void CutsceneMonologueUpdateTextTilesFade(void);
void CutsceneMonologueFadeIn(void);
void CutsceneMonologueFadeOut(void);
void CutsceneMonologueProcessOam(void);
void CutsceneMonologueDrawAllOam(void);
void CutsceneMonologueDrawOam(struct CutsceneMonologueOam* pOam);
void CutsceneMonologueResetOam(u8 slot);
void CutsceneMonologueOam_Empty(void);
void CutsceneComputeCircleWindow(void);
void CutsceneCircleWindowHblank(void);
void CutsceneMonologueDestroyOamOfType(u8 type);

void CutsceneFadeIn(void);
void CutsceneFadeOut(void);
void CutsceneDestroyOamOfType(u8 type);
void CutsceneProcessOam(void);
void CutsceneDrawAllOam(void);
void CutsceneDrawOam(struct CutsceneOam* pOam);
void CutsceneOam_Empty(struct CutsceneOam* pOam);

#endif /* CUTSCENE_COMMON_H */
