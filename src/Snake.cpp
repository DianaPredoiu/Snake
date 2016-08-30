#include "Snake.h"

Snake::Snake() 
{
	this->coordinates.push_back(new Position(3, 1)); //head position
	this->coordinates.push_back(new Position(2,1)); //body position
	this->coordinates.push_back(new Position(1,1)); //tail position
	this->headSymbol = 'H';
	this->bodySymbol = 'B';
	this->tailSymbol = 'T';
}

Snake::Snake(int i, int j)
{
	this->coordinates.push_back(new Position(j, i)); //head position
	this->coordinates.push_back(new Position(j-1, i)); //body position
	this->coordinates.push_back(new Position(j-2, i)); //tail position
	this->headSymbol = 'H';
	this->bodySymbol = 'B';
	this->tailSymbol = 'T';
}

std::vector<Position*> Snake::getCoordinates() const
{
	return this->coordinates;
}


char Snake::getHeadSymbol()
{
	return this->headSymbol;
}

char Snake::getBodySymbol()
{
	return this->bodySymbol;
}

char Snake::getTailSymbol()
{
	return this->tailSymbol;
}

//Position Snake::getHeadPosition()
//{
//	return this->headPosition;
//}
//
//void Snake::setHeadPOsition(Position pos)
//{
//	this->headPosition = pos;
//}
//
//Position Snake::getTailPosition()
//{
//	return this->tailPosition;
//}
//
//void Snake::setTailPosition(Position pos)
//{
//	this->tailPosition = pos;
//}



//void Snake::setHeadSymbol(char head)
//{
//	this->headSymbol = head;
//}





//void Snake::setTailSymbol(char tail)
//{
//	this->tailSymbol = tail;
//}
//
//void Snake::setBodySymbol(char body)
//{
//	this->bodySymbol = body;
//}
