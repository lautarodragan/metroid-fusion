#ifndef ERASE_SRAM_H
#define ERASE_SRAM_H

#include "types.h"

u32 EraseSramMenuHandler(void);
s32 EraseSramProcessInput(void);
void EraseSramApplyInput(void);
s32 EraseSramCheckForInput(void);
void EraseSramMenuInit(void);
void EraseSramResetOam(void);
void EraseSramUpdateCursorPosition(void);
void EraseSramVBlank(void);
void EraseSramLoadingVBlank(void);
void EraseSramProcessOam(void);

#endif /* ERASE_SRAM_H */
