#pragma once

#include <ZC/File/Read/ZC_FileReader.h>

#include <fstream>

class ZC_PC_FileReader : public ZC_FileReader
{
public:
    ZC_PC_FileReader(const char* _path) noexcept;

    ~ZC_PC_FileReader() noexcept override;
    
    size_t Read(char* pContainer, size_t count) noexcept override;
    long Seek(long offset) noexcept override;
    void Close() noexcept override;
    bool Eof() noexcept override;
    size_t CurrentReadPosition() noexcept override;
    size_t Size() noexcept override;

private:
    std::ifstream file;
    const size_t size;
};