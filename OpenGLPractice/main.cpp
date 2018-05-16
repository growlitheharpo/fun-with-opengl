#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Logging.h"
#include "ShaderProgram.h"

GLuint triangle_program;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);

	glUseProgram(triangle_program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	graphics::ShaderProgram program;
	triangle_program = program.createProgram("Shaders\\vertex.glsl", "Shaders\\frag.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");

	glewInit();
	DEBUG_IF_ELSE(glewIsSupported("GL_VERSION_4_4"),
		LOG("GLEW Version is 4.4."),
		LOG_ERR("GLEW 4.4 is not supported!"));

	init();

	glutDisplayFunc(renderScene);
	glutMainLoop();

	return 0;
}
