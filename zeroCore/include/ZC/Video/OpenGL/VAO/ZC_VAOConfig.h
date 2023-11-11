#pragma once

#include <ZC/Video/OpenGL/ZC_OpenGL.h>
#include "ZC_VAO.h"

#include <list>

class ZC_VAOConfig
{
    friend class ZC_VAO;
public:
    struct Format
    {
        GLuint attribindex;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLuint relativeoffset;

        Format(GLuint _attribindex, GLint _size, GLenum _type, GLboolean _normalized, GLuint _relativeoffset) noexcept;

        bool operator == (const Format& format) const noexcept;
    };

    ZC_VAOConfig() = default;
    ~ZC_VAOConfig() = default;

    ZC_VAOConfig(const ZC_VAOConfig& vaoConfig) = default;
    ZC_VAOConfig& operator = (const ZC_VAOConfig& vaoConfig) = default;

    ZC_VAOConfig(ZC_VAOConfig&& vaoConfig) noexcept;
    ZC_VAOConfig& operator = (ZC_VAOConfig&& vaoConfig) noexcept;

    bool operator == (const ZC_VAOConfig& vaoConfig) const noexcept;

    ZC_VAOConfig* AddFormat(const ZC_VAOConfig::Format& format) noexcept;

private:
    std::list<Format> formats;

    GLint CalculateStride() const noexcept;
};