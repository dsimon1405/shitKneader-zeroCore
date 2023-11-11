#pragma once

#include "ZC_AudioStream.h"

/*
Class for creating an audio stream.
*/
class ZC_Audio
{
public:
    ZC_Audio() = delete;

    /*
    Create ZC_AudioStream object.

    Params:
    _audioSet - a set of audio parameters for an audio stream.

    Return:
    On success true, else false (ZC_ErrorLogger::ErrorMessage() - for more information).
    */
    static bool MakeAudioStream(const ZC_AudioSet& _audioSet) noexcept;

    static void CloseAudioStream() noexcept
    {
        upAudioStream = nullptr;
    }

    static bool ReopenAudioStream() noexcept
    {
        static const ZC_AudioSet& setAudioStream = ZC_AudioStream::GetAudioSet();
        if (!upAudioStream && setAudioStream.frequency != 0)
        {
            MakeAudioStream(setAudioStream);
            return true;
        }

        return false;
    }

private:
    static inline std::unique_ptr<ZC_AudioStream> upAudioStream = nullptr;

    template<typename TClass>
    static bool CreateAudioStream(const ZC_AudioSet& audioSet) noexcept
    {
        if (!upAudioStream)
        {
            ZC_AudioStream* pAudioStream = dynamic_cast<ZC_AudioStream*>(new TClass(audioSet));
            if (!ZC_ErrorLogger::WasError())
            {
                upAudioStream = std::unique_ptr<ZC_AudioStream>(pAudioStream);
                return true;
            }
        
            delete pAudioStream;
            pAudioStream = nullptr;
        }
    
        return false;
    }
};