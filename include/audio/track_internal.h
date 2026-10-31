#ifndef TRACK_INTERNAL_H
#define TRACK_INTERNAL_H

#include "structs/audio.h"

u8 InitTrack(struct TrackData* pTrack, const u32* pHeader);
void StopMusicOrSound(struct TrackData* pTrack);
void ResetTrack(struct TrackData* pTrack);
u32 TrackUpdateTempoCounter(struct TrackData* pTrack);
void AudioCommand_Tempo(struct TrackData* pTrack, struct TrackVariables* pVariables);
void UpdateAudio(void);
void TrackLoadVoiceForKey(struct TrackVariables* pVariables);
void TrackUpdatePitch(struct TrackVariables* pVariables);
void TrackUpdateVolume(struct TrackVariables* pVariables);
void SoundChannelNoteOn(struct SoundChannel* pChannel, struct TrackVariables* pVariables, s32 param_3);
void AudioCommand_Goto(struct TrackVariables* pVariables);
void AudioCommand_PatternPlay(struct TrackVariables* pVariables);
void UploadSampleToWaveRam(const u32* pSample);
void PsgWriteRegisters(struct PsgSoundData* pSound);

#endif /* TRACK_INTERNAL_H */
