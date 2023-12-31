#pragma once

#include "ZC_OpenGL.h"
#include <ZC/Tools/ZC_DynamicArray.h>
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>
#ifdef ZC_ANDROID
#include <ZC/Video/ZC_AndroidNativeAppGlue_Window.h>
#endif

#include <concepts>
#include <list>

template <typename T>
concept ZC_cOpenGLType = std::same_as<T, GLbyte>
						 || std::same_as<T, GLubyte>
						 || std::same_as<T, GLshort>
						 || std::same_as<T, GLushort>
						 || std::same_as<T, GLhalf>
						 || std::same_as<T, GLint>
						 || std::same_as<T, GLuint>
						 || std::same_as<T, GLfloat>;

//	Wrapper OpenGL vertex buffer object.
class ZC_VBO
{
public:
	ZC_VBO(const ZC_VBO&) = delete;
	ZC_VBO& operator = (const ZC_VBO&) = delete;

	ZC_VBO(ZC_VBO&& vbo) noexcept;
	ZC_VBO& operator = (ZC_VBO&& vbo);

	virtual ~ZC_VBO();

	/*
	Create a vertex array buffer to store data in graphics memory.

	Return:
	On success pointer to ZC_VBO, otherwise nullptr (in second case ZC_ErrorLogger::ErrorMessage() - for more information).
	*/
	static ZC_VBO* CreateVBO();

	/*
	Maybe baby
	*/
	void BindVertexBuffer(GLuint vaoConfig, long offset, int stride) const;

	/*
	Reserve place in vbo.

	Params:
	size - number of bytes to reserve.
	_usege - style of using stored data (GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY).
	
	Return:
	On success true, otherwise false (in second case ZC_ErrorLogger::ErrorMessage() - for more information).
	*/
    bool BufferData(long size, GLenum _usage = GL_STATIC_DRAW);

	/*
	Saves data to a buffer.

	Params:
	data - data to save.
	_usege - style of using stored data (GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY).
	
	Return:
	On success true, otherwise false (in second case ZC_ErrorLogger::ErrorMessage() - for more information).
	*/
	template<ZC_cOpenGLType TOpenGL>
	bool BufferData(ZC_DynamicArray<TOpenGL>&& data, GLenum _usage);

	/*
	Save new data in vbo.

	Params:
	offset - offset in bytes before editing starts.
	data - data to save.
	
	Return:
	On success true, otherwise false (in second case ZC_ErrorLogger::ErrorMessage() - for more information).
	*/
	template<ZC_cOpenGLType TOpenGL>
	bool BufferSubData(long offset, ZC_DynamicArray<TOpenGL>&& data);

private:
	GLuint id = 0;
    static inline std::list<ZC_VBO> vbos;

	ZC_VBO();

	static void UnbindBuffer();
	
	void BindBuffer() const;
	bool BufferData(void* pData, size_t bytesSize, GLenum _usage);
	bool BufferSubData(long offset, void* pData, size_t bytesSize);

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
		VBOData(long _size, char* _pData, char* _pDataHead,
				long _offset = 0, VBOData* _pSamePrevious = nullptr) noexcept;

		VBOData(const VBOData&) = delete;
		ZC_VBO::VBOData& operator = (const VBOData&) = delete;

		VBOData(VBOData&& vboData) noexcept;
		ZC_VBO::VBOData& operator = (VBOData&& vboData) noexcept;

		~VBOData() noexcept;
	};

	std::list<VBOData> vboDatas;
	GLenum usage = 0;

	static void ResetVBOs();

	void ClearvboDatas() noexcept;
    void AddVBOData(long offset, long size, char* pData);
#endif
};

template<ZC_cOpenGLType TOpenGL>
bool ZC_VBO::BufferData(ZC_DynamicArray<TOpenGL>&& data, GLenum _usage)
{
	if (!BufferData(static_cast<void*>(data.pArray), data.size * sizeof(TOpenGL), _usage)) return false;
#ifdef ZC_ANDROID
	data.pArray = nullptr;
#endif
	return true;
}

template<ZC_cOpenGLType TOpenGL>
bool ZC_VBO::BufferSubData(long offset, ZC_DynamicArray<TOpenGL>&& data)
{
	if (!BufferSubData(offset, static_cast<void*>(data.pArray), data.size * sizeof(TOpenGL))) return false;
#ifdef ZC_ANDROID
	data.pArray = nullptr;
#endif
	return true;
}