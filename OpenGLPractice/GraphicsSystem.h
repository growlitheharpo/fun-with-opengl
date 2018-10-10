#pragma once
#include <vector>

#include "DynamicVector.h"
#include "ShaderProgram.h"
#include <map>
#include "RendererComponent.h"
#include "IntUtilities.h"

namespace rendering
{
	class GraphicsSystem
	{
	private:
		std::map<std::string, ShaderProgram::shader_id> shader_names_;

		memory::DynamicVector<ShaderProgram> shaders_;
		memory::DynamicVector<
			memory::DynamicVector<RendererComponent>,
			StorageForUMaxCount<16>::Unsigned,
			StorageForMaxCount<16>::Signed> renderables_;

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
