#include <iostream>
#include <SDL.h>


//The workin window
SDL_Window* window = NULL;

//The surface in the window
SDL_Surface* screenSurface = NULL;

//Current displayed image
SDL_Surface* currentSurface = NULL;

//Current displayed image on streched surface
SDL_Surface* stretchedSurface = NULL;

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load stretching surface
	stretchedSurface = loadSurface("05_optimized_surface_loading_and_soft_stretching/iarba.png");
	if (stretchedSurface == NULL)
	{
		printf("Failed to load stretching image!\n");
		success = false;
	}

	return success;
}

SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}


SDL_Surface *IMG_Load(const char *file)
{
	SDL_Texture* grass_image = nullptr;
	grass_image = IMG_LoadTexture(renderer, "res/grass.bmp");
	SDL_Rect grass_rect;
	grass_rect.x = 0;
	grass_rect.y = 0;
	grass_rect.w = SCREEN_WIDTH;
	grass_rect.h = SCREEN_HEIGHT;

	if (grass_image == NULL)
		std::cout << "Couldn't load grass_image" << std::endl;

	while (!quit && mainEvent->type != SDL_Quit)
	{
		SDL_RenderCopy(renderer, grass_image, NULL, &grass_rect);
	}
}