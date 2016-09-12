#pragma once
#include <vector>
#include "Position.h"
#include "DLLExportOptions.h"

class DLL_SNAKE Snake
{
private:
	std::vector<Position*> coordinates;
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

	~Snake();
};