#ifndef SA_X_NOC_AI_H
#define SA_X_NOC_AI_H

#include "types.h"

#define SA_X_NOC_POSE_WAITING_IN_DOOR_TO_LAY_POWER_BOMB 0x19
#define SA_X_NOC_POSE_WALKING_TO_LAY_POWER_BOMB 0x1A
#define SA_X_NOC_POSE_WAITING_IN_DOOR_DURING_CHASE 0x1B
#define SA_X_NOC_POSE_OPENING_DOOR_DURING_CHASE 0x1C
#define SA_X_NOC_POSE_IDLE_BEFORE_LAYING_POWER_BOMB_INIT 0x49
#define SA_X_NOC_POSE_IDLE_BEFORE_LAYING_POWER_BOMB 0x4A
#define SA_X_NOC_POSE_MORPHING_TO_LAY_POWER_BOMB_INIT 0x4B
#define SA_X_NOC_POSE_MORPHING_TO_LAY_POWER_BOMB 0x4C
#define SA_X_NOC_POSE_LAYING_POWER_BOMB_INIT 0x4D
#define SA_X_NOC_POSE_LAYING_POWER_BOMB 0x4E

void SaXNocCheckCollisionWalking(void);
void SaXNocCheckCollisionRunning(void);
void SaXNocCheckCollisionWalkingToLayPowerBomb(void);
void SaXNocInit(void);
void SaXNocWaitingInDoorDuringChase(void);
void SaXNocOpeningDoorDuringChase(void);
void SaXNocWaitingInDoorToLayPowerBomb(void);
void SaXNocWalkingToLayPowerBomb(void);
void SaXNocIdleBeforeLayingPowerBombInit(void);
void SaXNocIdleBeforeLayingPowerBomb(void);
void SaXNocMorphingToLayPowerBombInit(void);
void SaXNocMorphingToLayPowerBomb(void);
void SaXNocLayingPowerBombInit(void);
void SaXNocLayingPowerBomb(void);
void SaXNocWalking(void);
void SaXNocRunning(void);
void SaXNocTurningAroundChase(void);
void SaXNoc(void);

#endif /* SA_X_NOC_AI_H */
