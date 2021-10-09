#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H

#include "common/comboTextureStruct.h"
#include "SDL.h"

struct ComboTexture;
struct GlobalGameData;

void displayText(SDL_Renderer *renderer, struct GlobalGameData *gameData);

void initRect(struct GlobalGameData *gameData);

void dispGameStatus(SDL_Renderer *renderer, struct GlobalGameData *gameData);

void dispWhatAPity(SDL_Renderer *renderer, struct ComboTexture textTextures[], SDL_Rect *rect);

void dispWellDone(SDL_Renderer *renderer, struct ComboTexture textTextures[], SDL_Rect *rect);

void dispGameFinished(SDL_Renderer *renderer, struct ComboTexture textTextures[], SDL_Rect *rect);

void dispCardsDrawCount(SDL_Renderer *renderer, struct ComboTexture *drawCountTextTexture, SDL_Rect *rect);

void dispReplayButton(SDL_Renderer *renderer, SDL_Texture *replayButton, SDL_Rect *rectMemory);

void dispFinalDrawCount(SDL_Renderer *renderer, struct ComboTexture *piocheNumber);

#endif //DISPLAY_TEXT_H