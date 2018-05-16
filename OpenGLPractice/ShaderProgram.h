#pragma once
#include <GL/glew.h>
#include <string>

namespace graphics
{
	class ShaderProgram
	{
	private:
		GLuint program_ = 0;

		static std::string read_shader(const char* filename);
		static GLuint create_shader(GLenum shaderType, const std::string& source, const char* shaderName);
	
	public:
		ShaderProgram() = default;
		~ShaderProgram() = default;

		GLuint createProgram(const char* vertexShaderFile, const char* fragmentShaderFile);
	};
}
