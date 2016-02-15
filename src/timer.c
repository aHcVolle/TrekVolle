#include "timer.h"

TextLayer* m_Time_Text_Layer;
TextLayer* m_Date_Text_Layer;
TextLayer* m_Day_Text_Layer;

void Time_Redraw() 
{
   // Get a tm structure
   time_t Time_Temp = time(NULL);
   struct tm* Time_Tick = localtime(&Time_Temp);

   // Write the current hours and minutes into a buffer
   static char s_TimeBuffer[8];
   
   if (m_b_Clock24h)
      strftime(s_TimeBuffer, sizeof(s_TimeBuffer), "%H:%M", Time_Tick);
   else
   {
      strftime(s_TimeBuffer, sizeof(s_TimeBuffer), "%I:%M", Time_Tick);
   }

   // Display this time on the TextLayer
   text_layer_set_text(m_Time_Text_Layer, s_TimeBuffer);
   
   static char s_DateBuffer[20];
   if (m_i_DateStyle == DATE_DD_MM_YY)
      strftime(s_DateBuffer, sizeof(s_DateBuffer), "%a, %d.%m.%y", Time_Tick);
   else if (m_i_DateStyle == DATE_YY_MM_DD)
      strftime(s_DateBuffer, sizeof(s_DateBuffer), "%a, %y-%m-%d", Time_Tick);
   else // if DATE_MM_DD_YY
      strftime(s_DateBuffer, sizeof(s_DateBuffer), "%a, %m/%d/%y", Time_Tick);
   
   // Display this date on the TextLayer
   text_layer_set_text(m_Date_Text_Layer, s_DateBuffer);
   
   static char s_DayBuffer[20];
   strftime(s_DayBuffer, sizeof(s_DayBuffer), "D%j W%W", Time_Tick);
   
   // Display this day on the TextLayer
   text_layer_set_text(m_Day_Text_Layer, s_DayBuffer);
   
}

static void Time_Handle(struct tm *tick_time, TimeUnits units_changed) 
{
   Time_Redraw();
   
   if (tick_time->tm_min % m_i_NetworkRefreshTime == 0)
      Network_Request();
   
   // Get weather update every 30 minutes
   if ((!LastWeatherUpdateWasOK) || (tick_time->tm_min % 30 == 0))
   {
     RequestWeather();
   }
   
}

void Time_Init()
{
   m_Time_Text_Layer = GetTimeTextLayer();
   m_Date_Text_Layer = GetDateTextLayer();
   m_Day_Text_Layer  = GetDayTextLayer();
   
   
   // Make sure the time is displayed from the start
   Time_Redraw();

   // Add Handlers
   
   // Register with TickTimerService
   tick_timer_service_subscribe(MINUTE_UNIT, Time_Handle);
}

void Time_DeInit()
{
   tick_timer_service_unsubscribe();
}