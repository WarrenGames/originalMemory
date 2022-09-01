#include "mainMenu/levelButtons.h"
#include "mainMenu/mainMenuStructs.h"
#include "common/loadComboTexture.h"
#include "common/initTempStruct.h"
#include "common/defines.h"
#include <assert.h>

void initializeMainMenuGraphics(FILE *gameLog, SDL_Renderer *renderer, struct MainMenuGraphics *graphics)
{
	initializeMainMenuButtons(gameLog, renderer, graphics);
	initializeMainMenuTitle(gameLog, renderer, graphics);
	graphics->titlePosition.x = SCREENW / 2;
	graphics->titlePosition.y = SQUARE_SIZE;
	initializeMainMenuVignettesTextures(gameLog, renderer, graphics);
	initializeButtonsPositions(graphics);
	graphics->currentVignette = VIGN_NE;
	initDelayStruct(&graphics->timeDelay);
	initDelayStruct(&graphics->drawDelay);
	initializeVignetteData(&graphics->vignettesInfos[VIGN_NO], SQUARE_SIZE * 2, SQUARE_SIZE * 2 );
	initializeVignetteData(&graphics->vignettesInfos[VIGN_NE], SCREENW - SQUARE_SIZE * 2, SQUARE_SIZE * 2 );
	initializeVignetteData(&graphics->vignettesInfos[VIGN_SO], SQUARE_SIZE * 2, SCREENH - SQUARE_SIZE * 2 );
	initializeVignetteData(&graphics->vignettesInfos[VIGN_SE], SCREENW - SQUARE_SIZE * 2, SCREENH - SQUARE_SIZE * 2 );
}

void initializeMainMenuButtons(FILE *gameLog, SDL_Renderer *renderer, struct MainMenuGraphics *graphics)
{
	loadComboTextures(gameLog, renderer, "textures/btnEasy.png", &graphics->skillButtons[BTN_EASY] );
	loadComboTextures(gameLog, renderer, "textures/btnAverage.png", &graphics->skillButtons[BTN_MEDIUM] );
	loadComboTextures(gameLog, renderer, "textures/btnHard.png", &graphics->skillButtons[BTN_HARD] );
}

void initializeMainMenuTitle(FILE *gameLog, SDL_Renderer *renderer, struct MainMenuGraphics *graphics)
{
	TTF_Font *arial = TTF_OpenFont(ARIAL_FONT_PATH, 48);
	if( arial )
	{
		SDL_Color white = { 255, 255, 255, 255 };
		loadBlendedTextTexture(gameLog, renderer, arial, "Original memory", white, &graphics->title );
		TTF_CloseFont(arial);
	}
}

void initializeMainMenuVignettesTextures(FILE *gameLog, SDL_Renderer *renderer, struct MainMenuGraphics *graphics)
{
	loadComboTextures(gameLog, renderer, "textures/5.png", &graphics->vignettes[VIGN_NE]);
	loadComboTextures(gameLog, renderer, "textures/17.png", &graphics->vignettes[VIGN_NO]);
	loadComboTextures(gameLog, renderer, "textures/43.png", &graphics->vignettes[VIGN_SO]);
	loadComboTextures(gameLog, renderer, "textures/53.png", &graphics->vignettes[VIGN_SE]);
	loadComboTextures(gameLog, renderer, "textures/back.png", &graphics->cardBack);
}

void initializeVignetteData(struct VignetteInfos *vignetteData, int xPosition, int yPosition)
{
	vignetteData->position.x = xPosition;
	vignetteData->position.y = yPosition;
	vignetteData->phase = VIGN_PHASE_SHOW_REAL;
	vignetteData->side = VIGN_SIDE_RECTO;
	vignetteData->width = SQUARE_SIZE;
}

void initializeButtonsPositions(struct MainMenuGraphics *graphics)
{
	graphics->buttonsPositions[BTN_EASY].x = SCREENW / 2;
	graphics->buttonsPositions[BTN_EASY].y = SCREENH - SQUARE_SIZE * 7;
	graphics->buttonsPositions[BTN_MEDIUM].x = SCREENW / 2;
	graphics->buttonsPositions[BTN_MEDIUM].y = SCREENH - SQUARE_SIZE * 5;
	graphics->buttonsPositions[BTN_HARD].x = SCREENW / 2;
	graphics->buttonsPositions[BTN_HARD].y = SCREENH - SQUARE_SIZE * 3;
}

void freeMainMenuRessources(struct MainMenuGraphics *graphics)
{
	freeMainMenuButtons(graphics);
	freeMainMenuVignettes(graphics);
	freeComboTextureIfAny(&graphics->title);
	freeComboTextureIfAny(&graphics->cardBack);
}

void freeMainMenuButtons(struct MainMenuGraphics *graphics)
{
	for( size_t i = 0 ; i < BTN_MAX ; ++i )
	{
		freeComboTextureIfAny(&graphics->skillButtons[i]);
	}
}

void freeMainMenuVignettes(struct MainMenuGraphics *graphics)
{
	for( size_t i = 0 ; i < VIGN_MAX ; ++i )
	{
		freeComboTextureIfAny(&graphics->vignettes[i]);
	}
}

void updateVignettesAnimation(struct MainMenuGraphics *graphics)
{
	assert( graphics->currentVignette < VIGN_MAX );
	switch( graphics->vignettesInfos[graphics->currentVignette].phase )
	{
		case VIGN_PHASE_SHOW_REAL: 
			startHidingSequence(graphics);
			break;
		case VIGN_PHASE_HIDE: 
			hideCurrentVignette(graphics);
			break;
		case VIGN_PHASE_SHOW_HIDDEN:
			startRevealSequence(graphics);
			break;
		case VIGN_PHASE_REVEAL:
			showCurrentVignette(graphics);
			break;
	}
}

void hideCurrentVignette(struct MainMenuGraphics *graphics)
{
	if( hasTimeElapsed(&graphics->timeDelay, VIGNETTES_ANIMATION_DELAY) )
	{
		if( VIGN_SIDE_RECTO == graphics->vignettesInfos[graphics->currentVignette].side )
		{
			graphics->vignettesInfos[graphics->currentVignette].width--;
			changeSideToVersoIfAny(graphics->vignettesInfos[graphics->currentVignette].width, &graphics->vignettesInfos[graphics->currentVignette].side);
		}
		else if( VIGN_SIDE_VERSO == graphics->vignettesInfos[graphics->currentVignette].side )
		{
			graphics->vignettesInfos[graphics->currentVignette].width++;
			updateIfHidingFinished(&graphics->vignettesInfos[graphics->currentVignette], &graphics->currentVignette);
		}
		joinTimePoints(&graphics->timeDelay);
	}
}

void showCurrentVignette(struct MainMenuGraphics *graphics)
{
	if( hasTimeElapsed(&graphics->timeDelay, VIGNETTES_ANIMATION_DELAY) )
	{
		if( VIGN_SIDE_RECTO == graphics->vignettesInfos[graphics->currentVignette].side )
		{
			graphics->vignettesInfos[graphics->currentVignette].width++;
			updateIfRevealFinished(&graphics->vignettesInfos[graphics->currentVignette], &graphics->currentVignette);
		}
		else if( VIGN_SIDE_VERSO == graphics->vignettesInfos[graphics->currentVignette].side )
		{
			graphics->vignettesInfos[graphics->currentVignette].width--;
			changeSideToRectoIfAny(graphics->vignettesInfos[graphics->currentVignette].width, &graphics->vignettesInfos[graphics->currentVignette].side);
		}
		joinTimePoints(&graphics->timeDelay);
	}
}

void changeSideToRectoIfAny(int width, unsigned *side)
{
	if( 0 == width && VIGN_SIDE_VERSO == *side )
	{
		*side = VIGN_SIDE_RECTO;
	}
}

void changeSideToVersoIfAny(int width, unsigned *side)
{
	if( 0 == width && VIGN_SIDE_RECTO == *side )
	{
		*side = VIGN_SIDE_VERSO;
	}
}

void gotoNextVignette(unsigned *currentVignette)
{
	if( *currentVignette + 1 < VIGN_MAX )
	{
		(*currentVignette)++;
	}
	else{
		*currentVignette = 0;
	}
}

void updateIfHidingFinished(struct VignetteInfos *vignette, unsigned *currentVignette)
{
	if( VIGN_PHASE_HIDE == vignette->phase && SQUARE_SIZE == vignette->width && VIGN_SIDE_VERSO == vignette->side )
	{
		vignette->phase = VIGN_PHASE_SHOW_HIDDEN;
		gotoNextVignette(currentVignette);
	}
}

void updateIfRevealFinished(struct VignetteInfos *vignette, unsigned *currentVignette)
{
	if( VIGN_PHASE_REVEAL == vignette->phase && SQUARE_SIZE == vignette->width && VIGN_SIDE_RECTO == vignette->side )
	{
		vignette->phase = VIGN_PHASE_SHOW_REAL;
		gotoNextVignette(currentVignette);
	}
}

void startHidingSequence(struct MainMenuGraphics *graphics)
{
	if( VIGN_PHASE_SHOW_REAL == graphics->vignettesInfos[graphics->currentVignette].phase )
	{
		graphics->vignettesInfos[graphics->currentVignette].phase = VIGN_PHASE_HIDE;
	}
}

void startRevealSequence(struct MainMenuGraphics *graphics)
{
	if( VIGN_PHASE_SHOW_HIDDEN == graphics->vignettesInfos[graphics->currentVignette].phase )
	{
		graphics->vignettesInfos[graphics->currentVignette].phase = VIGN_PHASE_REVEAL;
	}
}
