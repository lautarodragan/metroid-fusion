#ifndef NAVIGATION_CONVERSATION_H
#define NAVIGATION_CONVERSATION_H

#include "types.h"

struct NavConversationPopUpInfo {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
};

extern u16** sNavConversationTextPointers[];
extern const u8 sNavConversationUnk_5766d4[];
extern const u8 sNavConversationUnk_5767ec[];

u32 unk_7a0fc(u8 messageId);
void NavigationConversationGetCurrentConversation(void);
u32 NavigationConversationHandler(void);
void NavigationConversationSetupOam(void);
void NavigationConversationUpdateTarget(u8 updateOam);
u32 NavigationConverstionFindTarget(void);

#endif /* NAVIGATION_CONVERSATION_H */
