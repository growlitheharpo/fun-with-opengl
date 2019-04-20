#pragma once
#include <vector>
#include <map>

#include "core/memory/vector.h"
#include "core/utils/IntUtilities.h"
#include "rendering/data/ShaderProgram.h"
#include "rendering/data/RendererComponent.h"

namespace rendering
{
	class GraphicsSystem
	{
	private:
		std::map<std::string, ShaderProgram::shader_id> shader_names_;

		memory::vector<ShaderProgram> shaders_;
		memory::vector<memory::vector<RendererComponent>> renderables_;

		bool initialized_ = false;

	public:
		GraphicsSystem() = default;
		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem(const GraphicsSystem&&) = delete;
		GraphicsSystem& operator = (const GraphicsSystem&) = delete;
		GraphicsSystem& operator = (const GraphicsSystem&&) = delete;

		~GraphicsSystem();

		void initialize();
		
		ShaderProgram::shader_id loadShader(const std::string& program_name, const std::vector<ShaderProgram::LoadInfo>& load_info);
		ShaderProgram::shader_id getProgramId(const std::string& name) const;

		RendererComponent* createRenderComponent(const std::string& shaderName);
		RendererComponent* createRenderComponent(ShaderProgram::shader_id shaderId);

		void render() const;
	};
}
