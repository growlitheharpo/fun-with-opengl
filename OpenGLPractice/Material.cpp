#include "Material.h"
#include <glm/mat4x2.hpp>

rendering::Material::Material(): shader_id_(std::numeric_limits<ShaderProgram::shader_id>::max())  // NOLINT
{
	for (auto& uniform_location : uniform_locations_)
		uniform_location = -1;
}

void rendering::Material::initialize(const ShaderProgram& shader)
{
	for (int i = 0; i < uniform_count; ++i)
	{
		uniform_locations_[i] = glGetUniformLocation(shader.get_id(), uniform_vals_[i]);
	}
}

void rendering::Material::sendUniform4x4(Uniform u, const glm::mat4& mat) const
{
	glUniform4fv(uniform_locations_[u], 1, &mat[0][0]);
}
