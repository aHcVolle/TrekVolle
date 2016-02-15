#include "communication.h"

static void Communication_InboxReceived(DictionaryIterator *iterator, void *context) 
{
   
   bool b_NewImageConfig = false;
   // Read tuples for data
   Tuple *Temperature_tuple = dict_find(iterator, KEY_TEMPERATURE);
   Tuple *Condition_tuple = dict_find(iterator, KEY_CONDITIONS);
   Tuple *Image_tuple = dict_find(iterator, KEY_ICON);
   Tuple *Location_tuple = dict_find(iterator,KEY_LOCATION);
   Tuple *Network_tuple = dict_find(iterator,KEY_ONLINE);
   Tuple *Batterycharge_tuple = dict_find(iterator,KEY_BATTERY_CHARGE);
   Tuple *Batterystate_tuple = dict_find(iterator,KEY_BATTERY_STATE);
   
   Tuple *Color_Background_tuple = dict_find(iterator,KEY_COLOR_BACKGROUND);
   Tuple *Color_Text_tuple = dict_find(iterator,KEY_COLOR_TEXT);
   Tuple *Color_Image_tuple = dict_find(iterator,KEY_COLOR_IMAGE);
   Tuple *Color_Window_tuple = dict_find(iterator,KEY_COLOR_WINDOW);
   Tuple *Color_Charging_tuple = dict_find(iterator,KEY_COLOR_CHARGING);
   Tuple *Color_Error_tuple = dict_find(iterator,KEY_COLOR_ERROR);
   Tuple *Color_BatteryLow_tuple = dict_find(iterator,KEY_COLOR_BATTERYLOW);
   
   Tuple *Weather_TemperatureCelcius_tuple = dict_find(iterator,KEY_WEATHER_TEMPERATURECELCIUS);
   Tuple *Weather_Refreshtime_tuple = dict_find(iterator,KEY_WEATHER_REFRESHTIME);
   Tuple *Weather_RetryUpdate_tuple = dict_find(iterator,KEY_WEATHER_RETRYUPDATE);
   
   Tuple *Clock_Clock24h_tuple = dict_find(iterator,KEY_CLOCK_CLOCK24H);
   Tuple *Clock_DateStyle_tuple = dict_find(iterator,KEY_CLOCK_DATESTYLE);
   
   Tuple *Network_Refreshtime_tuple = dict_find(iterator,KEY_NETWORK_REFRESHTIME);   
   Tuple *Network_VibrationEnabled_tuple = dict_find(iterator,KEY_NETWORK_VIBRATIONENABLED);
   
   Tuple *Bluetooth_VibrationEnabled_tuple = dict_find(iterator,KEY_BLUETOOTH_VIBRATIONENABLED);

   if(Temperature_tuple && Condition_tuple && Location_tuple && Image_tuple) 
      Weather_Handle(Temperature_tuple,Condition_tuple,Location_tuple,Image_tuple);

   if (Network_tuple)
      Network_Handle_Reply(Network_tuple);
   
   if (Batterycharge_tuple && Batterystate_tuple)
      Battery_Handle_Phone( (int)Batterycharge_tuple->value->int32, (bool)Batterystate_tuple->value->int32);
   
   
   if (Color_Background_tuple)
   {
      b_NewImageConfig = true;
      Color_Background = GColorFromHEX((int)Color_Background_tuple->value->int32);
   }
      
      
   if (Color_Text_tuple)
   {
      b_NewImageConfig = true;
      Color_Text = GColorFromHEX((int)Color_Text_tuple->value->int32);
   }
      
   
   if (Color_Image_tuple)
   {
      b_NewImageConfig = true;
      Color_Image = GColorFromHEX((int)Color_Image_tuple->value->int32);
   }
      
      
   if (Color_Window_tuple)
   {
      b_NewImageConfig = true;
      Color_Window = GColorFromHEX((int)Color_Window_tuple->value->int32);
   }
      
      
   if (Color_Charging_tuple)
   {
      b_NewImageConfig = true;
      Color_Charging = GColorFromHEX((int)Color_Charging_tuple->value->int32);
   }
      
      
   if (Color_Error_tuple)
   {
      b_NewImageConfig = true;
      Color_Error = GColorFromHEX((int)Color_Error_tuple->value->int32);
   }
      
       
   if (Color_BatteryLow_tuple)
   {
      b_NewImageConfig = true;
      Color_BatteryLow = GColorFromHEX((int)Color_BatteryLow_tuple->value->int32);
   }
   
   if (b_NewImageConfig)
   {
      Color_SetImageColor();
      Bluetooth_Redraw();
      Network_Redraw();
      Battery_RedrawAll();
      Weather_RedrawImage();
   }
      
   
   if (Weather_TemperatureCelcius_tuple)
   {
      m_b_Weather_TemperatureInCelcius = (bool)Weather_TemperatureCelcius_tuple->value->int32;
      Weather_RedrawText();
   }
   if (Weather_Refreshtime_tuple)
   {
      m_i_Weather_RefreshTime = (int)Weather_Refreshtime_tuple->value->int32;
   }
   if (Weather_RetryUpdate_tuple)
   {
      m_b_Weather_RetryUpdate = (bool)Weather_RetryUpdate_tuple->value->int32;
   }
   
      
   bool b_ClockChanged = false;
   if (Clock_Clock24h_tuple)
   {
      m_b_Clock_Clock24h = (bool)Clock_Clock24h_tuple->value->int32;
      b_ClockChanged = true;
   }
      
   
   if (Clock_DateStyle_tuple)
   {
      m_i_Clock_DateStyle = (int)Clock_DateStyle_tuple->value->int32;
      b_ClockChanged = true;
   }
   
   if (b_ClockChanged)
   {
      Time_Redraw();
   }
      
   
   if (Network_Refreshtime_tuple)
   {
      m_i_Network_RefreshTime = (int)Network_Refreshtime_tuple->value->int32;
   }
   
   if (Network_VibrationEnabled_tuple)
   {
      m_b_Network_VibrationEnabled = (bool)Network_VibrationEnabled_tuple->value->int32;
   }
   
   if (Bluetooth_VibrationEnabled_tuple)
   {
      m_b_Bluetooth_VibrationEnabled = (bool)Bluetooth_VibrationEnabled_tuple->value->int32;  
   }

}

static void Communication_InboxDropped(AppMessageResult reason, void *context) 
{
  //APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void Communication_OutboxFailed(DictionaryIterator *iterator, AppMessageResult reason, void *context) 
{
  //APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void Communication_OutboxSent(DictionaryIterator *iterator, void *context) 
{
  //APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}


void Communication_Init()
{
   
   // Register callbacks
   app_message_register_inbox_received(Communication_InboxReceived);
   app_message_register_inbox_dropped(Communication_InboxDropped);
   app_message_register_outbox_failed(Communication_OutboxFailed);
   app_message_register_outbox_sent(Communication_OutboxSent);
   
   // Open AppMessage
   app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
   
}

void Communication_DeInit()
{
   app_message_deregister_callbacks();   
}