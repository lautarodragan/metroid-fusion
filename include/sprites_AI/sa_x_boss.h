#ifndef SA_X_BOSS_AI_H
#define SA_X_BOSS_AI_H

#include "types.h"

#define SA_X_BOSS_POSE_SPIN_JUMPING_INIT 0x37
#define SA_X_BOSS_POSE_SPIN_JUMPING 0x38
#define SA_X_BOSS_POSE_WAITING_TO_APPEAR_INIT 0x41
#define SA_X_BOSS_POSE_WAITING_TO_APPEAR 0x42
#define SA_X_BOSS_POSE_FALLING_FROM_KNOCKBACK_INIT 0x43
#define SA_X_BOSS_POSE_FALLING_FROM_KNOCKBACK 0x44
#define SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_1_INIT 0x45
#define SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_1 0x46
#define SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_2_INIT 0x47
#define SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_2 0x48
#define SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_3_INIT 0x49
#define SA_X_BOSS_POSE_VARIABLE_JUMP_HEIGHT_3 0x4A
#define SA_X_BOSS_POSE_KNOCKBACK_INIT 0x4F
#define SA_X_BOSS_POSE_KNOCKBACK 0x50
#define SA_X_BOSS_POSE_KNEELING_INIT 0x51
#define SA_X_BOSS_POSE_KNEELING 0x52
#define SA_X_BOSS_POSE_TRANSFORMING_INTO_MONSTER_INIT 0x53
#define SA_X_BOSS_POSE_TRANSFORMING_INTO_MONSTER 0x54
#define SA_X_BOSS_POSE_AFTER_TRANSFORMATION 0x55

void SaXBossCheckCollisionRunning(void);
u8 SaXBossTrackSamus(void);
void SaXBossRunningInit(void);
void SaXBossRunning(void);
void SaXBossSpinJumpingInit(void);
void SaXBossSpinJumping(void);
void SaXBossWaitingToAppearInit(void);
void SaXBossWaitingToAppear(void);
void SaXBossInit(void);
void SaXBossFallingInit(void);
void SaXBossFalling(void);
void SaXBossTurningAroundChaseInit(void);
void SaXBossTurningAroundChase(void);
void SaxBossFallingFromKnockbackInit(void);
void SaxBossFallingFromKnockback(void);
void SaXBossVariableJumpHeightInit(void);
void SaXBossVariableJumpHeight(void);
void SaXBossUpdateMosaic(void);
void SaXBossKnockbackInit(void);
void SaXBossKnockback(void);
void SaXBossKneelingInit(void);
void SaXBossKneeling(void);
void SaXBossTransformingIntoMonsterInit(void);
void SaXBossTransformingIntoMonster(void);
void SaXBossAfterTransformation(void);
void SaXBoss(void);

#endif /* SA_X_BOSS_AI_H */
