#ifndef CLOCK_H
#define CLOCK_H

#include <pebble.h>
#include "mainwindow.h"
#include "weather.h"
#include "network.h"
#include "bluetooth.h"

// The different date options
#define DATE_DD_MM_YY 0
#define DATE_YY_MM_DD 1
#define DATE_MM_DD_YY 2

// Vars used in other files
int m_i_Clock_DateStyle;
bool m_b_Clock_Clock24h;

bool m_b_Clock_Sleep;
bool m_b_Clock_SleepEnabled;

// Functions used in other files
void Time_Redraw();
void Time_Init();
void Time_DeInit();

#endif