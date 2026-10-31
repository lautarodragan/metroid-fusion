#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include "types.h"

/*
 * Performance changes of the OPTIMIZE build (make OPTIMIZE=1, or
 * OPTIMIZE="NAME ..." for some of them; see book/src/performance.md).
 *
 * Each change is enabled by its own OPTIMIZE_<NAME> define and keeps the
 * game's behavior: same logic per logic frame, same RAM at every logic-frame
 * boundary, only fewer cycles. Without OPTIMIZE the code is the original
 * (the normal build matches the ROM).
 *
 * - OPTIMIZE_PROJ_HIT: ProjectileCheckHittingSprite visits the sprites in
 *   draw order with one sorted list instead of scanning the 24 slots for
 *   each of the 16 draw orders, and checks only the projectiles that can hit
 *   (rebuilt after every hit, since a hit can spawn or remove projectiles).
 * - OPTIMIZE_DRAW_ORDER: the same for the 3 sprite drawing passes
 *   (SpriteDrawAllHighPriority, SpriteDrawAll, SpriteDrawAllBehindSamus).
 * - OPTIMIZE_IWRAM: functions marked IWRAM_CODE run from IWRAM (one cycle per
 *   16-bit fetch, no cartridge wait states) instead of ROM; the code is the
 *   same. They are linked in the .iwram_code section (linker.ld, after the
 *   profiler's area) and copied there by InitializeGame. Their files are
 *   compiled with -mlong-calls (see the Makefile and tools/iwram_calls.py).
 */

#ifdef OPTIMIZE_IWRAM
#define IWRAM_CODE __attribute__((section(".iwram_code")))

extern const u8 gIwramCodeLoad[];
extern u8 gIwramCodeStart[];
extern u8 gIwramCodeEnd[];
#else
#define IWRAM_CODE
#endif

#endif /* OPTIMIZE_H */
