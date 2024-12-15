#include "loadSDL2.h"
#include "SDL_image.h"

SDL_Texture* loadSDLTexture(FILE *gameLog, struct SDL_Renderer *renderer, const char *texturePath)
{
	SDL_Surface *tempSurf = IMG_Load(texturePath);
	
	if( tempSurf )
	{
		SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurf);
		SDL_FreeSurface(tempSurf);
		if( tempTexture == NULL )
		{
			fprintf(gameLog, "Error: couldn't create SDL_Texture with prior texture path: %s, due to error: %s", texturePath, SDL_GetError() );
		}
		else{
			return tempTexture;
		}
	}
	else{
		fprintf(gameLog, "Error: couldn't create SDL_Surface with the following texture path: %s , due to error: %s", texturePath, IMG_GetError() );
	}
	
	return NULL;
}

void freeTextureIfAllocated(struct SDL_Texture **texture)
{
	if( *texture )
	{
		SDL_DestroyTexture(*texture);
		*texture = NULL;
	}
}

TTF_Font* loadFont(FILE *gameLog, const char *fontPath, unsigned ptSize)
{
	TTF_Font* font = TTF_OpenFont(fontPath, ptSize);
	
	if( !font )
	{
		fprintf(gameLog, "Error: couldn't open the following font: %s because: %s", fontPath, TTF_GetError() );
	}
	return font;
}

void freeFontIfAllocated(TTF_Font **font)
{
	if( *font )
	{
		TTF_CloseFont(*font);
		*font = NULL;
	}
}