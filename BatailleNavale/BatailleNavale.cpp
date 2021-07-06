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

bool ask_for_direction() {
    string input;
    int res = -1;
    while (res == -1) {
        cout << "Direction - (D)roite ou (B)as: ";
        cin >> input;
        if (input == "G" || input == "Gauche")
            res = 1;
        else if (input == "Bas" || input == "B")
            res = 0;
        else
            cout << "Mauvaise direction" << endl;
    }
    return res == 1;
}

int ask_for_coord(string coord_type, int max) {
    string input;
    int result = 0;
    while (!result) {
        cout << coord_type + " :";
        cin >> input;
        try {
            result = stoi(input);
        }
        catch (...) {
            cout << "Saisie Incorrecte." << endl;
        }
        if (result > max) {
            cout << "Coordonnée au-delà des limites." << endl;	
            result = 0;
        }
    }
    return result;
}

int main()
{
    GridWithHeaders *player1 = new GridWithHeaders(10, 10, '~'), *player2 = new GridWithHeaders(10, 10, '~');
    BaseGrid *space = new BaseGrid(10, 12, ' ');
    display_grids(player1, space, player2);
    Ship *s = new Ship (Cell (ask_for_coord("Ligne", 10), ask_for_coord("Colonne", 10)), 3, ask_for_direction());
    if (!player1->addShip(s)) {
        cout << "nok";
        delete s;
    }
    delete player1; 
    delete player2;
    delete space;
}


