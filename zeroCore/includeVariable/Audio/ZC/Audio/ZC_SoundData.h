#pragma once

#include "ZC_AudioSet.h"
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

#include <concepts>
template <typename TType>
concept ZC_cBitsPerSample = std::same_as<TType, int16_t> || std::same_as<TType, int32_t>;

class ZC_SoundData
{
public:
    
    ZC_SoundData() = default;
    ZC_SoundData(char* _data, const unsigned int& _size, const ZC_AudioSet& _audioSet) noexcept;

    ZC_SoundData(const ZC_SoundData&) = delete;
    ZC_SoundData& operator = (const ZC_SoundData&) = delete;

    ZC_SoundData(ZC_SoundData&& soundData) noexcept;
    ZC_SoundData& operator = (ZC_SoundData&& soundData) noexcept;

    ~ZC_SoundData() noexcept;

    template <ZC_cBitsPerSample TType>
    unsigned int Size() const noexcept
    {
        return dataSize / sizeof(TType);
    }

    template <ZC_cBitsPerSample TType>
    TType GetValue(const unsigned int& index) const noexcept
    {
        static unsigned int size = Size<TType>();
        if (index >= size)
        {
            ZC_ErrorLogger::Err("ZC_SoundData out of range exception!", __FILE__, __LINE__);
            return 0;
        }

        return reinterpret_cast<TType*>(data)[index];
    }

    ZC_AudioSet GetAudioSet() const noexcept;

private:
    int32_t dataSize = 0;
    char* data = nullptr;
    ZC_AudioSet audioSet;
};