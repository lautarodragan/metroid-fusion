#include "audio_wrappers.h"
#include "data/audio.h"

#include "gba.h"
#include "macros.h"

/**
 * @brief 2298 | 254 | Initializes the audio
 * 
 */
void InitializeAudio(void)
{
    u8 i;

    if (gMusicInfo.occupied)
        return;

    gMusicInfo.occupied = TRUE;

    WRITE_16(REG_IE, READ_16(REG_IE) | IF_DMA2);
    WRITE_8(REG_SOUNDCNT_X, 0x80); // Enable PSG and FIFO
    WRITE_16(REG_SOUNDCNT_H, 0xA90E); // 100% volume, reset and enable/disable DMA sound A right/left and DMA sound B left/right

    WRITE_8(REG_SOUNDBIAS + 1, (READ_8(REG_SOUNDBIAS + 1) & 0x3F) | 0x40);

    WRITE_8(REG_SOUND1CNT_H + 1, HIGH_BYTE(SOUNDCNT_ENVELOPE_INCREASE));
    WRITE_8(REG_SOUND1CNT_X + 1, HIGH_BYTE(SOUNDCNT_RESTART_SOUND));
    WRITE_8(REG_SOUND2CNT_L + 1, HIGH_BYTE(SOUNDCNT_ENVELOPE_INCREASE));
    WRITE_8(REG_SOUND2CNT_H + 1, HIGH_BYTE(SOUNDCNT_RESTART_SOUND));
    WRITE_8(REG_SOUND4CNT_L + 1, HIGH_BYTE(SOUNDCNT_ENVELOPE_INCREASE));
    WRITE_8(REG_SOUND4CNT_H + 1, HIGH_BYTE(SOUNDCNT_RESTART_SOUND));

    WRITE_8(REG_SOUND3CNT_L, 0x0);
    WRITE_8(REG_SOUNDCNT_L, 0x77); // Sound 1-4 master volume left/right 100%

    gSoundCodeAPointer = (SoundCodeAFunc_T)(gSoundCodeA + 1);
    DMA3_COPY_16(CallSoundCodeA, gSoundCodeA, sizeof(gSoundCodeA) / 2);

    gSoundCodeBPointer = (SoundCodeBFunc_T)(gSoundCodeB + 1);
    DMA3_COPY_16(CallSoundCodeB, gSoundCodeB, sizeof(gSoundCodeB) / 2);

    gSoundCodeCPointer = (SoundCodeCFunc_T)(gSoundCodeC + 1);
    DMA3_COPY_16(CallSoundCodeC, gSoundCodeC, sizeof(gSoundCodeC) / 2);

    DMA3_FILL_16(0, &gMusicInfo, 28);

    gMusicInfo.maxScanlines = (u8)gAudioMaxScanlines;

    for (i = 0; i < ARRAY_SIZE(gPsgSounds); i++)
    {
        DMA3_FILL_16(0, &gPsgSounds[i], sizeof(gPsgSounds[i]));
    }

    for (i = 0; i < (u16)gNumMusicPlayers; i++)
    {
        DMA3_FILL_16(0, sMusicTrackDataRom[i].pTrack, 44);
    }

    for (i = 0; i < (u16)gNumMusicPlayers; i++)
    {
        sMusicTrackDataRom[i].pTrack->pVariables = sMusicTrackDataRom[i].pVariables;
        sMusicTrackDataRom[i].pTrack->maxAmountOfTracks = sMusicTrackDataRom[i].maxAmountOfTracks;
        sMusicTrackDataRom[i].pTrack->usePriority = sMusicTrackDataRom[i].usePriority;
    }

     // SOUND_ACTION_DISABLE_STEREO | SOUND_ACTION_PWM(9) | SOUND_ACTION_FREQ_INDEX(SOUND_MODE_FREQ_10512) | SOUND_ACTION_VOLUME(15) | SOUND_ACTION_MAX_CHANNELS(6)
    DoSoundAction((u32)gAudioInitSoundAction);

    for (i = 0; i < gMusicInfo.maxSoundChannels; i++)
    {
        DMA3_FILL_16(0, &gMusicInfo.soundChannels[i], sizeof(gMusicInfo.soundChannels[i]));
    }

    for (i = 0; i < ARRAY_SIZE(gSoundChannelBackup); i++)
    {
        DMA3_FILL_16(0, &gSoundChannelBackup[i], sizeof(gSoundChannelBackup[i]));
    }

    gMusicInfo.occupied = FALSE;
}

/**
 * @brief 24ec | fc | Performs a sound action
 * 
 * @param action Action
 */
void DoSoundAction(u32 action)
{
    s8 i;
    u32 control;

    if (gMusicInfo.occupied)
        return;

    gMusicInfo.occupied = TRUE;

    if (action & SOUND_ACTION_ENABLE_REVERB)
        gMusicInfo.reverb = action + SOUND_ACTION_ENABLE_REVERB;

    if (action & SOUND_ACTION_MAX_CHANNELS_FLAG)
    {
        gMusicInfo.maxSoundChannels = (action & SOUND_ACTION_MAX_CHANNELS_FLAG) >> SOUND_ACTION_MAX_CHANNELS_SHIFT;
        for (i = ARRAY_SIZE(gMusicInfo.soundChannels); i >= 0 ; i--)
        {
            gMusicInfo.soundChannels[i].status = 0;
        }
    }

    if (action & SOUND_ACTION_VOLUME_FLAG)
        gMusicInfo.volume = (action & SOUND_ACTION_VOLUME_FLAG) >> SOUND_ACTION_VOLUME_SHIFT;

    if (action & SOUND_ACTION_FREQ_INDEX_FLAG)
    {
        gMusicInfo.freqIndex = (action & SOUND_ACTION_FREQ_INDEX_FLAG) >> SOUND_ACTION_FREQ_INDEX_SHIFT;
        if (gMusicInfo.freqIndex != SOUND_MODE_FREQ_NONE)
            SetupSoundTransfer();
    }

    // Set PWM amplitude control
    if (action & SOUND_ACTION_PWM_FLAG)
    {
        // Set amplitude resolution/sampling cycle to bits 28-29 of action
        WRITE_8(REG_SOUNDBIAS + 1, (READ_8(REG_SOUNDBIAS + 1) & 0x3F) | (action & SOUND_ACTION_PWM_FLAG) >> 14);
    }

    control = action & SOUND_ACTION_STEREO_FLAG;
    if (control)
    {
        // Enable stereo
        if (control == SOUND_ACTION_ENABLE_STEREO)
        {
            // Set sound volume to 50%, disable DMA sound A left and sound B right
            WRITE_16(REG_SOUNDCNT_H, READ_16(REG_SOUNDCNT_H) & 0xE10D);
            WRITE_16(REG_SOUNDCNT_H, READ_16(REG_SOUNDCNT_H) | 0x1);
        }
        // Disable stereo
        else if (control == SOUND_ACTION_DISABLE_STEREO)
        {
            // Set sound volume to 100% and enable DMA sound A/B left/right
            WRITE_16(REG_SOUNDCNT_H, READ_16(REG_SOUNDCNT_H) & ~0x1);
            WRITE_16(REG_SOUNDCNT_H, READ_16(REG_SOUNDCNT_H) | 0x3302);
        }
    }

    gMusicInfo.occupied = FALSE;
}

/**
 * @brief 25e8 | 124 | Sets up the DMA transfers to the fifo channels
 * 
 */
void SetupSoundTransfer(void)
{
    u32 buffer;
    u16 samplesPerFrame;
    u16 unk_1;
    u32 unk_2;

    WRITE_32(REG_DMA1_CNT, C_32_2_16((DMA_ENABLE | DMA_32BIT | DMA_DEST_FIXED), sizeof(u32)));
    WRITE_32(REG_DMA2_CNT, C_32_2_16((DMA_ENABLE | DMA_32BIT | DMA_DEST_FIXED), sizeof(u32)));
    WRITE_16(REG_DMA1_CNT + 2, DMA_32BIT);
    WRITE_16(REG_DMA2_CNT + 2, DMA_32BIT);

    buffer = 0;
    CpuFastSet(&buffer, gMusicInfo.soundRawData, C_32_2_16(CPU_SET_SRC_FIXED, sizeof(gMusicInfo.soundRawData) / sizeof(u32)));

    gMusicInfo.sampleRate = sNativeSampleRate[gMusicInfo.freqIndex];
    gMusicInfo.pitch = sMusicPitchData[gMusicInfo.freqIndex];
    samplesPerFrame = sPcmSamplesPerVBlankTable[gMusicInfo.freqIndex];
    gMusicInfo.samplesPerFrame = samplesPerFrame;

    unk_1 = samplesPerFrame / 16;
    gMusicInfo.blocksPerFrame = unk_1; // samplesPerFrame / 16
    unk_2 = 96 / gMusicInfo.blocksPerFrame;
    gMusicInfo.framesPerBuffer = unk_2;  // PCM_DMA_BUF_SIZE / samplesPerFrame, number of frames to process sample?
    gMusicInfo.blocksPerBuffer = unk_2 * unk_1;  // 96
    gMusicInfo.dmaBlock = gMusicInfo.blocksPerBuffer - 1; // 95
    gMusicInfo.mixBlock = unk_1 * 2; // (samplesPerFrame / 16) * 2

    // First half of raw sound data goes into FIFO A, second half into FIF0 B
    WRITE_32(REG_DMA1_SRC, (u32)&gMusicInfo.soundRawData[0]);
    WRITE_32(REG_DMA2_SRC, (u32)&gMusicInfo.soundRawData[sizeof(gMusicInfo.soundRawData) / 2]);

    WRITE_32(REG_DMA1_DST, (u32)REG_FIFO_A);
    WRITE_32(REG_DMA2_DST, (u32)REG_FIFO_B);

    WRITE_16(REG_DMA1_CNT + 2, DMA_ENABLE | DMA_START_HBLANK | DMA_START_VBLANK | DMA_32BIT | DMA_REPEAT);
    WRITE_16(REG_DMA2_CNT + 2, DMA_ENABLE | DMA_INTR_ENABLE | DMA_START_HBLANK | DMA_START_VBLANK | DMA_32BIT | DMA_REPEAT);

    WRITE_16(REG_TM0CNT_H, 0);
    WRITE_16(REG_TM0CNT_L, -((u32)FRAME_DRAW_CYCLES / samplesPerFrame)); // cycle time to play each sample

    // Wait for VBLANK
    while (READ_8(REG_VCOUNT) == (SCREEN_SIZE_Y - 1)) {}
    while (READ_8(REG_VCOUNT) != (SCREEN_SIZE_Y - 1)) {}

    WRITE_16(REG_TM0CNT_H, 0x80); // start timer 0
}

/**
 * @brief 270c | 2c | Plays a sound
 * 
 * @param sound Sound ID
 */
void SoundPlay(u16 sound)
{
    InitTrack(sMusicTrackDataRom[sSoundDataEntries[sound].trackGroupNumber].pTrack,
        sSoundDataEntries[sound].pHeader);
}

/**
 * @brief 2738 | 3c | Stops a sound
 * 
 * @param sound Sound ID
 */
void SoundStop(u16 sound)
{
    struct TrackData* pTrack;

    pTrack = sMusicTrackDataRom[sSoundDataEntries[sound].trackGroupNumber].pTrack;

    if (pTrack->flags & 2 && sSoundDataEntries[sound].pHeader == pTrack->pHeader)
        StopMusicOrSound(pTrack, sSoundDataEntries[sound].pHeader);
}

/**
 * @brief 2774 | 34 | Stops every music/sound currently playing
 * 
 */
void StopAllMusicAndSounds(void)
{
    s32 i;

    for (i = (u16)gNumMusicPlayers - 1; i >= 0; i--)
        StopMusicOrSound(sMusicTrackDataRom[i].pTrack);
}

/**
 * @brief 27a8 | 40 | Stops every music/sound currently playing, except the ones paused by PauseTracksAndBackupChannels
 * 
 */
void StopAllMusicAndSoundsNotPaused(void)
{
    s32 i;

    for (i = (u16)gNumMusicPlayers - 1; i >= 0; i--)
    {
        if (!(sMusicTrackDataRom[i].pTrack->unk_1E & TRUE))
            StopMusicOrSound(sMusicTrackDataRom[i].pTrack);
    }
}

/**
 * @brief 27e8 | 6c | Fades every single sound
 * 
 * @param timer Fading timer
 */
void FadeAllSounds(u16 timer)
{
    if (gMusicInfo.usingSecondMusicTrack == 0)
        ApplyMusicSoundFading(sMusicTrackDataRom[1].pTrack, timer);
    else
        ApplyMusicSoundFading(sMusicTrackDataRom[0].pTrack, timer);

    ApplyMusicSoundFading(sMusicTrackDataRom[2].pTrack, timer);
    ApplyMusicSoundFading(sMusicTrackDataRom[3].pTrack, timer);
    ApplyMusicSoundFading(sMusicTrackDataRom[4].pTrack, timer);
    ApplyMusicSoundFading(sMusicTrackDataRom[5].pTrack, timer);
    ApplyMusicSoundFading(sMusicTrackDataRom[6].pTrack, timer);
    ApplyMusicSoundFading(sMusicTrackDataRom[7].pTrack, timer);
}

/**
 * @brief 2854 | 40 | Plays a sound only if it isn't already playing
 * 
 * @param sound Sound ID
 */
void SoundPlayNotAlreadyPlaying(u16 sound)
{
    struct TrackData* pTrack;
    const u8* pHeader;

    pTrack = sMusicTrackDataRom[sSoundDataEntries[sound].trackGroupNumber].pTrack;
    pHeader = sSoundDataEntries[sound].pHeader;

    if (!(pTrack->flags & 2) || pHeader != pTrack->pHeader)
        InitTrack(pTrack, pHeader);
}

/**
 * @brief 2894 | 68 | Plays a sound, or resumes it if it was stopped
 * 
 * @param sound Sound ID
 */
void SoundPlayOrResume(u16 sound)
{
    struct TrackData* pTrack;
    const u8* pHeader;

    pTrack = sMusicTrackDataRom[sSoundDataEntries[sound].trackGroupNumber].pTrack;
    pHeader = sSoundDataEntries[sound].pHeader;

    if (pTrack->flags & 2)
    {
        if (pHeader != pTrack->pHeader)
            InitTrack(pTrack, pHeader);
    }
    else if (pTrack->flags & 1)
    {
        if (pHeader == pTrack->pHeader)
            ResumeMusicOrSound(pTrack);
        else
            InitTrack(pTrack, pHeader);
    }
    else if (pTrack->flags == 0)
    {
        InitTrack(pTrack, pHeader);
    }
}

/**
 * @brief 28fc | 3c | Resumes a sound if it was stopped
 * 
 * @param sound Sound ID
 */
void SoundResume(u16 sound)
{
    struct TrackData* pTrack;

    pTrack = sMusicTrackDataRom[sSoundDataEntries[sound].trackGroupNumber].pTrack;

    if (pTrack->flags & 1 && sSoundDataEntries[sound].pHeader == pTrack->pHeader)
        ResumeMusicOrSound(pTrack);
}

/**
 * @brief 2938 | 3c | Resumes a stopped music or sound
 * 
 * @param pTrack Track data pointer
 */
void ResumeMusicOrSound(struct TrackData* pTrack)
{
    s32 i;
    struct TrackVariables* pVariables;

    if (!pTrack->occupied)
    {
        pTrack->occupied = TRUE;

        if (pTrack->flags & 1)
        {
            pTrack->flags = 2;

            i = 0;
            pVariables = pTrack->pVariables;

            while (i < pTrack->amountOfTracks)
            {
                pVariables->volumeControl = 0x40;
                i++;
                pVariables++;
            }
        }

        pTrack->occupied = FALSE;
    }
}

/**
 * @brief 2974 | 34 | Resumes every stopped music/sound
 * 
 */
void ResumeAllMusicAndSounds(void)
{
    s32 i;

    for (i = (u16)gNumMusicPlayers - 1; i >= 0; i--)
        ResumeMusicOrSound(sMusicTrackDataRom[i].pTrack);
}

/**
 * @brief 29a8 | 54 | Apply fading to music or sound
 * 
 * @param pTrack Track data pointer
 * @param timer Fade timer
*/
void ApplyMusicSoundFading(struct TrackData* pTrack, u16 timer)
{
    s32 volume;

    if (timer == 0)
    {
        StopMusicOrSound(pTrack);
    }
    else if (!pTrack->occupied)
    {
        pTrack->occupied = TRUE;

        if (pTrack->flags & 2)
        {
            if (pTrack->flags & 0xF8)
            {
                ResetTrack(pTrack);
            }
            else
            {
                pTrack->flags |= 8;

                volume = USHORT_MAX;
                pTrack->fadeVolume = volume;
                pTrack->fadingTimer = volume / timer;
            }
        }

        pTrack->occupied = FALSE;
    }
}

/**
 * @brief 29fc | 44 | Apply raw(?) fading to music or sound
 * 
 * @param pTrack Track data pointer
 * @param timer Fade timer
*/
void ApplyRawMusicSoundFading(struct TrackData* pTrack, u16 timer)
{
    s32 volume;

    if (!pTrack->occupied)
    {
        pTrack->occupied = TRUE;

        if (pTrack->flags & 2)
        {
            if (!(pTrack->flags & 0xF8))
            {
                pTrack->flags |= 0x10;

                volume = USHORT_MAX;
                pTrack->fadeVolume = volume;
                pTrack->fadingTimer = volume / timer;
            }
        }

        pTrack->occupied = FALSE;
    }
}

/**
 * @brief 2a40 | 94 | Updates the fade out of a track, stops it when the volume reaches 0
 * 
 * @param pTrack Track data pointer
 */
void UpdateTrackFadeOut(struct TrackData* pTrack)
{
    s32 i;
    struct TrackVariables* pVariables;

    pVariables = pTrack->pVariables;

    if (pTrack->fadeVolume - pTrack->fadingTimer >= 0)
    {
        pTrack->fadeVolume -= pTrack->fadingTimer;
        if (pTrack->flags & 0x80)
        {
            pTrack->crossFadeChannelCounter += pTrack->crossFadeChannelStep;
            if ((u16)(pTrack->crossFadeChannelCounter >> 0xc) != 0)
            {
                pTrack->maxSoundChannels--;
                pTrack->crossFadeChannelCounter &= 0xFFF;
            }

            pTrack->crossFadeNoteCount = 0;
        }

        for (i = pTrack->amountOfTracks; i > 0; i--, pVariables++)
        {
            pVariables->volumeControl = pTrack->fadeVolume / 1024;
            pVariables->flags |= 4;
        }
    }
    else
    {
        ResetTrack(pTrack);

        if (pTrack->flags & 8)
            pTrack->flags = 0;

        if (pTrack->musicTrack != 0)
            pTrack->queueFlags |= 1;
    }
}

/**
 * @brief 2ad4 | 34 | Plays a fading in sound
 * 
 * @param sound Sound ID
 * @param timer Fading timer
 */
void PlayFadingSound(u16 sound, u16 timer)
{
    InitFadingMusic(sMusicTrackDataRom[sSoundDataEntries[sound].trackGroupNumber].pTrack,
        sSoundDataEntries[sound].pHeader, timer);
}

/**
 * @brief 2b08 | 64 | Initializes a music that fades in
 * 
 * @param pTrack Track data pointer
 * @param pHeader Sound header pointer
 * @param timer Fading timer
 */
void InitFadingMusic(struct TrackData* pTrack, const u8* pHeader, u16 timer)
{
    if (pHeader[0] == 0)
    {
        StopMusicOrSound(pTrack);
    }
    else
    {
        if (pTrack->flags & 2)
        {
            if (pTrack->soundPriority > pHeader[2])
                return;

            StopMusicOrSound(pTrack);
        }

        InitTrack(pTrack, pHeader);

        if (timer != 0 && !pTrack->occupied)
        {
            pTrack->occupied = TRUE;
            pTrack->flags = 0x20 | 2;
            pTrack->fadeVolume = 0;
            pTrack->fadingTimer = USHORT_MAX / timer;

            pTrack->occupied = FALSE;
        }
    }
}

/**
 * @brief 2b6c | 38 | Resumes a stopped music or sound with a fade in
 * 
 * @param pTrack Track data pointer
 * @param timer Fading timer
 */
void ResumeMusicOrSoundWithFadeIn(struct TrackData* pTrack, u16 timer)
{
    if (!pTrack->occupied)
    {
        pTrack->occupied = TRUE;
        if (pTrack->flags & 1)
        {
            pTrack->flags = 0x20 | 2;
            pTrack->fadeVolume = 0;
            pTrack->fadingTimer = USHORT_MAX / timer;
        }

        pTrack->occupied = FALSE;
    }
}

/**
 * @brief 2ba4 | 94 | Updates the fade in of a track
 * 
 * @param pTrack Track data pointer
 */
void UpdateTrackFadeIn(struct TrackData* pTrack)
{
    s32 i;
    struct TrackVariables* pVariables;

    pVariables = pTrack->pVariables;

    if (pTrack->fadeVolume + pTrack->fadingTimer <= USHORT_MAX)
    {
        pTrack->fadeVolume += pTrack->fadingTimer;
        if (pTrack->flags & 0x40)
        {
            pTrack->crossFadeChannelCounter += pTrack->crossFadeChannelStep;
            if ((u16)(pTrack->crossFadeChannelCounter >> 0xc) != 0)
            {
                pTrack->maxSoundChannels++;
                pTrack->crossFadeChannelCounter &= 0xFFF;
            }

            pTrack->crossFadeNoteCount = 0;
        }

        i = pTrack->amountOfTracks;
        while (i > 0)
        {
            pVariables->volumeControl = pTrack->fadeVolume / 1024;
            pVariables->flags |= 4;

            i--;
            pVariables++;
        }
    }
    else
    {
        i = pTrack->amountOfTracks;
        while (i > 0)
        {
            pVariables->volumeControl = 0x40;
            pVariables->flags |= 4;

            i--;
            pVariables++;
        }

        pTrack->flags = 0x2;
    }
}

/**
 * @brief 2c38 | 128 | Cross fades from the second music track to the first one
 * 
 * @param musicTrack1 First music track
 * @param musicTrack2 Second music track
 * @param timer Timer
 */
void CrossFadeMusic(u16 musicTrack1, u16 musicTrack2, u16 timer)
{
    struct TrackData* pTrack1;
    struct TrackData* pTrack2;
    const u8* pHeader;
    s32 var_0;
    u32 var_1;

    if (gMusicInfo.occupied)
        return;

    gMusicInfo.occupied = TRUE;

    pTrack1 = sMusicTrackDataRom[sSoundDataEntries[musicTrack1].trackGroupNumber].pTrack;
    pTrack2 = sMusicTrackDataRom[sSoundDataEntries[musicTrack2].trackGroupNumber].pTrack;

    if (!pTrack1->occupied && !pTrack2->occupied)
    {
        pTrack1->occupied = TRUE;
        pTrack2->occupied = TRUE;

        if (pTrack2->flags & 2)
        {
            if (!(pTrack2->flags & 0xF8))
            {
                pHeader = sSoundDataEntries[musicTrack1].pHeader;

                // Amount of tracks
                if (pHeader[0] == 0)
                {
                    ResetTrack(pTrack1);
                }
                else
                {
                    if (pTrack1->flags & 2)
                    {
                        // Priority
                        if (pTrack1->soundPriority > pHeader[2])
                        {
                            //pTrack1->occupied = FALSE;
                            //pTrack2->occupied = FALSE;
                            //gMusicInfo.occupied = FALSE;
                            var_0 = FALSE;
                        }
                        else
                        {
                            ResetTrack(pTrack1);
                            var_0 = TRUE;
                        }
                    }
                    else
                    {
                        var_0 = TRUE;
                    }

                    if (var_0)
                    {
                        var_1 = pTrack2->flags;
                        pTrack2->flags = var_1 | 0x80;
                        pTrack2->fadeVolume = USHORT_MAX;
                        pTrack2->fadingTimer = USHORT_MAX / timer;
                        pTrack2->crossFadeChannelStep = (gMusicInfo.maxSoundChannels * 4096) / timer;
                        pTrack2->crossFadeChannelCounter = 0;
                        pTrack2->maxSoundChannels = gMusicInfo.maxSoundChannels;

                        InitTrack(pTrack1, pHeader);
                        pTrack1->flags = 0x40 | 0x2;
                        pTrack1->fadeVolume = 0;
                        pTrack1->fadingTimer = pTrack2->fadingTimer;
                        pTrack1->crossFadeChannelStep = pTrack2->crossFadeChannelStep;
                        pTrack1->crossFadeChannelCounter = 0;
                        pTrack1->maxSoundChannels = 0;
                    }
                }
            }
        }

        pTrack1->occupied = FALSE;
        pTrack2->occupied = FALSE;
    }

    gMusicInfo.occupied = FALSE;
}

/**
 * @brief 2d60 | 30 | Sets the tempo of a track relative to its normal tempo (0x100 = normal)
 * 
 * @param pTrack Track data pointer
 * @param param_2 Unknown
 */
void SetTrackTempoControl(struct TrackData* pTrack, u16 param_2)
{
    u16 unk;

    if (!pTrack->occupied)
    {
        pTrack->occupied = TRUE;

        unk = param_2 / 256 * pTrack->tempo;
        pTrack->tempoInterval = unk * 256 / 150;

        pTrack->occupied = FALSE;
    }
}

/**
 * @brief 2d90 | 5c | Sets the volume of the tracks of a track group (0x100 = 100%)
 * 
 * @param pTrack Track data pointer
 * @param variablesMask Track data variables mask
 * @param param_3 Unknown
 */
void SetTrackVolume(struct TrackData* pTrack, u16 variablesMask, u16 param_3)
{
    struct TrackVariables* pVariables;
    s32 i;

    if (!pTrack->occupied)
    {
        pTrack->occupied = TRUE;

        if (!(pTrack->flags & (0x80|0x40|0x20|0x10|0x8)))
        {
            pVariables = pTrack->pVariables;
            param_3 = (param_3 & 0x3FC) / 4;
            i = pTrack->amountOfTracks - 1;

            while (i >= 0)
            {
                if ((variablesMask >> i) & 1)
                {
                    pVariables->volumeControl = param_3;
                    pVariables->flags |= 4;
                }

                i--;
                pVariables++;
            }
        }

        pTrack->occupied = FALSE;
    }
}

/**
 * @brief 2dec | 5c | Sets the pitch of the tracks of a track group
 * 
 * @param pTrack Track data pointer
 * @param variablesMask Track data variables mask
 * @param param_3 Unknown
 */
void SetTrackPitch(struct TrackData* pTrack, u16 variablesMask, u16 param_3)
{
    struct TrackVariables* pVariables;
    s32 i;

    if (!pTrack->occupied)
    {
        pTrack->occupied = TRUE;

        pVariables = pTrack->pVariables;
        i = pTrack->amountOfTracks;

        while (i > 0)
        {
            if ((variablesMask >> i) & 1)
            {
                pVariables->keyShiftControl = (s16)param_3 >> 8;
                pVariables->pitchControl = param_3;
                pVariables->flags |= 8;
            }

            i--;
            pVariables++;
        }

        pTrack->occupied = FALSE;
    }
}

/**
 * @brief 2e48 | 4c | Sets the panning of the tracks of a track group
 * 
 * @param pTrack Track data pointer
 * @param variablesMask Track data variables mask
 * @param param_3 Unknown
 */
void SetTrackPanning(struct TrackData* pTrack, u16 variablesMask, u8 param_3)
{
    struct TrackVariables* pVariables;
    s32 i;

    if (!pTrack->occupied)
    {
        pTrack->occupied = TRUE;

        pVariables = pTrack->pVariables;
        i = pTrack->amountOfTracks;

        while (i > 0)
        {
            if ((variablesMask >> i) & 1)
            {
                pVariables->panControl = (s8)param_3 >> 1;
                pVariables->flags |= 4;
            }

            i--;
            pVariables++;
        }

        pTrack->occupied = FALSE;
    }
}

/**
 * @brief 2e94 | 44 | Sets the modulation depth of the tracks of a track group
 * 
 * @param pTrack Track data pointer
 * @param variablesMask Track data variables mask
 * @param param_3 Unknown
 */
void SetTrackModulationDepth(struct TrackData* pTrack, u16 variablesMask, u8 param_3)
{
    struct TrackVariables* pVariables;
    s32 i;

    if (!pTrack->occupied)
    {
        pTrack->occupied = TRUE;

        pVariables = pTrack->pVariables;
        param_3 &= 0x7F;
        i = pTrack->amountOfTracks;

        while (i > 0)
        {
            if ((variablesMask >> i) & 1)
                pVariables->modulationDepth = param_3;

            i--;
            pVariables++;
        }

        pTrack->occupied = FALSE;
    }
}

/**
 * @brief 2ed8 | 44 | Sets the LFO speed of the tracks of a track group
 * 
 * @param pTrack Track data pointer
 * @param variablesMask Track data variables mask
 * @param param_3 Unknown
 */
void SetTrackLfoSpeed(struct TrackData* pTrack, u16 variablesMask, u8 param_3)
{
    struct TrackVariables* pVariables;
    s32 i;

    if (!pTrack->occupied)
    {
        pTrack->occupied = TRUE;

        pVariables = pTrack->pVariables;
        param_3 &= 0x7F;
        i = pTrack->amountOfTracks;

        while (i > 0)
        {
            if ((variablesMask >> i) & 1)
                pVariables->lfoSpeed = param_3;

            i--;
            pVariables++;
        }

        pTrack->occupied = FALSE;
    }
}
