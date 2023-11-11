#include "ZC_PC_FileReader.h"

#include <ZC/ErrorLogger/ZC_ErrorLogger.h>
#include "ZC_MakeAbsolutePath.h"

ZC_PC_FileReader::ZC_PC_FileReader(const char* const& _path, const char* const& callingFilePath, const int& callingFileLine) noexcept
    : ZC_FileReader(ZC_MakeAbsolutePath(_path))
{
    file.open(path, std::ios::binary);
    if (!file.is_open())
    {
        ZC_ErrorLogger::Err("Fail open file: " + std::string(path), callingFilePath, callingFileLine);
        file.close();
        return;
    }
    ZC_ErrorLogger::Clear();
}

ZC_PC_FileReader::~ZC_PC_FileReader() noexcept
{
    Close();
}

size_t ZC_PC_FileReader::Read(char* pContainer, size_t size, const char* const& callingFilePath, const int& callingFileLine) noexcept
{
    if (!file.is_open())
    {
        ZC_ErrorLogger::Clear();
        return 0;
    }

    size_t remainingSize = Size(callingFilePath, callingFileLine) - CurrentReadPosition();
    size = size > remainingSize ? remainingSize : size;

    file.read(pContainer, size);
    
    if (file.fail())
    {
        ZC_ErrorLogger::Err("Fail read file: " + std::string(path), callingFilePath, callingFileLine);
        return 0;
    }
    
    ZC_ErrorLogger::Clear();
    return size;
}

long ZC_PC_FileReader::Seek(long offset, const char* const& callingFilePath, const int& callingFileLine) noexcept
{
    if (!file.is_open())
    {
        ZC_ErrorLogger::Clear();
        return 0;
    }

    size_t fullLength = Size(callingFilePath, callingFileLine);
    size_t remainingLength = fullLength - CurrentReadPosition();
    if ((offset > 0 && offset > remainingLength) || (offset < 0 && offset * -1 > fullLength - remainingLength))
    {
        ZC_ErrorLogger::Clear();
        return 0;
    }
    
    file.seekg(offset, file.cur);
    if (file.fail())
    {
        ZC_ErrorLogger::Err("Fail seek file: " + std::string(path), callingFilePath, callingFileLine);
        return 0;
    }

    ZC_ErrorLogger::Clear();
    return offset;
}

void ZC_PC_FileReader::Close() noexcept
{
    file.close();
}

bool ZC_PC_FileReader::Eof(const char* const& callingFilePath, const int& callingFileLine) noexcept
{
    return Size(callingFilePath, callingFileLine) - CurrentReadPosition() == 0;
}

size_t ZC_PC_FileReader::CurrentReadPosition() noexcept
{
    if (!file.is_open()) return 0;
    return file.tellg();
}

size_t ZC_PC_FileReader::Size(const char* const& callingFilePath, const int& callingFileLine) noexcept
{
    if (!file.is_open())
    {
        ZC_ErrorLogger::Clear();
        return 0;
    }

    size_t currentPosition = file.tellg();
    file.seekg(0, file.end);
    if (file.fail())
    {
        ZC_ErrorLogger::Err("Fail seek file: " + std::string(path), callingFilePath, callingFileLine);
        return 0;
    }

    size_t fullLength = file.tellg();
    file.seekg(currentPosition, file.beg);
    if (file.fail())
    {
        ZC_ErrorLogger::Err("Fail seek file: " + std::string(path), callingFilePath, callingFileLine);
        return 0;
    }

    ZC_ErrorLogger::Clear();
    return fullLength;
}