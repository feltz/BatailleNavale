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
	for (int j = 0; j < m_sizeX; j++)
		buffer += char(65 + j);
	return buffer;
}

string GridWithHeaders::getPlayerLine()
{
	return "   " + m_player_name;
}

string GridWithHeaders::getFirstLineAsString() {
	m_iterPos = -3;
	return getPlayerLine();
}

string GridWithHeaders::getNextLineAsString() {
	m_iterPos++;
	if (m_iterPos == -1)
		return getHeaderLine();
	else if (m_iterPos >= 0 && m_iterPos < m_sizeY)
		return getLineAsString(m_iterPos);
	else
		return string ("");
}