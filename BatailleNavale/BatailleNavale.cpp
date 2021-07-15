// BatailleNavale.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <exception>
#include "GridWithHeaders.h"
#include "BaseGrid.h"
#include "Ship.h"
using namespace std;

void display_grids(BaseGrid** grids, int nb_grids) {
    string line;
    int len;
    for (int i = 0; i < nb_grids; i++)
        line += grids[i]->getFirstLineAsString();
    line += '\n';
    do {
        len = line.length();
        for (int i = 0; i < nb_grids; i++) 
            line += grids[i]->getNextLineAsString();
        line += '\n';
    } while (line.length() - len > 1);
    cout << line;
}

void enter_ships(GridWithHeaders *gridToEnter, BaseGrid **allGrids) {
    for (int type = ShipType::destroyer; type != ShipType::last; type++) {
        system("cls");
        display_grids(allGrids, 3);
        cout << "Saisie des bateaux de " << gridToEnter->getPlayerName() << endl << endl;
        gridToEnter->addShip(static_cast<ShipType>(type));
    }
}

void try_a_play(GridWithHeaders* player, BaseGrid** allGrids) {
    system("cls");
    display_grids(allGrids, 3);
    cout << player->getPlayerName() << " joue." << endl;
    CellShip* touched;
    CellShip cellToTest(10);
    if (touched = player->isCellOccupied(cellToTest))
        touched->touched();
    else
        ((CellShip*) (player->getCell(cellToTest.getX(), cellToTest.getY())))->tried();
}


int main()
{
    const int DEBUG = true;
    GridWithHeaders *player1 = new GridWithHeaders(10, 10, string ("Joueur 1")), *player2 = new GridWithHeaders(10, 10, string ( "Joueur 2"));
    BaseGrid *space = new BaseGrid(10, 14);
    BaseGrid* grids[3] = { player1, space, player2 };

    if (!DEBUG) {
        enter_ships(player1, grids);
        player1->setShipVisibility(false);
        enter_ships(player2, grids);
    }
    else {
        player1->insertShip(new Destroyer(1, 1));  player1->insertShip(new Submarine(2, 3));
        player1->insertShip(new Cruiser(3, 4));  player1->insertShip(new Battleship(5, 5));  player1->insertShip (new Carrier(4, 6));
        player1->setShipVisibility(false);
        player2->insertShip(new Destroyer(1, 1));  player2->insertShip(new Submarine(2, 3));
        player2->insertShip(new Cruiser(3, 4)); player2->insertShip(new Battleship(5, 5)); player2->insertShip(new Carrier(4, 6));
    }
    player2->setShipVisibility(false);


    do {
        try_a_play(player1, grids);
    } while (true);

    delete player1; 
    delete player2;
    delete space;
}


