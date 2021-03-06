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
	int ID;
	bool chrom[CHROM_LENGHT][CHROM_WIDTH];
	int fitness[CHROM_WIDTH];
	double energyBeing;
	double energyMove;
	double energyResistance;
	double ile_moge_temp;
	double FoodNeeded;
	double stalaEnergii;
	bool chosen;
	double color[3];
	int x;
	int y;
	bool died;
	double energy;


	void init(int ID);
	C_Willy(int ID);
	C_Willy();
	/*		algorytm genetyczny		*/
	static void losowanie(std::vector<C_Willy>& willy1, c_data *d);
	static void fitness_function(std::vector<C_Willy>& willy1, c_data *d);
	static void group_random(std::vector<C_Willy>& willy1, c_data *d);
	static int ile_wybranych(std::vector<C_Willy> willy1, c_data *d);
	static void new_population(std::vector<C_Willy>& willy1, c_data *d, int wybranych);
	static float srednia_fitness(std::vector<C_Willy> willy1, c_data *d, int a);
	///*------------------------------*/
	void C_Willy::Poruszanie();
	void C_Willy::Jedzenie();
	int C_Willy::calcChromValue(int w);
	bool C_Willy::calcSafeTemp();
	void C_Willy::die();
	void C_Willy::dont_die();
	void C_Willy::Life();
	void C_Willy::AddEnergy(double w);
	void C_Willy::obliczStatystyki();
	~C_Willy();

};

