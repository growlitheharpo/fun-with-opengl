#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

namespace rendering
{
	class ShaderProgram
	{
		friend class GraphicsSystem;

	public:
		struct LoadInfo
		{
			GLenum type;
			const char* filename;
			const char* name;
		};

		typedef std::vector<ShaderProgram>::size_type shader_id;

	private:

		GLuint program_ = 0;
		shader_id id_;

		static std::string read_shader(const char* filename);
		static GLuint create_shader(GLenum shaderType, const std::string& source, const char* shaderName);
	
		GLuint createProgram(const std::vector<LoadInfo>& info);
		void cleanup();

	public:
		explicit ShaderProgram(shader_id id);
		void activate() const;

		shader_id get_id() const { return id_; }
	};
}
