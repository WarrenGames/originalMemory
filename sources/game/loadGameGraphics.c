#include "loadGameGraphics.h"
#include "common/comboTextureStruct.h"
#include "numericData.h"
#include "game/cardsGraphics.h"
#include "common/loadSDL2.h"

void loadGraphicsMain(FILE *gameLogs, SDL_Renderer *renderer, struct CardsGraphics *graphics, unsigned pairNumber)
{
	graphics->arialFont = loadFont(gameLogs, "fonts/arial.ttf", 20);
	loadCardsFacesTextures(gameLogs, renderer, &graphics->cardsFaces, pairNumber);
	graphics->cardsBack = loadSDLTexture(gameLogs, renderer, "textures/back.png");
	loadTextsTextures(gameLogs, renderer, graphics->textToDisplay);
	computeTriesNumber(renderer, &graphics->drawingCountText, 0, graphics->arialFont);
	graphics->replayButton = loadSDLTexture(gameLogs, renderer, "textures/btnReplay.png");
}


void loadCardsFacesTextures(FILE *gameLog, SDL_Renderer *renderer, SDL_Texture ***textureArray, unsigned pairNumber)
{
	char cardsTexturesPath[32];

	*textureArray = malloc( pairNumber * sizeof(SDL_Texture*) );

	for(unsigned int i = 0 ; i < pairNumber ; ++i )
	{
		sprintf(cardsTexturesPath, "textures/%u.png", i);
		(*textureArray)[i] = loadSDLTexture(gameLog, renderer, cardsTexturesPath);
	}
}

void loadTextsTextures(FILE *gameLog, SDL_Renderer *renderer, struct ComboTexture tabTextes[])
{
    TTF_Font *font = TTF_OpenFont("fonts/arial.ttf",20);
	if( font )
	{
		SDL_Color redColor = {255, 0, 0, 255};
		SDL_Color blueColor = {0, 0, 255, 255};
		SDL_Color whiteColor = {255, 255, 255, 255};
		
		loadSingleTextTexture(gameLog, renderer, &tabTextes[WHAT_A_PITY], "He non, Dommage...", font, redColor);
		loadSingleTextTexture(gameLog, renderer, &tabTextes[WELL_DONE], "Bien joué !", font, whiteColor);
		loadSingleTextTexture(gameLog, renderer, &tabTextes[GAME_FINISHED], "Vous avez tout trouvé, bien joué", font, blueColor);
		loadSingleTextTexture(gameLog, renderer, &tabTextes[PUSH_SPACE], "Appuyez sur ESPACE pour reinitialiser", font, whiteColor);
		
		TTF_CloseFont(font);
	}
	else{
		fprintf(gameLog, "Error: couldn't load 'fonts/arial.ttf' font du to error: %s", TTF_GetError() );
	}
    
}

void loadSingleTextTexture(FILE *gameLog, SDL_Renderer *renderer, struct ComboTexture *textTexture, const char *text, TTF_Font *font, const SDL_Color color)
{
	if( font )
	{
		SDL_Surface *tempSurf = TTF_RenderUTF8_Blended(font, text, color);
		if( tempSurf )
		{
			textTexture->texture = SDL_CreateTextureFromSurface(renderer, tempSurf);
			textTexture->w = tempSurf->w;
			textTexture->h = tempSurf->h;
			if( textTexture->texture == NULL )
			{
				fprintf(gameLog, "Error: couldn't create text SDL_Texture with text %s , du to error: %s", text, SDL_GetError() );
			}
			SDL_FreeSurface(tempSurf);
		}
		else{
			fprintf(gameLog, "Error: couldn't create text SDL_Surface texture du to error: %s", TTF_GetError() );
		}
	}
}

void computeTriesNumber(SDL_Renderer *rendu, struct ComboTexture *selectNumber, unsigned int drawNumber, TTF_Font *font)
{
	SDL_Color blue = {0, 0, 255, 255};
	char drawNumberText[48];
	sprintf(drawNumberText, "Pioches effectuees: %u", drawNumber);
	
	SDL_Surface *surfTemp = TTF_RenderText_Blended(font, drawNumberText, blue);
	
	if( selectNumber->texture != NULL )
	{
		SDL_DestroyTexture(selectNumber->texture);
	}
	
	selectNumber->texture = SDL_CreateTextureFromSurface(rendu, surfTemp);
	selectNumber->w = surfTemp->w;
	selectNumber->h = surfTemp->h;
	SDL_FreeSurface(surfTemp);
}

void freeAllGraphics(struct CardsGraphics *graphics, unsigned pairNumber)
{
	freeFontIfAllocated(&graphics->arialFont);
	freeCardsFaces(graphics, pairNumber);
	freeCardsFacesArray(graphics);
	freeTextureIfAllocated(&graphics->cardsBack);
	freeTextToDisplay(&graphics->textToDisplay);
	freeTextureIfAllocated(&graphics->drawingCountText.texture);
	freeTextureIfAllocated(&graphics->replayButton);
}

void freeCardsFaces(struct CardsGraphics *graphics, unsigned pairNumber)
{
	for( unsigned i = 0 ; i < pairNumber ; ++i )
	{
		if( graphics->cardsFaces[i] )
		{
			SDL_DestroyTexture(graphics->cardsFaces[i]);
			graphics->cardsFaces[i] = NULL;
		}	
	}
}

void freeCardsFacesArray(struct CardsGraphics *graphics)
{
	if( graphics->cardsFaces )
	{
		free(graphics->cardsFaces);
		graphics->cardsFaces = NULL;
	}
}

void freeTextToDisplay(struct ComboTexture (*textToDisplay)[DISPLAY_MAX])
{
	for( unsigned i = 0 ; i < DISPLAY_MAX ; ++i )
	{
		if( (*textToDisplay)[i].texture )
		{
			SDL_DestroyTexture((*textToDisplay)[i].texture);
			(*textToDisplay)[i].texture = NULL;
		}
	}
}