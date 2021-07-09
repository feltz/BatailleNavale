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

void do_a_play(GridWithHeaders* player, BaseGrid** allGrids) {
    system("cls");
    display_grids(allGrids, 3);
    cout << player->getPlayerName() << " joue." << endl;
    Cell to_test = Cell(10);
}


int main()
{
    GridWithHeaders *player1 = new GridWithHeaders(10, 10, string ("Joueur 1")), *player2 = new GridWithHeaders(10, 10, string ( "Joueur 2"));
    BaseGrid *space = new BaseGrid(10, 14);
    BaseGrid* grids[3] = { player1, space, player2 };

    enter_ships(player1, grids);
    player1->setShipVisibility(false);
    enter_ships(player2, grids);
    player2->setShipVisibility(false);

    do {
        do_a_play(player1, grids);
    } while (true);

    delete player1; 
    delete player2;
    delete space;
}


