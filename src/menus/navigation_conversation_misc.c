#include "menus/navigation_conversation.h"
#include "menus/pause_screen.h"

#include "menus/pause_screen_map.h"

#include "gba.h"
#include "globals.h"
#include "io.h"
#include "audio_wrappers.h"

#include "constants/audio.h"
#include "constants/menus/pause_screen.h"

#include "data/event_data.h"

#include "structs/connection.h"
#include "structs/event.h"
#include "structs/menus/pause_screen.h"
#include "structs/minimap.h"

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

/**
 * @brief 7b158 | 36c | Handles the scrolling of the map to the target of a navigation conversation
 * 
 */
void NavigationConversionScrollToTarget(void)
{
    u32 temp;
    u8 oamId;

    PAUSE_SCREEN_DATA.unk_8++;

    switch (PAUSE_SCREEN_DATA.unk_9)
    {
        case 0:
            break;

        case 1:
            temp = FALSE;
            if (PAUSE_SCREEN_DATA.navTargetX == UCHAR_MAX || PAUSE_SCREEN_DATA.navTargetY == UCHAR_MAX)
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == sNavConversationUnk_5767ec[0])
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == sNavConversationUnk_5767ec[1])
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == sNavConversationUnk_5767ec[2])
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == sNavConversationUnk_5767ec[3])
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == PAUSE_OAM_ID_MAP_ELEVATOR_UP_ARROWS)
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == PAUSE_OAM_ID_MAP_ELEVATOR_DOWN_ARROWS)
                temp = TRUE;

            if (temp)
            {
                PAUSE_SCREEN_DATA.unk_9 = 12;
            }
            else
            {
                PAUSE_SCREEN_DATA.unk_9 = 2;
                PAUSE_SCREEN_DATA.typeFlags |= 0x100;
                PAUSE_SCREEN_DATA.typeFlags |= 0x200;
            }
            break;

        case 2:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x400)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9++;
            }
            break;

        case 3:
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9 = 4;
            break;

        case 5:
            if (!NavigationConversationScrollMapToDestination(PAUSE_SCREEN_DATA.navTargetX, PAUSE_SCREEN_DATA.navTargetY))
                break;

            if (PAUSE_SCREEN_DATA.unk_20F == 1)
                temp = sNavConversationUnk_5767ec[PAUSE_SCREEN_DATA.navTargetTextDirection];
            else if (PAUSE_SCREEN_DATA.currentArea == 0)
                temp = PAUSE_OAM_ID_MAP_ELEVATOR_DOWN_ARROWS;
            else
                temp = PAUSE_OAM_ID_MAP_ELEVATOR_UP_ARROWS;

            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId = temp;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;

            if (PAUSE_SCREEN_DATA.unk_20F == 1)
                PAUSE_SCREEN_DATA.unk_9 = 12;
            else
                PAUSE_SCREEN_DATA.unk_9 = 6;

            SoundStop(SOUND_119);
            PAUSE_SCREEN_DATA.mapViewX = PAUSE_SCREEN_DATA.navTargetX;
            PAUSE_SCREEN_DATA.mapViewY = PAUSE_SCREEN_DATA.navTargetY;
            break;

        case 6:
            if (PAUSE_SCREEN_DATA.unk_8 > 60)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9++;
            }
            break;

        case 7:
            PAUSE_SCREEN_DATA.unk_250 = 1;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].oamId = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 8:
            if (!(PAUSE_SCREEN_DATA.unk_250 & 4))
                break;

            if (PAUSE_SCREEN_DATA.unk_20F == 3)
                PAUSE_SCREEN_DATA.navTargetArea = 0;

            if (PAUSE_SCREEN_DATA.navTargetArea == 0)
            {
                PAUSE_SCREEN_DATA.mapX = sNavConversationUnk_576218[PAUSE_SCREEN_DATA.currentArea][0] - 1;
                PAUSE_SCREEN_DATA.mapY = sNavConversationUnk_576218[PAUSE_SCREEN_DATA.currentArea][1] - 1;
            }
            else
            {
                PAUSE_SCREEN_DATA.mapX = sNavConversationUnk_576226[PAUSE_SCREEN_DATA.navTargetArea][0] - 1;
                PAUSE_SCREEN_DATA.mapY = sNavConversationUnk_576226[PAUSE_SCREEN_DATA.navTargetArea][1] - 1;
            }

            PAUSE_SCREEN_DATA.currentArea = PAUSE_SCREEN_DATA.navTargetArea;
            MinimapGetData(PAUSE_SCREEN_DATA.currentArea, gMinimapData_Visited);
            MinimapSetVisitedTilesAndCollectedItems(PAUSE_SCREEN_DATA.currentArea);
            DMA3_COPY_16(gMinimapData_Visited, VRAM_BASE + 0xE000, MINIMAP_SIZE);
            unk_75988(TRUE);
            NavigationConversationUpdateTarget(FALSE);
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 9:
            if (PAUSE_SCREEN_DATA.unk_8 > 8)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9++;
                PAUSE_SCREEN_DATA.unk_250 |= 8;
            }
            break;

        case 10:
            if (PAUSE_SCREEN_DATA.unk_250 != 0)
                break;

            if (PAUSE_SCREEN_DATA.navTargetArea == 0)
                oamId = PAUSE_OAM_ID_MAP_ELEVATOR_UP_ARROWS;
            else if (PAUSE_SCREEN_DATA.currentArea == 0)
                oamId = PAUSE_OAM_ID_MAP_ELEVATOR_UP_ARROWS;
            else
                oamId = PAUSE_OAM_ID_MAP_ELEVATOR_DOWN_ARROWS;

            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].oamId = oamId;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 4:
        case 11:
            if (PAUSE_SCREEN_DATA.unk_8 > 30)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9 = 5;
                SoundPlay(SOUND_119);
            }
            break;

        case 12:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x200)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x200;
            if (PAUSE_SCREEN_DATA.typeFlags & 0x400)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x400;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 13:
            break;
    }
}

/**
 * @brief 7b4c4 | a8 | Scrolls the map towards a destination
 * 
 * @param x X destination
 * @param y Y destination
 * @return bool, reached
 */
u32 NavigationConversationScrollMapToDestination(u8 x, u8 y)
{
    u32 reached;
    s32 targetX;
    s32 targetY;
    s32 diff;
    s32 diffY;
    s32 speedX;
    s32 speedY;

    reached = TRUE;

    targetX = 0x200 - (15 - x) * 8;
    targetY = 0x200 - (10 - y) * 8;

    diff = gBackgroundPositions.bg[3].x - targetX;
    diffY = gBackgroundPositions.bg[3].y - targetY;

    if (diff < 0)
        diff = -diff;

    if (diffY < 0)
        diffY = -diffY;

    speedX = (diff >> 4) + 1;
    speedY = (diffY >> 4) + 1;

    diff = gBackgroundPositions.bg[3].x - targetX;
    if (diff != 0)
    {
        reached = FALSE;
        if (diff > 0)
        {
            gBackgroundPositions.bg[3].x -= speedX;
            if (gBackgroundPositions.bg[3].x < targetX)
                gBackgroundPositions.bg[3].x = targetX;
        }
        else if (diff < 0)
        {
            gBackgroundPositions.bg[3].x += speedX;
            if (gBackgroundPositions.bg[3].x > targetX)
                gBackgroundPositions.bg[3].x = targetX;
        }
    }

    diff = gBackgroundPositions.bg[3].y - targetY;
    if (diff != 0)
    {
        reached = FALSE;
        if (diff > 0)
        {
            gBackgroundPositions.bg[3].y -= speedY;
            if (gBackgroundPositions.bg[3].y < targetY)
                gBackgroundPositions.bg[3].y = targetY;
        }
        else if (diff < 0)
        {
            gBackgroundPositions.bg[3].y += speedY;
            if (gBackgroundPositions.bg[3].y > targetY)
                gBackgroundPositions.bg[3].y = targetY;
        }
    }

    return reached;
}

/**
 * @brief 7b56c | 108 | Handles the pop up window of a navigation conversation
 * 
 */
void unk_7b56c(void)
{
    PAUSE_SCREEN_DATA.unk_A++;

    switch (PAUSE_SCREEN_DATA.unk_B)
    {
        case 0:
            break;

        case 1:
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B++;
            break;

        case 2:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x40)
            {
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
            }
            break;

        case 3:
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].oamId = PAUSE_OAM_ID_POP_UP_WINDOW;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].currentAnimationFrame = 0;
            SoundPlay(SOUND_11C);
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B++;
            break;

        case 4:
            if (PAUSE_SCREEN_DATA.unk_A > 30)
            {
                PAUSE_SCREEN_DATA.currentPopUp = 1;
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
                PAUSE_SCREEN_DATA.typeFlags |= 0x80;
            }
            break;

        case 5:
            if (!(PAUSE_SCREEN_DATA.typeFlags & 0x40))
            {
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
            }
            break;

        case 6:
            PAUSE_SCREEN_DATA.currentPopUp = 3;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].oamId = PAUSE_OAM_ID_POP_UP_WINDOW_CLOSING;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].currentAnimationFrame = 0;
            SoundPlay(SOUND_11D);
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B++;
            break;

        case 7:
            if (PAUSE_SCREEN_DATA.unk_A > 30)
            {
                PAUSE_SCREEN_DATA.typeFlags &= ~0x80;
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
            }
            break;

        case 8:
        case 9:
            break;
    }
}
