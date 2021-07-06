#include "Ship.h"
#include <iostream>
using namespace std;

Ship::Ship(const Cell& begin, int nb_cells, bool hor)
{
	this->nb_cells = nb_cells;
	this->lifes = nb_cells;
	createCells(begin, hor);
}

Ship::Ship(int coord_max, int nb_cells)
{
	this->nb_cells = nb_cells;
	this->lifes = nb_cells;
	Cell begin = Cell(coord_max);
	createCells(begin, ask_for_direction());
}

void Ship::createCells(const Cell& begin, bool hor) {
	if (hor)
		for (int i = 0; i < nb_cells; i++)
			cells[i] = new Cell(begin.x + i, begin.y);
	else
		for (int i = 0; i < nb_cells; i++)
			cells[i] = new Cell(begin.x, begin.y + i);
}

bool Ship::ask_for_direction() {
	string input;
	int res = -1;
	while (res == -1) {
		cout << endl << "Direction - (D)roite ou (B)as: ";
		cin >> input;
		if (input == "G" || input == "Gauche" || input == "g")
			res = 1;
		else if (input == "Bas" || input == "B" || input == "b")
			res = 0;
		else
			cout << "Mauvaise direction" << endl;
	}
	return res == 1;
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


