#pragma once

#include "Item.h"
#include "DLLExportOptions.h"

class DLL_SNAKE Food : Item
{

public:
	Food();
	Food(int points, char symbol, Position coordinates);

	int getPoints();
	void setPoints(int points);

	char getSymbol();
	void setSymbol(char symbol);

	Position getCoordinates();
	void setCoordinates(Position coordinates);

	bool getState();
	void setState(bool state);

	~Food();
};