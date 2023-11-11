#pragma once

#include <ZC/File/Read/ZC_FileReader.h>

#include <fstream>

class ZC_PC_FileReader : public ZC_FileReader
{
public:
    ZC_PC_FileReader(const char* const& _path, const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept;

    ~ZC_PC_FileReader() noexcept override;
    
    size_t Read(char* pContainer, size_t size, const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept override;
    long Seek(long offset, const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept override;
    void Close() noexcept override;
    bool Eof(const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept override;
    size_t CurrentReadPosition() noexcept override;
    size_t Size(const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept override;

private:
    std::ifstream file;
};