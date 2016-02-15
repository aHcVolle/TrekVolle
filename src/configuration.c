#include "configuration.h"

void LoadConfigFromStorage()
{
   
   LoadDefaultConfig();
   
   if (m_b_Debug)
         printf("[CONF] Loading");
   
   if (persist_exists(KEY_COLOR_BACKGROUND)) 
   {
     Color_Background.argb = persist_read_int(KEY_COLOR_BACKGROUND);
   }
   if (persist_exists(KEY_COLOR_TEXT)) 
   {
     Color_Text.argb = persist_read_int(KEY_COLOR_TEXT);
   }
   if (persist_exists(KEY_COLOR_IMAGE)) 
   {
     Color_Image.argb = persist_read_int(KEY_COLOR_IMAGE);
   }
   if (persist_exists(KEY_COLOR_WINDOW)) 
   {
     Color_Window.argb = persist_read_int(KEY_COLOR_WINDOW);
   }
   if (persist_exists(KEY_COLOR_CHARGING)) 
   {
     Color_Charging.argb = persist_read_int(KEY_COLOR_CHARGING);
   }
   if (persist_exists(KEY_COLOR_ERROR)) 
   {
     Color_Error.argb = persist_read_int(KEY_COLOR_ERROR);
   }
   if (persist_exists(KEY_COLOR_BATTERYLOW)) 
   {
     Color_BatteryLow.argb = persist_read_int(KEY_COLOR_BATTERYLOW);
   }
   
   
   if (persist_exists(KEY_WEATHER_TEMPERATURECELCIUS)) 
   {
     m_b_Weather_TemperatureInCelcius = persist_read_bool(KEY_WEATHER_TEMPERATURECELCIUS);
   }
   if (persist_exists(KEY_WEATHER_REFRESHTIME)) 
   {
     m_i_Weather_RefreshTime = persist_read_int(KEY_WEATHER_REFRESHTIME);
   }
   if (persist_exists(KEY_WEATHER_RETRYUPDATE)) 
   {
     m_b_Weather_RetryUpdate = persist_read_bool(KEY_WEATHER_RETRYUPDATE);
   }
   
   if (persist_exists(KEY_CLOCK_CLOCK24H)) 
   {
     m_b_Clock_Clock24h = persist_read_bool(KEY_CLOCK_CLOCK24H);
   }
   if (persist_exists(KEY_CLOCK_DATESTYLE)) 
   {
     m_i_Clock_DateStyle = persist_read_int(KEY_CLOCK_DATESTYLE);
   }
   
   if (persist_exists(KEY_NETWORK_REFRESHTIME)) 
   {
     m_i_Network_RefreshTime = persist_read_int(KEY_NETWORK_REFRESHTIME);
   }
   if (persist_exists(KEY_NETWORK_VIBRATIONENABLED)) 
   {
     m_b_Network_VibrationEnabled = persist_read_bool(KEY_NETWORK_VIBRATIONENABLED);
   }
   
   if (persist_exists(KEY_BLUETOOTH_VIBRATIONENABLED)) 
   {
     m_b_Bluetooth_VibrationEnabled = persist_read_bool(KEY_BLUETOOTH_VIBRATIONENABLED);
   }
   
}

void SaveConfigToStorage()
{
   if (m_b_Debug)
         printf("[CONF] Saving");
   
   persist_write_int(KEY_COLOR_BACKGROUND, (int)Color_Background.argb);
   persist_write_int(KEY_COLOR_TEXT, (int)Color_Text.argb);
   persist_write_int(KEY_COLOR_IMAGE, (int)Color_Image.argb);
   persist_write_int(KEY_COLOR_WINDOW, (int)Color_Window.argb);
   persist_write_int(KEY_COLOR_CHARGING, (int)Color_Charging.argb);
   persist_write_int(KEY_COLOR_ERROR, (int)Color_Error.argb);
   persist_write_int(KEY_COLOR_BATTERYLOW, (int)Color_BatteryLow.argb);
         
   persist_write_bool(KEY_WEATHER_TEMPERATURECELCIUS, m_b_Weather_TemperatureInCelcius);
   persist_write_int(KEY_WEATHER_REFRESHTIME, m_i_Weather_RefreshTime);
   persist_write_bool(KEY_WEATHER_RETRYUPDATE, m_b_Weather_RetryUpdate);
      
   persist_write_bool(KEY_CLOCK_CLOCK24H, m_b_Clock_Clock24h);
   persist_write_int(KEY_CLOCK_DATESTYLE, m_i_Clock_DateStyle);
   
   persist_write_int(KEY_NETWORK_REFRESHTIME, m_i_Network_RefreshTime);
   persist_write_bool(KEY_NETWORK_VIBRATIONENABLED, m_b_Network_VibrationEnabled);   
   
   persist_write_bool(KEY_BLUETOOTH_VIBRATIONENABLED, m_b_Bluetooth_VibrationEnabled);
   
   
}

void LoadDefaultConfig()
{
   if (m_b_Debug)
         printf("[CONF] Setting defaults");
   
   Color_Background = GColorBlueMoon;
   Color_Text = GColorSunsetOrange;
   Color_Image = GColorSunsetOrange;
   Color_Window = GColorBlack;
   Color_Charging = GColorGreen;
   Color_Error = GColorRed;
   Color_BatteryLow = GColorRed;
   
   m_b_Weather_TemperatureInCelcius = true;
   m_i_Weather_RefreshTime = 30;
   m_b_Weather_RetryUpdate = true;
      
   m_i_Clock_DateStyle = DATE_DD_MM_YY;
   m_b_Clock_Clock24h = true;
   
   m_i_Network_RefreshTime = 1;
   m_b_Network_VibrationEnabled = true;
   
   m_b_Bluetooth_VibrationEnabled = true;
   
}

