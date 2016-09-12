#pragma once
#include "DLLExportOptions.h"
#include "Item.h"

enum  Effects
{
	NoEffect,
	BonusEffect,
	HalveBody,
	SubstractPoints
};

class DLL_SNAKE Surprise : Item
{
private:
	int time;
	Effects effect;//cut half of the snake's body / substract some points / etc

public:
	Surprise();
	Surprise(int points, char symbol, int time, Effects effect, Position coordinates);

	int getPoints();
	void setPoints(int points);

	char getSymbol();
	void setSymbol(char symbol);

	int getTime();
	void setTime(int time);

	Effects getEffect();
	void setEffect(Effects effect);

	Position getCoordinates();
	void setCoordinates(Position coordinates);

	bool getState();
	void setState(bool state);

	~Surprise();
};