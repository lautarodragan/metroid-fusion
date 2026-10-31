#ifndef AUDIO_WRAPPERS_H
#define AUDIO_WRAPPERS_H

#include "constants/audio.h"

#include "structs/audio.h"

extern void CallSoundCodeA(void);
extern void CallSoundCodeB(void);
extern void CallSoundCodeC(void);

void InitializeAudio(void);
void DoSoundAction(u32 action);
void SetupSoundTransfer(void);
void SoundPlay(u16 sound);
void SoundStop(u16 sound);
void StopAllMusicAndSounds(void);
void StopAllMusicAndSoundsNotPaused(void);
void FadeAllSounds(u16 timer);
void SoundPlayNotAlreadyPlaying(u16 sound);
void SoundPlayOrResume(u16 sound);
void SoundResume(u16 sound);
void ResumeMusicOrSound(struct TrackData* pTrack);
void ResumeAllMusicAndSounds(void);
void ApplyMusicSoundFading(struct TrackData* pTrack, u16 timer);
void ApplyRawMusicSoundFading(struct TrackData* pTrack, u16 timer);
void UpdateTrackFadeOut(struct TrackData* pTrack);
void PlayFadingSound(u16 sound, u16 timer);
void InitFadingMusic(struct TrackData* pTrack, const u8* pHeader, u16 timer);
void ResumeMusicOrSoundWithFadeIn(struct TrackData* pTrack, u16 timer);
void UpdateTrackFadeIn(struct TrackData* pTrack);
void CrossFadeMusic(u16 musicTrack1, u16 musicTrack2, u16 timer);
void SetTrackTempoControl(struct TrackData* pTrack, u16 param_2);
void SetTrackVolume(struct TrackData* pTrack, u16 variablesMask, u16 param_3);
void SetTrackPitch(struct TrackData* pTrack, u16 variablesMask, u16 param_3);
void SetTrackPanning(struct TrackData* pTrack, u16 variablesMask, u8 param_3);
void SetTrackModulationDepth(struct TrackData* pTrack, u16 variablesMask, u8 param_3);
void SetTrackLfoSpeed(struct TrackData* pTrack, u16 variablesMask, u8 param_3);

#endif /* AUDIO_WRAPPERS_H */
