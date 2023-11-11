#include <ZC/File/Read/ZC_FileReader.h>

#include <ZC_Config.h>
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

#if defined(ZC_PC)
    #include "PC/ZC_PC_FileReader.h"
    ZC_upFileReader ZC_FileReader::MakeReader(const char* const& path, const char* const& callingFilePath, const int& callingFileLine)
    {
        return CreateReader<ZC_PC_FileReader>(path, callingFilePath, callingFileLine);
    }
#elif defined(ZC_ANDROID)
    #if defined(ZC_ANDROID_NATIVE_APP_GLUE)
        #include "Android/AndroidNativeAppGlue/ZC_AndroidNativeAppGlue_FileReader.h"
        ZC_upFileReader ZC_FileReader::MakeReader(const char* const& path, const char* const& callingFilePath, const int& callingFileLine)
        {
            return CreateReader<ZC_AndroidNativeAppGlue_FileReader>(path, callingFilePath, callingFileLine);
            // return std::unique_ptr<ZC_FileReader>(dynamic_cast<ZC_FileReader*>(new ZC_AndroidNativeAppGlue_FileReader(path, callingFilePath, callingFileLine)));
        }
    #endif
#endif