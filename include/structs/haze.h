#ifndef HAZE_STRUCTS_H
#define HAZE_STRUCTS_H

#include "types.h"
#include "gba/memory.h"

typedef u32 (*HazeFunc_T)(void);

struct Haze {
    void* pAffected;
    // Size in bytes of the haze values of a frame (copied from gPreviousHazeValues to gHazeValues)
    u16 bufferSize;
    u8 size;
    u8 enabled:7;
    u8 active:1;
};

struct HazeLoop {
    s16 timer;
    u8 unk_2;
    // Loops 0 and 1: how much the wave offset advances this frame, loop 2: intensity (row of the haze table)
    u8 value;
};

#ifdef USE_EWRAM_SYMBOLS
extern u16 gHazeValues[1280];
extern u16 gPreviousHazeValues[1280];
#else
#define gHazeValues CAST_TO_ARRAY(u16, [1280], EWRAM_BASE + 0x24000)
#define gPreviousHazeValues CAST_TO_ARRAY(u16, [1280], EWRAM_BASE + 0x24a00)
#endif // USE_EWRAM_SYMBOLS

extern u8 gCurrentHazeValue;
extern struct Haze gHazeInfo;

extern struct HazeLoop gHazeLoops[3];
// Scrolling offset of the haze wave (inside the effect for Haze_Bg3StrongWeak)
extern u8 gHazeWaveOffset;
// Scrolling offset of the weak haze wave outside the effect (Haze_Bg3StrongWeak)
extern u8 gHazeWaveOffsetOutside;
extern HazeFunc_T gHazeProcessCodePointer;

#endif /* HAZE_STRUCTS_H */
