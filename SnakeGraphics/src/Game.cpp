#include "Game.h"

Game::Game()
{
	
}

bool loadTextures()
{
	// empty the surface to make sure it doesn't collide in textures
	free();

	SDL_Texture* newTexture = NULL;
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/");
	p.append(fileName);
	// load img and print on window
	SDL_Surface* loadedSurface = IMG_Load(p.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load the image " << p.c_str() << ", SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		newTexture = IMG_LoadTexture(renderer, p.c_str());
		int a, b;
		SDL_QueryTexture(newTexture, NULL, NULL, &a, &b);
		//newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_Rect texr; texr.x = 150; texr.y = 150; texr.w = a / 10; texr.h = b / 10;
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture" << p.c_str() << ", SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			//imWidth = width;
			//imHeight = height;
		}
}
bool Game::init()
{
	screenSurface = NULL;
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: \n" << SDL_GetError();
		success = false;
	}
	else
	{
		//Create window and renderer
		window = SDL_CreateWindow("El Snake Roho", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL Error: \n" << SDL_GetError();
			success = false;
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

		}

	}

	return success;
}

Game::~Game()
{

}

void Game::executeGame()
{

}
bool Game::hasTheGameStarted()
{

}
void Game::render()
{

}
void Game::gameLogic()
{

}
void Game::updateMove()
{

}
void Game::checkCollision()
{

}