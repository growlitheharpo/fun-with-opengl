#include "RendererComponent.h"

rendering::RendererComponent::RendererComponent(core::GameObject* go): Component(go), program(nullptr)
{

}

void rendering::RendererComponent::draw() const
{
	model.activate();
	program->activate();
	glDrawArrays(GL_TRIANGLES, 0, model.vertexCount());
}
