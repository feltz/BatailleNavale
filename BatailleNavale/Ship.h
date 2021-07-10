#pragma once

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
	string m_text = "";
 
	Ship(const int x, const int y, int nb_cells, bool hor = true);
	Ship(int coord_max, int nb_cells, string text);
public:
	~Ship();
	CellShip* getFirstCell();
	CellShip* getNextCell();
	int get_nb_cells();
	string get_text();
	void touched(CellShip*);
	bool isSunk();
};

class Destroyer : public Ship
{
public:
	Destroyer(const int x, const int y, bool hor = true) : Ship(x, y, 2, hor) {};
	Destroyer(int coord_max) : Ship(coord_max, 2, "Torpilleur") {};
};

class Submarine : public Ship
{
public:
	Submarine(const int x, const int y, bool hor = true) : Ship(x, y, 2, hor) {};
	Submarine(int coord_max) : Ship(coord_max, 2, "Sous-marin") {};
};

class Cruiser : public Ship
{
public:
	Cruiser (const int x, const int y, bool hor = true) : Ship(x, y, 3, hor) {};
	Cruiser (int coord_max) : Ship (coord_max, 3, "Contre - Torpilleur") {};
};

class Battleship : public Ship
{
public:
	Battleship (const int x, const int y, bool hor = true) : Ship(x, y, 4, hor) {};
	Battleship (int coord_max) : Ship (coord_max, 4, "Croiseur") {};
};

class Carrier : public Ship
{
public:
	Carrier (const int x, const int y, bool hor = true) : Ship(x, y, 5, hor) {};
	Carrier (int coord_max) : Ship (coord_max, 5, "Porte-avions") {};
};

