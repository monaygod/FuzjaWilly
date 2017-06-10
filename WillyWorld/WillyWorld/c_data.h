#pragma once
#include <iostream>
#include <stdlib.h>
#include "Constans.h"

using namespace std;
class c_data
{
private:
	int wielkosc_populacji;
	int wielkosc_mapy;
	

public:
	int chrom_lenght = CHROM_LENGHT;
	int chrom_width = CHROM_WIDTH;
	int generations = GENERATIONS;
	int group_size = GROUP_SIZE;
	int ile_losowan = 100;

	inline c_data() {
		cout << "Population size: "; cin >> wielkosc_populacji; cout << endl;
		cout << "Map size: "; cin >> wielkosc_mapy; cout << endl;
	}
	inline int c_data::getMapSize() {
		return wielkosc_mapy;
	}
	inline int c_data::getPopSize()	{
		return wielkosc_populacji;
	}
	inline int c_data::getChromosomLenght() {
		return chrom_lenght;
	}
	inline int c_data::getChromosomWidth() {
		return chrom_width;
	}
	inline int c_data::getGenerations() {
		return generations;
	}
	inline int c_data::getGroupSize() {
		return group_size;
	}
	inline int c_data::getIleLosowan() {
		return ile_losowan;
	}
	~c_data();
};

