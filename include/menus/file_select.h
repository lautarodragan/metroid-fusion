#ifndef FILE_SELECT_H
#define FILE_SELECT_H

#include "types.h"
#include "structs/menus/file_select.h"

u32 FileSelectHandler(void);
void FileSelectInit(void);
void FileSelectVblank(void);
void unk_9eaa4(void);
u32 FileSelectInput(void);
u8 FileSelectSetupOam(u8 type, s16 xPosition, s16 yPosition, u8 unk);
void FileSelectProcessSamusHead(struct FileSelectOam* pOam);
void FileSelectProcessCursor(struct FileSelectOam* pOam);
void FileSelectProcessDeleteArrow(struct FileSelectOam* pOam);
void unk_9fddc(struct FileSelectOam* pOam);
void unk_9ff00(struct FileSelectOam* pOam);
void FileSelectProcessAudioLogos(struct FileSelectOam* pOam);
void FileSelectProcessAudioSelect(struct FileSelectOam* pOam);
void FileSelectProcessFileOverlay(struct FileSelectOam* pOam);
void unk_a016c(struct FileSelectOam* pOam);
void unk_a01cc(struct FileSelectOam* pOam);
void FileSelectProcessFileActionPanel(struct FileSelectOam* pOam);
void FileSelectProcessCopyFilePanel(struct FileSelectOam* pOam);
void FileSelectProcessEraseFilePanel(struct FileSelectOam* pOam);
void unk_a039c(struct FileSelectOam* pOam);
void unk_a0424(struct FileSelectOam* pOam);
void unk_a0518(struct FileSelectOam* pOam);
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
void unk_a13e0(void);
void unk_a1478(void);
u32 unk_a147c(void);

void Sram_WriteFileInfo(void);
void Sram_SetCurrentFile(u8 file);

#endif /* FILE_SELECT_H */
