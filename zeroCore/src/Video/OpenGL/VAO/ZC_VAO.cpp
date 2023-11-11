#include <ZC/Video/OpenGL/VAO/ZC_VAO.h>

#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

ZC_VAO::ZC_VAO(ZC_VAO&& vao) noexcept
    : id(vao.id),
    config(vao.config),
    stride(vao.stride)
{
    vao.id = 0;
}

ZC_VAO& ZC_VAO::operator = (ZC_VAO&& vao) noexcept
{
    id = vao.id;
    config = vao.config;
    stride = vao.stride;

    vao.id = 0;
    return *this;
}

ZC_VAO::~ZC_VAO()
{
    glDeleteVertexArrays(1, &id);
}

GLint ZC_VAO::GetVAOConfigMaxCount() noexcept
{
    GLint maxCount;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &maxCount);
    return maxCount;
}

ZC_VAO* ZC_VAO::GetVAO(const ZC_VAOConfig& vaoConfig) noexcept
{
    for (auto& vaosPair : vaos)
    {
        if (vaosPair.first == vaoConfig) return &vaosPair.second;
    }

    ZC_ErrorLogger::Clear();
    ZC_VAO vao = CreateVAO(vaoConfig);
    if (ZC_ErrorLogger::WasError()) return nullptr;

    return &vaos.emplace_back(vaoConfig, std::move(vao)).second;
}

ZC_VAO* ZC_VAO::GetVAO(ZC_VAOConfig&& vaoConfig) noexcept
{
    for (auto& vaosPair : vaos)
    {
        if (vaosPair.first == vaoConfig) return &vaosPair.second;
    }

    ZC_ErrorLogger::Clear();
    ZC_VAO vao = CreateVAO(vaoConfig);
    if (ZC_ErrorLogger::WasError()) return nullptr;

    return &vaos.emplace_back(std::move(vaoConfig), std::move(vao)).second;
}

void ZC_VAO::UnbindVertexArray() noexcept
{
    glBindVertexArray(0);
}

void ZC_VAO::BindVertexArray() const noexcept
{
    glBindVertexArray(id);
}

void ZC_VAO::DrawArrays(const ZC_VBO* const& vbo, const long& bufferOffset, const GLenum& mode, const int& count) const noexcept
{
    BindVertexArray();
    vbo->BindVertexBuffer(config, bufferOffset, stride);
    glDrawArrays(mode, 0, count);
    UnbindVertexArray();
}

ZC_VAO::ZC_VAO(const GLuint& _config)
    : config(_config)
{
    glGenVertexArrays(1, &id);
}

bool ZC_VAO::ReserveVAOsCount(const GLint& count) noexcept
{
    vaos.reserve(count);
    return true;
}

ZC_VAO ZC_VAO::CreateVAO(const ZC_VAOConfig& vaoConfig) noexcept
{
    static bool vaosReserveCount = ReserveVAOsCount(GetVAOConfigMaxCount());
    
    GLuint config = vaos.size();
    ZC_VAO vao(config);
    
    vao.BindVertexArray();
    for (auto& format : vaoConfig.formats)
    {
        glEnableVertexAttribArray(format.attribindex);
        glVertexAttribFormat(format.attribindex, format.size, format.type, format.normalized, format.relativeoffset);
        glVertexAttribBinding(format.attribindex, config);
    }
    vao.UnbindVertexArray();

    vao.stride = vaoConfig.CalculateStride();

    return vao; 
}