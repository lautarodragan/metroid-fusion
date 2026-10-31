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
    u8 unk_8;
    u8 stage;
    u8 objMode;
    u8 priority;
    u8 xFlip;
    u8 paletteRow;
    u16 tileOffset;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    const struct FrameData* pOam;
    FileSelectOamFunc_T pHandler;
};

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
    u8 unk_12;
    u8 unk_13;
};

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
    u8 unk_16;
    u8 unk_17;
    struct FileSelectOam oam[23];
    struct SaveFileInfo corruptedFileInfo;
};

extern struct SaveFileInfo gSaveFilesInfo[3];

#endif /* FILE_SELECT_STRUCTS_H */
