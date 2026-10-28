#include "menus/easy_sleep_menu.h"
#include "audio_wrappers.h"
#include "globals.h"
#include "io.h"
#include "syscalls.h"

#include "constants/audio.h"
#include "constants/menus/pause_screen.h"

#include "gba/display.h"
#include "gba/interrupt.h"
#include "gba/keys.h"

#include "structs/menus/pause_screen.h"

enum EasySleepMenuStage {
    EASY_SLEEP_STAGE_CURSOR_ON_NO,
    EASY_SLEEP_STAGE_CURSOR_ON_YES,
    EASY_SLEEP_STAGE_DELAY,
    EASY_SLEEP_STAGE_BLANK_SCREEN,
    EASY_SLEEP_STAGE_SLEEP,
    EASY_SLEEP_STAGE_WAIT_FOR_RELEASE
};

/**
 * @brief 7ed20 | 184 | Handles the easy sleep menu
 * 
 * @return u32 bool, exiting
 */
u32 EasySleepMenuHandler(void)
{
    u32 exiting;
    u16 ie;

    exiting = FALSE;

    switch (PAUSE_SCREEN_DATA.subMenuStage)
    {
        case EASY_SLEEP_STAGE_CURSOR_ON_NO:
            if (gChangedInput & KEY_A)
            {
                SoundPlay(SOUND_1FB);
                exiting = TRUE;
            }
            else if (gChangedInput & KEY_LEFT)
            {
                PAUSE_SCREEN_DATA.subMenuStage = EASY_SLEEP_STAGE_CURSOR_ON_YES;
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_CURSOR].xPosition = 0x3C;
                SoundPlay(SOUND_1FA);
            }
            else if (gChangedInput & (KEY_B | KEY_L | KEY_R))
            {
                exiting = TRUE;
            }
            break;

        case EASY_SLEEP_STAGE_CURSOR_ON_YES:
            if (gChangedInput & KEY_A)
            {
                SoundPlay(SOUND_1FB);
                PAUSE_SCREEN_DATA.subMenuStage = EASY_SLEEP_STAGE_DELAY;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            else if (gChangedInput & KEY_RIGHT)
            {
                PAUSE_SCREEN_DATA.subMenuStage = EASY_SLEEP_STAGE_CURSOR_ON_NO;
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_CURSOR].xPosition = 0x8C;
                SoundPlay(SOUND_1FA);
            }
            else if (gChangedInput & (KEY_B | KEY_L | KEY_R))
            {
                exiting = TRUE;
            }
            break;

        case EASY_SLEEP_STAGE_DELAY:
            PAUSE_SCREEN_DATA.timer++;
            if (PAUSE_SCREEN_DATA.timer > 30)
            {
                PAUSE_SCREEN_DATA.subMenuStage++;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case EASY_SLEEP_STAGE_BLANK_SCREEN:
            PAUSE_SCREEN_DATA.dispcnt ^= DCNT_BLANK;
            PAUSE_SCREEN_DATA.subMenuStage++;
            break;

        case EASY_SLEEP_STAGE_SLEEP:
            // Wake up on L + R + Select
            WRITE_16(REG_KEY_CONTROL, KEY_CONTROL_ALL_INPUTS | KEY_CONTROL_ENABLE | KEY_L | KEY_R | KEY_SELECT);
            WRITE_16(REG_IME, FALSE);
            ie = READ_16(REG_IE);
            WRITE_16(REG_IE, IF_KEYPAD | IF_GAMEPAK);
            WRITE_16(REG_IME, TRUE);

            SoundBias0();
            SYSCALL(3); /* SYSCALL_Stop */
            SoundBias1();

            WRITE_16(REG_IME, FALSE);
            WRITE_16(REG_IE, ie);
            WRITE_16(REG_IME, TRUE);

            PAUSE_SCREEN_DATA.dispcnt ^= DCNT_BLANK;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_CURSOR].xPosition = 0x8C;
            PAUSE_SCREEN_DATA.subMenuStage++;
            break;

        case EASY_SLEEP_STAGE_WAIT_FOR_RELEASE:
            if (gButtonInput == KEY_NONE)
                PAUSE_SCREEN_DATA.subMenuStage = EASY_SLEEP_STAGE_CURSOR_ON_NO;
            break;
    }

    if (exiting)
    {
        PAUSE_SCREEN_DATA.subMenuStage = 0;
        PAUSE_SCREEN_DATA.timer = 0;
    }

    return exiting;
}
