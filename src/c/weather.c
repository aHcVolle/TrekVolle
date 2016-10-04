#include "weather.h"

// Used layers and bitmaps
TextLayer* m_Weather_Text_Layer = NULL;

// Buffers to store all the text
static char m_s_Weather_ConditionBuffer[32];
static char m_s_Weather_LocationBuffer[32];
static char m_s_Weather_TextBuffer[32];

// Used variables
int m_i_Weather_WeatherImage = -1;
int m_i_Weather_Temperature = 999;

// Redraw the weather text
void Weather_RedrawText()
{   
   // Only redraw if the last update as successful
   if (!m_b_Weather_LastUpdateWasOK)
   {
       return;
   }
   // Debug printout
   #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_RedrawText] Redrawing text");
   #endif
   
   // If we should display the current conditions
   if (m_i_Weather_DisplayState == DISPLAY_CONDITIONS)
   {
      // Save the weather text
      if (m_i_Weather_Temperature < -199)
      {
         snprintf(m_s_Weather_TextBuffer, sizeof(m_s_Weather_TextBuffer), "%s", m_s_Weather_ConditionBuffer);
         m_b_Weather_LastUpdateWasOK = false;
      }
      else if (m_b_Weather_TemperatureInCelcius)
      {
         // If we want the temperature in celcius
         snprintf(m_s_Weather_TextBuffer, sizeof(m_s_Weather_TextBuffer), "%d°C, %s", m_i_Weather_Temperature, m_s_Weather_ConditionBuffer);
      }         
      else
      {
         // If we want it in fahrenheit
         float Fahrenheit = m_i_Weather_Temperature * 1.8 + 32;
         snprintf(m_s_Weather_TextBuffer, sizeof(m_s_Weather_TextBuffer), "%d°F, %s", (int)Fahrenheit, m_s_Weather_ConditionBuffer);
      }
   }      
   else
   {
      // Or if we should display the current location
      snprintf(m_s_Weather_TextBuffer, sizeof(m_s_Weather_TextBuffer), "%s", m_s_Weather_LocationBuffer);
   }
      
   // Set the text
   text_layer_set_text(m_Weather_Text_Layer, m_s_Weather_TextBuffer);
   // Redraw the text
   //layer_mark_dirty(text_layer_get_layer(m_Weather_Text_Layer));
}

// Redraw the weather image
void Weather_RedrawImage()
{
   // Debug printout
   #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_RedrawImage] Redrawing image");
   #endif
   // And redraw
   Redraw_Image(&m_Image_Weather,m_i_Weather_WeatherImage,Color_Image);
}

// Redraw all weather related data
void Weather_Redraw()
{
   // Debug printout
   #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_Redraw] Redrawing everything");
   #endif
   // And do some work
   Weather_RedrawText();
   Weather_RedrawImage();
   Refresh_Display();
}

// New weather information will be processed here
void Weather_Handle(Tuple *Temperature_tuple,Tuple *Condition_tuple,Tuple *Location_tuple,Tuple *Image_tuple)
{
   // Debug printout
   #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_Handle] Handler");
   #endif
   // If we have some temperature information
   if(Temperature_tuple) 
   {
      m_i_Weather_Temperature = (int)Temperature_tuple->value->int32;
      #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_Handle] Handler: Got temperatue");
      #endif
      m_b_Weather_LastUpdateWasOK = true; 
   }
   // If we have info about the current condition
   if(Condition_tuple)
   {
      snprintf(m_s_Weather_ConditionBuffer, sizeof(m_s_Weather_ConditionBuffer), "%s", Condition_tuple->value->cstring);
      #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_Handle] Handler: Got condition");
      #endif
      m_b_Weather_LastUpdateWasOK = true;
   }
   // If we have info about hte current location
   if(Location_tuple) 
   {
      snprintf(m_s_Weather_LocationBuffer, sizeof(m_s_Weather_LocationBuffer), "%s", Location_tuple->value->cstring);
      #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_Handle] Handler: Got location");
      #endif
      m_b_Weather_LastUpdateWasOK = true;
   }
   // If we have info about the image to use
   if (Image_tuple)
   {  
      int i_NewWeatherImage = Weather_GetImageID(Image_tuple->value->cstring);
      #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_Handle] Handler: Got imageid %d",i_NewWeatherImage);
      #endif
      if (i_NewWeatherImage != m_i_Weather_WeatherImage)
      {
         m_i_Weather_WeatherImage = i_NewWeatherImage;
         Weather_RedrawImage();
      }
   }
   // Redraw the text
   Weather_RedrawText();
   
   // Save new data to non volatile memory
   time_t Time;
   time(&Time);
   m_i_Weather_LastRefresh = (int)Time;
   
}

// Init all the variables
void Weather_Init()
{
   // Debug printout
   #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_Init] Init");
   #endif
   // Init the vars
   m_b_Weather_LastUpdateWasOK = false;
   m_i_Weather_DisplayState = DISPLAY_CONDITIONS;
   m_i_Weather_Temperature_Min = 0;
   m_i_Weather_Temperature_Max = 0;
   m_Weather_Text_Layer = GetWeatherTextLayer();
   
   m_i_Weather_WeatherImage = RESOURCE_ID_IMAGE_ERROR;
   //
   Weather_LoadData();
   // Redraw the weather
   Weather_Redraw();
}

// Deinit the weather module
void Weather_DeInit()
{
   // Debug printout
   #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_DeInit] Deinit");
   #endif
   Weather_SaveData();
}

// Request a weather update
void Weather_Request()
{
   // But only if there is a bluetooth connection
   if (!m_b_Bluetooth_ConnectionState)
      return;
   
   // Only do this if the communication is already initialized
   if (!m_b_CommunicationIsInit)
      return;
   
   // Don't do this if we're battery saving
   if (m_b_BatterySavingActive)
      return;
   
   // We haven't got data yet
   m_b_Weather_LastUpdateWasOK = false;

   // Debug printout
   #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_Request] Request");
   #endif
   
   
   
   // Send Request
   Communication_Send(MESSAGE_KEY_TEMPERATURE);
}

void Weather_SaveData()
{
   
   #ifdef DEBUG_WEATHER
      printf("[WEATHER][Weather_SaveData] Saving weather data (time: %d)",m_i_Weather_LastRefresh);
   #endif
   
   int i_LastSaveTime = 0;
   if (persist_exists(MESSAGE_KEY_WEATHER_DATA_TIME))
      i_LastSaveTime = persist_read_int(MESSAGE_KEY_WEATHER_DATA_TIME);
   
   if (i_LastSaveTime != m_i_Weather_LastRefresh)
   {
      WriteInt(MESSAGE_KEY_WEATHER_DATA_TIME, m_i_Weather_LastRefresh);
      WriteInt(MESSAGE_KEY_WEATHER_DATA_TEMP, m_i_Weather_Temperature);
      WriteInt(MESSAGE_KEY_WEATHER_DATA_IMAGE, m_i_Weather_WeatherImage);
      WriteInt(MESSAGE_KEY_WEATHER_DATA_TEMPMIN, m_i_Weather_Temperature_Min);
      WriteInt(MESSAGE_KEY_WEATHER_DATA_TEMPMAX, m_i_Weather_Temperature_Max);
      WriteString(MESSAGE_KEY_WEATHER_DATA_COND, m_s_Weather_ConditionBuffer);
      WriteString(MESSAGE_KEY_WEATHER_DATA_LOCATION, m_s_Weather_LocationBuffer);
   }
}

void Weather_LoadData()
{
   if (persist_exists(MESSAGE_KEY_WEATHER_DATA_TIME)) 
   {
      m_i_Weather_LastRefresh = persist_read_int(MESSAGE_KEY_WEATHER_DATA_TIME);
      
      time_t now;
      time(&now);
      
      #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_LoadData] Times: saved: %d, now: %d",(int)m_i_Weather_LastRefresh,(int)now);
      #endif
      
      int i_TimeDiffInMinutes = (now - m_i_Weather_LastRefresh) / 60;
      // Reload Weather data from internet ?
      if (i_TimeDiffInMinutes <  m_i_Weather_RefreshTime)
      {
         #ifdef DEBUG_WEATHER
            printf("[WEATHER][Weather_LoadData] Using saved weather");
         #endif
         
         // Load it from storage
         if (persist_exists(MESSAGE_KEY_WEATHER_DATA_TEMP)) 
         {
            m_i_Weather_Temperature = persist_read_int(MESSAGE_KEY_WEATHER_DATA_TEMP);
         }
         if (persist_exists(MESSAGE_KEY_WEATHER_DATA_IMAGE)) 
         {
            m_i_Weather_WeatherImage = persist_read_int(MESSAGE_KEY_WEATHER_DATA_IMAGE);
         }
         if (persist_exists(MESSAGE_KEY_WEATHER_DATA_TEMPMIN)) 
         {
            m_i_Weather_Temperature_Min = persist_read_int(MESSAGE_KEY_WEATHER_DATA_TEMPMIN);
         }
         if (persist_exists(MESSAGE_KEY_WEATHER_DATA_TEMPMAX)) 
         {
            m_i_Weather_Temperature_Max = persist_read_int(MESSAGE_KEY_WEATHER_DATA_TEMPMAX);
         }
         if (persist_exists(MESSAGE_KEY_WEATHER_DATA_COND)) 
         {
            persist_read_string(MESSAGE_KEY_WEATHER_DATA_COND,m_s_Weather_ConditionBuffer,32);
         }
         if (persist_exists(MESSAGE_KEY_WEATHER_DATA_LOCATION)) 
         {
            persist_read_string(MESSAGE_KEY_WEATHER_DATA_LOCATION,m_s_Weather_LocationBuffer,32);
         }
         
         m_b_Weather_LastUpdateWasOK = true;
         
         m_i_Weather_Counter = i_TimeDiffInMinutes - 1;
         #ifdef DEBUG_WEATHER
            printf("[WEATHER][Weather_LoadData] Minutes to next weather refresh: %d",m_i_Weather_RefreshTime - m_i_Weather_Counter);
         #endif
         
         if (m_i_Clock_DayOfYear == DAY_TEMPHIGHLOW)
            Clock_Redraw();
      }
      else
      {
         #ifdef DEBUG_WEATHER
            printf("[WEATHER][Weather_LoadData] Saved weather data is too old");
         #endif
         
         // The saved data is too old
         m_b_Weather_LastUpdateWasOK = false;
      }
      
   }
   else
   {
      #ifdef DEBUG_WEATHER
         printf("[WEATHER][Weather_LoadData] There is no saved weather data");
      #endif
      
      // There is no saved data
      m_b_Weather_LastUpdateWasOK = false;
   }
}

// Convert an image name to a resource id
int Weather_GetImageID(char* s_WeatherImageName)
{
   #ifdef DEBUG_WEATHER
      printf("[WEATHER][Weather_GetImageID] Getting id for %s",s_WeatherImageName);
   #endif
   // Compare the image name
   if (strcmp(s_WeatherImageName,"01d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_01;
   else if (strcmp(s_WeatherImageName,"01n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_01N;
   else if (strcmp(s_WeatherImageName,"02d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_02;
   else if (strcmp(s_WeatherImageName,"02n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_02N;
   else if (strcmp(s_WeatherImageName,"03d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_03;
   else if (strcmp(s_WeatherImageName,"03n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_03;
   else if (strcmp(s_WeatherImageName,"04d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_04;
   else if (strcmp(s_WeatherImageName,"04n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_04;
   else if (strcmp(s_WeatherImageName,"09d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_09;
   else if (strcmp(s_WeatherImageName,"09n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_09;
   else if (strcmp(s_WeatherImageName,"10d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_10;
   else if (strcmp(s_WeatherImageName,"10n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_10N;
   else if (strcmp(s_WeatherImageName,"11d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_11;
   else if (strcmp(s_WeatherImageName,"11n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_11;   
   else if (strcmp(s_WeatherImageName,"13d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_13;
   else if (strcmp(s_WeatherImageName,"13n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_13;
   else if (strcmp(s_WeatherImageName,"50d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_50;
   else if (strcmp(s_WeatherImageName,"50n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_50;
   
   // This imagename is unknown!
   #ifdef DEBUG_WEATHER
      printf("[WEATHER][Weather_GetImageID] Unknown weather image %s",s_WeatherImageName);
   #endif
   return RESOURCE_ID_IMAGE_ERROR;
}