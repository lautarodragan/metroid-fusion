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
#include "text.h"

#include "data/menus/file_select_data.h"
#include "data/text_data.h"

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

    LZ77UncompVram(sFileSelectBgGfx, VRAM_BASE);
    LZ77UncompVram(sFileSelectBg3Tilemap, VRAM_BASE + 0xF800);
    DMA3_COPY_32(sFileSelectBgPal, PALRAM_BASE, PAL_SIZE / sizeof(u32));
    LZ77UncompVram(sFileSelectBg2Tilemap, VRAM_BASE + 0xE000);
    LZ77UncompVram(sFileSelectBg1Tilemap, EWRAM_BASE);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xE800, 0x800 / sizeof(u32));
    LZ77UncompVram(sFileSelectBg0Tilemap, VRAM_BASE + 0xF000);

    DMA3_COPY_32(sFileSelectBgPal_73db84, PALRAM_BASE, PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sFileSelectBgPal_73dac4, PALRAM_BASE, 8 / sizeof(u32));
    DMA3_COPY_32(&sFileSelectBgPal_73dac4[4], PALRAM_BASE + 0x1C, 4 / sizeof(u32));
    WRITE_16(PALRAM_BASE, 0);

    for (i = 0; i < 0x100; i += 2)
        WRITE_16(EWRAM_BASE + 0x800 + i, (READ_16(EWRAM_BASE + 0x340 + i) & 0xFFF) | 0x1000);

    LZ77UncompVram(sFileSelectObjGfx, VRAM_OBJ);
    DMA3_COPY_32(sFileSelectObjPal, PALRAM_OBJ, PAL_SIZE / sizeof(u32));

    FILE_SELECT_DATA.unk_8 = 0;
    FILE_SELECT_DATA.pText = sFileSelectTexts[gLanguage][0];

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
                FILE_SELECT_DATA.pText = sFileSelectTexts[gLanguage][1];
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
                FILE_SELECT_DATA.pText = sFileSelectTexts[gLanguage][24];
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
                FILE_SELECT_DATA.pText = sFileSelectTexts[gLanguage][2];
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
                FILE_SELECT_DATA.pText = sFileSelectTexts[gLanguage][3];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                FILE_SELECT_DATA.dispcntAction = 1;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.subroutine = 22;
                FILE_SELECT_DATA.unk_10 = 1;
                FileSelectSetupOam(4, sFileSelectChoiceCursorXPositions_73dbb0[gLanguage][1], 0x91, 1);
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
                FILE_SELECT_DATA.pText = sFileSelectTexts[gLanguage][2];
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
                FILE_SELECT_DATA.pText = sFileSelectTexts[gLanguage][2];
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
                FILE_SELECT_DATA.pText = sFileSelectTexts[gLanguage][4];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.unk_10 = 1;
                FileSelectSetupOam(5, sFileSelectChoiceCursorXPositions_73dbbe[gLanguage][1], 0x91, 1);
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

/**
 * @brief 9f518 | 418 | Sets up a new file select oam
 *
 * @param type Oam type
 * @param xPosition X position
 * @param yPosition Y position
 * @param unk Unused
 * @return u8 Oam slot (FILE_SELECT_OAM_COUNT if none was free)
 */
u8 FileSelectSetupOam(u8 type, s16 xPosition, s16 yPosition, u8 unk)
{
    s8 i;
    u32 zero;

    for (i = FILE_SELECT_OAM_COUNT - 1; i >= 0; i--)
    {
        if (FILE_SELECT_DATA.oam[i].type == FILE_SELECT_OAM_TYPE_NONE)
            break;
    }

    if (i < 0)
        return FILE_SELECT_OAM_COUNT;

    zero = 0;
    DMA_SET(3, &zero, &FILE_SELECT_DATA.oam[i], C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, sizeof(struct FileSelectOam) / sizeof(u32)));

    FILE_SELECT_DATA.oam[i].xPosition = xPosition;
    FILE_SELECT_DATA.oam[i].yPosition = yPosition;
    FILE_SELECT_DATA.oam[i].type = type;
    FILE_SELECT_DATA.oam[i].isDrawn = TRUE;

    if (type == FILE_SELECT_OAM_TYPE_SAMUS_HEAD)
    {
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectSamusHeadOam1;
        FILE_SELECT_DATA.oam[i].pHandler = FileSelectProcessSamusHead;
    }
    else if (type == FILE_SELECT_OAM_TYPE_CURSOR)
    {
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectCursorOam1;
        FILE_SELECT_DATA.oam[i].pHandler = FileSelectProcessCursor;
    }
    else if (type == FILE_SELECT_OAM_TYPE_DELETE_ARROW)
    {
        FILE_SELECT_DATA.oam[i].priority = 1;
        FILE_SELECT_DATA.oam[i].isDrawn = FALSE;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectDeleteArrowIdleOam;
        FILE_SELECT_DATA.oam[i].pHandler = FileSelectProcessDeleteArrow;
    }
    else if (type == 4)
    {
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectCursorOam1;
        FILE_SELECT_DATA.oam[i].pHandler = unk_9fddc;
    }
    else if (type == 5)
    {
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectCursorOam1;
        FILE_SELECT_DATA.oam[i].pHandler = unk_9ff00;
    }
    else if (type == 6)
    {
        FILE_SELECT_DATA.oam[i].priority = 3;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectAudioLogosOam3;
        FILE_SELECT_DATA.oam[i].pHandler = FileSelectProcessAudioLogos;
    }
    else if (type == 7)
    {
        FILE_SELECT_DATA.oam[i].priority = 2;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectFileOverlayOam[gMostRecentSaveFile];
        FILE_SELECT_DATA.oam[i].pHandler = FileSelectProcessFileOverlay;
    }
    else if (type == 8)
    {
        FILE_SELECT_DATA.oam[i].priority = 2;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectOam_7408e0;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a016c;
    }
    else if (type == 9)
    {
        FILE_SELECT_DATA.oam[i].isDrawn = FALSE;
        FILE_SELECT_DATA.oam[i].priority = 3;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectAudioSelectOam;
        FILE_SELECT_DATA.oam[i].pHandler = FileSelectProcessAudioSelect;
    }
    else if (type == 10)
    {
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectOam_740880;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a01cc;
    }
    else if (type == 11)
    {
        SoundPlay(SOUND_1FC);
        FILE_SELECT_DATA.oam[i].priority = 2;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectFileActionPanelOam1;
        FILE_SELECT_DATA.oam[i].pHandler = FileSelectProcessFileActionPanel;
    }
    else if (type == 12)
    {
        SoundPlay(SOUND_1FC);
        FILE_SELECT_DATA.oam[i].priority = 1;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectFilePanelOam1;
        FILE_SELECT_DATA.oam[i].pHandler = FileSelectProcessCopyFilePanel;
    }
    else if (type == 13)
    {
        SoundPlay(SOUND_1FC);
        FILE_SELECT_DATA.oam[i].priority = 1;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectFilePanelOam1;
        FILE_SELECT_DATA.oam[i].pHandler = FileSelectProcessEraseFilePanel;
    }
    else if (type == 14)
    {
        FILE_SELECT_DATA.oam[i].priority = 3;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a0518;
    }
    else if (type == 15)
    {
        FILE_SELECT_DATA.oam[i].priority = 3;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a0518;
    }
    else if (type == 16)
    {
        FILE_SELECT_DATA.oam[i].priority = 3;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a0518;
    }
    else if (type == 17)
    {
        FILE_SELECT_DATA.oam[i].priority = 2;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectFilePanelOam2;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a0518;
    }
    else if (type == 20)
    {
        FILE_SELECT_DATA.oam[i].priority = 3;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectOam_740b98;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a0518;
    }
    else if (type == 21)
    {
        FILE_SELECT_DATA.oam[i].priority = 3;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectOam_740b98;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a0518;
    }
    else if (type == 22)
    {
        FILE_SELECT_DATA.oam[i].priority = 3;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectOam_740b98;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a0518;
    }
    else if (type == 23)
    {
        SoundPlay(SOUND_1FC);
        FILE_SELECT_DATA.oam[i].priority = 1;
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectFilePanelOam1;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a039c;
    }
    else if (type == 24)
    {
        FILE_SELECT_DATA.oam[i].pOam = sFileSelectCursorOam1;
        FILE_SELECT_DATA.oam[i].pHandler = unk_a0424;
    }

    return i;
}

/**
 * @brief 9f930 | 1a4 | Processes the samus head oam
 *
 * @param pOam File select oam pointer
 */
void FileSelectProcessSamusHead(struct FileSelectOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->unk_9 == 0)
    {
        if (gChangedInput & KEY_UP)
        {
            switch (FILE_SELECT_DATA.selectedFile)
            {
                case 1:
                case 2:
                    pOam->xPosition = 15;
                    pOam->yPosition -= 16;
                    FILE_SELECT_DATA.selectedFile--;
                    SoundPlay(SOUND_1F9);
                    break;

                case 3:
                    pOam->xPosition = 15;
                    pOam->yPosition -= 37;
                    FILE_SELECT_DATA.selectedFile--;
                    SoundPlay(SOUND_1F9);
                    break;

                case 4:
                    pOam->xPosition = 15;
                    pOam->yPosition -= 40;
                    FILE_SELECT_DATA.selectedFile--;
                    SoundPlay(SOUND_1F9);
                    break;
            }
        }
        else if (gChangedInput & KEY_DOWN)
        {
            switch (FILE_SELECT_DATA.selectedFile)
            {
                case 0:
                case 1:
                    pOam->xPosition = 15;
                    pOam->yPosition += 16;
                    FILE_SELECT_DATA.selectedFile++;
                    SoundPlay(SOUND_1F9);
                    break;

                case 2:
                    pOam->xPosition = 15;
                    pOam->yPosition += 37;
                    FILE_SELECT_DATA.selectedFile++;
                    SoundPlay(SOUND_1F9);
                    break;

                case 3:
                    pOam->xPosition = 15;
                    pOam->yPosition += 40;
                    FILE_SELECT_DATA.selectedFile++;
                    SoundPlay(SOUND_1F9);
                    break;
            }
        }

        if (FILE_SELECT_DATA.selectedFile != 3 && gChangedInput & (KEY_A | KEY_START))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->unk_9 = 100;
            SoundPlay(SOUND_1FB);
        }
    }
    else if (pOam->unk_9 == 1)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->unk_9 = 100;
        }

        if (FILE_SELECT_DATA.timer == 11)
            pOam->unk_9 = 100;
    }
    else if (pOam->unk_9 == 100)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter)
            pFrame++;

        if (FILE_SELECT_DATA.subroutine == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectSamusHeadOam1;
            pOam->unk_9 = 0;
        }
        else if (FILE_SELECT_DATA.subroutine == 5 || FILE_SELECT_DATA.subroutine == 7 ||
            FILE_SELECT_DATA.subroutine == 12 || FILE_SELECT_DATA.subroutine == 13)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectSamusHeadOam2;
            pOam->unk_9 = 200;
        }
    }
    else
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief 9fad4 | 1bc | Processes the cursor oam
 *
 * @param pOam File select oam pointer
 */
void FileSelectProcessCursor(struct FileSelectOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->unk_9 == 0)
    {
        if (FILE_SELECT_DATA.subroutine == 2)
        {
            if (gChangedInput & KEY_B)
            {
                pOam->unk_9 = 100;
            }
            else if (gChangedInput & (KEY_A | KEY_START))
            {
                if (gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].unk_10 == TRUE)
                    SoundPlay(SOUND_1FB);
                else
                    SoundPlay(SOUND_1FE);

                FILE_SELECT_DATA.unk_E = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sFileSelectCursorOam2;
                pOam->unk_9 = 100;
            }
        }
        else if (FILE_SELECT_DATA.subroutine == 3)
        {
            if (gChangedInput & KEY_UP)
            {
                if (FILE_SELECT_DATA.unk_E != 0)
                {
                    FILE_SELECT_DATA.unk_E--;
                    pOam->yPosition -= 16;
                    SoundPlay(SOUND_1F9);
                }
            }
            else if (gChangedInput & KEY_DOWN)
            {
                if (FILE_SELECT_DATA.unk_E < 2)
                {
                    FILE_SELECT_DATA.unk_E++;
                    pOam->yPosition += 16;
                    SoundPlay(SOUND_1F9);
                }
            }

            if (gChangedInput & KEY_B)
            {
                pOam->unk_9 = 100;
            }
            else if (gChangedInput & (KEY_A | KEY_START))
            {
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sFileSelectCursorOam2;

                if (FILE_SELECT_DATA.unk_E == 0)
                {
                    pOam->unk_9 = 100;
                    if (gSaveFilesInfo[FILE_SELECT_DATA.selectedFile].unk_10 == TRUE)
                        SoundPlay(SOUND_1FB);
                    else
                        SoundPlay(SOUND_1FE);
                }
                else
                {
                    SoundPlay(SOUND_1FB);
                    pOam->unk_9 = 1;
                }
            }
        }
    }
    else if (pOam->unk_9 == 1)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->unk_9 = 100;
        }

        if (FILE_SELECT_DATA.timer == 11)
            pOam->unk_9 = 100;
    }
    else
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
            pOam->animationDurationCounter = 0;

        if (FILE_SELECT_DATA.subroutine == 3)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectCursorOam1;
            pOam->unk_9 = 0;
        }
    }
}

/**
 * @brief 9fc90 | 14c | Processes the delete arrow oam
 *
 * @param pOam File select oam pointer
 */
void FileSelectProcessDeleteArrow(struct FileSelectOam* pOam)
{
    u8 moved;
    u8 sound;

    sound = 0;
    moved = FALSE;

    if (pOam->unk_9 == 0)
    {
        pOam->isDrawn = TRUE;

        if (gChangedInput & KEY_UP)
        {
            if (FILE_SELECT_DATA.unk_F != 0)
            {
                FILE_SELECT_DATA.unk_F--;
                moved = TRUE;
            }

            if (FILE_SELECT_DATA.selectedFile == FILE_SELECT_DATA.unk_F)
            {
                if (FILE_SELECT_DATA.selectedFile == 0)
                {
                    FILE_SELECT_DATA.unk_F++;
                    moved = FALSE;
                }
                else
                {
                    FILE_SELECT_DATA.unk_F--;
                    moved = TRUE;
                }
            }
        }
        else if (gChangedInput & KEY_DOWN)
        {
            if (FILE_SELECT_DATA.unk_F < 2)
            {
                FILE_SELECT_DATA.unk_F++;
                moved = TRUE;
            }

            if (FILE_SELECT_DATA.selectedFile == FILE_SELECT_DATA.unk_F)
            {
                if (FILE_SELECT_DATA.selectedFile == 2)
                {
                    FILE_SELECT_DATA.unk_F--;
                    moved = FALSE;
                }
                else
                {
                    FILE_SELECT_DATA.unk_F++;
                    moved = TRUE;
                }
            }
        }

        pOam->pOam = sFileSelectDeleteArrowOam[FILE_SELECT_DATA.selectedFile][FILE_SELECT_DATA.unk_F];

        if (gChangedInput & KEY_B)
        {
            pOam->unk_9 = 100;
        }
        else if (gChangedInput & (KEY_A | KEY_START))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->unk_9 = 1;

            if (gSaveFilesInfo[FILE_SELECT_DATA.unk_F].unk_10 == TRUE || gSaveFilesInfo[FILE_SELECT_DATA.unk_F].unk_11 == TRUE ||
                gSaveFilesInfo[FILE_SELECT_DATA.unk_F].exists == TRUE)
                sound = 1;
            else
                sound = 2;
        }
    }
    else if (pOam->unk_9 == 1)
    {
        if (FILE_SELECT_DATA.timer == 11)
            pOam->unk_9 = 100;
    }
    else if (FILE_SELECT_DATA.subroutine == 17)
    {
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->unk_9 = 0;
    }

    if (moved)
        SoundPlay(SOUND_1F9);

    if (sound == 1)
        SoundPlay(SOUND_1FB);
    else if (sound == 2)
        SoundPlay(SOUND_207);
}

/**
 * @brief 9fddc | 124 | To document
 *
 * @param pOam File select oam pointer
 */
void unk_9fddc(struct FileSelectOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->unk_9 == 0)
    {
        if (FILE_SELECT_DATA.unk_10 == 0)
        {
            if (gChangedInput & KEY_RIGHT)
            {
                FILE_SELECT_DATA.unk_10 = 1;
                pOam->xPosition = sFileSelectChoiceCursorXPositions_73dbb0[gLanguage][1];
                SoundPlay(SOUND_1FA);
            }
        }
        else if (FILE_SELECT_DATA.unk_10 == 1)
        {
            if (gChangedInput & KEY_LEFT)
            {
                FILE_SELECT_DATA.unk_10 = 0;
                pOam->xPosition = sFileSelectChoiceCursorXPositions_73dbb0[gLanguage][0];
                SoundPlay(SOUND_1FA);
            }
        }

        if (gChangedInput & KEY_B)
        {
            pOam->unk_9 = 100;
        }
        else if (gChangedInput & (KEY_A | KEY_START))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;

            if (FILE_SELECT_DATA.unk_10 == 0)
            {
                SoundPlay(SOUND_207);
                pOam->pOam = sFileSelectCursorOam2;
                pOam->unk_9 = 1;
            }
            else
            {
                SoundPlay(SOUND_1FB);
                pOam->pOam = sFileSelectCursorOam2;
                pOam->unk_9 = 1;
            }
        }
    }
    else if (pOam->unk_9 == 1)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
            pOam->animationDurationCounter = 0;

        if (FILE_SELECT_DATA.timer == 11)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->unk_9 = 100;
        }
    }
    else
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief 9ff00 | 124 | To document
 *
 * @param pOam File select oam pointer
 */
void unk_9ff00(struct FileSelectOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->unk_9 == 0)
    {
        if (FILE_SELECT_DATA.unk_10 == 0)
        {
            if (gChangedInput & KEY_RIGHT)
            {
                FILE_SELECT_DATA.unk_10 = 1;
                pOam->xPosition = sFileSelectChoiceCursorXPositions_73dbbe[gLanguage][1];
                SoundPlay(SOUND_1FA);
            }
        }
        else if (FILE_SELECT_DATA.unk_10 == 1)
        {
            if (gChangedInput & KEY_LEFT)
            {
                FILE_SELECT_DATA.unk_10 = 0;
                pOam->xPosition = sFileSelectChoiceCursorXPositions_73dbbe[gLanguage][0];
                SoundPlay(SOUND_1FA);
            }
        }

        if (gChangedInput & KEY_B)
        {
            pOam->unk_9 = 100;
        }
        else if (gChangedInput & (KEY_A | KEY_START))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;

            if (FILE_SELECT_DATA.unk_10 == 0)
            {
                SoundPlay(SOUND_208);
                pOam->pOam = sFileSelectCursorOam2;
                pOam->unk_9 = 1;
            }
            else
            {
                SoundPlay(SOUND_1FB);
                pOam->pOam = sFileSelectCursorOam2;
                pOam->unk_9 = 1;
            }
        }
    }
    else if (pOam->unk_9 == 1)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
            pOam->animationDurationCounter = 0;

        if (FILE_SELECT_DATA.timer == 11)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->unk_9 = 100;
        }
    }
    else
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief a0024 | c0 | Processes the audio logos oam
 *
 * @param pOam File select oam pointer
 */
void FileSelectProcessAudioLogos(struct FileSelectOam* pOam)
{
    if (FILE_SELECT_DATA.selectedFile == 3)
    {
        if (pOam->unk_9 == 0)
        {
            pOam->pOam = sFileSelectAudioLogosOam1;
            if (gChangedInput & KEY_RIGHT)
            {
                pOam->unk_9 = 1;
                pOam->pOam = sFileSelectAudioLogosOam2;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                DoSoundAction(0x2000000);
                SoundPlay(SOUND_206);
            }
        }
        else if (pOam->unk_9 == 1)
        {
            pOam->pOam = sFileSelectAudioLogosOam2;
            if (gChangedInput & KEY_LEFT)
            {
                pOam->unk_9 = 0;
                pOam->pOam = sFileSelectAudioLogosOam1;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                DoSoundAction(0x1000000);
                SoundPlay(SOUND_1FA);
            }
        }
    }
    else
    {
        if (pOam->unk_9 == 0)
        {
            pOam->pOam = sFileSelectAudioLogosOam3;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
        else if (pOam->unk_9 == 1)
        {
            pOam->pOam = sFileSelectAudioLogosOam4;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
    }
}

/**
 * @brief a00e4 | 60 | Processes the audio select oam
 *
 * @param pOam File select oam pointer
 */
void FileSelectProcessAudioSelect(struct FileSelectOam* pOam)
{
    if (FILE_SELECT_DATA.selectedFile == 3)
    {
        pOam->isDrawn = TRUE;

        if (pOam->unk_9 == 0)
        {
            if (gChangedInput & KEY_RIGHT)
            {
                pOam->unk_9 = 1;
                pOam->xPosition = 170;
            }
        }
        else if (pOam->unk_9 == 1)
        {
            if (gChangedInput & KEY_LEFT)
            {
                pOam->unk_9 = 0;
                pOam->xPosition = 102;
            }
        }
    }
    else
    {
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->isDrawn = FALSE;
    }
}

/**
 * @brief a0144 | 28 | Processes the file overlay oam
 *
 * @param pOam File select oam pointer
 */
void FileSelectProcessFileOverlay(struct FileSelectOam* pOam)
{
    if (FILE_SELECT_DATA.subroutine == 0)
        pOam->pOam = sFileSelectFileOverlayOam[FILE_SELECT_DATA.selectedFile];
}

/**
 * @brief a016c | 60 | To document
 *
 * @param pOam File select oam pointer
 */
void unk_a016c(struct FileSelectOam* pOam)
{
    if (FILE_SELECT_DATA.subroutine != 0)
        return;

    pOam->pOam = sFileSelectOam_7408e0;

    if (FILE_SELECT_DATA.selectedFile <= 2)
    {
        pOam->isDrawn = TRUE;

        if (FILE_SELECT_DATA.selectedFile == 0)
            pOam->yPosition = 0x31;
        else if (FILE_SELECT_DATA.selectedFile == 1)
            pOam->yPosition = 0x41;
        else if (FILE_SELECT_DATA.selectedFile == 2)
            pOam->yPosition = 0x51;

        if (gChangedInput & (KEY_A | KEY_START))
            pOam->pOam = sFileSelectOam_7408d0;
    }
    else
    {
        pOam->isDrawn = FALSE;
    }
}

/**
 * @brief a01cc | 4 | Empty
 *
 * @param pOam File select oam pointer
 */
void unk_a01cc(struct FileSelectOam* pOam)
{
    return;
}

/**
 * @brief a01d0 | 9c | Processes the file action panel oam
 *
 * @param pOam File select oam pointer
 */
void FileSelectProcessFileActionPanel(struct FileSelectOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->unk_9 == 0)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectFileActionPanelOam2;
            pOam->unk_9 = 1;
        }
    }
    else if (pOam->unk_9 == 1)
    {
        switch (FILE_SELECT_DATA.subroutine)
        {
            case 4:
            case 21:
            case 26:
            case 33:
                SoundPlay(SOUND_1FD);
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sFileSelectFileActionPanelOam3;
                pOam->unk_9 = 2;
                break;
        }
    }
    else if (pOam->unk_9 == 2)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->type = FILE_SELECT_OAM_TYPE_NONE;
            pOam->isDrawn = FALSE;
        }
    }
}

/**
 * @brief a026c | 98 | Processes the copy file panel oam
 *
 * @param pOam File select oam pointer
 */
void FileSelectProcessCopyFilePanel(struct FileSelectOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->unk_9 == 0)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectFilePanelOam2;
            pOam->unk_9 = 1;
        }
    }
    else if (pOam->unk_9 == 1)
    {
        switch (FILE_SELECT_DATA.subroutine)
        {
            case 18:
            case 21:
            case 26:
                SoundPlay(SOUND_1FD);
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sFileSelectFilePanelOam3;
                pOam->unk_9 = 2;
                break;
        }
    }
    else if (pOam->unk_9 == 2)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->type = FILE_SELECT_OAM_TYPE_NONE;
            pOam->isDrawn = FALSE;
        }
    }
}

/**
 * @brief a0304 | 98 | Processes the erase file panel oam
 *
 * @param pOam File select oam pointer
 */
void FileSelectProcessEraseFilePanel(struct FileSelectOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->unk_9 == 0)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectFilePanelOam2;
            pOam->unk_9 = 1;
        }
    }
    else if (pOam->unk_9 == 1)
    {
        switch (FILE_SELECT_DATA.subroutine)
        {
            case 29:
            case 31:
            case 33:
                SoundPlay(SOUND_1FD);
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sFileSelectFilePanelOam3;
                pOam->unk_9 = 2;
                break;
        }
    }
    else if (pOam->unk_9 == 2)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->type = FILE_SELECT_OAM_TYPE_NONE;
            pOam->isDrawn = FALSE;
        }
    }
}

/**
 * @brief a039c | 88 | To document
 *
 * @param pOam File select oam pointer
 */
void unk_a039c(struct FileSelectOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->unk_9 == 0)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectFilePanelOam2;
            pOam->unk_9 = 1;
        }
    }
    else if (pOam->unk_9 == 1)
    {
        if (FILE_SELECT_DATA.subroutine == 11)
        {
            SoundPlay(SOUND_1FD);
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectFilePanelOam3;
            pOam->unk_9 = 2;
        }
    }
    else if (pOam->unk_9 == 2)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->type = FILE_SELECT_OAM_TYPE_NONE;
            pOam->isDrawn = FALSE;
        }
    }
}

/**
 * @brief a0424 | f4 | To document
 *
 * @param pOam File select oam pointer
 */
void unk_a0424(struct FileSelectOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->unk_9 == 0)
    {
        if (FILE_SELECT_DATA.unk_10 == 0)
        {
            if (gChangedInput & KEY_DOWN)
            {
                FILE_SELECT_DATA.unk_10 = 1;
                pOam->yPosition = 0x79;
                SoundPlay(SOUND_1FA);
            }
        }
        else if (FILE_SELECT_DATA.unk_10 == 1)
        {
            if (gChangedInput & KEY_UP)
            {
                FILE_SELECT_DATA.unk_10 = 0;
                pOam->yPosition = 0x69;
                SoundPlay(SOUND_1FA);
            }
        }

        if (gChangedInput & KEY_B)
        {
            pOam->unk_9 = 100;
        }
        else if (gChangedInput & (KEY_A | KEY_START))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            SoundPlay(SOUND_1FE);

            if (FILE_SELECT_DATA.unk_10 == 0)
            {
                pOam->pOam = sFileSelectCursorOam2;
                pOam->unk_9 = 100;
            }
            else
            {
                pOam->pOam = sFileSelectCursorOam2;
                pOam->unk_9 = 100;
            }
        }
    }
    else if (pOam->unk_9 == 1)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
            pOam->animationDurationCounter = 0;

        if (FILE_SELECT_DATA.timer == 11)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->unk_9 = 100;
        }
    }
    else
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame->timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief a0518 | 4 | Empty
 *
 * @param pOam File select oam pointer
 */
void unk_a0518(struct FileSelectOam* pOam)
{
    return;
}

/**
 * @brief a051c | 520 | Draws the info of a file
 *
 * @param file File
 */
void FileSelectDrawFileInfo(u8 file)
{
    s32 timeDigits[4];
    s32 energyDigits[4];
    s32 tankDigits[4];
    u32 base;
    u32 addr;
    struct SaveFileInfo* pInfo;
    u32* dst;
    const u16* pText;
    u32 width;
    u8 i;

    pInfo = &gSaveFilesInfo[file];

    if (file == 0)
    {
        dst = (u32*)(VRAM_BASE + 0x88C0);
        base = (u32)dst;
    }
    else if (file == 1)
    {
        dst = (u32*)(VRAM_BASE + 0x90C0);
        base = (u32)dst;
    }
    else
    {
        dst = (u32*)(VRAM_BASE + 0x98C0);
        base = (u32)dst;
    }

    FILE_SELECT_DATA.textTile = 0;
    FILE_SELECT_DATA.textPixelOffset = 0;

    if (pInfo->exists == FALSE)
    {
        if (gSaveFilesInfo[file].unk_10 == TRUE || gSaveFilesInfo[file].unk_11 == TRUE)
        {
            FILE_SELECT_DATA.corruptedFileInfo.currentEnergy = 99;
            pInfo = &FILE_SELECT_DATA.corruptedFileInfo;
        }
        else
        {
            FileSelectDestroyOamOfType(file + 14);
            FileSelectDestroyOamOfType(file + 20);

            DMA3_FILL_32(0, dst, 0x300);
            DMA3_FILL_32(0, (u8*)dst + 0x400, 0x300);

            pText = sFileSelectEmptyFileTexts[gLanguage][0];
            FILE_SELECT_DATA.textTile = 8;

            for (; *pText != 0xFF00; pText++)
            {
                if (*pText == 0x5A)
                    width = TextGetCharacterWidth(*pText) + 2;
                else if (*pText == 0x40)
                    width = 8 - FILE_SELECT_DATA.textPixelOffset;
                else
                    width = 8;

                dst = (u32*)(FILE_SELECT_DATA.textTile * 32 + base);
                TextDrawCharacter(*pText, dst, width, FILE_SELECT_DATA.textPixelOffset, 0);

                FILE_SELECT_DATA.textPixelOffset += width;
                while (FILE_SELECT_DATA.textPixelOffset >= 8)
                {
                    FILE_SELECT_DATA.textPixelOffset -= 8;
                    FILE_SELECT_DATA.textTile++;
                }
            }
            return;
        }
    }

    if (gLanguage == LANGUAGE_JAPANESE)
        width = 0;

    energyDigits[0] = DivArmDiv(1000, pInfo->currentEnergy);
    tankDigits[0] = energyDigits[1] = DivArmDiv(100, pInfo->currentEnergy);
    energyDigits[1] = DivArmMod(10, energyDigits[1]);
    tankDigits[1] = energyDigits[1];
    energyDigits[2] = DivArmDiv(10, pInfo->currentEnergy);
    energyDigits[2] = DivArmMod(10, energyDigits[2]);
    energyDigits[3] = pInfo->currentEnergy;
    energyDigits[3] = DivArmMod(10, energyDigits[3]);

    for (i = 2; i < 4; i++)
    {
        addr = (u32)&sCharactersGfx[(energyDigits[i] + 0x50) * 32];
        DMA3_COPY_32(addr, dst, 8);
        DMA3_COPY_32(addr + 0x400, (u8*)dst + 0x400, 8);
        dst += 8;
    }

    DMA3_FILL_32(0, dst, 0x200);
    DMA3_FILL_32(0, (u8*)dst + 0x400, 0x200);

    tankDigits[1] = DivArmMod(2, tankDigits[1]);
    tankDigits[2] = DivArmDiv(100, pInfo->maxEnergy);
    tankDigits[3] = DivArmMod(10, tankDigits[2]);
    tankDigits[3] = DivArmMod(2, tankDigits[3]);

    // The in game time is drawn 0xC0 bytes after the end of the energy digits
    addr = (u32)dst;
    dst = (u32*)((u8*)dst + 0x400);

    for (i = 0; i < tankDigits[0] - tankDigits[1]; i += 2)
    {
        if (i == 10)
            dst -= 0x4A0 / 4;
        DMA3_COPY_32(sFileSelectEnergyTanksFullGfx, dst, 8);
        dst += 8;
    }

    if (tankDigits[1] == 1)
    {
        if (i == 10)
            dst -= 0x4A0 / 4;

        if (tankDigits[2] == tankDigits[0])
        {
            DMA3_COPY_32(sFileSelectEnergyTankOneFullGfx, dst, 8);
        }
        else
        {
            DMA3_COPY_32(sFileSelectEnergyTankOneFullOneEmptyGfx, dst, 8);
        }

        i += 2;
        dst += 8;
    }

    for (; i < tankDigits[2] - tankDigits[3]; i += 2)
    {
        if (i == 10)
            dst -= 0x4A0 / 4;
        DMA3_COPY_32(sFileSelectEnergyTanksEmptyGfx, dst, 8);
        dst += 8;
    }

    if (tankDigits[3] == 1 && i < tankDigits[2])
    {
        if (i == 10)
            dst -= 0x4A0 / 4;
        DMA3_COPY_32(sFileSelectEnergyTankOneEmptyGfx, dst, 8);
    }

    dst = (u32*)(addr + 0xC0);

    timeDigits[0] = DivArmDiv(10, pInfo->igtHours);
    timeDigits[0] = DivArmMod(10, timeDigits[0]);
    timeDigits[1] = pInfo->igtHours;
    timeDigits[1] = DivArmMod(10, timeDigits[1]);

    for (i = 0; i < 2; i++)
    {
        addr = (u32)&sCharactersGfx[(timeDigits[i] + 0x50) * 32];
        DMA3_COPY_32(addr, dst, 8);
        DMA3_COPY_32(addr + 0x400, (u8*)dst + 0x400, 8);
        dst += 8;
    }

    FILE_SELECT_DATA.textTile = 10;
    dst = (u32*)(FILE_SELECT_DATA.textTile * 32 + base);
    width = TextGetCharacterWidth(0x5A) + 3;
    TextDrawCharacter(0x5A, dst, width, FILE_SELECT_DATA.textPixelOffset, 0);

    FILE_SELECT_DATA.textPixelOffset += width;
    while (FILE_SELECT_DATA.textPixelOffset >= 8)
    {
        FILE_SELECT_DATA.textPixelOffset -= 8;
        FILE_SELECT_DATA.textTile++;
    }

    timeDigits[0] = DivArmDiv(10, pInfo->igtMinutes);
    timeDigits[0] = DivArmMod(10, timeDigits[0]);
    timeDigits[1] = pInfo->igtMinutes;
    timeDigits[1] = DivArmMod(10, timeDigits[1]);

    for (i = 0; i < 2; i++)
    {
        dst = (u32*)(FILE_SELECT_DATA.textTile * 32 + base);
        TextDrawCharacter(timeDigits[i] + 0x50, dst, 8, FILE_SELECT_DATA.textPixelOffset, 0);

        FILE_SELECT_DATA.textPixelOffset += 8;
        while (FILE_SELECT_DATA.textPixelOffset >= 8)
        {
            FILE_SELECT_DATA.textPixelOffset -= 8;
            FILE_SELECT_DATA.textTile++;
        }
    }

    FileSelectDestroyOamOfType(file + 14);
    FileSelectSetUpAreaNameOam(file + 14, 0x9D, file * 16 + 0x20, pInfo->currentArea);
    FileSelectDestroyOamOfType(file + 20);

    if (gSaveFilesInfo[file].unk_10 == TRUE)
        FileSelectSetupOam(file + 20, 0xDC, file * 16 + 0x28, 1);
}

/**
 * @brief a0a3c | 148 | Draws a text on the file select screen
 *
 * @param text Text
 */
void FileSelectDrawText(u8 text)
{
    const u16* pOffsets;
    u32* dst;
    u32 width;
    u32 gfx;
    u32 color;

    FILE_SELECT_DATA.textLine = 0;
    FILE_SELECT_DATA.textTile = 0;
    FILE_SELECT_DATA.textPixelOffset = 0;

    if (FILE_SELECT_DATA.unk_8 == 24)
        pOffsets = sFileSelectTextTileOffsets[gLanguage][5];
    else
        pOffsets = sFileSelectTextTileOffsets[gLanguage][FILE_SELECT_DATA.unk_8];

    if (text == 1)
    {
        gfx = (u32)VRAM_BASE + 0x8000;
        color = 6;
    }
    else if (text == 2)
    {
        gfx = (u32)VRAM_BASE + 0xB000;
        color = 0;
    }
    else if (text == 3)
    {
        gfx = (u32)VRAM_BASE + 0xC800;
        color = 0;
    }

    for (; *FILE_SELECT_DATA.pText != 0xFF00; FILE_SELECT_DATA.pText++)
    {
        if (*FILE_SELECT_DATA.pText == 0xFE00)
        {
            FILE_SELECT_DATA.textTile = 0;
            FILE_SELECT_DATA.textLine += 2;
            FILE_SELECT_DATA.textPixelOffset = 0;
            pOffsets++;
            color = 0;
            continue;
        }

        dst = (u32*)(FILE_SELECT_DATA.textTile * 32 + FILE_SELECT_DATA.textLine * 0x400 + gfx + *pOffsets * 32);
        width = TextGetCharacterWidth(*FILE_SELECT_DATA.pText);
        TextDrawCharacter(*FILE_SELECT_DATA.pText, dst, width, FILE_SELECT_DATA.textPixelOffset, color);

        FILE_SELECT_DATA.textPixelOffset += width;
        while (FILE_SELECT_DATA.textPixelOffset >= 8)
        {
            FILE_SELECT_DATA.textPixelOffset -= 8;
            FILE_SELECT_DATA.textTile++;
        }
    }
}

/**
 * @brief a0b84 | 280 | Handles the corrupted files on the file select screen
 *
 * @return u32 bool, ended
 */
u32 FileSelectProcessCorruptedFile(void)
{
    u32 ended;

    ended = FALSE;

    FileSelectProcessOam();

    switch (FILE_SELECT_DATA.corruptedFileStage)
    {
        case 0:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDrawText(1);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                if (gSaveFilesInfo[0].corruptionFlag == 0)
                    FileSelectDrawFileInfo(0);
                else
                    FileSelectDrawFileCorruptedText(0);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                if (gSaveFilesInfo[1].corruptionFlag == 0)
                    FileSelectDrawFileInfo(1);
                else
                    FileSelectDrawFileCorruptedText(1);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                if (gSaveFilesInfo[2].corruptionFlag == 0)
                    FileSelectDrawFileInfo(2);
                else
                    FileSelectDrawFileCorruptedText(2);

                FILE_SELECT_DATA.timer = 0;
                gWrittenToBldy = 14;
                FILE_SELECT_DATA.corruptedFileStage = 1;
            }
            break;

        case 1:
            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                FILE_SELECT_DATA.corruptedFileStage = 2;
            break;

        case 2:
            for (; FILE_SELECT_DATA.corruptedFile < 3; FILE_SELECT_DATA.corruptedFile++)
            {
                if (gSaveFilesInfo[FILE_SELECT_DATA.corruptedFile].corruptionFlag != 0)
                {
                    FILE_SELECT_DATA.corruptedFileStage = 3;
                    break;
                }
            }

            if (FILE_SELECT_DATA.corruptedFile == 3)
                FILE_SELECT_DATA.corruptedFileStage = 7;
            break;

        case 3:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 10)
            {
                FILE_SELECT_DATA.corruptedFileStage = 4;
                FILE_SELECT_DATA.timer = 0;
                FileSelectSetupOam(17, 0x7A, 0x44, 0);
            }
            break;

        case 4:
            if (gSaveFilesInfo[FILE_SELECT_DATA.corruptedFile].corruptionFlag == 1)
                FILE_SELECT_DATA.unk_8 = FILE_SELECT_DATA.corruptedFile + 5;
            else
                FILE_SELECT_DATA.unk_8 = FILE_SELECT_DATA.corruptedFile + 8;

            FILE_SELECT_DATA.pText = sFileSelectTexts[gLanguage][FILE_SELECT_DATA.unk_8];
            FileSelectDrawCorruptionText(2);
            FileSelectSetupOam(10, 0x78, 0x64, 0);
            FILE_SELECT_DATA.dispcntAction = 3;
            FILE_SELECT_DATA.corruptedFileStage = 5;
            break;

        case 5:
            if (gChangedInput & (KEY_A | KEY_B))
            {
                FileSelectDestroyOamOfType(10);
                FileSelectDestroyOamOfType(17);
                SoundPlay(SOUND_1FB);
                FILE_SELECT_DATA.dispcntAction = 4;
                Sram_SetCurrentFile(FILE_SELECT_DATA.corruptedFile);
                FileSelectDrawFileInfo(FILE_SELECT_DATA.corruptedFile);
                FILE_SELECT_DATA.corruptedFileStage = 6;
            }
            break;

        case 6:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xB000, 0x1800);
            }
            else if (FILE_SELECT_DATA.timer == 10)
            {
                FILE_SELECT_DATA.corruptedFileStage = 2;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 7:
            FILE_SELECT_DATA.timer = 0;
            ended = TRUE;
            break;
    }

    FileSelectDrawAllOam();

    return ended;
}

/**
 * @brief a0e04 | 114 | Draws the "file corrupted" text of a file
 *
 * @param file File
 */
void FileSelectDrawFileCorruptedText(u8 file)
{
    u32 base;
    u32* dst;
    const u16* pText;
    u32 width;

    if (file == 0)
    {
        dst = (u32*)(VRAM_BASE + 0x88C0);
        base = (u32)dst;
    }
    else if (file == 1)
    {
        dst = (u32*)(VRAM_BASE + 0x90C0);
        base = (u32)dst;
    }
    else
    {
        dst = (u32*)(VRAM_BASE + 0x98C0);
        base = (u32)dst;
    }

    FILE_SELECT_DATA.textTile = 0;
    FILE_SELECT_DATA.textPixelOffset = 0;

    DMA3_FILL_32(0, dst, 0x300);
    DMA3_FILL_32(0, (u8*)dst + 0x400, 0x300);

    pText = sFileSelectEmptyFileTexts[gLanguage][0];
    FILE_SELECT_DATA.textTile = 8;

    for (; *pText != 0xFF00; pText++)
    {
        if (*pText == 0x5A)
            width = TextGetCharacterWidth(*pText) + 3;
        else if (*pText == 0x40)
            width = 8 - FILE_SELECT_DATA.textPixelOffset;
        else
            width = 8;

        dst = (u32*)(FILE_SELECT_DATA.textTile * 32 + base);
        TextDrawCharacter(*pText, dst, width, FILE_SELECT_DATA.textPixelOffset, 0);

        FILE_SELECT_DATA.textPixelOffset += width;
        while (FILE_SELECT_DATA.textPixelOffset >= 8)
        {
            FILE_SELECT_DATA.textPixelOffset -= 8;
            FILE_SELECT_DATA.textTile++;
        }
    }
}

/**
 * @brief a0f18 | f0 | Draws the corruption text
 *
 * @param text Text
 */
void FileSelectDrawCorruptionText(u8 text)
{
    u32* dst;
    u32 width;
    u32 gfx;

    FILE_SELECT_DATA.textLine = 0;
    FILE_SELECT_DATA.textTile = 0;
    FILE_SELECT_DATA.textPixelOffset = 0;

    if (text == 1)
        gfx = (u32)VRAM_BASE + 0x8000;
    else if (text == 2)
        gfx = (u32)VRAM_BASE + 0xB000;
    else if (text == 3)
        gfx = (u32)VRAM_BASE + 0xC800;

    for (; *FILE_SELECT_DATA.pText != 0xFF00; FILE_SELECT_DATA.pText++)
    {
        if (*FILE_SELECT_DATA.pText == 0xFE00)
        {
            FILE_SELECT_DATA.textTile = 0;
            FILE_SELECT_DATA.textLine += 2;
            FILE_SELECT_DATA.textPixelOffset = 0;
            continue;
        }

        dst = (u32*)(FILE_SELECT_DATA.textTile * 32 + FILE_SELECT_DATA.textLine * 0x400 + gfx);
        width = TextGetCharacterWidth(*FILE_SELECT_DATA.pText);
        TextDrawCharacter(*FILE_SELECT_DATA.pText, dst, width, FILE_SELECT_DATA.textPixelOffset, 0);

        FILE_SELECT_DATA.textPixelOffset += width;
        while (FILE_SELECT_DATA.textPixelOffset >= 8)
        {
            FILE_SELECT_DATA.textPixelOffset -= 8;
            FILE_SELECT_DATA.textTile++;
        }
    }
}

/**
 * @brief a1008 | 34 | Destroys the first file select oam of a type
 *
 * @param type Type
 */
void FileSelectDestroyOamOfType(u8 type)
{
    u8 i;

    for (i = 0; i < FILE_SELECT_OAM_COUNT; i++)
    {
        if (FILE_SELECT_DATA.oam[i].type == type)
        {
            FILE_SELECT_DATA.oam[i].type = FILE_SELECT_OAM_TYPE_NONE;
            FILE_SELECT_DATA.oam[i].isDrawn = FALSE;
            break;
        }
    }
}

/**
 * @brief a103c | 190 | Sets up an area name oam
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param area Area
 */
void FileSelectSetUpAreaNameOam(u8 type, s16 xPosition, s16 yPosition, s16 area)
{
    u8 slot;

    slot = FileSelectSetupOam(type, xPosition, yPosition, 1);

    switch (area)
    {
        case 1:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectAreaNameOam[gLanguage][1];
            break;

        case 2:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectAreaNameOam[gLanguage][2];
            break;

        case 3:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectAreaNameOam[gLanguage][3];
            break;

        case 4:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectAreaNameOam[gLanguage][4];
            break;

        case 5:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectAreaNameOam[gLanguage][5];
            break;

        case 6:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectAreaNameOam[gLanguage][6];
            break;

        case 0:
        default:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectAreaNameOam[gLanguage][0];
            break;
    }
}

/**
 * @brief a11cc | 3c | Calls the handler of every file select oam
 *
 */
void FileSelectProcessOam(void)
{
    u8 i;

    for (i = 0; i < FILE_SELECT_OAM_COUNT; i++)
    {
        if (FILE_SELECT_DATA.oam[i].type != FILE_SELECT_OAM_TYPE_NONE)
            FILE_SELECT_DATA.oam[i].pHandler(&FILE_SELECT_DATA.oam[i]);
    }
}

/**
 * @brief a1208 | 40 | Draws every file select oam
 *
 */
void FileSelectDrawAllOam(void)
{
    u8 i;

    for (i = 0; i < FILE_SELECT_OAM_COUNT; i++)
    {
        if (FILE_SELECT_DATA.oam[i].isDrawn)
            FileSelectDrawOam(&FILE_SELECT_DATA.oam[i]);
    }

    ResetFreeOam();
    gNextOamSlot = 0;
}

/**
 * @brief a1248 | 188 | Draws a file select oam
 *
 * @param pOam File select oam pointer
 */
void FileSelectDrawOam(struct FileSelectOam* pOam)
{
    u16* dst;
    const u16* src;
    const struct FrameData* pFrame;
    s32 i;
    s32 partCount;
    s32 slot;
    u16 part1;
    u16 part2;
    u32 x;
    u32 y;
    s32 offset;

    dst = (u16*)&gOamData[gNextOamSlot];
    pFrame = &pOam->pOam[pOam->currentAnimationFrame];

    if (pFrame->timer == pOam->animationDurationCounter)
    {
        pOam->currentAnimationFrame++;
        pOam->animationDurationCounter = 0;
        pFrame++;
    }

    if (pFrame->timer == 0)
    {
        pFrame -= pOam->currentAnimationFrame;
        pOam->currentAnimationFrame = 0;
    }

    src = pFrame->pFrame;
    partCount = *src++;

    for (i = 0; i < partCount; i++)
    {
        part1 = *src++;
        part2 = *src++;

        *dst++ = part1;
        *dst++ = part2;
        *dst++ = *src++;

        slot = gNextOamSlot + i;

        if (pOam->xFlip == TRUE)
        {
            gOamData[slot].split.xFlip ^= TRUE;
            offset = sFileSelectOamXFlipOffsets[gOamData[slot].split.shape][gOamData[slot].split.size] * 8 + part2;
            x = pOam->xPosition - offset;
            x &= 0x1FF;
            y = (part1 + pOam->yPosition) & 0xFF;
        }
        else
        {
            y = (part1 + pOam->yPosition) & 0xFF;
            x = (part2 + pOam->xPosition) & 0x1FF;
        }

        gOamData[slot].split.y = y;
        gOamData[slot].split.x = x;
        gOamData[slot].split.priority = pOam->priority;
        gOamData[slot].split.paletteNum += pOam->paletteRow;
        gOamData[slot].split.tileNum += pOam->tileOffset;
        gOamData[slot].split.objMode = pOam->objMode;

        dst++;
    }

    gNextOamSlot += partCount;
    pOam->animationDurationCounter++;
}

/**
 * @brief a13d0 | 10 | Sets the language
 *
 * @param unk Unused
 * @return u32 bool, ended
 */
u32 SetLanguage(u8 unk)
{
    gLanguage = LANGUAGE_ENGLISH;
    return TRUE;
}

/**
 * @brief a13e0 | 98 | To document
 *
 */
void unk_a13e0(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    WRITE_16(REG_DISPCNT, 0);

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    WRITE_16(REG_BG3CNT, 0);
    WRITE_16(REG_BG2CNT, 0);
    WRITE_16(REG_BG1CNT, 0);
    WRITE_16(REG_BG0CNT, 0);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_DISPCNT, 0);

    CallbackSetVBlank(unk_a1478);
}

/**
 * @brief a1478 | 4 | Empty v-blank
 *
 */
void unk_a1478(void)
{
    return;
}

/**
 * @brief a147c | 4 | To document
 *
 * @return u32 TRUE
 */
u32 unk_a147c(void)
{
    return TRUE;
}
