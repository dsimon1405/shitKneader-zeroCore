#pragma once

#include <ZC/ErrorLogger/ZC_ErrorLogger.h>
#include <ZC/Tools/ZC_uptr.h>

class ZC_FileReader;
using ZC_upFileReader = ZC_uptr<ZC_FileReader>;

/*
File read wrapper.
*/
class ZC_FileReader
{
public:
    ZC_FileReader() = delete;

    ZC_FileReader(const ZC_FileReader&) = delete;
    ZC_FileReader& operator=(const ZC_FileReader&) = delete;
    ZC_FileReader(ZC_FileReader&&) = delete;
    ZC_FileReader& operator=(ZC_FileReader&&) = delete;

    virtual ~ZC_FileReader() = default;

    /*
    Create ZC_FileReader.

    Params:
    path - absolute path to the file.
    callingFilePath - path to the calling file (optional, required to log an error, can be use __FILE__).
    callingFileLine - line in the calling file (optional, required to log an error, can be use __LINE__).

    Return:
    If ZC_FileReader created - unique_ptr<ZC_FileReader>, otherwise nullptr (ZC_ErrorLogger::ErrorMessage() - for more information).
    */
    static ZC_upFileReader MakeReader(const char* const& path, const char* const& callingFilePath = nullptr, const int& callingFileLine = 0);

    /*
    Read a sequence of bytes from the current read position.

    Params:
    pContainer - pointer to the element in which the bytes will be written.
    size - the number of bytes that will be read from the file (the read pointer will be moved to this value or to the end of the file).
    callingFilePath - path to the calling file (optional, required to log an error, can be use __FILE__).
    callingFileLine - line in the calling file (optional, required to log an error, can be use __LINE__).

    Return:
    Number of bytes read or 0 in case of error (in second case ZC_ErrorLogger::ErrorMessage() - for more information).
    */
    virtual size_t Read(char* pContainer, size_t size, const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept = 0;

    /*
    Move read pointer. If the move is outside the file range, the move pointer will not move.

    Params:
    offset - value to move the pointer to.
    callingFilePath - path to the calling file (optional, required to log an error, can be use __FILE__).
    callingFileLine - line in the calling file (optional, required to log an error, can be use __LINE__).

    Return:
    The offset to which the pointer was moved. If the move goes outside the file's range, it will return 0 also in case of an error. (in second case ZC_ErrorLogger::ErrorMessage() - for more information).
    */
    virtual long Seek(long offset, const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept = 0;

    /*
    Close file.
    */
    virtual void Close() noexcept = 0;

    /*
    Checking whether the read pointer has reached the end of the file.

    Params:
    callingFilePath - path to the calling file (optional, required to log an error, can be use __FILE__).
    callingFileLine - line in the calling file (optional, required to log an error, can be use __LINE__).

    Return:
    On the end of the file - true, otherwise false.
    */
    virtual bool Eof(const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept = 0;

    /*
    Help to know current read position.

    Return:
    Current read position or 0 if file close.
    */
    virtual size_t CurrentReadPosition() noexcept = 0;

    /*
    Help to know full file lenth in bytes.

    Params:
    callingFilePath - path to the calling file (optional, required to log an error, can be use __FILE__).
    callingFileLine - line in the calling file (optional, required to log an error, can be use __LINE__).

    Return:
    Full file length or 0 on fail operation (in second case ZC_ErrorLogger::ErrorMessage() - for more information).
    */
    virtual size_t Size(const char* const& callingFilePath = nullptr, const int& callingFileLine = 0) noexcept = 0;

protected:
    const char* path;

    ZC_FileReader(const char* _path) noexcept
        : path(_path)
    {}
};