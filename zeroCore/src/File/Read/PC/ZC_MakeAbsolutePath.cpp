#include "ZC_MakeAbsolutePath.h"

#include <ZC_Config.h>
#include <ZC_string.h>

#include <map>

std::string ZC_MakePathToAssets()
{
    std::string srcPath(ZC_SRC_ASSETS_PATH);
    auto sleshIndex = srcPath.find_last_of("/");
    return ZC_BUILD_ASSETS_PATH + srcPath.substr(sleshIndex, srcPath.size()) + "/";
}

const char* ZC_MakeAbsolutePath(const char* localPath)
{
    if (ZC_BUILD_ASSETS_PATH == "")
    {
        return localPath;
    }
    else
    {
        static std::map<const char*, std::string> paths;
        auto iter = paths.find(localPath);
        if (iter != paths.end())
        {
            return iter->second.c_str();
        }
        else
        {
            static const std::string pathToAssets = ZC_MakePathToAssets();
            return paths.emplace(localPath, pathToAssets + std::string(localPath)).first->second.c_str();
        }
    }
}