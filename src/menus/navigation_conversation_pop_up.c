#include "menus/navigation_conversation.h"
#include "menus/pause_screen.h"

#include "gba.h"
#include "globals.h"
#include "macros.h"
#include "audio_wrappers.h"
#include "callbacks.h"
#include "dma.h"
#include "oam_id.h"
#include "syscalls.h"

#include "constants/audio.h"
#include "constants/event.h"
#include "constants/menus/pause_screen.h"

#include "data/event_data.h"
#include "data/sa_x_close_up.h"
#include "data/menus/pause_screen_data.h"

#include "structs/connection.h"
#include "structs/display.h"
#include "structs/event.h"
#include "structs/menus/pause_screen.h"

/**
 * @brief 7bc98 | f8 | Loads the graphics of the pop ups of a navigation conversation
 *
 */
void NavigationConversationLoadPopUpGraphics(void)
{
    s32 i;
    void* dst;

    for (i = ARRAY_SIZE(sNavConversationPopUpsPerConversation); i > 0; i--)
    {
        if (PAUSE_SCREEN_DATA.conversationNumber == sNavConversationPopUpsPerConversation[i - 1].conversation)
            break;
    }

    if (i == 0)
        return;

    i--;

    if (sNavConversationPopUpsPerConversation[i].popUps[0] != 0)
        LZ77UncompVram(sNavConversationPopUps[sNavConversationPopUpsPerConversation[i].popUps[0]].pGraphics, EWRAM_BASE);

    if (sNavConversationPopUpsPerConversation[i].popUps[1] != 0)
        LZ77UncompVram(sNavConversationPopUps[sNavConversationPopUpsPerConversation[i].popUps[1]].pGraphics, EWRAM_BASE + 0x4000);

    if (sNavConversationPopUpsPerConversation[i].popUps[2] != 0)
        LZ77UncompVram(sNavConversationPopUps[sNavConversationPopUpsPerConversation[i].popUps[2]].pGraphics, EWRAM_BASE + 0x8000);

    for (i = 5, dst = VRAM_OBJ + 0x5700; i >= 0; dst -= 0x400, i--)
        BitFill(3, -1, dst, 0x100, 32);

    DMA3_FILL_32(0, PALRAM_OBJ + 0x1E0, 0x20);
}

/**
 * @brief 7bd90 | 50 | Updates the current pop up of a navigation conversation
 *
 */
void NavigationConversationUpdatePopUp(void)
{
    if (PAUSE_SCREEN_DATA.currentPopUp == 0)
        return;

    PAUSE_SCREEN_DATA.unk_21B++;
    sNavConversationPopUpFunctions[PAUSE_SCREEN_DATA.currentPopUp - 1]();

    if (PAUSE_SCREEN_DATA.unk_21D)
        NavigationConversationFadeInPopUpPalette();
}

/**
 * @brief 7bde0 | 1f4 | Initializes a pop up of a navigation conversation
 *
 */
void unk_7bde0(void)
{
    s32 i;
    s32 count;
    u8 conversation;
    struct NavConversationPopUpTiles tiles;

    PAUSE_SCREEN_DATA.unk_21A = UCHAR_MAX;

    i = ARRAY_SIZE(sNavConversationPopUpsPerConversation);
    conversation = PAUSE_SCREEN_DATA.conversationNumber;
    for (; i > 0; i--)
    {
        if (conversation == sNavConversationPopUpsPerConversation[i - 1].conversation)
            break;
    }

    i--;
    if (i == UCHAR_MAX)
    {
        PAUSE_SCREEN_DATA.currentPopUp = 0;
        return;
    }

    if (PAUSE_SCREEN_DATA.unk_219 == 1)
        PAUSE_SCREEN_DATA.unk_21A = sNavConversationPopUpsPerConversation[i].popUps[1];
    else if (PAUSE_SCREEN_DATA.unk_219 == 2)
        PAUSE_SCREEN_DATA.unk_21A = sNavConversationPopUpsPerConversation[i].popUps[2];
    else
        PAUSE_SCREEN_DATA.unk_21A = sNavConversationPopUpsPerConversation[i].popUps[0];

    if (PAUSE_SCREEN_DATA.unk_21A == 0)
    {
        PAUSE_SCREEN_DATA.currentPopUp = 0;
        return;
    }

    PAUSE_SCREEN_DATA.unk_229 = 0;
    PAUSE_SCREEN_DATA.unk_228 = 0;

    if (PAUSE_SCREEN_DATA.unk_219 == 1)
        PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE + 0x4000;
    else if (PAUSE_SCREEN_DATA.unk_219 == 2)
        PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE + 0x8000;
    else
        PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE;

    if (sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].unk_12_0 == 8)
    {
        tiles = sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].tiles;
        for (count = tiles.count; count > 0;)
        {
            count--;
            DMA3_COPY_16(&PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer[count * 0x100],
                VRAM_OBJ + 0x4300 + count * 0x400 + sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].tiles.slot * 0x400, 0x80);
        }
    }
    else if (sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].unk_12_0 == 4)
    {
        tiles = sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].tiles;
        for (count = tiles.count; count > 0;)
        {
            count--;
            DMA3_COPY_16(&PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer[count * 0x100],
                VRAM_OBJ + 0x4300 + count * 0x400 + sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].tiles.slot * 0x400 + 0x40, 0x40);
        }
    }

    if (PAUSE_SCREEN_DATA.unk_21A == 3)
        SoundPlay(SOUND_125);

    PAUSE_SCREEN_DATA.unk_21D = TRUE;
    PAUSE_SCREEN_DATA.currentPopUp++;
    PAUSE_SCREEN_DATA.unk_21B = 0;
}

/**
 * @brief 7bfd4 | fc | Fades in the palette of the current pop up of a navigation conversation
 *
 */
void NavigationConversationFadeInPopUpPalette(void)
{
    const u16* src;
    u16* dst;
    s32 i;
    s32 j;
    u8 target[3];
    u8 current[3];

    src = sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].pPalette;
    dst = PALRAM_OBJ + 0x1E0;

    for (i = 0; i < 16; i++, src++, dst++)
    {
        target[0] = RED(*src);
        target[1] = GREEN(*src);
        target[2] = BLUE(*src);

        current[0] = RED(*dst);
        current[1] = GREEN(*dst);
        current[2] = BLUE(*dst);

        for (j = 0; j < 3; j++)
        {
            if (target[j] > current[j])
                current[j]++;
            else if (target[j] < current[j])
                current[j]--;
        }

        *dst = current[0] | current[1] << 5 | current[2] << 10;
    }

    if (PAUSE_SCREEN_DATA.unk_21D > 0x20)
        PAUSE_SCREEN_DATA.unk_21D = 0;
    else
        PAUSE_SCREEN_DATA.unk_21D++;
}

/**
 * @brief 7c0d0 | 248 | Updates the X parasite pop up of a navigation conversation
 *
 */
void NavigationConversationUpdateXParasitePopUp(void)
{
    const u8* pAnim;
    s32 count;
    s32 slot;
    s32 nbrTiles;

    unk_7c3b4();

    if (sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].unk_12_0 == 8)
    {
        pAnim = sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].pAnimation;
        if (PAUSE_SCREEN_DATA.unk_21B < pAnim[PAUSE_SCREEN_DATA.unk_21C * 2 + 1])
            return;

        PAUSE_SCREEN_DATA.unk_21B = 0;
        PAUSE_SCREEN_DATA.unk_21C++;
        if (PAUSE_SCREEN_DATA.unk_21C >= sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].animationLength)
            PAUSE_SCREEN_DATA.unk_21C = 0;

        if (PAUSE_SCREEN_DATA.unk_219 == 1)
            PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE + 0x4000;
        else if (PAUSE_SCREEN_DATA.unk_219 == 2)
            PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE + 0x8000;
        else
            PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE;

        nbrTiles = sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].tiles.count;
        slot = sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].tiles.slot;
        count = (pAnim[PAUSE_SCREEN_DATA.unk_21C * 2] & 3) * 0x100;
        count += (pAnim[PAUSE_SCREEN_DATA.unk_21C * 2] >> 2) * 0x1800;
        PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = (const u32*)((u32)PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer + count);

        for (count = nbrTiles; count > 0;)
        {
            count--;
            DMA3_COPY_16(&PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer[count * 0x100],
                VRAM_OBJ + 0x4300 + count * 0x400 + slot * 0x400, 0x80);
        }
    }
    else if (sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].unk_12_0 == 4)
    {
        pAnim = sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].pAnimation;
        if (PAUSE_SCREEN_DATA.unk_21B < pAnim[PAUSE_SCREEN_DATA.unk_21C * 2 + 1])
            return;

        PAUSE_SCREEN_DATA.unk_21B = 0;
        PAUSE_SCREEN_DATA.unk_21C++;
        if (PAUSE_SCREEN_DATA.unk_21C >= sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].animationLength)
            PAUSE_SCREEN_DATA.unk_21C = 0;

        if (PAUSE_SCREEN_DATA.unk_219 == 1)
            PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE + 0x4000;
        else if (PAUSE_SCREEN_DATA.unk_219 == 2)
            PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE + 0x8000;
        else
            PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = EWRAM_BASE;

        nbrTiles = sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].tiles.count;
        slot = sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].tiles.slot;
        count = (pAnim[PAUSE_SCREEN_DATA.unk_21C * 2] & 7) * 0x80;
        count += (pAnim[PAUSE_SCREEN_DATA.unk_21C * 2] >> 3) * 0x1000;
        PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = (const u32*)((u32)PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer + count);

        for (count = nbrTiles; count > 0;)
        {
            count--;
            DMA3_COPY_16(&PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer[count * 0x100],
                VRAM_OBJ + 0x4300 + count * 0x400 + slot * 0x400 + 0x40, 0x40);
        }
    }
}

/**
 * @brief 7c318 | 9c | Clears the graphics of the pop ups of a navigation conversation
 *
 */
void NavigationConversationClearPopUpGraphics(void)
{
    s32 i;
    void* dst;

    for (i = 5, dst = VRAM_OBJ + 0x5700; i >= 0; dst -= 0x400, i--)
        BitFill(3, -1, dst, 0x100, 32);

    DMA3_FILL_32(0, PALRAM_OBJ + 0x1E0, 0x20);

    if (PAUSE_SCREEN_DATA.unk_21A == 3)
        SoundStop(SOUND_125);

    PAUSE_SCREEN_DATA.currentPopUp = 0;
    PAUSE_SCREEN_DATA.unk_21C = 0;
    PAUSE_SCREEN_DATA.unk_21B = 0;
    PAUSE_SCREEN_DATA.unk_21D = 0;
    PAUSE_SCREEN_DATA.unk_219++;
}

/**
 * @brief 7c3b4 | 8c | Updates the palette cycle of the current pop up of a navigation conversation
 *
 */
void unk_7c3b4(void)
{
    const u16* pPalette;

    if (sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].unk_10 == 0)
        return;

    PAUSE_SCREEN_DATA.unk_229++;
    if (PAUSE_SCREEN_DATA.unk_229 < sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].unk_10)
        return;

    PAUSE_SCREEN_DATA.unk_229 = 0;

    pPalette = &sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].pCyclePalette[PAUSE_SCREEN_DATA.unk_228];
    if (*pPalette == 0)
    {
        PAUSE_SCREEN_DATA.unk_228 = 0;
        pPalette = sNavConversationPopUps[PAUSE_SCREEN_DATA.unk_21A].pCyclePalette;
    }

    *(u16*)(PALRAM_OBJ + 0x1FE) = *pPalette;

    PAUSE_SCREEN_DATA.unk_228++;
    if (PAUSE_SCREEN_DATA.unk_228 > 15)
        PAUSE_SCREEN_DATA.unk_228 = 0;
}

/**
 * @brief 7c440 | 174 | Updates the palette animations of a navigation conversation
 *
 */
void unk_7c440(void)
{
    u16 i;
    u16 j;
    u16* dst;

    PAUSE_SCREEN_DATA.unk_225++;
    if (PAUSE_SCREEN_DATA.unk_225 >= sNavConversationFlashingDurations[PAUSE_SCREEN_DATA.unk_224])
    {
        PAUSE_SCREEN_DATA.unk_225 = 0;
        PAUSE_SCREEN_DATA.unk_224++;
        if (PAUSE_SCREEN_DATA.unk_224 > 3)
            PAUSE_SCREEN_DATA.unk_224 = 0;

        dst = PALRAM_BASE;
        dst[0x12] = sNavConversationFlashingColors1[PAUSE_SCREEN_DATA.unk_224];
        dst[0x13] = sNavConversationFlashingColors1[PAUSE_SCREEN_DATA.unk_224];
        dst[0x22] = sNavConversationFlashingColors2[PAUSE_SCREEN_DATA.unk_224];
        dst[0x23] = sNavConversationFlashingColors2[PAUSE_SCREEN_DATA.unk_224];
    }

    if (PAUSE_SCREEN_DATA.screenType == PAUSE_SCREEN_TYPE_MAP_SCREEN)
        return;

    if (PAUSE_SCREEN_DATA.screenType == PAUSE_SCREEN_TYPE_NAVIGATION_ROOM)
    {
        PAUSE_SCREEN_DATA.unk_22D++;
        if (PAUSE_SCREEN_DATA.unk_22D >= sNavConversationRoomBgAnimatedPalDurations[PAUSE_SCREEN_DATA.unk_22C])
        {
            PAUSE_SCREEN_DATA.unk_22D = 0;
            PAUSE_SCREEN_DATA.unk_22C++;
            if (PAUSE_SCREEN_DATA.unk_22C > 3)
                PAUSE_SCREEN_DATA.unk_22C = 0;

            dst = PALRAM_BASE + 0x138;
            j = PAUSE_SCREEN_DATA.unk_22C * 16 + 12;
            for (i = 0; i < 4; i++, j++, dst++)
                *dst = sNavConversationRoomBgAnimatedPal[j];
        }
    }
    else if (PAUSE_SCREEN_DATA.screenType == PAUSE_SCREEN_TYPE_SHIP)
    {
        PAUSE_SCREEN_DATA.unk_22D++;
        if (PAUSE_SCREEN_DATA.unk_22D >= sNavConversationShipBgAnimatedPalDurations[PAUSE_SCREEN_DATA.unk_22C])
        {
            PAUSE_SCREEN_DATA.unk_22D = 0;
            PAUSE_SCREEN_DATA.unk_22C++;
            if (PAUSE_SCREEN_DATA.unk_22C > 7)
                PAUSE_SCREEN_DATA.unk_22C = 0;

            dst = PALRAM_BASE + 0x194;
            j = PAUSE_SCREEN_DATA.unk_22C * 16 + 10;
            for (i = 0; i < 6; i++, j++, dst++)
                *dst = sNavConversationShipBgAnimatedPal[j];
        }
    }
}

/**
 * @brief 7c5b4 | 7c | Loads the special graphics of a navigation conversation
 *
 */
void NavigationConversationLoadSpecialGraphics(void)
{
    if (PAUSE_SCREEN_DATA.conversationNumber == NAV_CONVO_GO_TO_OPERATIONS_ROOM)
    {
        LZ77UncompVram(sNavConversationOperationsRoomImageGfx, EWRAM_BASE);
        LZ77UncompVram(sNavConversationOperationsRoomImageTilemap0, EWRAM_BASE + 0x6000);
        LZ77UncompVram(sNavConversationOperationsRoomImageTilemap1, EWRAM_BASE + 0x6800);
        LZ77UncompVram(sNavConversationOperationsRoomImageTilemap2, EWRAM_BASE + 0x7000);
        LZ77UncompVram(sNavConversationOperationsRoomImageTilemap3, EWRAM_BASE + 0x7800);
    }
    else if (PAUSE_SCREEN_DATA.conversationNumber == NAV_CONVO_FIND_SECURITY_ROOM_AND_DOWNLOAD_BOMBS)
    {
        LZ77UncompVram(sSaXCloseUpGfx, EWRAM_BASE);
    }
}

/**
 * @brief 7c630 | 83c | Handles the SA-X close up shown during a navigation conversation
 *
 */
void unk_7c630(void)
{
    switch (PAUSE_SCREEN_DATA.unk_265)
    {
        case 0:
            PAUSE_SCREEN_DATA.dispcntBackup = READ_16(REG_DISPCNT);
            PAUSE_SCREEN_DATA.bg3CntBackup = READ_16(REG_BG3CNT);
            PAUSE_SCREEN_DATA.bg2CntBackup = READ_16(REG_BG2CNT);
            PAUSE_SCREEN_DATA.bldcntBackup = READ_16(REG_BLDCNT);
            PAUSE_SCREEN_DATA.bldalphaBackup = READ_16(REG_BLDALPHA);
            PAUSE_SCREEN_DATA.dispcnt = 0;
            DMA3_COPY_16(PALRAM_BASE, EWRAM_BASE + 0x35000, 0x100);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 1:
            DmaTransfer(3, VRAM_BASE + 0x4000, EWRAM_BASE + 0x8000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 2:
            DmaTransfer(3, VRAM_BASE + 0x5000, EWRAM_BASE + 0x9000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 3:
            DmaTransfer(3, VRAM_BASE + 0x6000, EWRAM_BASE + 0xA000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 4:
            DmaTransfer(3, VRAM_BASE + 0x7000, EWRAM_BASE + 0xB000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 5:
            DmaTransfer(3, EWRAM_BASE, VRAM_BASE + 0x4000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 6:
            DmaTransfer(3, EWRAM_BASE + 0x1000, VRAM_BASE + 0x5000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 7:
            DmaTransfer(3, EWRAM_BASE + 0x2000, VRAM_BASE + 0x6000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 8:
            DmaTransfer(3, EWRAM_BASE + 0x3000, VRAM_BASE + 0x7000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 9:
            DmaTransfer(3, EWRAM_BASE + 0x4000, VRAM_BASE + 0x8000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 10:
            DmaTransfer(3, EWRAM_BASE + 0x5000, VRAM_BASE + 0x9000, 0x1000, 16);
            if (PAUSE_SCREEN_DATA.conversationNumber == 0x35)
            {
                PAUSE_SCREEN_DATA.unk_265 = 13;
                break;
            }

            gWrittenToBldalpha_Evb = 0;
            gWrittenToBldalpha_Eva = 16;
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 11:
            DmaTransfer(3, EWRAM_BASE + 0x6000, VRAM_BASE + 0xA000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 12:
            DmaTransfer(3, EWRAM_BASE + 0x7000, VRAM_BASE + 0xB000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265 = 21;
            break;

        case 13:
            DmaTransfer(3, EWRAM_BASE + 0x6000, VRAM_BASE + 0xA000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 14:
            DmaTransfer(3, EWRAM_BASE + 0x7000, VRAM_BASE + 0xB000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 15:
            DMA3_COPY_16(sNavConversationOperationsRoomImagePal, PALRAM_BASE, 0x100);
            CallbackSetVBlank(PauseScreenVBlank_Unused);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 16:
            gWrittenToBg3cnt = 0x1407;
            PAUSE_SCREEN_DATA.dispcnt |= 0x800;
            PAUSE_SCREEN_DATA.unk_265++;
            PAUSE_SCREEN_DATA.unk_266 = 0;
            break;

        case 17:
            PAUSE_SCREEN_DATA.unk_266++;
            if (PAUSE_SCREEN_DATA.unk_266 > sNavConversationSaXCloseUpDelays[0])
            {
                gWrittenToBg3cnt = 0x1507;
                PAUSE_SCREEN_DATA.unk_265++;
                PAUSE_SCREEN_DATA.unk_266 = 0;
            }
            break;

        case 18:
            PAUSE_SCREEN_DATA.unk_266++;
            if (PAUSE_SCREEN_DATA.unk_266 > sNavConversationSaXCloseUpDelays[1])
            {
                gWrittenToBg3cnt = 0x1607;
                PAUSE_SCREEN_DATA.unk_265++;
                PAUSE_SCREEN_DATA.unk_266 = 0;
            }
            break;

        case 19:
            PAUSE_SCREEN_DATA.unk_266++;
            if (PAUSE_SCREEN_DATA.unk_266 > sNavConversationSaXCloseUpDelays[2])
            {
                gWrittenToBg3cnt = 0x1707;
                PAUSE_SCREEN_DATA.unk_265++;
                PAUSE_SCREEN_DATA.unk_266 = 0;
            }
            break;

        case 20:
            PAUSE_SCREEN_DATA.unk_266++;
            if (PAUSE_SCREEN_DATA.unk_266 > sNavConversationSaXCloseUpDelays[3])
            {
                PAUSE_SCREEN_DATA.unk_265 = 27;
                PAUSE_SCREEN_DATA.unk_266 = 0;
            }
            break;

        case 21:
            LZ77UncompVram(sSaXCloseUpTileTable1, VRAM_BASE + 0x7800);
            LZ77UncompVram(sSaXCloseUpTileTable2, VRAM_BASE + 0xB800);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 22:
            DMA3_COPY_16(sSaXCloseUpPalGrayscale, PALRAM_BASE, 0x100);
            CallbackSetVBlank(PauseScreenVBlank_Unused);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 23:
            WRITE_16(REG_BG2CNT, 0xF06);
            WRITE_16(REG_BG3CNT, 0x1707);
            WRITE_16(REG_BLDCNT, 0x844);
            PAUSE_SCREEN_DATA.dispcnt |= 0xC00;
            PAUSE_SCREEN_DATA.unk_265++;
            PAUSE_SCREEN_DATA.unk_266 = 0;
            break;

        case 24:
            PAUSE_SCREEN_DATA.unk_266++;
            if (PAUSE_SCREEN_DATA.unk_266 > sSaXCloseUpDurations[0])
            {
                PAUSE_SCREEN_DATA.unk_265++;
                PAUSE_SCREEN_DATA.unk_266 = 0;
            }
            break;

        case 25:
            if (gWrittenToBldalpha_Eva == 0)
            {
                PAUSE_SCREEN_DATA.unk_265++;
                PAUSE_SCREEN_DATA.unk_266 = 0;
                break;
            }

            gWrittenToBldalpha_Eva--;
            gWrittenToBldalpha_Evb = 16 - gWrittenToBldalpha_Eva;
            break;

        case 26:
            PAUSE_SCREEN_DATA.unk_266++;
            if (PAUSE_SCREEN_DATA.unk_266 > sSaXCloseUpDurations[1])
            {
                PAUSE_SCREEN_DATA.unk_265 = 27;
                PAUSE_SCREEN_DATA.unk_266 = 0;
            }
            break;

        case 27:
            PAUSE_SCREEN_DATA.dispcnt = 0;
            PAUSE_SCREEN_DATA.unk_265++;
            PAUSE_SCREEN_DATA.unk_266 = 0;
            break;

        case 28:
            DmaTransfer(3, sMinimapTilesGfx, VRAM_BASE + 0x8000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 29:
            DmaTransfer(3, sMinimapTilesGfx + 0x1000, VRAM_BASE + 0x9000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 30:
            DmaTransfer(3, sMinimapTilesGfx + 0x2000, VRAM_BASE + 0xA000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 31:
            DmaTransfer(3, sMinimapTilesGfx + 0x3000, VRAM_BASE + 0xB000, 0x800, 16);
            DMA3_COPY_16(VRAM_BASE + 0x9800, VRAM_BASE + 0x9400, 0x200);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 32:
            DmaTransfer(3, EWRAM_BASE + 0x8000, VRAM_BASE + 0x4000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 33:
            DmaTransfer(3, EWRAM_BASE + 0x9000, VRAM_BASE + 0x5000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 34:
            DmaTransfer(3, EWRAM_BASE + 0xA000, VRAM_BASE + 0x6000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 35:
            DmaTransfer(3, EWRAM_BASE + 0xB000, VRAM_BASE + 0x7000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 36:
            DMA3_COPY_16(EWRAM_BASE + 0x35000, PALRAM_BASE, 0x100);
            CallbackSetVBlank(PauseScreenVBlank);
            PAUSE_SCREEN_DATA.unk_265++;
            break;

        case 37:
            WRITE_16(REG_BG3CNT, PAUSE_SCREEN_DATA.bg3CntBackup);
            WRITE_16(REG_BG2CNT, PAUSE_SCREEN_DATA.bg2CntBackup);
            WRITE_16(REG_BLDCNT, PAUSE_SCREEN_DATA.bldcntBackup);
            WRITE_16(REG_BLDALPHA, PAUSE_SCREEN_DATA.bldalphaBackup);
            PAUSE_SCREEN_DATA.dispcnt = PAUSE_SCREEN_DATA.dispcntBackup;
            PAUSE_SCREEN_DATA.unk_265 = 0;
            PAUSE_SCREEN_DATA.unk_264 = 0;
            break;
    }
}

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
        *(const struct BslDiagramInfo*)sBslDiagramInfoInit;

    if (PAUSE_SCREEN_DATA.screenType == PAUSE_SCREEN_TYPE_MAP_SCREEN)
        return;

    if (gPauseScreenFlag == 4)
        return;

    if (gCurrentArea != 0)
        PAUSE_SCREEN_DATA.unk_244 = sEvent_57607D[sEvent_576073[gCurrentArea]];
    else
        PAUSE_SCREEN_DATA.unk_244 = sEvent_57607D[7];

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].oamId = sBslDiagramOamIds[(s8)PAUSE_SCREEN_DATA.unk_244];
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].xPosition = 0x1C;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].yPosition = 0x32;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].priority = 1;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].objMode = 0;

    UpdateMenuOamDataId(PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET, PAUSE_OAM_ID_NONE);
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].priority = 1;

    if (gCurrentArea != 0)
        PAUSE_SCREEN_DATA.unk_249 = sEvent_576073[gCurrentArea];
    else
        PAUSE_SCREEN_DATA.unk_249 = sBslDiagramMainDeckRoomLocations[gCurrentRoom + 1];

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

    if (PAUSE_SCREEN_DATA.screenType == PAUSE_SCREEN_TYPE_MAP_SCREEN)
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
        pPalette = (const u16*)sBslDiagramAnimatedPal;
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
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].xPosition + (s8)sBslDiagramTargetOffsets[i * 3 + 0];
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].yPosition =
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].yPosition + ((s8(*)[3])sBslDiagramTargetOffsets)[i][1];
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].oamId =
                ((s8(*)[3])sBslDiagramTargetOffsets)[i][2] + PAUSE_OAM_ID_BSL_DIAGRAM_TARGET_ABOVE;
        }
        else
        {
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].xPosition =
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].xPosition + (s8)sBslDiagramFixedTargetOffsets[location * 3 + 0];
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].yPosition =
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].yPosition + ((s8(*)[3])sBslDiagramFixedTargetOffsets)[location][1];
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM_TARGET].oamId =
                ((s8(*)[3])sBslDiagramFixedTargetOffsets)[location][2] + PAUSE_OAM_ID_BSL_DIAGRAM_TARGET_ABOVE;
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

                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].oamId = sBslDiagramOamIds[(s8)PAUSE_SCREEN_DATA.unk_244];
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

                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BSL_DIAGRAM].oamId = sBslDiagramOamIds[(s8)PAUSE_SCREEN_DATA.unk_244];
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
