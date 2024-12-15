#include "common/loadComboTexture.h"
#include "common/comboTextureStruct.h"
#include "common/positionStruct.h"
#include "SDL_image.h"

void loadComboTextures(FILE *gameLog, SDL_Renderer *renderer, const char *texturePath, struct ComboTexture *comboTexture)
{
	SDL_Surface *tempSurf = IMG_Load(texturePath);
	
	resetComboTextureSize(comboTexture);
	
	if( tempSurf )
	{
		comboTexture->texture = SDL_CreateTextureFromSurface(renderer, tempSurf);
		comboTexture->w = tempSurf->w;
		comboTexture->h = tempSurf->h;
		SDL_FreeSurface(tempSurf);
		if( NULL == comboTexture->texture )
		{
			fprintf(gameLog, "Error: loading SDL_Texture from file: %s impossible, reason: %s\n", texturePath, SDL_GetError() );
		}
	}
	else{
		fprintf(gameLog, "Error : loading texture file : '%s' impossible, reason: %s\n", texturePath, IMG_GetError() );
	}
}

void loadBlendedTextTexture(FILE *gameLog, SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, struct ComboTexture *comboTexture)
{
	resetComboTextureSize(comboTexture);
	if( font )
	{
		SDL_Surface *tempSurf = TTF_RenderUTF8_Blended( font, text, color );
		if( tempSurf )
		{
			comboTexture->texture = SDL_CreateTextureFromSurface(renderer, tempSurf);
			comboTexture->w = tempSurf->w;
			comboTexture->h = tempSurf->h;
			SDL_FreeSurface(tempSurf);
		}
		else{
			fprintf(gameLog, "Error: couldn't create a SDL_Surface with text: '%s' .", text);
		}
	}
}

void freeComboTextureIfAny(struct ComboTexture *comboTexture)
{
	if( comboTexture->texture )
	{
		SDL_DestroyTexture(comboTexture->texture);
	}
}

void resetComboTextureSize(struct ComboTexture *comboTexture)
{
	if( comboTexture )
	{
		comboTexture->w = 0;
		comboTexture->h = 0;
	}
}

void drawComboToCenter(SDL_Renderer *renderer, const struct ComboTexture *comboTexture, const struct Position *centerPosition, SDL_Rect *rect)
{
	if( comboTexture->texture )
	{
		rect->x = centerPosition->x - comboTexture->w / 2;
		rect->y = centerPosition->y - comboTexture->h / 2;
		rect->w = comboTexture->w;
		rect->h = comboTexture->h;
		SDL_RenderCopy(renderer, comboTexture->texture, NULL, rect );
	}
}