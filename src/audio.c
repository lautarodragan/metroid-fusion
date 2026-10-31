#include "audio.h"
#include "macros.h"
#include "gba.h"
#include "syscalls.h"
#include "audio/track_internal.h"

#include "data/audio.h"

#include "constants/audio_engine.h"

static void TrackUpdateChannelsGateTime(struct TrackVariables* pVariables);
static void TrackUpdatePsgGateTime(struct TrackVariables* pVariables);
static void TrackApplyLfoToChannels(struct TrackVariables* pVariables);
static void TrackApplyLfoToPsg(struct TrackVariables* pVariables, s16 param_2);
static void TrackRequestChannelsVolumeUpdate(struct TrackVariables* pVariables);
static void TrackUpdateChannelsFrequency(struct TrackVariables* pVariables);
static void TrackRequestPsgVolumeUpdate(struct TrackVariables* pVariables);
static void TrackUpdatePsgFrequency(struct TrackVariables* pVariables);
static void TrackNoteOnDirectSound(struct TrackData* pTrack, struct TrackVariables* pVariables);
static void TrackNoteOnDirectSoundCrossFading(struct TrackData* pTrack, struct TrackVariables* pVariables);
static void TrackNoteOnPsg(struct TrackData* pTrack, struct TrackVariables* pVariables);
static void TrackNoteOnPsgCrossFading(struct TrackData* pTrack, struct TrackVariables* pVariables);
static void PsgNoteOn(struct PsgSoundData* pSound, struct TrackVariables* pVariables, u32 param_3);

static u16 GetPsgFrequency(struct TrackVariables* pVariables, u8 param_2, u8 param_3);

/**
 * @brief e48 | 394 | Mixes the direct sound channels into the PCM buffer (envelopes, volumes, sound code)
 * 
 */
void UpdateMusic(void)
{
    u32 var_0;
    s16 var_1;
    s16 var_2;
    u8 var_3;
    u16 var_4;
    u32 var_5;
    u8 var_6;
    u8 var_7;
    u8 var_8;
    u8* buffer;
    u8* buffer2;
    u32 vcount;
    u16 i;
    struct SoundChannel* pChannel;
    struct TrackVariables* pVariables;
    u32 *tmp;
    u32 tmp2;
    u32 tmp3;

    var_0 = tmp3 = gMusicInfo.maxScanlines;
    if (var_0 != 0)
    {
        vcount = READ_8(REG_VCOUNT);
        if (vcount < SCREEN_SIZE_Y)
            vcount += VERTICAL_LINE_COUNT;

        tmp3 = vcount;
        var_0 = vcount;
        tmp3 = gMusicInfo.maxScanlines;
        var_0 += tmp3;
    }

    var_8 = gMusicInfo.dmaBlock;
    var_4 = gMusicInfo.mixBlock * 16;
    var_7 = ((gMusicInfo.blocksPerFrame << 1) + var_8) - 1;
    if (var_7 >= gMusicInfo.blocksPerBuffer)
        var_7 -= gMusicInfo.blocksPerBuffer;

    var_3 = 0;
    if (var_8 <= var_7 && var_7 <= gMusicInfo.mixBlock)
    {
        var_4 = (var_7 - gMusicInfo.blocksPerFrame + 1) * 16;
        var_6 = gMusicInfo.blocksPerFrame;
        if (var_7 + 1 == gMusicInfo.blocksPerBuffer)
            gMusicInfo.mixBlock = 0;
        else
            gMusicInfo.mixBlock = var_7 + 1;
    }
    else if (gMusicInfo.mixBlock <= var_8 && var_8 <= var_7)
    {
        var_4 = (var_7 - gMusicInfo.blocksPerFrame + 1) * 16;
        var_6 = gMusicInfo.blocksPerFrame;
        if (var_7 + 1 == gMusicInfo.blocksPerBuffer)
            gMusicInfo.mixBlock = 0;
        else
            gMusicInfo.mixBlock = var_7 + 1;
    }
    else if (var_7 <= gMusicInfo.mixBlock && gMusicInfo.mixBlock <= var_8)
    {
        var_4 = 0;
        var_6 = var_7 + 1;
        gMusicInfo.mixBlock = var_6;
    }
    else if (gMusicInfo.mixBlock < var_7)
    {
        var_6 = (var_7 - gMusicInfo.mixBlock) + 1;
        if (var_7 + 1 == gMusicInfo.blocksPerBuffer)
            gMusicInfo.mixBlock = 0;
        else
            gMusicInfo.mixBlock = var_7 + 1;
    }
    else if (gMusicInfo.mixBlock > var_7)
    {
        var_6 = gMusicInfo.blocksPerBuffer - gMusicInfo.mixBlock;
        var_3 = var_7 + 1;
        gMusicInfo.mixBlock = var_3;
    }
    else
    {
        var_4 = 0;
        var_6 = var_7 + 1;
        gMusicInfo.mixBlock = var_6;
    }


    if (var_6 == 0)
        return;

    buffer2 = &gMusicInfo.soundRawData[var_4];
    tmp = gMusicInfo.musicRawData;
    buffer = gSoundCodeBPointer((u32*)buffer2, (u32*)buffer2, gMusicInfo.musicRawData, var_6 * 8);
    if (var_3 != 0)
    {
        buffer2 = gMusicInfo.soundRawData;
        gSoundCodeBPointer((u32*)buffer2, (u32*)buffer2, (u32*)buffer, var_3 * 8);
    }

    gMusicInfo.currentSoundChannel = 0;
    for (i = 0; i < gMusicInfo.maxSoundChannels; i++)
    {
        if (var_0 != 0)
        {
            vcount = READ_8(REG_VCOUNT);
            if (vcount < SCREEN_SIZE_Y)
                vcount += VERTICAL_LINE_COUNT;

            if (vcount >= var_0)
                break;
        }

        pChannel = &gMusicInfo.soundChannels[i];
        if (pChannel->status == 0)
            continue;

        gMusicInfo.currentSoundChannel++;
        pVariables = pChannel->pVariables;

        while (pChannel->flags != 0)
        {
            if (pChannel->flags & 0x2)
            {
                if (pChannel->type == 0x20)
                    pChannel->unk_18 = pChannel->pSample[3] << 14;
                else
                    pChannel->unk_18 = 0;

                pChannel->envelopeVolume = 0;
                pChannel->flags &= ~0x2;
                pChannel->flags |= 0x10;
            }
            else if (pChannel->flags & 0x4)
            {
                pChannel->flags &= ~0x4;
            }
            else if (pChannel->flags & 0x10)
            {
                if (pVariables->flags & 0x80)
                {
                    pVariables->pan = pChannel->pan;
                    TrackUpdateVolume(pVariables);
                }

                pChannel->rightVolume = (pVariables->rightVolume * (pChannel->velocity + 1)) >> 7;
                pChannel->leftVolume = (pVariables->leftVolume * (pChannel->velocity + 1)) >> 7;

                pChannel->flags &= ~0x10;
            }
        }

        var_1 = pChannel->envelopeVolume;
        var_5 = pChannel->status & 0xF;
        if (var_5 == 0xA)
        {
            pChannel->status = 0;
            continue;
        }
        
        if (var_5 == 1)
        {
            if (pChannel->envelope.attack != UCHAR_MAX)
            {
                goto lbl_1;
            }
            else
            {
                goto lbl_3;
            }
        }

        switch (var_5)
        {
            case 2:
                goto lbl_2;

                lbl_1:
                var_1 = 0;
                pChannel->status = 2;

                lbl_2:
                var_1 += pChannel->envelope.attack;
                if (var_1 <= 0xFE)
                    break;

                lbl_3:
                tmp2 = pChannel->envelope.decay;
                var_8 = pChannel->envelope.sustain;
                if (tmp2 != 0)
                {
                    var_1 = UCHAR_MAX;
                    pChannel->status = 3;
                }
                else
                {
                    var_1 = var_8;
                    pChannel->status = 4;
                    break;
                }

            case 3:
                if ((var_1 = (var_1 * pChannel->envelope.decay) >> 8) > (var_8 = pChannel->envelope.sustain))
                    break;

                if (var_8 != 0)
                {
                    var_1 = var_8;
                    pChannel->status = 4;
                    break;
                }

            case 5:
                pChannel->status = 6;

            case 6:
                if ((var_1 = (var_1 * pChannel->envelope.release) >> 8) > 0)
                    break;

                pChannel->status = 0;
                if (pChannel->echoVolume != 0 && pChannel->echoLength != 0)
                    pChannel->status = 8;
                else
                    SoundChannelUnlink(pChannel);
                continue;

            case 8:
                pChannel->echoLength--;
                if (pChannel->echoLength == 0)
                {
                    pChannel->status = 0;
                    SoundChannelUnlink(pChannel);
                }
                break;
        }

        pChannel->envelopeVolume = var_1;
        var_2 = (var_1 * (gMusicInfo.volume + 1)) >> 4;
        pChannel->envelopeVolumeRight = var_2 * pChannel->rightVolume >> 8;
        pChannel->envelopeVolumeLeft = var_2 * pChannel->leftVolume >> 8;

        tmp = gMusicInfo.musicRawData;
        gSoundCodeAPointer(pChannel, tmp, (var_6 + var_3) * 4);
    }

    buffer2 = &gMusicInfo.soundRawData[var_4];
    tmp = gMusicInfo.musicRawData;
    buffer = gSoundCodeCPointer((u32*)buffer2, tmp, var_6 * 4);
    if (var_3 != 0)
    {
        buffer2 = gMusicInfo.soundRawData;
        gSoundCodeCPointer((u32*)buffer2, (u32*)buffer, var_3 * 4);
    }
}

/**
 * @brief 11dc | 3f8 | Updates the PSG channels (envelopes, volumes, registers)
 * 
 */
void UpdatePsgSounds(void)
{
    s16 var_0;
    u8 control;
    u8 i;
    u8* ptr;
    struct PsgSoundData* pSound;
    struct TrackVariables* pVariables;
    u32 tmp;

    var_0 = FALSE;

    for (i = 0; i < ARRAY_SIZE(gPsgSounds); i++)
    {
        pSound = &gPsgSounds[i];

        if (pSound->status == 0)
            continue;

        while (pSound->flags)
        {
            if (pSound->flags & 0x2)
            {
                pVariables = pSound->pVariables;

                pSound->velocity = pVariables->velocity;
                pSound->volume = pVariables->volume;
                pSound->echoVolume = pVariables->echoVolume;
                pSound->echoLength = pVariables->echoLength;
                pSound->length = pVariables->length;
                pSound->sweep = pVariables->sweep;
                
                pSound->pSample = pVariables->pSample1;
                pSound->envelope.attack = pVariables->envelope1.attack;
                pSound->envelope.decay = pVariables->envelope1.decay;
                pSound->envelope.sustain = pVariables->envelope1.sustain;
                pSound->envelope.release = pVariables->envelope1.release;

                pSound->modulationType = pVariables->modulationType;

                pSound->flags &= ~0x2;
                pSound->flags |= 0x10;
                continue;
            }

            if (pSound->flags & 0x4)
            {
                pSound->regFrequency = pSound->frequency;

                PsgWriteRegisters(pSound);

                pSound->flags &= ~0x4;
                continue;
            }

            if (pSound->flags & 0x10)
            {
                if (pSound->pVariables->pan != pSound->pan)
                {
                    pSound->pVariables->pan = pSound->pan;
                    TrackUpdateVolume(pSound->pVariables);
                }

                pSound->rightVolume = (pSound->pVariables->rightVolume * (pSound->velocity + 1)) >> 7;
                pSound->leftVolume = (pSound->pVariables->leftVolume * (pSound->velocity + 1)) >> 7;

                pSound->envelopeGoal = (pSound->rightVolume + pSound->leftVolume) >> 4;
                pSound->sustainGoal = (pSound->envelopeGoal * pSound->envelope.sustain + 0xF) >> 4;

                ptr = (u8*)(REG_SOUNDCNT_L + 1);
                control = READ_8(ptr) & ~(0x11 << i);

                if (pSound->rightVolume >= pSound->leftVolume)
                {
                    if ((pSound->rightVolume >> 1) > pSound->leftVolume)
                    {
                        *ptr = control | (1 << i);
                    }
                    else
                    {
                        *ptr = control | (17 << i);
                    }
                }
                else
                {
                    if ((pSound->leftVolume >> 1) > pSound->rightVolume)
                    {
                        *ptr = control | (16 << i);
                    }
                    else
                    {
                        *ptr = control | (17 << i);
                    }
                }

                pSound->regEnvelope = 0;
                pSound->regFrequency |= 0x8000;

                var_0 = TRUE;

                pSound->flags &= ~0x10;
                continue;
            }

            if (pSound->flags & 0x20)
            {
                pSound->regFrequency = pSound->frequency | 0x8000;

                PsgWriteRegisters(pSound);

                pSound->flags &= ~0x20;
            }
        }

        control = pSound->status & 0xF;

        if (control == 0xA)
        {
            ClearRegistersForPsg(pSound, i);
            continue;
        }

        if (control == 0x1)
        {
            if (i == 0)
            {
                pSound->regSweep = pSound->sweep;
            }
            else if (i == 2)
            {
                pSound->regSweep = 0x80;
            }

            if (i < 2)
                pSound->regLengthDuty = (u8)(u32)pSound->pSample;
            else
                pSound->regLengthDuty = 0;

            tmp = 0;
            pSound->regFrequency = pSound->frequency | tmp | 0x8000;

            if (pSound->length != 0)
            {
                goto lbl_pre_case_9;
            }

            if (pSound->envelope.attack != 0)
            {
                goto lbl_pre_case_2;
            }
            else
            {
                if (pSound->envelope.decay == 0)
                {
                    goto lbl_1;
                }
                else
                {
                    goto lbl_2;
                }
            }
        }

        if (pSound->envelopeCounter == 0)
        {
            switch (pSound->status & 0xF)
            {
                case 2:
                    goto lbl_case_2;

                    lbl_pre_case_2:
                    pSound->envelopeVolume = 0;
                    if (i == 2)
                        pSound->regEnvelope = 0;
                    else
                        pSound->regEnvelope = pSound->envelope.attack + 8;

                    pSound->status = 2;
                    PsgWriteRegisters(pSound);

                    lbl_case_2:
                    if (++pSound->envelopeVolume >= pSound->envelopeGoal)
                    {
                        lbl_3:
                        if (pSound->envelope.decay == 0)
                        {
                            goto lbl_1;
                        }
                        else
                        {
                            goto lbl_2;
                        }
                    }
                    else
                    {
                        if (i == 2)
                        {
                            pSound->regEnvelope = 0;
                            var_0 = TRUE;
                        }
    
                        pSound->envelopeCounter = pSound->envelope.attack;
                        break;
                    }
                    

                case 3:
                    goto lbl_case_3;
                    
                    lbl_2:
                    pSound->envelopeVolume = pSound->envelopeGoal;
                    if (i == 2)
                    {
                        pSound->regEnvelope = 0;
                    }
                    else
                    {
                        pSound->regEnvelope = pSound->envelope.decay;
                        pSound->regFrequency = pSound->frequency | 0x8000;
                    }

                    pSound->status = 3;
                    var_0 = TRUE;

                    lbl_case_3:
                    if (--pSound->envelopeVolume > pSound->sustainGoal)
                    {
                        if (i == 2)
                        {
                            pSound->regEnvelope = 0;
                            var_0 = TRUE;
                        }

                        pSound->envelopeCounter = pSound->envelope.decay;
                        break;
                    }

                    lbl_1:
                    pSound->envelopeVolume = pSound->sustainGoal;

                    if (i == 2)
                    {
                        pSound->regEnvelope = 0;
                    }
                    else
                    {
                        pSound->regEnvelope = 0;
                        pSound->regFrequency = pSound->frequency | 0x8000;
                    }
                    
                    pSound->status = 4;
                    var_0 = TRUE;

                case 4:
                    pSound->envelopeVolume = pSound->sustainGoal;
                    
                    if ((pSound->status & 0xF) == 4)
                        pSound->envelopeCounter = 1;
                    break;

                case 5:
                    if (pSound->envelope.release != 0 && pSound->length == 0)
                    {
                        if (i != 2)
                        {
                            pSound->regEnvelope = pSound->envelope.release;
                            pSound->regFrequency = pSound->frequency | 0x8000;
                        }

                        pSound->status = 6;
                        var_0 = TRUE;
                    }
                    else
                    {
                        goto lbl_0;
                    }

                case 6:
                    pSound->envelopeVolume--;
                    if (pSound->envelopeVolume > 0)
                    {
                        if (i == 2)
                        {
                            pSound->regEnvelope = 0;
                            var_0 = TRUE;
                        }

                        pSound->envelopeCounter = pSound->envelope.release;
                        break;
                    }

                    lbl_0:
                    pSound->status = 0;

                    if (pSound->echoVolume != 0 && pSound->echoLength != 0)
                    {
                        pSound->envelopeVolume = (pSound->envelopeGoal * pSound->echoVolume + 0xFF) >> 8;
                        pSound->envelopeCounter = pSound->echoLength;

                        if (i == 2)
                        {
                            pSound->regEnvelope = sCgb3Vol[pSound->envelopeVolume];
                        }
                        else
                        {
                            pSound->regEnvelope = 0;
                            pSound->regFrequency = pSound->frequency | 0x8000;
                        }

                        pSound->status = 8;
                        var_0 = TRUE;
                    }
                    else
                    {
                        ClearRegistersForPsg(pSound, i);
                        continue;
                    }
                    break;

                case 8:
                    if (pSound->envelopeCounter == 0)
                    {
                        ClearRegistersForPsg(pSound, i);
                        pSound->status = 0;
                    }
                    continue;

                case 9:
                    goto lbl_case_9;

                    lbl_pre_case_9:
                    pSound->regLengthDuty |= pSound->length;
                    pSound->regEnvelope = 0;
                    pSound->envelopeVolume = pSound->sustainGoal;
                    pSound->regFrequency |= 0x4000;
                    pSound->status = 9;

                    var_0 = TRUE;

                    lbl_case_9:
                    pSound->envelopeCounter = UCHAR_MAX;
                    if (var_0)
                    {
                        pSound->regFrequency |= 0x4000;
                    }
                    break;
            }
        }

        if (var_0)
        {
            var_0 = FALSE;
            control = (u8)pSound->envelopeVolume;

            if (i == 2)
                pSound->regEnvelope = sCgb3Vol[control];
            else
                pSound->regEnvelope |= control << 4;

            PsgWriteRegisters(pSound);
        }

        pSound->envelopeCounter--;
    }
}

/**
 * @brief 15d4 | 38c | Updates a track data
 * 
 * @param pTrack Track data pointer
 */
void UpdateTrack(struct TrackData* pTrack)
{
    u8 i;
    struct TrackVariables* pVariables;
    u8 var_0;
    u8 var_1;
    s16 var_2;
    s32 tmp;

    if (gMusicInfo.volumeDownFlag & 1)
        gMusicInfo.volumeDownFlag &= 0xFE;
    else if (gMusicInfo.volumeDownFlag & 2)
        gMusicInfo.volumeDownFlag &= 0xFD;

    if (pTrack->occupied)
        return;

    pTrack->occupied = TRUE;

    if (!(pTrack->unk_1E & TRUE))
    {
        if (pTrack->flags & 0xF8)
        {
            if (pTrack->flags & 0x98)
                UpdateTrackFadeOut(pTrack);
            else
                UpdateTrackFadeIn(pTrack);
        }

        if (pTrack->flags & 0x2)
        {
            var_1 = TrackUpdateTempoCounter(pTrack);
            while (var_1 != 0)
            {
                for (i = 0, pVariables = pTrack->pVariables; i < pTrack->amountOfTracks; i++, pVariables++)
                {
                    if (pVariables->flags == 0)
                        continue;

                    if (pVariables->pChannel != NULL)
                        TrackUpdateChannelsGateTime(pVariables);

                    if (pVariables->pSoundPsg != NULL)
                        TrackUpdatePsgGateTime(pVariables);

                    if (pVariables->delay != 0)
                    {
                        pVariables->delay--;
                        if (pVariables->lfoDelayCounter != 0)
                        {
                            pVariables->lfoDelayCounter--;
                        }
                        else
                        {
                            if (pVariables->lfoSpeed != 0 && pVariables->modulationDepth != 0)
                            {
                                if (pVariables->pChannel != NULL)
                                {
                                    if (pVariables->pChannel->status != 0)
                                    {
                                        pVariables->lfoCounter += pVariables->lfoSpeed;
                                        if ((s8)(pVariables->lfoCounter - 0x40) < 0)
                                            var_2 = pVariables->lfoCounter;
                                        else
                                            var_2 = 0x80 - (u8)pVariables->lfoCounter;

                                        if (var_2 != (s8)pVariables->modulation)
                                        {
                                            pVariables->modulation = (var_2 * (pVariables->modulationDepth + 1)) >> 7;
                                            TrackApplyLfoToChannels(pVariables);
                                        }
                                    }
                                }
                                else
                                {
                                    if (pVariables->pSoundPsg != NULL && pVariables->pSoundPsg->status != 0)
                                    {
                                        pVariables->lfoCounter += pVariables->lfoSpeed;
                                        if ((s8)(pVariables->lfoCounter - 0x40) < 0)
                                            var_2 = pVariables->lfoCounter;
                                        else
                                            var_2 = 0x80 - (u8)pVariables->lfoCounter;

                                        if (var_2 != (s8)pVariables->modulation)
                                        {
                                            pVariables->modulation = (var_2 * (pVariables->modulationDepth + 1)) >> 7;
                                            TrackApplyLfoToPsg(pVariables, var_2);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    while (pVariables->delay == 0)
                    {
                        var_0 = *pVariables->pRawData;
                        if ((s8)var_0 >= 0)
                            var_0 = pVariables->runningStatus;
                        else if (var_0 > 0xBC)
                        {
                            pVariables->runningStatus = var_0;
                            pVariables->pRawData++;
                        }

                        if (var_0 > 0xCE)
                        {
                            pVariables->flags |= 0x2;
                            pVariables->gateTime = sClockTable[var_0 - 0xCF];

                            var_0 = *pVariables->pRawData;

                            if (pVariables->lfoDelay != 0)
                                pVariables->lfoDelayCounter = pVariables->lfoDelay;

                            if ((s8)var_0 >= 0)
                            {
                                pVariables->key = var_0;
                                pVariables->pRawData++;

                                var_0 = *pVariables->pRawData;
                                if ((s8)var_0 >= 0)
                                {
                                    pVariables->velocity = var_0;
                                    pVariables->pRawData++;
                                
                                    var_0 = *pVariables->pRawData;
                                }
                            }

                            if ((pVariables->flags & 0xF0) > 0x3F)
                                TrackLoadVoiceForKey(pVariables);

                            pVariables->modulation = 0;
                            TrackUpdatePitch(pVariables);
                            TrackUpdateVolume(pVariables);

                            if (pTrack->flags & 0xC0)
                            {
                                if (pVariables->channel & 7)
                                    TrackNoteOnPsgCrossFading(pTrack, pVariables);
                                else
                                    TrackNoteOnDirectSoundCrossFading(pTrack, pVariables);
                            }
                            else
                            {
                                if (pVariables->channel & 7)
                                    TrackNoteOnPsg(pTrack, pVariables);
                                else
                                    TrackNoteOnDirectSound(pTrack, pVariables);
                            }
                        }
                        else if (var_0 > 0xB0)
                        {
                            if (var_0 == TEMPO)
                            {
                                AudioCommand_Tempo(pTrack, pVariables);
                            }
                            else if (var_0 == VOICE)
                            {
                                AudioCommand_Voice(pTrack, pVariables);
                            }
                            else if (var_0 == FINE)
                            {
                                AudioCommand_Fine(pTrack, pVariables);
                                break;
                            }
                            else if (var_0 == 0xB6)
                            {
                                AudioCommand_FineRestoreMusic(pTrack, pVariables);
                                break;
                            }
                            else
                            {
                                sMusicCommandFunctionPointers[var_0 - FINE](pVariables);
                            }
                        }
                        else
                        {
                            pVariables->delay = sClockTable[var_0 - 0x80];
                            pVariables->pRawData++;
                            break;
                        }
                    }


                    if (pVariables->flags & 4)
                    {
                        TrackUpdateVolume(pVariables);
                        if (pVariables->pChannel != NULL)
                            TrackRequestChannelsVolumeUpdate(pVariables);

                        if (pVariables->pSoundPsg != NULL)
                            TrackRequestPsgVolumeUpdate(pVariables);

                        pVariables->flags &= ~4;
                    }

                    if (pVariables->flags & 8)
                    {
                        TrackUpdatePitch(pVariables);
                        if (pVariables->pChannel != NULL)
                            TrackUpdateChannelsFrequency(pVariables);

                        if (pVariables->pSoundPsg != NULL)
                            TrackUpdatePsgFrequency(pVariables);

                        pVariables->flags &= ~8;
                    }
                }
                
                var_1--;
            }
        }
    }

    pTrack->occupied = FALSE;
    tmp = pTrack->queueFlags;
    if (pTrack->queueFlags == 0x1)
    {
        PlayMusic(pTrack->musicTrack, pTrack->priority);
        pTrack->occupied = TRUE;

        pTrack->musicTrack = 0;
        pTrack->priority = 0;
        pTrack->queueFlags = 0;
        pTrack->occupied = FALSE;
    }
    else if (pTrack->queueFlags & 0x2)
    {
        if (tmp & 0x80)
            RestoreInterruptedMusic(tmp & 0x80);

        pTrack->queueFlags = 0;
    }
}

/**
 * @brief 1960 | 28 | Decrements the gate time of the sound channels of a track, and releases the notes that ended
 * 
 * @param pVariables Track variables pointer
 */
static void TrackUpdateChannelsGateTime(struct TrackVariables* pVariables)
{
    struct SoundChannel* pChannel;

    for (pChannel = pVariables->pChannel; pChannel != NULL; pChannel = pChannel->pChannel2)
    {
        if (pChannel->gateTime != 0)
        {
            if (--pChannel->gateTime == 0)
            {
                pChannel->status = 5;
            }
        }
    }
}

/**
 * @brief 1988 | 24 | Decrements the gate time of the PSG channel of a track, and releases the note if it ended
 * 
 * @param pVariables Track variables pointer
 */
static void TrackUpdatePsgGateTime(struct TrackVariables* pVariables)
{
    struct PsgSoundData* pSound;

    pSound = pVariables->pSoundPsg;

    if (pVariables->gateTime != 0)
    {
        if (--pVariables->gateTime == 0)
        {
            pSound->status = 5;
            pSound->envelopeCounter = 0;
        }
    }
}

/**
 * @brief 19ac | 90 | Applies the LFO (vibrato, tremolo or pan) to the sound channels of a track
 * 
 * @param pVariables Track variables pointer
 */
static void TrackApplyLfoToChannels(struct TrackVariables* pVariables)
{
    struct SoundChannel* pChannel;
    s32 frequency;
    s16 midiKey;

    pChannel = pVariables->pChannel;

    switch (pVariables->modulationType)
    {
        case 1:
        case 2:
            TrackUpdateVolume(pVariables);
            for (; pChannel != NULL; pChannel = pChannel->pChannel2)
                pChannel->flags |= 0x10;
            break;
        
        case 0:
            TrackUpdatePitch(pVariables);

            if (pChannel->type != 0 && pChannel->type != 0x20)
                break;

            for (; pChannel != NULL; pChannel = pChannel->pChannel2)
            {
                midiKey = pVariables->keyOffset + pChannel->midiKey;

                if (midiKey >= 0x80)
                    midiKey = 0x7F;
                else if (midiKey < 0)
                    midiKey = 0;

                frequency = MidiKey2Freq(pVariables->pSample1, midiKey, pVariables->pitchOffset);
                pChannel->frequency = frequency;

                if (frequency == gMusicInfo.sampleRate)
                    frequency = 0x4000;
                else
                    frequency = CallGetNoteFrequency(frequency, gMusicInfo.pitch);

                pChannel->frequency = frequency;
            }
    }
}

/**
 * @brief 1a3c | 90 | Applies the LFO (vibrato, tremolo or pan) to the PSG channel of a track
 * 
 * @param pVariables Track variables pointer
 * @param param_2 LFO value
 */
static void TrackApplyLfoToPsg(struct TrackVariables* pVariables, s16 param_2)
{
    struct PsgSoundData* pSound;
    s16 var_0;

    pSound = pVariables->pSoundPsg;

    if (pVariables->modulationType == 1)
    {
        TrackUpdateVolume(pVariables);
        pSound->regEnvelope = ((u8)pSound->envelopeVolume + (s32)pVariables->modulation / sPsgVolumeLfoDivisors[param_2]) * 16;
        pSound->flags |= 0x20;
    }
    else if (pVariables->modulationType == 0)
    {
        TrackUpdatePitch(pVariables);

        var_0 = pVariables->keyOffset + pVariables->pSoundPsg->midiKey;

        if (var_0 >= 0x80)
            var_0 = 0x7F;
        else if (var_0 < 0)
            var_0 = 0;

        pSound->frequency = GetPsgFrequency(pVariables, var_0, pVariables->pitchOffset);
        pSound->flags |= 0x4;
    }
    else if (pVariables->modulationType == 2)
    {
        TrackUpdateVolume(pVariables);
        pSound->flags |= 0x10;
    }
}

/**
 * @brief 1acc | 1c | Requests a volume update of the sound channels of a track
 * 
 * @param pVariables Track variables pointer
 */
static void TrackRequestChannelsVolumeUpdate(struct TrackVariables* pVariables)
{
    struct SoundChannel* pChannel;

    for (pChannel = pVariables->pChannel; pChannel != NULL; pChannel = pChannel->pChannel2)
        pChannel->flags |= 0x10;
}

/**
 * @brief 1ae8 | 64 | Updates the frequency of the sound channels of a track
 * 
 * @param pVariables Track variables pointer
 */
static void TrackUpdateChannelsFrequency(struct TrackVariables* pVariables)
{
    struct SoundChannel* pChannel;
    s32 frequency;
    s16 midiKey;

    for (pChannel = pVariables->pChannel; pChannel != NULL; pChannel = pChannel->pChannel2)
    {
        midiKey = pVariables->keyOffset + pChannel->midiKey;

        if (midiKey >= 0x80)
            midiKey = 0x7F;
        else if (midiKey < 0)
            midiKey = 0;

        frequency = MidiKey2Freq(pChannel->pSample, midiKey, pVariables->pitchOffset);
        pChannel->frequency = frequency;

        if (frequency == gMusicInfo.sampleRate)
            frequency = 0x4000;
        else
            frequency = CallGetNoteFrequency(frequency, gMusicInfo.pitch);

        pChannel->frequency = frequency;
        pChannel->flags |= 4;
    }
}

/**
 * @brief 1b4c | c | Requests a volume update of the PSG channel of a track
 * 
 * @param pVariables Track variables pointer
 */
static void TrackRequestPsgVolumeUpdate(struct TrackVariables* pVariables)
{
    pVariables->pSoundPsg->flags |= 0x10;
}

/**
 * @brief 1b58 | 44 | Updates the frequency of the PSG channel of a track
 * 
 * @param pVariables Track variables pointer
 */
static void TrackUpdatePsgFrequency(struct TrackVariables* pVariables)
{
    s16 var_0;

    var_0 = pVariables->keyOffset + pVariables->pSoundPsg->midiKey;

    if (var_0 >= 0x80)
        var_0 = 0x7F;
    else if (var_0 < 0)
        var_0 = 0;

    pVariables->pSoundPsg->frequency = GetPsgFrequency(pVariables, var_0, pVariables->pitchOffset);
    pVariables->pSoundPsg->flags |= 0x4;
}

/**
 * @brief 1b9c | 110 | Starts a note on a direct sound channel (a free one, or the one with the lowest priority)
 * 
 * @param pTrack Track data pointer
 * @param pVariables Track variables pointer
 */
static void TrackNoteOnDirectSound(struct TrackData* pTrack, struct TrackVariables* pVariables)
{
    u8 var_0;
    u8 var_1;
    u32 var_2;
    s32 var_3;
    s32 var_4;
    u8 i;
    struct SoundChannel* pChannel;
    struct TrackVariables* pVariables2;

    if (pTrack->soundPriority + pVariables->priority > UCHAR_MAX)
        var_0 = UCHAR_MAX;
    else
        var_0 = pTrack->soundPriority + pVariables->priority;

    var_2 = var_0;
    pVariables2 = pVariables;
    var_1 = FALSE;
    pChannel = NULL;

    for (i = 0; i < gMusicInfo.maxSoundChannels; i++)
    {
        if (gMusicInfo.soundChannels[i].status == 0)
        {
            pChannel = &gMusicInfo.soundChannels[i];
            goto end;
            //SoundChannelNoteOn(pChannel, pVariables, var_0);
            //return;
        }
        
        if (gMusicInfo.soundChannels[i].status == 5 || gMusicInfo.soundChannels[i].status == 6 || gMusicInfo.soundChannels[i].status == 8)
        {
            if (!var_1)
            {
                var_1 = TRUE;
                var_4 = FALSE;
                var_3 = TRUE;
            }
            else
            {
                var_4 = TRUE;
                var_3 = FALSE;
            }
        }
        else
        {
            var_4 = FALSE;
            var_3 = FALSE;
        }

        if (!var_3)
        {
            if (var_4 || !var_1)
            {
                if (gMusicInfo.soundChannels[i].priority >= var_2 &&
                    (gMusicInfo.soundChannels[i].priority > var_2 ||
                    (gMusicInfo.soundChannels[i].pVariables <= pVariables2 &&
                    gMusicInfo.soundChannels[i].pVariables < pVariables2)))
                {
                    continue;
                }
                var_3 = TRUE;
            }
            else
            {
                var_3 = FALSE;
            }
        }

        if (var_3)
        {
            var_2 = gMusicInfo.soundChannels[i].priority;
            pVariables2 = gMusicInfo.soundChannels[i].pVariables;
            pChannel = &gMusicInfo.soundChannels[i];
        }
    }

    if (pChannel != NULL)
    {
        end:
        SoundChannelNoteOn(pChannel, pVariables, var_0);
    }
}

/**
 * @brief 1cac | 54 | Starts a note on a direct sound channel during a cross fade, limited to the channels the track has
 * 
 * @param pTrack Track data pointer
 * @param pVariables Track variables pointer
 */
static void TrackNoteOnDirectSoundCrossFading(struct TrackData* pTrack, struct TrackVariables* pVariables)
{
    if (pTrack->flags & 0x80)
    {
        if (++pTrack->crossFadeNoteCount <= pTrack->maxSoundChannels)
            TrackNoteOnDirectSound(pTrack, pVariables);
    }
    else if (pTrack->flags & 0x40)
    {
        if (++pTrack->crossFadeNoteCount <= pTrack->maxSoundChannels)
            TrackNoteOnDirectSound(pTrack, pVariables);
    }
}

/**
 * @brief 1d00 | 50 | Starts a note on the PSG channel of a track if its priority allows it
 * 
 * @param pTrack Track data pointer
 * @param pVariables Track variables pointer
 */
static void TrackNoteOnPsg(struct TrackData* pTrack, struct TrackVariables* pVariables)
{
    u8 var_0;
    struct PsgSoundData* pSound;

    if (pTrack->soundPriority + pVariables->priority > UCHAR_MAX)
        var_0 = UCHAR_MAX;
    else
        var_0 = pTrack->soundPriority + pVariables->priority;

    pSound = &gPsgSoundsByChannel[pVariables->channel & 7];
    if (pSound->status == 0 ||
        (var_0 >= pSound->priority &&
        (var_0 != pSound->priority ||
        pVariables <= pSound->pVariables)))
    {
        PsgNoteOn(pSound, pVariables, var_0);
    }
}

/**
 * @brief 1d50 | 50 | Starts a note on the PSG channel of a track if its priority allows it (during a cross fade, identical)
 * 
 * @param pTrack Track data pointer
 * @param pVariables Track variables pointer
 */
static void TrackNoteOnPsgCrossFading(struct TrackData* pTrack, struct TrackVariables* pVariables)
{
    u8 var_0;
    struct PsgSoundData* pSound;

    if (pTrack->soundPriority + pVariables->priority > UCHAR_MAX)
        var_0 = UCHAR_MAX;
    else
        var_0 = pTrack->soundPriority + pVariables->priority;

    pSound = &gPsgSoundsByChannel[pVariables->channel & 7];
    if (pSound->status == 0 ||
        (var_0 >= pSound->priority &&
        (var_0 != pSound->priority ||
        pVariables <= pSound->pVariables)))
    {
        PsgNoteOn(pSound, pVariables, var_0);
    }
}

/**
 * @brief 1da0 | 74 | Starts a note on a PSG channel
 * 
 * @param pSound PSG sound pointer
 * @param pVariables Track variables pointer
 * @param param_3 Priority
 */
static void PsgNoteOn(struct PsgSoundData* pSound, struct TrackVariables* pVariables, u32 param_3)
{
    s16 var_0;
    s16 tmp;

    pSound->priority = param_3;
    pSound->type = pVariables->channel;
    pSound->pan = pVariables->pan;
    pSound->key = pVariables->key;

    if ((pVariables->flags & 0xF0) == 0x80)
        pSound->midiKey = pVariables->drumKey;
    else
        pSound->midiKey = pVariables->key;

    var_0 = pVariables->keyOffset + pSound->midiKey;

    if (var_0 >= 0x80)
        var_0 = 0x7F;
    else if (var_0 < 0)
        var_0 = 0;

    pSound->frequency = GetPsgFrequency(pVariables, var_0, pVariables->pitchOffset);
    pSound->pVariables->pSoundPsg = NULL;
    pSound->pVariables = pVariables;
    pSound->flags |= 2;
    pSound->status = 1;
    pVariables->pSoundPsg = pSound;
}

/**
 * @brief 1e14 | 34 | Removes a sound channel from the channel list of its track
 * 
 * @param pChannel Sound channel pointer
 */
void SoundChannelUnlink(volatile struct SoundChannel* pChannel)
{
    // Linked list?
    if (pChannel->pVariables != NULL)
    {
        if (pChannel->pChannel2 != NULL)
            pChannel->pChannel2->pChannel1 = pChannel->pChannel1;

        if (pChannel->pChannel1 != NULL)
            pChannel->pChannel1->pChannel2 = pChannel->pChannel2;
        else
            pChannel->pVariables->pChannel = pChannel->pChannel2;

        pChannel->pVariables = NULL;
    }
}

/**
 * @brief 1e48 | 6c | Gets the value of the frequency register of a PSG channel for a key
 * 
 * @param pVariables Track variables pointer
 * @param param_2 MIDI key
 * @param param_3 Fine pitch (in 1/256 semitone)
 * @return u16 Frequency register value
 */
static u16 GetPsgFrequency(struct TrackVariables* pVariables, u8 param_2, u8 param_3)
{
    u16 delay;
    u16 temp;

    if ((pVariables->channel & 7) < 4)
    {
        delay = sPsgFrequencyTable[param_2];
        if (param_3 != 0)
        {
            if (param_2 + 1 > 0x7F)
                param_2 = 0x7F;

            temp = (sPsgFrequencyTable[param_2 + 1] - delay) * (param_3 + 1) >> 8;
            delay += temp;
        }
    }
    else
    {
        delay = sNoiseTable[param_2 - 0x15] | (u8)(u32)pVariables->pSample1;
    }
    
    return delay;
}

/**
 * @brief 1eb4 | 50 | Processes the audio command FINE
 * 
 * @param pTrack Track data pointer
 * @param pVariables Track variables pointer
 */
void AudioCommand_Fine(struct TrackData* pTrack, struct TrackVariables* pVariables)
{
    struct SoundChannel* pChannel;
    struct SoundChannel* pNext;

    if (pVariables->pChannel != NULL)
    {
        for (pChannel = pVariables->pChannel; pChannel != NULL; pChannel = pNext)
        {
            pChannel->status = 10;
            pChannel->pVariables = NULL;
            pNext = pChannel->pChannel2;
            pChannel->pChannel2 = NULL;
            pChannel->pChannel1 = NULL;
        }
    }

    if (pVariables->pSoundPsg != NULL)
        pVariables->pSoundPsg->status = 10;

    if (++pTrack->currentTrack == pTrack->amountOfTracks)
    {
        ResetTrack(pTrack);
        pTrack->flags = 0;
        pTrack->currentTrack = 0;
    }

    pVariables->flags = 0;
}

/**
 * @brief 1f04 | 5c | Processes the end command 0xB6: same as FINE, and restores the interrupted music once every track ended
 * 
 * @param pTrack Track data pointer
 * @param pVariables Track variables pointer
 */
void AudioCommand_FineRestoreMusic(struct TrackData* pTrack, struct TrackVariables* pVariables)
{
    struct SoundChannel* pChannel;
    struct SoundChannel* pNext;

    if (pVariables->pChannel != NULL)
    {
        for (pChannel = pVariables->pChannel; pChannel != NULL; pChannel = pNext)
        {
            pChannel->status = 10;
            pChannel->pVariables = NULL;
            pNext = pChannel->pChannel2;
            pChannel->pChannel2 = NULL;
            pChannel->pChannel1 = NULL;
        }
    }

    if (pVariables->pSoundPsg != NULL)
        pVariables->pSoundPsg->status = 10;

    if (++pTrack->currentTrack == pTrack->amountOfTracks)
    {
        ResetTrack(pTrack);
        pTrack->flags = 0;
        pTrack->currentTrack = 0;
        pTrack->queueFlags |= 0x2;
    }

    pVariables->flags = 0;
}

/**
 * @brief 1f60 | 38 | Processes the audio command PEND
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_PatternEnd(struct TrackVariables* pVariables)
{
    s8 i;

    pVariables->pRawData++;

    for (i = ARRAY_SIZE(pVariables->patternStartPointers) - 1; i >= 0; i--)
    {
        if (pVariables->patternStartPointers[i])
        {
            pVariables->pRawData = pVariables->patternStartPointers[i];
            pVariables->patternStartPointers[i] = NULL;
            break;
        }
    }
}

/**
 * @brief 1f98 | 40 | Processes the audio command REPT
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_Repeat(struct TrackVariables* pVariables)
{
    if (pVariables->repeatCount == 0)
    {
        // Setup repeat
        pVariables->pRawData++;

        // Get repeat count
        pVariables->repeatCount = *pVariables->pRawData;

        // Start pattern
        AudioCommand_PatternPlay(pVariables);
        return;
    }

    if (--pVariables->repeatCount == 0)
    {
        // Repeat count reached 0, end pattern
        AudioCommand_PatternEnd(pVariables);
        return;
    }

    pVariables->pRawData++;

    // Replay pattern
    AudioCommand_PatternPlay(pVariables);
}

/**
 * @brief 1fd8 | 10 | Processes the audio command PRIO
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_Priority(struct TrackVariables* pVariables)
{
    pVariables->pRawData++;
    pVariables->priority = *pVariables->pRawData++;
}

/**
 * @brief 1fe8 | 18 | Processes the audio command KEYSH
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_KeyShift(struct TrackVariables* pVariables)
{
    pVariables->pRawData++;
    pVariables->keyShift = *pVariables->pRawData;
    pVariables->flags |= 0x8;
    pVariables->pRawData++;
}

/**
 * @brief 2000 | c0 | Processes the audio command VOICE
 * 
 * @param pTrack Track data pointer
 * @param pVariables Track variables pointer
 */
void AudioCommand_Voice(struct TrackData* pTrack, struct TrackVariables* pVariables)
{
    struct Voice* pVoice;
    u32 channel;

    pVoice = &pTrack->pVoice[*pVariables->pRawData];
    pVariables->channel = pVoice->instrumentType;

    if (pVariables->channel > 0x3F)
    {
        if (pVariables->channel == 0x80)
        {
            pVariables->flags |= 0x80;
            pVariables->pSample2 = pVoice->pSample;
        }
        else if (pVariables->channel == 0x40)
        {
            pVariables->flags |= 0x40;
            pVariables->pSample2 = pVoice->pSample;
            pVariables->envelope2 = pVoice->envelope;
        }
    }
    else
    {
        pVariables->flags &= 0xF;
        pVariables->length = pVoice->length;

        channel = pVariables->channel & 7;

        if (channel == 0)
        {
            pVariables->pSample1 = pVoice->pSample;
        }
        else if (channel < 3)
        {
            if (!(pVoice->panSweep & 0x80) && pVoice->panSweep & 0x70)
                pVariables->sweep = pVoice->panSweep;
            else
                pVariables->sweep = 8;

            pVariables->pSample1 = (u32*)((u32)pVoice->pSample << 0x1E >> 0x18);
        }
        else if (channel == 3)
        {
            UploadSampleToWaveRam(pVoice->pSample);
        }
        else if (channel == 4)
        {
            pVariables->pSample1 = (u32*)((u32)pVoice->pSample << 0x1B >> 0x18);
        }
        
        pVariables->envelope1 = pVoice->envelope;
    }

    pVariables->pRawData++;
}

/**
 * @brief 20c0 | 14 | Processes the audio command VOL
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_Volume(struct TrackVariables* pVariables)
{
    pVariables->volume = *pVariables->pRawData;
    pVariables->flags |= 0x4;
    pVariables->pRawData++;
}

/**
 * @brief 20d4 | 14 | Processes the audio command PAN
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_PanPot(struct TrackVariables* pVariables)
{
    pVariables->pan = *pVariables->pRawData;
    pVariables->flags |= 0x4;
    pVariables->pRawData++;
}

/**
 * @brief 20e8 | 18 | Processes the audio command BEND
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_PitchBend(struct TrackVariables* pVariables)
{
    pVariables->pitchBend = *pVariables->pRawData - C_V;
    pVariables->flags |= 0x8;
    pVariables->pRawData++;
}

/**
 * @brief 2100 | 14 | Processes the audio command BENDR
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_BendRange(struct TrackVariables* pVariables)
{
    pVariables->bendRange = *pVariables->pRawData;
    pVariables->flags |= 0x8;
    pVariables->pRawData++;
}

/**
 * @brief 2114 | 10 | Processes the audio command LFOS
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_LfoSpeed(struct TrackVariables* pVariables)
{
    pVariables->lfoSpeed = (*pVariables->pRawData + 1) / 2;
    pVariables->pRawData++;
}

/**
 * @brief 2124 | 10 | Processes the audio command LFODL
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_LfoDelay(struct TrackVariables* pVariables)
{
    u8 param;

    param = *pVariables->pRawData;
    pVariables->lfoDelay = param;
    pVariables->lfoDelayCounter = param;
    pVariables->pRawData++;
}

/**
 * @brief 2134 | c | Processes the audio command MOD
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_ModulationDepth(struct TrackVariables* pVariables)
{
    pVariables->modulationDepth = *pVariables->pRawData;
    pVariables->pRawData++;
}

/**
 * @brief 2140 | c | Processes the audio command MODT
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_ModulationType(struct TrackVariables* pVariables)
{
    pVariables->modulationType = *pVariables->pRawData;
    pVariables->pRawData++;
}

/**
 * @brief 214c | 18 | Processes the audio command TUNE
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_Tune(struct TrackVariables* pVariables)
{
    pVariables->tune = *pVariables->pRawData - C_V;
    pVariables->flags |= 0x8;
    pVariables->pRawData++;
}

/**
 * @brief 2164 | 30 | Processes the audio command XCMD
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_ExtendCommand(struct TrackVariables* pVariables)
{
    if (*pVariables->pRawData == xIECV)
    {
        pVariables->pRawData++;
        pVariables->echoVolume = *pVariables->pRawData;
        pVariables->pRawData++;
    }

    if (*pVariables->pRawData == xIECL)
    {
        pVariables->pRawData++;
        pVariables->echoLength = *pVariables->pRawData;
        pVariables->pRawData++;
    }
}

/**
 * @brief 2194 | 5c | Processes the audio command EOT
 * 
 * @param pVariables Track variables pointer
 */
void AudioCommand_EndOfTie(struct TrackVariables* pVariables)
{
    struct SoundChannel* pChannel;
    struct PsgSoundData* pSound;
    u32 param;

    if ((s8)*pVariables->pRawData >= 0)
    {
        param = *pVariables->pRawData;
        pVariables->key = param;
        pVariables->pRawData++;
    }
    else
    {
        param = pVariables->key;
    }
    
    if (pVariables->pChannel)
    {
        for (pChannel = pVariables->pChannel; pChannel != NULL; pChannel = pChannel->pChannel2)
        {
            if ((u8)(pChannel->status - 1) < 4 && pChannel->key == param)
            {
                pChannel->status = 5;
                break;
            }
        }
    }

    pSound = pVariables->pSoundPsg;
    if (pSound != NULL && pSound->key == param)
    {
        pSound->status = 5;
        pVariables->pSoundPsg->envelopeCounter = 0;
    }
}

/**
 * @brief 21f0 | 4 | Empty function
 * 
 * @param pVariables Track variables pointer
 */
void Music_EmptyCommand(struct TrackVariables* pVariables)
{
    return;
}

/**
 * @brief 21f4 | 5c | Clears the registers for a PSG sound
 * 
 * @param pSound PSG sound pointer
 * @param channel Channel
 */
void ClearRegistersForPsg(struct PsgSoundData* pSound, u8 channel)
{
    switch (channel)
    {
        case 0:
            WRITE_8(REG_SOUND1CNT_H + 1, 8);
            WRITE_16(REG_SOUND1CNT_X, SOUNDCNT_RESTART_SOUND);
            break;

        case 1:
            WRITE_8(REG_SOUND2CNT_L + 1, 8);
            WRITE_16(REG_SOUND2CNT_H, SOUNDCNT_RESTART_SOUND);
            break;

        case 2:
            WRITE_8(REG_SOUND3CNT_L, 0);
            break;

        case 3:
            WRITE_8(REG_SOUND4CNT_L + 1, 8);
            WRITE_16(REG_SOUND4CNT_H, SOUNDCNT_RESTART_SOUND);
            break;
    }
}

/**
 * @brief 2250 | 48 | Clears the registers for a PSG sound, unused
 * 
 * @param pSound PSG sound pointer
 * @param channel Channel
 */
void ClearRegistersForPsg_Unused(struct PsgSoundData* pSound, u8 channel)
{
    switch (channel)
    {
        case 0:
            WRITE_8(REG_SOUND1CNT_H + 1, 0);
            break;

        case 1:
            WRITE_8(REG_SOUND2CNT_L + 1, 0);
            break;

        case 2:
            WRITE_8(REG_SOUND3CNT_L, 0);
            break;

        case 3:
            WRITE_8(REG_SOUND4CNT_L + 1, 0);
            break;
    }
}
