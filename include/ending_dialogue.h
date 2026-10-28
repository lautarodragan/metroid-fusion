#ifndef ENDING_DIALOGUE_H
#define ENDING_DIALOGUE_H

#include "types.h"

#include "structs/cutscene.h"

extern const struct FrameData sEndingUnk_6331ec[];
extern const struct FrameData sEndingUnk_633294[];
extern const struct FrameData sEndingUnk_6332fc[];
extern const struct FrameData sEndingUnk_633364[];
extern const struct FrameData sEndingUnk_6333cc[];
extern const struct FrameData sEndingUnk_633434[];
extern const struct FrameData sEndingUnk_63345c[];
extern const struct FrameData sEndingUnk_6338a4[];
extern const struct FrameData sEndingUnk_6338d4[];
extern const struct FrameData sEndingUnk_6339d4[];
extern const struct FrameData sEndingUnk_633c4c[];
extern const struct FrameData sEndingUnk_633e64[];
extern const struct FrameData sEndingUnk_633e8c[];
extern const struct FrameData sEndingUnk_633f24[];

extern u16** sEndingDialogueTextTables[];

void EndingProcessMonologueCursor(struct SpecialCutsceneOam* pOam);
void unk_969e0(struct SpecialCutsceneOam* pOam);
void EndingProcessSr388RadarView(struct SpecialCutsceneOam* pOam);
void EndingProcessSamusViewRadarView(struct SpecialCutsceneOam* pOam);
void unk_96a70(struct SpecialCutsceneOam* pOam);
void EndingProcessAdamTextCursor(struct SpecialCutsceneOam* pOam);

void EndingProcessAdamPanel(struct SpecialCutsceneOam* pOam);
void EndingProcessAdamIcon(struct SpecialCutsceneOam* pOam);
void EndingProcessAnimalsScrolling(struct SpecialCutsceneOam* pOam);
void unk_96f00(struct SpecialCutsceneOam* pOam);
u8 EndingDialogueSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearch);
void EndingMonologueVblank(void);
void EndingConversationAndAnimalsVblank(void);
u8 EndingGetPositionAndSlotOfOamByType_2(u8 type, s16* pXPosition, s16* pYPosition);
void unk_97418(struct SpecialCutsceneOam* pOam);

#endif /* ENDING_DIALOGUE_H */
