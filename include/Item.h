#pragma once
/**
"Item" class is the base class for Food,Bonus and Surprise classes.
They all have in common a specific number of victory points and different symbols 
*/
class Item
{

protected:
	int points;
	char symbol;

public:

	virtual int getPoints() = 0;
	virtual void setPoints(int points) = 0;

	virtual char getSymbol() = 0;
	virtual void setSymbol(char symbol) = 0;

};