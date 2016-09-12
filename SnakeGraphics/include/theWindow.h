#include <iostream>
#include "SDL.h"

class WindowSDL{

public:
	WindowSDL(bool *quit, int ScreenWidth, int ScreenHeight);
	~WindowSDL();

	SDL_Renderer *GetRenderer();
	SDL_Event *GetMainEvent();

	SDL_Surface *GetSurface();
	SDL_Texture *GetTexture();
	SDL_Surface *GetDisplaySurface();
	SDL_Window *GetWindow();


	void SetTexture(SDL_Texture *tex);
	void SetSurface(SDL_Surface *surface);

	void Begin();
	void End();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	//Loads individual image
	void loadSurface(std::string path);

	//Loads individual image as texture
	SDL_Texture* loadTexture(std::string path);

private:
	// for window processing
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event *mainEvent;

	// for image processing
	// The window to render to

	// The screen surface contained by the window
	SDL_Surface *screenSurface = NULL;

	// The current image in display
	SDL_Surface *displaySurface = NULL;

	// Current displayed texture
	SDL_Texture *texture = NULL;
};