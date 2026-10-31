#ifndef SA_X_TRO_2_H
#define SA_X_TRO_2_H

#include "types.h"

#define SA_X_TRO_2_POSE_WAITING_IN_DOOR_DURING_CHASE 0x1B
#define SA_X_TRO_2_POSE_WAITING_IN_DOOR_END 0x1C
#define SA_X_TRO_2_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT 0x2D
#define SA_X_TRO_2_POSE_DELAY_BEFORE_SHOOTING_BEAM 0x2E
#define SA_X_TRO_2_POSE_SHOOTING_BEAM_INIT 0x2F
#define SA_X_TRO_2_POSE_SHOOTING_BEAM 0x30
#define SA_X_TRO_2_POSE_STOPPED_AT_DOOR_INIT 0x49
#define SA_X_TRO_2_POSE_STOPPED_AT_DOOR 0x4A
#define SA_X_TRO_2_POSE_IDLE_AFTER_HEARING_WEAPON_INIT 0x4B
#define SA_X_TRO_2_POSE_IDLE_AFTER_HEARING_WEAPON 0x4C
#define SA_X_TRO_2_POSE_TURNING_AFTER_HEARING_WEAPON_INIT 0x4D
#define SA_X_TRO_2_POSE_TURNING_AFTER_HEARING_WEAPON 0x4E

void SaXTro2CheckCollisionWalking(void);
void SaXTro2CheckCollisionRunning(void);
void SaXTro2Init(void);
void SaXTro2WaitingInDoorDuringChase(void);
void SaXTro2WaitingInDoorEnd(void);
void SaXTro2Walking(void);
void SaXTro2StoppedAtDoorInit(void);
void SaXTro2StoppedAtDoor(void);
void SaXTro2IdleAfterHearingWeaponInit(void);
void SaXTro2IdleAfterHearingWeapon(void);
void SaXTro2TurningAfterHearingWeaponInit(void);
void SaXTro2TurningAfterHearingWeapon(void);
void SaXTro2Running(void);
void SaXTro2TurningAroundChase(void);
void SaXTro2DelayBeforeShootingBeamInit(void);
void SaXTro2DelayBeforeShootingBeam(void);
void SaXTro2ShootingBeamInit(void);
void SaXTro2ShootingBeam(void);
void SaXTro2(void);

#endif /* SA_X_TRO_2_H */
