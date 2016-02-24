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
#define DEBUG_STEPCOUNT
// Functions used in other files
void Health_Init();
void Health_DeInit();
#endif