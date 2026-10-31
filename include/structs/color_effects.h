#ifndef COLOR_EFFECTS_STRUCT_H
#define COLOR_EFFECTS_STRUCT_H

#include "types.h"

#include "constants/color_fading.h"

// Structs

struct ColorFading {
    ColorFadingEffect type;
    u8 stage;
    u8 fadeTimer;
    u8 timer;
    ColorFadingStatus status;
    u8 usePalette3:4;
    u16 workTimer;
};

ASSERT_OFFSET(struct ColorFading, workTimer, 0x6);
ASSERT_SIZE(struct ColorFading, 0x8);

struct ColorFadingColorInfo {
    const u8* const colorArray;
    u8 size;
};

struct ColorMultiplier {
    s32 red;
    s32 green;
    s32 blue;
};

// Globals

extern struct ColorFading gColorFading;

#endif /* COLOR_EFFECTS_STRUCT_H */
