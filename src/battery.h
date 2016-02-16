#ifndef BATTERY_H
#define BATTERY_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"

// Functions used in other files
void Battery_Init();
void Battery_Deinit();
void Battery_RedrawAll();
void Battery_Handle_Phone(int i_BatteryLevel,bool b_ChargingState);
#endif