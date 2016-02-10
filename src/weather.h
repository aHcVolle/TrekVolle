#ifndef WEATHER_H
#define WEATHER_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"
#include "gbitmap_color_palette_manipulator.h"

enum DisplayStates
{
   DISPLAY_CONDITIONS,
   DISPLAY_LOCATION
};

int DisplayState;
bool LastWeatherUpdateWasOK;

void HandleWeather(Tuple *Temperature_tuple,Tuple *Condition_tuple,Tuple *Location_tuple,Tuple *Image_tuple);

void InitWeather();
void DeInitWeather();
void RequestWeather();

void RedrawWeatherText();
void RedrawWeatherImage();
void RedrawWeather();
int imagename2resid(char* imagename);
#endif