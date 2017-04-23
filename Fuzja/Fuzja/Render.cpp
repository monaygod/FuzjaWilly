#include <iostream>
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

float angleCouter = 0;
double rotate_y = 0;
double rotate_x = 0;
double zoom = 0.5;
int layers = 1;

void setLayers(int x) {
	layers = x;
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0, GLfloat(w) / GLfloat(h), 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);

}

void initGL() {
	GLfloat r = 0.2;
	GLfloat g = 0.3;
	GLfloat b = 0.5;
	glClearColor(r, g, b, 1.0);
}
void drawHex(double center[2], double hexSize, double color[3]) {
	float hexHeight = 2 * 0.866*hexSize;
	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	/*1*/glVertex3f(center[0] - (2 * hexSize), center[1], 0.01);
	glColor3f(color[0] + 0.1, color[1], color[2]);
	/*2*/glVertex3f(center[0] - hexSize, center[1] + hexHeight, 0.01);
	glColor3f(color[0] + 0.3, color[1], color[2]);
	/*3*/glVertex3f(center[0] + hexSize, center[1] + hexHeight, 0.01);
	glColor3f(color[0] + 0.5, color[1], color[2]);
	/*4*/glVertex3f(center[0] + (2 * hexSize), center[1], 0.01);
	glColor3f(color[0] + 0.7, color[1], color[2]);
	/*5*/glVertex3f(center[0] + hexSize, center[1] - hexHeight, 0.01);
	glColor3f(color[0] + 0.9, color[1], color[2]);
	/*6*/glVertex3f(center[0] - hexSize, center[1] - hexHeight, 0.01);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	/*1*/glVertex3f(center[0] - (2 * hexSize), center[1], 0.0);
	glColor3f(color[0] + 0.1, color[1], color[2]);
	/*2*/glVertex3f(center[0] - hexSize, center[1] + hexHeight, 0.0);
	glColor3f(color[0] + 0.3, color[1], color[2]);
	/*3*/glVertex3f(center[0] + hexSize, center[1] + hexHeight, 0.0);
	glColor3f(color[0] + 0.5, color[1], color[2]);
	/*4*/glVertex3f(center[0] + (2 * hexSize), center[1], 0.0);
	glColor3f(color[0] + 0.7, color[1], color[2]);
	/*5*/glVertex3f(center[0] + hexSize, center[1] - hexHeight, 0.0);
	glColor3f(color[0] + 0.9, color[1], color[2]);
	/*6*/glVertex3f(center[0] - hexSize, center[1] - hexHeight, 0.0);
	glEnd();
}
/*ale zmiany*/

void makeMap(int layers) {
	double forFun = 0.1;
	double origin[2];
	origin[0] = 0;
	origin[1] = 0;
	double hexCenter[2];
	double hexSize = 0.009;
	double hexHeight = 2 * 0.866 * hexSize;
	double color[3];
	color[0] = 0.1;	color[1] = 0.5; color[2] = 0.7;


	drawHex(origin, hexSize, color);

	for (int i = 1; i <= layers; i++) {
		//przesuniecie w gore
		hexCenter[0] = origin[0];
		hexCenter[1] = origin[1] + 2 * i*hexHeight;

		for (int j = 0; j < i * 6; j++) {
			forFun += 0.0005;
			color[0] = forFun;	color[1] = forFun; color[2] = 0.3;
			drawHex(hexCenter, hexSize, color);

			if (j < i) {
				//skos w prawo
				hexCenter[0] += 3 * hexSize;
				hexCenter[1] -= hexHeight;
			}
			if (j >= i && j < i + i) {
				//pionowo w dol
				hexCenter[0] += 0;
				hexCenter[1] -= 2 * hexHeight;
			}
			if (j >= i + i && j < i + i + i) {
				//skos w lewo
				hexCenter[0] -= 3 * hexSize;
				hexCenter[1] -= hexHeight;
			}
			if (j >= i + i + i && j < i + i + i + i) {
				//skos w lewo
				hexCenter[0] -= 3 * hexSize;
				hexCenter[1] += hexHeight;
			}
			if (j >= i + i + i + i && j < i + i + i + i + i) {
				//pionowo w gore
				hexCenter[0] += 0;
				hexCenter[1] += 2 * hexHeight;
			}
			if (j >= i + i + i + i + i && j < i + i + i + i + i + i) {
				//skos w prawo
				hexCenter[0] += 3 * hexSize;
				hexCenter[1] += hexHeight;
			}
		}
	}


}
void test() {
	std::cout << "asd";
	double lastTime = GetTickCount();
	double current;
		while (1)
		{
			current = GetTickCount();
			double delta = current - lastTime;
			if (delta > 1000) break;
		}
		lastTime = current;
}
void display() {
	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	float hexSize = 0.0900;
	float hexHeight = 2 * 0.866 * hexSize;
	double center[2];
	center[0] = 0;
	center[1] = 0;

	test();
	glLoadIdentity();

	glPushMatrix(); // save the current matrix
	glScalef(zoom, zoom, 1.0); // scale the matrix

	glRotatef(rotate_x, 1.0, 0.0, 0.0);	// Rotate by rotate_x in X-AXIS
	glRotatef(rotate_y, 0.0, 1.0, 0.0); // Rotate in Y-AXIS

										//drawHex(center, hexSize);
	makeMap(layers);

	glPopMatrix(); // load the unscaled matrix	
	glutSwapBuffers();
}

void Keys(int key, int x, int y) {

	if (key == GLUT_KEY_RIGHT) { cout << rotate_y << "\n"; rotate_y += 5; }

	else if (key == GLUT_KEY_LEFT) { cout << rotate_y << "\n"; rotate_y -= 5; }

	else if (key == GLUT_KEY_UP) { cout << rotate_x << "\n"; rotate_x += 5; }

	else if (key == GLUT_KEY_DOWN) { cout << rotate_x << "\n"; rotate_x -= 5; }

	//  Request display update
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	//Right  
	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	{
		layers += 1;
	}
	//Left  
	else if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		layers -= 1;
	}
	glutPostRedisplay();
}


void MouseWheel(int wheel, int direction, int x, int y) {

	wheel = 0;
	if (direction == -1) {
		zoom += 0.05;
	}
	else if (direction == +1) {
		zoom -= 0.05;
	}
	glutPostRedisplay();
}

int render(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 500);
	glutCreateWindow("Map Test");

	initGL();

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutSpecialFunc(Keys);
	glutMouseFunc(mouse);
	glutMouseWheelFunc(MouseWheel);

	glutMainLoop();
	return 0;
}