#pragma once
#include "GameMap.h"
#include "DLLExportOptions.h"

class DLL_SNAKE Rules
{
	GameMap *game;

public:
	Rules(GameMap *game);

	bool leftMove();
	bool upMove();
	bool rightMove();
	bool downMove();

	bool eatItself();

	bool isOutOfBounds();

	bool continuousMovement();

	~Rules();
};