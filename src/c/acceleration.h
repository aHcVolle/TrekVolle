#ifndef ACCELERATION_H
#define ACCELERATION_H

#include <pebble.h>
#include "weather.h"
#include "health.h"

#ifdef DEBUG_ENABLED
   #define DEBUG_ACCELERATION
#endif
// Var to control the accelerometer state
bool m_b_Acceleration_Enabled;

// Functions used in other files
void Acceleration_Init(void);
void Acceleration_DeInit(void);

#endif
