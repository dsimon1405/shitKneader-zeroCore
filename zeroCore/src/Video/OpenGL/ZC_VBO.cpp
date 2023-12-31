#include <ZC/Video/OpenGL/ZC_VBO.h>

ZC_VBO::~ZC_VBO()
{
    glDeleteBuffers(1, &id);
}

ZC_VBO* ZC_VBO::CreateVBO()
{
    return &vbos.emplace_back(ZC_VBO());
}

void ZC_VBO::BindVertexBuffer(GLuint vaoConfig, long offset, int stride) const
{
    glBindVertexBuffer(vaoConfig, id, offset, stride);
}

bool ZC_VBO::BufferData(long size, GLenum _usage)
{
    ZC_DynamicArray<GLbyte> emptyData(nullptr, size);
    return BufferData(std::move(emptyData), _usage);
}

ZC_VBO::ZC_VBO()
{
    glGenBuffers(1, &id);
}

void ZC_VBO::UnbindBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ZC_VBO::BindBuffer() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

bool ZC_VBO::BufferData(void* pData, size_t bytesSize, GLenum _usage)
{
    BindBuffer();
    ZC_ErrorLogger::Clear();
    glBufferData(GL_ARRAY_BUFFER, bytesSize, const_cast<const void*>(pData), _usage);
    UnbindBuffer();
    if (ZC_ErrorLogger::WasError()) return false;
#ifdef ZC_ANDROID
    usage = _usage;
    ClearvboDatas();
    char* pDataChar = reinterpret_cast<char*>(pData);
    vboDatas.emplace_back(bytesSize, pDataChar, pDataChar);
#endif
    return true;
}

bool ZC_VBO::BufferSubData(long offset, void* pData, size_t bytesSize)
{
    BindBuffer();
    ZC_ErrorLogger::Clear();
    glBufferSubData(GL_ARRAY_BUFFER, offset, bytesSize, const_cast<const void*>(pData));
    UnbindBuffer();
    if (ZC_ErrorLogger::WasError()) return false;
#ifdef ZC_ANDROID
    AddVBOData(offset, bytesSize, reinterpret_cast<char*>(pData));
#endif
    return true;
}
#ifdef ZC_PC
ZC_VBO::ZC_VBO(ZC_VBO&& vbo) noexcept
    : id(vbo.id)
{
    vbo.id = 0;
}

ZC_VBO& ZC_VBO::operator = (ZC_VBO&& vbo)
{
    if (id != 0) glDeleteBuffers(1, &id);
    id = vbo.id;

    vbo.id = 0;
    return *this;
}
#elif defined ZC_ANDROID
ZC_VBO::ZC_VBO(ZC_VBO&& vbo) noexcept
        : id(vbo.id),
        vboDatas(std::move(vbo.vboDatas)),
        usage(vbo.usage)
{
    vbo.id = 0;
}

ZC_VBO& ZC_VBO::operator = (ZC_VBO&& vbo)
{
    if (id != 0) glDeleteBuffers(1, &id);
    id = vbo.id;
    vboDatas = std::move(vbo.vboDatas);
    usage = vbo.usage;

    vbo.id = 0;
    return *this;
}

void ZC_VBO::ResetVBOs()
{
    for (ZC_VBO& vbo : vbos)
    {
        glGenBuffers(1, &vbo.id);
        if (vbo.vboDatas.empty()) continue;
        vbo.BindBuffer();
        auto vboDatasIter = vbo.vboDatas.begin();
        glBufferData(GL_ARRAY_BUFFER, vboDatasIter->size, vboDatasIter->pData, vbo.usage);
        for (++vboDatasIter; vboDatasIter != vbo.vboDatas.end(); ++vboDatasIter)
        {
            glBufferSubData(GL_ARRAY_BUFFER, vboDatasIter->offset, vboDatasIter->size, vboDatasIter->pData);
        }
    }
    UnbindBuffer();
}

void ZC_VBO::ClearvboDatas() noexcept
{
    for (auto& vboData : vboDatas)
    {
        vboData.size = 0;
    }
    vboDatas.clear();
}

void ZC_VBO::AddVBOData(long offset, long size, char* pData)
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

//  VBOData
ZC_VBO::VBOData::VBOData(long _size, char* _pData, char* _pDataHead,
                        long _offset, VBOData* _pSamePrevious) noexcept
    : offset(_offset),
      pData(_pData),
      size(_size),
      pDataHead(_pDataHead),
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