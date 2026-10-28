#ifndef CUTSCENE_HANDLER_H
#define CUTSCENE_HANDLER_H

#include "types.h"
#include "oam.h"

#include "structs/cutscene_data.h"

#include "cutscenes/cutscene_common.h"
#include "cutscenes/secret_conversation.h"
#include "cutscenes/restricted_lab_detaching.h"
#include "cutscenes/bsl_exploding.h"

extern u16** sMonologueTextPointers[];

extern const u16* const sCutsceneUnk_79c4a8[];
extern const u16* const sCutsceneUnk_79c4cc[];
extern const u8* const sCutsceneUnk_79c4f0[];
extern const u8* const sCutsceneUnk_79c514[];
extern const u8* const sCutsceneUnk_79c538[];
extern const struct FrameData* const sCutsceneUnk_79c55c[][2];

extern const u8 sCutsceneUnk_65fb5c[];
extern const u32 sCutsceneElevatorMonologueBg1Tilemap[];
extern const u16 sCutsceneMonologueBgPal[];
extern const u16 sCutsceneMonologueObjPal[];
extern const struct FrameData sCutsceneUnk_663e5c[];
extern const u32 sCutsceneFederationMonologueBg2Gfx[];
extern const u16 sCutsceneFederationMonologueBgPal[];
extern const u32 sCutsceneFederationMonologueBg2Tilemap[];

boolu32 CutsceneHandler(void);
void CutsceneInit(void);
void CutsceneVblank(void);
void unk_99af8(void);
boolu32 CutsceneProcess(void);
boolu32 CutsceneElevatorMonologue(boolu8 reverseScrolling);
void CutsceneElevatorMonologueInit(boolu8 reverseScrolling);
boolu32 CutsceneElevatorMonologueProcess(void);
u8 CutsceneElevatorMonologueSetupOam(u8 type, s16 xPosition, s16 yPosition);
void CutsceneProcessElevatorScrolling(struct CutsceneMonologueOam* pOam);
void unk_9a1a8(struct CutsceneMonologueOam* pOam);
void CutsceneElevatorMonologueVblank(void);
void unk_9a31c(void);
boolu32 CutsceneInternalMonologue(u8 unused);
void CutsceneInternalMonologueInit(u8 unused);
boolu32 CutsceneInternalMonologueProcess(void);
u8 CutsceneInternalMonologueSetupOam(u8 type, s16 xPosition, s16 yPosition);
void CutsceneInternalMonologueVblank(void);
void unk_9a63c(void);
boolu32 CutsceneFederationMonologue(u8 unused);
void CutsceneFederationMonologueInit(u8 unused);

#endif /* CUTSCENE_HANDLER_H */
