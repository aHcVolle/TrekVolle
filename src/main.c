#include <pebble.h>
#include "mainwindow.h"
#include "weather.h"
#include "health.h"
#include "battery.h"
#include "bluetooth.h"
#include "clock.h"
#include "network.h"
#include "communication.h"
#include "acceleration.h"
#include "configuration.h"

static void init() 
{
   m_b_Debug = false;
   
   // UI 
   show_mainwindow();
   // Set Color
   Color_SetTextColor();   
   Color_SetImageColor();
 
   // Network
   Network_Init();
   
   // Time 
   Time_Init();
   
   // Battery
   Battery_Init();
   
   // BT
   Bluetooth_Init();

   // Health
   Health_Init();
   
   // Weather
   Weather_Init();
   
   // Communication
   Communication_Init();
        
   // Acceleration
   Acceleration_Init();
}

static void deinit() 
{
   Weather_DeInit();
   Bluetooth_DeInit();
   Network_DeInit();
   Battery_Deinit();
   Time_DeInit();
   Communication_DeInit();
   Health_DeInit();
   Acceleration_DeInit();
   // Destroy Window
   hide_mainwindow();
}



int main(void) 
{
   init();
   app_event_loop();
   deinit();
}

