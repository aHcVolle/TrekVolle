#include "acceleration.h"

static void Acceleration_Handle(AccelAxisType axis, int32_t direction) 
{
   
   if  (axis == ACCEL_AXIS_Y)  
   {
      if (m_i_Weather_DisplayState == DISPLAY_CONDITIONS)
         m_i_Weather_DisplayState = DISPLAY_LOCATION;
      else
         m_i_Weather_DisplayState = DISPLAY_CONDITIONS;

      Weather_RedrawText();
   }
}


void Acceleration_Init(void)
{
   accel_tap_service_subscribe(Acceleration_Handle);
}

void Acceleration_DeInit(void)
{
   accel_tap_service_unsubscribe();
}