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
#include "data/text_data.h"
#include "text.h"
#include "syscalls.h"

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

            pText = sFileSelectUnk_79ec84[gLanguage][0];
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
        DMA3_COPY_32(sFileSelectUnk_73db64, dst, 8);
        dst += 8;
    }

    if (tankDigits[1] == 1)
    {
        if (i == 10)
            dst -= 0x4A0 / 4;

        if (tankDigits[2] == tankDigits[0])
        {
            DMA3_COPY_32(sFileSelectUnk_73db04, dst, 8);
        }
        else
        {
            DMA3_COPY_32(sFileSelectUnk_73db44, dst, 8);
        }

        i += 2;
        dst += 8;
    }

    for (; i < tankDigits[2] - tankDigits[3]; i += 2)
    {
        if (i == 10)
            dst -= 0x4A0 / 4;
        DMA3_COPY_32(sFileSelectUnk_73db24, dst, 8);
        dst += 8;
    }

    if (tankDigits[3] == 1 && i < tankDigits[2])
    {
        if (i == 10)
            dst -= 0x4A0 / 4;
        DMA3_COPY_32(sFileSelectUnk_73dae4, dst, 8);
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
