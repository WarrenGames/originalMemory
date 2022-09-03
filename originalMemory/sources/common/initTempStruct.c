#include "common/initTempStruct.h"
#include "common/timeDelayStruct.h"
#include "SDL_timer.h"
#include "SDL_version.h"

bool hasTimeElapsed(struct Temporisation* delay, unsigned elapsedTime)
{
	#if SDL_MINOR_VERSION == 0 && SDL_PATCHLEVEL < 18
		delay->current = SDL_GetTicks();
	#else
		delay->current = SDL_GetTicks64();
	#endif
	
	return delay->current - delay->precedent >= elapsedTime;
}

void joinTimePoints(struct Temporisation* delay)
{
	delay->precedent = delay->current;
}

void initDelayStruct(struct Temporisation* delay)
{
	#if SDL_MINOR_VERSION == 0 && SDL_PATCHLEVEL < 18
		delay->current = SDL_GetTicks();
		delay->precedent = SDL_GetTicks();
	#else
		delay->current = SDL_GetTicks64();
		delay->precedent = SDL_GetTicks64();
	#endif
}