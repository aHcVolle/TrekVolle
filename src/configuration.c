#include "configuration.h"

void HandleBackgroundColor(int RGB)
{
   Color_Background = GColorFromHEX(RGB);
   SetColor();
}

void HandleTextColor(int RGB)
{
   Color_Text = GColorFromHEX(RGB);
   SetColor();
}

void HandleImageColor(int RGB)
{
   Color_Image = GColorFromHEX(RGB);
   SetColor();
   RedrawBluetoothImage();
   RedrawNetworkImage();
   RedrawWeatherImage();
   RedrawBattery();
}

void HandleWindowColor(int RGB)
{
   Color_Window = GColorFromHEX(RGB);
   RedrawBluetoothImage();
   RedrawNetworkImage();
   RedrawWeatherImage();
   RedrawBattery();
   SetColor();
}

void HandleChargingColor(int RGB)
{
   Color_Charging = GColorFromHEX(RGB);
   SetColor();
   RedrawBattery();
}

void HandleErrorColor(int RGB)
{
   Color_Error = GColorFromHEX(RGB);
   SetColor();
   RedrawBluetoothImage();
   RedrawNetworkImage();
   RedrawBattery();
}

void HandleBatteryLowColor(int RGB)
{
   Color_BatteryLow = GColorFromHEX(RGB);
   SetColor();
   RedrawBattery();
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
   
}

