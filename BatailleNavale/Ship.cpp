#include "Ship.h"
using namespace std;

Ship::Ship(const Cell& begin, int nb_cells, bool hor)
{
	this->nb_cells = nb_cells;
	if (hor)
		for (int i = 0; i < nb_cells; i++)
			cells[i] = new Cell (begin.x + i, begin.y);
	else
		for (int i = 0; i < nb_cells; i++)
			cells[i] = new Cell (begin.x, begin.y + i);
	this->lifes = nb_cells;
	iter_cell = 0;
}

Ship::~Ship()
{
	for (int i = 0; i < nb_cells; i++)
		delete cells[i];
}

Cell* Ship::getFirstCell()
{
	iter_cell = 0;
	return cells[iter_cell];
}

Cell* Ship::getNextCell()
{
	iter_cell++;
	if (iter_cell < nb_cells)
		return cells[iter_cell];
	else
		return nullptr;
}

