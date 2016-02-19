#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <pebble.h>
#include "gbitmap_color_palette_manipulator.h"
#include "configuration.h"
#include "battery.h"


// Heap fragmentation help
#define PNG_BUFFER_SIZE 300
uint8_t* ui_PNG_Loadbuffer;

// Structures to hold all image informations
struct ImageData
{
   BitmapLayer* thisLayer;
   GBitmap*     thisBitmap;
};

struct ImageData m_Image_BatteryPebble;
struct ImageData m_Image_BatteryPhone;
struct ImageData m_Image_Network;
struct ImageData m_Image_Weather;
struct ImageData m_Image_Steps;
struct ImageData m_Image_Background;
struct ImageData m_Image_Bluetooth;

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

void Redraw_Image(struct ImageData* Image, int ImageID, GColor Color);

// Functions to return all the text pointers
TextLayer* GetStepTextLayer();
TextLayer* GetTimeTextLayer();
TextLayer* GetDateTextLayer();
TextLayer* GetDayTextLayer();
TextLayer* GetBatteryTextLayerPebble();
TextLayer* GetBatteryTextLayerPhone();
TextLayer* GetWeatherTextLayer();
#endif