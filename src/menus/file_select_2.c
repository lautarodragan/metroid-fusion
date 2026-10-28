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
