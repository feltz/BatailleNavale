// BatailleNavale.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <exception>
#include <cstdlib>
#include "GridWithHeaders.h"
#include "BaseGrid.h"
#include "Ship.h"
using namespace std;

int ask_for_menu() {
    string input;
    int result = 0;
    system("cls");
    cout << "1. Jeu contre l'ordinateur avec placement manuel des bateaux" << endl;
    cout << "2. Jeu contre l'ordinateur avec placement au hasard des bateaux du joueur" << endl;
    cout << "3. 2 joueurs avec placement mamuel des bateaux" << endl;
    cout << "4. 2 joueurs avec hasard au hasard des bateaux des joueurs" << endl << endl;
    cout << "     Votre choix : ";
    while (!result) {
        cin >> input;
        try {
            result = stoi(input);
        }
        catch (...) {}
        if (result < 1 || result > 4) {
            result = 0;
            cout << "Veuillez saisir un chiffre entre 1 et 4" << endl;
            cout << "     Votre choix : ";
        }
        else
            return result;
    }
}

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

void try_a_play(GridWithHeaders* player, GridWithHeaders* anti_player, BaseGrid** allGrids) {
    system("cls");
    display_grids(allGrids, 3);
    cout << player->getPlayerName() << " joue." << endl;
    CellShip* touched, * cellToTest;
    if (player->isComputer())
        cellToTest = player->getNewCellToPlay(anti_player->getDeadShips());
    else
        cellToTest = new CellShip(10);
    if (touched = anti_player->isCellOccupied(*cellToTest)) {
        touched->touched();
        if (player->isComputer())
            player->computerTouchedPlayer(touched);
    }
    else
        ((CellShip*) (anti_player->getCell(cellToTest->getX(), cellToTest->getY())))->tried();
    delete cellToTest;
}

void ships_random(BattleGrid* grid) {
    grid->insertShip(new Destroyer(10, true));  
    grid->insertShip(new Submarine(10, true));
    grid->insertShip(new Cruiser(10, true)); 
    grid->insertShip(new Cruiser(10, true));
    grid->insertShip(new Battleship(10, true)); 
    grid->insertShip(new Carrier(10, true));
}

int main()
{
    srand((unsigned int)time(0)); // On initialise les nombres aléatoires
    GridWithHeaders *player1 = new GridWithHeaders(10, 10, string ("Joueur 1")), *player2 = new GridWithHeaders(10, 10, string ( "Joueur 2"));
    BaseGrid *space = new BaseGrid(10, 14);
    BaseGrid* grids[3] = { player1, space, player2 };
    int menu = ask_for_menu();

    if (menu == 3) {
        enter_ships(player1, grids);
        player1->setShipVisibility(false);
        enter_ships(player2, grids);
    }
    else if (menu == 4) {
        ships_random(player1);
        display_grids(grids, 3);
        system("pause");
        system("cls");
        player1->setShipVisibility(false);
        ships_random(player2);
        display_grids(grids, 3);
        system("pause");
    }
    else if (menu == 1 || menu == 2) { 
        ships_random(player2);
        player2->setComputer();
        if (menu == 1)
            enter_ships(player1, grids);
        else {
            ships_random(player1);
            player2->setShipVisibility(false);
            display_grids(grids, 3);
            system("pause");
        }
    }
    player2->setShipVisibility(false);

    do {
        try_a_play(player1, player2, grids);
        try_a_play(player2, player1, grids);
    } while (true);

    delete player1; 
    delete player2;
    delete space;
}


