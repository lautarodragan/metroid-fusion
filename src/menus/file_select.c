#include "menus/file_select.h"
#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "callbacks.h"
#include "oam.h"
#include "syscalls.h"
#include "init_helpers.h"
#include "music_wrappers.h"
#include "audio_wrappers.h"
#include "audio/track_internal.h"

#include "data/menus/file_select_data.h"

#include "constants/audio.h"
#include "constants/game_state.h"
#include "constants/menus/file_select.h"

#include "structs/save_file.h"

/**
 * @brief 9e598 | 1b8 | File select subroutine
 *
 * @return u32 Result (0 if still running)
 */
u32 FileSelectHandler(void)
{
    u32 result;

    result = 0;

    switch (gSubGameMode1)
    {
        case 0:
            FileSelectInit();
            if (gSaveFilesInfo[0].corruptionFlag == 0 && gSaveFilesInfo[1].corruptionFlag == 0 &&
                gSaveFilesInfo[2].corruptionFlag == 0)
            {
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_SAMUS_HEAD, 15, gMostRecentSaveFile * 16 + 49, 0);
                WRITE_16(REG_BG1HOFS, 2);
                gSubGameMode1 = 1;
            }
            else
            {
                WRITE_16(REG_BG1HOFS, -0x30);
                WRITE_16(REG_BG1VOFS, 0x30);
                gSubGameMode1 = 5;
            }
            break;

        case 1:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDrawText(1);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                FileSelectDrawFileInfo(0);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                FileSelectDrawFileInfo(1);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                FileSelectDrawFileInfo(2);
                FILE_SELECT_DATA.timer = 0;
                gWrittenToBldy = 14;
                gSubGameMode1 = 2;
            }
            break;

        case 2:
            FileSelectDrawAllOam();
            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                gSubGameMode1++;
            break;

        case 3:
            FILE_SELECT_DATA.result = FileSelectInput();
            if (FILE_SELECT_DATA.result != 0)
            {
                gSubGameMode1++;
                FadeMusic(20);
            }
            break;

        case 4:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                result = FILE_SELECT_DATA.result;
                gSubGameMode1 = 0;
            }
            break;

        case 5:
            if (FileSelectProcessCorruptedFile())
            {
                WRITE_16(REG_BG1HOFS, 2);
                WRITE_16(REG_BG1VOFS, -6);
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_SAMUS_HEAD, 15, gMostRecentSaveFile * 16 + 49, 0);
                gSubGameMode1 = 3;
            }
            break;
    }

    return result;
}

/**
 * @brief 9e750 | 290 | Initializes the file select screen
 *
 */
void FileSelectInit(void)
{
    u32 zero;
    u32 i;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_9eaa4);

    WRITE_16(REG_DISPCNT, 0);

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    ClearGfxRam();
    gNextOamSlot = 0;
    ResetFreeOam();

    zero = 0;
    DMA_SET(3, &zero, &gNonGameplayRam, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, sizeof(gNonGameplayRam) / sizeof(u32)));

    WRITE_16(REG_BG3CNT, 0);
    WRITE_16(REG_BG2CNT, 0);
    WRITE_16(REG_BG1CNT, 0);
    WRITE_16(REG_BG0CNT, 0);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, -6);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    LZ77UncompVram(sFileSelectUnk_742fb4, VRAM_BASE);
    LZ77UncompVram(sFileSelectUnk_7470e0, VRAM_BASE + 0xF800);
    DMA3_COPY_32(sFileSelectUnk_7476a0, PALRAM_BASE, PAL_SIZE / sizeof(u32));
    LZ77UncompVram(sFileSelectUnk_73cfac, VRAM_BASE + 0xE000);
    LZ77UncompVram(sFileSelectUnk_73d380, EWRAM_BASE);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xE800, 0x800 / sizeof(u32));
    LZ77UncompVram(sFileSelectUnk_73d5ec, VRAM_BASE + 0xF000);

    DMA3_COPY_32(sFileSelectUnk_73db84, PALRAM_BASE, PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sFileSelectUnk_73dac4, PALRAM_BASE, 8 / sizeof(u32));
    DMA3_COPY_32(&sFileSelectUnk_73dac4[4], PALRAM_BASE + 0x1C, 4 / sizeof(u32));
    WRITE_16(PALRAM_BASE, 0);

    for (i = 0; i < 0x100; i += 2)
        WRITE_16(EWRAM_BASE + 0x800 + i, (READ_16(EWRAM_BASE + 0x340 + i) & 0xFFF) | 0x1000);

    LZ77UncompVram(sFileSelectUnk_73dc20, VRAM_OBJ);
    DMA3_COPY_32(sFileSelectUnk_740d08, PALRAM_OBJ, PAL_SIZE / sizeof(u32));

    FILE_SELECT_DATA.unk_8 = 0;
    FILE_SELECT_DATA.pText = sFileSelectUnk_79ec68[gLanguage][0];

    Sram_WriteFileInfo();
    FILE_SELECT_DATA.selectedFile = gMostRecentSaveFile;

    FileSelectSetupOam(9, 0x66, 0x74, 1);
    FileSelectSetupOam(6, 0x8E, 0x74, 1);
    FileSelectSetupOam(7, 0x84, 0x30, 1);
    FileSelectDrawAllOam();

    WRITE_16(REG_BG3CNT, 0x1F03);
    WRITE_16(REG_BG2CNT, 0x1C0A);
    WRITE_16(REG_BG1CNT, 0x1D09);
    WRITE_16(REG_BG0CNT, 0x1E08);
    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(FileSelectVblank);
}

/**
 * @brief 9e9e0 | c4 | V-blank code for the file select screen
 *
 */
void FileSelectVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    switch (FILE_SELECT_DATA.dispcntAction)
    {
        case 0:
            break;

        case 1:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
            FILE_SELECT_DATA.dispcntAction = 0;
            break;

        case 3:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
            FILE_SELECT_DATA.dispcntAction = 0;
            break;

        case 2:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG0);
            FILE_SELECT_DATA.dispcntAction = 0;
            break;

        case 4:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG1);
            FILE_SELECT_DATA.dispcntAction = 0;
            break;

        case 5:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~(DCNT_BG0 | DCNT_BG1));
            FILE_SELECT_DATA.dispcntAction = 0;
            break;

        default:
            FILE_SELECT_DATA.dispcntAction = 0;
    }
}

/**
 * @brief 9eaa4 | c | Empty v-blank code for the file select screen
 *
 */
void unk_9eaa4(void)
{
    UpdateAudio();
}

/**
 * @brief 9eab0 | a68 | Handles the input on the file select screen
 *
 * @return u32 Result (0 if still running)
 */
u32 FileSelectInput(void)
{
    u32 result;

    result = 0;

    FileSelectProcessOam();

    switch (FILE_SELECT_DATA.subroutine)
    {
        case 0:
            if (gChangedInput & (KEY_A | KEY_START))
            {
                if (FILE_SELECT_DATA.selectedFile == 3)
                    break;

                if (FILE_SELECT_DATA.selectedFile == 4)
                    FILE_SELECT_DATA.subroutine = 34;
                else
                    FILE_SELECT_DATA.subroutine = 1;
            }
            else if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.subroutine = 34;
            }
            break;

        case 1:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FILE_SELECT_DATA.unk_8 = 1;
                FILE_SELECT_DATA.pText = sFileSelectUnk_79ec68[gLanguage][1];
                FileSelectDrawText(2);
                FileSelectSetupOam(11, 0x52, 0x76, 1);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                if (gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].unk_10 == TRUE ||
                    gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].unk_11 == TRUE ||
                    gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].exists == TRUE)
                {
                    DMA3_COPY_32(EWRAM_BASE + 0x340, VRAM_BASE + 0xEB40, 0x100 / sizeof(u32));
                    FILE_SELECT_DATA.subroutine = 3;
                }
                else
                {
                    DMA3_COPY_32(EWRAM_BASE + 0x800, VRAM_BASE + 0xEB40, 0x100 / sizeof(u32));
                    FILE_SELECT_DATA.subroutine = 2;
                }

                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.unk_E = 0;
                FileSelectSetupOam(2, 0x16, 0x67, 1);
                FILE_SELECT_DATA.dispcntAction = 3;
            }
            break;

        case 2:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.subroutine = 4;
            }
            else if (gChangedInput & (KEY_A | KEY_START))
            {
                if (gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].unk_10 == TRUE)
                    FILE_SELECT_DATA.subroutine = 9;
                else
                    FILE_SELECT_DATA.subroutine = 5;
            }
            break;

        case 4:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(2);
                FILE_SELECT_DATA.dispcntAction = 4;
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.subroutine = 0;
            }
            break;

        case 3:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.subroutine = 4;
            }
            else if (gChangedInput & (KEY_A | KEY_START))
            {
                if (FILE_SELECT_DATA.unk_E == 0)
                {
                    if (gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].exists == FALSE)
                    {
                        if (gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].unk_10 == TRUE)
                            FILE_SELECT_DATA.subroutine = 9;
                        else if (gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].unk_11 == TRUE)
                            FILE_SELECT_DATA.subroutine = 5;
                    }
                    else if (gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].exists == TRUE)
                    {
                        if (gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].unk_10 == TRUE)
                            FILE_SELECT_DATA.subroutine = 9;
                        else
                            FILE_SELECT_DATA.subroutine = 7;
                    }
                }
                else if (FILE_SELECT_DATA.unk_E == 1)
                {
                    FILE_SELECT_DATA.subroutine = 16;
                    FILE_SELECT_DATA.timer = 0;
                }
                else if (FILE_SELECT_DATA.unk_E == 2)
                {
                    FILE_SELECT_DATA.subroutine = 27;
                }
            }
            break;

        case 5:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 42)
            {
                FILE_SELECT_DATA.subroutine = 6;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 7:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 42)
            {
                FILE_SELECT_DATA.subroutine = 8;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 9:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectSetupOam(23, 0x9C, 0x78, 1);
                FILE_SELECT_DATA.dispcntAction = 2;
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xC800, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                FILE_SELECT_DATA.unk_8 = 24;
                FILE_SELECT_DATA.pText = sFileSelectUnk_79ec68[gLanguage][24];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.subroutine = 10;
                FileSelectSetupOam(24, 0x66, 0x69, 1);
                FILE_SELECT_DATA.dispcntAction = 1;
            }
            break;

        case 10:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.subroutine = 11;
            }
            else if (gChangedInput & (KEY_A | KEY_START))
            {
                if (FILE_SELECT_DATA.unk_10 == 0)
                    FILE_SELECT_DATA.subroutine = 12;
                else
                    FILE_SELECT_DATA.subroutine = 13;
            }
            break;

        case 11:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(24);
                FILE_SELECT_DATA.dispcntAction = 2;
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.unk_10 = 0;
                FILE_SELECT_DATA.subroutine = 3;
            }
            break;

        case 12:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 42)
            {
                FILE_SELECT_DATA.timer = 0;
                if (gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].exists == TRUE)
                    FILE_SELECT_DATA.subroutine = 14;
                else
                    FILE_SELECT_DATA.subroutine = 15;
            }
            break;

        case 13:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].exists = FALSE;
                gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].unk_11 = FALSE;
            }
            else if (FILE_SELECT_DATA.timer == 42)
            {
                FILE_SELECT_DATA.subroutine = 15;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 8:
        case 14:
            gMostRecentSaveFile = FILE_SELECT_DATA.selectedFile;
            Sram_CheckLoadSaveFile();
            result = 2;
            break;

        case 6:
        case 15:
            gMostRecentSaveFile = FILE_SELECT_DATA.selectedFile;
            Sram_CheckLoadSaveFile();
            result = 1;
            break;

        case 16:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FILE_SELECT_DATA.dispcntAction = 2;
                FileSelectSetupOam(12, 0x9C, 0x78, 1);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xC800, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                FILE_SELECT_DATA.unk_8 = 2;
                FILE_SELECT_DATA.pText = sFileSelectUnk_79ec68[gLanguage][2];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.subroutine = 17;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.unk_F = 0;
                if (FILE_SELECT_DATA.selectedFile == 0)
                {
                    FILE_SELECT_DATA.unk_F = 1;
                    FileSelectSetupOam(3, 0x84, 0x30, 1);
                }
                else
                {
                    FileSelectSetupOam(3, 0x84, 0x30, 1);
                }
                FILE_SELECT_DATA.dispcntAction = 1;
            }
            break;

        case 17:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.subroutine = 18;
            }
            else if (gChangedInput & (KEY_A | KEY_START))
            {
                if (gSaveFilesInfo[FILE_SELECT_DATA.unk_F].unk_10 == TRUE ||
                    gSaveFilesInfo[FILE_SELECT_DATA.unk_F].unk_11 == TRUE ||
                    gSaveFilesInfo[FILE_SELECT_DATA.unk_F].exists == TRUE)
                    FILE_SELECT_DATA.subroutine = 19;
                else
                    FILE_SELECT_DATA.subroutine = 20;
            }
            break;

        case 18:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(3);
                FILE_SELECT_DATA.dispcntAction = 2;
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.subroutine = 3;
            }
            break;

        case 19:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FILE_SELECT_DATA.dispcntAction = 2;
                DMA3_FILL_32(0, VRAM_BASE + 0xC800, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                FILE_SELECT_DATA.unk_8 = 3;
                FILE_SELECT_DATA.pText = sFileSelectUnk_79ec68[gLanguage][3];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                FILE_SELECT_DATA.dispcntAction = 1;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.subroutine = 22;
                FILE_SELECT_DATA.unk_10 = 1;
                FileSelectSetupOam(4, sFileSelectUnk_73dbb0[gLanguage][1], 0x91, 1);
            }
            break;

        case 20:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                gMostRecentSaveFile = FILE_SELECT_DATA.selectedFile;
                Sram_CopyFile(FILE_SELECT_DATA.unk_F, 0);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                Sram_CopyFile(FILE_SELECT_DATA.unk_F, 1);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                Sram_CopyFile(FILE_SELECT_DATA.unk_F, 2);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                Sram_CopyFile(FILE_SELECT_DATA.unk_F, 3);
            }
            else if (FILE_SELECT_DATA.timer == 6)
            {
                FileSelectDrawFileInfo(FILE_SELECT_DATA.unk_F);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.subroutine = 21;
            }
            break;

        case 21:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FILE_SELECT_DATA.dispcntAction = 5;
                FileSelectDestroyOamOfType(2);
                FileSelectDestroyOamOfType(3);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {

            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.unk_F = 0;
                FILE_SELECT_DATA.unk_E = 0;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.subroutine = 0;
            }
            break;

        case 22:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.subroutine = 23;
            }
            else if (gChangedInput & (KEY_A | KEY_START))
            {
                if (FILE_SELECT_DATA.unk_10 == 0)
                    FILE_SELECT_DATA.subroutine = 25;
                else
                    FILE_SELECT_DATA.subroutine = 24;
            }
            break;

        case 23:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(4);
                FILE_SELECT_DATA.dispcntAction = 2;
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xC800, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                FILE_SELECT_DATA.unk_8 = 2;
                FILE_SELECT_DATA.pText = sFileSelectUnk_79ec68[gLanguage][2];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.dispcntAction = 1;
                FILE_SELECT_DATA.subroutine = 17;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.unk_10 = 0;
            }
            break;

        case 24:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 9)
            {
                FileSelectDestroyOamOfType(4);
                FILE_SELECT_DATA.dispcntAction = 2;
            }
            else if (FILE_SELECT_DATA.timer == 10)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xC800, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 11)
            {
                FILE_SELECT_DATA.unk_8 = 2;
                FILE_SELECT_DATA.pText = sFileSelectUnk_79ec68[gLanguage][2];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.dispcntAction = 1;
                FILE_SELECT_DATA.subroutine = 17;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.unk_10 = 0;
            }
            break;

        case 25:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                gMostRecentSaveFile = FILE_SELECT_DATA.selectedFile;
                Sram_CopyFile(FILE_SELECT_DATA.unk_F, 0);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                Sram_CopyFile(FILE_SELECT_DATA.unk_F, 1);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                Sram_CopyFile(FILE_SELECT_DATA.unk_F, 2);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                Sram_CopyFile(FILE_SELECT_DATA.unk_F, 3);
            }
            else if (FILE_SELECT_DATA.timer == 11)
            {
                FileSelectDrawFileInfo(FILE_SELECT_DATA.unk_F);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.subroutine = 26;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 26:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(2);
                FileSelectDestroyOamOfType(3);
                FileSelectDestroyOamOfType(4);
                FILE_SELECT_DATA.dispcntAction = 5;
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xC800, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.unk_10 = 0;
                FILE_SELECT_DATA.unk_F = 0;
                FILE_SELECT_DATA.unk_E = 0;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.subroutine = 0;
            }
            break;

        case 27:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectSetupOam(13, 0x9C, 0x78, 1);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xC800, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                FILE_SELECT_DATA.unk_8 = 4;
                FILE_SELECT_DATA.pText = sFileSelectUnk_79ec68[gLanguage][4];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.unk_10 = 1;
                FileSelectSetupOam(5, sFileSelectUnk_73dbbe[gLanguage][1], 0x91, 1);
                FILE_SELECT_DATA.dispcntAction = 1;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.subroutine = 28;
            }
            break;

        case 28:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.subroutine = 29;
            }
            else if (gChangedInput & (KEY_A | KEY_START))
            {
                if (FILE_SELECT_DATA.unk_10 == 0)
                    FILE_SELECT_DATA.subroutine = 32;
                else
                    FILE_SELECT_DATA.subroutine = 30;
            }
            break;

        case 29:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(5);
                FILE_SELECT_DATA.dispcntAction = 2;
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xC800, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.unk_10 = 0;
                FILE_SELECT_DATA.subroutine = 3;
            }
            break;

        case 30:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 8)
            {
                FileSelectDestroyOamOfType(5);
                FILE_SELECT_DATA.dispcntAction = 2;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.unk_10 = 0;
                FILE_SELECT_DATA.subroutine = 31;
            }
            break;

        case 31:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 6)
            {

            }
            else if (FILE_SELECT_DATA.timer == 11)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xC800, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.unk_10 = 0;
                FILE_SELECT_DATA.subroutine = 3;
            }
            break;

        case 32:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                gMostRecentSaveFile = FILE_SELECT_DATA.selectedFile;
                Sram_EraseFile(0);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                Sram_EraseFile(1);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                Sram_EraseFile(2);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                Sram_EraseFile(3);
            }
            else if (FILE_SELECT_DATA.timer == 11)
            {
                FileSelectDrawFileInfo(FILE_SELECT_DATA.selectedFile);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.subroutine = 33;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 33:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(2);
                FileSelectDestroyOamOfType(5);
                FILE_SELECT_DATA.dispcntAction = 5;
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xC800, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.unk_10 = 0;
                FILE_SELECT_DATA.unk_F = 0;
                FILE_SELECT_DATA.unk_E = 0;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.subroutine = 0;
            }
            break;

        case 34:
            result = 3;
            break;
    }

    FileSelectDrawAllOam();

    return result;
}
