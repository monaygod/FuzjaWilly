#include "c_map.h"


c_map::c_map(int size)
{
	my_size = size;
	tabWsk = new c_hex*[my_size];
	for (int i = 0; i < my_size; i++) {
		tabWsk[i] = new c_hex[my_size];
	}
	initMap();
	Sasiedzi();
}
void c_map::initMap() {
	double hexHeight = 2 * 0.866 * hexSize;
	double hexCenter[2];
	hexCenter[0] = -1 + 2 * hexSize;
	hexCenter[1] = 1 - hexHeight;
	int counter = 0;
	for (int y = 0; y < my_size; y++) {
		for (int x = 0; x < my_size; x++) {
			tabWsk[x][y].ID = counter;
			tabWsk[x][y].posX = x;
			tabWsk[x][y].posY = y;
			tabWsk[x][y].center[0] = hexCenter[0];
			tabWsk[x][y].center[1] = hexCenter[1];

			/* asd */
			tabWsk[x][y].temperature = (rand() % 60 - 20);
			tabWsk[x][y].food = rand() % 100;

			counter++;
			hexCenter[0] += 3 * hexSize;
			if (x % 2 == 0) {
				hexCenter[1] -= hexHeight;
			}
			else {
				hexCenter[1] += hexHeight;
			}
		}
		hexCenter[0] = -1 + 2 * hexSize;
		hexCenter[1] = 1 - hexHeight;
		hexCenter[1] -= 2 * (y + 1) * hexHeight;
	}
}
void c_map::Sasiedzi() {
	for (int y = 0; y < my_size; y++) {
		for (int x = 0; x < my_size; x++) {
			/*tabWsk[x][y].next[0] = tabWsk[x][y - 1];
			tabWsk[x][y].next[3] = tabWsk[x][y + 1];
			if (y % 2 == 0) {
				tabWsk[x][y].next[1] = tabWsk[x + 1][y];
				tabWsk[x][y].next[2] = tabWsk[x + 1][y + 1];
				tabWsk[x][y].next[4] = tabWsk[x - 1][y - 1];
				tabWsk[x][y].next[5] = tabWsk[x - 1][y];
			}
			else {
				tabWsk[x][y].next[1] = tabWsk[x + 1][y - 1];
				tabWsk[x][y].next[2] = tabWsk[x + 1][y];
				tabWsk[x][y].next[4] = tabWsk[x - 1][y];
				tabWsk[x][y].next[5] = tabWsk[x - 1][y - 1];
			}*/
		}
	}
}

c_map::~c_map()
{
	for (int i = 0; i < my_size; ++i)
	{
		delete[] tabWsk[i];
	}
	delete[] tabWsk;
}
