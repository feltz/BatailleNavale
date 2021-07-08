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
	BattleGrid(int sizeX = 10, int sizeY = 10, string player_name = "");
	~BattleGrid();
	void addShip(ShipType);
	Ship* isCellOccupied(const Cell&);
};

