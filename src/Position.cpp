#include "Position.h"

#pragma region Constructors
Position::Position() 
{

}

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}
#pragma endregion

#pragma region Get/Set
int Position::getX() const
{
	return this->x;
}

void Position::setX(int x)
{
	this->x = x;
}

int Position::getY() const
{
	return this->y;
}

void Position::setY(int y)
{
	this->y = y;
}
#pragma endregion 