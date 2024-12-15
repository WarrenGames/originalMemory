#ifndef MAIN_MENU_STRUCTS_H
#define MAIN_MENU_STRUCTS_H

#include "common/timeDelayStruct.h"
#include "common/comboTextureStruct.h"
#include "common/positionStruct.h"

enum{VIGN_NO, VIGN_NE, VIGN_SO, VIGN_SE, VIGN_MAX};

enum{BTN_EASY, BTN_MEDIUM, BTN_HARD, BTN_MAX};

enum{ VIGN_PHASE_SHOW_REAL, VIGN_PHASE_HIDE, VIGN_PHASE_SHOW_HIDDEN, VIGN_PHASE_REVEAL };
enum{ VIGN_SIDE_RECTO, VIGN_SIDE_VERSO };

#define VIGNETTES_ANIMATION_DELAY 10


struct VignetteInfos
{
	struct Position position;
	unsigned phase;
	unsigned side;
	int width;
	
};

struct MainMenuGraphics
{
	struct ComboTexture title;
	struct Position titlePosition;
	struct ComboTexture skillButtons[BTN_MAX];
	struct Position buttonsPositions[BTN_MAX];
	struct ComboTexture vignettes[VIGN_MAX];
	struct ComboTexture cardBack;
	unsigned currentVignette;
	struct VignetteInfos vignettesInfos[VIGN_MAX];
	struct Temporisation timeDelay;
	struct Temporisation drawDelay;
	SDL_Rect rect;
};

#endif //MAIN_MENU_STRUCTS_H