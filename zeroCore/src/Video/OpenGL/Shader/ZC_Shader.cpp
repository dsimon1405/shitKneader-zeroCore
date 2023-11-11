#include <ZC/Video/OpenGL/Shader/ZC_Shader.h>

#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

ZC_Shader::ZC_Shader(ZC_Shader&& shader) noexcept
    : id(shader.id)
{
    shader.id = 0;
}

ZC_Shader& ZC_Shader::operator = (ZC_Shader&& shader) noexcept
{
    id = shader.id;
    shader.id = 0;
	return *this;
}

ZC_Shader::~ZC_Shader()
{
	glDeleteProgram(id);
}

ZC_Shader* ZC_Shader::CreateShader(const std::string& name, ZC_ShaderCode shaderCode) noexcept
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

ZC_Shader::ZC_Shader(const ZC_ShaderCode& shaderCode) noexcept
{
	CreateShaderProgram(shaderCode);
}

void ZC_Shader::CreateShaderProgram(const ZC_ShaderCode& shaderCode) noexcept
{
	if (!shaderCode.vertexCode.array)
	{
		ZC_ErrorLogger::Err("ZC_ShaderCode::vertexCode = nullptr!", __FILE__, __LINE__);
		return;
	}
	if (!shaderCode.fragmentCode.array)
	{
		ZC_ErrorLogger::Err("ZC_ShaderCode::fragmentCode = nullptr!", __FILE__, __LINE__);
		return;
	}

	GLuint vertexID = 0;
	if (!CreateShader(shaderCode.vertexCode.array, GL_VERTEX_SHADER, vertexID)) return;

	GLuint fragmentID = 0;
	if (!CreateShader(shaderCode.fragmentCode.array, GL_FRAGMENT_SHADER, fragmentID))
	{
		glDeleteShader(vertexID);
		return;
	}

	GLuint geometryID = 0;
	if (shaderCode.geometryCode.array && !CreateShader(shaderCode.geometryCode.array, GL_GEOMETRY_SHADER, geometryID))
	{
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		return;
	}

	id = glCreateProgram();
	glAttachShader(id, vertexID);
	glAttachShader(id, fragmentID);
	if (shaderCode.geometryCode.array) glAttachShader(id, geometryID);

	glLinkProgram(id);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	if (shaderCode.geometryCode.array) glDeleteShader(geometryID);

	GLint success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		ZC_ErrorLogger::Err("Link shader program failed: " + std::string(infoLog), __FILE__, __LINE__);
		return;
	}

	ZC_ErrorLogger::Clear();
}

bool ZC_Shader::CreateShader(const char* const& shaderCode, const GLenum& shaderType, GLuint& shaderID) noexcept
{
	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, nullptr);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		glDeleteShader(shaderID);
		ZC_ErrorLogger::Err("Create shader failed: " + std::string(infoLog), __FILE__, __LINE__);
		return false;
	}
	return true;
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