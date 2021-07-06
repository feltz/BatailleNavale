#pragma once
#include "BaseGrid.h"
#include "Ship.h"

#define NB_SHIPS 6

class BattleGrid : public BaseGrid
{
private:
	int nb_ships;
protected: 
	Ship* ships[NB_SHIPS];
public: 
	BattleGrid(int sizeX = 10, int sizeY = 10, char fill = ' ');
	~BattleGrid();
	bool addShip(Ship*);
	Ship* isCellOccupied(const Cell&);
};

