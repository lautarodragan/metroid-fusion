#ifndef ENDING_DIALOGUE_H
#define ENDING_DIALOGUE_H

#include "types.h"

#include "structs/cutscene.h"

extern const struct FrameData sEndingDialogueType5Oam_Opening[11];
extern const struct FrameData sEndingAdamPanel0Oam[13];
extern const struct FrameData sEndingAdamPanel0Oam_Closing[13];
extern const struct FrameData sEndingAdamPanel1Oam[13];
extern const struct FrameData sEndingAdamPanel1Oam_Closing[13];
extern const struct FrameData sEndingAdamIconOam_Opening[5];
extern const struct FrameData sEndingAdamIconOam_Closing[137];
extern const struct FrameData sEndingAdamIconOam_Idle[6];
extern const struct FrameData sEndingDialogueType2Oam[32];
extern const struct FrameData sEndingSr388RadarViewOam_Opening[79];
extern const struct FrameData sEndingSamusViewRadarViewOam_Opening[67];
extern const struct FrameData sEndingNextPageArrowOam[5];
extern const struct FrameData sEndingTextCursorOam[7];
extern const struct FrameData sEndingUnk_633f24[];

extern u16** sEndingUnk_79c3ac[];

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
