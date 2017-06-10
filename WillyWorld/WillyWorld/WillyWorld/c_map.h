#pragma once
#include "c_willy.h"
#include "c_map.h"
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include "c_data.h"
#include "c_hex.h"

class c_map
{
public:
	int my_size;
	c_hex **tabWsk;


	void initMap();
	void Sasiedzi();
	c_map(int size);
	
	~c_map();
};

