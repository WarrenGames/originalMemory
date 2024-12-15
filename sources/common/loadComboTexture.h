#ifndef LOAD_COMBO_TEXTURE_H
#define LOAD_COMBO_TEXTURE_H

#include "SDL_render.h"
#include "SDL_ttf.h"
#include <stdio.h>

struct ComboTexture;
struct Position;

void loadComboTextures(FILE *gameLog, SDL_Renderer *renderer, const char *texturePath, struct ComboTexture *comboTexture);

void loadBlendedTextTexture(FILE *gameLog, SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, struct ComboTexture *comboTexture);

void freeComboTextureIfAny(struct ComboTexture *comboTexture);

void resetComboTextureSize(struct ComboTexture *comboTexture);

void drawComboToCenter(SDL_Renderer *renderer, const struct ComboTexture *comboTexture, const struct Position *centerPosition, SDL_Rect *rect);

#endif //LOAD_COMBO_TEXTURE_H