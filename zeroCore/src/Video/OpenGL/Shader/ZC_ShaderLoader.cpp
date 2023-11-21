#include <ZC/Video/OpenGL/Shader/ZC_ShaderLoader.h>

#include <ZC/File/Read/ZC_FileReader.h>
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

ZC_ShaderCode ZC_ShaderLoader::LoadShaderCode(const char* const& vertexPath, const char* const& fragmentPath, const char* const& geometryPath) noexcept
{

    ZC_DynamicArray<char> vertexCode = ReadShaderFile(vertexPath, ShaderType::Vertex);
    if (!vertexCode.pArray) return {};

    ZC_DynamicArray<char> fragmentCode = ReadShaderFile(fragmentPath, ShaderType::Fragment);
    if (!fragmentCode.pArray) return {};

    ZC_DynamicArray<char> geometryCode;
    if (geometryPath)
    {
        geometryCode = ReadShaderFile(geometryPath, ShaderType::Geometry);
        if (!geometryCode.pArray) return {};
    }

    return { std::move(vertexCode), std::move(fragmentCode), std::move(geometryCode) };
}

ZC_DynamicArray<char> ZC_ShaderLoader::ReadShaderFile(const char* path, const ShaderType& shaderType) noexcept
{
    ZC_upFileReader upFileReader = ZC_FileReader::MakeReader(path, __FILE__, __LINE__);
    if (!upFileReader) return ZC_DynamicArray<char>();

    unsigned int shaderStartSize = 0;
    switch (shaderType)
    {
        case ShaderType::Vertex:
            shaderStartSize = vertexStart.size();
            break;
        case ShaderType::Geometry:
            shaderStartSize = geometryStart.size();
            break;
        case ShaderType::Fragment:
            shaderStartSize = fragmentStart.size();
            break;
    }

    ZC_ErrorLogger::Clear();
    size_t fileSize = upFileReader->Size(__FILE__, __LINE__);
    if (fileSize == 0)
    {
        if (ZC_ErrorLogger::WasError()) return ZC_DynamicArray<char>();

        ZC_ErrorLogger::Err("Empty fIle: " + std::string(path), __FILE__, __LINE__);
        return ZC_DynamicArray<char>();
    }

    ZC_DynamicArray<char> fileData(shaderStartSize + fileSize + 1);
    fileData.pArray[fileSize + shaderStartSize] = '\0';
    if (upFileReader->Read(fileData.pArray + shaderStartSize, fileSize, __FILE__, __LINE__) == 0) return ZC_DynamicArray<char>();

    switch (shaderType)
    {
        case ShaderType::Vertex:
            FillShaderStart(fileData.pArray, vertexStart);
            break;
        case ShaderType::Geometry:
            FillShaderStart(fileData.pArray, geometryStart);
            break;
        case ShaderType::Fragment:
            FillShaderStart(fileData.pArray, fragmentStart);
            break;
    }

    return fileData;
}

void ZC_ShaderLoader::FillShaderStart(char*& shaderData, const std::string& shaderStart) noexcept
{
    for (size_t i = 0; i < shaderStart.size(); ++i)
    {
        shaderData[i] = shaderStart[i];
    }
}