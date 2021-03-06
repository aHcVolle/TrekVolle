#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <pebble.h>
#include "gbitmap_color_palette_manipulator.h"
#include "configuration.h"
#include "battery.h"

//#define DEBUG_ENABLED

#ifdef DEBUG_ENABLED
   #define DEBUG_MAINWINDOW
#endif

#ifdef DEBUG_ENABLED
   //#define DEBUG_IMAGEREDRAW
#endif

#if defined(PBL_PLATFORM_APLITE) || defined(PBL_PLATFORM_BASALT) || defined(PBL_PLATFORM_DIORITE) || defined(PBL_PLATFORM_CHALK)
 #define ICON_SIZE 16
#else
 #define ICON_SIZE 20
#endif



#if defined(PBL_PLATFORM_DIORITE) || defined(PBL_PLATFORM_EMERY)
 #define HAS_HEARTRATE
#endif


// Heap fragmentation help
#define PNG_BUFFER_SIZE 600
uint8_t* ui_PNG_Loadbuffer;

// Structures to hold all image informations
struct ImageData
{
   BitmapLayer* thisLayer;
   GBitmap*     thisBitmap;
   char s_Name[5];
};

struct ImageData m_Image_BatteryPebble;
struct ImageData m_Image_BatteryPhone;
struct ImageData m_Image_Network;
struct ImageData m_Image_Weather;
struct ImageData m_Image_Steps;
#if defined(HAS_HEARTRATE)
struct ImageData m_Image_Heart;
#endif
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
GColor Color_ClockHour;
GColor Color_ClockMin;

// Functions used in other files
void show_mainwindow(void);
void hide_mainwindow(void);
void show_PhoneBattery(bool show);
void show_ConnectionSymbols(bool show);
void show_HeartRate(bool show);
void Color_SetTextColor();
void Color_SetImageColor();

void Redraw_Image(struct ImageData* Image, int ImageID, GColor Color);
void Refresh_Display(void);

// Functions to return all the text pointers
TextLayer* GetStepTextLayer();
#if defined(HAS_HEARTRATE)
TextLayer* GetHeartTextLayer();
#endif
TextLayer* GetTimeHourTextLayer();
TextLayer* GetTimeMinuteTextLayer();
TextLayer* GetDateTextLayer();
TextLayer* GetDayTextLayer();
TextLayer* GetBatteryTextLayerPebble();
TextLayer* GetBatteryTextLayerPhone();
TextLayer* GetWeatherTextLayer();
#endif