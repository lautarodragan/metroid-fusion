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

#include "structs/audio.h"
#include "structs/bg_clip.h"
#include "structs/block.h"
#include "structs/connection.h"
#include "structs/event.h"
#include "structs/minimap.h"
#include "structs/samus.h"
#include "structs/save_file.h"
#include "structs/scroll.h"
#include "structs/sprite.h"

#define SAVE_FILE_POINTER(file) ((struct SaveFile*)sSaveDataEwramPointers[(file)])

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
        pHeader->magic[i] = sSramUnk_582248[i];

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
        if (pHeader->magic[i] != sSramUnk_582248[i])
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

    Sram_StringCopy_MetroidEpisode4A(pFile->magic, sSramUnk_582200);
    pFile->checksum = 0;
    pFile->notChecksum = UINT_MAX;
    pFile->gameCompletion.introPlayed = gGameCompletion.introPlayed;
    pFile->gameCompletion.completedGame = gGameCompletion.completedGame;
    Sram_StringCopy_SAVE_END(pFile->endMagic, sSramUnk_5821f8);

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

    Sram_StringCopy_MetroidEpisode4A(pFile->magic, sSramUnk_582200);
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

    Sram_StringCopy_SAVE_END(pFile->endMagic, sSramUnk_5821f8);

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

    if (SramWriteChecked((u8*)sSramUnk_5821e8, SRAM_BASE + 0x7FE0, sizeof(buffer)))
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
