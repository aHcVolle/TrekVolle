#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"
#include "bluetooth.h"
#include "weather.h"
#include "network.h"
#include "timer.h"

void HandleBackgroundColor(int RGB);
void HandleTextColor(int RGB);
void HandleImageColor(int RGB);
void HandleWindowColor(int RGB);
void HandleChargingColor(int RGB);
void HandleErrorColor(int RGB);
void HandleBatteryLowColor(int RGB);
void HandleTemperatureInCelcius(bool b_TemperatureInCelcius);
void HandleClock24h(bool b_Clock24h);
void HandleDateStyle(int i_DateStyle);
void HandleNetworkRefreshTime(int i_NetworkRefreshTime);

void LoadConfigFromStorage();
void SaveConfigToStorage();
void LoadDefaultConfig();

#endif