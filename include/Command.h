#pragma once
#include "GameMap.h"
class Command
{
public:
	virtual ~Command() {}
	virtual bool execute(GameMap& game) = 0;
};