#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "types.h"
#include "structs/menus/title_screen.h"

s32 TitleScreenHandler_Unused(void);
void TitleScreenInit_Unused(void);
void TitleScreenVblank(void);
void TitleScreenVblank_Empty(void);
s32 TitleScreenProcessInput_Unused(void);
u8 TitleScreenSetupObject(u8 section, u16 xPosition, u16 yPosition);
void TitleScreenProcessCyclingObject_Unused(struct TitleScreenObject* pObject);
void TitleScreenProcessPressStart(struct TitleScreenObject* pObject);
void TitleScreenProcessLanguage(struct TitleScreenObject* pObject);
void TitleScreenProcessSection4(struct TitleScreenObject* pObject);
void TitleScreenDrawAllObjects(void);
void TitleScreenDrawObject(struct TitleScreenObject* pObject);
void TitleScreenCallObjectsHandler(void);
void TitleScreenProcessCopyright(struct TitleScreenObject* pObject);
void TitleScreenInit(void);
s32 TitleScreenSpawningIn(void);
s32 TitleScreenHandler(void);
void TitleScreenDrawDebugText(const u8* src, u16* dst, u8 palette);

#endif /* TITLE_SCREEN_H */
