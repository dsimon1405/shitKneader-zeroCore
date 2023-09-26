#pragma once

#include <ZC_string.h>
#include <ZC/ZC_OpenGL.h>
#include <ZC/ZC_Noncopyable.h>

class ZC_Shader : public ZC_Noncopyable
{
public:
	ZC_Shader(const std::string& vertexCode, const std::string& fragmentCode, const std::string& geometryCode = std::string());
    ~ZC_Shader();
	void CreateShader(const std::string& shaderCode, const GLenum shaderType, GLuint& shaderID);
    void Use() const;

private:
	GLuint id;
};