#include "acceleration.h"

static void tap_handler(AccelAxisType axis, int32_t direction) 
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


void InitAcceleration(void)
{
   accel_tap_service_subscribe(tap_handler);
}

void DeInitAcceleration(void)
{
   accel_tap_service_unsubscribe();
}