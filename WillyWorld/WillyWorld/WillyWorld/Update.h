#pragma once
#include "c_willy.h"
#include "c_map.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "c_data.h"


void update();
void nowa_populacja(std::vector<C_Willy>& willy1, c_data *d1);
void ruch(std::vector<C_Willy>& willy1, c_data *d1);