#include "save_file.h"
#include "callbacks.h"
#include "dma.h"
#include "event.h"
#include "gba.h"
#include "globals.h"
#include "macros.h"
#include "minimap.h"
#include "sram/sram.h"
#include "sram_misc.h"
#include "types.h"

#include "audio/track_internal.h"

#include "data/sram_data.h"
#include "data/sram_pointers.h"

#include "constants/connection.h"
#include "constants/event.h"
#include "constants/samus.h"

#include "structs/audio.h"
#include "structs/bg_clip.h"
#include "structs/block.h"
#include "structs/connection.h"
#include "structs/event.h"
#include "structs/menus/boot_debug.h"
#include "structs/minimap.h"
#include "structs/samus.h"
#include "structs/save_file.h"
#include "structs/scroll.h"
#include "structs/sprite.h"

extern const struct Door* sAreaDoorPointers[AREA_END];

#define SAVE_FILE_POINTER(file) ((struct SaveFile*)sSaveDataEwramPointers[(file)])

#define WORLD_DATA_MINIMAP_SIZE 0x380
#define WORLD_DATA_COLLECTED_TANKS_OFFSET 0xC80

/**
 * @brief 7eea4 | 18 | Reads all the SRAM data
 *
 */
void Sram_ReadAll(void)
{
    Sram_ReadHeader();
    unk_7fb84();
    SramRead_MostRecentSaveFile();
    SramRead_Language();
}

/**
 * @brief 7eebc | 6c | Writes the SRAM header
 *
 */
void Sram_WriteHeader(void)
{
    struct SramHeader* pHeader;
    s32 i;
    u32* src;
    u32 checksum;

    pHeader = EWRAM_SRAM_HEADER;

    pHeader->unk_8 = '0';
    pHeader->unk_9 = '1';
    pHeader->unk_A = gUnk_3000010;
    pHeader->unk_B = 2;

    for (i = 0; i < SRAM_HEADER_MAGIC_SIZE; i++)
        pHeader->magic[i] = sSramHeaderMagic[i];

    pHeader->checksum = 0;
    pHeader->notChecksum = UINT_MAX;

    src = (u32*)EWRAM_SRAM_HEADER;
    checksum = 0;
    for (i = sizeof(struct SramHeader) / 16 - 1; i >= 0; i--)
    {
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
    }

    pHeader->checksum = checksum;
    pHeader->notChecksum = ~checksum;

    unk_c98();
}

/**
 * @brief 7ef28 | 150 | Reads the SRAM header
 *
 */
void Sram_ReadHeader(void)
{
    u32 corrupted;
    u32 backupCorrupted;
    u32 backup2Corrupted;

    SramTestFlash();
    if (!gSramTestFailed)
        ReadSramHeaderToEwram();

    corrupted = Sram_VerifyHeader(0);
    backupCorrupted = Sram_VerifyHeader(1);
    backup2Corrupted = Sram_VerifyHeader(2);

    if (corrupted)
    {
        DMA3_FILL_16(USHORT_MAX, EWRAM_SRAM_HEADER, SRAM_HEADER_SIZE);

        if (backup2Corrupted)
        {
            DMA3_FILL_16(USHORT_MAX, EWRAM_SRAM_HEADER_BACKUP_2, SRAM_HEADER_SIZE);

            if (backupCorrupted)
            {
                DMA3_FILL_16(USHORT_MAX, EWRAM_SRAM_HEADER_BACKUP, SRAM_HEADER_SIZE);
            }
            else
            {
                DMA3_COPY_16(EWRAM_SRAM_HEADER_BACKUP, EWRAM_SRAM_HEADER, SRAM_HEADER_SIZE / 2);
                corrupted = FALSE;
                unk_c98();
            }
        }
        else
        {
            DMA3_COPY_16(EWRAM_SRAM_HEADER_BACKUP_2, EWRAM_SRAM_HEADER, SRAM_HEADER_SIZE / 2);
            corrupted = FALSE;
            unk_c98();

            if (backupCorrupted)
            {
                DMA3_COPY_16(EWRAM_SRAM_HEADER, EWRAM_SRAM_HEADER_BACKUP, SRAM_HEADER_SIZE / 2);
                unk_cd8();
            }
        }
    }
    else
    {
        DMA3_COPY_16(EWRAM_SRAM_HEADER, EWRAM_SRAM_HEADER_BACKUP, SRAM_HEADER_SIZE / 2);
        unk_cd8();

        if (backup2Corrupted)
        {
            DMA3_COPY_16(EWRAM_SRAM_HEADER, EWRAM_SRAM_HEADER_BACKUP_2, SRAM_HEADER_SIZE / 2);
            unk_cf0();
        }
    }

    if (!corrupted)
    {
        gUnk_3000010 = 0;
    }
    else
    {
        EraseSram();
        gUnk_3000010 = 0;
        Sram_WriteHeader();
    }
}

/**
 * @brief 7f078 | 80 | Verifies an SRAM header
 *
 * @param header Header (0 = main, 1 = backup, 2 = second backup)
 * @return u32 Error flags
 */
u32 Sram_VerifyHeader(u8 header)
{
    u32 result;
    struct SramHeader* pHeader;
    u32* src;
    u32 checksum;
    u32 storedChecksum;
    s32 i;

    result = 0;

    if (header == 2)
        pHeader = EWRAM_SRAM_HEADER_BACKUP_2;
    else if (header == 1)
        pHeader = EWRAM_SRAM_HEADER_BACKUP;
    else
        pHeader = EWRAM_SRAM_HEADER;

    src = (u32*)pHeader;
    checksum = 0;
    storedChecksum = pHeader->checksum;

    for (i = 0; i < (s32)sizeof(struct SramHeader) / 16; i++)
    {
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
    }

    if (storedChecksum != checksum)
        result |= 1;

    for (i = 0; i < SRAM_HEADER_MAGIC_SIZE; i++)
    {
        if (pHeader->magic[i] != sSramHeaderMagic[i])
            result |= 2;
    }

    if (storedChecksum != ~pHeader->notChecksum)
        result |= 4;

    return result;
}

/**
 * @brief 7f0f8 | 138 | Processes the save done after the new file intro
 *
 * @param stage Stage
 */
void Sram_ProcessIntroSave(u8 stage)
{
    if (gSaveFilesInfo[gMostRecentSaveFile].unk_F)
    {
        switch (stage)
        {
            case 0:
                gDisableSoftReset = TRUE;
                gGameCompletion.introPlayed = TRUE;
                gSaveFilesInfo[gMostRecentSaveFile].unk_11 = TRUE;
                return;

            case 1:
            case 2:
                return;

            case 3:
                DmaTransfer(3, sSaveDataEwramPointers[gMostRecentSaveFile],
                    (void*)sSaveDataEwramBackupPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
                gDisableSoftReset = FALSE;
                return;
        }
    }
    else
    {
        switch (stage)
        {
            case 0:
                gDisableSoftReset = TRUE;
                gGameCompletion.introPlayed = TRUE;
                gSaveFilesInfo[gMostRecentSaveFile].unk_11 = TRUE;
                gGameCompletion.completedGame = gSaveFilesInfo[gMostRecentSaveFile].unk_10;
                BitFill(3, 0, (void*)sSaveDataEwramPointers[gMostRecentSaveFile], 0x300, 16);
                return;

            case 1:
                Sram_WriteHeaderAndGameInfo();
                return;

            case 2:
                WriteMostRecentFileToSram();
                return;

            case 3:
                DmaTransfer(3, sSaveDataEwramPointers[gMostRecentSaveFile],
                    (void*)sSaveDataEwramBackupPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
                gDisableSoftReset = FALSE;
                return;
        }
    }

    gDisableSoftReset = FALSE;
}

/**
 * @brief 7f230 | 84 | Writes the header and the game info of the current save file
 *
 */
void Sram_WriteHeaderAndGameInfo(void)
{
    struct SaveFile* pFile;
    s32 i;
    u32* src;
    u32 checksum;

    pFile = SAVE_FILE_POINTER(gMostRecentSaveFile);

    Sram_StringCopy_MetroidEpisode4A(pFile->magic, sSaveFileMagic);
    pFile->checksum = 0;
    pFile->notChecksum = UINT_MAX;
    pFile->gameCompletion.introPlayed = gGameCompletion.introPlayed;
    pFile->gameCompletion.completedGame = gGameCompletion.completedGame;
    Sram_StringCopy_SAVE_END(pFile->endMagic, sSaveFileEndMagic);

    src = (u32*)sSaveDataEwramPointers[gMostRecentSaveFile];
    checksum = 0;
    for (i = sizeof(struct SaveFile) / 32 - 1; i >= 0; i--)
    {
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
    }

    pFile->checksum = checksum;
    pFile->notChecksum = ~checksum;
}

/**
 * @brief 7f2b4 | 90 | Processes the save done after the ending
 *
 * @param stage Stage
 */
void Sram_ProcessEndingSave(u8 stage)
{
    switch (stage)
    {
        case 0:
            ReadMostRecentFileToEwram();
            break;

        case 1:
            gGameCompletion.completedGame = TRUE;
            Sram_CopyGameCompletion();
            break;

        case 2:
            WriteMostRecentFileToSram();
            gSaveFilesInfo[gMostRecentSaveFile].unk_10 = gGameCompletion.completedGame;
            break;

        case 3:
            DmaTransfer(3, sSaveDataEwramPointers[gMostRecentSaveFile],
                (void*)sSaveDataEwramBackupPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
            break;
    }
}

/**
 * @brief 7f344 | 68 | Copies the game completion to the current save file
 *
 */
void Sram_CopyGameCompletion(void)
{
    struct SaveFile* pFile;
    s32 i;
    u32* src;
    u32 checksum;

    pFile = SAVE_FILE_POINTER(gMostRecentSaveFile);

    pFile->checksum = 0;
    pFile->notChecksum = UINT_MAX;
    pFile->gameCompletion.completedGame = gGameCompletion.completedGame;

    src = (u32*)sSaveDataEwramPointers[gMostRecentSaveFile];
    checksum = 0;
    for (i = sizeof(struct SaveFile) / 32 - 1; i >= 0; i--)
    {
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
    }

    pFile->checksum = checksum;
    pFile->notChecksum = ~checksum;
}

/**
 * @brief 7f3ac | a4 | Saves the game during gameplay
 *
 * @param stage Stage
 */
void Sram_QuickSave(u8 stage)
{
    switch (stage)
    {
        case 0:
            gDisableSoftReset = TRUE;
            gUnk_3000b90 = TRUE;
            WriteMostRecentFileBackupToSram();
            return;

        case 1:
            SramWrite_WorldData();
            SramWrite_ToEwram();
            return;

        case 2:
            WriteMostRecentFileToSram();
            gSaveFilesInfo[gMostRecentSaveFile].exists = TRUE;
            return;

        case 3:
            DmaTransfer(3, sSaveDataEwramPointers[gMostRecentSaveFile],
                (void*)sSaveDataEwramBackupPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
    }

    gDisableSoftReset = FALSE;
}

/**
 * @brief 7f450 | 370 | Writes the current game state to the current save file in EWRAM
 * 
 */
void SramWrite_ToEwram(void)
{
    struct SaveFile* pFile;
    s32 i;
    u32* src;
    u32 checksum;
    struct SaveMusicInfo musicInfo;

    musicInfo.musicTrack = gMusicInfo.musicTrack;
    musicInfo.unk_1E = gMusicInfo.unk_1E;
    musicInfo.unk_20 = gMusicInfo.unk_20;
    musicInfo.priority = gMusicInfo.priority;
    musicInfo.unk_2 = gMusicInfo.unk_2;

    pFile = SAVE_FILE_POINTER(gMostRecentSaveFile);

    Sram_StringCopy_MetroidEpisode4A(pFile->magic, sSaveFileMagic);
    pFile->checksum = 0;
    pFile->notChecksum = UINT_MAX;

    pFile->gameCompletion = gGameCompletion;
    pFile->unk_1C = gUnk_3000b90;

    pFile->currentArea = gCurrentArea;
    pFile->currentRoom = gCurrentRoom;
    pFile->lastDoorUsed = gLastDoorUsed;
    pFile->abilityCount = gAbilityCount;
    pFile->eventCounter = gEventCounter;
    pFile->previousNavigationConversation = gPreviousNavigationConversation;
    pFile->previousCutscene = gPreviousCutscene;
    pFile->minimapX = gMinimapX;
    pFile->minimapY = gMinimapY;
    pFile->soundEventCounter = gSoundEventCounter;
    pFile->previousSoundEvent = gPreviousSoundEvent;
    pFile->unk_2A = gFlashingSectorNumber;
    pFile->securityHatchLevelBackup = gSecurityHatchLevelBackup;

    pFile->camera = *(struct SaveCamera*)&gCamera;

    pFile->bg0XPosition = gBg0XPosition;
    pFile->bg0YPosition = gBg0YPosition;
    pFile->bg1XPosition = gBg1XPosition;
    pFile->bg1YPosition = gBg1YPosition;
    pFile->bg2XPosition = gBg2XPosition;
    pFile->bg2YPosition = gBg2YPosition;
    pFile->bg3XPosition = gBg3XPosition;
    pFile->bg3YPosition = gBg3YPosition;

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
        pFile->numberOfNeverReformBlocks[i] = gNumberOfNeverReformBlocks[i];

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
        pFile->numberOfCollectedTanks[i] = gNumberOfCollectedTanks[i];

    pFile->samusData = gSamusData;
    pFile->samusAnimationInfo = gSamusAnimationInfo;
    pFile->samusEcho = gSamusEcho;
    pFile->samusEnvironmentalEffects[0] = gSamusEnvironmentalEffects[0];
    pFile->samusEnvironmentalEffects[1] = gSamusEnvironmentalEffects[1];
    pFile->equipment = gEquipment;

    pFile->preventMovementTimer = gPreventMovementTimer;
    pFile->disableDrawingSamusAndScrollingFlag = gDisableDrawingSamusAndScrollingFlag;

    pFile->atmosphericStabilizersOnline = gAtmosphericStabilizersOnline;
    pFile->missileGeronsDestroyed = gMissileGeronsDestroyed;
    pFile->superMissileGeronsDestroyed = gSuperMissileGeronsDestroyed;
    pFile->powerBombGeronsDestroyed = gPowerBombGeronsDestroyed;
    pFile->gadorasDestroyed = gGadorasDestroyed;
    pFile->missileHatchDestroyed = gMissileHatchDestroyed;
    pFile->waterLowered = gWaterLowered;

    pFile->inGameTimer = gInGameTimer;
    pFile->musicInfo = musicInfo;

    Sram_StringCopy_SAVE_END(pFile->endMagic, sSaveFileEndMagic);

    src = (u32*)sSaveDataEwramPointers[gMostRecentSaveFile];
    checksum = 0;
    for (i = sizeof(struct SaveFile) / 32 - 1; i >= 0; i--)
    {
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
    }

    pFile->checksum = checksum;
    pFile->notChecksum = ~checksum;
}

/**
 * @brief 7f7c0 | 2e8 | Reads the current save file in EWRAM to the current game state
 * 
 */
void SramRead_FromEwram(void)
{
    struct SaveFile* pFile;
    s32 i;
    struct SaveMusicInfo musicInfo;

    pFile = SAVE_FILE_POINTER(gMostRecentSaveFile);

    gGameCompletion = pFile->gameCompletion;
    gUnk_3000b90 = pFile->unk_1C;

    gCurrentArea = pFile->currentArea;
    gCurrentRoom = pFile->currentRoom;
    gLastDoorUsed = pFile->lastDoorUsed;
    gAbilityCount = pFile->abilityCount;
    gEventCounter = pFile->eventCounter;
    gPreviousNavigationConversation = pFile->previousNavigationConversation;
    gPreviousCutscene = pFile->previousCutscene;
    gMinimapX = pFile->minimapX;
    gMinimapY = pFile->minimapY;
    gSoundEventCounter = pFile->soundEventCounter;
    gPreviousSoundEvent = pFile->previousSoundEvent;
    gFlashingSectorNumber = pFile->unk_2A;
    gSecurityHatchLevelBackup = pFile->securityHatchLevelBackup;

    *(struct SaveCamera*)&gCamera = pFile->camera;

    gBg0XPosition = pFile->bg0XPosition;
    gBg0YPosition = pFile->bg0YPosition;
    gBg1XPosition = pFile->bg1XPosition;
    gBg1YPosition = pFile->bg1YPosition;
    gBg2XPosition = pFile->bg2XPosition;
    gBg2YPosition = pFile->bg2YPosition;
    gBg3XPosition = pFile->bg3XPosition;
    gBg3YPosition = pFile->bg3YPosition;

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
        gNumberOfNeverReformBlocks[i] = pFile->numberOfNeverReformBlocks[i];

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
        gNumberOfCollectedTanks[i] = pFile->numberOfCollectedTanks[i];

    gSamusData = pFile->samusData;
    gSamusAnimationInfo = pFile->samusAnimationInfo;
    gSamusEcho = pFile->samusEcho;
    gSamusEnvironmentalEffects[0] = pFile->samusEnvironmentalEffects[0];
    gSamusEnvironmentalEffects[1] = pFile->samusEnvironmentalEffects[1];
    gEquipment = pFile->equipment;

    gPreventMovementTimer = pFile->preventMovementTimer;
    gDisableDrawingSamusAndScrollingFlag = pFile->disableDrawingSamusAndScrollingFlag;

    gAtmosphericStabilizersOnline = pFile->atmosphericStabilizersOnline;
    gMissileGeronsDestroyed = pFile->missileGeronsDestroyed;
    gSuperMissileGeronsDestroyed = pFile->superMissileGeronsDestroyed;
    gPowerBombGeronsDestroyed = pFile->powerBombGeronsDestroyed;
    gGadorasDestroyed = pFile->gadorasDestroyed;
    gMissileHatchDestroyed = pFile->missileHatchDestroyed;
    gWaterLowered = pFile->waterLowered;

    gInGameTimer = pFile->inGameTimer;

    musicInfo = pFile->musicInfo;
    gMusicInfo.musicTrack = musicInfo.musicTrack;
    gMusicInfo.unk_1E = musicInfo.unk_1E;
    gMusicInfo.unk_20 = musicInfo.unk_20;
    gMusicInfo.priority = musicInfo.priority;
    gMusicInfo.unk_2 = musicInfo.unk_2;
}

/**
 * @brief 7faa8 | 1c | Copies the save file magic string
 * 
 * @param dst Destination
 * @param src Source
 */
void Sram_StringCopy_MetroidEpisode4A(u8* dst, const u8* src)
{
    s32 i;

    for (i = 0; i < SRAM_MAGIC_SIZE; i++)
        dst[i] = src[i];
}

/**
 * @brief 7fac4 | 1c | Copies the save file end string
 * 
 * @param dst Destination
 * @param src Source
 */
void Sram_StringCopy_SAVE_END(u8* dst, const u8* src)
{
    s32 i;

    for (i = 0; i < SRAM_END_MAGIC_SIZE; i++)
        dst[i] = src[i];
}

/**
 * @brief 7fae0 | 68 | Tests if SRAM can be written to and read from
 * 
 */
void SramTestFlash(void)
{
    u32 result;
    u8 buffer[16];
    s32 i;

    result = 0;
    gSramTestFailed = FALSE;

    if (SramWriteChecked((u8*)sSramTestData, SRAM_BASE + 0x7FE0, sizeof(buffer)))
        result = 1;

    SramWriteUnchecked(SRAM_BASE + 0x7FE0, buffer, sizeof(buffer));

    for (i = 0; i < (s32)sizeof(buffer); i++)
        buffer[i]++;

    if (SramWriteChecked(buffer, SRAM_BASE + 0x7FE0, sizeof(buffer)))
        result |= 2;

    gSramTestFailed = result != 0;
}

/**
 * @brief 7fb48 | 3c | Backs up the current save file (unused)
 * 
 */
void Sram_BackupCurrentFile_Unused(void)
{
    DmaTransfer(3, sSaveDataEwramPointers[gMostRecentSaveFile],
        (void*)sSaveDataEwramBackupPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
    WriteMostRecentFileBackupToSram();
}

/**
 * @brief 7fb84 | 18c | Reads and verifies all the save files
 * 
 */
void unk_7fb84(void)
{
    struct SaveFileInfo emptyInfo;
    s32 i;
    s32 flag;

    memset(&emptyInfo, 0, sizeof(emptyInfo));
    for (i = 0; i < ARRAY_SIZE(gSaveFilesInfo); i++)
        gSaveFilesInfo[i] = emptyInfo;

    gMostRecentSaveFile = 0;
    gIsLoadingFile = FALSE;

    if (!gSramTestFailed)
        ReadAllFilesToEwram();

    for (i = 0; i < ARRAY_SIZE(gSaveFilesInfo); i++)
    {
        gMostRecentSaveFile = i;
        unk_7fd10();

        flag = gSaveFilesInfo[gMostRecentSaveFile].corruptionFlag;
        if (flag == 0)
        {
            DmaTransfer(3, sSaveDataEwramPointers[gMostRecentSaveFile],
                (void*)sSaveDataEwramBackupPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
            WriteMostRecentFileBackupToSram();
            gSaveFilesInfo[i].exists = TRUE;
        }
        else if (flag == 1)
        {
            DmaTransfer(3, sSaveDataEwramBackupPointers[gMostRecentSaveFile],
                (void*)sSaveDataEwramPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
            gSaveFilesInfo[i].exists = flag;
        }
        else if (flag == 2)
        {
            BitFill(3, USHORT_MAX, (void*)sSaveDataEwramPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
            BitFill(3, USHORT_MAX, (void*)sSaveDataEwramBackupPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
        }
        else if (flag == 3)
        {
            BitFill(3, USHORT_MAX, (void*)sSaveDataEwramPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
            WriteMostRecentFileToSram();
            BitFill(3, USHORT_MAX, (void*)sSaveDataEwramBackupPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
            WriteMostRecentFileBackupToSram();
            gSaveFilesInfo[gMostRecentSaveFile].corruptionFlag = 0;
        }
        else
        {
            while (TRUE);
        }
    }

    gMostRecentSaveFile = 0;
}

/**
 * @brief 7fd10 | a0 | Checks the corruption state of the current save file
 * 
 */
void unk_7fd10(void)
{
    s32 result;
    s32 backupResult;

    result = unk_7fdb0(FALSE);
    backupResult = unk_7fdb0(TRUE);

    if (result == 0)
    {
        gSaveFilesInfo[gMostRecentSaveFile].corruptionFlag = 0;
    }
    else if (result == 1)
    {
        gSaveFilesInfo[gMostRecentSaveFile].corruptionFlag = 1;
        if (backupResult != 0)
            gSaveFilesInfo[gMostRecentSaveFile].corruptionFlag = 2;
    }
    else
    {
        gSaveFilesInfo[gMostRecentSaveFile].corruptionFlag = 3;
        if (backupResult == 0)
            gSaveFilesInfo[gMostRecentSaveFile].corruptionFlag = 1;
        else if (backupResult == 1)
            gSaveFilesInfo[gMostRecentSaveFile].corruptionFlag = 2;
    }
}

/**
 * @brief 7fdb0 | b0 | Verifies the current save file
 *
 * @param useBackup Use backup
 * @return s32 Error count (checksum error + magic error)
 */
s32 unk_7fdb0(u8 useBackup)
{
    s32 checksumResult;
    s32 magicResult;
    struct SaveFile* pFile;
    u32* src;
    u32 checksum;
    u32 storedChecksum;
    s32 i;

    checksumResult = 0;
    magicResult = 0;

    if (!useBackup)
        pFile = (struct SaveFile*)sSaveDataEwramPointers[gMostRecentSaveFile];
    else
        pFile = (struct SaveFile*)sSaveDataEwramBackupPointers[gMostRecentSaveFile];

    src = (u32*)pFile;
    checksum = 0;
    storedChecksum = pFile->checksum;

    for (i = 0; i < (s32)sizeof(struct SaveFile) / 32; i++)
    {
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
        checksum += *src++;
    }

    if (storedChecksum != checksum)
        checksumResult |= 1;
    else if (storedChecksum != ~pFile->notChecksum)
        checksumResult |= 1;

    for (i = 0; i < SRAM_MAGIC_SIZE; i++)
    {
        if (sSaveFileMagic[i] != pFile->magic[i])
            magicResult |= 1;
    }

    {
        // FIXME: Fake match, forces the copy of magicResult into r0
        register s32 magic asm("r0") = magicResult;
        asm("" : "+r"(magic));
        checksumResult += magic;
    }

    if (checksumResult > 1)
        BitFill(3, USHORT_MAX, pFile, sizeof(struct SaveFile), 16);

    return checksumResult;
}

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
        pData->magic[i] = sMostRecentSaveFileMagic[0][i];
        pData->magic2[i] = sMostRecentSaveFileMagic[1][i];
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
            if (pData->magic[i] != sMostRecentSaveFileMagic[0][i])
            {
                error = 3;
                break;
            }

            if (pData->magic2[i] != sMostRecentSaveFileMagic[1][i])
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
        pData->magic[i] = sLanguageDataMagic[0][i];
        pData->magic2[i] = sLanguageDataMagic[1][i];
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
                if (pData->magic[j] != sLanguageDataMagic[0][j])
                {
                    error = 3;
                    break;
                }

                if (pData->magic2[j] != sLanguageDataMagic[1][j])
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

    gInGameTimer = sDefaultInGameTime[0];
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
    gNavigationTargetLocation = 0;
    gFlashingSectorNumber = 0;

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

    gBootDebugOptions = sDefaultBootDebugOptions[0];
    gButtonAssignments = sDefaultButtonAssignments[0];

    BitFill(3, USHORT_MAX, gVisitedMinimapTiles, WORLD_DATA_MINIMAP_SIZE, 16);
    BitFill(3, USHORT_MAX, gNeverReformBlocks, 0x1200, 16);
    BitFill(3, USHORT_MAX, gCollectedTanks, 0x900, 16);

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        gNumberOfNeverReformBlocks[i] = 0;
        gNumberOfCollectedTanks[i] = 0;
    }

    gInGameTimer = sDefaultInGameTime[0];
    gDisableDrawingSamusAndScrollingFlag = FALSE;

    gPreviousNavigationConversation = UCHAR_MAX;
    gPreviousSoundEvent = UCHAR_MAX;

    gNavigationTargetLocation = 0;
    gFlashingSectorNumber = 0;
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

/**
 * @brief 80664 | e0 | Checks whether the current save file should be loaded, initializes a new one otherwise
 * 
 */
void Sram_CheckLoadSaveFile(void)
{
    gButtonAssignments = sDefaultButtonAssignments[0];
    gBootDebugOptions = sDefaultBootDebugOptions[0];

    gIsLoadingFile = gSaveFilesInfo[gMostRecentSaveFile].exists;
    if (gIsLoadingFile == FALSE)
    {
        Sram_InitSaveFile();
        gGameCompletion.completedGame = gSaveFilesInfo[gMostRecentSaveFile].unk_10;
        gGameCompletion.introPlayed = gSaveFilesInfo[gMostRecentSaveFile].unk_11;
        gGameCompletion.unk_2 = FALSE;
    }
    else
    {
        SramLoad_CurrentSave();
    }

    gUnk_3000be3 = FALSE;
    gMonochromeFading = 0;
    gDisableSoftReset = FALSE;
    gMaxInGameTimeFlag = FALSE;
    gDisableMusicFlag = FALSE;
    gSkipDoorTransition = FALSE;
    gPauseScreenFlag = 0;
    gUnk_3000b85 = 0;
    gDisablePauseFlag = FALSE;
    gSamusDoorPositionOffset = 0;
    gDebugFlag = FALSE;
}

/**
 * @brief 80744 | a8 | Erases the current save file
 * 
 * @param stage Stage
 */
void Sram_EraseFile(u8 stage)
{
    struct SaveFileInfo emptyInfo;

    memset(&emptyInfo, 0, sizeof(emptyInfo));

    if (stage == 0)
    {
        gDisableSoftReset = TRUE;
        gSaveFilesInfo[gMostRecentSaveFile] = emptyInfo;
        BitFill(3, USHORT_MAX, (void*)sSaveDataEwramPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
    }
    else if (stage == 1)
    {
        WriteMostRecentFileToSram();
    }
    else if (stage == 2)
    {
        BitFill(3, USHORT_MAX, (void*)sSaveDataEwramBackupPointers[gMostRecentSaveFile], sizeof(struct SaveFile), 16);
    }
    else
    {
        if (stage == 3)
            WriteMostRecentFileBackupToSram();

        gDisableSoftReset = FALSE;
    }
}

/**
 * @brief 807ec | c8 | Copies the current save file to another file
 * 
 * @param dst Destination file
 * @param stage Stage
 */
void Sram_CopyFile(u8 dst, u8 stage)
{
    u8 currentFile;

    if (stage == 0)
    {
        gDisableSoftReset = TRUE;
        gSaveFilesInfo[dst] = gSaveFilesInfo[gMostRecentSaveFile];
        DmaTransfer(3, sSaveDataEwramPointers[gMostRecentSaveFile], (void*)sSaveDataEwramPointers[dst],
            sizeof(struct SaveFile), 16);
    }
    else if (stage == 1)
    {
        currentFile = gMostRecentSaveFile;
        gMostRecentSaveFile = dst;
        WriteMostRecentFileToSram();
        gMostRecentSaveFile = currentFile;
    }
    else if (stage == 2)
    {
        DmaTransfer(3, sSaveDataEwramBackupPointers[gMostRecentSaveFile], (void*)sSaveDataEwramBackupPointers[dst],
            sizeof(struct SaveFile), 16);
    }
    else
    {
        if (stage == 3)
        {
            currentFile = gMostRecentSaveFile;
            gMostRecentSaveFile = dst;
            WriteMostRecentFileBackupToSram();
            gMostRecentSaveFile = currentFile;
        }

        gDisableSoftReset = FALSE;
    }
}

/**
 * @brief 808b4 | 9c | Updates the info of every save file
 * 
 */
void Sram_WriteFileInfo(void)
{
    s32 i;
    struct SaveFile* pFile;

    for (i = 0; i < ARRAY_SIZE(gSaveFilesInfo); i++)
    {
        if (gSaveFilesInfo[i].exists == TRUE)
        {
            pFile = SAVE_FILE_POINTER(i);

            gSaveFilesInfo[i].currentArea = pFile->currentArea;
            gSaveFilesInfo[i].eventCounter = pFile->eventCounter;
            gSaveFilesInfo[i].currentEnergy = pFile->equipment.currentEnergy;
            gSaveFilesInfo[i].maxEnergy = pFile->equipment.maxEnergy;
            gSaveFilesInfo[i].currentMissiles = pFile->equipment.currentMissiles;
            gSaveFilesInfo[i].maxMissiles = pFile->equipment.maxMissiles;
            gSaveFilesInfo[i].weaponsStatus = pFile->equipment.weaponsStatus;
            gSaveFilesInfo[i].igtHours = pFile->inGameTimer.hours;
            gSaveFilesInfo[i].igtMinutes = pFile->inGameTimer.minutes;
            gSaveFilesInfo[i].unk_F = pFile->unk_1C;
            gSaveFilesInfo[i].unk_10 = pFile->gameCompletion.completedGame;
            gSaveFilesInfo[i].unk_11 = pFile->gameCompletion.introPlayed;
        }

        if (!gSaveFilesInfo[i].exists || !gSaveFilesInfo[i].unk_F)
        {
            gSaveFilesInfo[i].exists = FALSE;
            gSaveFilesInfo[i].currentArea = 0;
            gSaveFilesInfo[i].eventCounter = 0;
            gSaveFilesInfo[i].currentEnergy = 0;
            gSaveFilesInfo[i].maxEnergy = 0;
            gSaveFilesInfo[i].currentMissiles = 0;
            gSaveFilesInfo[i].maxMissiles = 0;
            gSaveFilesInfo[i].weaponsStatus = 0;
            gSaveFilesInfo[i].igtHours = 0;
            gSaveFilesInfo[i].igtMinutes = 0;
        }
    }
}

/**
 * @brief 80950 | c | V-blank code while a file is loading
 * 
 */
void Sram_LoadingfileVblank(void)
{
    vu8 c = 0;
}

/**
 * @brief 8095c | c | V-blank code after a file was loaded
 * 
 */
void Sram_AfterLoadingFileVblank(void)
{
    UpdateAudio();
}

/**
 * @brief 80968 | 2c | Checks whether the current save file should be loaded, with the appropriate v-blank code
 * 
 * @return s32 bool, loading file
 */
s32 Sram_ChecLoadSaveFileWithBlank(void)
{
    CallbackSetVBlank(Sram_AfterLoadingFileVblank);
    Sram_CheckLoadSaveFile();
    CallbackSetVBlank(Sram_LoadingfileVblank);

    return gIsLoadingFile;
}

/**
 * @brief 80994 | 5c | Rewrites a save file to SRAM if it was corrupted
 * 
 * @param file File
 */
void Sram_SetCurrentFile(u8 file)
{
    u8 currentFile;

    currentFile = gMostRecentSaveFile;
    gMostRecentSaveFile = file;

    switch (gSaveFilesInfo[gMostRecentSaveFile].corruptionFlag)
    {
        case 1:
            WriteMostRecentFileToSram();
            break;

        case 2:
            WriteMostRecentFileToSram();
            WriteMostRecentFileBackupToSram();
            break;

        case 0:
            break;
    }

    gSaveFilesInfo[gMostRecentSaveFile].corruptionFlag = 0;
    gMostRecentSaveFile = currentFile;
}
