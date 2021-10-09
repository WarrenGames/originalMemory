#ifndef LEVELBUTTONS_H
#define LEVELBUTTONS_H

#include "SDL.h"
#include <stdio.h>

struct MainMenuGraphics;
struct VignetteInfos;

void initializeMainMenuGraphics(FILE *gameLog, SDL_Renderer *renderer, struct MainMenuGraphics *graphics);

void initializeMainMenuButtons(FILE *gameLog, SDL_Renderer *renderer, struct MainMenuGraphics *graphics);

void initializeMainMenuTitle(FILE *gameLog, SDL_Renderer *renderer, struct MainMenuGraphics *graphics);

void initializeMainMenuVignettesTextures(FILE *gameLog, SDL_Renderer *renderer, struct MainMenuGraphics *graphics);

void initializeVignetteData(struct VignetteInfos *vignetteData, int xPosition, int yPosition);

void initializeButtonsPositions(struct MainMenuGraphics *graphics);

void freeMainMenuRessources(struct MainMenuGraphics *graphics);

void freeMainMenuButtons(struct MainMenuGraphics *graphics);

void freeMainMenuVignettes(struct MainMenuGraphics *graphics);

void updateVignettesAnimation(struct MainMenuGraphics *graphics);

void hideCurrentVignette(struct MainMenuGraphics *graphics);

void showCurrentVignette(struct MainMenuGraphics *graphics);

void changeSideToRectoIfAny(int width, unsigned *side);

void changeSideToVersoIfAny(int width, unsigned *side);

void gotoNextVignette(unsigned *currentVignette);

void updateIfHidingFinished(struct VignetteInfos *vignette, unsigned *currentVignette);

void updateIfRevealFinished(struct VignetteInfos *vignette, unsigned *currentVignette);

void startHidingSequence(struct MainMenuGraphics *graphics);

void startRevealSequence(struct MainMenuGraphics *graphics);

#endif//LEVELBUTTONS_H