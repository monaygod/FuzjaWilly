#include "C_Willy.h"
#include "c_hex.h"
#include <math.h>
#include <stdlib.h>
#include <vector>


C_Willy::C_Willy()
{
	init();
}


C_Willy::~C_Willy()
{
}
//------------------------------------------------------------------------------

void C_Willy::init(){
	int temp = 0;
	for (int j = 0; j < CHROM_LENGHT; j++)
	{
		for (int o = 0; o < CHROM_WIDTH; o++)
		{
			temp = rand() % 2;
			chrom[j][o] = temp;
		}
	}
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
			int a = 0, b = 0, c = 0;
			a = (4 * willy1[i].chrom[0][j]) + (2 * willy1[i].chrom[1][j]) + (1 * willy1[i].chrom[2][j]);
			b = (4 * willy1[i].chrom[3][j]) + (2 * willy1[i].chrom[4][j]) + (1 * willy1[i].chrom[5][j]);
			c = (4 * willy1[i].chrom[6][j]) + (2 * willy1[i].chrom[7][j]) + (1 * willy1[i].chrom[8][j]);
			willy1[i].fitness[j] = (1 * a) + (1 * b) + (1 * c);
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
//void C_Willy::Poruszanie() {
//	c_hex *next[6];
//	for (int i = 0; i < 6; i++) {
//		next[i] = c_hex::getSasiedzi(i);
//	}
//	int i = 1;
//	while (i != 0)
//	{
//		int b = rand() % 6;
//		if (next(b) != NULL) {
//			bool w = CzyBylemTam(b);
//			if (!w) {
//				i = 0;
//			}
//			else {
//				if (next(b).food >= FoodNeeded) {
//					i = 0;
//				}
//			}
//		}
//	}
//}
//
//void C_Willy::Jedzenie() {
//	int jedzenie = c_hex::getFood(x, y);
//	if (jedzenie > FoodNeeded) {
//		c_hex::consume(x, y, FoodNeeded);
//		C_Willy::AddEnergy(1);
//	}
//	else {
//		c_hex::consume(x, y, jedzenie);
//		double w = jedzenie / FoodNeeded;
//		C_Willy::AddEnergy(w);
//	}
//}
//
//void C_Willy::Life() {
//	if (energy < energyNeeded) {
//		C_Willy::die();
//	}
//	else {
//		energy -= energyNeeded;
//	}
//}