#pragma once

class Position
{
private:
	int x;
	int y;
public:
	Position();
	Position(int x, int y); //x- columns(j), y-rows(i)
	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
};
