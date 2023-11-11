#include <ZC/Video/OpenGL/VAO/ZC_VAO.h>

ZC_VAOConfig::ZC_VAOConfig(ZC_VAOConfig&& vaoConfig) noexcept
        : formats(std::move(vaoConfig.formats))
{}

ZC_VAOConfig& ZC_VAOConfig::operator = (ZC_VAOConfig&& vaoConfig) noexcept
{
    formats = std::move(vaoConfig.formats);
    return *this;
}

bool ZC_VAOConfig::operator == (const ZC_VAOConfig& vaoConfig) const noexcept
{
    return formats == vaoConfig.formats;
}

ZC_VAOConfig* ZC_VAOConfig::AddFormat(const ZC_VAOConfig::Format& format) noexcept
{
    formats.emplace_back(format);
    return this;
}

GLint ZC_VAOConfig::CalculateStride() const noexcept
{
    GLint stride = 0;
    for (auto& format : formats)
    {
        GLint typeSize = 0;
        if (format.type == GL_BYTE || format.type == GL_UNSIGNED_BYTE) typeSize = sizeof(GLbyte);
        else if (format.type == GL_SHORT || format.type == GL_HALF_FLOAT || format.type == GL_UNSIGNED_SHORT) typeSize = sizeof(GLshort);
        else if (format.type == GL_INT || format.type == GL_FLOAT || format.type == GL_UNSIGNED_INT || format.type == GL_INT_2_10_10_10_REV
                 || format.type == GL_UNSIGNED_INT_2_10_10_10_REV || format.type == GL_UNSIGNED_INT_10F_11F_11F_REV) typeSize = sizeof(GLint);
#ifdef ZC_PC
        else if (format.type == GL_DOUBLE) typeSize = sizeof(GLdouble);
#endif

        stride += (format.size * typeSize);
    }
    return stride;
}

ZC_VAOConfig::Format::Format(GLuint _attribindex, GLint _size, GLenum _type, GLboolean _normalized, GLuint _relativeoffset) noexcept
        : attribindex(_attribindex),
          size(_size),
          type(_type),
          normalized(_normalized),
          relativeoffset(_relativeoffset)
{}

bool ZC_VAOConfig::Format::operator == (const Format& format) const noexcept
{
    if (attribindex != format.attribindex) return false;
    if (size != format.size) return false;
    if (type != format.type) return false;
    if (normalized != format.normalized) return false;
    if (relativeoffset != format.relativeoffset) return false;
    return true;
}