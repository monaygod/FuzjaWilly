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
c_map *map;
std::vector<C_Willy> willy;

int main(int argc, char* argv[]) {
	
	srand((unsigned int)time(NULL));


	dane = new c_data();
	map = new c_map(dane->getMapSize());

	for (int i = 0; i < dane->getPopSize(); i++) {
		C_Willy asd(i);
		asd.ID = i;
		willy.push_back(asd);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(550, 300);
	glutCreateWindow("Willy World || JakubC && JonatanD");

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
