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

struct NavConversationPopUp {
    const u8* pAnimation;
    u8 animationLength;
    const u16* pPalette;
    u32 unk_C;
    u32 unk_10:8;
    u32 unk_11_0:4;
    u32 unk_11_4:4;
    u32 unk_12_0:4;
    u32 unk_12_4:4;
    u32 unk_13:8;
    const u32* pGraphics;
};

extern u8 gNavigationTargetLocation;

extern u16** sNavConversationTextPointers[];
extern const u8 sNavConversationUnk_5766d4[];
extern const u8 sNavConversationUnk_5767ec[];
extern const struct NavConversationTarget sNavConversationUnk_5766e4[33];
extern const u8 sNavConversationUnk_576218[][2];
extern const u8 sNavConversationUnk_576226[][2];
extern const u8 sUnk_576802[];
extern const struct NavConversationPopUp sNavConversationUnk_57bc50[5];
extern const struct NavConversationPopUpsPerConversation sNavConversationUnk_57bcc8[3];
extern const Func_T sNavConversationUnk_79c170[3];

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

#endif /* NAVIGATION_CONVERSATION_H */
