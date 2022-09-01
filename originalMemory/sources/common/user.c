#include "common/user.h"
#include "common/defines.h"

void inputInitialisation(struct Input *in)
{
	in->xmouse = -1;
	in->ymouse = -1;
	in->spaceBar = false;
	in->escape = false;

	for(unsigned i = 0 ; i < 8 ; ++i)
	{
		in->mouseButtons[i] = false;
	}

	in->SDL_Quit = false;
}

void updateEvents(struct Input *in)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				setKeyState(event.key.keysym.sym, SDLK_SPACE, &in->spaceBar, true);
				setKeyState(event.key.keysym.sym, SDLK_ESCAPE, &in->escape, true);
				break;
			case SDL_KEYUP:
				setKeyState(event.key.keysym.sym, SDLK_SPACE, &in->spaceBar, false);
				setKeyState(event.key.keysym.sym, SDLK_ESCAPE, &in->escape, false);
				break;
			case SDL_MOUSEMOTION:
				in->xmouse = event.motion.x;
				in->ymouse = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				in->mouseButtons[event.button.button] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				in->mouseButtons[event.button.button] = false;
				break;
			case SDL_QUIT:
				in->SDL_Quit = true;
				break;
		}
	}
}

void setKeyState(SDL_Keycode keycode, SDL_Keycode ref, bool *stateVal, bool value)
{
	if( keycode == ref )
	{
		*stateVal = value;
	}
}