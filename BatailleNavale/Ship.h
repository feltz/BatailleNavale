#pragma once

#include "Cell.h"
#include <string>
using namespace std;

class Ship
{
private:
	bool ask_for_direction();
	void createCells(const Cell& begin, bool hor);
protected: 
	Cell* cells[5];
	int nb_cells, iter_cell = 0, lifes;
public: 
	Ship(const Cell & begin, int nb_cells, bool hor);
	Ship(int coord_max, int nb_cells);

	~Ship();
	Cell* getFirstCell();
	Cell* getNextCell();
};