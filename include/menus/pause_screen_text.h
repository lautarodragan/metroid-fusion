#ifndef PAUSE_SCREEN_TEXT_H
#define PAUSE_SCREEN_TEXT_H

#include "types.h"

extern u8 gFlashingSectorNumber;

extern u16** sPauseScreenTextPointers[];

void ProcessPauseScreenText(void);
void ProcessEasySleepText(void);
u8 GetFlashingSectorNumber(void);

#endif /* PAUSE_SCREEN_TEXT_H */
