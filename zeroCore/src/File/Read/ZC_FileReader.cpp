#include <ZC/File/Read/ZC_FileReader.h>

#include <ZC_Config.h>
#include "../../Tools/ZC_uptrCreateWithErrorCheck.h"

#if defined(ZC_PC)
    #include "PC/ZC_PC_FileReader.h"
    ZC_upFileReader ZC_FileReader::MakeReader(const char* const& path, const char* const& callingFilePath, const int& callingFileLine)
    {
        return ZC_uptrCreateWithErrorCheck<ZC_FileReader, ZC_PC_FileReader>(path, callingFilePath, callingFileLine);
    }
#elif defined(ZC_ANDROID)
    #if defined(ZC_ANDROID_NATIVE_APP_GLUE)
        #include "Android/AndroidNativeAppGlue/ZC_AndroidNativeAppGlue_FileReader.h"
        ZC_upFileReader ZC_FileReader::MakeReader(const char* const& path, const char* const& callingFilePath, const int& callingFileLine)
        {
            return ZC_uptrCreateWithErrorCheck<ZC_FileReader, ZC_AndroidNativeAppGlue_FileReader>(path, callingFilePath, callingFileLine);
        }
    #endif
#endif