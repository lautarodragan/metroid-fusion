#include "globals.h"
#include "compiler_tricks.h"
#include "new_file_intro.h"
#include "music_wrappers.h"

#include "constants/game_state.h"
#include "constants/audio.h"
#include "constants/text.h"
#include "constants/new_file_intro.h"

#include "structs/cutscene.h"

#include "data/new_file_intro_data.h"
#include "data/text_data.h"
#include "data/generic_data.h"
#include "data/menus/title_screen.h"
#include "data/sprite_data.h"
#include "data/sprites/hornoad.h"
#include "data/sprites/x_parasite.h"
#include "data/projectile_data.h"
#include "data/audio.h"

extern const u16 sElevatorMonologueBgPal_6638c0[];
extern const u16 sElevatorMonologueBgPal_66aa68[];
extern const u16 sElevatorMonologueBgPal_671a04[];
extern const u16 sElevatorMonologueObjPal_663a20[];
extern const u16 sElevatorMonologueObjPal_66abc8[];
extern const u16 sElevatorMonologueObjPal_671b64[];
extern const u32 sIntroGfx_652bd4[];
extern const u32 sIntroGfx_653980[];
extern const u32 sIntroGfx_6546f4[];
extern const u32 sIntroGfx_6552a0[];
extern const u32 sIntroGfx_655f3c[];
extern const u32 sIntroGfx_656cd0[];
extern const u32 sIntroGfx_657408[];
extern const u32 sIntroGfx_6579c4[];
extern const u32 sIntroGfx_657d2c[];
extern const u32 sIntroGfx_657f60[];
extern const u32 sIntroGfx_658150[];
extern const u32 sIntroGfx_658468[];
extern const u32 sIntroGfx_658848[];
extern const u32 sIntroShipAlertBgGfx_0[];
extern const u32 sIntroShipAlertBgGfx_1[];
extern const u32 sIntroShipAlertBgGfx_2[];
extern const u32 sIntroShipAlertBgGfx_3[];
extern const u32 sIntroShipAlertBgGfx_4[];
extern const u32 sIntroShipAlertObjGfx_0[];
extern const u32 sIntroShipAlertObjGfx_1[];
extern const u32 sIntroShipAlertObjGfx_2[];
extern const u32 sIntroShipAlertObjGfx_3[];
extern const u32 sIntroShipAlertObjGfx_4[];
extern const u32 sIntroShipAlertObjGfx_5[];
extern const u8 sElevatorMonologueBgGfx_65c468[];
extern const u8 sElevatorMonologueBgGfx_663eac[];
extern const u8 sElevatorMonologueBgGfx_66b524[];
extern const u8 sElevatorMonologueBgTilemap_662cfc[];
extern const u8 sElevatorMonologueBgTilemap_66ac88[];
extern const u8 sElevatorMonologueBgTilemap_671c24[];
extern const u8 sElevatorMonologueObjGfx_65fc24[];
extern const u8 sElevatorMonologueObjGfx_667c18[];
extern const u8 sElevatorMonologueObjGfx_66ec18[];
extern const u8 sGameOverTextGfxFrench[];
extern const u8 sGameOverTextGfxGerman[];
extern const u8 sGameOverTextGfxItalian[];
extern const u8 sGameOverTextGfxJapanese[];
extern const u8 sGameOverTextGfxSpanish[];

// FrameData arrays and tile offset arrays used by the tables below
extern const struct FrameData sElevatorMonologueOam_663dd0[];
extern const struct FrameData sElevatorMonologueOam_663df8[];
extern const struct FrameData sElevatorMonologueOam_66aa30[];
extern const struct FrameData sElevatorMonologueOam_66aa58[];
extern const struct FrameData sElevatorMonologueOam_6719cc[];
extern const struct FrameData sElevatorMonologueOam_6719f4[];
extern const struct FrameData sFileSelectAudioLogosOam4_740800[];
extern const struct FrameData sFileSelectAudioLogosOam4_740820[];
extern const struct FrameData sFileSelectAudioLogosOam4_740840[];
extern const struct FrameData sFileSelectCopyArrowIdleOam[];
extern const struct FrameData sFileSelectDeleteArrowIdleOam_740ac8[];
extern const struct FrameData sFileSelectDeleteArrowIdleOam_740ad8[];
extern const struct FrameData sFileSelectDeleteArrowIdleOam_740ae8[];
extern const struct FrameData sFileSelectDeleteArrowIdleOam_740b08[];
extern const struct FrameData sFileSelectDeleteArrowIdleOam_740b28[];
extern const struct FrameData sFileSelectFilePanelOam3_7409d8[];
extern const struct FrameData sFileSelectFilePanelOam3_7409e8[];
extern const struct FrameData sFileSelectFilePanelOam3_7409f8[];
extern const struct FrameData sFileSelectFilePanelOam3_740a08[];
extern const struct FrameData sFileSelectFilePanelOam3_740a18[];
extern const struct FrameData sFileSelectFilePanelOam3_740a28[];
extern const struct FrameData sFileSelectFilePanelOam3_740a38[];
extern const struct FrameData sFileSelectOam_7408c0[];
extern const struct FrameData sFileSelectOam_740ba8[];
extern const struct FrameData sFileSelectOam_740bb8[];
extern const struct FrameData sFileSelectOam_740bc8[];
extern const struct FrameData sFileSelectOam_740bd8[];
extern const struct FrameData sFileSelectOam_740be8[];
extern const struct FrameData sFileSelectOam_740bf8[];
extern const struct FrameData sFileSelectOam_740c08[];
extern const struct FrameData sFileSelectOam_740c18[];
extern const struct FrameData sFileSelectOam_740c28[];
extern const struct FrameData sFileSelectOam_740c38[];
extern const struct FrameData sFileSelectOam_740c48[];
extern const struct FrameData sFileSelectOam_740c58[];
extern const struct FrameData sFileSelectOam_740c68[];
extern const struct FrameData sFileSelectOam_740c78[];
extern const struct FrameData sFileSelectOam_740c88[];
extern const struct FrameData sFileSelectOam_740c98[];
extern const struct FrameData sFileSelectOam_740ca8[];
extern const struct FrameData sFileSelectOam_740cb8[];
extern const struct FrameData sFileSelectOam_740cc8[];
extern const struct FrameData sFileSelectOam_740cd8[];
extern const struct FrameData sFileSelectOam_740ce8[];
extern const struct FrameData sFileSelectOam_740cf8[];
extern const struct FrameData sGameOverCursorOverlayOam[];
extern const struct FrameData sGameOverCursorOverlayOam_73c29c[];
extern const struct FrameData sIntroDepthParticleOam_0[];
extern const struct FrameData sIntroDepthParticleOam_1[];
extern const struct FrameData sIntroDepthParticleOam_2[];
extern const struct FrameData sIntroDepthParticleOam_3[];
extern const u16 sFileSelectTextTileOffsets_73dbcc[];
extern const u16 sFileSelectTextTileOffsets_73dbd8[];
extern const u16 sFileSelectTextTileOffsets_73dbde[];
extern const u16 sFileSelectTextTileOffsets_73dbe4[];
extern const u16 sFileSelectTextTileOffsets_73dbea[];
extern const u16 sFileSelectTextTileOffsets_73dbf6[];
extern const u16 sFileSelectTextTileOffsets_73dbfc[];
extern const u16 sFileSelectTextTileOffsets_73dc02[];
extern const u16 sFileSelectTextTileOffsets_73dc08[];
extern const u16 sFileSelectTextTileOffsets_73dc14[];

// File select strings
extern const u16 sFileSelectTextJapanese_0[];
extern const u16 sFileSelectTextJapanese_1[];
extern const u16 sFileSelectTextJapanese_2[];
extern const u16 sFileSelectTextJapanese_3[];
extern const u16 sFileSelectTextJapanese_4[];
extern const u16 sFileSelectTextJapanese_5[];
extern const u16 sFileSelectTextJapanese_6[];
extern const u16 sFileSelectTextJapanese_7[];
extern const u16 sFileSelectTextJapanese_8[];
extern const u16 sFileSelectTextJapanese_9[];
extern const u16 sFileSelectTextJapanese_10[];
extern const u16 sFileSelectTextJapanese_11[];
extern const u16 sFileSelectTextJapanese_12[];
extern const u16 sFileSelectTextJapanese_13[];
extern const u16 sFileSelectTextJapanese_14[];
extern const u16 sFileSelectTextJapanese_15[];
extern const u16 sFileSelectTextJapanese_16[];
extern const u16 sFileSelectTextJapanese_17[];
extern const u16 sFileSelectTextJapanese_18[];
extern const u16 sFileSelectTextJapanese_19[];
extern const u16 sFileSelectTextJapanese_20[];
extern const u16 sFileSelectTextJapanese_21[];
extern const u16 sFileSelectTextJapanese_22[];
extern const u16 sFileSelectTextJapanese_23[];
extern const u16 sFileSelectTextJapanese_24[];
extern const u16 sFileSelectTextEnglish_0[];
extern const u16 sFileSelectTextEnglish_1[];
extern const u16 sFileSelectTextEnglish_2[];
extern const u16 sFileSelectTextEnglish_3[];
extern const u16 sFileSelectTextEnglish_4[];
extern const u16 sFileSelectTextEnglish_5[];
extern const u16 sFileSelectTextEnglish_6[];
extern const u16 sFileSelectTextEnglish_7[];
extern const u16 sFileSelectTextEnglish_8[];
extern const u16 sFileSelectTextEnglish_9[];
extern const u16 sFileSelectTextEnglish_10[];
extern const u16 sFileSelectTextEnglish_11[];
extern const u16 sFileSelectTextEnglish_12[];
extern const u16 sFileSelectTextEnglish_13[];
extern const u16 sFileSelectTextEnglish_14[];
extern const u16 sFileSelectTextEnglish_15[];
extern const u16 sFileSelectTextEnglish_16[];
extern const u16 sFileSelectTextEnglish_17[];
extern const u16 sFileSelectTextEnglish_18[];
extern const u16 sFileSelectTextEnglish_19[];
extern const u16 sFileSelectTextEnglish_20[];
extern const u16 sFileSelectTextEnglish_21[];
extern const u16 sFileSelectTextEnglish_22[];
extern const u16 sFileSelectTextEnglish_23[];
extern const u16 sFileSelectTextEnglish_24[];
extern const u16 sFileSelectTextGerman_0[];
extern const u16 sFileSelectTextGerman_1[];
extern const u16 sFileSelectTextGerman_2[];
extern const u16 sFileSelectTextGerman_3[];
extern const u16 sFileSelectTextGerman_4[];
extern const u16 sFileSelectTextGerman_5[];
extern const u16 sFileSelectTextGerman_6[];
extern const u16 sFileSelectTextGerman_7[];
extern const u16 sFileSelectTextGerman_8[];
extern const u16 sFileSelectTextGerman_9[];
extern const u16 sFileSelectTextGerman_10[];
extern const u16 sFileSelectTextGerman_11[];
extern const u16 sFileSelectTextGerman_12[];
extern const u16 sFileSelectTextGerman_13[];
extern const u16 sFileSelectTextGerman_14[];
extern const u16 sFileSelectTextGerman_15[];
extern const u16 sFileSelectTextGerman_16[];
extern const u16 sFileSelectTextGerman_17[];
extern const u16 sFileSelectTextGerman_18[];
extern const u16 sFileSelectTextGerman_19[];
extern const u16 sFileSelectTextGerman_20[];
extern const u16 sFileSelectTextGerman_21[];
extern const u16 sFileSelectTextGerman_22[];
extern const u16 sFileSelectTextGerman_23[];
extern const u16 sFileSelectTextGerman_24[];
extern const u16 sFileSelectTextFrench_0[];
extern const u16 sFileSelectTextFrench_1[];
extern const u16 sFileSelectTextFrench_2[];
extern const u16 sFileSelectTextFrench_3[];
extern const u16 sFileSelectTextFrench_4[];
extern const u16 sFileSelectTextFrench_5[];
extern const u16 sFileSelectTextFrench_6[];
extern const u16 sFileSelectTextFrench_7[];
extern const u16 sFileSelectTextFrench_8[];
extern const u16 sFileSelectTextFrench_9[];
extern const u16 sFileSelectTextFrench_10[];
extern const u16 sFileSelectTextFrench_11[];
extern const u16 sFileSelectTextFrench_12[];
extern const u16 sFileSelectTextFrench_13[];
extern const u16 sFileSelectTextFrench_14[];
extern const u16 sFileSelectTextFrench_15[];
extern const u16 sFileSelectTextFrench_16[];
extern const u16 sFileSelectTextFrench_17[];
extern const u16 sFileSelectTextFrench_18[];
extern const u16 sFileSelectTextFrench_19[];
extern const u16 sFileSelectTextFrench_20[];
extern const u16 sFileSelectTextFrench_21[];
extern const u16 sFileSelectTextFrench_22[];
extern const u16 sFileSelectTextFrench_23[];
extern const u16 sFileSelectTextFrench_24[];
extern const u16 sFileSelectTextItalian_0[];
extern const u16 sFileSelectTextItalian_1[];
extern const u16 sFileSelectTextItalian_2[];
extern const u16 sFileSelectTextItalian_3[];
extern const u16 sFileSelectTextItalian_4[];
extern const u16 sFileSelectTextItalian_5[];
extern const u16 sFileSelectTextItalian_6[];
extern const u16 sFileSelectTextItalian_7[];
extern const u16 sFileSelectTextItalian_8[];
extern const u16 sFileSelectTextItalian_9[];
extern const u16 sFileSelectTextItalian_10[];
extern const u16 sFileSelectTextItalian_11[];
extern const u16 sFileSelectTextItalian_12[];
extern const u16 sFileSelectTextItalian_13[];
extern const u16 sFileSelectTextItalian_14[];
extern const u16 sFileSelectTextItalian_15[];
extern const u16 sFileSelectTextItalian_16[];
extern const u16 sFileSelectTextItalian_17[];
extern const u16 sFileSelectTextItalian_18[];
extern const u16 sFileSelectTextItalian_19[];
extern const u16 sFileSelectTextItalian_20[];
extern const u16 sFileSelectTextItalian_21[];
extern const u16 sFileSelectTextItalian_22[];
extern const u16 sFileSelectTextItalian_23[];
extern const u16 sFileSelectTextItalian_24[];
extern const u16 sFileSelectTextSpanish_0[];
extern const u16 sFileSelectTextSpanish_1[];
extern const u16 sFileSelectTextSpanish_2[];
extern const u16 sFileSelectTextSpanish_3[];
extern const u16 sFileSelectTextSpanish_4[];
extern const u16 sFileSelectTextSpanish_5[];
extern const u16 sFileSelectTextSpanish_6[];
extern const u16 sFileSelectTextSpanish_7[];
extern const u16 sFileSelectTextSpanish_8[];
extern const u16 sFileSelectTextSpanish_9[];
extern const u16 sFileSelectTextSpanish_10[];
extern const u16 sFileSelectTextSpanish_11[];
extern const u16 sFileSelectTextSpanish_12[];
extern const u16 sFileSelectTextSpanish_13[];
extern const u16 sFileSelectTextSpanish_14[];
extern const u16 sFileSelectTextSpanish_15[];
extern const u16 sFileSelectTextSpanish_16[];
extern const u16 sFileSelectTextSpanish_17[];
extern const u16 sFileSelectTextSpanish_18[];
extern const u16 sFileSelectTextSpanish_19[];
extern const u16 sFileSelectTextSpanish_20[];
extern const u16 sFileSelectTextSpanish_21[];
extern const u16 sFileSelectTextSpanish_22[];
extern const u16 sFileSelectTextSpanish_23[];
extern const u16 sFileSelectTextSpanish_24[];
extern const u16 sFileSelectEmptyFileText_0[];
extern const u16 sFileSelectEmptyFileText_1[];

void SpecialCutsceneLoadingVblank(void); // For V-blank callback
u8 SpecialCutsceneGetRandomNumber(void);

static u16* sMonologueTextPointersJapanese[19];
static u16* sMonologueTextPointersEnglish[19];
static u16* sMonologueTextPointersGerman[19];
static u16* sMonologueTextPointersFrench[19];
static u16* sMonologueTextPointersItalian[19];
static u16* sMonologueTextPointersSpanish[19];

const u8* sTitleScreenDebugTextPointer = {
    sTitleScreenDebugText,
};

const struct FrameData* sIntroHorizontalParticleOamPointers[6] = {
    sIntroParticleOam_0,
    sIntroParticleOam_1,
    sIntroParticleOam_2,
    sIntroParticleOam_3,
    sIntroParticleOam_2,
    sIntroParticleOam_1
};

static const u16* sIntroNervousSystemPalPointers[12] = {
	sIntroNervousSystemPal_0,
	sIntroNervousSystemPal_1,
	sIntroNervousSystemPal_2,
	sIntroNervousSystemPal_3,
	sIntroNervousSystemPal_4,
	sIntroNervousSystemPal_5,
	sIntroNervousSystemPal_6,
	sIntroNervousSystemPal_7,
	sIntroNervousSystemPal_8,
	sIntroNervousSystemPal_9,
	sIntroNervousSystemPal_10,
	sIntroNervousSystemPal_11
};

static const u16* sIntroSamusCuredBgFadePalPointers[16] = {
	sIntroSamusCuredBgFadePal_0,
	sIntroSamusCuredBgFadePal_1,
	sIntroSamusCuredBgFadePal_2,
	sIntroSamusCuredBgFadePal_3,
	sIntroSamusCuredBgFadePal_4,
	sIntroSamusCuredBgFadePal_5,
	sIntroSamusCuredBgFadePal_6,
	sIntroSamusCuredBgFadePal_7,
	sIntroSamusCuredBgFadePal_8,
	sIntroSamusCuredBgFadePal_9,
	sIntroSamusCuredBgFadePal_10,
	sIntroSamusCuredBgFadePal_11,
	sIntroSamusCuredBgFadePal_12,
	sIntroSamusCuredBgFadePal_13,
	sIntroSamusCuredBgFadePal_14,
	sIntroSamusCuredBgFadePal_15
};

static const u16* sIntroSamusCuredFadePalPointers[16] = {
	sIntroSamusCuredFadePal_0,
	sIntroSamusCuredFadePal_1,
	sIntroSamusCuredFadePal_2,
	sIntroSamusCuredFadePal_3,
	sIntroSamusCuredFadePal_4,
	sIntroSamusCuredFadePal_5,
	sIntroSamusCuredFadePal_6,
	sIntroSamusCuredFadePal_7,
	sIntroSamusCuredFadePal_8,
	sIntroSamusCuredFadePal_9,
	sIntroSamusCuredFadePal_10,
	sIntroSamusCuredFadePal_11,
	sIntroSamusCuredFadePal_12,
	sIntroSamusCuredFadePal_13,
	sIntroSamusCuredFadePal_14,
	sIntroSamusCuredFadePal_15
};

const struct FrameData* sIntroSpaceViewParticleOam[6] = {
    sIntroDepthParticleOam_0,
    sIntroDepthParticleOam_1,
    sIntroDepthParticleOam_2,
    sIntroDepthParticleOam_3,
    sIntroDepthParticleOam_2,
    sIntroDepthParticleOam_1
};
u16** sEndingDialogueTextTables[LANGUAGE_COUNT] = {
    [LANGUAGE_JAPANESE] = (u16**)sNavConversationTextPointersJapanese,
    [LANGUAGE_HIRAGANA] = (u16**)sNavConversationTextPointersHiragana,
    [LANGUAGE_ENGLISH] = (u16**)sNavConversationTextPointersEnglish,
    [LANGUAGE_GERMAN] = (u16**)sNavConversationTextPointersGerman,
    [LANGUAGE_FRENCH] = (u16**)sNavConversationTextPointersFrench,
    [LANGUAGE_ITALIAN] = (u16**)sNavConversationTextPointersItalian,
    [LANGUAGE_SPANISH] = (u16**)sNavConversationTextPointersSpanish
};

static const u32* sIntroSr388SurfaceBgGfxPointers[8] = {
    sIntroSr388SurfaceBgGfx0,
    sIntroSr388SurfaceBgGfx1,
    sIntroSr388SurfaceBgGfx2,
    sIntroSr388SurfaceBgGfx3,
    sIntroSr388SurfaceBgGfx4,
    sIntroSr388SurfaceBgGfx5,
    sIntroSr388SurfaceBgGfx6,
    sIntroSr388SurfaceBgGfx7
};

static const u32* sIntroSr388PlanetBgGfxPointers[5] = {
    sIntroSr388PlanetBgGfx0,
    sIntroSr388PlanetBgGfx1,
    sIntroSr388PlanetBgGfx2,
    sIntroSr388PlanetBgGfx3,
    sIntroSr388PlanetBgGfx4
};

static const u32* sIntroBslObjectGfxPointers[8] = {
    sIntroBslObjectGfx0,
    sIntroBslObjectGfx1,
    sIntroBslObjectGfx2,
    sIntroBslObjectGfx3,
    sIntroBslObjectGfx4,
    sIntroBslObjectGfx5,
    sIntroBslObjectGfx6,
    sIntroBslObjectGfx7
};

const u32* sIntroSamusSittingBgGfxPointers[5] = {
    sIntroSamusSittingBgGfx0,
    sIntroSamusSittingBgGfx1,
    sIntroSamusSittingBgGfx2,
    sIntroSamusSittingBgGfx3,
    sIntroSamusSittingBgGfx4
};

static const u32* sIntroSamusHelmetCloseupBgGfxPointers[6] = {
    sIntroSamusHelmetCloseupBgGfx0,
    sIntroSamusHelmetCloseupBgGfx1,
    sIntroSamusHelmetCloseupBgGfx2,
    sIntroSamusHelmetCloseupBgGfx3,
    sIntroSamusHelmetCloseupBgGfx4,
    sIntroSamusHelmetCloseupBgGfx5
};

const u32* sIntroShipAlertBgGfxPointers[5] = {
    sIntroShipAlertBgGfx_0,
    sIntroShipAlertBgGfx_1,
    sIntroShipAlertBgGfx_2,
    sIntroShipAlertBgGfx_3,
    sIntroShipAlertBgGfx_4
};
const u32* sIntroShipAlertObjGfxPointers[6] = {
    sIntroShipAlertObjGfx_0,
    sIntroShipAlertObjGfx_1,
    sIntroShipAlertObjGfx_2,
    sIntroShipAlertObjGfx_3,
    sIntroShipAlertObjGfx_4,
    sIntroShipAlertObjGfx_5
};
const u32* sIntroGfxPointers_79c474[13] = {
    sIntroGfx_652bd4,
    sIntroGfx_653980,
    sIntroGfx_6546f4,
    sIntroGfx_6552a0,
    sIntroGfx_655f3c,
    sIntroGfx_656cd0,
    sIntroGfx_657408,
    sIntroGfx_6579c4,
    sIntroGfx_657d2c,
    sIntroGfx_657f60,
    sIntroGfx_658150,
    sIntroGfx_658468,
    sIntroGfx_658848
};
const u16* sElevatorMonologueBgPalPointers[9] = {
    sElevatorMonologueBgPal_6638c0,
    sElevatorMonologueBgPal_66aa68,
    sElevatorMonologueBgPal_6638c0,
    sElevatorMonologueBgPal_6638c0,
    sElevatorMonologueBgPal_66aa68,
    sElevatorMonologueBgPal_671a04,
    sElevatorMonologueBgPal_6638c0,
    sElevatorMonologueBgPal_6638c0,
    sElevatorMonologueBgPal_6638c0
};
const u16* sElevatorMonologueObjPalPointers[9] = {
    sElevatorMonologueObjPal_663a20,
    sElevatorMonologueObjPal_663a20,
    sElevatorMonologueObjPal_663a20,
    sElevatorMonologueObjPal_663a20,
    sElevatorMonologueObjPal_66abc8,
    sElevatorMonologueObjPal_671b64,
    sElevatorMonologueObjPal_663a20,
    sElevatorMonologueObjPal_663a20,
    sElevatorMonologueObjPal_663a20
};
const u8* sElevatorMonologueBgGfxPointers[9] = {
    sElevatorMonologueBgGfx_65c468,
    sElevatorMonologueBgGfx_663eac,
    sElevatorMonologueBgGfx_65c468,
    sElevatorMonologueBgGfx_65c468,
    sElevatorMonologueBgGfx_663eac,
    sElevatorMonologueBgGfx_66b524,
    sElevatorMonologueBgGfx_65c468,
    sElevatorMonologueBgGfx_65c468,
    sElevatorMonologueBgGfx_65c468
};
const u8* sElevatorMonologueObjGfxPointers[9] = {
    sElevatorMonologueObjGfx_65fc24,
    sElevatorMonologueObjGfx_65fc24,
    sElevatorMonologueObjGfx_65fc24,
    sElevatorMonologueObjGfx_65fc24,
    sElevatorMonologueObjGfx_667c18,
    sElevatorMonologueObjGfx_66ec18,
    sElevatorMonologueObjGfx_65fc24,
    sElevatorMonologueObjGfx_65fc24,
    sElevatorMonologueObjGfx_65fc24
};
const u8* sElevatorMonologueBgTilemapPointers[9] = {
    sElevatorMonologueBgTilemap_662cfc,
    sElevatorMonologueBgTilemap_66ac88,
    sElevatorMonologueBgTilemap_662cfc,
    sElevatorMonologueBgTilemap_662cfc,
    sElevatorMonologueBgTilemap_66ac88,
    sElevatorMonologueBgTilemap_671c24,
    sElevatorMonologueBgTilemap_662cfc,
    sElevatorMonologueBgTilemap_662cfc,
    sElevatorMonologueBgTilemap_662cfc
};
const struct FrameData* sElevatorMonologueOam[9][2] = {
    {
        sElevatorMonologueOam_663dd0,
        sElevatorMonologueOam_663df8
    },
    {
        sElevatorMonologueOam_663dd0,
        sElevatorMonologueOam_663df8
    },
    {
        sElevatorMonologueOam_663dd0,
        sElevatorMonologueOam_663df8
    },
    {
        sElevatorMonologueOam_663dd0,
        sElevatorMonologueOam_663df8
    },
    {
        sElevatorMonologueOam_66aa30,
        sElevatorMonologueOam_66aa58
    },
    {
        sElevatorMonologueOam_6719cc,
        sElevatorMonologueOam_6719f4
    },
    {
        sElevatorMonologueOam_663dd0,
        sElevatorMonologueOam_663df8
    },
    {
        sElevatorMonologueOam_663dd0,
        sElevatorMonologueOam_663df8
    },
    {
        sElevatorMonologueOam_663dd0,
        sElevatorMonologueOam_663df8
    }
};

u16** sMonologueTextPointers[LANGUAGE_COUNT] = {
    sMonologueTextPointersJapanese,
    sMonologueTextPointersJapanese,
    sMonologueTextPointersEnglish,
    sMonologueTextPointersGerman,
    sMonologueTextPointersFrench,
    sMonologueTextPointersItalian,
    sMonologueTextPointersSpanish
};

const u16* sMessageTextPointersJapanese[48] = {
    sMessageTextJapanese_0,
    sMessageTextJapanese_1,
    sMessageTextJapanese_2,
    sMessageTextJapanese_3,
    sMessageTextJapanese_4,
    sMessageTextJapanese_5,
    sMessageTextJapanese_6,
    sMessageTextJapanese_7,
    sMessageTextJapanese_8,
    sMessageTextJapanese_9,
    sMessageTextJapanese_10,
    sMessageTextJapanese_11,
    sMessageTextJapanese_12,
    sMessageTextJapanese_13,
    sMessageTextJapanese_14,
    sMessageTextJapanese_15,
    sMessageTextJapanese_16,
    sMessageTextJapanese_17,
    sMessageTextJapanese_18,
    sMessageTextJapanese_19,
    sMessageTextJapanese_20,
    sMessageTextJapanese_21,
    sMessageTextJapanese_22,
    sMessageTextJapanese_23,
    sMessageTextJapanese_24,
    sMessageTextJapanese_25,
    sMessageTextJapanese_26,
    sMessageTextJapanese_27,
    sMessageTextJapanese_28,
    sMessageTextJapanese_29,
    sMessageTextJapanese_30,
    sMessageTextJapanese_31,
    sMessageTextJapanese_32,
    sMessageTextJapanese_33,
    sMessageTextJapanese_34,
    sMessageTextJapanese_35,
    sMessageTextJapanese_36,
    sMessageTextJapanese_37,
    sMessageTextJapanese_38,
    sMessageTextJapanese_39,
    sMessageTextJapanese_40,
    sMessageTextJapanese_41,
    sMessageTextJapanese_42,
    sMessageTextJapanese_43,
    sMessageTextJapanese_44,
    sMessageTextJapanese_45,
    sMessageTextJapanese_46,
    sMessageTextJapanese_47
};
const u16* sLocationTextPointersJapanese[26] = {
    sLocationTextJapanese_0,
    sLocationTextJapanese_1,
    sLocationTextJapanese_2,
    sLocationTextJapanese_3,
    sLocationTextJapanese_4,
    sLocationTextJapanese_5,
    sLocationTextJapanese_6,
    sLocationTextJapanese_7,
    sLocationTextJapanese_8,
    sLocationTextJapanese_9,
    sLocationTextJapanese_10,
    sLocationTextJapanese_11,
    sLocationTextJapanese_12,
    sLocationTextJapanese_13,
    sLocationTextJapanese_14,
    sLocationTextJapanese_15,
    sLocationTextJapanese_16,
    sLocationTextJapanese_17,
    sLocationTextJapanese_18,
    sLocationTextJapanese_19,
    sLocationTextJapanese_20,
    sLocationTextJapanese_21,
    sLocationTextJapanese_22,
    sLocationTextJapanese_23,
    sLocationTextJapanese_24,
    sLocationTextJapanese_25
};
const u16* sMessageTextPointersHiragana[48] = {
    sMessageTextHiragana_0,
    sMessageTextHiragana_1,
    sMessageTextHiragana_2,
    sMessageTextHiragana_3,
    sMessageTextHiragana_4,
    sMessageTextHiragana_5,
    sMessageTextHiragana_6,
    sMessageTextHiragana_7,
    sMessageTextHiragana_8,
    sMessageTextHiragana_9,
    sMessageTextHiragana_10,
    sMessageTextHiragana_11,
    sMessageTextHiragana_12,
    sMessageTextHiragana_13,
    sMessageTextHiragana_14,
    sMessageTextHiragana_15,
    sMessageTextHiragana_16,
    sMessageTextHiragana_17,
    sMessageTextHiragana_18,
    sMessageTextHiragana_19,
    sMessageTextHiragana_20,
    sMessageTextHiragana_21,
    sMessageTextHiragana_22,
    sMessageTextHiragana_23,
    sMessageTextHiragana_24,
    sMessageTextHiragana_25,
    sMessageTextHiragana_26,
    sMessageTextHiragana_27,
    sMessageTextHiragana_28,
    sMessageTextHiragana_29,
    sMessageTextHiragana_30,
    sMessageTextHiragana_31,
    sMessageTextHiragana_32,
    sMessageTextHiragana_33,
    sMessageTextHiragana_34,
    sMessageTextHiragana_35,
    sMessageTextHiragana_36,
    sMessageTextHiragana_37,
    sMessageTextHiragana_38,
    sMessageTextHiragana_39,
    sMessageTextHiragana_40,
    sMessageTextHiragana_41,
    sMessageTextHiragana_42,
    sMessageTextHiragana_43,
    sMessageTextHiragana_44,
    sMessageTextHiragana_45,
    sMessageTextHiragana_46,
    sMessageTextHiragana_47
};
const u16* sLocationTextPointersHiragana[26] = {
    sLocationTextHiragana_0,
    sLocationTextHiragana_1,
    sLocationTextHiragana_2,
    sLocationTextHiragana_3,
    sLocationTextHiragana_4,
    sLocationTextHiragana_5,
    sLocationTextHiragana_6,
    sLocationTextHiragana_7,
    sLocationTextHiragana_8,
    sLocationTextHiragana_9,
    sLocationTextHiragana_10,
    sLocationTextHiragana_11,
    sLocationTextHiragana_12,
    sLocationTextHiragana_13,
    sLocationTextHiragana_14,
    sLocationTextHiragana_15,
    sLocationTextHiragana_16,
    sLocationTextHiragana_17,
    sLocationTextHiragana_18,
    sLocationTextHiragana_19,
    sLocationTextHiragana_20,
    sLocationTextHiragana_21,
    sLocationTextHiragana_22,
    sLocationTextHiragana_23,
    sLocationTextHiragana_24,
    sLocationTextHiragana_25
};
const u16* sMessageTextPointersEnglish[48] = {
    sMessageTextEnglish_0,
    sMessageTextEnglish_1,
    sMessageTextEnglish_2,
    sMessageTextEnglish_3,
    sMessageTextEnglish_4,
    sMessageTextEnglish_5,
    sMessageTextEnglish_6,
    sMessageTextEnglish_7,
    sMessageTextEnglish_8,
    sMessageTextEnglish_9,
    sMessageTextEnglish_10,
    sMessageTextEnglish_11,
    sMessageTextEnglish_12,
    sMessageTextEnglish_13,
    sMessageTextEnglish_14,
    sMessageTextEnglish_15,
    sMessageTextEnglish_16,
    sMessageTextEnglish_17,
    sMessageTextEnglish_18,
    sMessageTextEnglish_19,
    sMessageTextEnglish_20,
    sMessageTextEnglish_21,
    sMessageTextEnglish_22,
    sMessageTextEnglish_23,
    sMessageTextEnglish_24,
    sMessageTextEnglish_25,
    sMessageTextEnglish_26,
    sMessageTextEnglish_27,
    sMessageTextEnglish_28,
    sMessageTextEnglish_29,
    sMessageTextEnglish_30,
    sMessageTextEnglish_31,
    sMessageTextEnglish_32,
    sMessageTextEnglish_33,
    sMessageTextEnglish_34,
    sMessageTextEnglish_35,
    sMessageTextEnglish_36,
    sMessageTextEnglish_37,
    sMessageTextEnglish_38,
    sMessageTextEnglish_39,
    sMessageTextEnglish_40,
    sMessageTextEnglish_41,
    sMessageTextEnglish_42,
    sMessageTextEnglish_43,
    sMessageTextEnglish_44,
    sMessageTextEnglish_45,
    sMessageTextEnglish_46,
    sMessageTextEnglish_47
};
const u16* sLocationTextPointersEnglish[26] = {
    sLocationTextEnglish_0,
    sLocationTextEnglish_1,
    sLocationTextEnglish_2,
    sLocationTextEnglish_3,
    sLocationTextEnglish_4,
    sLocationTextEnglish_5,
    sLocationTextEnglish_6,
    sLocationTextEnglish_7,
    sLocationTextEnglish_8,
    sLocationTextEnglish_9,
    sLocationTextEnglish_10,
    sLocationTextEnglish_11,
    sLocationTextEnglish_12,
    sLocationTextEnglish_13,
    sLocationTextEnglish_14,
    sLocationTextEnglish_15,
    sLocationTextEnglish_16,
    sLocationTextEnglish_17,
    sLocationTextEnglish_18,
    sLocationTextEnglish_19,
    sLocationTextEnglish_20,
    sLocationTextEnglish_21,
    sLocationTextEnglish_22,
    sLocationTextEnglish_23,
    sLocationTextEnglish_24,
    sLocationTextEnglish_25
};
const u16* sMessageTextPointersGerman[48] = {
    sMessageTextGerman_0,
    sMessageTextGerman_1,
    sMessageTextGerman_2,
    sMessageTextGerman_3,
    sMessageTextGerman_4,
    sMessageTextGerman_5,
    sMessageTextGerman_6,
    sMessageTextGerman_7,
    sMessageTextGerman_8,
    sMessageTextGerman_9,
    sMessageTextGerman_10,
    sMessageTextGerman_11,
    sMessageTextGerman_12,
    sMessageTextGerman_13,
    sMessageTextGerman_14,
    sMessageTextGerman_15,
    sMessageTextGerman_16,
    sMessageTextGerman_17,
    sMessageTextGerman_18,
    sMessageTextGerman_19,
    sMessageTextGerman_20,
    sMessageTextGerman_21,
    sMessageTextGerman_22,
    sMessageTextGerman_23,
    sMessageTextGerman_24,
    sMessageTextGerman_25,
    sMessageTextGerman_26,
    sMessageTextGerman_27,
    sMessageTextGerman_28,
    sMessageTextGerman_29,
    sMessageTextGerman_30,
    sMessageTextGerman_31,
    sMessageTextGerman_32,
    sMessageTextGerman_33,
    sMessageTextGerman_34,
    sMessageTextGerman_35,
    sMessageTextGerman_36,
    sMessageTextGerman_37,
    sMessageTextGerman_38,
    sMessageTextGerman_39,
    sMessageTextGerman_40,
    sMessageTextGerman_41,
    sMessageTextGerman_42,
    sMessageTextGerman_43,
    sMessageTextGerman_44,
    sMessageTextGerman_45,
    sMessageTextGerman_46,
    sMessageTextGerman_47
};
const u16* sLocationTextPointersGerman[26] = {
    sLocationTextGerman_0,
    sLocationTextGerman_1,
    sLocationTextGerman_2,
    sLocationTextGerman_3,
    sLocationTextGerman_4,
    sLocationTextGerman_5,
    sLocationTextGerman_6,
    sLocationTextGerman_7,
    sLocationTextGerman_8,
    sLocationTextGerman_9,
    sLocationTextGerman_10,
    sLocationTextGerman_11,
    sLocationTextGerman_12,
    sLocationTextGerman_13,
    sLocationTextGerman_14,
    sLocationTextGerman_15,
    sLocationTextGerman_16,
    sLocationTextGerman_17,
    sLocationTextGerman_18,
    sLocationTextGerman_19,
    sLocationTextGerman_20,
    sLocationTextGerman_21,
    sLocationTextGerman_22,
    sLocationTextGerman_23,
    sLocationTextGerman_24,
    sLocationTextGerman_25
};
const u16* sMessageTextPointersFrench[48] = {
    sMessageTextFrench_0,
    sMessageTextFrench_1,
    sMessageTextFrench_2,
    sMessageTextFrench_3,
    sMessageTextFrench_4,
    sMessageTextFrench_5,
    sMessageTextFrench_6,
    sMessageTextFrench_7,
    sMessageTextFrench_8,
    sMessageTextFrench_9,
    sMessageTextFrench_10,
    sMessageTextFrench_11,
    sMessageTextFrench_12,
    sMessageTextFrench_13,
    sMessageTextFrench_14,
    sMessageTextFrench_15,
    sMessageTextFrench_16,
    sMessageTextFrench_17,
    sMessageTextFrench_18,
    sMessageTextFrench_19,
    sMessageTextFrench_20,
    sMessageTextFrench_21,
    sMessageTextFrench_22,
    sMessageTextFrench_23,
    sMessageTextFrench_24,
    sMessageTextFrench_25,
    sMessageTextFrench_26,
    sMessageTextFrench_27,
    sMessageTextFrench_28,
    sMessageTextFrench_29,
    sMessageTextFrench_30,
    sMessageTextFrench_31,
    sMessageTextFrench_32,
    sMessageTextFrench_33,
    sMessageTextFrench_34,
    sMessageTextFrench_35,
    sMessageTextFrench_36,
    sMessageTextFrench_37,
    sMessageTextFrench_38,
    sMessageTextFrench_39,
    sMessageTextFrench_40,
    sMessageTextFrench_41,
    sMessageTextFrench_42,
    sMessageTextFrench_43,
    sMessageTextFrench_44,
    sMessageTextFrench_45,
    sMessageTextFrench_46,
    sMessageTextFrench_47
};
const u16* sLocationTextPointersFrench[26] = {
    sLocationTextFrench_0,
    sLocationTextFrench_1,
    sLocationTextFrench_2,
    sLocationTextFrench_3,
    sLocationTextFrench_4,
    sLocationTextFrench_5,
    sLocationTextFrench_6,
    sLocationTextFrench_7,
    sLocationTextFrench_8,
    sLocationTextFrench_9,
    sLocationTextFrench_10,
    sLocationTextFrench_11,
    sLocationTextFrench_12,
    sLocationTextFrench_13,
    sLocationTextFrench_14,
    sLocationTextFrench_15,
    sLocationTextFrench_16,
    sLocationTextFrench_17,
    sLocationTextFrench_18,
    sLocationTextFrench_19,
    sLocationTextFrench_20,
    sLocationTextFrench_21,
    sLocationTextFrench_22,
    sLocationTextFrench_23,
    sLocationTextFrench_24,
    sLocationTextFrench_25
};
const u16* sMessageTextPointersItalian[48] = {
    sMessageTextItalian_0,
    sMessageTextItalian_1,
    sMessageTextItalian_2,
    sMessageTextItalian_3,
    sMessageTextItalian_4,
    sMessageTextItalian_5,
    sMessageTextItalian_6,
    sMessageTextItalian_7,
    sMessageTextItalian_8,
    sMessageTextItalian_9,
    sMessageTextItalian_10,
    sMessageTextItalian_11,
    sMessageTextItalian_12,
    sMessageTextItalian_13,
    sMessageTextItalian_14,
    sMessageTextItalian_15,
    sMessageTextItalian_16,
    sMessageTextItalian_17,
    sMessageTextItalian_18,
    sMessageTextItalian_19,
    sMessageTextItalian_20,
    sMessageTextItalian_21,
    sMessageTextItalian_22,
    sMessageTextItalian_23,
    sMessageTextItalian_24,
    sMessageTextItalian_25,
    sMessageTextItalian_26,
    sMessageTextItalian_27,
    sMessageTextItalian_28,
    sMessageTextItalian_29,
    sMessageTextItalian_30,
    sMessageTextItalian_31,
    sMessageTextItalian_32,
    sMessageTextItalian_33,
    sMessageTextItalian_34,
    sMessageTextItalian_35,
    sMessageTextItalian_36,
    sMessageTextItalian_37,
    sMessageTextItalian_38,
    sMessageTextItalian_39,
    sMessageTextItalian_40,
    sMessageTextItalian_41,
    sMessageTextItalian_42,
    sMessageTextItalian_43,
    sMessageTextItalian_44,
    sMessageTextItalian_45,
    sMessageTextItalian_46,
    sMessageTextItalian_47
};
const u16* sLocationTextPointersItalian[26] = {
    sLocationTextItalian_0,
    sLocationTextItalian_1,
    sLocationTextItalian_2,
    sLocationTextItalian_3,
    sLocationTextItalian_4,
    sLocationTextItalian_5,
    sLocationTextItalian_6,
    sLocationTextItalian_7,
    sLocationTextItalian_8,
    sLocationTextItalian_9,
    sLocationTextItalian_10,
    sLocationTextItalian_11,
    sLocationTextItalian_12,
    sLocationTextItalian_13,
    sLocationTextItalian_14,
    sLocationTextItalian_15,
    sLocationTextItalian_16,
    sLocationTextItalian_17,
    sLocationTextItalian_18,
    sLocationTextItalian_19,
    sLocationTextItalian_20,
    sLocationTextItalian_21,
    sLocationTextItalian_22,
    sLocationTextItalian_23,
    sLocationTextItalian_24,
    sLocationTextItalian_25
};
const u16* sMessageTextPointersSpanish[48] = {
    sMessageTextSpanish_0,
    sMessageTextSpanish_1,
    sMessageTextSpanish_2,
    sMessageTextSpanish_3,
    sMessageTextSpanish_4,
    sMessageTextSpanish_5,
    sMessageTextSpanish_6,
    sMessageTextSpanish_7,
    sMessageTextSpanish_8,
    sMessageTextSpanish_9,
    sMessageTextSpanish_10,
    sMessageTextSpanish_11,
    sMessageTextSpanish_12,
    sMessageTextSpanish_13,
    sMessageTextSpanish_14,
    sMessageTextSpanish_15,
    sMessageTextSpanish_16,
    sMessageTextSpanish_17,
    sMessageTextSpanish_18,
    sMessageTextSpanish_19,
    sMessageTextSpanish_20,
    sMessageTextSpanish_21,
    sMessageTextSpanish_22,
    sMessageTextSpanish_23,
    sMessageTextSpanish_24,
    sMessageTextSpanish_25,
    sMessageTextSpanish_26,
    sMessageTextSpanish_27,
    sMessageTextSpanish_28,
    sMessageTextSpanish_29,
    sMessageTextSpanish_30,
    sMessageTextSpanish_31,
    sMessageTextSpanish_32,
    sMessageTextSpanish_33,
    sMessageTextSpanish_34,
    sMessageTextSpanish_35,
    sMessageTextSpanish_36,
    sMessageTextSpanish_37,
    sMessageTextSpanish_38,
    sMessageTextSpanish_39,
    sMessageTextSpanish_40,
    sMessageTextSpanish_41,
    sMessageTextSpanish_42,
    sMessageTextSpanish_43,
    sMessageTextSpanish_44,
    sMessageTextSpanish_45,
    sMessageTextSpanish_46,
    sMessageTextSpanish_47
};
const u16* sLocationTextPointersSpanish[26] = {
    sLocationTextSpanish_0,
    sLocationTextSpanish_1,
    sLocationTextSpanish_2,
    sLocationTextSpanish_3,
    sLocationTextSpanish_4,
    sLocationTextSpanish_5,
    sLocationTextSpanish_6,
    sLocationTextSpanish_7,
    sLocationTextSpanish_8,
    sLocationTextSpanish_9,
    sLocationTextSpanish_10,
    sLocationTextSpanish_11,
    sLocationTextSpanish_12,
    sLocationTextSpanish_13,
    sLocationTextSpanish_14,
    sLocationTextSpanish_15,
    sLocationTextSpanish_16,
    sLocationTextSpanish_17,
    sLocationTextSpanish_18,
    sLocationTextSpanish_19,
    sLocationTextSpanish_20,
    sLocationTextSpanish_21,
    sLocationTextSpanish_22,
    sLocationTextSpanish_23,
    sLocationTextSpanish_24,
    sLocationTextSpanish_25
};

const u16** sLocationTextPointers[LANGUAGE_COUNT] = {
    (const u16**)sLocationTextPointersJapanese,
    (const u16**)sLocationTextPointersHiragana,
    (const u16**)sLocationTextPointersEnglish,
    (const u16**)sLocationTextPointersGerman,
    (const u16**)sLocationTextPointersFrench,
    (const u16**)sLocationTextPointersItalian,
    (const u16**)sLocationTextPointersSpanish
};

u16** sMessageTextPointers[LANGUAGE_COUNT] = {
    (u16**)sMessageTextPointersJapanese,
    (u16**)sMessageTextPointersHiragana,
    (u16**)sMessageTextPointersEnglish,
    (u16**)sMessageTextPointersGerman,
    (u16**)sMessageTextPointersFrench,
    (u16**)sMessageTextPointersItalian,
    (u16**)sMessageTextPointersSpanish
};

const u16* sNavConversationTextPointersJapanese[114] = {
    sNavConversationTextJapanese_0,
    sNavConversationTextJapanese_1,
    sNavConversationTextJapanese_2,
    sNavConversationTextJapanese_3,
    sNavConversationTextJapanese_4,
    sNavConversationTextJapanese_5,
    sNavConversationTextJapanese_6,
    sNavConversationTextJapanese_7,
    sNavConversationTextJapanese_8,
    sNavConversationTextJapanese_9,
    sNavConversationTextJapanese_10,
    sNavConversationTextJapanese_11,
    sNavConversationTextJapanese_12,
    sNavConversationTextJapanese_13,
    sNavConversationTextJapanese_14,
    sNavConversationTextJapanese_15,
    sNavConversationTextJapanese_16,
    sNavConversationTextJapanese_17,
    sNavConversationTextJapanese_18,
    sNavConversationTextJapanese_19,
    sNavConversationTextJapanese_20,
    sNavConversationTextJapanese_21,
    sNavConversationTextJapanese_22,
    sNavConversationTextJapanese_23,
    sNavConversationTextJapanese_24,
    sNavConversationTextJapanese_25,
    sNavConversationTextJapanese_26,
    sNavConversationTextJapanese_27,
    sNavConversationTextJapanese_28,
    sNavConversationTextJapanese_29,
    sNavConversationTextJapanese_30,
    sNavConversationTextJapanese_31,
    sNavConversationTextJapanese_32,
    sNavConversationTextJapanese_33,
    sNavConversationTextJapanese_34,
    sNavConversationTextJapanese_35,
    sNavConversationTextJapanese_36,
    sNavConversationTextJapanese_37,
    sNavConversationTextJapanese_38,
    sNavConversationTextJapanese_39,
    sNavConversationTextJapanese_40,
    sNavConversationTextJapanese_41,
    sNavConversationTextJapanese_42,
    sNavConversationTextJapanese_43,
    sNavConversationTextJapanese_44,
    sNavConversationTextJapanese_45,
    sNavConversationTextJapanese_46,
    sNavConversationTextJapanese_47,
    sNavConversationTextJapanese_48,
    sNavConversationTextJapanese_49,
    sNavConversationTextJapanese_50,
    sNavConversationTextJapanese_51,
    sNavConversationTextJapanese_52,
    sNavConversationTextJapanese_53,
    sNavConversationTextJapanese_54,
    sNavConversationTextJapanese_55,
    sNavConversationTextJapanese_56,
    sNavConversationTextJapanese_57,
    sNavConversationTextJapanese_58,
    sNavConversationTextJapanese_59,
    sNavConversationTextJapanese_60,
    sNavConversationTextJapanese_61,
    sNavConversationTextJapanese_62,
    sNavConversationTextJapanese_63,
    sNavConversationTextJapanese_64,
    sNavConversationTextJapanese_65,
    sNavConversationTextJapanese_66,
    sNavConversationTextJapanese_67,
    sNavConversationTextJapanese_68,
    sNavConversationTextJapanese_69,
    sNavConversationTextJapanese_70,
    sNavConversationTextJapanese_71,
    sNavConversationTextJapanese_72,
    sNavConversationTextJapanese_73,
    sNavConversationTextJapanese_74,
    sNavConversationTextJapanese_75,
    sNavConversationTextJapanese_76,
    sNavConversationTextJapanese_77,
    sNavConversationTextJapanese_78,
    sNavConversationTextJapanese_79,
    sNavConversationTextJapanese_80,
    sNavConversationTextJapanese_81,
    sNavConversationTextJapanese_82,
    sNavConversationTextJapanese_83,
    sNavConversationTextJapanese_84,
    sNavConversationTextJapanese_85,
    sNavConversationTextJapanese_86,
    sNavConversationTextJapanese_87,
    sNavConversationTextJapanese_88,
    sNavConversationTextJapanese_89,
    sNavConversationTextJapanese_90,
    sNavConversationTextJapanese_91,
    sNavConversationTextJapanese_92,
    sNavConversationTextJapanese_93,
    sNavConversationTextJapanese_94,
    sNavConversationTextJapanese_95,
    sNavConversationTextJapanese_96,
    sNavConversationTextJapanese_97,
    sNavConversationTextJapanese_98,
    sNavConversationTextJapanese_99,
    sNavConversationTextJapanese_100,
    sNavConversationTextJapanese_101,
    sNavConversationTextJapanese_102,
    sNavConversationTextJapanese_103,
    sNavConversationTextJapanese_104,
    sNavConversationTextJapanese_105,
    sNavConversationTextJapanese_106,
    sNavConversationTextJapanese_107,
    sNavConversationTextJapanese_108,
    sNavConversationTextJapanese_109,
    sNavConversationTextJapanese_110,
    sNavConversationTextJapanese_111,
    sNavConversationTextJapanese_112,
    sNavConversationTextJapanese_113
};
const u16* sPauseScreenTextPointersJapanese[111] = {
    sPauseScreenTextJapanese_0,
    sPauseScreenTextJapanese_1,
    sPauseScreenTextJapanese_2,
    sPauseScreenTextJapanese_3,
    sPauseScreenTextJapanese_4,
    sPauseScreenTextJapanese_5,
    sPauseScreenTextJapanese_6,
    sPauseScreenTextJapanese_7,
    sPauseScreenTextJapanese_8,
    sPauseScreenTextJapanese_9,
    sPauseScreenTextJapanese_10,
    sPauseScreenTextJapanese_11,
    sPauseScreenTextJapanese_12,
    sPauseScreenTextJapanese_13,
    sPauseScreenTextJapanese_14,
    sPauseScreenTextJapanese_15,
    sPauseScreenTextJapanese_16,
    sPauseScreenTextJapanese_17,
    sPauseScreenTextJapanese_18,
    sPauseScreenTextJapanese_19,
    sPauseScreenTextJapanese_20,
    sPauseScreenTextJapanese_21,
    sPauseScreenTextJapanese_22,
    sPauseScreenTextJapanese_23,
    sPauseScreenTextJapanese_24,
    sPauseScreenTextJapanese_25,
    sPauseScreenTextJapanese_26,
    sPauseScreenTextJapanese_27,
    sPauseScreenTextJapanese_28,
    sPauseScreenTextJapanese_29,
    sPauseScreenTextJapanese_30,
    sPauseScreenTextJapanese_31,
    sPauseScreenTextJapanese_32,
    sPauseScreenTextJapanese_33,
    sPauseScreenTextJapanese_34,
    sPauseScreenTextJapanese_35,
    sPauseScreenTextJapanese_36,
    sPauseScreenTextJapanese_37,
    sPauseScreenTextJapanese_38,
    sPauseScreenTextJapanese_39,
    sPauseScreenTextJapanese_40,
    sPauseScreenTextJapanese_41,
    sPauseScreenTextJapanese_42,
    sPauseScreenTextJapanese_43,
    sPauseScreenTextJapanese_44,
    sPauseScreenTextJapanese_45,
    sPauseScreenTextJapanese_46,
    sPauseScreenTextJapanese_47,
    sPauseScreenTextJapanese_48,
    sPauseScreenTextJapanese_49,
    sPauseScreenTextJapanese_50,
    sPauseScreenTextJapanese_51,
    sPauseScreenTextJapanese_52,
    sPauseScreenTextJapanese_53,
    sPauseScreenTextJapanese_54,
    sPauseScreenTextJapanese_55,
    sPauseScreenTextJapanese_56,
    sPauseScreenTextJapanese_57,
    sPauseScreenTextJapanese_58,
    sPauseScreenTextJapanese_59,
    sPauseScreenTextJapanese_60,
    sPauseScreenTextJapanese_61,
    sPauseScreenTextJapanese_62,
    sPauseScreenTextJapanese_63,
    sPauseScreenTextJapanese_64,
    sPauseScreenTextJapanese_65,
    sPauseScreenTextJapanese_66,
    sPauseScreenTextJapanese_67,
    sPauseScreenTextJapanese_68,
    sPauseScreenTextJapanese_69,
    sPauseScreenTextJapanese_70,
    sPauseScreenTextJapanese_71,
    sPauseScreenTextJapanese_72,
    sPauseScreenTextJapanese_73,
    sPauseScreenTextJapanese_74,
    sPauseScreenTextJapanese_75,
    sPauseScreenTextJapanese_76,
    sPauseScreenTextJapanese_77,
    sPauseScreenTextJapanese_78,
    sPauseScreenTextJapanese_79,
    sPauseScreenTextJapanese_80,
    sPauseScreenTextJapanese_81,
    sPauseScreenTextJapanese_82,
    sPauseScreenTextJapanese_83,
    sPauseScreenTextJapanese_84,
    sPauseScreenTextJapanese_85,
    sPauseScreenTextJapanese_86,
    sPauseScreenTextJapanese_87,
    sPauseScreenTextJapanese_88,
    sPauseScreenTextJapanese_89,
    sPauseScreenTextJapanese_90,
    sPauseScreenTextJapanese_91,
    sPauseScreenTextJapanese_92,
    sPauseScreenTextJapanese_93,
    sPauseScreenTextJapanese_94,
    sPauseScreenTextJapanese_95,
    sPauseScreenTextJapanese_96,
    sPauseScreenTextJapanese_97,
    sPauseScreenTextJapanese_98,
    sPauseScreenTextJapanese_99,
    sPauseScreenTextJapanese_100,
    sPauseScreenTextJapanese_101,
    sPauseScreenTextJapanese_102,
    sPauseScreenTextJapanese_103,
    sPauseScreenTextJapanese_104,
    sPauseScreenTextJapanese_105,
    sPauseScreenTextJapanese_106,
    sPauseScreenTextJapanese_107,
    sPauseScreenTextJapanese_108,
    sPauseScreenTextJapanese_109,
    sPauseScreenTextJapanese_110
};
const u16* sNavConversationTextPointersHiragana[114] = {
    sNavConversationTextHiragana_0,
    sNavConversationTextHiragana_1,
    sNavConversationTextHiragana_2,
    sNavConversationTextHiragana_3,
    sNavConversationTextHiragana_4,
    sNavConversationTextHiragana_5,
    sNavConversationTextHiragana_6,
    sNavConversationTextHiragana_7,
    sNavConversationTextHiragana_8,
    sNavConversationTextHiragana_9,
    sNavConversationTextHiragana_10,
    sNavConversationTextHiragana_11,
    sNavConversationTextHiragana_12,
    sNavConversationTextHiragana_13,
    sNavConversationTextHiragana_14,
    sNavConversationTextHiragana_15,
    sNavConversationTextHiragana_16,
    sNavConversationTextHiragana_17,
    sNavConversationTextHiragana_18,
    sNavConversationTextHiragana_19,
    sNavConversationTextHiragana_20,
    sNavConversationTextHiragana_21,
    sNavConversationTextHiragana_22,
    sNavConversationTextHiragana_23,
    sNavConversationTextHiragana_24,
    sNavConversationTextHiragana_25,
    sNavConversationTextHiragana_26,
    sNavConversationTextHiragana_27,
    sNavConversationTextHiragana_28,
    sNavConversationTextHiragana_29,
    sNavConversationTextHiragana_30,
    sNavConversationTextHiragana_31,
    sNavConversationTextHiragana_32,
    sNavConversationTextHiragana_33,
    sNavConversationTextHiragana_34,
    sNavConversationTextHiragana_35,
    sNavConversationTextHiragana_36,
    sNavConversationTextHiragana_37,
    sNavConversationTextHiragana_38,
    sNavConversationTextHiragana_39,
    sNavConversationTextHiragana_40,
    sNavConversationTextHiragana_41,
    sNavConversationTextHiragana_42,
    sNavConversationTextHiragana_43,
    sNavConversationTextHiragana_44,
    sNavConversationTextHiragana_45,
    sNavConversationTextHiragana_46,
    sNavConversationTextHiragana_47,
    sNavConversationTextHiragana_48,
    sNavConversationTextHiragana_49,
    sNavConversationTextHiragana_50,
    sNavConversationTextHiragana_51,
    sNavConversationTextHiragana_52,
    sNavConversationTextHiragana_53,
    sNavConversationTextHiragana_54,
    sNavConversationTextHiragana_55,
    sNavConversationTextHiragana_56,
    sNavConversationTextHiragana_57,
    sNavConversationTextHiragana_58,
    sNavConversationTextHiragana_59,
    sNavConversationTextHiragana_60,
    sNavConversationTextHiragana_61,
    sNavConversationTextHiragana_62,
    sNavConversationTextHiragana_63,
    sNavConversationTextHiragana_64,
    sNavConversationTextHiragana_65,
    sNavConversationTextHiragana_66,
    sNavConversationTextHiragana_67,
    sNavConversationTextHiragana_68,
    sNavConversationTextHiragana_69,
    sNavConversationTextHiragana_70,
    sNavConversationTextHiragana_71,
    sNavConversationTextHiragana_72,
    sNavConversationTextHiragana_73,
    sNavConversationTextHiragana_74,
    sNavConversationTextHiragana_75,
    sNavConversationTextHiragana_76,
    sNavConversationTextHiragana_77,
    sNavConversationTextHiragana_78,
    sNavConversationTextHiragana_79,
    sNavConversationTextHiragana_80,
    sNavConversationTextHiragana_81,
    sNavConversationTextHiragana_82,
    sNavConversationTextHiragana_83,
    sNavConversationTextHiragana_84,
    sNavConversationTextHiragana_85,
    sNavConversationTextHiragana_86,
    sNavConversationTextHiragana_87,
    sNavConversationTextHiragana_88,
    sNavConversationTextHiragana_89,
    sNavConversationTextHiragana_90,
    sNavConversationTextHiragana_91,
    sNavConversationTextHiragana_92,
    sNavConversationTextHiragana_93,
    sNavConversationTextHiragana_94,
    sNavConversationTextHiragana_95,
    sNavConversationTextHiragana_96,
    sNavConversationTextHiragana_97,
    sNavConversationTextHiragana_98,
    sNavConversationTextHiragana_99,
    sNavConversationTextHiragana_100,
    sNavConversationTextHiragana_101,
    sNavConversationTextHiragana_102,
    sNavConversationTextHiragana_103,
    sNavConversationTextHiragana_104,
    sNavConversationTextHiragana_105,
    sNavConversationTextHiragana_106,
    sNavConversationTextHiragana_107,
    sNavConversationTextHiragana_108,
    sNavConversationTextHiragana_109,
    sNavConversationTextHiragana_110,
    sNavConversationTextHiragana_111,
    sNavConversationTextHiragana_112,
    sNavConversationTextHiragana_113
};
const u16* sPauseScreenTextPointersHiragana[108] = {
    sPauseScreenTextHiragana_0,
    sPauseScreenTextHiragana_1,
    sPauseScreenTextHiragana_2,
    sPauseScreenTextHiragana_3,
    sPauseScreenTextHiragana_4,
    sPauseScreenTextHiragana_5,
    sPauseScreenTextHiragana_6,
    sPauseScreenTextHiragana_7,
    sPauseScreenTextHiragana_8,
    sPauseScreenTextHiragana_9,
    sPauseScreenTextHiragana_10,
    sPauseScreenTextHiragana_11,
    sPauseScreenTextHiragana_12,
    sPauseScreenTextHiragana_13,
    sPauseScreenTextHiragana_14,
    sPauseScreenTextHiragana_15,
    sPauseScreenTextHiragana_16,
    sPauseScreenTextHiragana_17,
    sPauseScreenTextHiragana_18,
    sPauseScreenTextHiragana_19,
    sPauseScreenTextHiragana_20,
    sPauseScreenTextHiragana_21,
    sPauseScreenTextHiragana_22,
    sPauseScreenTextHiragana_23,
    sPauseScreenTextHiragana_24,
    sPauseScreenTextHiragana_25,
    sPauseScreenTextHiragana_26,
    sPauseScreenTextHiragana_27,
    sPauseScreenTextHiragana_28,
    sPauseScreenTextHiragana_29,
    sPauseScreenTextHiragana_30,
    sPauseScreenTextHiragana_31,
    sPauseScreenTextHiragana_32,
    sPauseScreenTextHiragana_33,
    sPauseScreenTextHiragana_34,
    sPauseScreenTextHiragana_35,
    sPauseScreenTextHiragana_36,
    sPauseScreenTextHiragana_37,
    sPauseScreenTextHiragana_38,
    sPauseScreenTextHiragana_39,
    sPauseScreenTextHiragana_40,
    sPauseScreenTextHiragana_41,
    sPauseScreenTextHiragana_42,
    sPauseScreenTextHiragana_43,
    sPauseScreenTextHiragana_44,
    sPauseScreenTextHiragana_45,
    sPauseScreenTextHiragana_46,
    sPauseScreenTextHiragana_47,
    sPauseScreenTextHiragana_48,
    sPauseScreenTextHiragana_49,
    sPauseScreenTextHiragana_50,
    sPauseScreenTextHiragana_51,
    sPauseScreenTextHiragana_52,
    sPauseScreenTextHiragana_53,
    sPauseScreenTextHiragana_54,
    sPauseScreenTextHiragana_55,
    sPauseScreenTextHiragana_56,
    sPauseScreenTextHiragana_57,
    sPauseScreenTextHiragana_58,
    sPauseScreenTextHiragana_59,
    sPauseScreenTextHiragana_60,
    sPauseScreenTextHiragana_61,
    sPauseScreenTextHiragana_62,
    sPauseScreenTextHiragana_63,
    sPauseScreenTextHiragana_64,
    sPauseScreenTextHiragana_65,
    sPauseScreenTextHiragana_66,
    sPauseScreenTextHiragana_67,
    sPauseScreenTextHiragana_68,
    sPauseScreenTextHiragana_69,
    sPauseScreenTextHiragana_70,
    sPauseScreenTextHiragana_71,
    sPauseScreenTextHiragana_72,
    sPauseScreenTextHiragana_73,
    sPauseScreenTextHiragana_74,
    sPauseScreenTextHiragana_75,
    sPauseScreenTextHiragana_76,
    sPauseScreenTextHiragana_77,
    sPauseScreenTextHiragana_78,
    sPauseScreenTextHiragana_79,
    sPauseScreenTextHiragana_80,
    sPauseScreenTextHiragana_81,
    sPauseScreenTextHiragana_82,
    sPauseScreenTextHiragana_83,
    sPauseScreenTextHiragana_84,
    sPauseScreenTextHiragana_85,
    sPauseScreenTextHiragana_86,
    sPauseScreenTextHiragana_87,
    sPauseScreenTextHiragana_88,
    sPauseScreenTextHiragana_89,
    sPauseScreenTextHiragana_90,
    sPauseScreenTextHiragana_91,
    sPauseScreenTextHiragana_92,
    sPauseScreenTextHiragana_93,
    sPauseScreenTextHiragana_94,
    sPauseScreenTextHiragana_95,
    sPauseScreenTextHiragana_96,
    sPauseScreenTextHiragana_97,
    sPauseScreenTextHiragana_98,
    sPauseScreenTextHiragana_99,
    sPauseScreenTextHiragana_100,
    sPauseScreenTextHiragana_101,
    sPauseScreenTextHiragana_102,
    sPauseScreenTextHiragana_103,
    sPauseScreenTextHiragana_104,
    sPauseScreenTextHiragana_105,
    sPauseScreenTextHiragana_106,
    sPauseScreenTextHiragana_107
};
const u16* sNavConversationTextPointersEnglish[114] = {
    sNavConversationTextEnglish_0,
    sNavConversationTextEnglish_1,
    sNavConversationTextEnglish_2,
    sNavConversationTextEnglish_3,
    sNavConversationTextEnglish_4,
    sNavConversationTextEnglish_5,
    sNavConversationTextEnglish_6,
    sNavConversationTextEnglish_7,
    sNavConversationTextEnglish_8,
    sNavConversationTextEnglish_9,
    sNavConversationTextEnglish_10,
    sNavConversationTextEnglish_11,
    sNavConversationTextEnglish_12,
    sNavConversationTextEnglish_13,
    sNavConversationTextEnglish_14,
    sNavConversationTextEnglish_15,
    sNavConversationTextEnglish_16,
    sNavConversationTextEnglish_17,
    sNavConversationTextEnglish_18,
    sNavConversationTextEnglish_19,
    sNavConversationTextEnglish_20,
    sNavConversationTextEnglish_21,
    sNavConversationTextEnglish_22,
    sNavConversationTextEnglish_23,
    sNavConversationTextEnglish_24,
    sNavConversationTextEnglish_25,
    sNavConversationTextEnglish_26,
    sNavConversationTextEnglish_27,
    sNavConversationTextEnglish_28,
    sNavConversationTextEnglish_29,
    sNavConversationTextEnglish_30,
    sNavConversationTextEnglish_31,
    sNavConversationTextEnglish_32,
    sNavConversationTextEnglish_33,
    sNavConversationTextEnglish_34,
    sNavConversationTextEnglish_35,
    sNavConversationTextEnglish_36,
    sNavConversationTextEnglish_37,
    sNavConversationTextEnglish_38,
    sNavConversationTextEnglish_39,
    sNavConversationTextEnglish_40,
    sNavConversationTextEnglish_41,
    sNavConversationTextEnglish_42,
    sNavConversationTextEnglish_43,
    sNavConversationTextEnglish_44,
    sNavConversationTextEnglish_45,
    sNavConversationTextEnglish_46,
    sNavConversationTextEnglish_47,
    sNavConversationTextEnglish_48,
    sNavConversationTextEnglish_49,
    sNavConversationTextEnglish_50,
    sNavConversationTextEnglish_51,
    sNavConversationTextEnglish_52,
    sNavConversationTextEnglish_53,
    sNavConversationTextEnglish_54,
    sNavConversationTextEnglish_55,
    sNavConversationTextEnglish_56,
    sNavConversationTextEnglish_57,
    sNavConversationTextEnglish_58,
    sNavConversationTextEnglish_59,
    sNavConversationTextEnglish_60,
    sNavConversationTextEnglish_61,
    sNavConversationTextEnglish_62,
    sNavConversationTextEnglish_63,
    sNavConversationTextEnglish_64,
    sNavConversationTextEnglish_65,
    sNavConversationTextEnglish_66,
    sNavConversationTextEnglish_67,
    sNavConversationTextEnglish_68,
    sNavConversationTextEnglish_69,
    sNavConversationTextEnglish_70,
    sNavConversationTextEnglish_71,
    sNavConversationTextEnglish_72,
    sNavConversationTextEnglish_73,
    sNavConversationTextEnglish_74,
    sNavConversationTextEnglish_75,
    sNavConversationTextEnglish_76,
    sNavConversationTextEnglish_77,
    sNavConversationTextEnglish_78,
    sNavConversationTextEnglish_79,
    sNavConversationTextEnglish_80,
    sNavConversationTextEnglish_81,
    sNavConversationTextEnglish_82,
    sNavConversationTextEnglish_83,
    sNavConversationTextEnglish_84,
    sNavConversationTextEnglish_85,
    sNavConversationTextEnglish_86,
    sNavConversationTextEnglish_87,
    sNavConversationTextEnglish_88,
    sNavConversationTextEnglish_89,
    sNavConversationTextEnglish_90,
    sNavConversationTextEnglish_91,
    sNavConversationTextEnglish_92,
    sNavConversationTextEnglish_93,
    sNavConversationTextEnglish_94,
    sNavConversationTextEnglish_95,
    sNavConversationTextEnglish_96,
    sNavConversationTextEnglish_97,
    sNavConversationTextEnglish_98,
    sNavConversationTextEnglish_99,
    sNavConversationTextEnglish_100,
    sNavConversationTextEnglish_101,
    sNavConversationTextEnglish_102,
    sNavConversationTextEnglish_103,
    sNavConversationTextEnglish_104,
    sNavConversationTextEnglish_105,
    sNavConversationTextEnglish_106,
    sNavConversationTextEnglish_107,
    sNavConversationTextEnglish_108,
    sNavConversationTextEnglish_109,
    sNavConversationTextEnglish_110,
    sNavConversationTextEnglish_111,
    sNavConversationTextEnglish_112,
    sNavConversationTextEnglish_113
};
const u16* sPauseScreenTextPointersEnglish[111] = {
    sPauseScreenTextEnglish_0,
    sPauseScreenTextEnglish_1,
    sPauseScreenTextEnglish_2,
    sPauseScreenTextEnglish_3,
    sPauseScreenTextEnglish_4,
    sPauseScreenTextEnglish_5,
    sPauseScreenTextEnglish_6,
    sPauseScreenTextEnglish_7,
    sPauseScreenTextEnglish_8,
    sPauseScreenTextEnglish_9,
    sPauseScreenTextEnglish_10,
    sPauseScreenTextEnglish_11,
    sPauseScreenTextEnglish_12,
    sPauseScreenTextEnglish_13,
    sPauseScreenTextEnglish_14,
    sPauseScreenTextEnglish_15,
    sPauseScreenTextEnglish_16,
    sPauseScreenTextEnglish_17,
    sPauseScreenTextEnglish_18,
    sPauseScreenTextEnglish_19,
    sPauseScreenTextEnglish_20,
    sPauseScreenTextEnglish_21,
    sPauseScreenTextEnglish_22,
    sPauseScreenTextEnglish_23,
    sPauseScreenTextEnglish_24,
    sPauseScreenTextEnglish_25,
    sPauseScreenTextEnglish_26,
    sPauseScreenTextEnglish_27,
    sPauseScreenTextEnglish_28,
    sPauseScreenTextEnglish_29,
    sPauseScreenTextEnglish_30,
    sPauseScreenTextEnglish_31,
    sPauseScreenTextEnglish_32,
    sPauseScreenTextEnglish_33,
    sPauseScreenTextEnglish_34,
    sPauseScreenTextEnglish_35,
    sPauseScreenTextEnglish_36,
    sPauseScreenTextEnglish_37,
    sPauseScreenTextEnglish_38,
    sPauseScreenTextEnglish_39,
    sPauseScreenTextEnglish_40,
    sPauseScreenTextEnglish_41,
    sPauseScreenTextEnglish_42,
    sPauseScreenTextEnglish_43,
    sPauseScreenTextEnglish_44,
    sPauseScreenTextEnglish_45,
    sPauseScreenTextEnglish_46,
    sPauseScreenTextEnglish_47,
    sPauseScreenTextEnglish_48,
    sPauseScreenTextEnglish_49,
    sPauseScreenTextEnglish_50,
    sPauseScreenTextEnglish_51,
    sPauseScreenTextEnglish_52,
    sPauseScreenTextEnglish_53,
    sPauseScreenTextEnglish_54,
    sPauseScreenTextEnglish_55,
    sPauseScreenTextEnglish_56,
    sPauseScreenTextEnglish_57,
    sPauseScreenTextEnglish_58,
    sPauseScreenTextEnglish_59,
    sPauseScreenTextEnglish_60,
    sPauseScreenTextEnglish_61,
    sPauseScreenTextEnglish_62,
    sPauseScreenTextEnglish_63,
    sPauseScreenTextEnglish_64,
    sPauseScreenTextEnglish_65,
    sPauseScreenTextEnglish_66,
    sPauseScreenTextEnglish_67,
    sPauseScreenTextEnglish_68,
    sPauseScreenTextEnglish_69,
    sPauseScreenTextEnglish_70,
    sPauseScreenTextEnglish_71,
    sPauseScreenTextEnglish_72,
    sPauseScreenTextEnglish_73,
    sPauseScreenTextEnglish_74,
    sPauseScreenTextEnglish_75,
    sPauseScreenTextEnglish_76,
    sPauseScreenTextEnglish_77,
    sPauseScreenTextEnglish_78,
    sPauseScreenTextEnglish_79,
    sPauseScreenTextEnglish_80,
    sPauseScreenTextEnglish_81,
    sPauseScreenTextEnglish_82,
    sPauseScreenTextEnglish_83,
    sPauseScreenTextEnglish_84,
    sPauseScreenTextEnglish_85,
    sPauseScreenTextEnglish_86,
    sPauseScreenTextEnglish_87,
    sPauseScreenTextEnglish_88,
    sPauseScreenTextEnglish_89,
    sPauseScreenTextEnglish_90,
    sPauseScreenTextEnglish_91,
    sPauseScreenTextEnglish_92,
    sPauseScreenTextEnglish_93,
    sPauseScreenTextEnglish_94,
    sPauseScreenTextEnglish_95,
    sPauseScreenTextEnglish_96,
    sPauseScreenTextEnglish_97,
    sPauseScreenTextEnglish_98,
    sPauseScreenTextEnglish_99,
    sPauseScreenTextEnglish_100,
    sPauseScreenTextEnglish_101,
    sPauseScreenTextEnglish_102,
    sPauseScreenTextEnglish_103,
    sPauseScreenTextEnglish_104,
    sPauseScreenTextEnglish_105,
    sPauseScreenTextEnglish_106,
    sPauseScreenTextEnglish_107,
    sPauseScreenTextEnglish_108,
    sPauseScreenTextEnglish_109,
    sPauseScreenTextEnglish_110
};
const u16* sNavConversationTextPointersGerman[114] = {
    sNavConversationTextGerman_0,
    sNavConversationTextGerman_1,
    sNavConversationTextGerman_2,
    sNavConversationTextGerman_3,
    sNavConversationTextGerman_4,
    sNavConversationTextGerman_5,
    sNavConversationTextGerman_6,
    sNavConversationTextGerman_7,
    sNavConversationTextGerman_8,
    sNavConversationTextGerman_9,
    sNavConversationTextGerman_10,
    sNavConversationTextGerman_11,
    sNavConversationTextGerman_12,
    sNavConversationTextGerman_13,
    sNavConversationTextGerman_14,
    sNavConversationTextGerman_15,
    sNavConversationTextGerman_16,
    sNavConversationTextGerman_17,
    sNavConversationTextGerman_18,
    sNavConversationTextGerman_19,
    sNavConversationTextGerman_20,
    sNavConversationTextGerman_21,
    sNavConversationTextGerman_22,
    sNavConversationTextGerman_23,
    sNavConversationTextGerman_24,
    sNavConversationTextGerman_25,
    sNavConversationTextGerman_26,
    sNavConversationTextGerman_27,
    sNavConversationTextGerman_28,
    sNavConversationTextGerman_29,
    sNavConversationTextGerman_30,
    sNavConversationTextGerman_31,
    sNavConversationTextGerman_32,
    sNavConversationTextGerman_33,
    sNavConversationTextGerman_34,
    sNavConversationTextGerman_35,
    sNavConversationTextGerman_36,
    sNavConversationTextGerman_37,
    sNavConversationTextGerman_38,
    sNavConversationTextGerman_39,
    sNavConversationTextGerman_40,
    sNavConversationTextGerman_41,
    sNavConversationTextGerman_42,
    sNavConversationTextGerman_43,
    sNavConversationTextGerman_44,
    sNavConversationTextGerman_45,
    sNavConversationTextGerman_46,
    sNavConversationTextGerman_47,
    sNavConversationTextGerman_48,
    sNavConversationTextGerman_49,
    sNavConversationTextGerman_50,
    sNavConversationTextGerman_51,
    sNavConversationTextGerman_52,
    sNavConversationTextGerman_53,
    sNavConversationTextGerman_54,
    sNavConversationTextGerman_55,
    sNavConversationTextGerman_56,
    sNavConversationTextGerman_57,
    sNavConversationTextGerman_58,
    sNavConversationTextGerman_59,
    sNavConversationTextGerman_60,
    sNavConversationTextGerman_61,
    sNavConversationTextGerman_62,
    sNavConversationTextGerman_63,
    sNavConversationTextGerman_64,
    sNavConversationTextGerman_65,
    sNavConversationTextGerman_66,
    sNavConversationTextGerman_67,
    sNavConversationTextGerman_68,
    sNavConversationTextGerman_69,
    sNavConversationTextGerman_70,
    sNavConversationTextGerman_71,
    sNavConversationTextGerman_72,
    sNavConversationTextGerman_73,
    sNavConversationTextGerman_74,
    sNavConversationTextGerman_75,
    sNavConversationTextGerman_76,
    sNavConversationTextGerman_77,
    sNavConversationTextGerman_78,
    sNavConversationTextGerman_79,
    sNavConversationTextGerman_80,
    sNavConversationTextGerman_81,
    sNavConversationTextGerman_82,
    sNavConversationTextGerman_83,
    sNavConversationTextGerman_84,
    sNavConversationTextGerman_85,
    sNavConversationTextGerman_86,
    sNavConversationTextGerman_87,
    sNavConversationTextGerman_88,
    sNavConversationTextGerman_89,
    sNavConversationTextGerman_90,
    sNavConversationTextGerman_91,
    sNavConversationTextGerman_92,
    sNavConversationTextGerman_93,
    sNavConversationTextGerman_94,
    sNavConversationTextGerman_95,
    sNavConversationTextGerman_96,
    sNavConversationTextGerman_97,
    sNavConversationTextGerman_98,
    sNavConversationTextGerman_99,
    sNavConversationTextGerman_100,
    sNavConversationTextGerman_101,
    sNavConversationTextGerman_102,
    sNavConversationTextGerman_103,
    sNavConversationTextGerman_104,
    sNavConversationTextGerman_105,
    sNavConversationTextGerman_106,
    sNavConversationTextGerman_107,
    sNavConversationTextGerman_108,
    sNavConversationTextGerman_109,
    sNavConversationTextGerman_110,
    sNavConversationTextGerman_111,
    sNavConversationTextGerman_112,
    sNavConversationTextGerman_113
};
const u16* sPauseScreenTextPointersGerman[111] = {
    sPauseScreenTextGerman_0,
    sPauseScreenTextGerman_1,
    sPauseScreenTextGerman_2,
    sPauseScreenTextGerman_3,
    sPauseScreenTextGerman_4,
    sPauseScreenTextGerman_5,
    sPauseScreenTextGerman_6,
    sPauseScreenTextGerman_7,
    sPauseScreenTextGerman_8,
    sPauseScreenTextGerman_9,
    sPauseScreenTextGerman_10,
    sPauseScreenTextGerman_11,
    sPauseScreenTextGerman_12,
    sPauseScreenTextGerman_13,
    sPauseScreenTextGerman_14,
    sPauseScreenTextGerman_15,
    sPauseScreenTextGerman_16,
    sPauseScreenTextGerman_17,
    sPauseScreenTextGerman_18,
    sPauseScreenTextGerman_19,
    sPauseScreenTextGerman_20,
    sPauseScreenTextGerman_21,
    sPauseScreenTextGerman_22,
    sPauseScreenTextGerman_23,
    sPauseScreenTextGerman_24,
    sPauseScreenTextGerman_25,
    sPauseScreenTextGerman_26,
    sPauseScreenTextGerman_27,
    sPauseScreenTextGerman_28,
    sPauseScreenTextGerman_29,
    sPauseScreenTextGerman_30,
    sPauseScreenTextGerman_31,
    sPauseScreenTextGerman_32,
    sPauseScreenTextGerman_33,
    sPauseScreenTextGerman_34,
    sPauseScreenTextGerman_35,
    sPauseScreenTextGerman_36,
    sPauseScreenTextGerman_37,
    sPauseScreenTextGerman_38,
    sPauseScreenTextGerman_39,
    sPauseScreenTextGerman_40,
    sPauseScreenTextGerman_41,
    sPauseScreenTextGerman_42,
    sPauseScreenTextGerman_43,
    sPauseScreenTextGerman_44,
    sPauseScreenTextGerman_45,
    sPauseScreenTextGerman_46,
    sPauseScreenTextGerman_47,
    sPauseScreenTextGerman_48,
    sPauseScreenTextGerman_49,
    sPauseScreenTextGerman_50,
    sPauseScreenTextGerman_51,
    sPauseScreenTextGerman_52,
    sPauseScreenTextGerman_53,
    sPauseScreenTextGerman_54,
    sPauseScreenTextGerman_55,
    sPauseScreenTextGerman_56,
    sPauseScreenTextGerman_57,
    sPauseScreenTextGerman_58,
    sPauseScreenTextGerman_59,
    sPauseScreenTextGerman_60,
    sPauseScreenTextGerman_61,
    sPauseScreenTextGerman_62,
    sPauseScreenTextGerman_63,
    sPauseScreenTextGerman_64,
    sPauseScreenTextGerman_65,
    sPauseScreenTextGerman_66,
    sPauseScreenTextGerman_67,
    sPauseScreenTextGerman_68,
    sPauseScreenTextGerman_69,
    sPauseScreenTextGerman_70,
    sPauseScreenTextGerman_71,
    sPauseScreenTextGerman_72,
    sPauseScreenTextGerman_73,
    sPauseScreenTextGerman_74,
    sPauseScreenTextGerman_75,
    sPauseScreenTextGerman_76,
    sPauseScreenTextGerman_77,
    sPauseScreenTextGerman_78,
    sPauseScreenTextGerman_79,
    sPauseScreenTextGerman_80,
    sPauseScreenTextGerman_81,
    sPauseScreenTextGerman_82,
    sPauseScreenTextGerman_83,
    sPauseScreenTextGerman_84,
    sPauseScreenTextGerman_85,
    sPauseScreenTextGerman_86,
    sPauseScreenTextGerman_87,
    sPauseScreenTextGerman_88,
    sPauseScreenTextGerman_89,
    sPauseScreenTextGerman_90,
    sPauseScreenTextGerman_91,
    sPauseScreenTextGerman_92,
    sPauseScreenTextGerman_93,
    sPauseScreenTextGerman_94,
    sPauseScreenTextGerman_95,
    sPauseScreenTextGerman_96,
    sPauseScreenTextGerman_97,
    sPauseScreenTextGerman_98,
    sPauseScreenTextGerman_99,
    sPauseScreenTextGerman_100,
    sPauseScreenTextGerman_101,
    sPauseScreenTextGerman_102,
    sPauseScreenTextGerman_103,
    sPauseScreenTextGerman_104,
    sPauseScreenTextGerman_105,
    sPauseScreenTextGerman_106,
    sPauseScreenTextGerman_107,
    sPauseScreenTextGerman_108,
    sPauseScreenTextGerman_109,
    sPauseScreenTextGerman_110
};
const u16* sNavConversationTextPointersFrench[114] = {
    sNavConversationTextFrench_0,
    sNavConversationTextFrench_1,
    sNavConversationTextFrench_2,
    sNavConversationTextFrench_3,
    sNavConversationTextFrench_4,
    sNavConversationTextFrench_5,
    sNavConversationTextFrench_6,
    sNavConversationTextFrench_7,
    sNavConversationTextFrench_8,
    sNavConversationTextFrench_9,
    sNavConversationTextFrench_10,
    sNavConversationTextFrench_11,
    sNavConversationTextFrench_12,
    sNavConversationTextFrench_13,
    sNavConversationTextFrench_14,
    sNavConversationTextFrench_15,
    sNavConversationTextFrench_16,
    sNavConversationTextFrench_17,
    sNavConversationTextFrench_18,
    sNavConversationTextFrench_19,
    sNavConversationTextFrench_20,
    sNavConversationTextFrench_21,
    sNavConversationTextFrench_22,
    sNavConversationTextFrench_23,
    sNavConversationTextFrench_24,
    sNavConversationTextFrench_25,
    sNavConversationTextFrench_26,
    sNavConversationTextFrench_27,
    sNavConversationTextFrench_28,
    sNavConversationTextFrench_29,
    sNavConversationTextFrench_30,
    sNavConversationTextFrench_31,
    sNavConversationTextFrench_32,
    sNavConversationTextFrench_33,
    sNavConversationTextFrench_34,
    sNavConversationTextFrench_35,
    sNavConversationTextFrench_36,
    sNavConversationTextFrench_37,
    sNavConversationTextFrench_38,
    sNavConversationTextFrench_39,
    sNavConversationTextFrench_40,
    sNavConversationTextFrench_41,
    sNavConversationTextFrench_42,
    sNavConversationTextFrench_43,
    sNavConversationTextFrench_44,
    sNavConversationTextFrench_45,
    sNavConversationTextFrench_46,
    sNavConversationTextFrench_47,
    sNavConversationTextFrench_48,
    sNavConversationTextFrench_49,
    sNavConversationTextFrench_50,
    sNavConversationTextFrench_51,
    sNavConversationTextFrench_52,
    sNavConversationTextFrench_53,
    sNavConversationTextFrench_54,
    sNavConversationTextFrench_55,
    sNavConversationTextFrench_56,
    sNavConversationTextFrench_57,
    sNavConversationTextFrench_58,
    sNavConversationTextFrench_59,
    sNavConversationTextFrench_60,
    sNavConversationTextFrench_61,
    sNavConversationTextFrench_62,
    sNavConversationTextFrench_63,
    sNavConversationTextFrench_64,
    sNavConversationTextFrench_65,
    sNavConversationTextFrench_66,
    sNavConversationTextFrench_67,
    sNavConversationTextFrench_68,
    sNavConversationTextFrench_69,
    sNavConversationTextFrench_70,
    sNavConversationTextFrench_71,
    sNavConversationTextFrench_72,
    sNavConversationTextFrench_73,
    sNavConversationTextFrench_74,
    sNavConversationTextFrench_75,
    sNavConversationTextFrench_76,
    sNavConversationTextFrench_77,
    sNavConversationTextFrench_78,
    sNavConversationTextFrench_79,
    sNavConversationTextFrench_80,
    sNavConversationTextFrench_81,
    sNavConversationTextFrench_82,
    sNavConversationTextFrench_83,
    sNavConversationTextFrench_84,
    sNavConversationTextFrench_85,
    sNavConversationTextFrench_86,
    sNavConversationTextFrench_87,
    sNavConversationTextFrench_88,
    sNavConversationTextFrench_89,
    sNavConversationTextFrench_90,
    sNavConversationTextFrench_91,
    sNavConversationTextFrench_92,
    sNavConversationTextFrench_93,
    sNavConversationTextFrench_94,
    sNavConversationTextFrench_95,
    sNavConversationTextFrench_96,
    sNavConversationTextFrench_97,
    sNavConversationTextFrench_98,
    sNavConversationTextFrench_99,
    sNavConversationTextFrench_100,
    sNavConversationTextFrench_101,
    sNavConversationTextFrench_102,
    sNavConversationTextFrench_103,
    sNavConversationTextFrench_104,
    sNavConversationTextFrench_105,
    sNavConversationTextFrench_106,
    sNavConversationTextFrench_107,
    sNavConversationTextFrench_108,
    sNavConversationTextFrench_109,
    sNavConversationTextFrench_110,
    sNavConversationTextFrench_111,
    sNavConversationTextFrench_112,
    sNavConversationTextFrench_113
};
const u16* sPauseScreenTextPointersFrench[111] = {
    sPauseScreenTextFrench_0,
    sPauseScreenTextFrench_1,
    sPauseScreenTextFrench_2,
    sPauseScreenTextFrench_3,
    sPauseScreenTextFrench_4,
    sPauseScreenTextFrench_5,
    sPauseScreenTextFrench_6,
    sPauseScreenTextFrench_7,
    sPauseScreenTextFrench_8,
    sPauseScreenTextFrench_9,
    sPauseScreenTextFrench_10,
    sPauseScreenTextFrench_11,
    sPauseScreenTextFrench_12,
    sPauseScreenTextFrench_13,
    sPauseScreenTextFrench_14,
    sPauseScreenTextFrench_15,
    sPauseScreenTextFrench_16,
    sPauseScreenTextFrench_17,
    sPauseScreenTextFrench_18,
    sPauseScreenTextFrench_19,
    sPauseScreenTextFrench_20,
    sPauseScreenTextFrench_21,
    sPauseScreenTextFrench_22,
    sPauseScreenTextFrench_23,
    sPauseScreenTextFrench_24,
    sPauseScreenTextFrench_25,
    sPauseScreenTextFrench_26,
    sPauseScreenTextFrench_27,
    sPauseScreenTextFrench_28,
    sPauseScreenTextFrench_29,
    sPauseScreenTextFrench_30,
    sPauseScreenTextFrench_31,
    sPauseScreenTextFrench_32,
    sPauseScreenTextFrench_33,
    sPauseScreenTextFrench_34,
    sPauseScreenTextFrench_35,
    sPauseScreenTextFrench_36,
    sPauseScreenTextFrench_37,
    sPauseScreenTextFrench_38,
    sPauseScreenTextFrench_39,
    sPauseScreenTextFrench_40,
    sPauseScreenTextFrench_41,
    sPauseScreenTextFrench_42,
    sPauseScreenTextFrench_43,
    sPauseScreenTextFrench_44,
    sPauseScreenTextFrench_45,
    sPauseScreenTextFrench_46,
    sPauseScreenTextFrench_47,
    sPauseScreenTextFrench_48,
    sPauseScreenTextFrench_49,
    sPauseScreenTextFrench_50,
    sPauseScreenTextFrench_51,
    sPauseScreenTextFrench_52,
    sPauseScreenTextFrench_53,
    sPauseScreenTextFrench_54,
    sPauseScreenTextFrench_55,
    sPauseScreenTextFrench_56,
    sPauseScreenTextFrench_57,
    sPauseScreenTextFrench_58,
    sPauseScreenTextFrench_59,
    sPauseScreenTextFrench_60,
    sPauseScreenTextFrench_61,
    sPauseScreenTextFrench_62,
    sPauseScreenTextFrench_63,
    sPauseScreenTextFrench_64,
    sPauseScreenTextFrench_65,
    sPauseScreenTextFrench_66,
    sPauseScreenTextFrench_67,
    sPauseScreenTextFrench_68,
    sPauseScreenTextFrench_69,
    sPauseScreenTextFrench_70,
    sPauseScreenTextFrench_71,
    sPauseScreenTextFrench_72,
    sPauseScreenTextFrench_73,
    sPauseScreenTextFrench_74,
    sPauseScreenTextFrench_75,
    sPauseScreenTextFrench_76,
    sPauseScreenTextFrench_77,
    sPauseScreenTextFrench_78,
    sPauseScreenTextFrench_79,
    sPauseScreenTextFrench_80,
    sPauseScreenTextFrench_81,
    sPauseScreenTextFrench_82,
    sPauseScreenTextFrench_83,
    sPauseScreenTextFrench_84,
    sPauseScreenTextFrench_85,
    sPauseScreenTextFrench_86,
    sPauseScreenTextFrench_87,
    sPauseScreenTextFrench_88,
    sPauseScreenTextFrench_89,
    sPauseScreenTextFrench_90,
    sPauseScreenTextFrench_91,
    sPauseScreenTextFrench_92,
    sPauseScreenTextFrench_93,
    sPauseScreenTextFrench_94,
    sPauseScreenTextFrench_95,
    sPauseScreenTextFrench_96,
    sPauseScreenTextFrench_97,
    sPauseScreenTextFrench_98,
    sPauseScreenTextFrench_99,
    sPauseScreenTextFrench_100,
    sPauseScreenTextFrench_101,
    sPauseScreenTextFrench_102,
    sPauseScreenTextFrench_103,
    sPauseScreenTextFrench_104,
    sPauseScreenTextFrench_105,
    sPauseScreenTextFrench_106,
    sPauseScreenTextFrench_107,
    sPauseScreenTextFrench_108,
    sPauseScreenTextFrench_109,
    sPauseScreenTextFrench_110
};
const u16* sNavConversationTextPointersItalian[114] = {
    sNavConversationTextItalian_0,
    sNavConversationTextItalian_1,
    sNavConversationTextItalian_2,
    sNavConversationTextItalian_3,
    sNavConversationTextItalian_4,
    sNavConversationTextItalian_5,
    sNavConversationTextItalian_6,
    sNavConversationTextItalian_7,
    sNavConversationTextItalian_8,
    sNavConversationTextItalian_9,
    sNavConversationTextItalian_10,
    sNavConversationTextItalian_11,
    sNavConversationTextItalian_12,
    sNavConversationTextItalian_13,
    sNavConversationTextItalian_14,
    sNavConversationTextItalian_15,
    sNavConversationTextItalian_16,
    sNavConversationTextItalian_17,
    sNavConversationTextItalian_18,
    sNavConversationTextItalian_19,
    sNavConversationTextItalian_20,
    sNavConversationTextItalian_21,
    sNavConversationTextItalian_22,
    sNavConversationTextItalian_23,
    sNavConversationTextItalian_24,
    sNavConversationTextItalian_25,
    sNavConversationTextItalian_26,
    sNavConversationTextItalian_27,
    sNavConversationTextItalian_28,
    sNavConversationTextItalian_29,
    sNavConversationTextItalian_30,
    sNavConversationTextItalian_31,
    sNavConversationTextItalian_32,
    sNavConversationTextItalian_33,
    sNavConversationTextItalian_34,
    sNavConversationTextItalian_35,
    sNavConversationTextItalian_36,
    sNavConversationTextItalian_37,
    sNavConversationTextItalian_38,
    sNavConversationTextItalian_39,
    sNavConversationTextItalian_40,
    sNavConversationTextItalian_41,
    sNavConversationTextItalian_42,
    sNavConversationTextItalian_43,
    sNavConversationTextItalian_44,
    sNavConversationTextItalian_45,
    sNavConversationTextItalian_46,
    sNavConversationTextItalian_47,
    sNavConversationTextItalian_48,
    sNavConversationTextItalian_49,
    sNavConversationTextItalian_50,
    sNavConversationTextItalian_51,
    sNavConversationTextItalian_52,
    sNavConversationTextItalian_53,
    sNavConversationTextItalian_54,
    sNavConversationTextItalian_55,
    sNavConversationTextItalian_56,
    sNavConversationTextItalian_57,
    sNavConversationTextItalian_58,
    sNavConversationTextItalian_59,
    sNavConversationTextItalian_60,
    sNavConversationTextItalian_61,
    sNavConversationTextItalian_62,
    sNavConversationTextItalian_63,
    sNavConversationTextItalian_64,
    sNavConversationTextItalian_65,
    sNavConversationTextItalian_66,
    sNavConversationTextItalian_67,
    sNavConversationTextItalian_68,
    sNavConversationTextItalian_69,
    sNavConversationTextItalian_70,
    sNavConversationTextItalian_71,
    sNavConversationTextItalian_72,
    sNavConversationTextItalian_73,
    sNavConversationTextItalian_74,
    sNavConversationTextItalian_75,
    sNavConversationTextItalian_76,
    sNavConversationTextItalian_77,
    sNavConversationTextItalian_78,
    sNavConversationTextItalian_79,
    sNavConversationTextItalian_80,
    sNavConversationTextItalian_81,
    sNavConversationTextItalian_82,
    sNavConversationTextItalian_83,
    sNavConversationTextItalian_84,
    sNavConversationTextItalian_85,
    sNavConversationTextItalian_86,
    sNavConversationTextItalian_87,
    sNavConversationTextItalian_88,
    sNavConversationTextItalian_89,
    sNavConversationTextItalian_90,
    sNavConversationTextItalian_91,
    sNavConversationTextItalian_92,
    sNavConversationTextItalian_93,
    sNavConversationTextItalian_94,
    sNavConversationTextItalian_95,
    sNavConversationTextItalian_96,
    sNavConversationTextItalian_97,
    sNavConversationTextItalian_98,
    sNavConversationTextItalian_99,
    sNavConversationTextItalian_100,
    sNavConversationTextItalian_101,
    sNavConversationTextItalian_102,
    sNavConversationTextItalian_103,
    sNavConversationTextItalian_104,
    sNavConversationTextItalian_105,
    sNavConversationTextItalian_106,
    sNavConversationTextItalian_107,
    sNavConversationTextItalian_108,
    sNavConversationTextItalian_109,
    sNavConversationTextItalian_110,
    sNavConversationTextItalian_111,
    sNavConversationTextItalian_112,
    sNavConversationTextItalian_113
};
const u16* sPauseScreenTextPointersItalian[111] = {
    sPauseScreenTextItalian_0,
    sPauseScreenTextItalian_1,
    sPauseScreenTextItalian_2,
    sPauseScreenTextItalian_3,
    sPauseScreenTextItalian_4,
    sPauseScreenTextItalian_5,
    sPauseScreenTextItalian_6,
    sPauseScreenTextItalian_7,
    sPauseScreenTextItalian_8,
    sPauseScreenTextItalian_9,
    sPauseScreenTextItalian_10,
    sPauseScreenTextItalian_11,
    sPauseScreenTextItalian_12,
    sPauseScreenTextItalian_13,
    sPauseScreenTextItalian_14,
    sPauseScreenTextItalian_15,
    sPauseScreenTextItalian_16,
    sPauseScreenTextItalian_17,
    sPauseScreenTextItalian_18,
    sPauseScreenTextItalian_19,
    sPauseScreenTextItalian_20,
    sPauseScreenTextItalian_21,
    sPauseScreenTextItalian_22,
    sPauseScreenTextItalian_23,
    sPauseScreenTextItalian_24,
    sPauseScreenTextItalian_25,
    sPauseScreenTextItalian_26,
    sPauseScreenTextItalian_27,
    sPauseScreenTextItalian_28,
    sPauseScreenTextItalian_29,
    sPauseScreenTextItalian_30,
    sPauseScreenTextItalian_31,
    sPauseScreenTextItalian_32,
    sPauseScreenTextItalian_33,
    sPauseScreenTextItalian_34,
    sPauseScreenTextItalian_35,
    sPauseScreenTextItalian_36,
    sPauseScreenTextItalian_37,
    sPauseScreenTextItalian_38,
    sPauseScreenTextItalian_39,
    sPauseScreenTextItalian_40,
    sPauseScreenTextItalian_41,
    sPauseScreenTextItalian_42,
    sPauseScreenTextItalian_43,
    sPauseScreenTextItalian_44,
    sPauseScreenTextItalian_45,
    sPauseScreenTextItalian_46,
    sPauseScreenTextItalian_47,
    sPauseScreenTextItalian_48,
    sPauseScreenTextItalian_49,
    sPauseScreenTextItalian_50,
    sPauseScreenTextItalian_51,
    sPauseScreenTextItalian_52,
    sPauseScreenTextItalian_53,
    sPauseScreenTextItalian_54,
    sPauseScreenTextItalian_55,
    sPauseScreenTextItalian_56,
    sPauseScreenTextItalian_57,
    sPauseScreenTextItalian_58,
    sPauseScreenTextItalian_59,
    sPauseScreenTextItalian_60,
    sPauseScreenTextItalian_61,
    sPauseScreenTextItalian_62,
    sPauseScreenTextItalian_63,
    sPauseScreenTextItalian_64,
    sPauseScreenTextItalian_65,
    sPauseScreenTextItalian_66,
    sPauseScreenTextItalian_67,
    sPauseScreenTextItalian_68,
    sPauseScreenTextItalian_69,
    sPauseScreenTextItalian_70,
    sPauseScreenTextItalian_71,
    sPauseScreenTextItalian_72,
    sPauseScreenTextItalian_73,
    sPauseScreenTextItalian_74,
    sPauseScreenTextItalian_75,
    sPauseScreenTextItalian_76,
    sPauseScreenTextItalian_77,
    sPauseScreenTextItalian_78,
    sPauseScreenTextItalian_79,
    sPauseScreenTextItalian_80,
    sPauseScreenTextItalian_81,
    sPauseScreenTextItalian_82,
    sPauseScreenTextItalian_83,
    sPauseScreenTextItalian_84,
    sPauseScreenTextItalian_85,
    sPauseScreenTextItalian_86,
    sPauseScreenTextItalian_87,
    sPauseScreenTextItalian_88,
    sPauseScreenTextItalian_89,
    sPauseScreenTextItalian_90,
    sPauseScreenTextItalian_91,
    sPauseScreenTextItalian_92,
    sPauseScreenTextItalian_93,
    sPauseScreenTextItalian_94,
    sPauseScreenTextItalian_95,
    sPauseScreenTextItalian_96,
    sPauseScreenTextItalian_97,
    sPauseScreenTextItalian_98,
    sPauseScreenTextItalian_99,
    sPauseScreenTextItalian_100,
    sPauseScreenTextItalian_101,
    sPauseScreenTextItalian_102,
    sPauseScreenTextItalian_103,
    sPauseScreenTextItalian_104,
    sPauseScreenTextItalian_105,
    sPauseScreenTextItalian_106,
    sPauseScreenTextItalian_107,
    sPauseScreenTextItalian_108,
    sPauseScreenTextItalian_109,
    sPauseScreenTextItalian_110
};
const u16* sNavConversationTextPointersSpanish[114] = {
    sNavConversationTextSpanish_0,
    sNavConversationTextSpanish_1,
    sNavConversationTextSpanish_2,
    sNavConversationTextSpanish_3,
    sNavConversationTextSpanish_4,
    sNavConversationTextSpanish_5,
    sNavConversationTextSpanish_6,
    sNavConversationTextSpanish_7,
    sNavConversationTextSpanish_8,
    sNavConversationTextSpanish_9,
    sNavConversationTextSpanish_10,
    sNavConversationTextSpanish_11,
    sNavConversationTextSpanish_12,
    sNavConversationTextSpanish_13,
    sNavConversationTextSpanish_14,
    sNavConversationTextSpanish_15,
    sNavConversationTextSpanish_16,
    sNavConversationTextSpanish_17,
    sNavConversationTextSpanish_18,
    sNavConversationTextSpanish_19,
    sNavConversationTextSpanish_20,
    sNavConversationTextSpanish_21,
    sNavConversationTextSpanish_22,
    sNavConversationTextSpanish_23,
    sNavConversationTextSpanish_24,
    sNavConversationTextSpanish_25,
    sNavConversationTextSpanish_26,
    sNavConversationTextSpanish_27,
    sNavConversationTextSpanish_28,
    sNavConversationTextSpanish_29,
    sNavConversationTextSpanish_30,
    sNavConversationTextSpanish_31,
    sNavConversationTextSpanish_32,
    sNavConversationTextSpanish_33,
    sNavConversationTextSpanish_34,
    sNavConversationTextSpanish_35,
    sNavConversationTextSpanish_36,
    sNavConversationTextSpanish_37,
    sNavConversationTextSpanish_38,
    sNavConversationTextSpanish_39,
    sNavConversationTextSpanish_40,
    sNavConversationTextSpanish_41,
    sNavConversationTextSpanish_42,
    sNavConversationTextSpanish_43,
    sNavConversationTextSpanish_44,
    sNavConversationTextSpanish_45,
    sNavConversationTextSpanish_46,
    sNavConversationTextSpanish_47,
    sNavConversationTextSpanish_48,
    sNavConversationTextSpanish_49,
    sNavConversationTextSpanish_50,
    sNavConversationTextSpanish_51,
    sNavConversationTextSpanish_52,
    sNavConversationTextSpanish_53,
    sNavConversationTextSpanish_54,
    sNavConversationTextSpanish_55,
    sNavConversationTextSpanish_56,
    sNavConversationTextSpanish_57,
    sNavConversationTextSpanish_58,
    sNavConversationTextSpanish_59,
    sNavConversationTextSpanish_60,
    sNavConversationTextSpanish_61,
    sNavConversationTextSpanish_62,
    sNavConversationTextSpanish_63,
    sNavConversationTextSpanish_64,
    sNavConversationTextSpanish_65,
    sNavConversationTextSpanish_66,
    sNavConversationTextSpanish_67,
    sNavConversationTextSpanish_68,
    sNavConversationTextSpanish_69,
    sNavConversationTextSpanish_70,
    sNavConversationTextSpanish_71,
    sNavConversationTextSpanish_72,
    sNavConversationTextSpanish_73,
    sNavConversationTextSpanish_74,
    sNavConversationTextSpanish_75,
    sNavConversationTextSpanish_76,
    sNavConversationTextSpanish_77,
    sNavConversationTextSpanish_78,
    sNavConversationTextSpanish_79,
    sNavConversationTextSpanish_80,
    sNavConversationTextSpanish_81,
    sNavConversationTextSpanish_82,
    sNavConversationTextSpanish_83,
    sNavConversationTextSpanish_84,
    sNavConversationTextSpanish_85,
    sNavConversationTextSpanish_86,
    sNavConversationTextSpanish_87,
    sNavConversationTextSpanish_88,
    sNavConversationTextSpanish_89,
    sNavConversationTextSpanish_90,
    sNavConversationTextSpanish_91,
    sNavConversationTextSpanish_92,
    sNavConversationTextSpanish_93,
    sNavConversationTextSpanish_94,
    sNavConversationTextSpanish_95,
    sNavConversationTextSpanish_96,
    sNavConversationTextSpanish_97,
    sNavConversationTextSpanish_98,
    sNavConversationTextSpanish_99,
    sNavConversationTextSpanish_100,
    sNavConversationTextSpanish_101,
    sNavConversationTextSpanish_102,
    sNavConversationTextSpanish_103,
    sNavConversationTextSpanish_104,
    sNavConversationTextSpanish_105,
    sNavConversationTextSpanish_106,
    sNavConversationTextSpanish_107,
    sNavConversationTextSpanish_108,
    sNavConversationTextSpanish_109,
    sNavConversationTextSpanish_110,
    sNavConversationTextSpanish_111,
    sNavConversationTextSpanish_112,
    sNavConversationTextSpanish_113
};
const u16* sPauseScreenTextPointersSpanish[111] = {
    sPauseScreenTextSpanish_0,
    sPauseScreenTextSpanish_1,
    sPauseScreenTextSpanish_2,
    sPauseScreenTextSpanish_3,
    sPauseScreenTextSpanish_4,
    sPauseScreenTextSpanish_5,
    sPauseScreenTextSpanish_6,
    sPauseScreenTextSpanish_7,
    sPauseScreenTextSpanish_8,
    sPauseScreenTextSpanish_9,
    sPauseScreenTextSpanish_10,
    sPauseScreenTextSpanish_11,
    sPauseScreenTextSpanish_12,
    sPauseScreenTextSpanish_13,
    sPauseScreenTextSpanish_14,
    sPauseScreenTextSpanish_15,
    sPauseScreenTextSpanish_16,
    sPauseScreenTextSpanish_17,
    sPauseScreenTextSpanish_18,
    sPauseScreenTextSpanish_19,
    sPauseScreenTextSpanish_20,
    sPauseScreenTextSpanish_21,
    sPauseScreenTextSpanish_22,
    sPauseScreenTextSpanish_23,
    sPauseScreenTextSpanish_24,
    sPauseScreenTextSpanish_25,
    sPauseScreenTextSpanish_26,
    sPauseScreenTextSpanish_27,
    sPauseScreenTextSpanish_28,
    sPauseScreenTextSpanish_29,
    sPauseScreenTextSpanish_30,
    sPauseScreenTextSpanish_31,
    sPauseScreenTextSpanish_32,
    sPauseScreenTextSpanish_33,
    sPauseScreenTextSpanish_34,
    sPauseScreenTextSpanish_35,
    sPauseScreenTextSpanish_36,
    sPauseScreenTextSpanish_37,
    sPauseScreenTextSpanish_38,
    sPauseScreenTextSpanish_39,
    sPauseScreenTextSpanish_40,
    sPauseScreenTextSpanish_41,
    sPauseScreenTextSpanish_42,
    sPauseScreenTextSpanish_43,
    sPauseScreenTextSpanish_44,
    sPauseScreenTextSpanish_45,
    sPauseScreenTextSpanish_46,
    sPauseScreenTextSpanish_47,
    sPauseScreenTextSpanish_48,
    sPauseScreenTextSpanish_49,
    sPauseScreenTextSpanish_50,
    sPauseScreenTextSpanish_51,
    sPauseScreenTextSpanish_52,
    sPauseScreenTextSpanish_53,
    sPauseScreenTextSpanish_54,
    sPauseScreenTextSpanish_55,
    sPauseScreenTextSpanish_56,
    sPauseScreenTextSpanish_57,
    sPauseScreenTextSpanish_58,
    sPauseScreenTextSpanish_59,
    sPauseScreenTextSpanish_60,
    sPauseScreenTextSpanish_61,
    sPauseScreenTextSpanish_62,
    sPauseScreenTextSpanish_63,
    sPauseScreenTextSpanish_64,
    sPauseScreenTextSpanish_65,
    sPauseScreenTextSpanish_66,
    sPauseScreenTextSpanish_67,
    sPauseScreenTextSpanish_68,
    sPauseScreenTextSpanish_69,
    sPauseScreenTextSpanish_70,
    sPauseScreenTextSpanish_71,
    sPauseScreenTextSpanish_72,
    sPauseScreenTextSpanish_73,
    sPauseScreenTextSpanish_74,
    sPauseScreenTextSpanish_75,
    sPauseScreenTextSpanish_76,
    sPauseScreenTextSpanish_77,
    sPauseScreenTextSpanish_78,
    sPauseScreenTextSpanish_79,
    sPauseScreenTextSpanish_80,
    sPauseScreenTextSpanish_81,
    sPauseScreenTextSpanish_82,
    sPauseScreenTextSpanish_83,
    sPauseScreenTextSpanish_84,
    sPauseScreenTextSpanish_85,
    sPauseScreenTextSpanish_86,
    sPauseScreenTextSpanish_87,
    sPauseScreenTextSpanish_88,
    sPauseScreenTextSpanish_89,
    sPauseScreenTextSpanish_90,
    sPauseScreenTextSpanish_91,
    sPauseScreenTextSpanish_92,
    sPauseScreenTextSpanish_93,
    sPauseScreenTextSpanish_94,
    sPauseScreenTextSpanish_95,
    sPauseScreenTextSpanish_96,
    sPauseScreenTextSpanish_97,
    sPauseScreenTextSpanish_98,
    sPauseScreenTextSpanish_99,
    sPauseScreenTextSpanish_100,
    sPauseScreenTextSpanish_101,
    sPauseScreenTextSpanish_102,
    sPauseScreenTextSpanish_103,
    sPauseScreenTextSpanish_104,
    sPauseScreenTextSpanish_105,
    sPauseScreenTextSpanish_106,
    sPauseScreenTextSpanish_107,
    sPauseScreenTextSpanish_108,
    sPauseScreenTextSpanish_109,
    sPauseScreenTextSpanish_110
};

static u16* sMonologueTextPointersJapanese[19] = {
	(u16*)sMonologueTextJapanese_0,
	(u16*)sMonologueTextJapanese_1,
	(u16*)sMonologueTextJapanese_2,
	(u16*)sMonologueTextJapanese_3,
	(u16*)sMonologueTextJapanese_4,
	(u16*)sMonologueTextJapanese_5,
	(u16*)sMonologueTextJapanese_6,
	(u16*)sMonologueTextJapanese_7,
	(u16*)sMonologueTextJapanese_8,
	(u16*)sMonologueTextJapanese_9,
	(u16*)sMonologueTextJapanese_10,
	(u16*)sMonologueTextJapanese_11,
	(u16*)sMonologueTextJapanese_12,
	(u16*)sMonologueTextJapanese_13,
	(u16*)sMonologueTextJapanese_14,
	(u16*)sMonologueTextJapanese_15,
	(u16*)sMonologueTextJapanese_16,
	(u16*)sMonologueTextJapanese_17,
	(u16*)sMonologueTextJapanese_18
};

static u16* sMonologueTextPointersEnglish[19] = {
	(u16*)sMonologueTextEnglish_0,
	(u16*)sMonologueTextEnglish_1,
	(u16*)sMonologueTextEnglish_2,
	(u16*)sMonologueTextEnglish_3,
	(u16*)sMonologueTextEnglish_4,
	(u16*)sMonologueTextEnglish_5,
	(u16*)sMonologueTextEnglish_6,
	(u16*)sMonologueTextEnglish_7,
	(u16*)sMonologueTextEnglish_8,
	(u16*)sMonologueTextEnglish_9,
	(u16*)sMonologueTextEnglish_10,
	(u16*)sMonologueTextEnglish_11,
	(u16*)sMonologueTextEnglish_12,
	(u16*)sMonologueTextEnglish_13,
	(u16*)sMonologueTextEnglish_14,
	(u16*)sMonologueTextEnglish_15,
	(u16*)sMonologueTextEnglish_16,
	(u16*)sMonologueTextEnglish_17,
	(u16*)sMonologueTextEnglish_18
};

static u16* sMonologueTextPointersGerman[19] = {
	(u16*)sMonologueTextGerman_0,
	(u16*)sMonologueTextGerman_1,
	(u16*)sMonologueTextGerman_2,
	(u16*)sMonologueTextGerman_3,
	(u16*)sMonologueTextGerman_4,
	(u16*)sMonologueTextGerman_5,
	(u16*)sMonologueTextGerman_6,
	(u16*)sMonologueTextGerman_7,
	(u16*)sMonologueTextGerman_8,
	(u16*)sMonologueTextGerman_9,
	(u16*)sMonologueTextGerman_10,
	(u16*)sMonologueTextGerman_11,
	(u16*)sMonologueTextGerman_12,
	(u16*)sMonologueTextGerman_13,
	(u16*)sMonologueTextGerman_14,
	(u16*)sMonologueTextGerman_15,
	(u16*)sMonologueTextGerman_16,
	(u16*)sMonologueTextGerman_17,
	(u16*)sMonologueTextGerman_18
};

static u16* sMonologueTextPointersFrench[19] = {
	(u16*)sMonologueTextFrench_0,
	(u16*)sMonologueTextFrench_1,
	(u16*)sMonologueTextFrench_2,
	(u16*)sMonologueTextFrench_3,
	(u16*)sMonologueTextFrench_4,
	(u16*)sMonologueTextFrench_5,
	(u16*)sMonologueTextFrench_6,
	(u16*)sMonologueTextFrench_7,
	(u16*)sMonologueTextFrench_8,
	(u16*)sMonologueTextFrench_9,
	(u16*)sMonologueTextFrench_10,
	(u16*)sMonologueTextFrench_11,
	(u16*)sMonologueTextFrench_12,
	(u16*)sMonologueTextFrench_13,
	(u16*)sMonologueTextFrench_14,
	(u16*)sMonologueTextFrench_15,
	(u16*)sMonologueTextFrench_16,
	(u16*)sMonologueTextFrench_17,
	(u16*)sMonologueTextFrench_18
};

static u16* sMonologueTextPointersItalian[19] = {
	(u16*)sMonologueTextItalian_0,
	(u16*)sMonologueTextItalian_1,
	(u16*)sMonologueTextItalian_2,
	(u16*)sMonologueTextItalian_3,
	(u16*)sMonologueTextItalian_4,
	(u16*)sMonologueTextItalian_5,
	(u16*)sMonologueTextItalian_6,
	(u16*)sMonologueTextItalian_7,
	(u16*)sMonologueTextItalian_8,
	(u16*)sMonologueTextItalian_9,
	(u16*)sMonologueTextItalian_10,
	(u16*)sMonologueTextItalian_11,
	(u16*)sMonologueTextItalian_12,
	(u16*)sMonologueTextItalian_13,
	(u16*)sMonologueTextItalian_14,
	(u16*)sMonologueTextItalian_15,
	(u16*)sMonologueTextItalian_16,
	(u16*)sMonologueTextItalian_17,
	(u16*)sMonologueTextItalian_18
};

static u16* sMonologueTextPointersSpanish[19] = {
	(u16*)sMonologueTextSpanish_0,
	(u16*)sMonologueTextSpanish_1,
	(u16*)sMonologueTextSpanish_2,
	(u16*)sMonologueTextSpanish_3,
	(u16*)sMonologueTextSpanish_4,
	(u16*)sMonologueTextSpanish_5,
	(u16*)sMonologueTextSpanish_6,
	(u16*)sMonologueTextSpanish_7,
	(u16*)sMonologueTextSpanish_8,
	(u16*)sMonologueTextSpanish_9,
	(u16*)sMonologueTextSpanish_10,
	(u16*)sMonologueTextSpanish_11,
	(u16*)sMonologueTextSpanish_12,
	(u16*)sMonologueTextSpanish_13,
	(u16*)sMonologueTextSpanish_14,
	(u16*)sMonologueTextSpanish_15,
	(u16*)sMonologueTextSpanish_16,
	(u16*)sMonologueTextSpanish_17,
	(u16*)sMonologueTextSpanish_18
};

const struct FrameData* sGameOverCursorOam[3] = {
    sGameOverCursorOverlayOam,
    sGameOverCursorOverlayOam_73c29c,
    sGameOverCursorOverlayOam_73c29c
};
const u8* sGameOverTextGfxPointers[LANGUAGE_COUNT] = {
    sGameOverTextGfxJapanese,
    sGameOverTextGfxJapanese,
    sGameOverTextGfxJapanese,
    sGameOverTextGfxGerman,
    sGameOverTextGfxFrench,
    sGameOverTextGfxItalian,
    sGameOverTextGfxSpanish
};
const struct FrameData* sFileSelectFileOverlayOam[5] = {
    sFileSelectCopyArrowIdleOam,
    sFileSelectDeleteArrowIdleOam_740ac8,
    sFileSelectDeleteArrowIdleOam_740ad8,
    sFileSelectOam_7408c0,
    sFileSelectOam_7408c0
};
const struct FrameData* sFileSelectCopyArrowOam[3][3] = {
    {
        sFileSelectAudioLogosOam4_740800,
        sFileSelectAudioLogosOam4_740800,
        sFileSelectAudioLogosOam4_740820
    },
    {
        sFileSelectAudioLogosOam4_740840,
        sFileSelectAudioLogosOam4_740840,
        sFileSelectDeleteArrowIdleOam_740ae8
    },
    {
        sFileSelectDeleteArrowIdleOam_740b08,
        sFileSelectDeleteArrowIdleOam_740b28,
        sFileSelectDeleteArrowIdleOam_740b28
    }
};
const u16* sFileSelectTextTileOffsetsJapanese[6] = {
    sFileSelectTextTileOffsets_73dbcc,
    sFileSelectTextTileOffsets_73dbd8,
    sFileSelectTextTileOffsets_73dbde,
    sFileSelectTextTileOffsets_73dbde,
    sFileSelectTextTileOffsets_73dbde,
    sFileSelectTextTileOffsets_73dbe4
};
const u16* sFileSelectTextTileOffsetsEnglish[6] = {
    sFileSelectTextTileOffsets_73dbea,
    sFileSelectTextTileOffsets_73dbf6,
    sFileSelectTextTileOffsets_73dbfc,
    sFileSelectTextTileOffsets_73dbfc,
    sFileSelectTextTileOffsets_73dbfc,
    sFileSelectTextTileOffsets_73dc02
};
const u16* sFileSelectTextTileOffsetsFrench[6] = {
    sFileSelectTextTileOffsets_73dc08,
    sFileSelectTextTileOffsets_73dbf6,
    sFileSelectTextTileOffsets_73dbfc,
    sFileSelectTextTileOffsets_73dbfc,
    sFileSelectTextTileOffsets_73dbfc,
    sFileSelectTextTileOffsets_73dc02
};
const u16* sFileSelectTextTileOffsetsSpanish[6] = {
    sFileSelectTextTileOffsets_73dc14,
    sFileSelectTextTileOffsets_73dbf6,
    sFileSelectTextTileOffsets_73dbfc,
    sFileSelectTextTileOffsets_73dbfc,
    sFileSelectTextTileOffsets_73dbfc,
    sFileSelectTextTileOffsets_73dc02
};
const u16** sFileSelectTextTileOffsets[LANGUAGE_COUNT] = {
    [LANGUAGE_JAPANESE] = sFileSelectTextTileOffsetsJapanese,
    [LANGUAGE_HIRAGANA] = sFileSelectTextTileOffsetsJapanese,
    [LANGUAGE_ENGLISH] = sFileSelectTextTileOffsetsEnglish,
    [LANGUAGE_GERMAN] = sFileSelectTextTileOffsetsEnglish,
    [LANGUAGE_FRENCH] = sFileSelectTextTileOffsetsFrench,
    [LANGUAGE_ITALIAN] = sFileSelectTextTileOffsetsEnglish,
    [LANGUAGE_SPANISH] = sFileSelectTextTileOffsetsSpanish
};
const struct FrameData* sFileSelectAreaNameOam[LANGUAGE_COUNT][7] = {
    {
        sFileSelectFilePanelOam3_740a38,
        sFileSelectFilePanelOam3_7409d8,
        sFileSelectFilePanelOam3_7409e8,
        sFileSelectFilePanelOam3_7409f8,
        sFileSelectFilePanelOam3_740a08,
        sFileSelectFilePanelOam3_740a18,
        sFileSelectFilePanelOam3_740a28
    },
    {
        sFileSelectFilePanelOam3_740a38,
        sFileSelectFilePanelOam3_7409d8,
        sFileSelectFilePanelOam3_7409e8,
        sFileSelectFilePanelOam3_7409f8,
        sFileSelectFilePanelOam3_740a08,
        sFileSelectFilePanelOam3_740a18,
        sFileSelectFilePanelOam3_740a28
    },
    {
        sFileSelectFilePanelOam3_740a38,
        sFileSelectFilePanelOam3_7409d8,
        sFileSelectFilePanelOam3_7409e8,
        sFileSelectFilePanelOam3_7409f8,
        sFileSelectFilePanelOam3_740a08,
        sFileSelectFilePanelOam3_740a18,
        sFileSelectFilePanelOam3_740a28
    },
    {
        sFileSelectOam_740c08,
        sFileSelectOam_740ba8,
        sFileSelectOam_740bb8,
        sFileSelectOam_740bc8,
        sFileSelectOam_740bd8,
        sFileSelectOam_740be8,
        sFileSelectOam_740bf8
    },
    {
        sFileSelectOam_740c78,
        sFileSelectOam_740c18,
        sFileSelectOam_740c28,
        sFileSelectOam_740c38,
        sFileSelectOam_740c48,
        sFileSelectOam_740c58,
        sFileSelectOam_740c68
    },
    {
        sFileSelectOam_740ce8,
        sFileSelectOam_740c88,
        sFileSelectOam_740c98,
        sFileSelectOam_740ca8,
        sFileSelectOam_740cb8,
        sFileSelectOam_740cc8,
        sFileSelectOam_740cd8
    },
    {
        sFileSelectOam_740cf8,
        sFileSelectFilePanelOam3_7409d8,
        sFileSelectFilePanelOam3_7409e8,
        sFileSelectFilePanelOam3_7409f8,
        sFileSelectFilePanelOam3_740a08,
        sFileSelectFilePanelOam3_740a18,
        sFileSelectFilePanelOam3_740a28
    }
};
const u16* sFileSelectTextsJapanese[25] = {
    sFileSelectTextJapanese_0,
    sFileSelectTextJapanese_1,
    sFileSelectTextJapanese_2,
    sFileSelectTextJapanese_3,
    sFileSelectTextJapanese_4,
    sFileSelectTextJapanese_5,
    sFileSelectTextJapanese_6,
    sFileSelectTextJapanese_7,
    sFileSelectTextJapanese_8,
    sFileSelectTextJapanese_9,
    sFileSelectTextJapanese_10,
    sFileSelectTextJapanese_11,
    sFileSelectTextJapanese_12,
    sFileSelectTextJapanese_13,
    sFileSelectTextJapanese_14,
    sFileSelectTextJapanese_15,
    sFileSelectTextJapanese_16,
    sFileSelectTextJapanese_17,
    sFileSelectTextJapanese_18,
    sFileSelectTextJapanese_19,
    sFileSelectTextJapanese_20,
    sFileSelectTextJapanese_21,
    sFileSelectTextJapanese_22,
    sFileSelectTextJapanese_23,
    sFileSelectTextJapanese_24
};

const u16* sFileSelectTextsEnglish[25] = {
    sFileSelectTextEnglish_0,
    sFileSelectTextEnglish_1,
    sFileSelectTextEnglish_2,
    sFileSelectTextEnglish_3,
    sFileSelectTextEnglish_4,
    sFileSelectTextEnglish_5,
    sFileSelectTextEnglish_6,
    sFileSelectTextEnglish_7,
    sFileSelectTextEnglish_8,
    sFileSelectTextEnglish_9,
    sFileSelectTextEnglish_10,
    sFileSelectTextEnglish_11,
    sFileSelectTextEnglish_12,
    sFileSelectTextEnglish_13,
    sFileSelectTextEnglish_14,
    sFileSelectTextEnglish_15,
    sFileSelectTextEnglish_16,
    sFileSelectTextEnglish_17,
    sFileSelectTextEnglish_18,
    sFileSelectTextEnglish_19,
    sFileSelectTextEnglish_20,
    sFileSelectTextEnglish_21,
    sFileSelectTextEnglish_22,
    sFileSelectTextEnglish_23,
    sFileSelectTextEnglish_24
};

const u16* sFileSelectTextsGerman[25] = {
    sFileSelectTextGerman_0,
    sFileSelectTextGerman_1,
    sFileSelectTextGerman_2,
    sFileSelectTextGerman_3,
    sFileSelectTextGerman_4,
    sFileSelectTextGerman_5,
    sFileSelectTextGerman_6,
    sFileSelectTextGerman_7,
    sFileSelectTextGerman_8,
    sFileSelectTextGerman_9,
    sFileSelectTextGerman_10,
    sFileSelectTextGerman_11,
    sFileSelectTextGerman_12,
    sFileSelectTextGerman_13,
    sFileSelectTextGerman_14,
    sFileSelectTextGerman_15,
    sFileSelectTextGerman_16,
    sFileSelectTextGerman_17,
    sFileSelectTextGerman_18,
    sFileSelectTextGerman_19,
    sFileSelectTextGerman_20,
    sFileSelectTextGerman_21,
    sFileSelectTextGerman_22,
    sFileSelectTextGerman_23,
    sFileSelectTextGerman_24
};

const u16* sFileSelectTextsFrench[25] = {
    sFileSelectTextFrench_0,
    sFileSelectTextFrench_1,
    sFileSelectTextFrench_2,
    sFileSelectTextFrench_3,
    sFileSelectTextFrench_4,
    sFileSelectTextFrench_5,
    sFileSelectTextFrench_6,
    sFileSelectTextFrench_7,
    sFileSelectTextFrench_8,
    sFileSelectTextFrench_9,
    sFileSelectTextFrench_10,
    sFileSelectTextFrench_11,
    sFileSelectTextFrench_12,
    sFileSelectTextFrench_13,
    sFileSelectTextFrench_14,
    sFileSelectTextFrench_15,
    sFileSelectTextFrench_16,
    sFileSelectTextFrench_17,
    sFileSelectTextFrench_18,
    sFileSelectTextFrench_19,
    sFileSelectTextFrench_20,
    sFileSelectTextFrench_21,
    sFileSelectTextFrench_22,
    sFileSelectTextFrench_23,
    sFileSelectTextFrench_24
};

const u16* sFileSelectTextsItalian[25] = {
    sFileSelectTextItalian_0,
    sFileSelectTextItalian_1,
    sFileSelectTextItalian_2,
    sFileSelectTextItalian_3,
    sFileSelectTextItalian_4,
    sFileSelectTextItalian_5,
    sFileSelectTextItalian_6,
    sFileSelectTextItalian_7,
    sFileSelectTextItalian_8,
    sFileSelectTextItalian_9,
    sFileSelectTextItalian_10,
    sFileSelectTextItalian_11,
    sFileSelectTextItalian_12,
    sFileSelectTextItalian_13,
    sFileSelectTextItalian_14,
    sFileSelectTextItalian_15,
    sFileSelectTextItalian_16,
    sFileSelectTextItalian_17,
    sFileSelectTextItalian_18,
    sFileSelectTextItalian_19,
    sFileSelectTextItalian_20,
    sFileSelectTextItalian_21,
    sFileSelectTextItalian_22,
    sFileSelectTextItalian_23,
    sFileSelectTextItalian_24
};

const u16* sFileSelectTextsSpanish[25] = {
    sFileSelectTextSpanish_0,
    sFileSelectTextSpanish_1,
    sFileSelectTextSpanish_2,
    sFileSelectTextSpanish_3,
    sFileSelectTextSpanish_4,
    sFileSelectTextSpanish_5,
    sFileSelectTextSpanish_6,
    sFileSelectTextSpanish_7,
    sFileSelectTextSpanish_8,
    sFileSelectTextSpanish_9,
    sFileSelectTextSpanish_10,
    sFileSelectTextSpanish_11,
    sFileSelectTextSpanish_12,
    sFileSelectTextSpanish_13,
    sFileSelectTextSpanish_14,
    sFileSelectTextSpanish_15,
    sFileSelectTextSpanish_16,
    sFileSelectTextSpanish_17,
    sFileSelectTextSpanish_18,
    sFileSelectTextSpanish_19,
    sFileSelectTextSpanish_20,
    sFileSelectTextSpanish_21,
    sFileSelectTextSpanish_22,
    sFileSelectTextSpanish_23,
    sFileSelectTextSpanish_24
};

const u16* sFileSelectEmptyFileTextPointers[2] = {
    sFileSelectEmptyFileText_0,
    sFileSelectEmptyFileText_1
};
const u16** sFileSelectTexts[LANGUAGE_COUNT] = {
    [LANGUAGE_JAPANESE] = sFileSelectTextsJapanese,
    [LANGUAGE_HIRAGANA] = sFileSelectTextsJapanese,
    [LANGUAGE_ENGLISH] = sFileSelectTextsEnglish,
    [LANGUAGE_GERMAN] = sFileSelectTextsGerman,
    [LANGUAGE_FRENCH] = sFileSelectTextsFrench,
    [LANGUAGE_ITALIAN] = sFileSelectTextsItalian,
    [LANGUAGE_SPANISH] = sFileSelectTextsSpanish
};
const u16** sFileSelectEmptyFileTexts[LANGUAGE_COUNT] = {
    [LANGUAGE_JAPANESE] = sFileSelectEmptyFileTextPointers,
    [LANGUAGE_HIRAGANA] = sFileSelectEmptyFileTextPointers,
    [LANGUAGE_ENGLISH] = sFileSelectEmptyFileTextPointers,
    [LANGUAGE_GERMAN] = sFileSelectEmptyFileTextPointers,
    [LANGUAGE_FRENCH] = sFileSelectEmptyFileTextPointers,
    [LANGUAGE_ITALIAN] = sFileSelectEmptyFileTextPointers,
    [LANGUAGE_SPANISH] = sFileSelectEmptyFileTextPointers
};

/**
 * @brief 87610 | f8 | Handler for intro
 * 
 */
boolu32 IntroHandler(void) 
{
    boolu32 result;

    result = FALSE;
    
    if (gChangedInput & (KEY_START | KEY_A))
    {
        if (gSubGameMode1 == 3)
        {
            if (INTRO_DATA.handlerTimer != 0)
                INTRO_DATA.handlerTimer = 0;
        }
        else if (gSubGameMode1 != 0 && gSubGameMode1 != 3)
        {
            if (READ_16(REG_BLDCNT) & BLDCNT_ALPHA_BLENDING_EFFECT)
                WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
            
            INTRO_DATA.handlerTimer = 0;
            gSubGameMode1 = 3;
            FadeAllSounds(20);
            FadeMusic(20);
        }
    }

    switch (gSubGameMode1)
    {
        case 0:
            NewFileIntroInit();
            gSubGameMode1 = 1;
            break;
        
        case 1:
            if (IntroSpaceView())
                gSubGameMode1 = 2;
            break;
        
        case 2:
            if (IntroSamusShipCrashing())
                gSubGameMode1 = 3;
            break;
        
        case 3:
            if (INTRO_DATA.handlerTimer == 0)
            {
                if (gWrittenToBldy < BLDY_MAX_VALUE)
                    gWrittenToBldy++;
                else
                    result = TRUE;
            }
            else
                INTRO_DATA.handlerTimer--;
            
            SpecialCutsceneDrawAllOam(); 
    }

    return result;
}

 /**
 * @brief 87708 | 218 | Handler for new file intro
 * 
 */
boolu32 NewFileIntroHandler(void) 
{
    boolu32 result;

    result = FALSE;

    switch (gSubGameMode1)
    {
        case 0:
            StopAllMusicAndSounds();
            NewFileIntroInit();

            if (gGameCompletion.introPlayed == TRUE)
                return TRUE;
            else 
                gSubGameMode1 = 1;
            break;

        case 1:
            INTRO_DATA.timer++;
            if (INTRO_DATA.timer >= 100)
            {
                INTRO_DATA.timer = 0;
                gSubGameMode1 = 2;
            }
            break;

        case 2:
            if (NewFileIntroSr388Preview())
                gSubGameMode1 = 3;
            break;

        case 3:
            if (NewFileIntroInSr388())
                gSubGameMode1 = 4;
            break;

        case 4:
            if (NewFileIntroSamusShipFlying())
                gSubGameMode1 = 5;
            break;

        case 5:
            if (NewFileIntroSamusFainting())
                gSubGameMode1 = 6;
            break;

        case 6:
            if (NewFileIntroSamusDrifting())
                gSubGameMode1 = 7;
            break;

        case 7:
            if (NewFileIntroSamusFound())
                gSubGameMode1 = 8;
            break;

        case 8:
            if (NewFileIntroSamusGettingCured())
                gSubGameMode1 = 9;
            break;

        case 9:
            if (NewFileIntroSamusCured())
                gSubGameMode1 = 10;
            break;

        case 10:
            if (NewFileIntroArrivingAtBsl())
                gSubGameMode1 = 11;
            break;

        case 11:
            if (NewFileIntroLandingOnBsl())
            {
                INTRO_DATA.handlerTimer = 0;
                gSubGameMode1 = 12;
            }
            break;
        
        case 12:
            INTRO_DATA.handlerTimer++;
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (INTRO_DATA.handlerTimer == 1)
                {
                    INTRO_DATA.handlerTimer = 0;
                    gWrittenToBldy++;
                }
            }
            else
            {
                if (INTRO_DATA.handlerTimer == 1)
                {
                    Sram_ProcessIntroSave(0);
                }
                else if (INTRO_DATA.handlerTimer == 2)
                {
                    Sram_ProcessIntroSave(1);
                } 
                else if (INTRO_DATA.handlerTimer == 3)
                {
                    Sram_ProcessIntroSave(2);
                }
                else if (INTRO_DATA.handlerTimer == 4)
                {
                    Sram_ProcessIntroSave(3);
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.handlerTimer = 0;
                    result = TRUE;
                }
            }

            SpecialCutsceneDrawAllOam();
    }

    return result;
}

 /**
 * @brief 87920 | 50 | Main handler for the special cutscenes game mode (plays the cutscene of gCurrentCutscene)
 * 
 */
boolu32 SpecialCutsceneHandler(void) 
{
    boolu32 result;
    boolu32 done;
    
    result = FALSE;

    switch (gCurrentCutscene)
    {
        default:
            result = TRUE;
            done = FALSE;
            break;

        case 1:
            done = IntroHandler();
            break;

        case 2:
            done = NewFileIntroHandler();
            break;

        case 3:
            done = EndingHandler();
            break;

        case 4:
            done = DiedFromSr388CollisionHandler();
    }

    if (done)
    {
        StopAllMusicAndSounds();
        result = TRUE;
    }
    
    return result;
}

 /**
 * @brief 87970 | 94 | V-blank for the new file intro Samus ship flying cutscene
 * 
 */
void NewFileIntroSamusShipFlyingVblank(void) 
{
    DMA3_COPY_32(gOamData, OAM_BASE, 256);

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    WRITE_16(REG_BLDY, gWrittenToBldy);

    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

 /**
 * @brief 87a04 | 264 | Setup for the new file intro Samus ship flying cutscene
 * 
 */
void NewFileIntroSamusShipFlyingInit(void) 
{
    u16 i;
    
    CallbackSetVBlank(SpecialCutsceneLoadingVblank);
    
    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    for (i = 0; i < 8; i++)
        LZ77UncompVram(sIntroBslObjectGfxPointers[i], VRAM_OBJ + i * 0x1000);
    
    DMA3_COPY_32(sIntroSamusShipPal, PALRAM_OBJ, 5 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sPal_598150, PALRAM_OBJ + 0x100, 2 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / 4);

    LZ77UncompWram(sIntroBslSpaceBgGfx, EWRAM_BASE + 0x10000);

    DMA3_COPY_32(EWRAM_BASE + 0x10000, VRAM_BASE, (VRAM_SIZE / 3) / 4);

    LZ77UncompVram(sIntroBslTilemap, VRAM_BASE + 0xE800);
    LZ77UncompVram(sIntroSpaceTilemap, VRAM_BASE + 0xF800);

    DMA3_COPY_32(sIntroBslSpaceBgPal, PALRAM_BASE + 0x100, 8 * PAL_ROW_SIZE / 4);

    WRITE_16(PALRAM_BASE, 0);

    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 48;
    gBg2YPosition = -8;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
    WRITE_16(REG_BG0CNT, 28 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | 2 << BGCNT_CHAR_BASE_BLOCK_SHIFT);
    WRITE_16(REG_BG2CNT, BGCNT_SIZE_512x256 << BGCNT_SCREEN_SIZE_SHIFT | 29 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | BGCNT_LOW_MID_PRIORITY);
    WRITE_16(REG_BG3CNT, 31 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | BGCNT_LOW_PRIORITY);

    NewFileIntroSetupOam(200, 250, 0, 0);
    NewFileIntroSetupOam(1, (s16)gBg2XPosition, (s16)gBg2YPosition, 0);
    NewFileIntroSetupOam(2, 160, 90, 0);
    NewFileIntroSetupOam(4, 0, 0, 1);

    for (i = 0; i < 10; i++)
        NewFileIntroSetupOam(3, SpecialCutsceneGetRandomNumber(), SpecialCutsceneGetRandomNumber(), 1);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / 4 );

    INTRO_DATA.pText = sCutsceneTextNone;
    WRITE_16(REG_DISPCNT, DCNT_OBJ | DCNT_BG3 | DCNT_BG2);

    CallbackSetVBlank(NewFileIntroSamusShipFlyingVblank);
}

 /**
 * @brief 87C68 | 188 | Processes the new file intro Samus ship flying cutscene
 * 
 */
boolu32 NewFileIntroSamusShipFlyingProcess(void) 
{
    boolu32 result;

    result = FALSE;

    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.textAdvanceState == 0)
        INTRO_DATA.textAdvanceState = 1;
    
    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.activeOamCount < 12)
                NewFileIntroSetupOam(3, 0, SpecialCutsceneGetRandomNumber(), 1);

            if (INTRO_DATA.timer == 99)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
            }
            else if (INTRO_DATA.timer == 100)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][10];
                INTRO_DATA.subStage = 1;
            }
            break;
        
        case 1:
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.activeOamCount < 12)
                NewFileIntroSetupOam(3, 0, SpecialCutsceneGetRandomNumber(), 1);

            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 2;
            }
            break;

        case 2:
            if (INTRO_DATA.timer == 30)
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = BLDY_MAX_VALUE;
                result = TRUE;
            }
    }
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    IntroProcessText();

    return result;
}

 /**
 * @brief 87df0 | a0 | Main handler for new file intro Samus ship flying cutscene
 * 
 */
boolu32 NewFileIntroSamusShipFlying(void)
{
    boolu32 result;

    result = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusShipFlyingInit();
            INTRO_DATA.stage = 1;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroSamusShipFlyingProcess())
            {
                INTRO_DATA.stage = 3;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;   
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
                gWrittenToBldy++;
            else 
            {
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.subStage = 0;
                INTRO_DATA.stage = 0;
                result = TRUE;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
    }

    return result;
}

 /**
 * @brief 87e90 | 1d8 | Setup for the new file intro Samus fainting cutscene
 * 
 */
void NewFileIntroSamusFaintingInit(void)
{
    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / 4);

    LZ77UncompVram(sIntroSamusSittingTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusSittingTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusSittingGfx, VRAM_BASE);

    DMA3_COPY_32(sIntroSamusSittingPal, PALRAM_BASE, 128);

    WRITE_16(PALRAM_BASE, 0);

    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroBslSpaceBgPal, PALRAM_BASE + 0x100, 64);
    
    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 10;
    gBg2YPosition = 2;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
    WRITE_16(REG_BG0CNT, 28 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | 2 << BGCNT_CHAR_BASE_BLOCK_SHIFT);
    WRITE_16(REG_BG2CNT, 30 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | BGCNT_LOW_MID_PRIORITY);
    WRITE_16(REG_BG3CNT, 31 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | BGCNT_LOW_PRIORITY);

    NewFileIntroSetupOam(200, 250, 0, 0);
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, VRAM_SIZE / 24 );

    INTRO_DATA.pText = sCutsceneTextNone;
    
    WRITE_16(REG_DISPCNT, DCNT_OBJ | DCNT_BG3 | DCNT_BG2);

    CallbackSetVBlank(NewFileIntroSamusShipFlyingVblank);
    
    gWrittenToBldy = 0;
    gWrittenToBldalpha_Eva = 12;
    gWrittenToBldalpha_Evb = 8;
}

 /**
 * @brief 88068 | 13c | Processes the new file intro Samus fainting cutscene
 * 
 */
boolu32 NewFileIntroSamusFaintingProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.textAdvanceState == 0)
        INTRO_DATA.textAdvanceState = 1;
    
    INTRO_DATA.timer += 1;
    
    switch (INTRO_DATA.subStage) 
    {
        case 0:
            if (INTRO_DATA.timer == 1)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_FIRST_TARGET_PIXEL);
                NewFileIntroSetupOam(10, gBg2XPosition, gBg2YPosition, 1);
            }
            else if (INTRO_DATA.timer == 59)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
            }
            else if (INTRO_DATA.timer == 60)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][11];
                INTRO_DATA.subStage = 1;
            }
            break;
        
        case 1:
            INTRO_DATA.timer = 0;

            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 2;
                gWrittenToBldy = 16;
            }
            break;
        
        case 2:
            if (INTRO_DATA.timer == 30) 
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
                INTRO_DATA.timer = 0;
                finished = TRUE;
            }
            break;
    }
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 881a4 | 9c | Main handler for the new file intro Samus fainting cutscene
 * 
 */
boolu32 NewFileIntroSamusFainting(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusFaintingInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroSamusFaintingProcess())
            {
                INTRO_DATA.stage = 3;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
            }
            break;

        case 3:
            if (gWrittenToBldy < 16)
            {
                gWrittenToBldy++;
            }
            else 
            {
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.subStage = 0;
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 88240 | 26c | Setup for the 'gunship drifting away from BSL ship' cutscene
 * 
 */
void NewFileIntroSamusDriftingInit(void)
{
    u16 i;

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);
    
    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
    
    for (i = 0; i < 8; i++)
        LZ77UncompVram(sIntroBslObjectGfxPointers[i], VRAM_OBJ + i * 0x1000);
    
    DMA3_COPY_32(sIntroSamusShipPal, PALRAM_OBJ, 5 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sPal_598150, PALRAM_OBJ + 0x100, 2 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / 4);
    
    LZ77UncompWram(sIntroBslSpaceBgGfx, EWRAM_BASE + 0x10000);
    
    DMA3_COPY_32(EWRAM_BASE + 0x10000, VRAM_BASE, (VRAM_SIZE / 3) / 4);
    
    LZ77UncompVram(sIntroBslTilemap, VRAM_BASE + 0xE800);
    LZ77UncompVram(sIntroSpaceTilemap, VRAM_BASE + 0xF800);
    
    DMA3_COPY_32(sIntroBslSpaceBgPal, PALRAM_BASE + 0x100, 8 * PAL_ROW_SIZE / 4);
    
    SET_BACKDROP_COLOR(COLOR_BLACK);

    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    
    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);
    
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 48;
    gBg2YPosition = -8;
    gBg3XPosition = 0;
    gBg3YPosition = 0;
    
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 29, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_512x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    
    NewFileIntroSetupOam(200, 250, 0, 0);
    NewFileIntroSetupOam(1, gBg2XPosition, gBg2YPosition, 0);
    NewFileIntroSetupOam(20, 160, 90, 0);
    NewFileIntroSetupOam(4, 0, 0, 1);
    
    for (i = 0; i < 10; i++)
        NewFileIntroSetupOam(3, SpecialCutsceneGetRandomNumber(), SpecialCutsceneGetRandomNumber(), 1);
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    
    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / 4);
    
    INTRO_DATA.pText = sCutsceneTextNone;
    
    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);
    
    CallbackSetVBlank(NewFileIntroSamusShipFlyingVblank);
    
    gWrittenToBldy = 0;
}

 /**
 * @brief 884ac | c8 | V-blank for the 'Samus losing conciousness' cutscene
 * 
 */
void NewFileIntroSamusLosingConsciousnessVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    WRITE_16(REG_BLDY, gWrittenToBldy);

    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
    
    if (INTRO_DATA.paletteUpdate1 == 1)
    {
        INTRO_DATA.paletteUpdate1 = 0;
        DMA3_COPY_32(sIntroSamusCloseupGrayscalePal, PALRAM_BASE, 4 * PAL_ROW_SIZE / 4);
    }
}

 /**
 * @brief 88574 | 1e0 | Setup for the 'Samus losing conciousness' cutscene
 * 
 */
void NewFileIntroSamusLosingConsciousnessInit(void) 
{
    u16 i;

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);
    
    DMA3_FILL_32(0, 0x030016a0, 720); // TODO: Find out what 16a0 is
    
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / 4);

    for (i = 0; i < 6; i++)
        LZ77UncompVram(sIntroSamusHelmetCloseupBgGfxPointers[i], VRAM_BASE + i * 0x1000);
    
    LZ77UncompVram(sIntroSamusHelmetCloseupTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusHelmetCloseupTilemap, VRAM_BASE + 0xF800);

    DMA3_COPY_32(sIntroSamusHelmetCloseupPal, PALRAM_BASE, 4 * PAL_ROW_SIZE / 4);
    
    SET_BACKDROP_COLOR(COLOR_BLACK);

    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    
    DMA3_COPY_32(sIntroBslSpaceBgPal, PALRAM_BASE + 0x100, 8 * PAL_ROW_SIZE / 4);
    
    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);
    
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 10;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;
    
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    
    NewFileIntroSetupOam(200, 250, 0, 0);
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    
    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / 4);
    
    INTRO_DATA.pText = sCutsceneTextNone;
    
    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);
    
    CallbackSetVBlank(NewFileIntroSamusLosingConsciousnessVblank);
    
    gWrittenToBldy = 0;
    gWrittenToBldalpha_Eva = 12;
    gWrittenToBldalpha_Evb = 8;
}

 /**
 * @brief 88754 | 25c | Setup for the 'gunship drifting into asteroids' cutscene
 * 
 */
void NewFileIntroSamusDriftingIntoAsteroidsInit(void) 
{
    u16 i;
    void* temp1;
    u32 temp2;
    
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);
    
    CallbackSetVBlank(SpecialCutsceneLoadingVblank);
    
    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
    
    for (i = 0; i < 8; i++)
        LZ77UncompVram(sIntroBslObjectGfxPointers[i], VRAM_OBJ + i * 0x1000);
    
    DMA3_COPY_32(sIntroSpaceObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sPal_598150, PALRAM_OBJ + 0x100, 2 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / 4);

    LZ77UncompVram(sTitleScreenSpaceBackgroundGfx, VRAM_BASE);
    LZ77UncompVram(sTitleScreenSpaceBackgroundTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    
    DMA3_COPY_32(sIntroSpaceBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sIntroSubtitlePal, PALRAM_BASE + 0x1E0, PAL_ROW_SIZE / 4);
    
    SET_BACKDROP_COLOR(COLOR_BLACK);
    
    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);
    
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;
    
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);

    gWrittenToBldalpha_Eva = gWrittenToBldalpha_Evb = 0;

    //WRITE_16(REG_BLDALPHA, 0); // Doesn't match
    temp1 = REG_BLDALPHA;
    temp2 = 0;
    WRITE_16(temp1, temp2);
    
    NewFileIntroSetupOam(30, 140, 140, 0);
    NewFileIntroSetupOam(31, 140, 80, 0);
    
    for (i = 0; i < 4; i++)
        NewFileIntroSetupOam(36, SpecialCutsceneGetRandomNumber(), SpecialCutsceneGetRandomNumber(), 1);
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    
    INTRO_DATA.pText = sCutsceneTextNone;
    
    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / 4);
    
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG3 | DCNT_OBJ);
    
    CallbackSetVBlank(NewFileIntroSamusShipFlyingVblank);
    
    gWrittenToBldy = 0;
}

 /**
 * @brief 889b0 | 318 | To document
 * 
 */
boolu32 NewFileIntroSamusDriftingProcess(void)
{
    boolu32 finished;
    s16 x;
    s16 y;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && !INTRO_DATA.textAdvanceState)
        INTRO_DATA.textAdvanceState = 1;
    
    INTRO_DATA.timer++;
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.activeOamCount < 12)
                NewFileIntroSetupOam(3, 0, SpecialCutsceneGetRandomNumber(), TRUE);
            
            if (INTRO_DATA.timer != 149) // Why?
            {
                if (INTRO_DATA.timer == 150)
                {
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.subStage = 1;
                    gWrittenToBldy = BLDY_MAX_VALUE;
                }
            }
            break;
        
        case 1:
            NewFileIntroSamusLosingConsciousnessInit();
            INTRO_DATA.timer = 0;
            INTRO_DATA.subStage = 2;
            break;
        
        case 2:
            if (INTRO_DATA.timer == 1)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
                NewFileIntroSetupOam(10, gBg2XPosition, gBg2YPosition, TRUE);
                gWrittenToBldy = 0;
            }
            else if (INTRO_DATA.timer == 118)
            {
                break;
            }
            else if (INTRO_DATA.timer == 120)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.paletteUpdate1 = 1;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 3;
            }
            break;

        case 3:
            if (INTRO_DATA.timer == 60)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
                gWrittenToBldy = 16;
            }
            break;
        
        case 4:
            NewFileIntroSamusDriftingIntoAsteroidsInit();
            INTRO_DATA.timer = 0;
            INTRO_DATA.subStage = 5;
            break;
        
        case 5:
            INTRO_DATA.timer = 0;
            
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.activeOamCount < 12)
            {
                x = SpecialCutsceneGetRandomNumber();
                y = SpecialCutsceneGetRandomNumber();
                NewFileIntroSetupOam(36, x, y, TRUE);
            }
            break;

        case 6:
            WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);
            
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (INTRO_DATA.timer == 3)
                {
                    INTRO_DATA.timer = 0;
                    gWrittenToBldy++;
                }
            } 
            else if (INTRO_DATA.timer == 10)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 7;
                finished = TRUE;
            }
            
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.activeOamCount < 12)
            {
                x = SpecialCutsceneGetRandomNumber();
                y = SpecialCutsceneGetRandomNumber();
                NewFileIntroSetupOam(36, x, y, TRUE);
            }
            break;
        
        case 7:
            if (gWrittenToBldy) 
            {
                if (INTRO_DATA.timer == 6) 
                {
                    INTRO_DATA.timer = 0;
                    gWrittenToBldy--;
                }
            } 
            else 
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 8;
            }

            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.activeOamCount < 12)
            {
                x = SpecialCutsceneGetRandomNumber();
                y = SpecialCutsceneGetRandomNumber();
                NewFileIntroSetupOam(36, x, y, TRUE);
            }
            break;
        
        case 8:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.textAdvanceState == 1)
            {
                SpecialCutsceneDestroyOamOfType(201);
                INTRO_DATA.subStage = 9;
            }
            
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.activeOamCount < 12)
            {
                x = SpecialCutsceneGetRandomNumber();
                y = SpecialCutsceneGetRandomNumber();
                NewFileIntroSetupOam(36, x, y, TRUE);
            }
            break;
        
        case 9:
            finished = TRUE;
            break;
    }
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 88cc8 | 9c | To document
 * 
 */
boolu32 NewFileIntroSamusDrifting(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusDriftingInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroSamusDriftingProcess())
            {
                INTRO_DATA.stage = 3;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else 
            {
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.subStage = 0;
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 88d64 | 150 | To document
 * 
 */
void NewFileIntroProcessBslShip(struct SpecialCutsceneOam *pOam)
{
    s32 cos;
    s32 sin;
    
    pOam->unk_4 = pOam->xPosition;
    
    if (pOam->stage == 0) 
    {
        pOam->stage = 2;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_A++;
        pOam->xPosition = (((60 - pOam->spawnX) * pOam->unk_A) >> 10) + pOam->spawnX;
        pOam->yPosition = (((10 - pOam->spawnY) * pOam->unk_A) >> 10) + pOam->spawnY;
        
        if (pOam->xPosition > 39) 
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 1) 
        {
            pOam->unk_A = 0;
            pOam->spawnX = 0;
            pOam->spawnY = 4;
            pOam->unk_8 = pOam->yPosition;
            pOam->timer = 128;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        cos = pOam->spawnX * COS(pOam->timer);
        sin = pOam->spawnY * SIN(pOam->timer);
        pOam->yPosition = ((SIN(0) * cos + COS(0) * sin) >> 16) + pOam->unk_8;
        pOam->timer++;
        
        if (pOam->unk_A != 60) // Why?
        {
            if (pOam->unk_A == 200)
            {
                pOam->unk_A = 0;
                pOam->stage = 4;
            } 
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->stage = 5;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
    } 
    else if (pOam->stage == 5)
    {    
        pOam->unk_A++;
        pOam->xPosition = (((520 - pOam->spawnX) * pOam->unk_A) >> 10) + pOam->spawnX;
        pOam->yPosition = (((100 - pOam->spawnY) * pOam->unk_A) >> 10) + pOam->spawnY;

        if (pOam->xPosition >= 520)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 6;
        }
    }
    
    gBg2XPosition = pOam->xPosition;
    gBg2YPosition = pOam->yPosition;
}

 /**
 * @brief 88eb4 | 128 | To document
 * 
 */
void NewFileIntroProcessFlyingSamusShip(struct SpecialCutsceneOam *pOam)
{
    s32 rotation;
    s32 cos;
    s32 sin;
    s32 x;
    s32 y;

    rotation = 0;
    
    if (pOam->stage == 0)
    {
        pOam->unk_4 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->timer = 64;
        pOam->stage = 2;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->scaling -= 2;

        if (pOam->timer == 128)
        {
            pOam->stage = 2;
            pOam->scaling = Q_8_8(1);
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->spawnX = 0;
        pOam->spawnY = 8;
        pOam->unk_4 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 3;
    }
    else if (pOam->stage == 3)
    {
        pOam->timer += 2;
    }
    else if (pOam->stage == 4)
    {
        pOam->timer++;
        pOam->unk_A++;
        if (pOam->unk_A == 180)
        {
            pOam->unk_A = 0;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        pOam->spawnX = 280 - pOam->xPosition;
        pOam->spawnY = 60;
        pOam->unk_4 = pOam->xPosition + pOam->spawnX;
        pOam->unk_8 = pOam->yPosition;
        pOam->timer = 128;
        pOam->stage = 6;
    }
    else if (pOam->stage == 6)
    {
        pOam->timer++;
        if (pOam->timer == 0)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
    
    cos = pOam->spawnX * COS(pOam->timer);
    sin = pOam->spawnY * SIN(pOam->timer);
    
    x = cos * COS(rotation) - sin * SIN(0);
    y = cos * SIN(0) + sin * COS(rotation);
    
    pOam->xPosition = (x >> 16) + pOam->unk_4;
    pOam->yPosition = (y >> 16) + pOam->unk_8;
}

 /**
 * @brief 88fdc | b4 | To document
 * 
 */
void NewFileIntroProcessHorizontalParticle(struct SpecialCutsceneOam *pOam)
{
    s32 rng;
    
    if (pOam->stage == 0)
    {
        rng = SpecialCutsceneGetRandomNumber() & 7;
        pOam->unk_8 = rng + 1;
        rng = SpecialCutsceneGetRandomNumber() & 3;
        pOam->unk_4 = rng;
        pOam->pOam = sIntroHorizontalParticleOamPointers[pOam->unk_4];
        pOam->spawnX = pOam->xPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_A++;
        pOam->xPosition = ((pOam->unk_8 * pOam->unk_A) >> 4) + pOam->spawnX;
        
        pOam->timer++;
        if (pOam->timer == 8)
        {
            pOam->timer = 0;
            
            if (pOam->unk_4 < 5)
                pOam->unk_4++;
            else
                pOam->unk_4 = 0;
            
            pOam->pOam = sIntroHorizontalParticleOamPointers[pOam->unk_4];
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
    }
    
    if (pOam->xPosition >= SCREEN_SIZE_X || pOam->yPosition >= SCREEN_SIZE_Y)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 89090 | 28 | Scrolls background 3 by one pixel every 25 frames
 * 
 */
void NewFileIntroProcessBg3Scrolling(struct SpecialCutsceneOam *pOam) 
{
    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == 25)
    {
        pOam->animationDurationCounter = 0;
        gBg3XPosition--;
    }
}

 /**
 * @brief 890b8 | 104 | To document
 * 
 */
void NewFileIntroProcessSamusFainting(struct SpecialCutsceneOam* pOam)
{
    u8 rng1;
    u8 rng2;

    rng1 = sRandomNumberTable[MOD_AND(gFrameCounter16Bit, 32)] / 2;
    rng2 = sRandomNumberTable[MOD_AND(gFrameCounter16Bit + 7, 32)] / 2;

    if (!pOam->unk_8)
    {
        pOam->timer++;
        if (pOam->timer)
        {
            pOam->timer = 0;
            if (pOam->yPosition < 16)
            {
                pOam->yPosition += rng2;
                if (pOam->yPosition > 15)
                {
                    pOam->yPosition = 16;
                    pOam->unk_8 = 1;
                }
            }
        }
    }
    else
    {
        pOam->timer++;
        if (pOam->timer)
        {
            pOam->timer = 0;
            if (pOam->yPosition > 0)
            {
                pOam->yPosition -= rng2;
                if (pOam->yPosition <= 0)
                {
                    pOam->yPosition = 0;
                    pOam->unk_8 = 0;
                }
            }
        }
    }

    if (!pOam->unk_4)
    {
        pOam->unk_A++;
        if (pOam->unk_A)
        {
            pOam->unk_A = 0;
            if (pOam->xPosition < 16)
            {
                pOam->xPosition += rng1;
                if (pOam->xPosition > 15)
                {
                    pOam->xPosition = 16;
                    pOam->unk_4 = 1;
                }
            }
        }
    }
    else
    {
        pOam->unk_A++;
        if (pOam->unk_A)
        {
            pOam->unk_A = 0;
            if (pOam->xPosition > 0)
            {
                pOam->xPosition -= rng1;
                if (pOam->xPosition <= 0)
                {
                    pOam->xPosition = 0;
                    pOam->unk_4 = 0;
                }
            }
        }
    }

    gBg2XPosition = pOam->xPosition;
    gBg2YPosition = pOam->yPosition;
}

 /**
 * @brief 891bc | 74 | To document
 * 
 */
void NewFileIntroProcessSamusDrifting(struct SpecialCutsceneOam* pOam)
{
    pOam->unk_A++;
    
    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->xPosition = pOam->spawnX + (pOam->unk_A >> 1);
        pOam->yPosition = pOam->spawnY + (pOam->unk_A >> 2);

        pOam->timer++;
        if (pOam->timer == 2)
        {
            pOam->timer = 0;
            pOam->scaling++;
        }
    }

    if (pOam->xPosition > (SCREEN_SIZE_X + 40) || pOam->yPosition > (SCREEN_SIZE_Y + 20))
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 89230 | 258 | To document
 * 
 */
void NewFileIntroProcessSamusDriftingIntoAsteroids(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;

    pOam->unk_A++;
    
    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->rotation -= 4;
        pOam->scaling -= 8;
        pOam->stage = 2;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->yPosition = (SIN(pOam->timer) >> 7) + pOam->spawnY;
        
        if (pOam->timer > 52)
        {
            pOam->unk_4++;
            if (pOam->unk_4 == 12)
            {
                pOam->rotation--;
                pOam->xPosition--;
                pOam->unk_4 = 0;
            }
            
            pOam->unk_8++;
            if (pOam->unk_8 == 10)
            {
                pOam->unk_8 = 0;
                pOam->scaling--;
            }
        }

        if (pOam->timer > 127)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->timer++;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 2);
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 3) + (SIN(pOam->timer) >> 7);
        pOam->unk_4++;
        
        if (pOam->unk_4 == 12)
        {
            pOam->rotation--;
            pOam->unk_4 = 0;
        }
        
        pOam->unk_8++;
        if (pOam->unk_8 == 2)
        {
            pOam->unk_8 = 0;
            pOam->scaling--;
        }
        
        if (pOam->timer == 0)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        pOam->timer++;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 2);
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 3);
        pOam->unk_4++;
        
        if (pOam->unk_4 == 12)
        {
            pOam->rotation--;
            pOam->unk_4 = 0;
        }
        
        pOam->unk_8++;
        if (pOam->unk_8 == 1)
        {
            pOam->unk_8 = 0;
            pOam->scaling--;
        }
        
        if (pOam->timer == 0)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 4;
        }
        
        if (pOam->scaling < 3)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->timer++;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 1);
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 2);
        pOam->unk_4++;
        
        if (pOam->unk_4 == 12)
        {
            pOam->rotation--;
            pOam->unk_4 = 0;
        }
        
        pOam->unk_8++;
        if (pOam->unk_8 == 1)
        {
            pOam->unk_8 = 0;
            pOam->scaling--;
        }

        if (pOam->scaling < 3)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        pOam->unk_A = 0;
        pOam->scaling = Q_8_8(1);
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->affineMode = OAM_AFFINE_MODE_NORMAL;
        pOam->pOam = sOam_598000;
        pOam->stage = 6;
        INTRO_DATA.subStage = 6;
    }
    else if (pOam->stage == 6)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 89488 | 64 | Spawns the parts of the sideways BSL ship
 * 
 */
void NewFileIntroSpawnSidewaysBslShipParts(struct SpecialCutsceneOam *pOam) 
{
    if (pOam->stage == 0)
    {
        NewFileIntroSetupOam(32, pOam->xPosition + 122, pOam->yPosition, FALSE);
        NewFileIntroSetupOam(33, pOam->xPosition + 50, pOam->yPosition + 1, FALSE);
        NewFileIntroSetupOam(34, pOam->xPosition + 36, pOam->yPosition, FALSE);
        NewFileIntroSetupOam(35, pOam->xPosition, pOam->yPosition, FALSE);
        pOam->type = 0;
    }
}

 /**
 * @brief 894ec | c4 | To document
 * 
 */
void NewFileIntroProcessSidewaysBslShip(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->timer++;
        if (pOam->timer == 20)
        {
            pOam->spawnX++;
            pOam->timer = 0;

            if (pOam->unk_A == 4)
                pOam->unk_A = 0;

            if (pOam->unk_A < 2)
                pOam->yPosition++;
            else if (pOam->unk_A < 4)
                pOam->yPosition--;
                
            pOam->unk_A++;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->unk_A = 0;
        pOam->stage = 2;
    }
    else if (pOam->stage == 2)
    {
        pOam->timer++;
        if (pOam->timer == 2)
        {
            pOam->unk_A++;
            pOam->timer = 0;
        }

        pOam->xPosition = (((900 - pOam->spawnX) * pOam->unk_A) >> 12) + pOam->spawnX;
        pOam->yPosition = (((pOam->unk_4 - pOam->spawnY) * pOam->unk_A) >> 11) + pOam->spawnY;

        if (pOam->xPosition > 320)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 3;
        }
    }
}

 /**
 * @brief 895b0 | c4 | To document
 * 
 */
void NewFileIntroProcessDepthParticle(struct SpecialCutsceneOam* pOam)
{
    s32 x;
    s32 y;
    s32 divisor;
    
    pOam->unk_4 = pOam->unk_A;

    if (pOam->stage == 0)
    {
        pOam->spawnX = (pOam->xPosition - SCREEN_X_MIDDLE) * 100;
        pOam->spawnY = (pOam->yPosition - SCREEN_Y_MIDDLE) * 100;
        pOam->stage = 1;
    }
    else
    {
        if ((s16)pOam->unk_A < 100)
        {
            if ((s16)pOam->unk_A == 25)
                pOam->pOam = sIntroParticleOam_1;
            else if ((s16)pOam->unk_A == 50)
                pOam->pOam = sIntroParticleOam_2;
            else if ((s16)pOam->unk_A == 70)
                pOam->pOam = sIntroParticleOam_3;

            divisor = -pOam->unk_4 + 100;
            x = pOam->spawnX / divisor;
            pOam->xPosition = x + SCREEN_X_MIDDLE;
            y = pOam->spawnY / divisor + SCREEN_Y_MIDDLE;
            pOam->yPosition = y;

            if ((u16)(x + 128) > 256 || (s16)y > 168 || (s16)y < -8)
            {
                pOam->type = 0;
                pOam->exists = 0;
            }
        }
        else
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
    
    pOam->unk_A++;
}

 /**
 * @brief 89674 | 400 | To document
 * 
 */
u8 NewFileIntroSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder)
{
    s8 slot;

    if (!descendingSearchOrder)
    {
        for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }
        
        if (slot > 19)
            return 20;
    }
    else
    {
        for (slot = ARRAY_SIZE(INTRO_DATA.oam) - 1; slot >= 0; slot--)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }
        
        if (slot < 0)
            return 20;
    }
    
    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].exists = 1;

    if (type == 1)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslShip;
    }
    else if (type == 2)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].pOam = sIntroSamusShipFlyingOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessFlyingSamusShip;
    }
    else if (type == 3)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroParticleOam_0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessHorizontalParticle;
    }
    else if (type == 4)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBg3Scrolling;
    }
    else if (type == 10)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusFainting;
    }
    else if (type == 20)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].pOam = sIntroSamusShipFlyingOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusDrifting;
    }
    else if (type == 30)
    {
        INTRO_DATA.oam[slot].spawnX = xPosition;
        INTRO_DATA.oam[slot].spawnY = yPosition;
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_AFFINE;
        INTRO_DATA.oam[slot].pOam = sOam_597f88;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusDriftingIntoAsteroids;
    }
    else if (type == 31)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pOam = sOam_597f88;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSpawnSidewaysBslShipParts;
    }
    else if (type == 32)
    {
        INTRO_DATA.oam[slot].unk_4 = -40;
        INTRO_DATA.oam[slot].pOam = sIntroSidewaysBslShipOam_0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSidewaysBslShip;
    }
    else if (type == 33)
    {
        INTRO_DATA.oam[slot].unk_4 = -30;
        INTRO_DATA.oam[slot].pOam = sIntroSidewaysBslShipOam_1;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSidewaysBslShip;
    }
    else if (type == 34)
    {
        INTRO_DATA.oam[slot].unk_4 = -20;
        INTRO_DATA.oam[slot].pOam = sIntroSidewaysBslShipOam_2;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSidewaysBslShip;
    }
    else if (type == 35)
    {
        INTRO_DATA.oam[slot].unk_4 = -10;
        INTRO_DATA.oam[slot].pOam = sIntroSidewaysBslShipOam_3;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSidewaysBslShip;
    }
    else if (type == 36)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroParticleOam_0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessDepthParticle;
    }
    else if (type == 200)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }
    else if (type == 201)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessOam_Empty;
    }
    
    return slot;
}

 /**
 * @brief 89a74 | 3c | Spawns an OAM for the new file intro with an additional argument (unused)
 * 
 */
void NewFileIntroSetupOamWithArgument(u8 type, s16 xPos, s16 yPos, s16 arg3) 
{
    u8 slot;
    
    slot = NewFileIntroSetupOam(type, xPos, yPos, TRUE);
    INTRO_DATA.oam[slot].unk_8 = arg3;
}

 /**
 * @brief 89ab0 | 4 | To document
 * 
 */
void NewFileIntroProcessOam_Empty(void) 
{
    return;
}

 /**
 * @brief 89ab4 | 248 | To document
 * 
 */
void NewFileIntroSr388PreviewInit(void)
{
    u16 i;
    
    CallbackSetVBlank(SpecialCutsceneLoadingVblank);
    
    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
    
    LZ77UncompVram(sIntroSr388SpaceAndSurfaceObjGfx, VRAM_OBJ);
    
    DMA3_COPY_32(sIntroSr388SpaceAndSurfaceObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / sizeof(u32));
    
    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    for (i = 0; i < ARRAY_SIZE(sIntroSr388SurfaceBgGfxPointers); i++)
        LZ77UncompVram(sIntroSr388SurfaceBgGfxPointers[i], VRAM_BASE + i * 0x1000);

    LZ77UncompVram(sIntroSr388SurfaceTilemap, VRAM_BASE + 0xE800);

    for (i = 0; i < ARRAY_SIZE(sIntroSr388PlanetBgGfxPointers); i++)
        LZ77UncompVram(sIntroSr388PlanetBgGfxPointers[i], VRAM_BASE + 0x8000 + i * 0x1000);
    
    LZ77UncompVram(sIntroSr388SpaceBgTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSr388PlanetTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    
    DMA3_COPY_32(sSr388SpaceAndSurfacePal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 29, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(2, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(2, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 16;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;
    
    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    
    NewFileIntroSr388SetupOam(50, 250, 200);
    NewFileIntroSr388SetupOam(1, 0, 0);
    NewFileIntroSr388SetupOam(2, gBg2XPosition, 0);
    
    NewFileIntroSetupSr388PreviewAsteroid(3, 250, 100, -12);
    NewFileIntroSetupSr388PreviewAsteroid(4, 150, 10, -8);
    NewFileIntroSetupSr388PreviewAsteroid(5, 50, 60, -6);
    NewFileIntroSetupSr388PreviewAsteroid(6, 190, 130, -20);
    NewFileIntroSetupSr388PreviewAsteroid(5, 280, 30, -10);
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    
    INTRO_DATA.pText = sCutsceneTextNone;
    
    PlayMusic(MUSIC_SECTOR_1, 13);
    
    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);
    
    CallbackSetVBlank(NewFileIntroSr388PreviewVblank);
}

 /**
 * @brief 89cfc | 348 | To document
 * 
 */
boolu32 NewFileIntroSr388PreviewProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    INTRO_DATA.timer++;
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer == 1)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
            }
            else if (INTRO_DATA.timer == 50)
            {
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][8];
            }
            else if (INTRO_DATA.timer == 58)
            {
                gWrittenToBldalpha_Eva = 0;
                gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
            }
            else if (INTRO_DATA.timer == 59)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL);
            }
            else if (INTRO_DATA.timer == 60)
            {
                INTRO_DATA.timer = 0;
                NewFileIntroSr388SetupOam(9, gBg2XPosition + 92, 64);
                INTRO_DATA.subStage = 1;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (INTRO_DATA.timer == 2)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
                    gWrittenToBldalpha_Eva++;
            }

            if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.textAdvanceState == 0)
                INTRO_DATA.textAdvanceState = 1;

            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == 2)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Eva == 0)
                {
                    SpecialCutsceneDestroyOamOfType(9);
                    INTRO_DATA.subStage = 3;
                }
                else
                {
                    gWrittenToBldalpha_Eva--;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 3:
            if (INTRO_DATA.timer == 1)
            {
                gWrittenToBldalpha_Eva = 0;
                gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
            }
            else if (INTRO_DATA.timer == 2)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_SECOND_TARGET_PIXEL 
                         | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BACKDROP_SECOND_TARGET_PIXEL);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 4:
            if (gWrittenToBldalpha_Eva == BLDALPHA_MAX_VALUE)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~(DCNT_BG2 | DCNT_BG3));
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.subStage = 5;
                NewFileIntroSr388SetupOam(10, 128, 210);
            }
            else if (gWrittenToBldalpha_Eva == 2)
            {
                NewFileIntroSr388SetupOam(7, 0, 0);
            }

            if (INTRO_DATA.timer == 7)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
                {
                    gWrittenToBldalpha_Eva++;
                    gWrittenToBldalpha_Evb--;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 5:
            if (INTRO_DATA.timer == 70)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 6;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 6:
            INTRO_DATA.unk_213++;
            if (INTRO_DATA.unk_213 == 4)
            {
                INTRO_DATA.unk_213 = 0;

                if (gWrittenToBldy < BLDY_MAX_VALUE)
                {
                    gWrittenToBldy++;
                }
                else
                {
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.subStage = 0;
                    finished = TRUE;
                }
            }

            if (gWrittenToBldy >= BLDY_MAX_VALUE)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
    
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 8A044 | ac | To document
 * 
 */
boolu32 NewFileIntroSr388Preview(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSr388PreviewInit();
            INTRO_DATA.stage = 1;
            break;

        case 1:
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();

            INTRO_DATA.timer++;

            if (gWrittenToBldy)
            {
                if (INTRO_DATA.timer > 1)
                {
                    INTRO_DATA.timer = 0;
                    gWrittenToBldy--;
                }
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.stage = 2;
            }
            break;

        case 2:
            if (NewFileIntroSr388PreviewProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 8a0f0 | 40 | Sets the background 3 X position in the SR388 preview cutscene
 * 
 */
void NewFileIntroProcessSr388PreviewBg3(struct SpecialCutsceneOam* pOam)
{
    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == 36)
        pOam->animationDurationCounter = 0;

    gBg3XPosition = pOam->xPosition;

    if (INTRO_DATA.subStage == 5)
    {
        gBg3XPosition = 0;
        pOam->type = 0;
    }
}

 /**
 * @brief 8a130 | 40 | Sets the background 2 X position in the SR388 preview cutscene
 * 
 */
void NewFileIntroProcessSr388PreviewBg2(struct SpecialCutsceneOam* pOam)
{
    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == 29)
        pOam->animationDurationCounter = 0;

    gBg2XPosition = pOam->xPosition;

    if (INTRO_DATA.subStage == 5)
    {
        gBg2XPosition = 0;
        pOam->type = 0;
    }
}

 /**
 * @brief 8a170 | 6c | To document
 * 
 */
void NewFileIntroProcessSr388PreviewAsteroid(struct SpecialCutsceneOam *pOam)
{
    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_A++;
        pOam->xPosition = ((pOam->unk_8 * pOam->unk_A) >> 6) + pOam->spawnX;
        
        if (pOam->xPosition < -40)
        {
            pOam->spawnX = 280;
            pOam->unk_A = 0;
        }
    }
    
    if (INTRO_DATA.subStage == 5)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 8a1dc | 28 | Scrolls background 1 in the SR388 preview cutscene
 * 
 */
void NewFileIntroProcessSr388PreviewBg1Scrolling(struct SpecialCutsceneOam* pOam)
{
    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == 3)
    {
        pOam->animationDurationCounter = 0;
        pOam->unk_4++;
        gBg1YPosition = pOam->unk_4;
    }
}

 /**
 * @brief 8a204 | 64 | Spawns the sun reflection after a delay in the SR388 preview cutscene
 * 
 */
void NewFileIntroProcessSr388PreviewSpawnSunReflection(struct SpecialCutsceneOam *pOam)
{
    pOam->unk_A++;
    
    pOam->timer++;
    if (pOam->timer == 21)
        pOam->timer = 0;
    
    if (pOam->unk_A == 110)
        NewFileIntroSr388SetupOam(9, pOam->xPosition + 24, pOam->yPosition);
    else if (pOam->unk_A > 1000)
        pOam->unk_A = 1000;
    
    if (INTRO_DATA.subStage == 5)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 8a268 | 38 | To document
 * 
 */
void NewFileIntroProcessSunReflection(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == 29)
        pOam->timer = 0;

    if (INTRO_DATA.subStage == 5)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 8a2a0 | 30 | To document
 * 
 */
void NewFileIntroProcessSr388Rocks(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == 1)
    {
        pOam->timer = 0;
        pOam->yPosition--;
    }

    if (pOam->yPosition <= 160)
        pOam->pOam = sOam_59a0f0;
}

 /**
 * @brief 8a2d0 | 29c | To document
 * 
 */
u8 NewFileIntroSr388SetupOam(u8 type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot > 19)
        return 20;
    
    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].exists = 1;
    
    if (type == 1)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewBg3;
    }
    else if (type == 2)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewBg2;
    }
    else if (type == 3)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSr388PreviewAsteroidOam_0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewAsteroid;
    }
    else if (type == 4)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSr388PreviewAsteroidOam_1;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewAsteroid;
    }
    else if (type == 5)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSr388PreviewAsteroidOam_2;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewAsteroid;
    }
    else if (type == 6)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSr388PreviewAsteroidOam_3;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewAsteroid;
    }
    else if (type == 7)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewBg1Scrolling;
    }
    else if (type == 8)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sOam_59a100;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewSpawnSunReflection;
    }
    else if (type == 9)
    {
        INTRO_DATA.oam[slot].objMode = 1;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSr388PreviewSunReflectionOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSunReflection;
    }
    else if (type == 10)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroSr388PreviewRocksOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388Rocks;
    }
    else if (type == 50)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }
    
    return slot;
}

 /**
 * @brief 8a56c | 38 | To document
 * 
 */
void NewFileIntroSetupSr388PreviewAsteroid(u8 type, s16 xPosition, s16 yPosition, s16 arg3)
{
    u8 slot;
    
    slot = NewFileIntroSr388SetupOam(type, xPosition, yPosition);
    INTRO_DATA.oam[slot].unk_8 = arg3;
}

 /**
 * @brief 8a5a4 | 94 | V-blank for the SR388 preview cutscene
 * 
 */
void NewFileIntroSr388PreviewVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    WRITE_16(REG_BLDY, gWrittenToBldy);

    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

 /**
 * @brief 8a638 | 254 | Setup for the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroInSr388Init(void)
{
    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sIntroHornoadEncounterObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroHornoadEncounterObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroHornoadEncounterBgGfx, VRAM_BASE);
    LZ77UncompVram(sTilemap_5a86c8, VRAM_BASE + 0xE800);
    LZ77UncompVram(sTilemap_5a83b8, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    LZ77UncompVram(sTilemap_5a9044, VRAM_BASE + 0xC000);

    DMA3_COPY_32(sPal_5a8e44, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 24, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_512x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 29, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_512x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    
    gBg2XPosition = 136;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg1XPosition = gBg3XPosition + 392;
    gBg1YPosition = gBg2YPosition - 96;

    gUnusedBgXPosition = 560;
    gUnusedBgYPosition = -40;

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);

    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_NEXT_PAGE_ARROW, 250, 200);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_PLACEHOLDER, 0, 0);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_PLACEHOLDER, 0, 0);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_SAMUS, 234, 200);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_LEFT_RESEARCHER, 288, 200);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_RIGHT_RESEARCHER, 312, 100);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_BG_SCROLLING, 0, 0);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_CAVE_ENTRANCE_BG, 304 - gBg2XPosition, 200);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));
    
    INTRO_DATA.pText = sCutsceneTextNone;
    
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroInSr388Vblank);
}

 /**
 * @brief 8a88c | 344 | Processes the 'hornoad encounter in SR388' cutscene
 * 
 */
boolu32 NewFileIntroInSr388Process(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.textAdvanceState == 0)
        INTRO_DATA.textAdvanceState = 1;
    
    INTRO_DATA.timer++;
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            INTRO_DATA.unk_213++;
            if (INTRO_DATA.unk_213 == 4)
            {
                INTRO_DATA.unk_213 = 0;
            
                if (gWrittenToBldy)
                    gWrittenToBldy--;
            }
        
            if (INTRO_DATA.timer == 2)
            {
                INTRO_DATA.timer = 0;
                
                gBg2YPosition++;
                if (gBg2YPosition == 96)
                    INTRO_DATA.subStage = 2;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
        
            gBg2XPosition += INTRO_DATA.bg2XVelocity;
            break;
        
        case 1:
        case 2:
            INTRO_DATA.timer = 0;
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
        
            gBg2XPosition += INTRO_DATA.bg2XVelocity;
            break;
        
        case 3:
            if (INTRO_DATA.timer == 1)
                DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
        
            gBg2XPosition += INTRO_DATA.bg2XVelocity;
            break;
        
        case 4:
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            
            gBg2XPosition += INTRO_DATA.bg2XVelocity;
            INTRO_DATA.timer = 0;
            break;
        
        case 5:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.paletteUpdate1 = 1;
            }
            else if (INTRO_DATA.timer == 30)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][9];
                INTRO_DATA.subStage = 6;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 6:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 9;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 7:
            if (INTRO_DATA.timer == 10)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            }
            else if (INTRO_DATA.timer == 11)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.textTimer = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][10];
                INTRO_DATA.subStage = 8;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 8:
            INTRO_DATA.timer = 0;
        
            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 9;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 9:
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
        
            gBg2XPosition += INTRO_DATA.bg2XVelocity;
        
            if (INTRO_DATA.timer > 50)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                finished = TRUE;
            }
            break;
    }
    
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 8abd0 | 98 | Main handler for the 'hornoad encounter in SR388' cutscene
 * 
 */
boolu32 NewFileIntroInSr388(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroInSr388Init();
            
            INTRO_DATA.stage = 2;
            break;
        
        case 1:
            SpecialCutsceneFadeIn();

            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroInSr388Process())
            {
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
                gWrittenToBldy = 0;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                INTRO_DATA.subStage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 8ac68 | 5d8 | Processes Samus in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessSamusInSr388(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->timer++;
    
    if (INTRO_DATA.subStage == 0)
    {
        if (gBg2YPosition > 47)
        {
            pOam->yPosition = 240 - gBg2YPosition;
            pOam->xPosition--;
        }
        
        pOam->timer = 0;
    }
    else if (INTRO_DATA.subStage == 1)
    {
        pOam->yPosition = 240 - gBg2YPosition;
        
        if (pOam->stage == 0)
        {
            if (pOam->timer < 20)
            {
                pOam->xPosition--;
            }
            else if (pOam->timer < 70)
            {
                INTRO_DATA.bg2XVelocity = -1;
            }
            else if (pOam->timer == 70)
            {
                INTRO_DATA.bg2XVelocity = 0;
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                pOam->stage = 1;
            }
        }
        else if (pOam->stage == 1)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_TurningRight;
                pOam->stage = 2;
            }
        }
        else if (pOam->stage == 2)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleRight;
                pOam->stage = 3;
                INTRO_DATA.textTimer = 0;
            }
        }
        else if (pOam->stage == 3)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_TurningLeft;
                pOam->stage = 4;
            }
        }
        else if (pOam->stage == 4)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                pOam->stage = 5;
            }
        }
        else if (pOam->stage == 5)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 0;
                INTRO_DATA.subStage = 2;
            }
        }
    }
    else if (INTRO_DATA.subStage == 2)
    {
        pOam->stage = 3;
        INTRO_DATA.subStage = 3;
    }
    else if (INTRO_DATA.subStage == 3)
    {
        if (pOam->stage == 0)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_WalkingRight;
                pOam->stage = 1;
                pOam->xPosition++;
            }
        }
        else if (pOam->stage == 1)
        {
            if (pOam->xPosition < 260)
            {
                pOam->xPosition++;
            }
            else
            {
                pOam->xPosition = 260;
                pOam->timer = 0;
                pOam->stage = 2;
            }
        }
        else if (pOam->stage == 2)
        {
            if (pOam->timer == 1)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_WalkingLeft;
                pOam->stage = 3;
            }
        }
        else if (pOam->stage == 3)
        {
            if (pOam->xPosition > 140)
            {
                pOam->xPosition--;
            }
            else if (gBg2XPosition > 108)
            {
                INTRO_DATA.bg2XVelocity = -1;
            }
            else
            {
                INTRO_DATA.bg2XVelocity = 0;
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                pOam->stage = 4;
            }
        }
        else if (pOam->stage == 4)
        {
            if (pOam->timer == 60)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 5;
            }
        }
        else if (pOam->stage == 5)
        {
            pOam->pOam = sIntroInSr388SamusOam_WalkingLeft;
            
            if (gBg2XPosition > 40)
            {
                INTRO_DATA.bg2XVelocity = -1;
                
                if (gBg2XPosition == 56)
                    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_HORNOAD, 0, 128);
            }
            else
            {
                INTRO_DATA.bg2XVelocity = 0;
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                pOam->stage = 6;
            }
        }
        else if (pOam->stage == 6)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_TurningRight;
                pOam->stage = 7;
            }
        }
        else if (pOam->stage == 7)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleRight;
                pOam->stage = 8;
            }
        }
        else if (pOam->stage == 8)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_TurningLeft;
                pOam->stage = 9;
            }
        }
        else if (pOam->stage == 9)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                pOam->stage = 10;
            }
        }
        else if (pOam->stage == 10)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_WalkingLeft;
                pOam->stage = 11;
            }
        }
        else if (pOam->stage == 11)
        {
            pOam->pOam = sIntroInSr388SamusOam_WalkingLeft;
            
            if (pOam->timer == 1)
            {
                if (gBg2XPosition != 0)
                {
                    INTRO_DATA.bg2XVelocity = -1;
                }
                else
                {
                    INTRO_DATA.bg2XVelocity = 0;
                    pOam->timer = 0;
                    pOam->animationDurationCounter = 0;
                    pOam->currentAnimationFrame = 0;
                    pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                    INTRO_DATA.subStage = 4;
                    pOam->stage = 0;
                }
            }
            else
            {
                pOam->timer = 0;
                INTRO_DATA.bg2XVelocity = 0;
            }
        }
    }
    else if (INTRO_DATA.subStage == 4)
    {
        if (pOam->stage == 0)
        {
            if (pOam->timer == 60)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedLeft;
                pOam->stage = 1;
            }
        }
        else if (pOam->stage == 1)
        {
            if (pOam->timer == 60)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_FiringMissileLeft;
                
                NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_HORIZONTAL_MISSILE, pOam->xPosition - 20, pOam->yPosition - 22);
                
                pOam->stage = 2;
            }
        }
        else if (pOam->stage == 2)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedLeft;
                pOam->stage = 3;
            }
        }
        else if (pOam->stage == 3)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_HORIZONTAL_MISSILE, &x, &y);
            
            if (x == 300)
            {
                pOam->timer = 0;
                pOam->stage = 4;
            }
        }
        else if (pOam->stage == 4)
        {
            if (pOam->timer == 8)
            {
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedUpLeft;
                return;
            }
            else if (pOam->timer == 10)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_FiringMissileUpLeft;
                
                NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_FIRST_DIAGONAL_MISSILE, pOam->xPosition - 20, pOam->yPosition - 40);
                
                pOam->stage = 5;
            }
        }
        else if (pOam->stage == 5)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedUpLeft;
                pOam->stage = 6;
            }
        }
        else if (pOam->stage == 6)
        {
            if (pOam->timer == 130)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_FiringMissileUpLeft;
                
                NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_SECOND_DIAGONAL_MISSILE, pOam->xPosition - 20, pOam->yPosition - 40);
                
                pOam->stage = 7;
            }
        }
        else if (pOam->stage == 7)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedUpLeft;
                pOam->stage = 8;
            }   
        }
        else if (pOam->stage == 8)
        {
            if (pOam->timer == 78)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_FiringMissileUpLeft;
                
                NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_SECOND_DIAGONAL_MISSILE, pOam->xPosition - 20, pOam->yPosition - 40);
                
                pOam->stage = 9;
            }
        }
        else if (pOam->stage == 9)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedUpLeft;
                pOam->stage = 10;
            }
        }
    }
    else if (INTRO_DATA.subStage > 4)
    {
        pOam->animationDurationCounter = 0;
    }
}

 /**
 * @brief 8b240 | 20c | Processes the left BSL guy in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewfileIntroProcessLeftBiologicalResearcher(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->timer++;
    
    if (INTRO_DATA.subStage == 0)
    {
        if (gBg2YPosition > 47)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            pOam->xPosition = x + pOam->unk_8;
            pOam->yPosition = y;
        }
        
        pOam->timer = 0;
        pOam->stage = 20;
    }
    else if (INTRO_DATA.subStage == 1 || INTRO_DATA.subStage == 2)
    {
        NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
        
        pOam->xPosition = x + pOam->unk_8;
        pOam->yPosition = y;
        pOam->stage = 20;
    }
    else if (INTRO_DATA.subStage == 3)
    {
        if (pOam->stage == 16)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition < x)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 17;
            }
        }
        else if (pOam->stage == 17)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition > x + 10)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Turning;
                pOam->stage = 18;
            }
        }
        else if (pOam->stage == 18)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 19;
            }
        }
        else if (pOam->stage == 19)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition > x + pOam->unk_8)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Walking;
                pOam->stage = 20;
            }
        }
        else if (pOam->stage == 20)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition <= x + pOam->unk_8 - 7)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 21;
            }
            else
            {
                pOam->xPosition--;
            }
        }
        else if (pOam->stage == 21)
        {
            if (gBg2XPosition < 98)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Walking;
                pOam->stage = 22;
            }
        }
        else if (pOam->stage == 22)
        {
            if (gBg2XPosition > 45)
            {
                pOam->xPosition--;
            }
            else
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 23;
            }
        }
    }
    else if (INTRO_DATA.subStage == 4)
    {
        pOam->timer = 0;
    }
    else if (INTRO_DATA.subStage > 4)
    {
        pOam->animationDurationCounter = 0;
    }
    
    pOam->xPosition -= INTRO_DATA.bg2XVelocity;
}

 /**
 * @brief 8b44c | 214 | Processes the right BSL guy in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewfileIntroProcessRightBiologicalResearcher(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->timer++;
    
    if (INTRO_DATA.subStage == 0)
    {
        if (gBg2YPosition > 47)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            pOam->xPosition = x + pOam->unk_8;
            pOam->yPosition = y;
        }
        
        pOam->timer = 0;
        pOam->stage = 20;
    }
    else if (INTRO_DATA.subStage == 1 || INTRO_DATA.subStage == 2)
    {
        NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
        
        pOam->xPosition = x + pOam->unk_8;
        pOam->yPosition = y;
        pOam->stage = 20;
    }
    else if (INTRO_DATA.subStage == 3)
    {
        if (pOam->stage == 16)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition < x)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 17;
            }
        }
        else if (pOam->stage == 17)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition > x + 10)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Turning;
                pOam->stage = 18;
            }
        }
        else if (pOam->stage == 18)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 19;
            }
        }
        else if (pOam->stage == 19)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition > x + pOam->unk_8 + 10)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Walking;
                pOam->stage = 20;
            }
        }
        else if (pOam->stage == 20)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition <= x + pOam->unk_8 - 10)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 21;
            }
            else
            {
                pOam->xPosition--;
            }
        }
        else if (pOam->stage == 21)
        {
            if (gBg2XPosition < 103)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Walking;
                pOam->stage = 22;
            }
        }
        else if (pOam->stage == 22)
        {
            if (gBg2XPosition > 52)
            {
                pOam->xPosition--;
            }
            else
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 23;
            }
        }
    }
    else if (INTRO_DATA.subStage == 4)
    {
        pOam->timer = 0;
    }
    else if (INTRO_DATA.subStage > 4)
    {
        pOam->animationDurationCounter = 0;
    }
    
    pOam->xPosition -= INTRO_DATA.bg2XVelocity;
}

 /**
 * @brief 8b660 | 174 | Processes the hornoad in the SR388 cutscene (unused?)
 * 
 */
void NewFileIntroProcessUnusedHornoad(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    u32 timer;
    u8 tmp;
    s16 y;
    
    pOam->timer++;

    if (pOam->stage == 0)
    {
        pOam->spawnY = pOam-> yPosition;
        pOam->unk_4 = 0;
        pOam->pOam = sIntroInSr388HornoadOam_IdleUnused;

        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->pOam = sIntroInSr388HornoadOam_JumpingUnused;

        if (pOam->unk_8 == 0)
        {
            timer = pOam->timer;
            y = sHornoadJumpVelocityHigh[pOam->unk_4] * timer >> 2;
        }
        else
        {
            timer = pOam->timer;
            tmp = timer; // From permuter
            y = sHornoadJumpVelocityLow[pOam->unk_4] * tmp >> 2;
        }
        
        pOam->yPosition = pOam->spawnY + y;
        if (pOam->yPosition > 144)
        {
            pOam->yPosition = 144;
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_BouncingUnused;
            pOam->stage = 2;
        }

        if (y < 0)
            pOam->xPosition += 2;
        else
            pOam->xPosition += 1;

        if (pOam->animationDurationCounter == 4 && pOam->currentAnimationFrame == 2)
            pOam->xPosition += 8;

        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            pOam->spawnY = pOam->yPosition;
            pOam->unk_4++;

            if (pOam->unk_4 == 10)
                pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            pOam->animationDurationCounter = 0;

        if (pOam->timer == sArray_59db00[pOam->unk_A])
        {
            pOam->unk_A++;
            if (pOam->unk_A == 6)
                pOam->unk_A = 0;

            if (!pOam->unk_8)
                pOam->unk_8 = 1;
            else
                pOam->unk_8 = 0;

            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 0;
        }
    }

    pOam->xPosition -= INTRO_DATA.bg2XVelocity;
    if (pOam->xPosition > 260)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 8b7d4 | 4c8 | Processes the hornoad in the SR388 cutscene
 * 
 */
void NewFileIntroProcessHornoad(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;
    s16 var0;
    s16 var1;
    s32 var2;
    s32 spawnY;
    s32 xPos;
    s16 x;
    s16 y;

    pOam->timer++;

    if (pOam->stage == 0)
    {
        pOam->spawnY = pOam->yPosition;

        if (pOam->timer == 150)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Chomping;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->spawnY = pOam->yPosition;

        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Chomping;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_HORIZONTAL_MISSILE, &x, &y);

        pOam->spawnY = pOam->yPosition;

        if (x - pOam->xPosition < 25)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Biting;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        pOam->pOam = sIntroInSr388HornoadOam_Jumping;

        var0 = pOam->timer * sHornoadJumpVelocityHigh[pOam->unk_4] >> 2;
        var2 = var0 + (u16)pOam->spawnY;
        pOam->yPosition = var2;

        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            pOam->spawnY = var2;

            pOam->unk_4++;
            if (pOam->unk_4 == 5)
            {
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388HornoadOam_MidAir;
            }
            else if (pOam->unk_4 > 10)
            {
                pOam->unk_4 = 10;
            }
        }

        if (pOam->yPosition > 128)
        {
            pOam->spawnY = 128;
            pOam->yPosition = 128;
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Bouncing;
            pOam->unk_4 = 0;
            pOam->stage = 4;
        }
    }
    else if (pOam->stage == 4)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Panting;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_HORIZONTAL_MISSILE, &x, &y);

        if (x == 300)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Biting;
            pOam->stage = 6;
        }
    }
    else if (pOam->stage == 6)
    {
        pOam->pOam = sIntroInSr388HornoadOam_Jumping;

        var0 = pOam->timer * sHornoadJumpVelocityHigh[pOam->unk_4] >> 1;
        FAKE_MATCH_BLOCK(FAKE_MATCH_NOP_ADD(pOam->spawnY));
        spawnY = (u16)pOam->spawnY;
        var2 = var0;
        pOam->yPosition = var2 + spawnY;
        pOam->xPosition++;

        if (pOam->currentAnimationFrame == 2 && pOam->animationDurationCounter == 4)
        {
            xPos = (u16)pOam->xPosition;
            xPos += 8;
            pOam->xPosition = xPos;
        }
        else
        {
            FAKE_MATCH_NOP_ADD(var0);
        }

        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            pOam->spawnY = pOam->yPosition;

            pOam->unk_4++;
            if (pOam->unk_4 == 5)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388HornoadOam_MidAir;
            }
            else if (pOam->unk_4 > 10)
            {
                pOam->unk_4 = 10;
            }
        }

        if (pOam->unk_4 > 1)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_FIRST_DIAGONAL_MISSILE, &x, &y);

            if (pOam->xPosition >= x && pOam->yPosition >= y)
            {
                NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_MISSILE_EXPLOSION_BIG, pOam->xPosition, pOam->yPosition);

                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388HornoadOam_Shaking;
                pOam->unk_4 = 1;
                WRITE_16(REG_MOSAIC, sXParasiteMosaicValues[1] * 16);
                pOam->mosaic = 1;
                pOam->stage = 7;
            }
        }
    }
    else if (pOam->stage == 7)
    {
        if (pOam->timer == 2)
        {
            pOam->timer = 0;
            pOam->unk_4++;
            WRITE_16(REG_MOSAIC, sXParasiteMosaicValues[pOam->unk_4] * 16);
        }

        if (pOam->unk_A == 1)
        {
            if (pOam->unk_4 == 15)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388XParasiteOam_Floating;
                pOam->xPosition -= 4;
                pOam->yPosition -= 10;
                pOam->unk_A = 0;
                pOam->stage = 8;
            }
        }
        else
        {
            if (pOam->unk_4 == 29)
            {
                pOam->unk_A++;
                pOam->unk_4 = 1;
            }
        }
    }
    else if (pOam->stage == 8)
    {
        if (pOam->timer == 2)
        {
            pOam->timer = 0;
            pOam->unk_4++;
            WRITE_16(REG_MOSAIC, sXParasiteMosaicValues[pOam->unk_4] * 16);
        }

        if (pOam->unk_A == 1)
        {
            if (pOam->unk_4 == 29)
            {
                pOam->timer = 0;
                pOam->mosaic = 0;

                NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);

                pOam->spawnY = pOam->yPosition;
                pOam->spawnX = x;
                pOam->unk_4 = x - pOam->xPosition;
                pOam->unk_A = 63;
                pOam->stage = 9;
            }
        }
        else
        {
            if (pOam->unk_4 == 29)
            {
                pOam->unk_A++;
                pOam->unk_4 = 1;
            }
        }
    }
    else if (pOam->stage == 9)
    {
        if (pOam->timer != 10)
        {
            if (pOam->timer > 30)
            {
                pOam->timer = 0;
                pOam->stage = 10;
            }
        }
    }
    else if (pOam->stage == 10)
    {
        pOam->unk_A++;
        if (pOam->unk_A > 255)
            pOam->unk_A -= 256;

        var0 = pOam->unk_A;
        var1 = pOam->unk_A * 2;
        if (var1 > 255)
            var1 -= 256;

        pOam->xPosition = pOam->spawnX + ((pOam->unk_4 * COS(var1) * SIN(var0)) >> 16);
        pOam->yPosition = pOam->spawnY + ((pOam->unk_4 * COS(var1) * COS(var0)) >> 16);

        if (pOam->unk_A > 159)
        {
            pOam->unk_A = 0;
            pOam->timer = 0;
            pOam->unk_4 = 0;
            pOam->spawnY = 0;
            pOam->spawnX = 0;
            pOam->stage = 11;
        }
        else if (pOam->unk_A > 155)
        {
            pOam->spawnX--;
            pOam->spawnY++;
        }
        else if (pOam->unk_A > 119)
        {
            pOam->spawnY++;
        }
    }
    else if (pOam->stage == 11)
    {
        pOam->affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;

        pOam->scaling += Q_8_8(0.5f);
        if (pOam->scaling >= Q_8_8(2))
            pOam->stage = 12;
    }
    else if (pOam->stage == 12)
    {
        pOam->scaling -= Q_8_8(1.f / 16);
        if (pOam->scaling <= Q_8_8(0.56f))
        {
            INTRO_DATA.subStage = 5;
            pOam->stage = 13;
        }
    }
    else if (pOam->stage == 13)
    {
        pOam->animationDurationCounter = 0;
    }

    pOam->xPosition -= INTRO_DATA.bg2XVelocity;
}

 /**
 * @brief 8bc9c | b4 | Processes the horizontal missile in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessHorizontalMissile(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;

    pOam->timer++;
    
    if (pOam->stage == 0)
    {
        pOam->xPosition = pOam->spawnX - (pOam->timer * sNormalMissileVelocity[pOam->unk_4] >> 2);
        
        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            
            if (pOam->unk_4 < 6)
                pOam->unk_4++;
            
            pOam->spawnX = pOam->xPosition;
        }
        else if (pOam->timer == 1)
        {
            NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_MISSILE_TRAIL, pOam->xPosition + 12, pOam->yPosition + 2);
        }
        
        if (pOam->xPosition < 32)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388MissileExplosionOam_Small;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 8bd50 | c8 | Processes the first diagonal missile in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessFirstDiagonalMissile(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->timer++;
    
    if (pOam->stage == 0)
    {
        pOam->xPosition = pOam->spawnX - (pOam->timer * (sNormalMissileVelocity[pOam->unk_4] + 1) >> 2);
        pOam->yPosition = pOam->spawnY - (pOam->timer * (sNormalMissileVelocity[pOam->unk_4] + 1) >> 2);
        
        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            
            if (pOam->unk_4 < 6)
                pOam->unk_4++;
            
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
        }
        else if (pOam->timer == 1)
        {
            NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_MISSILE_TRAIL, pOam->xPosition + 10, pOam->yPosition + 12);
        }

        NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_HORNOAD, &x, &y);

        if (pOam->xPosition <= x - 2 && pOam->yPosition <= y - 2)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 8be18 | 2c | Destroys an OAM of the 'hornoad encounter in SR388' cutscene once its animation ended
 * 
 */
void NewFileIntroInSr388DestroyOamWhenAnimEnded(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    
    frame = &pOam->pOam[pOam->currentAnimationFrame];
    if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 8be44 | d8 | Scrolls backgrounds 1 and 3 along with background 2 in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessInSr388BgScrolling(struct SpecialCutsceneOam *pOam)
{
    if (pOam->stage == 0)
    {
        pOam->yPosition = gBg2YPosition;
        pOam->xPosition = gBg2XPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        if (pOam->yPosition + 1 < gBg2YPosition)
        {
            pOam->yPosition = gBg2YPosition;
            gBg3YPosition++;
        }
        
        if (pOam->xPosition - 1 > gBg2XPosition)
        {
            pOam->xPosition = gBg2XPosition;
            gBg3XPosition--;
        }
    }
    
    if (pOam->unk_4 == 0)
    {
        gBg1XPosition = gBg2XPosition + 256;
        gBg1YPosition = gBg2YPosition - 96;
        
        if (gBg1XPosition < 120)
        {
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG1);
            WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
            
            gWrittenToBldalpha_Eva = gWrittenToBldalpha_Evb = 0;
            pOam->unk_4 = 1;
        }
    }
    
    if (gBg2XPosition == 0)
        pOam->type = 0;
}

 /**
 * @brief 8bf1c | 4c | Processes the cave entrance background OAM in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessCaveEntranceBg(struct SpecialCutsceneOam* pOam)
{
    if (gBg2YPosition > 23)
        pOam->yPosition = 216 - gBg2YPosition;

    pOam->xPosition -= INTRO_DATA.bg2XVelocity;
    if (pOam->xPosition > 302)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 8bf68 | 48 | Processes the black rectangle OAM in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessBlackRectangle(struct SpecialCutsceneOam* pOam)
{
    if (gBg2YPosition > 23)
        pOam->yPosition = 216 - gBg2YPosition;

    pOam->xPosition -= INTRO_DATA.bg2XVelocity;
    if (pOam->xPosition > 250)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 8bfb0 | d4 | Processes the second and subsequent diagonal missiles in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessSecondDiagonalMissile(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;

    pOam->timer++;
    
    if (pOam->stage == 0)
    {
        pOam->xPosition = pOam->spawnX - (pOam->timer * (sNormalMissileVelocity[pOam->unk_4] + 1) >> 2);
        pOam->yPosition = pOam->spawnY - (pOam->timer * (sNormalMissileVelocity[pOam->unk_4] + 1) >> 2);
        
        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            
            if (pOam->unk_4 < 6)
                pOam->unk_4++;
            
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
        }
        else if (pOam->timer == 1)
        {
            NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_MISSILE_TRAIL, pOam->xPosition + 10, pOam->yPosition + 12);
        }
        
        if (pOam->yPosition < 50)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388MissileExplosionOam_Small;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 8c084 | 8 | Destroys a placeholder OAM of the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroInSr388DestroyOam(struct SpecialCutsceneOam* pOam)
{
    pOam->type = 0;
}

 /**
 * @brief 8c08c | 478 | Spawns an object for the 'hornoad encounter in SR388' cutscene
 * 
 */
u8 NewFileIntroInSr388SetupOam(IntroInSr388OamType type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot > 19)
        return 20;
    
    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].exists = 1;

    if (type == INTRO_IN_SR388_OAM_TYPE_SAMUS)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388SamusOam_WalkingLeft;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusInSr388;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_LEFT_RESEARCHER)
    {
        INTRO_DATA.oam[slot].unk_8 = 38;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388BslResearcherOam_Walking;
        INTRO_DATA.oam[slot].pFunction = NewfileIntroProcessLeftBiologicalResearcher;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_RIGHT_RESEARCHER)
    {
        INTRO_DATA.oam[slot].unk_8 = 72;
        INTRO_DATA.oam[slot].currentAnimationFrame = 1;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388BslResearcherOam_Walking;
        INTRO_DATA.oam[slot].pFunction = NewfileIntroProcessRightBiologicalResearcher;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_HORNOAD_UNUSED)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388HornoadOam_IdleUnused;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessUnusedHornoad;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_HORNOAD_UNUSED_2)
    {
        INTRO_DATA.oam[slot].unk_8 = 1;
        INTRO_DATA.oam[slot].unk_A = 2;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388HornoadOam_IdleUnused;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessUnusedHornoad;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_HORIZONTAL_MISSILE)
    {
        INTRO_DATA.oam[slot].spawnX = xPosition;
        INTRO_DATA.oam[slot].spawnY = yPosition;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388MissileOam_Horizontal;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessHorizontalMissile;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_FIRST_DIAGONAL_MISSILE)
    {
        INTRO_DATA.oam[slot].spawnX = xPosition;
        INTRO_DATA.oam[slot].spawnY = yPosition;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388MissileOam_Diagonal;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessFirstDiagonalMissile;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_MISSILE_TRAIL)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388MissileTrailOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroInSr388DestroyOamWhenAnimEnded;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_HORNOAD)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388HornoadOam_Panting;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessHornoad;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_MISSILE_EXPLOSION_BIG)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388MissileExplosionOam_Big;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroInSr388DestroyOamWhenAnimEnded;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_BG_SCROLLING)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessInSr388BgScrolling;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_CAVE_ENTRANCE_BG)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388CaveEntranceBgOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessCaveEntranceBg;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_BLACK_RECTANGLE)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388BlackRectangeOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBlackRectangle;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_SECOND_DIAGONAL_MISSILE)
    {
        INTRO_DATA.oam[slot].spawnX = xPosition;
        INTRO_DATA.oam[slot].spawnY = yPosition;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388MissileOam_Diagonal;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSecondDiagonalMissile;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_PLACEHOLDER)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroInSr388DestroyOam;
    }

    return slot;
}

 /**
 * @brief 8c504 | 38 | Spawns an OAM for the 'hornoad encounter in SR388' cutscene with an additional argument (unused)
 * 
 */
void NewFileIntroInSr388SetupOamWithArgument(IntroInSr388OamType type, s16 xPosition, s16 yPosition, u16 arg3)
{
    u8 slot;
    
    slot = NewFileIntroInSr388SetupOam(type, xPosition, yPosition);
    INTRO_DATA.oam[slot].unk_8 = arg3;
}

 /**
 * @brief 8c53c | 4 | Empty function
 * 
 */
void NewFileIntro_Empty(void)
{
    return;
}

 /**
 * @brief 8c540 | 54 | Returns the X and Y position of a new file intro OAM
 * 
 */
void NewFileIntroGetPositionOfOamByType(IntroInSr388OamType type, s16* pXPosition, s16* pYPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == type)
        {
            *pXPosition = INTRO_DATA.oam[slot].xPosition;
            *pYPosition = INTRO_DATA.oam[slot].yPosition;
            
            return;
        }
    }

    // Default values if not found
    *pXPosition = 300;
    *pYPosition = 200;
}

 /**
 * @brief 8c594 | dc | V-blank for the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroInSr388Vblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    WRITE_16(REG_BLDY, gWrittenToBldy);

    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);

    if (INTRO_DATA.paletteUpdate1 == 1)
    {
        INTRO_DATA.paletteUpdate1 = 0;

        DMA3_COPY_32(sPal_5a9440, PALRAM_OBJ, 15 * PAL_ROW_SIZE / sizeof(u32));
        DMA3_COPY_32(sPal_5a9260, PALRAM_BASE, 15 * PAL_ROW_SIZE / sizeof(u32));
    }
}

 /**
 * @brief 8c670 | 204 | Setup for the new file intro Metroid vaccine cutscene
 * 
 */
void NewFileIntroSamusGettingCuredInit(void)
{
    const u16* pText2;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    pText2 = INTRO_DATA.pText2; // Preserve second text pointer
    
    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    INTRO_DATA.pText2 = pText2;

    LZ77UncompVram(sIntroMetroidVaccineObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroMetroidVaccineObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroMetroidVaccineBgGfx, VRAM_BASE);
    LZ77UncompVram(sIntroMetroidVaccineBg1Tilemap, VRAM_BASE + 0xE800);
    LZ77UncompVram(sIntroMetroidVaccineBg2Tilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroMetroidVaccineBg3Tilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroMetroidVaccineBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 29, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
    
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NEXT_PAGE_ARROW, 260, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_DOUBLE_HELIX, 192, 96);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_VACCINE_BG_TEXT, 0, 0);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroSamusGettingCuredVblank);
}

 /**
 * @brief 8c874 | 158 | Processes the new file intro Metroid vaccine cutscene
 * 
 */
boolu32 NewFileIntroSamusGettingCuredOperationProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.textAdvanceState == 0)
        INTRO_DATA.textAdvanceState = 1;

    INTRO_DATA.timer++;
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1))
            {
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = INTRO_DATA.pText2;
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(2 + 2.f / 3))
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(3))
            {
                NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_VACCINE_TEXTBOXES, 108, 64);
                NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_ELECTROCARDIOGRAM, 128, 68);
            }
            else if (INTRO_DATA.timer > CONVERT_SECONDS(6 + 2.f / 3))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }
        
            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
                INTRO_DATA.textAdvanceState = 0;
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 1:
            INTRO_DATA.timer = 0;

            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
                INTRO_DATA.subStage = 3;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy += 2;
            }
            else
            {
                gWrittenToBldy = BLDY_MAX_VALUE;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
                finished = TRUE;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
    
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 8c9cc | 20 | H-blank code for the new file intro Samus nervous system cutscene
 * 
 */
void NewFileIntroSamusGettingCuredNervousSystemHblank(void)
{
    s16 val;

    val = READ_16(REG_VCOUNT) * 2; // * 2, / 2 shenanigans are needed for match
    WRITE_16(REG_WIN0H, ((u16*)(EWRAM_BASE + 0x2000))[val / 2]);
}

 /**
 * @brief 8c9ec | 320 | Setup for the new file intro Samus nervous system cutscene
 * 
 */
void NewFileIntroSamusGettingCuredNervousSystemInit(void)
{
    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));

    INTRO_DATA.textAdvanceState = 0;

    LZ77UncompVram(sIntroSamusNervousSystemObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroSamusNervousSystemObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroSamusNervousSystemBgGfx, VRAM_BASE);
    LZ77UncompVram(sIntroSamusNervousSystemBg1Tilemap, VRAM_BASE + 0xE800);
    LZ77UncompVram(sIntroSamusNervousSystemBg2Tilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusNervousSystemBg3Tilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroSamusNervousSystemBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    SET_BACKDROP_COLOR(COLOR_GREEN);

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 29, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    gWrittenToBldalpha_Evb = gWrittenToBldalpha_Eva = 0;

    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NEXT_PAGE_ARROW, 260, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_PLACEHOLDER, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_PLACEHOLDER, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_PLACEHOLDER, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_PLACEHOLDER, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_PLACEHOLDER, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_PLACEHOLDER, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_PLACEHOLDER, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_CORNER_TEXT, 172, 158);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NERVE_PARTS, 120, 80);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_1, 195, 97);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_2, 128, 128);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_3, 145, 28);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_4, 100, 72);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_5, 44, 30);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_6, 62, 121);

    INTRO_DATA.paletteUpdate1 = 0;
    INTRO_DATA.paletteFrame1 = 0;

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_WIN0V, C_16_2_8(0, SCREEN_SIZE_Y));

    INTRO_DATA.windowRadius = 70;
    INTRO_DATA.windowCenterX = 120;
    INTRO_DATA.windowCenterY = 78;

    NewFileIntroSamusGettingCuredSetupWindow();
    NewFileIntroSamusGettingCuredSetupWindow();

    DMA3_COPY_32(NewFileIntroSamusGettingCuredNervousSystemHblank, INTRO_DATA.hBlankCode, sizeof(INTRO_DATA.hBlankCode) / sizeof(u32));
    INTRO_DATA.hBlankCodePointer = INTRO_DATA.hBlankCode + 1;
    CallbackSetHBlank(INTRO_DATA.hBlankCodePointer);

    WRITE_16(REG_IE, READ_16(REG_IE) | IF_HBLANK);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) | DSTAT_IF_HBLANK);
    WRITE_16(REG_WININ, WIN0_BG0 | WIN0_BG1 | WIN0_BG3 | WIN0_OBJ | WIN0_COLOR_EFFECT);
    WRITE_16(REG_WINOUT, WIN0_ALL);
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);
    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_WIN0);
    
    CallbackSetVBlank(NewFileIntroSamusGettingCuredNervousSystemVblank);
}

 /**
 * @brief 8cd0c | 274 | Processes the new file intro Samus nervous system cutscene
 * 
 */
boolu32 NewFileIntroSamusGettingCuredNervousSystemProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && !INTRO_DATA.textAdvanceState)
        INTRO_DATA.textAdvanceState = 1;

    APPLY_DELTA_TIME_INC(INTRO_DATA.timer);

    switch (INTRO_DATA.subStage)
    {
        case 0:
            NewFileIntroSamusGettingCuredNervousSystemInit();
            INTRO_DATA.subStage = 1;
            break;
        
        case 1:
            if (gWrittenToBldy)
            {
                gWrittenToBldy -= 2;
            }
            else
            {
                gWrittenToBldy = 0;
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG3_SECOND_TARGET_PIXEL 
                         | BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BACKDROP_SECOND_TARGET_PIXEL);
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 2:
            if (gWrittenToBldalpha_Eva < 12)
            {
                gWrittenToBldalpha_Eva++;
                gWrittenToBldalpha_Evb++;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 3;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 3:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][16];
                INTRO_DATA.subStage = 4;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 4:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.textAdvanceState == 2)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.pText2 = INTRO_DATA.pText;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 5;
            }
            else if (INTRO_DATA.textAdvanceState == 4)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG0);
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 5;
                INTRO_DATA.pText2 = INTRO_DATA.pText;
                INTRO_DATA.pText = sCutsceneTextNone;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 5:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_PALETTE_ANIMATION, 0, 0);
            }
            else if (INTRO_DATA.timer > CONVERT_SECONDS(7.5f))
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = 4;
                INTRO_DATA.subStage = 7;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 6:
            if (gWrittenToBldalpha_Eva)
            {
                gWrittenToBldalpha_Eva -= 2;
                gWrittenToBldalpha_Evb -= 2;
            }
            else
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.subStage = 7;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 7:
            WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
            
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy += 2;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
                finished = 1;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
    
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 8cf80 | dc | Main handler for the new file intro Samus getting cured cutscenes
 * 
 */
boolu32 NewFileIntroSamusGettingCured(void)
{
    boolu32 finished;

    finished = FALSE;
    
    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusGettingCuredInit();
            INTRO_DATA.stage = 1;
            break;

        case 1:
            SpecialCutsceneFadeIn();

            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroSamusGettingCuredOperationProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (NewFileIntroSamusGettingCuredNervousSystemProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 4;
            }
            break;

        case 4:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 8d05c | 10 | Processes the new file intro Metroid vaccine background text OAM
 * 
 */
void NewFileIntroProcessVaccineBackgroundText(struct SpecialCutsceneOam* pOam)
{
    WRITE_16(REG_BG2VOFS, pOam->yPosition--);
}

 /**
 * @brief 8d06c | 10 | Destroys a placeholder OAM of the Samus getting cured cutscene
 * 
 */
void NewFileIntroSamusGettingCuredDestroyOam(struct SpecialCutsceneOam* pOam)
{
    pOam->type = 0;
    pOam->exists = 0;
}

 /**
 * @brief 8d07c | e0 | Processes the first X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_1(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX - 4)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 5)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY)
        {
            pOam->yPosition--;
        }
    }
    
    if (INTRO_DATA.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 20)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_1, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 220)
        {
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->exists = 0;
            }
        }
    }
}

 /**
 * @brief 8d15c | 6c | Processes the new file intro X lock-on OAM
 * 
 */
void NewFileIntroProcessXLockOn(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    
    if (INTRO_DATA.oam[pOam->unk_8].type != 0)
    {
        pOam->xPosition = INTRO_DATA.oam[pOam->unk_8].xPosition;
        pOam->yPosition = INTRO_DATA.oam[pOam->unk_8].yPosition;
    }

    frame = &pOam->pOam[pOam->currentAnimationFrame];
    if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 8d1c8 | e4 | Processes the second X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_2(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX + 4)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX - 4)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 4)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY - 4)
        {
            pOam->yPosition--;
        }
    }
    
    if (INTRO_DATA.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 20)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_2, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 220)
        {
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->exists = 0;
            }
        }
    }
}

 /**
 * @brief 8d2ac | f0 | Processes the third X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_3(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX + 6)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX - 1)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 4)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY - 3)
        {
            pOam->yPosition--;
        }
    }
    
    if (INTRO_DATA.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 40)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_3, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 240)
        {
            pOam->affineMode = OAM_AFFINE_MODE_AFFINE;
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->exists = 0;
            }
        }
    }
}

 /**
 * @brief 8d39c | e4 | Processes the fourth X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_4(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX + 5)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX - 5)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 5)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY - 5)
        {
            pOam->yPosition--;
        }
    }
    
    if (INTRO_DATA.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 40)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_4, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 240)
        {
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->exists = 0;
            }
        }
    }
}

 /**
 * @brief 8d480 | f0 | Processes the fifth X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_5(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX + 5)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX - 1)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 4)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY)
        {
            pOam->yPosition--;
        }
    }
    
    if (INTRO_DATA.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 60)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_5, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 260)
        {
            pOam->affineMode = OAM_AFFINE_MODE_AFFINE;
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->exists = 0;
            }
        }
    }
}

 /**
 * @brief 8d570 | f0 | Processes the sixth X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_6(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX + 5)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 3)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY - 3)
        {
            pOam->yPosition--;
        }
    }
    
    if (INTRO_DATA.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 60)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_6, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 260)
        {
            pOam->affineMode = OAM_AFFINE_MODE_AFFINE;
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->exists = 0;
            }
        }
    }
}

 /**
 * @brief 8d660 | 94 | Animates the palette of the Samus nervous system cutscene (see sIntroNervousSystemPalAnimation)
 * 
 */
void NewFileIntroProcessNervousSystemPaletteAnimation(struct SpecialCutsceneOam *pOam)
{
    u8 value;
    
    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        if (pOam->unk_A > 20)
        {
            pOam->unk_A = 0;
            INTRO_DATA.paletteUpdate1 = 1;
            INTRO_DATA.paletteFrame1 = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1 && LOW_BYTE(sIntroNervousSystemPalAnimation[pOam->unk_8]) == pOam->unk_A)
    {
        pOam->unk_A = 0;

        if (pOam->unk_8 < 29)
            pOam->unk_8++;

        value = HIGH_BYTE(sIntroNervousSystemPalAnimation[pOam->unk_8]);
        INTRO_DATA.paletteFrame1 = value;
        INTRO_DATA.paletteUpdate1 = 1;
    }
}

 /**
 * @brief 8d6f4 | 6d0 | Spawns an OAM for a new file intro Samus getting cured cutscene
 * 
 */
u8 NewFileIntroSamusGettingCuredSetupOam(IntroSamusGettingCuredOamType type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot > 19)
        return 20;
    
    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));
    
    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].exists = 1;

    if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_DOUBLE_HELIX)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroMetroidVaccineDoubleHelixOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_VACCINE_TEXTBOXES)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroMetroidVaccineTextboxesOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_ELECTROCARDIOGRAM)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroMetroidVaccineElectrocardiogramOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_VACCINE_BG_TEXT)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessVaccineBackgroundText;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_PLACEHOLDER)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredDestroyOam;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_COUNTDOWN_FAST)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemCountdownOam_Fast;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_COUNTDOWN_SLOW)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemCountdownOam_Slow;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NUMBER_281)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemNumber281Oam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_CORNER_TEXT)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemCornerTextOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NERVE_PARTS)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemNervePartsOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_1)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.25f);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_1;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_1;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_2)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.5f);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_2;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_2;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_3)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_3;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_3;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_4)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.25f);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_4;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_4;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_5)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_5;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_5;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_6)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_6;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_6;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_1)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_1);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_1;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_2)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_2);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_2;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_3)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_3);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_3;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_4)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_4);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_4;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_5)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_5);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_5;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_6)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_6);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_6;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_PALETTE_ANIMATION)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessNervousSystemPaletteAnimation;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }
    
    return slot;
}

 /**
 * @brief 8ddc4 | 38 | Spawns an OAM for a new file intro Samus getting cured cutscene with an additional argument (unused)
 * 
 */
void NewFileIntroSamusGettingCuredSetupOamWithArgument(IntroSamusGettingCuredOamType type, s16 xPosition, s16 yPosition, s16 arg3)
{
    u8 slot;

    slot = NewFileIntroSamusGettingCuredSetupOam(type, xPosition, yPosition);
    INTRO_DATA.oam[slot].unk_8 = arg3;
}

 /**
 * @brief 8ddfc | 3c | Returns the OAM slot of the specified Samus getting cured cutscene OAM
 * 
 */
u8 NewFileIntroFindOamByType(IntroSamusGettingCuredOamType type)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == type)
            return slot;
    }

    // Default value if not found
    return ARRAY_SIZE(INTRO_DATA.oam);
}

 /**
 * @brief 8de38 | 4c | V-blank code for the new file intro Metroid vaccine cutscene
 * 
 */
void NewFileIntroSamusGettingCuredVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

 /**
 * @brief 8de84 | a8 | V-blank code for the new file intro Samus nervous system cutscene
 * 
 */
void NewFileIntroSamusGettingCuredNervousSystemVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    if (INTRO_DATA.paletteUpdate1 == 1)
    {
        INTRO_DATA.paletteUpdate1 = 0;

        DMA3_COPY_32(sIntroNervousSystemPalPointers[INTRO_DATA.paletteFrame1], PALRAM_OBJ, 4 * PAL_ROW_SIZE / sizeof(u32));
        DMA3_COPY_32(sIntroNervousSystemPalPointers[INTRO_DATA.paletteFrame1], PALRAM_BASE, 4 * PAL_ROW_SIZE / sizeof(u32));
    }
}

 /**
 * @brief 8df2c | 4 | Empty OAM handler function for the 'Samus getting cured' cutscenes 
 * 
 */
void NewFileIntroSamusGettingCuredProcessOam_Empty(struct SpecialCutsceneOam* pOam)
{
    return;
}

 /**
 * @brief 8df30 | 210 | Setup for the intro Samus found cutscene
 * 
 */
void NewFileIntroSamusFoundInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroHazmatTeamGfx, VRAM_BASE);
    LZ77UncompVram(sIntroVariaSuitCoveredInXParasitesGfx, VRAM_BASE + 0x8000);
    LZ77UncompVram(sIntroHazmatTeamTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroVariaSuitCoveredInXParasitesTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroSamusFoundPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompWram(sIntroSuitRemovalSurgeryGfx, EWRAM_BASE);
    LZ77UncompWram(sIntroMetroidVaccineVialGfx, EWRAM_BASE + 0x8000);
    LZ77UncompWram(sIntroSuitRemovalSurgeryTilemap, EWRAM_BASE + 0xD000);
    LZ77UncompWram(sIntroMetroidVaccineVialTilemap, EWRAM_BASE + 0xD800);

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(2, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_NEXT_PAGE_ARROW, 260, 0);
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroSamusFoundVblank);
}

 /**
 * @brief 8e140 | 594 | Processes the intro Samus found cutscene
 * 
 */
boolu32 NewFileIntroSamusFoundProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && !INTRO_DATA.textAdvanceState)
        INTRO_DATA.textAdvanceState = 1;
    
    APPLY_DELTA_TIME_INC(INTRO_DATA.timer);
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer == TWO_THIRD_SECOND)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][12];
                INTRO_DATA.subStage = 1;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 1:
            INTRO_DATA.timer = 0;
            gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
            gWrittenToBldalpha_Evb = 0;

            if (INTRO_DATA.textAdvanceState == 2)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 2;
            }
            else if (INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 2;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.5f) - DELTA_TIME)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN, 16, 0);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG3);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 3;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 3:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f) - DELTA_TIME)
            {
                SpecialCutsceneDestroyOamOfType(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN);
                gWrittenToBldalpha_Eva = 0;
                gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f))
            {
                DMA3_COPY_32(EWRAM_BASE + 0xD000, VRAM_BASE + 0xF000, 0x200);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f) + DELTA_TIME)
            {
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_LOAD_GFX, 0, 0);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1 + 2.f / 3) - DELTA_TIME)
            {
                // Empty
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1 + 2.f / 3))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 4:
            INTRO_DATA.timer = 0;
            gWrittenToBldalpha_Eva = 0;
            gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;

            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_LAYING, 0, 0);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG2);
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 5;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 5:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f))
            {
                INTRO_DATA.timer = 0;
                SpecialCutsceneDestroyOamOfType(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_LAYING);
                gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
                gWrittenToBldalpha_Evb = 0;
                INTRO_DATA.subStage = 6;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 6:
            if (INTRO_DATA.timer == ONE_THIRD_SECOND)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][13];
                INTRO_DATA.subStage = 7;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 7:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 8;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 8:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
                INTRO_DATA.timer = 0;
                DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][14];
                INTRO_DATA.subStage = 9;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 9:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
                gWrittenToBldalpha_Evb = 0;
                INTRO_DATA.subStage = 10;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 10:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG3);
                DMA3_COPY_32(EWRAM_BASE + 0xD800, VRAM_BASE + 0xF800, 0x200);
            }
            else if (INTRO_DATA.timer == 2 * DELTA_TIME)
            {
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_LOAD_GFX_2, 0, 0);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(.25f))
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG3);
                INTRO_DATA.timer = 0;
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_VACCINE, 0, 0);
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_SCREEN_SCROLLING, 0, gBg2YPosition);
                INTRO_DATA.subStage = 11;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
	    case 11:
	        if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f))
            {
	            gWrittenToBldalpha_Eva = 0;
	            gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
	            INTRO_DATA.timer = 0;
	            SpecialCutsceneDestroyOamOfType(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_VACCINE);
	            SpecialCutsceneDestroyOamOfType(INTRO_SAMUS_FOUND_OAM_TYPE_SCREEN_SCROLLING);
	            INTRO_DATA.subStage = 12;
	        }
	
	        SpecialCutsceneProcessOam();
	        SpecialCutsceneDrawAllOam();
	        break;
        
	    case 12:
	        if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
	            INTRO_DATA.timer = 0;
	            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
	            INTRO_DATA.indent = 0;
	            INTRO_DATA.currentLine = 0;
	            INTRO_DATA.currentColumn = 0;
	            INTRO_DATA.pText = sMonologueTextPointers[gLanguage][15];
	            INTRO_DATA.subStage = 13;
	        }
	
	        SpecialCutsceneProcessOam();
	        SpecialCutsceneDrawAllOam();
	        break;
	
	    case 13:
	        INTRO_DATA.timer = 0;
            
	        if (INTRO_DATA.textAdvanceState == 2)
            {
                INTRO_DATA.textAdvanceState = 0;
	            INTRO_DATA.pText2 = INTRO_DATA.pText;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
	            INTRO_DATA.pText2 = INTRO_DATA.pText;
	            INTRO_DATA.pText = sCutsceneTextNone;
	            INTRO_DATA.subStage = 14;
            }
            else if (INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
	            INTRO_DATA.pText2 = INTRO_DATA.pText;
	            INTRO_DATA.pText = sCutsceneTextNone;
	            INTRO_DATA.subStage = 14;
            }
            
	        SpecialCutsceneProcessOam();
	        SpecialCutsceneDrawAllOam();
	        break;
	
	    case 14:
	        if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
	            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
	            WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
	            gWrittenToBldy = 0;
	            INTRO_DATA.timer = 0;
	            INTRO_DATA.subStage = 0;
	            finished = TRUE;
	        }
	
	        SpecialCutsceneProcessOam();
	        SpecialCutsceneDrawAllOam();
	        break;
    }
    
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 8e6d4 | a8 | Main handler of the intro Samus found cutscene
 * 
 */
boolu32 NewFileIntroSamusFound(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusFoundInit();
            INTRO_DATA.stage = 1;
            break;

        case 1:
            APPLY_DELTA_TIME_INC(INTRO_DATA.timer);
            if (INTRO_DATA.timer == CONVERT_SECONDS(.1f))
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldy)
                    gWrittenToBldy--;
                else
                    INTRO_DATA.stage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (NewFileIntroSamusFoundProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 8e77c | 6c | Fades in the Varia suit covered in X parasites screen
 * 
 */
void NewFileIntroProcessSamusFoundFadeIn(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == 4)
    {
        pOam->timer = 0;

        if (pOam->xPosition > 0)
            pOam->xPosition--;
    }

    gBg3XPosition = pOam->xPosition;
    gBg3YPosition = 0;

    pOam->unk_A++;
    if (pOam->unk_A == 5)
    {
        pOam->unk_A = 0;

        if (gWrittenToBldalpha_Eva)
        {
            gWrittenToBldalpha_Eva--;
            gWrittenToBldalpha_Evb++;
        }
    }
}

 /**
 * @brief 8e7e8 | 48 | Copies intro Samus found cutscene graphics from EWRAM into VRAM
 * 
 */
void NewFileIntroProcessSamusLayingLoading(struct SpecialCutsceneOam* pOam)
{
    u32 offset;

    offset = pOam->unk_A * 0x1000;
    DMA3_COPY_32(EWRAM_BASE + offset, VRAM_BASE + offset, 0x1000 / sizeof(u32));

    pOam->unk_A++;
    if (pOam->unk_A == pOam->unk_8 + pOam->unk_4)
        pOam->type = 0;
}

 /**
 * @brief 8e830 | 6c | Fades in the intro Varia suit removal surgery screen
 * 
 */
void NewFileIntroProcessSamusFoundFadeInSamusLaying(struct SpecialCutsceneOam* pOam)
{
    APPLY_DELTA_TIME_INC(pOam->timer);
    if (pOam->timer == 3)
    {
        pOam->timer = 0;
        
        if (pOam->yPosition < 96)
            pOam->yPosition++;
    }

    gBg2XPosition = 0;
    gBg2YPosition = pOam->yPosition;

    pOam->unk_A++;
    if (pOam->unk_A == 4)
    {
        pOam->unk_A = 0;

        if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
        {
            gWrittenToBldalpha_Eva++;
            gWrittenToBldalpha_Evb--;
        }
    }
}

 /**
 * @brief 8e89c | 6c | Fades in the intro Metroid vaccine closeup screen
 * 
 */
void NewFileIntroProcessSamusFoundFadeInVaccineCloseUp(struct SpecialCutsceneOam* pOam)
{
    APPLY_DELTA_TIME_INC(pOam->timer);
    if (pOam->timer == 4)
    {
        pOam->timer = 0;
        
        if (pOam->xPosition < 16)
            pOam->xPosition++;
    }

    gBg3XPosition = pOam->xPosition;
    gBg3YPosition = 0;

    pOam->unk_A++;
    if (pOam->unk_A == 5)
    {
        pOam->unk_A = 0;

        if (gWrittenToBldalpha_Eva)
        {
            gWrittenToBldalpha_Eva--;
            gWrittenToBldalpha_Evb++;
        }
    }
}

 /**
 * @brief 8e908 | 3c | Handles the downward scrolling of the intro Varia suit removal surgery screen
 * 
 */
void NewFileIntroProcessSamusFoundScreenScrolling(struct SpecialCutsceneOam* pOam)
{
    APPLY_DELTA_TIME_INC(pOam->timer);
    if (pOam->timer == 3)
    {
        pOam->timer = 0;
        
        if (pOam->yPosition < 96)
            pOam->yPosition++;
    }

    gBg2XPosition = 0;
    gBg2YPosition = pOam->yPosition;
}

 /**
 * @brief 8e944 | 1bc | Spawns an OAM for a new file intro Samus found cutscene
 * 
 */
u8 NewFileIntroSamusFoundSetupOam(IntroSamusFoundOamType type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot >= ARRAY_SIZE(INTRO_DATA.oam))
        return ARRAY_SIZE(INTRO_DATA.oam);

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].exists = 1;

    if (type == INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusFoundFadeIn;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_LOAD_GFX)
    {
        INTRO_DATA.oam[slot].unk_A = 0;
        INTRO_DATA.oam[slot].unk_8 = 0;
        INTRO_DATA.oam[slot].unk_4 = 8;
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusLayingLoading;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_LAYING)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusFoundFadeInSamusLaying;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_LOAD_GFX_2)
    {
        INTRO_DATA.oam[slot].unk_A = 8;
        INTRO_DATA.oam[slot].unk_8 = 8;
        INTRO_DATA.oam[slot].unk_4 = 5;
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusLayingLoading;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_VACCINE)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusFoundFadeInVaccineCloseUp;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_SCREEN_SCROLLING)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusFoundScreenScrolling;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }

    return slot;
}

 /**
 * @brief 8eb00 | 7c | V-blank for the intro Samus found cutscene
 * 
 */
void NewFileIntroSamusFoundVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

 /**
 * @brief 8eb7c | 4 | Empty function
 * 
 */
void NewFileIntroSamusFound_Empty(void)
{
    return;
}

 /**
 * @brief 8eb80 | 250 | Setup for the intro Samus cured cutscene
 * 
 */
void NewFileIntroSamusCuredInit(void)
{
    const u16* pText2;
    
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    pText2 = INTRO_DATA.pText2;

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    INTRO_DATA.pText2 = pText2;

    LZ77UncompVram(sIntroApproachingBslObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroApproachingBslObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 15 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroSamusRebornBgTopGfx, VRAM_BASE);
    LZ77UncompVram(sIntroSamusRebornBgBottomGfx, VRAM_BASE + 0x8000);
    LZ77UncompVram(sIntroSamusRebornBgTopTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusRebornBgBottomTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroSamusRebornBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(&sIntroSamusFoundPal[15 * PAL_ROW], PALRAM_BASE + 15 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompWram(sIntroSamusMonologueBgTilemap, EWRAM_BASE);
    LZ77UncompWram(sIntroSamusMonologueBgGfx, EWRAM_BASE + 0x1000);

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(2, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 256;

    NewFileIntroSamusCuredSetupOam(INTRO_SAMUS_CURED_OAM_TYPE_NEXT_PAGE_ARROW, 260, 0);
    NewFileIntroSamusCuredSetupOam(INTRO_SAMUS_CURED_OAM_TYPE_SCREEN_SCROLLER, 0, 0);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroSamusCuredVblank);
}

 /**
 * @brief 8edd0 | 428 | Processes the Samus cured cutscene
 * 
 */
boolu32 NewFileIntroSamusCuredProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.textAdvanceState == 0)
        INTRO_DATA.textAdvanceState = 1;
    
    APPLY_DELTA_TIME_INC(INTRO_DATA.timer);
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (gWrittenToBldy)
            {
                gWrittenToBldy--;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 1:
            if (INTRO_DATA.timer == CONVERT_SECONDS(4 + 2.f / 3))
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = INTRO_DATA.pText2;
                INTRO_DATA.subStage = 3;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
	    case 3:
	        INTRO_DATA.timer = 0;
	
	        if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
	        {
	            INTRO_DATA.textAdvanceState = 0;
	        }
	        else if (INTRO_DATA.textAdvanceState == 3)
	        {
	            INTRO_DATA.textAdvanceState = 0;
	            INTRO_DATA.subStage = 4;
	        }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 4:
            if (INTRO_DATA.timer == ONE_THIRD_SECOND)
            {
                INTRO_DATA.timer = 0;
                DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));
                INTRO_DATA.subStage = 5;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

	    case 5:
	        INTRO_DATA.unk_213++;
	        if (INTRO_DATA.unk_213 < 6)
	        {
	            DMA3_COPY_32(EWRAM_BASE + INTRO_DATA.unk_213 * 0x1000, VRAM_BASE + 0x7000 + INTRO_DATA.unk_213 * 0x1000, 0x1000 / sizeof(u32));
	        }
	        else if (INTRO_DATA.unk_213 == 6)
	        {
	            DMA3_COPY_32(sIntroSamusCuredFadePalPointers[0], PALRAM_BASE, 2 * PAL_ROW);
	            DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xF000, 0x800 / sizeof(u32));
	            gWrittenToBldalpha_Eva = 0;
	            gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
	            gBg2YPosition = 0;
	        }
	        else
	        {
	            INTRO_DATA.unk_213 = 10;
	        }
	
	        if (INTRO_DATA.timer == DELTA_TIME)
	        {
	            INTRO_DATA.timer = 0;
	
	            if (INTRO_DATA.paletteFrame1 < 15)
	            {
	                INTRO_DATA.paletteFrame1++;
	                INTRO_DATA.paletteUpdate1 = 1;
	            }
	            else
	            {
	                WRITE_16(REG_BLDCNT, BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT 
	                         | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
	                INTRO_DATA.unk_213 = 0;
	                INTRO_DATA.subStage = 6;
	            }
	        }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
	    case 6:
	        if (INTRO_DATA.timer == CONVERT_SECONDS(1 + 1.f / 6))
            {
	            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG2);
	            INTRO_DATA.timer = 0;
	            INTRO_DATA.subStage = 7;
	        }

	        SpecialCutsceneProcessOam();
	        SpecialCutsceneDrawAllOam();
	        break;
        
	    case 7:
	        INTRO_DATA.unk_213++;
	        if (INTRO_DATA.unk_213 == 8)
	        {
	            INTRO_DATA.unk_213 = 0;
	
	            if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
	            {
	                gWrittenToBldalpha_Eva++;
	                gWrittenToBldalpha_Evb--;
	            }
	            else
	            {
	                INTRO_DATA.timer = 0;
	                INTRO_DATA.subStage = 8;
	            }
	        }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 8:
            if (INTRO_DATA.timer == CONVERT_SECONDS(2.f / 15))
            {
                INTRO_DATA.timer = 0;
                
                if (INTRO_DATA.paletteFrame2 < 15)
                {
                    INTRO_DATA.paletteFrame2++;
                    INTRO_DATA.paletteUpdate2 = 1;
                }
                else
                {
                    gWrittenToBldy = 0;
                    INTRO_DATA.subStage = 9;
                }
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 9:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
                INTRO_DATA.timer = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][17];
                INTRO_DATA.subStage = 10;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 10:
            INTRO_DATA.timer = 0;

            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
	        {
	            INTRO_DATA.textAdvanceState = 0;
	        }
	        else if (INTRO_DATA.textAdvanceState == 3)
	        {
	            INTRO_DATA.textAdvanceState = 0;
	            INTRO_DATA.subStage = 11;
	        }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 11:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
                NewFileIntroSamusCuredSetupOam(INTRO_SAMUS_CURED_OAM_TYPE_SCREEN_GLARE, SCREEN_X_MIDDLE, 64);
            }
            else if (INTRO_DATA.timer == TWO_THIRD_SECOND)
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = BLDY_MAX_VALUE;
                INTRO_DATA.subStage = 12;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 12:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
                gWrittenToBldy++;
            else
                finished = TRUE;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    IntroProcessText();

    return finished;
}

 /**
 * @brief 8f1f8 | 88 | Main handler for the intro Samus cured cutscene
 * 
 */
boolu32 NewFileIntroSamusCured(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusCuredInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();

            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroSamusCuredProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
        
    return finished;
}

 /**
 * @brief 8f280 | 104 | Processes the screen scrolling in the Samus cured cutscene
 * 
 */
void NewFileIntroSamusCuredProcessScrolling(struct SpecialCutsceneOam *pOam)
{
    APPLY_DELTA_TIME_INC(pOam->timer);

    if (pOam->stage == 0)
    {
        pOam->xPosition = gBg2XPosition;
        pOam->yPosition = gBg2YPosition;
        pOam->spawnX = gBg3XPosition;
        pOam->spawnY = gBg3YPosition;
        pOam->unk_A = 0x5000;
        pOam->timer = 0;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        if (pOam->timer == CONVERT_SECONDS(1.f / 6))
        {
            pOam->timer = 0;
            pOam->stage = 2;
        }
    }
    else if (INTRO_DATA.subStage == 1)
    {
        if (pOam->timer == DELTA_TIME)
        {
            pOam->timer = 0;
            
            if (pOam->yPosition > -SCREEN_SIZE_Y)
            {
                pOam->yPosition--;
                pOam->unk_8++;
            }
            
            if (pOam->spawnY > 0)
                pOam->spawnY--;

            gBg2YPosition = pOam->yPosition;
            gBg3YPosition = pOam->spawnY;
        }
        
        if (pOam->unk_8 == 9)
        {
            pOam->unk_8 = 0;
            
            if (pOam->unk_A)
            {
                pOam->unk_A -= 0x400;
                DMA3_FILL_32(0, VRAM_BASE + 0x8000 + pOam->unk_A, 0x400);
            }
        }
    }
    else
    {
        pOam->timer = 0;
    }
}

 /**
 * @brief 8f384 | 140 | Spawns an OAM for the intro Samus cured cutscene
 * 
 */
u8 NewFileIntroSamusCuredSetupOam(IntroSamusCuredOamType type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot >= ARRAY_SIZE(INTRO_DATA.oam))
        return ARRAY_SIZE(INTRO_DATA.oam);

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].exists = 1;

    if (type == INTRO_SAMUS_CURED_OAM_TYPE_SCREEN_SCROLLER)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusCuredProcessScrolling;
    }
    else if (type == INTRO_SAMUS_CURED_OAM_TYPE_SCREEN_GLARE)
    {
        SoundPlay(SOUND_12D);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusCuredScreenGlareOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_CURED_OAM_TYPE_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }

    return slot;
}

 /**
 * @brief 8f4c4 | fc | V-blank for the Samus cured cutscene
 * 
 */
void NewFileIntroSamusCuredVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);

    if (INTRO_DATA.paletteUpdate1 == 1)
    {
        INTRO_DATA.paletteUpdate1 = 0;
        DMA3_COPY_32(sIntroSamusCuredBgFadePalPointers[INTRO_DATA.paletteFrame1], PALRAM_BASE + 5 * PAL_ROW_SIZE, 10 * PAL_ROW_SIZE / sizeof(u32));
    }

    if (INTRO_DATA.paletteUpdate2 == 1)
    {
        INTRO_DATA.paletteUpdate2 = 0;
        DMA3_COPY_32(sIntroSamusCuredFadePalPointers[INTRO_DATA.paletteFrame2], PALRAM_BASE, 4 * PAL_ROW_SIZE / sizeof(u32));
    }
}

 /**
 * @brief 8f5c0 | 4 | Intro Samus cured OAM handler (empty)
 * 
 */
void NewFileIntroSamusCuredProcessOam_Empty(struct SpecialCutsceneOam* pOam)
{
    return;
}

 /**
 * @brief 8f5c4 | 230 | Setup for the arriving at BSL cutscene
 * 
 */
void NewFileIntroArrivingAtBslInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sIntroApproachingBslObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroApproachingBslObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroArrivingAtBslSpaceMapBgGfx, VRAM_BASE);
    LZ77UncompVram(sIntroSamusMonologueBgGfx, VRAM_BASE + 0x8000);
    LZ77UncompVram(sIntroArrivingAtBslSpaceMapTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusMonologueBgTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroArrivingAtBslSpaceMapPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    SET_BACKDROP_COLOR(COLOR_BLACK);

    LZ77UncompWram(sMonologueTextTilemap, EWRAM_BASE);
    LZ77UncompWram(sIntroFlyingToBslObjGfx, EWRAM_BASE + 0x1000);
    LZ77UncompWram(sIntroFlyingToBslBgGfx, EWRAM_BASE + 0x9000);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg0XPosition = -8;
    gBg0YPosition = 8;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(2, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    gWrittenToBldalpha_Eva = 0;
    gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;

    NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_TRAJECTORY, 112, 80);
    NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_PLANETS_AND_SHIP, 112, 80);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroArrivingAtBslVblank);
}

 /**
 * @brief 8f7f4 | 750 | Processes the arriving at BSL cutscene
 * 
 */
boolu32 NewFileIntroArrivingAtBslProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.textAdvanceState == 0)
        INTRO_DATA.textAdvanceState = 1;

    APPLY_DELTA_TIME_INC(INTRO_DATA.timer);

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.05f))
            {
                INTRO_DATA.timer = 0;
                
                if (gWrittenToBldalpha_Evb > 8)
                    gWrittenToBldalpha_Evb--;
                
                if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
                    gWrittenToBldalpha_Eva += 2;
                else
                    INTRO_DATA.subStage = 2;
                
                if (gWrittenToBldalpha_Eva == 8)
                {
                    NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_TRAJECTORY, 112, 80);
                    NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_PLANETS_AND_SHIP, 112, 80);
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL_POPUP, 198, 36);
            }
            else if (INTRO_DATA.timer == TWO_THIRD_SECOND)
            {
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_PLACEHOLDER, 0, 0);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_TEXT_CURSOR, 20, 192);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_PANEL_FRAME, 128, 192);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_PANEL_BACKGROUND, 128, 192);
                INTRO_DATA.subStage = 3;
                INTRO_DATA.timer = 0;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            NewFileIntroProcessAdamText();
            break;

        case 3:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
                SoundPlay(SOUND_203);
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~ DCNT_BG0);
                INTRO_DATA.textAdvanceState = 0;
                SoundPlay(SOUND_203);
                INTRO_DATA.subStage = 4;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            NewFileIntroProcessAdamText();
            break;

        case 4:
            INTRO_DATA.timer = 0;
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 5:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[580].trackGroupNumber].pTrack, 0);
            }
            else if (INTRO_DATA.timer > CONVERT_SECONDS(.5f))
            {
                if (gWrittenToBldy < BLDY_MAX_VALUE)
                {
                    gWrittenToBldy++;
                }
                else
                {
                    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
                    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG3);
                    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.subStage = 6;
                }
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 6:
            INTRO_DATA.timer = 0;
            
            if (gWrittenToBldy)
                gWrittenToBldy--;
            else
                INTRO_DATA.subStage = 7;
            break;

        case 7:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                DMA3_FILL_32(0, VRAM_BASE, 0x4800);
            }
            else if (INTRO_DATA.timer == 2 * DELTA_TIME)
            {
                DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0x4800, 0x800 / sizeof(u32));
                DMA3_COPY_32(sMonologueTextPal, PALRAM_BASE + 12 * PAL_ROW_SIZE, 4 * PAL_ROW_SIZE / sizeof(u32));
                gBg0XPosition = 0;
                gBg0YPosition = 4;
            }
            else if (INTRO_DATA.timer == 3 * DELTA_TIME)
            {
                WRITE_16(REG_BG0CNT, CREATE_BGCNT(0, 9, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.fadeLine = 0;
                INTRO_DATA.fadeColumn = 0;
                INTRO_DATA.currentLine = 0;
                INTRO_DATA.currentColumn = 0;
                INTRO_DATA.indent = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][0];
                INTRO_DATA.subStage = 8;
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_MONOLOGUE_CURSOR, 260, 0);
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 8:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.textAdvanceState == 2 || INTRO_DATA.textAdvanceState == 4)
            {
                INTRO_DATA.textAdvanceState = 0;
            }
            else if (INTRO_DATA.textAdvanceState == 3)
            {
                INTRO_DATA.textAdvanceState = 0;
                INTRO_DATA.subStage = 9;
            }
            
            if (NewFileIntroCheckMonologueEnded())
            {
                INTRO_DATA.subStage = 9;
                INTRO_DATA.textAdvanceState = 0;
            }
            
            if (INTRO_DATA.unk_213 == 0)
            {
                INTRO_DATA.unk_213 = 100;
            }
            else if (INTRO_DATA.unk_213 == 1)
            {
                INTRO_DATA.unk_213 = 100;
                SpecialCutsceneProcessMonologue();
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 9:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                gWrittenToBldalpha_Evb = 0;
                gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
                FadeMusic(256);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_BG0_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG3_SECOND_TARGET_PIXEL);
                INTRO_DATA.subStage = 10;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 10:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 15))
            {
                INTRO_DATA.timer = 0;
                
                if (gWrittenToBldalpha_Evb < BLDALPHA_MAX_VALUE)
                    gWrittenToBldalpha_Evb++;
                
                if (gWrittenToBldalpha_Eva)
                    gWrittenToBldalpha_Eva--;
                
                if (gWrittenToBldalpha_Evb == BLDALPHA_MAX_VALUE && !gWrittenToBldalpha_Eva)
                {
                    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG0);
                    INTRO_DATA.subStage = 11;
                }
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 11:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
                gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
                gWrittenToBldalpha_Evb = 0;
            }
            else if (INTRO_DATA.timer < 6 * DELTA_TIME)
            {
                DMA3_COPY_32(EWRAM_BASE - 0x3000 + INTRO_DATA.timer * 0x2000, VRAM_BASE + 0xC000 + INTRO_DATA.timer * 0x2000, 0x2000 / sizeof(u32));
            }
            else if (INTRO_DATA.timer < 10 * DELTA_TIME)
            {
                DMA3_COPY_32(EWRAM_BASE - 0x3000 + INTRO_DATA.timer * 0x2000, VRAM_BASE - 0xC000 + INTRO_DATA.timer * 0x2000, 0x2000 / sizeof(u32));
            }
            else if (INTRO_DATA.timer == 10 * DELTA_TIME)
            {
                LZ77UncompVram(sIntroTilemap_5f65d8, VRAM_BASE + 0xE800);
            }
            else if (INTRO_DATA.timer == 11 * DELTA_TIME)
            {
                LZ77UncompVram(sIntroTilemap_5f5454, VRAM_BASE + 0xF000);
                WRITE_16(REG_BG1CNT, CREATE_BGCNT(2, 31, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
            }
            else if (INTRO_DATA.timer == 12 * DELTA_TIME)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG3);
                WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 29, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
                WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
                WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_SECOND_TARGET_PIXEL 
                        | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
                DMA3_COPY_32(sPal_5f4ed4, PALRAM_BASE + 4 * PAL_ROW_SIZE, 12 * PAL_ROW_SIZE / sizeof(u32));
                gBg2XPosition = 0;
                gBg2YPosition = 0;
                gBg3XPosition = 0;
                gBg3YPosition = 0;
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG3);
                INTRO_DATA.timer = 0;
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_PLACEHOLDER, 0, 0);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_1, 208, 100);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_2, 208, 100);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_3, 208, 100);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP, 196, 100);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL, 6, 78);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BG3_SCROLLER, 0, 0);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BG2_SCROLLER, 0, 0);
                SoundPlay_3b1c(SOUND_245);
                INTRO_DATA.subStage = 12;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 12:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 15))
            {
                INTRO_DATA.timer = 0;
                
                if (gWrittenToBldalpha_Evb < BLDALPHA_MAX_VALUE)
                    gWrittenToBldalpha_Evb++;
                
                if (gWrittenToBldalpha_Eva)
                    gWrittenToBldalpha_Eva--;

                if (gWrittenToBldalpha_Evb == BLDALPHA_MAX_VALUE)
                {
                    if (!gWrittenToBldalpha_Eva)
                    {
                        WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG1);
                        INTRO_DATA.subStage = 13;
                    }
                }
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 13:
            INTRO_DATA.timer = 0;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 14:
            if (INTRO_DATA.timer == CONVERT_SECONDS(4.f / 3))
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
    
    return finished;
}

 /**
 * @brief 8ff44 | 90 | Main handler of the arriving at BSL cutscene
 * 
 */
boolu32 NewFileIntroArrivingAtBsl(void)
{
    boolu32 finished;

    finished = FALSE;
    
    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroArrivingAtBslInit();
            INTRO_DATA.stage = 1;
            break;
        
        case 1:
            gWrittenToBldy = 0;
            SoundPlay(SOUND_244);
            
            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;
        
        case 2:
            if (NewFileIntroArrivingAtBslProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;
        
        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
    
    return finished;
}

 /**
 * @brief 8ffd4 | 270 | Processes Samus' ship in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessSamusShipArrivingAtBsl(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->unk_A++;
    
    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        
        if (pOam->unk_A == 20)
        {
            pOam->unk_A = 0;
            pOam->animationDurationCounter = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        if (pOam->timer == CONVERT_SECONDS(1.f / 30))
        {
            pOam->timer = 0;
            pOam->scaling--;
        }

        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 3);
        
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->spawnX = pOam->spawnX - (pOam->unk_A >> 3);
            pOam->spawnY = pOam->yPosition;
            pOam->timer = 0;
            pOam->unk_A = 0;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (pOam->unk_A == 2)
        {
            NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_EXPLOSION, pOam->xPosition, pOam->yPosition);
            pOam->rotation -= 1;
        }
        else if (pOam->unk_A == 4)
        {
            pOam->unk_A = 0;
            pOam->stage = 3;
            pOam->rotation -= 1;
        }
        
        pOam->scaling--;
        pOam->animationDurationCounter = 0;
    }
    else if (pOam->stage == 3)
    {
        pOam->scaling -= 2;
        
        NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL, &x, &y);
        
        if (pOam->rotation > Q_8_8(15.f / 16))
            pOam->rotation--;

        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 1);
        pOam->xPosition = pOam->spawnX - (pOam->unk_A << 1);

        if (pOam->unk_A == 10)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 4;
        }
        
        pOam->animationDurationCounter = 0;
    }
    else if (pOam->stage == 4)
    {
        pOam->scaling -= 4;
        
        NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL, &x, &y);
        
        if (pOam->rotation > Q_8_8(15.f / 16))
            pOam->rotation--;
        
        pOam->yPosition = pOam->spawnY - pOam->unk_A;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A << 2);
        
        if (x - pOam->xPosition > -20)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 5;
        }
        
        pOam->animationDurationCounter = 0;
    }
    else if (pOam->stage == 5)
    {
        pOam->scaling -= 2;
        
        NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL, &x, &y);
        
        if ((u8)(pOam->rotation - Q_8_8(.04f)) > Q_8_8(.745f))
            pOam->rotation++;

        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 1);
        pOam->xPosition = pOam->spawnX - (pOam->unk_A << 1);
        
        if (x - pOam->xPosition > 10)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 6;
        }
        
        pOam->animationDurationCounter = 0;
    }
    else if (pOam->stage == 6)
    {
        pOam->scaling--;

        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 2);
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 1);
    
        if ((u8)(pOam->rotation - Q_8_8(.04f)) > Q_8_8(.745f))
        {
            pOam->rotation++;
        }
        else
        {
            pOam->unk_A = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 7;
        }
    
        pOam->animationDurationCounter = 0;
    }
    else if (pOam->stage == 7)
    {
        if ((u8)(pOam->rotation - Q_8_8(1.f / 16)) > Q_8_8(.72f))
        {
            pOam->timer++;
            if (pOam->timer == CONVERT_SECONDS(.05f))
            {
                pOam->timer = 0;
                pOam->rotation++;
            }
        }
        
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 2);
        pOam->xPosition = (pOam->unk_A >> 1) + pOam->spawnX;
        
        pOam->scaling -= 2;
        if (pOam->scaling < Q_8_8(1.f / 8))
        {
            pOam->type = 0;
            pOam->exists = 0;
            INTRO_DATA.subStage = 14;
        }
        
        pOam->animationDurationCounter = 0;
    }
    
    if (pOam->scaling <= Q_8_8(1))
        pOam->affineMode = OAM_AFFINE_MODE_AFFINE;
}

 /**
 * @brief 90244 | 20 | Processes the BSL in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessBslPreview(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == CONVERT_SECONDS(1.f / 10))
    {
        pOam->timer = 0;
        pOam->xPosition++;
    }
}

 /**
 * @brief 90264 | 1ac | Processes the ship's thrusters in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessSamusShipArrivingAtBslThrusters(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    u8 slot;
    s16 x;
    s16 y;

    frame = &pOam->pOam[pOam->currentAnimationFrame];
    if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
    {
        pOam->currentAnimationFrame = 0;
        pOam->animationDurationCounter = 0;
    }

    pOam->timer++;
    if (pOam->timer == 4)
    {
        pOam->timer = 0;

        switch (pOam->type)
        {
            case 3:
                slot = NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_2, &x, &y);
                if (slot == ARRAY_SIZE(INTRO_DATA.oam))
                {
                    pOam->type = 0;
                    pOam->exists = 0;
                    break;
                }

                pOam->scaling = INTRO_DATA.oam[slot].scaling;
                pOam->affineMode = INTRO_DATA.oam[slot].affineMode;
                pOam->xPosition = x;
                pOam->yPosition = y;
                break;

            case 4:
                slot = NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_3, &x, &y);
                if (slot == ARRAY_SIZE(INTRO_DATA.oam))
                {
                    pOam->type = 0;
                    pOam->exists = 0;
                    break;
                }

                pOam->scaling = INTRO_DATA.oam[slot].scaling;
                pOam->affineMode = INTRO_DATA.oam[slot].affineMode;
                pOam->xPosition = x;
                pOam->yPosition = y;
                break;

            case 5:
                slot = NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP, &x, &y);
                if (slot == ARRAY_SIZE(INTRO_DATA.oam))
                {
                    pOam->type = 0;
                    pOam->exists = 0;
                    break;
                }

                pOam->scaling = INTRO_DATA.oam[slot].scaling;
                pOam->affineMode = INTRO_DATA.oam[slot].affineMode;

                if (INTRO_DATA.oam[slot].stage < 2)
                {
                    pOam->yPosition = y;

                    switch (INTRO_DATA.oam[slot].currentAnimationFrame)
                    {
                        case 0:
                            pOam->xPosition = x + 12;
                            break;
                
                        case 1:
                            pOam->xPosition = x + 10;
                            break;
                
                        case 2:
                            pOam->xPosition = x + 8;
                            break;
                
                        case 3:
                            pOam->xPosition = x + 6;
                            break;
                
                        case 4:
                            pOam->xPosition = x + 5;
                            break;
                
                        case 5:
                            pOam->xPosition = x + 4;
                            break;
                
                        case 6:
                            pOam->xPosition = x + 3;
                            break;
                
                        case 7:
                            pOam->xPosition = x + 2;
                            break;
                
                        case 8:
                            pOam->xPosition = x + 1;
                            break;

                        default:
                            pOam->xPosition = x;
                            break;
                    }
                }
                else
                {
                    pOam->yPosition = y;
                    pOam->xPosition = x;
                }
                break;
        }
    }
}

 /**
 * @brief 90410 | 2c | Processes the ship's thrusters flaring up in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessSamusShipArrivingAtBslThrusterExplosion(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    
    frame = &pOam->pOam[pOam->currentAnimationFrame];
    if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
}

 /**
 * @brief 9043c | 8 | Destroys a placeholder OAM of the arriving at BSL cutscene
 * 
 */
void NewFileIntroArrivingAtBslDestroyOam(struct SpecialCutsceneOam* pOam)
{
    pOam->type = 0;
}

 /**
 * @brief 90444 | 34 | Processes the background scrolling in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessSamusArrivingAtBslBg3Scrolling(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == TWO_THIRD_SECOND)
    {
        pOam->timer = 0;
        
        if (pOam->xPosition < 16)
        {
            pOam->xPosition++;
            gBg3XPosition++;
        }
    }
}

 /**
 * @brief 90478 | 34 | Processes the BG2 scrolling in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessSamusArrivingAtBslBg2Scrolling(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == CONVERT_SECONDS(.5f))
    {
        pOam->timer = 0;
        
        if (pOam->xPosition < 16)
        {
            pOam->xPosition++;
            gBg2XPosition--;
        }
    }
}

 /**
 * @brief 904ac | 19c | Processes the Adam panel in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessAdamPanel(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
            
        if (pOam->yPosition > 128)
        {
            pOam->yPosition -= 8;
            return;
        }
            
        pOam->yPosition = 128;
            
        if (pOam->type == 20)
            SoundPlay(SOUND_20A);
            
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter)
        {
            if (frame[1].timer == 0)
            {
                pOam->animationDurationCounter = 0;
                pOam->stage = 2;
            }
            
            if (pOam->type != 20)
                return;

            if (pOam->currentAnimationFrame == 10)
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_LENS, pOam->xPosition, pOam->yPosition);
        }
        
        if (pOam->type == 20)
        {
            if (pOam->currentAnimationFrame == 11)
            {
                if (pOam->animationDurationCounter == 15)
                {
                    INTRO_DATA.indent = 0;
                    INTRO_DATA.currentLine = 0;
                    INTRO_DATA.currentColumn = 0;
                    INTRO_DATA.pText = sMonologueTextPointers[gLanguage][18];
                }
            }
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->animationDurationCounter = 0;
        pOam->timer++;
        if (pOam->timer == 1)
        {
            pOam->timer = 0;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        pOam->animationDurationCounter = 0;
        
        if (INTRO_DATA.subStage == 4)
        {
            pOam->currentAnimationFrame = 0;
            
            if (pOam->type == 20)
            {
                pOam->pOam = sIntroArrivingAtBslAdamPanelFrameOam_Closing;
                SoundPlay(SOUND_20B);
            }
            else if (pOam->type == 21)
            {
                pOam->pOam = sIntroArrivingAtBslAdamPanelBackgroundOam_Closing;
            }

            pOam->stage = 4;
        }
    }
    else if (pOam->stage == 4)
    {
        if (pOam->currentAnimationFrame == 11 && pOam->animationDurationCounter == 3)
        {
            if (pOam->type == 20)
                SpecialCutsceneDestroyOamOfType(22);
            
            pOam->animationDurationCounter = 0;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        pOam->animationDurationCounter = 0;
        
        if (pOam->yPosition < 192)
        {
            pOam->yPosition += 8;
        }
        else
        {
            if (pOam->type == 20)
                INTRO_DATA.subStage = 5;

            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 90648 | 88 | Processes Adam's lens in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessAdamLens(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    frame = &pOam->pOam[pOam->currentAnimationFrame];

    if (pOam->stage == 0)
    {
        if (pOam->currentAnimationFrame == 3)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroArrivingAtBslAdamLensOam_Glowing;
            pOam->stage = 1;
        }
        
        if (INTRO_DATA.subStage == 4)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroArrivingAtBslAdamLensOam_Closing;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 1)
    {
        if (INTRO_DATA.subStage == 4)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroArrivingAtBslAdamLensOam_Closing;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            pOam->animationDurationCounter = 0;
    }
}

 /**
 * @brief 906d0 | 8c | Processes the Adam text cursor in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessAdamTextCursor(struct SpecialCutsceneOam* pOam)
{
    if (*INTRO_DATA.pText == CHAR_TERMINATOR)
    {
        pOam->xPosition = 290;
    }
    else if (*INTRO_DATA.pText != CHAR_NEW_LINE)
    {
        if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
        {
            pOam->xPosition = 290;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroArrivingAtBslAdamTextCursorOam;
        }
        else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
        {
            pOam->xPosition = SCREEN_X_MIDDLE;
            pOam->yPosition = 154;
            pOam->pOam = sIntroArrivingAtBslMonologueCursorOam;
        }
        else
        {
            pOam->xPosition = INTRO_DATA.currentColumn * 8 + INTRO_DATA.indent + 14;
            pOam->yPosition = INTRO_DATA.currentLine * 8 + 132;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
    }
    else
    {
        pOam->xPosition = INTRO_DATA.currentColumn * 8 + INTRO_DATA.indent + 14;
        pOam->yPosition = INTRO_DATA.currentLine * 8 + 132;
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
    }
}

 /**
 * @brief 9075c | 9c | Processes the BSL preview popup in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessBslPopUp(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    frame = &pOam->pOam[pOam->currentAnimationFrame];
    
    if (pOam->stage == 0)
    {
        if (pOam->currentAnimationFrame == 1 && pOam->animationDurationCounter == 1)
            SoundPlay(SOUND_11C);

        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->animationDurationCounter = 0;
        
        if (INTRO_DATA.subStage == 4)
        {
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroArrivingAtBslBslPopupOam_Closing;
            SoundPlay(SOUND_11D);
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 907f8 | 30 | Processes the monologue cursor in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessMonologueCursor(struct SpecialCutsceneOam* pOam)
{
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        pOam->xPosition = 118;
        pOam->yPosition = INTRO_DATA.currentLine * 8 + 24;
    }
    else
    {
        pOam->xPosition = 260;
    }
}

 /**
 * @brief 90828 | 438 | Spawns an OAM for the intro arriving at BSL cutscene
 * 
 */
u8 NewFileIntroArrivingAtBslSetupOam(IntroArrivingAtBslOamType type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot >= ARRAY_SIZE(INTRO_DATA.oam))
        return ARRAY_SIZE(INTRO_DATA.oam);
    
    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].exists = 1;

    if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.5f);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslSamusShipOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusShipArrivingAtBsl;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslBslOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslPreview;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_1)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.5f);
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslThrustersOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusShipArrivingAtBslThrusters;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_2)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.5f);
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslThrustersOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusShipArrivingAtBslThrusters;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_3)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.5f);
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslThrustersOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusShipArrivingAtBslThrusters;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_EXPLOSION)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslThrusterExplosionOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusShipArrivingAtBslThrusterExplosion;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_BG3_SCROLLER)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusArrivingAtBslBg3Scrolling;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_BG2_SCROLLER)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusArrivingAtBslBg2Scrolling;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_PANEL_FRAME)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslAdamPanelFrameOam_Opening;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessAdamPanel;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_PANEL_BACKGROUND)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslAdamPanelBackgroundOam_Opening;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessAdamPanel;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_LENS)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslAdamLensOam_Opening;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessAdamLens;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_TEXT_CURSOR)
    {
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslAdamTextCursorOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessAdamTextCursor;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_TRAJECTORY)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslShipTrajectoryOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroArrivingAtBslProcessOam_Empty;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_PLANETS_AND_SHIP)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslPlanetsAndShipOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroArrivingAtBslProcessOam_Empty;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL_POPUP)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslBslPopupOam_Opening;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslPopUp;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SCREEN_GLARE)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusCuredScreenGlareOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroArrivingAtBslProcessOam_Empty;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_MONOLOGUE_CURSOR)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslMonologueCursorOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessMonologueCursor;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_PLACEHOLDER)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroArrivingAtBslDestroyOam;
    }

    return slot;
}

 /**
 * @brief 90c60 | 9c | V-blank for the arriving at BSL cutscene
 * 
 */
void NewFileIntroArrivingAtBslVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    
    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG0HOFS, gBg0XPosition);
    WRITE_16(REG_BG0VOFS, gBg0YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
    
    SpecialCutsceneUpdateTextTilesFade();
}

 /**
 * @brief 90cfc | 60 | Returns slot, X and Y position of a new file intro OAM
 * 
 */
u8 NewFileIntroGetPositionAndSlotOfOamByType(IntroArrivingAtBslOamType type, s16* pXPosition, s16* pYPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == type)
        {
            *pXPosition = INTRO_DATA.oam[slot].xPosition;
            *pYPosition = INTRO_DATA.oam[slot].yPosition;
        
            return slot;
        }
    }

    // Default values if not found
    *pXPosition = 300;
    *pYPosition = 200;
        
    return ARRAY_SIZE(INTRO_DATA.oam);
}

 /**
 * @brief 90d5c | 4 | Empty OAM handler function
 * 
 */
void NewFileIntroArrivingAtBslProcessOam_Empty(struct SpecialCutsceneOam* pOam)
{
    return;
}

 /**
 * @brief 90d60 | 1f4 | Setup for the landing on BSL cutscene
 * 
 */
void NewFileIntroLandingOnBslInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(SpecialCutsceneLoadingVblank);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sIntroLandingOnBslObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroLandingOnBslObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroLandingOnBslBgGfx, VRAM_BASE);
    LZ77UncompVram(sIntroLandingOnBslHangarTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroLandingOnBslSpaceTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroLandingOnBslBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    gBg2XPosition = 0;
    gBg2YPosition = 40;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 40);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));

    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_BG_SCROLLER, SCREEN_X_MIDDLE, 0, FALSE);
    NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_LANDING_LIGHTS, 128, 100 - gBg2YPosition, TRUE);
    NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR, 128, 72 - gBg2YPosition, FALSE);
    NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR_LIGHT, 0, 0, FALSE);
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroLandingOnBslVblank);
}

 /**
 * @brief 90f54 | 128 | Processes the landing on BSL cutscene
 * 
 */
boolu32 NewFileIntroLandingOnBslProcess(void)
{
    boolu32 finished;

    finished = FALSE;

    APPLY_DELTA_TIME_INC(INTRO_DATA.timer);

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (gWrittenToBldy)
            {
                gWrittenToBldy--;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
                PlayMusic(MUSIC_MAIN_DECK_AMBIENCE, 13);
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (gBg2YPosition == 0)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1 + 1.f / 6))
            {
                INTRO_DATA.timer = 0;
                NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_SHIP, 128, 50, FALSE);
                INTRO_DATA.subStage = 3;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 3:
            INTRO_DATA.timer = 0;
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 4:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 5;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 5:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 30))
            {
                INTRO_DATA.timer = 0;
    
                if (gWrittenToBldy < BLDY_MAX_VALUE)
                    gWrittenToBldy++;
                else
                    finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 9107c | 88 | Main handler for the landing on BSL cutscene
 * 
 */
boolu32 NewFileIntroLandingOnBsl(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroLandingOnBslInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();

            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;
        
        case 2:
            if (NewFileIntroLandingOnBslProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;
        
        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 91104 | 74 | Handles the background scrolling in the landing on BSL cutscene
 * 
 */
void NewFileIntroProcessLandingOnBslScroll(struct SpecialCutsceneOam* pOam)
{
    INTRO_DATA.bg2YVelocity = 0;

    APPLY_DELTA_TIME_INC(pOam->timer);

    if (pOam->stage == 0)
    {
        pOam->yPosition = gBg2YPosition;
        pOam->timer = 0;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        INTRO_DATA.bg2YVelocity = 0;

        if (pOam->timer == 4)
        {
            pOam->timer = 0;

            if (pOam->yPosition > 0)
            {
                INTRO_DATA.bg2YVelocity = -1;
                pOam->yPosition--;
                gBg2YPosition = pOam->yPosition;
            }
            else
            {
                INTRO_DATA.bg2YVelocity = 0;
                pOam->type = 0;
            }
        }
    }
    else
    {
        pOam->timer = 0;
    }
}

 /**
 * @brief 91178 | a4 | Processes the hangar door in the intro
 * 
 */
void NewFileIntroProcessBslDoor(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_PALETTE_CHANGER, 0, 0, FALSE);
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->pOam = sIntroBslHangarDoorOam_Opening;
        SoundPlay_3b1c(SOUND_246);
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR_TOP, pOam->xPosition, pOam->yPosition, TRUE);
        NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR_BOTTOM, pOam->xPosition, pOam->yPosition, TRUE);
        pOam->type = 0;
        pOam->exists = 0;
    }
    
    pOam->yPosition -= INTRO_DATA.bg2YVelocity;
}

 /**
 * @brief 9121c | 7c | Processes the hangar door lights in the intro
 * 
 */
void NewFileIntroProcessBslDoorLight(struct SpecialCutsceneOam* pOam)
{
    pOam->unk_A++;
    if (pOam->unk_A == 8)
    {
        pOam->unk_A = 0;
        INTRO_DATA.paletteUpdate1 = 1;
        
        if (INTRO_DATA.paletteFrame1 < 5)
            INTRO_DATA.paletteFrame1++;
        else
            INTRO_DATA.paletteFrame1 = 0;
    }

    APPLY_DELTA_TIME_INC(pOam->timer);
    if (pOam->timer == 8)
    {
        pOam->timer = 0;
        INTRO_DATA.paletteUpdate2 = 1;
        
        if (INTRO_DATA.paletteFrame2 < 7)
            INTRO_DATA.paletteFrame2++;
        else
            INTRO_DATA.paletteFrame2 = 0;
    }
}

 /**
 * @brief 91298 | e8 | Processes the top half of the BSL hangar door in the intro
 * 
 */
void NewFileIntroProcessBslDoorTop(struct SpecialCutsceneOam* pOam)
{
    s16 x;
    s16 y;

    pOam->unk_A++;
    
    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        if (pOam->unk_A == 8)
        {
            pOam->unk_A = 0;
            
            if (pOam->spawnY < 54)
            {
                pOam->spawnY++;
                pOam->yPosition--;
            }
            else
            {
                pOam->stage = 2;
            }
        }
    }
    else if (pOam->stage == 2)
    {
        // Bug: Checks for a nonexistent OAM
        NewFileIntroGetPositionAndSlotOfOamByType_2(INTRO_LANDING_ON_BSL_OAM_TYPE_SHIP_UNUSED, &x, &y);

        if (y > 90) // This is always true because the default Y for nonexistent OAMs is 200
        {
            pOam->unk_A = 0;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        if (pOam->unk_A == 8)
        {
            pOam->unk_A = 0;
            
            if (pOam->spawnY > 0)
            {
                pOam->spawnY--;
                if (pOam->spawnY == 37)
                    NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_SHIP_ARMS_EXTENDING, 0, 0, TRUE);

                pOam->yPosition++;
            }
            else
            {
                // This branch appears to never get hit
                pOam->stage = 4;
                NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR_UNUSED, pOam->xPosition, pOam->yPosition, TRUE);
            }
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
    
    pOam->yPosition -= INTRO_DATA.bg2YVelocity;
}

 /**
 * @brief 91380 | c4 | Processes the bottom half of the BSL hangar door in the intro
 * 
 */
void NewFileIntroProcessBslDoorBottom(struct SpecialCutsceneOam* pOam)
{
    s16 x;
    s16 y;

    pOam->unk_A++;
    
    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        if (pOam->unk_A == 8)
        {
            pOam->unk_A = 0;
            
            if (pOam->spawnY < 54)
            {
                pOam->spawnY++;
                pOam->yPosition++;
            }
            else
            {
                pOam->stage = 2;
            }
        }
    }
    else if (pOam->stage == 2)
    {
        // Bug: Checks for a nonexistent OAM
        NewFileIntroGetPositionAndSlotOfOamByType_2(INTRO_LANDING_ON_BSL_OAM_TYPE_SHIP_UNUSED, &x, &y);
        
        if (y > 90) // This is always true because the default Y for nonexistent OAMs is 200
        {
            pOam->unk_A = 0;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        if (pOam->unk_A == 8)
        {
            pOam->unk_A = 0;
            
            if (pOam->spawnY > 0)
            {
                pOam->spawnY--;
                pOam->yPosition--;
            }
            else
            {
                pOam->stage = 4;
            }
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->type = 0;
        pOam->exists = 0;
    }
    
    pOam->yPosition -= INTRO_DATA.bg2YVelocity;
}

 /**
 * @brief 91444 | 64 | Processes the intro hangar palette changing effect
 * 
 */
void NewFileIntroProcessHangarPalettes(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        INTRO_DATA.paletteUpdate3 = 0;
        INTRO_DATA.paletteFrame3 = 5;
        pOam->stage = 1;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 75)
    {
        pOam->unk_A = 0;
        INTRO_DATA.paletteUpdate3 = 1;
        
        if (INTRO_DATA.paletteFrame3 < 9)
            INTRO_DATA.paletteFrame3++;
        else
            pOam->type = 0;
    }
}

 /**
 * @brief 914a8 | 334 | Processes Samus' ship in the landing on BSL cutscene (unused)
 * 
 */
void NewFileIntroProcessShipLanding_Unused(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->unk_A++;
    
    if (pOam->stage == 0)
    {
        if (NewFileIntroGetPositionAndSlotOfOamByType_2(INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR_TOP, &x, &y) != ARRAY_SIZE(INTRO_DATA.oam))
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        NewFileIntroGetPositionAndSlotOfOamByType_2(INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR_TOP, &x, &y);

        pOam->yPosition = (pOam->unk_A >> 2) + pOam->spawnY;
        if (pOam->yPosition - y > 8)
        {
            INTRO_DATA.paletteUpdate4 = 1;
            INTRO_DATA.paletteFrame4 = 1;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->unk_A = 0;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        APPLY_DELTA_TIME_INC(pOam->timer);

        if (INTRO_DATA.paletteFrame4 < 7)
        {
            pOam->yPosition = (pOam->unk_A >> 2) + pOam->spawnY;

            if (pOam->timer == CONVERT_SECONDS(1.f / 5))
            {
                pOam->timer = 0;
                INTRO_DATA.paletteUpdate4 = 1;
                INTRO_DATA.paletteFrame4++;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->unk_A = 0;
            }
        }
        else if (INTRO_DATA.paletteFrame4 == 7)
        {
            if (pOam->unk_A == 2)
            {
                pOam->unk_A = 0;
                pOam->yPosition++;
            }

            if (pOam->timer == CONVERT_SECONDS(1.f / 5))
            {
                pOam->timer = 0;
                pOam->pOam = sIntroShipLandingOam_Unused2;
                INTRO_DATA.paletteUpdate4 = 1;
                INTRO_DATA.paletteFrame4++;
            }
        }
        else if (INTRO_DATA.paletteFrame4 == 8)
        {
            if (pOam->unk_A == 2)
            {
                pOam->unk_A = 0;
                pOam->yPosition++;
            }

            if (pOam->timer == CONVERT_SECONDS(1.f / 6))
            {
                pOam->timer = 0;
                pOam->priority = 1;
                INTRO_DATA.paletteUpdate4 = 1;
                INTRO_DATA.paletteFrame4++;
            }
        }
        else if (INTRO_DATA.paletteFrame4 < 14)
        {
            if (pOam->unk_A == 2)
            {
                pOam->unk_A = 0;
                pOam->yPosition++;
            }

            if (pOam->timer == CONVERT_SECONDS(2.f / 15))
            {
                pOam->timer = 0;
                INTRO_DATA.paletteUpdate4 = 1;
                INTRO_DATA.paletteFrame4++;
            }
        }
        else if (INTRO_DATA.paletteFrame4 == 14)
        {
            if (pOam->unk_A == 2)
            {
                pOam->unk_A = 0;
                pOam->yPosition++;
            }

            if (pOam->timer == CONVERT_SECONDS(2.f / 15))
            {
                pOam->timer = 0;
                pOam->pOam = sIntroShipLandingOam;
                INTRO_DATA.paletteUpdate4 = 1;
                INTRO_DATA.paletteFrame4++;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->unk_A = 0;
                pOam->stage = 3;
            }
        }

        if (pOam->yPosition > 80)
            pOam->yPosition = 80;
    }
    else if (pOam->stage == 3)
    {
        if (pOam->unk_A == 20)
        {
            pOam->unk_A = 0;
            pOam->stage = 4;
            NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_SMOKE, pOam->xPosition, 150, FALSE);
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->unk_8++;
        if (pOam->unk_8 > 255)
            pOam->unk_8 -= 256;
        
        pOam->unk_A = 0;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->affineMode = OAM_AFFINE_MODE_NORMAL;
        pOam->pOam = sIntroShipLandingOam_Hovering;
        pOam->stage = 5;
    }
    else if (pOam->stage == 5)
    {
        pOam->yPosition = (pOam->unk_A >> 4) + pOam->spawnY;
        if (pOam->yPosition > 90 && pOam->currentAnimationFrame == 0 && pOam->animationDurationCounter == 1)
        {
            pOam->pOam = sIntroShipLandingOam_ExtendingLandingGear;
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 6;
        }
    }
    else if (pOam->stage == 6)
    {
        pOam->yPosition = (pOam->unk_A >> 4) + pOam->spawnY;

        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroShipLandingOam_ExtendedLandingGearIdle;
            pOam->stage = 7;
        }
    }
    else if (pOam->stage == 7)
    {
        pOam->yPosition = (pOam->unk_A >> 4) + pOam->spawnY;
        if (pOam->yPosition > 103)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroShipLandingOam_ExtendedLandingGearHovering;
            pOam->stage = 8;
        }
    }
    else if (pOam->stage == 8)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroShipLandingOam_ExtendedLandingGearIdle;
            INTRO_DATA.subStage = 4;
            pOam->stage = 9;
        }
    }
}

 /**
 * @brief 917dc | cc | Processes the smoke in the landing on BSL cutscene
 * 
 */
void NewFileIntroProcessShipLandingSmoke(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    if (pOam->stage == 0)
    {
        NewFileIntroGetPositionAndSlotOfOamByType_2(INTRO_LANDING_ON_BSL_OAM_TYPE_SHIP, &x, &y);
        pOam->xPosition = x;
        pOam->yPosition = 150;

        if (y > 100)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->unk_A = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroShipLandingSmokeOam_2;
                pOam->stage = 1;
            }
        }
    }
    else if (pOam->stage == 1)
    {
        NewFileIntroGetPositionAndSlotOfOamByType_2(INTRO_LANDING_ON_BSL_OAM_TYPE_SHIP, &x, &y);
        pOam->xPosition = x;
        pOam->yPosition = 150;

        if (y > 103)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 2;
            }
        }
    }
    else if (pOam->stage == 2)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->exists = 0;
        }
    }
}

 /**
 * @brief 918a8 | 44 | Processes the hangar door closing in the intro (unused)
 * 
 */
void NewFileIntroProcessBslDoorClosing_Unused(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroBslHangarDoorOam_Closed;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->animationDurationCounter = 0;
    }
}

 /**
 * @brief 918ec | 64 | Processes the ship arms extending in the landing on BSL cutscene
 * 
 */
void NewFileIntroProcessExtendingShipArms(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        INTRO_DATA.paletteUpdate3 = 0;
        INTRO_DATA.paletteFrame3 = 9;
        pOam->stage = 1;
    }
    
    pOam->unk_A++;
    if (pOam->unk_A == 75)
    {
        pOam->unk_A = 0;
        INTRO_DATA.paletteUpdate3 = 1;
        
        if (INTRO_DATA.paletteFrame3 > 6)
            INTRO_DATA.paletteFrame3--;
        else
            pOam->type = 0;
    }
}

 /**
 * @brief 91950 | 1c | Processes the landing lights in the landing on BSL cutscene
 * 
 */
void NewFileIntroProcessLandingLights(struct SpecialCutsceneOam* pOam)
{
    pOam->yPosition -= INTRO_DATA.bg2YVelocity;
}

 /**
 * @brief 9196c | 208 | Processes Samus' ship in the landing on BSL cutscene
 * 
 */
void NewFileIntroProcessShipLanding(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    pOam->unk_A++;
    
    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 2;
    }
    else if (pOam->stage == 1)
    {
        pOam->yPosition = (pOam->unk_A >> 2) + pOam->spawnY;
        pOam->unk_A = 0;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 2;
    }
    else if (pOam->stage == 2)
    {
        if (pOam->scaling < Q_8_8(1))
        {
            pOam->scaling++;
            if (pOam->scaling >= Q_8_8(1))
            {
                pOam->scaling = Q_8_8(1);
                pOam->affineMode = OAM_AFFINE_MODE_NORMAL;
            }
            else if (pOam->scaling >= Q_8_8(.75f))
            {
                pOam->priority = 1;
            }
        }

        pOam->yPosition = (pOam->unk_A >> 2) + pOam->spawnY;
        if (pOam->yPosition > SCREEN_Y_MIDDLE)
        {
            pOam->yPosition = SCREEN_Y_MIDDLE;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = SCREEN_Y_MIDDLE;
            pOam->unk_A = 0;

            if (pOam->scaling == Q_8_8(1))
            {
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroShipLandingOam_Idle;
                pOam->stage = 3;
            }
        }
    }
    else if (pOam->stage == 3)
    {
        if (pOam->unk_A > 4)
        {
            pOam->unk_A = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroShipLandingOam_Hovering;
            pOam->stage = 4;
            NewFileIntroLandingOnBslSetupOam(INTRO_LANDING_ON_BSL_OAM_TYPE_SMOKE, pOam->xPosition, 150, FALSE);
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->unk_A = 0;
        
        if (pOam->currentAnimationFrame == 6)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroShipLandingOam_Idle;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        if (pOam->unk_A > 10)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 6;
        }
    }
    else if (pOam->stage == 6)
    {
        pOam->yPosition = (pOam->unk_A >> 3) + pOam->spawnY;
        if (pOam->yPosition > 88)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroShipLandingOam_ExtendingLandingGear;
            pOam->stage = 7;
        }
    }
    else if (pOam->stage == 7)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            pOam->animationDurationCounter = 0;

        pOam->yPosition = (pOam->unk_A >> 3) + pOam->spawnY;
        if (pOam->yPosition > 103)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroShipLandingOam_ExtendedLandingGearHovering;
            pOam->stage = 8;
        }
    }
    else if (pOam->stage == 8)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroShipLandingOam_ExtendedLandingGearIdle;
            pOam->stage = 9;
            INTRO_DATA.subStage = 4;
        }
    }

    pOam->yPosition -= INTRO_DATA.bg2YVelocity;
}

 /**
 * @brief 91b74 | 388 | Spawns a new OAM for the landing on BSL cutscene
 * 
 */
u8 NewFileIntroLandingOnBslSetupOam(IntroLandingOnBslOamType type, s16 xPosition, s16 yPosition, boolu8 descendingSearch)
{
    s8 slot;

    if (!descendingSearch)
    {
        for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot >= ARRAY_SIZE(INTRO_DATA.oam))
            return ARRAY_SIZE(INTRO_DATA.oam);
    }
    else
    {
        for (slot = ARRAY_SIZE(INTRO_DATA.oam) - 1; slot >= 0; slot--)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot < 0)
            return ARRAY_SIZE(INTRO_DATA.oam);
    }

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].exists = 1;

    if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_BG_SCROLLER)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessLandingOnBslScroll;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroBslHangarDoorOam_Closed;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslDoor;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR_LIGHT)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslDoorLight;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR_TOP)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroBslHangarDoorOam_Top;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslDoorTop;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR_BOTTOM)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroBslHangarDoorOam_Bottom;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslDoorBottom;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_PALETTE_CHANGER)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessHangarPalettes;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_SHIP_UNUSED)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_AFFINE;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroShipLandingOam_Unused1;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessShipLanding_Unused;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_SMOKE)
    {
        INTRO_DATA.oam[slot].pOam = sIntroShipLandingSmokeOam_1;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessShipLandingSmoke;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_DOOR_UNUSED)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroBslHangarDoorOam_Closing;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslDoorClosing_Unused;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_SHIP_ARMS_EXTENDING)
    {
        INTRO_DATA.oam[slot].exists = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessExtendingShipArms;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_LANDING_LIGHTS)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroBslLandingLightsOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessLandingLights;
    }
    else if (type == INTRO_LANDING_ON_BSL_OAM_TYPE_SHIP)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.f / 128);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_AFFINE;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroShipLandingOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessShipLanding;
    }

    return slot;
}

 /**
 * @brief 91efc | 13c | V-blank for the landing on BSL cutscene
 * 
 */
void NewFileIntroLandingOnBslVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    
    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);

    if (INTRO_DATA.paletteUpdate1 == 1)
    {
        INTRO_DATA.paletteUpdate1 = 0;
        DMA3_COPY_32(&sIntroPal_5ffb08[INTRO_DATA.paletteFrame1 * PAL_ROW], PALRAM_OBJ + 10 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
    }

    if (INTRO_DATA.paletteUpdate2 == 1)
    {
        INTRO_DATA.paletteUpdate2 = 0;
        DMA3_COPY_32(&sIntroPal_5ff908[INTRO_DATA.paletteFrame2 * PAL_ROW], PALRAM_OBJ + 8 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
    }

    if (INTRO_DATA.paletteUpdate3 == 1)
    {
        INTRO_DATA.paletteUpdate3 = 0;
        DMA3_COPY_32(&sIntroPal_5ffb08[INTRO_DATA.paletteFrame3 * PAL_ROW], PALRAM_OBJ + 9 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
        DMA3_COPY_32(&sIntroPal_5ffb08[INTRO_DATA.paletteFrame3 * PAL_ROW], PALRAM_BASE + 11 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));
    }
}

 /**
 * @brief 92038 | 60 | Returns slot, X and Y position of a new file intro OAM
 * 
 */
u8 NewFileIntroGetPositionAndSlotOfOamByType_2(IntroLandingOnBslOamType type, s16* pXPosition, s16* pYPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == type)
        {
            *pXPosition = INTRO_DATA.oam[slot].xPosition;
            *pYPosition = INTRO_DATA.oam[slot].yPosition;
        
            return slot;
        }
    }

    // Default values if not found
    *pXPosition = 300;
    *pYPosition = 200;
        
    return ARRAY_SIZE(INTRO_DATA.oam);
}

 /**
 * @brief 92098 | 4 | Empty function
 * 
 */
void NewFileIntroLandingOnBsl_Empty(void)
{
    return;
}

