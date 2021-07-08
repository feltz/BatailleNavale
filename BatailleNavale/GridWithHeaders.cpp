#include "GridWithHeaders.h"
#include <iostream>
using namespace std;

GridWithHeaders::GridWithHeaders(int sizeX, int sizeY, string player_name) : BattleGrid (sizeX, sizeY, player_name)
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

string GridWithHeaders::getHeaderLine()
{
	string buffer = "  ";
	for (int j = 0; j < sizeX; j++)
		buffer += char(65 + j);
	return buffer;
}

string GridWithHeaders::getPlayerLine()
{
	return "   " + m_player_name;
}

string GridWithHeaders::getFirstLineAsString() {
	iterPos = -3;
	return getPlayerLine();
}

string GridWithHeaders::getNextLineAsString() {
	iterPos++;
	if (iterPos == -1)
		return getHeaderLine();
	else if (iterPos >= 0 && iterPos < sizeY)
		return getLineAsString(iterPos);
	else
		return string ("");
}