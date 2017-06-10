#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <math.h>

#include "c_hex.h"
#include "C_Willy.h"
#include "Update.h"
#include "c_map.h"
using namespace std;

float angleCouter = 0;
double rotate_y = 0;
double rotate_x = 0;
double zoom = 0.5;
int layers = 3;
extern c_map *map;
extern c_data *dane;
extern std::vector<C_Willy> willy;
void drawWilly(double center[2]);


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void initGL() {
	GLfloat r = 0.3;
	GLfloat g = 0.3;
	GLfloat b = 0.3;
	glClearColor(r, g, b, 1.0);
}

void drawWilly(double center[2], int max, int x, int y) {
	double willyCenter[6][2];
	float hexHeight = 0.866 * hexSize;

	willyCenter[0][0] = center[0] - (hexSize);
	willyCenter[0][1] = center[1];

	willyCenter[1][0] = center[0] - (hexSize / 2);
	willyCenter[1][1] = center[1] + hexHeight;

	willyCenter[2][0] = center[0] + (hexSize / 2);
	willyCenter[2][1] = center[1] + hexHeight;

	willyCenter[3][0] = center[0] + (hexSize);
	willyCenter[3][1] = center[1];

	willyCenter[4][0] = center[0] + (hexSize / 2);
	willyCenter[4][1] = center[1] - hexHeight;

	willyCenter[5][0] = center[0] - (hexSize / 2);
	willyCenter[5][1] = center[1] - hexHeight;

	float radius = 0.01;
	for (int w = 0; w < max; w++) {
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		for (int i = 0; i < 360; i++)
		{
			float theta = 2.0f * 3.1415926f * float(i) / float(360);
			glVertex3f(willyCenter[w][0] + (radius*cosf(theta)), willyCenter[w][1] + (radius*sinf(theta)), 0.0);
		}
		glEnd();
	}
	

}

void drawHex(double color1[3], c_map *m, int x, int y) {

	float hexHeight = 2 * 0.866 * hexSize;
	double center[2];
	double color[3];
	center[0] = m->tabWsk[x][y].center[0];
	center[1] = m->tabWsk[x][y].center[1];
	color[0] = color1[0];
	color[1] = color1[1];
	color[2] = color1[2];
	double temperature = 0;

	temperature = m->tabWsk[x][y].temperature;
	if (temperature <= 0.0) {
		color[0] += (temperature / 50.0);
		color[1] += (temperature / 100.0);
		color[2] -= (temperature / 1000.0);
	}
	else {
		color[0] += (temperature / 1000.0);
		color[1] -= (temperature / 100.0);
		color[2] -= (temperature / 50.0);
	}

	if (m->tabWsk[x][y].zajete != 0) {

		//color[0] = willy[map->tabWsk[x][y].WillyID].color[0];
		//color[1] = willy[map->tabWsk[x][y].WillyID].color[1];
		//color[2] = willy[map->tabWsk[x][y].WillyID].color[2];
		drawWilly(center, m->tabWsk[x][y].zajete,x,y);

	}

	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	/*1*/glVertex3f(center[0] - (2 * hexSize), center[1], 0.0);
	glColor3f(color[0] + 0.01, color[1] + 0.1, color[2] + 0.1);
	/*2*/glVertex3f(center[0] - hexSize, center[1] + hexHeight, 0.0);
	glColor3f(color[0] + 0.05, color[1] + 0.05, color[2] + 0.05);
	/*3*/glVertex3f(center[0] + hexSize, center[1] + hexHeight, 0.0);
	glColor3f(color[0] + 0.10, color[1] + 0.10, color[2] + 0.10);
	/*4*/glVertex3f(center[0] + (2 * hexSize), center[1], 0.0);
	glColor3f(color[0] + 0.15, color[1] + 0.15, color[2] + 0.15);
	/*5*/glVertex3f(center[0] + hexSize, center[1] - hexHeight, 0.0);
	glColor3f(color[0] + 0.20, color[1] + 0.20, color[2] + 0.20);
	/*6*/glVertex3f(center[0] - hexSize, center[1] - hexHeight, 0.0);
	glEnd();

	
}


void makeMap_3() {
	double color[3];
	color[0] = 0.7;	color[1] = 0.7; color[2] = 0.7;
	for (int y = 0; y < map->my_size; y++) {
		for (int x = 0; x < map->my_size; x++) {
			drawHex(color, map, x, y);
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutPostRedisplay();

	glLoadIdentity();

	gluLookAt(0.25 + rotate_x, -0.4 + rotate_y, 1.0,
			 0.25 + rotate_x, -0.4 + rotate_y, 0.0,
			  0.0, 1.0, 0.0);

	glPushMatrix(); // save the current matrix
	glScalef(zoom, zoom, 1.0); // scale the matrix

	//glRotatef(rotate_x, 1.0, 0.0, 0.0);	// Rotate by rotate_x in X-AXIS
	//glRotatef(rotate_y, 0.0, 1.0, 0.0); // Rotate in Y-AXIS
									
	makeMap_3();

	glPopMatrix(); // load the unscaled matrix	
	glutSwapBuffers();
}

void Keys(int key, int x, int y) {

	if (key == GLUT_KEY_RIGHT) { /*cout << rotate_x << "\n";*/ rotate_x += 0.05; }

	else if (key == GLUT_KEY_LEFT) { /*cout << rotate_x << "\n";*/ rotate_x -= 0.05; }

	else if (key == GLUT_KEY_UP) { /*cout << rotate_y << "\n";*/ rotate_y += 0.05; }

	else if (key == GLUT_KEY_DOWN) { /*cout << rotate_y << "\n";*/ rotate_y -= 0.05; }

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
		zoom -= 0.05;
		/*cout << "zoom:"<<zoom;*/
	}
	else if (direction == +1) {
		zoom += 0.05;
		/*cout << "zoom:" << zoom;*/
	}
	glutPostRedisplay();
}
