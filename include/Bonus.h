#pragma once
#include "Item.h"
#include "DLLExportOptions.h"
class DLL_SNAKE Bonus : Item
{
private:
	int time;

public:
	Bonus();
	Bonus(int points, char symbol, int time, Position coordinates);

	int getPoints();
	void setPoints(int points);

	char getSymbol();
	void setSymbol(char symbol);

	int getTime();
	void setTime(int time);

	Position getCoordinates();
	void setCoordinates(Position coordinates);

	bool getState();
	void setState(bool state);

	~Bonus();

};