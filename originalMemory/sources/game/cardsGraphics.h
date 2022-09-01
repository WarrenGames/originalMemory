#ifndef CARDS_GRAPHICS_STRUCTURE_DEFINITION_H
#define CARDS_GRAPHICS_STRUCTURE_DEFINITION_H

#include "common/comboTextureStruct.h"
#include "common/defines.h"
#include "SDL.h"
#include "SDL_ttf.h"

struct CardsGraphics
{
	TTF_Font *arialFont;
	SDL_Texture **cardsFaces;
	SDL_Texture *cardsBack;
	struct ComboTexture textToDisplay[DISPLAY_MAX];
	struct ComboTexture drawingCountText;
	SDL_Texture *replayButton;
	SDL_Rect drawingRect;
};

#endif //CARDS_GRAPHICS_STRUCTURE_DEFINITION_H