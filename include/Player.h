#pragma once
#include <string>
#include "DLLExportOptions.h"
class DLL_SNAKE Player
{
private:
	// a player is represented by a name, a score and a move 
	// length measured in units as in grid cells
	std::string playerName;
	int playerScore;
	std::string level;

public:
	// Constructors
	Player();
	Player(std::string name, int score, std::string level);
	
	// Accessor for the name
	std::string getPlayerName();

	// Accessor for the score
	int getScore();

	// Setter for the name
	void setPlayerName(std::string name);

	// Setter for the score
	void setPlayerScore(int score);

	std::string getLevel();
	void setLevel(std::string level);

	~Player();
};

