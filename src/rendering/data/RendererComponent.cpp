#include "RendererComponent.h"

#include "core/utils/NarrowCast.h"

rendering::RendererComponent::RendererComponent() : shader_id(std::numeric_limits<ShaderProgram::shader_id>::max())
{
}

rendering::RendererComponent::RendererComponent(const ShaderProgram::shader_id id) : shader_id(id)
{
}

void rendering::RendererComponent::activate() const
{
	model.activate();
}

void rendering::RendererComponent::draw() const
{
	model.activate();
	glDrawArrays(GL_TRIANGLES, 0, narrow_cast<GLsizei>(model.vertexCount()));
}
