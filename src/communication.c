#include "communication.h"

// Replies from javascript will be processed here 
static void Communication_InboxReceived(DictionaryIterator *iterator, void *context) 
{
   if (m_b_Debug)
      printf("[COM][Communication_InboxReceived] Received data");
   
   // Var to save if an image has been altered
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
   Tuple *Clock_Sleep_tuple = dict_find(iterator,KEY_CLOCK_SLEEP);
   
   Tuple *Network_Refreshtime_tuple = dict_find(iterator,KEY_NETWORK_REFRESHTIME);   
   Tuple *Network_VibrationEnabled_tuple = dict_find(iterator,KEY_NETWORK_VIBRATIONENABLED);
   
   Tuple *Bluetooth_VibrationEnabled_tuple = dict_find(iterator,KEY_BLUETOOTH_VIBRATIONENABLED);

   // Process the received tuples
   
   // If there was a weather update send the data
   if(Temperature_tuple && Condition_tuple && Location_tuple && Image_tuple) 
      Weather_Handle(Temperature_tuple,Condition_tuple,Location_tuple,Image_tuple);

   // If there was a network check
   if (Network_tuple)
      Network_Handle_Reply(Network_tuple);
   
   // If there were new phone battery status
   if (Batterycharge_tuple && Batterystate_tuple)
      Battery_Handle_Phone( (int)Batterycharge_tuple->value->int32, (bool)Batterystate_tuple->value->int32);
   
   // Here are all the color options
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
   
   // If the image color was changed lets redraw the images
   if (b_NewImageConfig)
   {
      Color_SetImageColor();
      Bluetooth_Redraw();
      Network_Redraw();
      Battery_RedrawAll();
      Weather_RedrawImage();
   }
      
   // If the temperature unit was changed
   if (Weather_TemperatureCelcius_tuple)
   {
      m_b_Weather_TemperatureInCelcius = (bool)Weather_TemperatureCelcius_tuple->value->int32;
      Weather_RedrawText();
   }
   // If the weather redrawtime was changed
   if (Weather_Refreshtime_tuple)
   {
      m_i_Weather_RefreshTime = (int)Weather_Refreshtime_tuple->value->int32;
   }
   // If the option to retry the weather update was changed
   if (Weather_RetryUpdate_tuple)
   {
      m_b_Weather_RetryUpdate = (bool)Weather_RetryUpdate_tuple->value->int32;
   }
   
   // Save if there was a change in the clock display   
   bool b_ClockChanged = false;
   // The clock mode was changed
   if (Clock_Clock24h_tuple)
   {
      m_b_Clock_Clock24h = (bool)Clock_Clock24h_tuple->value->int32;
      b_ClockChanged = true;
   }      
   // The datestyle was changed
   if (Clock_DateStyle_tuple)
   {
      m_i_Clock_DateStyle = (int)Clock_DateStyle_tuple->value->int32;
      b_ClockChanged = true;
   }
   // The sleep mode was changed
   if (Clock_Sleep_tuple)
   {
      m_b_Clock_Sleep = (bool)Clock_Sleep_tuple->value->int32;
   }
   
   // If there was a change in the clock 
   if (b_ClockChanged)
   {
      Time_Redraw();
   }
      
   // The network refresh time was changed
   if (Network_Refreshtime_tuple)
   {
      m_i_Network_RefreshTime = (int)Network_Refreshtime_tuple->value->int32;
   }
   // The network vibration settings have been changed
   if (Network_VibrationEnabled_tuple)
   {
      m_b_Network_VibrationEnabled = (bool)Network_VibrationEnabled_tuple->value->int32;
   }
   // The bluetooth vibration option has been changed
   if (Bluetooth_VibrationEnabled_tuple)
   {
      m_b_Bluetooth_VibrationEnabled = (bool)Bluetooth_VibrationEnabled_tuple->value->int32;  
   }

}

void Communication_Send(int i_MessageID)
{
   if (m_b_Debug)
      printf("[COM][Communication_Send] Sending data");
   // Begin dictionary
   DictionaryIterator *iter;
   app_message_outbox_begin(&iter);
   
   // Add a key-value pair
   dict_write_uint8(iter,i_MessageID , 0);
   
   // Send the message!
   app_message_outbox_send();
}

// Nothing to see here...
static void Communication_InboxDropped(AppMessageResult reason, void *context) {}
static void Communication_OutboxFailed(DictionaryIterator *iterator, AppMessageResult reason, void *context) {}
static void Communication_OutboxSent(DictionaryIterator *iterator, void *context) {}

// Register with the app messaging service
void Communication_Init()
{
   if (m_b_Debug)
      printf("[COM][Communication_Init] COM Init");
   // Register callbacks
   app_message_register_inbox_received(Communication_InboxReceived);
   app_message_register_inbox_dropped(Communication_InboxDropped);
   app_message_register_outbox_failed(Communication_OutboxFailed);
   app_message_register_outbox_sent(Communication_OutboxSent);
   
   // Open AppMessage
   //app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
   app_message_open(1000, 1000);
   
}

// Unregister from the messaging service
void Communication_DeInit()
{
   if (m_b_Debug)
      printf("[COM][Communication_DeInit] COM Deinit");
   
   app_message_deregister_callbacks();   
}