#ifndef CUTSCENE_COMMON_H
#define CUTSCENE_COMMON_H

#include "types.h"

#include "structs/cutscene_data.h"

void CutsceneMonologueProcessCursor(struct CutsceneMonologueOam* pOam);
boolu32 CutsceneMonologueProcessSpecialTextCharacters(void);
void CutsceneMonologueProcessText(void);
void unk_9cc4c(void);
void CutsceneMonologueFadeIn(void);
void CutsceneMonologueFadeOut(void);
void CutsceneMonologueProcessOam(void);
void CutsceneMonologueDrawAllOam(void);
void CutsceneMnologueDrawOam(struct CutsceneMonologueOam* pOam);
void CutsceneMonologueResetOam(u8 slot);
void unk_9d09c(void);
void unk_9d0a0(void);
void unk_9d1c4(void);
void CutsceneMonologueDestroyOamOfType(u8 type);

void CutsceneFadeIn(void);
void CutsceneFadeOut(void);
void CutsceneDestroyOamOfType(u8 type);
void CutsceneProcessOam(void);
void CutsceneDrawAllOam(void);
void CutsceneDrawOam(struct CutsceneOam* pOam);
void unk_9db70(struct CutsceneOam* pOam);

#endif /* CUTSCENE_COMMON_H */
