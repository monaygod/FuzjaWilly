#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#include "C_Willy.h"
#include "Render.h"
#include "Update.h"
#include "c_hex.h"


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 500);
	glutCreateWindow("Map Test");

	initGL();

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutIdleFunc(update);
	glutReshapeFunc(reshape);

	glutSpecialFunc(Keys);
	glutMouseFunc(mouse);
	glutMouseWheelFunc(MouseWheel);

	glutMainLoop();
	return 0;
}