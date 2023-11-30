#pragma once

#include "ZC_ShaderCode.h"
#include <ZC/Video/OpenGL/ZC_OpenGL.h>
#include <ZC/Tools/ZC_DynamicArray.h>
#include <ZC/Tools/ZC_string.h>

//  Class for load shader code from files.
class ZC_ShaderLoader
{
public:
    enum ShaderType
    {
        Vertex,
        Fragment,
        Geometry
    };

    ZC_ShaderLoader() = delete;

    /*
    Load shader code from file.

    Params:
    name - shader name.
    vertexPath - path to the vertex shader file.
    fragmentPath - path to the fragment shader file.
    geometryPath - path to the geometry shader file.

    Return:
    If success ZC_ShaderCode with code data, otherwise ZC_ShaderCode will consider nullptr data (use ZC_ErrorLogger::WasError() for check)(ZC_ErrorLogger::ErrorMessage() - for more information).
    */
    static ZC_ShaderCode LoadShaderCode(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr) noexcept;

    /*
    Read shader code from file.

    Params:
    path - the path to the file.
    shaderType - shader type to fill the shader header.

    Return:
    If success struct dynamic array with code, otherwise empty struct (ZC_ErrorLogger::ErrorMessage() - for more information).
    */
    static ZC_DynamicArray<char> ReadShaderFile(const char* path, ShaderType shaderType) noexcept;

private:
#ifdef ZC_PC
    static inline const std::string vertexStart = "#version " + std::to_string(ZC_OPEN_GL_MAJOR_VERSION)
            + std::to_string(ZC_OPEN_GL_MINOR_VERSION) + "0 core\n";
    static inline const std::string fragmentStart = vertexStart;
#elif defined ZC_ANDROID
    static inline const std::string vertexStart = "#version " + std::to_string(ZC_OPEN_GL_MAJOR_VERSION)
                                                  + std::to_string(ZC_OPEN_GL_MINOR_VERSION) + "0 es\n";
    static inline const std::string fragmentStart = vertexStart + "precision mediump float;";
#endif
    static inline const std::string geometryStart = vertexStart;

    static void FillShaderStart(char* shaderData, const std::string& shaderStart) noexcept;
};