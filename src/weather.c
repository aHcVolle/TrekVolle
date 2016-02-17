#include "weather.h"

// Used layers and bitmaps
TextLayer* m_Weather_Text_Layer = NULL;
static BitmapLayer* m_Weather_Image_Layer = NULL;
static GBitmap *m_Weather_Image = NULL;

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
      // If not request an update
      Weather_Request();
      return;
   }
   // Debug printout
   if (m_b_Debug)
         printf("[WTHR] Redrawing text");
   
   // If we should display the current conditions
   if (m_i_Weather_DisplayState == DISPLAY_CONDITIONS)
   {
      // Save the weather text
      if (m_b_Weather_TemperatureInCelcius)
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
   layer_mark_dirty(text_layer_get_layer(m_Weather_Text_Layer));
}

// Redraw the weather image
void Weather_RedrawImage()
{
   // Debug printout
   if (m_b_Debug)
         printf("[WTHR] Redrawing image");
   // And redraw
   Redraw_Image(m_Weather_Image_Layer,m_Weather_Image,m_i_Weather_WeatherImage,Color_Image);
}

// Redraw all weather related data
void Weather_Redraw()
{
   // Debug printout
   if (m_b_Debug)
         printf("[WTHR] Redrawing everything");
   // And do some work
   Weather_RedrawText();
   Weather_RedrawImage();
}

// New weather information will be processed here
void Weather_Handle(Tuple *Temperature_tuple,Tuple *Condition_tuple,Tuple *Location_tuple,Tuple *Image_tuple)
{
   // Debug printout
   if (m_b_Debug)
         printf("[WTHR] Handler");
   // If we have some temperature information
   if(Temperature_tuple) 
   {
      m_i_Weather_Temperature = (int)Temperature_tuple->value->int32;
      if (m_b_Debug)
         printf("[WTHR] Handler: Got temperatue");
      m_b_Weather_LastUpdateWasOK = true; 
   }
   // If we have info about the current condition
   if(Condition_tuple)
   {
      snprintf(m_s_Weather_ConditionBuffer, sizeof(m_s_Weather_ConditionBuffer), "%s", Condition_tuple->value->cstring);
      if (m_b_Debug)
         printf("[WTHR] Handler: Got condition");
      m_b_Weather_LastUpdateWasOK = true;
   }
   // If we have info about hte current location
   if(Location_tuple) 
   {
      snprintf(m_s_Weather_LocationBuffer, sizeof(m_s_Weather_LocationBuffer), "%s", Location_tuple->value->cstring);
      if (m_b_Debug)
         printf("[WTHR] Handler: Got location");
      m_b_Weather_LastUpdateWasOK = true;
   }
   // If we have info about the image to use
   if (Image_tuple)
   {  
      m_i_Weather_WeatherImage = Weather_GetImageID(Image_tuple->value->cstring);
      if (m_b_Debug)
         printf("[WTHR] Handler: Got imageid");
      Weather_RedrawImage();
   }
   // Redraw the text
   Weather_RedrawText();
}

// Init all the variables
void Weather_Init()
{
   // Debug printout
   if (m_b_Debug)
         printf("[WTHR] Init");
   // Init the vars
   m_b_Weather_LastUpdateWasOK = false;
   m_i_Weather_DisplayState = DISPLAY_CONDITIONS;
   m_Weather_Text_Layer = GetWeatherTextLayer();
   m_Weather_Image_Layer = GetWeatherImageLayer(); 
   
   m_i_Weather_WeatherImage = RESOURCE_ID_IMAGE_ERROR;
   // Redraw the weather
   Weather_RedrawImage();
}

// Deinit the weather module
void Weather_DeInit()
{
   // Debug printout
   if (m_b_Debug)
         printf("[WTHR] Deinit");
   // Kill all ze thingz!
   if (m_Weather_Image)
   {
      gbitmap_destroy(m_Weather_Image);
      m_Weather_Image = NULL;
   }  
}

// Request a weather update
void Weather_Request()
{
   // But only if there is a bluetooth connection
   if (!m_b_Bluetooth_ConnectionState)
      return;
   // We haven't got data yet
   m_b_Weather_LastUpdateWasOK = false;

   // Debug printout
   if (m_b_Debug)
         printf("[WTHR] Request");
   
   // Send Request
   Communication_Send(KEY_TEMPERATURE);
}

// Convert an image name to a resource id
int Weather_GetImageID(char* s_WeatherImageName)
{
   // Compare the image name
   if (strcmp(s_WeatherImageName,"01d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_01;
   else if (strcmp(s_WeatherImageName,"01n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_01;
   else if (strcmp(s_WeatherImageName,"02d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_02;
   else if (strcmp(s_WeatherImageName,"02n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_02;
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
      return RESOURCE_ID_IMAGE_WEATHER_10;
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
   printf("Unknown weather image %s",s_WeatherImageName);
   return RESOURCE_ID_IMAGE_ERROR;
}