#include "C_Willy.h"
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>

using namespace std;
int main_static = 1;
bool czy_juz = true;


void update(C_Willy willy1[]) {

}

void nowa_populacja(C_Willy willy1[]) {
		C_Willy::fitness_function(willy1);
		for (int i = 0;i < 2000;i++) {
			C_Willy::group_random(willy1);
		}
		int wybranych = C_Willy::ile_wybranych(willy1);
		C_Willy::new_population(willy1, wybranych);
		cout << "Pop: " << main_static + 1 << "\t\t1.: " << C_Willy::srednia_fitness(willy1, 0) <<
			"\t2.: " << C_Willy::srednia_fitness(willy1, 1) <<
			"\t3.: " << C_Willy::srednia_fitness(willy1, 2) << "\t" << wybranych << endl;
		main_static++;
}