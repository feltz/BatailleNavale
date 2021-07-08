#pragma once

#ifndef SHIP_H
#define SHIP_H

#include <string>

class Cell;
class CellShip;

using namespace std;

enum ShipType { destroyer, submarine, cruiser, battleship, carrier, last };

class Ship
{
private:
	bool ask_for_direction();
	void createCells(const Cell & begin, bool hor);
protected: 
	CellShip* m_cells[5];
	int m_nb_cells, m_iter_cell = 0, m_lifes;
	string m_text;
 
	Ship(const Cell & begin, int nb_cells, bool hor, string text);
	Ship(int coord_max, int nb_cells, string text);
public:
	~Ship();
	Cell* getFirstCell();
	Cell* getNextCell();
	int get_nb_cells();
	string get_text();
};

class Destroyer : public Ship
{
public:
	Destroyer(const Cell& begin, bool hor) : Ship(begin, 2, hor, "Torpilleur") {};
	Destroyer(int coord_max) : Ship(coord_max, 2, "Torpilleur") {};
};


class Submarine : public Ship
{
public:
	Submarine (const Cell& begin, bool hor) : Ship (begin, 3, hor, "Sous-marin") {};
	Submarine (int coord_max) : Ship(coord_max, 3, "Sous-marin") {};
};

class Cruiser : public Ship
{
public:
	Cruiser (const Cell& begin, bool hor) : Ship(begin, 3, hor, "Contre - Torpilleur") {};
	Cruiser (int coord_max) : Ship(coord_max, 3, "Contre - Torpilleur") {};
};

class Battleship : public Ship
{
public:
	Battleship (const Cell& begin, bool hor) : Ship(begin, 4, hor, "Croiseur") {};
	Battleship (int coord_max) : Ship(coord_max, 4, "Croiseur") {};
};

class Carrier : public Ship
{
public:
	Carrier (const Cell& begin, bool hor) : Ship(begin, 5, hor, "Porte-avions") {};
	Carrier (int coord_max) : Ship(coord_max, 5, "Porte-avions") {};
};

#endif