#pragma once
#include <vector>
#include "Position.h"

class Snake
{
private:
	std::vector<Position*> coordinates;
	//Position headPosition;
	//Position tailPosition;
	char headSymbol;
	char bodySymbol;
	char tailSymbol;
public:
	Snake();
	Snake(int i, int j);
	std::vector<Position*> getCoordinates() const;
	void setCoordinates(std::vector<Position*>  coordinates);
	char getHeadSymbol();
	char getBodySymbol();
	char getTailSymbol();

	/*Position getHeadPosition();
	void setHeadPOsition(Position pos);
	Position getTailPosition();
	void setTailPosition(Position pos);*/
	//void setHeadSymbol(char head);
	//void setBodySymbol(char body);
	//void setTailSymbol(char tail);

};