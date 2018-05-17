#include "GraphicsSystem.h"
#include "Logging.h"
#include <GL/freeglut.h>

using namespace rendering;

GraphicsSystem::~GraphicsSystem()
{
	for (auto& iter : shaders_)
		iter.cleanup();
	shaders_.clear();
}

void GraphicsSystem::initialize()
{
	DEBUG_IF(initialized_,
		throw std::runtime_error("Cannot initialize a graphics system that has already been initialized!"));

	int zero = 0;
	glutInit(&zero, nullptr);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("OpenGL Window");

	glewInit();
	DEBUG_IF_ELSE(glewIsSupported("GL_VERSION_4_4"),
		LOG("GLEW Version is 4.4."),
		LOG_ERR("GLEW 4.4 is not supported!"));

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	initialized_ = true;
}

ShaderProgram::shader_id GraphicsSystem::loadShader(const std::string& program_name,
	const std::vector<ShaderProgram::LoadInfo>& load_info)
{
	DEBUG_IF(!initialized_,
		throw std::runtime_error("Cannot perform graphics calls before initializing!"));

	ShaderProgram::shader_id new_id = shaders_.size();
	shaders_.emplace_back(new_id);
	shaders_.back().createProgram(load_info);
	shader_names_[program_name] = new_id;
	
	return new_id;
}

ShaderProgram::shader_id GraphicsSystem::getProgramId(const std::string& name) const
{
	const auto result = shader_names_.find(name);
	if (result == shader_names_.end())
		return std::numeric_limits<ShaderProgram::shader_id>::max();

	return (*result).second;
}
