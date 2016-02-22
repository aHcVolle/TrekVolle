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
#include "e_memory_tools.h"

// Init all the modules
static void init() 
{
   ui_PNG_Loadbuffer = malloc_low(PNG_BUFFER_SIZE);
   m_b_Debug = true;


   if (m_b_Debug)
      printf("\n\n\n\nTrekvolle is starting\n\n\n\n");

   if (m_b_Debug)
         printf("[MAIN][init] First image loaded, reserving %dB of memory",PNG_BUFFER_SIZE);
   
   // UI 
   show_mainwindow();
   // Set Color
   Color_SetTextColor();   
   Color_SetImageColor();
 
   // Communication
   Communication_Init();
   
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
   
   
        
   // Acceleration
   Acceleration_Init();
   
   // Do Ping
   Communication_Send(KEY_PINGPONG);
}

// Deinit all the functions
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

// We start here
int main(void) 
{
   
   
   init();
   app_event_loop();
   deinit();
}

