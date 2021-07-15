#pragma once

#include <iostream>
#include "Cell.h"
using namespace std;

class BaseGrid
{
protected: Cell*** table; // on peut aussi utiliser la classe Vector<char> de la librairie std
	       int m_sizeX = 0, m_sizeY = 0, m_iterPos = -1, m_fill = ' ';
		   string getLineAsString(const int pos);
public: BaseGrid(const int sizeX = 10, const int sizeY = 10, const unsigned char fill = ' ');
	    ~BaseGrid();
		virtual string getFirstLineAsString(); // Initialise l'it�ration
		virtual string getNextLineAsString(); // retourne "" si on a d�pass� la derni�re ligne ou si on a oubli� getFirstLineAsString
		virtual Cell* getCell(const int x, const int y);
};

