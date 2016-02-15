#include "timer.h"

TextLayer* Layer_Time_Text;
TextLayer* Layer_Date_Text;
TextLayer* Layer_Day_Text;

void RedrawTime() 
{
   // Get a tm structure
   time_t temp = time(NULL);
   struct tm *tick_time = localtime(&temp);

   // Write the current hours and minutes into a buffer
   static char s_timebuffer[8];
   
   if (Clock24h)
      strftime(s_timebuffer, sizeof(s_timebuffer), "%H:%M", tick_time);
   else
   {
      strftime(s_timebuffer, sizeof(s_timebuffer), "%I:%M", tick_time);
   }

   // Display this time on the TextLayer
   text_layer_set_text(Layer_Time_Text, s_timebuffer);
   
   static char s_datebuffer[20];
   if (DateStyle == DATE_DD_MM_YY)
      strftime(s_datebuffer, sizeof(s_datebuffer), "%a, %d.%m.%y", tick_time);
   else if (DateStyle == DATE_YY_MM_DD)
      strftime(s_datebuffer, sizeof(s_datebuffer), "%a, %y-%m-%d", tick_time);
   else // if DATE_MM_DD_YY
      strftime(s_datebuffer, sizeof(s_datebuffer), "%a, %m/%d/%y", tick_time);
   
   // Display this date on the TextLayer
   text_layer_set_text(Layer_Date_Text, s_datebuffer);
   
   static char s_daybuffer[20];
   strftime(s_daybuffer, sizeof(s_daybuffer), "D%j W%W", tick_time);
   
   // Display this day on the TextLayer
   text_layer_set_text(Layer_Day_Text, s_daybuffer);
   
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) 
{
   RedrawTime();
   
   if (tick_time->tm_min % m_i_NetworkRefreshTime == 0)
      Network_Request();
   
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
   RedrawTime();

   // Add Handlers
   
   // Register with TickTimerService
   tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

void DeInitTimer()
{
   tick_timer_service_unsubscribe();
}