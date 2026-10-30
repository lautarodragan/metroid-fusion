#include "macros.h"
#include "oam.h"

#include "gba/memory.h"

#include "constants/text.h"

#include "data/new_file_intro_data.h"

static const u16 sOamFrame_597708[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 128, 4, 0),
};

static const u16 sOamFrame_597710[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 129, 4, 0),
};

static const u16 sOamFrame_597718[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 130, 4, 0),
};

static const u16 sOamFrame_597720[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 131, 4, 0),
};

static const u16 sOamFrame_597728[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0, 8, 0),
};

static const u16 sOamFrame_597730[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 4, 8, 0),
};

static const u16 sOamFrame_597738[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 8, 8, 0),
};

static const u16 sOamFrame_597740[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 12, 8, 0),
};

static const u16 sOamFrame_597748[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 24, 8, 0),
};

static const u16 sOamFrame_597750[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 140, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_59775e[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_597766[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 142, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_597774[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-20, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 140, 3, 0),
    OAM_ENTRY(3, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 140, 3, 0),
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_597788[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_597790[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-20, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 142, 3, 0),
    OAM_ENTRY(3, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 142, 3, 0),
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_5977a4[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(0, -24, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_5977b2[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-32, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-32, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
};

static const u16 sOamFrame_5977d8[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-8, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(16, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
};

static const u16 sOamFrame_5977f2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-64, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(-64, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
};

static const u16 sOamFrame_597800[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597856[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_5978ac[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597902[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597958[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_5979ae[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597a04[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597a5a[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597ab0[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597b06[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597b5c[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u16 sOamFrame_597bb2[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(0, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_32x64, OAM_NO_FLIP, 746, 0, 0),
    OAM_ENTRY(-16, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 846, 0, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 910, 0, 0),
    OAM_ENTRY(0, 40, OAM_DIMS_16x8, OAM_NO_FLIP, 974, 0, 0),
    OAM_ENTRY(-62, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 738, 0, 0),
    OAM_ENTRY(-30, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 0, 0),
    OAM_ENTRY(-14, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 872, 0, 0),
    OAM_ENTRY(-62, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 936, 0, 0),
    OAM_ENTRY(-46, 24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 0, 0),
    OAM_ENTRY(2, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-67, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 832, 0, 0),
    OAM_ENTRY(-67, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 0, 0),
};

static const u8 sPadding_597c08[2] = {0, 0};

static const u16 sOamFrame_597c0a[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 332, 3, 0),
};

static const u16 sOamFrame_597c12[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 333, 3, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 333, 3, 0),
    OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 333, 3, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_XY_FLIP, 333, 3, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 332, 3, 0),
};

static const u16 sOamFrame_597c32[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 333, 3, 0),
    OAM_ENTRY(-12, -8, OAM_DIMS_8x8, OAM_Y_FLIP, 333, 3, 0),
    OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_X_FLIP, 333, 3, 0),
    OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_XY_FLIP, 333, 3, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 256, 3, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 256, 3, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 256, 3, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 256, 3, 0),
    OAM_ENTRY(4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 332, 3, 0),
};

static const u16 sOamFrame_597c6a[OAM_DATA_SIZE(12)] = {
    12,
    OAM_ENTRY(0, -20, OAM_DIMS_8x8, OAM_NO_FLIP, 333, 3, 0),
    OAM_ENTRY(0, -12, OAM_DIMS_8x8, OAM_Y_FLIP, 333, 3, 0),
    OAM_ENTRY(8, -20, OAM_DIMS_8x8, OAM_X_FLIP, 333, 3, 0),
    OAM_ENTRY(8, -12, OAM_DIMS_8x8, OAM_XY_FLIP, 333, 3, 0),
    OAM_ENTRY(-20, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 256, 3, 0),
    OAM_ENTRY(-20, -8, OAM_DIMS_16x16, OAM_Y_FLIP, 256, 3, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 256, 3, 0),
    OAM_ENTRY(-4, -8, OAM_DIMS_16x16, OAM_XY_FLIP, 256, 3, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 258, 3, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 258, 3, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 258, 3, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 258, 3, 0),
};

static const u16 sOamFrame_597cb4[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(-4, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 3, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 256, 3, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_Y_FLIP, 256, 3, 0),
    OAM_ENTRY(8, -28, OAM_DIMS_16x16, OAM_X_FLIP, 256, 3, 0),
    OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 256, 3, 0),
    OAM_ENTRY(-20, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 258, 3, 0),
    OAM_ENTRY(-20, -8, OAM_DIMS_16x16, OAM_Y_FLIP, 258, 3, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 258, 3, 0),
    OAM_ENTRY(-4, -8, OAM_DIMS_16x16, OAM_XY_FLIP, 258, 3, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 260, 3, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 260, 3, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 260, 3, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 260, 3, 0),
};

static const u16 sOamFrame_597d04[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(-16, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 264, 3, 0),
    OAM_ENTRY(-4, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 274, 3, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 258, 3, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_Y_FLIP, 258, 3, 0),
    OAM_ENTRY(8, -28, OAM_DIMS_16x16, OAM_X_FLIP, 258, 3, 0),
    OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 258, 3, 0),
    OAM_ENTRY(-20, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 260, 3, 0),
    OAM_ENTRY(-20, -8, OAM_DIMS_16x16, OAM_Y_FLIP, 260, 3, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 260, 3, 0),
    OAM_ENTRY(-4, -8, OAM_DIMS_16x16, OAM_XY_FLIP, 260, 3, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 262, 3, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 262, 3, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 262, 3, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 262, 3, 0),
};

static const u16 sOamFrame_597d5a[OAM_DATA_SIZE(12)] = {
    12,
    OAM_ENTRY(-16, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 3, 0),
    OAM_ENTRY(0, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 264, 3, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 3, 0),
    OAM_ENTRY(-4, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 276, 3, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 260, 3, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_Y_FLIP, 260, 3, 0),
    OAM_ENTRY(8, -28, OAM_DIMS_16x16, OAM_X_FLIP, 260, 3, 0),
    OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 260, 3, 0),
    OAM_ENTRY(-20, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 262, 3, 0),
    OAM_ENTRY(-20, -8, OAM_DIMS_16x16, OAM_Y_FLIP, 262, 3, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 262, 3, 0),
    OAM_ENTRY(-4, -8, OAM_DIMS_16x16, OAM_XY_FLIP, 262, 3, 0),
};

static const u16 sOamFrame_597da4[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-8, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 264, 3, 0),
    OAM_ENTRY(-16, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 268, 3, 0),
    OAM_ENTRY(0, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 3, 0),
    OAM_ENTRY(-8, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 274, 3, 0),
    OAM_ENTRY(-4, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 278, 3, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 262, 3, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_Y_FLIP, 262, 3, 0),
    OAM_ENTRY(8, -28, OAM_DIMS_16x16, OAM_X_FLIP, 262, 3, 0),
    OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 262, 3, 0),
};

static const u16 sOamFrame_597ddc[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-8, -42, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 3, 0),
    OAM_ENTRY(-16, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 270, 3, 0),
    OAM_ENTRY(0, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 268, 3, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 276, 3, 0),
};

static const u16 sOamFrame_597df6[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-8, -44, OAM_DIMS_16x16, OAM_NO_FLIP, 268, 3, 0),
    OAM_ENTRY(0, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 270, 3, 0),
    OAM_ENTRY(-8, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 278, 3, 0),
};

static const u16 sOamFrame_597e0a[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -46, OAM_DIMS_16x16, OAM_NO_FLIP, 270, 3, 0),
};

static const u16 sOamFrame_597e12[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 140, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 1, 0),
};

static const u16 sOamFrame_597e20[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 1, 0),
};

static const u16 sOamFrame_597e28[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 142, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 1, 0),
};

static const u16 sOamFrame_597e36[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 140, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 512, 1, 0),
};

static const u16 sOamFrame_597e44[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 512, 1, 0),
};

static const u16 sOamFrame_597e4c[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 142, 3, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 512, 1, 0),
};

static const u16 sOamFrame_597e5a[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(14, -22, OAM_DIMS_32x32, OAM_NO_FLIP, 512, 2, 0),
    OAM_ENTRY(46, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 580, 2, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_597e6e[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(14, -22, OAM_DIMS_32x32, OAM_NO_FLIP, 517, 2, 0),
    OAM_ENTRY(46, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 585, 2, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_597e82[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(13, -21, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 2, 0),
    OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 132, 1, 0),
};

static const u16 sOamFrame_597e90[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-30, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 526, 2, 0),
    OAM_ENTRY(-2, -27, OAM_DIMS_32x32, OAM_X_FLIP, 526, 2, 0),
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_597ea4[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_597eac[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-30, -25, OAM_DIMS_32x32, OAM_NO_FLIP, 530, 2, 0),
    OAM_ENTRY(-2, -25, OAM_DIMS_32x32, OAM_X_FLIP, 530, 2, 0),
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 16, 1, 0),
};

const struct FrameData sOam_597ec0[2] = {
    [0] = {
        .pFrame = sOamFrame_597708,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597ed0[2] = {
    [0] = {
        .pFrame = sOamFrame_597710,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597ee0[2] = {
    [0] = {
        .pFrame = sOamFrame_597718,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597ef0[2] = {
    [0] = {
        .pFrame = sOamFrame_597720,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f00[2] = {
    [0] = {
            .pFrame = sOamFrame_597728,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f10[2] = {
    [0] = {
            .pFrame = sOamFrame_597730,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f20[2] = {
    [0] = {
            .pFrame = sOamFrame_597738,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f30[2] = {
    [0] = {
            .pFrame = sOamFrame_597740,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f40[2] = {
    [0] = {
            .pFrame = sOamFrame_597748,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f50[7] = {
    [0] = {
            .pFrame = sOamFrame_597e5a,
            .timer = 1
    },
    [1] = {
            .pFrame = sOamFrame_59775e,
            .timer = 1
    },
    [2] = {
            .pFrame = sOamFrame_597e6e,
            .timer = 1
    },
    [3] = {
            .pFrame = sOamFrame_597e5a,
            .timer = 1
    },
    [4] = {
            .pFrame = sOamFrame_59775e,
            .timer = 1
    },
    [5] = {
            .pFrame = sOamFrame_597e82,
            .timer = 1
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597f88[5] = {
    [0] = {
            .pFrame = sOamFrame_597e90,
            .timer = 1
    },
    [1] = {
            .pFrame = sOamFrame_597788,
            .timer = 1
    },
    [2] = {
            .pFrame = sOamFrame_597eac,
            .timer = 1
    },
    [3] = {
            .pFrame = sOamFrame_597788,
            .timer = 1
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597fb0[2] = {
    [0] = {
            .pFrame = sOamFrame_5977a4,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597fc0[2] = {
    [0] = {
            .pFrame = sOamFrame_5977b2,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597fd0[2] = {
    [0] = {
            .pFrame = sOamFrame_5977d8,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597fe0[2] = {
    [0] = {
            .pFrame = sOamFrame_5977f2,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_597ff0[2] = {
    [0] = {
            .pFrame = sOamFrame_597800,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_598000[12] = {
    [0] = {
            .pFrame = sOamFrame_597c0a,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_597c12,
            .timer = 4
    },
    [2] = {
            .pFrame = sOamFrame_597c32,
            .timer = 4
    },
    [3] = {
            .pFrame = sOamFrame_597c6a,
            .timer = 4
    },
    [4] = {
            .pFrame = sOamFrame_597cb4,
            .timer = 4
    },
    [5] = {
            .pFrame = sOamFrame_597d04,
            .timer = 4
    },
    [6] = {
            .pFrame = sOamFrame_597d5a,
            .timer = 6
    },
    [7] = {
            .pFrame = sOamFrame_597da4,
            .timer = 7
    },
    [8] = {
            .pFrame = sOamFrame_597ddc,
            .timer = 8
    },
    [9] = {
            .pFrame = sOamFrame_597df6,
            .timer = 9
    },
    [10] = {
            .pFrame = sOamFrame_597e0a,
            .timer = 10
    },
    [11] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_598060[5] = {
    [0] = {
            .pFrame = sOamFrame_597e12,
            .timer = 1
    },
    [1] = {
            .pFrame = sOamFrame_597e20,
            .timer = 1
    },
    [2] = {
            .pFrame = sOamFrame_597e28,
            .timer = 1
    },
    [3] = {
            .pFrame = sOamFrame_597e20,
            .timer = 1
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_598088[5] = {
    [0] = {
            .pFrame = sOamFrame_597e36,
            .timer = 1
    },
    [1] = {
            .pFrame = sOamFrame_597e44,
            .timer = 1
    },
    [2] = {
            .pFrame = sOamFrame_597e4c,
            .timer = 1
    },
    [3] = {
            .pFrame = sOamFrame_597e44,
            .timer = 1
    },
    [4] = FRAME_DATA_TERMINATOR
};

const u16 sIntroSamusShipPal[5 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_ship.pal");
const u16 sPal_598150[2 * PAL_ROW] = INCBIN_U16("data/new_file_intro/598150.pal"); // Loaded to PALRAM but not used?

const u32 sIntroSamusHelmetCloseupTilemap[418] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup.tm.lz");

const u16 sIntroSamusHelmetCloseupPal[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_helmet_closeup.pal");

const u32 sIntroSamusShipFlyingTextTilemap[125] = INCBIN_U32("data/new_file_intro/samus_ship_flying_text.tm.lz");

const u16 sPal_598a8c[1 * PAL_ROW] = INCBIN_U16("data/new_file_intro/598a8c.pal");
const u16 sIntroSamusCloseupGrayscalePal[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_helmet_closeup_grayscale.pal");

const u16 sSr388SpaceAndSurfacePal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/sr388_space_and_surface.pal");

const u32 sIntroSr388SurfaceTilemap[551] = INCBIN_U32("data/new_file_intro/sr388_surface.tm.lz");
const u32 sIntroSr388SpaceBgTilemap[265] = INCBIN_U32("data/new_file_intro/sr388_space_bg.tm.lz");
const u32 sIntroSr388PlanetTilemap[199] = INCBIN_U32("data/new_file_intro/sr388_planet.tm.lz");

static const u16 sOamFrame_599d08[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 0, 8, 0),
};

static const u16 sOamFrame_599d10[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 8, 8, 0),
};

static const u16 sOamFrame_599d18[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 12, 8, 0),
};

static const u16 sOamFrame_599d20[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 136, 8, 0),
};

static const u16 sOamFrame_599d28[OAM_DATA_SIZE(52)] = {
    52,
    OAM_ENTRY_MODE(0, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 152, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, -48, OAM_DIMS_32x8, OAM_NO_FLIP, 216, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(64, -64, OAM_DIMS_32x32, OAM_NO_FLIP, 256, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(96, -64, OAM_DIMS_8x32, OAM_NO_FLIP, 287, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-64, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 260, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, -32, OAM_DIMS_16x32, OAM_NO_FLIP, 264, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-64, -64, OAM_DIMS_64x32, OAM_NO_FLIP, 144, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(32, -64, OAM_DIMS_32x32, OAM_NO_FLIP, 156, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 248, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-16, -32, OAM_DIMS_16x32, OAM_NO_FLIP, 266, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 268, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 332, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(16, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 334, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(24, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 335, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(32, -32, OAM_DIMS_8x16, OAM_NO_FLIP, 272, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(40, -32, OAM_DIMS_64x32, OAM_NO_FLIP, 273, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(40, 0, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-80, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 402, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-48, 0, OAM_DIMS_8x32, OAM_NO_FLIP, 512, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-40, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 513, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-40, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 545, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-24, 16, OAM_DIMS_16x16, OAM_NO_FLIP, 579, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-40, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 609, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-24, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 547, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(8, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 519, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(8, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 583, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, 16, OAM_DIMS_8x16, OAM_NO_FLIP, 582, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-8, 16, OAM_DIMS_8x16, OAM_NO_FLIP, 581, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 549, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, 0, OAM_DIMS_8x16, OAM_NO_FLIP, 518, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 517, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(16, 32, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(80, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 620, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-88, 32, OAM_DIMS_16x32, OAM_NO_FLIP, 281, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-64, 32, OAM_DIMS_32x32, OAM_NO_FLIP, 283, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, 32, OAM_DIMS_16x32, OAM_NO_FLIP, 392, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 502, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-16, 40, OAM_DIMS_16x16, OAM_NO_FLIP, 440, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, 48, OAM_DIMS_16x8, OAM_NO_FLIP, 470, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-24, 32, OAM_DIMS_16x8, OAM_NO_FLIP, 407, 5, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-8, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 409, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 406, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 439, 4, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-32, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 438, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-80, 64, OAM_DIMS_16x16, OAM_NO_FLIP, 523, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-56, 88, OAM_DIMS_32x8, OAM_NO_FLIP, 442, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-72, 80, OAM_DIMS_32x8, OAM_NO_FLIP, 410, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-24, 80, OAM_DIMS_16x16, OAM_NO_FLIP, 414, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(0, 64, OAM_DIMS_16x16, OAM_NO_FLIP, 478, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-8, 72, OAM_DIMS_8x16, OAM_NO_FLIP, 587, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
    OAM_ENTRY_MODE(-64, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 588, 6, 0, OAM_OBJ_MODE_SEMI_TRANSPARENT),
};

static const u16 sOamFrame_599e62[OAM_DATA_SIZE(17)] = {
    17,
    OAM_ENTRY(-128, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 736, 0, 0),
    OAM_ENTRY(-64, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 744, 0, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_64x64, OAM_NO_FLIP, 752, 0, 0),
    OAM_ENTRY(64, 0, OAM_DIMS_32x64, OAM_NO_FLIP, 760, 0, 0),
    OAM_ENTRY(96, 0, OAM_DIMS_16x32, OAM_NO_FLIP, 764, 0, 0),
    OAM_ENTRY(96, 32, OAM_DIMS_16x32, OAM_NO_FLIP, 892, 0, 0),
    OAM_ENTRY(-128, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 992, 0, 0),
    OAM_ENTRY(-96, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 996, 0, 0),
    OAM_ENTRY(-64, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 1000, 0, 0),
    OAM_ENTRY(-32, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 1004, 0, 0),
    OAM_ENTRY(0, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 1008, 0, 0),
    OAM_ENTRY(32, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 1012, 0, 0),
    OAM_ENTRY(64, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 1016, 0, 0),
    OAM_ENTRY(96, 64, OAM_DIMS_16x8, OAM_NO_FLIP, 1020, 0, 0),
    OAM_ENTRY(80, -64, OAM_DIMS_32x64, OAM_NO_FLIP, 506, 0, 0),
    OAM_ENTRY(72, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 697, 0, 0),
    OAM_ENTRY(-128, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 704, 0, 0),
};

static const u16 sOamFrame_599eca[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(80, -64, OAM_DIMS_32x64, OAM_NO_FLIP, 506, 0, 0),
    OAM_ENTRY(72, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 697, 0, 0),
    OAM_ENTRY(-128, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 704, 0, 0),
};

static const u16 sOamFrame_599ede[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(2, -15, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 1, 0),
};

static const u16 sOamFrame_599ee6[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(3, -15, OAM_DIMS_16x16, OAM_NO_FLIP, 18, 1, 0),
};

static const u16 sOamFrame_599eee[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(4, -15, OAM_DIMS_16x16, OAM_NO_FLIP, 20, 1, 0),
};

static const u16 sOamFrame_599ef6[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(2, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 124, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 30, 1, 0),
};

static const u16 sOamFrame_599f04[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599f12[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(10, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(-6, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 60, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599f2c[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599f46[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x16, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599f6c[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-22, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 24, 0, 0),
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x32, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599f98[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-30, -64, OAM_DIMS_16x8, OAM_NO_FLIP, 22, 0, 0),
    OAM_ENTRY(-22, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 24, 0, 0),
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x32, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(2, 48, OAM_DIMS_8x16, OAM_NO_FLIP, 87, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_599fd0[OAM_DATA_SIZE(10)] = {
    10,
    OAM_ENTRY(-30, -64, OAM_DIMS_16x8, OAM_NO_FLIP, 22, 0, 0),
    OAM_ENTRY(-22, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 24, 0, 0),
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x32, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(2, 48, OAM_DIMS_8x16, OAM_NO_FLIP, 87, 0, 0),
    OAM_ENTRY(-14, 64, OAM_DIMS_16x16, OAM_NO_FLIP, 88, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_59a00e[OAM_DATA_SIZE(12)] = {
    12,
    OAM_ENTRY(-30, -64, OAM_DIMS_16x8, OAM_NO_FLIP, 22, 0, 0),
    OAM_ENTRY(-22, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 24, 0, 0),
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x32, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(2, 48, OAM_DIMS_8x16, OAM_NO_FLIP, 87, 0, 0),
    OAM_ENTRY(-14, 64, OAM_DIMS_16x16, OAM_NO_FLIP, 88, 0, 0),
    OAM_ENTRY(-30, 80, OAM_DIMS_16x16, OAM_NO_FLIP, 90, 0, 0),
    OAM_ENTRY(-14, 80, OAM_DIMS_8x8, OAM_NO_FLIP, 54, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
    OAM_ENTRY(10, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 30, 1, 0),
    OAM_ENTRY(2, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 1, 0),
};

static const u16 sOamFrame_59a058[OAM_DATA_SIZE(10)] = {
    10,
    OAM_ENTRY(-30, -64, OAM_DIMS_16x8, OAM_NO_FLIP, 22, 0, 0),
    OAM_ENTRY(-22, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 24, 0, 0),
    OAM_ENTRY(-14, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 26, 0, 0),
    OAM_ENTRY(-6, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 0, 0),
    OAM_ENTRY(10, 24, OAM_DIMS_8x32, OAM_NO_FLIP, 31, 0, 0),
    OAM_ENTRY(2, 48, OAM_DIMS_8x16, OAM_NO_FLIP, 87, 0, 0),
    OAM_ENTRY(-14, 64, OAM_DIMS_16x16, OAM_NO_FLIP, 88, 0, 0),
    OAM_ENTRY(-30, 80, OAM_DIMS_16x16, OAM_NO_FLIP, 90, 0, 0),
    OAM_ENTRY(-14, 80, OAM_DIMS_8x8, OAM_NO_FLIP, 54, 0, 0),
    OAM_ENTRY(10, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 94, 1, 0),
};

static const u16 sOamFrame_59a096[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 798, 6, 0),
};

const struct FrameData sOam_59a0a0[2] = {
    [0] = {
            .pFrame = sOamFrame_599d08,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a0b0[2] = {
    [0] = {
            .pFrame = sOamFrame_599d10,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a0c0[2] = {
    [0] = {
            .pFrame = sOamFrame_599d18,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a0d0[2] = {
    [0] = {
            .pFrame = sOamFrame_599d20,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a0e0[2] = {
    [0] = {
            .pFrame = sOamFrame_599d28,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a0f0[2] = {
    [0] = {
            .pFrame = sOamFrame_599e62,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a100[13] = {
    [0] = {
            .pFrame = sOamFrame_59a096,
            .timer = 80
    },
    [1] = {
            .pFrame = sOamFrame_599ef6,
            .timer = 1
    },
    [2] = {
            .pFrame = sOamFrame_599f04,
            .timer = 1
    },
    [3] = {
            .pFrame = sOamFrame_599f12,
            .timer = 1
    },
    [4] = {
            .pFrame = sOamFrame_599f2c,
            .timer = 1
    },
    [5] = {
            .pFrame = sOamFrame_599f46,
            .timer = 1
    },
    [6] = {
            .pFrame = sOamFrame_599f6c,
            .timer = 1
    },
    [7] = {
            .pFrame = sOamFrame_599f98,
            .timer = 1
    },
    [8] = {
            .pFrame = sOamFrame_599fd0,
            .timer = 1
    },
    [9] = {
            .pFrame = sOamFrame_59a00e,
            .timer = 212
    },
    [10] = {
            .pFrame = sOamFrame_59a00e,
            .timer = 220
    },
    [11] = {
            .pFrame = sOamFrame_59a00e,
            .timer = 200
    },
    [12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a168[2] = {
    [0] = {
            .pFrame = sOamFrame_599eca,
            .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_59a178[8] = {
    [0] = {
            .pFrame = sOamFrame_59a096,
            .timer = 116
    },
    [1] = {
            .pFrame = sOamFrame_599ede,
            .timer = 12
    },
    [2] = {
            .pFrame = sOamFrame_599ee6,
            .timer = 8
    },
    [3] = {
            .pFrame = sOamFrame_599eee,
            .timer = 4
    },
    [4] = {
            .pFrame = sOamFrame_599d28,
            .timer = 140
    },
    [5] = {
            .pFrame = sOamFrame_59a096,
            .timer = 240
    },
    [6] = {
            .pFrame = sOamFrame_59a096,
            .timer = 200
    },
    [7] = FRAME_DATA_TERMINATOR
};

const u32 sIntroSr388SpaceAndSurfaceObjGfx[3538] = INCBIN_U32("data/new_file_intro/sr388_space_and_surface_objects.gfx.lz");
const u16 sIntroSr388SpaceAndSurfaceObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/sr388_space_and_surface_objects.pal");

const u8 sArray_59db00[8] = {20, 30, 40, 50, 40, 30, 0, 0};

const u32 sIntroHornoadEncounterObjGfx[4252] = INCBIN_U32("data/new_file_intro/hornoad_encounter_obj.gfx.lz");
const u16 sIntroHornoadEncounterObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/hornoad_encounter_obj.pal");

static const u16 sOamFrame_5a1f78[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -13, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a1f98[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -9, OAM_DIMS_16x16, OAM_Y_FLIP, 534, 8, 0),
	OAM_ENTRY(-12, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-5, -19, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(-5, -11, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-13, -19, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a1fb8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -7, OAM_DIMS_16x16, OAM_X_FLIP, 538, 8, 0),
	OAM_ENTRY(-5, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(2, -19, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(2, -11, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-6, -19, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a1fd8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -13, OAM_DIMS_16x16, OAM_X_FLIP, 540, 8, 0),
	OAM_ENTRY(-5, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(2, -19, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(2, -11, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-6, -19, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a1ff8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -15, OAM_DIMS_16x16, OAM_X_FLIP, 542, 8, 0),
	OAM_ENTRY(-16, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(-8, -11, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2018[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-16, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2038[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-16, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_16x8, OAM_X_FLIP, 512, 8, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 618, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2058[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -15, OAM_DIMS_16x8, OAM_X_FLIP, 613, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 528, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 530, 9, 0),
};

static const u16 sOamFrame_5a2078[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -15, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2098[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x8, OAM_X_FLIP, 525, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_X_FLIP, 581, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 527, 9, 0),
};

static const u16 sOamFrame_5a20b8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -15, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x8, OAM_X_FLIP, 520, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a20d8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 520, 9, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a20f8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -13, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 552, 9, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2118[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-10, -16, OAM_DIMS_8x16, OAM_X_FLIP, 585, 9, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 590, 9, 0),
	OAM_ENTRY(-12, -24, OAM_DIMS_8x16, OAM_X_FLIP, 578, 9, 0),
	OAM_ENTRY(3, -16, OAM_DIMS_8x16, OAM_X_FLIP, 585, 9, 0),
};

static const u16 sOamFrame_5a2132[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(2, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 585, 9, 0),
	OAM_ENTRY(-12, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 590, 9, 0),
	OAM_ENTRY(4, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 578, 9, 0),
	OAM_ENTRY(-11, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 585, 9, 0),
};

static const u16 sOamFrame_5a214c[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-6, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-4, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(0, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_X_FLIP, 520, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a216c[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 552, 9, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a218c[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 615, 9, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a21b2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a21d2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -9, OAM_DIMS_16x16, OAM_Y_FLIP, 534, 9, 0),
	OAM_ENTRY(-12, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-5, -21, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-13, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
	OAM_ENTRY(-5, -14, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
};

static const u16 sOamFrame_5a21f2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -7, OAM_DIMS_16x16, OAM_X_FLIP, 538, 9, 0),
	OAM_ENTRY(-5, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(2, -21, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-6, -20, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
	OAM_ENTRY(2, -12, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
};

static const u16 sOamFrame_5a2212[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -13, OAM_DIMS_16x16, OAM_X_FLIP, 540, 9, 0),
	OAM_ENTRY(-5, -10, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(2, -21, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-6, -20, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
	OAM_ENTRY(2, -12, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
};

static const u16 sOamFrame_5a2232[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -15, OAM_DIMS_16x16, OAM_X_FLIP, 542, 9, 0),
	OAM_ENTRY(-16, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
	OAM_ENTRY(-8, -13, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
};

static const u16 sOamFrame_5a2252[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-16, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2272[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-16, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2292[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-12, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-7, -20, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-7, -15, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-15, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a22b2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-12, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -15, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-7, -22, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -15, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-15, -21, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a22d2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-9, -13, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-16, -23, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a22f2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-13, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-10, -13, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-17, -23, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2312[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x16, OAM_X_FLIP, 592, 9, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x8, OAM_X_FLIP, 583, 9, 0),
};

static const u16 sOamFrame_5a2332[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-6, -23, OAM_DIMS_16x8, OAM_X_FLIP, 568, 9, 0),
	OAM_ENTRY(-16, -15, OAM_DIMS_16x16, OAM_NO_FLIP, 542, 9, 0),
	OAM_ENTRY(-6, -14, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 9, 0),
	OAM_ENTRY(1, -20, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(0, -11, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-7, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a2358[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, -22, OAM_DIMS_16x8, OAM_X_FLIP, 568, 9, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_16x16, OAM_X_FLIP, 538, 9, 0),
	OAM_ENTRY(-7, -14, OAM_DIMS_8x8, OAM_NO_FLIP, 536, 9, 0),
	OAM_ENTRY(-1, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-2, -12, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-9, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a237e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-14, -23, OAM_DIMS_16x8, OAM_X_FLIP, 568, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-10, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-7, -20, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-8, -11, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-15, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a23a4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-15, -22, OAM_DIMS_16x8, OAM_X_FLIP, 568, 9, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x16, OAM_X_FLIP, 515, 9, 0),
	OAM_ENTRY(-9, -12, OAM_DIMS_16x16, OAM_X_FLIP, 518, 9, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 517, 9, 0),
};

static const u16 sOamFrame_5a23ca[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -15, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_X_FLIP, 618, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x8, OAM_X_FLIP, 512, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
};

static const u16 sOamFrame_5a23ea[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 528, 9, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_8x16, OAM_X_FLIP, 530, 9, 0),
};

static const u16 sOamFrame_5a2404[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -13, OAM_DIMS_16x8, OAM_X_FLIP, 618, 9, 0),
	OAM_ENTRY(-8, -21, OAM_DIMS_16x8, OAM_X_FLIP, 512, 9, 0),
	OAM_ENTRY(-16, -21, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
};

static const u16 sOamFrame_5a2424[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-9, -11, OAM_DIMS_16x8, OAM_X_FLIP, 520, 9, 0),
	OAM_ENTRY(-9, -21, OAM_DIMS_16x16, OAM_X_FLIP, 512, 9, 0),
	OAM_ENTRY(-17, -21, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
};

static const u16 sOamFrame_5a2444[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_X_FLIP, 611, 9, 0),
	OAM_ENTRY(-8, -21, OAM_DIMS_16x16, OAM_X_FLIP, 512, 9, 0),
	OAM_ENTRY(-16, -21, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
};

static const u16 sOamFrame_5a2464[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 9, 0),
	OAM_ENTRY(-11, -14, OAM_DIMS_8x8, OAM_X_FLIP, 536, 9, 0),
	OAM_ENTRY(-8, -19, OAM_DIMS_16x8, OAM_X_FLIP, 512, 9, 0),
	OAM_ENTRY(-8, -11, OAM_DIMS_16x8, OAM_X_FLIP, 579, 9, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_8x16, OAM_X_FLIP, 514, 9, 0),
};

static const u16 sOamFrame_5a2484[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -11, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_16x8, OAM_X_FLIP, 588, 8, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a24a4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -12, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x8, OAM_X_FLIP, 588, 8, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a24c4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -13, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x8, OAM_X_FLIP, 588, 8, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x16, OAM_X_FLIP, 592, 8, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a24e4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -12, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x8, OAM_X_FLIP, 588, 8, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2504[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -11, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_16x8, OAM_X_FLIP, 620, 8, 0),
};

static const u16 sOamFrame_5a2524[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -12, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x8, OAM_X_FLIP, 620, 8, 0),
};

static const u16 sOamFrame_5a2544[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -13, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -18, OAM_DIMS_16x8, OAM_X_FLIP, 620, 8, 0),
	OAM_ENTRY(-8, -10, OAM_DIMS_16x16, OAM_X_FLIP, 592, 8, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2564[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-14, -16, OAM_DIMS_16x16, OAM_X_FLIP, 594, 8, 0),
	OAM_ENTRY(-11, -12, OAM_DIMS_8x8, OAM_X_FLIP, 536, 8, 0),
	OAM_ENTRY(-8, -17, OAM_DIMS_16x8, OAM_X_FLIP, 620, 8, 0),
	OAM_ENTRY(-8, -9, OAM_DIMS_16x8, OAM_X_FLIP, 579, 8, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_8x16, OAM_X_FLIP, 514, 8, 0),
};

static const u16 sOamFrame_5a2584[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-19, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 647, 3, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 649, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 711, 3, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 713, 3, 0),
};

static const u16 sOamFrame_5a25bc[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-18, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-2, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 652, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 716, 3, 0),
};

static const u16 sOamFrame_5a25e8[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-18, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-2, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -33, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -41, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -41, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 643, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 707, 3, 0),
};

static const u16 sOamFrame_5a2614[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-19, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 640, 3, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 642, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 704, 3, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 706, 3, 0),
};

static const u16 sOamFrame_5a264c[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-18, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-2, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 645, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 709, 3, 0),
};

static const u16 sOamFrame_5a2678[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-18, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-2, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -33, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -41, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -41, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 714, 3, 0),
};

static const u16 sOamFrame_5a26a4[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-12, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 868, 3, 0),
	OAM_ENTRY(4, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 870, 3, 0),
	OAM_ENTRY(-12, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 996, 3, 0),
	OAM_ENTRY(4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 998, 3, 0),
};

static const u16 sOamFrame_5a26be[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-4, -40, OAM_DIMS_16x32, OAM_X_FLIP, 868, 3, 0),
	OAM_ENTRY(-12, -40, OAM_DIMS_8x32, OAM_X_FLIP, 870, 3, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_16x8, OAM_X_FLIP, 996, 3, 0),
	OAM_ENTRY(-12, -8, OAM_DIMS_8x8, OAM_X_FLIP, 998, 3, 0),
};

static const u16 sOamFrame_5a26d8[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-18, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 960, 3, 0),
	OAM_ENTRY(-2, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 962, 3, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 896, 3, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 865, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 867, 3, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 686, 3, 0),
	OAM_ENTRY(4, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 688, 3, 0),
};

static const u16 sOamFrame_5a2704[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(2, -24, OAM_DIMS_16x8, OAM_X_FLIP, 960, 3, 0),
	OAM_ENTRY(-6, -24, OAM_DIMS_8x8, OAM_X_FLIP, 962, 3, 0),
	OAM_ENTRY(-14, -32, OAM_DIMS_32x16, OAM_X_FLIP, 896, 3, 0),
	OAM_ENTRY(-6, -40, OAM_DIMS_16x8, OAM_X_FLIP, 865, 3, 0),
	OAM_ENTRY(-14, -40, OAM_DIMS_8x8, OAM_X_FLIP, 867, 3, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_16x16, OAM_X_FLIP, 686, 3, 0),
	OAM_ENTRY(-12, -16, OAM_DIMS_8x16, OAM_X_FLIP, 688, 3, 0),
};

static const u16 sOamFrame_5a2730[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 662, 3, 0),
	OAM_ENTRY(4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 606, 3, 0),
};

static const u16 sOamFrame_5a273e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 662, 3, 0),
	OAM_ENTRY(7, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 605, 3, 0),
};

static const u16 sOamFrame_5a274c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 694, 3, 0),
	OAM_ENTRY(1, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 606, 3, 0),
};

static const u16 sOamFrame_5a275a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 694, 3, 0),
	OAM_ENTRY(2, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 604, 3, 0),
};

static const u16 sOamFrame_5a2768[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 728, 3, 0),
};

static const u16 sOamFrame_5a2770[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 729, 3, 0),
};

static const u16 sOamFrame_5a2778[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 730, 3, 0),
};

static const u16 sOamFrame_5a2780[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 731, 3, 0),
};

static const u16 sOamFrame_5a2788[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 732, 3, 0),
};

static const u16 sOamFrame_5a2790[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_XY_FLIP, 696, 3, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 696, 3, 0),
};

static const u16 sOamFrame_5a27aa[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-16, -17, OAM_DIMS_16x16, OAM_NO_FLIP, 665, 3, 0),
	OAM_ENTRY(0, -1, OAM_DIMS_16x16, OAM_XY_FLIP, 665, 3, 0),
	OAM_ENTRY(0, -17, OAM_DIMS_16x16, OAM_X_FLIP, 665, 3, 0),
	OAM_ENTRY(-16, -1, OAM_DIMS_16x16, OAM_Y_FLIP, 665, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_8x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_XY_FLIP, 696, 3, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_8x8, OAM_Y_FLIP, 696, 3, 0),
};

static const u16 sOamFrame_5a27dc[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-16, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 667, 3, 0),
	OAM_ENTRY(0, -18, OAM_DIMS_16x16, OAM_X_FLIP, 667, 3, 0),
	OAM_ENTRY(0, -2, OAM_DIMS_16x16, OAM_XY_FLIP, 667, 3, 0),
	OAM_ENTRY(-16, -2, OAM_DIMS_16x16, OAM_Y_FLIP, 667, 3, 0),
	OAM_ENTRY(-32, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 665, 3, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_16x16, OAM_XY_FLIP, 665, 3, 0),
	OAM_ENTRY(-16, -33, OAM_DIMS_16x16, OAM_X_FLIP, 665, 3, 0),
	OAM_ENTRY(-32, -17, OAM_DIMS_16x16, OAM_Y_FLIP, 665, 3, 0),
	OAM_ENTRY(4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(12, -16, OAM_DIMS_8x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(12, -8, OAM_DIMS_8x8, OAM_XY_FLIP, 696, 3, 0),
	OAM_ENTRY(4, -8, OAM_DIMS_8x8, OAM_Y_FLIP, 696, 3, 0),
};

static const u16 sOamFrame_5a2826[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-16, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 669, 3, 0),
	OAM_ENTRY(0, -19, OAM_DIMS_16x16, OAM_X_FLIP, 669, 3, 0),
	OAM_ENTRY(0, -3, OAM_DIMS_16x16, OAM_XY_FLIP, 669, 3, 0),
	OAM_ENTRY(-16, -3, OAM_DIMS_16x16, OAM_Y_FLIP, 669, 3, 0),
	OAM_ENTRY(-32, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 667, 3, 0),
	OAM_ENTRY(-16, -34, OAM_DIMS_16x16, OAM_X_FLIP, 667, 3, 0),
	OAM_ENTRY(-16, -18, OAM_DIMS_16x16, OAM_XY_FLIP, 667, 3, 0),
	OAM_ENTRY(-32, -18, OAM_DIMS_16x16, OAM_Y_FLIP, 667, 3, 0),
	OAM_ENTRY(-4, -25, OAM_DIMS_16x16, OAM_NO_FLIP, 665, 3, 0),
	OAM_ENTRY(12, -9, OAM_DIMS_16x16, OAM_XY_FLIP, 665, 3, 0),
	OAM_ENTRY(12, -25, OAM_DIMS_16x16, OAM_X_FLIP, 665, 3, 0),
	OAM_ENTRY(-4, -9, OAM_DIMS_16x16, OAM_Y_FLIP, 665, 3, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 757, 3, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5a287c[OAM_DATA_SIZE(16)] = {
	16,
	OAM_ENTRY(-16, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 733, 3, 0),
	OAM_ENTRY(-16, -5, OAM_DIMS_16x16, OAM_Y_FLIP, 733, 3, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_16x16, OAM_XY_FLIP, 733, 3, 0),
	OAM_ENTRY(0, -21, OAM_DIMS_16x16, OAM_X_FLIP, 733, 3, 0),
	OAM_ENTRY(-32, -35, OAM_DIMS_16x16, OAM_NO_FLIP, 669, 3, 0),
	OAM_ENTRY(-16, -35, OAM_DIMS_16x16, OAM_X_FLIP, 669, 3, 0),
	OAM_ENTRY(-16, -19, OAM_DIMS_16x16, OAM_XY_FLIP, 669, 3, 0),
	OAM_ENTRY(-32, -19, OAM_DIMS_16x16, OAM_Y_FLIP, 669, 3, 0),
	OAM_ENTRY(-4, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 667, 3, 0),
	OAM_ENTRY(12, -26, OAM_DIMS_16x16, OAM_X_FLIP, 667, 3, 0),
	OAM_ENTRY(12, -10, OAM_DIMS_16x16, OAM_XY_FLIP, 667, 3, 0),
	OAM_ENTRY(-4, -10, OAM_DIMS_16x16, OAM_Y_FLIP, 667, 3, 0),
	OAM_ENTRY(-33, -41, OAM_DIMS_16x16, OAM_NO_FLIP, 759, 3, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 757, 3, 0),
	OAM_ENTRY(-26, -6, OAM_DIMS_16x16, OAM_NO_FLIP, 759, 3, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5a28de[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-32, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 733, 3, 0),
	OAM_ENTRY(-32, -20, OAM_DIMS_16x16, OAM_Y_FLIP, 733, 3, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_16x16, OAM_XY_FLIP, 733, 3, 0),
	OAM_ENTRY(-16, -36, OAM_DIMS_16x16, OAM_X_FLIP, 733, 3, 0),
	OAM_ENTRY(-4, -27, OAM_DIMS_16x16, OAM_NO_FLIP, 669, 3, 0),
	OAM_ENTRY(12, -27, OAM_DIMS_16x16, OAM_X_FLIP, 669, 3, 0),
	OAM_ENTRY(12, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 669, 3, 0),
	OAM_ENTRY(-4, -11, OAM_DIMS_16x16, OAM_Y_FLIP, 669, 3, 0),
	OAM_ENTRY(-34, -42, OAM_DIMS_16x16, OAM_NO_FLIP, 761, 3, 0),
	OAM_ENTRY(17, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 759, 3, 0),
	OAM_ENTRY(-40, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 596, 3, 0),
	OAM_ENTRY(-28, -4, OAM_DIMS_16x16, OAM_NO_FLIP, 761, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 596, 3, 0),
	OAM_ENTRY(10, -6, OAM_DIMS_16x16, OAM_NO_FLIP, 759, 3, 0),
};

static const u16 sOamFrame_5a2934[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-4, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 733, 3, 0),
	OAM_ENTRY(-4, -12, OAM_DIMS_16x16, OAM_Y_FLIP, 733, 3, 0),
	OAM_ENTRY(12, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 733, 3, 0),
	OAM_ENTRY(12, -28, OAM_DIMS_16x16, OAM_X_FLIP, 733, 3, 0),
	OAM_ENTRY(-35, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 763, 3, 0),
	OAM_ENTRY(18, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 761, 3, 0),
	OAM_ENTRY(-41, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 598, 3, 0),
	OAM_ENTRY(24, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 596, 3, 0),
	OAM_ENTRY(-30, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 763, 3, 0),
	OAM_ENTRY(-34, 2, OAM_DIMS_16x16, OAM_NO_FLIP, 598, 3, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_16x16, OAM_NO_FLIP, 761, 3, 0),
	OAM_ENTRY(17, 1, OAM_DIMS_16x16, OAM_NO_FLIP, 596, 3, 0),
};

static const u16 sOamFrame_5a297e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(19, -35, OAM_DIMS_16x16, OAM_NO_FLIP, 763, 3, 0),
	OAM_ENTRY(-42, -50, OAM_DIMS_16x16, OAM_NO_FLIP, 600, 3, 0),
	OAM_ENTRY(25, -41, OAM_DIMS_16x16, OAM_NO_FLIP, 598, 3, 0),
	OAM_ENTRY(-36, 4, OAM_DIMS_16x16, OAM_NO_FLIP, 600, 3, 0),
	OAM_ENTRY(14, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 763, 3, 0),
	OAM_ENTRY(20, 4, OAM_DIMS_16x16, OAM_NO_FLIP, 598, 3, 0),
};

static const u16 sOamFrame_5a29a4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(8, -42, OAM_DIMS_16x16, OAM_NO_FLIP, 602, 3, 0),
	OAM_ENTRY(-43, -51, OAM_DIMS_16x16, OAM_NO_FLIP, 602, 3, 0),
	OAM_ENTRY(26, -42, OAM_DIMS_16x16, OAM_NO_FLIP, 600, 3, 0),
	OAM_ENTRY(-38, 6, OAM_DIMS_16x16, OAM_NO_FLIP, 602, 3, 0),
	OAM_ENTRY(23, 7, OAM_DIMS_16x16, OAM_NO_FLIP, 600, 3, 0),
};

static const u16 sOamFrame_5a29c4[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(27, -42, OAM_DIMS_16x16, OAM_NO_FLIP, 602, 3, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 602, 3, 0),
};

static const u16 sOamFrame_5a29d2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 800, 4, 0),
};

static const u16 sOamFrame_5a29da[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 802, 4, 0),
};

static const u16 sOamFrame_5a29e2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 804, 4, 0),
};

static const u16 sOamFrame_5a29ea[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 806, 4, 0),
};

static const u16 sOamFrame_5a29f2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 808, 4, 0),
};

static const u16 sOamFrame_5a29fa[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 810, 4, 0),
};

static const u16 sOamFrame_5a2a02[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_XY_FLIP, 696, 3, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 696, 3, 0),
};

static const u16 sOamFrame_5a2a1c[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 665, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 665, 3, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 665, 3, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 665, 3, 0),
};

static const u16 sOamFrame_5a2a36[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 667, 3, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 667, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 667, 3, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 667, 3, 0),
};

static const u16 sOamFrame_5a2a50[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 669, 3, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 669, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 669, 3, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 669, 3, 0),
};

static const u16 sOamFrame_5a2a6a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 733, 3, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 733, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 733, 3, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 733, 3, 0),
};

static const u16 sOamFrame_5a2a84[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-64, -24, OAM_DIMS_64x32, OAM_NO_FLIP, 816, 14, 0),
	OAM_ENTRY(-64, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 944, 14, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 948, 14, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 952, 14, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(64, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(96, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(96, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
};

static const u16 sOamFrame_5a2ac8[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(64, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(96, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(96, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 825, 14, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 825, 14, 0),
};

const struct FrameData sOam_5a2af0[13] = {
	[0] = {
		.pFrame = sOamFrame_5a2484,
		.timer = 34
	},
	[1] = {
		.pFrame = sOamFrame_5a24a4,
		.timer = 22
	},
	[2] = {
		.pFrame = sOamFrame_5a24c4,
		.timer = 18
	},
	[3] = {
		.pFrame = sOamFrame_5a24e4,
		.timer = 16
	},
	[4] = {
		.pFrame = sOamFrame_5a2504,
		.timer = 34
	},
	[5] = {
		.pFrame = sOamFrame_5a2524,
		.timer = 22
	},
	[6] = {
		.pFrame = sOamFrame_5a2544,
		.timer = 18
	},
	[7] = {
		.pFrame = sOamFrame_5a2564,
		.timer = 16
	},
	[8] = {
		.pFrame = sOamFrame_5a2504,
		.timer = 34
	},
	[9] = {
		.pFrame = sOamFrame_5a2524,
		.timer = 22
	},
	[10] = {
		.pFrame = sOamFrame_5a2544,
		.timer = 18
	},
	[11] = {
		.pFrame = sOamFrame_5a2564,
		.timer = 16
	},
	[12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_IdleUnused[2] = {
	[0] = {
		.pFrame = sOamFrame_5a1f78,
		.timer = 10
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_JumpingUnused[5] = {
	[0] = {
		.pFrame = sOamFrame_5a1f98,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a1fb8,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5a1fd8,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5a1ff8,
		.timer = 255
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_BouncingUnused[3] = {
	[0] = {
		.pFrame = sOamFrame_5a2018,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5a2038,
		.timer = 3
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Shaking[5] = {
	[0] = {
		.pFrame = sOamFrame_5a2078,
		.timer = 6
	},
	[1] = {
		.pFrame = sOamFrame_5a2058,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5a2078,
		.timer = 6
	},
	[3] = {
		.pFrame = sOamFrame_5a2098,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Panting[5] = {
	[0] = {
		.pFrame = sOamFrame_5a20b8,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5a20d8,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5a20f8,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5a20d8,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Chomping[12] = {
	[0] = {
		.pFrame = sOamFrame_5a2272,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a2292,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5a22b2,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5a22d2,
		.timer = 4
	},
	[4] = {
		.pFrame = sOamFrame_5a22f2,
		.timer = 4
	},
	[5] = {
		.pFrame = sOamFrame_5a2312,
		.timer = 4
	},
	[6] = {
		.pFrame = sOamFrame_5a2272,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5a2292,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5a22b2,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5a22d2,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5a22f2,
		.timer = 2
	},
	[11] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2c58[3] = {
	[0] = {
		.pFrame = sOamFrame_5a2118,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a20d8,
		.timer = 4
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Biting[5] = {
	[0] = {
		.pFrame = sOamFrame_5a216c,
		.timer = 10
	},
	[1] = {
		.pFrame = sOamFrame_5a218c,
		.timer = 10
	},
	[2] = {
		.pFrame = sOamFrame_5a216c,
		.timer = 10
	},
	[3] = {
		.pFrame = sOamFrame_5a21b2,
		.timer = 10
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Jumping[5] = {
	[0] = {
		.pFrame = sOamFrame_5a21d2,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a21f2,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5a2212,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5a2232,
		.timer = 255
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_Bouncing[3] = {
	[0] = {
		.pFrame = sOamFrame_5a2252,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5a2272,
		.timer = 3
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388HornoadOam_MidAir[3] = {
	[0] = {
		.pFrame = sOamFrame_5a2332,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a2358,
		.timer = 255
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388BslResearcherOam_Walking[7] = {
	[0] = {
		.pFrame = sOamFrame_5a2584,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5a25bc,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5a25e8,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5a2614,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5a264c,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5a2678,
		.timer = 8
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2d28[2] = {
	[0] = {
		.pFrame = sOamFrame_5a2704,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2d38[3] = {
	[0] = {
		.pFrame = sOamFrame_5a26a4,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a26be,
		.timer = 4
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388BslResearcherOam_Turning[3] = {
	[0] = {
		.pFrame = sOamFrame_5a26be,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a26a4,
		.timer = 4
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388BslResearcherOam_Idle[2] = {
	[0] = {
		.pFrame = sOamFrame_5a26d8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2d78[2] = {
	[0] = {
		.pFrame = sOamFrame_5a2704,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2d88[2] = {
	[0] = {
		.pFrame = sOamFrame_5a26d8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a2d98[2] = {
	[0] = {
		.pFrame = sOamFrame_5a2704,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388MissileOam_Horizontal[3] = {
	[0] = {
		.pFrame = sOamFrame_5a2730,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5a273e,
		.timer = 2
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388MissileOam_Diagonal[3] = {
	[0] = {
		.pFrame = sOamFrame_5a274c,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5a275a,
		.timer = 2
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388MissileTrailOam[6] = {
	[0] = {
		.pFrame = sOamFrame_5a2768,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5a2770,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5a2778,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5a2780,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5a2788,
		.timer = 8
	},
	[5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388MissileExplosionOam_Small[6] = {
	[0] = {
		.pFrame = sOamFrame_5a2a02,
		.timer = 6
	},
	[1] = {
		.pFrame = sOamFrame_5a2a1c,
		.timer = 6
	},
	[2] = {
		.pFrame = sOamFrame_5a2a36,
		.timer = 6
	},
	[3] = {
		.pFrame = sOamFrame_5a2a50,
		.timer = 6
	},
	[4] = {
		.pFrame = sOamFrame_5a2a6a,
		.timer = 6
	},
	[5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388MissileExplosionOam_Big[11] = {
	[0] = {
		.pFrame = sOamFrame_5a2790,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5a27aa,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5a27dc,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5a2826,
		.timer = 6
	},
	[4] = {
		.pFrame = sOamFrame_5a287c,
		.timer = 6
	},
	[5] = {
		.pFrame = sOamFrame_5a28de,
		.timer = 6
	},
	[6] = {
		.pFrame = sOamFrame_5a2934,
		.timer = 6
	},
	[7] = {
		.pFrame = sOamFrame_5a297e,
		.timer = 6
	},
	[8] = {
		.pFrame = sOamFrame_5a29a4,
		.timer = 6
	},
	[9] = {
		.pFrame = sOamFrame_5a29c4,
		.timer = 6
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388XParasiteOam_Floating[7] = {
	[0] = {
		.pFrame = sOamFrame_5a29d2,
		.timer = 5
	},
	[1] = {
		.pFrame = sOamFrame_5a29da,
		.timer = 5
	},
	[2] = {
		.pFrame = sOamFrame_5a29e2,
		.timer = 5
	},
	[3] = {
		.pFrame = sOamFrame_5a29ea,
		.timer = 5
	},
	[4] = {
		.pFrame = sOamFrame_5a29f2,
		.timer = 5
	},
	[5] = {
		.pFrame = sOamFrame_5a29fa,
		.timer = 5
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388CaveEntranceBgOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5a2a84,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388BlackRectangeOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5a2ac8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

static const u16 sOamFrame_5a2ee8[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-5, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5a2ef6[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 2, 0, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5a2f04[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 6, 0, 0),
	OAM_ENTRY(8, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 8, 0, 0),
	OAM_ENTRY(-16, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 37, 0, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 5, 0, 0),
};

static const u16 sOamFrame_5a2f1e[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 9, 0, 0),
	OAM_ENTRY(-12, -18, OAM_DIMS_8x16, OAM_NO_FLIP, 72, 0, 0),
	OAM_ENTRY(8, -21, OAM_DIMS_8x16, OAM_NO_FLIP, 11, 0, 0),
	OAM_ENTRY(-16, -30, OAM_DIMS_8x8, OAM_NO_FLIP, 36, 0, 0),
};

static const u16 sOamFrame_5a2f38[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-7, -39, OAM_DIMS_16x32, OAM_NO_FLIP, 12, 0, 0),
	OAM_ENTRY(-10, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 75, 0, 0),
	OAM_ENTRY(9, -21, OAM_DIMS_8x8, OAM_NO_FLIP, 107, 0, 0),
};

static const u16 sOamFrame_5a2f4c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 14, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 18, 0, 0),
	OAM_ENTRY(-5, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 64, 0, 0),
};

static const u16 sOamFrame_5a2f60[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-7, -37, OAM_DIMS_16x32, OAM_NO_FLIP, 16, 0, 0),
	OAM_ENTRY(6, -15, OAM_DIMS_8x16, OAM_NO_FLIP, 82, 0, 0),
	OAM_ENTRY(9, -29, OAM_DIMS_8x8, OAM_NO_FLIP, 50, 0, 0),
};

static const u16 sOamFrame_5a2f74[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -39, OAM_DIMS_16x32, OAM_NO_FLIP, 20, 0, 0),
	OAM_ENTRY(8, -33, OAM_DIMS_8x32, OAM_NO_FLIP, 22, 0, 0),
	OAM_ENTRY(-16, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 19, 0, 0),
	OAM_ENTRY(-8, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 51, 0, 0),
};

static const u16 sOamFrame_5a2f8e[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-7, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 23, 0, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 121, 0, 0),
	OAM_ENTRY(9, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 57, 0, 0),
	OAM_ENTRY(-15, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 25, 0, 0),
};

static const u16 sOamFrame_5a2fa8[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-6, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 26, 0, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 83, 0, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 28, 0, 0),
};

static const u16 sOamFrame_5a2fbc[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 61, 0, 0),
	OAM_ENTRY(-11, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5a2fd0[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(2, -29, OAM_DIMS_8x8, OAM_NO_FLIP, 31, 0, 0),
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_X_FLIP, 2, 0, 0),
	OAM_ENTRY(-15, -16, OAM_DIMS_16x16, OAM_X_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5a2fe4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(4, -32, OAM_DIMS_8x16, OAM_NO_FLIP, 137, 0, 0),
	OAM_ENTRY(-8, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 168, 0, 0),
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_X_FLIP, 6, 0, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 8, 0, 0),
	OAM_ENTRY(8, -32, OAM_DIMS_8x8, OAM_X_FLIP, 37, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 5, 0, 0),
};

static const u16 sOamFrame_5a300a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 30, 0, 0),
	OAM_ENTRY(6, -30, OAM_DIMS_8x8, OAM_NO_FLIP, 31, 0, 0),
	OAM_ENTRY(-8, -40, OAM_DIMS_16x32, OAM_X_FLIP, 9, 0, 0),
	OAM_ENTRY(4, -18, OAM_DIMS_8x16, OAM_X_FLIP, 72, 0, 0),
	OAM_ENTRY(-16, -21, OAM_DIMS_8x16, OAM_X_FLIP, 11, 0, 0),
};

static const u16 sOamFrame_5a302a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(1, -27, OAM_DIMS_8x8, OAM_NO_FLIP, 60, 0, 0),
	OAM_ENTRY(-9, -39, OAM_DIMS_16x32, OAM_X_FLIP, 12, 0, 0),
	OAM_ENTRY(2, -7, OAM_DIMS_8x8, OAM_X_FLIP, 75, 0, 0),
	OAM_ENTRY(-17, -21, OAM_DIMS_8x8, OAM_X_FLIP, 107, 0, 0),
};

static const u16 sOamFrame_5a3044[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-3, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 61, 0, 0),
	OAM_ENTRY(-12, -40, OAM_DIMS_16x32, OAM_X_FLIP, 14, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 18, 0, 0),
};

static const u16 sOamFrame_5a3058[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-10, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 92, 0, 0),
	OAM_ENTRY(-9, -21, OAM_DIMS_16x16, OAM_X_FLIP, 80, 0, 0),
	OAM_ENTRY(-9, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 94, 0, 0),
	OAM_ENTRY(-14, -15, OAM_DIMS_8x16, OAM_X_FLIP, 82, 0, 0),
	OAM_ENTRY(-17, -29, OAM_DIMS_8x8, OAM_X_FLIP, 50, 0, 0),
};

static const u16 sOamFrame_5a3078[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-12, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 130, 0, 0),
	OAM_ENTRY(2, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-8, -39, OAM_DIMS_16x32, OAM_X_FLIP, 20, 0, 0),
	OAM_ENTRY(-16, -33, OAM_DIMS_8x32, OAM_X_FLIP, 22, 0, 0),
	OAM_ENTRY(0, -7, OAM_DIMS_8x8, OAM_X_FLIP, 51, 0, 0),
};

static const u16 sOamFrame_5a3098[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(1, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-9, -40, OAM_DIMS_16x32, OAM_X_FLIP, 23, 0, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_X_FLIP, 121, 0, 0),
	OAM_ENTRY(-17, -16, OAM_DIMS_8x16, OAM_X_FLIP, 57, 0, 0),
	OAM_ENTRY(7, -32, OAM_DIMS_8x8, OAM_X_FLIP, 25, 0, 0),
};

static const u16 sOamFrame_5a30be[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-6, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 134, 0, 0),
	OAM_ENTRY(2, -26, OAM_DIMS_8x8, OAM_NO_FLIP, 136, 0, 0),
	OAM_ENTRY(-10, -40, OAM_DIMS_16x32, OAM_X_FLIP, 26, 0, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x16, OAM_X_FLIP, 83, 0, 0),
	OAM_ENTRY(-2, -8, OAM_DIMS_16x8, OAM_X_FLIP, 28, 0, 0),
};

static const u16 sOamFrame_5a30de[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 146, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_XY_FLIP, 170, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 138, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 200, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 201, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 192, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3110[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 194, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 202, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 203, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3142[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 196, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 232, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 233, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3174[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-10, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 180, 0, 0),
	OAM_ENTRY(-11, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 174, 0, 0),
	OAM_ENTRY(-3, -33, OAM_DIMS_8x8, OAM_NO_FLIP, 143, 0, 0),
	OAM_ENTRY(-9, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 198, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 234, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 235, 0, 0),
	OAM_ENTRY(-18, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a31a6[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 200, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 201, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 192, 0, 0),
};

static const u16 sOamFrame_5a31d2[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 194, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 202, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 203, 0, 0),
};

static const u16 sOamFrame_5a31fe[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 196, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 232, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 233, 0, 0),
};

static const u16 sOamFrame_5a322a[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(2, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-6, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 186, 0, 0),
	OAM_ENTRY(-4, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 159, 0, 0),
	OAM_ENTRY(-7, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 198, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 234, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 235, 0, 0),
};

static const u16 sOamFrame_5a3256[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 146, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_XY_FLIP, 170, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 138, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 200, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 201, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 192, 0, 0),
    OAM_ENTRY(-23, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a328e[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 194, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 202, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 203, 0, 0),
    OAM_ENTRY(-23, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a32c6[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
    OAM_ENTRY(-12, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 196, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 232, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 233, 0, 0),
    OAM_ENTRY(-23, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a32fe[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-10, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 180, 0, 0),
    OAM_ENTRY(-11, -25, OAM_DIMS_16x8, OAM_NO_FLIP, 174, 0, 0),
    OAM_ENTRY(-3, -33, OAM_DIMS_8x8, OAM_NO_FLIP, 143, 0, 0),
    OAM_ENTRY(-9, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 198, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 234, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 235, 0, 0),
    OAM_ENTRY(-21, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 0, 0),
    OAM_ENTRY(-18, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3336[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(15, -25, OAM_DIMS_8x8, OAM_X_FLIP, 63, 0, 0),
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 200, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 201, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 192, 0, 0),
};

static const u16 sOamFrame_5a3368[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(15, -25, OAM_DIMS_8x8, OAM_X_FLIP, 63, 0, 0),
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 194, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 202, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 203, 0, 0),
};

static const u16 sOamFrame_5a339a[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(15, -25, OAM_DIMS_8x8, OAM_X_FLIP, 63, 0, 0),
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 196, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 232, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 233, 0, 0),
};

static const u16 sOamFrame_5a33cc[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(13, -25, OAM_DIMS_8x8, OAM_X_FLIP, 63, 0, 0),
    OAM_ENTRY(2, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-6, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 186, 0, 0),
    OAM_ENTRY(-4, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 159, 0, 0),
    OAM_ENTRY(-7, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 198, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 234, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 235, 0, 0),
};

static const u16 sOamFrame_5a33fe[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 256, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 206, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 260, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 268, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 270, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a342a[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 257, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 208, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 262, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 271, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 273, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a3456[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 258, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 210, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 264, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 300, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 302, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a3482[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-2, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 259, 0, 0),
    OAM_ENTRY(-12, -35, OAM_DIMS_16x16, OAM_NO_FLIP, 212, 0, 0),
    OAM_ENTRY(-9, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 274, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 303, 0, 0),
    OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 305, 0, 0),
    OAM_ENTRY(-19, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a34ae[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 288, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 218, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 216, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 260, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 268, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 270, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 206, 0, 0),
};

static const u16 sOamFrame_5a34e0[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 289, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 250, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 248, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 262, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 271, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 273, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 208, 0, 0),
};

static const u16 sOamFrame_5a3512[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 290, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 251, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 219, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 264, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 300, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 302, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 210, 0, 0),
};

static const u16 sOamFrame_5a3544[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 291, 0, 0),
    OAM_ENTRY(-2, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 221, 0, 0),
    OAM_ENTRY(14, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 252, 0, 0),
    OAM_ENTRY(-7, -36, OAM_DIMS_16x16, OAM_X_FLIP, 274, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 266, 0, 0),
    OAM_ENTRY(-6, -8, OAM_DIMS_16x8, OAM_X_FLIP, 303, 0, 0),
    OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_X_FLIP, 305, 0, 0),
    OAM_ENTRY(-4, -35, OAM_DIMS_16x16, OAM_X_FLIP, 212, 0, 0),
};

static const u16 sOamFrame_5a3576[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 256, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 206, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 260, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 268, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 270, 0, 0),
    OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 223, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a35a8[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 257, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 208, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 262, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 271, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 273, 0, 0),
    OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 223, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a35da[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 258, 0, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 210, 0, 0),
    OAM_ENTRY(-11, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 204, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 264, 0, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 300, 0, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 302, 0, 0),
    OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 223, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a360c[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-2, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 259, 0, 0),
    OAM_ENTRY(-12, -35, OAM_DIMS_16x16, OAM_NO_FLIP, 212, 0, 0),
    OAM_ENTRY(-9, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 274, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 303, 0, 0),
    OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 305, 0, 0),
    OAM_ENTRY(-20, -39, OAM_DIMS_8x8, OAM_NO_FLIP, 223, 0, 0),
    OAM_ENTRY(-19, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 0, 0),
};

static const u16 sOamFrame_5a363e[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 288, 0, 0),
    OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_X_FLIP, 223, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 218, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 216, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 260, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 268, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 270, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 206, 0, 0),
};

static const u16 sOamFrame_5a3676[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 289, 0, 0),
    OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_X_FLIP, 223, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 250, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 248, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 262, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 271, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 273, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 208, 0, 0),
};

static const u16 sOamFrame_5a36ae[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 290, 0, 0),
    OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_X_FLIP, 223, 0, 0),
    OAM_ENTRY(11, -38, OAM_DIMS_8x8, OAM_NO_FLIP, 251, 0, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 219, 0, 0),
    OAM_ENTRY(-5, -37, OAM_DIMS_16x16, OAM_X_FLIP, 204, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 264, 0, 0),
    OAM_ENTRY(-5, -8, OAM_DIMS_16x8, OAM_X_FLIP, 300, 0, 0),
    OAM_ENTRY(-13, -8, OAM_DIMS_8x8, OAM_X_FLIP, 302, 0, 0),
    OAM_ENTRY(-3, -36, OAM_DIMS_16x16, OAM_X_FLIP, 210, 0, 0),
};

static const u16 sOamFrame_5a36e6[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 291, 0, 0),
    OAM_ENTRY(-2, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 221, 0, 0),
    OAM_ENTRY(12, -39, OAM_DIMS_8x8, OAM_X_FLIP, 223, 0, 0),
    OAM_ENTRY(14, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 252, 0, 0),
    OAM_ENTRY(-7, -36, OAM_DIMS_16x16, OAM_X_FLIP, 274, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 266, 0, 0),
    OAM_ENTRY(-6, -8, OAM_DIMS_16x8, OAM_X_FLIP, 303, 0, 0),
    OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_X_FLIP, 305, 0, 0),
    OAM_ENTRY(-4, -35, OAM_DIMS_16x16, OAM_X_FLIP, 212, 0, 0),
};

static const u16 sOamFrame_5a371e[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-15, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 276, 0, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 278, 0, 0),
    OAM_ENTRY(-7, -42, OAM_DIMS_16x8, OAM_NO_FLIP, 285, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 320, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 322, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 354, 0, 0),
};

static const u16 sOamFrame_5a3744[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-12, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 279, 0, 0),
    OAM_ENTRY(4, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 281, 0, 0),
    OAM_ENTRY(-4, -42, OAM_DIMS_16x8, OAM_NO_FLIP, 317, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 323, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 325, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 357, 0, 0),
};

static const u16 sOamFrame_5a376a[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-10, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 282, 0, 0),
    OAM_ENTRY(6, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 284, 0, 0),
    OAM_ENTRY(-10, -42, OAM_DIMS_16x8, OAM_NO_FLIP, 124, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 320, 0, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_X_FLIP, 322, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 354, 0, 0),
};

static const u16 sOamFrame_5a3790[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-8, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 146, 0, 0),
	OAM_ENTRY(-1, -33, OAM_DIMS_8x8, OAM_XY_FLIP, 170, 0, 0),
	OAM_ENTRY(-8, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 138, 0, 0),
	OAM_ENTRY(-7, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-17, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-5, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5a37bc[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-9, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
	OAM_ENTRY(-3, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
	OAM_ENTRY(-10, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
	OAM_ENTRY(-8, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-18, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 66, 0, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5a37e8[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-10, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-4, -35, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-11, -28, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-9, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-19, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 70, 0, 0),
	OAM_ENTRY(8, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 8, 0, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 5, 0, 0),
};

static const u16 sOamFrame_5a381a[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-11, -38, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-4, -36, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-11, -28, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-19, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 73, 0, 0),
	OAM_ENTRY(-12, -18, OAM_DIMS_8x16, OAM_NO_FLIP, 72, 0, 0),
	OAM_ENTRY(8, -21, OAM_DIMS_8x16, OAM_NO_FLIP, 11, 0, 0),
};

static const u16 sOamFrame_5a384c[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-10, -38, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
	OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
	OAM_ENTRY(-10, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
	OAM_ENTRY(-9, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-19, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-7, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 76, 0, 0),
	OAM_ENTRY(-10, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 75, 0, 0),
	OAM_ENTRY(9, -21, OAM_DIMS_8x8, OAM_NO_FLIP, 107, 0, 0),
};

static const u16 sOamFrame_5a387e[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-8, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 146, 0, 0),
	OAM_ENTRY(-1, -35, OAM_DIMS_8x8, OAM_XY_FLIP, 170, 0, 0),
	OAM_ENTRY(-9, -27, OAM_DIMS_16x8, OAM_XY_FLIP, 138, 0, 0),
	OAM_ENTRY(-7, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-17, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 326, 0, 0),
	OAM_ENTRY(2, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 18, 0, 0),
};

static const u16 sOamFrame_5a38aa[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-7, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
	OAM_ENTRY(1, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
	OAM_ENTRY(-7, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
	OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-16, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-7, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 328, 0, 0),
	OAM_ENTRY(6, -15, OAM_DIMS_8x16, OAM_NO_FLIP, 82, 0, 0),
	OAM_ENTRY(2, -28, OAM_DIMS_8x8, OAM_NO_FLIP, 199, 0, 0),
};

static const u16 sOamFrame_5a38dc[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-8, -38, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-1, -36, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-8, -28, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-7, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-17, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-8, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 330, 0, 0),
	OAM_ENTRY(8, -17, OAM_DIMS_8x16, OAM_NO_FLIP, 86, 0, 0),
	OAM_ENTRY(-8, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 51, 0, 0),
	OAM_ENTRY(2, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 51, 0, 0),
};

static const u16 sOamFrame_5a3914[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-9, -38, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-2, -36, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-9, -28, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-8, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-18, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 332, 0, 0),
	OAM_ENTRY(9, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 57, 0, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 121, 0, 0),
};

static const u16 sOamFrame_5a3946[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-9, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 148, 0, 0),
	OAM_ENTRY(-2, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 140, 0, 0),
	OAM_ENTRY(-9, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 171, 0, 0),
	OAM_ENTRY(-8, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-6, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 334, 0, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 83, 0, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 28, 0, 0),
	OAM_ENTRY(-18, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3978[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(1, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-8, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-5, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-9, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_16x16, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5a399e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(2, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-7, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
	OAM_ENTRY(-4, -35, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
	OAM_ENTRY(-8, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 66, 0, 0),
	OAM_ENTRY(-15, -16, OAM_DIMS_16x16, OAM_X_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5a39c4[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(3, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-5, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
	OAM_ENTRY(-3, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
	OAM_ENTRY(-7, -38, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 70, 0, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x16, OAM_X_FLIP, 8, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 5, 0, 0),
};

static const u16 sOamFrame_5a39f0[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(3, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-5, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
	OAM_ENTRY(-3, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
	OAM_ENTRY(-6, -39, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 73, 0, 0),
	OAM_ENTRY(4, -18, OAM_DIMS_8x16, OAM_X_FLIP, 72, 0, 0),
	OAM_ENTRY(-16, -21, OAM_DIMS_8x16, OAM_X_FLIP, 11, 0, 0),
};

static const u16 sOamFrame_5a3a1c[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(3, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-6, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
	OAM_ENTRY(-4, -35, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
	OAM_ENTRY(-7, -38, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-9, -23, OAM_DIMS_16x16, OAM_X_FLIP, 76, 0, 0),
	OAM_ENTRY(2, -7, OAM_DIMS_8x8, OAM_X_FLIP, 75, 0, 0),
	OAM_ENTRY(-17, -21, OAM_DIMS_8x8, OAM_X_FLIP, 107, 0, 0),
};

static const u16 sOamFrame_5a3a48[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(1, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-7, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-6, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-9, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-12, -24, OAM_DIMS_16x16, OAM_X_FLIP, 326, 0, 0),
	OAM_ENTRY(-10, -8, OAM_DIMS_8x8, OAM_X_FLIP, 18, 0, 0),
};

static const u16 sOamFrame_5a3a6e[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(0, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-9, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
	OAM_ENTRY(-7, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
	OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-9, -21, OAM_DIMS_16x16, OAM_X_FLIP, 328, 0, 0),
	OAM_ENTRY(-14, -15, OAM_DIMS_8x16, OAM_X_FLIP, 82, 0, 0),
	OAM_ENTRY(-10, -24, OAM_DIMS_8x8, OAM_X_FLIP, 199, 0, 0),
};

static const u16 sOamFrame_5a3a9a[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(1, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-8, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
	OAM_ENTRY(-5, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
	OAM_ENTRY(-9, -38, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -23, OAM_DIMS_16x16, OAM_X_FLIP, 330, 0, 0),
	OAM_ENTRY(-16, -17, OAM_DIMS_8x16, OAM_X_FLIP, 86, 0, 0),
	OAM_ENTRY(0, -7, OAM_DIMS_8x8, OAM_X_FLIP, 51, 0, 0),
	OAM_ENTRY(-10, -18, OAM_DIMS_8x8, OAM_X_FLIP, 51, 0, 0),
};

static const u16 sOamFrame_5a3acc[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(2, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-6, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 184, 0, 0),
	OAM_ENTRY(-4, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 158, 0, 0),
	OAM_ENTRY(-8, -38, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_X_FLIP, 332, 0, 0),
	OAM_ENTRY(-17, -16, OAM_DIMS_8x16, OAM_X_FLIP, 57, 0, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_X_FLIP, 121, 0, 0),
};

static const u16 sOamFrame_5a3af8[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(2, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-6, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 154, 0, 0),
	OAM_ENTRY(-4, -35, OAM_DIMS_8x16, OAM_NO_FLIP, 157, 0, 0),
	OAM_ENTRY(-8, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-10, -24, OAM_DIMS_16x16, OAM_X_FLIP, 334, 0, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x16, OAM_X_FLIP, 83, 0, 0),
	OAM_ENTRY(-2, -8, OAM_DIMS_16x8, OAM_X_FLIP, 28, 0, 0),
};

static const u16 sOamFrame_5a3b24[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-10, -37, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-3, -35, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-10, -27, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 336, 0, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 338, 0, 0),
	OAM_ENTRY(-19, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3b50[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-10, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-3, -38, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-10, -30, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-9, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-19, -30, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 340, 0, 0),
	OAM_ENTRY(-1, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(-2, -29, OAM_DIMS_8x8, OAM_NO_FLIP, 199, 0, 0),
};

static const u16 sOamFrame_5a3b82[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-11, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-4, -34, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-11, -26, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-8, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 342, 0, 0),
	OAM_ENTRY(-8, -7, OAM_DIMS_16x8, OAM_NO_FLIP, 370, 0, 0),
};

static const u16 sOamFrame_5a3bae[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-11, -30, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-4, -28, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-11, -20, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-20, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-9, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 344, 0, 0),
	OAM_ENTRY(-9, -2, OAM_DIMS_16x8, OAM_NO_FLIP, 346, 0, 0),
};

static const u16 sOamFrame_5a3bda[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-12, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-5, -26, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-12, -19, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -29, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-20, -19, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-9, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 348, 0, 0),
};

static const u16 sOamFrame_5a3c00[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-11, -33, OAM_DIMS_16x8, OAM_NO_FLIP, 178, 0, 0),
	OAM_ENTRY(-4, -31, OAM_DIMS_8x8, OAM_XY_FLIP, 173, 0, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_16x8, OAM_XY_FLIP, 141, 0, 0),
	OAM_ENTRY(-10, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-20, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
	OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 350, 0, 0),
	OAM_ENTRY(-9, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 378, 0, 0),
};

static const u16 sOamFrame_5a3c2c[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(3, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-5, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-3, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 336, 0, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 338, 0, 0),
};

static const u16 sOamFrame_5a3c52[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(3, -30, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-6, -39, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-4, -38, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-7, -40, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 340, 0, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_8x16, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-6, -29, OAM_DIMS_8x8, OAM_X_FLIP, 199, 0, 0),
};

static const u16 sOamFrame_5a3c7e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-5, -35, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-2, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-8, -23, OAM_DIMS_16x16, OAM_X_FLIP, 342, 0, 0),
	OAM_ENTRY(-8, -7, OAM_DIMS_16x8, OAM_X_FLIP, 370, 0, 0),
};

static const u16 sOamFrame_5a3ca4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(4, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-4, -28, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-2, -27, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-6, -30, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-7, -18, OAM_DIMS_16x16, OAM_X_FLIP, 344, 0, 0),
	OAM_ENTRY(-7, -2, OAM_DIMS_16x8, OAM_X_FLIP, 346, 0, 0),
};

static const u16 sOamFrame_5a3cca[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(4, -19, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-4, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-2, -26, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-6, -29, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-7, -16, OAM_DIMS_16x16, OAM_X_FLIP, 348, 0, 0),
};

static const u16 sOamFrame_5a3cea[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(4, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
	OAM_ENTRY(-4, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(-2, -31, OAM_DIMS_8x16, OAM_NO_FLIP, 156, 0, 0),
	OAM_ENTRY(-6, -34, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_X_FLIP, 350, 0, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_16x8, OAM_X_FLIP, 378, 0, 0),
};

static const u16 sOamFrame_5a3d10[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 395, 0, 0),
    OAM_ENTRY(-12, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 413, 0, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 417, 0, 0),
    OAM_ENTRY(-7, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 448, 0, 0),
    OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3d36[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 395, 0, 0),
    OAM_ENTRY(-12, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 413, 0, 0),
    OAM_ENTRY(-5, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 418, 0, 0),
    OAM_ENTRY(-10, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 450, 0, 0),
    OAM_ENTRY(6, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 419, 0, 0),
    OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3d62[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 396, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 475, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 420, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 484, 0, 0),
    OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 486, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3d8e[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 394, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 411, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 422, 0, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 487, 0, 0),
    OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 489, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3dba[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 394, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 411, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 426, 0, 0),
    OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 490, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3de0[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 395, 0, 0),
    OAM_ENTRY(-12, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 413, 0, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 428, 0, 0),
    OAM_ENTRY(-7, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 492, 0, 0),
    OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3e06[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -37, OAM_DIMS_8x8, OAM_NO_FLIP, 395, 0, 0),
    OAM_ENTRY(-12, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 413, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 430, 0, 0),
    OAM_ENTRY(-11, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 462, 0, 0),
    OAM_ENTRY(-10, -37, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3e2c[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 396, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 475, 0, 0),
    OAM_ENTRY(-19, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 465, 0, 0),
    OAM_ENTRY(-11, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 434, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3e52[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 394, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 411, 0, 0),
    OAM_ENTRY(-11, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 437, 0, 0),
    OAM_ENTRY(-11, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 469, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3e78[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-3, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 394, 0, 0),
    OAM_ENTRY(-12, -33, OAM_DIMS_16x16, OAM_NO_FLIP, 411, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 441, 0, 0),
    OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 505, 0, 0),
    OAM_ENTRY(-10, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 144, 0, 0),
    OAM_ENTRY(-20, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 150, 0, 0),
};

static const u16 sOamFrame_5a3e9e[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 399, 0, 0),
    OAM_ENTRY(-2, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 408, 0, 0),
    OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_X_FLIP, 417, 0, 0),
    OAM_ENTRY(-9, -16, OAM_DIMS_16x16, OAM_X_FLIP, 448, 0, 0),
    OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3ec4[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 399, 0, 0),
    OAM_ENTRY(-2, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 408, 0, 0),
    OAM_ENTRY(-3, -24, OAM_DIMS_8x8, OAM_X_FLIP, 418, 0, 0),
    OAM_ENTRY(-6, -16, OAM_DIMS_16x16, OAM_X_FLIP, 450, 0, 0),
    OAM_ENTRY(-14, -9, OAM_DIMS_8x8, OAM_X_FLIP, 419, 0, 0),
    OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3ef0[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 400, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 415, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 420, 0, 0),
    OAM_ENTRY(-6, -8, OAM_DIMS_16x8, OAM_X_FLIP, 484, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_X_FLIP, 486, 0, 0),
};

static const u16 sOamFrame_5a3f1c[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 398, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 407, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_X_FLIP, 422, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
    OAM_ENTRY(-6, -8, OAM_DIMS_16x8, OAM_X_FLIP, 487, 0, 0),
    OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_X_FLIP, 489, 0, 0),
};

static const u16 sOamFrame_5a3f48[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 398, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 407, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 426, 0, 0),
    OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 490, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3f6e[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 399, 0, 0),
    OAM_ENTRY(-2, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 408, 0, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_X_FLIP, 428, 0, 0),
    OAM_ENTRY(-9, -8, OAM_DIMS_16x8, OAM_X_FLIP, 492, 0, 0),
    OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3f94[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -27, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -35, OAM_DIMS_8x8, OAM_NO_FLIP, 399, 0, 0),
    OAM_ENTRY(-2, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 408, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_X_FLIP, 430, 0, 0),
    OAM_ENTRY(-21, -16, OAM_DIMS_32x16, OAM_X_FLIP, 462, 0, 0),
    OAM_ENTRY(-6, -37, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3fba[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 400, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 415, 0, 0),
    OAM_ENTRY(-13, -16, OAM_DIMS_32x16, OAM_X_FLIP, 465, 0, 0),
    OAM_ENTRY(-5, -24, OAM_DIMS_16x8, OAM_X_FLIP, 434, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a3fe0[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 398, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 407, 0, 0),
    OAM_ENTRY(-5, -24, OAM_DIMS_16x8, OAM_X_FLIP, 437, 0, 0),
    OAM_ENTRY(-21, -16, OAM_DIMS_32x16, OAM_X_FLIP, 469, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

static const u16 sOamFrame_5a4006[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(4, -26, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 0, 0),
    OAM_ENTRY(-5, -34, OAM_DIMS_8x8, OAM_NO_FLIP, 398, 0, 0),
    OAM_ENTRY(-2, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 407, 0, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 441, 0, 0),
    OAM_ENTRY(-8, -8, OAM_DIMS_16x8, OAM_X_FLIP, 505, 0, 0),
    OAM_ENTRY(-6, -36, OAM_DIMS_16x16, OAM_X_FLIP, 144, 0, 0),
};

const struct FrameData sOam_5a402c[11] = {
    [0] = {
            .pFrame = sOamFrame_5a2ee8,
            .timer = 3
    },
    [1] = {
            .pFrame = sOamFrame_5a2ef6,
            .timer = 3
    },
    [2] = {
            .pFrame = sOamFrame_5a2f04,
            .timer = 3
    },
    [3] = {
            .pFrame = sOamFrame_5a2f1e,
            .timer = 3
    },
    [4] = {
            .pFrame = sOamFrame_5a2f38,
            .timer = 3
    },
    [5] = {
            .pFrame = sOamFrame_5a2f4c,
            .timer = 3
    },
    [6] = {
            .pFrame = sOamFrame_5a2f60,
            .timer = 3
    },
    [7] = {
            .pFrame = sOamFrame_5a2f74,
            .timer = 3
    },
    [8] = {
            .pFrame = sOamFrame_5a2f8e,
            .timer = 3
    },
    [9] = {
            .pFrame = sOamFrame_5a2fa8,
            .timer = 3
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4084[11] = {
    [0] = {
            .pFrame = sOamFrame_5a2fbc,
            .timer = 3
    },
    [1] = {
            .pFrame = sOamFrame_5a2fd0,
            .timer = 3
    },
    [2] = {
            .pFrame = sOamFrame_5a2fe4,
            .timer = 3
    },
    [3] = {
            .pFrame = sOamFrame_5a300a,
            .timer = 3
    },
    [4] = {
            .pFrame = sOamFrame_5a302a,
            .timer = 3
    },
    [5] = {
            .pFrame = sOamFrame_5a3044,
            .timer = 3
    },
    [6] = {
            .pFrame = sOamFrame_5a3058,
            .timer = 3
    },
    [7] = {
            .pFrame = sOamFrame_5a3078,
            .timer = 3
    },
    [8] = {
            .pFrame = sOamFrame_5a3098,
            .timer = 3
    },
    [9] = {
            .pFrame = sOamFrame_5a30be,
            .timer = 3
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_IdleLeft[4] = {
    [0] = {
            .pFrame = sOamFrame_5a30de,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a3110,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a3142,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a40fc[3] = {
    [0] = {
            .pFrame = sOamFrame_5a3174,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a3110,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_IdleRight[4] = {
    [0] = {
            .pFrame = sOamFrame_5a31a6,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a31d2,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a31fe,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4134[3] = {
    [0] = {
            .pFrame = sOamFrame_5a322a,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a31d2,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_MissileArmedLeft[4] = {
    [0] = {
            .pFrame = sOamFrame_5a3256,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a328e,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a32c6,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_FiringMissileLeft[3] = {
    [0] = {
            .pFrame = sOamFrame_5a32fe,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a328e,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4184[4] = {
    [0] = {
            .pFrame = sOamFrame_5a3336,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a3368,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a339a,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a41a4[3] = {
    [0] = {
            .pFrame = sOamFrame_5a33cc,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a3368,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a41bc[4] = {
    [0] = {
            .pFrame = sOamFrame_5a33fe,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a342a,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a3456,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a41dc[3] = {
    [0] = {
            .pFrame = sOamFrame_5a3482,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a342a,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a41f4[4] = {
    [0] = {
            .pFrame = sOamFrame_5a34ae,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a34e0,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a3512,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4214[3] = {
    [0] = {
            .pFrame = sOamFrame_5a3544,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a34e0,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_MissileArmedUpLeft[4] = {
    [0] = {
            .pFrame = sOamFrame_5a3576,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a35a8,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a35da,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_FiringMissileUpLeft[3] = {
    [0] = {
            .pFrame = sOamFrame_5a360c,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a35a8,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4264[4] = {
    [0] = {
            .pFrame = sOamFrame_5a363e,
            .timer = 16
    },
    [1] = {
            .pFrame = sOamFrame_5a3676,
            .timer = 16
    },
    [2] = {
            .pFrame = sOamFrame_5a36ae,
            .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4284[3] = {
    [0] = {
            .pFrame = sOamFrame_5a36e6,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a3676,
            .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_TurningRight[4] = {
    [0] = {
            .pFrame = sOamFrame_5a371e,
            .timer = 2
    },
    [1] = {
            .pFrame = sOamFrame_5a3744,
            .timer = 2
    },
    [2] = {
            .pFrame = sOamFrame_5a376a,
            .timer = 2
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_TurningLeft[4] = {
    [0] = {
            .pFrame = sOamFrame_5a376a,
            .timer = 2
    },
    [1] = {
            .pFrame = sOamFrame_5a3744,
            .timer = 2
    },
    [2] = {
            .pFrame = sOamFrame_5a371e,
            .timer = 2
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a42dc[11] = {
    [0] = {
            .pFrame = sOamFrame_5a3790,
            .timer = 3
    },
    [1] = {
            .pFrame = sOamFrame_5a37bc,
            .timer = 3
    },
    [2] = {
            .pFrame = sOamFrame_5a37e8,
            .timer = 3
    },
    [3] = {
            .pFrame = sOamFrame_5a381a,
            .timer = 3
    },
    [4] = {
            .pFrame = sOamFrame_5a384c,
            .timer = 3
    },
    [5] = {
            .pFrame = sOamFrame_5a387e,
            .timer = 3
    },
    [6] = {
            .pFrame = sOamFrame_5a38aa,
            .timer = 3
    },
    [7] = {
            .pFrame = sOamFrame_5a38dc,
            .timer = 3
    },
    [8] = {
            .pFrame = sOamFrame_5a3914,
            .timer = 3
    },
    [9] = {
            .pFrame = sOamFrame_5a3946,
            .timer = 3
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4334[11] = {
    [0] = {
            .pFrame = sOamFrame_5a3978,
            .timer = 3
    },
    [1] = {
            .pFrame = sOamFrame_5a399e,
            .timer = 3
    },
    [2] = {
            .pFrame = sOamFrame_5a39c4,
            .timer = 3
    },
    [3] = {
            .pFrame = sOamFrame_5a39f0,
            .timer = 3
    },
    [4] = {
            .pFrame = sOamFrame_5a3a1c,
            .timer = 3
    },
    [5] = {
            .pFrame = sOamFrame_5a3a48,
            .timer = 3
    },
    [6] = {
            .pFrame = sOamFrame_5a3a6e,
            .timer = 3
    },
    [7] = {
            .pFrame = sOamFrame_5a3a9a,
            .timer = 3
    },
    [8] = {
            .pFrame = sOamFrame_5a3acc,
            .timer = 3
    },
    [9] = {
            .pFrame = sOamFrame_5a3af8,
            .timer = 3
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a438c[4] = {
    [0] = {
            .pFrame = sOamFrame_5a3b24,
            .timer = 6
    },
    [1] = {
            .pFrame = sOamFrame_5a3b50,
            .timer = 6
    },
    [2] = {
            .pFrame = sOamFrame_5a3b82,
            .timer = 4
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a43ac[2] = {
    [0] = {
            .pFrame = sOamFrame_5a3bae,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a43bc[3] = {
    [0] = {
            .pFrame = sOamFrame_5a3bda,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a3c00,
            .timer = 3
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a43d4[4] = {
    [0] = {
            .pFrame = sOamFrame_5a3c2c,
            .timer = 6
    },
    [1] = {
            .pFrame = sOamFrame_5a3c52,
            .timer = 6
    },
    [2] = {
            .pFrame = sOamFrame_5a3c7e,
            .timer = 4
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a43f4[2] = {
    [0] = {
            .pFrame = sOamFrame_5a3ca4,
            .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5a4404[3] = {
    [0] = {
            .pFrame = sOamFrame_5a3cca,
            .timer = 4
    },
    [1] = {
            .pFrame = sOamFrame_5a3cea,
            .timer = 3
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_WalkingLeft[11] = {
    [0] = {
            .pFrame = sOamFrame_5a3d10,
            .timer = 5
    },
    [1] = {
            .pFrame = sOamFrame_5a3d36,
            .timer = 5
    },
    [2] = {
            .pFrame = sOamFrame_5a3d62,
            .timer = 5
    },
    [3] = {
            .pFrame = sOamFrame_5a3d8e,
            .timer = 5
    },
    [4] = {
            .pFrame = sOamFrame_5a3dba,
            .timer = 5
    },
    [5] = {
            .pFrame = sOamFrame_5a3de0,
            .timer = 5
    },
    [6] = {
            .pFrame = sOamFrame_5a3e06,
            .timer = 5
    },
    [7] = {
            .pFrame = sOamFrame_5a3e2c,
            .timer = 5
    },
    [8] = {
            .pFrame = sOamFrame_5a3e52,
            .timer = 5
    },
    [9] = {
            .pFrame = sOamFrame_5a3e78,
            .timer = 5
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroInSr388SamusOam_WalkingRight[11] = {
    [0] = {
            .pFrame = sOamFrame_5a3e9e,
            .timer = 5
    },
    [1] = {
            .pFrame = sOamFrame_5a3ec4,
            .timer = 5
    },
    [2] = {
            .pFrame = sOamFrame_5a3ef0,
            .timer = 5
    },
    [3] = {
            .pFrame = sOamFrame_5a3f1c,
            .timer = 5
    },
    [4] = {
            .pFrame = sOamFrame_5a3f48,
            .timer = 5
    },
    [5] = {
            .pFrame = sOamFrame_5a3f6e,
            .timer = 5
    },
    [6] = {
            .pFrame = sOamFrame_5a3f94,
            .timer = 5
    },
    [7] = {
            .pFrame = sOamFrame_5a3fba,
            .timer = 5
    },
    [8] = {
            .pFrame = sOamFrame_5a3fe0,
            .timer = 5
    },
    [9] = {
            .pFrame = sOamFrame_5a4006,
            .timer = 5
    },
    [10] = FRAME_DATA_TERMINATOR
};

const u32 sIntroHornoadEncounterBgGfx[4027] = INCBIN_U32("data/new_file_intro/hornoad_encounter_bg.gfx.lz");

const u32 sTilemap_5a83b8[196] = INCBIN_U32("data/new_file_intro/5a83b8.tm.lz");
const u32 sTilemap_5a86c8[479] = INCBIN_U32("data/new_file_intro/5a86c8.tm.lz");

const u16 sPal_5a8e44[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5a8e44.pal");

const u32 sTilemap_5a9044[135] = INCBIN_U32("data/new_file_intro/5a9044.tm.lz");

const u16 sPal_5a9260[15 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5a9260.pal");
const u16 sPal_5a9440[15 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5a9440.pal");

const u16 sArray_5a9620[30] = {
	C_16_2_8(0, 36),
	C_16_2_8(1, 12),
	C_16_2_8(2, 12),
	C_16_2_8(3, 36),
	C_16_2_8(2, 12),
	C_16_2_8(1, 12),
	C_16_2_8(0, 36),
	C_16_2_8(1, 12),
	C_16_2_8(2, 12),
	C_16_2_8(3, 36),
	C_16_2_8(4, 12),
	C_16_2_8(5, 12),
	C_16_2_8(6, 12),
	C_16_2_8(7, 12),
	C_16_2_8(11, 36),
	C_16_2_8(10, 12),
	C_16_2_8(9, 12),
	C_16_2_8(8, 36),
	C_16_2_8(9, 12),
	C_16_2_8(10, 12),
	C_16_2_8(11, 36),
	C_16_2_8(10, 12),
	C_16_2_8(9, 12),
	C_16_2_8(8, 36),
	C_16_2_8(9, 12),
	C_16_2_8(10, 12),
	C_16_2_8(11, 36),
	C_16_2_8(10, 12),
	C_16_2_8(9, 12),
	C_16_2_8(8, 36)
};

const u32 sIntroMetroidVaccineObjGfx[1485] = INCBIN_U32("data/new_file_intro/metroid_vaccine_obj.gfx.lz");

static const u16 sOamFrame_5aad90[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-39, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
};

static const u16 sOamFrame_5aaefa[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-38, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
};

static const u16 sOamFrame_5ab064[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-37, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
};

static const u16 sOamFrame_5ab1ce[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-36, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
};

static const u16 sOamFrame_5ab338[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-34, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
};

static const u16 sOamFrame_5ab4a2[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-32, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
};

static const u16 sOamFrame_5ab60c[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
};

static const u16 sOamFrame_5ab776[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-27, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
};

static const u16 sOamFrame_5ab8e0[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
};

static const u16 sOamFrame_5aba4a[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-21, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5abbb4[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-18, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
};

static const u16 sOamFrame_5abd1e[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-14, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5abe88[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-11, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5abff2[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-1, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5ac15c[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-4, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
};

static const u16 sOamFrame_5ac2c6[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-7, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5ac430[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(3, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
};

static const u16 sOamFrame_5ac59a[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(6, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
};

static const u16 sOamFrame_5ac704[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(10, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
};

static const u16 sOamFrame_5ac86e[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(13, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
};

static const u16 sOamFrame_5ac9d8[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(16, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
};

static const u16 sOamFrame_5acb42[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(19, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
};

static const u16 sOamFrame_5accac[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(22, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
};

static const u16 sOamFrame_5ace16[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
};

static const u16 sOamFrame_5acf80[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(26, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
};

static const u16 sOamFrame_5ad0ea[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(28, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5ad254[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(29, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5ad3be[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
};

static const u16 sOamFrame_5ad528[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(31, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5ad692[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(31, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5ad7fc[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
};

static const u16 sOamFrame_5ad966[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(29, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
};

static const u16 sOamFrame_5adad0[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(28, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
};

static const u16 sOamFrame_5adc3a[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(26, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
};

static const u16 sOamFrame_5adda4[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
};

static const u16 sOamFrame_5adf0e[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(22, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
};

static const u16 sOamFrame_5ae078[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(19, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
};

static const u16 sOamFrame_5ae1e2[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(16, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
};

static const u16 sOamFrame_5ae34c[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(13, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
};

static const u16 sOamFrame_5ae4b6[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(10, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5ae620[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(6, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
};

static const u16 sOamFrame_5ae78a[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(3, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5ae8f4[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-1, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5aea5e[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-4, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
};

static const u16 sOamFrame_5aebc8[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-7, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
};

static const u16 sOamFrame_5aed32[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-11, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
};

static const u16 sOamFrame_5aee9c[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-14, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
};

static const u16 sOamFrame_5af006[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-18, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
};

static const u16 sOamFrame_5af170[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-21, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
};

static const u16 sOamFrame_5af2da[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
};

static const u16 sOamFrame_5af444[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-27, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
};

static const u16 sOamFrame_5af5ae[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
};

static const u16 sOamFrame_5af718[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-32, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 224, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
};

static const u16 sOamFrame_5af882[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-34, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 192, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 196, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 0, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 4, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 256, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
};

static const u16 sOamFrame_5af9ec[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-36, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
};

static const u16 sOamFrame_5afb56[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-37, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(26, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-34, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(28, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-36, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(19, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-27, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(6, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-14, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-7, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-1, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-21, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(13, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-1, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 128, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 132, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5afcc0[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-38, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-38, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(30, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-32, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(24, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-21, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(13, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-14, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(19, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-27, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(28, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-36, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(31, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-39, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(26, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-34, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(3, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-11, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-11, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(3, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-34, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-4, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 96, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 100, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 352, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 356, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 288, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 292, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 32, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 36, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 164, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_X_FLIP, 384, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_X_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5afe2a[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-39, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-37, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-30, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(22, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-18, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(10, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-4, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-4, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(10, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-18, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(22, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-30, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(29, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(30, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(13, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-21, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-1, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-7, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-14, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(6, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-27, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(19, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-36, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-1, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-7, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 64, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 64, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 68, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 324, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 256, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 260, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 192, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 196, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 416, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 0, 0),
};

static const u16 sOamFrame_5aff94[OAM_DATA_SIZE(60)] = {
	60,
	OAM_ENTRY(-39, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, -96, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-36, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(28, -88, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-27, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(19, -80, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-14, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(6, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-7, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-1, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(13, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-21, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(24, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(-32, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(30, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-38, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(29, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(-37, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(22, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(-30, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(10, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-18, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 0, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 4, 0),
	OAM_ENTRY(-18, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(10, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-30, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 1, 0),
	OAM_ENTRY(22, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 3, 0),
	OAM_ENTRY(-37, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(29, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-39, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(31, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-34, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 2, 0),
	OAM_ENTRY(26, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 2, 0),
	OAM_ENTRY(-24, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(16, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(-11, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 3, 0),
	OAM_ENTRY(3, 48, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 1, 0),
	OAM_ENTRY(3, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 414, 4, 0),
	OAM_ENTRY(-11, 56, OAM_DIMS_8x8, OAM_NO_FLIP, 415, 0, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 32, 0, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 36, 0, 0),
	OAM_ENTRY(0, -88, OAM_DIMS_32x8, OAM_X_FLIP, 96, 0, 0),
	OAM_ENTRY(-32, -88, OAM_DIMS_32x8, OAM_X_FLIP, 100, 0, 0),
	OAM_ENTRY(0, -72, OAM_DIMS_32x8, OAM_X_FLIP, 352, 0, 0),
	OAM_ENTRY(-32, -72, OAM_DIMS_32x8, OAM_X_FLIP, 356, 0, 0),
	OAM_ENTRY(-32, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, -56, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(0, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 0, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_X_FLIP, 0, 0, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_X_FLIP, 4, 0, 0),
	OAM_ENTRY(0, 40, OAM_DIMS_32x8, OAM_X_FLIP, 224, 0, 0),
	OAM_ENTRY(-32, 40, OAM_DIMS_32x8, OAM_X_FLIP, 228, 0, 0),
	OAM_ENTRY(-32, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 0, 0),
	OAM_ENTRY(0, 56, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 0, 0),
};

static const u16 sOamFrame_5b00fe[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-112, -59, OAM_DIMS_8x16, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b0106[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-103, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_16x16, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b0114[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-103, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_16x16, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-96, -59, OAM_DIMS_8x16, OAM_NO_FLIP, 10, 6, 0),
};

static const u16 sOamFrame_5b0128[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-103, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-87, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 148, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b013c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-80, -59, OAM_DIMS_8x16, OAM_NO_FLIP, 12, 6, 0),
};

static const u16 sOamFrame_5b0150[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 150, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-80, -59, OAM_DIMS_16x16, OAM_NO_FLIP, 12, 6, 0),
};

static const u16 sOamFrame_5b016a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 150, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-88, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 11, 6, 0),
};

static const u16 sOamFrame_5b0184[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-80, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 12, 6, 0),
};

static const u16 sOamFrame_5b019e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-44, 31, OAM_DIMS_8x8, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-48, -59, OAM_DIMS_8x16, OAM_NO_FLIP, 16, 6, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b01c4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-48, -59, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 6, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b01e4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 39, OAM_DIMS_8x8, OAM_NO_FLIP, 170, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-56, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 15, 6, 0),
};

static const u16 sOamFrame_5b020a[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 39, OAM_DIMS_16x8, OAM_NO_FLIP, 170, 5, 0),
	OAM_ENTRY(-48, -59, OAM_DIMS_32x16, OAM_NO_FLIP, 16, 6, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b0230[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-13, 31, OAM_DIMS_8x32, OAM_NO_FLIP, 140, 5, 0),
	OAM_ENTRY(-29, 39, OAM_DIMS_16x8, OAM_NO_FLIP, 170, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-72, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 13, 6, 0),
};

static const u16 sOamFrame_5b025c[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 31, OAM_DIMS_32x32, OAM_NO_FLIP, 138, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-64, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 14, 6, 0),
};

static const u16 sOamFrame_5b0282[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 31, OAM_DIMS_32x32, OAM_NO_FLIP, 138, 5, 0),
	OAM_ENTRY(3, 31, OAM_DIMS_8x32, OAM_NO_FLIP, 142, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-56, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 15, 6, 0),
};

static const u16 sOamFrame_5b02ae[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 31, OAM_DIMS_32x32, OAM_NO_FLIP, 138, 5, 0),
	OAM_ENTRY(3, 31, OAM_DIMS_16x32, OAM_NO_FLIP, 142, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-48, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 16, 6, 0),
};

static const u16 sOamFrame_5b02da[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-103, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 146, 5, 0),
	OAM_ENTRY(-71, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 182, 5, 0),
	OAM_ENTRY(-44, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 136, 5, 0),
	OAM_ENTRY(-29, 31, OAM_DIMS_64x32, OAM_NO_FLIP, 138, 5, 0),
	OAM_ENTRY(-112, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 6, 0),
	OAM_ENTRY(-48, -59, OAM_DIMS_64x32, OAM_NO_FLIP, 16, 6, 0),
	OAM_ENTRY(16, -59, OAM_DIMS_16x32, OAM_NO_FLIP, 24, 6, 0),
};

static const u16 sOamFrame_5b0306[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-128, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b030e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-126, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b0316[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-124, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b031e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-122, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b0326[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-128, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b032e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-126, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b0336[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-124, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b033e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-122, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b0346[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-120, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b034e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-118, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-126, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
};

static const u16 sOamFrame_5b035c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-116, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-124, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
};

static const u16 sOamFrame_5b036a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-114, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-122, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
};

static const u16 sOamFrame_5b0378[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-128, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0380[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-126, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0388[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-124, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0390[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-122, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0398[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-120, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03a0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-118, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03a8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-116, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03b0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-114, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03b8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-112, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03c0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-110, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03c8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-108, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03d0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-106, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03d8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-104, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03e0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-102, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03e8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-100, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03f0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-98, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b03f8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-96, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0400[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-94, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b040e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 28, 5, 0),
	OAM_ENTRY(-92, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 332, 5, 0),
};

static const u16 sOamFrame_5b041c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 30, 5, 0),
	OAM_ENTRY(-90, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 336, 5, 0),
};

static const u16 sOamFrame_5b042a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 90, 5, 0),
	OAM_ENTRY(-88, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 340, 5, 0),
};

static const u16 sOamFrame_5b0438[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 92, 5, 0),
	OAM_ENTRY(-86, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 344, 5, 0),
};

static const u16 sOamFrame_5b0446[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 94, 5, 0),
	OAM_ENTRY(-84, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 348, 5, 0),
};

static const u16 sOamFrame_5b0454[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 154, 5, 0),
	OAM_ENTRY(-82, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 360, 5, 0),
};

static const u16 sOamFrame_5b0462[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 156, 5, 0),
	OAM_ENTRY(-80, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 364, 5, 0),
};

static const u16 sOamFrame_5b0470[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 158, 5, 0),
	OAM_ENTRY(-78, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 368, 5, 0),
};

static const u16 sOamFrame_5b047e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 274, 5, 0),
	OAM_ENTRY(-76, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 372, 5, 0),
};

static const u16 sOamFrame_5b048c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 276, 5, 0),
	OAM_ENTRY(-74, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 376, 5, 0),
};

static const u16 sOamFrame_5b049a[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 278, 5, 0),
};

static const u16 sOamFrame_5b04a2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 216, 5, 0),
};

static const u16 sOamFrame_5b04aa[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 218, 5, 0),
};

static const u16 sOamFrame_5b04b2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 220, 5, 0),
};

static const u16 sOamFrame_5b04ba[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 222, 5, 0),
};

static const u16 sOamFrame_5b04c2[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 380, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 266, 5, 0),
};

static const u16 sOamFrame_5b04d0[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 381, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 210, 5, 0),
};

static const u16 sOamFrame_5b04de[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 382, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 212, 5, 0),
};

static const u16 sOamFrame_5b04ec[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 214, 5, 0),
	OAM_ENTRY(-48, 72, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b04fa[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 392, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 268, 5, 0),
};

static const u16 sOamFrame_5b0508[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 394, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 270, 5, 0),
};

static const u16 sOamFrame_5b0516[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-48, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 396, 5, 0),
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b0524[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 280, 5, 0),
	OAM_ENTRY(-48, 72, OAM_DIMS_16x8, OAM_NO_FLIP, 398, 5, 0),
};

static const u16 sOamFrame_5b0532[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 282, 5, 0),
	OAM_ENTRY(-56, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 400, 5, 0),
};

static const u16 sOamFrame_5b0540[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 284, 5, 0),
	OAM_ENTRY(-56, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 404, 0, 0),
};

static const u16 sOamFrame_5b054e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, 72, OAM_DIMS_16x16, OAM_NO_FLIP, 286, 5, 0),
	OAM_ENTRY(-56, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 408, 5, 0),
};

static const u16 sOamFrame_5b055c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-56, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0564[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-54, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b056c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-52, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0574[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-50, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b057c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-48, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0584[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-46, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b058c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-44, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0594[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-42, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b059c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-40, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05a4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-38, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05ac[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-36, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05b4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-34, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05bc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-32, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05c4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-30, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05cc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-28, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05d4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-26, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05dc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-24, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05e4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-22, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05ec[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-20, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05f4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-18, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b05fc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0604[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-14, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b060c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-12, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0614[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-10, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b061c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0624[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-6, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b062c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0634[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-2, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b063c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(0, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0644[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b064c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(4, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0654[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(6, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b065c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(8, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0664[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(10, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b066c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(12, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0674[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(14, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b067c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(16, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0684[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(18, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b068c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(20, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0694[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(22, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b069c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(24, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06a4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(26, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06ac[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(28, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06b4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(30, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06bc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(32, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06c4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(34, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06cc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(36, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06d4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(38, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06dc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(40, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06e4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(42, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06ec[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(44, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06f4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(46, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b06fc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(48, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0704[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(50, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b070c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(52, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0714[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(54, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b071c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(56, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0724[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(58, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b072c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(60, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0734[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(62, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b073c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(64, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0744[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(66, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b074c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(68, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0754[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(70, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b075c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(72, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0764[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(74, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b076c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(76, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0774[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(78, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b077c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(80, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0784[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(82, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b078c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(84, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0794[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(86, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b079c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(88, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07a4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(90, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07ac[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(92, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07b4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(94, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07bc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(96, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07c4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(98, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07cc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(100, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07d4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(102, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07dc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(104, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07e4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(106, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07ec[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(108, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07f4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(110, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b07fc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(112, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0804[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(114, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b080c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(116, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b0814[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(118, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

static const u16 sOamFrame_5b081c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(120, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 328, 5, 0),
};

const struct FrameData sIntroMetroidVaccineDoubleHelixOam[60] = {
	[0] = {
		.pFrame = sOamFrame_5aad90,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5aaefa,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5ab064,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5ab1ce,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5ab338,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5ab4a2,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5ab60c,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5ab776,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5ab8e0,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5aba4a,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5abbb4,
		.timer = 2
	},
	[11] = {
		.pFrame = sOamFrame_5abd1e,
		.timer = 2
	},
	[12] = {
		.pFrame = sOamFrame_5abe88,
		.timer = 2
	},
	[13] = {
		.pFrame = sOamFrame_5abff2,
		.timer = 2
	},
	[14] = {
		.pFrame = sOamFrame_5ac15c,
		.timer = 2
	},
	[15] = {
		.pFrame = sOamFrame_5ac2c6,
		.timer = 2
	},
	[16] = {
		.pFrame = sOamFrame_5ac430,
		.timer = 2
	},
	[17] = {
		.pFrame = sOamFrame_5ac59a,
		.timer = 2
	},
	[18] = {
		.pFrame = sOamFrame_5ac704,
		.timer = 2
	},
	[19] = {
		.pFrame = sOamFrame_5ac86e,
		.timer = 2
	},
	[20] = {
		.pFrame = sOamFrame_5ac9d8,
		.timer = 2
	},
	[21] = {
		.pFrame = sOamFrame_5acb42,
		.timer = 2
	},
	[22] = {
		.pFrame = sOamFrame_5accac,
		.timer = 2
	},
	[23] = {
		.pFrame = sOamFrame_5ace16,
		.timer = 2
	},
	[24] = {
		.pFrame = sOamFrame_5acf80,
		.timer = 2
	},
	[25] = {
		.pFrame = sOamFrame_5ad0ea,
		.timer = 2
	},
	[26] = {
		.pFrame = sOamFrame_5ad254,
		.timer = 2
	},
	[27] = {
		.pFrame = sOamFrame_5ad3be,
		.timer = 2
	},
	[28] = {
		.pFrame = sOamFrame_5ad528,
		.timer = 2
	},
	[29] = {
		.pFrame = sOamFrame_5ad692,
		.timer = 2
	},
	[30] = {
		.pFrame = sOamFrame_5ad7fc,
		.timer = 2
	},
	[31] = {
		.pFrame = sOamFrame_5ad966,
		.timer = 2
	},
	[32] = {
		.pFrame = sOamFrame_5adad0,
		.timer = 2
	},
	[33] = {
		.pFrame = sOamFrame_5adc3a,
		.timer = 2
	},
	[34] = {
		.pFrame = sOamFrame_5adda4,
		.timer = 2
	},
	[35] = {
		.pFrame = sOamFrame_5adf0e,
		.timer = 2
	},
	[36] = {
		.pFrame = sOamFrame_5ae078,
		.timer = 2
	},
	[37] = {
		.pFrame = sOamFrame_5ae1e2,
		.timer = 2
	},
	[38] = {
		.pFrame = sOamFrame_5ae34c,
		.timer = 2
	},
	[39] = {
		.pFrame = sOamFrame_5ae4b6,
		.timer = 2
	},
	[40] = {
		.pFrame = sOamFrame_5ae620,
		.timer = 2
	},
	[41] = {
		.pFrame = sOamFrame_5ae78a,
		.timer = 2
	},
	[42] = {
		.pFrame = sOamFrame_5ae8f4,
		.timer = 2
	},
	[43] = {
		.pFrame = sOamFrame_5aea5e,
		.timer = 2
	},
	[44] = {
		.pFrame = sOamFrame_5aebc8,
		.timer = 2
	},
	[45] = {
		.pFrame = sOamFrame_5aed32,
		.timer = 2
	},
	[46] = {
		.pFrame = sOamFrame_5aee9c,
		.timer = 2
	},
	[47] = {
		.pFrame = sOamFrame_5af006,
		.timer = 2
	},
	[48] = {
		.pFrame = sOamFrame_5af170,
		.timer = 2
	},
	[49] = {
		.pFrame = sOamFrame_5af2da,
		.timer = 2
	},
	[50] = {
		.pFrame = sOamFrame_5af444,
		.timer = 2
	},
	[51] = {
		.pFrame = sOamFrame_5af5ae,
		.timer = 2
	},
	[52] = {
		.pFrame = sOamFrame_5af718,
		.timer = 2
	},
	[53] = {
		.pFrame = sOamFrame_5af882,
		.timer = 2
	},
	[54] = {
		.pFrame = sOamFrame_5af9ec,
		.timer = 2
	},
	[55] = {
		.pFrame = sOamFrame_5afb56,
		.timer = 2
	},
	[56] = {
		.pFrame = sOamFrame_5afcc0,
		.timer = 2
	},
	[57] = {
		.pFrame = sOamFrame_5afe2a,
		.timer = 2
	},
	[58] = {
		.pFrame = sOamFrame_5aff94,
		.timer = 2
	},
	[59] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroMetroidVaccineTextboxesOam[21] = {
	[0] = {
		.pFrame = sOamFrame_5b00fe,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5b0106,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5b0114,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5b0128,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5b013c,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5b0150,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5b016a,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5b0184,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5b019e,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5b01c4,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5b01e4,
		.timer = 2
	},
	[11] = {
		.pFrame = sOamFrame_5b020a,
		.timer = 2
	},
	[12] = {
		.pFrame = sOamFrame_5b0230,
		.timer = 2
	},
	[13] = {
		.pFrame = sOamFrame_5b025c,
		.timer = 2
	},
	[14] = {
		.pFrame = sOamFrame_5b0282,
		.timer = 2
	},
	[15] = {
		.pFrame = sOamFrame_5b02ae,
		.timer = 2
	},
	[16] = {
		.pFrame = sOamFrame_5b02da,
		.timer = 240
	},
	[17] = {
		.pFrame = sOamFrame_5b02da,
		.timer = 240
	},
	[18] = {
		.pFrame = sOamFrame_5b02da,
		.timer = 240
	},
	[19] = {
		.pFrame = sOamFrame_5b02da,
		.timer = 240
	},
	[20] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroMetroidVaccineElectrocardiogramOam[146] = {
	[0] = {
		.pFrame = sOamFrame_5b0306,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b030e,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b0316,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b031e,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b0326,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b032e,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b0336,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b033e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b0346,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b034e,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b035c,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b036a,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b0378,
		.timer = 1
	},
	[13] = {
		.pFrame = sOamFrame_5b0380,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b0388,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b0390,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b0398,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b03a0,
		.timer = 1
	},
	[18] = {
		.pFrame = sOamFrame_5b03a8,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b03b0,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b03b8,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b03c0,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b03c8,
		.timer = 1
	},
	[23] = {
		.pFrame = sOamFrame_5b03d0,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b03d8,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b03e0,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b03e8,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b03f0,
		.timer = 1
	},
	[28] = {
		.pFrame = sOamFrame_5b03f8,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b0400,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b040e,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b041c,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b042a,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b0438,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b0446,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b0454,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b0462,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b0470,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b047e,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b048c,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b049a,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b04a2,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b04aa,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b04b2,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b04ba,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b04c2,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b04d0,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b04de,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b04ec,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b04fa,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b0508,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b0516,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b0524,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b0532,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b0540,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b054e,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b055c,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b0564,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b056c,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b0574,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b057c,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b0584,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b058c,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b0594,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b059c,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b05a4,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b05ac,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b05b4,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b05bc,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b05c4,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b05cc,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b05d4,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b05dc,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b05e4,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b05ec,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b05f4,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b05fc,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b0604,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b060c,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b0614,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b061c,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b0624,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b062c,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b0634,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b063c,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b0644,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b064c,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b0654,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b065c,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b0664,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b066c,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b0674,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b067c,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b0684,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b068c,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b0694,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b069c,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b06a4,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b06ac,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b06b4,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b06bc,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b06c4,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b06cc,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b06d4,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b06dc,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b06e4,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b06ec,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b06f4,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b06fc,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b0704,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b070c,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b0714,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b071c,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b0724,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b072c,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b0734,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b073c,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b0744,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b074c,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b0754,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b075c,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b0764,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b076c,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b0774,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b077c,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b0784,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b078c,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b0794,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b079c,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b07a4,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b07ac,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b07b4,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b07bc,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b07c4,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b07cc,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b07d4,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b07dc,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b07e4,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b07ec,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b07f4,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b07fc,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b0804,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b080c,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b0814,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b081c,
		.timer = 1
	},
	[145] = FRAME_DATA_TERMINATOR
};

const u16 sIntroMetroidVaccineObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/metroid_vaccine_obj.pal");

const u32 sIntroMetroidVaccineBgGfx[2794] = INCBIN_U32("data/new_file_intro/metroid_vaccine_bg.gfx.lz");

const u16 sIntroMetroidVaccineBgPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/metroid_vaccine_bg.pal");

const u32 sIntroMetroidVaccineBg1Tilemap[106] = INCBIN_U32("data/new_file_intro/metroid_vaccine_bg1.tm.lz");
const u32 sIntroMetroidVaccineBg2Tilemap[109] = INCBIN_U32("data/new_file_intro/metroid_vaccine_bg2.tm.lz");
const u32 sIntroMetroidVaccineBg3Tilemap[208] = INCBIN_U32("data/new_file_intro/metroid_vaccine_bg3.tm.lz");

const u32 sIntroSamusNervousSystemObjGfx[2495] = INCBIN_U32("data/new_file_intro/samus_nervous_system_obj.gfx.lz");

static const u16 sOamFrame_5b6c7c[OAM_DATA_SIZE(31)] = {
	31,
	OAM_ENTRY(8, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 263, 3, 0),
	OAM_ENTRY(8, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 295, 1, 0),
	OAM_ENTRY(8, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 327, 2, 0),
	OAM_ENTRY(-96, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 256, 2, 0),
	OAM_ENTRY(-96, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 288, 3, 0),
	OAM_ENTRY(-88, -56, OAM_DIMS_8x8, OAM_NO_FLIP, 289, 2, 0),
	OAM_ENTRY(-80, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 322, 3, 0),
	OAM_ENTRY(-88, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 321, 3, 0),
	OAM_ENTRY(-72, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 323, 2, 0),
	OAM_ENTRY(-96, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 320, 3, 0),
	OAM_ENTRY(-80, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 292, 3, 0),
	OAM_ENTRY(-72, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 293, 3, 0),
	OAM_ENTRY(-72, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 261, 3, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 262, 3, 0),
	OAM_ENTRY(-80, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 260, 3, 0),
	OAM_ENTRY(88, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 291, 2, 0),
	OAM_ENTRY(80, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 290, 2, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 266, 3, 0),
	OAM_ENTRY(72, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 265, 3, 0),
	OAM_ENTRY(64, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 264, 3, 0),
	OAM_ENTRY(88, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 267, 3, 0),
	OAM_ENTRY(-72, 40, OAM_DIMS_8x8, OAM_NO_FLIP, 325, 2, 0),
	OAM_ENTRY(-96, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 352, 3, 0),
	OAM_ENTRY(-88, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 353, 3, 0),
	OAM_ENTRY(-80, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 354, 3, 0),
	OAM_ENTRY(-72, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 355, 3, 0),
	OAM_ENTRY(-64, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 324, 1, 0),
	OAM_ENTRY(-64, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 356, 1, 0),
	OAM_ENTRY(-72, -72, OAM_DIMS_8x8, OAM_NO_FLIP, 257, 3, 0),
	OAM_ENTRY(-72, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 258, 2, 0),
	OAM_ENTRY(-64, -64, OAM_DIMS_8x8, OAM_NO_FLIP, 259, 3, 0),
};

static const u16 sOamFrame_5b6d38[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0, 4, 0),
};

static const u16 sOamFrame_5b6d40[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 4, 4, 0),
};

static const u16 sOamFrame_5b6d48[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 8, 4, 0),
};

static const u16 sOamFrame_5b6d50[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 12, 4, 0),
};

static const u16 sOamFrame_5b6d58[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 16, 4, 0),
};

static const u16 sOamFrame_5b6d60[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 20, 4, 0),
};

static const u16 sOamFrame_5b6d68[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 24, 4, 0),
};

static const u16 sOamFrame_5b6d70[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 28, 4, 0),
};

static const u16 sOamFrame_5b6d78[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 128, 4, 0),
};

static const u16 sOamFrame_5b6d80[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 132, 4, 0),
};

static const u16 sOamFrame_5b6d88[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 136, 4, 0),
};

static const u16 sOamFrame_5b6d90[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 140, 4, 0),
};

static const u16 sOamFrame_5b6d98[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 144, 4, 0),
};

static const u16 sOamFrame_5b6da0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 148, 4, 0),
};

static const u16 sOamFrame_5b6da8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 152, 4, 0),
};

static const u16 sOamFrame_5b6db0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 156, 4, 0),
};

static const u16 sOamFrame_5b6db8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0, 6, 0),
};

static const u16 sOamFrame_5b6dc0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 4, 6, 0),
};

static const u16 sOamFrame_5b6dc8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 8, 6, 0),
};

static const u16 sOamFrame_5b6dd0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 12, 6, 0),
};

static const u16 sOamFrame_5b6dd8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 16, 6, 0),
};

static const u16 sOamFrame_5b6de0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 20, 6, 0),
};

static const u16 sOamFrame_5b6de8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 24, 6, 0),
};

static const u16 sOamFrame_5b6df0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 28, 6, 0),
};

static const u16 sOamFrame_5b6df8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 128, 6, 0),
};

static const u16 sOamFrame_5b6e00[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 132, 6, 0),
};

static const u16 sOamFrame_5b6e08[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 136, 6, 0),
};

static const u16 sOamFrame_5b6e10[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 140, 6, 0),
};

static const u16 sOamFrame_5b6e18[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 144, 6, 0),
};

static const u16 sOamFrame_5b6e20[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 148, 6, 0),
};

static const u16 sOamFrame_5b6e28[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 152, 6, 0),
};

static const u16 sOamFrame_5b6e30[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 156, 6, 0),
};

static const u16 sOamFrame_5b6e38[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0, 7, 0),
};

static const u16 sOamFrame_5b6e40[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 4, 7, 0),
};

static const u16 sOamFrame_5b6e48[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 8, 7, 0),
};

static const u16 sOamFrame_5b6e50[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 12, 7, 0),
};

static const u16 sOamFrame_5b6e58[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 16, 7, 0),
};

static const u16 sOamFrame_5b6e60[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 20, 7, 0),
};

static const u16 sOamFrame_5b6e68[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 24, 7, 0),
};

static const u16 sOamFrame_5b6e70[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 28, 7, 0),
};

static const u16 sOamFrame_5b6e78[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 128, 7, 0),
};

static const u16 sOamFrame_5b6e80[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 132, 7, 0),
};

static const u16 sOamFrame_5b6e88[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 136, 7, 0),
};

static const u16 sOamFrame_5b6e90[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 140, 7, 0),
};

static const u16 sOamFrame_5b6e98[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 144, 7, 0),
};

static const u16 sOamFrame_5b6ea0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 148, 7, 0),
};

static const u16 sOamFrame_5b6ea8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 152, 7, 0),
};

static const u16 sOamFrame_5b6eb0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 156, 7, 0),
};

static const u16 sOamFrame_5b6eb8[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-32, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6ed2[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-30, -30, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(14, -30, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-30, 14, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(14, 14, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6eec[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-28, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(12, -28, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-28, 12, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(12, 12, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f06[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-26, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(10, -26, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-26, 10, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(10, 10, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f20[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f3a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-22, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(6, -22, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-22, 6, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(6, 6, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f54[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-20, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(4, -20, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-20, 4, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(4, 4, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f6e[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-18, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 393, 5, 0),
	OAM_ENTRY(2, -18, OAM_DIMS_16x16, OAM_X_FLIP, 393, 5, 0),
	OAM_ENTRY(-18, 2, OAM_DIMS_16x16, OAM_Y_FLIP, 393, 5, 0),
	OAM_ENTRY(2, 2, OAM_DIMS_16x16, OAM_XY_FLIP, 393, 5, 0),
};

static const u16 sOamFrame_5b6f88[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b6f90[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b6f98[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b6fa6[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b6fba[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b6fd4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b6ffa[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-57, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 278, 5, 0),
	OAM_ENTRY(-25, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 282, 5, 0),
};

static const u16 sOamFrame_5b701a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 300, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 304, 5, 0),
};

static const u16 sOamFrame_5b703a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 332, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 336, 5, 0),
};

static const u16 sOamFrame_5b705a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 364, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 368, 5, 0),
};

static const u16 sOamFrame_5b707a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 273, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 277, 5, 0),
};

static const u16 sOamFrame_5b709a[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 305, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 309, 5, 0),
};

static const u16 sOamFrame_5b70ba[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 337, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 341, 5, 0),
};

static const u16 sOamFrame_5b70da[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -10, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-28, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
};

static const u16 sOamFrame_5b70fa[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b711a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b7134[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b7148[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
};

static const u16 sOamFrame_5b7156[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b715e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-60, -11, OAM_DIMS_16x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-44, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 371, 5, 0),
};

static const u16 sOamFrame_5b716c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-60, -11, OAM_DIMS_16x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b7174[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-60, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b717c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b718a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-15, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b71a4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b71c4[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-2, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(30, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b71f0[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 278, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 282, 5, 0),
};

static const u16 sOamFrame_5b7216[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 310, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 314, 5, 0),
};

static const u16 sOamFrame_5b723c[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 342, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 346, 5, 0),
};

static const u16 sOamFrame_5b7262[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 374, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 378, 5, 0),
};

static const u16 sOamFrame_5b7288[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 283, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 287, 5, 0),
};

static const u16 sOamFrame_5b72ae[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 315, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 319, 5, 0),
};

static const u16 sOamFrame_5b72d4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 347, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 351, 5, 0),
};

static const u16 sOamFrame_5b72fa[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(1, 13, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(33, 13, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7320[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 329, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 329, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7346[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 329, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7366[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b737a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(1, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7388[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(9, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 380, 5, 0),
};

static const u16 sOamFrame_5b7390[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(17, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 381, 5, 0),
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b739e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(25, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 382, 5, 0),
};

static const u16 sOamFrame_5b73a6[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(33, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b73ae[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b73bc[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b73d0[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b73ea[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(21, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(53, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b7410[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 278, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 282, 5, 0),
};

static const u16 sOamFrame_5b7430[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 310, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 314, 5, 0),
};

static const u16 sOamFrame_5b7450[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 342, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 346, 5, 0),
};

static const u16 sOamFrame_5b7470[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 374, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 378, 5, 0),
};

static const u16 sOamFrame_5b7490[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 283, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 287, 5, 0),
};

static const u16 sOamFrame_5b74b0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 315, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 319, 5, 0),
};

static const u16 sOamFrame_5b74d0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 347, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 351, 5, 0),
};

static const u16 sOamFrame_5b74f0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(24, 5, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(56, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7510[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b7530[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b754a[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b755e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b756c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(32, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 380, 5, 0),
};

static const u16 sOamFrame_5b7574[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(40, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 381, 5, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7582[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(48, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 382, 5, 0),
};

static const u16 sOamFrame_5b758a[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(56, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7592[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b75a0[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b75b4[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
};

static const u16 sOamFrame_5b75ce[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(18, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(50, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b75f4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 278, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 282, 5, 0),
};

static const u16 sOamFrame_5b7614[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 310, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 314, 5, 0),
};

static const u16 sOamFrame_5b7634[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 342, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 346, 5, 0),
};

static const u16 sOamFrame_5b7654[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 374, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 378, 5, 0),
};

static const u16 sOamFrame_5b7674[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 283, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 287, 5, 0),
};

static const u16 sOamFrame_5b7694[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 315, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 319, 5, 0),
};

static const u16 sOamFrame_5b76b4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 347, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 351, 5, 0),
};

static const u16 sOamFrame_5b76d4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(21, -10, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(53, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b76f4[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 329, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b7714[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b772e[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 331, 5, 0),
};

static const u16 sOamFrame_5b7742[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(21, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 379, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7750[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(29, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 380, 5, 0),
};

static const u16 sOamFrame_5b7758[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(37, -11, OAM_DIMS_16x8, OAM_NO_FLIP, 381, 5, 0),
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7766[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(45, -11, OAM_DIMS_16x8, OAM_NO_FLIP, 382, 5, 0),
};

static const u16 sOamFrame_5b776e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(53, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 383, 5, 0),
};

static const u16 sOamFrame_5b7776[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
};

static const u16 sOamFrame_5b7784[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
};

static const u16 sOamFrame_5b779e[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b77be[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 384, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b77ea[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-37, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 278, 5, 0),
	OAM_ENTRY(-5, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 282, 5, 0),
};

static const u16 sOamFrame_5b7810[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 300, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 304, 5, 0),
};

static const u16 sOamFrame_5b7836[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 332, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 336, 5, 0),
};

static const u16 sOamFrame_5b785c[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 364, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 368, 5, 0),
};

static const u16 sOamFrame_5b7882[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 273, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 277, 5, 0),
};

static const u16 sOamFrame_5b78a8[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 305, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 309, 5, 0),
};

static const u16 sOamFrame_5b78ce[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 337, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 341, 5, 0),
};

static const u16 sOamFrame_5b78f4[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 13, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-8, 13, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
};

static const u16 sOamFrame_5b791a[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b7940[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 329, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b7960[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 330, 5, 0),
};

static const u16 sOamFrame_5b7974[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 373, 5, 0),
};

static const u16 sOamFrame_5b7982[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b798a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-40, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 369, 5, 0),
	OAM_ENTRY(-24, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 371, 5, 0),
};

static const u16 sOamFrame_5b7998[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-40, 12, OAM_DIMS_16x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b79a0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-40, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 369, 5, 0),
};

static const u16 sOamFrame_5b79a8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 388, 5, 0),
};

static const u16 sOamFrame_5b79b0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 389, 5, 0),
};

static const u16 sOamFrame_5b79b8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 390, 5, 0),
};

static const u16 sOamFrame_5b79c0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 391, 5, 0),
};

static const u16 sOamFrame_5b79c8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 392, 5, 0),
};

static const u16 sOamFrame_5b79d0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 452, 5, 0),
};

static const u16 sOamFrame_5b79d8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 453, 5, 0),
};

static const u16 sOamFrame_5b79e0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 454, 5, 0),
};

static const u16 sOamFrame_5b79e8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 455, 5, 0),
};

static const u16 sOamFrame_5b79f0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 456, 5, 0),
};

static const u16 sOamFrame_5b79f8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(2, 2, OAM_DIMS_32x16, OAM_NO_FLIP, 395, 5, 0),
};

static const u16 sOamFrame_5b7a00[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 399, 5, 0),
	OAM_ENTRY(32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 403, 5, 0),
};

static const u16 sOamFrame_5b7a0e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 357, 3, 0),
};

static const u16 sOamFrame_5b7a16[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a1e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a2c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a40[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a5a[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 299, 5, 0),
	OAM_ENTRY(-60, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(-28, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a80[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7a8e[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-15, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7aa8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7ac8[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-2, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(30, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b7af4[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7b02[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7b16[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7b30[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(7, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(15, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(21, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(53, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b7b56[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7b64[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7b78[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
};

static const u16 sOamFrame_5b7b92[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 299, 5, 0),
	OAM_ENTRY(18, -11, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(50, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

static const u16 sOamFrame_5b7bb8[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
};

static const u16 sOamFrame_5b7bc6[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
};

static const u16 sOamFrame_5b7be0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
};

static const u16 sOamFrame_5b7c00[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 296, 5, 0),
	OAM_ENTRY(8, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 297, 5, 0),
	OAM_ENTRY(0, 15, OAM_DIMS_8x8, OAM_NO_FLIP, 298, 5, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 268, 5, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 272, 5, 0),
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_1[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7a80,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b717c,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7a8e,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b718a,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7aa8,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b71a4,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7ac8,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b71c4,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b71f0,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b7216,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b723c,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b7262,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b7288,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b72ae,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b72d4,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b72fa,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b7320,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b7346,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b7366,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b737a,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b7388,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b7390,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b739e,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b73a6,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_2[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7af4,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b73ae,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7b02,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b73bc,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7b16,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b73d0,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7b30,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b73ea,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b7410,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b7430,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b7450,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b7470,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b7490,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b74b0,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b74d0,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b74f0,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b7510,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b7530,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b754a,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b755e,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b756c,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b7574,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b7582,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b758a,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_3[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7b56,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b7592,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7b64,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b75a0,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7b78,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b75b4,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7b92,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b75ce,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b75f4,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b7614,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b7634,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b7654,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b7674,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b7694,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b76b4,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b76d4,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b76f4,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b7714,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b772e,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b7742,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b7750,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b7758,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b7766,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b776e,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_4[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7a1e,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b6f98,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7a2c,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b6fa6,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7a40,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b6fba,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b6ffa,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b701a,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b703a,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b705a,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b707a,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b709a,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b70ba,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b70da,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b70fa,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b711a,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b7134,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b7148,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b7156,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b715e,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b716c,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b7174,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_5[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7bb8,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b7776,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7bc6,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b7784,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7be0,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b779e,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7c00,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b77be,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b77ea,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b7810,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b7836,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b785c,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b7882,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b78a8,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b78ce,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b78f4,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b791a,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b7940,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b7960,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b7974,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b7982,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b798a,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b7998,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b79a0,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXLockOnOam_6[171] = {
	[0] = {
		.pFrame = sOamFrame_5b6eb8,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5b6ed2,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5b6eec,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5b6f06,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5b6f20,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5b6f3a,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5b6f54,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5b6f6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[13] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[18] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[23] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5b7a16,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5b6f88,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5b6f90,
		.timer = 4
	},
	[28] = {
		.pFrame = sOamFrame_5b7a1e,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5b6f98,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5b7a2c,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5b6fa6,
		.timer = 1
	},
	[32] = {
		.pFrame = sOamFrame_5b7a40,
		.timer = 1
	},
	[33] = {
		.pFrame = sOamFrame_5b6fba,
		.timer = 1
	},
	[34] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[35] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[36] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[37] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[38] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[39] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[40] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[41] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[42] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[43] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[44] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[45] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[46] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[47] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[48] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[49] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[50] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[51] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[52] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[53] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[54] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[55] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[56] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[57] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[58] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[59] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[60] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[61] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[62] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[63] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[64] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[65] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[66] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[67] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[68] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[69] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[70] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[71] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[72] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[73] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[74] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[75] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[76] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[77] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[78] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[79] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[80] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[81] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[82] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[83] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[84] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[85] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[86] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[87] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[88] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[89] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[90] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[91] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[92] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[93] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[94] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[95] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[96] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[97] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[98] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[99] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[100] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[101] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[102] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[103] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[104] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[105] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[106] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[107] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[108] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[109] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[110] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[111] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[112] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[113] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[114] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[115] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[116] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[117] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[118] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[119] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[120] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[121] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[122] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[123] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[124] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[125] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[126] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[127] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[128] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[129] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[130] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[131] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[132] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[133] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[134] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[135] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[136] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[137] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[138] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[139] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[140] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[141] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[142] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[143] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[144] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[145] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[146] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[147] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[148] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[149] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[150] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[151] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[152] = {
		.pFrame = sOamFrame_5b7a5a,
		.timer = 1
	},
	[153] = {
		.pFrame = sOamFrame_5b6fd4,
		.timer = 1
	},
	[154] = {
		.pFrame = sOamFrame_5b6ffa,
		.timer = 4
	},
	[155] = {
		.pFrame = sOamFrame_5b701a,
		.timer = 4
	},
	[156] = {
		.pFrame = sOamFrame_5b703a,
		.timer = 4
	},
	[157] = {
		.pFrame = sOamFrame_5b705a,
		.timer = 4
	},
	[158] = {
		.pFrame = sOamFrame_5b707a,
		.timer = 4
	},
	[159] = {
		.pFrame = sOamFrame_5b709a,
		.timer = 4
	},
	[160] = {
		.pFrame = sOamFrame_5b70ba,
		.timer = 4
	},
	[161] = {
		.pFrame = sOamFrame_5b70da,
		.timer = 4
	},
	[162] = {
		.pFrame = sOamFrame_5b70fa,
		.timer = 120
	},
	[163] = {
		.pFrame = sOamFrame_5b711a,
		.timer = 3
	},
	[164] = {
		.pFrame = sOamFrame_5b7134,
		.timer = 3
	},
	[165] = {
		.pFrame = sOamFrame_5b7148,
		.timer = 3
	},
	[166] = {
		.pFrame = sOamFrame_5b7156,
		.timer = 3
	},
	[167] = {
		.pFrame = sOamFrame_5b715e,
		.timer = 3
	},
	[168] = {
		.pFrame = sOamFrame_5b716c,
		.timer = 3
	},
	[169] = {
		.pFrame = sOamFrame_5b7174,
		.timer = 3
	},
	[170] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemCountdownOam_Fast[11] = {
	[0] = {
		.pFrame = sOamFrame_5b79f0,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5b79e8,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5b79e0,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5b79d8,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5b79d0,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5b79c8,
		.timer = 8
	},
	[6] = {
		.pFrame = sOamFrame_5b79c0,
		.timer = 8
	},
	[7] = {
		.pFrame = sOamFrame_5b79b8,
		.timer = 8
	},
	[8] = {
		.pFrame = sOamFrame_5b79b0,
		.timer = 8
	},
	[9] = {
		.pFrame = sOamFrame_5b79a8,
		.timer = 8
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemCountdownOam_Slow[11] = {
	[0] = {
		.pFrame = sOamFrame_5b79f0,
		.timer = 80
	},
	[1] = {
		.pFrame = sOamFrame_5b79e8,
		.timer = 80
	},
	[2] = {
		.pFrame = sOamFrame_5b79e0,
		.timer = 80
	},
	[3] = {
		.pFrame = sOamFrame_5b79d8,
		.timer = 80
	},
	[4] = {
		.pFrame = sOamFrame_5b79d0,
		.timer = 80
	},
	[5] = {
		.pFrame = sOamFrame_5b79c8,
		.timer = 80
	},
	[6] = {
		.pFrame = sOamFrame_5b79c0,
		.timer = 80
	},
	[7] = {
		.pFrame = sOamFrame_5b79b8,
		.timer = 80
	},
	[8] = {
		.pFrame = sOamFrame_5b79b0,
		.timer = 80
	},
	[9] = {
		.pFrame = sOamFrame_5b79a8,
		.timer = 80
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemNumber281Oam[2] = {
	[0] = {
		.pFrame = sOamFrame_5b79f8,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemCornerTextOam[3] = {
	[0] = {
		.pFrame = sOamFrame_5b7a00,
		.timer = 40
	},
	[1] = {
		.pFrame = sOamFrame_5b7a0e,
		.timer = 30
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemNervePartsOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5b6c7c,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_1[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6d38,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6d40,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6d48,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6d50,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6d58,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6d60,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6d68,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6d70,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6d78,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6d80,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6d88,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6d90,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6d98,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6da0,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6da8,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6db0,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_2[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6d98,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6da0,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6da8,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6db0,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6d38,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6d40,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6d48,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6d50,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6d58,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6d60,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6d68,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6d70,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6d78,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6d80,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6d88,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6d90,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_3[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6df0,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6df8,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6e00,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6e08,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6e10,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6e18,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6e20,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6e28,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6e30,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6db8,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6dc0,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6dc8,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6dd0,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6dd8,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6de0,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6de8,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_4[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6d68,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6d70,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6d78,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6d80,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6d88,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6d90,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6d98,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6da0,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6da8,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6db0,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6d38,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6d40,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6d48,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6d50,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6d58,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6d60,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_5[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6e50,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6e58,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6e60,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6e68,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6e70,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6e78,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6e80,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6e88,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6e90,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6e98,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6ea0,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6ea8,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6eb0,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6e38,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6e40,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6e48,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusNervousSystemXParasiteOam_6[17] = {
	[0] = {
		.pFrame = sOamFrame_5b6e10,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5b6e18,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5b6e20,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5b6e28,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5b6e30,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5b6db8,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5b6dc0,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5b6dc8,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5b6dd0,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5b6dd8,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5b6de0,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5b6de8,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5b6df0,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5b6df8,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5b6e00,
		.timer = 3
	},
	[15] = {
		.pFrame = sOamFrame_5b6e08,
		.timer = 3
	},
	[16] = FRAME_DATA_TERMINATOR
};

const u16 sIntroSamusNervousSystemObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_nervous_system_obj.pal");

const u32 sIntroSamusNervousSystemBgGfx[4869] = INCBIN_U32("data/new_file_intro/samus_nervous_system_bg.gfx.lz");

const u16 sIntroSamusNervousSystemBgPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_nervous_system_bg.pal");

const u32 sIntroSamusNervousSystemBg3Tilemap[369] = INCBIN_U32("data/new_file_intro/samus_nervous_system_bg3.tm.lz");
const u32 sIntroSamusNervousSystemBg2Tilemap[63] = INCBIN_U32("data/new_file_intro/samus_nervous_system_bg2.tm.lz");
const u32 sIntroSamusNervousSystemBg1Tilemap[68] = INCBIN_U32("data/new_file_intro/samus_nervous_system_bg1.tm.lz");

const u16 sPal_5bf838[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bf838.pal");
const u16 sPal_5bf8b8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bf8b8.pal");
const u16 sPal_5bf938[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bf938.pal");
const u16 sPal_5bf9b8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bf9b8.pal");
const u16 sPal_5bfa38[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfa38.pal");
const u16 sPal_5bfab8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfab8.pal");
const u16 sPal_5bfb38[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfb38.pal");
const u16 sPal_5bfbb8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfbb8.pal");
const u16 sPal_5bfc38[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfc38.pal");
const u16 sPal_5bfcb8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfcb8.pal");
const u16 sPal_5bfd38[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfd38.pal");
const u16 sPal_5bfdb8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5bfdb8.pal");

const u32 sIntroVariaSuitCoveredInXParasitesGfx[4230] = INCBIN_U32("data/new_file_intro/suit_covered_in_parasites.gfx.lz");
const u32 sIntroHazmatTeamGfx[4915] = INCBIN_U32("data/new_file_intro/hazmat_team.gfx.lz");

const u16 sIntroSamusFoundPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_found.pal");

const u32 sIntroVariaSuitCoveredInXParasitesTilemap[385] = INCBIN_U32("data/new_file_intro/suit_covered_in_parasites.tm.lz");
const u32 sIntroHazmatTeamTilemap[395] = INCBIN_U32("data/new_file_intro/hazmat_team.tm.lz");

const u32 sIntroSuitRemovalSurgeryGfx[7003] = INCBIN_U32("data/new_file_intro/suit_removal_surgery.gfx.lz");
const u32 sIntroSuitRemovalSurgeryTilemap[551] = INCBIN_U32("data/new_file_intro/suit_removal_surgery.tm.lz");

const u32 sIntroMetroidVaccineVialGfx[3525] = INCBIN_U32("data/new_file_intro/metroid_vaccine_vial.gfx.lz");
const u32 sIntroMetroidVaccineVialTilemap[385] = INCBIN_U32("data/new_file_intro/metroid_vaccine_vial.tm.lz");

const u32 sIntroSamusRebornBgTopGfx[6616] = INCBIN_U32("data/new_file_intro/samus_reborn_bg_top.gfx.lz");
const u32 sIntroSamusRebornBgBottomGfx[3537] = INCBIN_U32("data/new_file_intro/samus_reborn_bg_bottom.gfx.lz");
const u16 sIntroSamusRebornBgPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_reborn_bg.pal");
const u32 sIntroSamusRebornBgTopTilemap[551] = INCBIN_U32("data/new_file_intro/samus_reborn_bg_top.tm.lz");
const u32 sIntroSamusRebornBgBottomTilemap[368] = INCBIN_U32("data/new_file_intro/samus_reborn_bg_bottom.tm.lz");

// Samus cured cutscene: BG palette rows 5-14 for each step of the fade (sPalPointers_79c314)
const u16 sIntroSamusCuredBgFadePal_0[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_0.pal");
const u16 sIntroSamusCuredBgFadePal_1[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_1.pal");
const u16 sIntroSamusCuredBgFadePal_3[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_3.pal");
const u16 sIntroSamusCuredBgFadePal_4[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_4.pal");
const u16 sIntroSamusCuredBgFadePal_5[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_5.pal");
const u16 sIntroSamusCuredBgFadePal_6[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_6.pal");
const u16 sIntroSamusCuredBgFadePal_7[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_7.pal");
const u16 sIntroSamusCuredBgFadePal_8[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_8.pal");
const u16 sIntroSamusCuredBgFadePal_9[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_9.pal");
const u16 sIntroSamusCuredBgFadePal_10[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_10.pal");
const u16 sIntroSamusCuredBgFadePal_11[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_11.pal");
const u16 sIntroSamusCuredBgFadePal_12[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_12.pal");
const u16 sIntroSamusCuredBgFadePal_13[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_13.pal");
const u16 sIntroSamusCuredBgFadePal_14[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_14.pal");
const u16 sIntroSamusCuredBgFadePal_15[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_15.pal");
const u16 sIntroSamusCuredBgFadePal_2[10 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_bg_fade_2.pal");

const u32 sIntroApproachingBslObjGfx[3614] = INCBIN_U32("data/new_file_intro/approaching_bsl_obj.gfx.lz");

const u32 sIntroFlyingToBslBgGfx[4107] = INCBIN_U32("data/new_file_intro/5e49e4.gfx.lz");
const u32 sIntroArrivingAtBslSpaceMapBgGfx[2178] = INCBIN_U32("data/new_file_intro/space_map_bg");
const u32 sIntroFlyingToBslObjGfx[3286] = INCBIN_U32("data/new_file_intro/5eac18.gfx.lz");

const u32 sIntroSamusMonologueBgGfx[3282] = INCBIN_U32("data/new_file_intro/samus_monologue_bg.gfx.lz");

static const u16 sOamFrame_5f12b8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-7, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 544, 3, 0),
	OAM_ENTRY(-1, -7, OAM_DIMS_8x8, OAM_X_FLIP, 544, 3, 0),
	OAM_ENTRY(-1, -1, OAM_DIMS_8x8, OAM_XY_FLIP, 544, 3, 0),
	OAM_ENTRY(-7, -1, OAM_DIMS_8x8, OAM_Y_FLIP, 544, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 725, 3, 0),
};

static const u16 sOamFrame_5f12d8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 544, 3, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_X_FLIP, 544, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_XY_FLIP, 544, 3, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 544, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 724, 3, 0),
};

static const u16 sOamFrame_5f12f8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-9, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 544, 3, 0),
	OAM_ENTRY(1, -9, OAM_DIMS_8x8, OAM_X_FLIP, 544, 3, 0),
	OAM_ENTRY(1, 1, OAM_DIMS_8x8, OAM_XY_FLIP, 544, 3, 0),
	OAM_ENTRY(-9, 1, OAM_DIMS_8x8, OAM_Y_FLIP, 544, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 723, 3, 0),
};

static const u16 sOamFrame_5f1318[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-4, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 545, 3, 0),
	OAM_ENTRY(-4, 5, OAM_DIMS_8x8, OAM_XY_FLIP, 545, 3, 0),
	OAM_ENTRY(5, -4, OAM_DIMS_8x8, OAM_X_FLIP, 515, 3, 0),
	OAM_ENTRY(-13, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 515, 3, 0),
	OAM_ENTRY(-16, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 802, 3, 0),
};

static const u16 sOamFrame_5f1338[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-4, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 545, 3, 0),
	OAM_ENTRY(-4, 4, OAM_DIMS_8x8, OAM_XY_FLIP, 545, 3, 0),
	OAM_ENTRY(4, -4, OAM_DIMS_8x8, OAM_X_FLIP, 515, 3, 0),
	OAM_ENTRY(-12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 515, 3, 0),
};

static const u16 sOamFrame_5f1352[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-4, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 545, 3, 0),
	OAM_ENTRY(-4, 3, OAM_DIMS_8x8, OAM_XY_FLIP, 545, 3, 0),
	OAM_ENTRY(3, -4, OAM_DIMS_8x8, OAM_X_FLIP, 515, 3, 0),
	OAM_ENTRY(-11, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 515, 3, 0),
	OAM_ENTRY(-16, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 802, 3, 0),
};

static const u16 sOamFrame_5f1372[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-4, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 545, 3, 0),
	OAM_ENTRY(-4, 2, OAM_DIMS_8x8, OAM_XY_FLIP, 545, 3, 0),
	OAM_ENTRY(2, -4, OAM_DIMS_8x8, OAM_X_FLIP, 515, 3, 0),
	OAM_ENTRY(-10, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 515, 3, 0),
};

static const u16 sOamFrame_5f138c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f1394[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_Y_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f139c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f13a4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x16, OAM_X_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f13ac[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
	OAM_ENTRY(-4, 2, OAM_DIMS_8x8, OAM_Y_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13ba[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
	OAM_ENTRY(-4, 3, OAM_DIMS_8x8, OAM_Y_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13c8[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
	OAM_ENTRY(-4, 4, OAM_DIMS_8x8, OAM_Y_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13d6[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13de[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, 3, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13e6[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 608, 3, 0),
};

static const u16 sOamFrame_5f13ee[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-5, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 547, 3, 0),
};

static const u16 sOamFrame_5f13f6[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 552, 9, 0),
};

static const u16 sOamFrame_5f13fe[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-8, -24, OAM_DIMS_32x16, OAM_NO_FLIP, 580, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 580, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 580, 3, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 580, 3, 0),
	OAM_ENTRY(-8, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 580, 3, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 580, 3, 0),
};

static const u16 sOamFrame_5f1424[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 684, 3, 0),
};

static const u16 sOamFrame_5f142c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 684, 3, 0),
};

static const u16 sOamFrame_5f1434[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -3, OAM_DIMS_16x8, OAM_NO_FLIP, 684, 3, 0),
};

static const u16 sOamFrame_5f143c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-5, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 577, 3, 0),
};

static const u16 sOamFrame_5f1444[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 577, 3, 0),
};

static const u16 sOamFrame_5f144c[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-3, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 577, 3, 0),
};

static const u16 sOamFrame_5f1454[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 755, 3, 0),
};

static const u16 sOamFrame_5f1468[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 755, 3, 0),
};

static const u16 sOamFrame_5f1470[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, -23, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 756, 3, 0),
};

static const u16 sOamFrame_5f1484[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 756, 3, 0),
};

static const u16 sOamFrame_5f148c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, -22, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5f14a0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5f14a8[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, -23, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f14bc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f14c4[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, -22, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f14d8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f14e0[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f14ee[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 578, 3, 0),
	OAM_ENTRY(-4, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1502[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1510[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 578, 3, 0),
};

static const u16 sOamFrame_5f1518[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1520[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_Y_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1528[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -11, OAM_DIMS_8x8, OAM_Y_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_Y_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1536[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -6, OAM_DIMS_8x8, OAM_Y_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -11, OAM_DIMS_8x8, OAM_Y_FLIP, 578, 3, 0),
	OAM_ENTRY(-4, -16, OAM_DIMS_8x8, OAM_Y_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f154a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-4, -6, OAM_DIMS_8x8, OAM_Y_FLIP, 579, 3, 0),
	OAM_ENTRY(-4, -12, OAM_DIMS_8x8, OAM_Y_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1558[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -6, OAM_DIMS_8x8, OAM_Y_FLIP, 578, 3, 0),
};

static const u16 sOamFrame_5f1560[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -6, OAM_DIMS_8x8, OAM_Y_FLIP, 610, 3, 0),
};

static const u16 sOamFrame_5f1568[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 934, 8, 0),
};

static const u16 sOamFrame_5f1594[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 966, 8, 0),
};

static const u16 sOamFrame_5f15c0[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 938, 8, 0),
};

static const u16 sOamFrame_5f15ec[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
};

static const u16 sOamFrame_5f1618[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
};

static const u16 sOamFrame_5f1644[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 970, 8, 0),
};

static const u16 sOamFrame_5f1670[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, 1, OAM_DIMS_8x8, OAM_Y_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, 6, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 755, 3, 0),
};

static const u16 sOamFrame_5f1684[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, 5, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 756, 3, 0),
};

static const u16 sOamFrame_5f1698[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, -1, OAM_DIMS_8x8, OAM_Y_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, 4, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5f16ac[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-4, 0, OAM_DIMS_8x8, OAM_Y_FLIP, 726, 3, 0),
	OAM_ENTRY(-16, 5, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f16c0[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 740, 3, 0),
	OAM_ENTRY(-39, -10, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 755, 3, 0),
};

static const u16 sOamFrame_5f16d4[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 740, 3, 0),
	OAM_ENTRY(-39, -9, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 756, 3, 0),
};

static const u16 sOamFrame_5f16e8[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 740, 3, 0),
	OAM_ENTRY(-39, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5f16fc[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 740, 3, 0),
	OAM_ENTRY(-39, -9, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f1710[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 740, 3, 0),
	OAM_ENTRY(7, -10, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 755, 3, 0),
};

static const u16 sOamFrame_5f1724[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 740, 3, 0),
	OAM_ENTRY(7, -9, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 756, 3, 0),
};

static const u16 sOamFrame_5f1738[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 740, 3, 0),
	OAM_ENTRY(7, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 757, 3, 0),
};

static const u16 sOamFrame_5f174c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 740, 3, 0),
	OAM_ENTRY(7, -9, OAM_DIMS_32x16, OAM_NO_FLIP, 727, 3, 0),
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 758, 3, 0),
};

static const u16 sOamFrame_5f1760[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f1768[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -6, OAM_DIMS_16x8, OAM_NO_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f1770[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -3, OAM_DIMS_16x8, OAM_Y_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f1778[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -2, OAM_DIMS_16x8, OAM_Y_FLIP, 512, 3, 0),
};

static const u16 sOamFrame_5f1780[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-5, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f1788[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-6, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f1790[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-3, -8, OAM_DIMS_8x16, OAM_X_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f1798[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-2, -8, OAM_DIMS_8x16, OAM_X_FLIP, 514, 3, 0),
};

static const u16 sOamFrame_5f17a0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 680, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 744, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 1004, 8, 0),
	OAM_ENTRY(38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 773, 3, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 744, 3, 0),
};

static const u16 sOamFrame_5f17c0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(16, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 1004, 8, 0),
};

static const u16 sOamFrame_5f17c8[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 680, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 744, 3, 0),
	OAM_ENTRY(38, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 773, 3, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 744, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 1008, 8, 0),
};

static const u16 sOamFrame_5f17e8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(16, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 1008, 8, 0),
};

static const u16 sOamFrame_5f17f0[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 680, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 744, 3, 0),
	OAM_ENTRY(16, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 1004, 8, 0),
	OAM_ENTRY(38, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 773, 3, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 744, 3, 0),
};

static const u16 sOamFrame_5f1810[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(16, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 1004, 8, 0),
};

static const u16 sOamFrame_5f1818[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 680, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 744, 3, 0),
	OAM_ENTRY(38, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 773, 3, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 744, 3, 0),
	OAM_ENTRY(16, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 1008, 8, 0),
};

static const u16 sOamFrame_5f1838[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(16, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 1008, 8, 0),
};

static const u16 sOamFrame_5f1840[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 680, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 744, 3, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 773, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 982, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 984, 8, 0),
};

static const u16 sOamFrame_5f1860[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(16, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 982, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 984, 8, 0),
};

static const u16 sOamFrame_5f186e[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 680, 3, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 744, 3, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 773, 3, 0),
	OAM_ENTRY(16, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 985, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 987, 8, 0),
};

static const u16 sOamFrame_5f188e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(16, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 985, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 987, 8, 0),
};

static const u16 sOamFrame_5f189c[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 680, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 744, 3, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 773, 3, 0),
	OAM_ENTRY(16, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 982, 8, 0),
	OAM_ENTRY(32, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 984, 8, 0),
};

static const u16 sOamFrame_5f18bc[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(16, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 982, 8, 0),
	OAM_ENTRY(32, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 984, 8, 0),
};

static const u16 sOamFrame_5f18ca[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 680, 3, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 744, 3, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_8x8, OAM_Y_FLIP, 773, 3, 0),
	OAM_ENTRY(16, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 985, 8, 0),
	OAM_ENTRY(32, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 987, 8, 0),
};

static const u16 sOamFrame_5f18ea[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(16, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 985, 8, 0),
	OAM_ENTRY(32, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 987, 8, 0),
};

static const u16 sOamFrame_5f18f8[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-29, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 942, 3, 0),
	OAM_ENTRY(-15, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 976, 3, 0),
	OAM_ENTRY(17, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 980, 3, 0),
};

static const u16 sOamFrame_5f190c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 944, 8, 0),
};

static const u16 sOamFrame_5f1920[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 945, 8, 0),
};

static const u16 sOamFrame_5f1934[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 946, 8, 0),
};

static const u16 sOamFrame_5f1948[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 947, 8, 0),
};

static const u16 sOamFrame_5f195c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 948, 8, 0),
};

static const u16 sOamFrame_5f1970[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 912, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 916, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 949, 8, 0),
};

static const u16 sOamFrame_5f1984[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 788, 8, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 790, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 788, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 790, 8, 0),
};

static const u16 sOamFrame_5f199e[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 820, 8, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 822, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 820, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 822, 8, 0),
};

static const u16 sOamFrame_5f19b8[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 852, 8, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 854, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 852, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 854, 8, 0),
};

static const u16 sOamFrame_5f19d2[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 884, 8, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 886, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 884, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_X_FLIP, 886, 8, 0),
};

static const u16 sOamFrame_5f19ec[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 884, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 884, 8, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 885, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 885, 8, 0),
};

static const u16 sOamFrame_5f1a06[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 11, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 11, 0),
};

static const u16 sOamFrame_5f1a14[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 12, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 12, 0),
};

static const u16 sOamFrame_5f1a22[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 13, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 13, 0),
};

static const u16 sOamFrame_5f1a30[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 14, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 14, 0),
};

static const u16 sOamFrame_5f1a3e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 11, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 11, 0),
};

static const u16 sOamFrame_5f1a4c[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 12, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 12, 0),
};

static const u16 sOamFrame_5f1a5a[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 13, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 13, 0),
};

static const u16 sOamFrame_5f1a68[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 14, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 14, 0),
};

static const u16 sOamFrame_5f1a76[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 448, 6, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 450, 6, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 460, 6, 0),
};

static const u16 sOamFrame_5f1a8a[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 451, 6, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 453, 6, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 460, 6, 0),
};

static const u16 sOamFrame_5f1a9e[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 454, 6, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 456, 6, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 460, 6, 0),
};

static const u16 sOamFrame_5f1ab2[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 457, 6, 0),
	OAM_ENTRY(-8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 459, 6, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 460, 6, 0),
};

static const u16 sOamFrame_5f1ac6[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 480, 6, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 482, 6, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 492, 6, 0),
};

static const u16 sOamFrame_5f1ada[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 483, 6, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 485, 6, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 492, 6, 0),
};

static const u16 sOamFrame_5f1aee[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 486, 6, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 488, 6, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 492, 6, 0),
};

static const u16 sOamFrame_5f1b02[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-24, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 489, 6, 0),
	OAM_ENTRY(-8, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 491, 6, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 492, 6, 0),
};

static const u16 sOamFrame_5f1b16[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 3, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 3, 0),
};

static const u16 sOamFrame_5f1b24[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 891, 5, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 895, 5, 0),
};

static const u16 sOamFrame_5f1b32[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 3, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 3, 0),
};

static const u16 sOamFrame_5f1b40[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 923, 5, 0),
	OAM_ENTRY(12, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 927, 5, 0),
};

static const u16 sOamFrame_5f1b4e[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-24, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 917, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 921, 8, 0),
};

static const u16 sOamFrame_5f1b5c[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-32, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 441, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 445, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 447, 8, 0),
	OAM_ENTRY(-40, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 504, 3, 0),
};

static const u16 sOamFrame_5f1b76[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 473, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 477, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 479, 8, 0),
};

static const u16 sOamFrame_5f1b8a[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 505, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 509, 8, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 511, 8, 0),
};

static const u16 sOamFrame_5f1b9e[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-32, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 409, 3, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 414, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 413, 8, 0),
	OAM_ENTRY(-40, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 504, 3, 0),
	OAM_ENTRY(24, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 504, 3, 0),
};

static const u16 sOamFrame_5f1bbe[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-14, -6, OAM_DIMS_16x8, OAM_NO_FLIP, 439, 3, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 405, 3, 0),
};

static const u16 sOamFrame_5f1bcc[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-14, -6, OAM_DIMS_16x8, OAM_NO_FLIP, 439, 3, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 437, 3, 0),
};

static const u16 sOamFrame_5f1bda[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-14, -6, OAM_DIMS_16x8, OAM_NO_FLIP, 439, 3, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 407, 3, 0),
};

static const u16 sOamFrame_5f1be8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 441, 3, 0),
};

static const u16 sOamFrame_5f1bf0[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 473, 3, 0),
};

static const u16 sOamFrame_5f1bf8[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 505, 3, 0),
};

const struct FrameData sOam_5f1c00[5] = {
	[0] = {
		.pFrame = sOamFrame_5f12b8,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f12d8,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f12f8,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f12d8,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1c28[5] = {
	[0] = {
		.pFrame = sOamFrame_5f143c,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1444,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f144c,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1444,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslMonologueCursorOam[5] = {
	[0] = {
		.pFrame = sOamFrame_5f1424,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f142c,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f1434,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f142c,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1c78[7] = {
	[0] = {
		.pFrame = sOamFrame_5f1318,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5f1338,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5f1352,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5f1372,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5f1352,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5f1338,
		.timer = 3
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1cb0[5] = {
	[0] = {
		.pFrame = sOamFrame_5f138c,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1760,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f1768,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1760,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1cd8[5] = {
	[0] = {
		.pFrame = sOamFrame_5f1394,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1770,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f1778,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1770,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1d00[5] = {
	[0] = {
		.pFrame = sOamFrame_5f139c,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1780,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f1788,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1780,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1d28[5] = {
	[0] = {
		.pFrame = sOamFrame_5f13a4,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1790,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f1798,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1790,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1d50[5] = {
	[0] = {
		.pFrame = sOamFrame_5f13ac,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f13ba,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f13c8,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f13ba,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1d78[5] = {
	[0] = {
		.pFrame = sOamFrame_5f13d6,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f13de,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f13e6,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f13de,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamTextCursorOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5f13ee,
		.timer = 30
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1db0[3] = {
	[0] = {
		.pFrame = sOamFrame_5f13ee,
		.timer = 16
	},
	[1] = {
		.pFrame = sOamFrame_5f13f6,
		.timer = 16
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1dc8[2] = {
	[0] = {
		.pFrame = sOamFrame_5f13fe,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1dd8[8] = {
	[0] = {
		.pFrame = sOamFrame_5f14d8,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5f14e0,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f14ee,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5f1502,
		.timer = 4
	},
	[4] = {
		.pFrame = sOamFrame_5f1510,
		.timer = 4
	},
	[5] = {
		.pFrame = sOamFrame_5f1518,
		.timer = 4
	},
	[6] = {
		.pFrame = sOamFrame_5f13f6,
		.timer = 8
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1e18[8] = {
	[0] = {
		.pFrame = sOamFrame_5f1520,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5f1528,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5f1536,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5f154a,
		.timer = 4
	},
	[4] = {
		.pFrame = sOamFrame_5f1558,
		.timer = 4
	},
	[5] = {
		.pFrame = sOamFrame_5f1560,
		.timer = 4
	},
	[6] = {
		.pFrame = sOamFrame_5f13f6,
		.timer = 8
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1e58[7] = {
	[0] = {
		.pFrame = sOamFrame_5f1568,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1594,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f15c0,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f15ec,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f1618,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f1644,
		.timer = 1
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1e90[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1568,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1ea0[33] = {
	[0] = {
		.pFrame = sOamFrame_5f1454,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f1454,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f1454,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f1454,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f1470,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f1470,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5f1470,
		.timer = 1
	},
	[13] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5f1470,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5f148c,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[18] = {
		.pFrame = sOamFrame_5f148c,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5f148c,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5f148c,
		.timer = 1
	},
	[23] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5f14a8,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5f14a8,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[28] = {
		.pFrame = sOamFrame_5f14a8,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5f14a8,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[32] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f1fa8[33] = {
	[0] = {
		.pFrame = sOamFrame_5f1670,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f1670,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f1670,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f1670,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f1684,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f1684,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5f1684,
		.timer = 1
	},
	[13] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5f1684,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5f1698,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[18] = {
		.pFrame = sOamFrame_5f1698,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5f1698,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5f1698,
		.timer = 1
	},
	[23] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5f16ac,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5f16ac,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[28] = {
		.pFrame = sOamFrame_5f16ac,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5f16ac,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[32] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f20b0[33] = {
	[0] = {
		.pFrame = sOamFrame_5f16c0,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f16c0,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f16c0,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f16c0,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f16d4,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f16d4,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5f16d4,
		.timer = 1
	},
	[13] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5f16d4,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5f16e8,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[18] = {
		.pFrame = sOamFrame_5f16e8,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5f16e8,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5f16e8,
		.timer = 1
	},
	[23] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5f16fc,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5f16fc,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[28] = {
		.pFrame = sOamFrame_5f16fc,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5f16fc,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[32] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f21b8[33] = {
	[0] = {
		.pFrame = sOamFrame_5f1710,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f1710,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f1710,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f1710,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f1468,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f1724,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f1724,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[12] = {
		.pFrame = sOamFrame_5f1724,
		.timer = 1
	},
	[13] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[14] = {
		.pFrame = sOamFrame_5f1724,
		.timer = 1
	},
	[15] = {
		.pFrame = sOamFrame_5f1484,
		.timer = 1
	},
	[16] = {
		.pFrame = sOamFrame_5f1738,
		.timer = 1
	},
	[17] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[18] = {
		.pFrame = sOamFrame_5f1738,
		.timer = 1
	},
	[19] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[20] = {
		.pFrame = sOamFrame_5f1738,
		.timer = 1
	},
	[21] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[22] = {
		.pFrame = sOamFrame_5f1738,
		.timer = 1
	},
	[23] = {
		.pFrame = sOamFrame_5f14a0,
		.timer = 1
	},
	[24] = {
		.pFrame = sOamFrame_5f174c,
		.timer = 1
	},
	[25] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[26] = {
		.pFrame = sOamFrame_5f174c,
		.timer = 1
	},
	[27] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[28] = {
		.pFrame = sOamFrame_5f174c,
		.timer = 1
	},
	[29] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[30] = {
		.pFrame = sOamFrame_5f174c,
		.timer = 1
	},
	[31] = {
		.pFrame = sOamFrame_5f14bc,
		.timer = 1
	},
	[32] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f22c0[5] = {
	[0] = {
		.pFrame = sOamFrame_5f17a0,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f17c0,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f17c8,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f17e8,
		.timer = 1
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f22e8[5] = {
	[0] = {
		.pFrame = sOamFrame_5f17f0,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1810,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f1818,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f1838,
		.timer = 1
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2310[5] = {
	[0] = {
		.pFrame = sOamFrame_5f1840,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f1860,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f186e,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f188e,
		.timer = 1
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2338[5] = {
	[0] = {
		.pFrame = sOamFrame_5f189c,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f18bc,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f18ca,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f18ea,
		.timer = 1
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2360[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b4e,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2370[2] = {
	[0] = {
		.pFrame = sOamFrame_5f190c,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2380[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1920,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2390[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1934,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f23a0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1948,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f23b0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f195c,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f23c0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1970,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f23d0[10] = {
	[0] = {
		.pFrame = sOamFrame_5f1984,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f199e,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f19b8,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f19d2,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f19ec,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5f19d2,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f19b8,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f199e,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f1984,
		.timer = 2
	},
	[9] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2420[7] = {
	[0] = {
		.pFrame = sOamFrame_5f1a06,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1a14,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f1a22,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1a30,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5f1a22,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5f1a14,
		.timer = 8
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2458[7] = {
	[0] = {
		.pFrame = sOamFrame_5f1a3e,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f1a4c,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f1a5a,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f1a68,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5f1a5a,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5f1a4c,
		.timer = 8
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2490[5] = {
	[0] = {
		.pFrame = sOamFrame_5f1b16,
		.timer = 6
	},
	[1] = {
		.pFrame = sOamFrame_5f1b24,
		.timer = 6
	},
	[2] = {
		.pFrame = sOamFrame_5f1b16,
		.timer = 6
	},
	[3] = {
		.pFrame = sOamFrame_5f1b24,
		.timer = 6
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f24b8[5] = {
	[0] = {
		.pFrame = sOamFrame_5f1b32,
		.timer = 6
	},
	[1] = {
		.pFrame = sOamFrame_5f1b40,
		.timer = 6
	},
	[2] = {
		.pFrame = sOamFrame_5f1b32,
		.timer = 6
	},
	[3] = {
		.pFrame = sOamFrame_5f1b40,
		.timer = 6
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f24e0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1a76,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f24f0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1a8a,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2500[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1a9e,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2510[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1ab2,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2520[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1ac6,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2530[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1ada,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2540[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1aee,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2550[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b02,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2560[2] = {
	[0] = {
		.pFrame = sOamFrame_5f18f8,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2570[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b5c,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2580[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b76,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2590[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b8a,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25a0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1b9e,
		.timer = 255
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25b0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1bbe,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25c0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1bcc,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25d0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1bda,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25e0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1be8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f25f0[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1bf0,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f2600[2] = {
	[0] = {
		.pFrame = sOamFrame_5f1bf8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

static const u16 sOamFrame_5f2610[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-8, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 705, 9, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 711, 9, 0),
	OAM_ENTRY(-8, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 521, 9, 0),
};

static const u16 sOamFrame_5f262a[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 705, 9, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 710, 9, 0),
	OAM_ENTRY(-16, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 520, 9, 0),
};

static const u16 sOamFrame_5f2644[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-32, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 705, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 710, 9, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 708, 9, 0),
	OAM_ENTRY(-32, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 646, 9, 0),
	OAM_ENTRY(16, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 520, 9, 0),
};

static const u16 sOamFrame_5f2670[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-40, -3, OAM_DIMS_16x8, OAM_NO_FLIP, 705, 9, 0),
	OAM_ENTRY(8, -3, OAM_DIMS_32x8, OAM_NO_FLIP, 708, 9, 0),
	OAM_ENTRY(-24, -3, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(-40, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(24, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 520, 9, 0),
};

static const u16 sOamFrame_5f2696[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-40, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 520, 9, 0),
	OAM_ENTRY(-40, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 705, 9, 0),
	OAM_ENTRY(8, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 708, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
};

static const u16 sOamFrame_5f26bc[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-40, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 672, 9, 0),
	OAM_ENTRY(-40, 2, OAM_DIMS_16x16, OAM_NO_FLIP, 673, 9, 0),
	OAM_ENTRY(8, 2, OAM_DIMS_32x16, OAM_NO_FLIP, 676, 9, 0),
	OAM_ENTRY(-24, 10, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_16x32, OAM_NO_FLIP, 520, 9, 0),
	OAM_ENTRY(32, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 649, 9, 0),
	OAM_ENTRY(-40, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(-40, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(24, 10, OAM_DIMS_16x8, OAM_NO_FLIP, 648, 9, 0),
};

static const u16 sOamFrame_5f2700[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-40, -22, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -22, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(-40, -14, OAM_DIMS_8x16, OAM_NO_FLIP, 672, 9, 0),
	OAM_ENTRY(-40, 6, OAM_DIMS_16x16, OAM_NO_FLIP, 673, 9, 0),
	OAM_ENTRY(8, 6, OAM_DIMS_32x16, OAM_NO_FLIP, 676, 9, 0),
	OAM_ENTRY(-24, 14, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(24, -22, OAM_DIMS_16x32, OAM_NO_FLIP, 520, 9, 0),
	OAM_ENTRY(32, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 649, 9, 0),
	OAM_ENTRY(-40, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(-40, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(24, 10, OAM_DIMS_16x8, OAM_NO_FLIP, 648, 9, 0),
};

static const u16 sOamFrame_5f2744[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-40, -28, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -28, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(-40, -20, OAM_DIMS_8x16, OAM_NO_FLIP, 672, 9, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_16x16, OAM_NO_FLIP, 673, 9, 0),
	OAM_ENTRY(8, 12, OAM_DIMS_32x16, OAM_NO_FLIP, 676, 9, 0),
	OAM_ENTRY(-24, 20, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(24, -28, OAM_DIMS_16x32, OAM_NO_FLIP, 520, 9, 0),
	OAM_ENTRY(32, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 649, 9, 0),
	OAM_ENTRY(-40, -4, OAM_DIMS_8x16, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(-40, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 648, 9, 0),
	OAM_ENTRY(-32, -20, OAM_DIMS_64x32, OAM_NO_FLIP, 536, 1, 0),
	OAM_ENTRY(-32, 4, OAM_DIMS_32x16, OAM_NO_FLIP, 664, 1, 0),
	OAM_ENTRY(0, 4, OAM_DIMS_32x16, OAM_NO_FLIP, 668, 1, 0),
};

static const u16 sOamFrame_5f279a[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-40, -32, OAM_DIMS_32x8, OAM_NO_FLIP, 640, 9, 0),
	OAM_ENTRY(-8, -32, OAM_DIMS_32x8, OAM_NO_FLIP, 644, 9, 0),
	OAM_ENTRY(-40, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 672, 9, 0),
	OAM_ENTRY(-40, 16, OAM_DIMS_16x16, OAM_NO_FLIP, 673, 9, 0),
	OAM_ENTRY(8, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 676, 9, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 736, 9, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_16x32, OAM_NO_FLIP, 520, 9, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 649, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(-40, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 675, 9, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_64x32, OAM_NO_FLIP, 536, 1, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 664, 1, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 668, 1, 0),
	OAM_ENTRY(24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 648, 9, 0),
};

static const u16 sOamFrame_5f27f0[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(-88, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(-88, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-104, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-88, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(-88, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
};

static const u16 sOamFrame_5f2828[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 741, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(-64, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(-64, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(-64, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-80, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2872[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 742, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(-48, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(-48, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f28bc[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 743, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(-24, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(-24, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-40, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2912[OAM_DATA_SIZE(13)] = {
	13,
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(-16, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2962[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 741, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(0, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(-16, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f29ca[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 742, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2a32[OAM_DATA_SIZE(19)] = {
	19,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 743, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(32, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(16, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2aa6[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(48, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(48, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2b14[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 741, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(64, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(64, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(64, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(64, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(48, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2b8e[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 742, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(80, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(80, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(80, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(64, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2c08[OAM_DATA_SIZE(22)] = {
	22,
	OAM_ENTRY(-126, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 743, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 522, 8, 0),
	OAM_ENTRY(-128, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 650, 8, 0),
	OAM_ENTRY(-128, 16, OAM_DIMS_32x16, OAM_NO_FLIP, 714, 8, 0),
	OAM_ENTRY(96, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 592, 8, 0),
	OAM_ENTRY(96, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 656, 8, 0),
	OAM_ENTRY(96, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 688, 8, 0),
	OAM_ENTRY(96, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 752, 8, 0),
	OAM_ENTRY(80, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 750, 8, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 590, 8, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 652, 8, 0),
	OAM_ENTRY(-96, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(0, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
	OAM_ENTRY(64, 24, OAM_DIMS_32x8, OAM_Y_FLIP, 652, 8, 0),
};

static const u16 sOamFrame_5f2c8e[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-106, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 462, 3, 0),
	OAM_ENTRY(-115, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 464, 3, 0),
	OAM_ENTRY(-112, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-84, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2cb4[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-113, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 3, 0),
	OAM_ENTRY(-93, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 420, 3, 0),
	OAM_ENTRY(-109, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 494, 3, 0),
	OAM_ENTRY(-102, 0, OAM_DIMS_16x8, OAM_X_FLIP, 494, 3, 0),
	OAM_ENTRY(-110, 12, OAM_DIMS_32x8, OAM_X_FLIP, 496, 3, 0),
	OAM_ENTRY(-118, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 496, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-60, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2cf2[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-114, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 392, 3, 0),
	OAM_ENTRY(-90, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 396, 3, 0),
	OAM_ENTRY(-76, 4, OAM_DIMS_32x8, OAM_X_FLIP, 392, 3, 0),
	OAM_ENTRY(-120, 12, OAM_DIMS_32x8, OAM_NO_FLIP, 500, 3, 0),
	OAM_ENTRY(-105, 12, OAM_DIMS_32x8, OAM_X_FLIP, 500, 3, 0),
	OAM_ENTRY(-111, 1, OAM_DIMS_32x8, OAM_NO_FLIP, 468, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-44, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2d36[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-115, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 424, 3, 0),
	OAM_ENTRY(-59, 4, OAM_DIMS_32x8, OAM_X_FLIP, 424, 3, 0),
	OAM_ENTRY(-90, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 428, 3, 0),
	OAM_ENTRY(-73, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 428, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-28, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2d6e[OAM_DATA_SIZE(16)] = {
	16,
	OAM_ENTRY(-116, 2, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-116, 6, OAM_DIMS_32x8, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(-42, 2, OAM_DIMS_32x8, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(-42, 6, OAM_DIMS_32x8, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-96, 2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-64, 2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-96, 2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-64, 2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-96, 6, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-64, 6, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-12, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2dd0[OAM_DATA_SIZE(16)] = {
	16,
	OAM_ENTRY(-117, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-117, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(-25, 0, OAM_DIMS_32x8, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(-25, 8, OAM_DIMS_32x8, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-52, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-52, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-72, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-72, 0, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(4, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2e32[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(-118, -2, OAM_DIMS_32x16, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-118, 2, OAM_DIMS_32x16, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(-8, -2, OAM_DIMS_32x16, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(-8, 2, OAM_DIMS_32x16, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-90, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 10, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, 10, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-32, 10, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-32, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(20, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2e9a[OAM_DATA_SIZE(19)] = {
	19,
	OAM_ENTRY(-119, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-119, 4, OAM_DIMS_32x16, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(9, -4, OAM_DIMS_32x16, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(9, 4, OAM_DIMS_32x16, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-90, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-8, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(36, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2f0e[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-120, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-120, 6, OAM_DIMS_32x16, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(26, -6, OAM_DIMS_32x16, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(26, 6, OAM_DIMS_32x16, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-90, -6, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, -6, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, -6, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(0, -6, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 14, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, 14, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, 14, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(0, 14, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(52, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f2f88[OAM_DATA_SIZE(22)] = {
	22,
	OAM_ENTRY(-121, -7, OAM_DIMS_32x16, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-121, 7, OAM_DIMS_32x16, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(43, -7, OAM_DIMS_32x16, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(43, 7, OAM_DIMS_32x16, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-90, -7, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, -7, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, -7, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(6, -7, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 15, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, 15, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, 15, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(6, 15, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(24, -7, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(24, 15, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(68, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f300e[OAM_DATA_SIZE(23)] = {
	23,
	OAM_ENTRY(-122, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 384, 3, 0),
	OAM_ENTRY(-122, 8, OAM_DIMS_32x16, OAM_Y_FLIP, 384, 3, 0),
	OAM_ENTRY(60, -8, OAM_DIMS_32x16, OAM_X_FLIP, 384, 3, 0),
	OAM_ENTRY(60, 8, OAM_DIMS_32x16, OAM_XY_FLIP, 384, 3, 0),
	OAM_ENTRY(-90, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(6, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(-90, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-58, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-26, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(6, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(32, -8, OAM_DIMS_32x8, OAM_NO_FLIP, 388, 3, 0),
	OAM_ENTRY(32, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 388, 3, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(84, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f309a[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-120, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(8, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(40, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-122, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(100, -8, OAM_DIMS_8x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f30d2[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 630, 8, 0),
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 530, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 594, 8, 0),
};

static const u16 sOamFrame_5f30e6[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 662, 8, 0),
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 532, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 596, 8, 0),
};

static const u16 sOamFrame_5f30fa[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 694, 8, 0),
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 534, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 598, 8, 0),
};

static const u16 sOamFrame_5f310e[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 622, 8, 0),
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 626, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 690, 8, 0),
};

static const u16 sOamFrame_5f3122[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 628, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 692, 8, 0),
};

static const u16 sOamFrame_5f3130[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 552, 9, 0),
};

static const u16 sOamFrame_5f3138[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 772, 8, 0),
};

static const u16 sOamFrame_5f3140[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 771, 8, 0),
};

static const u16 sOamFrame_5f3148[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f3150[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-48, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f3164[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-80, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(48, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f3184[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-80, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(48, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(80, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-112, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f31b0[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-80, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(48, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(72, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(104, -12, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(-80, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(16, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(48, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(72, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, -4, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(104, -4, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
};

static const u16 sOamFrame_5f321e[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-80, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(72, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(104, -16, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(-80, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(16, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(48, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(72, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(104, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
};

static const u16 sOamFrame_5f328c[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-80, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(16, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(48, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(72, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, 4, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 8, 0),
	OAM_ENTRY(104, 4, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
	OAM_ENTRY(-80, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-48, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-16, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(16, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(48, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(72, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-120, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-112, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(104, -20, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(112, -8, OAM_DIMS_8x16, OAM_X_FLIP, 735, 8, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 735, 8, 0),
};

static const u16 sOamFrame_5f3306[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-72, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(-40, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(56, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(-72, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(-40, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(56, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(72, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(72, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(-120, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 9, 0),
	OAM_ENTRY(-104, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 9, 0),
	OAM_ENTRY(-120, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 9, 0),
	OAM_ENTRY(-104, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 769, 9, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 735, 9, 0),
	OAM_ENTRY(104, -24, OAM_DIMS_16x16, OAM_X_FLIP, 768, 9, 0),
	OAM_ENTRY(104, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 9, 0),
	OAM_ENTRY(112, -8, OAM_DIMS_8x16, OAM_X_FLIP, 735, 9, 0),
};

static const u16 sOamFrame_5f3380[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 778, 9, 0),
};

static const u16 sOamFrame_5f3388[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
};

static const u16 sOamFrame_5f3390[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
};

static const u16 sOamFrame_5f339e[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f33b2[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f33d2[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-112, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f33fe[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-120, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(104, -12, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(72, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(24, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(56, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, -4, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(104, -4, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(72, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(24, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(56, 4, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f346c[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-120, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(104, -16, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(72, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(56, -16, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(104, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(72, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(24, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(56, 8, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f34da[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-120, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(104, -20, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(72, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(24, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(56, -20, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, 4, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(104, 4, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(72, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(24, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(56, 12, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(112, -4, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
};

static const u16 sOamFrame_5f3554[OAM_DATA_SIZE(22)] = {
	22,
	OAM_ENTRY(-120, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(104, -24, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(72, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(24, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(56, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-104, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-72, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(104, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(72, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-40, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(56, 16, OAM_DIMS_32x8, OAM_Y_FLIP, 775, 9, 0),
	OAM_ENTRY(-120, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-120, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(112, -8, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(112, 0, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
};

static const u16 sOamFrame_5f35da[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3606[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3632[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-112, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-112, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3688[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-112, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-112, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f36de[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f370a[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-112, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3736[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-112, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-112, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f378c[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(-112, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-112, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-80, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(48, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(80, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f37e2[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 780, 0, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 770, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 9, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 768, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 770, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
};

static const u16 sOamFrame_5f3826[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-8, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 910, 0, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 780, 0, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 770, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 9, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 768, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 770, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
};

static const u16 sOamFrame_5f3870[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 784, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 777, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
};

static const u16 sOamFrame_5f38b4[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 908, 3, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 784, 3, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 777, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
};

static const u16 sOamFrame_5f38fe[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 772, 8, 0),
};

static const u16 sOamFrame_5f3906[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 771, 8, 0),
};

static const u16 sOamFrame_5f390e[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f3916[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-20, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
	OAM_ENTRY(-12, -5, OAM_DIMS_32x8, OAM_NO_FLIP, 769, 8, 0),
};

static const u16 sOamFrame_5f3924[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-24, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-24, -4, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_NO_FLIP, 771, 9, 0),
	OAM_ENTRY(-8, 4, OAM_DIMS_16x8, OAM_Y_FLIP, 771, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3950[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-24, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-24, 4, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(8, 4, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 771, 9, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_16x8, OAM_Y_FLIP, 771, 9, 0),
	OAM_ENTRY(-16, -12, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-24, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
};

static const u16 sOamFrame_5f398e[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 768, 8, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 768, 8, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 768, 8, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 771, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 771, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 800, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 800, 9, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f39d2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 778, 9, 0),
};

static const u16 sOamFrame_5f39da[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 776, 9, 0),
};

static const u16 sOamFrame_5f39e2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
};

static const u16 sOamFrame_5f39ea[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-12, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 775, 9, 0),
	OAM_ENTRY(-20, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 778, 9, 0),
};

static const u16 sOamFrame_5f39f8[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(-24, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-24, -4, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(8, -12, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(8, -4, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, -12, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(-8, 4, OAM_DIMS_16x8, OAM_Y_FLIP, 777, 9, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3a24[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-24, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-24, 4, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(8, -20, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(8, 4, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_16x8, OAM_Y_FLIP, 777, 9, 0),
	OAM_ENTRY(-24, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(-16, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 516, 9, 0),
	OAM_ENTRY(-16, 4, OAM_DIMS_32x8, OAM_NO_FLIP, 580, 9, 0),
};

static const u16 sOamFrame_5f3a62[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 774, 9, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_Y_FLIP, 774, 9, 0),
	OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_X_FLIP, 774, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_XY_FLIP, 774, 9, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 777, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x8, OAM_Y_FLIP, 777, 9, 0),
	OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(16, 0, OAM_DIMS_8x8, OAM_X_FLIP, 806, 9, 0),
	OAM_ENTRY(-24, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 806, 9, 0),
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 516, 9, 0),
};

static const u16 sOamFrame_5f3aa6[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 791, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 622, 8, 0),
};

static const u16 sOamFrame_5f3aba[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 793, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 857, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 622, 8, 0),
};

static const u16 sOamFrame_5f3ace[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-120, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 795, 8, 0),
	OAM_ENTRY(-120, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 859, 8, 0),
	OAM_ENTRY(-128, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 622, 8, 0),
};

static const u16 sOamFrame_5f3ae2[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 89, 5, 0),
	OAM_ENTRY(-45, -68, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(-13, -68, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-53, -63, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-74, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 0, 5, 0),
	OAM_ENTRY(-58, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 2, 5, 0),
	OAM_ENTRY(-74, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 64, 5, 0),
	OAM_ENTRY(-58, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 66, 5, 0),
	OAM_ENTRY(-119, -25, OAM_DIMS_32x16, OAM_NO_FLIP, 113, 5, 0),
	OAM_ENTRY(-119, -9, OAM_DIMS_32x8, OAM_NO_FLIP, 117, 5, 0),
};

static const u16 sOamFrame_5f3b2c[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 89, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-45, -68, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(-13, -68, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-53, -63, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-74, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 3, 5, 0),
	OAM_ENTRY(-58, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 5, 5, 0),
	OAM_ENTRY(-74, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 67, 5, 0),
	OAM_ENTRY(-58, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 69, 5, 0),
	OAM_ENTRY(-119, -25, OAM_DIMS_32x16, OAM_NO_FLIP, 113, 5, 0),
	OAM_ENTRY(-119, -9, OAM_DIMS_32x8, OAM_NO_FLIP, 117, 5, 0),
};

static const u16 sOamFrame_5f3b76[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 89, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-45, -68, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(-13, -68, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-53, -63, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-74, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 6, 5, 0),
	OAM_ENTRY(-58, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 8, 5, 0),
	OAM_ENTRY(-74, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 70, 5, 0),
	OAM_ENTRY(-58, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 72, 5, 0),
	OAM_ENTRY(-119, -25, OAM_DIMS_32x16, OAM_NO_FLIP, 113, 5, 0),
	OAM_ENTRY(-119, -9, OAM_DIMS_32x8, OAM_NO_FLIP, 117, 5, 0),
};

static const u16 sOamFrame_5f3bc0[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-45, -68, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(-13, -68, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-53, -63, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-74, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 9, 5, 0),
	OAM_ENTRY(-58, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 11, 5, 0),
	OAM_ENTRY(-74, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 73, 5, 0),
	OAM_ENTRY(-58, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 75, 5, 0),
	OAM_ENTRY(-119, -25, OAM_DIMS_32x16, OAM_NO_FLIP, 113, 5, 0),
	OAM_ENTRY(-119, -9, OAM_DIMS_32x8, OAM_NO_FLIP, 117, 5, 0),
};

static const u16 sOamFrame_5f3c04[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-45, -68, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(-13, -68, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-53, -63, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-74, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 12, 5, 0),
	OAM_ENTRY(-58, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 14, 5, 0),
	OAM_ENTRY(-74, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 76, 5, 0),
	OAM_ENTRY(-58, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 78, 5, 0),
	OAM_ENTRY(-119, -25, OAM_DIMS_32x16, OAM_NO_FLIP, 113, 5, 0),
	OAM_ENTRY(-119, -9, OAM_DIMS_32x8, OAM_NO_FLIP, 117, 5, 0),
};

static const u16 sOamFrame_5f3c48[OAM_DATA_SIZE(23)] = {
	23,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-35, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0, 5, 0),
	OAM_ENTRY(-19, -14, OAM_DIMS_8x16, OAM_NO_FLIP, 2, 5, 0),
	OAM_ENTRY(-35, 2, OAM_DIMS_16x8, OAM_NO_FLIP, 64, 5, 0),
	OAM_ENTRY(-19, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 66, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 15, 5, 0),
	OAM_ENTRY(-47, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 16, 5, 0),
	OAM_ENTRY(-81, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 17, 5, 0),
	OAM_ENTRY(-49, -6, OAM_DIMS_8x16, OAM_NO_FLIP, 21, 5, 0),
	OAM_ENTRY(-10, -23, OAM_DIMS_8x8, OAM_X_FLIP, 16, 5, 0),
	OAM_ENTRY(-2, -29, OAM_DIMS_32x16, OAM_NO_FLIP, 22, 5, 0),
	OAM_ENTRY(30, -29, OAM_DIMS_8x16, OAM_NO_FLIP, 26, 5, 0),
	OAM_ENTRY(-81, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 27, 5, 0),
	OAM_ENTRY(-49, -6, OAM_DIMS_8x16, OAM_NO_FLIP, 31, 5, 0),
	OAM_ENTRY(2, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 47, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3cd4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(119, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 144, 5, 0),
};

static const u16 sOamFrame_5f3cdc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(111, -2, OAM_DIMS_16x8, OAM_NO_FLIP, 143, 5, 0),
};

static const u16 sOamFrame_5f3ce4[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(111, -2, OAM_DIMS_16x8, OAM_NO_FLIP, 143, 5, 0),
	OAM_ENTRY(103, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 142, 5, 0),
};

static const u16 sOamFrame_5f3cf2[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
};

static const u16 sOamFrame_5f3cfa[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(87, 6, OAM_DIMS_16x8, OAM_NO_FLIP, 139, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3d1a[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(87, 6, OAM_DIMS_16x8, OAM_NO_FLIP, 139, 5, 0),
	OAM_ENTRY(79, 6, OAM_DIMS_8x8, OAM_NO_FLIP, 138, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3d40[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3d60[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(63, 11, OAM_DIMS_8x8, OAM_NO_FLIP, 112, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3d86[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(55, 11, OAM_DIMS_16x8, OAM_NO_FLIP, 111, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3dac[OAM_DATA_SIZE(7)] = {
	7,
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(55, 11, OAM_DIMS_16x8, OAM_NO_FLIP, 111, 5, 0),
	OAM_ENTRY(47, 11, OAM_DIMS_8x8, OAM_NO_FLIP, 110, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
};

static const u16 sOamFrame_5f3dd8[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
};

static const u16 sOamFrame_5f3e10[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(31, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 108, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
};

static const u16 sOamFrame_5f3e4e[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(23, 16, OAM_DIMS_16x8, OAM_NO_FLIP, 107, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
};

static const u16 sOamFrame_5f3e8c[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
};

static const u16 sOamFrame_5f3eca[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
};

static const u16 sOamFrame_5f3f08[OAM_DATA_SIZE(13)] = {
	13,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
};

static const u16 sOamFrame_5f3f58[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 88, 5, 0),
};

static const u16 sOamFrame_5f3fae[OAM_DATA_SIZE(15)] = {
	15,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 88, 5, 0),
	OAM_ENTRY(-47, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 16, 5, 0),
};

static const u16 sOamFrame_5f400a[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 88, 5, 0),
	OAM_ENTRY(-47, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 16, 5, 0),
	OAM_ENTRY(-81, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 17, 5, 0),
	OAM_ENTRY(-49, -6, OAM_DIMS_8x16, OAM_NO_FLIP, 21, 5, 0),
};

static const u16 sOamFrame_5f4072[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(48, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(94, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(-49, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 87, 5, 0),
	OAM_ENTRY(95, -2, OAM_DIMS_32x8, OAM_NO_FLIP, 141, 5, 0),
	OAM_ENTRY(71, 6, OAM_DIMS_32x8, OAM_NO_FLIP, 137, 5, 0),
	OAM_ENTRY(39, 11, OAM_DIMS_32x8, OAM_NO_FLIP, 109, 5, 0),
	OAM_ENTRY(7, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 105, 5, 0),
	OAM_ENTRY(90, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 102, 5, 0),
	OAM_ENTRY(106, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 104, 5, 0),
	OAM_ENTRY(43, 19, OAM_DIMS_16x16, OAM_NO_FLIP, 99, 5, 0),
	OAM_ENTRY(59, 19, OAM_DIMS_8x16, OAM_NO_FLIP, 101, 5, 0),
	OAM_ENTRY(-58, 23, OAM_DIMS_16x16, OAM_NO_FLIP, 96, 5, 0),
	OAM_ENTRY(-42, 23, OAM_DIMS_8x16, OAM_NO_FLIP, 98, 5, 0),
	OAM_ENTRY(-43, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 88, 5, 0),
	OAM_ENTRY(-47, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 16, 5, 0),
	OAM_ENTRY(-81, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 27, 5, 0),
	OAM_ENTRY(-49, -6, OAM_DIMS_8x16, OAM_NO_FLIP, 31, 5, 0),
};

static const u16 sOamFrame_5f40da[OAM_DATA_SIZE(47)] = {
	47,
	OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 164, 2, 0),
	OAM_ENTRY(-24, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 195, 2, 0),
	OAM_ENTRY(-32, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 226, 2, 0),
	OAM_ENTRY(8, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 199, 2, 0),
	OAM_ENTRY(24, -32, OAM_DIMS_8x16, OAM_NO_FLIP, 201, 2, 0),
	OAM_ENTRY(-48, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 320, 2, 0),
	OAM_ENTRY(-48, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 288, 2, 0),
	OAM_ENTRY(-32, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 354, 2, 0),
	OAM_ENTRY(32, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 298, 2, 0),
	OAM_ENTRY(32, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 362, 2, 0),
	OAM_ENTRY(-40, 16, OAM_DIMS_16x8, OAM_NO_FLIP, 174, 2, 0),
	OAM_ENTRY(-24, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 176, 2, 0),
	OAM_ENTRY(24, 16, OAM_DIMS_16x8, OAM_NO_FLIP, 182, 2, 0),
	OAM_ENTRY(-16, 72, OAM_DIMS_32x8, OAM_NO_FLIP, 303, 2, 0),
	OAM_ENTRY(-8, 80, OAM_DIMS_16x8, OAM_NO_FLIP, 336, 2, 0),
	OAM_ENTRY(-32, 64, OAM_DIMS_8x8, OAM_NO_FLIP, 269, 2, 0),
	OAM_ENTRY(24, 64, OAM_DIMS_8x8, OAM_NO_FLIP, 276, 2, 0),
	OAM_ENTRY(0, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 243, 2, 0),
	OAM_ENTRY(-8, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 261, 6, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 325, 6, 0),
	OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 292, 6, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 262, 4, 0),
	OAM_ENTRY(-8, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 197, 4, 0),
	OAM_ENTRY(-8, -24, OAM_DIMS_32x8, OAM_NO_FLIP, 229, 4, 0),
	OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 227, 4, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 290, 4, 0),
	OAM_ENTRY(-32, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 258, 4, 0),
	OAM_ENTRY(-16, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 324, 4, 0),
	OAM_ENTRY(-24, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 355, 4, 0),
	OAM_ENTRY(-16, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 356, 4, 0),
	OAM_ENTRY(-16, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 177, 4, 0),
	OAM_ENTRY(-40, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 225, 7, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 289, 7, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 256, 7, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 194, 7, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 234, 7, 0),
	OAM_ENTRY(40, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 267, 7, 0),
	OAM_ENTRY(48, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 300, 7, 0),
	OAM_ENTRY(-16, 24, OAM_DIMS_32x8, OAM_NO_FLIP, 209, 7, 0),
	OAM_ENTRY(-8, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 242, 7, 0),
	OAM_ENTRY(16, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 181, 7, 0),
	OAM_ENTRY(40, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 184, 7, 0),
	OAM_ENTRY(24, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 214, 7, 0),
	OAM_ENTRY(-32, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 207, 7, 0),
	OAM_ENTRY(-24, 64, OAM_DIMS_8x16, OAM_NO_FLIP, 270, 7, 0),
	OAM_ENTRY(16, 64, OAM_DIMS_8x16, OAM_NO_FLIP, 275, 7, 0),
	OAM_ENTRY(-16, 64, OAM_DIMS_32x8, OAM_NO_FLIP, 271, 7, 0),
};

static const u16 sOamFrame_5f41f6[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(0, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 149, 5, 0),
};

const struct FrameData sIntroArrivingAtBslBslPopupOam_Opening[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 84
	},
	[1] = {
		.pFrame = sOamFrame_5f2610,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f262a,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f2644,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f2670,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f2696,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f26bc,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f2700,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f2744,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f279a,
		.timer = 255
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslBslPopupOam_Closing[10] = {
	[0] = {
		.pFrame = sOamFrame_5f279a,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f2744,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f2700,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f26bc,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f2696,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f2670,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f2644,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f262a,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f2610,
		.timer = 1
	},
	[9] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamPanelFrameOam_Opening[13] = {
	[0] = {
		.pFrame = sOamFrame_5f27f0,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f2828,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f2872,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f28bc,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f2912,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f2962,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f29ca,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f2a32,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f2aa6,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f2b14,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5f2b8e,
		.timer = 2
	},
	[11] = {
		.pFrame = sOamFrame_5f2c08,
		.timer = 50
	},
	[12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamPanelFrameOam_Closing[13] = {
	[0] = {
		.pFrame = sOamFrame_5f2c08,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f2b8e,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f2b14,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f2aa6,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f2a32,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f29ca,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f2962,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f2912,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f28bc,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f2872,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f2828,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f27f0,
		.timer = 50
	},
	[12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamPanelBackgroundOam_Opening[13] = {
	[0] = {
		.pFrame = sOamFrame_5f2c8e,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f2cb4,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f2cf2,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f2d36,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f2d6e,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f2dd0,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f2e32,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f2e9a,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f2f0e,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f2f88,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5f300e,
		.timer = 2
	},
	[11] = {
		.pFrame = sOamFrame_5f309a,
		.timer = 50
	},
	[12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamPanelBackgroundOam_Closing[13] = {
	[0] = {
		.pFrame = sOamFrame_5f309a,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f300e,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f2f88,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f2f0e,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f2e9a,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f2e32,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f2dd0,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f2d6e,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f2d36,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f2cf2,
		.timer = 1
	},
	[10] = {
		.pFrame = sOamFrame_5f2cb4,
		.timer = 1
	},
	[11] = {
		.pFrame = sOamFrame_5f2c8e,
		.timer = 255
	},
	[12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamLensOam_Opening[5] = {
	[0] = {
		.pFrame = sOamFrame_5f30d2,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f30e6,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f30fa,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f310e,
		.timer = 255
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamLensOam_Closing[5] = {
	[0] = {
		.pFrame = sOamFrame_5f310e,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f30fa,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f30e6,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f30d2,
		.timer = 255
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4498[2] = {
	[0] = {
		.pFrame = sOamFrame_5f3122,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f44a8[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3138,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3140,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3148,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f3150,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3164,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3184,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f31b0,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f321e,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f328c,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3306,
		.timer = 255
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4500[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3306,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f328c,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f321e,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f31b0,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3184,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3164,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f3150,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f3148,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3140,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3138,
		.timer = 2
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4558[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f35da,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f3606,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3632,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3688,
		.timer = 255
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f45b0[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3688,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3632,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3606,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f35da,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4608[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f36de,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f370a,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3736,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f378c,
		.timer = 255
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4660[11] = {
	[0] = {
		.pFrame = sOamFrame_5f378c,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3736,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f370a,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f36de,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3130,
		.timer = 2
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f46b8[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3380,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3388,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3390,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f339e,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f33b2,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f33d2,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f33fe,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f346c,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f34da,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3554,
		.timer = 255
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4710[11] = {
	[0] = {
		.pFrame = sOamFrame_5f3554,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f34da,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f346c,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f33fe,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f33d2,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f33b2,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f339e,
		.timer = 2
	},
	[7] = {
		.pFrame = sOamFrame_5f3390,
		.timer = 2
	},
	[8] = {
		.pFrame = sOamFrame_5f3388,
		.timer = 2
	},
	[9] = {
		.pFrame = sOamFrame_5f3380,
		.timer = 2
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4768[2] = {
	[0] = {
		.pFrame = sOamFrame_5f37e2,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4778[3] = {
	[0] = {
		.pFrame = sOamFrame_5f37e2,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f3826,
		.timer = 8
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4790[2] = {
	[0] = {
		.pFrame = sOamFrame_5f3870,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f47a0[3] = {
	[0] = {
		.pFrame = sOamFrame_5f3870,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f38b4,
		.timer = 8
	},
	[2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f47b8[8] = {
	[0] = {
		.pFrame = sOamFrame_5f38fe,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3906,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f390e,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f3916,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f3924,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3950,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f398e,
		.timer = 2
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f47f8[8] = {
	[0] = {
		.pFrame = sOamFrame_5f398e,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3950,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f3924,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f3916,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f390e,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3906,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f38fe,
		.timer = 2
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4838[8] = {
	[0] = {
		.pFrame = sOamFrame_5f39d2,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f39da,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f39e2,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f39ea,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f39f8,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f3a24,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f3a62,
		.timer = 2
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sOam_5f4878[8] = {
	[0] = {
		.pFrame = sOamFrame_5f3a62,
		.timer = 2
	},
	[1] = {
		.pFrame = sOamFrame_5f3a24,
		.timer = 2
	},
	[2] = {
		.pFrame = sOamFrame_5f39f8,
		.timer = 2
	},
	[3] = {
		.pFrame = sOamFrame_5f39ea,
		.timer = 2
	},
	[4] = {
		.pFrame = sOamFrame_5f39e2,
		.timer = 2
	},
	[5] = {
		.pFrame = sOamFrame_5f39da,
		.timer = 2
	},
	[6] = {
		.pFrame = sOamFrame_5f39d2,
		.timer = 2
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslAdamLensOam_Glowing[6] = {
	[0] = {
		.pFrame = sOamFrame_5f310e,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f3aa6,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f3aba,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f3ace,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5f3aa6,
		.timer = 8
	},
	[5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslShipTrajectoryOam[26] = {
	[0] = {
		.pFrame = sOamFrame_5f3cd4,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5f3cdc,
		.timer = 3
	},
	[2] = {
		.pFrame = sOamFrame_5f3ce4,
		.timer = 3
	},
	[3] = {
		.pFrame = sOamFrame_5f3cf2,
		.timer = 3
	},
	[4] = {
		.pFrame = sOamFrame_5f3cfa,
		.timer = 3
	},
	[5] = {
		.pFrame = sOamFrame_5f3d1a,
		.timer = 3
	},
	[6] = {
		.pFrame = sOamFrame_5f3d40,
		.timer = 3
	},
	[7] = {
		.pFrame = sOamFrame_5f3d60,
		.timer = 3
	},
	[8] = {
		.pFrame = sOamFrame_5f3d86,
		.timer = 3
	},
	[9] = {
		.pFrame = sOamFrame_5f3dac,
		.timer = 3
	},
	[10] = {
		.pFrame = sOamFrame_5f3dd8,
		.timer = 3
	},
	[11] = {
		.pFrame = sOamFrame_5f3e10,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5f3e4e,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5f3e8c,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5f3eca,
		.timer = 27
	},
	[15] = {
		.pFrame = sOamFrame_5f3f08,
		.timer = 15
	},
	[16] = {
		.pFrame = sOamFrame_5f3f58,
		.timer = 3
	},
	[17] = {
		.pFrame = sOamFrame_5f3fae,
		.timer = 3
	},
	[18] = {
		.pFrame = sOamFrame_5f400a,
		.timer = 30
	},
	[19] = {
		.pFrame = sOamFrame_5f4072,
		.timer = 20
	},
	[20] = {
		.pFrame = sOamFrame_5f400a,
		.timer = 30
	},
	[21] = {
		.pFrame = sOamFrame_5f4072,
		.timer = 20
	},
	[22] = {
		.pFrame = sOamFrame_5f400a,
		.timer = 30
	},
	[23] = {
		.pFrame = sOamFrame_5f4072,
		.timer = 20
	},
	[24] = {
		.pFrame = sOamFrame_5f400a,
		.timer = 30
	},
	[25] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslPlanetsAndShipOam[6] = {
	[0] = {
		.pFrame = sOamFrame_5f3ae2,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5f3b2c,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f3b76,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f3bc0,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5f3c04,
		.timer = 8
	},
	[5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroSamusCuredScreenGlareOam[3] = {
	[0] = {
		.pFrame = sOamFrame_5f40da,
		.timer = 3
	},
	[1] = {
		.pFrame = sOamFrame_5f41f6,
		.timer = 1
	},
	[2] = FRAME_DATA_TERMINATOR
};

static const u16 sOamFrame_5f4a00[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-37, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 128, 0, 0),
	OAM_ENTRY(-5, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 132, 0, 0),
	OAM_ENTRY(-37, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 0, 0),
};

static const u16 sOamFrame_5f4a14[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-35, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 0, 0),
	OAM_ENTRY(-35, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 136, 0, 0),
	OAM_ENTRY(-3, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 140, 0, 0),
};

static const u16 sOamFrame_5f4a28[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-33, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 16, 0, 0),
	OAM_ENTRY(-33, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 144, 0, 0),
	OAM_ENTRY(-1, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 148, 0, 0),
};

static const u16 sOamFrame_5f4a3c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 24, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 152, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 156, 0, 0),
};

static const u16 sOamFrame_5f4a50[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 160, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 288, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 292, 0, 0),
};

static const u16 sOamFrame_5f4a64[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 168, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 296, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 300, 0, 0),
};

static const u16 sOamFrame_5f4a78[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 176, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 304, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 308, 0, 0),
};

static const u16 sOamFrame_5f4a8c[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 184, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 312, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 316, 0, 0),
};

static const u16 sOamFrame_5f4aa0[OAM_DATA_SIZE(3)] = {
	3,
	OAM_ENTRY(-32, -16, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 0, 0),
	OAM_ENTRY(-32, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 448, 0, 0),
	OAM_ENTRY(0, 16, OAM_DIMS_32x8, OAM_NO_FLIP, 452, 0, 0),
};

static const u16 sOamFrame_5f4ab4[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 336, 0, 0),
};

static const u16 sOamFrame_5f4abc[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 544, 1, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 556, 1, 0),
	OAM_ENTRY(-32, -40, OAM_DIMS_64x32, OAM_NO_FLIP, 484, 1, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_64x64, OAM_NO_FLIP, 612, 1, 0),
	OAM_ENTRY(-16, 56, OAM_DIMS_32x16, OAM_NO_FLIP, 870, 1, 0),
};

static const u16 sOamFrame_5f4adc[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 3, 0),
};

static const u16 sOamFrame_5f4ae4[OAM_DATA_SIZE(4)] = {
	4,
	OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 731, 3, 0),
	OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 733, 3, 0),
	OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 795, 3, 0),
	OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 797, 3, 0),
};

static const u16 sOamFrame_5f4afe[OAM_DATA_SIZE(1)] = {
	1,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 378, 3, 0),
};

static const u16 sOamFrame_5f4b06[OAM_DATA_SIZE(5)] = {
	5,
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 378, 3, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 440, 3, 0),
	OAM_ENTRY(0, -32, OAM_DIMS_32x32, OAM_X_FLIP, 440, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_32x32, OAM_XY_FLIP, 440, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_32x32, OAM_Y_FLIP, 440, 3, 0),
};

static const u16 sOamFrame_5f4b26[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-32, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 444, 3, 0),
	OAM_ENTRY(0, -32, OAM_DIMS_32x32, OAM_X_FLIP, 444, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_32x32, OAM_XY_FLIP, 444, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_32x32, OAM_Y_FLIP, 444, 3, 0),
	OAM_ENTRY(6, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(14, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 698, 3, 0),
	OAM_ENTRY(22, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(-14, -4, OAM_DIMS_8x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(-22, -4, OAM_DIMS_8x8, OAM_X_FLIP, 698, 3, 0),
	OAM_ENTRY(-30, -4, OAM_DIMS_8x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 380, 3, 0),
};

static const u16 sOamFrame_5f4b6a[OAM_DATA_SIZE(9)] = {
	9,
	OAM_ENTRY(-32, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 572, 3, 0),
	OAM_ENTRY(0, -32, OAM_DIMS_32x32, OAM_X_FLIP, 572, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_32x32, OAM_XY_FLIP, 572, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_32x32, OAM_Y_FLIP, 572, 3, 0),
	OAM_ENTRY(4, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(36, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(-36, -4, OAM_DIMS_32x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(-52, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 382, 3, 0),
};

static const u16 sOamFrame_5f4ba2[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-32, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 568, 3, 0),
	OAM_ENTRY(-32, 0, OAM_DIMS_32x32, OAM_Y_FLIP, 568, 3, 0),
	OAM_ENTRY(0, -32, OAM_DIMS_32x32, OAM_X_FLIP, 568, 3, 0),
	OAM_ENTRY(0, 0, OAM_DIMS_32x32, OAM_XY_FLIP, 568, 3, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_32x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_32x8, OAM_X_FLIP, 696, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 696, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 696, 3, 0),
};

static const u16 sOamFrame_5f4be0[OAM_DATA_SIZE(14)] = {
	14,
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 698, 3, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 698, 3, 0),
	OAM_ENTRY(32, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(32, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 698, 3, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(64, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_X_FLIP, 698, 3, 0),
	OAM_ENTRY(-32, -4, OAM_DIMS_16x8, OAM_X_FLIP, 698, 3, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_16x8, OAM_X_FLIP, 698, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
};

static const u16 sOamFrame_5f4c36[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(64, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(32, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 700, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-96, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-32, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-32, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_X_FLIP, 700, 3, 0),
};

static const u16 sOamFrame_5f4ca4[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-16, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-32, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-48, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-96, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(16, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(32, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(48, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(64, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(80, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
};

static const u16 sOamFrame_5f4cee[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-36, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-72, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(-108, -4, OAM_DIMS_16x8, OAM_X_FLIP, 702, 3, 0),
	OAM_ENTRY(20, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(56, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
	OAM_ENTRY(92, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 702, 3, 0),
};

static const u16 sOamFrame_5f4d14[OAM_DATA_SIZE(6)] = {
	6,
	OAM_ENTRY(-40, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 734, 3, 0),
	OAM_ENTRY(-80, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 734, 3, 0),
	OAM_ENTRY(-120, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 734, 3, 0),
	OAM_ENTRY(24, -4, OAM_DIMS_16x8, OAM_X_FLIP, 734, 3, 0),
	OAM_ENTRY(64, -4, OAM_DIMS_16x8, OAM_X_FLIP, 734, 3, 0),
	OAM_ENTRY(104, -4, OAM_DIMS_16x8, OAM_X_FLIP, 734, 3, 0),
};

const struct FrameData sIntroArrivingAtBslSamusShipOam[11] = {
	[0] = {
		.pFrame = sOamFrame_5f4a00,
		.timer = 50
	},
	[1] = {
		.pFrame = sOamFrame_5f4a14,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5f4a28,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5f4a3c,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5f4a50,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5f4a64,
		.timer = 8
	},
	[6] = {
		.pFrame = sOamFrame_5f4a78,
		.timer = 8
	},
	[7] = {
		.pFrame = sOamFrame_5f4a8c,
		.timer = 8
	},
	[8] = {
		.pFrame = sOamFrame_5f4aa0,
		.timer = 8
	},
	[9] = {
		.pFrame = sOamFrame_5f4ab4,
		.timer = 50
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslBslOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5f4abc,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslThrusterExplosionOam[18] = {
	[0] = {
		.pFrame = sOamFrame_5f4adc,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f4ae4,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f4b06,
		.timer = 1
	},
	[3] = {
		.pFrame = sOamFrame_5f4adc,
		.timer = 1
	},
	[4] = {
		.pFrame = sOamFrame_5f4ae4,
		.timer = 1
	},
	[5] = {
		.pFrame = sOamFrame_5f4b06,
		.timer = 1
	},
	[6] = {
		.pFrame = sOamFrame_5f4adc,
		.timer = 1
	},
	[7] = {
		.pFrame = sOamFrame_5f4ae4,
		.timer = 1
	},
	[8] = {
		.pFrame = sOamFrame_5f4b06,
		.timer = 1
	},
	[9] = {
		.pFrame = sOamFrame_5f4b26,
		.timer = 2
	},
	[10] = {
		.pFrame = sOamFrame_5f4b6a,
		.timer = 2
	},
	[11] = {
		.pFrame = sOamFrame_5f4ba2,
		.timer = 3
	},
	[12] = {
		.pFrame = sOamFrame_5f4be0,
		.timer = 3
	},
	[13] = {
		.pFrame = sOamFrame_5f4c36,
		.timer = 3
	},
	[14] = {
		.pFrame = sOamFrame_5f4ca4,
		.timer = 4
	},
	[15] = {
		.pFrame = sOamFrame_5f4cee,
		.timer = 5
	},
	[16] = {
		.pFrame = sOamFrame_5f4d14,
		.timer = 6
	},
	[17] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroArrivingAtBslThrustersOam[4] = {
	[0] = {
		.pFrame = sOamFrame_5f4afe,
		.timer = 1
	},
	[1] = {
		.pFrame = sOamFrame_5f4ae4,
		.timer = 1
	},
	[2] = {
		.pFrame = sOamFrame_5f4adc,
		.timer = 1
	},
	[3] = FRAME_DATA_TERMINATOR
};

// Rows 0-3 of the BG palette whose rows 4-15 are sPal_5f4ed4 (only the transparent color is set).
// Not referenced by code: only rows 4-15 are copied
const u16 sPal_5f4e54[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5f4e54.pal");

const u16 sPal_5f4ed4[12 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5f4ed4.pal");
const u16 sIntroArrivingAtBslSpaceMapPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/space_map.pal");
const u16 sIntroApproachingBslObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/approaching_bsl_obj.pal");

const u32 sIntroTilemap_5f5454[385] = INCBIN_U32("data/new_file_intro/5f5454.tm.lz");
const u32 sIntroArrivingAtBslSpaceMapTilemap[368] = INCBIN_U32("data/new_file_intro/5f5a58.tm.lz");
const u32 sIntroSamusMonologueBgTilemap[368] = INCBIN_U32("data/new_file_intro/samus_monologue_bg.tm.lz");
const u32 sIntroTilemap_5f65d8[238] = INCBIN_U32("data/new_file_intro/5f65d8.tm.lz");

// Samus cured cutscene: BG palette rows 0-3 for each step of the fade (sPalPointers_79c354)
const u16 sIntroSamusCuredFadePal_0[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_0.pal");
const u16 sIntroSamusCuredFadePal_1[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_1.pal");
const u16 sIntroSamusCuredFadePal_2[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_2.pal");
const u16 sIntroSamusCuredFadePal_3[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_3.pal");
const u16 sIntroSamusCuredFadePal_4[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_4.pal");
const u16 sIntroSamusCuredFadePal_5[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_5.pal");
const u16 sIntroSamusCuredFadePal_6[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_6.pal");
const u16 sIntroSamusCuredFadePal_7[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_7.pal");
const u16 sIntroSamusCuredFadePal_8[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_8.pal");
const u16 sIntroSamusCuredFadePal_9[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_9.pal");
const u16 sIntroSamusCuredFadePal_10[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_10.pal");
const u16 sIntroSamusCuredFadePal_11[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_11.pal");
const u16 sIntroSamusCuredFadePal_12[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_12.pal");
const u16 sIntroSamusCuredFadePal_13[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_13.pal");
const u16 sIntroSamusCuredFadePal_14[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_14.pal");
const u16 sIntroSamusCuredFadePal_15[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_cured_fade_15.pal");

const u32 sIntroLandingOnBslBgGfx[3697] = INCBIN_U32("data/new_file_intro/landing_on_bsl_bg.gfx.lz");
const u32 sIntroLandingOnBslObjGfx[3297] = INCBIN_U32("data/new_file_intro/landing_on_bsl_obj.gfx.lz");

static const u16 sOamFrame_5fded8[OAM_DATA_SIZE(12)] = {
	12,
	OAM_ENTRY(-72, 0, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 9, 0),
	OAM_ENTRY(-72, 16, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 9, 0),
	OAM_ENTRY(8, 0, OAM_DIMS_64x32, OAM_NO_FLIP, 330, 9, 0),
	OAM_ENTRY(8, 16, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 9, 0),
	OAM_ENTRY(-8, 0, OAM_DIMS_16x32, OAM_NO_FLIP, 328, 9, 0),
	OAM_ENTRY(-8, 32, OAM_DIMS_16x16, OAM_NO_FLIP, 456, 9, 0),
	OAM_ENTRY(56, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 9, 0),
	OAM_ENTRY(-72, -32, OAM_DIMS_64x32, OAM_NO_FLIP, 64, 9, 0),
	OAM_ENTRY(-8, -32, OAM_DIMS_64x32, OAM_NO_FLIP, 72, 9, 0),
	OAM_ENTRY(56, -32, OAM_DIMS_16x32, OAM_NO_FLIP, 80, 9, 0),
	OAM_ENTRY(-72, -48, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 9, 0),
	OAM_ENTRY(-8, -48, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 9, 0),
};

static const u16 sOamFrame_5fdf22[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(56, -51, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 9, 0),
	OAM_ENTRY(-72, -35, OAM_DIMS_64x32, OAM_NO_FLIP, 64, 9, 0),
	OAM_ENTRY(-8, -35, OAM_DIMS_64x32, OAM_NO_FLIP, 72, 9, 0),
	OAM_ENTRY(56, -35, OAM_DIMS_16x32, OAM_NO_FLIP, 80, 9, 0),
	OAM_ENTRY(-72, -51, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 9, 0),
	OAM_ENTRY(-8, -51, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 9, 0),
	OAM_ENTRY(-72, 2, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 9, 0),
	OAM_ENTRY(-72, 18, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 9, 0),
	OAM_ENTRY(8, 2, OAM_DIMS_64x32, OAM_NO_FLIP, 330, 9, 0),
	OAM_ENTRY(8, 18, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 9, 0),
	OAM_ENTRY(-8, 2, OAM_DIMS_16x32, OAM_NO_FLIP, 328, 9, 0),
	OAM_ENTRY(-8, 34, OAM_DIMS_16x16, OAM_NO_FLIP, 456, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 466, 10, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 470, 10, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 468, 10, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 466, 10, 0),
	OAM_ENTRY(56, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 470, 10, 0),
};

static const u16 sOamFrame_5fdf8a[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(56, -52, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 9, 0),
	OAM_ENTRY(-72, -36, OAM_DIMS_64x32, OAM_NO_FLIP, 64, 9, 0),
	OAM_ENTRY(-8, -36, OAM_DIMS_64x32, OAM_NO_FLIP, 72, 9, 0),
	OAM_ENTRY(56, -36, OAM_DIMS_16x32, OAM_NO_FLIP, 80, 9, 0),
	OAM_ENTRY(-72, -52, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 9, 0),
	OAM_ENTRY(-8, -52, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 9, 0),
	OAM_ENTRY(-72, 4, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 9, 0),
	OAM_ENTRY(-72, 20, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 9, 0),
	OAM_ENTRY(8, 4, OAM_DIMS_64x32, OAM_NO_FLIP, 330, 9, 0),
	OAM_ENTRY(8, 20, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 9, 0),
	OAM_ENTRY(-8, 4, OAM_DIMS_16x32, OAM_NO_FLIP, 328, 9, 0),
	OAM_ENTRY(-8, 36, OAM_DIMS_16x16, OAM_NO_FLIP, 456, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 466, 10, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 470, 10, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 468, 10, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 466, 10, 0),
	OAM_ENTRY(56, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 470, 10, 0),
};

static const u16 sOamFrame_5fdff2[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(-72, 6, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 9, 0),
	OAM_ENTRY(-72, 22, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 9, 0),
	OAM_ENTRY(8, 6, OAM_DIMS_64x32, OAM_NO_FLIP, 330, 9, 0),
	OAM_ENTRY(8, 22, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 9, 0),
	OAM_ENTRY(-8, 6, OAM_DIMS_16x32, OAM_NO_FLIP, 328, 9, 0),
	OAM_ENTRY(-8, 38, OAM_DIMS_16x16, OAM_NO_FLIP, 456, 9, 0),
	OAM_ENTRY(56, -54, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 9, 0),
	OAM_ENTRY(-72, -38, OAM_DIMS_64x32, OAM_NO_FLIP, 64, 9, 0),
	OAM_ENTRY(-8, -38, OAM_DIMS_64x32, OAM_NO_FLIP, 72, 9, 0),
	OAM_ENTRY(56, -38, OAM_DIMS_16x32, OAM_NO_FLIP, 80, 9, 0),
	OAM_ENTRY(-72, -54, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 9, 0),
	OAM_ENTRY(-8, -54, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 466, 10, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 470, 10, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 468, 10, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 466, 10, 0),
	OAM_ENTRY(56, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 470, 10, 0),
};

static const u16 sOamFrame_5fe05a[OAM_DATA_SIZE(17)] = {
	17,
	OAM_ENTRY(-72, 8, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 9, 0),
	OAM_ENTRY(-72, 24, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 9, 0),
	OAM_ENTRY(8, 8, OAM_DIMS_64x32, OAM_NO_FLIP, 330, 9, 0),
	OAM_ENTRY(8, 24, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 9, 0),
	OAM_ENTRY(-8, 8, OAM_DIMS_16x32, OAM_NO_FLIP, 328, 9, 0),
	OAM_ENTRY(-8, 40, OAM_DIMS_16x16, OAM_NO_FLIP, 456, 9, 0),
	OAM_ENTRY(56, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 9, 0),
	OAM_ENTRY(-72, -40, OAM_DIMS_64x32, OAM_NO_FLIP, 64, 9, 0),
	OAM_ENTRY(-8, -40, OAM_DIMS_64x32, OAM_NO_FLIP, 72, 9, 0),
	OAM_ENTRY(56, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 80, 9, 0),
	OAM_ENTRY(-72, -56, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 9, 0),
	OAM_ENTRY(-8, -56, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 9, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 466, 10, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 470, 10, 0),
	OAM_ENTRY(-8, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 468, 10, 0),
	OAM_ENTRY(24, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 466, 10, 0),
	OAM_ENTRY(56, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 470, 10, 0),
};

static const u16 sOamFrame_5fe0c2[OAM_DATA_SIZE(22)] = {
	22,
	OAM_ENTRY(-72, 10, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 9, 0),
	OAM_ENTRY(-72, 26, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 9, 0),
	OAM_ENTRY(8, 10, OAM_DIMS_64x32, OAM_NO_FLIP, 330, 9, 0),
	OAM_ENTRY(8, 26, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 9, 0),
	OAM_ENTRY(-8, 10, OAM_DIMS_16x32, OAM_NO_FLIP, 328, 9, 0),
	OAM_ENTRY(-8, 42, OAM_DIMS_16x16, OAM_NO_FLIP, 456, 9, 0),
	OAM_ENTRY(-72, -10, OAM_DIMS_32x16, OAM_NO_FLIP, 192, 10, 1),
	OAM_ENTRY(-40, -10, OAM_DIMS_32x16, OAM_NO_FLIP, 196, 10, 1),
	OAM_ENTRY(-8, -10, OAM_DIMS_32x16, OAM_NO_FLIP, 200, 10, 1),
	OAM_ENTRY(24, -10, OAM_DIMS_32x16, OAM_NO_FLIP, 204, 10, 1),
	OAM_ENTRY(56, -10, OAM_DIMS_16x16, OAM_NO_FLIP, 208, 10, 1),
	OAM_ENTRY(-72, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 256, 10, 1),
	OAM_ENTRY(-40, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 260, 10, 1),
	OAM_ENTRY(-8, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 264, 10, 1),
	OAM_ENTRY(24, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 268, 10, 1),
	OAM_ENTRY(56, -6, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 10, 1),
	OAM_ENTRY(56, -58, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 9, 0),
	OAM_ENTRY(-72, -42, OAM_DIMS_64x32, OAM_NO_FLIP, 64, 9, 0),
	OAM_ENTRY(-8, -42, OAM_DIMS_64x32, OAM_NO_FLIP, 72, 9, 0),
	OAM_ENTRY(56, -42, OAM_DIMS_16x32, OAM_NO_FLIP, 80, 9, 0),
	OAM_ENTRY(-72, -58, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 9, 0),
	OAM_ENTRY(-8, -58, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 9, 0),
};

static const u16 sOamFrame_5fe148[OAM_DATA_SIZE(22)] = {
	22,
	OAM_ENTRY(-72, 12, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 9, 0),
	OAM_ENTRY(-72, 28, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 9, 0),
	OAM_ENTRY(8, 12, OAM_DIMS_64x32, OAM_NO_FLIP, 330, 9, 0),
	OAM_ENTRY(8, 28, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 9, 0),
	OAM_ENTRY(-8, 12, OAM_DIMS_16x32, OAM_NO_FLIP, 328, 9, 0),
	OAM_ENTRY(-8, 44, OAM_DIMS_16x16, OAM_NO_FLIP, 456, 9, 0),
	OAM_ENTRY(-72, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 192, 10, 1),
	OAM_ENTRY(-40, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 196, 10, 1),
	OAM_ENTRY(-8, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 200, 10, 1),
	OAM_ENTRY(24, -12, OAM_DIMS_32x16, OAM_NO_FLIP, 204, 10, 1),
	OAM_ENTRY(56, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 208, 10, 1),
	OAM_ENTRY(-72, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 256, 10, 1),
	OAM_ENTRY(-40, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 260, 10, 1),
	OAM_ENTRY(-8, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 264, 10, 1),
	OAM_ENTRY(24, -4, OAM_DIMS_32x16, OAM_NO_FLIP, 268, 10, 1),
	OAM_ENTRY(56, -4, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 10, 1),
	OAM_ENTRY(56, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 9, 0),
	OAM_ENTRY(-72, -44, OAM_DIMS_64x32, OAM_NO_FLIP, 64, 9, 0),
	OAM_ENTRY(-8, -44, OAM_DIMS_64x32, OAM_NO_FLIP, 72, 9, 0),
	OAM_ENTRY(56, -44, OAM_DIMS_16x32, OAM_NO_FLIP, 80, 9, 0),
	OAM_ENTRY(-72, -60, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 9, 0),
	OAM_ENTRY(-8, -60, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 9, 0),
};

static const u16 sOamFrame_5fe1ce[OAM_DATA_SIZE(22)] = {
	22,
	OAM_ENTRY(-72, 14, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 9, 0),
	OAM_ENTRY(-72, 30, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 9, 0),
	OAM_ENTRY(8, 14, OAM_DIMS_64x32, OAM_NO_FLIP, 330, 9, 0),
	OAM_ENTRY(8, 30, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 9, 0),
	OAM_ENTRY(-8, 14, OAM_DIMS_16x32, OAM_NO_FLIP, 328, 9, 0),
	OAM_ENTRY(-8, 46, OAM_DIMS_16x16, OAM_NO_FLIP, 456, 9, 0),
	OAM_ENTRY(-72, -14, OAM_DIMS_32x16, OAM_NO_FLIP, 192, 10, 1),
	OAM_ENTRY(-40, -14, OAM_DIMS_32x16, OAM_NO_FLIP, 196, 10, 1),
	OAM_ENTRY(-8, -14, OAM_DIMS_32x16, OAM_NO_FLIP, 200, 10, 1),
	OAM_ENTRY(24, -14, OAM_DIMS_32x16, OAM_NO_FLIP, 204, 10, 1),
	OAM_ENTRY(56, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 208, 10, 1),
	OAM_ENTRY(-72, -2, OAM_DIMS_32x16, OAM_NO_FLIP, 256, 10, 1),
	OAM_ENTRY(-40, -2, OAM_DIMS_32x16, OAM_NO_FLIP, 260, 10, 1),
	OAM_ENTRY(-8, -2, OAM_DIMS_32x16, OAM_NO_FLIP, 264, 10, 1),
	OAM_ENTRY(24, -2, OAM_DIMS_32x16, OAM_NO_FLIP, 268, 10, 1),
	OAM_ENTRY(56, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 10, 1),
	OAM_ENTRY(56, -62, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 9, 0),
	OAM_ENTRY(-72, -46, OAM_DIMS_64x32, OAM_NO_FLIP, 64, 9, 0),
	OAM_ENTRY(-8, -46, OAM_DIMS_64x32, OAM_NO_FLIP, 72, 9, 0),
	OAM_ENTRY(56, -46, OAM_DIMS_16x32, OAM_NO_FLIP, 80, 9, 0),
	OAM_ENTRY(-72, -62, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 9, 0),
	OAM_ENTRY(-8, -62, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 9, 0),
};

static const u16 sOamFrame_5fe254[OAM_DATA_SIZE(22)] = {
	22,
	OAM_ENTRY(-72, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 192, 10, 1),
	OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 196, 10, 1),
	OAM_ENTRY(-8, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 200, 10, 1),
	OAM_ENTRY(24, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 204, 10, 1),
	OAM_ENTRY(56, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 208, 10, 1),
	OAM_ENTRY(-72, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 256, 10, 1),
	OAM_ENTRY(-40, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 260, 10, 1),
	OAM_ENTRY(-8, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 264, 10, 1),
	OAM_ENTRY(24, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 268, 10, 1),
	OAM_ENTRY(56, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 10, 1),
	OAM_ENTRY(-72, 16, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 9, 0),
	OAM_ENTRY(-72, 32, OAM_DIMS_64x32, OAM_NO_FLIP, 384, 9, 0),
	OAM_ENTRY(8, 16, OAM_DIMS_64x32, OAM_NO_FLIP, 330, 9, 0),
	OAM_ENTRY(8, 32, OAM_DIMS_64x32, OAM_NO_FLIP, 394, 9, 0),
	OAM_ENTRY(-8, 16, OAM_DIMS_16x32, OAM_NO_FLIP, 328, 9, 0),
	OAM_ENTRY(-8, 48, OAM_DIMS_16x16, OAM_NO_FLIP, 456, 9, 0),
	OAM_ENTRY(56, -64, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 9, 0),
	OAM_ENTRY(-72, -48, OAM_DIMS_64x32, OAM_NO_FLIP, 64, 9, 0),
	OAM_ENTRY(-8, -48, OAM_DIMS_64x32, OAM_NO_FLIP, 72, 9, 0),
	OAM_ENTRY(56, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 80, 9, 0),
	OAM_ENTRY(-72, -64, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 9, 0),
	OAM_ENTRY(-8, -64, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 9, 0),
};

static const u16 sOamFrame_5fe2da[OAM_DATA_SIZE(11)] = {
	11,
	OAM_ENTRY(-72, -18, OAM_DIMS_32x16, OAM_NO_FLIP, 192, 10, 1),
	OAM_ENTRY(-40, -18, OAM_DIMS_32x16, OAM_NO_FLIP, 196, 10, 1),
	OAM_ENTRY(-8, -18, OAM_DIMS_32x16, OAM_NO_FLIP, 200, 10, 1),
	OAM_ENTRY(24, -18, OAM_DIMS_32x16, OAM_NO_FLIP, 204, 10, 1),
	OAM_ENTRY(56, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 208, 10, 1),
	OAM_ENTRY(56, -66, OAM_DIMS_16x16, OAM_NO_FLIP, 16, 9, 0),
	OAM_ENTRY(-72, -50, OAM_DIMS_64x32, OAM_NO_FLIP, 64, 9, 0),
	OAM_ENTRY(-8, -50, OAM_DIMS_64x32, OAM_NO_FLIP, 72, 9, 0),
	OAM_ENTRY(56, -50, OAM_DIMS_16x32, OAM_NO_FLIP, 80, 9, 0),
	OAM_ENTRY(-72, -66, OAM_DIMS_64x32, OAM_NO_FLIP, 0, 9, 0),
	OAM_ENTRY(-8, -66, OAM_DIMS_64x32, OAM_NO_FLIP, 8, 9, 0),
};

static const u16 sOamFrame_5fe31e[OAM_DATA_SIZE(13)] = {
	13,
	OAM_ENTRY(-72, 2, OAM_DIMS_32x16, OAM_NO_FLIP, 256, 10, 1),
	OAM_ENTRY(-40, 2, OAM_DIMS_32x16, OAM_NO_FLIP, 260, 10, 1),
	OAM_ENTRY(-8, 2, OAM_DIMS_32x16, OAM_NO_FLIP, 264, 10, 1),
	OAM_ENTRY(24, 2, OAM_DIMS_32x16, OAM_NO_FLIP, 268, 10, 1),
	OAM_ENTRY(56, 2, OAM_DIMS_16x16, OAM_NO_FLIP, 272, 10, 1),
	OAM_ENTRY(-72, 18, OAM_DIMS_64x32, OAM_NO_FLIP, 320, 9, 0),
	OAM_ENTRY(-8, 18, OAM_DIMS_64x32, OAM_NO_FLIP, 328, 9, 0),
	OAM_ENTRY(56, 18, OAM_DIMS_16x32, OAM_NO_FLIP, 336, 9, 0),
	OAM_ENTRY(-72, 50, OAM_DIMS_32x16, OAM_NO_FLIP, 448, 9, 0),
	OAM_ENTRY(-40, 50, OAM_DIMS_32x16, OAM_NO_FLIP, 452, 9, 0),
	OAM_ENTRY(-8, 50, OAM_DIMS_32x16, OAM_NO_FLIP, 456, 9, 0),
	OAM_ENTRY(24, 50, OAM_DIMS_32x16, OAM_NO_FLIP, 460, 9, 0),
	OAM_ENTRY(56, 50, OAM_DIMS_16x16, OAM_NO_FLIP, 464, 9, 0),
};

const struct FrameData sIntroBslHangarDoorOam_Opening[10] = {
	[0] = {
		.pFrame = sOamFrame_5fded8,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5fdf22,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5fdf8a,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5fdff2,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5fe05a,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5fe0c2,
		.timer = 8
	},
	[6] = {
		.pFrame = sOamFrame_5fe148,
		.timer = 8
	},
	[7] = {
		.pFrame = sOamFrame_5fe1ce,
		.timer = 8
	},
	[8] = {
		.pFrame = sOamFrame_5fe254,
		.timer = 8
	},
	[9] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroBslHangarDoorOam_Closing[10] = {
	[0] = {
		.pFrame = sOamFrame_5fe254,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5fe1ce,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5fe148,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5fe0c2,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5fe05a,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5fdff2,
		.timer = 8
	},
	[6] = {
		.pFrame = sOamFrame_5fdf8a,
		.timer = 8
	},
	[7] = {
		.pFrame = sOamFrame_5fdf22,
		.timer = 8
	},
	[8] = {
		.pFrame = sOamFrame_5fded8,
		.timer = 8
	},
	[9] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroBslHangarDoorOam_Top[2] = {
	[0] = {
		.pFrame = sOamFrame_5fe2da,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroBslHangarDoorOam_Bottom[2] = {
	[0] = {
		.pFrame = sOamFrame_5fe31e,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroBslHangarDoorOam_Closed[2] = {
	[0] = {
		.pFrame = sOamFrame_5fded8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

static const u16 sOamFrame_5fe440[OAM_DATA_SIZE(28)] = {
	28,
	OAM_ENTRY(-80, -67, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -67, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -67, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(56, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(72, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(72, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(56, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(64, 16, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-104, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-104, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-88, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-88, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-96, 16, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(46, -17, OAM_DIMS_32x32, OAM_NO_FLIP, 772, 8, 0),
	OAM_ENTRY(46, 7, OAM_DIMS_32x32, OAM_NO_FLIP, 868, 8, 0),
	OAM_ENTRY(-78, -17, OAM_DIMS_32x32, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-78, 7, OAM_DIMS_32x32, OAM_NO_FLIP, 864, 8, 0),
	OAM_ENTRY(-56, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -10, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -2, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -10, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -2, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fe4ea[OAM_DATA_SIZE(28)] = {
	28,
	OAM_ENTRY(-80, -66, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -66, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -66, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(56, -34, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(72, -34, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(72, -2, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(56, -2, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(64, 14, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-104, -34, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-104, -2, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-88, -34, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-88, -2, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-96, 14, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(46, -17, OAM_DIMS_32x32, OAM_NO_FLIP, 772, 8, 0),
	OAM_ENTRY(46, 7, OAM_DIMS_32x32, OAM_NO_FLIP, 868, 8, 0),
	OAM_ENTRY(-78, -17, OAM_DIMS_32x32, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-78, 7, OAM_DIMS_32x32, OAM_NO_FLIP, 864, 8, 0),
	OAM_ENTRY(-56, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -11, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -3, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -11, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -3, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fe594[OAM_DATA_SIZE(28)] = {
	28,
	OAM_ENTRY(-80, -65, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -65, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -65, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -25, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -25, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -25, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(56, -36, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(72, -36, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(72, -4, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(56, -4, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(64, 12, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-104, -36, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-104, -4, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-88, -36, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-88, -4, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-96, 12, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(46, -17, OAM_DIMS_32x32, OAM_NO_FLIP, 772, 8, 0),
	OAM_ENTRY(46, 7, OAM_DIMS_32x32, OAM_NO_FLIP, 868, 8, 0),
	OAM_ENTRY(-78, -17, OAM_DIMS_32x32, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-78, 7, OAM_DIMS_32x32, OAM_NO_FLIP, 864, 8, 0),
	OAM_ENTRY(-56, -28, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -28, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -12, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -4, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -28, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -28, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -12, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fe63e[OAM_DATA_SIZE(28)] = {
	28,
	OAM_ENTRY(-80, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(56, -38, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(72, -38, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(72, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(56, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(64, 10, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-104, -38, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-104, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-88, -38, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-88, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-96, 10, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(46, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 772, 8, 0),
	OAM_ENTRY(46, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 868, 8, 0),
	OAM_ENTRY(-78, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-78, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 864, 8, 0),
	OAM_ENTRY(-56, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fe6e8[OAM_DATA_SIZE(28)] = {
	28,
	OAM_ENTRY(-80, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(56, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(72, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(72, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(56, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(64, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-104, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-104, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-88, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-96, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(46, -30, OAM_DIMS_32x32, OAM_NO_FLIP, 772, 8, 0),
	OAM_ENTRY(46, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 868, 8, 0),
	OAM_ENTRY(-77, -30, OAM_DIMS_32x32, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-77, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 864, 8, 0),
	OAM_ENTRY(-56, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fe792[OAM_DATA_SIZE(28)] = {
	28,
	OAM_ENTRY(-80, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(54, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(70, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(70, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(54, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(62, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-102, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-102, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-86, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-86, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-94, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(44, -37, OAM_DIMS_32x32, OAM_NO_FLIP, 772, 8, 0),
	OAM_ENTRY(44, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 868, 8, 0),
	OAM_ENTRY(-76, -37, OAM_DIMS_32x32, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-76, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 864, 8, 0),
	OAM_ENTRY(-56, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fe83c[OAM_DATA_SIZE(26)] = {
	26,
	OAM_ENTRY(-80, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(52, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(68, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(68, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(52, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(60, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-100, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-100, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-84, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-84, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-92, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(40, -19, OAM_DIMS_32x32, OAM_NO_FLIP, 868, 8, 0),
	OAM_ENTRY(-72, -19, OAM_DIMS_32x32, OAM_NO_FLIP, 864, 8, 0),
	OAM_ENTRY(-56, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fe8da[OAM_DATA_SIZE(26)] = {
	26,
	OAM_ENTRY(-80, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(50, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(66, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(66, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(50, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(58, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-98, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-98, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-82, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-82, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-90, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(36, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 868, 8, 0),
	OAM_ENTRY(-68, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 864, 8, 0),
	OAM_ENTRY(-56, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fe978[OAM_DATA_SIZE(24)] = {
	24,
	OAM_ENTRY(-80, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(48, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(64, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(64, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(48, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(56, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-96, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-96, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-80, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-80, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-88, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(-56, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fea0a[OAM_DATA_SIZE(24)] = {
	24,
	OAM_ENTRY(-80, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -64, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(46, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(62, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(62, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(46, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(54, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-94, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-94, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-78, -40, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-78, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-86, 8, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(-56, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -29, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -13, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fea9c[OAM_DATA_SIZE(24)] = {
	24,
	OAM_ENTRY(-80, -63, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -63, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -63, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -23, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -23, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -23, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(46, -39, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(62, -39, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(62, -7, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(46, -7, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(54, 9, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-94, -39, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-94, -7, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-78, -39, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-78, -7, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-86, 9, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(-56, -30, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -30, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -14, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -30, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -30, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -14, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5feb2e[OAM_DATA_SIZE(24)] = {
	24,
	OAM_ENTRY(-80, -62, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -62, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -62, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -22, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -22, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -22, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(46, -38, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(62, -38, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(62, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(46, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(54, 10, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-94, -38, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-94, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-78, -38, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-78, -6, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-86, 10, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(-56, -31, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -31, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -15, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -7, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -31, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -31, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -15, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -7, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5febc0[OAM_DATA_SIZE(24)] = {
	24,
	OAM_ENTRY(-80, -61, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -61, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -61, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -21, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -21, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -21, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(46, -37, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(62, -37, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(62, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(46, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(54, 11, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-94, -37, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-94, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-78, -37, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-78, -5, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-86, 11, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(-56, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -8, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fec52[OAM_DATA_SIZE(28)] = {
	28,
	OAM_ENTRY(-80, -66, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -66, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -66, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -26, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(57, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(73, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(73, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(57, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(65, 16, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-105, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-105, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-89, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-89, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-97, 16, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(47, -17, OAM_DIMS_32x32, OAM_NO_FLIP, 772, 8, 0),
	OAM_ENTRY(47, 7, OAM_DIMS_32x32, OAM_NO_FLIP, 868, 8, 0),
	OAM_ENTRY(-79, -17, OAM_DIMS_32x32, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-79, 7, OAM_DIMS_32x32, OAM_NO_FLIP, 864, 8, 0),
	OAM_ENTRY(-56, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -11, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -3, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -27, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -11, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -3, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5fecfc[OAM_DATA_SIZE(28)] = {
	28,
	OAM_ENTRY(-80, -65, OAM_DIMS_64x64, OAM_NO_FLIP, 512, 8, 0),
	OAM_ENTRY(16, -65, OAM_DIMS_64x64, OAM_NO_FLIP, 524, 8, 0),
	OAM_ENTRY(-32, -65, OAM_DIMS_64x64, OAM_NO_FLIP, 518, 8, 0),
	OAM_ENTRY(-16, -25, OAM_DIMS_32x32, OAM_NO_FLIP, 680, 8, 0),
	OAM_ENTRY(-64, -25, OAM_DIMS_32x32, OAM_NO_FLIP, 674, 8, 0),
	OAM_ENTRY(32, -25, OAM_DIMS_32x32, OAM_NO_FLIP, 686, 8, 0),
	OAM_ENTRY(58, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 730, 8, 0),
	OAM_ENTRY(74, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 732, 8, 0),
	OAM_ENTRY(74, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 860, 8, 0),
	OAM_ENTRY(58, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 858, 8, 0),
	OAM_ENTRY(66, 16, OAM_DIMS_32x32, OAM_NO_FLIP, 923, 8, 0),
	OAM_ENTRY(-106, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 725, 8, 0),
	OAM_ENTRY(-106, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 853, 8, 0),
	OAM_ENTRY(-90, -32, OAM_DIMS_32x32, OAM_NO_FLIP, 727, 8, 0),
	OAM_ENTRY(-90, 0, OAM_DIMS_32x32, OAM_NO_FLIP, 855, 8, 0),
	OAM_ENTRY(-98, 16, OAM_DIMS_32x32, OAM_NO_FLIP, 918, 8, 0),
	OAM_ENTRY(47, -17, OAM_DIMS_32x32, OAM_NO_FLIP, 772, 8, 0),
	OAM_ENTRY(47, 7, OAM_DIMS_32x32, OAM_NO_FLIP, 868, 8, 0),
	OAM_ENTRY(-79, -17, OAM_DIMS_32x32, OAM_NO_FLIP, 768, 8, 0),
	OAM_ENTRY(-79, 7, OAM_DIMS_32x32, OAM_NO_FLIP, 864, 8, 0),
	OAM_ENTRY(-56, -28, OAM_DIMS_32x32, OAM_NO_FLIP, 776, 8, 0),
	OAM_ENTRY(-32, -28, OAM_DIMS_32x32, OAM_NO_FLIP, 779, 8, 0),
	OAM_ENTRY(-56, -12, OAM_DIMS_32x32, OAM_NO_FLIP, 840, 8, 0),
	OAM_ENTRY(-32, -4, OAM_DIMS_32x32, OAM_NO_FLIP, 875, 8, 0),
	OAM_ENTRY(0, -28, OAM_DIMS_32x32, OAM_NO_FLIP, 783, 8, 0),
	OAM_ENTRY(16, -28, OAM_DIMS_32x32, OAM_NO_FLIP, 785, 8, 0),
	OAM_ENTRY(16, -12, OAM_DIMS_32x32, OAM_NO_FLIP, 849, 8, 0),
	OAM_ENTRY(0, -4, OAM_DIMS_32x32, OAM_NO_FLIP, 879, 8, 0),
};

static const u16 sOamFrame_5feda6[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-56, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 532, 14, 0),
	OAM_ENTRY(-40, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 534, 14, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 596, 14, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 598, 14, 0),
	OAM_ENTRY(40, -24, OAM_DIMS_16x16, OAM_X_FLIP, 532, 14, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x16, OAM_X_FLIP, 534, 14, 0),
	OAM_ENTRY(40, -8, OAM_DIMS_16x8, OAM_X_FLIP, 596, 14, 0),
	OAM_ENTRY(32, -8, OAM_DIMS_8x8, OAM_X_FLIP, 598, 14, 0),
	OAM_ENTRY(-80, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 541, 14, 0),
	OAM_ENTRY(-64, -48, OAM_DIMS_8x16, OAM_NO_FLIP, 543, 14, 0),
	OAM_ENTRY(-80, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 605, 14, 0),
	OAM_ENTRY(-64, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 607, 14, 0),
	OAM_ENTRY(-72, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 628, 14, 0),
	OAM_ENTRY(64, -48, OAM_DIMS_16x16, OAM_X_FLIP, 541, 14, 0),
	OAM_ENTRY(56, -48, OAM_DIMS_8x16, OAM_X_FLIP, 543, 14, 0),
	OAM_ENTRY(64, -32, OAM_DIMS_16x8, OAM_X_FLIP, 605, 14, 0),
	OAM_ENTRY(56, -32, OAM_DIMS_8x8, OAM_X_FLIP, 607, 14, 0),
	OAM_ENTRY(56, -16, OAM_DIMS_16x16, OAM_X_FLIP, 628, 14, 0),
};

static const u16 sOamFrame_5fee14[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-60, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 535, 14, 0),
	OAM_ENTRY(-44, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 537, 14, 0),
	OAM_ENTRY(-60, -12, OAM_DIMS_16x8, OAM_NO_FLIP, 599, 14, 0),
	OAM_ENTRY(-44, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 601, 14, 0),
	OAM_ENTRY(-88, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 532, 14, 0),
	OAM_ENTRY(-72, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 534, 14, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 596, 14, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 598, 14, 0),
	OAM_ENTRY(44, -28, OAM_DIMS_16x16, OAM_X_FLIP, 535, 14, 0),
	OAM_ENTRY(36, -28, OAM_DIMS_8x16, OAM_X_FLIP, 537, 14, 0),
	OAM_ENTRY(44, -12, OAM_DIMS_16x8, OAM_X_FLIP, 599, 14, 0),
	OAM_ENTRY(36, -12, OAM_DIMS_8x8, OAM_X_FLIP, 601, 14, 0),
	OAM_ENTRY(72, -24, OAM_DIMS_16x16, OAM_X_FLIP, 532, 14, 0),
	OAM_ENTRY(64, -24, OAM_DIMS_8x16, OAM_X_FLIP, 534, 14, 0),
	OAM_ENTRY(72, -8, OAM_DIMS_16x8, OAM_X_FLIP, 596, 14, 0),
	OAM_ENTRY(64, -8, OAM_DIMS_8x8, OAM_X_FLIP, 598, 14, 0),
	OAM_ENTRY(-72, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 628, 14, 0),
	OAM_ENTRY(56, -40, OAM_DIMS_16x16, OAM_X_FLIP, 628, 14, 0),
	OAM_ENTRY(-36, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 634, 14, 0),
	OAM_ENTRY(20, -16, OAM_DIMS_16x16, OAM_X_FLIP, 634, 14, 0),
};

static const u16 sOamFrame_5fee8e[OAM_DATA_SIZE(26)] = {
	26,
	OAM_ENTRY(-64, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 538, 14, 0),
	OAM_ENTRY(-48, -32, OAM_DIMS_8x16, OAM_NO_FLIP, 540, 14, 0),
	OAM_ENTRY(-64, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 602, 14, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 604, 14, 0),
	OAM_ENTRY(-92, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 535, 14, 0),
	OAM_ENTRY(-76, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 537, 14, 0),
	OAM_ENTRY(-92, -12, OAM_DIMS_16x8, OAM_NO_FLIP, 599, 14, 0),
	OAM_ENTRY(-76, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 601, 14, 0),
	OAM_ENTRY(48, -32, OAM_DIMS_16x16, OAM_X_FLIP, 538, 14, 0),
	OAM_ENTRY(40, -32, OAM_DIMS_8x16, OAM_X_FLIP, 540, 14, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_16x8, OAM_X_FLIP, 602, 14, 0),
	OAM_ENTRY(40, -16, OAM_DIMS_8x8, OAM_X_FLIP, 604, 14, 0),
	OAM_ENTRY(76, -28, OAM_DIMS_16x16, OAM_X_FLIP, 535, 14, 0),
	OAM_ENTRY(68, -28, OAM_DIMS_8x16, OAM_X_FLIP, 537, 14, 0),
	OAM_ENTRY(76, -12, OAM_DIMS_16x8, OAM_X_FLIP, 599, 14, 0),
	OAM_ENTRY(68, -12, OAM_DIMS_8x8, OAM_X_FLIP, 601, 14, 0),
	OAM_ENTRY(-80, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 532, 14, 0),
	OAM_ENTRY(-64, -48, OAM_DIMS_8x16, OAM_NO_FLIP, 534, 14, 0),
	OAM_ENTRY(-80, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 596, 14, 0),
	OAM_ENTRY(-64, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 598, 14, 0),
	OAM_ENTRY(64, -48, OAM_DIMS_16x16, OAM_X_FLIP, 532, 14, 0),
	OAM_ENTRY(56, -48, OAM_DIMS_8x16, OAM_X_FLIP, 534, 14, 0),
	OAM_ENTRY(64, -32, OAM_DIMS_16x8, OAM_X_FLIP, 596, 14, 0),
	OAM_ENTRY(56, -32, OAM_DIMS_8x8, OAM_X_FLIP, 598, 14, 0),
	OAM_ENTRY(-40, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 632, 14, 0),
	OAM_ENTRY(24, -16, OAM_DIMS_16x16, OAM_X_FLIP, 632, 14, 0),
};

static const u16 sOamFrame_5fef2c[OAM_DATA_SIZE(26)] = {
	26,
	OAM_ENTRY(-68, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 541, 14, 0),
	OAM_ENTRY(-52, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 543, 14, 0),
	OAM_ENTRY(-68, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 605, 14, 0),
	OAM_ENTRY(-52, -20, OAM_DIMS_8x8, OAM_NO_FLIP, 607, 14, 0),
	OAM_ENTRY(-96, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 538, 14, 0),
	OAM_ENTRY(-80, -32, OAM_DIMS_8x16, OAM_NO_FLIP, 540, 14, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 602, 14, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 604, 14, 0),
	OAM_ENTRY(52, -36, OAM_DIMS_16x16, OAM_X_FLIP, 541, 14, 0),
	OAM_ENTRY(44, -36, OAM_DIMS_8x16, OAM_X_FLIP, 543, 14, 0),
	OAM_ENTRY(52, -20, OAM_DIMS_16x8, OAM_X_FLIP, 605, 14, 0),
	OAM_ENTRY(44, -20, OAM_DIMS_8x8, OAM_X_FLIP, 607, 14, 0),
	OAM_ENTRY(80, -32, OAM_DIMS_16x16, OAM_X_FLIP, 538, 14, 0),
	OAM_ENTRY(72, -32, OAM_DIMS_8x16, OAM_X_FLIP, 540, 14, 0),
	OAM_ENTRY(80, -16, OAM_DIMS_16x8, OAM_X_FLIP, 602, 14, 0),
	OAM_ENTRY(72, -16, OAM_DIMS_8x8, OAM_X_FLIP, 604, 14, 0),
	OAM_ENTRY(-80, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 535, 14, 0),
	OAM_ENTRY(-64, -48, OAM_DIMS_8x16, OAM_NO_FLIP, 537, 14, 0),
	OAM_ENTRY(-80, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 599, 14, 0),
	OAM_ENTRY(-64, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 601, 14, 0),
	OAM_ENTRY(64, -48, OAM_DIMS_16x16, OAM_X_FLIP, 535, 14, 0),
	OAM_ENTRY(56, -48, OAM_DIMS_8x16, OAM_X_FLIP, 537, 14, 0),
	OAM_ENTRY(64, -32, OAM_DIMS_16x8, OAM_X_FLIP, 599, 14, 0),
	OAM_ENTRY(56, -32, OAM_DIMS_8x8, OAM_X_FLIP, 601, 14, 0),
	OAM_ENTRY(-44, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 630, 14, 0),
	OAM_ENTRY(28, -18, OAM_DIMS_16x16, OAM_X_FLIP, 630, 14, 0),
};

static const u16 sOamFrame_5fefca[OAM_DATA_SIZE(20)] = {
	20,
	OAM_ENTRY(-100, -35, OAM_DIMS_16x16, OAM_NO_FLIP, 541, 14, 0),
	OAM_ENTRY(-84, -35, OAM_DIMS_8x16, OAM_NO_FLIP, 543, 14, 0),
	OAM_ENTRY(-100, -19, OAM_DIMS_16x8, OAM_NO_FLIP, 605, 14, 0),
	OAM_ENTRY(-84, -19, OAM_DIMS_8x8, OAM_NO_FLIP, 607, 14, 0),
	OAM_ENTRY(84, -35, OAM_DIMS_16x16, OAM_X_FLIP, 541, 14, 0),
	OAM_ENTRY(76, -35, OAM_DIMS_8x16, OAM_X_FLIP, 543, 14, 0),
	OAM_ENTRY(84, -19, OAM_DIMS_16x8, OAM_X_FLIP, 605, 14, 0),
	OAM_ENTRY(76, -19, OAM_DIMS_8x8, OAM_X_FLIP, 607, 14, 0),
	OAM_ENTRY(-80, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 538, 14, 0),
	OAM_ENTRY(-64, -48, OAM_DIMS_8x16, OAM_NO_FLIP, 540, 14, 0),
	OAM_ENTRY(-80, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 602, 14, 0),
	OAM_ENTRY(-64, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 604, 14, 0),
	OAM_ENTRY(-48, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 628, 14, 0),
	OAM_ENTRY(32, -16, OAM_DIMS_16x16, OAM_X_FLIP, 628, 14, 0),
	OAM_ENTRY(64, -48, OAM_DIMS_16x16, OAM_X_FLIP, 538, 14, 0),
	OAM_ENTRY(56, -48, OAM_DIMS_8x16, OAM_X_FLIP, 540, 14, 0),
	OAM_ENTRY(64, -32, OAM_DIMS_16x8, OAM_X_FLIP, 602, 14, 0),
	OAM_ENTRY(56, -32, OAM_DIMS_8x8, OAM_X_FLIP, 604, 14, 0),
	OAM_ENTRY(-72, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 632, 14, 0),
	OAM_ENTRY(56, -16, OAM_DIMS_16x16, OAM_X_FLIP, 632, 14, 0),
};

static const u16 sOamFrame_5ff044[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-56, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 532, 14, 0),
	OAM_ENTRY(-40, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 534, 14, 0),
	OAM_ENTRY(-56, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 596, 14, 0),
	OAM_ENTRY(-40, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 598, 14, 0),
	OAM_ENTRY(40, -24, OAM_DIMS_16x16, OAM_X_FLIP, 532, 14, 0),
	OAM_ENTRY(32, -24, OAM_DIMS_8x16, OAM_X_FLIP, 534, 14, 0),
	OAM_ENTRY(40, -8, OAM_DIMS_16x8, OAM_X_FLIP, 596, 14, 0),
	OAM_ENTRY(32, -8, OAM_DIMS_8x8, OAM_X_FLIP, 598, 14, 0),
	OAM_ENTRY(-80, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 541, 14, 0),
	OAM_ENTRY(-64, -48, OAM_DIMS_8x16, OAM_NO_FLIP, 543, 14, 0),
	OAM_ENTRY(-80, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 605, 14, 0),
	OAM_ENTRY(-64, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 607, 14, 0),
	OAM_ENTRY(-72, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 628, 14, 0),
	OAM_ENTRY(64, -48, OAM_DIMS_16x16, OAM_X_FLIP, 541, 14, 0),
	OAM_ENTRY(56, -48, OAM_DIMS_8x16, OAM_X_FLIP, 543, 14, 0),
	OAM_ENTRY(64, -32, OAM_DIMS_16x8, OAM_X_FLIP, 605, 14, 0),
	OAM_ENTRY(56, -32, OAM_DIMS_8x8, OAM_X_FLIP, 607, 14, 0),
	OAM_ENTRY(56, -16, OAM_DIMS_16x16, OAM_X_FLIP, 628, 14, 0),
};

static const u16 sOamFrame_5ff0b2[OAM_DATA_SIZE(18)] = {
	18,
	OAM_ENTRY(-60, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 535, 14, 0),
	OAM_ENTRY(-44, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 537, 14, 0),
	OAM_ENTRY(-60, -12, OAM_DIMS_16x8, OAM_NO_FLIP, 599, 14, 0),
	OAM_ENTRY(-44, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 601, 14, 0),
	OAM_ENTRY(-88, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 532, 14, 0),
	OAM_ENTRY(-72, -24, OAM_DIMS_8x16, OAM_NO_FLIP, 534, 14, 0),
	OAM_ENTRY(-88, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 596, 14, 0),
	OAM_ENTRY(-72, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 598, 14, 0),
	OAM_ENTRY(44, -28, OAM_DIMS_16x16, OAM_X_FLIP, 535, 14, 0),
	OAM_ENTRY(36, -28, OAM_DIMS_8x16, OAM_X_FLIP, 537, 14, 0),
	OAM_ENTRY(44, -12, OAM_DIMS_16x8, OAM_X_FLIP, 599, 14, 0),
	OAM_ENTRY(36, -12, OAM_DIMS_8x8, OAM_X_FLIP, 601, 14, 0),
	OAM_ENTRY(72, -24, OAM_DIMS_16x16, OAM_X_FLIP, 532, 14, 0),
	OAM_ENTRY(64, -24, OAM_DIMS_8x16, OAM_X_FLIP, 534, 14, 0),
	OAM_ENTRY(72, -8, OAM_DIMS_16x8, OAM_X_FLIP, 596, 14, 0),
	OAM_ENTRY(64, -8, OAM_DIMS_8x8, OAM_X_FLIP, 598, 14, 0),
	OAM_ENTRY(-72, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 628, 14, 0),
	OAM_ENTRY(56, -40, OAM_DIMS_16x16, OAM_X_FLIP, 628, 14, 0),
};

static const u16 sOamFrame_5ff120[OAM_DATA_SIZE(24)] = {
	24,
	OAM_ENTRY(-64, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 538, 14, 0),
	OAM_ENTRY(-48, -32, OAM_DIMS_8x16, OAM_NO_FLIP, 540, 14, 0),
	OAM_ENTRY(-64, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 602, 14, 0),
	OAM_ENTRY(-48, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 604, 14, 0),
	OAM_ENTRY(-92, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 535, 14, 0),
	OAM_ENTRY(-76, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 537, 14, 0),
	OAM_ENTRY(-92, -12, OAM_DIMS_16x8, OAM_NO_FLIP, 599, 14, 0),
	OAM_ENTRY(-76, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 601, 14, 0),
	OAM_ENTRY(48, -32, OAM_DIMS_16x16, OAM_X_FLIP, 538, 14, 0),
	OAM_ENTRY(40, -32, OAM_DIMS_8x16, OAM_X_FLIP, 540, 14, 0),
	OAM_ENTRY(48, -16, OAM_DIMS_16x8, OAM_X_FLIP, 602, 14, 0),
	OAM_ENTRY(40, -16, OAM_DIMS_8x8, OAM_X_FLIP, 604, 14, 0),
	OAM_ENTRY(76, -28, OAM_DIMS_16x16, OAM_X_FLIP, 535, 14, 0),
	OAM_ENTRY(68, -28, OAM_DIMS_8x16, OAM_X_FLIP, 537, 14, 0),
	OAM_ENTRY(76, -12, OAM_DIMS_16x8, OAM_X_FLIP, 599, 14, 0),
	OAM_ENTRY(68, -12, OAM_DIMS_8x8, OAM_X_FLIP, 601, 14, 0),
	OAM_ENTRY(-80, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 532, 14, 0),
	OAM_ENTRY(-64, -48, OAM_DIMS_8x16, OAM_NO_FLIP, 534, 14, 0),
	OAM_ENTRY(-80, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 596, 14, 0),
	OAM_ENTRY(-64, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 598, 14, 0),
	OAM_ENTRY(64, -48, OAM_DIMS_16x16, OAM_X_FLIP, 532, 14, 0),
	OAM_ENTRY(56, -48, OAM_DIMS_8x16, OAM_X_FLIP, 534, 14, 0),
	OAM_ENTRY(64, -32, OAM_DIMS_16x8, OAM_X_FLIP, 596, 14, 0),
	OAM_ENTRY(56, -32, OAM_DIMS_8x8, OAM_X_FLIP, 598, 14, 0),
};

static const u16 sOamFrame_5ff1b2[OAM_DATA_SIZE(24)] = {
	24,
	OAM_ENTRY(-68, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 541, 14, 0),
	OAM_ENTRY(-52, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 543, 14, 0),
	OAM_ENTRY(-68, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 605, 14, 0),
	OAM_ENTRY(-52, -20, OAM_DIMS_8x8, OAM_NO_FLIP, 607, 14, 0),
	OAM_ENTRY(-96, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 538, 14, 0),
	OAM_ENTRY(-80, -32, OAM_DIMS_8x16, OAM_NO_FLIP, 540, 14, 0),
	OAM_ENTRY(-96, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 602, 14, 0),
	OAM_ENTRY(-80, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 604, 14, 0),
	OAM_ENTRY(52, -36, OAM_DIMS_16x16, OAM_X_FLIP, 541, 14, 0),
	OAM_ENTRY(44, -36, OAM_DIMS_8x16, OAM_X_FLIP, 543, 14, 0),
	OAM_ENTRY(52, -20, OAM_DIMS_16x8, OAM_X_FLIP, 605, 14, 0),
	OAM_ENTRY(44, -20, OAM_DIMS_8x8, OAM_X_FLIP, 607, 14, 0),
	OAM_ENTRY(80, -32, OAM_DIMS_16x16, OAM_X_FLIP, 538, 14, 0),
	OAM_ENTRY(72, -32, OAM_DIMS_8x16, OAM_X_FLIP, 540, 14, 0),
	OAM_ENTRY(80, -16, OAM_DIMS_16x8, OAM_X_FLIP, 602, 14, 0),
	OAM_ENTRY(72, -16, OAM_DIMS_8x8, OAM_X_FLIP, 604, 14, 0),
	OAM_ENTRY(-84, -52, OAM_DIMS_16x16, OAM_NO_FLIP, 535, 14, 0),
	OAM_ENTRY(-68, -52, OAM_DIMS_8x16, OAM_NO_FLIP, 537, 14, 0),
	OAM_ENTRY(-84, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 599, 14, 0),
	OAM_ENTRY(-68, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 601, 14, 0),
	OAM_ENTRY(68, -52, OAM_DIMS_16x16, OAM_X_FLIP, 535, 14, 0),
	OAM_ENTRY(60, -52, OAM_DIMS_8x16, OAM_X_FLIP, 537, 14, 0),
	OAM_ENTRY(68, -36, OAM_DIMS_16x8, OAM_X_FLIP, 599, 14, 0),
	OAM_ENTRY(60, -36, OAM_DIMS_8x8, OAM_X_FLIP, 601, 14, 0),
};

static const u16 sOamFrame_5ff244[OAM_DATA_SIZE(16)] = {
	16,
	OAM_ENTRY(-88, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 538, 14, 0),
	OAM_ENTRY(-72, -56, OAM_DIMS_8x16, OAM_NO_FLIP, 540, 14, 0),
	OAM_ENTRY(-88, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 602, 14, 0),
	OAM_ENTRY(-72, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 604, 14, 0),
	OAM_ENTRY(-100, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 541, 14, 0),
	OAM_ENTRY(-84, -36, OAM_DIMS_8x16, OAM_NO_FLIP, 543, 14, 0),
	OAM_ENTRY(-100, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 605, 14, 0),
	OAM_ENTRY(-84, -20, OAM_DIMS_8x8, OAM_NO_FLIP, 607, 14, 0),
	OAM_ENTRY(72, -56, OAM_DIMS_16x16, OAM_X_FLIP, 538, 14, 0),
	OAM_ENTRY(64, -56, OAM_DIMS_8x16, OAM_X_FLIP, 540, 14, 0),
	OAM_ENTRY(72, -40, OAM_DIMS_16x8, OAM_X_FLIP, 602, 14, 0),
	OAM_ENTRY(64, -40, OAM_DIMS_8x8, OAM_X_FLIP, 604, 14, 0),
	OAM_ENTRY(84, -36, OAM_DIMS_16x16, OAM_X_FLIP, 541, 14, 0),
	OAM_ENTRY(76, -36, OAM_DIMS_8x16, OAM_X_FLIP, 543, 14, 0),
	OAM_ENTRY(84, -20, OAM_DIMS_16x8, OAM_X_FLIP, 605, 14, 0),
	OAM_ENTRY(76, -20, OAM_DIMS_8x8, OAM_X_FLIP, 607, 14, 0),
};

static const u16 sOamFrame_5ff2a6[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-92, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 541, 14, 0),
	OAM_ENTRY(-76, -60, OAM_DIMS_8x16, OAM_NO_FLIP, 543, 14, 0),
	OAM_ENTRY(-92, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 605, 14, 0),
	OAM_ENTRY(-76, -44, OAM_DIMS_8x8, OAM_NO_FLIP, 607, 14, 0),
	OAM_ENTRY(76, -60, OAM_DIMS_16x16, OAM_X_FLIP, 541, 14, 0),
	OAM_ENTRY(68, -60, OAM_DIMS_8x16, OAM_X_FLIP, 543, 14, 0),
	OAM_ENTRY(76, -44, OAM_DIMS_16x8, OAM_X_FLIP, 605, 14, 0),
	OAM_ENTRY(68, -44, OAM_DIMS_8x8, OAM_X_FLIP, 607, 14, 0),
};

static const u16 sOamFrame_5ff2d8[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-64, -40, OAM_DIMS_64x64, OAM_NO_FLIP, 85, 8, 0),
	OAM_ENTRY(0, -40, OAM_DIMS_64x64, OAM_X_FLIP, 85, 8, 0),
};

static const u16 sOamFrame_5ff2e6[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-64, -60, OAM_DIMS_64x64, OAM_NO_FLIP, 21, 8, 0),
	OAM_ENTRY(-64, 4, OAM_DIMS_64x32, OAM_NO_FLIP, 277, 8, 0),
	OAM_ENTRY(-80, -60, OAM_DIMS_16x32, OAM_NO_FLIP, 19, 8, 0),
	OAM_ENTRY(-80, -28, OAM_DIMS_16x32, OAM_NO_FLIP, 147, 8, 0),
	OAM_ENTRY(-80, 4, OAM_DIMS_16x32, OAM_NO_FLIP, 275, 8, 0),
	OAM_ENTRY(0, -60, OAM_DIMS_64x64, OAM_X_FLIP, 21, 8, 0),
	OAM_ENTRY(0, 4, OAM_DIMS_64x32, OAM_X_FLIP, 277, 8, 0),
	OAM_ENTRY(64, -60, OAM_DIMS_16x32, OAM_X_FLIP, 19, 8, 0),
	OAM_ENTRY(64, -28, OAM_DIMS_16x32, OAM_X_FLIP, 147, 8, 0),
	OAM_ENTRY(64, 4, OAM_DIMS_16x32, OAM_X_FLIP, 275, 8, 0),
};

static const u16 sOamFrame_5ff324[OAM_DATA_SIZE(8)] = {
	8,
	OAM_ENTRY(-64, -61, OAM_DIMS_64x64, OAM_NO_FLIP, 21, 8, 0),
	OAM_ENTRY(0, -61, OAM_DIMS_64x64, OAM_X_FLIP, 21, 8, 0),
	OAM_ENTRY(-64, -29, OAM_DIMS_64x64, OAM_NO_FLIP, 149, 8, 0),
	OAM_ENTRY(0, -29, OAM_DIMS_64x64, OAM_X_FLIP, 149, 8, 0),
	OAM_ENTRY(-88, -61, OAM_DIMS_64x64, OAM_NO_FLIP, 18, 8, 0),
	OAM_ENTRY(24, -61, OAM_DIMS_64x64, OAM_X_FLIP, 18, 8, 0),
	OAM_ENTRY(-88, 1, OAM_DIMS_32x32, OAM_NO_FLIP, 274, 8, 0),
	OAM_ENTRY(56, 1, OAM_DIMS_32x32, OAM_X_FLIP, 274, 8, 0),
};

static const u16 sOamFrame_5ff356[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-49, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 158, 14, 0),
	OAM_ENTRY(-33, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 14, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 95, 14, 0),
	OAM_ENTRY(-43, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 127, 14, 0),
	OAM_ENTRY(41, 0, OAM_DIMS_8x8, OAM_X_FLIP, 158, 14, 0),
	OAM_ENTRY(25, -11, OAM_DIMS_8x8, OAM_X_FLIP, 63, 14, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_X_FLIP, 95, 14, 0),
	OAM_ENTRY(35, -4, OAM_DIMS_8x8, OAM_X_FLIP, 127, 14, 0),
	OAM_ENTRY(-31, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 29, 14, 0),
	OAM_ENTRY(23, -12, OAM_DIMS_8x8, OAM_X_FLIP, 29, 14, 0),
};

static const u16 sOamFrame_5ff394[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-49, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 157, 14, 0),
	OAM_ENTRY(-43, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 126, 14, 0),
	OAM_ENTRY(-31, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 31, 14, 0),
	OAM_ENTRY(-33, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 14, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 95, 14, 0),
	OAM_ENTRY(41, 0, OAM_DIMS_8x8, OAM_X_FLIP, 157, 14, 0),
	OAM_ENTRY(35, -4, OAM_DIMS_8x8, OAM_X_FLIP, 126, 14, 0),
	OAM_ENTRY(23, -12, OAM_DIMS_8x8, OAM_X_FLIP, 31, 14, 0),
	OAM_ENTRY(25, -11, OAM_DIMS_8x8, OAM_X_FLIP, 63, 14, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_X_FLIP, 95, 14, 0),
};

static const u16 sOamFrame_5ff3d2[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-43, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 125, 14, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 94, 14, 0),
	OAM_ENTRY(-49, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 159, 14, 0),
	OAM_ENTRY(-31, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 31, 14, 0),
	OAM_ENTRY(-33, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 14, 0),
	OAM_ENTRY(35, -4, OAM_DIMS_8x8, OAM_X_FLIP, 125, 14, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_X_FLIP, 94, 14, 0),
	OAM_ENTRY(41, 0, OAM_DIMS_8x8, OAM_X_FLIP, 159, 14, 0),
	OAM_ENTRY(23, -12, OAM_DIMS_8x8, OAM_X_FLIP, 31, 14, 0),
	OAM_ENTRY(25, -11, OAM_DIMS_8x8, OAM_X_FLIP, 63, 14, 0),
};

static const u16 sOamFrame_5ff410[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 93, 14, 0),
	OAM_ENTRY(-33, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 62, 14, 0),
	OAM_ENTRY(-43, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 127, 14, 0),
	OAM_ENTRY(-49, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 159, 14, 0),
	OAM_ENTRY(-31, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 31, 14, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_X_FLIP, 93, 14, 0),
	OAM_ENTRY(25, -11, OAM_DIMS_8x8, OAM_X_FLIP, 62, 14, 0),
	OAM_ENTRY(35, -4, OAM_DIMS_8x8, OAM_X_FLIP, 127, 14, 0),
	OAM_ENTRY(41, 0, OAM_DIMS_8x8, OAM_X_FLIP, 159, 14, 0),
	OAM_ENTRY(23, -12, OAM_DIMS_8x8, OAM_X_FLIP, 31, 14, 0),
};

static const u16 sOamFrame_5ff44e[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-33, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 61, 14, 0),
	OAM_ENTRY(-31, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 30, 14, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 127, 14, 0),
	OAM_ENTRY(-43, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 127, 14, 0),
	OAM_ENTRY(-49, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 159, 14, 0),
	OAM_ENTRY(25, -11, OAM_DIMS_8x8, OAM_X_FLIP, 61, 14, 0),
	OAM_ENTRY(23, -12, OAM_DIMS_8x8, OAM_X_FLIP, 30, 14, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_X_FLIP, 127, 14, 0),
	OAM_ENTRY(35, -4, OAM_DIMS_8x8, OAM_X_FLIP, 127, 14, 0),
	OAM_ENTRY(41, 0, OAM_DIMS_8x8, OAM_X_FLIP, 159, 14, 0),
};

static const u16 sOamFrame_5ff48c[OAM_DATA_SIZE(10)] = {
	10,
	OAM_ENTRY(-31, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 29, 14, 0),
	OAM_ENTRY(-33, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 63, 14, 0),
	OAM_ENTRY(-38, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 95, 14, 0),
	OAM_ENTRY(-43, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 127, 14, 0),
	OAM_ENTRY(23, -12, OAM_DIMS_8x8, OAM_X_FLIP, 29, 14, 0),
	OAM_ENTRY(25, -11, OAM_DIMS_8x8, OAM_X_FLIP, 63, 14, 0),
	OAM_ENTRY(30, -8, OAM_DIMS_8x8, OAM_X_FLIP, 95, 14, 0),
	OAM_ENTRY(35, -4, OAM_DIMS_8x8, OAM_X_FLIP, 127, 14, 0),
	OAM_ENTRY(-49, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 159, 14, 0),
	OAM_ENTRY(41, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 159, 14, 0),
};

static const u16 sOamFrame_5ff4ca[OAM_DATA_SIZE(2)] = {
	2,
	OAM_ENTRY(-32, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 412, 8, 0),
	OAM_ENTRY(0, -16, OAM_DIMS_32x32, OAM_X_FLIP, 412, 8, 0),
};

const struct FrameData sIntroShipLandingOam_ExtendingLandingGear[11] = {
	[0] = {
		.pFrame = sOamFrame_5fea0a,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5fe978,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5fe8da,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5fe83c,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5fe792,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5fe6e8,
		.timer = 8
	},
	[6] = {
		.pFrame = sOamFrame_5fe63e,
		.timer = 8
	},
	[7] = {
		.pFrame = sOamFrame_5fe594,
		.timer = 8
	},
	[8] = {
		.pFrame = sOamFrame_5fe4ea,
		.timer = 8
	},
	[9] = {
		.pFrame = sOamFrame_5fe440,
		.timer = 100
	},
	[10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingOam_Idle[2] = {
	[0] = {
		.pFrame = sOamFrame_5fea0a,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingOam_Hovering[8] = {
	[0] = {
		.pFrame = sOamFrame_5fea0a,
		.timer = 12
	},
	[1] = {
		.pFrame = sOamFrame_5fea9c,
		.timer = 12
	},
	[2] = {
		.pFrame = sOamFrame_5feb2e,
		.timer = 12
	},
	[3] = {
		.pFrame = sOamFrame_5febc0,
		.timer = 12
	},
	[4] = {
		.pFrame = sOamFrame_5feb2e,
		.timer = 12
	},
	[5] = {
		.pFrame = sOamFrame_5fea9c,
		.timer = 12
	},
	[6] = {
		.pFrame = sOamFrame_5fea0a,
		.timer = 255
	},
	[7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingOam_ExtendedLandingGearHovering[5] = {
	[0] = {
		.pFrame = sOamFrame_5fe440,
		.timer = 8
	},
	[1] = {
		.pFrame = sOamFrame_5fec52,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5fecfc,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5fec52,
		.timer = 8
	},
	[4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingOam_ExtendedLandingGearIdle[2] = {
	[0] = {
		.pFrame = sOamFrame_5fe440,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingSmokeOam_1[6] = {
	[0] = {
		.pFrame = sOamFrame_5feda6,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5fee14,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5fee8e,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5fef2c,
		.timer = 4
	},
	[4] = {
		.pFrame = sOamFrame_5fefca,
		.timer = 4
	},
	[5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingSmokeOam_2[6] = {
	[0] = {
		.pFrame = sOamFrame_5ff0b2,
		.timer = 4
	},
	[1] = {
		.pFrame = sOamFrame_5ff120,
		.timer = 4
	},
	[2] = {
		.pFrame = sOamFrame_5ff1b2,
		.timer = 4
	},
	[3] = {
		.pFrame = sOamFrame_5ff244,
		.timer = 4
	},
	[4] = {
		.pFrame = sOamFrame_5ff2a6,
		.timer = 4
	},
	[5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingOam_Unused1[2] = {
	[0] = {
		.pFrame = sOamFrame_5ff2d8,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingOam_Unused2[2] = {
	[0] = {
		.pFrame = sOamFrame_5ff2e6,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingOam[2] = {
	[0] = {
		.pFrame = sOamFrame_5ff324,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingOam_RetractingLandingGear[15] = {
	[0] = {
		.pFrame = sOamFrame_5fe440,
		.timer = 50
	},
	[1] = {
		.pFrame = sOamFrame_5fe4ea,
		.timer = 8
	},
	[2] = {
		.pFrame = sOamFrame_5fe594,
		.timer = 8
	},
	[3] = {
		.pFrame = sOamFrame_5fe63e,
		.timer = 8
	},
	[4] = {
		.pFrame = sOamFrame_5fe6e8,
		.timer = 8
	},
	[5] = {
		.pFrame = sOamFrame_5fe792,
		.timer = 8
	},
	[6] = {
		.pFrame = sOamFrame_5fe83c,
		.timer = 8
	},
	[7] = {
		.pFrame = sOamFrame_5fe8da,
		.timer = 8
	},
	[8] = {
		.pFrame = sOamFrame_5fe978,
		.timer = 8
	},
	[9] = {
		.pFrame = sOamFrame_5fea0a,
		.timer = 50
	},
	[10] = {
		.pFrame = sOamFrame_5fea0a,
		.timer = 12
	},
	[11] = {
		.pFrame = sOamFrame_5fea9c,
		.timer = 12
	},
	[12] = {
		.pFrame = sOamFrame_5feb2e,
		.timer = 12
	},
	[13] = {
		.pFrame = sOamFrame_5febc0,
		.timer = 100
	},
	[14] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroBslLandingLightsOam[7] = {
	[0] = {
		.pFrame = sOamFrame_5ff356,
		.timer = 6
	},
	[1] = {
		.pFrame = sOamFrame_5ff394,
		.timer = 6
	},
	[2] = {
		.pFrame = sOamFrame_5ff3d2,
		.timer = 6
	},
	[3] = {
		.pFrame = sOamFrame_5ff410,
		.timer = 6
	},
	[4] = {
		.pFrame = sOamFrame_5ff44e,
		.timer = 6
	},
	[5] = {
		.pFrame = sOamFrame_5ff48c,
		.timer = 6
	},
	[6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sIntroShipLandingOam_FarAway[2] = {
	[0] = {
		.pFrame = sOamFrame_5ff4ca,
		.timer = 4
	},
	[1] = FRAME_DATA_TERMINATOR
};

const u16 sIntroLandingOnBslBgPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/landing_on_bsl_bg.pal");
const u16 sIntroPal_5ff908[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5ff908.pal");
const u16 sIntroPal_5ffb08[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/5ffb08.pal");
const u16 sIntroLandingOnBslObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/landing_on_bsl_obj.pal");

const u32 sIntroLandingOnBslSpaceTilemap[257] = INCBIN_U32("data/new_file_intro/landing_on_bsl_space.tm.lz");
const u32 sIntroLandingOnBslHangarTilemap[396] = INCBIN_U32("data/new_file_intro/landing_on_bsl_hangar.tm.lz");

const u32 sIntroSamusSittingGfx[4818] = INCBIN_U32("data/new_file_intro/samus_sitting.gfx.lz");
const u16 sIntroSamusSittingPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_sitting.pal");
const u32 sIntroSamusSittingTilemap[417] = INCBIN_U32("data/new_file_intro/samus_sitting.tm.lz");

const u32 sTitleScreenSpaceBackgroundGfx[3270] = INCBIN_U32("data/menus/title_screen/space_background.gfx.lz");

const u16 sPal_609020[8 * PAL_ROW] = INCBIN_U16("data/new_file_intro/609020.pal");
const u16 sTitleScreenSpaceBackgroundPal[8 * PAL_ROW] = INCBIN_U16("data/menus/title_screen/space_background.pal");

const u32 sTitleScreenSpaceBackgroundTilemap[418] = INCBIN_U32("data/menus/title_screen/space_background.tm.lz");

// OAM frames of the FrameData arrays below
const u16 sOamFrame_6098a8[] = INCBIN_U16("data/oam_frames/6098a8.bin");
const u16 sOamFrame_6098b0[] = INCBIN_U16("data/oam_frames/6098b0.bin");
const u16 sOamFrame_6098b8[] = INCBIN_U16("data/oam_frames/6098b8.bin");
const u16 sOamFrame_6098c0[] = INCBIN_U16("data/oam_frames/6098c0.bin");
const u16 sOamFrame_6098c8[] = INCBIN_U16("data/oam_frames/6098c8.bin");
const u16 sOamFrame_6098d0[] = INCBIN_U16("data/oam_frames/6098d0.bin");
const u16 sOamFrame_6098d8[] = INCBIN_U16("data/oam_frames/6098d8.bin");
const u16 sOamFrame_6098e0[] = INCBIN_U16("data/oam_frames/6098e0.bin");
const u16 sOamFrame_6098e8[] = INCBIN_U16("data/oam_frames/6098e8.bin");
const u16 sOamFrame_6098fe[] = INCBIN_U16("data/oam_frames/6098fe.bin");
const u16 sOamFrame_609944[] = INCBIN_U16("data/oam_frames/609944.bin");
const u16 sOamFrame_609952[] = INCBIN_U16("data/oam_frames/609952.bin");
const u16 sOamFrame_609978[] = INCBIN_U16("data/oam_frames/609978.bin");
const u16 sOamFrame_609992[] = INCBIN_U16("data/oam_frames/609992.bin");
const u16 sOamFrame_6099a0[] = INCBIN_U16("data/oam_frames/6099a0.bin");
const u16 sOamFrame_609da8[] = INCBIN_U16("data/oam_frames/609da8.bin");
const u16 sOamFrame_609daa[] = INCBIN_U16("data/oam_frames/609daa.bin");
const u16 sOamFrame_609db2[] = INCBIN_U16("data/oam_frames/609db2.bin");
const u16 sOamFrame_609dd2[] = INCBIN_U16("data/oam_frames/609dd2.bin");
const u16 sOamFrame_609e0a[] = INCBIN_U16("data/oam_frames/609e0a.bin");
const u16 sOamFrame_609e54[] = INCBIN_U16("data/oam_frames/609e54.bin");
const u16 sOamFrame_609ea4[] = INCBIN_U16("data/oam_frames/609ea4.bin");
const u16 sOamFrame_609efa[] = INCBIN_U16("data/oam_frames/609efa.bin");
const u16 sOamFrame_609f44[] = INCBIN_U16("data/oam_frames/609f44.bin");
const u16 sOamFrame_609f7c[] = INCBIN_U16("data/oam_frames/609f7c.bin");
const u16 sOamFrame_609f96[] = INCBIN_U16("data/oam_frames/609f96.bin");
const u16 sOamFrame_609faa[] = INCBIN_U16("data/oam_frames/609faa.bin");
const u16 sOamFrame_609fb2[] = INCBIN_U16("data/oam_frames/609fb2.bin");
const u16 sOamFrame_609fc0[] = INCBIN_U16("data/oam_frames/609fc0.bin");
const u16 sOamFrame_609fc8[] = INCBIN_U16("data/oam_frames/609fc8.bin");
const u16 sOamFrame_609fd6[] = INCBIN_U16("data/oam_frames/609fd6.bin");
const u16 sOamFrame_609fe4[] = INCBIN_U16("data/oam_frames/609fe4.bin");
const u16 sOamFrame_609fec[] = INCBIN_U16("data/oam_frames/609fec.bin");
const u16 sOamFrame_609ffa[] = INCBIN_U16("data/oam_frames/609ffa.bin");
const u16 sOamFrame_60a014[] = INCBIN_U16("data/oam_frames/60a014.bin");
const u16 sOamFrame_60a02e[] = INCBIN_U16("data/oam_frames/60a02e.bin");
const u16 sOamFrame_60a036[] = INCBIN_U16("data/oam_frames/60a036.bin");
const u16 sOamFrame_60a044[] = INCBIN_U16("data/oam_frames/60a044.bin");
const u16 sOamFrame_60a058[] = INCBIN_U16("data/oam_frames/60a058.bin");
const u16 sOamFrame_60a072[] = INCBIN_U16("data/oam_frames/60a072.bin");
const u16 sOamFrame_60a092[] = INCBIN_U16("data/oam_frames/60a092.bin");
const u16 sOamFrame_60a0b8[] = INCBIN_U16("data/oam_frames/60a0b8.bin");
const u16 sOamFrame_60a0e4[] = INCBIN_U16("data/oam_frames/60a0e4.bin");
const u16 sOamFrame_60a116[] = INCBIN_U16("data/oam_frames/60a116.bin");
const u16 sOamFrame_60a14e[] = INCBIN_U16("data/oam_frames/60a14e.bin");
const u16 sOamFrame_60a18c[] = INCBIN_U16("data/oam_frames/60a18c.bin");
const u16 sOamFrame_60a1d0[] = INCBIN_U16("data/oam_frames/60a1d0.bin");
const u16 sOamFrame_60a21a[] = INCBIN_U16("data/oam_frames/60a21a.bin");
const u16 sOamFrame_60a26a[] = INCBIN_U16("data/oam_frames/60a26a.bin");
const u16 sOamFrame_60a2c0[] = INCBIN_U16("data/oam_frames/60a2c0.bin");
const u16 sOamFrame_60a31c[] = INCBIN_U16("data/oam_frames/60a31c.bin");
const u16 sOamFrame_60a37e[] = INCBIN_U16("data/oam_frames/60a37e.bin");
const u16 sOamFrame_60a386[] = INCBIN_U16("data/oam_frames/60a386.bin");
const u16 sOamFrame_60a394[] = INCBIN_U16("data/oam_frames/60a394.bin");
const u16 sOamFrame_60a3a8[] = INCBIN_U16("data/oam_frames/60a3a8.bin");
const u16 sOamFrame_60a3c2[] = INCBIN_U16("data/oam_frames/60a3c2.bin");
const u16 sOamFrame_60a3e2[] = INCBIN_U16("data/oam_frames/60a3e2.bin");
const u16 sOamFrame_60a408[] = INCBIN_U16("data/oam_frames/60a408.bin");
const u16 sOamFrame_60a434[] = INCBIN_U16("data/oam_frames/60a434.bin");
const u16 sOamFrame_60a466[] = INCBIN_U16("data/oam_frames/60a466.bin");
const u16 sOamFrame_60a49e[] = INCBIN_U16("data/oam_frames/60a49e.bin");
const u16 sOamFrame_60a4dc[] = INCBIN_U16("data/oam_frames/60a4dc.bin");
const u16 sOamFrame_60a520[] = INCBIN_U16("data/oam_frames/60a520.bin");
const u16 sOamFrame_60a56a[] = INCBIN_U16("data/oam_frames/60a56a.bin");
const u16 sOamFrame_60a5ba[] = INCBIN_U16("data/oam_frames/60a5ba.bin");
const u16 sOamFrame_60a5c2[] = INCBIN_U16("data/oam_frames/60a5c2.bin");
const u16 sOamFrame_60a5d0[] = INCBIN_U16("data/oam_frames/60a5d0.bin");
const u16 sOamFrame_60a5e4[] = INCBIN_U16("data/oam_frames/60a5e4.bin");
const u16 sOamFrame_60a5fe[] = INCBIN_U16("data/oam_frames/60a5fe.bin");
const u16 sOamFrame_60a61e[] = INCBIN_U16("data/oam_frames/60a61e.bin");
const u16 sOamFrame_60a644[] = INCBIN_U16("data/oam_frames/60a644.bin");
const u16 sOamFrame_60a670[] = INCBIN_U16("data/oam_frames/60a670.bin");
const u16 sOamFrame_60a6a2[] = INCBIN_U16("data/oam_frames/60a6a2.bin");
const u16 sOamFrame_60a6aa[] = INCBIN_U16("data/oam_frames/60a6aa.bin");
const u16 sOamFrame_60a6b8[] = INCBIN_U16("data/oam_frames/60a6b8.bin");
const u16 sOamFrame_60a6cc[] = INCBIN_U16("data/oam_frames/60a6cc.bin");
const u16 sOamFrame_60a71c[] = INCBIN_U16("data/oam_frames/60a71c.bin");
const u16 sOamFrame_60a76c[] = INCBIN_U16("data/oam_frames/60a76c.bin");
const u16 sOamFrame_60a7bc[] = INCBIN_U16("data/oam_frames/60a7bc.bin");
const u16 sOamFrame_60a812[] = INCBIN_U16("data/oam_frames/60a812.bin");
const u16 sOamFrame_60a850[] = INCBIN_U16("data/oam_frames/60a850.bin");
const u16 sOamFrame_60a88e[] = INCBIN_U16("data/oam_frames/60a88e.bin");
const u16 sOamFrame_60a8cc[] = INCBIN_U16("data/oam_frames/60a8cc.bin");
const u16 sOamFrame_60a910[] = INCBIN_U16("data/oam_frames/60a910.bin");
const u16 sOamFrame_60a954[] = INCBIN_U16("data/oam_frames/60a954.bin");
const u16 sOamFrame_60a998[] = INCBIN_U16("data/oam_frames/60a998.bin");
const u16 sOamFrame_60a9d6[] = INCBIN_U16("data/oam_frames/60a9d6.bin");
const u16 sOamFrame_60aa14[] = INCBIN_U16("data/oam_frames/60aa14.bin");
const u16 sOamFrame_60aa6a[] = INCBIN_U16("data/oam_frames/60aa6a.bin");
const u16 sOamFrame_60aaba[] = INCBIN_U16("data/oam_frames/60aaba.bin");
const u16 sOamFrame_60ab04[] = INCBIN_U16("data/oam_frames/60ab04.bin");
const u16 sOamFrame_60ab36[] = INCBIN_U16("data/oam_frames/60ab36.bin");
const u16 sOamFrame_60ab5c[] = INCBIN_U16("data/oam_frames/60ab5c.bin");
const u16 sOamFrame_60aba2[] = INCBIN_U16("data/oam_frames/60aba2.bin");
const u16 sOamFrame_60abb6[] = INCBIN_U16("data/oam_frames/60abb6.bin");
const u16 sOamFrame_60abca[] = INCBIN_U16("data/oam_frames/60abca.bin");
const u16 sOamFrame_60abd8[] = INCBIN_U16("data/oam_frames/60abd8.bin");
const u16 sOamFrame_60abec[] = INCBIN_U16("data/oam_frames/60abec.bin");
const u16 sOamFrame_60abf4[] = INCBIN_U16("data/oam_frames/60abf4.bin");

// FrameData arrays of the intro space scenes
const struct FrameData sIntroDepthParticleOam_0[2] = {
    { sOamFrame_6098a8, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroDepthParticleOam_1[2] = {
    { sOamFrame_6098b0, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroDepthParticleOam_2[2] = {
    { sOamFrame_6098b8, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroDepthParticleOam_3[12] = {
    { sOamFrame_6098c0, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6098c8, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6098d0, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6098d8, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6098e0, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6098e8, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroSamusShipEnteringOam[7] = {
    { sOamFrame_60aba2, 1 },
    { sOamFrame_6098fe, 1 },
    { sOamFrame_60abb6, 1 },
    { sOamFrame_60aba2, 1 },
    { sOamFrame_6098fe, 1 },
    { sOamFrame_60abca, 1 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroSamusShipBackviewOam[5] = {
    { sOamFrame_60abd8, 1 },
    { sOamFrame_60abec, 1 },
    { sOamFrame_60abf4, 1 },
    { sOamFrame_60abec, 1 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroBslShipBackOam_3[2] = {
    { sOamFrame_609944, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroBslShipBackOam_2[2] = {
    { sOamFrame_609952, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroBslShipBackOam_1[2] = {
    { sOamFrame_609978, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroBslShipBackOam_0[4] = {
    { sOamFrame_609992, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6099a0, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroDriftingShipOam_End[57] = {
    { sOamFrame_609daa, 4 },
    { sOamFrame_609db2, 4 },
    { sOamFrame_609dd2, 4 },
    { sOamFrame_609e0a, 4 },
    { sOamFrame_609e54, 4 },
    { sOamFrame_609ea4, 4 },
    { sOamFrame_609efa, 6 },
    { sOamFrame_609f44, 7 },
    { sOamFrame_609f7c, 8 },
    { sOamFrame_609f96, 9 },
    { sOamFrame_609faa, 10 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_609fb2, 1 },
    { sOamFrame_609fc0, 1 },
    { sOamFrame_609fc8, 1 },
    { sOamFrame_609fc0, 1 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_609fd6, 1 },
    { sOamFrame_609fe4, 1 },
    { sOamFrame_609fec, 1 },
    { sOamFrame_609fe4, 1 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_609ffa, 140 },
    { sOamFrame_609da8, 140 },
    { sOamFrame_60a014, 180 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_60a02e, 4 },
    { sOamFrame_60a036, 4 },
    { sOamFrame_60a044, 4 },
    { sOamFrame_60a058, 4 },
    { sOamFrame_60a072, 4 },
    { sOamFrame_60a092, 4 },
    { sOamFrame_60a0b8, 4 },
    { sOamFrame_60a0e4, 4 },
    { sOamFrame_60a116, 4 },
    { sOamFrame_60a14e, 4 },
    { sOamFrame_60a18c, 4 },
    { sOamFrame_60a1d0, 4 },
    { sOamFrame_60a21a, 4 },
    { sOamFrame_60a26a, 4 },
    { sOamFrame_60a2c0, 4 },
    { sOamFrame_60a31c, 100 },
    { sOamFrame_609da8, 100 },
    { sOamFrame_60a37e, 6 },
    { sOamFrame_60a386, 6 },
    { sOamFrame_60a394, 6 },
    { sOamFrame_60a3a8, 6 },
    { sOamFrame_60a3c2, 6 },
    { sOamFrame_60a3e2, 6 },
    { sOamFrame_60a408, 6 },
    { sOamFrame_60a434, 6 },
    { sOamFrame_60a466, 6 },
    { sOamFrame_60a49e, 6 },
    { sOamFrame_60a4dc, 6 },
    { sOamFrame_60a520, 6 },
    { sOamFrame_60a56a, 120 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroSplashTextOam[71] = {
    { sOamFrame_60a02e, 4 },
    { sOamFrame_60a036, 4 },
    { sOamFrame_60a044, 4 },
    { sOamFrame_60a058, 4 },
    { sOamFrame_60a072, 4 },
    { sOamFrame_60a092, 4 },
    { sOamFrame_60a0b8, 4 },
    { sOamFrame_60a0e4, 4 },
    { sOamFrame_60a116, 4 },
    { sOamFrame_60a14e, 4 },
    { sOamFrame_60a18c, 4 },
    { sOamFrame_60a1d0, 4 },
    { sOamFrame_60a21a, 4 },
    { sOamFrame_60a26a, 4 },
    { sOamFrame_60a2c0, 4 },
    { sOamFrame_60a31c, 100 },
    { sOamFrame_609da8, 100 },
    { sOamFrame_60a5ba, 6 },
    { sOamFrame_60a5c2, 6 },
    { sOamFrame_60a5d0, 6 },
    { sOamFrame_60a5e4, 6 },
    { sOamFrame_60a5fe, 6 },
    { sOamFrame_60a61e, 6 },
    { sOamFrame_60a644, 6 },
    { sOamFrame_60a670, 120 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_60a6a2, 3 },
    { sOamFrame_60a6aa, 3 },
    { sOamFrame_60a6b8, 3 },
    { sOamFrame_60a6cc, 3 },
    { sOamFrame_60a71c, 3 },
    { sOamFrame_60a76c, 3 },
    { sOamFrame_60a7bc, 3 },
    { sOamFrame_60a812, 3 },
    { sOamFrame_60a850, 3 },
    { sOamFrame_60a88e, 3 },
    { sOamFrame_60a8cc, 3 },
    { sOamFrame_60a910, 3 },
    { sOamFrame_60a954, 3 },
    { sOamFrame_60a998, 3 },
    { sOamFrame_60a9d6, 3 },
    { sOamFrame_60aa14, 3 },
    { sOamFrame_60aa6a, 3 },
    { sOamFrame_60aaba, 3 },
    { sOamFrame_60ab04, 3 },
    { sOamFrame_60ab36, 3 },
    { sOamFrame_60ab5c, 3 },
    { sOamFrame_609da8, 200 },
    { sOamFrame_60a6a2, 3 },
    { sOamFrame_60a6aa, 3 },
    { sOamFrame_60a6b8, 3 },
    { sOamFrame_60a6cc, 3 },
    { sOamFrame_60a71c, 3 },
    { sOamFrame_60a76c, 3 },
    { sOamFrame_60a7bc, 3 },
    { sOamFrame_60a812, 3 },
    { sOamFrame_60a850, 3 },
    { sOamFrame_60a88e, 3 },
    { sOamFrame_60a8cc, 3 },
    { sOamFrame_60a910, 3 },
    { sOamFrame_60a954, 3 },
    { sOamFrame_60a998, 3 },
    { sOamFrame_60a9d6, 3 },
    { sOamFrame_60aa14, 3 },
    { sOamFrame_60aa6a, 3 },
    { sOamFrame_60aaba, 3 },
    { sOamFrame_60ab04, 3 },
    { sOamFrame_60ab36, 3 },
    { sOamFrame_60ab5c, 3 },
    { sOamFrame_609da8, 126 },
    FRAME_DATA_TERMINATOR
};

const u8 sIntroSpaceTilemap[1320] = INCBIN_U8("data/new_file_intro/space_bg.tm.lz");
const u8 sIntroBslTilemap[1586] = INCBIN_U8("data/new_file_intro/bsl_bg.tm.lz");

static const u8 padding[2] = {0, 0};

const u32 sIntroBslSpaceBgGfx[4421] = INCBIN_U32("data/new_file_intro/bsl_space_bg.gfx.lz");

// OBJ graphics of the drifting out, space view and flying view scenes
const u32 sIntroSpaceObjGfx[2852] = INCBIN_U32("data/new_file_intro/space_obj.gfx.lz");

const u16 sIntroBslSpaceBgPal[8 * PAL_ROW] = INCBIN_U16("data/new_file_intro/bsl_space_bg.pal");
const u16 sPal_612f48[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/612f48.pal");

const u32 sNextPageArrowGfx[8] = INCBIN_U32("data/new_file_intro/next_page_arrow.gfx");

static const u16 sOamFrame_613168[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 1023, 15, 0),
};

static const u16 sOamFrame_613170[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 1023, 15, 0),
};

static const u16 sOamFrame_613178[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 1023, 15, 0),
};

const struct FrameData sIntroNextPageArrowOam[5] = {
    [0] = {
            .pFrame = sOamFrame_613168,
            .timer = 8
    },
    [1] = {
            .pFrame = sOamFrame_613170,
            .timer = 8
    },
    [2] = {
            .pFrame = sOamFrame_613178,
            .timer = 8
    },
    [3] = {
            .pFrame = sOamFrame_613170,
            .timer = 8
    },
    [4] = FRAME_DATA_TERMINATOR
};

const u16 sNextPageArrowPal[1 * PAL_ROW] = INCBIN_U16("data/new_file_intro/next_page_arrow.pal");

// Ending cutscenes and the died on SR388 (BSL crashing) cutscene
const u32 sEndingAdamConversationBgGfx[1992] = INCBIN_U32("data/ending/adam_conversation_bg.gfx.lz");
const u32 sEndingInShipObjGfx[3439] = INCBIN_U32("data/ending/in_ship_obj.gfx.lz");
const u32 sEndingMonologueBgGfx[3198] = INCBIN_U32("data/ending/monologue_bg.gfx.lz");
const u32 sEndingAnimalsBg3Gfx[6083] = INCBIN_U32("data/ending/animals_bg3.gfx.lz");
const u32 sEndingAnimalsBg2Gfx[2131] = INCBIN_U32("data/ending/animals_bg2.gfx.lz");
const u32 sBslCrashingObjGfx[2961] = INCBIN_U32("data/ending/bsl_crashing_obj.gfx.lz");
const u32 sEndingShipFrontViewBgGfx[5039] = INCBIN_U32("data/ending/ship_front_view_bg.gfx.lz");
// Followed by the OAM frames of the ending FrameData arrays below
const u32 sBslCrashingBgGfx[4683] = INCBIN_U32("data/ending/bsl_crashing_bg.gfx.lz");
const u16 sOamFrame_62ff20[13] = INCBIN_U16("data/oam_frames/62ff20.bin");
const u16 sOamFrame_62ff3a[13] = INCBIN_U16("data/oam_frames/62ff3a.bin");
const u16 sOamFrame_62ff54[22] = INCBIN_U16("data/oam_frames/62ff54.bin");
const u16 sOamFrame_62ff80[19] = INCBIN_U16("data/oam_frames/62ff80.bin");
const u16 sOamFrame_62ffa6[19] = INCBIN_U16("data/oam_frames/62ffa6.bin");
const u16 sOamFrame_62ffcc[34] = INCBIN_U16("data/oam_frames/62ffcc.bin");
const u16 sOamFrame_630010[34] = INCBIN_U16("data/oam_frames/630010.bin");
const u16 sOamFrame_630054[34] = INCBIN_U16("data/oam_frames/630054.bin");
const u16 sOamFrame_630098[43] = INCBIN_U16("data/oam_frames/630098.bin");
const u16 sOamFrame_6300ee[28] = INCBIN_U16("data/oam_frames/6300ee.bin");
const u16 sOamFrame_630126[37] = INCBIN_U16("data/oam_frames/630126.bin");
const u16 sOamFrame_630170[37] = INCBIN_U16("data/oam_frames/630170.bin");
const u16 sOamFrame_6301ba[43] = INCBIN_U16("data/oam_frames/6301ba.bin");
const u16 sOamFrame_630210[40] = INCBIN_U16("data/oam_frames/630210.bin");
const u16 sOamFrame_630260[52] = INCBIN_U16("data/oam_frames/630260.bin");
const u16 sOamFrame_6302c8[52] = INCBIN_U16("data/oam_frames/6302c8.bin");
const u16 sOamFrame_630330[58] = INCBIN_U16("data/oam_frames/630330.bin");
const u16 sOamFrame_6303a4[55] = INCBIN_U16("data/oam_frames/6303a4.bin");
const u16 sOamFrame_630412[61] = INCBIN_U16("data/oam_frames/630412.bin");
const u16 sOamFrame_63048c[61] = INCBIN_U16("data/oam_frames/63048c.bin");
const u16 sOamFrame_630506[67] = INCBIN_U16("data/oam_frames/630506.bin");
const u16 sOamFrame_63058c[19] = INCBIN_U16("data/oam_frames/63058c.bin");
const u16 sOamFrame_6305b2[31] = INCBIN_U16("data/oam_frames/6305b2.bin");
const u16 sOamFrame_6305f0[34] = INCBIN_U16("data/oam_frames/6305f0.bin");
const u16 sOamFrame_630634[28] = INCBIN_U16("data/oam_frames/630634.bin");
const u16 sOamFrame_63066c[49] = INCBIN_U16("data/oam_frames/63066c.bin");
const u16 sOamFrame_6306ce[49] = INCBIN_U16("data/oam_frames/6306ce.bin");
const u16 sOamFrame_630730[52] = INCBIN_U16("data/oam_frames/630730.bin");
const u16 sOamFrame_630798[58] = INCBIN_U16("data/oam_frames/630798.bin");
const u16 sOamFrame_63080c[61] = INCBIN_U16("data/oam_frames/63080c.bin");
const u16 sOamFrame_630886[67] = INCBIN_U16("data/oam_frames/630886.bin");
const u16 sOamFrame_63090c[70] = INCBIN_U16("data/oam_frames/63090c.bin");
const u16 sOamFrame_630998[28] = INCBIN_U16("data/oam_frames/630998.bin");
const u16 sOamFrame_6309d0[10] = INCBIN_U16("data/oam_frames/6309d0.bin");
const u16 sOamFrame_6309e4[10] = INCBIN_U16("data/oam_frames/6309e4.bin");
const u16 sOamFrame_6309f8[10] = INCBIN_U16("data/oam_frames/6309f8.bin");
const u16 sOamFrame_630a0c[10] = INCBIN_U16("data/oam_frames/630a0c.bin");
const u16 sOamFrame_630a20[7] = INCBIN_U16("data/oam_frames/630a20.bin");
const u16 sOamFrame_630a2e[4] = INCBIN_U16("data/oam_frames/630a2e.bin");
const u16 sOamFrame_630a36[4] = INCBIN_U16("data/oam_frames/630a36.bin");
const u16 sOamFrame_630a3e[4] = INCBIN_U16("data/oam_frames/630a3e.bin");
const u16 sOamFrame_630a46[4] = INCBIN_U16("data/oam_frames/630a46.bin");
const u16 sOamFrame_630a4e[10] = INCBIN_U16("data/oam_frames/630a4e.bin");
const u16 sOamFrame_630a62[16] = INCBIN_U16("data/oam_frames/630a62.bin");
const u16 sOamFrame_630a82[22] = INCBIN_U16("data/oam_frames/630a82.bin");
const u16 sOamFrame_630aae[55] = INCBIN_U16("data/oam_frames/630aae.bin");
const u16 sOamFrame_630b1c[55] = INCBIN_U16("data/oam_frames/630b1c.bin");
const u16 sOamFrame_630b8a[61] = INCBIN_U16("data/oam_frames/630b8a.bin");
const u16 sOamFrame_630c04[61] = INCBIN_U16("data/oam_frames/630c04.bin");
const u16 sOamFrame_630c7e[4] = INCBIN_U16("data/oam_frames/630c7e.bin");
const u16 sOamFrame_630c86[4] = INCBIN_U16("data/oam_frames/630c86.bin");
const u16 sOamFrame_630c8e[7] = INCBIN_U16("data/oam_frames/630c8e.bin");
const u16 sOamFrame_630c9c[10] = INCBIN_U16("data/oam_frames/630c9c.bin");
const u16 sOamFrame_630cb0[16] = INCBIN_U16("data/oam_frames/630cb0.bin");
const u16 sOamFrame_630cd0[22] = INCBIN_U16("data/oam_frames/630cd0.bin");
const u16 sOamFrame_630cfc[55] = INCBIN_U16("data/oam_frames/630cfc.bin");
const u16 sOamFrame_630d6a[55] = INCBIN_U16("data/oam_frames/630d6a.bin");
const u16 sOamFrame_630dd8[61] = INCBIN_U16("data/oam_frames/630dd8.bin");
const u16 sOamFrame_630e52[67] = INCBIN_U16("data/oam_frames/630e52.bin");
const u16 sOamFrame_630ed8[22] = INCBIN_U16("data/oam_frames/630ed8.bin");
const u16 sOamFrame_630f04[22] = INCBIN_U16("data/oam_frames/630f04.bin");
const u16 sOamFrame_630f30[43] = INCBIN_U16("data/oam_frames/630f30.bin");
const u16 sOamFrame_630f86[43] = INCBIN_U16("data/oam_frames/630f86.bin");
const u16 sOamFrame_630fdc[22] = INCBIN_U16("data/oam_frames/630fdc.bin");
const u16 sOamFrame_631008[22] = INCBIN_U16("data/oam_frames/631008.bin");
const u16 sOamFrame_631034[43] = INCBIN_U16("data/oam_frames/631034.bin");
const u16 sOamFrame_63108a[43] = INCBIN_U16("data/oam_frames/63108a.bin");
const u16 sOamFrame_6310e0[34] = INCBIN_U16("data/oam_frames/6310e0.bin");
const u16 sOamFrame_631124[37] = INCBIN_U16("data/oam_frames/631124.bin");
const u16 sOamFrame_63116e[34] = INCBIN_U16("data/oam_frames/63116e.bin");
const u16 sOamFrame_6311b2[37] = INCBIN_U16("data/oam_frames/6311b2.bin");
const u16 sOamFrame_6311fc[4] = INCBIN_U16("data/oam_frames/6311fc.bin");
const u16 sOamFrame_631204[4] = INCBIN_U16("data/oam_frames/631204.bin");
const u16 sOamFrame_63120c[4] = INCBIN_U16("data/oam_frames/63120c.bin");
const u16 sOamFrame_631214[7] = INCBIN_U16("data/oam_frames/631214.bin");
const u16 sOamFrame_631222[22] = INCBIN_U16("data/oam_frames/631222.bin");
const u16 sOamFrame_63124e[31] = INCBIN_U16("data/oam_frames/63124e.bin");
const u16 sOamFrame_63128c[34] = INCBIN_U16("data/oam_frames/63128c.bin");
const u16 sOamFrame_6312d0[4] = INCBIN_U16("data/oam_frames/6312d0.bin");
const u16 sOamFrame_6312d8[4] = INCBIN_U16("data/oam_frames/6312d8.bin");
const u16 sOamFrame_6312e0[4] = INCBIN_U16("data/oam_frames/6312e0.bin");
const u16 sOamFrame_6312e8[7] = INCBIN_U16("data/oam_frames/6312e8.bin");
const u16 sOamFrame_6312f6[22] = INCBIN_U16("data/oam_frames/6312f6.bin");
const u16 sOamFrame_631322[31] = INCBIN_U16("data/oam_frames/631322.bin");
const u16 sOamFrame_631360[34] = INCBIN_U16("data/oam_frames/631360.bin");
const u16 sOamFrame_6313a4[10] = INCBIN_U16("data/oam_frames/6313a4.bin");
const u16 sOamFrame_6313b8[10] = INCBIN_U16("data/oam_frames/6313b8.bin");
const u16 sOamFrame_6313cc[10] = INCBIN_U16("data/oam_frames/6313cc.bin");
const u16 sOamFrame_6313e0[49] = INCBIN_U16("data/oam_frames/6313e0.bin");
const u16 sOamFrame_631442[49] = INCBIN_U16("data/oam_frames/631442.bin");
const u16 sOamFrame_6314a4[49] = INCBIN_U16("data/oam_frames/6314a4.bin");
const u16 sOamFrame_631506[49] = INCBIN_U16("data/oam_frames/631506.bin");
const u16 sOamFrame_631568[49] = INCBIN_U16("data/oam_frames/631568.bin");
const u16 sOamFrame_6315ca[49] = INCBIN_U16("data/oam_frames/6315ca.bin");
const u16 sOamFrame_63162c[49] = INCBIN_U16("data/oam_frames/63162c.bin");
const u16 sOamFrame_63168e[49] = INCBIN_U16("data/oam_frames/63168e.bin");
const u16 sOamFrame_6316f0[55] = INCBIN_U16("data/oam_frames/6316f0.bin");
const u16 sOamFrame_63175e[49] = INCBIN_U16("data/oam_frames/63175e.bin");
const u16 sOamFrame_6317c0[49] = INCBIN_U16("data/oam_frames/6317c0.bin");
const u16 sOamFrame_631822[49] = INCBIN_U16("data/oam_frames/631822.bin");
const u16 sOamFrame_631884[49] = INCBIN_U16("data/oam_frames/631884.bin");
const u16 sOamFrame_6318e6[49] = INCBIN_U16("data/oam_frames/6318e6.bin");
const u16 sOamFrame_631948[49] = INCBIN_U16("data/oam_frames/631948.bin");
const u16 sOamFrame_6319aa[49] = INCBIN_U16("data/oam_frames/6319aa.bin");
const u16 sOamFrame_631a0c[49] = INCBIN_U16("data/oam_frames/631a0c.bin");
const u16 sOamFrame_631a6e[55] = INCBIN_U16("data/oam_frames/631a6e.bin");
const u16 sOamFrame_631adc[49] = INCBIN_U16("data/oam_frames/631adc.bin");
const u16 sOamFrame_631b3e[49] = INCBIN_U16("data/oam_frames/631b3e.bin");
const u16 sOamFrame_631ba0[49] = INCBIN_U16("data/oam_frames/631ba0.bin");
const u16 sOamFrame_631c02[49] = INCBIN_U16("data/oam_frames/631c02.bin");
const u16 sOamFrame_631c64[49] = INCBIN_U16("data/oam_frames/631c64.bin");
const u16 sOamFrame_631cc6[49] = INCBIN_U16("data/oam_frames/631cc6.bin");
const u16 sOamFrame_631d28[49] = INCBIN_U16("data/oam_frames/631d28.bin");
const u16 sOamFrame_631d8a[49] = INCBIN_U16("data/oam_frames/631d8a.bin");
const u16 sOamFrame_631dec[55] = INCBIN_U16("data/oam_frames/631dec.bin");
const u16 sOamFrame_631e5a[49] = INCBIN_U16("data/oam_frames/631e5a.bin");
const u16 sOamFrame_631ebc[49] = INCBIN_U16("data/oam_frames/631ebc.bin");
const u16 sOamFrame_631f1e[49] = INCBIN_U16("data/oam_frames/631f1e.bin");
const u16 sOamFrame_631f80[49] = INCBIN_U16("data/oam_frames/631f80.bin");
const u16 sOamFrame_631fe2[49] = INCBIN_U16("data/oam_frames/631fe2.bin");
const u16 sOamFrame_632044[49] = INCBIN_U16("data/oam_frames/632044.bin");
const u16 sOamFrame_6320a6[49] = INCBIN_U16("data/oam_frames/6320a6.bin");
const u16 sOamFrame_632108[49] = INCBIN_U16("data/oam_frames/632108.bin");
const u16 sOamFrame_63216a[55] = INCBIN_U16("data/oam_frames/63216a.bin");
const u16 sOamFrame_6321d8[49] = INCBIN_U16("data/oam_frames/6321d8.bin");
const u16 sOamFrame_63223a[49] = INCBIN_U16("data/oam_frames/63223a.bin");
const u16 sOamFrame_63229c[49] = INCBIN_U16("data/oam_frames/63229c.bin");
const u16 sOamFrame_6322fe[49] = INCBIN_U16("data/oam_frames/6322fe.bin");
const u16 sOamFrame_632360[49] = INCBIN_U16("data/oam_frames/632360.bin");
const u16 sOamFrame_6323c2[49] = INCBIN_U16("data/oam_frames/6323c2.bin");
const u16 sOamFrame_632424[49] = INCBIN_U16("data/oam_frames/632424.bin");
const u16 sOamFrame_632486[49] = INCBIN_U16("data/oam_frames/632486.bin");
const u16 sOamFrame_6324e8[55] = INCBIN_U16("data/oam_frames/6324e8.bin");
const u16 sOamFrame_632556[49] = INCBIN_U16("data/oam_frames/632556.bin");
const u16 sOamFrame_6325b8[49] = INCBIN_U16("data/oam_frames/6325b8.bin");
const u16 sOamFrame_63261a[49] = INCBIN_U16("data/oam_frames/63261a.bin");
const u16 sOamFrame_63267c[49] = INCBIN_U16("data/oam_frames/63267c.bin");
const u16 sOamFrame_6326de[49] = INCBIN_U16("data/oam_frames/6326de.bin");
const u16 sOamFrame_632740[49] = INCBIN_U16("data/oam_frames/632740.bin");
const u16 sOamFrame_6327a2[49] = INCBIN_U16("data/oam_frames/6327a2.bin");
const u16 sOamFrame_632804[49] = INCBIN_U16("data/oam_frames/632804.bin");
const u16 sOamFrame_632866[55] = INCBIN_U16("data/oam_frames/632866.bin");
const u16 sOamFrame_6328d4[49] = INCBIN_U16("data/oam_frames/6328d4.bin");
const u16 sOamFrame_632936[49] = INCBIN_U16("data/oam_frames/632936.bin");
const u16 sOamFrame_632998[49] = INCBIN_U16("data/oam_frames/632998.bin");
const u16 sOamFrame_6329fa[49] = INCBIN_U16("data/oam_frames/6329fa.bin");
const u16 sOamFrame_632a5c[49] = INCBIN_U16("data/oam_frames/632a5c.bin");
const u16 sOamFrame_632abe[49] = INCBIN_U16("data/oam_frames/632abe.bin");
const u16 sOamFrame_632b20[49] = INCBIN_U16("data/oam_frames/632b20.bin");
const u16 sOamFrame_632b82[101] = INCBIN_U16("data/oam_frames/632b82.bin");
const u16 sOamFrame_632c4c[4] = INCBIN_U16("data/oam_frames/632c4c.bin");
const u16 sOamFrame_632c54[4] = INCBIN_U16("data/oam_frames/632c54.bin");
const u16 sOamFrame_632c5c[4] = INCBIN_U16("data/oam_frames/632c5c.bin");
const u16 sOamFrame_632c64[4] = INCBIN_U16("data/oam_frames/632c64.bin");
const u16 sOamFrame_632c6c[4] = INCBIN_U16("data/oam_frames/632c6c.bin");
const u16 sOamFrame_632c74[4] = INCBIN_U16("data/oam_frames/632c74.bin");
const u16 sOamFrame_632c7c[4] = INCBIN_U16("data/oam_frames/632c7c.bin");
const u16 sOamFrame_632c84[4] = INCBIN_U16("data/oam_frames/632c84.bin");
const u16 sOamFrame_632c8c[4] = INCBIN_U16("data/oam_frames/632c8c.bin");
const u16 sOamFrame_632c94[4] = INCBIN_U16("data/oam_frames/632c94.bin");
const u16 sOamFrame_632c9c[4] = INCBIN_U16("data/oam_frames/632c9c.bin");
const u16 sOamFrame_632ca4[4] = INCBIN_U16("data/oam_frames/632ca4.bin");
const u16 sOamFrame_632cac[4] = INCBIN_U16("data/oam_frames/632cac.bin");
const u16 sOamFrame_632cb4[4] = INCBIN_U16("data/oam_frames/632cb4.bin");
const u16 sOamFrame_632cbc[16] = INCBIN_U16("data/oam_frames/632cbc.bin");
const u16 sOamFrame_632cdc[16] = INCBIN_U16("data/oam_frames/632cdc.bin");
const u16 sOamFrame_632cfc[19] = INCBIN_U16("data/oam_frames/632cfc.bin");
const u16 sOamFrame_632d22[16] = INCBIN_U16("data/oam_frames/632d22.bin");
const u16 sOamFrame_632d42[19] = INCBIN_U16("data/oam_frames/632d42.bin");
const u16 sOamFrame_632d68[19] = INCBIN_U16("data/oam_frames/632d68.bin");
const u16 sOamFrame_632d8e[22] = INCBIN_U16("data/oam_frames/632d8e.bin");
const u16 sOamFrame_632dba[19] = INCBIN_U16("data/oam_frames/632dba.bin");
const u16 sOamFrame_632de0[22] = INCBIN_U16("data/oam_frames/632de0.bin");
const u16 sOamFrame_632e0c[31] = INCBIN_U16("data/oam_frames/632e0c.bin");
const u16 sOamFrame_632e4a[34] = INCBIN_U16("data/oam_frames/632e4a.bin");
const u16 sOamFrame_632e8e[31] = INCBIN_U16("data/oam_frames/632e8e.bin");
const u16 sOamFrame_632ecc[34] = INCBIN_U16("data/oam_frames/632ecc.bin");
const u16 sOamFrame_632f10[34] = INCBIN_U16("data/oam_frames/632f10.bin");
const u16 sOamFrame_632f54[43] = INCBIN_U16("data/oam_frames/632f54.bin");
const u16 sOamFrame_632faa[7] = INCBIN_U16("data/oam_frames/632faa.bin");
const u16 sOamFrame_632fb8[10] = INCBIN_U16("data/oam_frames/632fb8.bin");
const u16 sOamFrame_632fcc[10] = INCBIN_U16("data/oam_frames/632fcc.bin");
const u16 sOamFrame_632fe0[10] = INCBIN_U16("data/oam_frames/632fe0.bin");
const u16 sOamFrame_632ff4[10] = INCBIN_U16("data/oam_frames/632ff4.bin");
const u16 sOamFrame_633008[10] = INCBIN_U16("data/oam_frames/633008.bin");
const u16 sOamFrame_63301c[10] = INCBIN_U16("data/oam_frames/63301c.bin");
const u16 sOamFrame_633030[4] = INCBIN_U16("data/oam_frames/633030.bin");
const u16 sOamFrame_633038[4] = INCBIN_U16("data/oam_frames/633038.bin");
const u16 sOamFrame_633040[4] = INCBIN_U16("data/oam_frames/633040.bin");
const u16 sOamFrame_633048[4] = INCBIN_U16("data/oam_frames/633048.bin");
const u16 sOamFrame_633050[4] = INCBIN_U16("data/oam_frames/633050.bin");
const u16 sOamFrame_633058[4] = INCBIN_U16("data/oam_frames/633058.bin");
const u16 sOamFrame_633060[4] = INCBIN_U16("data/oam_frames/633060.bin");
const u16 sOamFrame_633068[4] = INCBIN_U16("data/oam_frames/633068.bin");
const u16 sOamFrame_633070[4] = INCBIN_U16("data/oam_frames/633070.bin");
const u16 sOamFrame_633078[4] = INCBIN_U16("data/oam_frames/633078.bin");
const u16 sOamFrame_633080[4] = INCBIN_U16("data/oam_frames/633080.bin");
const u16 sOamFrame_633088[4] = INCBIN_U16("data/oam_frames/633088.bin");
const u16 sOamFrame_633090[127] = INCBIN_U16("data/oam_frames/633090.bin");
const u16 sOamFrame_63318e[43] = INCBIN_U16("data/oam_frames/63318e.bin");
const u16 sOamFrame_6331e4[4] = INCBIN_U16("data/oam_frames/6331e4.bin");

// FrameData arrays of the ending dialogue, the ending and the died on SR388 cutscene
const struct FrameData sEndingDialogueType5Oam_Opening[11] = {
    { sOamFrame_630a2e, 30 },
    { sOamFrame_62ff20, 1 },
    { sOamFrame_62ff3a, 1 },
    { sOamFrame_62ff54, 1 },
    { sOamFrame_62ff80, 2 },
    { sOamFrame_62ffa6, 2 },
    { sOamFrame_62ffcc, 2 },
    { sOamFrame_630010, 2 },
    { sOamFrame_630054, 2 },
    { sOamFrame_630098, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingDialogueType5Oam_Closing[10] = {
    { sOamFrame_630098, 2 },
    { sOamFrame_630054, 2 },
    { sOamFrame_630010, 2 },
    { sOamFrame_62ffcc, 2 },
    { sOamFrame_62ffa6, 2 },
    { sOamFrame_62ff80, 1 },
    { sOamFrame_62ff54, 1 },
    { sOamFrame_62ff3a, 1 },
    { sOamFrame_62ff20, 1 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingAdamPanel0Oam[13] = {
    { sOamFrame_6300ee, 1 },
    { sOamFrame_630126, 1 },
    { sOamFrame_630170, 1 },
    { sOamFrame_6301ba, 1 },
    { sOamFrame_630210, 1 },
    { sOamFrame_630260, 1 },
    { sOamFrame_6302c8, 1 },
    { sOamFrame_630330, 2 },
    { sOamFrame_6303a4, 2 },
    { sOamFrame_630412, 2 },
    { sOamFrame_63048c, 2 },
    { sOamFrame_630506, 50 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingAdamPanel0Oam_Closing[13] = {
    { sOamFrame_630506, 2 },
    { sOamFrame_63048c, 2 },
    { sOamFrame_630412, 2 },
    { sOamFrame_6303a4, 2 },
    { sOamFrame_630330, 1 },
    { sOamFrame_6302c8, 1 },
    { sOamFrame_630260, 1 },
    { sOamFrame_630210, 1 },
    { sOamFrame_6301ba, 1 },
    { sOamFrame_630170, 1 },
    { sOamFrame_630126, 1 },
    { sOamFrame_6300ee, 50 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingAdamPanel1Oam[13] = {
    { sOamFrame_63058c, 1 },
    { sOamFrame_6305b2, 1 },
    { sOamFrame_6305f0, 1 },
    { sOamFrame_630634, 1 },
    { sOamFrame_63066c, 1 },
    { sOamFrame_6306ce, 1 },
    { sOamFrame_630730, 1 },
    { sOamFrame_630798, 2 },
    { sOamFrame_63080c, 2 },
    { sOamFrame_630886, 2 },
    { sOamFrame_63090c, 2 },
    { sOamFrame_630998, 50 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingAdamPanel1Oam_Closing[13] = {
    { sOamFrame_630998, 2 },
    { sOamFrame_63090c, 2 },
    { sOamFrame_630886, 2 },
    { sOamFrame_63080c, 2 },
    { sOamFrame_630798, 1 },
    { sOamFrame_630730, 1 },
    { sOamFrame_6306ce, 1 },
    { sOamFrame_63066c, 1 },
    { sOamFrame_630634, 1 },
    { sOamFrame_6305f0, 1 },
    { sOamFrame_6305b2, 1 },
    { sOamFrame_63058c, 255 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingAdamIconOam_Opening[5] = {
    { sOamFrame_6309d0, 8 },
    { sOamFrame_6309e4, 8 },
    { sOamFrame_6309f8, 8 },
    { sOamFrame_630a0c, 255 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingAdamIconOam_Closing[137] = {
    { sOamFrame_630a0c, 8 },
    { sOamFrame_6309f8, 8 },
    { sOamFrame_6309e4, 8 },
    { sOamFrame_6309d0, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_630a20, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_630a36, 2 },
    { sOamFrame_630a3e, 2 },
    { sOamFrame_630a46, 2 },
    { sOamFrame_630a4e, 2 },
    { sOamFrame_630a62, 2 },
    { sOamFrame_630a82, 2 },
    { sOamFrame_630aae, 2 },
    { sOamFrame_630b1c, 2 },
    { sOamFrame_630b8a, 2 },
    { sOamFrame_630c04, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_630c04, 2 },
    { sOamFrame_630b8a, 2 },
    { sOamFrame_630b1c, 2 },
    { sOamFrame_630aae, 2 },
    { sOamFrame_630a82, 2 },
    { sOamFrame_630a62, 2 },
    { sOamFrame_630a4e, 2 },
    { sOamFrame_630a46, 2 },
    { sOamFrame_630a3e, 2 },
    { sOamFrame_630a36, 2 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630ed8, 2 },
    { sOamFrame_630f04, 2 },
    { sOamFrame_630f30, 2 },
    { sOamFrame_630f86, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_630f86, 2 },
    { sOamFrame_630f30, 2 },
    { sOamFrame_630f04, 2 },
    { sOamFrame_630ed8, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630fdc, 2 },
    { sOamFrame_631008, 2 },
    { sOamFrame_631034, 2 },
    { sOamFrame_63108a, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_63108a, 2 },
    { sOamFrame_631034, 2 },
    { sOamFrame_631008, 2 },
    { sOamFrame_630fdc, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    { sOamFrame_630a2e, 2 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_630c7e, 2 },
    { sOamFrame_630c86, 2 },
    { sOamFrame_630c8e, 2 },
    { sOamFrame_630c9c, 2 },
    { sOamFrame_630cb0, 2 },
    { sOamFrame_630cd0, 2 },
    { sOamFrame_630cfc, 2 },
    { sOamFrame_630d6a, 2 },
    { sOamFrame_630dd8, 2 },
    { sOamFrame_630e52, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_630e52, 2 },
    { sOamFrame_630dd8, 2 },
    { sOamFrame_630d6a, 2 },
    { sOamFrame_630cfc, 2 },
    { sOamFrame_630cd0, 2 },
    { sOamFrame_630cb0, 2 },
    { sOamFrame_630c9c, 2 },
    { sOamFrame_630c8e, 2 },
    { sOamFrame_630c86, 2 },
    { sOamFrame_630c7e, 2 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6310e0, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6310e0, 8 },
    { sOamFrame_631124, 8 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_63116e, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_63116e, 8 },
    { sOamFrame_6311b2, 8 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6311fc, 2 },
    { sOamFrame_631204, 2 },
    { sOamFrame_63120c, 2 },
    { sOamFrame_631214, 2 },
    { sOamFrame_631222, 2 },
    { sOamFrame_63124e, 2 },
    { sOamFrame_63128c, 2 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_63128c, 2 },
    { sOamFrame_63124e, 2 },
    { sOamFrame_631222, 2 },
    { sOamFrame_631214, 2 },
    { sOamFrame_63120c, 2 },
    { sOamFrame_631204, 2 },
    { sOamFrame_6311fc, 2 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6312d0, 2 },
    { sOamFrame_6312d8, 2 },
    { sOamFrame_6312e0, 2 },
    { sOamFrame_6312e8, 2 },
    { sOamFrame_6312f6, 2 },
    { sOamFrame_631322, 2 },
    { sOamFrame_631360, 2 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_631360, 2 },
    { sOamFrame_631322, 2 },
    { sOamFrame_6312f6, 2 },
    { sOamFrame_6312e8, 2 },
    { sOamFrame_6312e0, 2 },
    { sOamFrame_6312d8, 2 },
    { sOamFrame_6312d0, 2 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingAdamIconOam_Idle[6] = {
    { sOamFrame_630a0c, 8 },
    { sOamFrame_6313a4, 8 },
    { sOamFrame_6313b8, 8 },
    { sOamFrame_6313cc, 8 },
    { sOamFrame_6313a4, 8 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingDialogueType2Oam[32] = {
    { sOamFrame_632c4c, 3 },
    { sOamFrame_632c54, 3 },
    { sOamFrame_632c5c, 3 },
    { sOamFrame_632c64, 3 },
    { sOamFrame_632c6c, 3 },
    { sOamFrame_632c74, 3 },
    { sOamFrame_632c7c, 3 },
    { sOamFrame_632c84, 3 },
    { sOamFrame_632c8c, 3 },
    { sOamFrame_632c94, 3 },
    { sOamFrame_632c9c, 3 },
    { sOamFrame_632ca4, 3 },
    { sOamFrame_632cac, 3 },
    { sOamFrame_632cb4, 3 },
    { sOamFrame_632cbc, 3 },
    { sOamFrame_632cdc, 3 },
    { sOamFrame_632cfc, 3 },
    { sOamFrame_632d22, 3 },
    { sOamFrame_632d42, 3 },
    { sOamFrame_632d68, 3 },
    { sOamFrame_632d8e, 3 },
    { sOamFrame_632dba, 3 },
    { sOamFrame_632de0, 3 },
    { sOamFrame_632e0c, 3 },
    { sOamFrame_632e4a, 3 },
    { sOamFrame_632e8e, 3 },
    { sOamFrame_632ecc, 3 },
    { sOamFrame_632f10, 21 },
    { sOamFrame_632f54, 64 },
    { sOamFrame_632f54, 255 },
    { sOamFrame_632f54, 255 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingSr388RadarViewOam_Opening[79] = {
    { sOamFrame_6313e0, 2 },
    { sOamFrame_631442, 2 },
    { sOamFrame_6314a4, 2 },
    { sOamFrame_631506, 2 },
    { sOamFrame_631568, 2 },
    { sOamFrame_6315ca, 2 },
    { sOamFrame_63162c, 2 },
    { sOamFrame_63168e, 2 },
    { sOamFrame_6316f0, 60 },
    { sOamFrame_631442, 2 },
    { sOamFrame_6314a4, 2 },
    { sOamFrame_631506, 2 },
    { sOamFrame_631568, 2 },
    { sOamFrame_6315ca, 2 },
    { sOamFrame_63162c, 2 },
    { sOamFrame_63168e, 2 },
    { sOamFrame_6316f0, 60 },
    { sOamFrame_63175e, 2 },
    { sOamFrame_6317c0, 2 },
    { sOamFrame_631822, 2 },
    { sOamFrame_631884, 2 },
    { sOamFrame_6318e6, 2 },
    { sOamFrame_631948, 2 },
    { sOamFrame_6319aa, 2 },
    { sOamFrame_631a0c, 2 },
    { sOamFrame_631a6e, 60 },
    { sOamFrame_631adc, 2 },
    { sOamFrame_631b3e, 2 },
    { sOamFrame_631ba0, 2 },
    { sOamFrame_631c02, 2 },
    { sOamFrame_631c64, 2 },
    { sOamFrame_631cc6, 2 },
    { sOamFrame_631d28, 2 },
    { sOamFrame_631d8a, 2 },
    { sOamFrame_631dec, 60 },
    { sOamFrame_631e5a, 2 },
    { sOamFrame_631ebc, 2 },
    { sOamFrame_631f1e, 2 },
    { sOamFrame_631f80, 2 },
    { sOamFrame_631fe2, 2 },
    { sOamFrame_632044, 2 },
    { sOamFrame_6320a6, 2 },
    { sOamFrame_632108, 2 },
    { sOamFrame_63216a, 60 },
    { sOamFrame_6321d8, 2 },
    { sOamFrame_63223a, 2 },
    { sOamFrame_63229c, 2 },
    { sOamFrame_6322fe, 2 },
    { sOamFrame_632360, 2 },
    { sOamFrame_6323c2, 2 },
    { sOamFrame_632424, 2 },
    { sOamFrame_632486, 2 },
    { sOamFrame_6324e8, 60 },
    { sOamFrame_632556, 2 },
    { sOamFrame_6325b8, 2 },
    { sOamFrame_63261a, 2 },
    { sOamFrame_63267c, 2 },
    { sOamFrame_6326de, 2 },
    { sOamFrame_632740, 2 },
    { sOamFrame_6327a2, 2 },
    { sOamFrame_632804, 2 },
    { sOamFrame_632866, 60 },
    { sOamFrame_6328d4, 2 },
    { sOamFrame_632936, 2 },
    { sOamFrame_632998, 2 },
    { sOamFrame_6329fa, 2 },
    { sOamFrame_632a5c, 2 },
    { sOamFrame_632abe, 2 },
    { sOamFrame_632b20, 2 },
    { sOamFrame_632b82, 60 },
    { sOamFrame_6328d4, 2 },
    { sOamFrame_632936, 2 },
    { sOamFrame_632998, 2 },
    { sOamFrame_6329fa, 2 },
    { sOamFrame_632a5c, 2 },
    { sOamFrame_632abe, 2 },
    { sOamFrame_632b20, 2 },
    { sOamFrame_632b82, 60 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingSamusViewRadarViewOam_Opening[67] = {
    { sOamFrame_632faa, 81 },
    { sOamFrame_632fb8, 60 },
    { sOamFrame_633030, 40 },
    { sOamFrame_632fcc, 60 },
    { sOamFrame_633038, 40 },
    { sOamFrame_632fe0, 60 },
    { sOamFrame_633040, 40 },
    { sOamFrame_632ff4, 60 },
    { sOamFrame_633048, 40 },
    { sOamFrame_633008, 60 },
    { sOamFrame_633050, 40 },
    { sOamFrame_63301c, 60 },
    { sOamFrame_633050, 35 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_6313e0, 2 },
    { sOamFrame_631442, 2 },
    { sOamFrame_6314a4, 2 },
    { sOamFrame_631506, 2 },
    { sOamFrame_631568, 2 },
    { sOamFrame_6315ca, 2 },
    { sOamFrame_63162c, 2 },
    { sOamFrame_63168e, 2 },
    { sOamFrame_6316f0, 60 },
    { sOamFrame_63175e, 2 },
    { sOamFrame_6317c0, 2 },
    { sOamFrame_631822, 2 },
    { sOamFrame_631884, 2 },
    { sOamFrame_6318e6, 2 },
    { sOamFrame_631948, 2 },
    { sOamFrame_6319aa, 2 },
    { sOamFrame_631a0c, 2 },
    { sOamFrame_631a6e, 60 },
    { sOamFrame_631e5a, 2 },
    { sOamFrame_631ebc, 2 },
    { sOamFrame_631f1e, 2 },
    { sOamFrame_631f80, 2 },
    { sOamFrame_631fe2, 2 },
    { sOamFrame_632044, 2 },
    { sOamFrame_6320a6, 2 },
    { sOamFrame_632108, 2 },
    { sOamFrame_63216a, 60 },
    { sOamFrame_632556, 2 },
    { sOamFrame_6325b8, 2 },
    { sOamFrame_63261a, 2 },
    { sOamFrame_63267c, 2 },
    { sOamFrame_6326de, 2 },
    { sOamFrame_632740, 2 },
    { sOamFrame_6327a2, 2 },
    { sOamFrame_632804, 2 },
    { sOamFrame_632866, 60 },
    { sOamFrame_6328d4, 2 },
    { sOamFrame_632936, 2 },
    { sOamFrame_632998, 2 },
    { sOamFrame_6329fa, 2 },
    { sOamFrame_632a5c, 2 },
    { sOamFrame_632abe, 2 },
    { sOamFrame_632b20, 2 },
    { sOamFrame_632b82, 60 },
    { sOamFrame_6328d4, 2 },
    { sOamFrame_632936, 2 },
    { sOamFrame_632998, 2 },
    { sOamFrame_6329fa, 2 },
    { sOamFrame_632a5c, 2 },
    { sOamFrame_632abe, 2 },
    { sOamFrame_632b20, 2 },
    { sOamFrame_632b82, 60 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingNextPageArrowOam[5] = {
    { sOamFrame_633060, 8 },
    { sOamFrame_633068, 8 },
    { sOamFrame_633070, 8 },
    { sOamFrame_633068, 8 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingTextCursorOam[7] = {
    { sOamFrame_633058, 30 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_633078, 8 },
    { sOamFrame_633080, 8 },
    { sOamFrame_633088, 8 },
    { sOamFrame_633080, 8 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingSr388RadarViewOam_Idle[9] = {
    { sOamFrame_6328d4, 2 },
    { sOamFrame_632936, 2 },
    { sOamFrame_632998, 2 },
    { sOamFrame_6329fa, 2 },
    { sOamFrame_632a5c, 2 },
    { sOamFrame_632abe, 2 },
    { sOamFrame_632b20, 2 },
    { sOamFrame_632b82, 60 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingSamusViewRadarViewOam_Idle[3] = {
    { sOamFrame_633050, 40 },
    { sOamFrame_63301c, 60 },
    FRAME_DATA_TERMINATOR
};
// FrameData array (type 30 of the ending dialogue), followed by the OAM frames of the BSL
// crashing cutscene
const struct FrameData sEndingUnk_633f24[6] = {
    { sOamFrame_633090, 3 },
    { sOamFrame_6331e4, 1 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_630098, 2 },
    { sOamFrame_63318e, 2 },
    FRAME_DATA_TERMINATOR
};
const u16 sOamFrame_633f54[] = INCBIN_U16("data/oam_frames/633f54.bin");
const u16 sOamFrame_633f5c[] = INCBIN_U16("data/oam_frames/633f5c.bin");
const u16 sOamFrame_633fb2[] = INCBIN_U16("data/oam_frames/633fb2.bin");
const u16 sOamFrame_634008[] = INCBIN_U16("data/oam_frames/634008.bin");
const u16 sOamFrame_63405e[] = INCBIN_U16("data/oam_frames/63405e.bin");
const u16 sOamFrame_6340ae[] = INCBIN_U16("data/oam_frames/6340ae.bin");
const u16 sOamFrame_634104[] = INCBIN_U16("data/oam_frames/634104.bin");
const u16 sOamFrame_634160[] = INCBIN_U16("data/oam_frames/634160.bin");
const u16 sOamFrame_6341c2[] = INCBIN_U16("data/oam_frames/6341c2.bin");
const u16 sOamFrame_63421e[] = INCBIN_U16("data/oam_frames/63421e.bin");
const u16 sOamFrame_63427a[] = INCBIN_U16("data/oam_frames/63427a.bin");
const u16 sOamFrame_6342dc[] = INCBIN_U16("data/oam_frames/6342dc.bin");
const u16 sOamFrame_634344[] = INCBIN_U16("data/oam_frames/634344.bin");
const u16 sOamFrame_6343ac[] = INCBIN_U16("data/oam_frames/6343ac.bin");
const u16 sOamFrame_63441a[] = INCBIN_U16("data/oam_frames/63441a.bin");
const u16 sOamFrame_634476[] = INCBIN_U16("data/oam_frames/634476.bin");
const u16 sOamFrame_6344ea[] = INCBIN_U16("data/oam_frames/6344ea.bin");
const u16 sOamFrame_63455e[] = INCBIN_U16("data/oam_frames/63455e.bin");
const u16 sOamFrame_6345cc[] = INCBIN_U16("data/oam_frames/6345cc.bin");
const u16 sOamFrame_634634[] = INCBIN_U16("data/oam_frames/634634.bin");
const u16 sOamFrame_6346a2[] = INCBIN_U16("data/oam_frames/6346a2.bin");
const u16 sOamFrame_634710[] = INCBIN_U16("data/oam_frames/634710.bin");
const u16 sOamFrame_63477e[] = INCBIN_U16("data/oam_frames/63477e.bin");
const u16 sOamFrame_6347f2[] = INCBIN_U16("data/oam_frames/6347f2.bin");
const u16 sOamFrame_634872[] = INCBIN_U16("data/oam_frames/634872.bin");
const u16 sOamFrame_6348f8[] = INCBIN_U16("data/oam_frames/6348f8.bin");
const u16 sOamFrame_63497e[] = INCBIN_U16("data/oam_frames/63497e.bin");
const u16 sOamFrame_634a16[] = INCBIN_U16("data/oam_frames/634a16.bin");
const u16 sOamFrame_634aae[] = INCBIN_U16("data/oam_frames/634aae.bin");
const u16 sOamFrame_634b46[] = INCBIN_U16("data/oam_frames/634b46.bin");
const u16 sOamFrame_634bd2[] = INCBIN_U16("data/oam_frames/634bd2.bin");
const u16 sOamFrame_634c5e[] = INCBIN_U16("data/oam_frames/634c5e.bin");
const u16 sOamFrame_634cea[] = INCBIN_U16("data/oam_frames/634cea.bin");
const u16 sOamFrame_634d76[] = INCBIN_U16("data/oam_frames/634d76.bin");
const u16 sOamFrame_634e08[] = INCBIN_U16("data/oam_frames/634e08.bin");
const u16 sOamFrame_634e9a[] = INCBIN_U16("data/oam_frames/634e9a.bin");
const u16 sOamFrame_634f1a[] = INCBIN_U16("data/oam_frames/634f1a.bin");
const u16 sOamFrame_634fa0[] = INCBIN_U16("data/oam_frames/634fa0.bin");
const u16 sOamFrame_635020[] = INCBIN_U16("data/oam_frames/635020.bin");
const u16 sOamFrame_635094[] = INCBIN_U16("data/oam_frames/635094.bin");
const u16 sOamFrame_63510e[] = INCBIN_U16("data/oam_frames/63510e.bin");
const u16 sOamFrame_635182[] = INCBIN_U16("data/oam_frames/635182.bin");
const u16 sOamFrame_6351fc[] = INCBIN_U16("data/oam_frames/6351fc.bin");
const u16 sOamFrame_635270[] = INCBIN_U16("data/oam_frames/635270.bin");
const u16 sOamFrame_6352f0[] = INCBIN_U16("data/oam_frames/6352f0.bin");
const u16 sOamFrame_635364[] = INCBIN_U16("data/oam_frames/635364.bin");
const u16 sOamFrame_6353d2[] = INCBIN_U16("data/oam_frames/6353d2.bin");
const u16 sOamFrame_63544c[] = INCBIN_U16("data/oam_frames/63544c.bin");
const u16 sOamFrame_6354ba[] = INCBIN_U16("data/oam_frames/6354ba.bin");
const u16 sOamFrame_635528[] = INCBIN_U16("data/oam_frames/635528.bin");
const u16 sOamFrame_635596[] = INCBIN_U16("data/oam_frames/635596.bin");
const u16 sOamFrame_6355f8[] = INCBIN_U16("data/oam_frames/6355f8.bin");
const u16 sOamFrame_635660[] = INCBIN_U16("data/oam_frames/635660.bin");
const u16 sOamFrame_6356c2[] = INCBIN_U16("data/oam_frames/6356c2.bin");
const u16 sOamFrame_63572a[] = INCBIN_U16("data/oam_frames/63572a.bin");
const u16 sOamFrame_635786[] = INCBIN_U16("data/oam_frames/635786.bin");
const u16 sOamFrame_6357d6[] = INCBIN_U16("data/oam_frames/6357d6.bin");
const u16 sOamFrame_635826[] = INCBIN_U16("data/oam_frames/635826.bin");
const u16 sOamFrame_635870[] = INCBIN_U16("data/oam_frames/635870.bin");
const u16 sOamFrame_6358b4[] = INCBIN_U16("data/oam_frames/6358b4.bin");
const u16 sOamFrame_6358ec[] = INCBIN_U16("data/oam_frames/6358ec.bin");
const u16 sOamFrame_63591e[] = INCBIN_U16("data/oam_frames/63591e.bin");
const u16 sOamFrame_63594a[] = INCBIN_U16("data/oam_frames/63594a.bin");
const u16 sOamFrame_635970[] = INCBIN_U16("data/oam_frames/635970.bin");
const u16 sOamFrame_635996[] = INCBIN_U16("data/oam_frames/635996.bin");
const u16 sOamFrame_6359b6[] = INCBIN_U16("data/oam_frames/6359b6.bin");
const u16 sOamFrame_6359d0[] = INCBIN_U16("data/oam_frames/6359d0.bin");
const u16 sOamFrame_6359e4[] = INCBIN_U16("data/oam_frames/6359e4.bin");
const u16 sOamFrame_6359f8[] = INCBIN_U16("data/oam_frames/6359f8.bin");
const u16 sOamFrame_635a0c[] = INCBIN_U16("data/oam_frames/635a0c.bin");
const u16 sOamFrame_635a20[] = INCBIN_U16("data/oam_frames/635a20.bin");
const u16 sOamFrame_635a28[] = INCBIN_U16("data/oam_frames/635a28.bin");
const u16 sOamFrame_635a36[] = INCBIN_U16("data/oam_frames/635a36.bin");
const u16 sOamFrame_635a3e[] = INCBIN_U16("data/oam_frames/635a3e.bin");
const u16 sOamFrame_635a4c[] = INCBIN_U16("data/oam_frames/635a4c.bin");
const u16 sOamFrame_635a5a[] = INCBIN_U16("data/oam_frames/635a5a.bin");
const u16 sOamFrame_635b34[] = INCBIN_U16("data/oam_frames/635b34.bin");
const u16 sOamFrame_635bfc[] = INCBIN_U16("data/oam_frames/635bfc.bin");
const u16 sOamFrame_635c04[] = INCBIN_U16("data/oam_frames/635c04.bin");
const u16 sOamFrame_635c24[] = INCBIN_U16("data/oam_frames/635c24.bin");
const u16 sOamFrame_635c5c[] = INCBIN_U16("data/oam_frames/635c5c.bin");
const u16 sOamFrame_635ca6[] = INCBIN_U16("data/oam_frames/635ca6.bin");
const u16 sOamFrame_635cf6[] = INCBIN_U16("data/oam_frames/635cf6.bin");
const u16 sOamFrame_635d4c[] = INCBIN_U16("data/oam_frames/635d4c.bin");
const u16 sOamFrame_635d96[] = INCBIN_U16("data/oam_frames/635d96.bin");
const u16 sOamFrame_635dce[] = INCBIN_U16("data/oam_frames/635dce.bin");
const u16 sOamFrame_635de8[] = INCBIN_U16("data/oam_frames/635de8.bin");
const u16 sOamFrame_635dfc[] = INCBIN_U16("data/oam_frames/635dfc.bin");
const u16 sOamFrame_635e9a[] = INCBIN_U16("data/oam_frames/635e9a.bin");
const u16 sOamFrame_635ea2[] = INCBIN_U16("data/oam_frames/635ea2.bin");
const u16 sOamFrame_635eaa[] = INCBIN_U16("data/oam_frames/635eaa.bin");
const u16 sOamFrame_635eb2[] = INCBIN_U16("data/oam_frames/635eb2.bin");
const u16 sOamFrame_635eba[] = INCBIN_U16("data/oam_frames/635eba.bin");
const u16 sOamFrame_635ec2[] = INCBIN_U16("data/oam_frames/635ec2.bin");
const u16 sOamFrame_635eca[] = INCBIN_U16("data/oam_frames/635eca.bin");
const u16 sOamFrame_635ed2[] = INCBIN_U16("data/oam_frames/635ed2.bin");
const u16 sOamFrame_635eda[] = INCBIN_U16("data/oam_frames/635eda.bin");
const u16 sOamFrame_635ee2[] = INCBIN_U16("data/oam_frames/635ee2.bin");
const u16 sOamFrame_635eea[] = INCBIN_U16("data/oam_frames/635eea.bin");
const u16 sOamFrame_635ef2[] = INCBIN_U16("data/oam_frames/635ef2.bin");
const u16 sOamFrame_635efa[] = INCBIN_U16("data/oam_frames/635efa.bin");
const u16 sOamFrame_635f02[] = INCBIN_U16("data/oam_frames/635f02.bin");
const u16 sOamFrame_635f0a[] = INCBIN_U16("data/oam_frames/635f0a.bin");
const u16 sOamFrame_635f66[] = INCBIN_U16("data/oam_frames/635f66.bin");
const u16 sOamFrame_635fc2[] = INCBIN_U16("data/oam_frames/635fc2.bin");
const u16 sOamFrame_635fca[] = INCBIN_U16("data/oam_frames/635fca.bin");
const u16 sOamFrame_635fd8[] = INCBIN_U16("data/oam_frames/635fd8.bin");
const u16 sOamFrame_635fe0[] = INCBIN_U16("data/oam_frames/635fe0.bin");
const u16 sOamFrame_635fe8[] = INCBIN_U16("data/oam_frames/635fe8.bin");
const u16 sOamFrame_635ff0[] = INCBIN_U16("data/oam_frames/635ff0.bin");
const u16 sOamFrame_635ff8[] = INCBIN_U16("data/oam_frames/635ff8.bin");
const u16 sOamFrame_63600c[] = INCBIN_U16("data/oam_frames/63600c.bin");
const struct FrameData sBslCrashingFallingBslOam[3] = {
    { sOamFrame_635a20, 100 },
    { sOamFrame_635a28, 100 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sBslCrashingFallingBslTransparentOam[3] = {
    { sOamFrame_633f54, 100 },
    { sOamFrame_635a36, 100 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sBslCrashingType3Oam[71] = {
    { sOamFrame_633f54, 131 },
    { sOamFrame_635a0c, 1 },
    { sOamFrame_6359f8, 1 },
    { sOamFrame_6359e4, 1 },
    { sOamFrame_6359d0, 1 },
    { sOamFrame_6359b6, 1 },
    { sOamFrame_635996, 1 },
    { sOamFrame_635970, 1 },
    { sOamFrame_63594a, 1 },
    { sOamFrame_63591e, 1 },
    { sOamFrame_6358ec, 1 },
    { sOamFrame_6358b4, 1 },
    { sOamFrame_635870, 1 },
    { sOamFrame_635826, 1 },
    { sOamFrame_6357d6, 1 },
    { sOamFrame_635786, 1 },
    { sOamFrame_63572a, 1 },
    { sOamFrame_6356c2, 1 },
    { sOamFrame_635660, 1 },
    { sOamFrame_6355f8, 1 },
    { sOamFrame_635596, 1 },
    { sOamFrame_635528, 1 },
    { sOamFrame_6354ba, 1 },
    { sOamFrame_63544c, 1 },
    { sOamFrame_6353d2, 1 },
    { sOamFrame_635364, 1 },
    { sOamFrame_6352f0, 1 },
    { sOamFrame_635270, 1 },
    { sOamFrame_6351fc, 1 },
    { sOamFrame_635182, 1 },
    { sOamFrame_63510e, 1 },
    { sOamFrame_635094, 1 },
    { sOamFrame_635020, 1 },
    { sOamFrame_634fa0, 1 },
    { sOamFrame_634f1a, 1 },
    { sOamFrame_634e9a, 1 },
    { sOamFrame_634e08, 1 },
    { sOamFrame_634d76, 1 },
    { sOamFrame_634cea, 1 },
    { sOamFrame_634c5e, 1 },
    { sOamFrame_634bd2, 1 },
    { sOamFrame_634b46, 1 },
    { sOamFrame_634aae, 1 },
    { sOamFrame_634a16, 1 },
    { sOamFrame_63497e, 1 },
    { sOamFrame_6348f8, 1 },
    { sOamFrame_634872, 1 },
    { sOamFrame_6347f2, 1 },
    { sOamFrame_63477e, 1 },
    { sOamFrame_634710, 1 },
    { sOamFrame_6346a2, 1 },
    { sOamFrame_634634, 1 },
    { sOamFrame_6345cc, 1 },
    { sOamFrame_63455e, 1 },
    { sOamFrame_6344ea, 1 },
    { sOamFrame_634476, 1 },
    { sOamFrame_63441a, 1 },
    { sOamFrame_6343ac, 1 },
    { sOamFrame_634344, 1 },
    { sOamFrame_6342dc, 1 },
    { sOamFrame_63427a, 1 },
    { sOamFrame_63421e, 1 },
    { sOamFrame_6341c2, 1 },
    { sOamFrame_634160, 1 },
    { sOamFrame_634104, 1 },
    { sOamFrame_6340ae, 1 },
    { sOamFrame_63405e, 1 },
    { sOamFrame_634008, 1 },
    { sOamFrame_633fb2, 1 },
    { sOamFrame_633f5c, 1 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingLeavingSmallShipOam[3] = {
    { sOamFrame_635a3e, 2 },
    { sOamFrame_635a4c, 2 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingLeavingBigShipOam[3] = {
    { sOamFrame_635a5a, 2 },
    { sOamFrame_635b34, 2 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sBslCrashingFallingBslOam_End[29] = {
    { sOamFrame_635bfc, 4 },
    { sOamFrame_635c04, 4 },
    { sOamFrame_635c24, 4 },
    { sOamFrame_635c5c, 4 },
    { sOamFrame_635ca6, 4 },
    { sOamFrame_635cf6, 4 },
    { sOamFrame_635d4c, 6 },
    { sOamFrame_635d96, 7 },
    { sOamFrame_635dce, 8 },
    { sOamFrame_635de8, 9 },
    { sOamFrame_635dfc, 10 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_635e9a, 5 },
    { sOamFrame_635ea2, 5 },
    { sOamFrame_635eaa, 5 },
    { sOamFrame_635eb2, 5 },
    { sOamFrame_635eba, 5 },
    { sOamFrame_635ec2, 5 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_635eca, 4 },
    { sOamFrame_635ed2, 4 },
    { sOamFrame_635eda, 4 },
    { sOamFrame_635ee2, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_635eea, 4 },
    { sOamFrame_635ef2, 4 },
    { sOamFrame_635efa, 4 },
    { sOamFrame_635f02, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingFrontFacingShipOam[3] = {
    { sOamFrame_635f0a, 3 },
    { sOamFrame_635f66, 2 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sEndingFrontFacingShipThrustersOam[16] = {
    { sOamFrame_635fc2, 1 },
    { sOamFrame_633f54, 1 },
    { sOamFrame_635fca, 1 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_635fd8, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_635fe0, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_635fe8, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_635ff0, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_635ff8, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_63600c, 4 },
    FRAME_DATA_TERMINATOR
};

const u16 sEndingInShipBgPal[16 * PAL_ROW] = INCBIN_U16("data/ending/in_ship_bg.pal");
const u16 sEndingInShipObjPal[16 * PAL_ROW] = INCBIN_U16("data/ending/in_ship_obj.pal");
const u16 sEndingAnimalsBgPal[16 * PAL_ROW] = INCBIN_U16("data/ending/animals_bg.pal");
const u16 sBslCrashingAnimatedBgPal[16 * PAL_ROW] = INCBIN_U16("data/ending/bsl_crashing_animated_bg.pal");
const u16 sBslCrashingObjPal[16 * PAL_ROW] = INCBIN_U16("data/ending/bsl_crashing_obj.pal");
const u16 sEndingShipFrontViewBgPal[16 * PAL_ROW] = INCBIN_U16("data/ending/ship_front_view_bg.pal");
const u16 sBslCrashingBgPal[16 * PAL_ROW] = INCBIN_U16("data/ending/bsl_crashing_bg.pal");

const u32 sEndingAdamConversationBgTilemap[368] = INCBIN_U32("data/ending/adam_conversation_bg.tm.lz");
const u32 sEndingMonologueBgTilemap[368] = INCBIN_U32("data/ending/monologue_bg.tm.lz");
const u32 sEndingAnimalsBg3Tilemap[551] = INCBIN_U32("data/ending/animals_bg3.tm.lz");
const u32 sEndingAnimalsBg2Tilemap[368] = INCBIN_U32("data/ending/animals_bg2.tm.lz");
const u32 sBslCrashingBg1Tilemap[418] = INCBIN_U32("data/ending/bsl_crashing_bg1.tm.lz");
const u32 sEndingShipFrontViewBg2Tilemap[199] = INCBIN_U32("data/ending/ship_front_view_bg2.tm.lz");
const u32 sEndingShipFrontViewBg3Tilemap[387] = INCBIN_U32("data/ending/ship_front_view_bg3.tm.lz");
const u32 sBslCrashingBg3Tilemap[368] = INCBIN_U32("data/ending/bsl_crashing_bg3.tm.lz");

// Width and height of each OAM shape and size in tiles (see sOamXFlipOffsets)
const u8 sCutsceneOamXFlipOffsets[3][4] = INCBIN_U8("data/cutscenes/oam_x_flip_offsets.bin");
const u8 sCutsceneOamYFlipOffsets[3][4] = INCBIN_U8("data/cutscenes/oam_y_flip_offsets.bin");

const u16 sCutsceneTextNone[2] = {
    CHAR_TERMINATOR, CHAR_TERMINATOR
};

const u32 sIntroSr388SurfaceBgGfx0[686] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_0.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx1[767] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_1.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx2[848] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_2.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx3[641] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_3.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx4[577] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_4.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx5[655] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_5.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx6[513] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_6.gfx.lz");
const u32 sIntroSr388SurfaceBgGfx7[177] = INCBIN_U32("data/new_file_intro/sr388_surface_bg_7.gfx.lz");

const u32 sIntroSr388PlanetBgGfx0[719] = INCBIN_U32("data/new_file_intro/sr388_planet_bg_0.gfx.lz");
const u32 sIntroSr388PlanetBgGfx1[809] = INCBIN_U32("data/new_file_intro/sr388_planet_bg_1.gfx.lz");
const u32 sIntroSr388PlanetBgGfx2[794] = INCBIN_U32("data/new_file_intro/sr388_planet_bg_2.gfx.lz");
const u32 sIntroSr388PlanetBgGfx3[782] = INCBIN_U32("data/new_file_intro/sr388_planet_bg_3.gfx.lz");
const u32 sIntroSr388PlanetBgGfx4[772] = INCBIN_U32("data/new_file_intro/sr388_planet_bg_4.gfx.lz");

const u32 sIntroBslObjectGfx0[448] = INCBIN_U32("data/new_file_intro/bsl_object_0.gfx.lz");
const u32 sIntroBslObjectGfx1[402] = INCBIN_U32("data/new_file_intro/bsl_object_1.gfx.lz");
const u32 sIntroBslObjectGfx2[420] = INCBIN_U32("data/new_file_intro/bsl_object_2.gfx.lz");
const u32 sIntroBslObjectGfx3[124] = INCBIN_U32("data/new_file_intro/bsl_object_3.gfx.lz");
const u32 sIntroBslObjectGfx4[298] = INCBIN_U32("data/new_file_intro/bsl_object_4.gfx.lz");
const u32 sIntroBslObjectGfx5[186] = INCBIN_U32("data/new_file_intro/bsl_object_5.gfx.lz");
const u32 sIntroBslObjectGfx6[543] = INCBIN_U32("data/new_file_intro/bsl_object_6.gfx.lz");
const u32 sIntroBslObjectGfx7[482] = INCBIN_U32("data/new_file_intro/bsl_object_7.gfx.lz");

const u32 sIntroSamusSittingBgGfx0[920] = INCBIN_U32("data/new_file_intro/samus_sitting_bg_0.gfx.lz");
const u32 sIntroSamusSittingBgGfx1[978] = INCBIN_U32("data/new_file_intro/samus_sitting_bg_1.gfx.lz");
const u32 sIntroSamusSittingBgGfx2[962] = INCBIN_U32("data/new_file_intro/samus_sitting_bg_2.gfx.lz");
const u32 sIntroSamusSittingBgGfx3[944] = INCBIN_U32("data/new_file_intro/samus_sitting_bg_3.gfx.lz");
const u32 sIntroSamusSittingBgGfx4[800] = INCBIN_U32("data/new_file_intro/samus_sitting_bg_4.gfx.lz");

const u32 sIntroSamusHelmetCloseupBgGfx0[598] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_0.gfx.lz");
const u32 sIntroSamusHelmetCloseupBgGfx1[848] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_1.gfx.lz");
const u32 sIntroSamusHelmetCloseupBgGfx2[908] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_2.gfx.lz");
const u32 sIntroSamusHelmetCloseupBgGfx3[812] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_3.gfx.lz");
const u32 sIntroSamusHelmetCloseupBgGfx4[844] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_4.gfx.lz");
const u32 sIntroSamusHelmetCloseupBgGfx5[403] = INCBIN_U32("data/new_file_intro/samus_helmet_closeup_bg_5.gfx.lz");

// Ship alert graphics (sIntroShipAlertBgGfxPointers, sIntroShipAlertObjGfxPointers) and the
// graphics of the unreferenced sIntroGfxPointers_79c474
const u32 sIntroShipAlertBgGfx_0[] = INCBIN_U32("data/new_file_intro/ship_alert_bg_0.gfx.lz");
const u32 sIntroShipAlertBgGfx_1[] = INCBIN_U32("data/new_file_intro/ship_alert_bg_1.gfx.lz");
const u32 sIntroShipAlertBgGfx_2[] = INCBIN_U32("data/new_file_intro/ship_alert_bg_2.gfx.lz");
const u32 sIntroShipAlertBgGfx_3[] = INCBIN_U32("data/new_file_intro/ship_alert_bg_3.gfx.lz");
const u32 sIntroShipAlertBgGfx_4[] = INCBIN_U32("data/new_file_intro/ship_alert_bg_4.gfx.lz");
const u32 sIntroShipAlertObjGfx_0[] = INCBIN_U32("data/new_file_intro/ship_alert_obj_0.gfx.lz");
const u32 sIntroShipAlertObjGfx_1[] = INCBIN_U32("data/new_file_intro/ship_alert_obj_1.gfx.lz");
const u32 sIntroShipAlertObjGfx_2[] = INCBIN_U32("data/new_file_intro/ship_alert_obj_2.gfx.lz");
const u32 sIntroShipAlertObjGfx_3[] = INCBIN_U32("data/new_file_intro/ship_alert_obj_3.gfx.lz");
const u32 sIntroShipAlertObjGfx_4[] = INCBIN_U32("data/new_file_intro/ship_alert_obj_4.gfx.lz");
const u32 sIntroShipAlertObjGfx_5[] = INCBIN_U32("data/new_file_intro/ship_alert_obj_5.gfx.lz");
const u32 sIntroGfx_652bd4[] = INCBIN_U32("data/new_file_intro/652bd4.gfx.lz");
const u32 sIntroGfx_653980[] = INCBIN_U32("data/new_file_intro/653980.gfx.lz");
const u32 sIntroGfx_6546f4[] = INCBIN_U32("data/new_file_intro/6546f4.gfx.lz");
const u32 sIntroGfx_6552a0[] = INCBIN_U32("data/new_file_intro/6552a0.gfx.lz");
const u32 sIntroGfx_655f3c[] = INCBIN_U32("data/new_file_intro/655f3c.gfx.lz");
const u32 sIntroGfx_656cd0[] = INCBIN_U32("data/new_file_intro/656cd0.gfx.lz");
const u32 sIntroGfx_657408[] = INCBIN_U32("data/new_file_intro/657408.gfx.lz");
const u32 sIntroGfx_6579c4[] = INCBIN_U32("data/new_file_intro/6579c4.gfx.lz");
const u32 sIntroGfx_657d2c[] = INCBIN_U32("data/new_file_intro/657d2c.gfx.lz");
const u32 sIntroGfx_657f60[] = INCBIN_U32("data/new_file_intro/657f60.gfx.lz");
const u32 sIntroGfx_658150[] = INCBIN_U32("data/new_file_intro/658150.gfx.lz");
const u32 sIntroGfx_658468[] = INCBIN_U32("data/new_file_intro/658468.gfx.lz");
const u32 sIntroGfx_658848[] = INCBIN_U32("data/new_file_intro/658848.gfx.lz");
const u32 sIntroSamusInShipTilemap[385] = INCBIN_U32("data/new_file_intro/samus_in_ship.tm.lz");
const u16 sIntroSamusInShipPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/samus_in_ship.pal");
const u32 sIntroShipAlertBg1Tilemap[368] = INCBIN_U32("data/new_file_intro/ship_alert_bg1.tm.lz");
const u16 sIntroShipAlertBgPal[8 * PAL_ROW] = INCBIN_U16("data/new_file_intro/ship_alert_bg.pal");
// Rows 8-15 of the ship alert BG palette (sIntroShipAlertBgPal is rows 0-7). Rows 8-14 are
// black, row 15 holds plain test colors (white, red, magenta, yellow, green, blue, cyan).
// Not referenced by code: only rows 0-7 are copied
const u16 sIntroShipAlertBgPalRows8To15[8 * PAL_ROW] = INCBIN_U16("data/new_file_intro/ship_alert_bg_rows_8_15.pal");
// OAM frames of the FrameData arrays below
const u16 sOamFrame_659ba4[] = INCBIN_U16("data/oam_frames/659ba4.bin");
const u16 sOamFrame_659bd0[] = INCBIN_U16("data/oam_frames/659bd0.bin");
const u16 sOamFrame_659bf0[] = INCBIN_U16("data/oam_frames/659bf0.bin");
const u16 sOamFrame_659c34[] = INCBIN_U16("data/oam_frames/659c34.bin");
const u16 sOamFrame_659c72[] = INCBIN_U16("data/oam_frames/659c72.bin");
const u16 sOamFrame_659cb6[] = INCBIN_U16("data/oam_frames/659cb6.bin");
const u16 sOamFrame_659cfa[] = INCBIN_U16("data/oam_frames/659cfa.bin");
const u16 sOamFrame_659d38[] = INCBIN_U16("data/oam_frames/659d38.bin");
const u16 sOamFrame_659d76[] = INCBIN_U16("data/oam_frames/659d76.bin");
const u16 sOamFrame_659da8[] = INCBIN_U16("data/oam_frames/659da8.bin");
const u16 sOamFrame_659de0[] = INCBIN_U16("data/oam_frames/659de0.bin");
const u16 sOamFrame_659de8[] = INCBIN_U16("data/oam_frames/659de8.bin");
const u16 sOamFrame_659df0[] = INCBIN_U16("data/oam_frames/659df0.bin");
const u16 sOamFrame_659df8[] = INCBIN_U16("data/oam_frames/659df8.bin");
const u16 sOamFrame_659e00[] = INCBIN_U16("data/oam_frames/659e00.bin");
const u16 sOamFrame_659e08[] = INCBIN_U16("data/oam_frames/659e08.bin");
const u16 sOamFrame_659e10[] = INCBIN_U16("data/oam_frames/659e10.bin");
const u16 sOamFrame_659e18[] = INCBIN_U16("data/oam_frames/659e18.bin");
const u16 sOamFrame_659e32[] = INCBIN_U16("data/oam_frames/659e32.bin");
const u16 sOamFrame_659e5e[] = INCBIN_U16("data/oam_frames/659e5e.bin");
const u16 sOamFrame_659e90[] = INCBIN_U16("data/oam_frames/659e90.bin");
const u16 sOamFrame_659ec8[] = INCBIN_U16("data/oam_frames/659ec8.bin");
const u16 sOamFrame_659f1e[] = INCBIN_U16("data/oam_frames/659f1e.bin");
const u16 sOamFrame_659f86[] = INCBIN_U16("data/oam_frames/659f86.bin");
const u16 sOamFrame_659ff4[] = INCBIN_U16("data/oam_frames/659ff4.bin");
const u16 sOamFrame_65a080[] = INCBIN_U16("data/oam_frames/65a080.bin");
const u16 sOamFrame_65a09a[] = INCBIN_U16("data/oam_frames/65a09a.bin");
const u16 sOamFrame_65a0b4[] = INCBIN_U16("data/oam_frames/65a0b4.bin");
const u16 sOamFrame_65a0ce[] = INCBIN_U16("data/oam_frames/65a0ce.bin");
const u16 sOamFrame_65a0e8[] = INCBIN_U16("data/oam_frames/65a0e8.bin");
const u16 sOamFrame_65a102[] = INCBIN_U16("data/oam_frames/65a102.bin");
const u16 sOamFrame_65a11c[] = INCBIN_U16("data/oam_frames/65a11c.bin");
const u16 sOamFrame_65a136[] = INCBIN_U16("data/oam_frames/65a136.bin");
const u16 sOamFrame_65a150[] = INCBIN_U16("data/oam_frames/65a150.bin");
const u16 sOamFrame_65a16a[] = INCBIN_U16("data/oam_frames/65a16a.bin");
const u16 sOamFrame_65a184[] = INCBIN_U16("data/oam_frames/65a184.bin");
const u16 sOamFrame_65a18c[] = INCBIN_U16("data/oam_frames/65a18c.bin");
const u16 sOamFrame_65a194[] = INCBIN_U16("data/oam_frames/65a194.bin");
const u16 sOamFrame_65a19c[] = INCBIN_U16("data/oam_frames/65a19c.bin");
const u16 sOamFrame_65a1a4[] = INCBIN_U16("data/oam_frames/65a1a4.bin");
const u16 sOamFrame_65a1ac[] = INCBIN_U16("data/oam_frames/65a1ac.bin");
const u16 sOamFrame_65a1b4[] = INCBIN_U16("data/oam_frames/65a1b4.bin");
const u16 sOamFrame_65a1bc[] = INCBIN_U16("data/oam_frames/65a1bc.bin");
const u16 sOamFrame_65a1c4[] = INCBIN_U16("data/oam_frames/65a1c4.bin");
const u16 sOamFrame_65a1cc[] = INCBIN_U16("data/oam_frames/65a1cc.bin");
const u16 sOamFrame_65a1d4[] = INCBIN_U16("data/oam_frames/65a1d4.bin");
const u16 sOamFrame_65a1e8[] = INCBIN_U16("data/oam_frames/65a1e8.bin");
const u16 sOamFrame_65a202[] = INCBIN_U16("data/oam_frames/65a202.bin");
const u16 sOamFrame_65a21c[] = INCBIN_U16("data/oam_frames/65a21c.bin");
const u16 sOamFrame_65a23c[] = INCBIN_U16("data/oam_frames/65a23c.bin");
const u16 sOamFrame_65a25c[] = INCBIN_U16("data/oam_frames/65a25c.bin");
const u16 sOamFrame_65a27c[] = INCBIN_U16("data/oam_frames/65a27c.bin");
const u16 sOamFrame_65a29c[] = INCBIN_U16("data/oam_frames/65a29c.bin");
const u16 sOamFrame_65a2bc[] = INCBIN_U16("data/oam_frames/65a2bc.bin");
const u16 sOamFrame_65a2dc[] = INCBIN_U16("data/oam_frames/65a2dc.bin");
const u16 sOamFrame_65a2fc[] = INCBIN_U16("data/oam_frames/65a2fc.bin");
const u16 sOamFrame_65a328[] = INCBIN_U16("data/oam_frames/65a328.bin");
const u16 sOamFrame_65a354[] = INCBIN_U16("data/oam_frames/65a354.bin");
const u16 sOamFrame_65a380[] = INCBIN_U16("data/oam_frames/65a380.bin");
const u16 sOamFrame_65a3ac[] = INCBIN_U16("data/oam_frames/65a3ac.bin");
const u16 sOamFrame_65a3d8[] = INCBIN_U16("data/oam_frames/65a3d8.bin");
const u16 sOamFrame_65a404[] = INCBIN_U16("data/oam_frames/65a404.bin");
const u16 sOamFrame_65a430[] = INCBIN_U16("data/oam_frames/65a430.bin");
const u16 sOamFrame_65a462[] = INCBIN_U16("data/oam_frames/65a462.bin");
const u16 sOamFrame_65a49a[] = INCBIN_U16("data/oam_frames/65a49a.bin");
const u16 sOamFrame_65a4d2[] = INCBIN_U16("data/oam_frames/65a4d2.bin");
const u16 sOamFrame_65a50a[] = INCBIN_U16("data/oam_frames/65a50a.bin");
const u16 sOamFrame_65a542[] = INCBIN_U16("data/oam_frames/65a542.bin");
const u16 sOamFrame_65a57a[] = INCBIN_U16("data/oam_frames/65a57a.bin");
const u16 sOamFrame_65a5b2[] = INCBIN_U16("data/oam_frames/65a5b2.bin");
const u16 sOamFrame_65a5f0[] = INCBIN_U16("data/oam_frames/65a5f0.bin");
const u16 sOamFrame_65a634[] = INCBIN_U16("data/oam_frames/65a634.bin");
const u16 sOamFrame_65a678[] = INCBIN_U16("data/oam_frames/65a678.bin");
const u16 sOamFrame_65a6bc[] = INCBIN_U16("data/oam_frames/65a6bc.bin");
const u16 sOamFrame_65a700[] = INCBIN_U16("data/oam_frames/65a700.bin");
const u16 sOamFrame_65a744[] = INCBIN_U16("data/oam_frames/65a744.bin");
const u16 sOamFrame_65a788[] = INCBIN_U16("data/oam_frames/65a788.bin");
const u16 sOamFrame_65a7cc[] = INCBIN_U16("data/oam_frames/65a7cc.bin");
const u16 sOamFrame_65a816[] = INCBIN_U16("data/oam_frames/65a816.bin");
const u16 sOamFrame_65a866[] = INCBIN_U16("data/oam_frames/65a866.bin");
const u16 sOamFrame_65a8b6[] = INCBIN_U16("data/oam_frames/65a8b6.bin");
const u16 sOamFrame_65a906[] = INCBIN_U16("data/oam_frames/65a906.bin");
const u16 sOamFrame_65a956[] = INCBIN_U16("data/oam_frames/65a956.bin");
const u16 sOamFrame_65a9a6[] = INCBIN_U16("data/oam_frames/65a9a6.bin");
const u16 sOamFrame_65a9fc[] = INCBIN_U16("data/oam_frames/65a9fc.bin");
const u16 sOamFrame_65aa58[] = INCBIN_U16("data/oam_frames/65aa58.bin");
const u16 sOamFrame_65aaba[] = INCBIN_U16("data/oam_frames/65aaba.bin");
const u16 sOamFrame_65ab22[] = INCBIN_U16("data/oam_frames/65ab22.bin");
const u16 sOamFrame_65ab90[] = INCBIN_U16("data/oam_frames/65ab90.bin");
const u16 sOamFrame_65abf2[] = INCBIN_U16("data/oam_frames/65abf2.bin");
const u16 sOamFrame_65ac60[] = INCBIN_U16("data/oam_frames/65ac60.bin");
const u16 sOamFrame_65ace6[] = INCBIN_U16("data/oam_frames/65ace6.bin");
const u16 sOamFrame_65ad7e[] = INCBIN_U16("data/oam_frames/65ad7e.bin");
const u16 sOamFrame_65adaa[] = INCBIN_U16("data/oam_frames/65adaa.bin");
const u16 sOamFrame_65add6[] = INCBIN_U16("data/oam_frames/65add6.bin");
const u16 sOamFrame_65adf6[] = INCBIN_U16("data/oam_frames/65adf6.bin");
const u16 sOamFrame_65ae16[] = INCBIN_U16("data/oam_frames/65ae16.bin");
const u16 sOamFrame_65ae3c[] = INCBIN_U16("data/oam_frames/65ae3c.bin");
const u16 sOamFrame_65ae62[] = INCBIN_U16("data/oam_frames/65ae62.bin");
const u16 sOamFrame_65ae8e[] = INCBIN_U16("data/oam_frames/65ae8e.bin");
const u16 sOamFrame_65aeba[] = INCBIN_U16("data/oam_frames/65aeba.bin");
const u16 sOamFrame_65aee6[] = INCBIN_U16("data/oam_frames/65aee6.bin");
const u16 sOamFrame_65af12[] = INCBIN_U16("data/oam_frames/65af12.bin");
const u16 sOamFrame_65af3e[] = INCBIN_U16("data/oam_frames/65af3e.bin");
const u16 sOamFrame_65af5e[] = INCBIN_U16("data/oam_frames/65af5e.bin");
const u16 sOamFrame_65af7e[] = INCBIN_U16("data/oam_frames/65af7e.bin");
const u16 sOamFrame_65afa4[] = INCBIN_U16("data/oam_frames/65afa4.bin");
const u16 sOamFrame_65afca[] = INCBIN_U16("data/oam_frames/65afca.bin");
const u16 sOamFrame_65aff6[] = INCBIN_U16("data/oam_frames/65aff6.bin");
const u16 sOamFrame_65b01c[] = INCBIN_U16("data/oam_frames/65b01c.bin");
const u16 sOamFrame_65b04e[] = INCBIN_U16("data/oam_frames/65b04e.bin");
const u16 sOamFrame_65b080[] = INCBIN_U16("data/oam_frames/65b080.bin");
const u16 sOamFrame_65b0b2[] = INCBIN_U16("data/oam_frames/65b0b2.bin");
const u16 sOamFrame_65b0e4[] = INCBIN_U16("data/oam_frames/65b0e4.bin");
const u16 sOamFrame_65b104[] = INCBIN_U16("data/oam_frames/65b104.bin");
const u16 sOamFrame_65b124[] = INCBIN_U16("data/oam_frames/65b124.bin");
const u16 sOamFrame_65b14a[] = INCBIN_U16("data/oam_frames/65b14a.bin");
const u16 sOamFrame_65b170[] = INCBIN_U16("data/oam_frames/65b170.bin");
const u16 sOamFrame_65b196[] = INCBIN_U16("data/oam_frames/65b196.bin");
const u16 sOamFrame_65b1bc[] = INCBIN_U16("data/oam_frames/65b1bc.bin");
const u16 sOamFrame_65b1e2[] = INCBIN_U16("data/oam_frames/65b1e2.bin");
const u16 sOamFrame_65b202[] = INCBIN_U16("data/oam_frames/65b202.bin");
const u16 sOamFrame_65b222[] = INCBIN_U16("data/oam_frames/65b222.bin");
const u16 sOamFrame_65b248[] = INCBIN_U16("data/oam_frames/65b248.bin");
const u16 sOamFrame_65b26e[] = INCBIN_U16("data/oam_frames/65b26e.bin");
const u16 sOamFrame_65b29a[] = INCBIN_U16("data/oam_frames/65b29a.bin");
const u16 sOamFrame_65b2c6[] = INCBIN_U16("data/oam_frames/65b2c6.bin");
const u16 sOamFrame_65b2f2[] = INCBIN_U16("data/oam_frames/65b2f2.bin");
const u16 sOamFrame_65b31e[] = INCBIN_U16("data/oam_frames/65b31e.bin");
const u16 sOamFrame_65b34a[] = INCBIN_U16("data/oam_frames/65b34a.bin");
const u16 sOamFrame_65b36a[] = INCBIN_U16("data/oam_frames/65b36a.bin");
const u16 sOamFrame_65b38a[] = INCBIN_U16("data/oam_frames/65b38a.bin");
const u16 sOamFrame_65b3b0[] = INCBIN_U16("data/oam_frames/65b3b0.bin");
const u16 sOamFrame_65b3d6[] = INCBIN_U16("data/oam_frames/65b3d6.bin");
const u16 sOamFrame_65b402[] = INCBIN_U16("data/oam_frames/65b402.bin");
const u16 sOamFrame_65b428[] = INCBIN_U16("data/oam_frames/65b428.bin");
const u16 sOamFrame_65b45a[] = INCBIN_U16("data/oam_frames/65b45a.bin");
const u16 sOamFrame_65b48c[] = INCBIN_U16("data/oam_frames/65b48c.bin");
const u16 sOamFrame_65b4be[] = INCBIN_U16("data/oam_frames/65b4be.bin");
const u16 sOamFrame_65b4f0[] = INCBIN_U16("data/oam_frames/65b4f0.bin");
const u16 sOamFrame_65b510[] = INCBIN_U16("data/oam_frames/65b510.bin");
const u16 sOamFrame_65b530[] = INCBIN_U16("data/oam_frames/65b530.bin");
const u16 sOamFrame_65b556[] = INCBIN_U16("data/oam_frames/65b556.bin");
const u16 sOamFrame_65b57c[] = INCBIN_U16("data/oam_frames/65b57c.bin");
const u16 sOamFrame_65b5a8[] = INCBIN_U16("data/oam_frames/65b5a8.bin");
const u16 sOamFrame_65b5d4[] = INCBIN_U16("data/oam_frames/65b5d4.bin");
const u16 sOamFrame_65b600[] = INCBIN_U16("data/oam_frames/65b600.bin");
const u16 sOamFrame_65b62c[] = INCBIN_U16("data/oam_frames/65b62c.bin");
const u16 sOamFrame_65b658[] = INCBIN_U16("data/oam_frames/65b658.bin");
const u16 sOamFrame_65b684[] = INCBIN_U16("data/oam_frames/65b684.bin");
const u16 sOamFrame_65b6a4[] = INCBIN_U16("data/oam_frames/65b6a4.bin");
const u16 sOamFrame_65b6c4[] = INCBIN_U16("data/oam_frames/65b6c4.bin");
const u16 sOamFrame_65b6ea[] = INCBIN_U16("data/oam_frames/65b6ea.bin");
const u16 sOamFrame_65b710[] = INCBIN_U16("data/oam_frames/65b710.bin");
const u16 sOamFrame_65b73c[] = INCBIN_U16("data/oam_frames/65b73c.bin");
const u16 sOamFrame_65b768[] = INCBIN_U16("data/oam_frames/65b768.bin");
const u16 sOamFrame_65b794[] = INCBIN_U16("data/oam_frames/65b794.bin");
const u16 sOamFrame_65b7c0[] = INCBIN_U16("data/oam_frames/65b7c0.bin");
const u16 sOamFrame_65b7ec[] = INCBIN_U16("data/oam_frames/65b7ec.bin");
const u16 sOamFrame_65b80c[] = INCBIN_U16("data/oam_frames/65b80c.bin");
const u16 sOamFrame_65b832[] = INCBIN_U16("data/oam_frames/65b832.bin");
const u16 sOamFrame_65b85e[] = INCBIN_U16("data/oam_frames/65b85e.bin");
const u16 sOamFrame_65b884[] = INCBIN_U16("data/oam_frames/65b884.bin");
const u16 sOamFrame_65b8b0[] = INCBIN_U16("data/oam_frames/65b8b0.bin");
const u16 sOamFrame_65b8dc[] = INCBIN_U16("data/oam_frames/65b8dc.bin");
const u16 sOamFrame_65b908[] = INCBIN_U16("data/oam_frames/65b908.bin");
const u16 sOamFrame_65b934[] = INCBIN_U16("data/oam_frames/65b934.bin");
const u16 sOamFrame_65b960[] = INCBIN_U16("data/oam_frames/65b960.bin");
const u16 sOamFrame_65b986[] = INCBIN_U16("data/oam_frames/65b986.bin");
const u16 sOamFrame_65b9ac[] = INCBIN_U16("data/oam_frames/65b9ac.bin");
const u16 sOamFrame_65b9d8[] = INCBIN_U16("data/oam_frames/65b9d8.bin");
const u16 sOamFrame_65ba04[] = INCBIN_U16("data/oam_frames/65ba04.bin");
const u16 sOamFrame_65ba30[] = INCBIN_U16("data/oam_frames/65ba30.bin");
const u16 sOamFrame_65ba5c[] = INCBIN_U16("data/oam_frames/65ba5c.bin");
const u16 sOamFrame_65ba88[] = INCBIN_U16("data/oam_frames/65ba88.bin");
const u16 sOamFrame_65baa8[] = INCBIN_U16("data/oam_frames/65baa8.bin");
const u16 sOamFrame_65bac8[] = INCBIN_U16("data/oam_frames/65bac8.bin");
const u16 sOamFrame_65baee[] = INCBIN_U16("data/oam_frames/65baee.bin");
const u16 sOamFrame_65bb0e[] = INCBIN_U16("data/oam_frames/65bb0e.bin");
const u16 sOamFrame_65bb2e[] = INCBIN_U16("data/oam_frames/65bb2e.bin");
// FrameData arrays of the ship alert
const struct FrameData sIntroShipAlertTimeAndDistanceOam[57] = {
    { sOamFrame_65bb2e, 80 },
    { sOamFrame_65a1d4, 1 },
    { sOamFrame_65a1e8, 1 },
    { sOamFrame_65a202, 1 },
    { sOamFrame_65a21c, 1 },
    { sOamFrame_65a23c, 1 },
    { sOamFrame_65a25c, 1 },
    { sOamFrame_65a27c, 1 },
    { sOamFrame_65a29c, 1 },
    { sOamFrame_65a2bc, 1 },
    { sOamFrame_65a2dc, 1 },
    { sOamFrame_65a2fc, 1 },
    { sOamFrame_65a328, 1 },
    { sOamFrame_65a354, 1 },
    { sOamFrame_65a380, 1 },
    { sOamFrame_65a3ac, 1 },
    { sOamFrame_65a3d8, 1 },
    { sOamFrame_65a404, 1 },
    { sOamFrame_65a430, 1 },
    { sOamFrame_65a462, 1 },
    { sOamFrame_65a49a, 1 },
    { sOamFrame_65a4d2, 1 },
    { sOamFrame_65a50a, 1 },
    { sOamFrame_65a542, 1 },
    { sOamFrame_65a57a, 1 },
    { sOamFrame_65a5b2, 1 },
    { sOamFrame_65a5f0, 1 },
    { sOamFrame_65a634, 1 },
    { sOamFrame_65a678, 1 },
    { sOamFrame_65a6bc, 1 },
    { sOamFrame_65a700, 1 },
    { sOamFrame_65a744, 1 },
    { sOamFrame_65a788, 1 },
    { sOamFrame_65a7cc, 1 },
    { sOamFrame_65a816, 1 },
    { sOamFrame_65a866, 1 },
    { sOamFrame_65a8b6, 1 },
    { sOamFrame_65a906, 1 },
    { sOamFrame_65a956, 10 },
    { sOamFrame_65bb2e, 10 },
    { sOamFrame_65a956, 10 },
    { sOamFrame_65bb2e, 10 },
    { sOamFrame_65a956, 10 },
    { sOamFrame_65bb2e, 10 },
    { sOamFrame_65a9a6, 1 },
    { sOamFrame_65a9fc, 1 },
    { sOamFrame_65aa58, 1 },
    { sOamFrame_65aaba, 1 },
    { sOamFrame_65ab22, 1 },
    { sOamFrame_65ab90, 1 },
    { sOamFrame_65abf2, 10 },
    { sOamFrame_65ac60, 6 },
    { sOamFrame_65ace6, 240 },
    { sOamFrame_65ace6, 240 },
    { sOamFrame_65ace6, 240 },
    { sOamFrame_65ace6, 240 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroShipAlertOam_65bd00[9] = {
    { sOamFrame_659bf0, 8 },
    { sOamFrame_659c34, 8 },
    { sOamFrame_659c72, 8 },
    { sOamFrame_659cb6, 8 },
    { sOamFrame_659cfa, 8 },
    { sOamFrame_659d38, 8 },
    { sOamFrame_659d76, 8 },
    { sOamFrame_659da8, 8 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroShipAlertOam_65bd48[3] = {
    { sOamFrame_659ba4, 30 },
    { sOamFrame_659bd0, 30 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroShipAlertAsteroidsPopUpOam[20] = {
    { sOamFrame_65bb2e, 60 },
    { sOamFrame_659de0, 3 },
    { sOamFrame_659de8, 3 },
    { sOamFrame_659df0, 3 },
    { sOamFrame_659df8, 2 },
    { sOamFrame_659e00, 2 },
    { sOamFrame_659e08, 2 },
    { sOamFrame_659e10, 20 },
    { sOamFrame_659e18, 2 },
    { sOamFrame_659e32, 2 },
    { sOamFrame_659e5e, 2 },
    { sOamFrame_659e90, 2 },
    { sOamFrame_659ec8, 2 },
    { sOamFrame_659f1e, 2 },
    { sOamFrame_659f86, 2 },
    { sOamFrame_659ff4, 240 },
    { sOamFrame_659ff4, 240 },
    { sOamFrame_659ff4, 240 },
    { sOamFrame_659ff4, 240 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroShipAlertOam_65be00[34] = {
    { sOamFrame_65bb2e, 114 },
    { sOamFrame_65bb0e, 3 },
    { sOamFrame_65baee, 3 },
    { sOamFrame_65bac8, 3 },
    { sOamFrame_65baa8, 3 },
    { sOamFrame_65ba88, 3 },
    { sOamFrame_65ba5c, 3 },
    { sOamFrame_65ba30, 3 },
    { sOamFrame_65ba04, 3 },
    { sOamFrame_65b9d8, 3 },
    { sOamFrame_65b9ac, 3 },
    { sOamFrame_65b986, 3 },
    { sOamFrame_65b960, 3 },
    { sOamFrame_65b934, 3 },
    { sOamFrame_65b908, 3 },
    { sOamFrame_65b8dc, 3 },
    { sOamFrame_65b8b0, 3 },
    { sOamFrame_65b884, 3 },
    { sOamFrame_65b85e, 3 },
    { sOamFrame_65b832, 3 },
    { sOamFrame_65b80c, 3 },
    { sOamFrame_65b7ec, 3 },
    { sOamFrame_65b7c0, 3 },
    { sOamFrame_65b794, 3 },
    { sOamFrame_65b768, 3 },
    { sOamFrame_65b73c, 3 },
    { sOamFrame_65b710, 3 },
    { sOamFrame_65b6ea, 3 },
    { sOamFrame_65b6c4, 3 },
    { sOamFrame_65b6a4, 3 },
    { sOamFrame_65b684, 3 },
    { sOamFrame_65b658, 3 },
    { sOamFrame_65b62c, 3 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroShipAlertBigNumberOam_65bf10[56] = {
    { sOamFrame_65b600, 3 },
    { sOamFrame_65b5d4, 3 },
    { sOamFrame_65b5a8, 3 },
    { sOamFrame_65b57c, 3 },
    { sOamFrame_65b556, 3 },
    { sOamFrame_65b530, 3 },
    { sOamFrame_65b510, 3 },
    { sOamFrame_65b4f0, 3 },
    { sOamFrame_65b4be, 3 },
    { sOamFrame_65b48c, 3 },
    { sOamFrame_65b45a, 3 },
    { sOamFrame_65b428, 3 },
    { sOamFrame_65b402, 3 },
    { sOamFrame_65b3d6, 3 },
    { sOamFrame_65b3b0, 3 },
    { sOamFrame_65b38a, 3 },
    { sOamFrame_65b36a, 3 },
    { sOamFrame_65b34a, 3 },
    { sOamFrame_65b31e, 3 },
    { sOamFrame_65b2f2, 3 },
    { sOamFrame_65b2c6, 3 },
    { sOamFrame_65b29a, 3 },
    { sOamFrame_65b26e, 3 },
    { sOamFrame_65b248, 3 },
    { sOamFrame_65b222, 3 },
    { sOamFrame_65b202, 3 },
    { sOamFrame_65b1e2, 3 },
    { sOamFrame_65b1bc, 3 },
    { sOamFrame_65b196, 3 },
    { sOamFrame_65b170, 3 },
    { sOamFrame_65b14a, 3 },
    { sOamFrame_65b124, 3 },
    { sOamFrame_65b104, 3 },
    { sOamFrame_65b0e4, 3 },
    { sOamFrame_65b0b2, 3 },
    { sOamFrame_65b080, 3 },
    { sOamFrame_65b04e, 3 },
    { sOamFrame_65b01c, 3 },
    { sOamFrame_65aff6, 3 },
    { sOamFrame_65afca, 3 },
    { sOamFrame_65afa4, 3 },
    { sOamFrame_65af7e, 3 },
    { sOamFrame_65af5e, 3 },
    { sOamFrame_65af3e, 3 },
    { sOamFrame_65af12, 3 },
    { sOamFrame_65aee6, 3 },
    { sOamFrame_65aeba, 3 },
    { sOamFrame_65ae8e, 3 },
    { sOamFrame_65ae62, 3 },
    { sOamFrame_65ae3c, 3 },
    { sOamFrame_65ae16, 3 },
    { sOamFrame_65adf6, 3 },
    { sOamFrame_65add6, 3 },
    { sOamFrame_65adaa, 3 },
    { sOamFrame_65ad7e, 3 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroShipAlertBigNumberOam_65c0d0[11] = {
    { sOamFrame_65a080, 1 },
    { sOamFrame_65a09a, 1 },
    { sOamFrame_65a0b4, 1 },
    { sOamFrame_65a0ce, 1 },
    { sOamFrame_65a0e8, 1 },
    { sOamFrame_65a102, 1 },
    { sOamFrame_65a11c, 1 },
    { sOamFrame_65a136, 1 },
    { sOamFrame_65a150, 1 },
    { sOamFrame_65a16a, 1 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroShipAlertBigNumberOam_65c128[11] = {
    { sOamFrame_65a1ac, 8 },
    { sOamFrame_65a1a4, 8 },
    { sOamFrame_65a19c, 8 },
    { sOamFrame_65a194, 8 },
    { sOamFrame_65a18c, 8 },
    { sOamFrame_65a184, 8 },
    { sOamFrame_65a1cc, 8 },
    { sOamFrame_65a1c4, 8 },
    { sOamFrame_65a1bc, 8 },
    { sOamFrame_65a1b4, 8 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroShipAlertBigNumberOam_65c180[11] = {
    { sOamFrame_65a1cc, 80 },
    { sOamFrame_65a1c4, 80 },
    { sOamFrame_65a1bc, 80 },
    { sOamFrame_65a1b4, 80 },
    { sOamFrame_65a1ac, 80 },
    { sOamFrame_65a1a4, 80 },
    { sOamFrame_65a19c, 80 },
    { sOamFrame_65a194, 80 },
    { sOamFrame_65a18c, 80 },
    { sOamFrame_65a184, 80 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroShipAlertBigNumberOam_65c1d8[11] = {
    { sOamFrame_65a1b4, 60 },
    { sOamFrame_65a1ac, 60 },
    { sOamFrame_65a1a4, 60 },
    { sOamFrame_65a19c, 60 },
    { sOamFrame_65a194, 60 },
    { sOamFrame_65a18c, 60 },
    { sOamFrame_65a184, 60 },
    { sOamFrame_65a1cc, 60 },
    { sOamFrame_65a1c4, 60 },
    { sOamFrame_65a1bc, 60 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sIntroShipAlertBigNumberOam_65c230[7] = {
    { sOamFrame_65a1a4, 200 },
    { sOamFrame_65a1a4, 200 },
    { sOamFrame_65a1a4, 200 },
    { sOamFrame_65a19c, 200 },
    { sOamFrame_65a19c, 200 },
    { sOamFrame_65a19c, 200 },
    FRAME_DATA_TERMINATOR
};
const u16 sIntroShipAlertObjPal[16 * PAL_ROW] = INCBIN_U16("data/new_file_intro/ship_alert_obj.pal");
// Elevator monologue graphics, palettes and tilemaps (the sElevatorMonologue*Pointers tables)
const u8 sElevatorMonologueBgGfx_65c468[] = INCBIN_U8("data/cutscenes/elevator_monologue/bg_65c468.gfx.lz");
// LZ77 compressed graphics of the monologue cursor (decompressed to the last 0x400 bytes of OBJ
// VRAM)
const u8 sCutsceneMonologueCursorGfx[] = INCBIN_U8("data/cutscenes/monologue/cursor.gfx.lz");
const u8 sElevatorMonologueObjGfx_65fc24[] = INCBIN_U8("data/cutscenes/elevator_monologue/obj_65fc24.gfx.lz");

const u32 sIntroTilemap_662804[318] = INCBIN_U32("data/new_file_intro/662804.tm.lz");

const u8 sElevatorMonologueBgTilemap_662cfc[] = INCBIN_U8("data/cutscenes/elevator_monologue/bg_662cfc.tm.lz");
const u32 sCutsceneElevatorMonologueBg1Tilemap[66] = INCBIN_U32("data/cutscenes/elevator_monologue/bg1.tm.lz");
// The monologue inits copy 16 rows from here, the last 4 rows come from sIntroPal_663820
const u16 sCutsceneMonologueBgPal[12 * PAL_ROW] = INCBIN_U16("data/cutscenes/monologue/bg.pal");

const u16 sIntroPal_663820[4 * PAL_ROW] = INCBIN_U16("data/new_file_intro/663820.pal");

const u16 sCutsceneMonologueCursorPal[1 * PAL_ROW] = INCBIN_U16("data/cutscenes/monologue/cursor.pal");
// Elevator monologue palettes, then the OAM frames of the FrameData arrays below
const u16 sElevatorMonologueBgPal_6638c0[] = INCBIN_U16("data/cutscenes/elevator_monologue/bg_6638c0.pal");
const u16 sElevatorMonologueObjPal_663a20[] = INCBIN_U16("data/cutscenes/elevator_monologue/obj_663a20.pal");
const u16 sOamFrame_663ae0[] = INCBIN_U16("data/oam_frames/663ae0.bin");
const u16 sOamFrame_663c32[] = INCBIN_U16("data/oam_frames/663c32.bin");
const u16 sOamFrame_663d84[] = INCBIN_U16("data/oam_frames/663d84.bin");
const struct FrameData sElevatorMonologueOam_663dd0[5] = {
    { sOamFrame_663ae0, 120 },
    { sOamFrame_663c32, 4 },
    { sOamFrame_663ae0, 4 },
    { sOamFrame_663c32, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sElevatorMonologueOam_663df8[2] = {
    { sOamFrame_663d84, 255 },
    FRAME_DATA_TERMINATOR
};
const u16 sOamFrame_663e08[] = INCBIN_U16("data/oam_frames/663e08.bin");
const u16 sOamFrame_663e16[] = INCBIN_U16("data/oam_frames/663e16.bin");
const u16 sOamFrame_663e24[] = INCBIN_U16("data/oam_frames/663e24.bin");
const u16 sOamFrame_663e32[] = INCBIN_U16("data/oam_frames/663e32.bin");
const u16 sOamFrame_663e40[] = INCBIN_U16("data/oam_frames/663e40.bin");
const u16 sOamFrame_663e4e[] = INCBIN_U16("data/oam_frames/663e4e.bin");
// FrameData arrays of the monologue cursor and the elevator monologues
const struct FrameData sCutsceneMonologueCursorHiddenOam[3] = {
    { sOamFrame_663e08, 4 },
    { sOamFrame_663e16, 4 },
    FRAME_DATA_TERMINATOR
};
// Starts with the FrameData array of the monologue cursor (next page arrow), much larger than
// that: the rest is not identified (probably the elevator monologue data reached through the
// sElevatorMonologue*Pointers tables)
const struct FrameData sCutsceneMonologueCursorNextPageOam[7] = {
    { sOamFrame_663e24, 6 },
    { sOamFrame_663e32, 6 },
    { sOamFrame_663e40, 6 },
    { sOamFrame_663e4e, 6 },
    { sOamFrame_663e40, 6 },
    { sOamFrame_663e32, 6 },
    FRAME_DATA_TERMINATOR
};
const u8 sElevatorMonologueBgGfx_663eac[] = INCBIN_U8("data/cutscenes/elevator_monologue/bg_663eac.gfx.lz");
const u8 sElevatorMonologueObjGfx_667c18[] = INCBIN_U8("data/cutscenes/elevator_monologue/obj_667c18.gfx.lz");
const u16 sOamFrame_66a764[] = INCBIN_U16("data/oam_frames/66a764.bin");
const u16 sOamFrame_66a8a4[] = INCBIN_U16("data/oam_frames/66a8a4.bin");
const u16 sOamFrame_66a9e4[] = INCBIN_U16("data/oam_frames/66a9e4.bin");
const struct FrameData sElevatorMonologueOam_66aa30[5] = {
    { sOamFrame_66a764, 120 },
    { sOamFrame_66a8a4, 4 },
    { sOamFrame_66a764, 4 },
    { sOamFrame_66a8a4, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sElevatorMonologueOam_66aa58[2] = {
    { sOamFrame_66a9e4, 255 },
    FRAME_DATA_TERMINATOR
};
const u16 sElevatorMonologueBgPal_66aa68[] = INCBIN_U16("data/cutscenes/elevator_monologue/bg_66aa68.pal");
const u16 sElevatorMonologueObjPal_66abc8[] = INCBIN_U16("data/cutscenes/elevator_monologue/obj_66abc8.pal");
const u8 sElevatorMonologueBgTilemap_66ac88[] = INCBIN_U8("data/cutscenes/elevator_monologue/bg_66ac88.tm.lz");
const u8 sElevatorMonologueBgGfx_66b524[] = INCBIN_U8("data/cutscenes/elevator_monologue/bg_66b524.gfx.lz");
const u8 sElevatorMonologueObjGfx_66ec18[] = INCBIN_U8("data/cutscenes/elevator_monologue/obj_66ec18.gfx.lz");
const u16 sOamFrame_671760[] = INCBIN_U16("data/oam_frames/671760.bin");
const u16 sOamFrame_671870[] = INCBIN_U16("data/oam_frames/671870.bin");
const u16 sOamFrame_671980[] = INCBIN_U16("data/oam_frames/671980.bin");
const struct FrameData sElevatorMonologueOam_6719cc[5] = {
    { sOamFrame_671760, 120 },
    { sOamFrame_671870, 4 },
    { sOamFrame_671760, 4 },
    { sOamFrame_671870, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sElevatorMonologueOam_6719f4[2] = {
    { sOamFrame_671980, 255 },
    FRAME_DATA_TERMINATOR
};
const u16 sElevatorMonologueBgPal_671a04[] = INCBIN_U16("data/cutscenes/elevator_monologue/bg_671a04.pal");
const u16 sElevatorMonologueObjPal_671b64[] = INCBIN_U16("data/cutscenes/elevator_monologue/obj_671b64.pal");
const u8 sElevatorMonologueBgTilemap_671c24[] = INCBIN_U8("data/cutscenes/elevator_monologue/bg_671c24.tm.lz");
const u32 sCutsceneFederationMonologueBg2Gfx[2342] = INCBIN_U32("data/cutscenes/federation_monologue/bg2.gfx.lz");
const u16 sCutsceneFederationMonologueBgPal[12 * PAL_ROW] = INCBIN_U16("data/cutscenes/federation_monologue/bg.pal");
const u32 sCutsceneFederationMonologueBg2Tilemap[368] = INCBIN_U32("data/cutscenes/federation_monologue/bg2.tm.lz");
const u32 sCutsceneSecretConversationBgGfx[2551] = INCBIN_U32("data/cutscenes/secret_conversation/bg.gfx.lz");
const u16 sCutsceneSecretConversationBgPal[5 * PAL_ROW] = INCBIN_U16("data/cutscenes/secret_conversation/bg.pal");
const u32 sCutsceneSecretConversationBg1Tilemap[191] = INCBIN_U32("data/cutscenes/secret_conversation/bg1.tm.lz");
const u16 sCutsceneSecretConversationAnimatedPal0[1 * PAL_ROW] = INCBIN_U16("data/cutscenes/secret_conversation/bg_animated_0.pal");
const u16 sCutsceneSecretConversationAnimatedPal1[1 * PAL_ROW] = INCBIN_U16("data/cutscenes/secret_conversation/bg_animated_1.pal");
const u16 sCutsceneSecretConversationAnimatedPal2[1 * PAL_ROW] = INCBIN_U16("data/cutscenes/secret_conversation/bg_animated_2.pal");
const u16 sCutsceneSecretConversationAnimatedPal3[1 * PAL_ROW] = INCBIN_U16("data/cutscenes/secret_conversation/bg_animated_3.pal");
const u32 sCutsceneSecretConversationBg2Tilemap[307] = INCBIN_U32("data/cutscenes/secret_conversation/bg2.tm.lz");
const u32 sCutsceneSecretConversationObjGfx[467] = INCBIN_U32("data/cutscenes/secret_conversation/obj.gfx.lz");
const u16 sCutsceneSecretConversationObjPal[2 * PAL_ROW] = INCBIN_U16("data/cutscenes/secret_conversation/obj.pal");
// OAM frames of the FrameData arrays below
const u16 sOamFrame_6788e8[] = INCBIN_U16("data/oam_frames/6788e8.bin");
const u16 sOamFrame_67890e[] = INCBIN_U16("data/oam_frames/67890e.bin");
const u16 sOamFrame_678982[] = INCBIN_U16("data/oam_frames/678982.bin");
const u16 sOamFrame_6789f6[] = INCBIN_U16("data/oam_frames/6789f6.bin");
const u16 sOamFrame_678a6a[] = INCBIN_U16("data/oam_frames/678a6a.bin");
const u16 sOamFrame_678ad2[] = INCBIN_U16("data/oam_frames/678ad2.bin");
const u16 sOamFrame_678b3a[] = INCBIN_U16("data/oam_frames/678b3a.bin");
const u16 sOamFrame_678b54[] = INCBIN_U16("data/oam_frames/678b54.bin");
const u16 sOamFrame_678b6e[] = INCBIN_U16("data/oam_frames/678b6e.bin");
const u16 sOamFrame_678b88[] = INCBIN_U16("data/oam_frames/678b88.bin");
const u16 sOamFrame_678ba2[] = INCBIN_U16("data/oam_frames/678ba2.bin");
const u16 sOamFrame_678bbc[] = INCBIN_U16("data/oam_frames/678bbc.bin");
const u16 sOamFrame_678bd6[] = INCBIN_U16("data/oam_frames/678bd6.bin");
const u16 sOamFrame_678c20[] = INCBIN_U16("data/oam_frames/678c20.bin");
const u16 sOamFrame_678c6a[] = INCBIN_U16("data/oam_frames/678c6a.bin");
const u16 sOamFrame_678cb4[] = INCBIN_U16("data/oam_frames/678cb4.bin");
const u16 sOamFrame_678d10[] = INCBIN_U16("data/oam_frames/678d10.bin");
const u16 sOamFrame_678d66[] = INCBIN_U16("data/oam_frames/678d66.bin");
const u16 sOamFrame_678dc8[] = INCBIN_U16("data/oam_frames/678dc8.bin");
const u16 sOamFrame_678e42[] = INCBIN_U16("data/oam_frames/678e42.bin");
const u16 sOamFrame_678eec[] = INCBIN_U16("data/oam_frames/678eec.bin");
const u16 sOamFrame_678fc6[] = INCBIN_U16("data/oam_frames/678fc6.bin");
const u16 sOamFrame_67903a[] = INCBIN_U16("data/oam_frames/67903a.bin");
const u16 sOamFrame_6790ae[] = INCBIN_U16("data/oam_frames/6790ae.bin");
const u16 sOamFrame_679122[] = INCBIN_U16("data/oam_frames/679122.bin");
const u16 sOamFrame_679196[] = INCBIN_U16("data/oam_frames/679196.bin");
const u16 sOamFrame_67920a[] = INCBIN_U16("data/oam_frames/67920a.bin");
// FrameData arrays of the secret conversation
const struct FrameData sCutsceneSecretConversationNavigationPanelOam_679280[5] = {
    { sOamFrame_678b88, 16 },
    { sOamFrame_678ba2, 16 },
    { sOamFrame_678bbc, 16 },
    { sOamFrame_678ba2, 16 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneSecretConversationNavigationPanelOam_6792a8[5] = {
    { sOamFrame_678b3a, 16 },
    { sOamFrame_678b54, 16 },
    { sOamFrame_678b6e, 16 },
    { sOamFrame_678b54, 16 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneSecretConversationIncomingDispatchOam_6792d0[16] = {
    { sOamFrame_678c6a, 3 },
    { sOamFrame_678cb4, 3 },
    { sOamFrame_678d10, 2 },
    { sOamFrame_678d66, 1 },
    { sOamFrame_678dc8, 1 },
    { sOamFrame_678e42, 1 },
    { sOamFrame_678eec, 1 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_678eec, 1 },
    { sOamFrame_678e42, 1 },
    { sOamFrame_678dc8, 1 },
    { sOamFrame_678d66, 1 },
    { sOamFrame_678d10, 2 },
    { sOamFrame_678cb4, 3 },
    { sOamFrame_678c6a, 3 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneSecretConversationIncomingDispatchOam_679350[10] = {
    { sOamFrame_678fc6, 8 },
    { sOamFrame_67903a, 8 },
    { sOamFrame_6790ae, 8 },
    { sOamFrame_679122, 8 },
    { sOamFrame_679196, 8 },
    { sOamFrame_67920a, 8 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_678bd6, 8 },
    { sOamFrame_678c20, 8 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneSecretConversationOam_6793a0[2] = {
    { sOamFrame_6788e8, 255 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneSecretConversationOam_6793b0[14] = {
    { sOamFrame_67890e, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_678ad2, 255 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_678982, 4 },
    { sOamFrame_6789f6, 4 },
    { sOamFrame_678a6a, 4 },
    { sOamFrame_678ad2, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_678ad2, 6 },
    { sOamFrame_678a6a, 6 },
    { sOamFrame_6789f6, 6 },
    { sOamFrame_678982, 6 },
    FRAME_DATA_TERMINATOR
};
const u32 sCutsceneBslSpaceBgGfx[4331] = INCBIN_U32("data/cutscenes/bsl_space/bg.gfx.lz");
// LZ77 compressed OBJ graphics of the BSL space view
const u32 sCutsceneBslSpaceObjGfx[3128] = INCBIN_U32("data/cutscenes/bsl_space/obj.gfx.lz");
// OAM frames of the FrameData arrays below
const u16 sOamFrame_6808ac[] = INCBIN_U16("data/oam_frames/6808ac.bin");
const u16 sOamFrame_6808b4[] = INCBIN_U16("data/oam_frames/6808b4.bin");
const u16 sOamFrame_6808bc[] = INCBIN_U16("data/oam_frames/6808bc.bin");
const u16 sOamFrame_6808dc[] = INCBIN_U16("data/oam_frames/6808dc.bin");
const u16 sOamFrame_680914[] = INCBIN_U16("data/oam_frames/680914.bin");
const u16 sOamFrame_68095e[] = INCBIN_U16("data/oam_frames/68095e.bin");
const u16 sOamFrame_6809ae[] = INCBIN_U16("data/oam_frames/6809ae.bin");
const u16 sOamFrame_680a04[] = INCBIN_U16("data/oam_frames/680a04.bin");
const u16 sOamFrame_680a4e[] = INCBIN_U16("data/oam_frames/680a4e.bin");
const u16 sOamFrame_680a86[] = INCBIN_U16("data/oam_frames/680a86.bin");
const u16 sOamFrame_680aa0[] = INCBIN_U16("data/oam_frames/680aa0.bin");
const u16 sOamFrame_680ab4[] = INCBIN_U16("data/oam_frames/680ab4.bin");
const u16 sOamFrame_680aee[] = INCBIN_U16("data/oam_frames/680aee.bin");
const u16 sOamFrame_680b08[] = INCBIN_U16("data/oam_frames/680b08.bin");
const u16 sOamFrame_680b1c[] = INCBIN_U16("data/oam_frames/680b1c.bin");
const u16 sOamFrame_680b24[] = INCBIN_U16("data/oam_frames/680b24.bin");
const u16 sOamFrame_680b2c[] = INCBIN_U16("data/oam_frames/680b2c.bin");
const u16 sOamFrame_680b34[] = INCBIN_U16("data/oam_frames/680b34.bin");
const u16 sOamFrame_680b3c[] = INCBIN_U16("data/oam_frames/680b3c.bin");
const u16 sOamFrame_680b44[] = INCBIN_U16("data/oam_frames/680b44.bin");
const u16 sOamFrame_680b4c[] = INCBIN_U16("data/oam_frames/680b4c.bin");
const u16 sOamFrame_680b54[] = INCBIN_U16("data/oam_frames/680b54.bin");
const u16 sOamFrame_680b5c[] = INCBIN_U16("data/oam_frames/680b5c.bin");
const u16 sOamFrame_680b64[] = INCBIN_U16("data/oam_frames/680b64.bin");
const u16 sOamFrame_680b6c[] = INCBIN_U16("data/oam_frames/680b6c.bin");
const u16 sOamFrame_680b74[] = INCBIN_U16("data/oam_frames/680b74.bin");
const u16 sOamFrame_680b7c[] = INCBIN_U16("data/oam_frames/680b7c.bin");
const u16 sOamFrame_680b84[] = INCBIN_U16("data/oam_frames/680b84.bin");
const u16 sOamFrame_680b8c[] = INCBIN_U16("data/oam_frames/680b8c.bin");
const u16 sOamFrame_680b94[] = INCBIN_U16("data/oam_frames/680b94.bin");
const u16 sOamFrame_680b9c[] = INCBIN_U16("data/oam_frames/680b9c.bin");
const u16 sOamFrame_680ba4[] = INCBIN_U16("data/oam_frames/680ba4.bin");
const u16 sOamFrame_680bac[] = INCBIN_U16("data/oam_frames/680bac.bin");
const u16 sOamFrame_680bb4[] = INCBIN_U16("data/oam_frames/680bb4.bin");
const u16 sOamFrame_680bbc[] = INCBIN_U16("data/oam_frames/680bbc.bin");
const u16 sOamFrame_680bc4[] = INCBIN_U16("data/oam_frames/680bc4.bin");
const u16 sOamFrame_680bcc[] = INCBIN_U16("data/oam_frames/680bcc.bin");
const u16 sOamFrame_680bd4[] = INCBIN_U16("data/oam_frames/680bd4.bin");
const u16 sOamFrame_680bdc[] = INCBIN_U16("data/oam_frames/680bdc.bin");
const u16 sOamFrame_680be4[] = INCBIN_U16("data/oam_frames/680be4.bin");
const u16 sOamFrame_680bec[] = INCBIN_U16("data/oam_frames/680bec.bin");
const u16 sOamFrame_680c92[] = INCBIN_U16("data/oam_frames/680c92.bin");
const u16 sOamFrame_680c9a[] = INCBIN_U16("data/oam_frames/680c9a.bin");
const u16 sOamFrame_680ca2[] = INCBIN_U16("data/oam_frames/680ca2.bin");
const u16 sOamFrame_680caa[] = INCBIN_U16("data/oam_frames/680caa.bin");
const u16 sOamFrame_680cb2[] = INCBIN_U16("data/oam_frames/680cb2.bin");
const u16 sOamFrame_680cba[] = INCBIN_U16("data/oam_frames/680cba.bin");
const u16 sOamFrame_680cc2[] = INCBIN_U16("data/oam_frames/680cc2.bin");
const u16 sOamFrame_680cca[] = INCBIN_U16("data/oam_frames/680cca.bin");
const u16 sOamFrame_680cd2[] = INCBIN_U16("data/oam_frames/680cd2.bin");
const u16 sOamFrame_680cda[] = INCBIN_U16("data/oam_frames/680cda.bin");
const u16 sOamFrame_680ce2[] = INCBIN_U16("data/oam_frames/680ce2.bin");
const u16 sOamFrame_680cea[] = INCBIN_U16("data/oam_frames/680cea.bin");
const u16 sOamFrame_680cf2[] = INCBIN_U16("data/oam_frames/680cf2.bin");
const u16 sOamFrame_680cfa[] = INCBIN_U16("data/oam_frames/680cfa.bin");
const u16 sOamFrame_680d02[] = INCBIN_U16("data/oam_frames/680d02.bin");
const u16 sOamFrame_680d0a[] = INCBIN_U16("data/oam_frames/680d0a.bin");
const u16 sOamFrame_680d12[] = INCBIN_U16("data/oam_frames/680d12.bin");
const u16 sOamFrame_680d1a[] = INCBIN_U16("data/oam_frames/680d1a.bin");
const u16 sOamFrame_680d22[] = INCBIN_U16("data/oam_frames/680d22.bin");
const u16 sOamFrame_680d2a[] = INCBIN_U16("data/oam_frames/680d2a.bin");
const u16 sOamFrame_680d32[] = INCBIN_U16("data/oam_frames/680d32.bin");
// FrameData arrays of the restricted lab detaching and BSL exploding cutscenes
const struct FrameData sCutsceneRestrictedLabDetachingBslPartOam_680d54[2] = {
    { sOamFrame_680aee, 255 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingBslPartOam_680d64[2] = {
    { sOamFrame_680b08, 255 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingBslPartOam_680d74[2] = {
    { sOamFrame_680b1c, 255 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingOam_680d84[2] = {
    { sOamFrame_680b24, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingOam_680d94[2] = {
    { sOamFrame_680b2c, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingOam_680da4[5] = {
    { sOamFrame_680b34, 2 },
    { sOamFrame_680b3c, 2 },
    { sOamFrame_680b44, 2 },
    { sOamFrame_680b4c, 2 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingOam_680dcc[12] = {
    { sOamFrame_680bc4, 8 },
    { sOamFrame_680bd4, 8 },
    { sOamFrame_680bdc, 8 },
    { sOamFrame_680be4, 8 },
    { sOamFrame_680bec, 8 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_680b7c, 4 },
    { sOamFrame_680b84, 4 },
    { sOamFrame_680b8c, 4 },
    { sOamFrame_680b94, 4 },
    { sOamFrame_680b9c, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingOam_680e2c[2] = {
    { sOamFrame_680b54, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingOam_680e3c[18] = {
    { sOamFrame_680b5c, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_680b64, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_680b6c, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_680b74, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_680ba4, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_680bac, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_680bb4, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_680bbc, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_680bcc, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneBslExplodingExplosionsOam[12] = {
    { sOamFrame_6808b4, 4 },
    { sOamFrame_6808bc, 4 },
    { sOamFrame_6808dc, 4 },
    { sOamFrame_680914, 4 },
    { sOamFrame_68095e, 4 },
    { sOamFrame_6809ae, 4 },
    { sOamFrame_680a04, 6 },
    { sOamFrame_680a4e, 7 },
    { sOamFrame_680a86, 8 },
    { sOamFrame_680aa0, 9 },
    { sOamFrame_680ab4, 10 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingFallingLabOam[9] = {
    { sOamFrame_6808ac, 4 },
    FRAME_DATA_TERMINATOR,
    { sOamFrame_680c92, 5 },
    { sOamFrame_680c9a, 5 },
    { sOamFrame_680ca2, 5 },
    { sOamFrame_680caa, 5 },
    { sOamFrame_680cb2, 5 },
    { sOamFrame_680cba, 5 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingOam_680f74[5] = {
    { sOamFrame_680cc2, 4 },
    { sOamFrame_680cca, 4 },
    { sOamFrame_680cd2, 4 },
    { sOamFrame_680cda, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingOam_680f9c[5] = {
    { sOamFrame_680ce2, 4 },
    { sOamFrame_680cea, 4 },
    { sOamFrame_680cf2, 4 },
    { sOamFrame_680cfa, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingOam_680fc4[5] = {
    { sOamFrame_680d02, 4 },
    { sOamFrame_680d0a, 4 },
    { sOamFrame_680d12, 4 },
    { sOamFrame_680d1a, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneRestrictedLabDetachingOam_680fec[2] = {
    { sOamFrame_680d22, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneBslExplodingOam_680ffc[2] = {
    { sOamFrame_680d32, 4 },
    FRAME_DATA_TERMINATOR
};
const struct FrameData sCutsceneBslExplodingBslFarOam[2] = {
    { sOamFrame_680d2a, 4 },
    FRAME_DATA_TERMINATOR
};
const u16 sCutsceneBslSpaceBgFadePal[16 * PAL_ROW] = INCBIN_U16("data/cutscenes/bsl_space/bg_fade.pal");
const u16 sCutsceneBslSpaceObjPal[16 * PAL_ROW] = INCBIN_U16("data/cutscenes/bsl_space/obj.pal");
const u16 sCutsceneRestrictedLabDetachingObjRow0CyclePal[16 * PAL_ROW] = INCBIN_U16("data/cutscenes/restricted_lab_detaching/obj_row0_cycle.pal");
const u16 sCutsceneRestrictedLabDetachingObjRow1CyclePal[16 * PAL_ROW] = INCBIN_U16("data/cutscenes/restricted_lab_detaching/obj_row1_cycle.pal");
const u16 sCutsceneRestrictedLabDetachingObjRow3CyclePal[16 * PAL_ROW] = INCBIN_U16("data/cutscenes/restricted_lab_detaching/obj_row3_cycle.pal");
const u32 sCutsceneBslSpaceTilemap_681a1c[418] = INCBIN_U32("data/cutscenes/bsl_space/681a1c.tm.lz");
const u32 sCutsceneBslSpaceTilemap_6820a4[318] = INCBIN_U32("data/cutscenes/bsl_space/6820a4.tm.lz");
const u16 sCutsceneBslSpaceBgPal[16 * PAL_ROW] = INCBIN_U16("data/cutscenes/bsl_space/bg.pal");
// Width in tiles of an OAM sprite, by [shape][size]
const u8 sCutsceneOamTileWidths[3][4] = INCBIN_U8("data/cutscenes/oam_tile_widths.bin");
const u32 sCutsceneBslExplodingBg2Tilemap[277] = INCBIN_U32("data/cutscenes/bsl_exploding/bg2.tm.lz");
const u32 sCutsceneBslExplodingBg3Tilemap[236] = INCBIN_U32("data/cutscenes/bsl_exploding/bg3.tm.lz");
