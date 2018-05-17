#pragma once
#include "Component.h"
#include "ShaderProgram.h"
#include "Model.h"

namespace rendering
{
	class RendererComponent : public core::Component
	{
	public:
		RendererComponent();
		explicit RendererComponent(ShaderProgram::shader_id);

		ShaderProgram::shader_id shader_id;
		Model model;
		
		void activate() const;
		void draw() const;
	};
}
