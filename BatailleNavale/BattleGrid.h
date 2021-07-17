#pragma once
#include "BaseGrid.h"
#include "Ship.h"
#include "Cell.h"
#include "MiniTab.h"

#define NB_SHIPS 6

class BattleGrid : public BaseGrid
{
private:
	int m_nb_ships;
	CellShip* getNewCellToPlayFromTouched();
protected: 
	Ship* m_ships[NB_SHIPS];
	string m_player_name;
	BattleGrid* think = nullptr;
public: 
	BattleGrid(const int sizeX = 10, const int sizeY = 10, const string player_name = "");
	~BattleGrid();
	void addShip(ShipType);
	void insertShip(Ship*);
	CellShip* isCellOccupied(const Cell&);
	void setShipVisibility(bool);
	void setComputer();
	bool isComputer();
	CellShip* getNewCellToPlay(const MiniTab<Ship*>& ships); // Prochain coup de l'ordinateur
	void computerTouchedPlayer(CellShip*);
	MiniTab<Ship*> getDeadShips() const;
	inline string getPlayerName () const { return m_player_name; }
	Cell* getCell(const int x, const int y);
};

