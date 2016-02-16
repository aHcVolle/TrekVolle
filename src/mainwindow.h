#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <pebble.h>
#include "gbitmap_color_palette_manipulator.h"
#include "configuration.h"
#include "battery.h"

// Variables to store the configurated colors
GColor Color_Background;
GColor Color_Text;
GColor Color_Image;
GColor Color_Window;
GColor Color_Charging;
GColor Color_Error;
GColor Color_BatteryLow;

// Functions used in other files
void show_mainwindow(void);
void hide_mainwindow(void);
void show_PhoneBattery(bool show);
void Color_SetTextColor();
void Color_SetImageColor();

void Redraw_Image(BitmapLayer* l_Image, GBitmap* Bitmap, int ImageID, GColor Color);

// Functions to return all the image pointers
BitmapLayer* GetWeatherImageLayer();
BitmapLayer* GetBluetoothImageLayer();
BitmapLayer* GetNetworkImageLayer();
BitmapLayer* GetBatteryImageLayerPebble();
BitmapLayer* GetBatteryImageLayerPhone();

TextLayer* GetStepTextLayer();
TextLayer* GetTimeTextLayer();
TextLayer* GetDateTextLayer();
TextLayer* GetDayTextLayer();
TextLayer* GetBatteryTextLayerPebble();
TextLayer* GetBatteryTextLayerPhone();
TextLayer* GetWeatherTextLayer();

#endif