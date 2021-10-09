#include "common/initTempStruct.h"
#include "common/timeDelayStruct.h"
#include "SDL.h"

bool hasTimeElapsed(struct Temporisation* delay, unsigned elapsedTime)
{
	delay->current = SDL_GetTicks();
	return delay->current - delay->precedent >= elapsedTime;
}

void joinTimePoints(struct Temporisation* delay)
{
	delay->precedent = delay->current;
}

void initDelayStruct(struct Temporisation* delay)
{
	delay->current = SDL_GetTicks();
	delay->precedent = SDL_GetTicks();
}