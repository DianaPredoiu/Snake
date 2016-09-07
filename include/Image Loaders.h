#pragma once

#include <iostream>
#include <SDL.h>

bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);


SDL_Surface *IMG_Load(const char *file);
