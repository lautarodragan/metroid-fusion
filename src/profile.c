#include "profile.h"

#ifdef PROFILE

#include "gba.h"
#include "io.h"

/**
 * @brief Starts the cycle counter (timers 2 and 3 chained) and clears the profile
 *
 */
void ProfileInit(void)
{
    u32 i;
    u32* dst;

    dst = (u32*)&gProfile;
    for (i = 0; i < sizeof(gProfile) / sizeof(u32); i++)
        dst[i] = 0;

    gProfile.magic = PROFILE_MAGIC;

    // Timer 2 counts cycles (prescaler 1), timer 3 counts the overflows of timer 2
    WRITE_16(REG_BASE + 0x10A, 0);
    WRITE_16(REG_BASE + 0x10E, 0);
    WRITE_16(REG_BASE + 0x108, 0);
    WRITE_16(REG_BASE + 0x10C, 0);
    WRITE_16(REG_BASE + 0x10E, 0x80 | 0x4); // enable, count up (cascade)
    WRITE_16(REG_BASE + 0x10A, 0x80);       // enable, 1 tick per cycle
}

/**
 * @brief Publishes the counts of the logic frame that ends (gProfile.last) and starts a new one
 *
 */
void ProfileEndFrame(void)
{
    u32 i;
    u32* src;
    u32* dst;

    gProfile.cur.cycles[PROF_LOOP] = ProfileReadTimer() - gProfile.loopStart;

    src = (u32*)&gProfile.cur;
    dst = (u32*)&gProfile.last;
    for (i = 0; i < sizeof(gProfile.cur) / sizeof(u32); i++)
    {
        dst[i] = src[i];
        src[i] = 0;
    }

    gProfile.frames++;
}

#endif // PROFILE
