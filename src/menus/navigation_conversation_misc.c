#include "menus/navigation_conversation.h"
#include "menus/pause_screen.h"

#include "gba.h"
#include "globals.h"

#include "constants/menus/pause_screen.h"

#include "structs/menus/pause_screen.h"

/**
 * @brief 7ae54 | 138 | Sets up the OAM of a navigation conversation
 * 
 */
void NavigationConversationSetupOam(void)
{
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_OUTLINE].xPosition = 0x7C;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_OUTLINE].yPosition = 0xCC;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_LIGHT].oamId = PAUSE_OAM_ID_ADAM_TEXT_BOX_LIGHT_OFF;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_LIGHT].animationDurationCounter = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_LIGHT].currentAnimationFrame = 0;

    NavConversationSetBottomTextBoxOam(1);

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_BACKGROUND].objMode = 1;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_CURSOR].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_CURSOR].objMode = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_LIGHT].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_LIGHT].objMode = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_OUTLINE].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_OUTLINE].objMode = 0;

    *(struct NavConversationPopUpInfo*)&PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer =
        *(const struct NavConversationPopUpInfo*)sNavConversationUnk_5766d4;

    PAUSE_SCREEN_DATA.unk_1A = 0;
    PAUSE_SCREEN_DATA.typeFlags = 0;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_BACKGROUND].objMode = 1;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_CURSOR].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_CURSOR].objMode = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_OUTLINE].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_OUTLINE].objMode = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_PORTRAIT].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_PORTRAIT].objMode = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_FED_PORTRAIT_FLICKERING].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_FED_PORTRAIT_FLICKERING].objMode = 0;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_PORTRAIT].xPosition = 0xD4;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_PORTRAIT].yPosition = 0x44;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_FED_PORTRAIT_FLICKERING].xPosition = 0xD4;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_FED_PORTRAIT_FLICKERING].yPosition = 0x44;

    if (PAUSE_SCREEN_DATA.unk_0)
    {
        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_BACKGROUND].priority = 1;
        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_BACKGROUND].priority = 1;
    }
    else
    {
        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_BACKGROUND].priority = 2;
        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_BACKGROUND].priority = 2;
    }
}

/**
 * @brief 7af8c | 70 | Updates the target of a navigation conversation
 * 
 * @param updateOam Update OAM flag
 */
void NavigationConversationUpdateTarget(u8 updateOam)
{
    u8 oamId;

    if (!NavigationConverstionFindTarget())
        return;

    if (!updateOam)
        return;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].animationDurationCounter = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].currentAnimationFrame = 0;

    if (PAUSE_SCREEN_DATA.unk_20F == 1)
        oamId = sNavConversationUnk_5767ec[PAUSE_SCREEN_DATA.navTargetTextDirection];
    else if (PAUSE_SCREEN_DATA.currentArea == 0)
        oamId = PAUSE_OAM_ID_MAP_ELEVATOR_DOWN_ARROWS;
    else
        oamId = PAUSE_OAM_ID_MAP_ELEVATOR_UP_ARROWS;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId = oamId;
}
