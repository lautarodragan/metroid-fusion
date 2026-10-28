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

extern u8 gNavigationTargetLocation;

extern u16** sNavConversationTextPointers[];
extern const u8 sNavConversationUnk_5766d4[];
extern const u8 sNavConversationUnk_5767ec[];
extern const struct NavConversationTarget sNavConversationUnk_5766e4[33];
extern const u8 sNavConversationUnk_576218[][2];
extern const u8 sNavConversationUnk_576226[][2];
extern const u8 sUnk_576802[];

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

#endif /* NAVIGATION_CONVERSATION_H */
