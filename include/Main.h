#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "GameMap.h"
#include "Rules.h"
#include "catch.hpp"
#include "DLLExportOptions.h"
void displayDetails(GameMap &game, std::vector<Position*> pos);

void DLL_SNAKE Game();