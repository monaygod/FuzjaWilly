#include "c_willy.h"
#include "c_map.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "c_data.h"

using namespace std;


extern std::vector<C_Willy> willy;
extern c_data *dane;
extern c_map map;
int main_static = 0;
bool czy_juz = true;

void nowa_populacja(std::vector<C_Willy>& willy1, c_data *d1);

void update() {
	nowa_populacja(willy, dane);
}








void nowa_populacja(std::vector<C_Willy>& willy1, c_data *d1) {
	C_Willy::fitness_function(willy1,d1);
	for (int i = 0; i < 100; i++) {
		C_Willy::group_random(willy1, d1);
	}
	int wybranych = C_Willy::ile_wybranych(willy1, d1);
	C_Willy::new_population(willy1, d1, wybranych);
	cout << "Pop: " << main_static + 1 << "\t\t1.: " << C_Willy::srednia_fitness(willy1, d1, 0) <<
		"\t2.: " << C_Willy::srednia_fitness(willy1, d1, 1) <<
		"\t3.: " << C_Willy::srednia_fitness(willy1, d1, 2) << "\t" << wybranych << endl;
	main_static++;
}