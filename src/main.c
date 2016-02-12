#include <pebble.h>
#include "mainwindow.h"
#include "weather.h"
#include "health.h"
#include "battery.h"
#include "bluetooth.h"
#include "timer.h"
#include "network.h"
#include "communication.h"
#include "acceleration.h"


static void init() 
{
   // UI 
   show_mainwindow();
   // Set Color
   SetColor();   
 
   // Network
   InitNetwork();
   
   // Time 
   InitTimer();
   
   // Battery
   Battery_Init();
   
   // BT
   InitBluetooth();

   // Health
   InitHealth();
   
   // Weather
   InitWeather();
   
   // Communication
   InitCommunication();
     
   
   // Acceleration
   InitAcceleration();
}

static void deinit() 
{
   DeInitWeather();
   DeInitBluetooth();
   DeInitNetwork();
   Battery_Deinit();
   DeInitTimer();
   DeInitCommunication();
   DeInitHealth();
   DeInitAcceleration();
   // Destroy Window
   hide_mainwindow();
}



int main(void) 
{
   init();
   app_event_loop();
   deinit();
}

