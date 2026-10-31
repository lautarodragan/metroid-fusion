#ifndef FILE_SELECT_H
#define FILE_SELECT_H

#include "types.h"
#include "structs/menus/file_select.h"

u32 FileSelectHandler(void);
void FileSelectInit(void);
void FileSelectVblank(void);
void FileSelectVblank_Empty(void);
u32 FileSelectInput(void);
u8 FileSelectSetupOam(u8 type, s16 xPosition, s16 yPosition, u8 unk);
void FileSelectProcessSamusHead(struct FileSelectOam* pOam);
void FileSelectProcessCursor(struct FileSelectOam* pOam);
void FileSelectProcessCopyArrow(struct FileSelectOam* pOam);
void FileSelectProcessCopyConfirmCursor(struct FileSelectOam* pOam);
void FileSelectProcessEraseConfirmCursor(struct FileSelectOam* pOam);
void FileSelectProcessAudioLogos(struct FileSelectOam* pOam);
void FileSelectProcessAudioSelect(struct FileSelectOam* pOam);
void FileSelectProcessFileOverlay(struct FileSelectOam* pOam);
void FileSelectProcessFileHighlight(struct FileSelectOam* pOam);
void FileSelectProcessCorruptionObject_Empty(struct FileSelectOam* pOam);
void FileSelectProcessFileActionPanel(struct FileSelectOam* pOam);
void FileSelectProcessCopyFilePanel(struct FileSelectOam* pOam);
void FileSelectProcessEraseFilePanel(struct FileSelectOam* pOam);
void FileSelectProcessContinueStartOverPanel(struct FileSelectOam* pOam);
void FileSelectProcessContinueStartOverCursor(struct FileSelectOam* pOam);
void FileSelectProcessOam_Empty(struct FileSelectOam* pOam);
void FileSelectDrawFileInfo(u8 file);
void FileSelectDrawText(u8 text);
u32 FileSelectProcessCorruptedFile(void);
void FileSelectDrawFileCorruptedText(u8 file);
void FileSelectDrawCorruptionText(u8 text);
void FileSelectDestroyOamOfType(u8 type);
void FileSelectSetUpAreaNameOam(u8 type, s16 xPosition, s16 yPosition, s16 area);
void FileSelectProcessOam(void);
void FileSelectDrawAllOam(void);
void FileSelectDrawOam(struct FileSelectOam* pOam);
u32 SetLanguage(u8 unk);
void LanguageSelectInit_Unused(void);
void LanguageSelectVblank_Empty(void);
u32 LanguageSelectHandler_Unused(void);

void Sram_WriteFileInfo(void);
void Sram_SetCurrentFile(u8 file);
void Sram_CheckLoadSaveFile(void);
void Sram_CopyFile(u8 file, u8 stage);
void Sram_EraseFile(u8 stage);

#endif /* FILE_SELECT_H */
