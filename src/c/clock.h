#ifndef CLOCK_H
#define CLOCK_H

#include <pebble.h>
#include "mainwindow.h"
#include "weather.h"
#include "network.h"
#include "bluetooth.h"
#include "health.h"

#ifdef DEBUG_ENABLED
   #define DEBUG_CLOCK
#endif

// The different date options
#define DATE_DD_MM_YY 0
#define DATE_YY_MM_DD 1
#define DATE_MM_DD_YY 2

#define DAY_DAYOFYEAR 0
#define DAY_TEMPHIGHLOW 1

// Vars used in other files
int m_i_Clock_DateStyle;
bool m_b_Clock_Clock24h;
int m_i_Clock_DayOfYear;

bool m_b_Clock_Sleep;
bool m_b_Clock_SleepEnabled;

int m_i_Weather_Counter;
int m_i_Network_Counter;

int m_i_Clock_Sleep_Begin;
int m_i_Clock_Sleep_End;

// Functions used in other files
void Clock_Redraw();
void Clock_Init();
void Clock_DeInit();

#endif
