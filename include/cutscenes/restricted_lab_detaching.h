#ifndef RESTRICTED_LAB_DETACHING_H
#define RESTRICTED_LAB_DETACHING_H

#include "types.h"

#include "structs/cutscene_data.h"

boolu32 CutsceneRestrictedLabDetaching(void);
void CutsceneRestrictedLabDetachingInit(void);
boolu32 CutsceneRestrictedLabDetachingProcess(void);
void CutsceneRestrictedLabDetachingProcessFallingLab(struct CutsceneOam* pOam);
u8 CutsceneRestrictedLabDetachingSetupOam(u8 type, s16 xPosition, s16 yPosition);
void CutsceneRestrictedLabDetachingProcessBslPart(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingProcessScrolling(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingMoveOam(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingMoveOam_2(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingMoveAndShrinkWithPal1(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingMoveAndShrinkWithPal0(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingScrollBg2WithVelocity(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingMoveAndShrinkWithPal3(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingMoveAndShrink(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingFadeBg(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingShakeBg1(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingMoveOamUntilAnimEnded(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingScrollBg2(struct CutsceneOam* pOam);
u8 CutsceneRestrictedLabDetachingSetupOamWithXVelocity(u8 type, s16 xPosition, s16 yPosition, s16 xVelocity);
u8 CutsceneRestrictedLabDetachingSetupOamWithVelocity(u8 type, s16 xPosition, s16 yPosition, s16 xVelocity, s16 yVelocity);
void CutsceneRestrictedLabDetachingGetPositionOfOamByType(u8 type, s16* pXPosition, s16* pYPosition);
void CutsceneRestrictedLabDetachingVblank(void);
void CutsceneRestrictedLabDetachingLoadingVblank(void);

#endif /* RESTRICTED_LAB_DETACHING_H */
