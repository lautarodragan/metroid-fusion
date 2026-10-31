#ifndef SA_X_AI_H
#define SA_X_AI_H

#include "types.h"

#define SA_X_MISSILE_SPEED (HALF_BLOCK_SIZE - PIXEL_SIZE)
#define SA_X_MISSILE_DIAGONAL_SPEED ((u16)(SA_X_MISSILE_SPEED * .75f))

// Work variables shared by the SA-X AIs
#define SA_X_LANDED work0 // Falling/mid-air, waits for the landing pose to end
#define SA_X_TIMER work1
#define SA_X_DIAG_AIM work2 // Shooting
#define SA_X_JUMP_TYPE work2 // Set when checking the collision in front, selects the jump Y velocity table
#define SA_X_X_SPEED_IDX work3
#define SA_X_Y_SPEED_IDX work4
#define SA_X_LOST_SAMUS_TIMER workY // Increases while Samus is detected but not in Y range, she is lost at 20 seconds

// Sprite poses shared by the SA-X AIs (some variants reuse some of these values for their own poses)
#define SA_X_SPRITE_POSE_WALKING_INIT 0x1
#define SA_X_SPRITE_POSE_WALKING 0x2
#define SA_X_SPRITE_POSE_TURNING_AROUND_INIT 0x3
#define SA_X_SPRITE_POSE_TURNING_AROUND 0x4
#define SA_X_SPRITE_POSE_STANDING_INIT 0x7
#define SA_X_SPRITE_POSE_STANDING 0x8
#define SA_X_SPRITE_POSE_RUNNING_INIT 0x17
#define SA_X_SPRITE_POSE_RUNNING 0x18
#define SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM_INIT 0x29
#define SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_BEAM 0x2A
#define SA_X_SPRITE_POSE_SHOOTING_BEAM_INIT 0x2B
#define SA_X_SPRITE_POSE_SHOOTING_BEAM 0x2C
#define SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_MISSILE_INIT 0x2D
#define SA_X_SPRITE_POSE_DELAY_BEFORE_SHOOTING_MISSILE 0x2E
#define SA_X_SPRITE_POSE_SHOOTING_MISSILE_INIT 0x2F
#define SA_X_SPRITE_POSE_SHOOTING_MISSILE 0x30
#define SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_MISSILE_INIT 0x31
#define SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_MISSILE 0x32
#define SA_X_SPRITE_POSE_MID_AIR_INIT 0x37
#define SA_X_SPRITE_POSE_MID_AIR 0x38
#define SA_X_SPRITE_POSE_TURNING_AROUND_CHASE_INIT 0x39
#define SA_X_SPRITE_POSE_TURNING_AROUND_CHASE 0x3A
#define SA_X_SPRITE_POSE_MORPHING_INIT 0x3B
#define SA_X_SPRITE_POSE_MORPHING 0x3C
#define SA_X_SPRITE_POSE_ROLLING_INIT 0x3D
#define SA_X_SPRITE_POSE_ROLLING 0x3E
#define SA_X_SPRITE_POSE_UNMORPHING_INIT 0x3F
#define SA_X_SPRITE_POSE_UNMORPHING 0x40
#define SA_X_SPRITE_POSE_IDLE_BEFORE_SHOOTING_DOOR_INIT 0x41
#define SA_X_SPRITE_POSE_IDLE_BEFORE_SHOOTING_DOOR 0x42
#define SA_X_SPRITE_POSE_SHOOTING_DOOR_INIT 0x43
#define SA_X_SPRITE_POSE_SHOOTING_DOOR 0x44
#define SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_DOOR_INIT 0x45
#define SA_X_SPRITE_POSE_IDLE_AFTER_SHOOTING_DOOR 0x46
#define SA_X_SPRITE_POSE_WALKING_TO_DOOR_INIT 0x47
#define SA_X_SPRITE_POSE_WALKING_TO_DOOR 0x48

void SaXSetDirection(void);
void SaXSeeAndLocateSamus(void);
u8 SaXCheckShootOrTurnTowardsSamus(void);
u8 SaXCheckStartChasing(void);
u8 SaXCheckStartChasingOrTurnAround(void);
void SaXCheckFallJumpOrMorph(void);
void SaXInit(void);
void SaXElevatorInit(void);
void SaXFallingInit(void);
void SaXFalling(void);
void SaXStandingInit(void);
void SaXStanding(void);
void SaXWalkingInit(void);
void SaXWalking(void);
void SaXTurningAroundInit(void);
void SaXTurningAround(void);
void SaXTurningAroundChaseInit(void);
void SaXTurningAroundChase(void);
void SaXRunningInit(void);
void SaXRunning(void);
void SaXMidAirInit(void);
void SaXMidAir(void);
void SaXDelayBeforeShootingBeamInit(void);
void SaXDelayBeforeShootingBeam(void);
void SaXShootingBeamInit(void);
void SaXShootingBeam(void);
void SaXDelayBeforeShootingMissileInit(void);
void SaXDelayBeforeShootingMissile(void);
void SaXShootingMissileInit(void);
void SaXShootingMissile(void);
void SaXIdleAfterShootingMissileInit(void);
void SaXIdleAfterShootingMissile(void);
void SaXMorphingInit(void);
void SaXMorphing(void);
void SaXRollingInit(void);
void SaXRolling(void);
void SaXUnmorphingInit(void);
void SaXUnmorphing(void);
void SaXIdleBeforeShootingDoorInit(void);
void SaXIdleBeforeShootingDoor(void);
void SaXShootingDoorInit(void);
void SaXShootingDoor(void);
void SaXIdleAfterShootingDoorInit(void);
void SaXIdleAfterShootingDoor(void);
void SaXWalkingToDoorInit(void);
void SaXWalkingToDoor(void);
void SaXBeamInit(void);
void SaXBeamMove(void);
void SaXMissileInit(void);
void SaXMissileExploding(void);
void SaXMissileMoving(void);
void SaXPowerBombInit(void);
void SaXPowerBombSpinningSlowly(void);
void SaXPowerBombSpinningQuickly(void);
void SaXPowerBombExploding(void);
void LabExplosionInit(void);
void LabExplosionExploding(void);
void SaXUpdateGraphics(void);
u8 SaXUpdateFreezeTimer(void);
void SaXElevator(void);
void SaXBeam(void);
void SaXMissile(void);
void SaXPowerBomb(void);
void LabExplosion(void);

#endif /* SA_X_AI_H */
