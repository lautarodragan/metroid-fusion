#include "menus/navigation_conversation.h"
#include "compiler_tricks.h"
#include "menus/pause_screen.h"
#include "menus/pause_screen_map.h"
#include "menus/pause_screen_text.h"

#include "gba.h"
#include "globals.h"
#include "io.h"
#include "dma.h"
#include "audio_wrappers.h"
#include "sound_event.h"
#include "text.h"
#include "new_file_intro.h"

#include "constants/audio.h"
#include "constants/event.h"
#include "constants/menus/pause_screen.h"

#include "data/event_data.h"
#include "data/menus/pause_screen_misc_data.h"

#include "structs/connection.h"
#include "structs/event.h"
#include "structs/menus/pause_screen.h"
#include "structs/minimap.h"

// Called without a prototype in the original code (the character isn't truncated to a u8),
// music_wrappers.h isn't included for that reason
void PlayCharacterAppearingSound();

// Defined in music_wrappers.h
void PlayMusic(u16 musicTrack, u8 priority);
void PlayMusicOrSoundFromId(u16 sound, u8 arg1);
void StopMusicOrSoundFromId(u16 sound, u8 arg1);

#define NAV_TEXT_TIMER(slot) (PAUSE_SCREEN_DATA.unk_E[(slot)])
#define NAV_TEXT_POS(slot) ((&PAUSE_SCREEN_DATA.unk_E[2])[(slot)])

/**
 * @brief 79afc | 600 | Processes the text of a navigation conversation
 *
 */
void NavigationConversationProcessText(void)
{
    u8* dst;
    u32 skipping;
    u16* pText;
    s32 result;
    s32 position;
    u32 character;
    u16 type;
    u32 value;

    if (PAUSE_SCREEN_DATA.unk_17)
    {
        if (!(PAUSE_SCREEN_DATA.typeFlags & 0x10))
            return;
    }
    else if (!(PAUSE_SCREEN_DATA.typeFlags & 0x8))
    {
        return;
    }

    if (PAUSE_SCREEN_DATA.unk_18)
        dst = VRAM_BASE + 0x6000;
    else
        dst = VRAM_BASE + 0x7000;

    skipping = FALSE;

    if (NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) == 0xFC00)
    {
        if (!(gChangedInput & (KEY_A | KEY_B | KEY_DOWN)))
            return;

        SoundPlay(SOUND_203);
        NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0;
        if (NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) > 0xE0)
            TextClearGraphics(2);

        NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) = 0xE0;
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 11;
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
        return;
    }
    else if (NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) == 0xFE00)
    {
        NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0;
        if (NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) > 0xE0)
            TextClearGraphics(2);

        NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) = 0xE0;
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 11;
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
        return;
    }
    else if (NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) == 0xFD00)
    {
        if (!(gChangedInput & (KEY_A | KEY_B | KEY_DOWN)))
            return;

        SoundPlay(SOUND_203);
        NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0;
        TextClearGraphics(1);
        NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) = 0;
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 11;
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
        return;
    }
    else if (NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) == 0xE001)
    {
        if (!(PAUSE_SCREEN_DATA.typeFlags & 0x400))
            NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0;
        return;
    }

    if (PAUSE_SCREEN_DATA.unk_1F != 0)
    {
        PAUSE_SCREEN_DATA.unk_1F--;
        return;
    }

    if (PAUSE_SCREEN_DATA.unk_1A && !(gButtonInput & (KEY_A | KEY_B | KEY_DOWN)))
        PAUSE_SCREEN_DATA.unk_1A = FALSE;

    NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18)++;

    if (gButtonInput & (KEY_A | KEY_B | KEY_DOWN) && !PAUSE_SCREEN_DATA.unk_1A)
        skipping = TRUE;
    else if (NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) < PAUSE_SCREEN_DATA.unk_1D)
        return;

    NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0;

    result = (PAUSE_SCREEN_DATA.conversationNumber - 1) * 2;
    if (PAUSE_SCREEN_DATA.conversationNumber == gPreviousNavigationConversation)
        result++;

    pText = sNavConversationTextPointers[gLanguage][result];
    pText += PAUSE_SCREEN_DATA.unk_C;
    PAUSE_SCREEN_DATA.unk_C++;

    while (TRUE)
    {
        result = 0;
        character = *pText >> 12;
        type = *pText & 0xFF00;

        switch (character)
        {
            case 15:
                if (*pText == 0xFF00)
                {
                    PAUSE_SCREEN_DATA.unk_1C = 1;
                    PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 3;
                    result = 2;
                }
                else if (*pText == 0xFE00)
                {
                    NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0xFE00;
                    result = 1;
                }
                else if (*pText == 0xFD00)
                {
                    NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0xFD00;
                    PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 3;
                    PAUSE_SCREEN_DATA.unk_1A = TRUE;
                    result = 2;
                }
                else if (*pText == 0xFC00)
                {
                    NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0xFC00;
                    PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 3;
                    PAUSE_SCREEN_DATA.unk_1A = TRUE;
                    result = 2;
                }
                else if (*pText == 0xFB00)
                {
                    PAUSE_SCREEN_DATA.unk_1C = 2;
                    PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 3;
                    result = 2;
                }
                break;

            case 14:
                if (type == 0xE000)
                {
                    if (*pText == 0xE000)
                    {
                        if (PAUSE_SCREEN_DATA.typeFlags & 0x200)
                            PAUSE_SCREEN_DATA.typeFlags |= 0x400;
                    }
                    else if (*pText == 0xE001)
                    {
                        NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0xE001;
                    }
                }
                else if (type == 0xE100)
                {
                    PAUSE_SCREEN_DATA.unk_1F = *pText;
                }
                else if (type == 0xE200)
                {
                    if (*pText == 0xE201)
                    {
                        PAUSE_SCREEN_DATA.typeFlags |= 0x2;
                        PAUSE_SCREEN_DATA.unk_18 = 1;
                        PAUSE_SCREEN_DATA.unk_19 = 2;
                    }
                    else if (*pText == 0xE202)
                    {
                        PAUSE_SCREEN_DATA.typeFlags |= 0x4;
                        PAUSE_SCREEN_DATA.unk_18 = 1;
                        PAUSE_SCREEN_DATA.unk_19 = 2;
                    }
                    else
                    {
                        PAUSE_SCREEN_DATA.typeFlags |= 0x1;
                        PAUSE_SCREEN_DATA.unk_18 = 0;
                        PAUSE_SCREEN_DATA.unk_19 = 1;
                    }
                    PAUSE_SCREEN_DATA.unk_17 = *pText;
                }
                else if (type == 0xE300)
                {
                    if (*pText == 0xE300)
                        PAUSE_SCREEN_DATA.typeFlags |= 0x40;
                    else if (*pText == 0xE301)
                        PAUSE_SCREEN_DATA.typeFlags &= ~0x40;
                }
                result = 1;
                break;

            case 12:
                PAUSE_SCREEN_DATA.unk_1C = 6;
                result = 1;
                break;

            case 11:
                if (*pText == 0xB001)
                {
                    PAUSE_SCREEN_DATA.unk_264 = TRUE;
                    result = 1;
                }
                else if (*pText == 0xB002)
                {
                    PAUSE_SCREEN_DATA.unk_264 = TRUE;
                    result = 1;
                }
                else if (*pText == 0xB003)
                {
                    if (PAUSE_SCREEN_DATA.unk_1C != 5 && PAUSE_SCREEN_DATA.unk_1C != 3)
                    {
                        PlayMusic(MUSIC_SILENCE_1_SHIP, 2);
                        SoundEventUpdate(0, SEVENT_TTYPE_ROOM_EVENT);
                    }
                    result = 3;
                }
                break;

            case 10:
                result = PAUSE_SCREEN_DATA.conversationOnRepeat != 0;
                StopMusicOrSoundFromId(*pText & 0xFFF, result);
                result = 3;
                break;

            case 9:
                result = PAUSE_SCREEN_DATA.conversationOnRepeat != 0;
                PlayMusicOrSoundFromId(*pText & 0xFFF, result);
                result = 3;
                break;

            case 8:
                if (type == 0x8000)
                {
                    NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) += *pText & 0xFF;
                }
                else if (type == 0x8100)
                {
                    PAUSE_SCREEN_DATA.unk_1E = *pText;
                }
                else if (type == 0x8200)
                {
                    PAUSE_SCREEN_DATA.unk_1D = *pText;
                    if (PAUSE_SCREEN_DATA.unk_1D == 0)
                        PAUSE_SCREEN_DATA.unk_1D = 8;
                }
                else if (type == 0x8300)
                {
                    if (NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) >= 0xE0)
                        NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) = 0xE0;
                    else
                        NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) = 0;

                    NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) += *(u8*)pText;
                }
                result = 3;
                break;
        }

        if (result != 3)
            break;

        PAUSE_SCREEN_DATA.unk_C++;
        pText++;
    }

    if (result == 2)
    {
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
        return;
    }

    if (result == 1)
        return;

    PAUSE_SCREEN_DATA.navConvCharacterWidth = value = TextGetCharacterWidth(*pText);

    result = NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) + PAUSE_SCREEN_DATA.navConvCharacterWidth;
    if (result > 0x1C0)
    {
        TextClearGraphics(2);
        NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) = 0xE0;
    }
    else if (result > 0xE0 && NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) < 0xE0)
    {
        NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) = 0xE0;
    }

    value = NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18);
    if (value == 0 || value == 0xE0)
        NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) = value;

    result = NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18);
    if (NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) >= 0xE0)
    {
        dst += 0x800;
        result -= 0xE0;
    }

    result = (result >> 3) * 32;
    dst += result;
    position = NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) & 7;

    TextDrawCharacter(*pText, (u32*)dst, PAUSE_SCREEN_DATA.navConvCharacterWidth, position, PAUSE_SCREEN_DATA.unk_1E);

    if (!skipping && *pText != 0x40)
    {
        if (PAUSE_SCREEN_DATA.unk_17 == 1)
        {
            PlayCharacterAppearingSound(*pText, 0x21);
            PAUSE_SCREEN_DATA.unk_1B = 2;
        }
        else if (PAUSE_SCREEN_DATA.unk_17 == 2)
        {
            PlayCharacterAppearingSound(*pText, 0x41);
            PAUSE_SCREEN_DATA.unk_1B = 3;
        }
        else
        {
            PlayCharacterAppearingSound(*pText, 0x1);
            PAUSE_SCREEN_DATA.unk_1B = 1;
        }
    }

    result = TRUE;
    value = pText[1];
    if (value & 0x8000)
        result = (value & 0xF000) != 0xF000;

    if (result)
        NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) += PAUSE_SCREEN_DATA.navConvCharacterWidth;
}

/**
 * @brief 7a0fc | 1e0 | Processes the text of a message during a navigation conversation
 * 
 * @param messageId Message ID
 * @return bool, ended
 */
u32 unk_7a0fc(u8 messageId)
{
    u32 ended;
    u32 secondLine;
    u16* pText;
    u8* dst;
    s32 position;

    if (!(PAUSE_SCREEN_DATA.typeFlags & 0x8))
        return FALSE;

    ended = FALSE;
    secondLine = FALSE;

    while (TRUE)
    {
        pText = sMessageTextPointers[gLanguage][messageId + 43];
        dst = VRAM_BASE + 0x7000;
        pText += PAUSE_SCREEN_DATA.unk_21;
        if (*pText == 0xFE00)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent = 0xE0;
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if ((*pText & 0xFF00) == 0x8000)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent += *(u8*)pText;
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if ((*pText & 0xFF00) == 0x8300)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            if (PAUSE_SCREEN_DATA.navConvTextIndent >= 0xE0)
                PAUSE_SCREEN_DATA.navConvTextIndent = 0xE0;
            else
                PAUSE_SCREEN_DATA.navConvTextIndent = 0;

            PAUSE_SCREEN_DATA.navConvTextIndent += *(u8*)pText;
            if (*pText == 0x83A0)
                PAUSE_SCREEN_DATA.navConvTextIndent -= 0x10;
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if (!secondLine)
        {
            if (*pText != 0x40 && PAUSE_SCREEN_DATA.navConvTextIndent < 0xE0)
            {
                if (PAUSE_SCREEN_DATA.unk_1A && !(gButtonInput & (KEY_A | KEY_B | KEY_DOWN)))
                    PAUSE_SCREEN_DATA.unk_1A = FALSE;

                PAUSE_SCREEN_DATA.unk_20++;
                if (!(gButtonInput & (KEY_A | KEY_B | KEY_DOWN)) || PAUSE_SCREEN_DATA.unk_1A)
                {
                    if (PAUSE_SCREEN_DATA.unk_20 < 8)
                        return ended;
                }
            }
            PAUSE_SCREEN_DATA.unk_20 = 0;
        }

        PAUSE_SCREEN_DATA.navConvCharacterWidth = TextGetCharacterWidth(*pText);

        if (PAUSE_SCREEN_DATA.navConvTextIndent + PAUSE_SCREEN_DATA.navConvCharacterWidth > 0xE0 &&
            PAUSE_SCREEN_DATA.navConvTextIndent < 0xE0)
            PAUSE_SCREEN_DATA.navConvTextIndent = 0xE0;

        position = PAUSE_SCREEN_DATA.navConvTextIndent;
        if (position == 0 || position == 0xE0)
            PAUSE_SCREEN_DATA.navConvTextIndent = position;

        if (*pText != 0x40)
        {
            PlayCharacterAppearingSound(*pText, 1);

            position = PAUSE_SCREEN_DATA.navConvTextIndent;
            if (PAUSE_SCREEN_DATA.navConvTextIndent >= 0xE0)
            {
                secondLine = TRUE;
                dst += 0x800;
                position -= 0xE0;
            }
            dst += (position >> 3) * 32;

            position = PAUSE_SCREEN_DATA.navConvTextIndent & 7;
            TextDrawCharacter(*pText, (u32*)dst, PAUSE_SCREEN_DATA.navConvCharacterWidth, position, 0);
        }

        PAUSE_SCREEN_DATA.navConvTextIndent += PAUSE_SCREEN_DATA.navConvCharacterWidth;
        PAUSE_SCREEN_DATA.unk_21++;

        if (pText[1] == 0xFF00)
            ended = TRUE;

        if (!secondLine || ended)
            break;
    }

    return ended;
}

/**
 * @brief 7a2dc | c8 | Gets the current navigation conversation
 * 
 */
void NavigationConversationGetCurrentConversation(void)
{
    s32 i;

    for (i = gEventCounter; i > 0; i--)
    {
        if (sEventLocationAndNavigationInfo[i].navConversation != 0)
            break;
    }

    PAUSE_SCREEN_DATA.conversationNumber = sEventLocationAndNavigationInfo[i].navConversation;

    if (PAUSE_SCREEN_DATA.conversationNumber == gPreviousNavigationConversation)
        PAUSE_SCREEN_DATA.conversationOnRepeat = TRUE;
    else
        PAUSE_SCREEN_DATA.conversationOnRepeat = FALSE;

    TextClearGraphics(0);
    NavigationConversationUpdateTarget(TRUE);
    NavigationConversationSetupOam();

    PAUSE_SCREEN_DATA.unk_238 = 0;
    PAUSE_SCREEN_DATA.unk_239 = 0;
    PAUSE_SCREEN_DATA.unk_23C = 0;
    PAUSE_SCREEN_DATA.unk_23D = 0;
    PAUSE_SCREEN_DATA.unk_250 = 0;
    PAUSE_SCREEN_DATA.unk_251 = 0;
    PAUSE_SCREEN_DATA.unk_252 = 0;
}

/**
 * @brief 7a3a4 | ab0 | Handles a navigation conversation
 *
 * @return u32 bool, ended
 */
u32 NavigationConversationHandler(void)
{
    u32 ended;
    // Used as the text pointer index, the first character of the text and the menu action
    s32 temp;

    unk_7b674();
    NavigationConversionScrollToTarget();
    unk_7b56c();
    NavConversationUpdateBottomTextBoxOam();
    NavConversationUpdateTopTextBoxOam();

    ended = FALSE;

    switch (PAUSE_SCREEN_DATA.subMenuStage)
    {
        case 0:
            PAUSE_SCREEN_DATA.timer = 0;
            NavigationConversationSetupOam();
            if (PAUSE_SCREEN_DATA.conversationOnRepeat)
            {
                PAUSE_SCREEN_DATA.unk_1C = 4;
                PAUSE_SCREEN_DATA.subMenuStage = 17;
                break;
            }

            PAUSE_SCREEN_DATA.unk_1C = 0;
            PAUSE_SCREEN_DATA.subMenuStage++;
            break;

        case 1:
            PAUSE_SCREEN_DATA.dispcnt |= DCNT_BG0;
            PAUSE_SCREEN_DATA.unk_9 = 1;
            PAUSE_SCREEN_DATA.unk_B = 1;
            PAUSE_SCREEN_DATA.unk_1D = 8;
            PAUSE_SCREEN_DATA.unk_1E = 0;
            PAUSE_SCREEN_DATA.unk_1F = 0;

            temp = (PAUSE_SCREEN_DATA.conversationNumber - 1) * 2;
            if (PAUSE_SCREEN_DATA.conversationOnRepeat)
                temp++;

            temp = sNavConversationTextPointers[gLanguage][temp][0];
            if (temp == 0xE201)
            {
                PAUSE_SCREEN_DATA.typeFlags |= 2;
                PAUSE_SCREEN_DATA.unk_18 = 1;
                PAUSE_SCREEN_DATA.unk_19 = 2;
                PAUSE_SCREEN_DATA.unk_17 = 1;
            }
            else if (temp == 0xE202)
            {
                PAUSE_SCREEN_DATA.typeFlags |= 4;
                PAUSE_SCREEN_DATA.unk_18 = 1;
                PAUSE_SCREEN_DATA.unk_19 = 2;
                PAUSE_SCREEN_DATA.unk_17 = 2;
            }
            else
            {
                PAUSE_SCREEN_DATA.typeFlags |= 1;
                PAUSE_SCREEN_DATA.unk_18 = 0;
                PAUSE_SCREEN_DATA.unk_19 = 1;
                PAUSE_SCREEN_DATA.unk_17 = 0;
            }

            PAUSE_SCREEN_DATA.subMenuStage++;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 2:
            PAUSE_SCREEN_DATA.unk_1B = 0;
            if (PAUSE_SCREEN_DATA.unk_1C == 1)
            {
                if (gChangedInput & (KEY_A | KEY_B | KEY_DOWN) && !(PAUSE_SCREEN_DATA.typeFlags & 0x200) &&
                    PAUSE_SCREEN_DATA.unk_241 == 0)
                {
                    PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 0;
                    PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
                    PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
                    TextClearGraphics(0);
                    PAUSE_SCREEN_DATA.subMenuStage = 3;
                    PAUSE_SCREEN_DATA.timer = 0;
                    break;
                }

                if (PAUSE_SCREEN_DATA.typeFlags & 0x200)
                {
                    if (!(PAUSE_SCREEN_DATA.typeFlags & 0x400))
                        PAUSE_SCREEN_DATA.typeFlags |= 0x400;
                    break;
                }
            }
            else if (PAUSE_SCREEN_DATA.unk_1C == 2)
            {
                if (!(PAUSE_SCREEN_DATA.typeFlags & 0x400))
                {
                    PAUSE_SCREEN_DATA.unk_24 = 0;
                    PAUSE_SCREEN_DATA.unk_25 = 1;
                    PAUSE_SCREEN_DATA.unk_1A = 1;
                    PAUSE_SCREEN_DATA.unk_1B = 0;
                    PAUSE_SCREEN_DATA.subMenuStage = 8;
                    PAUSE_SCREEN_DATA.timer = 0;
                }
            }
            else if (PAUSE_SCREEN_DATA.unk_1C == 6)
            {
                ended = TRUE;
            }
            else
            {
                NavigationConversationProcessText();
            }

            if (PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId == 3)
            {
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition = 0x74;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].yPosition =
                    sNavConversationTextBoxCursorYPositions[PAUSE_SCREEN_DATA.unk_18][1];
                break;
            }

            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].yPosition = 0;
            if (NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) >= 0xE0)
            {
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition += NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) - 0xD8;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].yPosition +=
                    sNavConversationTextBoxCursorYPositions[PAUSE_SCREEN_DATA.unk_18][0] + 0x10;
            }
            else
            {
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition += NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) + 8;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].yPosition +=
                    sNavConversationTextBoxCursorYPositions[PAUSE_SCREEN_DATA.unk_18][0];
            }
            break;

        case 3:
            PAUSE_SCREEN_DATA.unk_1B = 0;
            if (PAUSE_SCREEN_DATA.conversationNumber != gPreviousNavigationConversation)
            {
                gPreviousNavigationConversation = PAUSE_SCREEN_DATA.conversationNumber;
                if (!PAUSE_SCREEN_DATA.conversationOnRepeat)
                    SoundEventUpdateForNavConversation();
            }

            PAUSE_SCREEN_DATA.subMenuStage++;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 4:
            if (PAUSE_SCREEN_DATA.timer > 8)
            {
                PAUSE_SCREEN_DATA.subMenuStage++;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 5:
            PAUSE_SCREEN_DATA.dispcnt ^= DCNT_BG0;

            if (PAUSE_SCREEN_DATA.typeFlags & 0x40)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x40;

            if (PAUSE_SCREEN_DATA.typeFlags & 0x8)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x8;

            if (PAUSE_SCREEN_DATA.typeFlags & 0x10)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x10;

            PAUSE_SCREEN_DATA.subMenuStage++;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 6:
            if (PAUSE_SCREEN_DATA.typeFlags & 1)
                return FALSE;
            if (PAUSE_SCREEN_DATA.typeFlags & 2)
                return FALSE;
            if (PAUSE_SCREEN_DATA.typeFlags & 4)
                return FALSE;

            PAUSE_SCREEN_DATA.subMenuStage++;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 7:
            ended = TRUE;
            PAUSE_SCREEN_DATA.subMenuStage = 0;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 8:
            if (PAUSE_SCREEN_DATA.unk_24 == 0)
            {
                if (!(gChangedInput & (KEY_A | KEY_B | KEY_DOWN)))
                    break;

                SoundPlay(SOUND_203);
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 0;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
                TextClearGraphics(1);
                PAUSE_SCREEN_DATA.unk_24 = 1;
                PAUSE_SCREEN_DATA.unk_1C = 3;
                PAUSE_SCREEN_DATA.unk_20 = 0;
                PAUSE_SCREEN_DATA.unk_21 = 0;
                PAUSE_SCREEN_DATA.navConvTextIndent = 0;
            }
            else if (PAUSE_SCREEN_DATA.unk_24 == 2)
            {
                PAUSE_SCREEN_DATA.subMenuStage = 9;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            else if (unk_7a0fc(0))
            {
                PAUSE_SCREEN_DATA.unk_24 = 2;
                PAUSE_SCREEN_DATA.unk_1A = 1;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 2;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].yPosition = 0x8C;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition = 0x34;
            }
            break;

        case 9:
            temp = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].yPosition = 0x8C;

            if (gChangedInput & KEY_LEFT)
            {
                temp = PAUSE_SCREEN_DATA.unk_25 != TRUE;
                PAUSE_SCREEN_DATA.unk_25 = TRUE;
            }
            else if (gChangedInput & KEY_RIGHT)
            {
                if (PAUSE_SCREEN_DATA.unk_25)
                    temp = 1;
                PAUSE_SCREEN_DATA.unk_25 = FALSE;
            }
            else if (gChangedInput & KEY_A)
            {
                temp = 2;
                PAUSE_SCREEN_DATA.subMenuStage = 10;
                PAUSE_SCREEN_DATA.timer = 0;
            }

            if (PAUSE_SCREEN_DATA.unk_25)
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition = 0x34;
            else
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition = 0x84;

            if (temp == 1)
            {
                SoundPlay(SOUND_1FA);
            }
            else if (temp == 2)
            {
                if (PAUSE_SCREEN_DATA.unk_25)
                    SoundPlay(SOUND_204);
                else
                    SoundPlay(SOUND_205);
            }
            break;

        case 10:
            if (!(PAUSE_SCREEN_DATA.typeFlags & (0x40 | 0x80)))
            {
                PAUSE_SCREEN_DATA.subMenuStage = 16;
                if (!PAUSE_SCREEN_DATA.unk_25)
                {
                    PAUSE_SCREEN_DATA.mapX = gMinimapX;
                    PAUSE_SCREEN_DATA.mapY = gMinimapY;
                    if (PAUSE_SCREEN_DATA.currentArea != gCurrentArea)
                    {
                        PAUSE_SCREEN_DATA.subMenuStage = 11;
                        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].oamId = 0;
                        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].animationDurationCounter = 0;
                        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].currentAnimationFrame = 0;
                    }
                    else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId != 0)
                    {
                        PAUSE_SCREEN_DATA.subMenuStage = 15;
                    }

                    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId = 0;
                    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].animationDurationCounter = 0;
                    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].currentAnimationFrame = 0;
                    PAUSE_SCREEN_DATA.unk_C = 0;
                    PAUSE_SCREEN_DATA.unk_219 = 0;
                }

                TextClearGraphics(1);
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 0;
                PAUSE_SCREEN_DATA.unk_1A = 1;
                NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) = 0;
                NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0;
                PAUSE_SCREEN_DATA.unk_1C = 0;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            else if (PAUSE_SCREEN_DATA.typeFlags & 0x40)
            {
                PAUSE_SCREEN_DATA.typeFlags ^= 0x40;
            }
            break;

        case 11:
            PAUSE_SCREEN_DATA.unk_250 |= 1;
            PAUSE_SCREEN_DATA.timer = 0;
            PAUSE_SCREEN_DATA.subMenuStage = 12;
            break;

        case 12:
            if (PAUSE_SCREEN_DATA.unk_250 & 4)
            {
                PAUSE_SCREEN_DATA.currentArea = gCurrentArea;
                unk_75988(TRUE);
                PAUSE_SCREEN_DATA.timer = 0;
                PAUSE_SCREEN_DATA.subMenuStage = 13;
            }
            break;

        case 13:
            if (PAUSE_SCREEN_DATA.timer > 4)
            {
                MinimapGetData(PAUSE_SCREEN_DATA.currentArea, EWRAM_BASE + 0x34000);
                MinimapSetVisitedTilesAndCollectedItems(PAUSE_SCREEN_DATA.currentArea);
                DMA3_COPY_16(EWRAM_BASE + 0x34000, VRAM_BASE + 0xE000, 0x400);
                PAUSE_SCREEN_DATA.subMenuStage = 14;
                PAUSE_SCREEN_DATA.timer = 0;
                PAUSE_SCREEN_DATA.unk_250 |= 8;
            }
            break;

        case 14:
            if (PAUSE_SCREEN_DATA.unk_250 == 0)
            {
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].oamId = 1;
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].currentAnimationFrame = 0;
                PAUSE_SCREEN_DATA.timer = 0;
                PAUSE_SCREEN_DATA.subMenuStage = 16;
            }
            break;

        case 15:
            if (NavigationConversationScrollMapToDestination(PAUSE_SCREEN_DATA.mapX, PAUSE_SCREEN_DATA.mapY))
            {
                PAUSE_SCREEN_DATA.timer = 0;
                PAUSE_SCREEN_DATA.subMenuStage = 16;
            }
            break;

        case 16:
            if (PAUSE_SCREEN_DATA.timer > 16)
            {
                NavigationConversationUpdateTarget(FALSE);
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition = 8;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].yPosition =
                    sNavConversationTextBoxCursorYPositions[PAUSE_SCREEN_DATA.unk_18][0];
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 11;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
                PAUSE_SCREEN_DATA.subMenuStage = 1;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 17:
            PAUSE_SCREEN_DATA.dispcnt |= DCNT_BG0;
            PAUSE_SCREEN_DATA.unk_1D = 8;
            PAUSE_SCREEN_DATA.unk_1E = 0;
            PAUSE_SCREEN_DATA.unk_1F = 0;
            PAUSE_SCREEN_DATA.typeFlags |= 1;
            PAUSE_SCREEN_DATA.unk_18 = 0;
            PAUSE_SCREEN_DATA.unk_19 = 1;
            PAUSE_SCREEN_DATA.unk_17 = 0;
            PAUSE_SCREEN_DATA.unk_24 = 1;
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.unk_20 = 0;
            PAUSE_SCREEN_DATA.unk_21 = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent = 0;
            PAUSE_SCREEN_DATA.unk_1C = 5;
            PAUSE_SCREEN_DATA.subMenuStage++;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 18:
            if (PAUSE_SCREEN_DATA.unk_24 == 0)
                break;

            if (PAUSE_SCREEN_DATA.unk_24 == 2)
            {
                PAUSE_SCREEN_DATA.subMenuStage = 19;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            else if (unk_7a0fc(1))
            {
                PAUSE_SCREEN_DATA.unk_24 = 2;
                PAUSE_SCREEN_DATA.unk_1A = 1;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 2;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].yPosition = 0x8C;
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition = 0x84;
                PAUSE_SCREEN_DATA.unk_25 = FALSE;
            }
            break;

        case 19:
            temp = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].yPosition = 0x8C;

            if (gChangedInput & KEY_LEFT)
            {
                temp = PAUSE_SCREEN_DATA.unk_25 != TRUE;
                PAUSE_SCREEN_DATA.unk_25 = TRUE;
            }
            else if (gChangedInput & KEY_RIGHT)
            {
                if (PAUSE_SCREEN_DATA.unk_25)
                    temp = 1;
                PAUSE_SCREEN_DATA.unk_25 = FALSE;
            }
            else if (gChangedInput & KEY_A)
            {
                temp = 2;
                PAUSE_SCREEN_DATA.subMenuStage = 20;
                PAUSE_SCREEN_DATA.timer = 0;
            }

            if (PAUSE_SCREEN_DATA.unk_25)
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition = 0x34;
            else
                PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition = 0x84;

            if (temp == 1)
            {
                SoundPlay(SOUND_1FA);
            }
            else if (temp == 2)
            {
                if (PAUSE_SCREEN_DATA.unk_25)
                    SoundPlay(SOUND_204);
                else
                    SoundPlay(SOUND_205);
            }
            break;

        case 20:
            PAUSE_SCREEN_DATA.subMenuStage = 21;
            if (PAUSE_SCREEN_DATA.unk_25 == TRUE)
            {
                gPreviousNavigationConversation = UCHAR_MAX;
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId = 0;
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].currentAnimationFrame = 0;
                PAUSE_SCREEN_DATA.unk_C = 0;
                PAUSE_SCREEN_DATA.unk_219 = 0;
            }

            TextClearGraphics(1);
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 0;
            PAUSE_SCREEN_DATA.unk_1A = 1;
            NAV_TEXT_POS(PAUSE_SCREEN_DATA.unk_18) = 0;
            NAV_TEXT_TIMER(PAUSE_SCREEN_DATA.unk_18) = 0;
            PAUSE_SCREEN_DATA.unk_1C = 0;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 21:
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].xPosition = 8;
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].yPosition =
                sNavConversationTextBoxCursorYPositions[PAUSE_SCREEN_DATA.unk_18][0];
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].oamId = 11;
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_SCREEN_DATA.unk_19].currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.subMenuStage = 1;
            PAUSE_SCREEN_DATA.timer = 0;
            break;
    }

    return ended;
}

/**
 * @brief 7ae54 | 138 | Sets up the OAM of a navigation conversation
 * 
 */
void NavigationConversationSetupOam(void)
{
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_OUTLINE].xPosition = 0x7C;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_OUTLINE].yPosition = 0xCC;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_LIGHT].oamId = PAUSE_OAM_ID_ADAM_TEXT_BOX_LIGHT_OFF;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_LIGHT].animationDurationCounter = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_LIGHT].currentAnimationFrame = 0;

    NavConversationSetBottomTextBoxOam(1);

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_BACKGROUND].objMode = 1;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_CURSOR].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_CURSOR].objMode = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_LIGHT].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_LIGHT].objMode = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_OUTLINE].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_OUTLINE].objMode = 0;

    *(struct NavConversationPopUpInfo*)&PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer =
        *(const struct NavConversationPopUpInfo*)sNavConversationPopUpInfoInit;

    PAUSE_SCREEN_DATA.unk_1A = 0;
    PAUSE_SCREEN_DATA.typeFlags = 0;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_BACKGROUND].objMode = 1;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_CURSOR].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_CURSOR].objMode = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_OUTLINE].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_OUTLINE].objMode = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_PORTRAIT].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_PORTRAIT].objMode = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_FED_PORTRAIT_FLICKERING].priority = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_FED_PORTRAIT_FLICKERING].objMode = 0;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_PORTRAIT].xPosition = 0xD4;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_PORTRAIT].yPosition = 0x44;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_FED_PORTRAIT_FLICKERING].xPosition = 0xD4;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_FED_PORTRAIT_FLICKERING].yPosition = 0x44;

    if (PAUSE_SCREEN_DATA.unk_0)
    {
        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_BACKGROUND].priority = 1;
        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_BACKGROUND].priority = 1;
    }
    else
    {
        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_TOP_TEXT_BOX_BACKGROUND].priority = 2;
        PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_ADAM_TEXT_BOX_BACKGROUND].priority = 2;
    }
}

/**
 * @brief 7af8c | 70 | Updates the target of a navigation conversation
 * 
 * @param updateOam Update OAM flag
 */
void NavigationConversationUpdateTarget(u8 updateOam)
{
    u8 oamId;

    if (!NavigationConverstionFindTarget())
        return;

    if (!updateOam)
        return;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].animationDurationCounter = 0;
    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].currentAnimationFrame = 0;

    if (PAUSE_SCREEN_DATA.unk_20F == 1)
        oamId = sNavTargetOamIds[PAUSE_SCREEN_DATA.navTargetTextDirection];
    else if (PAUSE_SCREEN_DATA.currentArea == 0)
        oamId = PAUSE_OAM_ID_MAP_ELEVATOR_DOWN_ARROWS;
    else
        oamId = PAUSE_OAM_ID_MAP_ELEVATOR_UP_ARROWS;

    PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId = oamId;
}

/**
 * @brief 7affc | 15c | Finds the target of the current navigation conversation
 * 
 * @return bool, conversation already happened
 */
u32 NavigationConverstionFindTarget(void)
{
    u32 found;
    u32 i;
    u8 x;
    u8 y;

    PAUSE_SCREEN_DATA.unk_20F = 0;
    PAUSE_SCREEN_DATA.navTargetX = UCHAR_MAX;
    PAUSE_SCREEN_DATA.navTargetY = -1;
    PAUSE_SCREEN_DATA.navTargetArea = 0;
    PAUSE_SCREEN_DATA.navTargetTextDirection = 0;

    if (gPauseScreenFlag == 4)
        return FALSE;

    gNavigationTargetLocation = 0;
    found = FALSE;

    for (i = 0; i <= 32; i++)
    {
        if (PAUSE_SCREEN_DATA.conversationNumber == sNavConversationTargets[i].conversation)
        {
            found = TRUE;
            PAUSE_SCREEN_DATA.navTargetTextDirection = sNavConversationTargets[i].textDirection;
            break;
        }
    }

    if (!found)
        return FALSE;

    gNavigationTargetLocation = sNavConversationTargets[i].location;
    PAUSE_SCREEN_DATA.navTargetArea = sNavigationTargetLocationAreas[gNavigationTargetLocation];

    if (PAUSE_SCREEN_DATA.currentArea == PAUSE_SCREEN_DATA.navTargetArea)
    {
        x = sNavConversationTargets[i].xPosition;
        y = sNavConversationTargets[i].yPosition;
        PAUSE_SCREEN_DATA.unk_20F = 1;
    }
    else if (PAUSE_SCREEN_DATA.currentArea == 0)
    {
        x = sNavTargetMainDeckElevatorPositions[PAUSE_SCREEN_DATA.navTargetArea][0];
        y = sNavTargetMainDeckElevatorPositions[PAUSE_SCREEN_DATA.navTargetArea][1];
        PAUSE_SCREEN_DATA.unk_20F = 2;
    }
    else
    {
        x = sNavTargetAreaElevatorPositions[PAUSE_SCREEN_DATA.currentArea][0];
        y = sNavTargetAreaElevatorPositions[PAUSE_SCREEN_DATA.currentArea][1];
        if (PAUSE_SCREEN_DATA.navTargetArea == 0)
            PAUSE_SCREEN_DATA.unk_20F = 2;
        else
            PAUSE_SCREEN_DATA.unk_20F = 3;
    }

    PAUSE_SCREEN_DATA.navTargetX = x - 1;
    PAUSE_SCREEN_DATA.navTargetY = y - 1;

    found = FALSE;
    if (gPreviousNavigationConversation == PAUSE_SCREEN_DATA.conversationNumber)
        found = TRUE;

    return found;
}

/**
 * @brief 7b158 | 36c | Handles the scrolling of the map to the target of a navigation conversation
 * 
 */
void NavigationConversionScrollToTarget(void)
{
    u32 temp;
    u8 oamId;

    PAUSE_SCREEN_DATA.unk_8++;

    switch (PAUSE_SCREEN_DATA.unk_9)
    {
        case 0:
            break;

        case 1:
            temp = FALSE;
            if (PAUSE_SCREEN_DATA.navTargetX == UCHAR_MAX || PAUSE_SCREEN_DATA.navTargetY == UCHAR_MAX)
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == sNavTargetOamIds[0])
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == sNavTargetOamIds[1])
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == sNavTargetOamIds[2])
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == sNavTargetOamIds[3])
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == PAUSE_OAM_ID_MAP_ELEVATOR_UP_ARROWS)
                temp = TRUE;
            else if (PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId == PAUSE_OAM_ID_MAP_ELEVATOR_DOWN_ARROWS)
                temp = TRUE;

            if (temp)
            {
                PAUSE_SCREEN_DATA.unk_9 = 12;
            }
            else
            {
                PAUSE_SCREEN_DATA.unk_9 = 2;
                PAUSE_SCREEN_DATA.typeFlags |= 0x100;
                PAUSE_SCREEN_DATA.typeFlags |= 0x200;
            }
            break;

        case 2:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x400)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9++;
            }
            break;

        case 3:
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9 = 4;
            break;

        case 5:
            if (!NavigationConversationScrollMapToDestination(PAUSE_SCREEN_DATA.navTargetX, PAUSE_SCREEN_DATA.navTargetY))
                break;

            if (PAUSE_SCREEN_DATA.unk_20F == 1)
                temp = sNavTargetOamIds[PAUSE_SCREEN_DATA.navTargetTextDirection];
            else if (PAUSE_SCREEN_DATA.currentArea == 0)
                temp = PAUSE_OAM_ID_MAP_ELEVATOR_DOWN_ARROWS;
            else
                temp = PAUSE_OAM_ID_MAP_ELEVATOR_UP_ARROWS;

            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId = temp;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;

            if (PAUSE_SCREEN_DATA.unk_20F == 1)
                PAUSE_SCREEN_DATA.unk_9 = 12;
            else
                PAUSE_SCREEN_DATA.unk_9 = 6;

            SoundStop(SOUND_119);
            PAUSE_SCREEN_DATA.mapViewX = PAUSE_SCREEN_DATA.navTargetX;
            PAUSE_SCREEN_DATA.mapViewY = PAUSE_SCREEN_DATA.navTargetY;
            break;

        case 6:
            if (PAUSE_SCREEN_DATA.unk_8 > 60)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9++;
            }
            break;

        case 7:
            PAUSE_SCREEN_DATA.unk_250 = 1;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_MAP_TARGET].oamId = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].oamId = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 8:
            if (!(PAUSE_SCREEN_DATA.unk_250 & 4))
                break;

            if (PAUSE_SCREEN_DATA.unk_20F == 3)
                PAUSE_SCREEN_DATA.navTargetArea = 0;

            if (PAUSE_SCREEN_DATA.navTargetArea == 0)
            {
                PAUSE_SCREEN_DATA.mapX = sNavTargetMainDeckElevatorPositions[PAUSE_SCREEN_DATA.currentArea][0] - 1;
                PAUSE_SCREEN_DATA.mapY = sNavTargetMainDeckElevatorPositions[PAUSE_SCREEN_DATA.currentArea][1] - 1;
            }
            else
            {
                PAUSE_SCREEN_DATA.mapX = sNavTargetAreaElevatorPositions[PAUSE_SCREEN_DATA.navTargetArea][0] - 1;
                PAUSE_SCREEN_DATA.mapY = sNavTargetAreaElevatorPositions[PAUSE_SCREEN_DATA.navTargetArea][1] - 1;
            }

            PAUSE_SCREEN_DATA.currentArea = PAUSE_SCREEN_DATA.navTargetArea;
            MinimapGetData(PAUSE_SCREEN_DATA.currentArea, gMinimapData_Visited);
            MinimapSetVisitedTilesAndCollectedItems(PAUSE_SCREEN_DATA.currentArea);
            DMA3_COPY_16(gMinimapData_Visited, VRAM_BASE + 0xE000, MINIMAP_SIZE);
            unk_75988(TRUE);
            NavigationConversationUpdateTarget(FALSE);
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 9:
            if (PAUSE_SCREEN_DATA.unk_8 > 8)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9++;
                PAUSE_SCREEN_DATA.unk_250 |= 8;
            }
            break;

        case 10:
            if (PAUSE_SCREEN_DATA.unk_250 != 0)
                break;

            if (PAUSE_SCREEN_DATA.navTargetArea == 0)
                oamId = PAUSE_OAM_ID_MAP_ELEVATOR_UP_ARROWS;
            else if (PAUSE_SCREEN_DATA.currentArea == 0)
                oamId = PAUSE_OAM_ID_MAP_ELEVATOR_UP_ARROWS;
            else
                oamId = PAUSE_OAM_ID_MAP_ELEVATOR_DOWN_ARROWS;

            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].oamId = oamId;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_BLINKING_SQUARE].currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 4:
        case 11:
            if (PAUSE_SCREEN_DATA.unk_8 > 30)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9 = 5;
                SoundPlay(SOUND_119);
            }
            break;

        case 12:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x200)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x200;
            if (PAUSE_SCREEN_DATA.typeFlags & 0x400)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x400;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 13:
            break;
    }
}

/**
 * @brief 7b4c4 | a8 | Scrolls the map towards a destination
 * 
 * @param x X destination
 * @param y Y destination
 * @return bool, reached
 */
u32 NavigationConversationScrollMapToDestination(u8 x, u8 y)
{
    u32 reached;
    s32 targetX;
    s32 targetY;
    s32 diff;
    s32 diffY;
    s32 speedX;
    s32 speedY;

    reached = TRUE;

    targetX = 0x200 - (15 - x) * 8;
    targetY = 0x200 - (10 - y) * 8;

    diff = gBackgroundPositions.bg[3].x - targetX;
    diffY = gBackgroundPositions.bg[3].y - targetY;

    if (diff < 0)
        diff = -diff;

    if (diffY < 0)
        diffY = -diffY;

    speedX = (diff >> 4) + 1;
    speedY = (diffY >> 4) + 1;

    diff = gBackgroundPositions.bg[3].x - targetX;
    if (diff != 0)
    {
        reached = FALSE;
        if (diff > 0)
        {
            gBackgroundPositions.bg[3].x -= speedX;
            if (gBackgroundPositions.bg[3].x < targetX)
                gBackgroundPositions.bg[3].x = targetX;
        }
        else if (diff < 0)
        {
            gBackgroundPositions.bg[3].x += speedX;
            if (gBackgroundPositions.bg[3].x > targetX)
                gBackgroundPositions.bg[3].x = targetX;
        }
    }

    diff = gBackgroundPositions.bg[3].y - targetY;
    if (diff != 0)
    {
        reached = FALSE;
        if (diff > 0)
        {
            gBackgroundPositions.bg[3].y -= speedY;
            if (gBackgroundPositions.bg[3].y < targetY)
                gBackgroundPositions.bg[3].y = targetY;
        }
        else if (diff < 0)
        {
            gBackgroundPositions.bg[3].y += speedY;
            if (gBackgroundPositions.bg[3].y > targetY)
                gBackgroundPositions.bg[3].y = targetY;
        }
    }

    return reached;
}

/**
 * @brief 7b56c | 108 | Handles the pop up window of a navigation conversation
 * 
 */
void unk_7b56c(void)
{
    PAUSE_SCREEN_DATA.unk_A++;

    switch (PAUSE_SCREEN_DATA.unk_B)
    {
        case 0:
            break;

        case 1:
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B++;
            break;

        case 2:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x40)
            {
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
            }
            break;

        case 3:
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].oamId = PAUSE_OAM_ID_POP_UP_WINDOW;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].currentAnimationFrame = 0;
            SoundPlay(SOUND_11C);
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B++;
            break;

        case 4:
            if (PAUSE_SCREEN_DATA.unk_A > 30)
            {
                PAUSE_SCREEN_DATA.currentPopUp = 1;
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
                PAUSE_SCREEN_DATA.typeFlags |= 0x80;
            }
            break;

        case 5:
            if (!(PAUSE_SCREEN_DATA.typeFlags & 0x40))
            {
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
            }
            break;

        case 6:
            PAUSE_SCREEN_DATA.currentPopUp = 3;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].oamId = PAUSE_OAM_ID_POP_UP_WINDOW_CLOSING;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[PAUSE_OAM_IDX_POP_UP_WINDOW].currentAnimationFrame = 0;
            SoundPlay(SOUND_11D);
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B++;
            break;

        case 7:
            if (PAUSE_SCREEN_DATA.unk_A > 30)
            {
                PAUSE_SCREEN_DATA.typeFlags &= ~0x80;
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
            }
            break;

        case 8:
        case 9:
            break;
    }
}

/**
 * @brief 7b674 | 260 | Handles the transition of the map during a navigation conversation
 *
 */
void unk_7b674(void)
{
    s32 size;

    if (!(PAUSE_SCREEN_DATA.unk_250 & (1 | 2)))
        return;

    PAUSE_SCREEN_DATA.unk_252++;

    switch (PAUSE_SCREEN_DATA.unk_251)
    {
        case 0:
            if (PAUSE_SCREEN_DATA.unk_250 & 1)
                PAUSE_SCREEN_DATA.unk_251 = 1;
            else if (PAUSE_SCREEN_DATA.unk_250 & 2)
                PAUSE_SCREEN_DATA.unk_251 = 4;

            gPreviousArea = UCHAR_MAX;
            PAUSE_SCREEN_DATA.unk_252 = 0;
            break;

        case 1:
            if (MOD_AND(PAUSE_SCREEN_DATA.unk_252, 8) == 0)
                break;

            gWrittenToMosaic_L += 0x11;
            if (gWrittenToMosaic_L == sUnk_576802[0])
            {
                PAUSE_SCREEN_DATA.unk_252 = 0;
                PAUSE_SCREEN_DATA.unk_251++;
                PAUSE_SCREEN_DATA.unk_250 |= 4;
            }
            break;

        case 3:
            FAKE_MATCH_NOP_OR(PAUSE_SCREEN_DATA.unk_250);
            if (MOD_AND(PAUSE_SCREEN_DATA.unk_252, 8) != 0)
            {
                gWrittenToMosaic_L -= 0x11;
                if (gWrittenToMosaic_L == 0)
                {
                    PAUSE_SCREEN_DATA.unk_251 = 8;
                    PAUSE_SCREEN_DATA.unk_252 = 0;
                }
            }
            break;

        case 4:
            PAUSE_SCREEN_DATA.window1Size = 0;
            PAUSE_SCREEN_DATA.unk_251 = 5;
            PAUSE_SCREEN_DATA.unk_252 = 0;
            break;

        case 5:
            size = (0x50 - PAUSE_SCREEN_DATA.window1Size) >> 4;
            if (size < 4)
                size = 4;

            PAUSE_SCREEN_DATA.window1Size += size;
            if (PAUSE_SCREEN_DATA.window1Size > 0x50)
            {
                PAUSE_SCREEN_DATA.window1Size = 0x50;
                PAUSE_SCREEN_DATA.unk_252 = 0;
                PAUSE_SCREEN_DATA.unk_251++;
                PAUSE_SCREEN_DATA.unk_250 |= 4;
            }

            WRITE_16(REG_WIN1V, PAUSE_SCREEN_DATA.window1Size << 8 | (0xA0 - PAUSE_SCREEN_DATA.window1Size));
            break;

        case 2:
        case 6:
            if (PAUSE_SCREEN_DATA.unk_250 & 8)
            {
                PAUSE_SCREEN_DATA.unk_251++;
                PAUSE_SCREEN_DATA.unk_252 = 0;
            }
            break;

        case 7:
            size = (0x50 - PAUSE_SCREEN_DATA.window1Size) >> 4;
            if (size < 4)
                size = 4;

            size = PAUSE_SCREEN_DATA.window1Size - size;
            if (size < 0)
            {
                PAUSE_SCREEN_DATA.window1Size = 0;
                PAUSE_SCREEN_DATA.unk_251 = 8;
                PAUSE_SCREEN_DATA.unk_252 = 0;
            }
            else
            {
                PAUSE_SCREEN_DATA.window1Size = size;
            }

            WRITE_16(REG_WIN1V, PAUSE_SCREEN_DATA.window1Size << 8 | (0xA0 - PAUSE_SCREEN_DATA.window1Size));
            break;

        case 8:
            PAUSE_SCREEN_DATA.unk_252 = 0;
            PAUSE_SCREEN_DATA.unk_251 = 0;
            PAUSE_SCREEN_DATA.unk_250 = 0;
            break;
    }
}

/**
 * @brief 7b8d4 | 11c | Draws the text of the pause screen (current objective)
 *
 */
void ProcessPauseScreenText(void)
{
    s32 indent;
    u16* pText;
    u32 width;
    s32 offset;
    void* dst;
    s32 temp;

    BitFill(3, 0, EWRAM_BASE + 0xC000, 0x1000, 16);

    indent = 0;
    dst = EWRAM_BASE + 0xC000;
    pText = sPauseScreenTextPointers[gLanguage][gEventCounter];

    while (*pText != 0xFF00)
    {
        // Doubles as the "should draw" flag
        temp = TRUE;

        if ((*pText & 0xFF00) == 0x8000)
        {
            width = *pText & 0xFF;
            temp = FALSE;
        }
        else if ((*pText & 0xFF00) == 0x8300)
        {
            width = 0;
            indent = *pText & 0xFF;
            temp = FALSE;
        }
        else if (*pText == 0xFE00)
        {
            width = 0;
            if (indent > 0xE0)
                break;

            indent = 0xE0;
            temp = FALSE;
        }

        if (temp)
        {
            width = TextGetCharacterWidth(*pText);
            temp = indent + width;

            if (temp > 0xE0 && indent < 0xE0)
                indent = 0xE0;
            else if (temp > 0x1C0)
                break;

            if (indent >= 0xE0)
            {
                temp = 0x800;
                offset = indent - 0xE0;
            }
            else
            {
                temp = 0;
                offset = indent;
            }

            temp += (offset >> 3) * 32;
            offset &= 7;
            TextDrawCharacter(*pText, dst + temp, width, offset, 0);
        }

        pText++;
        indent += width;

        if (indent >= 0x1C0)
            break;
    }
}

/**
 * @brief 7b9f0 | 200 | Draws the text of the easy sleep menu
 *
 */
void ProcessEasySleepText(void)
{
    s32 indent;
    u16* pText;
    u32 width;
    s32 offset;
    void* dst;
    // Doubles as the "should draw" flag
    s32 temp;
    s32 i;

    BitFill(3, 0, EWRAM_BASE + 0xD000, 0x1000, 16);
    BitFill(3, 0, EWRAM_BASE + 0xE000, 0x1000, 16);
    BitFill(3, 0, EWRAM_BASE + 0xF000, 0x800, 16);

    for (i = 0; i < 2; i++)
    {
        dst = EWRAM_BASE + 0xE000;
        if (i == 0)
            dst = EWRAM_BASE + 0xD000;

        pText = sMessageTextPointers[gLanguage][i + 45];
        indent = 0;

        while (*pText != 0xFF00)
        {
            temp = TRUE;

            if ((*pText & 0xFF00) == 0x8000)
            {
                width = *pText & 0xFF;
                temp = FALSE;
            }
            else if ((*pText & 0xFF00) == 0x8300)
            {
                width = 0;
                indent = *pText & 0xFF;
                temp = FALSE;
            }
            else if (*pText == 0xFE00)
            {
                width = 0;
                if (indent > 0xE0)
                    break;

                indent = 0xE0;
                temp = FALSE;
            }

            if (temp)
            {
                width = TextGetCharacterWidth(*pText);
                temp = indent + width;

                if (temp > 0xE0 && indent < 0xE0)
                    indent = 0xE0;
                else if (temp > 0x1C0)
                    break;

                if (indent >= 0xE0)
                {
                    temp = 0x800;
                    offset = indent - 0xE0;
                }
                else
                {
                    temp = 0;
                    offset = indent;
                }

                temp += (offset >> 3) * 32;
                offset &= 7;
                TextDrawCharacter(*pText, dst + temp, width, offset, 0);
            }

            pText++;
            indent += width;

            if (indent >= 0x1C0)
                break;
        }
    }

    dst = EWRAM_BASE + 0xF000;
    pText = sMessageTextPointers[gLanguage][47];
    indent = 0;

    while (*pText != 0xFF00)
    {
        temp = TRUE;

        if (*pText == 0xFE00)
        {
            width = 0;
            if (indent <= 0x70)
                indent = 0x70;
            else
                break;
            temp = FALSE;
        }
        else if (*pText & 0x8000)
        {
            width = 0;
            temp = FALSE;
        }

        if (temp)
        {
            width = TextGetCharacterWidth(*pText);
            temp = indent + width;

            if (temp > 0x1C0)
                break;

            temp = (indent >> 3) * 32;
            offset = indent & 7;
            TextDrawCharacter(*pText, dst + temp, width, offset, 0);
        }

        pText++;
        indent += width;

        if (indent >= 0x1C0)
            break;
    }
}

/**
 * @brief 7bbf0 | a8 | Gets the number of the sector that should be flashing
 *
 * @return u8 Sector number
 */
u8 GetFlashingSectorNumber(void)
{
    s32 i;
    u32 found;

    gFlashingSectorNumber = 0;

    for (i = gEventCounter; i > 0; i--)
    {
        if (sEventLocationAndNavigationInfo[i].navConversation != 0)
            break;
    }

    found = sEventLocationAndNavigationInfo[i].navConversation;
    if (gPreviousNavigationConversation != found)
        return gFlashingSectorNumber;

    found = FALSE;
    for (i = 0; i < sizeof(sNavConversationTargets) / sizeof(sNavConversationTargets[0]); i++)
    {
        if (gPreviousNavigationConversation == sNavConversationTargets[i].conversation)
        {
            found = TRUE;
            break;
        }
    }

    if (!found)
        return gFlashingSectorNumber;

    i = sNavConversationTargets[i].location;
    gFlashingSectorNumber = sNavigationTargetLocationAreas[i];
    return gFlashingSectorNumber;
}
