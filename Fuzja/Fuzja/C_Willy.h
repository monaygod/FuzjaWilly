#pragma once
#define GENERATIONS 20
#define CHROM_LENGHT 9
#define CHROM_WIDTH 3
#define POPULATION 10000
#define GROUP_SIZE 15
#define LOS 100
class C_Willy
{
public:
	double HexID;
	bool chrom[CHROM_LENGHT][CHROM_WIDTH];
	int fitness[CHROM_WIDTH];
	bool chosen = false;


	void init();
	C_Willy();
	/*		algorytm genetyczny		*/
	static void losowanie(C_Willy willy1[]);
	static void fitness_function( C_Willy willy1[]);
	static void group_random( C_Willy willy1[]);
	static int ile_wybranych( C_Willy willy1[]);
	static void new_population( C_Willy willy1[], int wybranych);
	static float srednia_fitness( C_Willy willy1[], int a);
	/*------------------------------*/
	

	~C_Willy();
	
};
