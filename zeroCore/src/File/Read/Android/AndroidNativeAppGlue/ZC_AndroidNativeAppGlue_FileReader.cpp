#include "ZC_AndroidNativeAppGlue_FileReader.h"

#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

ZC_AndroidNativeAppGlue_FileReader::ZC_AndroidNativeAppGlue_FileReader(const char* _path) noexcept
    : ZC_FileReader(_path)
{
    file = AAssetManager_open(pAndroidApp->activity->assetManager, path, AASSET_MODE_BUFFER);
    if (!file)
    {
        ZC_ErrorLogger::Err("Fail open file: " + std::string(path), __FILE__, __LINE__);
        return;
    }
    ZC_ErrorLogger::Clear();
}

ZC_AndroidNativeAppGlue_FileReader::~ZC_AndroidNativeAppGlue_FileReader() noexcept
{
    if (file)
    {
        AAsset_close(file);
        file = nullptr;
    }
}

size_t ZC_AndroidNativeAppGlue_FileReader::Read(char* pContainer, size_t count) noexcept
{
    if (!file || AAsset_getRemainingLength(file) == 0)
    {
        ZC_ErrorLogger::Clear();
        return 0;
    }

    int readCount = AAsset_read(file, reinterpret_cast<void*>(pContainer), count);

    if (readCount == 0 && count != 0)
    {
        ZC_ErrorLogger::Err("Fail read file: " + std::string(path), __FILE__, __LINE__);
        return 0;
    }

    ZC_ErrorLogger::Clear();
    return count;
}

long ZC_AndroidNativeAppGlue_FileReader::Seek(long offset) noexcept
{
    if (!file)
    {
        ZC_ErrorLogger::Clear();
        return 0;
    }

    long remainingLength = AAsset_getRemainingLength(file);
    if ((offset > 0 && offset > remainingLength) || (offset < 0 && offset * -1 > AAsset_getLength(file) - remainingLength))
    {
        ZC_ErrorLogger::Clear();
        return 0;
    }

    long seekResult = AAsset_seek(file, offset, SEEK_CUR);
    if (seekResult == -1)
    {
        ZC_ErrorLogger::Err("Fail seek file: " + std::string(path), __FILE__, __LINE__);
        return 0;
    }

    ZC_ErrorLogger::Clear();
    return offset;
}

void ZC_AndroidNativeAppGlue_FileReader::Close() noexcept
{
    if (file)
    {
        AAsset_close(file);
        file = nullptr;
    }
}

bool ZC_AndroidNativeAppGlue_FileReader::Eof() noexcept
{
    return file != nullptr && AAsset_getRemainingLength(file) == 0;
}

size_t ZC_AndroidNativeAppGlue_FileReader::CurrentReadPosition() noexcept
{
    return file ? AAsset_getRemainingLength(file) : 0;
}

size_t ZC_AndroidNativeAppGlue_FileReader::Size() noexcept
{
    return file ? AAsset_getLength(file) : 0;
}