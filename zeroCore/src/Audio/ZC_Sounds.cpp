#include <ZC/Audio/ZC_Sounds.h>

#include "ZC_WAVHeader.h"
#include <ZC/Tools/ZC_DynamicArray.h>

bool ZC_Sounds::LoadWAV(const std::string& name, const char* const& path) noexcept
{
    std::unique_lock<std::shared_mutex> soundsULock(soundsSMutex);
    auto soundsIter = sounds.find(name);
    if (soundsIter != sounds.end())
    {
        ZC_ErrorLogger::Err("Already exists sound: " + name, __FILE__, __LINE__);
        return false;
    }

    soundsIter = sounds.emplace(name, ZC_SoundData()).first;

    soundsULock.unlock();
    soundsCVA.notify_all();

    ZC_ErrorLogger::Clear();
    ZC_SoundData soundData = ReadWAV(path);
    
    soundsULock.lock();
    if (soundData.GetAudioSet().frequency == 0)
    {
        sounds.erase(soundsIter);
        soundsULock.unlock();
        soundsCVA.notify_all();

        if (ZC_ErrorLogger::WasError()) return false;
        
        ZC_ErrorLogger::Err("Empty sound: " + std::string(path), __FILE__, __LINE__);
        return false;
    }

    soundsIter->second = std::move(soundData);
    soundsULock.unlock();
    soundsCVA.notify_all();

    return true;
}

ZC_upSound ZC_Sounds::GetSound(const std::string& name) noexcept
{
    std::shared_lock<std::shared_mutex> soundsSLock(soundsSMutex);
    std::map<std::string, ZC_SoundData>::iterator soundsIter;
    soundsCVA.wait(soundsSLock, [&]
        {
            soundsIter = sounds.find(name);
            if (soundsIter == sounds.end()) return true;
            
            return soundsIter->second.GetAudioSet().frequency != 0;
        });

    if (soundsIter == sounds.end()) return nullptr;
    
    return ZC_uptrMake<ZC_Sound>(&soundsIter->second);
}

ZC_SoundData ZC_Sounds::ReadWAV(const char* const& path) noexcept
{
    ZC_upFileReader file = ZC_FileReader::MakeReader(path, __FILE__, __LINE__);
    if (!file) return ZC_SoundData();

    WAVHeader header;

    if (file->Seek(8, __FILE__, __LINE__) != 8)
    {
        file->Close();
        return ZC_SoundData();
    }

    static size_t formatSize = sizeof(header.format);
    if (file->Read(&header.format[0], formatSize, __FILE__, __LINE__) != formatSize)
    {
        file->Close();
        return ZC_SoundData();
    }

    static const char* WAVEString = "WAVE";
    if (!ConstCharEqual(WAVEString, header.format))
    {
        ZC_ErrorLogger::Err("File format != 'WAVE': " + std::string(path), __FILE__, __LINE__);
        file->Close();
        return ZC_SoundData();
    }

    if (file->Seek(4, __FILE__, __LINE__) != 4)
    {
        file->Close();
        return ZC_SoundData();
    }

    static size_t subchunk1SizeSize = sizeof(header.subchunk1Size);
    if (file->Read(reinterpret_cast<char*>(&header.subchunk1Size), subchunk1SizeSize, __FILE__, __LINE__) != subchunk1SizeSize)
    {
        file->Close();
        return ZC_SoundData();
    }

    if (file->Seek(2, __FILE__, __LINE__) != 2)
    {
        file->Close();
        return ZC_SoundData();
    }

    static size_t channelsSize = sizeof(header.channels);
    if (file->Read(reinterpret_cast<char*>(&header.channels), channelsSize, __FILE__, __LINE__) != channelsSize)
    {
        file->Close();
        return ZC_SoundData();
    }

    static size_t frequencySize = sizeof(header.frequency);
    if (file->Read(reinterpret_cast<char*>(&header.frequency), frequencySize, __FILE__, __LINE__) != frequencySize)
    {
        file->Close();
        return ZC_SoundData();
    }

    if (file->Seek(6, __FILE__, __LINE__) != 6)
    {
        file->Close();
        return ZC_SoundData();
    }

    static size_t bitsPerSampleSize = sizeof(header.bitsPerSample);
    if (file->Read(reinterpret_cast<char*>(&header.bitsPerSample), bitsPerSampleSize, __FILE__, __LINE__) != bitsPerSampleSize)
    {
        file->Close();
        return ZC_SoundData();
    }

    if (header.subchunk1Size != 16)
    {
        if (file->Seek(header.subchunk1Size - 16, __FILE__, __LINE__) != header.subchunk1Size - 16)
        {
            file->Close();
            return ZC_SoundData();
        }
    }

    static size_t subchunk2IdSize = sizeof(header.subchunk2Id);
    if (file->Read(&header.subchunk2Id[0], subchunk2IdSize, __FILE__, __LINE__) != subchunk2IdSize)
    {
        file->Close();
        return ZC_SoundData();
    }

    static size_t subchunk2SizeSize = sizeof(header.subchunk2Size);
    if (file->Read(reinterpret_cast<char*>(&header.subchunk2Size), subchunk2SizeSize, __FILE__, __LINE__) != subchunk2SizeSize)
    {
        file->Close();
        return ZC_SoundData();
    }

    static const char* dataString = "data";
    //  if subchunk2Id != 'data', miss all till find 'data'
    while (!ConstCharEqual(dataString, header.subchunk2Id))
    {
        if (file->Seek(header.subchunk2Size, __FILE__, __LINE__) != header.subchunk2Size)
        {
            file->Close();
            return ZC_SoundData();
        }

        if (file->Read(&header.subchunk2Id[0], subchunk2IdSize, __FILE__, __LINE__) != subchunk2IdSize)
        {
            file->Close();
            return ZC_SoundData();
        }

        if (file->Read(reinterpret_cast<char*>(&header.subchunk2Size), subchunk2SizeSize, __FILE__, __LINE__) != subchunk2SizeSize)
        {
            file->Close();
            return ZC_SoundData();
        }

        if (file->Eof())
        {
            ZC_ErrorLogger::Err("Can't find chunk2Id == 'data': " + std::string(path), __FILE__, __LINE__);
            file->Close();
            return ZC_SoundData();
        }
    }

    ZC_AudioSet audioSet(
    audioSet.channels = header.channels == 1 ? ZC_AudioSet::Channels::Mono : ZC_AudioSet::Channels::Stereo,
    audioSet.frequency = header.frequency,
    audioSet.bitsPerSample = header.bitsPerSample == 16 ? ZC_AudioSet::BitsPerSample::S16 : ZC_AudioSet::BitsPerSample::S32);

    switch (audioSet.bitsPerSample)
    {
        case ZC_AudioSet::BitsPerSample::S16:
            if (!DeleteStartNullData<int16_t>(file, header.subchunk2Size, path)) return ZC_SoundData();
            header.subchunk2Size -= header.subchunk2Size % sizeof(int16_t);
            break;
        case ZC_AudioSet::BitsPerSample::S32:
            if (!DeleteStartNullData<int32_t>(file, header.subchunk2Size, path)) return ZC_SoundData();
            header.subchunk2Size -= header.subchunk2Size % sizeof(int32_t);
            break;
    }

    ZC_DynamicArray<char> data(header.subchunk2Size);
    if (file->Read(data.pArray, header.subchunk2Size, __FILE__, __LINE__) != header.subchunk2Size)
    {
        file->Close();
        return ZC_SoundData();
    }

    ZC_ErrorLogger::Clear();
    if (!file->Eof())
    {
        ZC_ErrorLogger::Err("Read " + std::to_string(header.subchunk2Size)
            + " bytes, until the end of the file " + std::to_string(file->Size() - file->CurrentReadPosition())
            + " bytes in the file: " + std::string(path), __FILE__, __LINE__);
    }

    return ZC_SoundData(std::move(data), audioSet);
}

bool ZC_Sounds::ConstCharEqual(const char* const& first, char* const& second) noexcept
{
    for (size_t i = 0; ; ++i)
    {
        if (first[i] == '\0')
        {
            return true;
        }
        if (first[i] != second[i])
        {
            return false;
        }
    }
}