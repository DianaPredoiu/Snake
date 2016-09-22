#include "Player.h"

#pragma region Constructors
Player::Player()
{
	playerName = ""; 
	playerScore = 0;
}

Player::Player(std::string name, int score, std::string level)
	: playerName(name), playerScore(score), level(level)
{

}
#pragma endregion

#pragma region Get/Set
// Accessor for the name
std::string Player::getPlayerName()
{
	return playerName;
}

// Accessor for the score
int Player::getScore()
{
	return playerScore;
}

// Setter for the name
void Player::setPlayerName(std::string name)
{
	playerName = name;
}

// Setter for the score
void Player::setPlayerScore(int score)
{
	playerScore = score;
}

std::string Player::getLevel()
{
	return level;
}

void Player::setLevel(std::string level)
{
	this->level = level;
}

#pragma endregion

#pragma region Destructor
Player::~Player()
{

}
#pragma endregion