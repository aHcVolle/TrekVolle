#include "clock.h"

// Used layers
TextLayer* m_TimeHour_Text_Layer = NULL;
TextLayer* m_TimeMinute_Text_Layer = NULL;
TextLayer* m_Date_Text_Layer = NULL;
TextLayer* m_Day_Text_Layer = NULL;

// Used variables 
int m_i_Weather_Counter = 0;
int m_i_Network_Counter = 0;
int m_i_LastMinute = -1;


// Redraw the clocks text
void Clock_Redraw() 
{
   // Debug printout
   #ifdef DEBUG_CLOCK
         printf("[CLOCK][Clock_Redraw] Redrawing");
   #endif
   
   // Get a tm structure
   time_t Time_Temp = time(NULL);
   struct tm* Time_Tick = localtime(&Time_Temp);

   // Write the current hours and minutes into a buffer
   static char s_TimeHourBuffer[3];
   static char s_TimeMinuteBuffer[5];
   // Distinguish betwwen 24 and 12 hour mode
   if (m_b_Clock_Clock24h)
   {
      strftime(s_TimeHourBuffer, sizeof(s_TimeHourBuffer), "%H", Time_Tick);
      strftime(s_TimeMinuteBuffer, sizeof(s_TimeMinuteBuffer), ":%M", Time_Tick);
   }      
   else
   {
      strftime(s_TimeHourBuffer, sizeof(s_TimeHourBuffer), "%I", Time_Tick);
      strftime(s_TimeMinuteBuffer, sizeof(s_TimeMinuteBuffer), ":%M", Time_Tick);
   }

   // Display this time on the TextLayer
   text_layer_set_text(m_TimeHour_Text_Layer, s_TimeHourBuffer);
   text_layer_set_text(m_TimeMinute_Text_Layer, s_TimeMinuteBuffer);
   
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
   if (m_i_Clock_DayOfYearStyle == DAY_DAYOFYEAR)
   {
      strftime(s_DayBuffer, sizeof(s_DayBuffer), "D%j W%W", Time_Tick);
   }
   else if (m_i_Clock_DayOfYearStyle == DAY_TEMPHIGHLOW)
   {
      int TempMin = m_i_Weather_Temperature_Min;
      int TempMax = m_i_Weather_Temperature_Max;
      if (!m_b_Weather_TemperatureInCelcius)
      {
         TempMin = (float) TempMin * 1.8 + 32;
         TempMax = (float) TempMax * 1.8 + 32;
      }
      snprintf(s_DayBuffer, sizeof(s_DayBuffer), "%3d - %3d", TempMin,TempMax);
   }
   
   
   
   // Display this buffer on the TextLayer
   text_layer_set_text(m_Day_Text_Layer, s_DayBuffer);
   
}

// A new time tick will be processed here
static void Clock_Handle(struct tm *tick_time, TimeUnits units_changed) 
{
   if (m_i_LastMinute == tick_time->tm_min)
   {
      return;
   }
   m_i_LastMinute = tick_time->tm_min;
   
   // Debug printout 
   #ifdef DEBUG_CLOCK
         printf("[CLOCK][Clock_Handle] Handler %d:%d:%d",tick_time->tm_hour,tick_time->tm_min,tick_time->tm_sec);
   #endif
   // Redraw the time
   Clock_Redraw();
   
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
   
   #if defined(PBL_HEALTH)
      // Get new health data
      Health_GetMovementData();
   #endif
   
   #ifdef DEBUG_CLOCK
      printf("[CLOCK][Clock_Handle] After Heap Used: %d, Free: %d",(int) heap_bytes_used(), (int)heap_bytes_free() );
   #endif
}

// Init the used variables and register with the time service
void Clock_Init()
{
   // Debug printout
   #ifdef DEBUG_CLOCK
         printf("[CLOCK][Clock_Init] Init");
   #endif
   // Init the vars
   m_TimeHour_Text_Layer = GetTimeHourTextLayer();
   m_TimeMinute_Text_Layer = GetTimeMinuteTextLayer();
   m_Date_Text_Layer = GetDateTextLayer();
   m_Day_Text_Layer  = GetDayTextLayer();
   
   
   // Make sure the time is displayed from the start
   Clock_Redraw();

   
   // Register with TickTimerService
   tick_timer_service_subscribe(MINUTE_UNIT, Clock_Handle);
}

// Unregister from the service
void Clock_DeInit()
{
   // Debug printout
   #ifdef DEBUG_CLOCK
         printf("[CLOCK][Clock_DeInit] Deinit");
   #endif
   // Unregister from the service
   tick_timer_service_unsubscribe();
}