#include <ZC/Video/OpenGL/ZC_VBO.h>

ZC_VBO* ZC_VBO::CreateVBO() noexcept
{
    return &vbos.emplace_back(ZC_VBO());
}

void ZC_VBO::BindBuffer() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void ZC_VBO::UnbindBuffer() noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ZC_VBO::ZC_VBO() noexcept
{
    glGenBuffers(1, &id);
}

void ZC_VBO::BindVertexBuffer(const GLuint& vaoConfig, const long& offset, const int& stride) const noexcept
{
    glBindVertexBuffer(vaoConfig, id, offset, stride);
}
#ifdef ZC_PC
ZC_VBO::ZC_VBO(ZC_VBO&& vbo) noexcept
    : id(vbo.id)
{
    vbo.id = 0;
}

ZC_VBO& ZC_VBO::operator = (ZC_VBO&& vbo) noexcept
{
    id = vbo.id;

    vbo.id = 0;
    return *this;
}

ZC_VBO::~ZC_VBO() noexcept
{
    glDeleteBuffers(1, &id);
}

void ZC_VBO::BufferData(const long& size, void* const& pData, const GLenum& usage) noexcept
{
    BindBuffer();
    glBufferData(GL_ARRAY_BUFFER, size, static_cast<void*>(pData), usage);
    UnbindBuffer();
}

void ZC_VBO::BufferSubData(const long& offset, const long& size, void* const& pData) noexcept
{
    BindBuffer();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, static_cast<void*>(pData));
    UnbindBuffer();
}
#elif defined ZC_ANDROID
ZC_VBO::ZC_VBO(ZC_VBO&& vbo) noexcept
        : id(vbo.id),
        vboDatas(std::move(vbo.vboDatas)),
        usage(vbo.usage)
{
    vbo.id = 0;
}

ZC_VBO& ZC_VBO::operator = (ZC_VBO&& vbo) noexcept
{
    id = vbo.id;
    vboDatas = std::move(vbo.vboDatas);
    usage = vbo.usage;

    vbo.id = 0;
    return *this;
}

ZC_VBO::~ZC_VBO() noexcept
{
    glDeleteBuffers(1, &id);
}

void ZC_VBO::BufferData(const long& size, void* const& pData, const GLenum& _usage) noexcept
{
    usage = _usage;
    BindBuffer();
    glBufferData(GL_ARRAY_BUFFER, size, pData, usage);
    UnbindBuffer();

    vboDatas.clear();
    vboDatas.emplace_back(size, static_cast<char*>(pData), static_cast<char*>(pData));
}

void ZC_VBO::BufferSubData(const long& offset, const long& size, void* const& pData) noexcept
{
    BindBuffer();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, pData);
    UnbindBuffer();

    EditvboDatas(offset, size, static_cast<char*>(pData));
}

void ZC_VBO::EditvboDatas(const long& offset, const long& size, char* const& pData) noexcept
{
    auto emplacePosition = vboDatas.end();
    long endPos = offset + size;
    for (auto vboDatasIter = vboDatas.begin()->pData ? vboDatas.begin() : ++vboDatas.begin(); vboDatasIter != vboDatas.end(); ++vboDatasIter)
    {
        long endPosIter = vboDatasIter->offset + vboDatasIter->size;
        if (offset < vboDatasIter->offset && endPos >= endPosIter)
        {
            vboDatasIter->size = 0;
            continue;
        }
        if (offset >= vboDatasIter->offset && offset < endPosIter)
        {
            vboDatasIter->size = offset - vboDatasIter->offset;
            if (endPos < endPosIter)
            {
                long startPosOffset = size + vboDatasIter->size;
                vboDatasIter = vboDatas.emplace(++vboDatasIter,
                                                 VBOData(endPosIter - endPos,
                                                         vboDatasIter->pData + startPosOffset,
                                                         vboDatasIter->pDataHead,
                                                         vboDatasIter->offset + startPosOffset,
                                                         &*vboDatasIter));
                emplacePosition = vboDatasIter;
                (--vboDatasIter)->pSameNext = &*emplacePosition;
                break;
            }
            if (endPos == endPosIter)
            {
                emplacePosition = ++vboDatasIter;
                break;
            }
        }
        if (endPos > vboDatasIter->offset && endPos <= endPosIter)
        {
            long startOffset = offset + size - vboDatasIter->offset;
            vboDatasIter->offset += startOffset;
            vboDatasIter->size -= startOffset;
            emplacePosition = vboDatasIter;
            break;
        }
    }
    vboDatas.emplace(emplacePosition, VBOData(size, pData, pData, offset));
    for (auto vboDatasIter = vboDatas.begin()->pData ? vboDatas.begin() : ++vboDatas.begin(); vboDatasIter != vboDatas.end();)
    {
        vboDatasIter = vboDatasIter->size == 0 ? vboDatas.erase(vboDatasIter) : ++vboDatasIter;
    }
}

void ZC_VBO::ResetVBOs() noexcept
{
    for (ZC_VBO& vbo : vbos)
    {
        glGenBuffers(1, &vbo.id);
        vbo.BindBuffer();
        if (vbo.vboDatas.empty()) continue;
        auto vboDatasIter = vbo.vboDatas.begin();
        glBufferData(GL_ARRAY_BUFFER, vboDatasIter->size, vboDatasIter->pData, vbo.usage);
        for (++vboDatasIter; vboDatasIter != vbo.vboDatas.end(); ++vboDatasIter)
        {
            glBufferSubData(GL_ARRAY_BUFFER, vboDatasIter->offset, vboDatasIter->size, vboDatasIter->pData);
        }
        vbo.UnbindBuffer();
    }
}

//  VBOData
ZC_VBO::VBOData::VBOData(const long& _size, char* const& _pData, char* const& _pDataHead,
                        const long& _offset, VBOData* const& _pSamePrevious) noexcept
    : pData(_pData),
      size(_size),
      pDataHead(_pDataHead),
      offset(_offset),
      pSamePrevious(_pSamePrevious)
{}

ZC_VBO::VBOData::VBOData(VBOData&& vboData) noexcept
    : VBOData(vboData.size, vboData.pData, vboData.pDataHead, vboData.offset, vboData.pSamePrevious)
{
    pSameNext = vboData.pSameNext;

    vboData.pSameNext = nullptr;
    vboData.pSamePrevious = nullptr;
    vboData.pDataHead = nullptr;
}

ZC_VBO::VBOData& ZC_VBO::VBOData::operator = (VBOData&& vboData) noexcept
{
    size = vboData.size;
    pData = vboData.pData;
    pDataHead = vboData.pDataHead;
    offset = vboData.offset;
    pSamePrevious = vboData.pSamePrevious;
    pSameNext = vboData.pSameNext;

    vboData.pSameNext = nullptr;
    vboData.pSamePrevious = nullptr;
    vboData.pDataHead = nullptr;
    return *this;
}

ZC_VBO::VBOData::~VBOData() noexcept
{
    if (pSameNext)
    {
        pSameNext->pSamePrevious = pSamePrevious;
        pDataHead = nullptr;
    }
    if (pSamePrevious)
    {
        pSamePrevious->pSameNext = pSameNext;
        pDataHead = nullptr;
    }

    delete[] pDataHead;
}
#endif