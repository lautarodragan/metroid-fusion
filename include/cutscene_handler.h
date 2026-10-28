#ifndef CUTSCENE_HANDLER_H
#define CUTSCENE_HANDLER_H

#include "types.h"
#include "oam.h"

struct CutsceneMonologueOam {
    s16 xPosition;                // 0x0
    s16 yPosition;                // 0x2
    u8 type;                      // 0x4
    u8 exists;                    // 0x5
    u8 unk_6;
    u8 unk_7;
    u8 timer;                     // 0x8
    u8 stage;                     // 0x9
    u8 unk_A;
    u8 unk_B;
    u8 unk_C;
    u8 unk_D;
    u16 unk_E;
    const struct FrameData* pOam; // 0x10
    void* pFunction;              // 0x14
};

// Layout of gNonGameplayRam during the monologue cutscenes
struct CutsceneMonologueData {
    u8 unk_0[8];
    u16 stage;                    // 0x8
    u16 monologueId;              // 0xA
    const u16* pText;             // 0xC
    u16 unk_10;
    u16 bg2YPosition;             // 0x12
    u16 bg1YPosition;             // 0x14
    u8 unk_16;
    u8 unk_17;
    u8 unk_18[0x214 - 0x18];
    struct CutsceneMonologueOam oam[5]; // 0x214
};

#define CUTSCENE_MONOLOGUE_DATA (*(struct CutsceneMonologueData*)&gNonGameplayRam)

extern u16** sMonologueTextPointers[];

extern const u16* const sCutsceneUnk_79c4a8[];
extern const u16* const sCutsceneUnk_79c4cc[];
extern const u8* const sCutsceneUnk_79c4f0[];
extern const u8* const sCutsceneUnk_79c514[];
extern const u8* const sCutsceneUnk_79c538[];
extern const struct FrameData* const sCutsceneUnk_79c55c[][2];

extern const u8 sCutsceneUnk_65fb5c[];
extern const u8 sCutsceneUnk_663598[];
extern const u16 sCutsceneUnk_6636a0[];
extern const u16 sCutsceneUnk_6638a0[];
extern const struct FrameData sCutsceneUnk_663e5c[];
extern const u8 sCutsceneUnk_6724c0[];
extern const u16 sCutsceneUnk_674958[];
extern const u8 sCutsceneUnk_674ad8[];

// Defined in the following cutscene code
void CutsceneMonologueProcessCursor(struct CutsceneMonologueOam* pOam);
boolu32 CutsceneMonologueProcessSpecialTextCharacters(void);
void CutsceneMonologueProcessText(void);
void unk_9cc4c(void);
void CutsceneMonologueFadeIn(void);
void CutsceneMonologueFadeOut(void);
void CutsceneMonologueProcessOam(void);
void CutsceneMonologueDrawAllOam(void);
void CutsceneMonologueResetOam(u8 slot);
void unk_9d09c(struct CutsceneMonologueOam* pOam);
boolu32 CutsceneFederationMonologueProcess(void);
u8 CutsceneFederationMonologueSetupOam(u8 type, s16 xPosition, s16 yPosition);
void CutsceneFederationMonologueVblank(void);
void unk_9a99c(void);
boolu32 CutsceneSecretConversation(void);
boolu32 CutsceneRestrictedLabDetaching(void);
boolu32 CutsceneBslExploding(void);

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
