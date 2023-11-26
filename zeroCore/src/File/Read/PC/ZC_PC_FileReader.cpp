#include "ZC_PC_FileReader.h"

#include <ZC/ErrorLogger/ZC_ErrorLogger.h>
#include "ZC_MakeAbsolutePath.h"

ZC_PC_FileReader::ZC_PC_FileReader(const char* _path) noexcept
    : ZC_FileReader(ZC_MakeAbsolutePath(_path)),
    file(path, std::ios::binary),
    size(Size())
{
    if (!file.is_open())
    {
        ZC_ErrorLogger::Err("Fail open file: " + std::string(path), __FILE__, __LINE__);
        file.close();
        return;
    }
    ZC_ErrorLogger::Clear();
}

ZC_PC_FileReader::~ZC_PC_FileReader() noexcept
{
    Close();
}

size_t ZC_PC_FileReader::Read(char* pContainer, size_t count) noexcept
{
    if (!file.is_open())
    {
        ZC_ErrorLogger::Clear();
        return 0;
    }

    size_t remainingSize = size - CurrentReadPosition();
    count = count > remainingSize ? remainingSize : count;

    file.read(pContainer, count);
    
    if (file.fail())
    {
        ZC_ErrorLogger::Err("Fail read file: " + std::string(path), __FILE__, __LINE__);
        return 0;
    }
    
    ZC_ErrorLogger::Clear();
    return count;
}

long ZC_PC_FileReader::Seek(long offset) noexcept
{
    if (!file.is_open())
    {
        ZC_ErrorLogger::Clear();
        return 0;
    }

    size_t remainingLength = size - CurrentReadPosition();
    if ((offset > 0 && offset > remainingLength) || (offset < 0 && offset * -1 > size - remainingLength))
    {
        ZC_ErrorLogger::Clear();
        return 0;
    }
    
    file.seekg(offset, file.cur);
    if (file.fail())
    {
        ZC_ErrorLogger::Err("Fail seek file: " + std::string(path), __FILE__, __LINE__);
        return 0;
    }

    ZC_ErrorLogger::Clear();
    return offset;
}

void ZC_PC_FileReader::Close() noexcept
{
    file.close();
}

bool ZC_PC_FileReader::Eof() noexcept
{
    return size - CurrentReadPosition() == 0;
}

size_t ZC_PC_FileReader::CurrentReadPosition() noexcept
{
    if (!file.is_open()) return 0;
    return file.tellg();
}

size_t ZC_PC_FileReader::Size() noexcept
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
        ZC_ErrorLogger::Err("Fail seek file: " + std::string(path), __FILE__, __LINE__);
        return 0;
    }

    size_t fullLength = file.tellg();
    file.seekg(currentPosition, file.beg);
    if (file.fail())
    {
        ZC_ErrorLogger::Err("Fail seek file: " + std::string(path), __FILE__, __LINE__);
        return 0;
    }

    ZC_ErrorLogger::Clear();
    return fullLength;
}