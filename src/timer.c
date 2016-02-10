#include "timer.h"

TextLayer* Layer_Time_Text;
TextLayer* Layer_Date_Text;
TextLayer* Layer_Day_Text;

static void update_time() 
{
   // Get a tm structure
   time_t temp = time(NULL);
   struct tm *tick_time = localtime(&temp);

   // Write the current hours and minutes into a buffer
   static char s_timebuffer[8];

   strftime(s_timebuffer, sizeof(s_timebuffer), "%H:%M", tick_time);

   // Display this time on the TextLayer
   text_layer_set_text(Layer_Time_Text, s_timebuffer);
   
   static char s_datebuffer[20];
   strftime(s_datebuffer, sizeof(s_datebuffer), "%a, %d.%m.%y", tick_time);
   
   // Display this date on the TextLayer
   text_layer_set_text(Layer_Date_Text, s_datebuffer);
   
   static char s_daybuffer[20];
   strftime(s_daybuffer, sizeof(s_daybuffer), "D%j W%W", tick_time);
   
   // Display this day on the TextLayer
   text_layer_set_text(Layer_Day_Text, s_daybuffer);
   
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) 
{
   update_time();
   RequestNetwork();
   
   // Get weather update every 30 minutes
   if ((!LastWeatherUpdateWasOK) || (tick_time->tm_min % 30 == 0))
   {
     RequestWeather();
   }
   
}

void InitTimer()
{
   Layer_Time_Text = GetTimeTextLayer();
   Layer_Date_Text = GetDateTextLayer();
   Layer_Day_Text  = GetDayTextLayer();
   
   
   // Make sure the time is displayed from the start
   update_time();

   // Add Handlers
   
   // Register with TickTimerService
   tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

void DeInitTimer()
{
   tick_timer_service_unsubscribe();
}