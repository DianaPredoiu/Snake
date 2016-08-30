#pragma once
#include "Item.h"

enum Effects
{
	NoEffect,
	HalveBody,
	SubstractPoints
};

class Surprise : Item
{
private:
	int time;
	Effects effect;//cut half of the snake's body / substract some points / etc

public:
	Surprise();
	Surprise(int points, char symbol, int time, Effects effect);

	int getPoints();
	void setPoints(int points);

	char getSymbol();
	void setSymbol(char symbol);

	int getTime();
	void setTime(int time);

	Effects getEffect();
	void setEffect(Effects effect);

	~Surprise();
};