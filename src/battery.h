#ifndef BATTERY_H
#define BATTERY_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"

#ifdef DEBUG_ENABLED
   #define DEBUG_BATTERY
#endif

#ifdef DEBUG_ENABLED
   #define DEBUG_BATTERY
#endif

#define DEBUG_BATTERY

// Battery struct
struct BatteryData
{
   TextLayer* l_Text;
   struct ImageData* p_ImageData; 
   int i_BatteryLevel;
   bool b_ChargingState;
   bool b_FirstValue;
   char s_Text[5];
   GColor c_Color;
   int i_ImageID;
};

// Functions used in other files
void Battery_Init();
void Battery_Deinit();
void Battery_RedrawAll();
void Battery_Handle_Phone(int i_BatteryLevel,bool b_ChargingState);
void Battery_RequestPhone();
#endif