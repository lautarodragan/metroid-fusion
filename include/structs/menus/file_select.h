#ifndef FILE_SELECT_STRUCTS_H
#define FILE_SELECT_STRUCTS_H

#include "types.h"
#include "oam.h"

struct FileSelectOam;
typedef void (*FileSelectOamFunc_T)(struct FileSelectOam*);

struct FileSelectOam {
    u16 xPosition;
    u16 yPosition;
    u8 type;
    u8 isDrawn;
    u8 currentAnimationFrame;
    u8 animationDurationCounter;
    UNUSED(1);
    u8 stage;
    u8 objMode;
    u8 priority;
    u8 xFlip;
    u8 paletteRow;
    u16 tileOffset;
    UNUSED(4);
    const struct FrameData* pOam;
    FileSelectOamFunc_T pHandler;
};

ASSERT_SIZE(struct FileSelectOam, 0x1C);

/**
 * @brief Summary of a save file, as shown on the file select screen
 */
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
    u8 savedDuringGameplay; // Saved at least once during gameplay (not only after the intro)
    s8 completedGame;
    s8 introPlayed;
};

ASSERT_SIZE(struct SaveFileInfo, 0x14);

struct FileSelectData {
    u16 textTile;
    u16 textLine;
    const u16* pText;
    u16 textId; // Index in sFileSelectTexts of the text being drawn
    s16 subroutine;
    u8 timer;
    u8 selectedFile;
    u8 fileActionCursor; // 0 = start, 1 = copy, 2 = erase
    u8 copyDestinationFile;
    u8 choiceCursor; // 0 = yes/continue, 1 = no/start over
    u8 dispcntAction;
    s8 result;
    u8 textPixelOffset;
    u8 corruptedFileStage;
    u8 corruptedFile;
    struct FileSelectOam oam[23];
    struct SaveFileInfo corruptedFileInfo;
};

ASSERT_OFFSET(struct FileSelectData, oam, 0x18);
ASSERT_SIZE(struct FileSelectData, 0x2B0);

extern struct SaveFileInfo gSaveFilesInfo[3];

#endif /* FILE_SELECT_STRUCTS_H */
