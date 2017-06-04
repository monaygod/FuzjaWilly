#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <math.h>

#include "c_hex.h"
#include "C_Willy.h"
#include "Update.h"
#define MAP_SIZE 3
#define hexSize 0.10
using namespace std;

float angleCouter = 0;
double rotate_y = 0;
double rotate_x = 0;
double zoom = 0.5;
int layers = 3;
c_hex *tabWsk[MAP_SIZE][MAP_SIZE];


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


void drawHex(double center[2], double color[3]) {

	float hexHeight = 2 * 0.866 * hexSize;
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

void initMap() {
	double hexHeight = 2 * 0.866 * hexSize;
	double hexCenter[2];
	int counter = 0;
	for (int y = 0; y < MAP_SIZE; y++) {
		for (int x = 0; x < MAP_SIZE; x++) {
			tabWsk[x][y] = new c_hex();
			tabWsk[x][y]->ID = counter;
			tabWsk[x][y]->posX = x;
			tabWsk[x][y]->posY = y;
			tabWsk[x][y]->center[0] = hexCenter[0];
			tabWsk[x][y]->center[1] = hexCenter[1];

			/* asd */
			tabWsk[x][y]->temperature = (rand() % 60 - 20);
			tabWsk[x][y]->food = rand() % 100;

			counter++;
			hexCenter[0] += 3 * hexSize;
			if (x % 2 == 0) {
				hexCenter[1] -= hexHeight;
			}
			else {
				hexCenter[1] += hexHeight;
			}
		}
		hexCenter[0] = -1 + 2 * hexSize;
		hexCenter[1] = 1 - hexHeight;
		hexCenter[1] -= 2 * (y+1) * hexHeight;
	}
}
void Sasiedzi() {
	for (int y = 0; y < MAP_SIZE; y++) {
		for (int x = 0; x < MAP_SIZE; x++) {
			tabWsk[x][y]->next[0] = tabWsk[x][y - 1];
			tabWsk[x][y]->next[3] = tabWsk[x][y + 1];
			if (y % 2 == 0) {
				tabWsk[x][y]->next[1] = tabWsk[x + 1][y];
				tabWsk[x][y]->next[2] = tabWsk[x + 1][y + 1];
				tabWsk[x][y]->next[4] = tabWsk[x - 1][y - 1];
				tabWsk[x][y]->next[5] = tabWsk[x - 1][y];
			}
			else {
				tabWsk[x][y]->next[1] = tabWsk[x + 1][y - 1];
				tabWsk[x][y]->next[2] = tabWsk[x + 1][y];
				tabWsk[x][y]->next[4] = tabWsk[x - 1][y];
				tabWsk[x][y]->next[5] = tabWsk[x - 1][y - 1];
			}
		}
	}
}

//void makeMap(int layers) {
//	double forFun = 0.1;
//	double origin[2];
//	origin[0] = 0;
//	origin[1] = 0;
//	double hexCenter[2];
//	double hexSize = 0.010;
//	double hexHeight = 2 * 0.866 * hexSize;
//	double color[3];
//	color[0] = 0.5;	color[1] = 0.5; color[2] = 0.5;
//
//
//	drawHex(origin, hexSize, color);
//
//	for (int i = 1; i <= layers; i++) {
//		//przesuniecie w gore
//		hexCenter[0] = origin[0];
//		hexCenter[1] = origin[1] + 2 * i*hexHeight;
//
//		for (int j = 0; j < i * 6; j++) {
//			forFun += 0.0005;
//			color[0] = 0.01;	color[1] = forFun; color[2] = 2 - forFun;
//			drawHex(hexCenter, hexSize, color);
//
//			if (j < i) {
//				//skos w prawo
//				hexCenter[0] += 3 * hexSize;
//				hexCenter[1] -= hexHeight;
//			}
//			if (j >= i && j < i + i) {
//				//pionowo w dol
//				hexCenter[0] += 0;
//				hexCenter[1] -= 2 * hexHeight;
//			}
//			if (j >= i + i && j < i + i + i) {
//				//skos w lewo
//				hexCenter[0] -= 3 * hexSize;
//				hexCenter[1] -= hexHeight;
//			}
//			if (j >= i + i + i && j < i + i + i + i) {
//				//skos w lewo
//				hexCenter[0] -= 3 * hexSize;
//				hexCenter[1] += hexHeight;
//			}
//			if (j >= i + i + i + i && j < i + i + i + i + i) {
//				//pionowo w gore
//				hexCenter[0] += 0;
//				hexCenter[1] += 2 * hexHeight;
//			}
//			if (j >= i + i + i + i + i && j < i + i + i + i + i + i) {
//				//skos w prawo
//				hexCenter[0] += 3 * hexSize;
//				hexCenter[1] += hexHeight;
//			}
//		}
//	}
//}

//void makeMap_2(int layers) {
//	double color[3];
//	int couter = 1;
//	double hexHeight = 2 * 0.866 * hexSize;
//	double hexCenter[2];
//
//	hexCenter[0] = -1 + 2 * hexSize;
//	hexCenter[1] = 1 - hexHeight;
//
//	color[0] = 0.5;	color[1] = 0.5; color[2] = 0.5;
//
//	for (int x = 0; x < layers; x++) {
//
//		for (int y = 1; y < layers; y++) {
//			drawHex(hexCenter, color);
//			hexCenter[0] += 3 * hexSize;
//			if (y % 2 == 1) {
//				hexCenter[1] -= hexHeight;
//			}
//			else if (y % 2 == 0) {
//				hexCenter[1] += hexHeight;
//			}
//
//		}
//		hexCenter[0] = -1 + 2 * hexSize;
//		hexCenter[1] = 1 - hexHeight;
//		hexCenter[1] -= 2 * x * hexHeight;
//	}
//}

void makeMap_3() {
	double color[3];
	color[0] = 0.5;	color[1] = 0.5; color[2] = 0.5;
	for (int y = 0; y < MAP_SIZE; y++) {
		for (int x = 0; x < MAP_SIZE; x++) {
			drawHex(tabWsk[x][y]->center, color);
		}
	}
}
void display() {
	//  Clear screen and Z-buffer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	float hexHeight = 2 * 0.866 * hexSize;
	double center[2];
	center[0] = 0;
	center[1] = 0;


	glLoadIdentity();

	glPushMatrix(); // save the current matrix
	glScalef(zoom, zoom, 1.0); // scale the matrix

	glRotatef(rotate_x, 1.0, 0.0, 0.0);	// Rotate by rotate_x in X-AXIS
	glRotatef(rotate_y, 0.0, 1.0, 0.0); // Rotate in Y-AXIS

										//drawHex(center, hexSize);
	makeMap_3();

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
