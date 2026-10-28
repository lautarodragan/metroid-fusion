#include "save_file.h"
#include "dma.h"
#include "globals.h"
#include "gba.h"
#include "macros.h"
#include "sram_misc.h"
#include "sram/sram.h"
#include "types.h"

#include "data/sram_data.h"
#include "data/sram_pointers.h"

#include "constants/connection.h"
#include "constants/samus.h"

#include "structs/bg_clip.h"
#include "structs/block.h"
#include "structs/minimap.h"
#include "structs/samus.h"
#include "structs/save_file.h"

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
