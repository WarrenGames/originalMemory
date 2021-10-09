#include "displayText.h"
#include "game/globalGameData.h"
#include "common/defines.h"

void displayText(SDL_Renderer *renderer, struct GlobalGameData *gameData)
{
	initRect(gameData);
	dispGameStatus(renderer, gameData);
	dispCardsDrawCount(renderer, &gameData->graphics.drawingCountText, &gameData->graphics.drawingRect);
}

void initRect(struct GlobalGameData *gameData)
{
	gameData->graphics.drawingRect.x = MARGIN;
	gameData->graphics.drawingRect.y = MARGIN + ( gameData->data.cardNumber * 2 / 14 ) * SQUARE_SIZE + MARGIN / 2;
	gameData->graphics.drawingRect.w = 0;
	gameData->graphics.drawingRect.h = 0;
}

void dispGameStatus(SDL_Renderer *renderer, struct GlobalGameData *gameData)
{
	switch( gameData->data.whichTextToDisplay)
	{
		case WHAT_A_PITY:
			dispWhatAPity(renderer, gameData->graphics.textToDisplay, &gameData->graphics.drawingRect);
			break;
		case WELL_DONE:
			dispWellDone(renderer, gameData->graphics.textToDisplay, &gameData->graphics.drawingRect);
			break;
		case GAME_FINISHED:
			dispGameFinished(renderer, gameData->graphics.textToDisplay, &gameData->graphics.drawingRect);
			break;
	}
}

void dispWhatAPity(SDL_Renderer *renderer, struct ComboTexture textToDisplay[], SDL_Rect *rect)
{
	rect->w = textToDisplay[WHAT_A_PITY].w;
	rect->h = textToDisplay[WHAT_A_PITY].h;
	SDL_RenderCopy(renderer, textToDisplay[WHAT_A_PITY].texture, NULL, rect);
	rect->y += SQUARE_SIZE / 2;
	rect->w = textToDisplay[PUSH_SPACE].w;
	rect->h = textToDisplay[PUSH_SPACE].h;
	SDL_RenderCopy(renderer, textToDisplay[PUSH_SPACE].texture, NULL, rect);
}

void dispWellDone(SDL_Renderer *renderer, struct ComboTexture textTextures[], SDL_Rect *rect)
{
	rect->w = textTextures[WELL_DONE].w;
	rect->h = textTextures[WELL_DONE].h;
	SDL_RenderCopy(renderer, textTextures[WELL_DONE].texture, NULL, rect);
	rect->y += SQUARE_SIZE / 2;
	rect->w = textTextures[PUSH_SPACE].w;
	rect->h = textTextures[PUSH_SPACE].h;
	SDL_RenderCopy(renderer, textTextures[PUSH_SPACE].texture, NULL, rect);
}

void dispGameFinished(SDL_Renderer *renderer, struct ComboTexture textTextures[], SDL_Rect *rect)
{
	rect->w = textTextures[GAME_FINISHED].w;
	rect->h = textTextures[GAME_FINISHED].h;
	SDL_RenderCopy(renderer, textTextures[GAME_FINISHED].texture, NULL, rect);
}

void dispCardsDrawCount(SDL_Renderer *renderer, struct ComboTexture *drawCountTextTexture, SDL_Rect *rect)
{
	rect->x = MARGIN;
	rect->y = MARGIN / 2 - drawCountTextTexture->h / 2;
	rect->w = drawCountTextTexture->w;
	rect->h = drawCountTextTexture->h;
	SDL_RenderCopy(renderer, drawCountTextTexture->texture, NULL, rect);
}


void dispReplayButton(SDL_Renderer *renderer, SDL_Texture *replayButton, SDL_Rect *rectMemory)
{
	SDL_Rect rect;
	SDL_QueryTexture(replayButton, NULL, NULL, &rect.w, &rect.h);
	rect.x = SCREENW / 2 - rect.w / 2;
	rect.y = SCREENH / 2 - rect.h / 2;
	SDL_RenderCopy(renderer, replayButton, NULL, &rect);
	
	*rectMemory = rect;
}

void dispFinalDrawCount(SDL_Renderer *renderer, struct ComboTexture *drawNumTextT)
{
	SDL_Rect rect = {SCREENW / 2 - drawNumTextT->w / 2, SQUARE_SIZE * 2 - drawNumTextT->h / 2, drawNumTextT->w, drawNumTextT->h};
	SDL_RenderCopy(renderer, drawNumTextT->texture, NULL, &rect );
}
