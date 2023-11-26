#pragma once

#include <ZC/Video/OpenGL/ZC_OpenGL.h>
#include "ZC_VAOConfig.h"
#include <ZC/Video/OpenGL/ZC_VBO.h>
#ifdef ZC_ANDROID
#include <ZC/Video/ZC_AndroidNativeAppGlue_Window.h>
#endif

#include <map>

//	Wrapper OpenGL vertex array object.
class ZC_VAO
{
public:
	ZC_VAO(const ZC_VAO&) = delete;
	ZC_VAO& operator = (const ZC_VAO&) = delete;

	ZC_VAO(ZC_VAO&& vao) noexcept;
	ZC_VAO& operator = (ZC_VAO&& vao) noexcept;

	~ZC_VAO();

	/*If ZC_VAO does not exist (there was no previously called GetVAO with the same vaoConfig), it is created using ZC_VAOConfig with the COPY constructor.

	Params:
	vaoConfig - vao configuration.

	Return:
	On success pointer to ZC_VAO, otherwise nullptr (in second case ZC_ErrorLogger::ErrorMessage() - for more information).
	*/
	static ZC_VAO* GetVAO(const ZC_VAOConfig& vaoConfig) noexcept;

	/*
	If ZC_VAO does not exist (there was no previously called GetVAO with the same vaoConfig), it is created using ZC_VAOConfig with the MOVE constructor. If previously it was called GetVAO with the same vaoConfig, nothing happens with vaoConfig.

	Params:
	vaoConfig - vao configuration.

	Return:
	On success pointer to ZC_VAO, otherwise nullptr (in second case ZC_ErrorLogger::ErrorMessage() - for more information).
	*/
	static ZC_VAO* GetVAO(ZC_VAOConfig&& vaoConfig) noexcept;

	/*
	Unbind vertex array object.
	*/
	static void UnbindVertexArray() noexcept;

	/*
	Bind vertex array object.
	*/
	void BindVertexArray() const noexcept;

	/*
	Drawings graphic objects.

	Params:
	vbo - buffer containing data.
	bufferOffset - starting offset in bytes in vbo.
	mode - OpenGL drawing mode (depends on the location of the data in vbo) : GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY GL_PATCHES.
	count - count of drawing elements (depends on mode).
	*/
	void DrawArrays(const ZC_VBO* vbo, long bufferOffset, GLenum mode, int count) const noexcept;

private:
	static inline std::map<ZC_VAOConfig, ZC_VAO> vaos;
	
	GLuint id = 0;
	GLuint config;
	GLint stride = 0;

	ZC_VAO(const GLuint& _config);

	static ZC_VAO CreateVAO(const ZC_VAOConfig& vaoConfig) noexcept;

#ifdef ZC_ANDROID
	friend class ZC_AndroidNativeAppGlue_Window;
    static void ResetVAOs() noexcept;
#endif
};