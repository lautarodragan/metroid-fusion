#ifndef NAVIGATION_CONVERSATION_H
#define NAVIGATION_CONVERSATION_H

#include "types.h"

struct NavConversationPopUpInfo {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
};

struct NavConversationTarget {
    s8 conversation;
    u8 location;
    u8 xPosition;
    u8 yPosition;
    u8 textDirection;
};

struct NavConversationPopUpsPerConversation {
    s8 conversation;
    u8 popUps[3];
};

struct __attribute__((packed)) NavConversationPopUpTiles {
    u8 count:4;
    u8 slot:4;
};

struct NavConversationPopUp {
    const u8* pAnimation;
    u8 animationLength;
    const u16* pPalette;
    const u16* pCyclePalette;
    u32 unk_10:8;
    struct NavConversationPopUpTiles tiles;
    u8 unk_12_0:4;
    u8 unk_12_4:4;
    u32 unk_13:8;
    const u32* pGraphics;
};

extern u8 gNavigationTargetLocation;

extern u16** sNavConversationTextPointers[];
extern const u32 sNavConversationPopUpInfoInit[3];
extern const u8 sNavTargetOamIds[4];
extern const struct NavConversationTarget sNavConversationTargets[33];
extern const u8 sNavTargetMainDeckElevatorPositions[][2];
extern const u8 sNavTargetAreaElevatorPositions[][2];
extern const u8 sUnk_576802[];
extern const struct NavConversationPopUp sNavConversationPopUps[5];
extern const struct NavConversationPopUpsPerConversation sNavConversationPopUpsPerConversation[3];
extern const Func_T sNavConversationPopUpFunctions[3];

extern const u16 sNavConversationFlashingColors1[16];
extern const u16 sNavConversationFlashingColors2[2 * 16];
extern const u16 sNavConversationRoomBgAnimatedPal[4 * 16];
extern const u16 sNavConversationShipBgAnimatedPal[8 * 16];
extern const u8 sNavConversationFlashingDurations[4];
extern const u8 sNavConversationRoomBgAnimatedPalDurations[4];
extern const u8 sNavConversationShipBgAnimatedPalDurations[8];

extern const u32 sNavConversationOperationsRoomImageGfx[3831];
extern const u32 sNavConversationOperationsRoomImageTilemap0[358];
extern const u32 sNavConversationOperationsRoomImageTilemap1[358];
extern const u32 sNavConversationOperationsRoomImageTilemap2[358];
extern const u32 sNavConversationOperationsRoomImageTilemap3[358];

// Defined in src/data/menus/pause_screen_misc_data.c
extern const u8 sBslDiagramMainDeckRoomLocations[90];
extern const u16 sNavConversationOperationsRoomImagePal[16 * 16];
extern const u16 sBslDiagramAnimatedPal[16 * 16];
extern const u32 sBslDiagramInfoInit[4];

// Defined in src/text.c
extern u8 sNavConversationSaXCloseUpDelays[];
extern u8 sBslDiagramOamIds[];
extern u8 sBslDiagramTargetOffsets[];
extern u8 sBslDiagramFixedTargetOffsets[];

u32 unk_7a0fc(u8 messageId);
void NavigationConversationGetCurrentConversation(void);
u32 NavigationConversationHandler(void);
void NavigationConversationSetupOam(void);
void NavigationConversationUpdateTarget(u8 updateOam);
u32 NavigationConverstionFindTarget(void);
void NavigationConversionScrollToTarget(void);
u32 NavigationConversationScrollMapToDestination(u8 x, u8 y);
void unk_7b56c(void);
void unk_7b674(void);

void NavigationConversationLoadPopUpGraphics(void);
void NavigationConversationUpdatePopUp(void);
void unk_7bde0(void);
void NavigationConversationFadeInPopUpPalette(void);
void NavigationConversationUpdateXParasitePopUp(void);
void NavigationConversationClearPopUpGraphics(void);
void unk_7c3b4(void);
void unk_7c440(void);
void NavigationConversationLoadSpecialGraphics(void);
void unk_7c630(void);
void unk_7ce6c(void);
void unk_7cfb0(void);
void unk_7d27c(void);

#endif /* NAVIGATION_CONVERSATION_H */
