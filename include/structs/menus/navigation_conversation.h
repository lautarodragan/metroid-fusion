#ifndef NAVIGATION_CONVERSATION_STRUCT_H
#define NAVIGATION_CONVERSATION_STRUCT_H

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

#endif /* NAVIGATION_CONVERSATION_STRUCT_H */
