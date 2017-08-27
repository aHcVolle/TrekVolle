#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <pebble.h>
#include "mainwindow.h"
#include "configuration.h"
#include "network.h"

#ifdef DEBUG_ENABLED
   #define DEBUG_BLUETOOTH
#endif

// Vars used int other files
bool m_b_Bluetooth_VibrationEnabled;
bool m_b_Bluetooth_ConnectionState;

// Functions used in other files
void Bluetooth_Init();
void Bluetooth_DeInit();
void Bluetooth_Redraw();
#endif
