#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Logging.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "GraphicsSystem.h"
#include "GameObject.h"
#include "RendererComponent.h"

rendering::GraphicsSystem gSystem;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	gSystem.render();

	glutSwapBuffers();
}

void close()
{
	DLOG("Finished!");
	glutLeaveMainLoop();
}

void loadTriangleProgram()
{
	rendering::ShaderProgram::LoadInfo v, f;

	v.type = GL_VERTEX_SHADER;
	v.filename = "Shaders\\vertex.glsl";
	v.name = "Triangle Vertex";

	f.type = GL_FRAGMENT_SHADER;
	f.filename = "Shaders\\frag.glsl";
	f.name = "Triangle Frag";

	gSystem.loadShader("Triangle", { v, f });
}

int main(int argc, char **argv)
{
	gSystem.initialize();
	
	loadTriangleProgram();
	
	core::GameObject triangleObj;
	
	rendering::RendererComponent* renderer = triangleObj.addComponent(gSystem.createRenderComponent("Triangle"));
	renderer->model = Model::create_debug_triangle();
	
	glutDisplayFunc(renderScene);
	glutCloseFunc(close);
	glutMainLoop();

	return 0;
}
