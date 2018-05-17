#pragma once
#include <vector>
#include "ShaderProgram.h"
#include <map>

namespace rendering
{
	class GraphicsSystem
	{
	private:
		std::vector<ShaderProgram> shaders_;
		std::map<std::string, ShaderProgram::shader_id> shader_names_;

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
	};
}
