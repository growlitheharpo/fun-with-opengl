#include "GraphicsSystem.h"
#include "Logging.h"
#include <GL/freeglut.h>

rendering::GraphicsSystem::~GraphicsSystem()
{
	for (auto& iter : shaders)
		iter.second.cleanup();
	shaders.clear();
}

void rendering::GraphicsSystem::initialize()
{
	DEBUG_IF(initialized,
		throw std::runtime_error("Cannot initialize a graphics system that has already been initialized!"));

	int zero = 0;
	glutInit(&zero, nullptr);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("OpenGL Window");

	glewInit();
	glewInit();
	DEBUG_IF_ELSE(glewIsSupported("GL_VERSION_4_4"),
		LOG("GLEW Version is 4.4."),
		LOG_ERR("GLEW 4.4 is not supported!"));

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	initialized = true;
}

void rendering::GraphicsSystem::load_shader(const std::string& program_name,
	const std::vector<ShaderProgram::LoadInfo>& load_info)
{
	DEBUG_IF(!initialized,
		throw std::runtime_error("Cannot perform graphics calls before initializing!"));

	ShaderProgram new_program;
	new_program.createProgram(load_info);
	shaders[program_name] = new_program;
}

rendering::ShaderProgram const* rendering::GraphicsSystem::get_program(const std::string& name) const
{
	const auto result = shaders.find(name);
	if (result == shaders.end())
		return nullptr;

	return &(*result).second;
}
