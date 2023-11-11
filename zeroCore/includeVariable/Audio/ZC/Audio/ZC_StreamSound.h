#pragma once

#include "ZC_SoundData.h"
#include <ZC/Tools/Signal/ZC_Signal.h>

#include <mutex>

class ZC_StreamSound
{
public:
    enum SoundState
    {
        Play,
        PlayLoop,
        Pause,
        Stop
    };

    ZC_StreamSound() = delete;

    ZC_StreamSound(ZC_StreamSound&&) = delete;
    ZC_StreamSound& operator = (const ZC_StreamSound&) = delete;
    ZC_StreamSound(const ZC_StreamSound&) = delete;
    ZC_StreamSound& operator = (ZC_StreamSound&&) = delete;

    virtual ~ZC_StreamSound() = default;

    template <ZC_cBitsPerSample TType>
    bool Pop(TType& value) noexcept
    {
        static unsigned int soundDataSize = soundData->Size<TType>();
        std::lock_guard<std::mutex> lock(soundStateMutex);
        if (soundState == SoundState::Stop || soundState == SoundState::Pause || soundDataSize == 0)
        {
            value = 0;
            return false;
        }
        
        value = soundData->GetValue<TType>(soundDataIndex++) * volume;
        if (soundDataIndex >= soundDataSize)
        {
            soundDataIndex = 0;
            if (soundState != SoundState::PlayLoop)
            {
                soundState = SoundState::Stop;
                conGetpZC_StreamSound->Disconnect();
                return false;
            }
        }
        
        return true;
    }

protected:
    SoundState soundState = SoundState::Stop;
    const ZC_SoundData* soundData;
    unsigned int soundDataIndex = 0;
    double volume = 1.0;
    ZC_SignalConnection* conGetpZC_StreamSound;
    std::mutex soundStateMutex;

    ZC_StreamSound(const ZC_SoundData* _soundData) noexcept;
};