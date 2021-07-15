#include "BaseGrid.h"
#include "Cell.h"

#include <iostream>
using namespace std;

BaseGrid::BaseGrid(const int sizeX, const int sizeY, const unsigned char fill) : m_sizeX(sizeY), m_sizeY (sizeY), m_fill (fill) {
	table = new Cell** [m_sizeY];
	for (int i = 0; i < m_sizeY; i++) {
		table[i] = new Cell*[m_sizeX];
		for (int j = 0; j < m_sizeX; j++)
			table[i][j] = nullptr;
	}
}

BaseGrid::~BaseGrid()
{
	for (int i = 0; i < m_sizeY; i++) {
		for (int j = 0; j < m_sizeX; j++)
			if (table[i][j])
				delete table[i][j];
		delete table[i];
	}
	delete table;
}

string BaseGrid::getLineAsString(int pos)
{
	string buffer;
	for (int j = 0; j < m_sizeX; j++)
		buffer += getCell (pos, j)->toChar();
	return buffer;
}

string BaseGrid::getFirstLineAsString()
{
	m_iterPos = 0;
	return getLineAsString(m_iterPos);
}

string BaseGrid::getNextLineAsString() {
	m_iterPos++;
	if (m_iterPos < m_sizeY)
		return getLineAsString(m_iterPos);
	else
		return "";
}

Cell* BaseGrid::getCell(const int x, const int y)
{
	if (table[x][y])
		return table[x][y];
	else
		return table[x][y] = new Cell(x, y, m_fill);
}