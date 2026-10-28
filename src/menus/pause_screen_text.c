#include "menus/pause_screen_text.h"
#include "menus/navigation_conversation.h"

#include "gba.h"
#include "globals.h"

#include "data/event_data.h"

#include "structs/event.h"

/**
 * @brief 7bbf0 | a8 | Gets the number of the sector that should be flashing
 *
 * @return u8 Sector number
 */
u8 GetFlashingSectorNumber(void)
{
    s32 i;
    u32 found;

    gFlashingSectorNumber = 0;

    for (i = gEventCounter; i > 0; i--)
    {
        if (sEventLocationAndNavigationInfo[i].navConversation != 0)
            break;
    }

    found = sEventLocationAndNavigationInfo[i].navConversation;
    if (gPreviousNavigationConversation != found)
        return gFlashingSectorNumber;

    found = FALSE;
    for (i = 0; i < sizeof(sNavConversationUnk_5766e4) / sizeof(sNavConversationUnk_5766e4[0]); i++)
    {
        if (gPreviousNavigationConversation == sNavConversationUnk_5766e4[i].conversation)
        {
            found = TRUE;
            break;
        }
    }

    if (!found)
        return gFlashingSectorNumber;

    i = sNavConversationUnk_5766e4[i].location;
    gFlashingSectorNumber = sNavigationTargetLocationAreas[i];
    return gFlashingSectorNumber;
}
