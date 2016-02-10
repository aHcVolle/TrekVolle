#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"
#include "bluetooth.h"
#include "weather.h"
#include "network.h"

void HandleBackgroundColor(int RGB);
void HandleTextColor(int RGB);
void HandleImageColor(int RGB);
void HandleWindowColor(int RGB);
void HandleChargingColor(int RGB);
void HandleErrorColor(int RGB);
void HandleBatteryLowColor(int RGB);


void LoadConfigFromStorage();
void SaveConfigToStorage();
void LoadDefaultConfig();

#endif