#ifndef NAVIGATION_CONVERSATION_H
#define NAVIGATION_CONVERSATION_H

#include "types.h"

#include "structs/menus/navigation_conversation.h"

extern u8 gNavigationTargetLocation;

extern u16** sNavConversationTextPointers[];
extern const u32 sNavConversationPopUpInfoInit[3];
extern const u8 sNavTargetOamIds[4];
extern const struct NavConversationTarget sNavConversationTargets[33];
extern const u8 sNavTargetMainDeckElevatorPositions[][2];
extern const u8 sNavTargetAreaElevatorPositions[][2];
extern const u8 sNavConversationAreaTransitionMaxMosaic[];
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

u32 NavigationConversationProcessMessageText(u8 messageId);
void NavigationConversationGetCurrentConversation(void);
u32 NavigationConversationHandler(void);
void NavigationConversationSetupOam(void);
void NavigationConversationUpdateTarget(u8 updateOam);
u32 NavigationConverstionFindTarget(void);
void NavigationConversionScrollToTarget(void);
u32 NavigationConversationScrollMapToDestination(u8 x, u8 y);
void NavigationConversationProcessPopUpWindow(void);
void NavigationConversationProcessAreaTransition(void);

void NavigationConversationLoadPopUpGraphics(void);
void NavigationConversationUpdatePopUp(void);
void NavigationConversationInitPopUp(void);
void NavigationConversationFadeInPopUpPalette(void);
void NavigationConversationUpdateXParasitePopUp(void);
void NavigationConversationClearPopUpGraphics(void);
void NavigationConversationUpdatePopUpPaletteCycle(void);
void NavigationConversationUpdatePaletteAnimations(void);
void NavigationConversationLoadSpecialGraphics(void);
void NavigationConversationProcessSpecialImage(void);
void NavigationConversationInitBslDiagram(void);
void NavigationConversationUpdateBslDiagram(void);
void NavigationConversationSetBslDiagramRotation(void);

#endif /* NAVIGATION_CONVERSATION_H */
