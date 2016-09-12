#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class IMTexture
{
public:
	//Initializes variables
	IMTexture(SDL_Renderer *requiredRenderer, std::string fileName, int width, int height);

	IMTexture()
	{
		imHeight = 0;
		imWidth = 0;
		imTexture = NULL;
	}

	//Deallocates memory
	~IMTexture();

	//Loads image at specified path
	SDL_Texture* loadFromFile(std::string fileName);

	// draws an image at a given position
	void DrawImage(SDL_Surface *surface, char *image_path, int x_pos, int y_pos);

	//Deallocates texture
	void free();

	//Gets image dimensions
	int getWidth();
	int getHeight();

	SDL_Texture* GetTexture();

private:

	SDL_Renderer* renderer;
	//The actual hardware texture
	SDL_Texture* imTexture;

	//Image dimensions
	int imWidth;
	int imHeight;
};