#ifndef ACCELERATION_H
#define ACCELERATION_H

#include <pebble.h>
#include "weather.h"

#ifdef DEBUG_ENABLED
   #define DEBUG_ACCELERATION
#endif

// Functions used in other files
void Acceleration_Init(void);
void Acceleration_DeInit(void);

#endif