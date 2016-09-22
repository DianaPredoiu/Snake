#pragma once

#include <SDL.h>
#include <Texture.h>
#include <Item.h>

class SymbolTranslation{
private:
	char symbol;
	Texture texture;
	SDL_Renderer* renderer;

public:
	// Constructor
	SymbolTranslation(char sym, SDL_Renderer* requiredRenderer);

	// accessors
	SDL_Texture* GetTexture();
	char GetSymbol();

	// Texture management depending on given symbol
	void ConvertToTextureFromSymbol();

	~SymbolTranslation();
};