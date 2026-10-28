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
