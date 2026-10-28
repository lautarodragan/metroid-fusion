#include "menus/file_select.h"
#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "oam.h"
#include "init_helpers.h"
#include "audio_wrappers.h"

#include "data/menus/file_select_data.h"

#include "constants/audio.h"
#include "constants/game_state.h"
#include "constants/menus/file_select.h"

#include "structs/save_file.h"

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
            pOam->pOam = sFileSelectUnk_740a48;
            pOam->unk_9 = 0;
        }
        else if (FILE_SELECT_DATA.subroutine == 5 || FILE_SELECT_DATA.subroutine == 7 ||
            FILE_SELECT_DATA.subroutine == 12 || FILE_SELECT_DATA.subroutine == 13)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectUnk_740a70;
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
                pOam->pOam = sFileSelectUnk_740b70;
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
                pOam->pOam = sFileSelectUnk_740b70;

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
            pOam->pOam = sFileSelectUnk_740b48;
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

        pOam->pOam = sFileSelectUnk_79e8a4[FILE_SELECT_DATA.selectedFile][FILE_SELECT_DATA.unk_F];

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
                pOam->xPosition = sFileSelectUnk_73dbb0[gLanguage][1];
                SoundPlay(SOUND_1FA);
            }
        }
        else if (FILE_SELECT_DATA.unk_10 == 1)
        {
            if (gChangedInput & KEY_LEFT)
            {
                FILE_SELECT_DATA.unk_10 = 0;
                pOam->xPosition = sFileSelectUnk_73dbb0[gLanguage][0];
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
                pOam->pOam = sFileSelectUnk_740b70;
                pOam->unk_9 = 1;
            }
            else
            {
                SoundPlay(SOUND_1FB);
                pOam->pOam = sFileSelectUnk_740b70;
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
                pOam->xPosition = sFileSelectUnk_73dbbe[gLanguage][1];
                SoundPlay(SOUND_1FA);
            }
        }
        else if (FILE_SELECT_DATA.unk_10 == 1)
        {
            if (gChangedInput & KEY_LEFT)
            {
                FILE_SELECT_DATA.unk_10 = 0;
                pOam->xPosition = sFileSelectUnk_73dbbe[gLanguage][0];
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
                pOam->pOam = sFileSelectUnk_740b70;
                pOam->unk_9 = 1;
            }
            else
            {
                SoundPlay(SOUND_1FB);
                pOam->pOam = sFileSelectUnk_740b70;
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
            pOam->pOam = sFileSelectUnk_7407c0;
            if (gChangedInput & KEY_RIGHT)
            {
                pOam->unk_9 = 1;
                pOam->pOam = sFileSelectUnk_7407d0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                DoSoundAction(0x2000000);
                SoundPlay(SOUND_206);
            }
        }
        else if (pOam->unk_9 == 1)
        {
            pOam->pOam = sFileSelectUnk_7407d0;
            if (gChangedInput & KEY_LEFT)
            {
                pOam->unk_9 = 0;
                pOam->pOam = sFileSelectUnk_7407c0;
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
            pOam->pOam = sFileSelectUnk_7407e0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
        else if (pOam->unk_9 == 1)
        {
            pOam->pOam = sFileSelectUnk_7407f0;
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
        pOam->pOam = sFileSelectUnk_79e890[FILE_SELECT_DATA.selectedFile];
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

    pOam->pOam = sFileSelectUnk_7408e0;

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
            pOam->pOam = sUnk_7408d0;
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
            pOam->pOam = sFileSelectUnk_740940;
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
                pOam->pOam = sFileSelectUnk_740950;
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
            pOam->pOam = sFileSelectUnk_7409a0;
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
                pOam->pOam = sFileSelectUnk_7409b0;
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
            pOam->pOam = sFileSelectUnk_7409a0;
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
                pOam->pOam = sFileSelectUnk_7409b0;
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
            pOam->pOam = sFileSelectUnk_7409a0;
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
            pOam->pOam = sFileSelectUnk_7409b0;
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
                pOam->pOam = sFileSelectUnk_740b70;
                pOam->unk_9 = 100;
            }
            else
            {
                pOam->pOam = sFileSelectUnk_740b70;
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
