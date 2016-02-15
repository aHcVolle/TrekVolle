#include "acceleration.h"

static void Acceleration_Handle(AccelAxisType axis, int32_t direction) 
{
   
   if  (axis == ACCEL_AXIS_Y)  
   {
      if (DisplayState == DISPLAY_CONDITIONS)
         DisplayState = DISPLAY_LOCATION;
      else
         DisplayState = DISPLAY_CONDITIONS;

      RedrawWeatherText();
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