#include "game/initGlobalGameData.h"
#include "game/globalGameData.h"
#include "loadGameGraphics.h"
#include "allocMeltCardsData.h"
#include "common/initTempStruct.h"

void initializeEverything(FILE *gameLog, SDL_Renderer *renderer, struct GlobalGameData* gameData, unsigned pairNumber)
{
	gameData->quitGame = false;
	gameData->pairNumber = pairNumber;
	initializeSDL_Textures(&gameData->graphics);
	loadGraphicsMain(gameLog, renderer, &gameData->graphics, pairNumber);
	distributeIndexInCardArray(&gameData->data, pairNumber);
	initDelayStruct(&gameData->drawFreq);
	
	gameData->canPlayGame = isEveythingOk(gameData);
}

bool isEveythingOk(const struct GlobalGameData* gameData)
{
	return areAllGraphicsLoaded(&gameData->graphics, gameData->pairNumber)
		&& areNumericDataLoaded(&gameData->data);
}

bool areAllGraphicsLoaded(const struct CardsGraphics* const graphics, unsigned pairNumber)
{
	return graphics->arialFont 
		&& areCardsFacesLoaded(graphics, pairNumber)
		&& graphics->cardsBack
		&& areDisplayTextsAllLoaded(graphics)
		&& graphics->drawingCountText.texture
		&& graphics->replayButton;
}

bool areCardsFacesLoaded(const struct CardsGraphics* const graphics, unsigned pairNumber)
{
	for( size_t i = 0 ; i < pairNumber ; ++i )
	{
		if( NULL == graphics->cardsFaces[i] )
			return false;
	}
	return true;
}

bool areDisplayTextsAllLoaded(const struct CardsGraphics* const graphics)
{
	for( size_t i = 0 ; i < DISPLAY_MAX ; ++i )
	{
		if( NULL == graphics->textToDisplay[i].texture )
			return false;
	}
	return true;
}

bool areNumericDataLoaded(const struct CardsNumericData* const numericData)
{
	return numericData->cardsIndexArray && numericData->divulgedCards;
}

void freeEverything(struct GlobalGameData *gameData)
{
	freeAllGraphics(&gameData->graphics, gameData->pairNumber);
	freeMemoryAllocations(&gameData->data);
}