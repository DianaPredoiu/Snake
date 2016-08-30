#pragma once
#include "Item.h"

class Food : Item
{

public:
	Food();
	Food(int points, char symbol);

	int getPoints();
	void setPoints(int points);

	char getSymbol();
	void setSymbol(char symbol);

	~Food();
};