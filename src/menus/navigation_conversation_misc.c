#include "menus/navigation_conversation.h"
#include "menus/pause_screen.h"

#include "gba.h"
#include "globals.h"

#include "constants/menus/pause_screen.h"

#include "data/event_data.h"

#include "structs/event.h"
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

/**
 * @brief 7affc | 15c | Finds the target of the current navigation conversation
 * 
 * @return bool, conversation already happened
 */
u32 NavigationConverstionFindTarget(void)
{
    u32 found;
    u32 i;
    u8 x;
    u8 y;

    PAUSE_SCREEN_DATA.unk_20F = 0;
    PAUSE_SCREEN_DATA.navTargetX = UCHAR_MAX;
    PAUSE_SCREEN_DATA.navTargetY = -1;
    PAUSE_SCREEN_DATA.navTargetArea = 0;
    PAUSE_SCREEN_DATA.navTargetTextDirection = 0;

    if (gPauseScreenFlag == 4)
        return FALSE;

    gNavigationTargetLocation = 0;
    found = FALSE;

    for (i = 0; i <= 32; i++)
    {
        if (PAUSE_SCREEN_DATA.conversationNumber == sNavConversationUnk_5766e4[i].conversation)
        {
            found = TRUE;
            PAUSE_SCREEN_DATA.navTargetTextDirection = sNavConversationUnk_5766e4[i].textDirection;
            break;
        }
    }

    if (!found)
        return FALSE;

    gNavigationTargetLocation = sNavConversationUnk_5766e4[i].location;
    PAUSE_SCREEN_DATA.navTargetArea = sNavigationTargetLocationAreas[gNavigationTargetLocation];

    if (PAUSE_SCREEN_DATA.currentArea == PAUSE_SCREEN_DATA.navTargetArea)
    {
        x = sNavConversationUnk_5766e4[i].xPosition;
        y = sNavConversationUnk_5766e4[i].yPosition;
        PAUSE_SCREEN_DATA.unk_20F = 1;
    }
    else if (PAUSE_SCREEN_DATA.currentArea == 0)
    {
        x = sNavConversationUnk_576218[PAUSE_SCREEN_DATA.navTargetArea][0];
        y = sNavConversationUnk_576218[PAUSE_SCREEN_DATA.navTargetArea][1];
        PAUSE_SCREEN_DATA.unk_20F = 2;
    }
    else
    {
        x = sNavConversationUnk_576226[PAUSE_SCREEN_DATA.currentArea][0];
        y = sNavConversationUnk_576226[PAUSE_SCREEN_DATA.currentArea][1];
        if (PAUSE_SCREEN_DATA.navTargetArea == 0)
            PAUSE_SCREEN_DATA.unk_20F = 2;
        else
            PAUSE_SCREEN_DATA.unk_20F = 3;
    }

    PAUSE_SCREEN_DATA.navTargetX = x - 1;
    PAUSE_SCREEN_DATA.navTargetY = y - 1;

    found = FALSE;
    if (gPreviousNavigationConversation == PAUSE_SCREEN_DATA.conversationNumber)
        found = TRUE;

    return found;
}
