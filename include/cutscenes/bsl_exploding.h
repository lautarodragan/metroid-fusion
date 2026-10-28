#ifndef BSL_EXPLODING_H
#define BSL_EXPLODING_H

#include "types.h"

#include "structs/cutscene_data.h"

boolu32 CutsceneBslExploding(void);
void CutsceneBslExplodingInit(void);
boolu32 CutsceneBslExplodingProcess(void);
void CutsceneBslExplodingProcessScrolling(struct CutsceneOam* pOam);
void CutsceneBslExplodingProcessBslFar(struct CutsceneOam* pOam);
void CutsceneBslExplodingProcessExplosions(struct CutsceneOam* pOam);
u8 CutsceneBslExplodingSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder);
u8 CutsceneBslExplodingGetOamInfoByType(u8 type, s16* pXPosition, s16* pYPosition, s16* pScaling);
void CutsceneBslExplodingVblank(void);
void unk_9c92c(void);

#endif /* BSL_EXPLODING_H */
