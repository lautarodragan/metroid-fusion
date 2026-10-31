#ifndef SA_X_OMEGA_AI_H
#define SA_X_OMEGA_AI_H

#include "types.h"

#define SA_X_OMEGA_POSE_STANDING_INIT 0x7
#define SA_X_OMEGA_POSE_STANDING 0x8
#define SA_X_OMEGA_POSE_RUNNING_INIT 0x3F
#define SA_X_OMEGA_POSE_RUNNING 0x40
#define SA_X_OMEGA_POSE_DELAY_BEFORE_SHOOTING_OMEGA_INIT 0x41
#define SA_X_OMEGA_POSE_DELAY_BEFORE_SHOOTING_OMEGA 0x42
#define SA_X_OMEGA_POSE_SHOOTING_OMEGA_INIT 0x43
#define SA_X_OMEGA_POSE_SHOOTING_OMEGA 0x44
#define SA_X_OMEGA_POSE_AFTER_SHOOTING_OMEGA_INIT 0x45
#define SA_X_OMEGA_POSE_AFTER_SHOOTING_OMEGA 0x46
#define SA_X_OMEGA_POSE_HIT_BY_OMEGA_INIT 0x47
#define SA_X_OMEGA_POSE_HIT_BY_OMEGA 0x48
#define SA_X_OMEGA_POSE_REVERTING_TO_X_INIT 0x49
#define SA_X_OMEGA_POSE_REVERTING_TO_X 0x4A

void SaXOmegaInit(void);
void SaXOmegaForming(void);
void SaXOmegaFalling(void);
void SaXOmegaStandingInit(void);
void SaXOmegaStanding(void);
void SaXOmegaRunningInit(void);
void SaXOmegaRunning(void);
void SaXOmegaDelayBeforeShootingOmegaInit(void);
void SaXOmegaDelayBeforeShootingOmega(void);
void SaXOmegaShootingOmegaInit(void);
void SaXOmegaShootingOmega(void);
void SaXOmegaAfterShootingOmegaInit(void);
void SaXOmegaAfterShootingOmega(void);
void SaXOmegaHitByOmegaInit(void);
void SaXOmegaHitByOmega(void);
void SaXOmegaRevertingToXInit(void);
void SaXOmegaRevertingToX(void);
void SaXOmega(void);

#endif /* SA_X_OMEGA_AI_H */
