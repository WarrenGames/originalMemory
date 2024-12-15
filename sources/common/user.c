#include "common/user.h"
#include "common/defines.h"

void inputInitialisation(struct Input *in)
{
	in->xmouse = -1;
	in->ymouse = -1;
	in->spaceBar = false;
	in->escape = false;

	for( unsigned i = 0 ; i < 8 ; ++i)
	{
		in->mouseButtons[i] = false;
	}

	in->SDL_Quit = false;
}

void updateEvents(struct Input *in)
{
	while(SDL_PollEvent(&(in->event) ) )
	{
		switch (in->event.type)
		{
			case SDL_KEYDOWN:
				setKeyState(in->event.key.keysym.sym, SDLK_SPACE, &in->spaceBar, true);
				setKeyState(in->event.key.keysym.sym, SDLK_ESCAPE, &in->escape, true);
				break;
			case SDL_KEYUP:
				setKeyState(in->event.key.keysym.sym, SDLK_SPACE, &in->spaceBar, false);
				setKeyState(in->event.key.keysym.sym, SDLK_ESCAPE, &in->escape, false);
				break;
			case SDL_MOUSEMOTION:
				in->xmouse = in->event.motion.x;
				in->ymouse = in->event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				in->mouseButtons[in->event.button.button] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				in->mouseButtons[in->event.button.button] = false;
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