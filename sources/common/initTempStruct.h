#ifndef INIT_TEMP_STRUCT_H
#define INIT_TEMP_STRUCT_H

#include <stdbool.h>

struct Temporisation;

bool hasTimeElapsed(struct Temporisation* delay, unsigned elapsedTime);

void joinTimePoints(struct Temporisation* delay);

void initDelayStruct(struct Temporisation* delay);

#endif //INIT_TEMP_STRUCT_H