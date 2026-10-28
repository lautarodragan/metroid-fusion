#include "save_file.h"
#include "dma.h"
#include "globals.h"
#include "gba.h"
#include "sram_misc.h"
#include "types.h"

#include "data/sram_data.h"
#include "data/sram_pointers.h"

#include "structs/save_file.h"

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
                gSaveFilesInfo[gMostRecentSaveFile].gameCompletion.introPlayed = TRUE;
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
                gSaveFilesInfo[gMostRecentSaveFile].gameCompletion.introPlayed = TRUE;
                gGameCompletion.completedGame = gSaveFilesInfo[gMostRecentSaveFile].gameCompletion.completedGame;
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
            gSaveFilesInfo[gMostRecentSaveFile].gameCompletion.completedGame = gGameCompletion.completedGame;
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
