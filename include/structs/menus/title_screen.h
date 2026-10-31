#ifndef TITLE_SCREEN_STRUCTS_H
#define TITLE_SCREEN_STRUCTS_H

#include "types.h"
#include "oam.h"

struct TitleScreenObject;
typedef void (*TitleScreenObjectFunc_T)(struct TitleScreenObject*);

struct TitleScreenObject {
    u16 xPosition;
    u16 yPosition;
    u8 section;
    u8 paletteRow; // Palette cycling index
    u8 isDrawn;
    u8 currentAnimationFrame;
    u8 animationDurationCounter;
    u8 timer;
    u8 action;
    u8 objMode;
    u8 unk_C;
    const struct FrameData* pOam;
    TitleScreenObjectFunc_T pHandler;
};

struct TitleScreenData {
    u16 timer;
    u16 idleTimer; // Frames without input, starts the demo at 1200
    u8 startDemo;
    u8 stage;
    u8 padding_6[6];
    struct TitleScreenObject objects[4];
};

#endif /* TITLE_SCREEN_STRUCTS_H */
