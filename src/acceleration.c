#include "acceleration.h"

static void Acceleration_Handle(AccelAxisType axis, int32_t direction) 
{
   if  (axis == ACCEL_AXIS_Y)  
   {
      if (m_b_Debug)
         printf("[ACC] Device accelerated");
      
      if (m_i_Weather_DisplayState == DISPLAY_CONDITIONS)
         m_i_Weather_DisplayState = DISPLAY_LOCATION;
      else
         m_i_Weather_DisplayState = DISPLAY_CONDITIONS;

      Weather_RedrawText();
   }
}


void Acceleration_Init(void)
{
   if (m_b_Debug)
         printf("[ACC] Init");
   accel_tap_service_subscribe(Acceleration_Handle);
}

void Acceleration_DeInit(void)
{
   if (m_b_Debug)
         printf("[ACC] Deinit");
   accel_tap_service_unsubscribe();
}