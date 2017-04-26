#pragma once
class c_hex
{
public:
	int posX;
	int posY;
	double temperature;
	double food;
	//double height;
	int ID;
	bool habitat;
	c_hex *next[6];

	c_hex();
	~c_hex();
	
};

