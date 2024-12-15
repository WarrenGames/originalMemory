#ifndef LOAD_GAME_GRAPHICS_H
#define LOAD_GAME_GRAPHICS_H

#include "common/comboTextureStruct.h"
#include "common/defines.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include <stdio.h>

struct CardsGraphics;
struct ComboTexture;

void initializeSDL_Textures(struct CardsGraphics *graphics);

void loadGraphicsMain(FILE *gameLogs, SDL_Renderer *renderer, struct CardsGraphics *graphics, unsigned pairNumber);

void loadCardsFacesTextures(FILE *gameLog, SDL_Renderer *renderer, SDL_Texture ***textureArray, unsigned pairNumber);

void loadTextsTextures(FILE *gameLog, SDL_Renderer *renderer, struct ComboTexture tabTextes[]);

void loadSingleTextTexture(FILE *gameLog, SDL_Renderer *renderer, struct ComboTexture *textTexture, const char *text, TTF_Font *font, 
							const SDL_Color color);

void computeTriesNumber(SDL_Renderer *renderer, struct ComboTexture *selectNumber, unsigned int drawNumber, TTF_Font *font);

void freeAllGraphics(struct CardsGraphics *Graphics, unsigned pairNumber);

void freeCardsFaces(struct CardsGraphics *Graphics, unsigned pairNumber);

void freeCardsFacesArray(struct CardsGraphics *Graphics);

void freeTextToDisplay(struct ComboTexture (*textToDisplay)[DISPLAY_MAX]);

#endif //LOAD_GAME_GRAPHICS_H