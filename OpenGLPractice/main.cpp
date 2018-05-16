#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Logging.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "GraphicsSystem.h"
#include "GameObject.h"
#include "RendererComponent.h"

rendering::RendererComponent* renderer;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	renderer->draw();

	glutSwapBuffers();
}

void close()
{
	DLOG("Finished!");
	glutLeaveMainLoop();
}

void loadTriangleProgram(rendering::GraphicsSystem& gSystem)
{
	rendering::ShaderProgram::LoadInfo v, f;

	v.type = GL_VERTEX_SHADER;
	v.filename = "Shaders\\vertex.glsl";
	v.name = "Triangle Vertex";

	f.type = GL_FRAGMENT_SHADER;
	f.filename = "Shaders\\frag.glsl";
	f.name = "Triangle Frag";

	gSystem.load_shader("Triangle", { v, f });
}

int main(int argc, char **argv)
{
	rendering::GraphicsSystem gSystem;
	gSystem.initialize();

	loadTriangleProgram(gSystem);

	core::GameObject triGo;
	renderer = new rendering::RendererComponent(&triGo);
	triGo.add_component(renderer);

	renderer->program = gSystem.get_program("Triangle");
	renderer->model = Model::create_debug_triangle();

	glutDisplayFunc(renderScene);
	glutCloseFunc(close);
	glutMainLoop();

	return 0;
}
