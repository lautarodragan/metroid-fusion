#include "menus/file_select.h"
#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "oam.h"
#include "text.h"
#include "init_helpers.h"
#include "audio_wrappers.h"
#include "callbacks.h"

#include "data/menus/file_select_data.h"

#include "constants/audio.h"
#include "constants/game_state.h"
#include "constants/menus/file_select.h"

#include "structs/save_file.h"

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
        pOffsets = sFileSelectUnk_79e928[gLanguage][5];
    else
        pOffsets = sFileSelectUnk_79e928[gLanguage][FILE_SELECT_DATA.unk_8];

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

            FILE_SELECT_DATA.pText = sFileSelectUnk_79ec68[gLanguage][FILE_SELECT_DATA.unk_8];
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

    pText = sFileSelectUnk_79ec84[gLanguage][0];
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
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectUnk_79e944[gLanguage][1];
            break;

        case 2:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectUnk_79e944[gLanguage][2];
            break;

        case 3:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectUnk_79e944[gLanguage][3];
            break;

        case 4:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectUnk_79e944[gLanguage][4];
            break;

        case 5:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectUnk_79e944[gLanguage][5];
            break;

        case 6:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectUnk_79e944[gLanguage][6];
            break;

        case 0:
        default:
            FILE_SELECT_DATA.oam[slot].pOam = sFileSelectUnk_79e944[gLanguage][0];
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
            offset = sFileSelectUnk_73dba4[gOamData[slot].split.shape][gOamData[slot].split.size] * 8 + part2;
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
