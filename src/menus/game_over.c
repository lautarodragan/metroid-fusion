#include "menus/game_over.h"
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

#include "data/menus/game_over_data.h"

#include "constants/audio.h"
#include "constants/game_state.h"
#include "constants/menus/game_over.h"

/**
 * @brief 9deb4 | a4 | Game over subroutine
 *
 * @return u32 Choice made (0 if still running)
 */
u32 GameOverHandler(void)
{
    u32 result;

    result = GAME_OVER_CHOICE_NONE;

    switch (gSubGameMode1)
    {
        case 0:
            GameOverInit();
            gSubGameMode1 = 1;
            break;

        case 1:
            GameOverDrawAllOam();
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy--;
            }
            else
            {
                PlayMusic(MUSIC_AFTER_EVENT, 0);
                gSubGameMode1++;
            }
            break;

        case 2:
            if (GameOverAfterOptionDelay())
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                gSubGameMode1++;
            }
            break;

        case 3:
            GameOverDrawAllOam();
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                if (GAME_OVER_DATA.choice == GAME_OVER_CHOICE_CONTINUE)
                    result = GAME_OVER_CHOICE_CONTINUE;
                else if (GAME_OVER_DATA.choice == GAME_OVER_CHOICE_QUIT)
                    result = GAME_OVER_CHOICE_QUIT;

                gSubGameMode1 = 0;
            }
            break;
    }

    return result;
}

/**
 * @brief 9df58 | 1cc | Initializes the game over screen
 *
 */
void GameOverInit(void)
{
    u32 zero;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_9e58c);

    WRITE_16(REG_DISPCNT, 0);

    zero = 0;
    DMA_SET(3, &zero, &gNonGameplayRam, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, sizeof(gNonGameplayRam) / sizeof(u32)));

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    DMA3_COPY_32(VRAM_OBJ, gSpriteGfxBackup, sizeof(gSpriteGfxBackup) / sizeof(u32));

    ClearGfxRam();
    gNextOamSlot = 0;
    ResetFreeOam();

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

    LZ77UncompVram(sGameOverUnk_739a78, VRAM_OBJ);
    DMA3_COPY_32(sGameOverUnk_73c4e4, PALRAM_OBJ, PAL_SIZE / sizeof(u32));
    LZ77UncompVram(sGameOverUnk_73422c, VRAM_BASE);

    if (gLanguage > LANGUAGE_HIRAGANA)
        LZ77UncompVram(sGameOverTextGfxPointers[gLanguage], VRAM_BASE);

    LZ77UncompVram(sGameOverUnk_73c6e4, VRAM_BASE + 0xF800);
    LZ77UncompVram(sGameOverUnk_73cca8, VRAM_BASE + 0xF000);
    DMA3_COPY_32(sGameOverUnk_73c2e4, PALRAM_BASE, PAL_SIZE / sizeof(u32));

    WRITE_16(REG_BG1CNT, 0x1E02);
    WRITE_16(REG_BG3CNT, 0x1F03);

    GameOverSetupOam(GAME_OVER_OAM_TYPE_CURSOR, GAME_OVER_CURSOR_X, GAME_OVER_CURSOR_Y_CONTINUE);
    GameOverDrawAllOam();

    WRITE_16(REG_DISPCNT, DCNT_BG1 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(GameOverVblank);
}

/**
 * @brief 9e124 | 34 | Handles the delay after an option was selected
 *
 * @return boolu32 bool, ended
 */
boolu32 GameOverAfterOptionDelay(void)
{
    boolu32 ended;

    ended = FALSE;

    GameOverProcessOam();
    GameOverDrawAllOam();

    if (GAME_OVER_DATA.optionSelected == TRUE)
    {
        if (++GAME_OVER_DATA.optionSelectedTimer == 30)
        {
            GAME_OVER_DATA.optionSelectedTimer = 0;
            ended = TRUE;
        }
    }

    return ended;
}

/**
 * @brief 9e158 | ac | Sets up a game over oam
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot (GAME_OVER_OAM_COUNT if none were available)
 */
u8 GameOverSetupOam(u8 type, u16 xPosition, u16 yPosition)
{
    u8 i;

    for (i = 0; GAME_OVER_DATA.oam[i].type != GAME_OVER_OAM_TYPE_NONE; )
    {
        i++;
        if (i >= GAME_OVER_OAM_COUNT)
            return GAME_OVER_OAM_COUNT;
    }

    if (i >= GAME_OVER_OAM_COUNT)
        return GAME_OVER_OAM_COUNT;

    GameOverResetOam(i);

    GAME_OVER_DATA.oam[i].xPosition = xPosition;
    GAME_OVER_DATA.oam[i].yPosition = yPosition;
    GAME_OVER_DATA.oam[i].type = type;
    GAME_OVER_DATA.oam[i].isDrawn = TRUE;

    if (type == GAME_OVER_OAM_TYPE_CURSOR)
    {
        GAME_OVER_DATA.oam[i].priority = 3;
        GAME_OVER_DATA.oam[i].pOam = sGameOverCursorOam[0];
        GAME_OVER_DATA.oam[i].pHandler = GameOverProcessCursor;
    }
    else if (type == GAME_OVER_OAM_TYPE_2)
    {
        GAME_OVER_DATA.oam[i].priority = 3;
        GAME_OVER_DATA.oam[i].pOam = sGameOverUnk_73c274;
        GAME_OVER_DATA.oam[i].pHandler = unk_9e2cc;
    }

    return i;
}

/**
 * @brief 9e204 | c8 | Processes the game over cursor
 *
 * @param pOam Game over oam pointer
 */
void GameOverProcessCursor(struct GameOverOam* pOam)
{
    if (pOam->unk_9 != 0)
        return;

    if (gChangedInput & KEY_UP)
    {
        if ((s16)pOam->yPosition != GAME_OVER_CURSOR_Y_CONTINUE)
        {
            pOam->yPosition = GAME_OVER_CURSOR_Y_CONTINUE;
            SoundPlay(SOUND_1F9);
        }
    }
    else if (gChangedInput & KEY_DOWN)
    {
        if ((s16)pOam->yPosition != GAME_OVER_CURSOR_Y_QUIT)
        {
            pOam->yPosition = GAME_OVER_CURSOR_Y_QUIT;
            SoundPlay(SOUND_1F9);
        }
    }

    if (gChangedInput & (KEY_A | KEY_START))
    {
        if ((s16)pOam->yPosition == GAME_OVER_CURSOR_Y_CONTINUE)
        {
            SoundPlay(SOUND_1FE);
            FadeMusic(10);
            pOam->pOam = sGameOverCursorOam[1];
            GAME_OVER_DATA.choice = GAME_OVER_CHOICE_CONTINUE;
        }
        else if ((s16)pOam->yPosition == GAME_OVER_CURSOR_Y_QUIT)
        {
            SoundPlay(SOUND_1FE);
            FadeMusic(10);
            pOam->pOam = sGameOverCursorOam[2];
            GAME_OVER_DATA.choice = GAME_OVER_CHOICE_QUIT;
        }

        GAME_OVER_DATA.optionSelected = TRUE;
        pOam->currentAnimationFrame = 0;
        pOam->animationDurationCounter = 0;
        pOam->unk_9 = 1;
    }
}

/**
 * @brief 9e2cc | 28 | To document
 *
 * @param pOam Game over oam pointer
 */
void unk_9e2cc(struct GameOverOam* pOam)
{
    u16 xPosition;
    u16 yPosition;

    GameOverGetPositionAndSlotOfOamByType(GAME_OVER_OAM_TYPE_CURSOR, &xPosition, &yPosition);
    pOam->xPosition = xPosition;
    pOam->yPosition = yPosition;
}

/**
 * @brief 9e2f4 | 28 | Resets a game over oam
 *
 * @param slot Slot
 */
void GameOverResetOam(u8 slot)
{
    GAME_OVER_DATA.oam[slot].currentAnimationFrame = 0;
    GAME_OVER_DATA.oam[slot].animationDurationCounter = 0;
    GAME_OVER_DATA.oam[slot].unk_8 = 0;
    GAME_OVER_DATA.oam[slot].unk_9 = 0;
    GAME_OVER_DATA.oam[slot].objMode = 0;
    GAME_OVER_DATA.oam[slot].priority = 0;
    GAME_OVER_DATA.oam[slot].xFlip = 0;
    GAME_OVER_DATA.oam[slot].paletteRow = 0;
    GAME_OVER_DATA.oam[slot].tileOffset = 0;
}

/**
 * @brief 9e31c | 38 | Calls the handler of every game over oam
 *
 */
void GameOverProcessOam(void)
{
    u8 i;

    for (i = 0; i < GAME_OVER_OAM_COUNT; i++)
    {
        if (GAME_OVER_DATA.oam[i].type != GAME_OVER_OAM_TYPE_NONE)
            GAME_OVER_DATA.oam[i].pHandler(&GAME_OVER_DATA.oam[i]);
    }
}

/**
 * @brief 9e354 | 40 | Draws every game over oam
 *
 */
void GameOverDrawAllOam(void)
{
    u8 i;

    for (i = 0; i < GAME_OVER_OAM_COUNT; i++)
    {
        if (GAME_OVER_DATA.oam[i].isDrawn)
            GameOverDrawOam(&GAME_OVER_DATA.oam[i]);
    }

    ResetFreeOam();
    gNextOamSlot = 0;
}

/**
 * @brief 9e394 | 188 | Draws a game over oam
 *
 * @param pOam Game over oam pointer
 */
void GameOverDrawOam(struct GameOverOam* pOam)
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
            offset = sGameOverUnk_734220[gOamData[slot].split.shape][gOamData[slot].split.size] * 8 + part2;
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
 * @brief 9e51c | 44 | Gets the position of the first game over oam of a type
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 */
void GameOverGetPositionAndSlotOfOamByType(u8 type, u16* pXPosition, u16* pYPosition)
{
    u8 i;

    for (i = 0; i < GAME_OVER_OAM_COUNT; i++)
    {
        if (GAME_OVER_DATA.oam[i].type == type)
        {
            *pXPosition = GAME_OVER_DATA.oam[i].xPosition;
            *pYPosition = GAME_OVER_DATA.oam[i].yPosition;
            return;
        }
    }

    *pXPosition = 300;
    *pYPosition = 200;
}

/**
 * @brief 9e560 | 2c | V-blank code for the game over screen
 *
 */
void GameOverVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 9e58c | c | Empty v-blank code for the game over screen
 *
 */
void unk_9e58c(void)
{
    UpdateAudio();
}
