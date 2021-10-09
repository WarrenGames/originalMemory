#include "displayCards.h"
#include "game/globalGameData.h"
#include "game/displayText.h"
#include "common/initTempStruct.h"
#include "common/defines.h"

void displayEverythingInScreen(SDL_Renderer *renderer, struct GlobalGameData *gameData)
{
	if( hasTimeElapsed( &gameData->drawFreq, 16 ) )
	{
		SDL_RenderClear(renderer);
		displayCards(renderer, gameData);
		displayText(renderer, gameData);
		SDL_RenderPresent(renderer);
		joinTimePoints( &gameData->drawFreq );
	}
}

void displayCards(SDL_Renderer *renderer, struct GlobalGameData *gameData)
{
	gameData->graphics.drawingRect.w = SQUARE_SIZE;
	gameData->graphics.drawingRect.h = SQUARE_SIZE;
	unsigned int countDown = 0;
	for(unsigned int i = 0 ; i < gameData->data.cardNumber / 7 ; ++i)
	{
		gameData->graphics.drawingRect.y = MARGIN + i * (SQUARE_SIZE + INTERSTICECARDS);
		for(unsigned int j = 0 ; j < 14 ; ++j)
		{
			displayOrQuitLoop(renderer, gameData, &countDown, j);
			if( quitLoop(countDown, gameData) )
				break;
		}
		if( quitLoop(countDown, gameData) )
			break;
	}
}

void displayOrQuitLoop(SDL_Renderer *renderer, struct GlobalGameData *gameData, unsigned *decompte, int j)
{
	if( *decompte < gameData->data.cardNumber * 2)
	{
		drawOneCardFace(renderer, gameData, decompte, j);
	}
	(*decompte)++;
}

void drawOneCardFace(SDL_Renderer *renderer, struct GlobalGameData *gameData, unsigned *decompte, int j)
{
	gameData->graphics.drawingRect.x = MARGIN + j * (SQUARE_SIZE + INTERSTICECARDS);
	//Revealed card
	if( false == gameData->data.divulgedCards[*decompte] 
		&& (gameData->data.selectedCards[CARD1] == *decompte || gameData->data.selectedCards[CARD2] == *decompte) )
	{
		SDL_RenderCopy(renderer, 
						gameData->graphics.cardsFaces[ gameData->data.cardsIndexArray[*decompte] ], 
						NULL, 
						&gameData->graphics.drawingRect);
	}
	//Back turned card
	else if( false == gameData->data.divulgedCards[*decompte] 
			&& gameData->data.selectedCards[CARD1] != *decompte 
			&& gameData->data.selectedCards[CARD2] != *decompte )
	{
		SDL_RenderCopy(renderer, gameData->graphics.cardsBack, NULL, &gameData->graphics.drawingRect);
	}
}

bool quitLoop(unsigned decompte, struct GlobalGameData *gameData)
{
	return decompte >= gameData->data.cardNumber * 2;
}