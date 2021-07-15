#pragma once

#ifndef CELL_H
#define CELL_H

#include <string>
//#include "Ship.h"
using namespace std;

enum CellState { normal, tried, touched, dead };

class Ship;

class Cell
{
protected:
	int m_x, m_y, m_fill;
	bool m_visible = true;
public:
	Cell(int x = 0, int y = 0, char fill = ' ') : m_x(x), m_y(y), m_fill (fill) {};
	virtual unsigned char toChar() const;
	inline void changeFill(char fill) { m_fill = fill; }
	bool hasSameCoordinates (const Cell&) const;
	inline int getX() const { return m_x; }
	inline int getY() const { return m_y; }
	inline void setVisibility(bool visible) { m_visible = visible; }
};

class CellShip : public Cell {
private:
	CellState m_state = CellState::normal;
	int ask_for_coord(string coord_type, int max);
	Ship* m_ship = nullptr;
public:
	CellShip(int x, int y, Ship* ship = nullptr) : Cell(x, y, ship == nullptr ? '~' : '#'), m_ship(ship) {};
	CellShip(int coord_max);
	unsigned char toChar() const;
	void touched();
	void tried();
	void setState(const CellState&);
	Ship* getShip();
};

#endif

