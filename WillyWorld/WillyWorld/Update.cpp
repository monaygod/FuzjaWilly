#include "c_willy.h"
#include "c_map.h"
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include "c_data.h"

using namespace std;


extern std::vector<C_Willy> willy;
extern c_data *dane;
extern c_map *map;
int main_static = 0;
bool czy_juz = true;
int ile_do_ruch = 11;
int ile_do_new_pop = 35;
int popAlive = 0;

void nowa_populacja(std::vector<C_Willy>& willy1, c_data *d1);
void ruch(std::vector<C_Willy>& willy1, c_data *d1);

void update() {
	popAlive = 0;
	if (ile_do_ruch > 10) {
		if (ile_do_new_pop > 25) {
			if (ile_do_new_pop > 35) {
				cout << "New Populaton" << endl;
				nowa_populacja(willy, dane);
				ile_do_new_pop = 0;
				ile_do_ruch = 0;
			}
			else {
				ile_do_new_pop++;
			}
		}
		else {
			for (int i = 0; i < dane->getPopSize(); i++) {
				if (willy[i].died != true) {
					popAlive++;
				}
			}
			cout << "Move " << "\t   Alive: " << popAlive << endl;
			ruch(willy, dane);
			//funckja ruchu
			ile_do_ruch = 0;
			ile_do_new_pop++;
		}
		
	}
	else {
		
		ile_do_ruch++;
	}
	Sleep(10);  //za ma³o obliczeñ
}

void nowa_populacja(std::vector<C_Willy>& willy1, c_data *d1) {
	map->clearMap();
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
//	map->initMap();
	
	for (int i = 0; i < d1->getPopSize(); i++)	{
		willy[i].dont_die();
	}
}

void ruch(std::vector<C_Willy>& willy1, c_data *d1) {
	for (int i = 0; i < d1->getPopSize(); i++) {
		if (willy[i].died == false) {
			willy1[i].Poruszanie();
			willy1[i].Jedzenie();
			willy1[i].Life();
		}
	}
	long int b = d1->getPopSize() * rand() % 40;
	for (int i = 0; i < b; i++) {
		C_Willy::losowanie(willy1, dane);
	}
	for (int i = 0; i < d1->getPopSize(); i++) {
		willy1[i].obliczStatystyki();
	}

}