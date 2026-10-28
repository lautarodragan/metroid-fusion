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
void unk_9ba50(struct CutsceneOam* pOam);
void unk_9bac0(struct CutsceneOam* pOam);
void unk_9bb30(struct CutsceneOam* pOam);
void unk_9bc04(struct CutsceneOam* pOam);
void unk_9bcdc(struct CutsceneOam* pOam);
void unk_9bd24(struct CutsceneOam* pOam);
void unk_9bdf8(struct CutsceneOam* pOam);
void unk_9be8c(struct CutsceneOam* pOam);
void unk_9bf54(struct CutsceneOam* pOam);
void unk_9bfb8(struct CutsceneOam* pOam);
void unk_9c04c(struct CutsceneOam* pOam);
u8 unk_9c080(u8 type, s16 xPosition, s16 yPosition, s16 xVelocity);
u8 unk_9c0b4(u8 type, s16 xPosition, s16 yPosition, s16 xVelocity, s16 yVelocity);
void CutsceneRestrictedLabDetachingGetPositionOfOamByType(u8 type, s16* pXPosition, s16* pYPosition);
void CutsceneRestrictedLabDetachingVblank(void);
void unk_9c1bc(void);

#endif /* RESTRICTED_LAB_DETACHING_H */
