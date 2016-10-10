#ifndef HEALTH_H
#define HEALTH_H

#include <pebble.h>
#include "mainwindow.h"

#ifdef DEBUG_ENABLED
   #define DEBUG_HEALTH
#endif

#ifdef DEBUG_ENABLED
   #define DEBUG_STEPCOUNT
#endif

#ifdef DEBUG_ENABLED
   #define DEBUG_HEARTRATE
#endif

// Functions used in other files
void Health_Init();
void Health_DeInit();
void Health_GetMovementData(void);
void Health_GetHeartRateData(void);
#endif