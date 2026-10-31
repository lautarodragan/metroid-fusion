#ifndef CLIPDATA_H
#define CLIPDATA_H

#include "types.h"

#include "structs/clipdata.h"

void ClipdataUpdateBlockReveal(void);
s32 ClipdataRevealBlocksRow(void);
void ClipdataSetupCode(void);
u32 ClipdataProcessForSamus(u16 yPosition, u16 xPosition);
u32 ClipdataProcess(u16 yPosition, u16 xPosition);
u32 ClipdataConvertToCollision(struct CollisionData* pCollision);
s32 ClipdataCheckCurrentAffectingAtPosition(u16 yPosition, u16 xPosition);
u32 ClipdataCheckElevatorDisabled(u16 movementClip);
u32 ClipdataGetGroundEffect(u16 yPosition, u16 xPosition);

#endif /* CLIPDATA_H */
