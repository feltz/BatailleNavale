#include "GridWithHeaders.h"
#include <iostream>
using namespace std;

GridWithHeaders::GridWithHeaders(int sizeX, int sizeY, char fill) : BattleGrid (sizeX, sizeY, fill)
{
}

GridWithHeaders::~GridWithHeaders()
{
}

string GridWithHeaders::getLineAsString(int pos)
{
	char y_header[3];
	sprintf_s(y_header, "%2d", pos+1);
	return string (y_header) + BaseGrid::getLineAsString(pos);
}
string GridWithHeaders::getFirstLineAsString()
{
	iterPos = -1;
	string buffer = "  ";
	for (int j = 0; j < sizeX; j++)
		buffer += char(65 + j);
	return buffer;
}

string GridWithHeaders::getNextLineAsString() {
	iterPos++;
	if (iterPos < sizeY)
		return getLineAsString(iterPos);
	else
		return "";
}