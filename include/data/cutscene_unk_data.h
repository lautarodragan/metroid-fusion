#ifndef CUTSCENE_UNK_DATA_H
#define CUTSCENE_UNK_DATA_H

#include "types.h"
#include "oam.h"

// Data used by the intro and ending cutscenes, most of it not identified yet

extern const u32* sIntroSamusSittingBgGfxPointers[5];

extern const u8 sIntroUnk_658be0[];
extern const u8 sIntroUnk_6591e4[];
extern const u8 sIntroUnk_6593e4[];
extern const u8 sIntroUnk_6599a4[];
extern const u8 sIntroUnk_65c268[];
extern const u8 sIntroUnk_6101b8[];

// Defined as raw bytes in new_file_intro_data.c, but these are OAM frame data
extern const struct FrameData sIntroUnk_60ac08[];
extern const struct FrameData sIntroUnk_60ac18[];
extern const struct FrameData sIntroUnk_60ac28[];
extern const struct FrameData sIntroUnk_60ac38[];
extern const struct FrameData sIntroUnk_60acd0[];
extern const struct FrameData sIntroUnk_60acf8[];
extern const struct FrameData sIntroUnk_60ad08[];
extern const struct FrameData sIntroUnk_60ad18[];
extern const struct FrameData sIntroUnk_60ad28[];
extern const struct FrameData sIntroUnk_60ad48[];
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

// Defined as raw bytes in new_file_intro.c, but these are tables of pointers to compressed graphics
extern const u32* sIntroUnk_79c448[];
extern const u32* sIntroUnk_79c45c[];

#endif /* CUTSCENE_UNK_DATA_H */
