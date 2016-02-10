#include "battery.h"

TextLayer* Layer_Battery_Text_Phone = NULL;
TextLayer* Layer_Battery_Text_Pebble = NULL;
BitmapLayer* Layer_Battery_Image_Pebble = NULL;
BitmapLayer* Layer_Battery_Image_Phone = NULL;

GBitmap *Image_Battery_Phone;
GBitmap *Image_Battery_Pebble;

bool FirstPhoneBattery;

int BatteryLevelPhone;
int BatteryLevelPebble;
bool BatteryStatePhone;
bool BatteryStatePebble;

void ColorBatteryImagePhone(int Image_ID, GColor Color)
{
   if (Layer_Battery_Image_Phone == NULL)
      return;
   
   bitmap_layer_set_bitmap(Layer_Battery_Image_Phone, NULL);
   if (Image_Battery_Phone)
   {
      gbitmap_destroy(Image_Battery_Phone);
      Image_Battery_Phone = NULL;
   }         
   Image_Battery_Phone = gbitmap_create_with_resource(Image_ID);
   replace_gbitmap_color(GColorWhite, Color, Image_Battery_Phone, NULL);
   replace_gbitmap_color(GColorBlack,  Color_Window, Image_Battery_Phone, NULL);
   bitmap_layer_set_bitmap(Layer_Battery_Image_Phone, Image_Battery_Phone);
   layer_mark_dirty(bitmap_layer_get_layer(Layer_Battery_Image_Phone));
}  

void ColorBatteryImagePebble(int Image_ID, GColor Color)
{
   if (Layer_Battery_Image_Pebble == NULL)
      return;
   
   bitmap_layer_set_bitmap(Layer_Battery_Image_Pebble, NULL);
   if (Image_Battery_Pebble)
   {
      gbitmap_destroy(Image_Battery_Pebble);
      Image_Battery_Pebble = NULL;
   }         
   Image_Battery_Pebble = gbitmap_create_with_resource(Image_ID);
   replace_gbitmap_color(GColorWhite, Color, Image_Battery_Pebble, NULL);
   replace_gbitmap_color(GColorBlack,  Color_Window, Image_Battery_Pebble, NULL);
   bitmap_layer_set_bitmap(Layer_Battery_Image_Pebble, Image_Battery_Pebble);
   layer_mark_dirty(bitmap_layer_get_layer(Layer_Battery_Image_Pebble));
}   

static void handle_battery(BatteryChargeState charge_state) 
{
   BatteryLevelPebble = charge_state.charge_percent;
   BatteryStatePebble = charge_state.is_charging;
   RedrawPebbleBattery();
   
}

void RequestBattery()
{
     // Begin dictionary
     DictionaryIterator *iter;
     app_message_outbox_begin(&iter);
   
     // Add a key-value pair
     dict_write_uint8(iter, KEY_BATTERY_CHARGE, 0);
   
     // Send the message!
     app_message_outbox_send();
}

void HandleBatteryReply(Tuple *batterycharge_tuple,Tuple *batterystate_tuple)
{
   show_PhoneBattery(true);
   
   BatteryLevelPhone = (int)batterycharge_tuple->value->int32;
   BatteryStatePhone = (int)batterystate_tuple->value->int32;
   RedrawPhoneBattery();
}

void RedrawPhoneBattery()
{
   static char battery_text[5];
   
   if (Layer_Battery_Text_Phone == NULL)
      return;
  
   if (BatteryLevelPhone < 30)
   {
      text_layer_set_text_color(Layer_Battery_Text_Phone, Color_BatteryLow);
      ColorBatteryImagePhone(RESOURCE_ID_IMAGE_BATTERY_LOW,Color_BatteryLow);
   }
   else if (BatteryLevelPhone < 60)
   {
      text_layer_set_text_color(Layer_Battery_Text_Phone, Color_Text);
      ColorBatteryImagePhone(RESOURCE_ID_IMAGE_BATTERY_MID, Color_Image);
   }
   else
   {
      text_layer_set_text_color(Layer_Battery_Text_Phone, Color_Text);
      ColorBatteryImagePhone(RESOURCE_ID_IMAGE_BATTERY_HIGH, Color_Image);
   }
   
   if (BatteryStatePhone)
   {
      text_layer_set_text_color(Layer_Battery_Text_Phone, Color_Charging);
   }
   
   if (BatteryLevelPhone > 99)
      snprintf(battery_text, sizeof(battery_text), "%d", BatteryLevelPhone);
   else
      snprintf(battery_text, sizeof(battery_text), "%d%%", BatteryLevelPhone);
   text_layer_set_text(Layer_Battery_Text_Phone, battery_text);
   layer_mark_dirty(text_layer_get_layer(Layer_Battery_Text_Phone));
   
}

void RedrawPebbleBattery()
{
   static char battery_text[5];
   if (Layer_Battery_Text_Pebble == NULL)
      return;
   
   if (BatteryLevelPebble < 30)
   {
      text_layer_set_text_color(Layer_Battery_Text_Pebble, Color_BatteryLow);
      ColorBatteryImagePebble(RESOURCE_ID_IMAGE_BATTERY_LOW,Color_BatteryLow);
   }
   else if (BatteryLevelPebble < 60)
   {
      text_layer_set_text_color(Layer_Battery_Text_Pebble, Color_Text);
      ColorBatteryImagePebble(RESOURCE_ID_IMAGE_BATTERY_MID, Color_Image);
   }
   else
   {
      text_layer_set_text_color(Layer_Battery_Text_Pebble, Color_Text);
      ColorBatteryImagePebble(RESOURCE_ID_IMAGE_BATTERY_HIGH, Color_Image);
   }
   
   if (BatteryStatePebble)
   {
      text_layer_set_text_color(Layer_Battery_Text_Pebble, Color_Charging);
   }
   
   if (BatteryLevelPebble > 99)
      snprintf(battery_text, sizeof(battery_text), "%d", BatteryLevelPebble);
   else
      snprintf(battery_text, sizeof(battery_text), "%d%%", BatteryLevelPebble);
   text_layer_set_text(Layer_Battery_Text_Pebble, battery_text);
   layer_mark_dirty(text_layer_get_layer(Layer_Battery_Text_Pebble));
}

void RedrawBattery()
{
   RedrawPhoneBattery();
   RedrawPebbleBattery();
}


void InitBattery()
{
   Layer_Battery_Text_Pebble =  GetBatteryTextLayerPebble();
   Layer_Battery_Image_Pebble = GetBatteryImageLayerPebble();
   Layer_Battery_Text_Phone =   GetBatteryTextLayerPhone();
   Layer_Battery_Image_Phone =  GetBatteryImageLayerPhone();
   show_PhoneBattery(false);
   battery_state_service_subscribe(handle_battery);
   handle_battery(battery_state_service_peek());
}

void DeInitBattery()
{
   battery_state_service_unsubscribe();
   if (Image_Battery_Phone)
   {
      gbitmap_destroy(Image_Battery_Phone);
      Image_Battery_Phone = NULL;
   }
      
   if (Image_Battery_Pebble)
   {
      gbitmap_destroy(Image_Battery_Pebble);
      Image_Battery_Pebble = NULL;
   }
      
}