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
 
	Ship (const int x, const int y, int nb_cells, bool hor = true); // Constructeur avec positionnement fixe (pratique pour faire du debug)
	Ship (int coord_max, int nb_cells, string text = ""); // Constructeur avec saisie de l'utilisateur si un texte est renseigné, sinon au hasard
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
	Destroyer(int coord_max, bool random = false) : Ship(coord_max, 2, random ? "" : "Torpilleur") {};
};

class Submarine : public Ship
{
public:
	Submarine(const int x, const int y, bool hor = true) : Ship(x, y, 2, hor) {};
	Submarine(int coord_max, bool random = false) : Ship(coord_max, 2, random ? "" : "Sous-marin") {};
};

class Cruiser : public Ship
{
public:
	Cruiser (const int x, const int y, bool hor = true) : Ship(x, y, 3, hor) {};
	Cruiser (int coord_max, bool random = false) : Ship (coord_max, 3, random ? "" : "Contre - Torpilleur") {};
};

class Battleship : public Ship
{
public:
	Battleship (const int x, const int y, bool hor = true) : Ship(x, y, 4, hor) {};
	Battleship (int coord_max, bool random = false) : Ship (coord_max, 4, random ? "" : "Croiseur") {};
};

class Carrier : public Ship
{
public:
	Carrier (const int x, const int y, bool hor = true) : Ship(x, y, 5, hor) {};
	Carrier (int coord_max, bool random = false) : Ship (coord_max, 5, random ? "" : "Porte-avions") {};
};

