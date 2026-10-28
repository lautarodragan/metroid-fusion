#include "cutscenes/secret_conversation.h"
#include "cutscenes/cutscene_common.h"

#include "audio_wrappers.h"
#include "callbacks.h"
#include "gba.h"
#include "globals.h"
#include "macros.h"
#include "oam.h"
#include "syscalls.h"

#include "audio/track_internal.h"

#include "data/cutscenes_data.h"

#include "structs/cutscene_data.h"

/**
 * @brief 9a848 | 3c | Processes the federation monologue cutscene
 *
 * @return boolu32 Ended
 */
boolu32 CutsceneFederationMonologueProcess(void)
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
 * @brief 9a884 | e0 | Sets up an OAM object for the federation monologue cutscene
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot
 */
u8 CutsceneFederationMonologueSetupOam(u8 type, u16 xPosition, u16 yPosition)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam); i++)
    {
        if (!CUTSCENE_MONOLOGUE_DATA.oam[i].type)
            break;
    }

    if (i >= ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam))
        return ARRAY_SIZE(CUTSCENE_MONOLOGUE_DATA.oam);

    CutsceneMonologueResetOam(i);

    CUTSCENE_MONOLOGUE_DATA.oam[i].xPosition = xPosition;
    CUTSCENE_MONOLOGUE_DATA.oam[i].yPosition = yPosition;
    CUTSCENE_MONOLOGUE_DATA.oam[i].type = type;
    CUTSCENE_MONOLOGUE_DATA.oam[i].exists = TRUE;

    if (type == 1)
    {
        CUTSCENE_MONOLOGUE_DATA.oam[i].priority = 0;
        CUTSCENE_MONOLOGUE_DATA.oam[i].paletteOffset = 15;
        CUTSCENE_MONOLOGUE_DATA.oam[i].tileOffset = 0x3E0;
        CUTSCENE_MONOLOGUE_DATA.oam[i].pOam = sCutsceneMonologueCursorHiddenOam;
        CUTSCENE_MONOLOGUE_DATA.oam[i].pFunction = CutsceneMonologueProcessCursor;
    }

    return i;
}

/**
 * @brief 9a964 | 38 | V-blank code for the federation monologue cutscene
 *
 */
void CutsceneFederationMonologueVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    unk_9cc4c();
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 9a99c | c | Loading V-blank code for the federation monologue cutscene
 *
 */
void unk_9a99c(void)
{
    UpdateAudio();
}

/**
 * @brief 9a9a8 | 84 | Main handler for the secret conversation cutscene
 *
 * @return boolu32 Ended
 */
boolu32 CutsceneSecretConversation(void)
{
    boolu32 ended;

    ended = FALSE;

    switch (CUTSCENE_DATA.stage)
    {
        case 0:
            CUTSCENE_DATA.stage = 1;
            CutsceneSecretConversationInit();
            break;

        case 1:
            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                CUTSCENE_DATA.stage = 2;
            break;

        case 2:
            if (CutsceneSecretConversationProcess())
            {
                CUTSCENE_DATA.stage = 3;
                WRITE_16(REG_DISPCNT, DCNT_BG1 | DCNT_BG2 | DCNT_OBJ);
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
            }
            break;

        case 3:
            CutsceneFadeOut();
            if (gWrittenToBldy == BLDY_MAX_VALUE)
                ended = TRUE;
            break;
    }

    return ended;
}

/**
 * @brief 9aa2c | 138 | Initializes the secret conversation cutscene
 *
 */
void CutsceneSecretConversationInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_9ae0c);

    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sCutsceneSecretConversationObjGfx, VRAM_BASE + 0x14000);
    DMA3_COPY_32(sCutsceneSecretConversationObjPal, PALRAM_BASE + 0x300, 0x10);

    LZ77UncompVram(sCutsceneSecretConversationBgGfx, VRAM_BASE + 0x800);
    LZ77UncompVram(sCutsceneSecretConversationBg1Tilemap, VRAM_BASE + 0xC000);
    LZ77UncompVram(sCutsceneSecretConversationBg2Tilemap, VRAM_BASE + 0xC800);

    DMA3_COPY_32(sCutsceneSecretConversationBgPal, PALRAM_BASE, 0x28);
    DMA3_COPY_32(sCutsceneSecretConversationAnimatedPal0, PALRAM_BASE + 0x1E0, 8);

    CutsceneSecretConversationSetupOam(1, 120, 128);
    CutsceneSecretConversationSetupOam(2, 120, 128);
    CutsceneSecretConversationSetupOam(3, 120, 128);

    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 24, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 25, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_DISPCNT, DCNT_BG1 | DCNT_BG2 | DCNT_OBJ);
    gWrittenToBldy--;

    CutsceneDrawAllOam();
    CallbackSetVBlank(CutsceneSecretConversationVblank);
}

/**
 * @brief 9ab64 | 64 | Processes the secret conversation cutscene
 *
 * @return boolu32 Ended
 */
boolu32 CutsceneSecretConversationProcess(void)
{
    boolu32 ended;

    ended = FALSE;

    switch (CUTSCENE_DATA.subStage)
    {
        case 0:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.timer >= 30)
            {
                CUTSCENE_DATA.subStage = 1;
                CUTSCENE_DATA.timer = 0;
                CutsceneSecretConversationSetupOam(4, 120, 68);
                CutsceneProcessOam();
            }
            CutsceneDrawAllOam();
            break;

        case 1:
            CutsceneProcessOam();
            CutsceneDrawAllOam();
            break;

        case 2:
            CutsceneProcessOam();
            CutsceneDrawAllOam();
            ended = TRUE;
            break;
    }

    return ended;
}

/**
 * @brief 9abc8 | 10c | Sets up an OAM object for the secret conversation cutscene
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot
 */
u8 CutsceneSecretConversationSetupOam(u8 type, u16 xPosition, u16 yPosition)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(CUTSCENE_DATA.oam); i++)
    {
        if (!CUTSCENE_DATA.oam[i].type)
            break;
    }

    if (i >= ARRAY_SIZE(CUTSCENE_DATA.oam))
        return ARRAY_SIZE(CUTSCENE_DATA.oam);

    DMA3_FILL_32(0, &CUTSCENE_DATA.oam[i], sizeof(CUTSCENE_DATA.oam[i]));

    CUTSCENE_DATA.oam[i].xPosition = xPosition;
    CUTSCENE_DATA.oam[i].yPosition = yPosition;
    CUTSCENE_DATA.oam[i].type = type;
    CUTSCENE_DATA.oam[i].exists = TRUE;

    if (type == 1)
    {
        CUTSCENE_DATA.oam[i].pOam = sCutsceneSecretConversationOam_6793b0;
        CUTSCENE_DATA.oam[i].pFunction = unk_9db70;
    }
    else if (type == 2)
    {
        CUTSCENE_DATA.oam[i].pOam = sCutsceneSecretConversationNavigationPanelOam_679280;
        CUTSCENE_DATA.oam[i].pFunction = CutsceneSecretConversationProcessNavigationPanel;
    }
    else if (type == 3)
    {
        CUTSCENE_DATA.oam[i].pOam = sCutsceneSecretConversationOam_6793a0;
        CUTSCENE_DATA.oam[i].pFunction = unk_9db70;
    }
    else if (type == 4)
    {
        CUTSCENE_DATA.oam[i].pOam = sCutsceneSecretConversationIncomingDispatchOam_6792d0;
        CUTSCENE_DATA.oam[i].pFunction = CutsceneSecretConversationProcessIncomingDispatch;
    }

    return i;
}

/**
 * @brief 9acd4 | 20 | Processes the navigation panel in the secret conversation cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void CutsceneSecretConversationProcessNavigationPanel(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->stage = 1;
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->pOam = sCutsceneSecretConversationNavigationPanelOam_6792a8;
    }
}

/**
 * @brief 9acf4 | 70 | Processes the "incoming dispatch" message in the secret conversation cutscene
 *
 * @param pOam Cutscene OAM data pointer
 */
void CutsceneSecretConversationProcessIncomingDispatch(struct CutsceneOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->stage == 0)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];

        if (pOam->unk_13 == 0)
        {
            SoundPlay(0x22F);
            pOam->unk_13 = 1;
        }

        if (pFrame[0].timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->stage = 1;
            pOam->unk_13 = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sCutsceneSecretConversationIncomingDispatchOam_679350;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_13++;
        if (pOam->unk_13 == 180)
        {
            pOam->stage = 2;
            pOam->unk_13 = 0;
            CUTSCENE_DATA.subStage = 2;
        }
    }
}

/**
 * @brief 9ad64 | a8 | V-blank code for the secret conversation cutscene
 *
 */
void CutsceneSecretConversationVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    CUTSCENE_DATA.unk_11++;
    switch (CUTSCENE_DATA.unk_11)
    {
        case 7:
            DMA3_COPY_32(sCutsceneSecretConversationAnimatedPal1, PALRAM_BASE + 0x1E0, 8);
            break;

        case 14:
            DMA3_COPY_32(sCutsceneSecretConversationAnimatedPal2, PALRAM_BASE + 0x1E0, 8);
            break;

        case 21:
            DMA3_COPY_32(sCutsceneSecretConversationAnimatedPal3, PALRAM_BASE + 0x1E0, 8);
            break;

        case 28:
            DMA3_COPY_32(sCutsceneSecretConversationAnimatedPal0, PALRAM_BASE + 0x1E0, 8);
            CUTSCENE_DATA.unk_11 = 0;
            break;
    }
}

/**
 * @brief 9ae0c | c | Loading V-blank code for the secret conversation cutscene
 *
 */
void unk_9ae0c(void)
{
    UpdateAudio();
}
