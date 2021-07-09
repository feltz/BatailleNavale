#include "BattleGrid.h"

void BattleGrid::addShip (ShipType type)
{
    Ship* ship = nullptr;
    do {
        bool collision = false;
        switch (type) {
            case ShipType::destroyer: ship = new Destroyer(sizeX); break; 
            case ShipType::submarine: ship = new Submarine(sizeX); break;
            case ShipType::cruiser: ship = new Cruiser(sizeX); break;
            case ShipType::battleship: ship = new Battleship(sizeX); break;
            case ShipType::carrier: ship = new Carrier(sizeX); break;
        }

        Cell* cell = ship->getFirstCell();
        do {
            collision = collision || this->isCellOccupied(*cell);
        } while ((cell = ship->getNextCell()) && !collision);
        if (collision) {
            cout << "Emplacement déjà occupé ! Refaites votre saisie." << endl;
            delete ship;
            ship = nullptr;
        }
    } while (!ship);
    m_ships[m_nb_ships++] = ship;
    Cell* cell = ship->getFirstCell();
    do {
        table[cell->getX()][cell->getY()] = cell;
    } while ((cell = ship->getNextCell()));
}

BattleGrid::BattleGrid(int sizeX, int sizeY, string player_name) : BaseGrid(sizeX, sizeY, '~'), m_player_name (player_name), m_nb_ships (0)
{
    for (int i = 0; i < NB_SHIPS; i++)
        m_ships[i] = nullptr;
}

Ship* BattleGrid::isCellOccupied(const Cell & celltoTest)
{
    for (int i = 0; i < m_nb_ships; i++) {
        Cell* cell = m_ships[i]->getFirstCell();
        do {
            if (celltoTest.hasSameCoordinates (*cell))
                return m_ships[i];
        } while (cell = m_ships[i]->getNextCell());
    }
    return nullptr;
}

void BattleGrid::setShipVisibility(bool visible) {
    for (int i = 0; i < m_nb_ships; i++) {
        Cell* cell = m_ships[i]->getFirstCell();
        do {
            cell->setVisibility(visible);
        } while (cell = m_ships[i]->getNextCell());
    }
}

BattleGrid::~BattleGrid()
{
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++)
            if (dynamic_cast <CellShip*> (table[i][j]))
                table[i][j] = nullptr;
    }
}
