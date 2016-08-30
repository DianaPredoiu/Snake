#pragma once
#include "Item.h"

class Bonus : Item
{
private:
	int time;

public:
	Bonus();
	Bonus(int points, char symbol, int time);

	int getPoints();
	void setPoints(int points);

	char getSymbol();
	void setSymbol(char symbol);

	int getTime();
	void setTime(int time);

	~Bonus();

};