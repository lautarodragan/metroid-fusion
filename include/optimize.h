#ifndef OPTIMIZE_H
#define OPTIMIZE_H

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
 *   (unk_eb04, SpriteDrawAll, unk_ec38).
 */

#endif /* OPTIMIZE_H */
