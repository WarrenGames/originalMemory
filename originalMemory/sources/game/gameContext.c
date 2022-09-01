#include "game/gameContext.h"
#include "game/globalGameData.h"
#include "game/displayCards.h"
#include "game/initGlobalGameData.h"
#include "game/loadGameGraphics.h"
#include "game/displayText.h"
#include "common/user.h"

void gameCustomized(FILE *gameLog, SDL_Renderer *renderer, struct Input *in, unsigned int pairNumber)
{	
	SDL_SetRenderDrawColor(renderer, 0, 127, 14, 255);
	struct GlobalGameData gameData;
	initializeEverything(gameLog, renderer, &gameData, pairNumber);
	inputInitialisation(in);
	
	gameMainLoop(renderer, in, &gameData);
    
	freeEverything(&gameData);
	in->spaceBar = false;
}

void gameMainLoop(SDL_Renderer *renderer, struct Input* in, struct GlobalGameData *gameData)
{
	while( false == gameData->quitGame )
	{
		updateEvents(in);

		quitGame(in, &gameData->quitGame );
		drawCardsWMouse(renderer, in, gameData);
		checkIfGameFinished(renderer, in, gameData);
		displayEverythingInScreen(renderer, gameData);
    }
}

void drawCardsWMouse(SDL_Renderer *renderer, struct Input *in, struct GlobalGameData *gameData)
{
	switch( gameData->data.currentStep )
	{
		case WAIT_CARD1_CHOICE:
			waitForFirstCardToBeClicked(in, gameData);
			break;
        case WAIT_CARD2_CHOICE:
			waitForSecondCardToBeClicked(renderer, in, gameData);
			break;
		case TEST_IF_CARDS_TWINS:
            testIfRevealedCardsAreTwins(in, gameData);
			break;
	}
}

void waitForFirstCardToBeClicked(struct Input *in, struct GlobalGameData *gameData)
{
	if( in->mouseButtons[SDL_BUTTON_LEFT])
	{
		determineSelectedCardIndex(in, gameData, CARD1);
		switchToSecondCardPicking(gameData);
		in->mouseButtons[SDL_BUTTON_LEFT] = false;
	}
}

void switchToSecondCardPicking(struct GlobalGameData *gameData)
{
	if( gameData->data.selectedCards[CARD1] != gameData->pairNumber * 2)
	{
		gameData->data.currentStep = WAIT_CARD2_CHOICE;
	}
}

void waitForSecondCardToBeClicked(SDL_Renderer *renderer, struct Input *in, struct GlobalGameData *gameData)
{
	if( in->mouseButtons[SDL_BUTTON_LEFT] && false == in->spaceBar)
	{
		determineSelectedCardIndex(in, gameData, CARD2);
		
		if( gameData->data.selectedCards[CARD2] != gameData->pairNumber * 2 && gameData->data.selectedCards[CARD2] != gameData->data.selectedCards[CARD1] )
		{   
			gameData->data.currentStep = TEST_IF_CARDS_TWINS;
			gameData->data.triesNumber++;
			computeTriesNumber(renderer, &gameData->graphics.drawingCountText, gameData->data.triesNumber, gameData->graphics.arialFont);
		}
		
		in->mouseButtons[SDL_BUTTON_LEFT] = false;
	}
}

void testIfRevealedCardsAreTwins(struct Input *in, struct GlobalGameData *gameData)
{
	displayTextAccordinglyOfPickedCards(gameData);
	turnBackCardsWithSpaceBar(in, gameData);
}

void displayTextAccordinglyOfPickedCards(struct GlobalGameData *gameData)
{
	if( gameData->data.cardsIndexArray[gameData->data.selectedCards[CARD1]] == gameData->data.cardsIndexArray[gameData->data.selectedCards[CARD2]] )
	{
		gameData->data.areCardsTwins = true;
		gameData->data.whichTextToDisplay = WELL_DONE;
	}
	else{
		gameData->data.whichTextToDisplay = WHAT_A_PITY;
	}
}

void turnBackCardsWithSpaceBar(struct Input *in, struct GlobalGameData *gameData)
{
	if( in->spaceBar || in->mouseButtons[SDL_BUTTON_RIGHT] )
	{
		removeCardsFromBoardBecauseTheyreTwins(gameData);
		gameData->data.selectedCards[CARD1] = gameData->pairNumber * 2;
		gameData->data.selectedCards[CARD2] = gameData->pairNumber * 2;
		gameData->data.currentStep = WAIT_CARD1_CHOICE;
		in->spaceBar = false;
		in->mouseButtons[SDL_BUTTON_RIGHT] = false;
	}
}

void removeCardsFromBoardBecauseTheyreTwins(struct GlobalGameData *gameData)
{
	if( gameData->data.areCardsTwins )
	{
		gameData->data.divulgedCards[gameData->data.selectedCards[CARD1]] = CARD_REVEAL;
		gameData->data.divulgedCards[gameData->data.selectedCards[CARD2]] = CARD_REVEAL;
		gameData->data.areCardsTwins = false;
	}
}

void checkIfGameFinished(SDL_Renderer *renderer, struct Input *in, struct GlobalGameData *gameData)
{
	if( isGameFinished(gameData) )
	{
		gameData->data.currentStep = GAME_WON;
		gameData->data.whichTextToDisplay = GAME_FINISHED;
		handleReplay(renderer, in, gameData);
	}
}

bool isGameFinished(const struct GlobalGameData *gameData)
{
	for(unsigned int i = 0 ; i < gameData->data.cardNumber * 2 ; ++i)
	{
		if( false == gameData->data.divulgedCards[i] )
			return false;
	}
	return true;
}

void quitGame(const struct Input *in, bool *quit)
{
	if( in->escape || in->SDL_Quit)
	{
		*quit = true;
	}
}

void handleReplay(SDL_Renderer *renderer, struct Input *in, struct GlobalGameData *gameData)
{	
	SDL_Rect memoryRect;
	dispReplayButton(renderer, gameData->graphics.replayButton, &memoryRect);
	
	while( false == gameData->quitGame )
	{
		updateEvents(in);
		if( ( in->xmouse >= memoryRect.x && in->xmouse < memoryRect.x + memoryRect.w && in->ymouse >= memoryRect.y	&& in->ymouse < memoryRect.y + memoryRect.h 
				&& in->mouseButtons[SDL_BUTTON_LEFT] ) || in->SDL_Quit  )
		{
			gameData->quitGame = true;
		}
		
		SDL_RenderClear(renderer);
		dispReplayButton(renderer, gameData->graphics.replayButton, &memoryRect);
		dispFinalDrawCount(renderer, &gameData->graphics.drawingCountText);
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
	in->mouseButtons[SDL_BUTTON_LEFT] = false;
}


void determineSelectedCardIndex(const struct Input *in, struct GlobalGameData *gameData, unsigned numeroCarte)
{
	gameData->data.selectedCards[numeroCarte] = gameData->pairNumber * 2;
	for( int i = 0 ; i < (int)gameData->pairNumber * 2 / CARDSBYROW ; ++i)
	{
		for( int j = 0 ; j < CARDSBYROW ; ++j)
		{
			if( isCardPicked(in, j, i) && false == hasCardBeenRevealed(gameData, j, i) )
			{
				gameData->data.selectedCards[numeroCarte] = i * CARDSBYROW + j;
				break;
			}
		}
	}
}

bool isCardPicked(const struct Input *in, int jCardsRow, int iCardsColumn)
{
	return jCardsRow == ( in->xmouse - MARGIN) / (SQUARE_SIZE + INTERSTICECARDS)
		&& jCardsRow + 1 > ( in->xmouse + INTERSTICECARDS - MARGIN) / (SQUARE_SIZE + INTERSTICECARDS)
		&& iCardsColumn ==  ( in->ymouse - MARGIN) / (SQUARE_SIZE + INTERSTICECARDS)
		&& iCardsColumn + 1 > ( in->ymouse + INTERSTICECARDS - MARGIN) / (SQUARE_SIZE + INTERSTICECARDS) ;
}

bool hasCardBeenRevealed(const struct GlobalGameData *gameData, int jCardRow, int iCardColumn)
{
	return gameData->data.divulgedCards[iCardColumn * CARDSBYROW + jCardRow];
}