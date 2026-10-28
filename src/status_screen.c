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
 * @brief 7e678 | 34 | Handler for the status screen
 * 
 */
void StatusScreenHandler(void)
{
    if ((gChangedInput & (KEY_B | KEY_L | KEY_R)) && !gNonGameplayRam.pauseScreen.subMenuStage) 
    {
        gNonGameplayRam.pauseScreen.unk_28.unk_0 = 7;
        gNonGameplayRam.pauseScreen.timer = 0;
        gNonGameplayRam.pauseScreen.subMenuStage = 0;
    }
}

/**
 * @brief 7e6ac | a8 | Draws everything on the status screen menu
 * 
 */
void StatusScreenDrawEverything(void)
{
    StatusScreenDrawBeamOrSuit(STATUS_SECTION_BEAM, gEquipment.beamStatus);
    StatusScreenDrawMissileOrBomb(STATUS_SECTION_MISSILE, gEquipment.weaponsStatus);
    StatusScreenDrawBeamOrSuit(STATUS_SECTION_SUIT, gEquipment.suitMiscStatus);
    StatusScreenDrawMissileOrBomb(STATUS_SECTION_BOMB, gEquipment.weaponsStatus);
    StatusScreenDrawMisc(STATUS_SECTION_MISC, gEquipment.suitMiscStatus);
    StatusScreenDrawNumber(STATUS_SECTION_ENERGY_CURRENT, gEquipment.currentEnergy, 6, FALSE);
    StatusScreenDrawNumber(STATUS_SECTION_ENERGY_MAX, gEquipment.maxEnergy, 3, TRUE);

    if (gEquipment.weaponsStatus & MBF_MISSILES)
    {
        StatusScreenDrawNumber(STATUS_SECTION_MISSILES_CURRENT, gEquipment.currentMissiles, 6, FALSE);
        StatusScreenDrawNumber(STATUS_SECTION_MISSILES_MAX, gEquipment.maxMissiles, 3, TRUE);
    } 
    else
    {
        StatusScreenRemoveAmmoHeader(1);
    }

    if ((gEquipment.weaponsStatus & (MBF_BOMBS | MBF_POWER_BOMBS)) == (MBF_BOMBS | MBF_POWER_BOMBS))
    {
        StatusScreenDrawNumber(STATUS_SECTION_POWER_BOMBS_CURRENT, gEquipment.currentPowerBombs, 6, FALSE);
        StatusScreenDrawNumber(STATUS_SECTION_POWER_BOMBS_MAX, gEquipment.maxPowerBombs, 3, TRUE);
        return;
    }

    StatusScreenRemoveAmmoHeader(2);
}

/**
 * @brief 7e754 | e0 | Draws a number on the status screen
 * 
 * @param section Section
 * @param value Value
 * @param palette Palette slot
 * @param isMax Bool for current vs max ammo count
 */
void StatusScreenDrawNumber(u8 section, u16 value, u8 palette, boolu8 isMax)
{
    u16* dst;
    s32 width;
    s32 power;
    s32 digit;
    s32 started;
    s32 i;

    // FIXME: Fake match, the empty asm statements only change register allocation priorities
    asm("" : : "r"(palette));
    dst = &STATUS_SCREEN_TILEMAP[STATUS_SCREEN_DST_TOP(section) * HALF_BLOCK_SIZE + STATUS_SCREEN_DST_LEFT(section)];
    width = STATUS_SCREEN_DST_RIGHT(section) - STATUS_SCREEN_DST_LEFT(section);
    power = sPauseDebugNumbersIncrementValues[width];
    width++;
    started = FALSE;
    asm("" : : "r"(started));

    for (i = 0; power > 0; power /= 10, i++)
    {
        digit = value / power % 10;

        if (digit == 0)
        {
            if (!started)
            {
                // Leading zero, blank tile for current values, skipped for max values
                digit = 0x8C;
                if (isMax)
                    digit = 0;
            }
            else
            {
                digit = 0x80;
            }
        }
        else
        {
            started = TRUE;
            digit += 0x80;
        }

        if (digit != 0)
            dst[i] = palette << 12 | digit;
        else
            i--;
    }

    for (; width != i; i++)
        dst[i] = palette << 12 | 0x8C;
}

/**
 * @brief 7e834 | 148 | Draws the beam or suit section of the status screen
 * 
 * @param section Section
 * @param value Acquired items flags
 */
void StatusScreenDrawBeamOrSuit(u8 section, u8 value)
{
    s32 i;
    s32 j;
    s32 last;
    s32 dstPos;
    s32 srcPos;
    u16* tilemap;

    tilemap = STATUS_SCREEN_TILEMAP;
    last = 0;
    for (i = 0; i < sStatusScreenSectionSizes[section]; i++)
    {
        dstPos = (STATUS_SCREEN_DST_TOP(section) + (i + 1)) * HALF_BLOCK_SIZE + STATUS_SCREEN_DST_LEFT(section);
        srcPos = (STATUS_SCREEN_SRC_TOP(section) + (i + 1)) * HALF_BLOCK_SIZE + STATUS_SCREEN_SRC_LEFT(section);

        if (sPauseDebugItemFlagsPointers[section][i] & value)
        {
            last = i + 1;
            for (j = 0; j <= STATUS_SCREEN_DST_RIGHT(section) - STATUS_SCREEN_DST_LEFT(section); j++)
                tilemap[dstPos + j] = tilemap[srcPos + j];
        }
    }

    if (last != 0)
    {
        // Draw the bottom of the section after the last acquired item
        dstPos = (STATUS_SCREEN_DST_TOP(section) + 1 + last) * HALF_BLOCK_SIZE + STATUS_SCREEN_DST_LEFT(section);
        srcPos = STATUS_SCREEN_SRC_BOTTOM(section) * HALF_BLOCK_SIZE + STATUS_SCREEN_SRC_LEFT(section);

        for (j = 0; j <= STATUS_SCREEN_DST_RIGHT(section) - STATUS_SCREEN_DST_LEFT(section); j++)
            tilemap[dstPos + j] = tilemap[srcPos + j];
    }
}

/**
 * @brief 7e97c | 15c | Draws the missile or bomb section of the status screen
 *
 * @param section Section
 * @param value Acquired items flags
 */
void StatusScreenDrawMissileOrBomb(u8 section, u8 value)
{
    s32 i;
    s32 j;
    s32 last;
    s32 dstPos;
    s32 srcPos;
    u16* tilemap;

    tilemap = STATUS_SCREEN_TILEMAP;
    last = -1;
    for (i = 0; i < sStatusScreenSectionSizes[section]; i++)
    {
        dstPos = (STATUS_SCREEN_DST_TOP(section) + i) * HALF_BLOCK_SIZE + STATUS_SCREEN_DST_LEFT(section);
        srcPos = (STATUS_SCREEN_SRC_TOP(section) + i) * HALF_BLOCK_SIZE + STATUS_SCREEN_SRC_LEFT(section);

        if (sPauseDebugItemFlagsPointers[section][i] & value)
        {
            last = i;
            for (j = 0; j <= STATUS_SCREEN_DST_RIGHT(section) - STATUS_SCREEN_DST_LEFT(section); j++)
                tilemap[dstPos + j] = tilemap[srcPos + j];
        }
        else if (i == 0)
        {
            // The base item isn't acquired, draw nothing
            return;
        }
    }

    if (last >= 0)
    {
        // Draw the bottom of the section after the last acquired item
        dstPos = (STATUS_SCREEN_DST_TOP(section) + 1 + last) * HALF_BLOCK_SIZE + STATUS_SCREEN_DST_LEFT(section);
        srcPos = STATUS_SCREEN_SRC_BOTTOM(section) * HALF_BLOCK_SIZE + STATUS_SCREEN_SRC_LEFT(section);

        for (j = 0; j <= STATUS_SCREEN_DST_RIGHT(section) - STATUS_SCREEN_DST_LEFT(section); j++)
            tilemap[dstPos + j] = tilemap[srcPos + j];
    }
}
