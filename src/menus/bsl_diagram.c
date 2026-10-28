#include "menus/bsl_diagram.h"
#include "menus/navigation_conversation.h"

#include "gba.h"
#include "globals.h"
#include "oam_id.h"

#include "constants/menus/pause_screen.h"

#include "data/event_data.h"

#include "structs/connection.h"
#include "structs/event.h"
#include "structs/menus/pause_screen.h"

struct BslDiagramInfo {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
};

/**
 * @brief 7ce6c | 144 | Initializes the BSL diagram
 *
 */
void unk_7ce6c(void)
{
    u8* pData;

    if (gCurrentArea > 6)
        return;

    pData = (u8*)&PAUSE_SCREEN_DATA;
    *(struct BslDiagramInfo*)(pData + OFFSET_OF(struct PauseScreenData, unk_240)) =
        *(const struct BslDiagramInfo*)sUnk_581500;

    if (PAUSE_SCREEN_DATA.unk_0 == 0)
        return;

    if (gPauseScreenFlag == 4)
        return;

    if (gCurrentArea != 0)
        PAUSE_SCREEN_DATA.unk_244 = sEvent_57607D[sEvent_576073[gCurrentArea]];
    else
        PAUSE_SCREEN_DATA.unk_244 = sEvent_57607D[7];

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].oamId = sUnk_79c180[(s8)PAUSE_SCREEN_DATA.unk_244];
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].xPosition = 0x1C;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].yPosition = 0x32;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].priority = 1;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].objMode = 0;

    UpdateMenuOamDataId(PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET, PAUSE_OAM_ID_NONE);
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].priority = 1;

    if (gCurrentArea != 0)
        PAUSE_SCREEN_DATA.unk_249 = sEvent_576073[gCurrentArea];
    else
        PAUSE_SCREEN_DATA.unk_249 = sUnk_5760e8[gCurrentRoom + 1];

    unk_7d27c();

    DMA3_FILL_16(0x7A73, PALRAM_OBJ + 0x142, 0x18);
}

/**
 * @brief 7cfb0 | 2cc | Updates the BSL diagram
 *
 */
void unk_7cfb0(void)
{
    s32 i;
    const u16* pPalette;
    u16* dst;
    s32 location;

    if (PAUSE_SCREEN_DATA.unk_0 == 0)
        return;

    if (gPauseScreenFlag == 4)
        return;

    PAUSE_SCREEN_DATA.unk_248++;
    if (PAUSE_SCREEN_DATA.unk_248 > 7)
    {
        PAUSE_SCREEN_DATA.unk_248 = 0;
        PAUSE_SCREEN_DATA.unk_247++;
        if (PAUSE_SCREEN_DATA.unk_247 > 5)
            PAUSE_SCREEN_DATA.unk_247 = 0;

        i = PAUSE_SCREEN_DATA.unk_249;
        dst = (u16*)(PALRAM_OBJ + 0x140) + i;
        pPalette = (const u16*)sUnk_581300;
        *dst = pPalette[PAUSE_SCREEN_DATA.unk_247 * 16 + i];
    }

    if (PAUSE_SCREEN_DATA.unk_24A == 2)
    {
        PAUSE_SCREEN_DATA.unk_24A = 3;
        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].xPosition = 0x1C;
        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].yPosition = 0x32;
    }
    else if (PAUSE_SCREEN_DATA.unk_24A == 3)
    {
        i = (s8)sEvent_57608A[location = gNavigationTargetLocation];
        if (i >= 0)
        {
            i += (s8)PAUSE_SCREEN_DATA.unk_244;
            if (i > 35)
                i -= 36;

            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].xPosition =
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].xPosition + (s8)sUnk_79c1a4[i * 3 + 0];
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].yPosition =
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].yPosition + ((s8(*)[3])sUnk_79c1a4)[i][1];
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].oamId =
                ((s8(*)[3])sUnk_79c1a4)[i][2] + PAUSE_OAM_ID_BSL_DIAGRAM_TARGET_ABOVE;
        }
        else
        {
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].xPosition =
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].xPosition + (s8)sUnk_79c210[location * 3 + 0];
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].yPosition =
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].yPosition + ((s8(*)[3])sUnk_79c210)[location][1];
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].oamId =
                ((s8(*)[3])sUnk_79c210)[location][2] + PAUSE_OAM_ID_BSL_DIAGRAM_TARGET_ABOVE;
        }
    }

    if (PAUSE_SCREEN_DATA.unk_240 == 0)
        return;

    PAUSE_SCREEN_DATA.unk_242++;

    switch (PAUSE_SCREEN_DATA.unk_240)
    {
        case 1:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x400)
                PAUSE_SCREEN_DATA.unk_240 = 2;
            break;

        case 2:
            if (!(PAUSE_SCREEN_DATA.typeFlags & 0x400))
            {
                PAUSE_SCREEN_DATA.unk_24A = 2;
                PAUSE_SCREEN_DATA.unk_240 = 1;
            }
            break;

        case 3:
            if (PAUSE_SCREEN_DATA.unk_242 > 8)
            {
                PAUSE_SCREEN_DATA.unk_242 = 0;
                PAUSE_SCREEN_DATA.unk_244++;
                if ((s8)PAUSE_SCREEN_DATA.unk_244 > 35)
                    PAUSE_SCREEN_DATA.unk_244 = 0;

                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].oamId = sUnk_79c180[(s8)PAUSE_SCREEN_DATA.unk_244];
            }
            break;

        case 4:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x400)
            {
                PAUSE_SCREEN_DATA.unk_240 = 5;
                PAUSE_SCREEN_DATA.unk_241 = 1;
            }
            break;

        case 5:
            if (!(PAUSE_SCREEN_DATA.typeFlags & 0x400))
            {
                PAUSE_SCREEN_DATA.unk_240 = 6;
                PAUSE_SCREEN_DATA.unk_24A = 2;
            }
            break;

        case 6:
            if ((s8)PAUSE_SCREEN_DATA.unk_244 == (s8)PAUSE_SCREEN_DATA.unk_245)
            {
                PAUSE_SCREEN_DATA.unk_240 = 4;
                PAUSE_SCREEN_DATA.unk_241 = 0;
                break;
            }

            if (PAUSE_SCREEN_DATA.unk_242 > 8)
            {
                PAUSE_SCREEN_DATA.unk_242 = 0;
                PAUSE_SCREEN_DATA.unk_244 += PAUSE_SCREEN_DATA.unk_246;
                if ((s8)PAUSE_SCREEN_DATA.unk_244 > 35)
                    PAUSE_SCREEN_DATA.unk_244 = 0;
                else if ((s8)PAUSE_SCREEN_DATA.unk_244 < 0)
                    PAUSE_SCREEN_DATA.unk_244 = 35;

                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].oamId = sUnk_79c180[(s8)PAUSE_SCREEN_DATA.unk_244];
            }
            break;
    }
}

/**
 * @brief 7d27c | d0 | Sets up the rotation of the BSL diagram towards the navigation target
 *
 */
void unk_7d27c(void)
{
    s32 diff;
    s32 sign;

    if (gNavigationTargetLocation == 0)
    {
        PAUSE_SCREEN_DATA.unk_240 = 0;
        return;
    }

    PAUSE_SCREEN_DATA.unk_240 = 1;

    if (PAUSE_SCREEN_DATA.conversationNumber == gPreviousNavigationConversation)
        PAUSE_SCREEN_DATA.unk_24A = 2;
    else
        PAUSE_SCREEN_DATA.unk_24A = 1;

    if ((s8)sEvent_57607D[gNavigationTargetLocation] < 0)
        return;

    PAUSE_SCREEN_DATA.unk_245 = sEvent_57607D[gNavigationTargetLocation];
    if ((s8)PAUSE_SCREEN_DATA.unk_245 == (s8)PAUSE_SCREEN_DATA.unk_244)
        return;

    PAUSE_SCREEN_DATA.unk_240 = 4;

    // Rotate along the shortest way around the 36 steps of the diagram
    diff = (s8)PAUSE_SCREEN_DATA.unk_245 - (s8)PAUSE_SCREEN_DATA.unk_244;
    sign = 1;
    if (diff < 0)
        sign = -1;

    diff *= sign;
    if (diff > 18)
    {
        diff = -1;
    }
    else
    {
        if (diff == 18)
            sign = 1;
        diff = 1;
    }

    PAUSE_SCREEN_DATA.unk_246 = diff * sign;
}
