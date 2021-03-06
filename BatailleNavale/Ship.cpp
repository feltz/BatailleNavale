#include "Ship.h"
#include "Cell.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Ship::Ship(const int x, const int y, int nb_cells, bool hor) : m_nb_cells(nb_cells), m_lifes(nb_cells)
{
	createCells(Cell (x, y), hor);
}

Ship::Ship(int coord_max, int nb_cells, string text) : m_nb_cells(nb_cells), m_lifes(nb_cells), m_text (text)
{
	if (text.length() > 0) {
		cout << "Saisie du " + m_text << endl;
		CellShip begin = CellShip(coord_max);
		createCells(begin, ask_for_direction());
	}
	else {
		int max = coord_max - nb_cells;
		createCells(Cell(rand() % max, rand() % max), rand() % 2 == 1);
	}
}

int Ship::get_nb_cells() {
	return m_nb_cells;
}

string Ship::get_text() {
	return m_text;
}

void Ship::createCells(const Cell& begin, bool hor) {
	if (hor)
		for (int i = 0; i < m_nb_cells; i++)
			m_cells[i] = new CellShip(begin.getX() + i, begin.getY(), this);
	else
		for (int i = 0; i < m_nb_cells; i++)
			m_cells[i] = new CellShip(begin.getX(), begin.getY() + i, this);
}

bool Ship::ask_for_direction() {
	string input;
	int res = -1;
	while (res == -1) {
		cout << endl << "Direction - (D)roite ou (B)as: ";
		cin >> input;
		input[0] = toupper(input[0]);
		if (input == "D" || input == "Droite")
			res = 0;
		else if (input == "Bas" || input == "B")
			res = 1;
		else
			cout << "Mauvaise direction" << endl;
	}
	return res == 1;
}

void Ship::touched(CellShip* cell_touched) {
	m_lifes--;
	cell_touched->setState(CellState::touched);
	if (m_lifes == 0)
		for (int i = 0; i < m_nb_cells; i++)
			m_cells[i]->setState(CellState::dead);

}

bool Ship::isSunk() {
	return m_lifes == 0;
}

Ship::~Ship()
{
	for (int i = 0; i < m_nb_cells; i++)
		delete m_cells[i];
}

CellShip* Ship::getFirstCell()
{
	m_iter_cell = 0;
	return m_cells[m_iter_cell];
}

CellShip* Ship::getNextCell()
{
	m_iter_cell++;
	if (m_iter_cell < m_nb_cells)
		return m_cells[m_iter_cell];
	else
		return nullptr;
}