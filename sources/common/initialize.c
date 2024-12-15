#include "common/initialize.h"
#include "mainMenu/instructionsMenuPrincipal.h"
#include "common/defines.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string.h>

void runGame()
{
	FILE *gameLog = initializeLogFile("The games of the warren", "Original Memory", "gameLogs.txt");
	
	if( gameLog )
	{
		handleSDL2Modules(gameLog);
		fclose(gameLog);
	}
	else{
		printf("Error: couldn't open 'gameLogs.txt' file\n");
	}
}

FILE* initializeLogFile(const char* company, const char* gameName, const char* logFileName)
{
	char *base_path = SDL_GetPrefPath(company, gameName);
	
	if( base_path )
	{
		char completeLogFilePath[2048] = "";
		strcpy(completeLogFilePath, base_path);
		strcat(completeLogFilePath, logFileName);
		SDL_free(base_path);
		return fopen(completeLogFilePath, "w+");
	}
	else{
		return NULL;
	}
}

void handleSDL2Modules(FILE *gameLog)
{
	bool isSDL2initialized = false;
	initializeSDL2(gameLog, &isSDL2initialized);
		
	bool isTTF2initialized = false;
	initializeTTF2(gameLog, &isTTF2initialized);

	setScreenDefinition(gameLog, isSDL2initialized, isTTF2initialized);

	TTF2_Quit(isTTF2initialized);
		
	SDL2_Quit(isSDL2initialized);
}

void initializeSDL2(FILE *gameLog, bool *initSDL2)
{
	if( SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		fprintf(gameLog, "Error initialization SDL2: %s\n", SDL_GetError() );
		*initSDL2 = false;
	}
	else{
		fprintf(gameLog, "SDL2 was properly initialized\n");
		*initSDL2 = true;
	}
}

void initializeTTF2(FILE *gameLog, bool *initTTF2)
{
	if( TTF_Init() == -1 )
	{
		fprintf(gameLog, "Error initialization SDL2_TTF: %s\n", TTF_GetError() );
		*initTTF2 = false;
	}
	else{
		fprintf(gameLog, "SDL2 TTF was properly initialized\n");
		*initTTF2 = true;
	}
}

void SDL2_Quit(bool initSDL2)
{
	if( initSDL2 == true )
		SDL_Quit();
}

void TTF2_Quit(bool initTTF2)
{
	if( initTTF2 == true )
		TTF_Quit();
}

SDL_Window* loadAndLogWindow(FILE *gameLog)
{
	SDL_Window *window = SDL_CreateWindow("Original Memory - jeu de mémoire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREENW, SCREENH, 0);
	
	if( window == NULL )
	{
		fprintf(gameLog, "Error initialization SDL2: %s\n", SDL_GetError() );
	}
	return window;
}

SDL_Renderer* loadAndLogRenderer(FILE *gameLog, SDL_Window *window)
{
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if( renderer == NULL )
	{
		fprintf(gameLog, "Error initialization SDL2: %s\n", SDL_GetError() );
	}
	return renderer;
}

void setScreenDefinition(FILE *gameLog, bool isSDL2initialized, bool isTTF2initialized)
{
	if( isSDL2initialized && isTTF2initialized )
	{
		SDL_Window *window = loadAndLogWindow(gameLog);
		SDL_Renderer *renderer = loadAndLogRenderer(gameLog, window);
		setWindowIcon(gameLog, window, "textures/5.png");
		runGameIfContextInitialized(gameLog, renderer, window);
		destroyRendererIfAny(&renderer);
		destroyWindowIfAny(&window);
	}
}

void destroyRendererIfAny(SDL_Renderer **renderer)
{
	if( *renderer )
	{
		SDL_DestroyRenderer(*renderer);
		*renderer = NULL;
	}
}

void destroyWindowIfAny(SDL_Window **window)
{
	if( *window )
	{
		SDL_DestroyWindow(*window);
		*window = NULL;
	}
}

void runGameIfContextInitialized(FILE *gameLog, SDL_Renderer *renderer, SDL_Window *window)
{
	if( renderer && window )
	{
		mainMenuContext(gameLog, renderer);
	}
}

void setWindowIcon(FILE *gameLog, SDL_Window *window, const char *textureFilePath)
{
	SDL_Surface *iconSurface = IMG_Load(textureFilePath);
	if( iconSurface )
	{
		SDL_SetWindowIcon(window, iconSurface);
	}
	else{
		fprintf(gameLog, "Error: couldn't load the following texture for the window icon: '%s' ", textureFilePath );
	}
}