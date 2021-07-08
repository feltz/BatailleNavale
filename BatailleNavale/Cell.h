#pragma once

#ifndef CELL_H
#define CELL_H

#include <string>
//#include "Ship.h"
using namespace std;

enum CellState { normal, touched, dead };

class Ship;

class Cell
{
protected:
	int m_x, m_y, m_fill;
public:
	Cell(int x = 0, int y = 0, char fill = ' ') : m_x(x), m_y(y), m_fill (fill) {};
	inline virtual char toChar() const { return m_fill; }
	inline void changeFill(char fill) { m_fill = fill; }
	bool hasSameCoordinates (const Cell&) const;
	inline int getX() const { return m_x; }
	inline int getY() const { return m_y; }
};

class CellShip : public Cell {
private:
	CellState m_state = CellState::normal;
	int ask_for_coord(string coord_type, int max);
	Ship* m_ship = nullptr;
public:
	CellShip(int x, int y, Ship* ship = nullptr) : Cell(x, y, '~') , m_ship(ship) {};
	CellShip(int coord_max);
	char toChar() const;
};

#endif

