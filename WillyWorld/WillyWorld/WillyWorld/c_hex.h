#pragma once
class c_hex
{
public:
	int posX;
	int posY;
	double center[2];
	double temperature;
	double food;
	//double height;
	int ID;
	int WillyID=-1;
	bool populated;
	int zajete;	
	c_hex *next[6];

	c_hex();
	~c_hex();

};

