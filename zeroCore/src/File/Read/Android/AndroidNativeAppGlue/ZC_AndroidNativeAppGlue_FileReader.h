#pragma once

#include <ZC/File/Read/ZC_FileReader.h>

#include <ZC/Video/ZC_android_app.h>

class ZC_AndroidNativeAppGlue_FileReader : public ZC_FileReader, public ZC_android_app
{
public:
    ZC_AndroidNativeAppGlue_FileReader(const char* _path) noexcept;

    ~ZC_AndroidNativeAppGlue_FileReader() noexcept override;
    
    size_t Read(char* pContainer, size_t count) noexcept override;
    long Seek(long offset) noexcept override;
    void Close() noexcept override;
    bool Eof() noexcept override;
    size_t CurrentReadPosition() noexcept override;
    size_t Size() noexcept override;

private:
    AAsset* file;
};