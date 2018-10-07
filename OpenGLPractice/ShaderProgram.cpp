#include "ShaderProgram.h"

#include <GL/glew.h>
#include <fstream>
#include "Logging.h"

using namespace rendering;

ShaderProgram::ShaderProgram(shader_id id)
{
	id_ = id;
}

std::string ShaderProgram::read_shader(const char* filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good())
		DLOG_ERR("Could not read file " << filename);

	file.seekg(0, std::ios::end);
	shaderCode.resize(static_cast<std::string::size_type>(file.tellg()));
	file.seekg(0, std::ios::beg);

	file.read(&shaderCode[0], shaderCode.size());
	file.close();

	return shaderCode;
}

GLuint ShaderProgram::create_shader(GLenum shaderType, const std::string& source, const char* shaderName)
{
	int compile_result = 0;

	const GLuint shader = glCreateShader(shaderType);

	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	if (compile_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		
		std::string log;
		log.resize(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, nullptr, &log[0]);
		LOG_ERR("ERROR compiling shader \"" << shaderName << "\": " << log);
		return 0;
	}

	return shader;
}

GLuint ShaderProgram::createProgram(const std::vector<LoadInfo>& info)
{
	std::vector<GLuint> programs;
	programs.reserve(info.size());

	for (const auto& shader: info)
	{
		const std::string code = read_shader(shader.filename);
		programs.push_back(create_shader(shader.type, code, shader.name));
	}

	int link_result = 0;
	program_ = glCreateProgram();
	for (const auto& shader : programs)
		glAttachShader(program_, shader);
	glLinkProgram(program_);

	glGetProgramiv(program_, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program_ , GL_INFO_LOG_LENGTH, &info_log_length);

		std::string log;
		log.resize(info_log_length);
		glGetProgramInfoLog(program_, info_log_length, nullptr, &log[0]);
		LOG_ERR("ERROR linking shader! " << log);
		return 0;
	}

	return program_;
}

void ShaderProgram::cleanup()
{
	glDeleteProgram(program_);
	program_ = 0;
}

void ShaderProgram::activate() const
{
	glUseProgram(program_);
}
