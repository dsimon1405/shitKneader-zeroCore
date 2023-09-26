#include <ZC/Renderer/ZC_Shader.h>

#include <ZC_EL.h>

ZC_Shader::ZC_Shader(const std::string& vertexCode, const std::string& fragmentCode, const std::string& geometryCode)
{
	GLuint vertexID = 0;
	CreateShader(vertexCode, GL_VERTEX_SHADER, vertexID);

	GLuint fragmentID = 0;
	CreateShader(fragmentCode, GL_FRAGMENT_SHADER, fragmentID);

	GLuint geometryID = 0;
	if (!geometryCode.empty()) CreateShader(geometryCode, GL_GEOMETRY_SHADER, geometryID);

	id = glCreateProgram();
	glAttachShader(id, vertexID);
	glAttachShader(id, fragmentID);
	if (!geometryCode.empty()) glAttachShader(id, geometryID);

	glLinkProgram(id);

	GLint success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		ZC_Err("Link shader program failed: " + std::string(infoLog));
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	if (!geometryCode.empty()) glDeleteShader(geometryID);;
}

ZC_Shader::~ZC_Shader()
{
	glDeleteProgram(id);
}

void ZC_Shader::CreateShader(const std::string& shaderCode, const GLenum shaderType, GLuint& shaderID)
{
	shaderID = glCreateShader(shaderType);
	const GLchar* pShaderCode = shaderCode.c_str();
	glShaderSource(shaderID, 1, &pShaderCode, NULL);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		ZC_Err("Create shader " + std::to_string(shaderType) + " failed: " + std::string(infoLog));
	}
}

void ZC_Shader::Use() const
{
	glUseProgram(id);
}