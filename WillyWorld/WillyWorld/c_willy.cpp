#include "C_Willy.h"
#include "c_hex.h"
#include "c_map.h"
#include <math.h>
#include <stdlib.h>
#include <vector>

extern c_map *map;

C_Willy::C_Willy(int ID)
{
	init(ID);
}
C_Willy::C_Willy()
{
}


C_Willy::~C_Willy()
{
}
//------------------------------------------------------------------------------

void C_Willy::init(int ID){
	c_map *m = map;
	int temp = 0;
	for (int j = 0; j < CHROM_LENGHT; j++)
	{
		for (int o = 0; o < CHROM_WIDTH; o++)
		{
			temp = rand() % 2;
			chrom[j][o] = temp;
		}
	}
	int i = 1;
	while (i != 0) {
		y = rand() % (m->my_size);
		x = rand() % (m->my_size);

		if (m->tabWsk[x][y].zajete < 6) {
			m->tabWsk[x][y].zajete++;
			i = 0;
		}
	}
	m->tabWsk[x][y].WillyID = ID;
	color[0] = (rand() % 100) / 99.0;
	color[1] = (rand() % 100) / 99.0;
	color[2] = (rand() % 100) / 99.0;
	chosen = false;
	died = false;
	//calcChromValue() 

	energyResistance = (1000-calcChromValue(0))/1000;
	energyBeing = (1000 - calcChromValue(1)) / 40;
	energyMove = (1000 - calcChromValue(2)) / 14;
	ile_moge_temp = bezpieczny_zakres / energyResistance;

	energy = 100;
	FoodNeeded = 30;
	stalaEnergii = 50;

};

//------------------------------------------------------------------------------


void C_Willy::losowanie(std::vector<C_Willy>& willy1, c_data *d) {
	for (int i = 0; i < (rand()% d->ile_losowan); i++) {
		willy1[rand() % d->getPopSize()].chrom[rand() % d->chrom_lenght][rand() % d->chrom_width] = rand() % 2;
	}
}
void C_Willy::fitness_function(std::vector<C_Willy>& willy1, c_data *d) {
	for (int i = 0; i < d->getPopSize(); i++) {
		for (int j = 0; j < d->chrom_width; j++) {
			willy1[i].fitness[j] = willy1[i].calcChromValue(j) ;
		}
	}
}
void C_Willy::group_random(std::vector<C_Willy>& willy1, c_data *d) {
	int max = 0, chosen[GROUP_SIZE];
	int wybrany;
	for (int i = 0; i < d->group_size; i++) {
		chosen[i] = rand() % d->getPopSize();
		for (int j = 0; j < i; j++) {
			if (chosen[i] == chosen[j]) {
				i--;
				break;
			}

		}
	}
	for (int i = 0; i < d->chrom_width; i++)
	{
		for (int j = 0; j < d->group_size; j++)
		{
			if (willy1[chosen[j]].fitness[i] > max)
			{
				max = willy1[chosen[j]].fitness[i];
				wybrany = chosen[j];
			}
		}
		willy1[wybrany].chosen = true;
		max = 0;
	}
}
int C_Willy::ile_wybranych(std::vector<C_Willy> willy1, c_data *d) {
	int a = 0;
	for (int i = 0; i < d->getPopSize(); i++) {
		if (willy1[i].chosen == true) {
			a++;
		}
	}
	return a;
}
void C_Willy::new_population(std::vector<C_Willy>& willy1, c_data *d, int wybranych) {
	int j = 0;
	C_Willy* pom = new C_Willy[wybranych];
	for (int i = 0; i < d->getPopSize(); i++) {
		if (willy1[i].chosen == true) {
			for (int k = 0; k < d->chrom_lenght; k++) {
				for (int o = 0; o < d->chrom_width; o++) {
					pom[j].chrom[k][o] = willy1[i].chrom[k][o];
				}
			}
			willy1[i].chosen = false;
			j++;
		}
	}
	for (int i = 0; i < d->getPopSize(); i++) {
		for (j = 0; j < d->chrom_width; j++) {
			int a = rand() % 10, b = rand() % wybranych;
			for (int k = 0; k < a; k++) {
				willy1[i].chrom[k][j] = pom[b].chrom[k][j];
			}
			b = rand() % wybranych;
			for (int k = a; k < d->chrom_lenght; k++) {
				willy1[i].chrom[k][j] = pom[b].chrom[k][j];
			}
		}
	}
	delete[] pom;
}
float C_Willy::srednia_fitness(std::vector<C_Willy> willy1, c_data *d, int a) {
	float b = 0;
	for (int i = 0; i < d->getPopSize(); i++) {
		b = b + willy1[i].fitness[a];
	}
	b = b / d->getPopSize();
	return b;
}

//------------------------------------------------------------------------------------
//
//
void C_Willy::Poruszanie() {
	c_hex *next[6];
	for (int i = 0; i < 6; i++) {
		next[i] = map->tabWsk[x][y].next[i];
	}
	int ile_prob = 0;
	if (map->tabWsk[x][y].food == 0) {
		int i = 1;
		while (i != 0)
		{
			int b = rand() % 6;
			if (next[b] != NULL) {
				if (next[b]->zajete < 6) {
					i = 0;
					map->tabWsk[x][y].zajete--;
					next[b]->zajete++;
					x = next[b]->posX;
					y = next[b]->posY;
					/*bool w = CzyBylemTam(b);
					if (!w) {
						i = 0;
					}
					else {
						if (next(b).food >= FoodNeeded) {
							i = 0;
						}
					}*/
				}
				if (ile_prob > 6) {
					i = 0;
				}
			}
			ile_prob++;

		}
	}
}
void C_Willy::Jedzenie() {
	if (map->tabWsk[x][y].food != 0) {
		int jedzenie = map->tabWsk[x][y].food;
			if (jedzenie > FoodNeeded) {
				map->tabWsk[x][y].food -= FoodNeeded;
				C_Willy::AddEnergy(1);
			}
			else {
				map->tabWsk[x][y].food = 0;
				double w = jedzenie / FoodNeeded;
				C_Willy::AddEnergy(w);
			}
	}
}
int C_Willy::calcChromValue(int w) {
	int value = 0;
	for (int i = 0; i < CHROM_LENGHT; i++) {
		value += chrom[i][w] * pow(2, i);
	}
	return value;
}

bool C_Willy::calcSafeTemp() {
	int base = 10;

	if (map->tabWsk[x][y].temperature < ile_moge_temp ||
		map->tabWsk[x][y].temperature > -ile_moge_temp) {
		return true;
	}
	else {
		return false;
	}
}

void C_Willy::die() {
	map->tabWsk[x][y].zajete--;
	died = true;

}
void C_Willy::dont_die() {
	int this_id = ID;
	energyResistance = (1000 - calcChromValue(0)) / 1000;
	energyBeing = (1000 - calcChromValue(1)) / 40;
	energyMove = (1000 - calcChromValue(2)) / 14;
	ile_moge_temp = bezpieczny_zakres / energyResistance;
	energy = 100;
	died = false;
	int i = 1;
	while (i != 0) {
		y = rand() % (map->my_size);
		x = rand() % (map->my_size);

		if (map->tabWsk[x][y].zajete < 6) {
			map->tabWsk[x][y].zajete++;
			i = 0;
		}
	}
}

void C_Willy::Life() {
	if (calcSafeTemp()) {
		if (energy < energyBeing) {
			C_Willy::die();
		}
		else {
			energy -= energyBeing;
		}
	}
	else {
		double energyBeing2 = energyBeing * 1.5;
		if (energy < energyBeing2) {
			C_Willy::die();
		}
		else {
			energy -= energyBeing2;
		}
	}
}
void C_Willy::AddEnergy(double w) {
	energy += (stalaEnergii * w);
}
void C_Willy::obliczStatystyki() {
	energyResistance = (1000 - calcChromValue(0)) / 1000;
	energyBeing = (1000 - calcChromValue(1)) / 40;
	energyMove = (1000 - calcChromValue(2)) / 14;
	ile_moge_temp = bezpieczny_zakres / energyResistance;
}