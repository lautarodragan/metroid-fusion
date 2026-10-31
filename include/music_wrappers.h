#ifndef MUSIC_WRAPPERS_H
#define MUSIC_WRAPPERS_H

#include "structs/audio.h"

void Dma2IntrCode(void);
void RestartSound(void);
void PauseTracksAndBackupChannels(u8 isInterrupting);
void ResumeTracksFromChannelBackup(u8 arg0);
void Music_Empty(void);
void CheckSetNewMusicTrack(u16 musicTrack);
void CheckPlayNewMusicTrack(void);
void PlayMusic(u16 musicTrack, u8 priority);
void StopMusic(void);
void FadeMusic(u16 timer);
void FadeMusicThenPlay(u16 timer, u16 track, u8 priority);
void PlayMusicWithFadeIn(u16 arg0, u16 arg1, u8 arg2);
void PlayInterruptingMusic(u16 track, u8 arg1);
void RestoreInterruptedMusic(void);
void FadeMusic_2(u16 timer);
void RestartMusic(void);
void SoundPlay_3b1c(u16 sound);
void SoundPlayOnFreeTrack(u16 sound);
void PlayMusicOrSoundFromId(u16 sound, u8 arg1);
void StopMusicOrSoundFromId(u16 sound, u8 arg1);
void DecreaseMusicVolume(void);
void ResetMusicVolume(void);
void PlayPersistentSound(u16 sound);
void StopPersistentSound(void);
void PlayCharacterAppearingSound(u8 unused, u8 speaker);

#endif /* MUSIC_WRAPPERS_H */
