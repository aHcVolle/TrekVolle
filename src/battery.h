#ifndef BATTERY_H
#define BATTERY_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"

void InitBattery();
void DeInitBattery();
void RedrawPhoneBattery();
void RedrawPebbleBattery();
void RedrawBattery();
void HandleBatteryReply(Tuple *batterycharge_tuple,Tuple *batterystate_tuple);
#endif