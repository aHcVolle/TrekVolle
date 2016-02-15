#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"
#include "bluetooth.h"
#include "weather.h"
#include "network.h"
#include "timer.h"

bool m_b_Bluetooth_VibrationEnabled;
bool m_b_Network_VibrationEnabled;


void HandleTemperatureInCelcius(bool b_TemperatureInCelcius);
void HandleClock24h(bool b_Clock24h);
void HandleDateStyle(int i_DateStyle);
void HandleNetworkRefreshTime(int i_NetworkRefreshTime);
void HandleBluetoothVibrationEnabled(bool b_VibrationEnabled);
void HandleNetworkVibrationEnabled(bool b_VibrationEnabled);


void LoadConfigFromStorage();
void SaveConfigToStorage();
void LoadDefaultConfig();

#endif