#pragma once
#include "Command.h"

class MoveLeft : public Command
{
public:
	bool execute(GameMap& game);
};