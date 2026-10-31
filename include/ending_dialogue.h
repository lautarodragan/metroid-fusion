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
extern const struct FrameData sEndingDialogueType30Oam[];

extern u16** sEndingDialogueTextTables[];

void EndingProcessMonologueCursor(struct SpecialCutsceneOam* pOam);
void EndingProcessHoldLastAnimFrame(struct SpecialCutsceneOam* pOam);
void EndingProcessSr388RadarView(struct SpecialCutsceneOam* pOam);
void EndingProcessSamusViewRadarView(struct SpecialCutsceneOam* pOam);
void EndingProcessDialogueType5(struct SpecialCutsceneOam* pOam);
void EndingProcessAdamTextCursor(struct SpecialCutsceneOam* pOam);

void EndingProcessAdamPanel(struct SpecialCutsceneOam* pOam);
void EndingProcessAdamIcon(struct SpecialCutsceneOam* pOam);
void EndingProcessAnimalsScrolling(struct SpecialCutsceneOam* pOam);
void EndingDestroyOam(struct SpecialCutsceneOam* pOam);
u8 EndingDialogueSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearch);
void EndingMonologueVblank(void);
void EndingConversationAndAnimalsVblank(void);
u8 EndingGetPositionAndSlotOfOamByType_2(u8 type, s16* pXPosition, s16* pYPosition);
void EndingDialogueOam_Empty(struct SpecialCutsceneOam* pOam);

#endif /* ENDING_DIALOGUE_H */
