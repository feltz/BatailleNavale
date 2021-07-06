#pragma once

#include <string>
using namespace std;

class Cell
{ 
private:
	int ask_for_coord(string coord_type, int max);
public:
	int x, y;
	Cell(int x, int y);
	Cell(int coord_max);
	friend bool operator==(const Cell&, const Cell&);
};


