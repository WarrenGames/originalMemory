#include "allocMeltCardsData.h"
#include "numericData.h"
#include "common/defines.h"
#include <stdlib.h>
#include <time.h>

void distributeIndexInCardArray(struct CardsNumericData *cardsData, unsigned int pairNumber)
{
	setLinearCardsValue(cardsData, pairNumber);
	meltCardsValueData(cardsData, pairNumber);
	initMiscellaneous(cardsData, pairNumber);
}

void setLinearCardsValue(struct CardsNumericData *cardsData, unsigned int pairNumber)
{
	cardsData->cardsIndexArray = malloc(pairNumber * 2 * (sizeof(int)));
	cardsData->divulgedCards = malloc(pairNumber * 2 * (sizeof(bool)));
	//PairNumber : 63 for hard mode, 48 medium skill et 32 for easy mode
	//cards array size:  (2 * pairNumber) 
	for(unsigned i = 0 ; i < pairNumber ; ++i)
	{	//Ici, assigner les valeurs (=index de tableau SDL_Textures) à un groupe de deux cartes
		cardsData->cardsIndexArray[i * 2] = i;
		cardsData->cardsIndexArray[i * 2 + 1] = i;
	}
}

void meltCardsValueData(struct CardsNumericData *cardsData, unsigned int pairNumber)
{
	srand(time(NULL));
	for(unsigned i = 0 ; i < pairNumber * 2 ; ++i)
	{	//Ici, mélange des cartes en intervertissant deux cartes (d'une manières linéaire la première jusqu' à la dernière avec une tirée au hasard)
		unsigned int randNumber = rand() % (pairNumber * 2);
		unsigned int temp = cardsData->cardsIndexArray[i];
		cardsData->cardsIndexArray[i] = cardsData->cardsIndexArray[randNumber];
		cardsData->cardsIndexArray[randNumber] = temp;

        cardsData->divulgedCards[i] = 0;
	}
}

void initMiscellaneous(struct CardsNumericData* cardsData, unsigned int pairNumber)
{
	cardsData->selectedCards[0] = pairNumber * 2;
	cardsData->selectedCards[1] = pairNumber * 2;
	cardsData->currentStep = WAIT_CARD1_CHOICE;
	cardsData->cardNumber = pairNumber;
	cardsData->areCardsTwins = false;
	cardsData->whichTextToDisplay = DISPLAY_MAX;
	cardsData->triesNumber = 0;
}

void freeMemoryAllocations(struct CardsNumericData* cardsData)
{
	if( cardsData->cardsIndexArray )
	{
		free(cardsData->cardsIndexArray);
	}
	if( cardsData->divulgedCards )
	{
		free(cardsData->divulgedCards);
	}
}