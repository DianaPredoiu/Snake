#include <SymbolTranslation.h>

SymbolTranslation::SymbolTranslation(char sym, SDL_Renderer* requiredRenderer)
{
	this->symbol = sym;
	renderer = requiredRenderer;
}

// accessors
Texture SymbolTranslation::GetTexture()
{
	return texture;
}

char SymbolTranslation::GetSymbol()
{
	return symbol;
}

// Texture management depending on given symbol
Texture SymbolTranslation::ConvertToTextureFromSymbol()
{
	// a switch case to choose the right image 
	// for the item depending on the given symbol
	switch (symbol)
	{
		case 'F':
		{
			texture.loadFromFile("food1.png", renderer, 50, 50);
			break;
		}
		case 'B':
		{
			texture.loadFromFile("bonus.png", renderer, 50, 50);
			break;
		}
		case '?':
		{
			texture.loadFromFile("surprise.png", renderer, 50, 50);
			break;
		}
		case 'H':
		{
			texture.loadFromFile("cap.png", renderer, 50, 50);
			break;
		}
		case 'b':
		{
			texture.loadFromFile("corp.png", renderer, 50, 50);
			break;
		}
		case 'T':
		{
			texture.loadFromFile("coada.png", renderer, 50, 50);
			break;
		}
		default: break;
	}
	return texture;
}