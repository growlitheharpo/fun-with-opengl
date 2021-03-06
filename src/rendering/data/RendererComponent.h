﻿#pragma once
#include "core/Component.h"

#include "rendering/data/Model.h"
#include "rendering/data/ShaderProgram.h"

namespace rendering
{
	class RendererComponent : public core::Component
	{
	public:
		RendererComponent();
		explicit RendererComponent(ShaderProgram::shader_id);

		DISABLE_COPY_SEMANTICS(RendererComponent);
		USE_DEFAULT_MOVE_SEMANTICS(RendererComponent);

		~RendererComponent() = default;

		ShaderProgram::shader_id shader_id;
		Model model;
		
		void activate() const;
		void draw() const;
	};
}
