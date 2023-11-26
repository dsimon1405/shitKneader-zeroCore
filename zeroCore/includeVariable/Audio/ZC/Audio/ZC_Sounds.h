#pragma once

#include <ZC/File/Read/ZC_FileReader.h>
#include <ZC/Audio/ZC_Sound.h>

#include <map>
#include <shared_mutex>
#include <condition_variable>

//  Class for loading WAV files, and getting sounds.
class ZC_Sounds
{
public:
    ZC_Sounds() = delete;
    
    /*
    Loads a WAV file. It may happen that the file will be successfully read for the number of bytes specified in the file to be read, but this value will be less than the number of bytes in the file, in this case true will be returned, but ZC_ErrorLogger::ErrorMessage() will contain a message about incomplete reading file.

    Params:
    name - sound's name.
    path - the path to the file is full or relative depending on the settings CMakeLists.txt(ZC_BUILD_ASSETS_PATH)

    Return:
    On success true, otherwise false (ZC_ErrorLogger::ErrorMessage() - for more information).
    */
    static bool LoadWAV(const std::string& name, const char* path) noexcept;

    /*
    Helps tp get loaded sound.

    Params:
    name - sound's name.

    Return:
    If sound is loaded a unique pointer to the sound, otherwise nullptr.
    */
    static ZC_upSound GetSound(const std::string& name) noexcept;

private:
    static inline std::map<std::string, ZC_SoundData> sounds;
    static inline std::shared_mutex soundsSMutex;
    static inline std::condition_variable_any soundsCVA;

    static ZC_SoundData ReadWAV(const char* path) noexcept;

    template<ZC_cBitsPerSample T>
    static bool DeleteStartNullData(ZC_upFileReader& file, int32_t& size, const char* path) noexcept;

    static bool ConstCharEqual(const char* first, char* second) noexcept;
};

template<ZC_cBitsPerSample T>
bool ZC_Sounds::DeleteStartNullData(ZC_upFileReader& file, int32_t& size, const char* path) noexcept
{
    T readData = 0;
    static size_t readDataSizeof = sizeof(readData);
    do
    {
        size -= readDataSizeof;
        if (file->Read(reinterpret_cast<char*>(&readData), readDataSizeof) != readDataSizeof)
        {
            file->Close();
            return false;
        }
        if (file->Eof())
        {
            ZC_ErrorLogger::Err("All data is 0 in the file: " + std::string(path), __FILE__, __LINE__);
            file->Close();
            return false;
        }

    } while (readData == 0);

    size += readDataSizeof;
    if (file->Seek(static_cast<int>(readDataSizeof) * -1) != readDataSizeof * -1)
    {
        file->Close();
        return false;
    }
    return true;
}
