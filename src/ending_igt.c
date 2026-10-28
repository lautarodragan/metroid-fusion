#include "globals.h"
#include "macros.h"

#include "data/ending_data.h"

#include "structs/ending.h"

void EndingDrawIgtAndCompletionPercentage(void);
void EndingImageUpdateLettersSpawnDelay(u32 slot);

/**
 * @brief a1480 | 1a8 | Draws the in game timer and the completion percentage
 *
 */
void EndingDrawIgtAndCompletionPercentage(void)
{
    s32 digit1;
    s32 digit2;
    s32 digit3;
    s32 digit4;
    s32 offset;

    // Hours
    digit1 = 0;
    digit2 = gInGameTimer.hours;
    while (digit2 > 9)
    {
        digit2 -= 10;
        digit1++;
    }

    // Minutes
    digit3 = 0;
    digit4 = gInGameTimer.minutes;
    while (digit4 > 9)
    {
        digit4 -= 10;
        digit3++;
    }

    if (digit1 != 0)
    {
        offset = digit1 * 64;
        DMA3_COPY_16(&sEndingUnk_74e650[offset], VRAM_OBJ + 0x0, 0x20);
        DMA3_COPY_16(&sEndingUnk_74e8d0[offset], VRAM_OBJ + 0x400, 0x20);
    }

    offset = digit2 * 64;
    DMA3_COPY_16(&sEndingUnk_74e650[offset], VRAM_OBJ + 0x40, 0x20);
    DMA3_COPY_16(&sEndingUnk_74e8d0[offset], VRAM_OBJ + 0x440, 0x20);

    offset = digit3 * 64;
    DMA3_COPY_16(&sEndingUnk_74e650[offset], VRAM_OBJ + 0xA0, 0x20);
    DMA3_COPY_16(&sEndingUnk_74e8d0[offset], VRAM_OBJ + 0x4A0, 0x20);

    offset = digit4 * 64;
    DMA3_COPY_16(&sEndingUnk_74e650[offset], VRAM_OBJ + 0xE0, 0x20);
    DMA3_COPY_16(&sEndingUnk_74e8d0[offset], VRAM_OBJ + 0x4E0, 0x20);

    // Completion percentage (hundreds, tens and ones)
    digit1 = 0;
    digit2 = 0;
    digit3 = ENDING_DATA.completionPercentage;
    while (digit3 > 99)
    {
        digit3 -= 100;
        digit1++;
    }

    while (digit3 > 9)
    {
        digit3 -= 10;
        digit2++;
    }

    if (digit1 != 0)
    {
        offset = digit1 * 64;
        DMA3_COPY_16(&sEndingUnk_74e650[offset], VRAM_OBJ + 0x120, 0x20);
        DMA3_COPY_16(&sEndingUnk_74e8d0[offset], VRAM_OBJ + 0x520, 0x20);
    }

    if (digit1 != 0 || digit2 != 0)
    {
        offset = digit2 * 64;
        DMA3_COPY_16(&sEndingUnk_74e650[offset], VRAM_OBJ + 0x160, 0x20);
        DMA3_COPY_16(&sEndingUnk_74e8d0[offset], VRAM_OBJ + 0x560, 0x20);
    }

    offset = digit3 * 64;
    DMA3_COPY_16(&sEndingUnk_74e650[offset], VRAM_OBJ + 0x1A0, 0x20);
    DMA3_COPY_16(&sEndingUnk_74e8d0[offset], VRAM_OBJ + 0x5A0, 0x20);
}

/**
 * @brief a1628 | 3c | Updates the spawn delay of a letter of the ending image
 *
 * @param slot Letter slot
 */
void EndingImageUpdateLettersSpawnDelay(u32 slot)
{
    if (ENDING_DATA.unk_124[slot] != 0 && ENDING_DATA.unk_142[slot] != 0)
    {
        ENDING_DATA.unk_142[slot]--;
        if (ENDING_DATA.unk_142[slot] == 0)
            ENDING_DATA.unk_124[slot]++;
    }
}
