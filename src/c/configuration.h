#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"
#include "bluetooth.h"
#include "weather.h"
#include "network.h"
#include "clock.h"
#include "acceleration.h"

#ifdef DEBUG_ENABLED
   #define DEBUG_CONFIGURATION
#endif


// Functions used in other files
void WriteInt(int Key, int Value);
void WriteBool(int Key, bool Value);
void WriteString(int Key, const char* String);


void LoadConfigFromStorage();
void SaveConfigToStorage();
void LoadDefaultConfig();

#endif