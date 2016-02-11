#include "weather.h"
TextLayer* Layer_Weather_Text;
static BitmapLayer* Layer_Weather_Image = NULL;
static GBitmap *Image_Weather;

static char conditions_buffer[32];
static char location_buffer[32];
static char weather_layer_buffer[32];

int WeatherImage;

int Temperature;

void RedrawWeatherText()
{
   if (!LastWeatherUpdateWasOK)
   {
      RequestWeather();
      return;
   }
      
   if (DisplayState == DISPLAY_CONDITIONS)
   {
      if (TemperatureInCelcius)
         snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%d°C, %s", Temperature, conditions_buffer);
      else
      {
         float Fahrenheit = Temperature * 1.8 + 32;
         snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%d°F, %s", (int)Fahrenheit, conditions_buffer);
      }
   }      
   else
      snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s", location_buffer);
      
   text_layer_set_text(Layer_Weather_Text, weather_layer_buffer);
   layer_mark_dirty(text_layer_get_layer(Layer_Weather_Text));
}

void RedrawWeatherImage()
{
   if (Layer_Weather_Image == NULL)
      return;
   
   bitmap_layer_set_bitmap(Layer_Weather_Image, NULL);
   if (Image_Weather)
   {
      gbitmap_destroy(Image_Weather);
      Image_Weather = NULL;
   }
         
   Image_Weather = gbitmap_create_with_resource(WeatherImage);
   replace_gbitmap_color(GColorWhite, Color_Image, Image_Weather, NULL);
   replace_gbitmap_color(GColorBlack,  Color_Window, Image_Weather, NULL);
   bitmap_layer_set_bitmap(Layer_Weather_Image, Image_Weather);
   layer_mark_dirty(bitmap_layer_get_layer(Layer_Weather_Image));
}

void RedrawWeather()
{
   RedrawWeatherText();
   RedrawWeatherImage();
}


void HandleWeather(Tuple *Temperature_tuple,Tuple *Condition_tuple,Tuple *Location_tuple,Tuple *Image_tuple)
{
   if(Temperature_tuple) 
   {
      Temperature = (int)Temperature_tuple->value->int32;
      LastWeatherUpdateWasOK = true;
   }
   
   if(Condition_tuple)
   {
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", Condition_tuple->value->cstring);
      LastWeatherUpdateWasOK = true;
   }
      
   if(Location_tuple) 
   {
      snprintf(location_buffer, sizeof(location_buffer), "%s", Location_tuple->value->cstring);
      LastWeatherUpdateWasOK = true;
   }
   
   if (Image_tuple)
   {  
      WeatherImage = imagename2resid(Image_tuple->value->cstring);
      RedrawWeatherImage();
   }
   
   RedrawWeatherText();
}

void InitWeather()
{
   LastWeatherUpdateWasOK = false;
   DisplayState = DISPLAY_CONDITIONS;
   Layer_Weather_Text = GetWeatherTextLayer();
   Layer_Weather_Image = GetWeatherImageLayer(); 
   
   WeatherImage = RESOURCE_ID_IMAGE_ERROR;
   RedrawWeatherImage();
}

void DeInitWeather()
{
   if (Image_Weather)
   {
      gbitmap_destroy(Image_Weather);
      Image_Weather = NULL;
   }  
}

void RequestWeather()
{
   LastWeatherUpdateWasOK = false;

   //printf("C: requesting weather update...\n");
   // Begin dictionary
   DictionaryIterator *iter;
   app_message_outbox_begin(&iter);
   
   // Add a key-value pair
   dict_write_uint8(iter, KEY_TEMPERATURE, 0);
   
   // Send the message!
   app_message_outbox_send();
}


int imagename2resid(char* imagename)
{
   if (strcmp(imagename,"01d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_01;
   else if (strcmp(imagename,"01n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_01;
   else if (strcmp(imagename,"02d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_02;
   else if (strcmp(imagename,"02n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_02;
   else if (strcmp(imagename,"03d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_03;
   else if (strcmp(imagename,"03n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_03;
   else if (strcmp(imagename,"04d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_04;
   else if (strcmp(imagename,"04n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_04;
   else if (strcmp(imagename,"09d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_09;
   else if (strcmp(imagename,"09n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_09;
   else if (strcmp(imagename,"10d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_10;
   else if (strcmp(imagename,"10n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_10;
   else if (strcmp(imagename,"11d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_11;
   else if (strcmp(imagename,"11n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_11;   
   else if (strcmp(imagename,"13d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_13;
   else if (strcmp(imagename,"13n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_13;
   else if (strcmp(imagename,"50d") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_50;
   else if (strcmp(imagename,"50n") == 0)
      return RESOURCE_ID_IMAGE_WEATHER_50;
      
   printf("Unknown weather image %s\n",imagename);
   return RESOURCE_ID_IMAGE_ERROR;
}