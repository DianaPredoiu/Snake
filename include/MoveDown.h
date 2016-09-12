#pragma once
#include "Command.h"

class MoveDown : public Command
{
public:
	bool execute(GameMap& game);
};