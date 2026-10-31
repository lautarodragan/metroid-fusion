#ifndef AUDIO_STRUCTS_H
#define AUDIO_STRUCTS_H

#include "types.h"
#include "constants/audio.h"

struct Envelope {
    u8 attack;
    u8 decay;
    u8 sustain;
    u8 release;
};

struct Voice {
    u8 instrumentType;
    u8 pitch;
    // PSG length
    u8 length;
    // Pan for the voices of a drum kit, sweep for PSG channel 1
    u8 panSweep;
    u32* pSample;
    struct Envelope envelope;
};

struct SoundQueue {
    u8 exists;
    u8 priority;
    u16 fadingTimer;
    const u8* pHeader;
};

// Direct sound channel, mixed by the sound code
struct SoundChannel {
    // Envelope phase: 0 = off, 1 = start, 2 = attack, 3 = decay, 4 = sustain, 5 = start release, 6 = release,
    // 8 = echo, 10 = stop
    u8 status;
    u8 type;
    u8 priority;
    u8 pan;
    u8 rightVolume;
    u8 leftVolume;
    // Key of the note (used to find the note to end)
    u8 key;
    // Key used for the frequency (the fixed key of drum kit voices)
    u8 midiKey;
    struct Envelope envelope;
    u8 echoVolume;
    u8 echoLength;
    u8 gateTime;
    u8 velocity;
    u8 envelopeVolume;
    u8 envelopeVolumeRight;
    u8 envelopeVolumeLeft;
    // 0x2 = start, 0x4 = frequency changed, 0x10 = volume changed
    u8 flags;
    u32* pSize;
    // Position in the sample (14 fractional bits), advanced by the mixer (SoundCodeA); type 0x20 starts at the end
    u32 samplePosition;
    u32 frequency;
    u32* pSample; // Type?
    u8* pData;
    struct TrackVariables* pVariables;
    struct SoundChannel* pChannel1;
    struct SoundChannel* pChannel2;
};

struct SoundChannelBackup {
    struct SoundChannel* pChannel;
    struct SoundChannel channel;
};

// PSG (CGB) channel
struct PsgSoundData {
    // Envelope phase, same values as SoundChannel.status, plus 9 = length mode
    u8 status;
    u8 type;
    u8 rightVolume;
    u8 leftVolume;
    struct Envelope envelope;
    u16 frequency;
    u8 velocity;
    u8 volume;
    u8 pan;
    u8 echoVolume;
    u8 echoLength;
    // 0x2 = start, 0x4 = frequency changed, 0x10 = volume changed, 0x20 = envelope changed (volume LFO)
    u8 flags;
    // Values written to the channel's registers by PsgWriteRegisters: NRx0 (sweep, channel 3 enable)
    u8 regSweep;
    // NRx1 (length, duty)
    u8 regLengthDuty;
    // NRx2 (envelope, channel 3 volume)
    u8 regEnvelope;
    u8 undefined_13;
    // NRx3/NRx4 (frequency, 0x4000 = length enable, 0x8000 = restart)
    u16 regFrequency;
    u8 priority;
    u8 key;
    u8 envelopeCounter;
    s8 envelopeVolume;
    u8 envelopeGoal;
    u8 sustainGoal;
    u8 midiKey;
    u8 length;
    u8 sweep;
    u8 modulationType;
    u32* pSample; // Type?
    struct TrackVariables* pVariables;
};

struct TrackVariables {
    // 0x1 = exists, 0x2 = note started, 0x4 = volume changed, 0x8 = pitch changed,
    // 0x40 = key split voice, 0x80 = drum kit voice (the voice is loaded for every note)
    u8 flags;
    u8 key;
    u8 delay;
    u8 runningStatus;
    u8 volume;
    // Volume set by the code (fading, SetTrackVolume), 0x40 = 100%
    u8 volumeControl;
    u8 pan;
    // Pan set by the code (SetTrackPanning)
    u8 panControl;
    u8 rightVolume;
    u8 leftVolume;
    u8 repeatCount;
    u8 priority;
    u8 echoVolume;
    u8 echoLength;
    u8 gateTime;
    u8 velocity;
    u8 lfoSpeed;
    u8 modulationDepth;
    u8 modulationType;
    s8 modulation;
    u8 lfoDelay;
    u8 lfoDelayCounter;
    s8 lfoCounter;
    // Computed by TrackUpdatePitch: key offset (in semitones) and fine pitch offset (in 1/256 semitone)
    s8 keyOffset;
    u8 pitchOffset;
    s8 pitchBend;
    u8 bendRange;
    u8 unk_1B;
    u8 keyShift;
    // Key shift set by the code (SetTrackPitch)
    u8 keyShiftControl;
    u8 tune;
    // Pitch set by the code (SetTrackPitch)
    u8 pitchControl;
    u32 unk_20;
    const u8* pRawData;
    const u8* patternStartPointers[3];
    u8 channel;
    // Fixed key of the current drum kit voice
    u8 drumKey;
    // PSG length of the voice
    u8 length;
    // PSG sweep of the voice
    u8 sweep;

    u32* pSample1; // Type?
    struct Envelope envelope1;
    u32* pSample2; // Type?
    struct Envelope envelope2;

    struct SoundChannel* pChannel;
    struct PsgSoundData* pSoundPsg;
};

struct TrackData {
    u8 flags;
    u8 amountOfTracks;

    u8 undefined_2;
    // Priority from the sound header
    u8 soundPriority;
    u8 currentTrack;

    u8 maxAmountOfTracks;
    u16 fadeVolume;
    u16 fadingTimer;

    u16 tempo;
    // Added to tempoCounter every frame, 0x100 = one tick per frame (tempo 150)
    u16 tempoInterval;
    u16 tempoCounter;

    const u8* pHeader;
    struct Voice* pVoice;
    struct TrackVariables* pVariables;

    u8 occupied;
    // A sound only replaces the current one if its priority is at least as high
    u8 usePriority;
    // 0x1 = paused by PauseTracksAndBackupChannels (can't be started, stopped or updated),
    // 0x2 = resumed by ResumeTracksFromChannelBackup or played by SoundPlayOnUnusedMusicTrack
    u8 pauseFlags;
    u8 priority;
    u16 musicTrack;
    u8 maxSoundChannels;

    // Cross fade (CrossFadeMusic): notes started this frame, and the number of sound channels changing
    // by crossFadeChannelStep / 4096 every frame
    u8 crossFadeNoteCount;
    u16 crossFadeChannelCounter;
    u16 crossFadeChannelStep;

    u8 queueFlags;

    u8 undefined_29;
    u8 undefined_2A;
    u8 undefined_2B;
    u8 undefined_2C;
    u8 undefined_2D;
    u8 undefined_2E;
    u8 undefined_2F;
    u8 undefined_30;
    u8 undefined_31;
    u8 undefined_32;

    u8 unk_33;
    u8 unk_34;
    u8 unk_35;

    u8 undefined_36;
    u8 undefined_37;
    u8 undefined_38;
    u8 undefined_39;
    u8 undefined_3A;
    u8 undefined_3B;
    u8 undefined_3C;
    u8 undefined_3D;
    u8 undefined_3E;
    u8 undefined_3F;
};

struct TrackGroupRomData {
    struct TrackData* pTrack;
    struct TrackVariables* pVariables;
    u16 maxAmountOfTracks;
    u16 usePriority;
};

struct SoundEntry {
    const u8* pHeader;
    u16 trackGroupNumber;
    u16 trackGroupNumber_2;
};

struct MusicInfo {
    u8 unk_0;
    boolu8 occupied;
    // Sound played with PlayPersistentSound, restarted after an interrupting music ends
    u16 persistentSound;

    u8 reverb; // unused
    u8 maxSoundChannels;
    u8 volume;
    u8 freqIndex;

    u8 unk_8;
    // If not 0, the mixing stops this many scanlines after it started
    u8 maxScanlines;
    u8 currentSoundChannel;
    u8 volumeDownFlag;
    // The PCM buffer is processed in blocks of 16 samples
    u8 blocksPerFrame; // samplesPerFrame / 16
    u8 framesPerBuffer; // unused, PCM_DMA_BUF_SIZE / samplesPerFrame
    u8 blocksPerBuffer; // 96
    u8 unk_F;
    // Block being played by the DMA (incremented by the DMA 2 interrupt)
    u8 dmaBlock;
    // Next block to mix
    u8 mixBlock;
    u16 sampleRate;
    u32 samplesPerFrame; // unused
    u32 pitch;
    // Music of track group 0
    u16 musicTrack;
    // Music of track group 1
    u16 secondMusicTrack;
    // Track group of the current music (FALSE = 0, TRUE = 1)
    u8 usingSecondMusicTrack;
    u8 priority;
    u16 musicTrackOnTransition;
    u32 musicRawData[768];
    u8 soundRawData[PCM_DMA_BUF_SIZE * 2];
    struct SoundChannel soundChannels[11];
};

struct MusicTrack {
    u16 number;
    u8 lowered;
};


typedef void (*MusicFunc_T)(struct TrackVariables*);

// Linker variables
extern char gNumMusicPlayers[];
// Constants defined in the linker script (so that they are loaded from a literal pool)
extern char gAudioMaxScanlines[];
extern char gAudioInitSoundAction[];
extern char gAudioDecreasedMusicVolume[];

extern struct MusicInfo gMusicInfo;

// gPsgSounds - 1, indexed by the PSG channel of a track (1 to 4)
extern struct PsgSoundData gPsgSoundsByChannel[];
extern struct PsgSoundData gPsgSounds[4];

extern struct SoundChannelBackup gSoundChannelBackup[6];
// extern struct SoundChannelBackup gSoundChannelTrack2Backup[6];
// extern struct SoundQueue gSoundQueue[8];

typedef void (*SoundCodeAFunc_T)(struct SoundChannel*, u32*, u8);
typedef u8* (*SoundCodeBFunc_T)(u32*, u32*, u32*, u8);
typedef u8* (*SoundCodeCFunc_T)(u32*, u32*, u8);

extern SoundCodeAFunc_T gSoundCodeAPointer;
extern u8 gSoundCodeA[1624];
extern SoundCodeBFunc_T gSoundCodeBPointer;
extern u8 gSoundCodeB[164];
extern SoundCodeCFunc_T gSoundCodeCPointer;
extern u8 gSoundCodeC[176];

extern struct TrackVariables gTrack0Variables[10];
extern struct TrackVariables gTrack1Variables[10];
extern struct TrackVariables gTrack2Variables[2];
extern struct TrackVariables gTrack3Variables[2];
extern struct TrackVariables gTrack4Variables[2];
extern struct TrackVariables gTrack5Variables[2];
extern struct TrackVariables gTrack6Variables[3];
extern struct TrackVariables gTrack7Variables[1];

extern struct MusicTrack gCurrentMusicTrack;

extern struct TrackData gTrackData3;
extern struct TrackData gTrackData1;
extern struct TrackData gTrackData6;
extern struct TrackData gTrackData4;
extern struct TrackData gTrackData0;
extern struct TrackData gTrackData7;
extern struct TrackData gTrackData2;
extern struct TrackData gTrackData5;

#endif /* AUDIO_STRUCTS_H */
