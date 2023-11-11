#pragma once

#include <ZC/Tools/Signal/ZC_Signal.h>
#include "ZC_StreamSound.h"

/*
Audio stream class.
*/
class ZC_AudioStream
{
public:
    enum State
    {
        //  The stream will play sounds.
        Active,
        //  The stream will not play sounds.
        Passive,
        //  Stream does not exist.
        Null
    };

    ZC_AudioStream(const ZC_AudioStream&) = delete;
    ZC_AudioStream& operator = (const ZC_AudioStream&) = delete;
    ZC_AudioStream(ZC_AudioStream&&) = delete;
    ZC_AudioStream& operator = (ZC_AudioStream&&) = delete;

    virtual ~ZC_AudioStream() = default;

    //  Make the audio stream active if it exists.
    static void MakeActive() noexcept;

    //  Make the audio stream passive if it exists.
    static void MakePassive() noexcept;

    /*
    Helps to get the state of an audio stream.

    Return:
    Current ZC_AudioStream::State.
    */
    static typename ZC_AudioStream::State GetState() noexcept;

    /*
    Helps to get the set of an audio stream.

    Return:
    ZC_AudioSet.
    */
    static const ZC_AudioSet& GetAudioSet() noexcept;

protected:
    static inline ZC_AudioSet audioSet;
    static inline ZC_Signal<ZC_StreamSound*()> sGetpZC_StreamSound;

    ZC_AudioStream() = default;
    ZC_AudioStream(const ZC_AudioSet& _audioSet) noexcept;

    static void GetStreamData(void* pDataContainer, const int& bytesCount) noexcept;

private:
    static inline ZC_AudioStream::State stateAudioStream = ZC_AudioStream::State::Null;

    template <ZC_cBitsPerSample TType>
    static void FillData(void* pDataContainer, const int& bytesCount, std::vector<ZC_StreamSound*>& sounds)
    {
        TType* pData = static_cast<TType*>(pDataContainer);
        unsigned long pDataSize = bytesCount / sizeof(TType);
        for (size_t pDataIndex = 0; pDataIndex < pDataSize; ++pDataIndex)
        {
            long long soundsData = 0;
            long long soundsSize = sounds.size();
            long long pDataDivider = soundsSize < 2 ? 2 : soundsSize;
            
            for (std::vector<ZC_StreamSound*>::iterator soundsIter = sounds.begin(); soundsIter != sounds.end();)
            {
                TType data = 0;
                soundsIter = (*soundsIter)->Pop(data) ? ++soundsIter : sounds.erase(soundsIter);
                soundsData += data;
            }

            pData[pDataIndex] = stateAudioStream == ZC_AudioStream::State::Active ? soundsData / pDataDivider : 0;
        }
    }
};