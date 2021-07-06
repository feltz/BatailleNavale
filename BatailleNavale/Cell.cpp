#include "Cell.h"
#include <string>
#include <iostream>
using namespace std;

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;
}

Cell::Cell(int coord_max)
{
	x = ask_for_coord("Ligne", 10);
	y = ask_for_coord("Colonne", 10);
}

bool operator==(const Cell& c1, const Cell& c2)
{
	return c1.x == c2.x && c1.y == c2.y;
}

int Cell::ask_for_coord(string coord_type, int max) {
	string input;
	int result = 0;
	while (!result) {
		cout << coord_type + " : ";
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
