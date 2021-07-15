#include "BattleGrid.h"

BattleGrid::BattleGrid(int sizeX, int sizeY, string player_name) : BaseGrid(sizeX, sizeY, '~'), m_player_name(player_name), m_nb_ships(0)
{
    for (int i = 0; i < NB_SHIPS; i++)
        m_ships[i] = nullptr;
}

void BattleGrid::insertShip(Ship*ship) {
    m_ships[m_nb_ships++] = ship;
    Cell* cell = ship->getFirstCell();
    do {
        int x = cell->getX(), y = cell->getY();
        if (table[x][y])
            delete table[x][y];
        table[x][y] = cell;
    } while ((cell = ship->getNextCell()));
}

void BattleGrid::addShip (ShipType type)
{
    Ship* ship = nullptr;
    do {
        bool collision = false;
        switch (type) {
            case ShipType::destroyer: ship = new Destroyer(m_sizeX); break; 
            case ShipType::submarine: ship = new Submarine(m_sizeX); break;
            case ShipType::cruiser: ship = new Cruiser(m_sizeX); break;
            case ShipType::battleship: ship = new Battleship(m_sizeX); break;
            case ShipType::carrier: ship = new Carrier(m_sizeX); break;
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
    insertShip(ship);
}

CellShip* BattleGrid::isCellOccupied(const Cell & celltoTest)
{
    for (int i = 0; i < m_nb_ships; i++) {
        CellShip* cell = m_ships[i]->getFirstCell();
        do {
            if (celltoTest.hasSameCoordinates (*cell))
                return cell;
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

Cell* BattleGrid::getCell(const int x, const int y)
{
    if (table[x][y])
        return table[x][y];
    else
        return table[x][y] = new CellShip(x, y);
}

BattleGrid::~BattleGrid()
{
    for (int i = 0; i < m_sizeY; i++) {
        for (int j = 0; j < m_sizeX; j++)
            if (((CellShip*)table[i][j])->getShip()) // Les cellules des bateaux sont detruites via la classe Ship
                table[i][j] = nullptr;
    }
}
