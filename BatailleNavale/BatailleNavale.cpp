// BatailleNavale.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <exception>
#include "GridWithHeaders.h"
#include "BaseGrid.h"
#include "Ship.h"
using namespace std;

void display_grids(BaseGrid* g1, BaseGrid* g2, BaseGrid* g3) {
    string line, tmp;
    line = g1->getFirstLineAsString() + g2->getFirstLineAsString() + g3->getFirstLineAsString() + "\n";
    do {
        tmp = g1->getNextLineAsString() + g2->getNextLineAsString() + g3->getNextLineAsString();
        line += tmp + '\n';
    } while (tmp.length() > 0);
    cout << line;
}

int main()
{
    GridWithHeaders *player1 = new GridWithHeaders(10, 10, '~'), *player2 = new GridWithHeaders(10, 10, '~');
    BaseGrid *space = new BaseGrid(10, 12, ' ');
    display_grids(player1, space, player2);
    Ship* s;
    if (!player1->addShip(s = new Ship(10, 3))) {
        cout << "Emplacement déjà occupé !";
        delete s;
    }
    delete player1; 
    delete player2;
    delete space;
}


