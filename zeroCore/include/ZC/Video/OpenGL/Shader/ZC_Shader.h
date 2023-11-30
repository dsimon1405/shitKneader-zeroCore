#pragma once

#include <ZC/Tools/ZC_string.h>
#include <ZC/Video/OpenGL/ZC_OpenGL.h>
#include "ZC_ShaderCode.h"
#ifdef ZC_ANDROID
#include <ZC/Video/ZC_AndroidNativeAppGlue_Window.h>
#endif

#include <map>

//	OpenGL shader program class.
class ZC_Shader
{
public:
	ZC_Shader() = delete;

	ZC_Shader(const ZC_Shader&) = delete;
	ZC_Shader& operator = (const ZC_Shader&) = delete;
	
	ZC_Shader(ZC_Shader&& shader) noexcept;
	ZC_Shader& operator = (ZC_Shader&& shader) noexcept;

    ~ZC_Shader();

	/*
    Create shader program.

    Params:
    name - shader name.
    shaderCode - code for creating shader program.

    Return:
    On success pointer to ZC_Shader, otherwise nullptr.
    */
	static ZC_Shader* CreateShader(const std::string& name, ZC_ShaderCode&& shaderCode) noexcept;

	/*
    Help to get shader.

    Params:
    name - shader name.

    Return:
    If shader exists pointer to ZC_Shader, otherwise nullptr.
    */
	static ZC_Shader* GetShader(const std::string& name) noexcept;

	/*
	Activate shader program.
	*/
    void Use() const noexcept;

	void SetUniformMatrix4fv(const char* name, const float* pData) const noexcept;
	
private:
	GLuint id = 0;

	ZC_Shader(const ZC_ShaderCode& shaderCode) noexcept;

	static GLuint CreateShader(const char* shaderCode, GLenum shaderType) noexcept;

	void CreateShaderProgram(const ZC_ShaderCode& shaderCode) noexcept;
#ifdef ZC_PC
	static inline std::map<std::string, ZC_Shader> shaders;
#elif defined ZC_ANDROID
	friend class ZC_AndroidNativeAppGlue_Window;

	static inline std::map<std::string, std::pair<ZC_Shader, ZC_ShaderCode>> shaders;

	static void ResetShaders() noexcept;
#endif
};