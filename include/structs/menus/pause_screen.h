#ifndef PAUSE_SCREEN_MENU_STRUCTS_H
#define PAUSE_SCREEN_MENU_STRUCTS_H

#include "types.h"
#include "oam.h"
#include "constants/menus/pause_screen.h"

struct MenuOam {
    s16 yPosition;
    s16 xPosition;
    u8 unk_4;
    u8 unk_5;
    u8 unk_6;
    u8 unk_7;
    u8 animationDurationCounter;
    u8 currentAnimationFrame;
    u8 oamId;
    u8 priority:2;
    u8 objMode:2;
    u8 ended:1;
    u8 notDrawn:1;
    u8 exists:2;
};

struct PauseScreenState {
    u8 current; // PauseScreenStateId
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
    u8 unk_26;
    u8 unk_27;
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
    u8 unk_219;
    u8 unk_21A;
    u8 unk_21B;
    u8 unk_21C;
    u8 unk_21D;
    u8 unk_21E;
    u8 unk_21F;
    u8 conversationNumber;
    u8 conversationOnRepeat;
    u8 unk_222;
    u8 unk_223;
    u8 unk_224;
    u8 unk_225;
    u8 unk_226;
    u8 unk_227;
    u8 unk_228;
    u8 unk_229;
    u8 unk_22A;
    u8 unk_22B;
    u8 unk_22C;
    u8 unk_22D;
    u8 unk_22E;
    u8 unk_22F;
    u8 downloadMapTimer;
    u8 downloadMapStage;
    u8 downloadMapLinesDrawn;
    u8 downloadMapCurrentLine;
    u8 downloadMapTrailingLineIndex; // Index in sPauseScreenDownloadScanLineTrailingOamIndices
    u8 unk_235;
    u8 unk_236;
    u8 unk_237;
    u8 bottomTextBoxStage;
    u8 bottomTextBoxTimer;
    u8 unk_23A;
    u8 unk_23B;
    u8 topTextBoxStage;
    u8 topTextBoxTimer;
    u8 unk_23E;
    u8 unk_23F;
    u8 unk_240;
    u8 unk_241;
    u8 unk_242;
    u8 unk_243;
    u8 unk_244;
    u8 unk_245;
    u8 unk_246;
    u8 unk_247;
    u8 unk_248;
    u8 unk_249;
    u8 unk_24A;
    u8 unk_24B;
    u8 unk_24C;
    u8 unk_24D;
    u8 unk_24E;
    u8 unk_24F;
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
    u8 unk_262;
    u8 unk_263;
    u8 unk_264;
    u8 unk_265;
    u8 unk_266;
    u8 unk_267;
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
    u8 unk_281;
    u8 unk_282;
    u8 unk_283;
    u8 debugIgtMinutes; // Minutes of the in game time last drawn by the pause debug menu
};

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
