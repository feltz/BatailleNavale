#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool operator==(const Cell& c1, const Cell& c2)
{
	return c1.x == c2.x && c1.y == c2.y;
}
