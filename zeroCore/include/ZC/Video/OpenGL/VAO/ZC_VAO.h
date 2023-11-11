#pragma once

#include <ZC/Video/OpenGL/ZC_OpenGL.h>
#include "ZC_VAOConfig.h"
#include <ZC/Video/OpenGL/ZC_VBO.h>

#include <vector>

class ZC_VAO
{
public:
	ZC_VAO(const ZC_VAO&) = delete;
	ZC_VAO& operator = (const ZC_VAO&) = delete;

	ZC_VAO(ZC_VAO&& vao) noexcept;
	ZC_VAO& operator = (ZC_VAO&& vao) noexcept;

	~ZC_VAO();

	static GLint GetVAOConfigMaxCount() noexcept;
	static ZC_VAO* GetVAO(const ZC_VAOConfig& vaoConfig) noexcept;
	static ZC_VAO* GetVAO(ZC_VAOConfig&& vaoConfig) noexcept;
	static void UnbindVertexArray() noexcept;

	void BindVertexArray() const noexcept;
	void DrawArrays(const ZC_VBO* const& vbo, const long& bufferOffset, const GLenum& mode, const int& count) const noexcept;

private:
	static inline std::vector<std::pair<ZC_VAOConfig, ZC_VAO>> vaos;
	
	GLuint id = 0;
	GLuint config;
	GLint stride = 0;

	ZC_VAO(const GLuint& _config);

	static bool ReserveVAOsCount(const GLint& count) noexcept;
	static ZC_VAO CreateVAO(const ZC_VAOConfig& vaoConfig) noexcept;
};