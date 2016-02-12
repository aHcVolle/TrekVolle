#include "communication.h"

static void inbox_received_callback(DictionaryIterator *iterator, void *context) 
{
   
   
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
   
   Tuple *TemperatureInCelcius_tuple = dict_find(iterator,KEY_TEMPERATURE_CELCIUS);
   Tuple *Clock24h_tuple = dict_find(iterator,KEY_CLOCK_24H);
   Tuple *DateStyle_tuple = dict_find(iterator,KEY_DATE_STYLE);
   Tuple *NetworkRefresh_tuple = dict_find(iterator,KEY_NETWORK_REFRESHTIME);
   
   Tuple *Network_VibrationEnabled_tuple = dict_find(iterator,KEY_NETWORK_VIBRATIONENABLED);
   Tuple *Bluetooth_VibrationEnabled_tuple = dict_find(iterator,KEY_NETWORK_VIBRATIONENABLED);

   if(Temperature_tuple && Condition_tuple && Location_tuple && Image_tuple) 
      HandleWeather(Temperature_tuple,Condition_tuple,Location_tuple,Image_tuple);

   if (Network_tuple)
      HandleNetworkReply(Network_tuple);
   
   if (Batterycharge_tuple && Batterystate_tuple)
      HandleBatteryReply(Batterycharge_tuple, Batterystate_tuple);
   
   
   if (Color_Background_tuple)
      HandleBackgroundColor((int)Color_Background_tuple->value->int32);
      
   if (Color_Text_tuple)
      HandleTextColor((int)Color_Text_tuple->value->int32);
   
   if (Color_Image_tuple)
      HandleImageColor((int)Color_Image_tuple->value->int32);
      
   if (Color_Window_tuple)
      HandleWindowColor((int)Color_Window_tuple->value->int32);
      
   if (Color_Charging_tuple)
      HandleChargingColor((int)Color_Charging_tuple->value->int32);
      
   if (Color_Error_tuple)
      HandleErrorColor((int)Color_Error_tuple->value->int32);
       
   if (Color_BatteryLow_tuple)
      HandleBatteryLowColor((int)Color_BatteryLow_tuple->value->int32);
   
   if (TemperatureInCelcius_tuple)
      HandleTemperatureInCelcius((bool)TemperatureInCelcius_tuple->value->int32);
   
   if (Clock24h_tuple)
      HandleClock24h((bool)Clock24h_tuple->value->int32);
   
   if (DateStyle_tuple)
      HandleDateStyle((int)DateStyle_tuple->value->int32);
   
   if (NetworkRefresh_tuple)
      HandleNetworkRefreshTime((int)NetworkRefresh_tuple->value->int32);
   
   if (Network_VibrationEnabled_tuple)
      HandleNetworkVibrationEnabled((bool)Network_VibrationEnabled_tuple->value->int32);
   
   if (Bluetooth_VibrationEnabled_tuple)
      HandleBluetoothVibrationEnabled((bool)Bluetooth_VibrationEnabled_tuple->value->int32);

}

static void inbox_dropped_callback(AppMessageResult reason, void *context) 
{
  //APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) 
{
  //APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) 
{
  //APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}


void InitCommunication()
{
   
   // Register callbacks
   app_message_register_inbox_received(inbox_received_callback);
   app_message_register_inbox_dropped(inbox_dropped_callback);
   app_message_register_outbox_failed(outbox_failed_callback);
   app_message_register_outbox_sent(outbox_sent_callback);
   
   // Open AppMessage
   app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
   
}

void DeInitCommunication()
{
   app_message_deregister_callbacks();   
}