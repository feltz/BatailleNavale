#include "BaseGrid.h"
#include "Cell.h"

#include <iostream>
using namespace std;

BaseGrid::BaseGrid(int sizeX, int sizeY, char fill) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	table = new Cell** [sizeY];
	for (int i = 0; i < sizeY; i++) {
		table[i] = new Cell*[sizeX];
		for (int j = 0; j < sizeX; j++)
			table[i][j] = new Cell(i, j, fill);
	}
}

BaseGrid::~BaseGrid()
{
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++)
			if (table[i][j])
				delete table[i][j];
		delete table[i];
	}
	delete table;
}

string BaseGrid::getLineAsString(int pos)
{
	string buffer;
	for (int j = 0; j < sizeX; j++)
		buffer += table[pos][j]->toChar();
	return buffer;
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
