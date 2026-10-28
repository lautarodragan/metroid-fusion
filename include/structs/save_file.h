#ifndef SAVE_FILE_STRUCT_H
#define SAVE_FILE_STRUCT_H

#include "types.h"
#include "gba/memory.h"
#include "globals.h"

#include "structs/samus.h"
#include "structs/scroll.h"

#define EWRAM_SRAM (EWRAM_BASE + 0x38000)
#define SRAM_HEADER_SIZE 0x80
#define SRAM_FULL_HEADER_SIZE (SRAM_HEADER_SIZE * 2)

#define SRAM_MAGIC_SIZE 16
#define SRAM_END_MAGIC_SIZE 8
#define SRAM_HEADER_MAGIC_SIZE 20

// Copies of the SRAM header in EWRAM
#define EWRAM_SRAM_HEADER ((struct SramHeader*)(EWRAM_SRAM))
#define EWRAM_SRAM_HEADER_BACKUP ((struct SramHeader*)(EWRAM_SRAM + SRAM_HEADER_SIZE))
#define EWRAM_SRAM_HEADER_BACKUP_2 ((struct SramHeader*)(EWRAM_SRAM + 0x7100))

struct SramHeader {
    u32 checksum;
    u32 notChecksum;
    u8 unk_8;
    u8 unk_9;
    u8 unk_A;
    u8 unk_B;
    u8 magic[SRAM_HEADER_MAGIC_SIZE];
    u8 unk_20[SRAM_HEADER_SIZE - 0x20];
};

// gCamera is 20 bytes long, the camera struct only describes the first 16
struct SaveCamera {
    u8 data[20];
};

struct SaveMusicInfo {
    u16 musicTrack;
    u16 unk_1E;
    u8 unk_20;
    u8 priority;
    u16 unk_2;
};

struct SaveFile {
    u8 magic[SRAM_MAGIC_SIZE];
    u32 checksum;
    u32 notChecksum;
    struct GameCompletion gameCompletion;
    u8 unk_1C;
    u8 currentArea;
    u8 currentRoom;
    u8 lastDoorUsed;
    u8 abilityCount;
    u8 eventCounter;
    u8 previousNavigationConversation;
    u8 previousCutscene;
    u8 minimapX;
    u8 minimapY;
    u16 soundEventCounter;
    u16 previousSoundEvent;
    u8 unk_2A;
    u8 securityHatchLevelBackup;
    struct SaveCamera camera;
    u16 bg0XPosition;
    u16 bg0YPosition;
    u16 bg1XPosition;
    u16 bg1YPosition;
    u16 bg2XPosition;
    u16 bg2YPosition;
    u16 bg3XPosition;
    u16 bg3YPosition;
    u8 numberOfNeverReformBlocks[8];
    u8 numberOfCollectedTanks[8];
    struct SamusData samusData;
    struct SamusAnimationInfo samusAnimationInfo;
    struct SamusEcho samusEcho;
    struct SamusEnvironmentalEffect samusEnvironmentalEffects[2];
    struct Equipment equipment;
    u16 preventMovementTimer;
    u8 disableDrawingSamusAndScrollingFlag;
    u8 unk_D7;
    u16 atmosphericStabilizersOnline;
    u16 missileGeronsDestroyed;
    u16 superMissileGeronsDestroyed;
    u16 powerBombGeronsDestroyed;
    u16 gadorasDestroyed;
    u8 missileHatchDestroyed;
    u8 waterLowered;
    struct InGameTime inGameTimer;
    struct SaveMusicInfo musicInfo;
    u8 endMagic[SRAM_END_MAGIC_SIZE];
    u8 unk_F8[0x1200 - 0xF8];
};

#define SRAM_EXTRA_DATA_SIZE 0x40
#define SRAM_EXTRA_DATA_MAGIC_SIZE 16

#define EWRAM_SRAM_MOST_RECENT_SAVE_FILE ((struct SramExtraData*)(EWRAM_SRAM + 0x7000))

// Small blocks of data stored outside of the save files (most recent save file, language)
struct SramExtraData {
    u8 id;
    u8 counter;
    u16 checksum;
    u16 notChecksum;
    u8 magic[SRAM_EXTRA_DATA_MAGIC_SIZE];
    u8 value;
    u8 magic2[SRAM_EXTRA_DATA_MAGIC_SIZE];
    u8 unk_27[SRAM_EXTRA_DATA_SIZE - 0x27];
};

// Info about each save file, used on the file select
struct SaveFileInfo {
    u8 exists;
    u8 corruptionFlag;
    u8 currentArea;
    u8 eventCounter;
    u16 currentEnergy;
    u16 maxEnergy;
    u16 currentMissiles;
    u16 maxMissiles;
    u8 weaponsStatus;
    u8 igtHours;
    u8 igtMinutes;
    u8 unk_F;
    struct GameCompletion gameCompletion;
};

extern u8 gMostRecentSaveFile;
extern u8 gUnk_3000010;
extern u8 gSramTestFailed;
extern u8 gUnk_3000b90;
extern u8 gUnk_300004c;
extern u8 gUnk_300004d;
extern struct SaveFileInfo gSaveFilesInfo[3];

#endif /* SAVE_FILE_STRUCT_H */
