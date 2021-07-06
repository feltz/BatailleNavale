#pragma once

#include "Cell.h"
#include <string>
using namespace std;

class Ship
{
protected: 
	Cell* cells[5];
	int nb_cells, iter_cell, lifes;
public: 
	Ship(const Cell & begin, int nb_cells, bool hor);
	~Ship();
	Cell* getFirstCell();
	Cell* getNextCell();
};