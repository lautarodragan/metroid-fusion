#include "lagmeter.h"

#ifdef LAGMETER

#include "gba.h"
#include "globals.h"
#include "io.h"
#include "oam.h"

#include "data/sprite_pointers.h"
#include "structs/connection.h"

/*
 * See include/lagmeter.h. Everything here runs once per logic frame, outside the game's own
 * code: LagMeterStartFrame at the start of the main loop, LagMeterEndFrame right before the
 * V-blank wait. With the counter hidden (L+R+SELECT) the cost is about a hundred cycles per
 * frame; with it shown, a few hundred more (one of its 8 tiles is checked and rewritten per
 * frame, 2 OAM entries).
 */

#define FRAME_CYCLES 280896

// Font: 4x8 cells (3x5 glyphs with a shadow), one u16 of 4 pixels (4 bits each) per row
#define CHAR_SPACE 10
#define CHAR_SLASH 11
#define CHAR_PERCENT 12

static const u16 sLagMeterFont[13][8] = {
    { 0x0000, 0x0111, 0xE1E1, 0xE1E1, 0xE1E1, 0xE111, 0xEEE0, 0x0000 }, // '0'
    { 0x0000, 0x0010, 0x0E11, 0x0E10, 0x0E10, 0x0111, 0xEEE0, 0x0000 }, // '1'
    { 0x0000, 0x0111, 0xE1E0, 0xE111, 0xEEE1, 0x0111, 0xEEE0, 0x0000 }, // '2'
    { 0x0000, 0x0111, 0xE1E0, 0xE110, 0xE100, 0xE111, 0xEEE0, 0x0000 }, // '3'
    { 0x0000, 0x0101, 0xE1E1, 0xE111, 0xE1E0, 0xE100, 0xE000, 0x0000 }, // '4'
    { 0x0000, 0x0111, 0xEEE1, 0x0111, 0xE1E0, 0xE111, 0xEEE0, 0x0000 }, // '5'
    { 0x0000, 0x0111, 0xEEE1, 0x0111, 0xE1E1, 0xE111, 0xEEE0, 0x0000 }, // '6'
    { 0x0000, 0x0111, 0xE1E0, 0xE100, 0xE010, 0x0E10, 0x0E00, 0x0000 }, // '7'
    { 0x0000, 0x0111, 0xE1E1, 0xE111, 0xE1E1, 0xE111, 0xEEE0, 0x0000 }, // '8'
    { 0x0000, 0x0111, 0xE1E1, 0xE111, 0xE1E0, 0xE111, 0xEEE0, 0x0000 }, // '9'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, // ' '
    { 0x0000, 0x0100, 0xE100, 0xE010, 0x0E01, 0x00E1, 0x00E0, 0x0000 }, // '/'
    { 0x0000, 0x0101, 0xE1E0, 0xE010, 0x0E01, 0x01E1, 0xE0E0, 0x0000 }, // '%'
};

// First record of each area (rooms per area: 87, 54, 61, 39, 48, 52, 41, 4, 4, 4)
static const u16 sLagMeterAreaFirstRecord[LAGMETER_AREAS + 1] = {
    0, 87, 141, 202, 241, 289, 341, 382, 386, 390, 394
};

// The counter uses the last 8 tiles of OBJ VRAM (the end of graphics slot 7, which holds the
// debug sprite graphics in most rooms; the area banner, the escape timer and a few spritesets
// use it too, and the counter is hidden while they do)
#define LAGMETER_TILE 0x3F8
#define LAGMETER_VRAM ((vu32*)(VRAM_OBJ + LAGMETER_TILE * 32))
#define LAGMETER_X 2
#define LAGMETER_Y 150
#define LAGMETER_PALETTE 3 // HUD palette: color 1 is white, color 14 dark blue

#define LAGMETER_TOGGLE (KEY_L | KEY_R | KEY_SELECT)

// SRAM is 8 bits wide: byte accesses only
static u32 SramRead(u32 offset, u32 size)
{
    vu8* src;
    u32 value;
    u32 i;

    src = (vu8*)SRAM_BASE + offset;
    value = 0;
    for (i = 0; i < size; i++)
        value |= src[i] << (i * 8);

    return value;
}

static void SramStore(u32 offset, u32 value, u32 size)
{
    vu8* dst;
    u32 i;

    dst = (vu8*)SRAM_BASE + offset;
    for (i = 0; i < size; i++)
        dst[i] = value >> (i * 8);
}

#define HEADER(field) (LAGMETER_SRAM_HEADER + OFFSET_OF(struct LagMeterSramHeader, field))
#define HEADER_SIZE(field) (sizeof(((struct LagMeterSramHeader*)0)->field))
#define HEADER_READ(field) SramRead(HEADER(field), HEADER_SIZE(field))
#define HEADER_WRITE(field, value) SramStore(HEADER(field), value, HEADER_SIZE(field))

static u32 RecordOffset(u32 index)
{
    if (index < LAGMETER_SRAM_RECORDS_A_COUNT)
        return LAGMETER_SRAM_RECORDS_A + index * LAGMETER_RECORD_SIZE;
    else
        return LAGMETER_SRAM_RECORDS_B + (index - LAGMETER_SRAM_RECORDS_A_COUNT) * LAGMETER_RECORD_SIZE;
}

/**
 * @brief Checks the log in SRAM, starts a new one if there is none
 *
 */
static void LagMeterCheckSram(void)
{
    u32 i;

    if (HEADER_READ(magic) == LAGMETER_MAGIC && HEADER_READ(version) == LAGMETER_VERSION &&
        HEADER_READ(records) == LAGMETER_RECORDS)
        return;

    for (i = 0; i < sizeof(struct LagMeterSramHeader); i++)
        SramStore(LAGMETER_SRAM_HEADER + i, 0, 1);
    for (i = 0; i < LAGMETER_RECORDS; i++)
    {
        SramStore(RecordOffset(i), 0, 4);
        SramStore(RecordOffset(i) + 4, 0, 2);
    }

    HEADER_WRITE(version, LAGMETER_VERSION);
    HEADER_WRITE(areas, LAGMETER_AREAS);
    HEADER_WRITE(records, LAGMETER_RECORDS);
    HEADER_WRITE(magic, LAGMETER_MAGIC);
}

static u32 LoadPercent(u32 cycles)
{
    // cycles * 100 / FRAME_CYCLES without a division (5973 / 2^24 = 100 / 280896 within 0.01%)
    if (cycles >= FRAME_CYCLES * 255 / 100)
        return 255;
    return (cycles * 5973) >> 24;
}

static u32 AddSaturate16(u32 a, u32 b)
{
    a += b;
    return a > USHORT_MAX ? USHORT_MAX : a;
}

/**
 * @brief Adds the totals of the room being tracked (and of the other modes) to the log in SRAM
 *
 */
static void LagMeterFlush(void)
{
    struct LagMeter* lm;
    u32 offset;
    u32 load;
    u32 index;

    lm = &gLagMeter;
    LagMeterCheckSram();

    load = LoadPercent(lm->roomMaxCycles);

    if (lm->tracking && lm->area < LAGMETER_AREAS)
    {
        index = sLagMeterAreaFirstRecord[lm->area] + lm->room;
        if (index < sLagMeterAreaFirstRecord[lm->area + 1])
        {
            offset = RecordOffset(index);
            SramStore(offset + 0, AddSaturate16(SramRead(offset + 0, 2), lm->roomLag), 2);
            SramStore(offset + 2, AddSaturate16(SramRead(offset + 2, 2),
                (lm->roomLogic + (1 << (LAGMETER_FRAME_UNIT_SHIFT - 1))) >> LAGMETER_FRAME_UNIT_SHIFT), 2);
            if (lm->roomWorstStreak > SramRead(offset + 4, 1))
                SramStore(offset + 4, lm->roomWorstStreak, 1);
            if (load > SramRead(offset + 5, 1))
                SramStore(offset + 5, load, 1);
        }
    }

    if (lm->tracking)
    {
        HEADER_WRITE(playLogicFrames, HEADER_READ(playLogicFrames) + lm->roomLogic);
        HEADER_WRITE(playLagFrames, HEADER_READ(playLagFrames) + lm->roomLag);
        HEADER_WRITE(playLaggingFrames, HEADER_READ(playLaggingFrames) + lm->roomLagging);
        if (lm->roomWorstStreak > HEADER_READ(worstStreak))
            HEADER_WRITE(worstStreak, lm->roomWorstStreak);
        if (load > HEADER_READ(maxLoad))
            HEADER_WRITE(maxLoad, load);
    }

    HEADER_WRITE(otherLogicFrames, HEADER_READ(otherLogicFrames) + lm->pendingOtherLogic);
    HEADER_WRITE(otherLagFrames, HEADER_READ(otherLagFrames) + lm->pendingOtherLag);
    lm->pendingOtherLogic = 0;
    lm->pendingOtherLag = 0;

    lm->roomLogic = 0;
    lm->roomLag = 0;
    lm->roomLagging = 0;
    lm->roomMaxCycles = 0;
    lm->roomWorstStreak = 0;
    lm->streak = 0;
    lm->totalLag = HEADER_READ(playLagFrames);
}

/**
 * @brief Starts the cycle counter, reads the log (InitializeGame)
 *
 */
void LagMeterInit(void)
{
    u32 i;
    u32* dst;

    dst = (u32*)&gLagMeter;
    for (i = 0; i < sizeof(gLagMeter) / sizeof(u32); i++)
        dst[i] = 0;

    // Timer 2 counts cycles (prescaler 1), timer 3 counts the overflows of timer 2
    WRITE_16(REG_BASE + 0x10A, 0);
    WRITE_16(REG_BASE + 0x10E, 0);
    WRITE_16(REG_BASE + 0x108, 0);
    WRITE_16(REG_BASE + 0x10C, 0);
    WRITE_16(REG_BASE + 0x10E, 0x80 | 0x4); // enable, count up (cascade)
    WRITE_16(REG_BASE + 0x10A, 0x80);       // enable, 1 tick per cycle

    LagMeterCheckSram();
    HEADER_WRITE(boots, HEADER_READ(boots) + 1);

    gLagMeter.totalLag = HEADER_READ(playLagFrames);
    gLagMeter.display = 1;
    gLagMeter.dirty = TRUE;
    for (i = 0; i < ARRAY_SIZE(gLagMeter.written); i++)
        gLagMeter.written[i] = UCHAR_MAX;
}

/**
 * @brief Counts the lag of the logic frame that ended, starts timing the next one
 *
 */
void LagMeterStartFrame(void)
{
    struct LagMeter* lm;
    u32 vblanks;
    u32 lag;
    u32 playing;

    lm = &gLagMeter;
    vblanks = lm->vblanks;
    lag = vblanks - lm->lastVblanks;
    lm->lastVblanks = vblanks;
    // A logic frame that spans n video frames lagged n - 1 frames
    lag = lag != 0 ? lag - 1 : 0;

    if (lm->started)
    {
        if (lm->tracking)
        {
            lm->roomLogic++;
            if (lm->lastCycles > lm->roomMaxCycles)
                lm->roomMaxCycles = lm->lastCycles;

            if (lag != 0)
            {
                lm->roomLag += lag;
                lm->roomLagging++;
                lm->totalLag += lag;
                if (lm->streak < UCHAR_MAX)
                    lm->streak++;
                if (lm->streak > lm->roomWorstStreak)
                    lm->roomWorstStreak = lm->streak;
                lm->dirty = TRUE;
            }
            else
            {
                lm->streak = 0;
            }
        }
        else
        {
            lm->pendingOtherLogic++;
            lm->pendingOtherLag += lag;
        }
    }
    lm->started = TRUE;

    // The state the next logic frame starts in
    playing = gMainGameMode == GAME_MODE_IN_GAME && gSubGameMode1 == SUB_GAME_MODE_PLAYING;
    if (lm->tracking && (!playing || lm->area != gCurrentArea || lm->room != gCurrentRoom))
    {
        LagMeterFlush();
        lm->tracking = FALSE;
        lm->dirty = TRUE;
    }

    if (playing && !lm->tracking)
    {
        lm->tracking = TRUE;
        lm->area = gCurrentArea;
        lm->room = gCurrentRoom;
        lm->dirty = TRUE;
    }

    lm->loopStart = LagMeterReadTimer();
}

static u32 PutNumber(u8* text, u32 pos, s32 value)
{
    u8 digits[10];
    s32 n;

    n = 0;
    do {
        digits[n++] = value % 10;
        value /= 10;
    } while (value != 0);

    while (n > 0 && pos < ARRAY_SIZE(gLagMeter.text))
        text[pos++] = digits[--n];

    return pos;
}

static void LagMeterUpdateText(void)
{
    struct LagMeter* lm;
    u32 pos;

    lm = &gLagMeter;
    for (pos = 0; pos < ARRAY_SIZE(lm->text); pos++)
        lm->text[pos] = CHAR_SPACE;

    pos = PutNumber(lm->text, 0, lm->roomLag);
    lm->text[pos++] = CHAR_SLASH;
    pos = PutNumber(lm->text, pos, lm->totalLag);

    if (lm->display == 2 && pos + 2 < ARRAY_SIZE(lm->text))
    {
        pos = PutNumber(lm->text, pos + 1, LoadPercent(lm->shownMaxCycles));
        if (pos < ARRAY_SIZE(lm->text))
            lm->text[pos] = CHAR_PERCENT;
    }
}

/**
 * @brief Checks one tile of the counter and rewrites it if it holds the counter or the debug
 * graphics (and nothing else)
 *
 * @param tile Tile (0-7)
 */
static void LagMeterUpdateTile(u32 tile)
{
    struct LagMeter* lm;
    vu32* dst;
    const u32* debugGfx;
    const u16* old0;
    const u16* old1;
    const u16* new0;
    const u16* new1;
    u32 isOld;
    u32 isDebug;
    u32 row;
    u32 word;

    lm = &gLagMeter;
    dst = LAGMETER_VRAM + tile * 8;
    debugGfx = (const u32*)((const u8*)sSpritesGraphicsPointers[0] + 0x800 - 0x100) + tile * 8;

    isOld = lm->written[tile * 2] < ARRAY_SIZE(sLagMeterFont) && lm->written[tile * 2 + 1] < ARRAY_SIZE(sLagMeterFont);
    isDebug = TRUE;
    if (isOld)
    {
        old0 = sLagMeterFont[lm->written[tile * 2]];
        old1 = sLagMeterFont[lm->written[tile * 2 + 1]];
    }

    for (row = 0; row < 8; row++)
    {
        word = dst[row];
        if (isOld && word != (old0[row] | old1[row] << 16))
            isOld = FALSE;
        if (isDebug && word != debugGfx[row])
            isDebug = FALSE;
    }

    if (!isOld && !isDebug)
    {
        // Someone else's graphics (area banner, escape timer, spriteset): leave them
        lm->ownedTiles &= ~(1 << tile);
        lm->written[tile * 2] = UCHAR_MAX;
        lm->written[tile * 2 + 1] = UCHAR_MAX;
        return;
    }

    new0 = sLagMeterFont[lm->text[tile * 2]];
    new1 = sLagMeterFont[lm->text[tile * 2 + 1]];
    for (row = 0; row < 8; row++)
        dst[row] = new0[row] | new1[row] << 16;

    lm->written[tile * 2] = lm->text[tile * 2];
    lm->written[tile * 2 + 1] = lm->text[tile * 2 + 1];
    lm->ownedTiles |= 1 << tile;
}

/**
 * @brief Ends the timing of the logic frame, handles the toggle, draws the counter
 *
 */
void LagMeterEndFrame(void)
{
    struct LagMeter* lm;
    union OamData* oam;
    u32 i;

    lm = &gLagMeter;
    lm->lastCycles = LagMeterReadTimer() - lm->loopStart;

    if (!lm->tracking)
        return;

    if (lm->lastCycles > lm->windowMaxCycles)
        lm->windowMaxCycles = lm->lastCycles;
    if (++lm->windowFrames >= 60)
    {
        lm->shownMaxCycles = lm->windowMaxCycles;
        lm->windowMaxCycles = 0;
        lm->windowFrames = 0;
        if (lm->display == 2)
            lm->dirty = TRUE;
    }

    if ((gButtonInput & LAGMETER_TOGGLE) == LAGMETER_TOGGLE && (gChangedInput & LAGMETER_TOGGLE))
    {
        lm->display = lm->display >= 2 ? 0 : lm->display + 1;
        lm->dirty = TRUE;
    }

    // Draw only when this frame built the OAM of the game (playing)
    if (lm->display == 0 || gMainGameMode != GAME_MODE_IN_GAME || gSubGameMode1 != SUB_GAME_MODE_PLAYING)
        return;

    if (lm->dirty)
    {
        LagMeterUpdateText();
        lm->dirty = FALSE;
    }

    LagMeterUpdateTile(lm->vramTimer++ & 7);

    if (lm->ownedTiles != 0xFF || gNextOamSlot > OAM_BUFFER_DATA_SIZE - 2)
        return;

    // Two 32x8 sprites, in the last OAM slots (the game hid them, ResetFreeOam)
    for (i = 0; i < 2; i++)
    {
        oam = &gOamData[OAM_BUFFER_DATA_SIZE - 2 + i];
        oam->all.attr0 = LAGMETER_Y | 1 << 14;                      // wide
        oam->all.attr1 = (LAGMETER_X + i * 32) | 1 << 14;           // 32x8
        oam->all.attr2 = (LAGMETER_TILE + i * 4) | LAGMETER_PALETTE << 12; // priority 0
    }
}

#endif // LAGMETER
