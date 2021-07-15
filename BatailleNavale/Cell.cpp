#include "Cell.h"
#include "Ship.h"
#include <string>
#include <iostream>
using namespace std;

bool Cell::hasSameCoordinates(const Cell&cell) const {
	return m_x == cell.m_x && m_y == cell.m_y;
}

CellShip::CellShip(int coord_max)
{
	m_x = ask_for_coord("Ligne", 10) - 1;
	m_y = ask_for_coord("Colonne", 10) - 1;
	m_state = CellState::normal;
	m_fill = '~';
}

unsigned char Cell::toChar() const {
	return m_fill;
}

int CellShip::ask_for_coord(string coord_type, int max) {
	string input;
	int result = 0;
	while (!result) {
		cout << coord_type + " : ";
		cin >> input;
		try {
			result = stoi(input);
		}
		catch (...) {
			int ch = int(input[0]);
			if (ch >= 97 && ch <= 107)
				result = ch - 96;
			else if (ch >= 65 && ch <= 75)
				result = ch - 64;
			else
				cout << "Saisie Incorrecte." << endl;
		}
		if (result > max) {
			cout << "Coordonnée au-delà des limites." << endl;
			result = 0;
		}
	}
	return result;
}

unsigned char CellShip::toChar() const {
	switch (m_state) {
		case CellState::tried: return '.';
		case CellState::normal: if (m_visible) return m_fill; else return '~';
		case CellState::touched: return 'x';
		case CellState::dead: return 254; // black square
	}
}

void CellShip::setState(const CellState & state) {
	m_state = state;
}

Ship* CellShip::getShip()
{
	return m_ship;
}

void CellShip::touched()
{
	if (m_state == CellState::normal)
		m_ship->touched(this);
}

void CellShip::tried()
{
	setState(CellState::tried);
}