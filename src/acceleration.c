#include "acceleration.h"

static void Acceleration_Handle(AccelAxisType axis, int32_t direction) 
{
   // Check if the axis was the y axis
   if  (axis == ACCEL_AXIS_Y)  
   {
      if (m_b_Debug)
         printf("[ACC] Device accelerated");
      // Switch display state
      if (m_i_Weather_DisplayState == DISPLAY_CONDITIONS)
         m_i_Weather_DisplayState = DISPLAY_LOCATION;
      else
         m_i_Weather_DisplayState = DISPLAY_CONDITIONS;
      // Redraw the weather text to display the new data
      Weather_RedrawText();
   }
}

// Register to the acceleration service
void Acceleration_Init(void)
{
   if (m_b_Debug)
         printf("[ACC] Init"); 
   accel_tap_service_subscribe(Acceleration_Handle);
}

// Unregister from the acceleration service
void Acceleration_DeInit(void)
{
   if (m_b_Debug)
         printf("[ACC] Deinit");
   accel_tap_service_unsubscribe();
}