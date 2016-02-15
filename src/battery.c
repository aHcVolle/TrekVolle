#include "battery.h"

// Phone battery vars
struct BatteryData
{
   TextLayer*   l_Text;
   BitmapLayer* l_Image;
   GBitmap*     bmp_Image;
   int i_BatteryLevel;
   bool b_ChargingState;
   bool b_FirstValue;
   char s_Text[5];
};

struct BatteryData m_BatteryPhone;
struct BatteryData m_BatteryPebble;

void BatteryRedrawImage(struct BatteryData* Battery,int Image_ID,GColor Color)
{
   if (Battery->l_Image == NULL)
      return;
   
   bitmap_layer_set_bitmap(Battery->l_Image, NULL);
   if (Battery->bmp_Image)
   {
      gbitmap_destroy(Battery->bmp_Image);
      Battery->bmp_Image = NULL;
   }         
   Battery->bmp_Image = gbitmap_create_with_resource(Image_ID);
   replace_gbitmap_color(GColorWhite, Color, Battery->bmp_Image, NULL);
   replace_gbitmap_color(GColorBlack,  Color_Window, Battery->bmp_Image, NULL);
   bitmap_layer_set_bitmap(Battery->l_Image, Battery->bmp_Image);
   layer_mark_dirty(bitmap_layer_get_layer(Battery->l_Image));
}



void Battery_RequestPhone()
{
     // Begin dictionary
     DictionaryIterator *iter;
     app_message_outbox_begin(&iter);
   
     // Add a key-value pair
     dict_write_uint8(iter, KEY_BATTERY_CHARGE, 0);
   
     // Send the message!
     app_message_outbox_send();
}



void Battery_Redraw(struct BatteryData* Battery)
{
   
   if (Battery->l_Text == NULL)
      return;
  
   if (Battery->i_BatteryLevel < 30)
   {
      text_layer_set_text_color(Battery->l_Text, Color_BatteryLow);
      BatteryRedrawImage(Battery,RESOURCE_ID_IMAGE_BATTERY_LOW,Color_BatteryLow);
   }
   else if (Battery->i_BatteryLevel < 60)
   {
      text_layer_set_text_color(Battery->l_Text, Color_Text);
      BatteryRedrawImage(Battery,RESOURCE_ID_IMAGE_BATTERY_MID,Color_Image);
   }
   else
   {
      text_layer_set_text_color(Battery->l_Text, Color_Text);
      BatteryRedrawImage(Battery,RESOURCE_ID_IMAGE_BATTERY_HIGH,Color_Image);
   }
   
   if (Battery->b_ChargingState )
   {
      text_layer_set_text_color(Battery->l_Text, Color_Charging);
   }
   
   if (Battery->i_BatteryLevel > 99)
      snprintf(Battery->s_Text, sizeof(Battery->s_Text), "%d", Battery->i_BatteryLevel);
   else
      snprintf(Battery->s_Text, sizeof(Battery->s_Text), "%d%%", Battery->i_BatteryLevel);
   text_layer_set_text(Battery->l_Text, Battery->s_Text);
   layer_mark_dirty(text_layer_get_layer(Battery->l_Text));
   
}

static void Battery_Handle_Pebble(BatteryChargeState charge_state) 
{
   m_BatteryPebble.i_BatteryLevel = charge_state.charge_percent;
   m_BatteryPebble.b_ChargingState = charge_state.is_charging;
   Battery_Redraw(&m_BatteryPebble);
}

void Battery_Handle_Phone(int i_BatteryLevel,bool b_ChargingState)
{
   show_PhoneBattery(true);
   
   m_BatteryPhone.i_BatteryLevel = i_BatteryLevel;
   m_BatteryPhone.b_ChargingState = b_ChargingState;
   Battery_Redraw(&m_BatteryPhone);
}

void Battery_RedrawAll()
{
   Battery_Redraw(&m_BatteryPhone);
   Battery_Redraw(&m_BatteryPebble);
}


void Battery_Init()
{
   m_BatteryPebble.l_Text =  GetBatteryTextLayerPebble();
   m_BatteryPebble.l_Image = GetBatteryImageLayerPebble();
   m_BatteryPhone.l_Text =   GetBatteryTextLayerPhone();
   m_BatteryPhone.l_Image =  GetBatteryImageLayerPhone();
   show_PhoneBattery(false);
   battery_state_service_subscribe(Battery_Handle_Pebble);
   Battery_Handle_Pebble(battery_state_service_peek());
}

void Battery_Deinit()
{
   battery_state_service_unsubscribe();
   if (m_BatteryPhone.bmp_Image)
   {
      gbitmap_destroy(m_BatteryPhone.bmp_Image);
      m_BatteryPhone.bmp_Image = NULL;
   }
      
   if (m_BatteryPebble.bmp_Image)
   {
      gbitmap_destroy(m_BatteryPebble.bmp_Image);
      m_BatteryPebble.bmp_Image = NULL;
   }
      
}