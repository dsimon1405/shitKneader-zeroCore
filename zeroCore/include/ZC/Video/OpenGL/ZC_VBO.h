#pragma once

#include "ZC_OpenGL.h"
#ifdef ZC_ANDROID
#include <ZC/Video/ZC_AndroidNativeAppGlue_Window.h>
#endif

#include <list>

class ZC_VBO
{
public:
	ZC_VBO(const ZC_VBO&) = delete;
	ZC_VBO& operator = (const ZC_VBO&) = delete;

	ZC_VBO(ZC_VBO&& vbo) noexcept;
	ZC_VBO& operator = (ZC_VBO&& vbo) noexcept;

	virtual ~ZC_VBO() noexcept;

	static ZC_VBO* CreateVBO() noexcept;
	static void UnbindBuffer() noexcept;

	void BindBuffer() const noexcept;
	void BufferData(const long& size, void* const& pData, const GLenum& usage = GL_STATIC_DRAW) noexcept;
	void BufferSubData(const long& offset, const long& size, void* const& pData) noexcept;
	void BindVertexBuffer(const GLuint& vaoConfig, const long& offset, const int& stride) const noexcept;

private:
	GLuint id = 0;
    static inline std::list<ZC_VBO> vbos;

	ZC_VBO() noexcept;

#ifdef ZC_ANDROID
	friend class ZC_AndroidNativeAppGlue_Window;
private:
	struct VBOData
	{
		long offset;
		char* pData;
		long size;

		char* pDataHead;
		VBOData* pSamePrevious = nullptr;
		VBOData* pSameNext = nullptr;

        VBOData() = delete;
		VBOData(const long& _size, char* const& _pData, char* const& _pDataHead,
				const long& _offset = 0, VBOData* const& _pSamePrevious = nullptr) noexcept;

		VBOData(const VBOData&) = delete;
		ZC_VBO::VBOData& operator = (const VBOData&) = delete;

		VBOData(VBOData&& vboData) noexcept;
		ZC_VBO::VBOData& operator = (VBOData&& vboData) noexcept;

		~VBOData() noexcept;
	};

	std::list<VBOData> vboDatas;
	GLenum usage = 0;

	static void ResetVBOs() noexcept;

    void EditvboDatas(const long& offset, const long& size, char* const& pData) noexcept;
#endif
};