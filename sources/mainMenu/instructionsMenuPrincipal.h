#ifndef H_INSTRUCTIONS_MAINMENU
#define H_INSTRUCTIONS_MAINMENU

#include "SDL_render.h"
#include <stdio.h>
#include <stdbool.h>

struct Input;
struct MainMenuGraphics;
struct VignetteInfos;
struct ComboTexture;
struct Position;

void mainMenuContext(FILE *gameLog, struct SDL_Renderer *renderer);

void mainMenuMainLoop(FILE *gameLog, struct SDL_Renderer *renderer, struct Input *in, struct MainMenuGraphics *graphics, bool quitMenu);

void updateInterface(FILE *gameLog, SDL_Renderer *renderer, struct Input *in, struct MainMenuGraphics *graphics);

void pollButtons(FILE *gameLog, SDL_Renderer *renderer, struct Input *in, struct MainMenuGraphics *graphics);

void checkButtonClick(FILE *gameLog, SDL_Renderer *renderer, struct Input *in, struct ComboTexture *buttonTexture, struct Position *buttonPosition, unsigned pairNumber);

void drawEverything(SDL_Renderer *renderer, struct MainMenuGraphics *graphics);

void drawTitle(SDL_Renderer *renderer, struct MainMenuGraphics *graphic );

void drawSkillButtons(SDL_Renderer *renderer, struct MainMenuGraphics *graphics);

void drawVignettes(SDL_Renderer *renderer, struct MainMenuGraphics *graphics);

void drawSingleVignette(SDL_Renderer *renderer, struct VignetteInfos *vignette, struct ComboTexture *vignetteTexture, struct ComboTexture *cardBack, SDL_Rect *rect);

void exitMenu(struct Input *in, bool *quitGame);

#endif //H_INSTRUCTIONS_MAINMENU