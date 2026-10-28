#include "save_file.h"
#include "dma.h"
#include "globals.h"
#include "gba.h"
#include "event.h"
#include "macros.h"
#include "minimap.h"
#include "sram_misc.h"
#include "sram/sram.h"
#include "types.h"

#include "data/sram_data.h"
#include "data/sram_pointers.h"

#include "constants/connection.h"
#include "constants/event.h"
#include "constants/samus.h"

#include "structs/bg_clip.h"
#include "structs/block.h"
#include "structs/connection.h"
#include "structs/event.h"
#include "structs/menus/boot_debug.h"
#include "structs/minimap.h"
#include "structs/samus.h"
#include "structs/save_file.h"

extern const struct Door* sAreaDoorPointers[AREA_END];

#define WORLD_DATA_MINIMAP_SIZE 0x380
#define WORLD_DATA_COLLECTED_TANKS_OFFSET 0xC80

/**
 * @brief 7fe60 | 34 | Loads the current save file if a file is being loaded
 *
 */
void SramLoad_CurrentSave(void)
{
    if (gIsLoadingFile == TRUE)
    {
        SramRead_FromEwram();
        SramRead_WorldData();

        gSamusData.pose = SPOSE_LOADING_SAVE;
        gSamusData.animationDurationCounter = 0;
        gSamusData.currentAnimationFrame = 0;
    }
}

/**
 * @brief 7fe94 | 10 | Loads the current save file (unused)
 *
 */
void SramLoad_CurrentSave_Unused(void)
{
    SramRead_FromEwram();
    SramRead_WorldData();
}

/**
 * @brief 7fea4 | d8 | Writes the world data (minimap, never reform blocks and collected tanks) to the current save file
 *
 */
void SramWrite_WorldData(void)
{
    u8* pWorldData;
    u32 offset;
    s32 i;
    u32 size;
    s32 area;

    pWorldData = (u8*)sUnk_582274[gMostRecentSaveFile];

    DmaTransfer(3, gVisitedMinimapTiles, pWorldData, WORLD_DATA_MINIMAP_SIZE, 16);
    offset = WORLD_DATA_MINIMAP_SIZE;

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        size = gNumberOfNeverReformBlocks[i] * 3;
        if (size & 3)
        {
            size &= 0xFFFC;
            size += 4;
        }

        if (size != 0)
        {
            // Main Deck has twice as much space
            area = i;
            if (area != AREA_MAIN_DECK)
                area = i + 1;

            DmaTransfer(3, gNeverReformBlocks[area], pWorldData + offset, size, 16);
            offset += size;
        }
    }

    offset = WORLD_DATA_COLLECTED_TANKS_OFFSET;
    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        size = gNumberOfCollectedTanks[i] * 4;

        if (size != 0)
        {
            // Main Deck has twice as much space
            area = i;
            if (area != AREA_MAIN_DECK)
                area = i + 1;

            DmaTransfer(3, gCollectedTanks[area], pWorldData + offset, size, 16);
            offset += size;
        }
    }
}

/**
 * @brief 7ff7c | ec | Reads the world data (minimap, never reform blocks and collected tanks) from the current save file
 *
 */
void SramRead_WorldData(void)
{
    u8* pWorldData;
    u32 offset;
    s32 i;
    u32 size;
    s32 area;

    pWorldData = (u8*)sUnk_582274[gMostRecentSaveFile];

    DmaTransfer(3, pWorldData, gVisitedMinimapTiles, WORLD_DATA_MINIMAP_SIZE, 16);
    BitFill(3, USHORT_MAX, gNeverReformBlocks, 0x1B00, 16);
    offset = WORLD_DATA_MINIMAP_SIZE;

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        size = gNumberOfNeverReformBlocks[i] * 3;
        if (size & 3)
        {
            size &= 0xFFFC;
            size += 4;
        }

        if (size != 0)
        {
            // Main Deck has twice as much space
            area = i;
            if (area != AREA_MAIN_DECK)
                area = i + 1;

            DmaTransfer(3, pWorldData + offset, gNeverReformBlocks[area], size, 16);
            offset += size;
        }
    }

    offset = WORLD_DATA_COLLECTED_TANKS_OFFSET;
    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        size = gNumberOfCollectedTanks[i] * 4;

        if (size != 0)
        {
            // Main Deck has twice as much space
            area = i;
            if (area != AREA_MAIN_DECK)
                area = i + 1;

            DmaTransfer(3, pWorldData + offset, gCollectedTanks[area], size, 16);
            offset += size;
        }
    }
}

/**
 * @brief 80068 | 8c | Writes the most recent save file to SRAM
 * 
 */
void SramWrite_MostRecentSaveFile(void)
{
    struct SramExtraData* pData;
    u16* src;
    u16 checksum;
    s32 i;

    pData = EWRAM_SRAM_MOST_RECENT_SAVE_FILE;
    src = (u16*)pData;

    pData->id = 0x1E;
    pData->counter++;
    pData->checksum = 0;
    pData->notChecksum = USHORT_MAX;
    pData->value = gMostRecentSaveFile;

    for (i = 0; i < SRAM_EXTRA_DATA_MAGIC_SIZE; i++)
    {
        pData->magic[i] = sSramUnk_582288[0][i];
        pData->magic2[i] = sSramUnk_582288[1][i];
    }

    checksum = 0;
    for (i = 0; i < SRAM_EXTRA_DATA_SIZE / 8; i++)
    {
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
    }

    pData->checksum = checksum;
    pData->notChecksum = USHORT_MAX - checksum;

    unk_dd4();
}

/**
 * @brief 800f4 | e0 | Reads the most recent save file from SRAM
 * 
 */
void SramRead_MostRecentSaveFile(void)
{
    struct SramExtraData* pData;
    u16* src;
    u16 checksum;
    u16 storedChecksum;
    u32 error;
    s32 i;

    pData = EWRAM_SRAM_MOST_RECENT_SAVE_FILE;

    error = pData->id != 0x1E;

    if (!error)
    {
        src = (u16*)pData;
        checksum = 0;
        storedChecksum = pData->checksum;

        for (i = 0; i < SRAM_EXTRA_DATA_SIZE / 8; i++)
        {
            checksum += *src++;
            checksum += *src++;
            checksum += *src++;
            checksum += *src++;
        }

        if (storedChecksum != checksum)
            error = 2;
    }

    if (!error)
    {
        for (i = 0; i < SRAM_EXTRA_DATA_MAGIC_SIZE; i++)
        {
            if (pData->magic[i] != sSramUnk_582288[0][i])
            {
                error = 3;
                break;
            }

            if (pData->magic2[i] != sSramUnk_582288[1][i])
            {
                error = 4;
                break;
            }
        }
    }

    if (!error)
    {
        gMostRecentSaveFile = pData->value;
    }
    else
    {
        DMA3_FILL_16(USHORT_MAX, EWRAM_SRAM_MOST_RECENT_SAVE_FILE, SRAM_EXTRA_DATA_SIZE);
        gMostRecentSaveFile = 0;
    }
}

/**
 * @brief 801d4 | 90 | Writes the language to SRAM
 * 
 */
void SramWrite_Language(void)
{
    struct SramExtraData* pData;
    u16* src;
    u16 checksum;
    s32 i;

    pData = (struct SramExtraData*)(EWRAM_SRAM + 0x7040);
    src = (u16*)pData;

    pData->id = 0x1F;
    pData->counter++;
    pData->checksum = 0;
    pData->notChecksum = USHORT_MAX;
    pData->value = gLanguage;

    for (i = 0; i < SRAM_EXTRA_DATA_MAGIC_SIZE; i++)
    {
        pData->magic[i] = sSramUnk_5822a8[0][i];
        pData->magic2[i] = sSramUnk_5822a8[1][i];
    }

    checksum = 0;
    for (i = 0; i < SRAM_EXTRA_DATA_SIZE / 8; i++)
    {
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
    }

    pData->checksum = checksum;
    pData->notChecksum = USHORT_MAX - checksum;

    unk_dec(0);
}

/**
 * @brief 80264 | 180 | Reads the language from SRAM
 * 
 */
void SramRead_Language(void)
{
    struct SramExtraData* pData;
    u16* src;
    u16 checksum;
    u16 storedChecksum;
    u32 error;
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_SIZE(sUnk_582280); i++)
    {
        pData = (struct SramExtraData*)sUnk_582280[i];
        src = (u16*)pData;

        error = pData->id != 0x1F;

        if (!error)
        {
            checksum = 0;
            storedChecksum = pData->checksum;

            for (j = 0; j < SRAM_EXTRA_DATA_SIZE / 8; j++)
            {
                checksum += *src++;
                checksum += *src++;
                checksum += *src++;
                checksum += *src++;
            }

            if (storedChecksum != checksum)
                error = 2;
        }

        if (!error)
        {
            for (j = 0; j < SRAM_EXTRA_DATA_MAGIC_SIZE; j++)
            {
                if (pData->magic[j] != sSramUnk_5822a8[0][j])
                {
                    error = 3;
                    break;
                }

                if (pData->magic2[j] != sSramUnk_5822a8[1][j])
                {
                    error = 4;
                    break;
                }
            }
        }

        if (i == 0)
        {
            if (!error)
            {
                // Main copy is valid, update the backup
                DMA3_COPY_16(sUnk_582280[0], sUnk_582280[1], SRAM_EXTRA_DATA_SIZE / 2);
                unk_dec(1);
                break;
            }
        }
        else
        {
            if (!error)
            {
                // Backup is valid, restore the main copy
                DMA3_COPY_16(sUnk_582280[1], sUnk_582280[0], SRAM_EXTRA_DATA_SIZE / 2);
                unk_dec(0);
                break;
            }

            // Both are invalid, clear both
            DMA3_FILL_16(0, sUnk_582280[0], SRAM_EXTRA_DATA_SIZE);
            unk_dec(0);
            DMA3_FILL_16(0, sUnk_582280[1], SRAM_EXTRA_DATA_SIZE);
            unk_dec(1);
        }
    }

    if (!error)
        gLanguage = pData->value;
    else
        gLanguage = 0;
}

/**
 * @brief 803e4 | 14c | Initializes a new save file
 * 
 */
void Sram_InitSaveFile(void)
{
    s32 i;
    const struct Door* pDoor;
    s32 offset;
    s32 exit;

    BitFill(3, 0, gVisitedMinimapTiles, WORLD_DATA_MINIMAP_SIZE, 16);
    BitFill(3, USHORT_MAX, gNeverReformBlocks, 0x1200, 16);
    BitFill(3, USHORT_MAX, gCollectedTanks, 0x900, 16);

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        gNumberOfNeverReformBlocks[i] = 0;
        gNumberOfCollectedTanks[i] = 0;
    }

    gInGameTimer = sSramUnk_5822d4[0];
    gDisableDrawingSamusAndScrollingFlag = TRUE;
    EventSet(EVENT_NONE);

    gPreviousNavigationConversation = UCHAR_MAX;
    gPreviousSoundEvent = UCHAR_MAX;

    gEquipment.securityHatchLevel |= UCHAR_MAX;
    gSecurityHatchLevel = UCHAR_MAX;
    gSecurityHatchLevelBackup = UCHAR_MAX;
    gEquipment.downloadedMaps = 0;

    gAbilityCount = 0;
    gCurrentArea = AREA_MAIN_DECK;
    gPreviousArea = AREA_MAIN_DECK;
    gCurrentRoom = 0;
    gLastDoorUsed = 0;
    gUnk_300004c = 0;
    gUnk_300004d = 0;

    pDoor = sAreaDoorPointers[AREA_MAIN_DECK];
    offset = pDoor->xStart;
    exit = pDoor->xExit;
    gPreviousXPosition = gSamusData.xPosition = BLOCK_TO_SUB_PIXEL(offset) + PIXEL_TO_SUB_PIXEL(exit + 8);

    offset = pDoor->yEnd + 1;
    exit = pDoor->yExit;
    gPreviousYPosition = gSamusData.yPosition = BLOCK_TO_SUB_PIXEL(offset) + PIXEL_TO_SUB_PIXEL(exit) - ONE_SUB_PIXEL;

    MinimapLoadInitial();
    gIsLoadingFile = FALSE;
}

/**
 * @brief 80530 | 134 | Resets the game state for a demo
 * 
 */
void Sram_ResetForDemo(void)
{
    s32 i;

    gBootDebugOptions = sSramUnk_5822e4[0];
    gButtonAssignments = sSramUnk_5822c8[0];

    BitFill(3, USHORT_MAX, gVisitedMinimapTiles, WORLD_DATA_MINIMAP_SIZE, 16);
    BitFill(3, USHORT_MAX, gNeverReformBlocks, 0x1200, 16);
    BitFill(3, USHORT_MAX, gCollectedTanks, 0x900, 16);

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        gNumberOfNeverReformBlocks[i] = 0;
        gNumberOfCollectedTanks[i] = 0;
    }

    gInGameTimer = sSramUnk_5822d4[0];
    gDisableDrawingSamusAndScrollingFlag = FALSE;

    gPreviousNavigationConversation = UCHAR_MAX;
    gPreviousSoundEvent = UCHAR_MAX;

    gUnk_300004c = 0;
    gUnk_300004d = 0;
    gIsLoadingFile = FALSE;
    gUnk_3000be3 = FALSE;
    gMonochromeFading = 0;
    gDisableSoftReset = FALSE;
    gMaxInGameTimeFlag = TRUE;
    gDisableMusicFlag = FALSE;
    gSkipDoorTransition = FALSE;
    gPauseScreenFlag = 0;
    gUnk_3000b85 = 0;
    gDisablePauseFlag = FALSE;
    gSamusDoorPositionOffset = 0;
    gDebugFlag = FALSE;
}
