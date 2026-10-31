#ifndef EVENT_STRUCTS_H
#define EVENT_STRUCTS_H

#include "types.h"

struct AbilityRamValue {
    u8 beamStatus;
    u8 weaponStatus;
    u8 suitStatus;
    u8 isSuit;
    u8 messageNumber;
    u16 soundEvent;
};

struct SecurityUnlockEvent {
    u8 securityLevel;
    u8 area;
    u8 previousEvent;
    u8 nextEvent;
    u16 soundEvent;
};

struct MonologueEvent {
    u8 event;
    u8 elevatorRoomPair;
    u8 side;
    u8 cutscene;
    u16 soundEventAtStart;
    u16 soundEventAtEnd;
};

struct EventLocationAndNavigationInfo {
    u8 area;
    u8 room;
    u8 xStart;
    u8 yStart;
    u8 xEnd;
    u8 yEnd;
    s8 navConversation;
    u8 navRoom;
    u16 download:1;
    u16 skippable:1;
};

extern u8 gAbilityCount;
extern u8 gSecurityHatchLevel;
extern u8 gSecurityHatchLevelBackup;
// Stage of the pause screen handler, also used by the SA-X close-up handler
extern u8 gPauseScreenStage;
extern u8 gEventCounter;
extern u8 gPreviousNavigationConversation;
extern u8 gPreviousCutscene;
extern s8 gRoomEventTrigger;

extern u16 gSoundEventCounter;
extern u16 gPreviousSoundEvent;

extern s8 gDoorUnlockTimer;
// Hatches locked by a gold X spawner door lock: 0 = none, 1 = lock with a timer at the end of the transition, 2 = locked
extern s8 gTimedHatchLockState;

#endif /* EVENT_STRUCTS_H */
