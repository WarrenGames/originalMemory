#ifndef INIT_GLOBAL_GAME_DATA_H
#define INIT_GLOBAL_GAME_DATA_H

#include "SDL.h"
#include <stdio.h>
#include <stdbool.h>

struct GlobalGameData;
struct CardsGraphics;
struct CardsNumericData;

void initializeEverything(FILE *gameLog, SDL_Renderer *renderer, struct GlobalGameData* gameData, unsigned pairNumber);

bool isEveythingOk(const struct GlobalGameData* const gameData);

bool areAllGraphicsLoaded(const struct CardsGraphics* const graphics, unsigned pairNumber);

bool areCardsFacesLoaded(const struct CardsGraphics* const graphics, unsigned pairNumber);

bool areDisplayTextsAllLoaded(const struct CardsGraphics* const graphics);

bool areNumericDataLoaded(const struct CardsNumericData* const numericData);

void freeEverything(struct GlobalGameData *gameData);

#endif //INIT_GLOBAL_GAME_DATA_H