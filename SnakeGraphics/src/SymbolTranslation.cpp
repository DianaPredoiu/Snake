#include <SymbolTranslation.h>

SymbolTranslation::SymbolTranslation(char sym, SDL_Renderer* requiredRenderer)
{
	this->symbol = sym;
	renderer = requiredRenderer;
}

// accessors
SDL_Texture* SymbolTranslation::GetTexture()
{
	return texture.GetTexture();
}

char SymbolTranslation::GetSymbol()
{
	return symbol;
}

// Texture management depending on given symbol
void SymbolTranslation::ConvertToTextureFromSymbol()
{
	// a switch case to choose the right image 
	// for the item depending on the given symbol
	switch (symbol)
	{
		case 'F':
		{
			texture.loadFromFile("food.png", renderer);
			break;
		}
		case 'B':
		{
			texture.loadFromFile("bonus2.png", renderer);
			break;
		}
		case '?':
		{
			texture.loadFromFile("surprise2.png", renderer);
			break;
		}
		case 'H':
		{
			texture.loadFromFile("head.png", renderer);
			break;
		}
		case 'b':
		{
			texture.loadFromFile("body.png", renderer);
			break;
		}
		case 'T':
		{
			texture.loadFromFile("tail.png", renderer);
			break;
		}
		default: break;
	}
}

SymbolTranslation::~SymbolTranslation()
{
	delete renderer;
}