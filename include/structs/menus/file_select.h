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
    u8 unk_9;
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

struct FileSelectData {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2;
    u8 unk_3;
    const u16* pText;
    u16 unk_8;
    s16 subroutine;
    u8 timer;
    u8 selectedFile;
    u8 unk_E;
    u8 unk_F;
    u8 unk_10;
    u8 dispcntAction;
    s8 result;
    u8 unk_13;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 unk_17;
    struct FileSelectOam oam[23];
};

/**
 * @brief Summary of a save file, as shown on the file select screen
 */
struct SaveFileInfo {
    u8 exists;
    u8 corruptionFlag;
    u8 currentArea;
    u8 unk_3;
    u16 currentEnergy;
    u16 maxEnergy;
    u16 currentMissiles;
    u16 maxMissiles;
    u8 unk_C;
    u8 igtHours;
    u8 igtMinutes;
    u8 unk_F;
    s8 unk_10;
    s8 unk_11;
    u8 unk_12;
    u8 unk_13;
};

extern struct SaveFileInfo gSaveFilesInfo[3];

#endif /* FILE_SELECT_STRUCTS_H */
