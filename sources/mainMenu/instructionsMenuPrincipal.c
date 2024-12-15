#include "mainMenu/instructionsMenuPrincipal.h"
#include "mainMenu/mainMenuStructs.h"
#include "mainMenu/levelButtons.h"
#include "game/gameContext.h"
#include "common/initTempStruct.h"
#include "common/loadComboTexture.h"
#include "common/user.h"
#include "common/defines.h"
#include <assert.h>

void mainMenuContext(FILE *gameLog, SDL_Renderer *renderer)
{
	struct MainMenuGraphics graphics;
	initializeMainMenuGraphics(gameLog, renderer, &graphics);
	bool quitMenu = false;
	struct Input in;
	inputInitialisation(&in);
	
	mainMenuMainLoop(gameLog, renderer, &in, &graphics, quitMenu);
	
	freeMainMenuRessources(&graphics);
}

void mainMenuMainLoop(FILE *gameLog, struct SDL_Renderer *renderer, struct Input *in, struct MainMenuGraphics *graphics, bool quitMenu)
{
	while( false == quitMenu )
	{
		updateEvents(in);
		updateInterface(gameLog, renderer, in, graphics);
		exitMenu(in, &quitMenu);
		drawEverything(renderer, graphics);
	}
}

void updateInterface(FILE *gameLog, SDL_Renderer *renderer, struct Input *in, struct MainMenuGraphics *graphics)
{
	updateVignettesAnimation(graphics);
	pollButtons(gameLog, renderer, in, graphics);
}

void pollButtons(FILE *gameLog, SDL_Renderer *renderer, struct Input *in, struct MainMenuGraphics *graphics)
{
	checkButtonClick(gameLog, renderer, in, &graphics->skillButtons[EASY_SKILL], &graphics->buttonsPositions[EASY_SKILL], EASY_PAIR_NUMBER);
	checkButtonClick(gameLog, renderer, in, &graphics->skillButtons[MEDIUM_SKILL], &graphics->buttonsPositions[MEDIUM_SKILL], MEDIUM_PAIR_NUMBER);
	checkButtonClick(gameLog, renderer, in, &graphics->skillButtons[HARD_SKILL], &graphics->buttonsPositions[HARD_SKILL], HARD_PAIR_NUMBER);
}

void checkButtonClick(FILE *gameLog, SDL_Renderer *renderer, struct Input *in, struct ComboTexture *buttonTexture, struct Position *buttonPosition, unsigned pairNumber)
{
	if( in->mouseButtons[SDL_BUTTON_LEFT]
		&& in->xmouse >= buttonPosition->x - buttonTexture->w / 2 
		&& in->xmouse < buttonPosition->x + buttonTexture->w / 2 
		&& in->ymouse >= buttonPosition->y - buttonTexture->h / 2
		&& in->ymouse < buttonPosition->y + buttonTexture->h / 2 )
	{
		gameCustomized(gameLog, renderer, in, pairNumber);
	}
}

void drawEverything(SDL_Renderer *renderer, struct MainMenuGraphics *graphics)
{
	if( hasTimeElapsed(&graphics->drawDelay, 16) )
	{
		SDL_SetRenderDrawColor(renderer, 0, 127, 14, 255);
		SDL_RenderClear(renderer);
		drawTitle(renderer, graphics);
		drawSkillButtons(renderer, graphics);
		drawVignettes(renderer, graphics);
		SDL_RenderPresent(renderer);
		joinTimePoints(&graphics->drawDelay);
	}
}

void drawTitle(SDL_Renderer *renderer, struct MainMenuGraphics *graphics)
{
	if( graphics->title.texture )
	{
		drawComboToCenter(renderer, &graphics->title, &graphics->titlePosition, &graphics->rect);
	}
}

void drawSkillButtons(SDL_Renderer *renderer, struct MainMenuGraphics *graphics)
{
	for( unsigned i = 0 ; i < BTN_MAX ; ++i )
	{
		drawComboToCenter(renderer, &graphics->skillButtons[i], &graphics->buttonsPositions[i], &graphics->rect);
	}
}

void drawVignettes(SDL_Renderer *renderer, struct MainMenuGraphics *graphics)
{
	for( int i = 0 ; i < VIGN_MAX ; ++i )
	{
		drawSingleVignette(renderer, &graphics->vignettesInfos[i], &graphics->vignettes[i], &graphics->cardBack, &graphics->rect);
	}
}

void drawSingleVignette(SDL_Renderer *renderer, struct VignetteInfos *vignette, struct ComboTexture *vignetteTexture, struct ComboTexture *cardBack, SDL_Rect *rect)
{
	if( vignetteTexture->texture )
	{
		switch( vignette->side )
		{
			case VIGN_SIDE_RECTO:
				rect->w = vignette->width;
				rect->h = vignetteTexture->h;
				rect->x = vignette->position.x - rect->w / 2;
				rect->y = vignette->position.y - rect->h / 2;
				SDL_RenderCopy(renderer, vignetteTexture->texture, NULL, rect);
				break;
			case VIGN_SIDE_VERSO:
				rect->w = vignette->width;
				rect->h = cardBack->h;
				rect->x = vignette->position.x - rect->w / 2;
				rect->y = vignette->position.y - rect->h / 2;
				SDL_RenderCopy(renderer, cardBack->texture, NULL, rect);
				break;
			default:
				assert( "Error: bad vignette 'side' value" && false );
				break;
		}
	}
}

void exitMenu(struct Input *in, bool *quitGame)
{
	if( in->escape || in->SDL_Quit )
	{
		*quitGame = true;
	}
}
