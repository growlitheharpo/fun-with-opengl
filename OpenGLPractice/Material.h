#pragma once
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace rendering
{
	class Material
	{
	public:
		enum Uniform
		{
			mvp = 0,

			uniform_count,
		};

	private:
		char const* const uniform_vals_[uniform_count]
		{
			"MVP"
		};

		ShaderProgram::shader_id shader_id_;
		GLint uniform_locations_[uniform_count];
	
	public:
		Material();

		void initialize(const ShaderProgram& shader);
		void sendUniform4x4(Uniform u, const glm::mat4& mat) const;
	};
}
