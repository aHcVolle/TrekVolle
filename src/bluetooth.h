#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <pebble.h>
#include "mainwindow.h"
#include "configuration.h"

bool m_b_Bluetooth_VibrationEnabled;

void Bluetooth_Init();
void Bluetooth_DeInit();
void Bluetooth_Redraw();
#endif