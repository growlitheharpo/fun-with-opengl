#include "GraphicsSystem.h"

rendering::GraphicsSystem::~GraphicsSystem()
{
	for (auto& iter : shaders)
		iter.second.cleanup();
	shaders.clear();
}

void rendering::GraphicsSystem::load_shader(const std::string& program_name,
	const std::vector<ShaderProgram::LoadInfo>& load_info)
{
	ShaderProgram new_program;
	new_program.createProgram(load_info);
	shaders[program_name] = new_program;
}
