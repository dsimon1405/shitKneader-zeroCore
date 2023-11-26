#include <ZC/Video/OpenGL/Shader/ZC_Shader.h>

#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

ZC_Shader::ZC_Shader(ZC_Shader&& shader) noexcept
    : id(shader.id)
{
    shader.id = 0;
}

ZC_Shader& ZC_Shader::operator = (ZC_Shader&& shader) noexcept
{
	if (id != 0) glDeleteProgram(id);
    id = shader.id;
    shader.id = 0;
	return *this;
}

ZC_Shader::~ZC_Shader()
{
	glDeleteProgram(id);
}

ZC_Shader* ZC_Shader::CreateShader(const std::string& name, ZC_ShaderCode&& shaderCode) noexcept
{
	if (shaders.find(name) != shaders.end())
	{
		ZC_ErrorLogger::Err("Already exists shader: " + name, __FILE__, __LINE__);
		return nullptr;
	}
	ZC_ErrorLogger::Clear();
	ZC_Shader shader(shaderCode);
	if (ZC_ErrorLogger::WasError()) return nullptr;
#ifdef ZC_PC
	return &shaders.emplace(name, std::move(shader)).first->second;
#elif defined ZC_ANDROID
	return &shaders.emplace(name, std::make_pair<ZC_Shader, ZC_ShaderCode>(std::move(shader), std::move(shaderCode))).first->second.first;
#endif
}

ZC_Shader* ZC_Shader::GetShader(const std::string& name) noexcept
{
	auto shadersIter = shaders.find(name);
	if (shadersIter == shaders.end()) return nullptr;
#ifdef ZC_PC
	return &shadersIter->second;
#elif defined ZC_ANDROID
	return &shadersIter->second.first;
#endif
}

void ZC_Shader::Use() const noexcept
{
	if (id != 0) glUseProgram(id);
}

void ZC_Shader::SetUniformMatrix4fv(const char* name, const float* pData) const noexcept
{
	GLint location = glGetUniformLocation(id, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, pData);
}

ZC_Shader::ZC_Shader(const ZC_ShaderCode& shaderCode) noexcept
{
	if (!shaderCode.vertexCode)
	{
		ZC_ErrorLogger::Err("ZC_ShaderCode::vertexCode = nullptr!", __FILE__, __LINE__);
		return;
	}
	if (!shaderCode.fragmentCode)
	{
		ZC_ErrorLogger::Err("ZC_ShaderCode::fragmentCode = nullptr!", __FILE__, __LINE__);
		return;
	}
	CreateShaderProgram(shaderCode);
}

void ZC_Shader::CreateShaderProgram(const ZC_ShaderCode& shaderCode) noexcept
{
	GLuint vertexID = CreateShader(shaderCode.vertexCode.Begin(), GL_VERTEX_SHADER);
	if (vertexID == 0) return;

	GLuint fragmentID = CreateShader(shaderCode.fragmentCode.Begin(), GL_FRAGMENT_SHADER);
	if (fragmentID == 0)
	{
		glDeleteShader(vertexID);
		return;
	}

	GLuint geometryID = 0;
	if (shaderCode.geometryCode)
	{
		geometryID = CreateShader(shaderCode.geometryCode.pArray, GL_GEOMETRY_SHADER);
		if (geometryID == 0)
		{
			glDeleteShader(vertexID);
			glDeleteShader(fragmentID);
			return;
		}
	}

	id = glCreateProgram();
	glAttachShader(id, vertexID);
	glAttachShader(id, fragmentID);
	if (geometryID != 0) glAttachShader(id, geometryID);

	glLinkProgram(id);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	if (geometryID != 0) glDeleteShader(geometryID);
}

GLuint ZC_Shader::CreateShader(const char* shaderCode, GLenum shaderType) noexcept
{
	GLuint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, nullptr);
	glCompileShader(shaderID);
	return ZC_ErrorLogger::WasError() ? 0 : shaderID;
}
#ifdef ZC_ANDROID
void ZC_Shader::ResetShaders() noexcept
{
	for (auto& shadersPair : shaders)
	{
		shadersPair.second.first.CreateShaderProgram(shadersPair.second.second);
	}
}
#endif