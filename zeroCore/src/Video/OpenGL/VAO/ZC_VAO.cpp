#include <ZC/Video/OpenGL/VAO/ZC_VAO.h>

ZC_VAO::ZC_VAO(ZC_VAO&& vao) noexcept
    : id(vao.id),
    config(vao.config),
    stride(vao.stride)
{
    vao.id = 0;
}

ZC_VAO& ZC_VAO::operator = (ZC_VAO&& vao)
{
    if (id != 0) glDeleteVertexArrays(1, &id);
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

ZC_VAO* ZC_VAO::GetVAO(const ZC_VAOConfig& vaoConfig)
{
    auto vaosIter = vaos.find(vaoConfig);
    if (vaosIter != vaos.end()) return &vaosIter->second;

    ZC_ErrorLogger::Clear();
    ZC_VAO vao = CreateVAO(vaoConfig);
    if (ZC_ErrorLogger::WasError()) return nullptr;

    return &vaos.emplace(vaoConfig, std::move(vao)).first->second;
}

ZC_VAO* ZC_VAO::GetVAO(ZC_VAOConfig&& vaoConfig)
{
    auto vaosIter = vaos.find(vaoConfig);
    if (vaosIter != vaos.end()) return &vaosIter->second;

    ZC_ErrorLogger::Clear();
    ZC_VAO vao = CreateVAO(vaoConfig);
    if (ZC_ErrorLogger::WasError()) return nullptr;

    return &vaos.emplace(std::move(vaoConfig), std::move(vao)).first->second;
}

void ZC_VAO::UnbindVertexArray()
{
    glBindVertexArray(0);
}

void ZC_VAO::BindVertexArray() const
{
    glBindVertexArray(id);
}

void ZC_VAO::DrawArrays(const ZC_VBO* vbo, long bufferOffset, GLenum mode, int count) const
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

ZC_VAO ZC_VAO::CreateVAO(const ZC_VAOConfig& vaoConfig)
{
    GLuint config = static_cast<GLuint>(vaos.size());

    ZC_VAO vao(config);
    vao.BindVertexArray();
    vaoConfig.Config(config);
    UnbindVertexArray();

    if (ZC_ErrorLogger::WasError()) return vao;

    vao.stride = vaoConfig.Stride();
    
    return vao; 
}
#ifdef ZC_ANDROID
void ZC_VAO::ResetVAOs()
{
    for (auto& vaosPair : vaos)
    {
        glGenVertexArrays(1, &vaosPair.second.id);
        vaosPair.second.BindVertexArray();
        vaosPair.first.Config(vaosPair.second.config);
    }
    UnbindVertexArray();
}
#endif