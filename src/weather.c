#include "weather.h"
TextLayer* m_Weather_Text_Layer;
static BitmapLayer* m_Weather_Image_Layer = NULL;
static GBitmap *m_Weather_Image;

static char m_s_Weather_ConditionBuffer[32];
static char m_s_Weather_LocationBuffer[32];
static char m_s_Weather_TextBuffer[32];

int m_i_Weather_WeatherImage;
int m_i_Weather_Temperature;

void Weather_RedrawText()
{
   if (!m_b_Weather_LastUpdateWasOK)
   {
      Weather_Request();
      return;
   }
      
   if (m_i_Weather_DisplayState == DISPLAY_CONDITIONS)
   {
      if (m_b_Weather_TemperatureInCelcius)
         snprintf(m_s_Weather_TextBuffer, sizeof(m_s_Weather_TextBuffer), "%d°C, %s", m_i_Weather_Temperature, m_s_Weather_ConditionBuffer);
      else
      {
         float Fahrenheit = m_i_Weather_Temperature * 1.8 + 32;
         snprintf(m_s_Weather_TextBuffer, sizeof(m_s_Weather_TextBuffer), "%d°F, %s", (int)Fahrenheit, m_s_Weather_ConditionBuffer);
      }
   }      
   else
      snprintf(m_s_Weather_TextBuffer, sizeof(m_s_Weather_TextBuffer), "%s", m_s_Weather_LocationBuffer);
      
   text_layer_set_text(m_Weather_Text_Layer, m_s_Weather_TextBuffer);
   layer_mark_dirty(text_layer_get_layer(m_Weather_Text_Layer));
}

void Weather_RedrawImage()
{
   Redraw_Image(m_Weather_Image_Layer,m_Weather_Image,m_i_Weather_WeatherImage,Color_Image);
}

void Weather_Redraw()
{
   Weather_RedrawText();
   Weather_RedrawImage();
}


void Weather_Handle(Tuple *Temperature_tuple,Tuple *Condition_tuple,Tuple *Location_tuple,Tuple *Image_tuple)
{
   if(Temperature_tuple) 
   {
      m_i_Weather_Temperature = (int)Temperature_tuple->value->int32;
      m_b_Weather_LastUpdateWasOK = true;
   }
   
   if(Condition_tuple)
   {
      snprintf(m_s_Weather_ConditionBuffer, sizeof(m_s_Weather_ConditionBuffer), "%s", Condition_tuple->value->cstring);
      m_b_Weather_LastUpdateWasOK = true;
   }
      
   if(Location_tuple) 
   {
      snprintf(m_s_Weather_LocationBuffer, sizeof(m_s_Weather_LocationBuffer), "%s", Location_tuple->value->cstring);
      m_b_Weather_LastUpdateWasOK = true;
   }
   
   if (Image_tuple)
   {  
      m_i_Weather_WeatherImage = Weather_GetImageID(Image_tuple->value->cstring);
      Weather_RedrawImage();
   }
   
   Weather_RedrawText();
}

void Weather_Init()
{
   m_b_Weather_LastUpdateWasOK = false;
   m_i_Weather_DisplayState = DISPLAY_CONDITIONS;
   m_Weather_Text_Layer = GetWeatherTextLayer();
   m_Weather_Image_Layer = GetWeatherImageLayer(); 
   
   m_i_Weather_WeatherImage = RESOURCE_ID_IMAGE_ERROR;
   Weather_RedrawImage();
}

void Weather_DeInit()
{
   if (m_Weather_Image)
   {
      gbitmap_destroy(m_Weather_Image);
      m_Weather_Image = NULL;
   }  
}

void Weather_Request()
{
   m_b_Weather_LastUpdateWasOK = false;

   //printf("C: requesting weather update...\n");
   // Begin dictionary
   DictionaryIterator *iter;
   app_message_outbox_begin(&iter);
   
   // Add a key-value pair
   dict_write_uint8(iter, KEY_TEMPERATURE, 0);
   
   // Send the message!
   app_message_outbox_send();
}


int Weather_GetImageID(char* s_WeatherImageName)
{
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
      
   printf("Unknown weather image %s\n",s_WeatherImageName);
   return RESOURCE_ID_IMAGE_ERROR;
}