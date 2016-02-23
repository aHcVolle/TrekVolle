#ifndef WEATHER_H
#define WEATHER_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"

#ifdef DEBUG_ENABLED
   #define DEBUG_WEATHER
#endif

// Display states
enum DisplayStates
{
   DISPLAY_CONDITIONS,
   DISPLAY_LOCATION
};

// Variables used in other files
int m_i_Weather_DisplayState;
bool m_b_Weather_LastUpdateWasOK;
bool m_b_Weather_RetryUpdate;
bool m_b_Weather_TemperatureInCelcius;
int m_i_Weather_RefreshTime;

int m_i_Weather_Temperature_Min;
int m_i_Weather_Temperature_Max;

// Functions used in other files
void Weather_Handle(Tuple *Temperature_tuple,Tuple *Condition_tuple,Tuple *Location_tuple,Tuple *Image_tuple);

void Weather_Init();
void Weather_DeInit();
void Weather_Request();

void Weather_RedrawText();
void Weather_RedrawImage();
void Weather_Redraw();
int  Weather_GetImageID(char* s_WeatherImageName);
#endif