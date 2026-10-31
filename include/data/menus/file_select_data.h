#ifndef FILE_SELECT_DATA_H
#define FILE_SELECT_DATA_H

#include "types.h"
#include "oam.h"
#include "gba/memory.h"
#include "constants/game_state.h"

// Defined in src/data/sa_x_close_up.c

extern const u32 sFileSelectBg2Tilemap[245];
extern const u32 sFileSelectBg1Tilemap[155];
extern const u32 sFileSelectBg0Tilemap[154];
extern const u16 sFileSelectBgPal_73dac4[];
extern const u32 sFileSelectEnergyTankOneEmptyGfx[];
extern const u32 sFileSelectEnergyTankOneFullGfx[];
extern const u32 sFileSelectEnergyTanksEmptyGfx[];
extern const u32 sFileSelectEnergyTankOneFullOneEmptyGfx[];
extern const u32 sFileSelectEnergyTanksFullGfx[];
extern const u16 sFileSelectBgPal_73db84[];
extern const u8 sFileSelectOamXFlipOffsets[3][4];
extern const u8 sFileSelectChoiceCursorXPositions_73dbb0[LANGUAGE_COUNT][2];
extern const u8 sFileSelectChoiceCursorXPositions_73dbbe[LANGUAGE_COUNT][2];
extern const u32 sFileSelectObjGfx[1413];
extern const struct FrameData sFileSelectAudioLogosOam1[];
extern const struct FrameData sFileSelectAudioLogosOam2[];
extern const struct FrameData sFileSelectAudioLogosOam3[];
extern const struct FrameData sFileSelectAudioLogosOam4[];
extern const struct FrameData sFileSelectOam_740880[];
extern const struct FrameData sFileSelectOam_7408d0[];
extern const struct FrameData sFileSelectOam_7408e0[];
extern const struct FrameData sFileSelectAudioSelectOam[];
extern const struct FrameData sFileSelectFileActionPanelOam1[];
extern const struct FrameData sFileSelectFileActionPanelOam2[];
extern const struct FrameData sFileSelectFileActionPanelOam3[];
extern const struct FrameData sFileSelectFilePanelOam1[];
extern const struct FrameData sFileSelectFilePanelOam2[];
extern const struct FrameData sFileSelectFilePanelOam3[];
extern const struct FrameData sFileSelectSamusHeadOam1[];
extern const struct FrameData sFileSelectSamusHeadOam2[];
extern const struct FrameData sFileSelectCopyArrowIdleOam[];
extern const struct FrameData sFileSelectCursorOam1[];
extern const struct FrameData sFileSelectCursorOam2[];
extern const struct FrameData sFileSelectOam_740b98[];
extern const u16 sFileSelectObjPal[16 * PAL_ROW];
extern const u32 sFileSelectBgGfx[4171];
extern const u32 sFileSelectBg3Tilemap[368];
extern const u16 sFileSelectBgPal[16 * PAL_ROW];

// Defined in src/new_file_intro.c

extern const struct FrameData* const sFileSelectFileOverlayOam[5];
extern const struct FrameData* const sFileSelectCopyArrowOam[3][3];
extern const u16* const* const sFileSelectTextTileOffsets[LANGUAGE_COUNT];
extern const struct FrameData* const sFileSelectAreaNameOam[][7];
extern const u16* const* const sFileSelectTexts[LANGUAGE_COUNT];
extern const u16* const* const sFileSelectEmptyFileTexts[LANGUAGE_COUNT];

#endif /* FILE_SELECT_DATA_H */
