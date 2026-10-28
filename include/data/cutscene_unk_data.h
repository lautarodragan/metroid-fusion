#ifndef CUTSCENE_UNK_DATA_H
#define CUTSCENE_UNK_DATA_H

#include "types.h"
#include "oam.h"

// Data used by the intro and ending cutscenes, most of it not identified yet

extern const u32* sIntroSamusSittingBgGfxPointers[5];
extern u16** sMonologueTextPointers[];

extern const u32 sIntroSamusInShipTilemap[];
extern const u16 sIntroSamusInShipPal[];
extern const u32 sIntroShipAlertBg1Tilemap[];
extern const u16 sIntroShipAlertBgPal[];
extern const u16 sIntroShipAlertObjPal[];
// Defined as raw bytes in new_file_intro_data.c, but these are OAM frame data
extern const struct FrameData sIntroDepthParticleOam_0[2];
extern const struct FrameData sIntroDepthParticleOam_1[2];
extern const struct FrameData sIntroDepthParticleOam_2[2];
extern const struct FrameData sIntroDepthParticleOam_3[12];
extern const struct FrameData sIntroSamusShipEnteringOam[7];
extern const struct FrameData sIntroSamusShipBackviewOam[5];
extern const struct FrameData sIntroBslShipBackOam_3[2];
extern const struct FrameData sIntroBslShipBackOam_2[2];
extern const struct FrameData sIntroBslShipBackOam_1[2];
extern const struct FrameData sIntroBslShipBackOam_0[4];
extern const struct FrameData sIntroDriftingShipOam_End[57];
extern const struct FrameData sIntroSplashTextOam[71];
extern const struct FrameData sIntroShipAlertTimeAndDistanceOam[];
extern const struct FrameData sIntroShipAlertOam_65bd00[];
extern const struct FrameData sIntroShipAlertOam_65bd48[];
extern const struct FrameData sIntroShipAlertAsteroidsPopUpOam[];
extern const struct FrameData sIntroShipAlertOam_65be00[];
extern const struct FrameData sIntroShipAlertBigNumberOam_65bf10[];
extern const struct FrameData sIntroShipAlertBigNumberOam_65c0d0[];
extern const struct FrameData sIntroShipAlertBigNumberOam_65c128[];
extern const struct FrameData sIntroShipAlertBigNumberOam_65c180[];
extern const struct FrameData sIntroShipAlertBigNumberOam_65c1d8[];
extern const struct FrameData sIntroShipAlertBigNumberOam_65c230[];
extern const struct FrameData sBslCrashingFallingBslOam_End[29];
extern const struct FrameData sBslCrashingFallingBslOam[3];
extern const struct FrameData sBslCrashingFallingBslTransparentOam[3];
extern const struct FrameData sBslCrashingType3Oam[71];
extern const struct FrameData sEndingLeavingSmallShipOam[3];
extern const struct FrameData sEndingLeavingBigShipOam[3];
extern const struct FrameData sEndingFrontFacingShipOam[3];
extern const struct FrameData sEndingFrontFacingShipThrustersOam[16];
extern const struct FrameData sEndingNextPageArrowOam[5];
extern const struct FrameData sEndingTextCursorOam[7];
extern const struct FrameData sEndingSr388RadarViewOam_Idle[9];
extern const struct FrameData sEndingSamusViewRadarViewOam_Idle[3];
extern const struct FrameData sEndingDialogueType5Oam_Closing[10];

// Defined as raw bytes in new_file_intro.c, but this is a table of pointers to OAM frame data
extern const struct FrameData* sIntroUnk_79c394[];

// Defined as raw bytes in new_file_intro.c, but these are tables of pointers to compressed graphics
extern const u32* sIntroUnk_79c448[];
extern const u32* sIntroUnk_79c45c[];

#endif /* CUTSCENE_UNK_DATA_H */
