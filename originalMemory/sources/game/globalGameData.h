#ifndef GLOBAL_GAME_DATA_H
#define GLOBAL_GAME_DATA_H

#include "game/cardsGraphics.h"
#include "game/numericData.h"
#include "common/timeDelayStruct.h"

struct GlobalGameData
{
	struct CardsGraphics graphics;
	struct CardsNumericData data;
	struct Temporisation drawFreq;
	unsigned pairNumber;
	bool quitGame;
	bool canPlayGame;
};

#endif //GLOBAL_GAME_DATA_H