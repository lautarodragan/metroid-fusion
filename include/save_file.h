#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include "types.h"

void Sram_ReadAll(void);
void Sram_WriteHeader(void);
void Sram_ReadHeader(void);
u32 Sram_VerifyHeader(u8 header);
void Sram_ProcessIntroSave(u8 stage);
void Sram_WriteHeaderAndGameInfo(void);
void Sram_ProcessEndingSave(u8 stage);
void Sram_CopyGameCompletion(void);
void Sram_QuickSave(u8 stage);
void SramWrite_ToEwram(void);
void SramRead_FromEwram(void);
void Sram_StringCopy_MetroidEpisode4A(u8* dst, const u8* src);
void Sram_StringCopy_SAVE_END(u8* dst, const u8* src);
void SramTestFlash(void);
void Sram_BackupCurrentFile_Unused(void);
void unk_7fb84(void);
void unk_7fd10(void);
s32 unk_7fdb0(u8 useBackup);
void SramLoad_CurrentSave(void);
void SramLoad_CurrentSave_Unused(void);
void SramWrite_WorldData(void);
void SramRead_WorldData(void);
void SramWrite_MostRecentSaveFile(void);
void SramRead_MostRecentSaveFile(void);
void SramWrite_Language(void);
void SramRead_Language(void);

#endif /* SAVE_FILE_H */
