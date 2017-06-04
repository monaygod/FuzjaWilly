#pragma once
#include "Constans.h"
#include "c_hex.h"
#include "c_data.h"
#include <math.h>
#include <stdlib.h>
#include <vector>

class C_Willy
{
public:
	int HexID[2];
	bool chrom[CHROM_LENGHT][CHROM_WIDTH];
	int fitness[CHROM_WIDTH];
	bool chosen = false;
	bool bylem_tam[1000];


	void init();
	C_Willy();
	/*		algorytm genetyczny		*/
	static void losowanie(std::vector<C_Willy>& willy1, c_data *d);
	static void fitness_function(std::vector<C_Willy>& willy1, c_data *d);
	static void group_random(std::vector<C_Willy>& willy1, c_data *d);
	static int ile_wybranych(std::vector<C_Willy> willy1, c_data *d);
	static void new_population(std::vector<C_Willy>& willy1, c_data *d, int wybranych);
	static float srednia_fitness(std::vector<C_Willy> willy1, c_data *d, int a);
	///*------------------------------*/
	////void C_Willy::Poruszanie();

	~C_Willy();

};

