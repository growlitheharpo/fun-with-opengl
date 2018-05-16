#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Logging.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "GameObject.h"

Model triangle_model;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	//triangle_model.activate();
	//glUseProgram(triangle_program);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void close()
{
	DLOG("Finished!");
	glutLeaveMainLoop();
}

void init()
{
	glEnable(GL_DEPTH_TEST);

	triangle_model = Model::create_debug_triangle();

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

	// *****
	// glut main loop holds until we're done
	glutMainLoop();
	//
	// *****

	triangle_model.release();
	//glDeleteProgram(triangle_program);

	return 0;
}
