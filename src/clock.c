#include "clock.h"

// Used layers
TextLayer* m_Time_Text_Layer = NULL;
TextLayer* m_Date_Text_Layer = NULL;
TextLayer* m_Day_Text_Layer = NULL;

// Used variables 
int m_i_Weather_Counter = 0;
int m_i_Network_Counter = 0;

// Redraw the clocks text
void Time_Redraw() 
{
   // Debug printout
   if (m_b_Debug)
         printf("[CLOCK] Redrawing");
   
   // Get a tm structure
   time_t Time_Temp = time(NULL);
   struct tm* Time_Tick = localtime(&Time_Temp);

   // Write the current hours and minutes into a buffer
   static char s_TimeBuffer[8];
   // Distinguish betwwen 24 and 12 hour mode
   if (m_b_Clock_Clock24h)
      strftime(s_TimeBuffer, sizeof(s_TimeBuffer), "%H:%M", Time_Tick);
   else
   {
      strftime(s_TimeBuffer, sizeof(s_TimeBuffer), "%I:%M", Time_Tick);
   }

   // Display this time on the TextLayer
   text_layer_set_text(m_Time_Text_Layer, s_TimeBuffer);
   
   // Write the current date into a buffer based on the options
   static char s_DateBuffer[20];
   if (m_i_Clock_DateStyle == DATE_DD_MM_YY)
      strftime(s_DateBuffer, sizeof(s_DateBuffer), "%a, %d.%m.%y", Time_Tick);
   else if (m_i_Clock_DateStyle == DATE_YY_MM_DD)
      strftime(s_DateBuffer, sizeof(s_DateBuffer), "%a, %y-%m-%d", Time_Tick);
   else // if DATE_MM_DD_YY
      strftime(s_DateBuffer, sizeof(s_DateBuffer), "%a, %m/%d/%y", Time_Tick);
   
   // Display this date on the TextLayer
   text_layer_set_text(m_Date_Text_Layer, s_DateBuffer);
   
   // Write the current day/week into a buffer
   static char s_DayBuffer[20];
   strftime(s_DayBuffer, sizeof(s_DayBuffer), "D%j W%W", Time_Tick);
   
   // Display this buffer on the TextLayer
   text_layer_set_text(m_Day_Text_Layer, s_DayBuffer);
   
}

// A new time tick will be processed here
static void Time_Handle(struct tm *tick_time, TimeUnits units_changed) 
{
   // Debug printout 
   if (m_b_Debug)
         printf("[CLOCK] Handler");
   
   // Redraw the time
   Time_Redraw();
   
   // See if we want to request a network check
   m_i_Network_Counter++;
   if (m_i_Network_Counter >= m_i_Network_RefreshTime)
   {
      Network_Request();
      m_i_Network_Counter = 0;
   }
   
   // Or a weather update
   m_i_Weather_Counter++;
   if ((m_b_Weather_RetryUpdate && !m_b_Weather_LastUpdateWasOK) || (m_i_Weather_Counter >= m_i_Weather_RefreshTime))
   {
      Weather_Request();
      m_i_Weather_Counter = 0;     
   }   
   
   // Check the sleep mode
   if ((tick_time->tm_hour >= 0) && (tick_time->tm_hour < 7))
   {
      m_b_Clock_SleepEnabled = true;
   }
   else
   {
      m_b_Clock_SleepEnabled = false;
   }
}

// Init the used variables and register with the time service
void Time_Init()
{
   // Debug printout
   if (m_b_Debug)
         printf("[CLOCK] Init");
   
   // Init the vars
   m_Time_Text_Layer = GetTimeTextLayer();
   m_Date_Text_Layer = GetDateTextLayer();
   m_Day_Text_Layer  = GetDayTextLayer();
   
   
   // Make sure the time is displayed from the start
   Time_Redraw();

   
   // Register with TickTimerService
   tick_timer_service_subscribe(MINUTE_UNIT, Time_Handle);
}

// Unregister from the service
void Time_DeInit()
{
   // Debug printout
   if (m_b_Debug)
         printf("[CLOCK] Deinit");
   // Unregister from the service
   tick_timer_service_unsubscribe();
}