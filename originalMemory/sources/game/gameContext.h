#ifndef H_CONTEXTS
#define H_CONTEXTS

#include "SDL_render.h"
#include <stdio.h>
#include <stdbool.h>

struct Input;
struct GlobalGameData;

void gameCustomized(FILE *gameLog, SDL_Renderer *renderer, struct Input *In, unsigned int pairNumber);

void gameMainLoop(SDL_Renderer *renderer, struct Input *in, struct GlobalGameData *gameData);

void drawCardsWMouse(SDL_Renderer *renderer, struct Input *in, struct GlobalGameData *gameData);

void waitForFirstCardToBeClicked(struct Input *In, struct GlobalGameData *gameData);

void switchToSecondCardPicking(struct GlobalGameData *gameData);

void waitForSecondCardToBeClicked(SDL_Renderer *renderer, struct Input *in, struct GlobalGameData *gameData);

void testIfRevealedCardsAreTwins(struct Input *in, struct GlobalGameData *gameData);

void displayTextAccordinglyOfPickedCards(struct GlobalGameData *gameData);

void turnBackCardsWithSpaceBar(struct Input *in, struct GlobalGameData *gameData);

void removeCardsFromBoardBecauseTheyreTwins(struct GlobalGameData *gameData);

void checkIfGameFinished(SDL_Renderer *renderer, struct Input *in, struct GlobalGameData *gameData);

bool isGameFinished(const struct GlobalGameData *gameData);

void quitGame(const struct Input *in, bool *quit);

void handleReplay(SDL_Renderer *renderer, struct Input *in, struct GlobalGameData *gameData);

void determineSelectedCardIndex(const struct Input *in, struct GlobalGameData *gameData, unsigned numeroCarte);

bool isCardPicked(const struct Input *in, int jCardsRow, int iCardsColumn);

bool hasCardBeenRevealed(const struct GlobalGameData *gameData, int jCardRow, int iCardColumn);

#endif //H_CONTEXTS
