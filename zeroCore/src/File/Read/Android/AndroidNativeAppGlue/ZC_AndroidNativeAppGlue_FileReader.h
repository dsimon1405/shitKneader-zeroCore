#pragma once

#include <ZC/File/Read/ZC_FileReader.h>

#include <ZC/Video/ZC_android_app.h>

class ZC_AndroidNativeAppGlue_FileReader : public ZC_FileReader, public ZC_android_app
{
public:
    ZC_AndroidNativeAppGlue_FileReader(const char* const& _path, const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept;

    ~ZC_AndroidNativeAppGlue_FileReader() noexcept override;
    
    size_t Read(char* pContainer, size_t size, const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept override;
    long Seek(long offset, const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept override;
    void Close() noexcept override;
    bool Eof(const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept override;
    size_t CurrentReadPosition() noexcept override;
    size_t Size(const char* const& callingFilePath= nullptr, const int& callingFileLine = 0) noexcept override;

private:
    AAsset* file;
};