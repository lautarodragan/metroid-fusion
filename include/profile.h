#ifndef PROFILE_H
#define PROFILE_H

/*
 * Cycle profiler for the PROFILE build (make PROFILE=1).
 *
 * Timers 2 and 3 (unused by the game, which only uses timer 0 for the sound)
 * are chained into a free-running 32-bit counter at the CPU clock
 * (16.78 MHz, one tick per cycle). Code regions are timed with
 * PROFILE_START/PROFILE_END, which subtract the time spent in interrupt
 * handlers meanwhile, so every region reports its own CPU cycles. The
 * results of the last logic frame are in gProfile.last (a free area of
 * IWRAM, see linker.ld), copied there right before the main loop waits for
 * V-blank; the emulator harness reads them at every logic-frame boundary
 * (tests/emu/lag.py). A video frame is 280,896 cycles.
 *
 * Two levels:
 * - PROFILE=1 (-DPROFILE): only the whole logic frame, the sound update, the
 *   in-game handler and the V-blank handler are timed (PROFILE_FRAME_CALL),
 *   so the game code runs as in the normal build (a few hundred cycles of
 *   overhead per frame). Use it for frame totals.
 * - PROFILE=2 (-DPROFILE -DPROFILE_DETAIL): also every subsystem of the
 *   in-game handler and every sprite (PROFILE_CALL, PROFILE_DETAIL blocks).
 *   The probes cost cycles and registers in the loops they are in, so the
 *   totals are higher than in the normal build; use it for the breakdown.
 *
 * Without PROFILE every macro expands to nothing (or to the plain call), so
 * the normal build is unchanged.
 */

#include "types.h"

#define PROFILE_MAGIC 0x464f5250 // "PROF"

enum ProfileRegion {
    PROF_LOOP,                  // the whole logic frame: main loop start to the V-blank wait (with interrupts)
    PROF_AUDIO,                 // UpdateAudio in the main loop
    PROF_HANDLER,               // InGameHandler
    PROF_SAMUS_PHYSICS,         // SamusUpdatePhysics + SamusUpdateCollisionData
    PROF_ROOM_ANIM,             // RoomUpdateAnimatedGraphicsAndPalette
    PROF_SPRITE_UPDATE,         // SpriteUpdate (with everything below it)
    PROF_SPRITE_DEBRIS,         // SpriteDebrisUpdateAll
    PROF_SPRITE_SAMUS_COLLISION,// SpriteUtilSamusAndSpriteCollision
    PROF_SPRITE_AI,             // sprite AI calls (sum)
    PROF_SPRITE_ANIM,           // standing on sprite + animation + on screen check (sum)
    PROF_SPRITE_COPY,           // copies to/from gCurrentSprite in SpriteUpdate (sum)
    PROF_SCROLL,                // ScrollProcessGeneral
    PROF_SAMUS_GFX,             // SamusCallUpdateGraphics
    PROF_PROJ_UPDATE,           // ProjectileUpdate (with the hit checks)
    PROF_PROJ_HIT,              // ProjectileCheckHittingSprite
    PROF_HUD,                   // HudDraw
    PROF_DRAW_HIGH,             // SpriteDrawAllHighPriority (sprites with high priority)
    PROF_PARTICLE,              // ParticleUpdate
    PROF_PROJ_DRAW,             // ProjectileDrawAll_False + ProjectileDrawAll_True
    PROF_DRAW_ALL,              // SpriteDrawAll (debris, SA-X, sprites with draw order 1-8)
    PROF_SAMUS_DRAW,            // SamusDraw
    PROF_DRAW_LOW,              // SpriteDrawAllBehindSamus (sprites with draw order 9-16)
    PROF_SPRITE_DRAW,           // SpriteDraw calls (sum, in the 3 above)
    PROF_RESET_OAM,             // ResetFreeOam
    PROF_ROOM_UPDATE,           // RoomUpdate (with the 2 below)
    PROF_ROOM_TILEMAP,          // background positions and tilemap streaming in RoomUpdate
    PROF_ROOM_CHECKS,           // special clipdata, blocks, hatches, room events in RoomUpdate
    PROF_HAZE,                  // HazeProcess
    PROF_LOW_HEALTH,            // SamusCallCheckPlayLowHealthSound
    PROF_VBLANK,                // V-blank interrupt handler (H-blank handlers are not timed: the
                                // timing overhead starves the main loop in a cutscene whose
                                // H-blank handler runs on every line)
    PROF_SPRITE_DRAW_COUNT,     // number of SpriteDraw calls (not cycles)
    PROF_FIXED_INVERSE_COUNT,   // number of FixedInverse calls (not cycles)

    PROF_COUNT
};

#define PROFILE_SPRITE_SLOTS 24

struct ProfileFrame {
    u32 cycles[PROF_COUNT];
    u32 aiCycles[PROFILE_SPRITE_SLOTS];     // AI of each sprite slot
    u32 drawCycles[PROFILE_SPRITE_SLOTS];   // SpriteDraw of each sprite slot
};

struct Profile {
    u32 magic;
    u32 frames;                 // logic frames profiled
    vu32 isrCycles;             // cycles in interrupt handlers since the start (wraps)
    u32 loopStart;
    struct ProfileFrame cur;
    struct ProfileFrame last;
};

#ifdef PROFILE

extern struct Profile gProfile;

struct ProfileMark {
    u32 time;
    u32 isr;
};

static inline u32 ProfileReadTimer(void)
{
    u32 hi;
    u32 lo;

    do {
        hi = *(vu16*)0x400010C; // TM3CNT_L
        lo = *(vu16*)0x4000108; // TM2CNT_L
    } while (hi != *(vu16*)0x400010C);

    return hi << 16 | lo;
}

void ProfileInit(void);
void ProfileEndFrame(void);

// The time and the interrupt cycles are read again if an interrupt came between the two reads
static inline void ProfileMark(struct ProfileMark* m)
{
    do {
        m->isr = gProfile.isrCycles;
        m->time = ProfileReadTimer();
    } while (m->isr != gProfile.isrCycles);
}

static inline u32 ProfileElapsed(struct ProfileMark* start)
{
    struct ProfileMark now;

    ProfileMark(&now);
    return now.time - start->time - (now.isr - start->isr);
}

#define PROFILE_START(m) ProfileMark(&(m))
#define PROFILE_ELAPSED(m) ProfileElapsed(&(m))
#define PROFILE_END(m, region) do { gProfile.cur.cycles[region] += PROFILE_ELAPSED(m); } while (0)
#define PROFILE_FRAME_CALL(region, call) do { struct ProfileMark _pm; PROFILE_START(_pm); call; PROFILE_END(_pm, region); } while (0)

#ifdef PROFILE_DETAIL
#define PROFILE_CALL(region, call) PROFILE_FRAME_CALL(region, call)
#define PROFILE_COUNT(region) do { gProfile.cur.cycles[region]++; } while (0)
#else
#define PROFILE_CALL(region, call) call
#define PROFILE_COUNT(region)
#endif

// Interrupt handlers: raw time, added to isrCycles
#define PROFILE_ISR_START(t) do { (t) = ProfileReadTimer(); } while (0)
#define PROFILE_ISR_END(t, region) do { u32 _d = ProfileReadTimer() - (t); gProfile.isrCycles += _d; gProfile.cur.cycles[region] += _d; } while (0)

#else // !PROFILE

#define PROFILE_FRAME_CALL(region, call) call
#define PROFILE_CALL(region, call) call
#define PROFILE_COUNT(region)

#endif // PROFILE

#endif /* PROFILE_H */
