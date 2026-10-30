#ifndef LAGMETER_H
#define LAGMETER_H

/*
 * Lag meter for real hardware (make LAGMETER=1, *_lagmeter.gba). Measurement tooling: the
 * normal build does not contain any of it.
 *
 * - Counts lag frames: the V-blank interrupt counts video frames, and the main loop compares
 *   that count once per logic frame (a logic frame that spans n video frames lagged n - 1
 *   frames, the same definition as tests/emu/lag.py).
 * - Times every logic frame with timers 2 and 3 chained (cycles from the start of the main
 *   loop to the V-blank wait, interrupts included, like PROFILE=1).
 * - Keeps per-room totals of the frames played in each room (game mode in game, sub mode
 *   playing) and writes them to save memory when Samus leaves the room (door, pause, death,
 *   cutscene...), in two areas of SRAM that the game never uses (see below). Frames in other
 *   modes (menus, pause, room loads, cutscenes) go to separate totals.
 * - Shows a small counter in the bottom left corner while playing: lag frames in this room
 *   (since entering it) / lag frames in total (all sessions). L+R+SELECT cycles through
 *   off / counter / counter and the highest frame load of the last second, in percent.
 *
 * tools/lagmeter_report.py reads the .sav and prints the tables.
 *
 * SRAM layout (the game uses 0x0000-0x01FF, the six files at 0x0200-0x6FFF, 0x7000-0x70BF,
 * 0x7100-0x717F, 0x7800-0x7BFF, 0x7FE0-0x7FFF):
 *   0x7180  header (struct LagMeterSramHeader, 32 bytes)
 *   0x71A0  records 0 to 271 (6 bytes each, up to 0x7800)
 *   0x7C00  records 272 to 393
 * Record index: sum of the room counts of the previous areas + room.
 */

#include "types.h"

#define LAGMETER_MAGIC 0x4D47414C // "LAGM"
#define LAGMETER_VERSION 1

#define LAGMETER_SRAM_HEADER 0x7180
#define LAGMETER_SRAM_RECORDS_A 0x71A0
#define LAGMETER_SRAM_RECORDS_A_COUNT 272
#define LAGMETER_SRAM_RECORDS_B 0x7C00
#define LAGMETER_RECORD_SIZE 6
#define LAGMETER_AREAS 10
#define LAGMETER_RECORDS 394

// One logic frame of the room's totals is 16 frames in the record (rounded)
#define LAGMETER_FRAME_UNIT_SHIFT 4

struct LagMeterSramHeader {
    u32 magic;
    u8 version;
    u8 areas;
    u16 records;
    u16 boots;              // power-ons (and soft resets) with this build
    u8 worstStreak;         // most consecutive lagging logic frames while playing
    u8 maxLoad;             // highest logic frame load while playing (percent of a frame)
    u32 playLogicFrames;    // logic frames played (in game, playing)
    u32 playLagFrames;      // lag frames while playing
    u32 otherLogicFrames;   // logic frames in the other modes
    u32 otherLagFrames;     // lag frames in the other modes
    u32 playLaggingFrames;  // logic frames that lagged while playing
};

/*
 * Room record (6 bytes, little endian):
 *   u16 lag frames (saturates at 65535)
 *   u16 logic frames played / 16 (rounded per visit, saturates)
 *   u8  worst streak (most consecutive lagging logic frames)
 *   u8  highest load (percent of a frame, saturates at 255)
 */

#ifdef LAGMETER

struct LagMeter {
    vu32 vblanks;           // incremented by the V-blank interrupt
    u32 lastVblanks;
    u32 loopStart;
    u32 lastCycles;         // duration of the last logic frame
    u32 windowMaxCycles;    // highest duration in the current window (display)
    u32 shownMaxCycles;     // highest duration of the last full window
    u32 roomLogic;          // this visit
    u32 roomLag;
    u32 roomMaxCycles;
    u32 roomLagging;        // logic frames that lagged in this visit
    u32 pendingOtherLogic;  // not yet added to the SRAM header
    u32 pendingOtherLag;
    u32 totalLag;           // shown: lag frames played in total (SRAM + pending + room)
    u8 started;
    u8 tracking;            // a room is being tracked (the last logic frame was played)
    u8 area;
    u8 room;
    u8 streak;
    u8 roomWorstStreak;
    u8 display;             // 0 off, 1 counter, 2 counter and load
    u8 dirty;               // the text changed
    u8 windowFrames;
    u8 vramTimer;
    u8 ownedTiles;          // tiles that hold the counter or the debug graphics (bit per tile)
    u8 pad[3];
    u8 text[16];            // characters (index in the font) to show
    u8 written[16];         // characters in VRAM
};

extern struct LagMeter gLagMeter;

void LagMeterInit(void);
void LagMeterStartFrame(void);
void LagMeterEndFrame(void);

static inline u32 LagMeterReadTimer(void)
{
    u32 hi;
    u32 lo;

    do {
        hi = *(vu16*)0x400010C; // TM3CNT_L
        lo = *(vu16*)0x4000108; // TM2CNT_L
    } while (hi != *(vu16*)0x400010C);

    return hi << 16 | lo;
}

#define LAGMETER_VBLANK() do { gLagMeter.vblanks++; } while (0)

#endif // LAGMETER

#endif /* LAGMETER_H */
