#ifndef ROOM_STRUCTS_H
#define ROOM_STRUCTS_H

#include "types.h"
#include "oam.h"

#include "constants/connection.h"

#define ROOM_SPRITE_DATA_TERMINATOR UCHAR_MAX, UCHAR_MAX, UCHAR_MAX

struct TilesetTransparentColor {
    u16 transparentColor;
    // Color the gradient of HazeCalculateTransparentColorGradient was computed for
    u16 gradientBaseColor;
    u16 previousTransparentColor; // Copy of transparentColor made by HazeCalculateTransparentColorGradient, written but never read in the final game
};

extern struct TilesetTransparentColor gTilesetTransparentColor;

struct RoomEntry {
    u8 tilesetNumber;
    u8 bg0Prop;
    u8 bg1Prop;
    u8 bg2Prop;
    u8 bg3Prop;
    u8 scrollsFlag;
    u8 bg3Scroll;
    u8 transparency;
    const u8* pEnemyRoomData;
    u8 firstSpritesetEvent;
    u8 secondSpritesetEvent;
    u8 mapX;
    u8 mapY;
    u8 visualEffect;
    u16 effectY;
    u8 damagingEffect;
    u16 musicTrack;
    u8 bg0Size;
    u8 bg3Size;
    u8 animatedTileset;
    u8 animatedPalette;
};

extern struct RoomEntry gCurrentRoomEntry;

struct ScreenBlockPadding {
    u16 right;
    u16 left;
    u16 top;
    u16 bottom;
};

extern struct ScreenBlockPadding gScreenBlockPadding;

struct Bg3Movement {
    u8 direction;
    u8 timer;
    u8 leftToRightStage;
    u16 xOffset;
};

extern struct Bg3Movement gBg3Movement;

struct Bg0Movement {
    u8 type;
    u8 counter;
    u16 unused;
    u16 xOffset;
    u16 yOffset;
};

extern struct Bg0Movement gBg0Movement;

struct HorizontalTilemap {
    u8 tileCount;
    u16 blockX;
    u16 blockY;
    u16 tiles[56]; // ((SCREEN_SIZE_Y / PIXEL_PER_BLOCK) + 4) * 4
};

extern struct HorizontalTilemap gHorizontalTilemap[3];

struct VerticalTilemap {
    u8 tileCount;
    u16 blockX;
    u16 blockY;
    u16 tiles[76]; // ((SCREEN_SIZE_X / PIXEL_PER_BLOCK) + 4) * 4
};

extern struct VerticalTilemap gVerticalTilemap[3];

struct TilesetEntry {
    const u32* pTileGraphics;
    const u16* pPalette;
    const u32* pBackgroundGraphics;
    const u8* pTilemap;
    u8 animatedTileset;
    u8 animatedPalette;
};

struct RoomEntryRom {
    u8 tileset;
    u8 bg0Prop;
    u8 bg1Prop;
    u8 bg2Prop;
    u8 bg3Prop;
    const u8* pBg0Data;
    const u8* pBg1Data;
    const u8* pBg2Data;
    const u8* pClipData;
    const u32* pBg3Data;
    u8 bg3Scrolling;
    u8 transparency;
    const u8* pDefaultSpriteData;
    u8 defaultSpriteset;
    u8 firstSpritesetEvent;
    const u8* pFirstSpriteData;
    u8 firstSpriteset;
    u8 secondSpritesetEvent;
    const u8* pSecondSpriteData;
    u8 secondSpriteset;
    u8 mapX;
    u8 mapY;
    u8 effect;
    u8 effectY;
    u16 musicTrack;
};

extern const struct RoomEntryRom* sAreaRoomEntryPointers[AREA_END];

extern u16 gDecompClipdataMap[1024];
extern u16 gDecompBg0Map[6144];
extern u16 gDecompBg1Map[6144];
extern u16 gDecompBg2Map[6144];
extern u16 gDecompBg3Map[2048];

extern u8 gSpritesetEntryUsed;
extern u8 gScrollCounter;

// Movement of an object drawn on BG0: Nightmare's shadow (ScrollNightmareShadow) and SR388 (ScrollSr388Planet)
struct Bg0ObjectMovement {
    u8 stage;
    // Stage of the previous pass (5 = to the left, 6 = to the right), 0 after two passes
    u8 previousPass;
    // Keep passing forever (the shadow stops after two passes the first time)
    u8 keepPassing;
    u8 passCount;
    // Index in sNightmareShadowPositions
    u8 positionIndex;
    s8 yVelocityOffset;
    u16 timer;
};

extern struct Bg0ObjectMovement gBg0ObjectMovement;

struct WaterMovement {
    u8 moving;
    u8 loopTimer;
    u8 stage;
    s16 yOffset;
    u16 unk_6;
    // How much the water was drained (electrified water event)
    s16 drainOffset;
};

extern struct WaterMovement gWaterMovement;

#endif /* ROOM_STRUCTS_H */
