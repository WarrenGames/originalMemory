#ifndef LOAD_SDL2_H
#define LOAD_SDL2_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "stdio.h"

SDL_Texture* loadSDLTexture(FILE *gameLog, SDL_Renderer *renderer, const char *texturePath);

void freeTextureIfAllocated(SDL_Texture **texture);

TTF_Font* loadFont(FILE *gameLog, const char *fontPath, unsigned ptSize);

void freeFontIfAllocated(TTF_Font **Font);

#endif //LOAD_SDL2_H