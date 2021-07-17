#include "BattleGrid.h"
#include "Cell.h"

BattleGrid::BattleGrid(int sizeX, int sizeY, string player_name) : BaseGrid(sizeX, sizeY, '~'), m_player_name(player_name), m_nb_ships (0)
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


void BattleGrid::setComputer() {
    think = new BattleGrid(m_sizeX, m_sizeY, "None");
}

bool BattleGrid::isComputer() {
    return think != nullptr;
}

MiniTab<Ship*> BattleGrid::getDeadShips() const {
    Ship* ships[NB_SHIPS];
    int nb_ships = 0;
    for (int i = 0; i < NB_SHIPS; i++)
        if (m_ships[i]->isSunk())
            ships[nb_ships++] = m_ships[i];
    MiniTab<Ship*> res(nb_ships);
    for (int i = 0; i < nb_ships; i++)
        res.m_elems[i] = ships[i];
    return res;
}

CellShip* BattleGrid::getNewCellToPlayFromTouched() {
    CellShip* cell;
    for (int i = 0; i < m_sizeY; i++)
        for (int j = 0; j < m_sizeX; j++) {
            cell = (CellShip*)think->getCell(i, j);
            if (cell->getState() == CellState::touched) {
                Cell* cellToTest = nullptr;
                int shift = 1;
                while (!cellToTest) {
                    if (cell->getY() - shift > 0 && ((CellShip*)think->getCell(cell->getX(), cell->getY() - shift))->getState() == CellState::normal)
                        cellToTest = getCell(cell->getX(), cell->getY() - shift);
                    if (cell->getY() + shift < m_sizeX && ((CellShip*)think->getCell(cell->getX(), cell->getY() + shift))->getState() == CellState::normal)
                        cellToTest = getCell(cell->getX(), cell->getY() + shift);
                    if (cell->getX() - shift > 0 && ((CellShip*)think->getCell(cell->getX() - shift, cell->getY()))->getState() == CellState::normal)
                        cellToTest = getCell(cell->getX() - shift, cell->getY());
                    if (cell->getX() + shift < m_sizeY && ((CellShip*)think->getCell(cell->getX() + shift, cell->getY()))->getState() == CellState::normal)
                        cellToTest = getCell(cell->getX() + shift, cell->getY());
                }
                return (CellShip*) cellToTest;
            }
        }
    return nullptr;
}

CellShip* BattleGrid::getNewCellToPlay(const MiniTab<Ship*> & ships) {
    CellShip* cell;
    if (cell = getNewCellToPlayFromTouched())
      return new CellShip(cell->getX(), cell->getY());
    int max_cells = 2, proba_max = 0, proba_max_count = 1;
    if (ships.m_nb_elems == 0)
        max_cells = 5;
    else
        for (int i = 0; i < ships.m_nb_elems; i++)
            if (ships.m_elems[i]->get_nb_cells() > max_cells)
                max_cells = ships.m_elems[i]->get_nb_cells();
    for (int i = 0; i < m_sizeY; i++)
        for (int j = 0; j < m_sizeX; j++) {
            cell = (CellShip *) think->getCell(i, j);
            cell->m_proba = 0;
            if (cell->getState() == CellState::normal) {
                for (int k = 0; k < max_cells; k++) {
                    if (j - k > 0 && ((CellShip*)think->getCell(i, j - k))->getState() == CellState::normal)
                        cell->m_proba++;
                    if (j+ k < m_sizeX && ((CellShip*)think->getCell(i, j + k))->getState() == CellState::normal)
                        cell->m_proba++;
                    if (i - k > 0 && ((CellShip*)think->getCell(i-k, j))->getState() == CellState::normal)
                        cell->m_proba++;
                    if (i + k < m_sizeY && ((CellShip*)think->getCell(i + k, j))->getState() == CellState::normal)
                        cell->m_proba++;
                }
                if (cell->m_proba > proba_max) {
                    proba_max = cell->m_proba;
                    proba_max_count = 1;
                }
                else if (cell->m_proba == proba_max)
                    proba_max_count++;
            }
        }
    int proba_max_random = rand() % proba_max_count+1;
    int count = 1;
    for (int i = 0; i < m_sizeY; i++)
        for (int j = 0; j < m_sizeX; j++) {
            cell = (CellShip*)think->getCell(i, j);
            if (cell->m_proba == proba_max)
                if (count < proba_max_random)
                    count++;
                else {
                    cell->setState(CellState::tried);
                    return new CellShip(cell->getX(), cell->getY());
                }
        }
}

void BattleGrid::computerTouchedPlayer(CellShip* cell_touched) {
    CellShip* cell = (CellShip*)think->getCell(cell_touched->getX(), cell_touched->getY());
    cell->setState(CellState::touched);
}

BattleGrid::~BattleGrid()
{
    for (int i = 0; i < m_sizeY; i++) {
        for (int j = 0; j < m_sizeX; j++)
            if (((CellShip*)table[i][j])->getShip()) // Les cellules des bateaux sont detruites via la classe Ship
                table[i][j] = nullptr;
    }
    if (think)
        delete think;
}
