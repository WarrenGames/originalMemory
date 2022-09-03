#ifndef DISPLAY_CARDS_H
#define DISPLAY_CARDS_H

#include <stdbool.h>
#include "SDL_render.h"

struct Temporisation;
struct GlobalGameData;

void displayEverythingInScreen(SDL_Renderer *renderer, struct GlobalGameData *gameData);

void displayCards(SDL_Renderer *renderer, struct GlobalGameData *gameData);

void displayOrQuitLoop(SDL_Renderer *renderer, struct GlobalGameData *gameData, unsigned *decompte, int j);

void drawOneCardFace(SDL_Renderer *renderer, struct GlobalGameData *gameData, const unsigned *decompte, int j);

bool quitLoop(unsigned decompte, const struct GlobalGameData *gameData);

#endif //DISPLAY_CARDS_H