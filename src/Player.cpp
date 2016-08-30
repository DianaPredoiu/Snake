#include "Player.h"

//Constructors
Player::Player()
{
	playerName = ""; playerScore = 0; moveLength = 0;
}

Player::Player(std::string name, int score, int moveLength)
	: playerName(name), playerScore(score)
{

}

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

// get and update for moveLength
int Player::getMoveLength()
{
	return moveLength;
}

void Player::updateMoveLength(int length)
{
	moveLength += length;
}

// A method to update the score
void Player::updateScore()
{
	// Don't ask why this formula but it is original
	playerScore += moveLength * 36 / 5 + 1;
}