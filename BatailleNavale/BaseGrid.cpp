#include "BaseGrid.h"

#include <iostream>
using namespace std;

BaseGrid::BaseGrid(int sizeX, int sizeY, char fill) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	table = new char* [sizeY];
	for (int i = 0; i < sizeY; i++) {
		table[i] = new char[sizeX];
		for (int j = 0; j < sizeX; j++)
			table[i][j] = fill;
	}
}

BaseGrid::~BaseGrid()
{
	for (int i = 0; i < sizeY; i++)
		delete table[i];
	delete table;
}

string BaseGrid::getLineAsString(int pos)
{
	return string(table[pos], sizeX);
}

string BaseGrid::getFirstLineAsString()
{
	iterPos = 0;
	return getLineAsString(iterPos);
}

string BaseGrid::getNextLineAsString() {
	iterPos++;
	if (iterPos < sizeY)
		return getLineAsString(iterPos);
	else
		return "";
}
