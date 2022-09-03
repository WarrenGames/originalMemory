#ifndef USER_H
#define USER_H

#include "SDL_keycode.h"
#include "SDL_events.h"
#include <stdbool.h>

struct Input
{
	SDL_Event event;
	int xmouse; 
	int ymouse;
	bool spaceBar;
	bool escape;
	bool mouseButtons[8];
	bool SDL_Quit;
};

void inputInitialisation(struct Input *in);

void updateEvents(struct Input *in);

void setKeyState(SDL_Keycode keycode, SDL_Keycode ref, bool *stateVal, bool value);

#endif //USER_H
