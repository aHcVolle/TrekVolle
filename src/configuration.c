#include "configuration.h"

void HandleTemperatureInCelcius(bool b_TemperatureInCelcius)
{
   TemperatureInCelcius = b_TemperatureInCelcius;
   RedrawWeather();
}

void HandleClock24h(bool b_Clock24h)
{
   m_b_Clock24h = b_Clock24h;
   Time_Redraw();
}

void HandleDateStyle(int i_DateStyle)
{
   m_i_DateStyle = i_DateStyle;
   Time_Redraw();
}

void HandleNetworkRefreshTime(int i_NetworkRefreshTime)
{
   m_i_NetworkRefreshTime = i_NetworkRefreshTime;
}

void HandleBluetoothVibrationEnabled(bool b_VibrationEnabled)
{
   m_b_Bluetooth_VibrationEnabled = b_VibrationEnabled;   
}

void HandleNetworkVibrationEnabled(bool b_VibrationEnabled)
{
   m_b_Network_VibrationEnabled = b_VibrationEnabled;
}



void LoadConfigFromStorage()
{
   
   LoadDefaultConfig();
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
   
   
   if (persist_exists(KEY_TEMPERATURE_CELCIUS)) 
   {
     TemperatureInCelcius = persist_read_bool(KEY_TEMPERATURE_CELCIUS);
   }
   if (persist_exists(KEY_CLOCK_24H)) 
   {
     m_b_Clock24h = persist_read_bool(KEY_CLOCK_24H);
   }
   if (persist_exists(KEY_DATE_STYLE)) 
   {
     m_i_DateStyle = persist_read_int(KEY_DATE_STYLE);
   }
   if (persist_exists(KEY_NETWORK_REFRESHTIME)) 
   {
     m_i_NetworkRefreshTime = persist_read_int(KEY_NETWORK_REFRESHTIME);
   }
   
   if (persist_exists(KEY_BLUETOOTH_VIBRATIONENABLED)) 
   {
     m_b_Bluetooth_VibrationEnabled = persist_read_bool(KEY_BLUETOOTH_VIBRATIONENABLED);
   }
   if (persist_exists(KEY_NETWORK_VIBRATIONENABLED)) 
   {
     m_b_Network_VibrationEnabled = persist_read_bool(KEY_NETWORK_VIBRATIONENABLED);
   }
}

void SaveConfigToStorage()
{
   persist_write_int(KEY_COLOR_BACKGROUND, (int)Color_Background.argb);
   persist_write_int(KEY_COLOR_TEXT, (int)Color_Text.argb);
   persist_write_int(KEY_COLOR_IMAGE, (int)Color_Image.argb);
   persist_write_int(KEY_COLOR_WINDOW, (int)Color_Window.argb);
   persist_write_int(KEY_COLOR_CHARGING, (int)Color_Charging.argb);
   persist_write_int(KEY_COLOR_ERROR, (int)Color_Error.argb);
   persist_write_int(KEY_COLOR_BATTERYLOW, (int)Color_BatteryLow.argb);
         
   persist_write_bool(KEY_TEMPERATURE_CELCIUS, TemperatureInCelcius);
   persist_write_bool(KEY_CLOCK_24H, m_b_Clock24h);
   persist_write_int(KEY_DATE_STYLE, m_i_DateStyle);
   persist_write_int(KEY_NETWORK_REFRESHTIME, m_i_NetworkRefreshTime);
   
   persist_write_bool(KEY_BLUETOOTH_VIBRATIONENABLED, m_b_Bluetooth_VibrationEnabled);
   persist_write_bool(KEY_NETWORK_VIBRATIONENABLED, m_b_Network_VibrationEnabled);
   
}

void LoadDefaultConfig()
{
   Color_Background = GColorBlueMoon;
   Color_Text = GColorSunsetOrange;
   Color_Image = GColorSunsetOrange;
   Color_Window = GColorBlack;
   Color_Charging = GColorGreen;
   Color_Error = GColorRed;
   Color_BatteryLow = GColorRed;
   TemperatureInCelcius = true;
   m_i_NetworkRefreshTime = 1;
   m_i_DateStyle = DATE_DD_MM_YY;
   m_b_Clock24h = true;
   m_b_Network_VibrationEnabled = true;
   m_b_Bluetooth_VibrationEnabled = true;
}

