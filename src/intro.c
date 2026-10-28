#include "globals.h"
#include "new_file_intro.h"
#include "music_wrappers.h"
#include "audio_wrappers.h"
#include "callbacks.h"
#include "syscalls.h"

#include "constants/game_state.h"
#include "constants/audio.h"
#include "constants/text.h"
#include "constants/new_file_intro.h"

#include "structs/cutscene.h"

#include "data/new_file_intro_data.h"
#include "data/cutscene_unk_data.h"
#include "data/generic_data.h"
#include "data/sprite_data.h"
#include "data/audio.h"

void unk_99940(void); // For V-blank callback
u8 SpecialCutsceneGetRandomNumber(void);

void unk_93884(void);
void IntroShipAlertAndDraftingVblank(void);
u8 IntroSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearch);
void IntroSetupBigNumberOam(u8 type, s16 xPosition, s16 yPosition, s16 delay);
void unk_9397c(struct SpecialCutsceneOam* pOam);
u8 IntroSpaceViewSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearch);
void IntroSpaceViewVblank(void);
void Dma3Transfer_Unused2(void* src, void* dst, u16 size, u16 count);

 /**
 * @brief 9223c | 294 | Processes the Samus in ship cutscene
 *
 */
boolu32 IntroSamusInShipProcess(void)
{
    boolu32 finished;

    finished = FALSE;

    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer <= 5)
            {
                LZ77UncompVram(sIntroSamusSittingBgGfxPointers[INTRO_DATA.timer - 1], VRAM_BASE + 0x8000 + (INTRO_DATA.timer - 1) * 0x1000);
            }
            else if (INTRO_DATA.timer == 6)
            {
                LZ77UncompVram(sIntroUnk_658be0, VRAM_BASE + 0xE800);
                DMA3_COPY_32(sIntroUnk_6591e4, PALRAM_BASE, 8 * PAL_ROW_SIZE / sizeof(u32));
                gWrittenToBldalpha_Eva = 0;
                gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
                WRITE_16(REG_BG1HOFS, 0);
                WRITE_16(REG_BG1VOFS, 0);
                WRITE_16(REG_BG1CNT, CREATE_BGCNT(2, 29, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
            }
            else if (INTRO_DATA.timer == 7)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT |
                    BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BACKDROP_SECOND_TARGET_PIXEL);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Evb != 0)
                {
                    if (gWrittenToBldalpha_Evb == BLDALPHA_MAX_VALUE)
                    {
                        ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[SOUND_1EC].trackGroupNumber].pTrack, 10);
                        ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[SOUND_1ED].trackGroupNumber].pTrack, 10);
                    }

                    gWrittenToBldalpha_Evb -= 2;
                }
                else
                {
                    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
                    INTRO_DATA.subStage = 2;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
                {
                    if (gWrittenToBldalpha_Eva == 0)
                        PlayFadingSound(SOUND_1EB, 0);

                    gWrittenToBldalpha_Eva++;
                }
                else
                {
                    INTRO_DATA.subStage = 3;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 3:
            if (INTRO_DATA.timer == CONVERT_SECONDS(2.f / 3))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
                gWrittenToBldy = 0;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 4:
            INTRO_DATA.timer = 0;
            INTRO_DATA.subStage = 5;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 5:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.subStage = 6;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 6:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy += 2;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    IntroProcessText();

    return finished;
}

 /**
 * @brief 924d0 | 270 | Setup for the ship alert cutscene
 *
 */
void IntroShipAlertInit(void)
{
    u16 i;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));

    for (i = 0; i < 6; i++)
        LZ77UncompVram(sIntroUnk_79c45c[i], VRAM_OBJ + i * 0x1000);

    DMA3_COPY_32(sIntroUnk_65c268, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    for (i = 0; i < 5; i++)
        LZ77UncompVram(sIntroUnk_79c448[i], VRAM_BASE + i * 0x1000);

    LZ77UncompVram(sIntroUnk_6593e4, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroUnk_6599a4, PALRAM_BASE, 8 * PAL_ROW_SIZE / sizeof(u32));

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 30, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gWrittenToBldalpha_Eva = gWrittenToBldalpha_Evb = 0;
    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    IntroSetupOam(19, 96, 128, FALSE);
    IntroSetupOam(20, 128, 96, FALSE);
    IntroSetupOam(21, 128, 128, FALSE);
    IntroSetupOam(22, 200, 38, FALSE);
    IntroSetupOam(23, 210, 88, FALSE);
    IntroSetupBigNumberOam(24, 210, 88, 210);
    IntroSetupBigNumberOam(25, 67, 151, 200);
    IntroSetupBigNumberOam(26, 44, 152, 200);
    IntroSetupBigNumberOam(27, 37, 152, 200);
    IntroSetupBigNumberOam(28, 69, 125, 200);
    IntroSetupBigNumberOam(29, 62, 125, 200);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG1 | DCNT_OBJ);

    CallbackSetVBlank(IntroShipAlertAndDraftingVblank);
}

 /**
 * @brief 92740 | f0 | Processes the ship alert cutscene
 *
 */
boolu32 IntroShipAlertProcess(void)
{
    boolu32 finished;

    finished = FALSE;

    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            IntroShipAlertInit();
            INTRO_DATA.subStage = 1;
            INTRO_DATA.timer = 0;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy -= 2;
            }
            else
            {
                INTRO_DATA.subStage = 2;
                INTRO_DATA.timer = 0;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == 399)
            {
                gWrittenToBldy = 0;
            }
            else if (INTRO_DATA.timer == 400)
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.subStage = 3;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (gWrittenToBldy == 0)
                    ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[SOUND_1EB].trackGroupNumber].pTrack, 10);

                gWrittenToBldy += 2;
            }
            else
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.timer = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    IntroProcessText();

    return finished;
}

 /**
 * @brief 92830 | 1d0 | Setup for the Samus drifting out cutscene
 *
 */
void IntroSamusDriftingOutInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));

    LZ77UncompVram(sIntroUnk_6101b8, VRAM_OBJ);
    DMA3_COPY_32(sPal_612f48, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sTitleScreenSpaceBackgroundGfx, VRAM_BASE);
    LZ77UncompVram(sTitleScreenSpaceBackgroundTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sPal_609020, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    WRITE_16(PALRAM_BASE, 0);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gWrittenToBldalpha_Eva = gWrittenToBldalpha_Evb = 0;
    WRITE_16(REG_BLDALPHA, 0);

    IntroSetupOam(10, 145, 140, FALSE);
    IntroSetupOam(11, 140, 80, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(IntroShipAlertAndDraftingVblank);
}

 /**
 * @brief 92a00 | 1f4 | Processes the Samus drifting out cutscene
 *
 */
boolu32 IntroSamusDriftingOutProcess(void)
{
    boolu32 finished;
    s16 xPosition;
    s16 yPosition;

    finished = FALSE;

    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            IntroSamusDriftingOutInit();
            INTRO_DATA.subStage = 1;
            INTRO_DATA.timer = 0;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (gWrittenToBldy != 0)
            {
                if (gWrittenToBldy == BLDY_MAX_VALUE)
                {
                    PlayFadingSound(SOUND_1EC, 0);
                    PlayFadingSound(SOUND_1ED, 0);
                }

                gWrittenToBldy -= 2;
            }
            else
            {
                INTRO_DATA.subStage = 2;
                INTRO_DATA.timer = 0;
            }

            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 10)
            {
                xPosition = SpecialCutsceneGetRandomNumber();
                yPosition = SpecialCutsceneGetRandomNumber();
                IntroSetupOam(16, xPosition, yPosition, TRUE);
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(2.f + 1.f / 3))
                PlayMusic(MUSIC_PRE_TITLE_END, 15);

            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 10)
            {
                xPosition = SpecialCutsceneGetRandomNumber();
                yPosition = SpecialCutsceneGetRandomNumber();
                IntroSetupOam(16, xPosition, yPosition, TRUE);
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 3:
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 10)
            {
                xPosition = SpecialCutsceneGetRandomNumber();
                yPosition = SpecialCutsceneGetRandomNumber();
                IntroSetupOam(16, xPosition, yPosition, TRUE);
            }

            if (INTRO_DATA.timer == 1)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 4:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (INTRO_DATA.timer == 3)
                {
                    INTRO_DATA.timer = 0;

                    if (gWrittenToBldy == 0)
                        ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[SOUND_1EC].trackGroupNumber].pTrack, 30);

                    gWrittenToBldy++;
                }
            }
            else if (INTRO_DATA.timer == 8)
            {
                INTRO_DATA.timer = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    IntroProcessText();

    return finished;
}

 /**
 * @brief 92bf4 | 118 | Main handler for the Samus ship crashing cutscene
 *
 */
boolu32 IntroSamusShipCrashing(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                INTRO_DATA.stage = 2;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (IntroSamusInShipProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (IntroShipAlertProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 4;
            }
            break;

        case 4:
            if (IntroSamusDriftingOutProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 5;
            }
            break;

        case 5:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 92d0c | 148 | Handles the background shaking while Samus is in the ship
 *
 */
void unk_92d0c(struct SpecialCutsceneOam* pOam)
{
    u8 rng1;
    u8 rng2;

    rng1 = sRandomNumberTable[MOD_AND(gFrameCounter16Bit, 32)] / 4;
    rng2 = sRandomNumberTable[MOD_AND(gFrameCounter16Bit + 7, 32)] / 4;

    if (!pOam->unk_8)
    {
        pOam->timer++;
        if (pOam->timer)
        {
            pOam->timer = 0;
            if (pOam->yPosition < 16)
            {
                pOam->yPosition += rng2;
                if (pOam->yPosition > 15)
                {
                    pOam->yPosition = 16;
                    pOam->unk_8 = 1;
                }
            }
        }
    }
    else
    {
        pOam->timer++;
        if (pOam->timer)
        {
            pOam->timer = 0;
            if (pOam->yPosition > 0)
            {
                pOam->yPosition -= rng2;
                if (pOam->yPosition <= 0)
                {
                    pOam->yPosition = 0;
                    pOam->unk_8 = 0;
                }
            }
        }
    }

    if (!pOam->unk_4)
    {
        pOam->unk_A++;
        if (pOam->unk_A)
        {
            pOam->unk_A = 0;
            if (pOam->xPosition < 16)
            {
                pOam->xPosition += rng1;
                if (pOam->xPosition > 15)
                {
                    pOam->xPosition = 16;
                    pOam->unk_4 = 1;
                }
            }
        }
    }
    else
    {
        pOam->unk_A++;
        if (pOam->unk_A)
        {
            pOam->unk_A = 0;
            if (pOam->xPosition > 0)
            {
                pOam->xPosition -= rng1;
                if (pOam->xPosition <= 0)
                {
                    pOam->xPosition = 0;
                    pOam->unk_4 = 0;
                }
            }
        }
    }

    gBg2XPosition = pOam->xPosition;
    gBg2YPosition = pOam->yPosition;

    if (INTRO_DATA.subStage == 4)
    {
        pOam->rotation++;
        if (pOam->rotation == 2)
        {
            pOam->rotation = 0;

            if (gWrittenToBldalpha_Eva != 0)
                gWrittenToBldalpha_Eva--;

            if (gWrittenToBldalpha_Evb < BLDALPHA_MAX_VALUE)
                gWrittenToBldalpha_Evb++;
        }
    }
}

 /**
 * @brief 92e54 | 26c | Handles Samus' ship drifting out
 *
 * @param pOam Cutscene OAM data pointer
 */
void IntroProcessDriftingShip(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->yPosition = (SIN(pOam->timer) >> 7) + pOam->spawnY;

        if (pOam->timer > 52)
        {
            pOam->unk_4++;
            if (pOam->unk_4 == 12)
            {
                pOam->rotation--;
                pOam->xPosition--;
                pOam->unk_4 = 0;
            }

            pOam->unk_8++;
            if (pOam->unk_8 == 10)
            {
                pOam->unk_8 = 0;
                pOam->scaling--;
            }
        }

        if (pOam->timer > 127)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 2;
            SoundPlay(SOUND_1F2);
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->timer++;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 2);
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 3) + (SIN(pOam->timer) >> 7);
        pOam->unk_4++;

        if (pOam->unk_4 == 12)
        {
            pOam->rotation--;
            pOam->unk_4 = 0;
        }

        pOam->unk_8++;
        if (pOam->unk_8 == 2)
        {
            pOam->unk_8 = 0;
            pOam->scaling--;
        }

        if (pOam->timer == 0)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        pOam->timer++;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 2);
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 3);
        pOam->unk_4++;

        if (pOam->unk_4 == 12)
        {
            pOam->rotation--;
            pOam->unk_4 = 0;
        }

        pOam->unk_8++;
        if (pOam->unk_8 == 1)
        {
            pOam->unk_8 = 0;
            pOam->scaling--;
        }

        if (pOam->timer == 0)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 4;
        }

        if (pOam->scaling < 3)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->timer++;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 1);
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 2);
        pOam->unk_4++;

        if (pOam->unk_4 == 12)
        {
            pOam->rotation--;
            pOam->unk_4 = 0;
        }

        pOam->unk_8++;
        if (pOam->unk_8 == 1)
        {
            pOam->unk_8 = 0;
            pOam->scaling--;
        }

        if (pOam->scaling < 3)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        pOam->unk_A = 0;
        pOam->scaling = Q_8_8(1);
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->affineMode = OAM_AFFINE_MODE_NORMAL;
        pOam->pOam = sIntroUnk_60ad48;
        pOam->stage = 6;
        SoundPlay_3b1c(SOUND_1F3);
        INTRO_DATA.timer = 0;
        INTRO_DATA.subStage = 3;
    }
    else if (pOam->stage == 6)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
}

 /**
 * @brief 930c0 | 64 | Spawns the parts of the BSL ship
 *
 * @param pOam Cutscene OAM data pointer
 */
void IntroProcessBslShipSpawning(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        IntroSetupOam(12, pOam->xPosition + 122, pOam->yPosition, FALSE);
        IntroSetupOam(13, pOam->xPosition + 50, pOam->yPosition + 1, FALSE);
        IntroSetupOam(14, pOam->xPosition + 36, pOam->yPosition, FALSE);
        IntroSetupOam(15, pOam->xPosition, pOam->yPosition, FALSE);
        pOam->type = 0;
    }
}

 /**
 * @brief 93124 | d4 | Handles the back of the BSL ship
 *
 * @param pOam Cutscene OAM data pointer
 */
void IntroProcessBslShipBack(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->timer++;
        if (pOam->timer == 20)
        {
            pOam->spawnX++;
            pOam->timer = 0;

            if (pOam->unk_A == 4)
                pOam->unk_A = 0;

            if (pOam->unk_A < 2)
                pOam->yPosition++;
            else if (pOam->unk_A < 4)
                pOam->yPosition--;

            if (pOam->spawnX == 30)
            {
                pOam->stage = 1;
                pOam->timer = 0;
            }

            pOam->unk_A++;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->unk_A = 0;
        pOam->stage = 2;
    }
    else if (pOam->stage == 2)
    {
        pOam->timer++;
        if (pOam->timer == 2)
        {
            pOam->unk_A++;
            pOam->timer = 0;
        }

        pOam->xPosition = (((900 - pOam->spawnX) * pOam->unk_A) >> 12) + pOam->spawnX;
        pOam->yPosition = (((pOam->unk_4 - pOam->spawnY) * pOam->unk_A) >> 11) + pOam->spawnY;

        if (pOam->xPosition > 320)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 3;
        }
    }
}

 /**
 * @brief 931f8 | c4 | Handles a depth particle
 *
 * @param pOam Cutscene OAM data pointer
 */
void IntroProcessDepthParticle(struct SpecialCutsceneOam* pOam)
{
    s32 x;
    s32 y;
    s32 divisor;

    pOam->unk_4 = pOam->unk_A;

    if (pOam->stage == 0)
    {
        pOam->spawnX = (pOam->xPosition - SCREEN_X_MIDDLE) * 100;
        pOam->spawnY = (pOam->yPosition - SCREEN_Y_MIDDLE) * 100;
        pOam->stage = 1;
    }
    else
    {
        if ((s16)pOam->unk_A < 100)
        {
            if ((s16)pOam->unk_A == 25)
                pOam->pOam = sIntroUnk_60ac18;
            else if ((s16)pOam->unk_A == 50)
                pOam->pOam = sIntroUnk_60ac28;
            else if ((s16)pOam->unk_A == 70)
                pOam->pOam = sIntroUnk_60ac38;

            divisor = -pOam->unk_4 + 100;
            x = pOam->spawnX / divisor;
            pOam->xPosition = x + SCREEN_X_MIDDLE;
            y = pOam->spawnY / divisor + SCREEN_Y_MIDDLE;
            pOam->yPosition = y;

            if ((u16)(x + 128) > 256 || (s16)y > 168 || (s16)y < -8)
            {
                pOam->type = 0;
                pOam->unk_18_0 = 0;
            }
        }
        else
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }

    pOam->unk_A++;
}

 /**
 * @brief 932bc | 20 | Handles the time and distance text
 *
 * @param pOam Cutscene OAM data pointer
 */
void IntroProcessTimeAndDistanceOam(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0 && pOam->currentAnimationFrame == 1)
    {
        SoundPlay(SOUND_1EE);
        pOam->stage = 1;
    }
}

 /**
 * @brief 932dc | 24 | Handles the asteroids pop up
 *
 * @param pOam Cutscene OAM data pointer
 */
void IntroProcessAsteroidsPopUp(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0 && pOam->currentAnimationFrame == 1)
    {
        SoundPlay(SOUND_1EF);
        pOam->stage = 1;
    }
}

 /**
 * @brief 93300 | 34 | To document
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_93300(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_A++;
        if (pOam->unk_A == pOam->unk_8)
        {
            pOam->unk_18_0 = 1;
            pOam->stage = 1;
            SoundPlay(SOUND_1F1);
        }
    }
}

 /**
 * @brief 93334 | 48 | To document
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_93334(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->currentAnimationFrame == 1 && pOam->animationDurationCounter == 1)
        SoundPlay(SOUND_1F0);

    frame = &pOam->pOam[pOam->currentAnimationFrame];
    if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 9337c | 2c | Handles a big changing number
 *
 * @param pOam Cutscene OAM data pointer
 */
void IntroOamProcessBigChangingNumber(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_A++;
        if (pOam->unk_A == pOam->unk_8)
        {
            pOam->unk_18_0 = 1;
            pOam->stage = 1;
        }
    }
}

 /**
 * @brief 933a8 | 4a0 | Spawns an OAM for the intro
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param descendingSearch Search for a free slot in descending order
 * @return u8 Slot
 */
u8 IntroSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearch)
{
    s8 slot;

    if (!descendingSearch)
    {
        for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot > 19)
            return 20;
    }
    else
    {
        for (slot = ARRAY_SIZE(INTRO_DATA.oam) - 1; slot >= 0; slot--)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot < 0)
            return 20;
    }

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = 1;

    if (type == 1)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_92d0c;
    }
    else if (type == 10)
    {
        INTRO_DATA.oam[slot].spawnX = xPosition;
        INTRO_DATA.oam[slot].spawnY = yPosition;
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_AFFINE;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_60acd0;
        INTRO_DATA.oam[slot].pFunction = IntroProcessDriftingShip;
    }
    else if (type == 11)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_60acd0;
        INTRO_DATA.oam[slot].pFunction = IntroProcessBslShipSpawning;
    }
    else if (type == 12)
    {
        INTRO_DATA.oam[slot].unk_4 = -40;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_60ad28;
        INTRO_DATA.oam[slot].pFunction = IntroProcessBslShipBack;
    }
    else if (type == 13)
    {
        INTRO_DATA.oam[slot].unk_4 = -30;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_60ad18;
        INTRO_DATA.oam[slot].pFunction = IntroProcessBslShipBack;
    }
    else if (type == 14)
    {
        INTRO_DATA.oam[slot].unk_4 = -20;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_60ad08;
        INTRO_DATA.oam[slot].pFunction = IntroProcessBslShipBack;
    }
    else if (type == 15)
    {
        INTRO_DATA.oam[slot].unk_4 = -10;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_60acf8;
        INTRO_DATA.oam[slot].pFunction = IntroProcessBslShipBack;
    }
    else if (type == 16)
    {
        INTRO_DATA.oam[slot].pOam = sIntroUnk_60ac08;
        INTRO_DATA.oam[slot].pFunction = IntroProcessDepthParticle;
    }
    else if (type == 19)
    {
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65bb38;
        INTRO_DATA.oam[slot].pFunction = IntroProcessTimeAndDistanceOam;
    }
    else if (type == 20)
    {
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65bd00;
        INTRO_DATA.oam[slot].pFunction = unk_9397c;
    }
    else if (type == 21)
    {
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65bd48;
        INTRO_DATA.oam[slot].pFunction = unk_9397c;
    }
    else if (type == 22)
    {
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65bd60;
        INTRO_DATA.oam[slot].pFunction = IntroProcessAsteroidsPopUp;
    }
    else if (type == 23)
    {
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65be00;
        INTRO_DATA.oam[slot].pFunction = unk_93334;
    }
    else if (type == 24)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65bf10;
        INTRO_DATA.oam[slot].pFunction = IntroOamProcessBigChangingNumber;
    }
    else if (type == 25)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65c0d0;
        INTRO_DATA.oam[slot].pFunction = unk_93300;
    }
    else if (type == 26)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65c128;
        INTRO_DATA.oam[slot].pFunction = IntroOamProcessBigChangingNumber;
    }
    else if (type == 27)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65c180;
        INTRO_DATA.oam[slot].pFunction = IntroOamProcessBigChangingNumber;
    }
    else if (type == 28)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65c1d8;
        INTRO_DATA.oam[slot].pFunction = IntroOamProcessBigChangingNumber;
    }
    else if (type == 29)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroUnk_65c230;
        INTRO_DATA.oam[slot].pFunction = IntroOamProcessBigChangingNumber;
    }

    return slot;
}

 /**
 * @brief 93848 | 3c | Spawns a big number OAM for the intro
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param delay Delay before the number appears
 */
void IntroSetupBigNumberOam(u8 type, s16 xPosition, s16 yPosition, s16 delay)
{
    u8 slot;

    slot = IntroSetupOam(type, xPosition, yPosition, FALSE);
    INTRO_DATA.oam[slot].unk_8 = delay;
}

 /**
 * @brief 93884 | 7c | V-blank for the Samus in ship cutscene
 *
 */
void unk_93884(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

 /**
 * @brief 93900 | 7c | V-blank for the ship alert and drafting cutscenes
 *
 */
void IntroShipAlertAndDraftingVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

 /**
 * @brief 9397c | 4 | Empty OAM process function
 *
 * @param pOam Cutscene OAM data pointer
 */
void unk_9397c(struct SpecialCutsceneOam* pOam)
{
    return;
}

 /**
 * @brief 93980 | 240 | Setup for the intro space view cutscene
 *
 */
void IntroSpaceViewInit(void)
{
    u16 i;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DoSoundAction(0x1000000);
    StopAllMusicAndSounds();

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sIntroUnk_6101b8, VRAM_OBJ);
    DMA3_COPY_32(sPal_612f48, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroBslSpaceBgGfx, VRAM_BASE);

    LZ77UncompWram(sIntroBslTilemap, EWRAM_BASE + 0x10000);
    DMA3_COPY_32(EWRAM_BASE + 0x10000, VRAM_BASE + 0xE800, 0x800 / sizeof(u32));

    DMA3_FILL_16(0x1FF, VRAM_BASE + 0xF000, 0x800);

    LZ77UncompVram(sIntroSpaceTilemap, VRAM_BASE + 0xF800);

    DMA3_COPY_32(sIntroBslSpaceBgPal, PALRAM_BASE + 0x100, 8 * PAL_ROW_SIZE / sizeof(u32));
    WRITE_16(PALRAM_BASE, 0);

    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 29, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_512x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    IntroSpaceViewSetupOam(1, 0, 0, TRUE);
    IntroSpaceViewSetupOam(2, -240, -110, TRUE);

    for (i = 0; i < 10; i++)
        IntroSpaceViewSetupOam(5, SpecialCutsceneGetRandomNumber(), SpecialCutsceneGetRandomNumber(), TRUE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(IntroSpaceViewVblank);

    PlayMusic(MUSIC_60, 15);
}

 /**
 * @brief 93bc0 | 38c | Processes the intro space view cutscene
 *
 * @return boolu32 bool, ended
 */
boolu32 IntroSpaceViewPartProcess(void)
{
    boolu32 finished;

    finished = FALSE;

    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy--;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }

            if (SpecialCutsceneGetRandomNumber() < 64 && INTRO_DATA.unk_215 < 14)
                IntroSpaceViewSetupOam(5, SpecialCutsceneGetRandomNumber(), SpecialCutsceneGetRandomNumber(), TRUE);

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                INTRO_DATA.timer = 0;
                IntroSpaceViewSetupOam(4, 120, 74, FALSE);
                INTRO_DATA.subStage = 2;
            }

            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
                IntroSpaceViewSetupOam(5, 0, SpecialCutsceneGetRandomNumber(), TRUE);

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(8.f))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 3;
            }

            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
                IntroSpaceViewSetupOam(5, 0, SpecialCutsceneGetRandomNumber(), TRUE);

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 3:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                SoundPlay(SOUND_1E9);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(17.5f))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 5;
            }

            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
                IntroSpaceViewSetupOam(5, 0, SpecialCutsceneGetRandomNumber(), TRUE);

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 4:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (gWrittenToBldy == 0)
                    ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[SOUND_1EB].trackGroupNumber].pTrack, 10);

                gWrittenToBldy += 2;
            }
            else
            {
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 5:
            if (INTRO_DATA.timer <= 5)
            {
                LZ77UncompVram(sIntroSamusSittingBgGfxPointers[INTRO_DATA.timer - 1], VRAM_BASE + 0x8000 + (INTRO_DATA.timer - 1) * 0x1000);
            }
            else if (INTRO_DATA.timer == 6)
            {
                LZ77UncompVram(sIntroUnk_658be0, VRAM_BASE + 0xE000);
                DMA3_COPY_32(sIntroUnk_6591e4, PALRAM_BASE, 8 * PAL_ROW_SIZE / sizeof(u32));
                gWrittenToBldalpha_Eva = 0;
                gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
                WRITE_16(REG_BG1HOFS, 0);
                WRITE_16(REG_BG1VOFS, 0);
                WRITE_16(REG_BG1CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
            }
            else if (INTRO_DATA.timer == 7)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT |
                    BLDCNT_BG2_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL |
                    BLDCNT_BACKDROP_SECOND_TARGET_PIXEL);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 6;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 6:
            if (INTRO_DATA.timer == 4)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
                {
                    if (gWrittenToBldalpha_Eva == 0)
                    {
                        ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[SOUND_1E9].trackGroupNumber].pTrack, 60);
                        ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[SOUND_1EA].trackGroupNumber].pTrack, 60);
                        PlayFadingSound(SOUND_1EB, 60);
                    }

                    gWrittenToBldalpha_Eva++;
                    gWrittenToBldalpha_Evb--;
                }
                else
                {
                    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
                    INTRO_DATA.subStage = 7;
                    gWrittenToBldy = 0;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 7:
            if (INTRO_DATA.timer == CONVERT_SECONDS(2.5f))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
            }
            break;
    }

    IntroProcessText();

    return finished;
}

 /**
 * @brief 93f4c | 1c8 | Setup for the intro flying view cutscene
 *
 */
void IntroFlyingViewInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));

    LZ77UncompVram(sIntroUnk_6101b8, VRAM_OBJ);
    DMA3_COPY_32(sPal_612f48, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sTitleScreenSpaceBackgroundGfx, VRAM_BASE);
    LZ77UncompVram(sTitleScreenSpaceBackgroundTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sPal_609020, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sPal_598a8c, PALRAM_BASE + 15 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
    WRITE_16(PALRAM_BASE, 0);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    IntroSpaceViewSetupOam(10, 145, 140, FALSE);
    IntroSpaceViewSetupOam(11, 140, 80, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(IntroSpaceViewVblank);
}

 /**
 * @brief 94114 | f0 | Processes the intro flying view cutscene
 *
 * @return boolu32 bool, ended
 */
boolu32 IntroFlyingViewProcess(void)
{
    boolu32 finished;

    finished = FALSE;

    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (gWrittenToBldy != 0)
            {
                if (gWrittenToBldy == BLDY_MAX_VALUE)
                {
                    PlayFadingSound(SOUND_1EC, 0);
                    PlayFadingSound(SOUND_1ED, 0);
                }

                gWrittenToBldy -= 2;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 10)
                IntroSpaceViewSetupOam(16, SpecialCutsceneGetRandomNumber(), SpecialCutsceneGetRandomNumber(), FALSE);

            if (INTRO_DATA.timer == CONVERT_SECONDS(5.f))
            {
                INTRO_DATA.timer = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
                gWrittenToBldy++;
            else
                finished = TRUE;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    IntroProcessText();

    return finished;
}

 /**
 * @brief 94204 | 124 | Main handler for the intro space view cutscene
 *
 * @return boolu32 bool, ended
 */
boolu32 IntroSpaceView(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            IntroSpaceViewInit();
            INTRO_DATA.stage = 1;
            break;

        case 1:
            SpecialCutsceneFadeIn();

            if (gWrittenToBldy == 0)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (IntroSpaceViewPartProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
                gWrittenToBldy++;
            else
                INTRO_DATA.stage = 4;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();

        case 4:
            IntroFlyingViewInit();
            INTRO_DATA.stage = 6;
            break;

        case 5:
            INTRO_DATA.stage = 6;
            break;

        case 6:
            if (IntroFlyingViewProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }
            break;

        case 7:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 94328 | 28 | Handles the background scrolling in the intro space view cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void IntroProcessSpaceViewScrolling(struct SpecialCutsceneOam* pOam)
{
    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == CONVERT_SECONDS(.5f))
    {
        pOam->animationDurationCounter = 0;
        gBg3XPosition--;
    }
}

 /**
 * @brief 94350 | 23c | Handles the BSL ship moving sideways
 *
 * @param pOam Cutscene OAM data pointer
 */
void IntroProcessBslShipSideways(struct SpecialCutsceneOam* pOam)
{
    s32 cos;
    s32 sin;
    s32 y;
    u8 status;

    pOam->unk_4 = pOam->xPosition;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;

        if (INTRO_DATA.subStage == 3)
            pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 780)
            IntroSpaceViewSetupOam(3, 260, 110, FALSE);

        pOam->xPosition = (((60 - pOam->spawnX) * (pOam->unk_A << 1)) >> 11) + pOam->spawnX;
        pOam->yPosition = (((10 - pOam->spawnY) * (pOam->unk_A << 1)) >> 11) + pOam->spawnY;

        if (pOam->xPosition > 29)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 1)
        {
            pOam->unk_A = 0;
            pOam->spawnY = 4;
            pOam->unk_4 = pOam->xPosition;
            pOam->unk_8 = pOam->yPosition;
            pOam->timer = 0;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        cos = pOam->spawnX * COS(pOam->timer);
        sin = pOam->spawnY * SIN(pOam->timer);
        y = cos * SIN(0) + sin * COS(0);
        pOam->xPosition = pOam->unk_A / 4 + pOam->spawnX;
        pOam->yPosition = (y >> 16) + pOam->unk_8;
        pOam->timer++;

        pOam->unk_A++;
        if (pOam->unk_A != 60)
        {
            if (pOam->unk_A == 30000)
            {
                pOam->unk_A = 0;
                pOam->stage = 4;
            }
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->stage = 5;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
    }
    else if (pOam->stage == 5)
    {
        pOam->unk_A++;
        pOam->xPosition = (((520 - pOam->spawnX) * pOam->unk_A) >> 10) + pOam->spawnX;
        pOam->yPosition = (((100 - pOam->spawnY) * pOam->unk_A) >> 10) + pOam->spawnY;

        if (pOam->xPosition >= 520)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 6;
        }
    }

    gBg2XPosition = pOam->xPosition;
    gBg2YPosition = pOam->yPosition;

    if (pOam->xPosition >= -120)
    {
        pOam->currentAnimationFrame += pOam->xPosition - pOam->unk_4;

        status = pOam->unk_1A_4;
        if (status == 0)
        {
            if (pOam->currentAnimationFrame >= 8)
            {
                pOam->currentAnimationFrame -= 8;
                Dma3Transfer_Unused2(EWRAM_BASE + 0x10800 + pOam->animationDurationCounter * 2,
                    VRAM_BASE + 0xF000 + pOam->animationDurationCounter * 2, 1, 20);

                pOam->animationDurationCounter++;
                if (pOam->animationDurationCounter == 32)
                {
                    pOam->animationDurationCounter = 0;
                    pOam->unk_1A_4 = 1;
                }
            }
        }
        else if (status == 1)
        {
            if (pOam->currentAnimationFrame >= 8)
            {
                pOam->currentAnimationFrame -= 8;

                pOam->animationDurationCounter++;
                if (pOam->animationDurationCounter == 32)
                {
                    pOam->animationDurationCounter = 0;
                    pOam->unk_1A_4 = 10;
                }
            }
        }
    }
}
