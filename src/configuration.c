#include "configuration.h"

// Load the stored vars from the non volatile storage
void LoadConfigFromStorage()
{
   // First load the default variables
   LoadDefaultConfig();
   
   // Debug printout
   #ifdef DEBUG_CONFIGURATION
         printf("[CONF][LoadConfigFromStorage] Loading");
   #endif
   
   // And now load the saved vars
   if (persist_exists(MESSAGE_KEY_COLOR_BACKGROUND)) 
   {
     Color_Background.argb = persist_read_int(MESSAGE_KEY_COLOR_BACKGROUND);
   }
   if (persist_exists(MESSAGE_KEY_COLOR_TEXT)) 
   {
     Color_Text.argb = persist_read_int(MESSAGE_KEY_COLOR_TEXT);
   }
   if (persist_exists(MESSAGE_KEY_COLOR_IMAGE)) 
   {
     Color_Image.argb = persist_read_int(MESSAGE_KEY_COLOR_IMAGE);
   }
   if (persist_exists(MESSAGE_KEY_COLOR_WINDOW)) 
   {
     Color_Window.argb = persist_read_int(MESSAGE_KEY_COLOR_WINDOW);
   }
   if (persist_exists(MESSAGE_KEY_COLOR_CHARGING)) 
   {
     Color_Charging.argb = persist_read_int(MESSAGE_KEY_COLOR_CHARGING);
   }
   if (persist_exists(MESSAGE_KEY_COLOR_ERROR)) 
   {
     Color_Error.argb = persist_read_int(MESSAGE_KEY_COLOR_ERROR);
   }
   if (persist_exists(MESSAGE_KEY_COLOR_BATTERYLOW)) 
   {
     Color_BatteryLow.argb = persist_read_int(MESSAGE_KEY_COLOR_BATTERYLOW);
   }
   if (persist_exists(MESSAGE_KEY_COLOR_CLOCK_HOUR)) 
   {
     Color_ClockHour.argb = persist_read_int(MESSAGE_KEY_COLOR_CLOCK_HOUR);
   }
   if (persist_exists(MESSAGE_KEY_COLOR_CLOCK_MIN)) 
   {
     Color_ClockMin.argb = persist_read_int(MESSAGE_KEY_COLOR_CLOCK_MIN);
   }
   
   if (persist_exists(MESSAGE_KEY_WEATHER_TEMPERATURECELCIUS)) 
   {
     m_b_Weather_TemperatureInCelcius = persist_read_bool(MESSAGE_KEY_WEATHER_TEMPERATURECELCIUS);
   }
   if (persist_exists(MESSAGE_KEY_WEATHER_REFRESHTIME)) 
   {
     m_i_Weather_RefreshTime = persist_read_int(MESSAGE_KEY_WEATHER_REFRESHTIME);
   }
   if (persist_exists(MESSAGE_KEY_WEATHER_RETRYUPDATE)) 
   {
     m_b_Weather_RetryUpdate = persist_read_bool(MESSAGE_KEY_WEATHER_RETRYUPDATE);
   }

   
   if (persist_exists(MESSAGE_KEY_CLOCK_CLOCK24H)) 
   {
     m_b_Clock_Clock24h = persist_read_bool(MESSAGE_KEY_CLOCK_CLOCK24H);
   }
   if (persist_exists(MESSAGE_KEY_CLOCK_DATESTYLE)) 
   {
     m_i_Clock_DateStyle = persist_read_int(MESSAGE_KEY_CLOCK_DATESTYLE);
   }
   if (persist_exists(MESSAGE_KEY_CLOCK_SLEEP)) 
   {
     m_b_Clock_Sleep = persist_read_bool(MESSAGE_KEY_CLOCK_SLEEP);
   }
   if (persist_exists(MESSAGE_KEY_CLOCK_DAYOFYEAR)) 
   {
     m_i_Clock_DayOfYear = persist_read_int(MESSAGE_KEY_CLOCK_DAYOFYEAR);
   }
   
   if (persist_exists(MESSAGE_KEY_NETWORK_REFRESHTIME)) 
   {
     m_i_Network_RefreshTime = persist_read_int(MESSAGE_KEY_NETWORK_REFRESHTIME);
   }
   if (persist_exists(MESSAGE_KEY_NETWORK_VIBRATIONENABLED)) 
   {
     m_b_Network_VibrationEnabled = persist_read_bool(MESSAGE_KEY_NETWORK_VIBRATIONENABLED);
   }
   
   if (persist_exists(MESSAGE_KEY_BLUETOOTH_VIBRATIONENABLED)) 
   {
     m_b_Bluetooth_VibrationEnabled = persist_read_bool(MESSAGE_KEY_BLUETOOTH_VIBRATIONENABLED);
   }
   
   if (persist_exists(MESSAGE_KEY_ACCELERATION_ENABLE)) 
   {
     m_b_Acceleration_Enabled = persist_read_bool(MESSAGE_KEY_ACCELERATION_ENABLE);
   }
   
}

// Save all the variables to the storage
void SaveConfigToStorage()
{
   // Debug printout
   #ifdef DEBUG_CONFIGURATION
         printf("[CONF][SaveConfigToStorage] Saving");
   #endif
   
   // And save
   persist_write_int(MESSAGE_KEY_COLOR_BACKGROUND, (int)Color_Background.argb);
   persist_write_int(MESSAGE_KEY_COLOR_TEXT, (int)Color_Text.argb);
   persist_write_int(MESSAGE_KEY_COLOR_IMAGE, (int)Color_Image.argb);
   persist_write_int(MESSAGE_KEY_COLOR_WINDOW, (int)Color_Window.argb);
   persist_write_int(MESSAGE_KEY_COLOR_CHARGING, (int)Color_Charging.argb);
   persist_write_int(MESSAGE_KEY_COLOR_ERROR, (int)Color_Error.argb);
   persist_write_int(MESSAGE_KEY_COLOR_BATTERYLOW, (int)Color_BatteryLow.argb);
   persist_write_int(MESSAGE_KEY_COLOR_CLOCK_HOUR, (int)Color_ClockHour.argb);
   persist_write_int(MESSAGE_KEY_COLOR_CLOCK_MIN,  (int)Color_ClockMin.argb);
         
   persist_write_bool(MESSAGE_KEY_WEATHER_TEMPERATURECELCIUS, m_b_Weather_TemperatureInCelcius);
   persist_write_int(MESSAGE_KEY_WEATHER_REFRESHTIME, m_i_Weather_RefreshTime);
   persist_write_bool(MESSAGE_KEY_WEATHER_RETRYUPDATE, m_b_Weather_RetryUpdate);
      
   persist_write_bool(MESSAGE_KEY_CLOCK_CLOCK24H, m_b_Clock_Clock24h);
   persist_write_int(MESSAGE_KEY_CLOCK_DATESTYLE, m_i_Clock_DateStyle);
   persist_write_bool(MESSAGE_KEY_CLOCK_SLEEP, m_b_Clock_Sleep);
   persist_write_int(MESSAGE_KEY_CLOCK_DAYOFYEAR, m_i_Clock_DayOfYear);
   
   persist_write_int(MESSAGE_KEY_NETWORK_REFRESHTIME, m_i_Network_RefreshTime);
   persist_write_bool(MESSAGE_KEY_NETWORK_VIBRATIONENABLED, m_b_Network_VibrationEnabled);   
   
   persist_write_bool(MESSAGE_KEY_BLUETOOTH_VIBRATIONENABLED, m_b_Bluetooth_VibrationEnabled);
   
   persist_write_bool(MESSAGE_KEY_ACCELERATION_ENABLE, m_b_Acceleration_Enabled);
    
}

// Init all variables to their default value
void LoadDefaultConfig()
{
   // Debug printout
   #ifdef DEBUG_CONFIGURATION
         printf("[CONF][LoadDefaultConfig] Setting defaults");
   #endif
   
   // Set the vars
   #ifdef PBL_COLOR
   Color_Background = GColorBlueMoon;
   Color_Text = GColorSunsetOrange;
   Color_Image = GColorSunsetOrange;
   Color_Window = GColorBlack;
   Color_Charging = GColorGreen;
   Color_Error = GColorRed;
   Color_BatteryLow = GColorRed;
   Color_ClockHour = GColorSunsetOrange;
   Color_ClockMin = GColorSunsetOrange;
   #else
   Color_Background = GColorWhite;
   Color_Text = GColorWhite;
   Color_Image = GColorWhite;
   Color_Window = GColorBlack;
   Color_Charging = GColorWhite;
   Color_Error = GColorBlack;
   Color_BatteryLow = GColorWhite;
   Color_ClockHour = GColorWhite;
   Color_ClockMin = GColorWhite;
   #endif
   
   m_b_Weather_TemperatureInCelcius = true;
   m_i_Weather_RefreshTime = 30;
   m_b_Weather_RetryUpdate = true;
      
   m_i_Clock_DateStyle = DATE_DD_MM_YY;
   m_b_Clock_Clock24h = clock_is_24h_style();
   m_b_Clock_Sleep = true;
   m_i_Clock_DayOfYear = DAY_DAYOFYEAR;
   
   m_i_Network_RefreshTime = 1;
   m_b_Network_VibrationEnabled = true;
   
   m_b_Bluetooth_VibrationEnabled = true;
   
   m_b_Acceleration_Enabled = true;
}

