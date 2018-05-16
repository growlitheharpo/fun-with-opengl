#pragma once
#include <vector>
#include "ShaderProgram.h"
#include <unordered_map>

namespace rendering
{
	class GraphicsSystem
	{
	private:
		std::unordered_map<std::string, ShaderProgram> shaders;

	public:
		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem(const GraphicsSystem&&) = delete;
		GraphicsSystem& operator = (const GraphicsSystem&) = delete;
		GraphicsSystem& operator = (const GraphicsSystem&&) = delete;

		~GraphicsSystem();

		void load_shader(const std::string& program_name, const std::vector<ShaderProgram::LoadInfo>& load_info);
	};
}
