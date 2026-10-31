#ifndef SRAM_MISC_H
#define SRAM_MISC_H

#include "types.h"

void EraseSram_Unused(void);
void EraseSram(void);
void WriteSramHeaderToSram(void);
void WriteSramHeaderBackupToSram(void);
void WriteSramHeaderBackup2ToSram(void);
void WriteMostRecentFileToSram(void);
void WriteMostRecentFileBackupToSram(void);
void ReadAllFilesToEwram(void);
void ReadMostRecentFileToEwram(void);
void ReadSramHeaderToEwram(void);
void WriteMostRecentSaveFileDataToSram(void);
void WriteLanguageDataToSram(u8 copy);
void WriteSramTail_Unused(void);
void WriteDemoInputsToSram(void);

#endif /* SRAM_MISC_H */
