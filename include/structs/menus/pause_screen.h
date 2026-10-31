#ifndef PAUSE_SCREEN_MENU_STRUCTS_H
#define PAUSE_SCREEN_MENU_STRUCTS_H

#include "types.h"
#include "oam.h"
#include "constants/menus/pause_screen.h"

struct MenuOam {
    s16 yPosition;
    s16 xPosition;
    UNUSED(4);
    u8 animationDurationCounter;
    u8 currentAnimationFrame;
    u8 oamId;
    u8 priority:2;
    u8 objMode:2;
    u8 ended:1;
    u8 notDrawn:1;
    u8 exists:2;
};

ASSERT_SIZE(struct MenuOam, 0xC);

struct PauseScreenState {
    u8 current; // PauseScreenStateId
    // unk_1 to unk_3 are only written (0) by the copy of sPauseScreenDefaultState, never read in the final game
    u8 unk_1;
    u8 unk_2;
    u8 unk_3;
};

struct PauseScreenData {
    u8 screenType; // PauseScreenType
    u8 objectiveTextBoxState;
    u8 enableDebug;
    u16 typeFlags;
    u8 timer;
    u8 subMenuStage;
    u8 navScrollTimer;
    u8 navScrollStage;
    u8 popUpWindowTimer;
    u8 popUpWindowStage;
    u16 navTextIndex;
    u16 navTextTimersAndPositions[4]; // [0..1] text timer per text box, [2..3] text pixel position per text box (NAV_TEXT_TIMER, NAV_TEXT_POS)
    u8 navConvCharacterWidth;
    u8 navSpeaker; // 0 = Adam, 1 = Samus, 2 = Federation
    u8 navTextBox; // 0 = bottom (Adam), 1 = top (Samus/Federation)
    u8 navTextCursorOamIdx; // PAUSE_OAM_IDX_CURSOR or PAUSE_OAM_IDX_TOP_TEXT_BOX_CURSOR
    u8 navWaitForInputRelease; // Skipping text is disabled until A/B/DOWN are released
    u8 navTalkingCharacter; // Character currently speaking (portrait animation), 0 = none, 1 = Adam, 2 = Samus, 3 = Federation
    u8 navConversationStatus; // 0 = processing text, 1 = ended, 2 = asking to proceed, 3/5 = message drawn, 4 = repeated conversation, 6 = end
    u8 navTextSpeed; // Frames per character
    u8 navTextColor;
    u8 navTextDelay;
    u8 navMessageCharacterTimer;
    u8 navMessageTextIndex; // Index in the message text
    u16 navConvTextIndent;
    u8 navMessageStage; // 0 = waiting for input, 1 = drawing, 2 = drawn
    u8 navYesSelected; // Yes/No choice of the message
    struct PauseScreenState state;
    struct MenuOam oam[PAUSE_OAM_IDX_COUNT];
    u8 navTargetX;
    u8 navTargetY;
    u8 navTargetArea;
    u8 navTargetType; // 0 = none, 1 = in the current area, 2 = elevator to/from main deck, 3 = elevator to another sector
    u8 mapX;
    u8 mapY;
    u8 currentArea;
    u8 navTargetTextDirection;
    const u32* pNavConvPopUpGraphicsPointer;
    u8 currentPopUp;
    u8 popUpIndex; // Index of the pop up in the conversation (0-2)
    u8 popUpId; // Index in sNavConversationPopUps
    u8 popUpAnimationTimer;
    u8 popUpAnimationFrame;
    u8 popUpPaletteFadeTimer;
    UNUSED(2);
    u8 conversationNumber;
    u8 conversationOnRepeat;
    UNUSED(2);
    u8 flashingColorIndex;
    u8 flashingColorTimer;
    UNUSED(2);
    u8 popUpCyclePaletteIndex;
    u8 popUpCyclePaletteTimer;
    UNUSED(2);
    u8 bgAnimatedPalFrame;
    u8 bgAnimatedPalTimer;
    UNUSED(2);
    u8 downloadMapTimer;
    u8 downloadMapStage;
    u8 downloadMapLinesDrawn;
    u8 downloadMapCurrentLine;
    u8 downloadMapTrailingLineIndex; // Index in sPauseScreenDownloadScanLineTrailingOamIndices
    UNUSED(3);
    u8 bottomTextBoxStage;
    u8 bottomTextBoxTimer;
    UNUSED(2);
    u8 topTextBoxStage;
    u8 topTextBoxTimer;
    UNUSED(2);
    u8 bslDiagramStage;
    u8 bslDiagramRotating; // Prevents ending the conversation while rotating
    u8 bslDiagramTimer;
    UNUSED(1);
    u8 bslDiagramRotation; // Rotation step (0-35)
    u8 bslDiagramTargetRotation;
    u8 bslDiagramRotationDirection; // 1 or -1
    u8 bslDiagramPalFrame;
    u8 bslDiagramPalTimer;
    u8 bslDiagramFlashingLocation; // Palette color of the current location
    u8 bslDiagramTargetState; // 1 = hidden, 2 = placing, 3 = following the diagram
    UNUSED(5);
    u8 areaTransitionFlags; // 1 = mosaic, 2 = window, 4 = screen covered (set by the transition), 8 = uncover (set by the caller)
    u8 areaTransitionStage;
    u8 areaTransitionTimer;
    u8 window1Size;
    s8 mapRightBorder;
    s8 mapLeftBorder;
    s8 mapTopBorder;
    s8 mapBottomBorder;
    s8 mapViewX;
    s8 mapViewY;
    s8 mapRightEdge; // Bounds of the visited map, the borders are these shrunk by up to 3 tiles
    s8 mapLeftEdge;
    s8 mapTopEdge;
    s8 mapBottomEdge;
    u8 canScrollRight;
    u8 canScrollLeft;
    u8 canScrollUp;
    u8 canScrollDown;
    UNUSED(2);
    u8 specialImageActive; // Operations room image or SA-X close up
    u8 specialImageStage;
    u8 specialImageTimer;
    u16 dispcnt;
    u16 dispcntBackup;
    u16 bg3CntBackup;
    u16 bg2CntBackup;
    u16 bldcntBackup;
    u16 bldalphaBackup;
    u8 igtAndTanksDisplay; // 0 = hidden, 1 = in game time, 2 = collected tanks (toggled with SELECT)
    u8 maxEnergyTanks;
    u8 currentEnergyTanks;
    u8 maxMissileTanks;
    u8 currentMissileTanks;
    u8 maxPowerBombTanks;
    u8 currentPowerBombTanks;
    u8 totalEnergyTanks;
    u8 currentTotalEnergyTanks;
    u8 totalMissileTanks;
    u8 currentTotalMissileTanks;
    u8 totalPowerBombTanks;
    u8 currentTotalPowerBombTanks;
    UNUSED(3);
    u8 debugIgtMinutes; // Minutes of the in game time last drawn by the pause debug menu
};

ASSERT_OFFSET(struct PauseScreenData, state, 0x28);
ASSERT_OFFSET(struct PauseScreenData, dispcnt, 0x268);
ASSERT_SIZE(struct PauseScreenData, 0x288);

struct MaintainedInput {
    u8 delay;
    u8 set;
};

#ifdef USE_EWRAM_SYMBOLS
extern u16 gPauseScreenBg0[0x400];
extern u16 gPauseScreenSleepTilemap[0x800];
#else // !USE_EWRAM_SYMBOLS
#define gPauseScreenBg0 CAST_TO_ARRAY(u16, [0x400], EWRAM_BASE + 0xF800)
#define gPauseScreenSleepTilemap CAST_TO_ARRAY(u16, [0x800], EWRAM_BASE + 0x10000)
#endif // USE_EWRAM_SYMBOLS

extern struct MaintainedInput gMaintainedInput;

#endif /* PAUSE_SCREEN_MENU_STRUCTS_H */
