#pragma once

#include <iostream>
#include "Battlegrid.h"
using namespace std;

class GridWithHeaders : public BattleGrid
{
protected: 
	string getLineAsString(int pos);
	string getPlayerLine();
	string getHeaderLine();
public: 
	GridWithHeaders(int sizeX = 10, int sizeY = 10, string player_name = "");
	~GridWithHeaders();
	string getFirstLineAsString();
	string getNextLineAsString();
};

