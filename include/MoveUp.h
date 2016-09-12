#pragma once
#include "Command.h"

class MoveUp : public Command
{
public:
	bool execute(GameMap& game) override;
};