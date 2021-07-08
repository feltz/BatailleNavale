#pragma once

#include <iostream>
#include "Cell.h"
using namespace std;

class BaseGrid
{
protected: Cell*** table; // on peut aussi utiliser la classe Vector<char> de la librairie std
	       int sizeX = 0, sizeY = 0, iterPos = -1;
		   string getLineAsString(int pos);
public: BaseGrid(int sizeX = 10, int sizeY = 10, char fill = ' ');
	    ~BaseGrid();
		virtual string getFirstLineAsString(); // Initialise l'itération
		virtual string getNextLineAsString(); // retourne "" si on a dépassé la dernière ligne ou si on a oublié getFirstLineAsString
};

