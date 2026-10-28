#ifndef CUTSCENE_UNK_DATA_H
#define CUTSCENE_UNK_DATA_H

#include "types.h"
#include "oam.h"

// Data used by the intro and ending cutscenes, most of it not identified yet

extern const u32* sIntroSamusSittingBgGfxPointers[5];
extern u16** sMonologueTextPointers[];

extern const u8 sIntroUnk_658be0[];
extern const u8 sIntroUnk_6591e4[];
extern const u8 sIntroUnk_6593e4[];
extern const u8 sIntroUnk_6599a4[];
extern const u8 sIntroUnk_65c268[];
extern const u8 sIntroUnk_6101b8[];

extern const u8 sSr388CollisionUnk_6238f4[];
extern const u8 sSr388CollisionUnk_62b5f4[];
extern const u8 sSr388CollisionUnk_636c38[];
extern const u8 sSr388CollisionUnk_637038[];
extern const u8 sSr388CollisionUnk_638c14[];
extern const u8 sSr388CollisionUnk_639bc4[];

extern const u8 sEndingUnk_6131c8[];
extern const u8 sEndingUnk_6150e8[];
extern const u8 sEndingUnk_6186a4[];
extern const u8 sEndingUnk_61b89c[];
extern const u8 sEndingUnk_6217a8[];
extern const u8 sEndingUnk_626738[];
extern const u8 sEndingUnk_636438[];
extern const u8 sEndingUnk_636638[];
extern const u8 sEndingUnk_636838[];
extern const u8 sEndingUnk_637238[];
extern const u8 sEndingUnk_6377f8[];
extern const u8 sEndingUnk_637db8[];
extern const u8 sEndingUnk_638654[];
extern const u8 sEndingUnk_636e38[];
extern const u8 sEndingUnk_63929c[];
extern const u8 sEndingUnk_6395b8[];

// Defined as raw bytes in new_file_intro_data.c, but these are OAM frame data
extern const struct FrameData sIntroUnk_60ac08[];
extern const struct FrameData sIntroUnk_60ac18[];
extern const struct FrameData sIntroUnk_60ac28[];
extern const struct FrameData sIntroUnk_60ac38[];
extern const struct FrameData sIntroUnk_60ac98[];
extern const struct FrameData sIntroUnk_60acd0[];
extern const struct FrameData sIntroUnk_60acf8[];
extern const struct FrameData sIntroUnk_60ad08[];
extern const struct FrameData sIntroUnk_60ad18[];
extern const struct FrameData sIntroUnk_60ad28[];
extern const struct FrameData sIntroUnk_60ad48[];
extern const struct FrameData sIntroUnk_60af10[];
extern const struct FrameData sIntroUnk_65bb38[];
extern const struct FrameData sIntroUnk_65bd00[];
extern const struct FrameData sIntroUnk_65bd48[];
extern const struct FrameData sIntroUnk_65bd60[];
extern const struct FrameData sIntroUnk_65be00[];
extern const struct FrameData sIntroUnk_65bf10[];
extern const struct FrameData sIntroUnk_65c0d0[];
extern const struct FrameData sIntroUnk_65c128[];
extern const struct FrameData sIntroUnk_65c180[];
extern const struct FrameData sIntroUnk_65c1d8[];
extern const struct FrameData sIntroUnk_65c230[];
extern const struct FrameData sSr388CollisionUnk_6362b8[];
extern const struct FrameData sSr388CollisionUnk_636020[];
extern const struct FrameData sSr388CollisionUnk_636038[];
extern const struct FrameData sSr388CollisionUnk_636050[];
extern const struct FrameData sEndingUnk_636288[];
extern const struct FrameData sEndingUnk_6362a0[];
extern const struct FrameData sEndingUnk_6363a0[];
extern const struct FrameData sEndingUnk_6363b8[];

// Defined as raw bytes in new_file_intro_data.c, but this is palette data
extern const u16 sSr388CollisionUnk_636a38[];

// Defined as raw bytes in new_file_intro.c, but this is a table of pointers to OAM frame data
extern const struct FrameData* sIntroUnk_79c394[];

// Defined as raw bytes in new_file_intro.c, but these are tables of pointers to compressed graphics
extern const u32* sIntroUnk_79c448[];
extern const u32* sIntroUnk_79c45c[];

#endif /* CUTSCENE_UNK_DATA_H */
