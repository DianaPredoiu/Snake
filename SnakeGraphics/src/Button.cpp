#include "Button.h"

Button::Button(ButtonActions action, int x, int y, int width, int height)
{
	this->action = action;
	box.x = x;
	box.y = y;
	box.h = height;
	box.w = width;
}

SDL_Rect Button::getBox()
{
	return box;
}

void Button::setCoordinates(int x, int y)
{
	box.x = x;
	box.y = y;
}

bool Button::isPressed(SDL_Event e)
{
	int mouseX = e.button.x;
	int mouseY = e.button.y;

	//if the mouse is over the button 
	if ((mouseX > box.x) && (mouseX < box.x + box.w) && (mouseY > box.y) && (mouseY < box.y + box.h) && e.button.button == SDL_BUTTON_LEFT && e.button.type == SDL_MOUSEBUTTONUP)
		return true;
	return false;
}

Button::~Button()
{

}