#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <pebble.h>
#include "mainwindow.h"
#include "configuration.h"
#include "gbitmap_color_palette_manipulator.h"

void Bluetooth_Init();
void Bluetooth_DeInit();
void Bluetooth_Redraw();
#endif