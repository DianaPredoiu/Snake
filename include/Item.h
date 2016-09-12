#pragma once
#include "Position.h"
#include "Texture.h"
#include "DLLExportOptions.h"
/**
"Item" class is the base class for Food,Bonus and Surprise classes.
They all have in common a specific number of victory points and different symbols
*/
class DLL_SNAKE Item
{

protected:
	int points;
	char symbol;
	Position coordinates; //items coordinates
	bool state; //item state 

public:

	virtual int getPoints() = 0;
	virtual void setPoints(int points) = 0;

	virtual char getSymbol() = 0;
	virtual void setSymbol(char symbol) = 0;

	virtual Position getCoordinates() = 0;
	virtual void setCoordinates(Position coordinates) = 0;

	virtual bool getState() = 0;
	virtual void setState(bool state) = 0;

	//Texture texture;
};