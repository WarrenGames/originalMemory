#ifndef TIME_DELAY_STRUCT_H
#define TIME_DELAY_STRUCT_H

#include "SDL_version.h"

struct Temporisation
{
	#if SDL_MINOR_VERSION == 0 && SDL_PATCHLEVEL < 18
		unsigned current;
		unsigned precedent;
	#else
		Uint64 current;
		Uint64 precedent;
	#endif
};

#endif //TIME_DELAY_STRUCT_H