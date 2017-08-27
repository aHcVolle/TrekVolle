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


// Display states
enum HealthDisplayStates
{
   DISPLAY_SPORT,
   DISPLAY_GLOBAL
};

#if defined(PBL_HEALTH)

int m_i_Sport_LastStepCount;
int m_i_Sport_LastDistance;

int m_i_Sport_Duration;
int m_i_Sport_Distance;
int m_i_Sport_DistanceDifference;

int m_i_Health_DisplayState;

int m_i_Sport_Step_Threshold;
#endif

// Functions used in other files
void Health_Init();
void Health_DeInit();
void Health_GetMovementData(void);
void Health_GetHeartRateData(void);
#endif
