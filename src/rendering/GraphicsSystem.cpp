#include "GraphicsSystem.h"

#include <GL/freeglut.h>
#include <GL/glew.h>
#include "core/Logging.h"
#include "core/memory/vector.h"

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
	const memory::vector<ShaderProgram::LoadInfo>& load_info)
{
	DEBUG_IF(!initialized_,
		throw std::runtime_error("Cannot perform graphics calls before initializing!"));

	// The new ID (i.e., index) of the shader is the current size
	ShaderProgram::shader_id new_id = shaders_.size();

	// Create and load the shader and add it to the name map
	ShaderProgram* program = PLACEMENT_NEW(shaders_.push_back_for_placement_new(), ShaderProgram(new_id));
	program->createProgram(load_info);
	shader_names_[program_name] = new_id;

	// Add a new renderable category for renderables that will use this shader
	renderables_.push_back();
	
	return new_id;
}

ShaderProgram::shader_id GraphicsSystem::getProgramId(const std::string& name) const
{
	const auto result = shader_names_.find(name);
	if (result == shader_names_.end())
		return std::numeric_limits<ShaderProgram::shader_id>::max();

	return (*result).second;
}

RendererComponent* GraphicsSystem::createRenderComponent(const std::string& shaderName)
{
	return createRenderComponent(getProgramId(shaderName));
}

RendererComponent* GraphicsSystem::createRenderComponent(ShaderProgram::shader_id shaderId)
{
	DEBUG_IF(shaderId >= renderables_.size(),
		throw std::runtime_error("Trying to create a render component with shader that does not exist!"));

	auto& list = renderables_[shaderId];
	return PLACEMENT_NEW(list.push_back_for_placement_new(), RendererComponent(shaderId));
}

void GraphicsSystem::render() const
{
	for (ShaderProgram::shader_id i = 0; i < shaders_.size(); ++i)
	{
		DEBUG_IF(renderables_.size() <= i,
			throw std::runtime_error("Renderables container must be 1-to-1 with the shader program list!"));

		if (renderables_[i].empty())
			continue;

		shaders_[i].activate();
		for (const auto& renderable : renderables_[i])
		{
			renderable.activate();
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(renderable.model.vertexCount()));
		}
	}
}
