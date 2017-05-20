#include "C_Willy.h"
#include "c_hex.h"
#include <math.h>
#include <stdlib.h>


C_Willy::C_Willy()
{
	init();
}


C_Willy::~C_Willy()
{
}

//------------------------------------------------------------------------------

void C_Willy::init() 
{
	int temp = 0;
	for (int j = 0; j < CHROM_LENGHT;j++) 
	{
		for (int o = 0;o < CHROM_WIDTH;o++) 
		{
			temp = rand() % 2;
			chrom[j][o] = temp;
		}
	}
};

//------------------------------------------------------------------------------


void C_Willy::losowanie(C_Willy willy1[]) {
	for (int i = 0; i < LOS; i++) {
		willy1[rand() % POPULATION].chrom[rand() % CHROM_LENGHT][rand() % CHROM_WIDTH] = rand() % 2;
	}
}
void C_Willy::fitness_function(C_Willy willy1[]) {
	for (int i = 0; i < POPULATION; i++) {
		for (int j = 0; j < CHROM_WIDTH; j++) {
			int a = 0, b = 0, c = 0;
			a = (4 * willy1[i].chrom[0][j]) + (2 * willy1[i].chrom[1][j]) + (1 * willy1[i].chrom[2][j]);
			b = (4 * willy1[i].chrom[3][j]) + (2 * willy1[i].chrom[4][j]) + (1 * willy1[i].chrom[5][j]);
			c = (4 * willy1[i].chrom[6][j]) + (2 * willy1[i].chrom[7][j]) + (1 * willy1[i].chrom[8][j]);
			willy1[i].fitness[j] = (1 * a) + (1 * b) + (1 * c);
		}
	}
}
void C_Willy::group_random(C_Willy willy1[]) {
	int max = 0, chosen[GROUP_SIZE];
	int wybrany;
	for (int i = 0; i < GROUP_SIZE; i++) {
		chosen[i] = rand() % POPULATION;
		for (int j = 0; j < i; j++) {
			if (chosen[i] == chosen[j]) {
				i--;
				break;
			}

		}
	}
	for (int i = 0; i < CHROM_WIDTH; i++)
	{
		for (int j = 0; j < GROUP_SIZE; j++)
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
int C_Willy::ile_wybranych(C_Willy willy1[]) {
	int a = 0;
	for (int i = 0; i < POPULATION; i++) {
		if (willy1[i].chosen == true) {
			a++;
		}
	}
	return a;
}
void C_Willy::new_population(C_Willy willy1[], int wybranych) {
	int j = 0;
	C_Willy* pom = new C_Willy[wybranych];
	for (int i = 0; i < POPULATION; i++) {
		if (willy1[i].chosen == true) {
			for (int k = 0; k < CHROM_LENGHT; k++) {
				for (int o = 0; o < CHROM_WIDTH; o++) {
					pom[j].chrom[k][o] = willy1[i].chrom[k][o];
				}
			}
			willy1[i].chosen = false;
			j++;
		}
	}
	for (int i = 0; i < POPULATION; i++) {
		for (j = 0; j < CHROM_WIDTH; j++) {
			int a = rand() % 10, b = rand() % wybranych;
			for (int k = 0; k < a; k++) {
				willy1[i].chrom[k][j] = pom[b].chrom[k][j];
			}
			b = rand() % wybranych;
			for (int k = a; k < CHROM_LENGHT; k++) {
				willy1[i].chrom[k][j] = pom[b].chrom[k][j];
			}
		}
	}
	delete[] pom;
}

float C_Willy::srednia_fitness(C_Willy willy1[], int a) {
	float b = 0;
	for (int i = 0; i < POPULATION; i++) {
		b = b + willy1[i].fitness[a];
	}
	b = b / POPULATION;
	return b;
}

//------------------------------------------------------------------------------------


