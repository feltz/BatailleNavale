#pragma once
class Cell
{ public:
	int x, y;
	Cell(int x, int y);
	friend bool operator==(const Cell&, const Cell&);
};


