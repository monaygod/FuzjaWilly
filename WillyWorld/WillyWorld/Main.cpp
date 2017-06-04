#include "Render.h"
#include "Update.h"
#include "c_data.h"
#include "c_willy.h"
#include "c_map.h"


#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <vector>


using namespace std;
c_data *dane;
std::vector<C_Willy> willy;

int main(int argc, char* argv[]) {
	dane = new c_data();
	srand((unsigned int)time(NULL));
	c_map map(dane->getMapSize());
	for (int i = 0; i < dane->getPopSize(); i++) {
		C_Willy asd;
		willy.push_back(asd);
	}
	
	//for (int i = 0; i < dane->generations; i++) {
	//	Sleep(1000);
	//	update();
	//}

	initMap();
	Sasiedzi();


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
	system("pause");
	return 0;
}
