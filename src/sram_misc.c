#include "sram_misc.h"

#include "gba.h"
#include "sram/sram.h"
#include "types.h"

#include "data/generic_data.h"
#include "data/sram_pointers.h"

#include "structs/save_file.h"

/**
 * @brief c28 | 38 | Erases all save files, excluding the SRAM header (unused)
 *
 */
void EraseSram_Unused(void)
{
    BitFill(3, USHORT_MAX, EWRAM_SRAM + SRAM_FULL_HEADER_SIZE, SRAM_SIZE - SRAM_FULL_HEADER_SIZE, 16);
    SramWrite((u8*)EWRAM_SRAM + SRAM_FULL_HEADER_SIZE, SRAM_BASE + SRAM_FULL_HEADER_SIZE,
        SRAM_SIZE - SRAM_FULL_HEADER_SIZE);
}

/**
 * @brief c60 | 38 | Fully erases all the contents of SRAM
 *
 */
void EraseSram(void)
{
    BitFill(3, USHORT_MAX, EWRAM_SRAM, SRAM_SIZE, 16);
    SramWrite((u8*)EWRAM_SRAM, SRAM_BASE, SRAM_SIZE);
}

/**
 * @brief c98 | 40 | Writes the SRAM header to SRAM, and copies it to the second backup (0x7100) and writes it
 *
 */
void WriteSramHeaderToSram(void)
{
    SramWriteChecked((u8*)EWRAM_SRAM, (u8*)SRAM_BASE, 0x80);
    DMA3_COPY_16(EWRAM_SRAM, EWRAM_SRAM + 0x7100, 0x40);
    SramWriteChecked((u8*)EWRAM_SRAM + 0x7100, (u8*)SRAM_BASE + 0x7100, 0x80);
}

/**
 * @brief cd8 | 18 | Writes the backup of the SRAM header to SRAM
 *
 */
void WriteSramHeaderBackupToSram(void)
{
    SramWriteChecked((u8*)EWRAM_SRAM + SRAM_HEADER_SIZE, (u8*)SRAM_BASE + SRAM_HEADER_SIZE, SRAM_HEADER_SIZE);
}

/**
 * @brief cf0 | 18 | Writes the second backup of the SRAM header (0x7100) to SRAM
 *
 */
void WriteSramHeaderBackup2ToSram(void)
{
    SramWriteChecked((u8*)EWRAM_SRAM + 0x7100, (u8*)SRAM_BASE + 0x7100, 0x80);
}

/**
 * @brief d08 | 2c | Writes the most recent save file to SRAM
 *
 */
void WriteMostRecentFileToSram(void)
{
    SramWrite((u8*)sSaveDataEwramPointers[gMostRecentSaveFile], (u8*)sSaveDataSramPointers[gMostRecentSaveFile],
        sizeof(struct SaveFile));
}

/**
 * @brief d34 | 2c | Writes the backup of the most recent save file to SRAM
 *
 */
void WriteMostRecentFileBackupToSram(void)
{
    SramWrite((u8*)sSaveDataEwramBackupPointers[gMostRecentSaveFile],
        (u8*)sSaveDataSramBackupPointers[gMostRecentSaveFile], sizeof(struct SaveFile));
}

/**
 * @brief d60 | 1c | Reads all the save files (and the data after them) from SRAM to EWRAM
 *
 */
void ReadAllFilesToEwram(void)
{
    SramWriteUnchecked((u8*)SRAM_BASE + 0x200, (u8*)EWRAM_SRAM + 0x200, 0x7e00);
}

/**
 * @brief d7c | 2c | Reads the most recent save file from SRAM to EWRAM
 *
 */
void ReadMostRecentFileToEwram(void)
{
    SramWriteUnchecked((u8*)sSaveDataSramPointers[gMostRecentSaveFile],
        (u8*)sSaveDataEwramPointers[gMostRecentSaveFile], sizeof(struct SaveFile));
}

/**
 * @brief da8 | 2c | Reads the SRAM header, its backup and its second backup from SRAM to EWRAM
 *
 */
void ReadSramHeaderToEwram(void)
{
    SramWriteUnchecked((u8*)SRAM_BASE, (u8*)EWRAM_SRAM, 0x100);
    SramWriteUnchecked((u8*)SRAM_BASE + 0x7100, (u8*)EWRAM_SRAM + 0x7100, 0x80);
}

/**
 * @brief dd4 | 18 | Writes the most recent save file data (0x7000) to SRAM
 *
 */
void WriteMostRecentSaveFileDataToSram(void)
{
    SramWriteChecked((u8*)EWRAM_SRAM + 0x7000, (u8*)SRAM_BASE + 0x7000, 0x40);
}

/**
 * @brief dec | 28 | Writes a copy of the language data to SRAM
 *
 * @param copy Copy (0 = main, 1 = backup)
 */
void WriteLanguageDataToSram(u8 copy)
{
    SramWriteChecked((u8*)sLanguageDataEwramPointers[copy], (u8*)sLanguageDataSramPointers[copy], 0x40);
}

/**
 * @brief e14 | 18 | Writes 0x7FF0-0x7FFF to SRAM (unused, the game doesn't store anything there)
 *
 */
void unk_e14(void)
{
    SramWriteChecked((u8*)EWRAM_SRAM + 0x7ff0, (u8*)SRAM_BASE + 0x7ff0, 0x10);
}

/**
 * @brief e2c | 1c | Writes the recorded demo inputs and durations (0x7800) to SRAM
 *
 */
void WriteDemoInputsToSram(void)
{
    SramWriteChecked((u8*)EWRAM_SRAM + 0x7800, (u8*)SRAM_BASE + 0x7800, 0x400);
}
