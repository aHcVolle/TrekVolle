#ifndef TIMER_H
#define TIMER_H
#include <pebble.h>
#include "mainwindow.h"
#include "weather.h"
#include "network.h"

#define DATE_DD_MM_YY 0
#define DATE_YY_MM_DD 1
#define DATE_MM_DD_YY 2

int DateStyle;
bool Clock24h;

void RedrawTime();
void InitTimer();
void DeInitTimer();
#endif