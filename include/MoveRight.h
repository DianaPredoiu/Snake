#pragma once
#include "Command.h"

class MoveRight : public Command
{
public:
	bool execute(GameMap& game);
};