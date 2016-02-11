#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <pebble.h>
#include "weather.h"
#include "network.h"
#include "battery.h"
#include "configuration.h"

#define KEY_TEMPERATURE 0
#define KEY_CONDITIONS 1
#define KEY_ICON 2
#define KEY_LOCATION 3

#define KEY_ONLINE 4

#define KEY_BATTERY_CHARGE 5
#define KEY_BATTERY_STATE 6

#define KEY_COLOR_BACKGROUND 7
#define KEY_COLOR_TEXT 8
#define KEY_COLOR_IMAGE 9
#define KEY_COLOR_WINDOW 10
#define KEY_COLOR_CHARGING 11
#define KEY_COLOR_ERROR 12 
#define KEY_COLOR_BATTERYLOW 13

#define KEY_TEMPERATURE_CELCIUS 14
#define KEY_CLOCK_24H 15
#define KEY_DATE_STYLE 16
#define KEY_NETWORK_REFRESHTIME 17

void InitCommunication();
void DeInitCommunication();



#endif