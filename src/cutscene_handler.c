#include "globals.h"
#include "cutscene_handler.h"
#include "callbacks.h"
#include "init_helpers.h"
#include "oam.h"
#include "syscalls.h"

#include "audio/track_internal.h"

#include "data/new_file_intro_data.h"

/**
 * @brief 9994c | 78 | Main handler for the cutscenes
 *
 * @return boolu32 Finished
 */
boolu32 CutsceneHandler(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (gSubGameMode1)
    {
        case 0:
            CutsceneInit();
            gSubGameMode1 = 2;
            break;

        case 1:
            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                gSubGameMode1++;
            break;

        case 2:
            if (CutsceneProcess())
                gSubGameMode1++;
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                finished = TRUE;
                gSubGameMode1 = 0;
            }
            break;
    }

    return finished;
}

/**
 * @brief 999c4 | 120 | Initializes a cutscene
 *
 */
void CutsceneInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99af8);

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    DMA3_COPY_32(VRAM_OBJ, gSpriteGfxBackup, sizeof(gSpriteGfxBackup) / sizeof(u32));

    gNextOamSlot = 0;
    ResetFreeOam();

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
    DMA3_FILL_32(COLOR_WHITE, PALRAM_BASE, PALRAM_SIZE / 2);
    WRITE_16(PALRAM_BASE, 0);
    DMA3_FILL_32(0, VRAM_BASE, 0x10000);

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

    CallbackSetVBlank(CutsceneVblank);
}

/**
 * @brief 99ae4 | 14 | V-blank for the cutscenes
 *
 */
void CutsceneVblank(void)
{
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 99af8 | c | V-blank for the cutscenes while they're loading
 *
 */
void unk_99af8(void)
{
    UpdateAudio();
}

/**
 * @brief 99b04 | a8 | Processes the current cutscene
 *
 * @return boolu32 Finished
 */
boolu32 CutsceneProcess(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (gCurrentCutscene)
    {
        case CUTSCENE_MONOLOGUE_INTRO:
        case CUTSCENE_MONOLOGUE_END:
            if (CutsceneInternalMonologue(0))
                finished = TRUE;
            break;

        case CUTSCENE_ELEVATOR_MONOLOGUE_REMIND:
            if (CutsceneElevatorMonologue(FALSE))
                finished = TRUE;
            break;

        case CUTSCENE_ELEVATOR_MONOLOGUE_TRUST:
            if (CutsceneElevatorMonologue(FALSE))
                finished = TRUE;
            break;

        case CUTSCENE_ELEVATOR_MONOLOGUE_SA_X:
            if (CutsceneElevatorMonologue(FALSE))
                finished = TRUE;
            break;

        case CUTSCENE_ELEVATOR_MONOLOGUE_ANIMALS:
            if (CutsceneElevatorMonologue(TRUE))
                finished = TRUE;
            break;

        case CUTSCENE_ELEVATOR_MONOLOGUE_INCIDENT:
            if (CutsceneElevatorMonologue(FALSE))
                finished = TRUE;
            break;

        case CUTSCENE_MONOLOGUE_FEDERATION:
            if (CutsceneFederationMonologue(0))
                finished = TRUE;
            break;

        case CUTSCENE_SECRET_CONVERSATION:
            if (CutsceneSecretConversation())
                finished = TRUE;
            break;

        case CUTSCENE_RESTRICTED_LAB_DETACHING:
        case CUTSCENE_RESTRICTED_LAB_DETACHING_DYING:
            if (CutsceneRestrictedLabDetaching())
                finished = TRUE;
            break;

        case CUTSCENE_BSL_EXPLODING:
            if (CutsceneBslExploding())
                finished = TRUE;
            break;

        default:
            finished = TRUE;
    }

    return finished;
}

/**
 * @brief 99bac | 8c | Main handler for the elevator monologue cutscenes
 *
 * @param reverseScrolling Whether the elevator scrolls in the opposite direction
 * @return boolu32 Finished
 */
boolu32 CutsceneElevatorMonologue(boolu8 reverseScrolling)
{
    boolu32 finished;

    finished = FALSE;

    switch (CUTSCENE_MONOLOGUE_DATA.stage)
    {
        case 0:
            CUTSCENE_MONOLOGUE_DATA.stage = 1;
            CutsceneElevatorMonologueInit(reverseScrolling);
            break;

        case 1:
            CutsceneMonologueFadeIn();
            if (gWrittenToBldy == 0)
                CUTSCENE_MONOLOGUE_DATA.stage++;
            break;

        case 2:
            if (CutsceneElevatorMonologueProcess())
            {
                CUTSCENE_MONOLOGUE_DATA.stage = 3;
                WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_OBJ);
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
            }
            break;

        case 3:
            CutsceneMonologueFadeOut();
            if (gWrittenToBldy == BLDY_MAX_VALUE)
                finished = TRUE;
            break;
    }

    return finished;
}

/**
 * @brief 99c38 | 22c | Initializes an elevator monologue cutscene
 *
 * @param reverseScrolling Whether the elevator scrolls in the opposite direction
 */
void CutsceneElevatorMonologueInit(boolu8 reverseScrolling)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_9a31c);

    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sElevatorMonologueObjGfxPointers[gCurrentCutscene - 1], VRAM_OBJ + 0x2000);
    LZ77UncompVram(sCutsceneUnk_65fb5c, VRAM_BASE + 0x17C00);
    DMA3_COPY_32(sCutsceneUnk_6638a0, PALRAM_OBJ + 15 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sElevatorMonologueObjPalPointers[gCurrentCutscene - 1], PALRAM_OBJ, 6 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sElevatorMonologueBgGfxPointers[gCurrentCutscene - 1], VRAM_BASE);
    LZ77UncompVram(sElevatorMonologueBgTilemapPointers[gCurrentCutscene - 1], VRAM_BASE + 0xD000);
    LZ77UncompWram(sIntroTilemap_662804, EWRAM_BASE);
    LZ77UncompVram(sCutsceneUnk_663598, VRAM_BASE + 0xD800);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xC800, 0x800 / sizeof(u32));

    DMA3_COPY_32(sCutsceneUnk_6636a0, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sElevatorMonologueBgPalPointers[gCurrentCutscene - 1], PALRAM_BASE, 11 * PAL_ROW_SIZE / sizeof(u32));

    WRITE_16(REG_BG0VOFS, 4);
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 25, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 27, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 26, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_OBJ);

    gWrittenToBldy--;

    CutsceneElevatorMonologueSetupOam(1, 12, 16);
    CutsceneElevatorMonologueSetupOam(2, 120, 120);
    CutsceneElevatorMonologueSetupOam(3, 120, 120);

    if (!reverseScrolling)
        CutsceneElevatorMonologueSetupOam(4, 120, 104);
    else
        CutsceneElevatorMonologueSetupOam(5, 120, 104);

    CUTSCENE_MONOLOGUE_DATA.monologueId = gCurrentCutscene - 1;
    CUTSCENE_MONOLOGUE_DATA.pText = sMonologueTextPointers[gLanguage][CUTSCENE_MONOLOGUE_DATA.monologueId];

    CutsceneMonologueDrawAllOam();
    CallbackSetVBlank(CutsceneElevatorMonologueVblank);
}

/**
 * @brief 99e64 | 3c | Processes an elevator monologue cutscene
 *
 * @return boolu32 Ended
 */
boolu32 CutsceneElevatorMonologueProcess(void)
{
    boolu32 ended;

    ended = CutsceneMonologueProcessSpecialTextCharacters();

    switch (CUTSCENE_MONOLOGUE_DATA.unk_17)
    {
        case 0:
            CUTSCENE_MONOLOGUE_DATA.unk_17 = 100;
            break;

        case 1:
            CUTSCENE_MONOLOGUE_DATA.unk_17 = 100;
            CutsceneMonologueProcessText();
            break;
    }

    CutsceneMonologueProcessOam();
    CutsceneMonologueDrawAllOam();

    return ended;
}

/**
 * @brief 99ea0 | 1e8 | Spawns an OAM for the elevator monologue cutscenes
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot
 */
u8 CutsceneElevatorMonologueSetupOam(u8 type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam); slot++)
    {
        if (CUTSCENE_MONOLOGUE_DATA.oam[slot].type == 0)
            break;
    }

    if (slot >= ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam))
        return ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam);

    CutsceneMonologueResetOam(slot);

    CUTSCENE_MONOLOGUE_DATA.oam[slot].xPosition = xPosition;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].yPosition = yPosition;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].type = type;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].exists = TRUE;

    if (type == 1)
    {
        CUTSCENE_MONOLOGUE_DATA.oam[slot].paletteOffset = 15;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].tileOffset = 0x3E0;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pOam = sCutsceneUnk_663e5c;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pFunction = CutsceneMonologueProcessCursor;
    }
    else if (type == 2)
    {
        CUTSCENE_MONOLOGUE_DATA.oam[slot].priority = 3;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pOam = sElevatorMonologueOam[gCurrentCutscene - 1][0];
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pFunction = (CutsceneMonologueOamFunc_T)unk_9d09c;
    }
    else if (type == 3)
    {
        CUTSCENE_MONOLOGUE_DATA.oam[slot].objMode = 2;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].priority = 3;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pOam = sElevatorMonologueOam[gCurrentCutscene - 1][0];
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pFunction = (CutsceneMonologueOamFunc_T)unk_9d09c;
    }
    else if (type == 4)
    {
        CUTSCENE_MONOLOGUE_DATA.oam[slot].priority = 3;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pOam = sElevatorMonologueOam[gCurrentCutscene - 1][1];
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pFunction = CutsceneProcessElevatorScrolling;
    }
    else if (type == 5)
    {
        CUTSCENE_MONOLOGUE_DATA.oam[slot].priority = 3;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pOam = sElevatorMonologueOam[gCurrentCutscene - 1][1];
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pFunction = unk_9a1a8;
    }

    return slot;
}

/**
 * @brief 9a088 | 120 | Processes the elevator scrolling in the elevator monologue cutscenes
 *
 * @param pOam Cutscene monologue OAM pointer
 */
void CutsceneProcessElevatorScrolling(struct CutsceneMonologueOam* pOam)
{
    pOam->yPosition += 2;

    WRITE_16(REG_BG2VOFS, --CUTSCENE_MONOLOGUE_DATA.bg2YPosition & 0xFFFF);

    if (pOam->stage == 0)
    {
        if (gWrittenToBldy == 0)
        {
            gWrittenToBldalpha_Eva = 0;
            gWrittenToBldalpha_Evb = 16;

            WRITE_16(REG_WININ, 0);
            WRITE_16(REG_WINOUT, 0x331D);

            WRITE_16(REG_BG1VOFS, CUTSCENE_MONOLOGUE_DATA.bg1YPosition = 0);

            WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
            WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1 | DCNT_WINOBJ);

            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (gWrittenToBldalpha_Eva == 10)
        {
            pOam->stage = 2;
            pOam->unk_8 = 0;
        }
        else if (pOam->unk_8 > 3)
        {
            pOam->unk_8 = 0;
            gWrittenToBldalpha_Eva++;
        }
        else
        {
            pOam->unk_8++;
        }

        WRITE_16(REG_BG1VOFS, (CUTSCENE_MONOLOGUE_DATA.bg1YPosition -= 3) & 0xFFFF);
    }
    else
    {
        if (gWrittenToBldalpha_Eva == 4)
        {
            pOam->stage = 1;
            pOam->unk_8 = 0;
        }
        else if (pOam->unk_8 > 3)
        {
            pOam->unk_8 = 0;
            gWrittenToBldalpha_Eva--;
        }
        else
        {
            pOam->unk_8++;
        }

        WRITE_16(REG_BG1VOFS, (CUTSCENE_MONOLOGUE_DATA.bg1YPosition -= 3) & 0xFFFF);
    }
}

/**
 * @brief 9a1a8 | 120 | Processes the elevator scrolling (reversed) in the elevator monologue cutscenes
 *
 * @param pOam Cutscene monologue OAM pointer
 */
void unk_9a1a8(struct CutsceneMonologueOam* pOam)
{
    pOam->yPosition -= 2;

    WRITE_16(REG_BG2VOFS, ++CUTSCENE_MONOLOGUE_DATA.bg2YPosition & 0xFFFF);

    if (pOam->stage == 0)
    {
        if (gWrittenToBldy == 0)
        {
            gWrittenToBldalpha_Eva = 0;
            gWrittenToBldalpha_Evb = 16;

            WRITE_16(REG_WININ, 0);
            WRITE_16(REG_WINOUT, 0x331D);

            WRITE_16(REG_BG1VOFS, CUTSCENE_MONOLOGUE_DATA.bg1YPosition = 0);

            WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
            WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1 | DCNT_WINOBJ);

            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (gWrittenToBldalpha_Eva == 10)
        {
            pOam->stage = 2;
            pOam->unk_8 = 0;
        }
        else if (pOam->unk_8 > 3)
        {
            pOam->unk_8 = 0;
            gWrittenToBldalpha_Eva++;
        }
        else
        {
            pOam->unk_8++;
        }

        WRITE_16(REG_BG1VOFS, (CUTSCENE_MONOLOGUE_DATA.bg1YPosition += 3) & 0xFFFF);
    }
    else
    {
        if (gWrittenToBldalpha_Eva == 4)
        {
            pOam->stage = 1;
            pOam->unk_8 = 0;
        }
        else if (pOam->unk_8 > 3)
        {
            pOam->unk_8 = 0;
            gWrittenToBldalpha_Eva--;
        }
        else
        {
            pOam->unk_8++;
        }

        WRITE_16(REG_BG1VOFS, (CUTSCENE_MONOLOGUE_DATA.bg1YPosition += 3) & 0xFFFF);
    }
}

/**
 * @brief 9a2c8 | 54 | V-blank for the elevator monologue cutscenes
 *
 */
void CutsceneElevatorMonologueVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    unk_9cc4c();

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 9a31c | c | V-blank for the elevator monologue cutscenes while they're loading
 *
 */
void unk_9a31c(void)
{
    UpdateAudio();
}

/**
 * @brief 9a328 | 84 | Main handler for the internal monologue cutscenes
 *
 * @param unused Unused
 * @return boolu32 Finished
 */
boolu32 CutsceneInternalMonologue(u8 unused)
{
    boolu32 finished;

    finished = FALSE;

    switch (CUTSCENE_MONOLOGUE_DATA.stage)
    {
        case 0:
            CUTSCENE_MONOLOGUE_DATA.stage = 1;
            CutsceneInternalMonologueInit(unused);
            break;

        case 1:
            CutsceneMonologueFadeIn();
            if (gWrittenToBldy == 0)
                CUTSCENE_MONOLOGUE_DATA.stage++;
            break;

        case 2:
            if (CutsceneInternalMonologueProcess())
            {
                CUTSCENE_MONOLOGUE_DATA.stage = 3;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
            }
            break;

        case 3:
            CutsceneMonologueFadeOut();
            if (gWrittenToBldy == BLDY_MAX_VALUE)
                finished = TRUE;
            break;
    }

    return finished;
}

/**
 * @brief 9a3ac | 13c | Initializes an internal monologue cutscene
 *
 * @param unused Unused
 */
void CutsceneInternalMonologueInit(u8 unused)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_9a63c);

    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sCutsceneUnk_65fb5c, VRAM_BASE + 0x17C00);
    DMA3_COPY_32(sCutsceneUnk_6638a0, PALRAM_OBJ + 15 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompWram(sIntroTilemap_662804, EWRAM_BASE);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xC800, 0x800 / sizeof(u32));

    DMA3_COPY_32(sCutsceneUnk_6636a0, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    WRITE_16(PALRAM_BASE, 0);

    WRITE_16(REG_BG0VOFS, 4);
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 25, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_OBJ);

    gWrittenToBldy--;

    CutsceneInternalMonologueSetupOam(1, 12, 16);

    CUTSCENE_MONOLOGUE_DATA.monologueId = gCurrentCutscene - 1;
    CUTSCENE_MONOLOGUE_DATA.pText = sMonologueTextPointers[gLanguage][CUTSCENE_MONOLOGUE_DATA.monologueId];

    CutsceneMonologueDrawAllOam();
    CallbackSetVBlank(CutsceneInternalMonologueVblank);
}

/**
 * @brief 9a4e8 | 3c | Processes an internal monologue cutscene
 *
 * @return boolu32 Ended
 */
boolu32 CutsceneInternalMonologueProcess(void)
{
    boolu32 ended;

    ended = CutsceneMonologueProcessSpecialTextCharacters();

    switch (CUTSCENE_MONOLOGUE_DATA.unk_17)
    {
        case 0:
            CUTSCENE_MONOLOGUE_DATA.unk_17 = 100;
            break;

        case 1:
            CUTSCENE_MONOLOGUE_DATA.unk_17 = 100;
            CutsceneMonologueProcessText();
            break;
    }

    CutsceneMonologueProcessOam();
    CutsceneMonologueDrawAllOam();

    return ended;
}

/**
 * @brief 9a524 | e0 | Spawns an OAM for the internal monologue cutscenes
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot
 */
u8 CutsceneInternalMonologueSetupOam(u8 type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam); slot++)
    {
        if (CUTSCENE_MONOLOGUE_DATA.oam[slot].type == 0)
            break;
    }

    if (slot >= ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam))
        return ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam);

    CutsceneMonologueResetOam(slot);

    CUTSCENE_MONOLOGUE_DATA.oam[slot].xPosition = xPosition;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].yPosition = yPosition;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].type = type;
    CUTSCENE_MONOLOGUE_DATA.oam[slot].exists = TRUE;

    if (type == 1)
    {
        CUTSCENE_MONOLOGUE_DATA.oam[slot].priority = 2;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].paletteOffset = 15;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].tileOffset = 0x3E0;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pOam = sCutsceneUnk_663e5c;
        CUTSCENE_MONOLOGUE_DATA.oam[slot].pFunction = CutsceneMonologueProcessCursor;
    }

    return slot;
}

/**
 * @brief 9a604 | 38 | V-blank for the internal monologue cutscenes
 *
 */
void CutsceneInternalMonologueVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    unk_9cc4c();

    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 9a63c | c | V-blank for the internal monologue cutscenes while they're loading
 *
 */
void unk_9a63c(void)
{
    UpdateAudio();
}

/**
 * @brief 9a648 | 84 | Main handler for the federation monologue cutscene
 *
 * @param unused Unused
 * @return boolu32 Finished
 */
boolu32 CutsceneFederationMonologue(u8 unused)
{
    boolu32 finished;

    finished = FALSE;

    switch (CUTSCENE_MONOLOGUE_DATA.stage)
    {
        case 0:
            CUTSCENE_MONOLOGUE_DATA.stage = 1;
            CutsceneFederationMonologueInit(unused);
            break;

        case 1:
            CutsceneMonologueFadeIn();
            if (gWrittenToBldy == 0)
                CUTSCENE_MONOLOGUE_DATA.stage++;
            break;

        case 2:
            if (CutsceneFederationMonologueProcess())
            {
                CUTSCENE_MONOLOGUE_DATA.stage = 3;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
            }
            break;

        case 3:
            CutsceneMonologueFadeOut();
            if (gWrittenToBldy == BLDY_MAX_VALUE)
                finished = TRUE;
            break;
    }

    return finished;
}

/**
 * @brief 9a6cc | 17c | Initializes the federation monologue cutscene
 *
 * @param unused Unused
 */
void CutsceneFederationMonologueInit(u8 unused)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_9a99c);

    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sCutsceneUnk_65fb5c, VRAM_BASE + 0x17C00);
    DMA3_COPY_32(sCutsceneUnk_6638a0, PALRAM_OBJ + 15 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sCutsceneUnk_6724c0, VRAM_BASE);
    LZ77UncompVram(sCutsceneUnk_674ad8, VRAM_BASE + 0xD000);
    LZ77UncompWram(sIntroTilemap_662804, EWRAM_BASE);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xC800, 0x800 / sizeof(u32));

    DMA3_COPY_32(sCutsceneUnk_674958, PALRAM_BASE, 12 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sIntroPal_663820, PALRAM_BASE + 12 * PAL_ROW_SIZE, 4 * PAL_ROW_SIZE / sizeof(u32));
    WRITE_16(PALRAM_BASE, 0);

    WRITE_16(REG_BG0VOFS, 4);
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 25, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 26, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_OBJ);

    gWrittenToBldy--;

    CutsceneFederationMonologueSetupOam(1, 12, 16);

    CUTSCENE_MONOLOGUE_DATA.monologueId = gCurrentCutscene - 1;
    CUTSCENE_MONOLOGUE_DATA.pText = sMonologueTextPointers[gLanguage][CUTSCENE_MONOLOGUE_DATA.monologueId];

    CutsceneMonologueDrawAllOam();
    CallbackSetVBlank(CutsceneFederationMonologueVblank);
}
