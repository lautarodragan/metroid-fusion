#ifndef SA_X_LAB_AI_H
#define SA_X_LAB_AI_H

#include "types.h"

#define SA_X_LAB_POSE_SHOOTING_LAB_INIT 0x1
#define SA_X_LAB_POSE_SHOOTING_LAB 0x2
#define SA_X_LAB_POSE_GETTING_COVERED_BY_METROIDS 0x18
#define SA_X_LAB_POSE_COVERED_BY_METROIDS 0x1A
#define SA_X_LAB_POSE_COVERED_BY_METROIDS_AFTER_DETACHMENT 0x1C

void SaXLabInit(void);
void SaXLabShootingLabInit(void);
void SaXLabSetTarget(void);
void SaXLabGettingCoveredByMetroids(void);
void SaXLabCoveredByMetroids(void);
void SaXLabCoveredByMetroidsAfterDetachment(void);
void SaXLab(void);

#endif /* SA_X_LAB_AI_H */
