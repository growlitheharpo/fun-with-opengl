#pragma once
#include "Component.h"
#include "ShaderProgram.h"
#include "Model.h"

namespace rendering
{
	class RendererComponent : public core::Component
	{
	public:
		explicit RendererComponent(core::GameObject* go);

		ShaderProgram const* program;
		Model model;
	};
}
