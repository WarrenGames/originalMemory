#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "SDL.h"
#include <stdbool.h>
#include <stdio.h>

void runGame();

FILE* initializeLogFile(const char* company, const char* gameName, const char* logFileName);

void handleSDL2Modules(FILE *gameLog);

void initializeSDL2(FILE *gameLog, bool *initSDL2);

void initializeTTF2(FILE *gameLog, bool *initTTF2);

void SDL2_Quit(bool initSDL2);

void TTF2_Quit(bool initTTF2);

SDL_Window* loadAndLogWindow(FILE *gameLog);

SDL_Renderer* loadAndLogRenderer(FILE *gameLog, SDL_Window *window);

void setScreenDefinition(FILE *gameLog, bool isSDL2initialized, bool isTTF2initialized);

void destroyRendererIfAny(SDL_Renderer *renderer);

void destroyWindowIfAny(SDL_Window *window);

void runGameIfContextInitialized(FILE *gameLog, SDL_Renderer *renderer, SDL_Window *window);

void setWindowIcon(FILE *gameLog, SDL_Window *window, const char *textureFilePath);

#endif //INITIALIZE_H