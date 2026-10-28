#ifndef NAVIGATION_CONVERSATION_H
#define NAVIGATION_CONVERSATION_H

#include "types.h"

extern u16** sNavConversationTextPointers[];

u32 unk_7a0fc(u8 messageId);
void NavigationConversationGetCurrentConversation(void);
u32 NavigationConversationHandler(void);
void NavigationConversationSetupOam(void);
void NavigationConversationUpdateTarget(u8 arg0);

#endif /* NAVIGATION_CONVERSATION_H */
