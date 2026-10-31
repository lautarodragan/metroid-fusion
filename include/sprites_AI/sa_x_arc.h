#ifndef SA_X_ARC_AI_H
#define SA_X_ARC_AI_H

#include "types.h"

#define SA_X_ARC_POSE_WAITING_IN_DOOR 0x19
#define SA_X_ARC_POSE_OPENING_DOOR 0x1A
#define SA_X_ARC_POSE_WAITING_IN_DOOR_DURING_CHASE 0x1B
#define SA_X_ARC_POSE_OPENING_DOOR_DURING_CHASE 0x1C
#define SA_X_ARC_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT 0x2D
#define SA_X_ARC_POSE_DELAY_BEFORE_SHOOTING_BEAM 0x2E
#define SA_X_ARC_POSE_SHOOTING_BEAM_INIT 0x2F
#define SA_X_ARC_POSE_SHOOTING_BEAM 0x30
#define SA_X_ARC_POSE_STOPPED_AT_PILLAR_INIT 0x49
#define SA_X_ARC_POSE_STOPPED_AT_PILLAR 0x4A
#define SA_X_ARC_POSE_IDLE_AFTER_HEARING_WEAPON_INIT 0x4B
#define SA_X_ARC_POSE_IDLE_AFTER_HEARING_WEAPON 0x4C
#define SA_X_ARC_POSE_TURNING_AROUND_AFTER_HEARING_WEAPON_INIT 0x4D
#define SA_X_ARC_POSE_TURNING_AROUND_AFTER_HEARING_WEAPON 0x4E

void SaXArcCheckCollisionWalking(void);
void SaXArcCheckCollisionRunning(void);
void SaXArcInit(void);
void SaXArcWaitingInDoorDuringChase(void);
void SaXArcOpeningDoorDuringChase(void);
void SaXArcWaitingInDoor(void);
void SaXArcOpeningDoor(void);
void SaXArcWalking(void);
void SaXArcStoppedAtPillarInit(void);
void SaXArcStoppedAtPillar(void);
void SaXArcIdleAfterHearingWeaponInit(void);
void SaXArcIdleAfterHearingWeapon(void);
void SaXArcTurningAroundAfterHearingWeaponInit(void);
void SaXArcTurningAroundAfterHearingWeapon(void);
void SaXArcRunning(void);
void SaXArcTurningAroundChase(void);
void SaXArcDelayBeforeShootingBeamInit(void);
void SaXArcDelayBeforeShootingBeam(void);
void SaXArcShootingBeamInit(void);
void SaXArcShootingBeam(void);
void SaXArc(void);

#endif /* SA_X_ARC_AI_H */
