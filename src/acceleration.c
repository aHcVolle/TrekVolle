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
      #ifdef DEBUG_ACCELERATION 
         printf("[ACC][Acceleration_Handle] Acceleration blocked"); 
      #endif
      return;
   }
   m_b_Acceleration_Blocked = true;
   #ifdef DEBUG_ACCELERATION 
      printf("[ACC][Acceleration_Handle] Axis: %d Direction: %d",(int)axis,(int)direction);  
   #endif
   
   
   // Check if the axis was the y axis


   #ifdef DEBUG_ACCELERATION 
      printf("[ACC][Acceleration_Handle] Device accelerated"); 
   #endif
   // Switch display state
   if (m_i_Weather_DisplayState == DISPLAY_CONDITIONS)
      m_i_Weather_DisplayState = DISPLAY_LOCATION;
   else
      m_i_Weather_DisplayState = DISPLAY_CONDITIONS;
   // Redraw the weather text to display the new data
   Weather_RedrawText();

   
   // Try to avoid double switches....   
   app_timer_register(1000, Acceleration_TimerCallback, NULL);
}

// Register to the acceleration service
void Acceleration_Init(void)
{
   #ifdef DEBUG_ACCELERATION 
      printf("[ACC][Acceleration_Init] Init");
   #endif
   m_b_Acceleration_Blocked = false;
   if (m_b_Acceleration_Enabled)
      accel_tap_service_subscribe(Acceleration_Handle);
}

// Unregister from the acceleration service
void Acceleration_DeInit(void)
{
   #ifdef DEBUG_ACCELERATION 
      printf("[ACC][Acceleration_DeInit] Deinit"); 
   #endif
   accel_tap_service_unsubscribe();
}