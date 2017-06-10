#pragma once
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <atltime.h>
#include <windows.h>
#include <iostream>

#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "Constans.h"

void reshape(int w, int h);
void initGL();
void drawHex(double center[2], double color[3]);
void drawWilly(double center[2], int max);
void initMap();
void Sasiedzi();
void makeMap(int layers);
void makeMap_2(int layers);
void makeMap_3();
void display();
void Keys(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void MouseWheel(int wheel, int direction, int x, int y);
//int render(int argc, char* argv[]);