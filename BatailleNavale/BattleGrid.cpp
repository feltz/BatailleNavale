#include "BattleGrid.h"

bool BattleGrid::addShip(Ship* ship)
{
    bool collision = false;
    Cell* cell = ship->getFirstCell();
    do {
        collision = collision || this->isCellOccupied(*cell); 
    } while ((cell = ship->getNextCell()) && !collision);
    if (!collision)
        ships[nb_ships++] = ship;
    return !collision;
}

BattleGrid::BattleGrid(int sizeX, int sizeY, char fill) : BaseGrid(sizeX, sizeY, fill)
{
    nb_ships = 0;
    for (int i = 0; i < NB_SHIPS; i++)
        ships[i] = NULL;
}

Ship* BattleGrid::isCellOccupied(const Cell & celltoTest)
{
    for (int i = 0; i < nb_ships; i++) {
        Cell* cell = ships[i]->getFirstCell();
        do {
            if (celltoTest == *cell)
                return ships[i];
        } while (cell = ships[i]->getNextCell());
    }
    return NULL;
}

BattleGrid::~BattleGrid()
{
    for (int i = 0; i < nb_ships; i++)
        delete ships[i];
}
