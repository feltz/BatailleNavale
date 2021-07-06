#pragma once

#include <iostream>
#include "Battlegrid.h"
using namespace std;

class GridWithHeaders : public BattleGrid
{
protected: string getLineAsString(int pos);
public: GridWithHeaders(int sizeX = 10, int sizeY = 10, char fill = ' ');
	    ~GridWithHeaders();
		string getFirstLineAsString();
		string getNextLineAsString();
};

