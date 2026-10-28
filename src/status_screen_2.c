#include "status_screen.h"
#include "globals.h"
#include "gba/memory.h"
#include "types.h"

#include "data/menus/pause_screen_misc_data.h"
#include "data/menus/status_screen_data.h"

#include "constants/samus.h"
#include "constants/status_screen.h"

#include "gba/keys.h"

#include "structs/samus.h"

#define STATUS_SCREEN_TILEMAP ((u16*)(VRAM_BASE + 0xC800))

/**
 * @brief 7ec8c | 94 | Removes an ammo header from the status screen
 *
 * @param position 1 for missiles 2 for power bombs
 */
void StatusScreenRemoveAmmoHeader(u8 position)
{
    s32 i;
    s32 j;
    s32 row;
    s32 dstPos;
    s32 srcPos;
    u16* tilemap;

    if (position == 1)
        row = 1;
    else if (position == 2)
        row = 2;
    else
        return;

    tilemap = STATUS_SCREEN_TILEMAP;
    // FIXME: Fake match, the empty asm statement only changes the register allocation priority of tilemap
    asm("" : : "r"(tilemap));

    for (i = 0; i < 2; i++)
    {
        // Overwrite the ammo header with the empty header
        dstPos = (STATUS_SCREEN_HEADER_TOP(row) + i) * HALF_BLOCK_SIZE + STATUS_SCREEN_HEADER_LEFT(row);
        srcPos = (STATUS_SCREEN_HEADER_TOP(0) + i) * HALF_BLOCK_SIZE + STATUS_SCREEN_HEADER_LEFT(0);

        for (j = 0; j <= STATUS_SCREEN_HEADER_RIGHT(0) - STATUS_SCREEN_HEADER_LEFT(0); j++)
            tilemap[dstPos + j] = STATUS_SCREEN_TILEMAP[srcPos + j];
    }
}
