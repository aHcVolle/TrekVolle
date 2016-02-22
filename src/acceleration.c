#include "acceleration.h"

// Var to store acceleration state
bool m_b_Acceleration_Blocked;

void Acceleration_TimerCallback(void *data)
{
   m_b_Acceleration_Blocked = false;
}

static void Acceleration_Handle(AccelAxisType axis, int32_t direction) 
{
   if (m_b_Acceleration_Blocked)
   {
      if (m_b_Debug)
         printf("[ACC][Acceleration_Handle] Acceleration blocked"); 
      return;
   }
   m_b_Acceleration_Blocked = true;
   if (m_b_Debug)
         printf("[ACC][Acceleration_Handle] Axis: %d Direction: %d",(int)axis,(int)direction); 
   
   
   // Check if the axis was the y axis
   //if  (axis == ACCEL_AXIS_Y)  
   {
      if (m_b_Debug)
         printf("[ACC][Acceleration_Handle] Device accelerated");
      // Switch display state
      if (m_i_Weather_DisplayState == DISPLAY_CONDITIONS)
         m_i_Weather_DisplayState = DISPLAY_LOCATION;
      else
         m_i_Weather_DisplayState = DISPLAY_CONDITIONS;
      // Redraw the weather text to display the new data
      Weather_RedrawText();
   }
   
   // Try to avoid double switches....
   
   app_timer_register(1000, Acceleration_TimerCallback, NULL);
}

// Register to the acceleration service
void Acceleration_Init(void)
{
   if (m_b_Debug)
         printf("[ACC][Acceleration_Init] Init"); 
   m_b_Acceleration_Blocked = false;
   accel_tap_service_subscribe(Acceleration_Handle);
}

// Unregister from the acceleration service
void Acceleration_DeInit(void)
{
   if (m_b_Debug)
         printf("[ACC][Acceleration_DeInit] Deinit");
   accel_tap_service_unsubscribe();
}