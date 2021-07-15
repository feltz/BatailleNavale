#pragma once
#include "BaseGrid.h"
#include "Ship.h"
#include "Cell.h"

#define NB_SHIPS 6

class BattleGrid : public BaseGrid
{
private:
	int m_nb_ships;
protected: 
	Ship* m_ships[NB_SHIPS];
	string m_player_name;
public: 
	BattleGrid(const int sizeX = 10, const int sizeY = 10, const string player_name = "");
	~BattleGrid();
	void addShip(ShipType);
	void insertShip(Ship*);
	CellShip* isCellOccupied(const Cell&);
	void setShipVisibility(bool);
	inline string getPlayerName () const { return m_player_name; }
	Cell* getCell(const int x, const int y);
};

