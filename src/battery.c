#include "battery.h"

// Battery struct
struct BatteryData
{
   TextLayer*   l_Text;
   BitmapLayer* l_Image;
   GBitmap*     bmp_Image;
   int i_BatteryLevel;
   bool b_ChargingState;
   bool b_FirstValue;
   char s_Text[5];
   GColor c_Color;
   int i_ImageID;
};

// Battery vars
struct BatteryData m_BatteryPhone;
struct BatteryData m_BatteryPebble;

// Redraw an battery image
void Battery_RedrawImage(struct BatteryData* Battery,int Image_ID,GColor Color)
{
   if (m_b_Debug)
      printf("[BATT] Redrawing battery image");
   Redraw_Image(Battery->l_Image,Battery->bmp_Image,Image_ID,Color);
}

// Request the phone's battery state (not used anywhere but ....)
void Battery_RequestPhone()
{
   // Only do this if bluetooth is connected
   if (!m_b_Bluetooth_ConnectionState)
      return;
   
   if (m_b_Debug)
      printf("[BATT] Phone battery requested");
   // Begin a dictionary
   DictionaryIterator *iter;
   app_message_outbox_begin(&iter);
   // Add a key-value pair
   dict_write_uint8(iter, KEY_BATTERY_CHARGE, 0);
   // Send the message!
   app_message_outbox_send();
}

// Redraw all battery related things
void Battery_Redraw(struct BatteryData* Battery)
{
   // Vars to hold the new settings
   int i_ImageID;
   GColor BatteryColor;
   GColor TextColor;
   
   // Get out of here if there's no text layer 
   if (Battery->l_Text == NULL)
      return;  

   // See if we have a low battery ...
   if (Battery->i_BatteryLevel < 30)
   {
      TextColor = Color_BatteryLow;
      i_ImageID = RESOURCE_ID_IMAGE_BATTERY_LOW;
      BatteryColor = Color_BatteryLow;
   }
   // ... or if the battery level is in the middle
   else if (Battery->i_BatteryLevel < 60)
   {
      TextColor = Color_Text;
      i_ImageID = RESOURCE_ID_IMAGE_BATTERY_MID;
      BatteryColor = Color_Image;
   }
   // Or if it is almost full
   else
   {
      TextColor = Color_Text;
      i_ImageID = RESOURCE_ID_IMAGE_BATTERY_HIGH;
      BatteryColor = Color_Image;
   }
   
   // Check if the battery is charging
   if (Battery->b_ChargingState )
   {
      TextColor = Color_Charging;
   }
   
   // If some of the image data changed redraw it
   if ((!gcolor_equal(Battery->c_Color,BatteryColor)) || (Battery->i_ImageID != i_ImageID))
   {
      if (m_b_Debug)
         printf("[BATT] Redrawing battery image");
      Battery->c_Color = BatteryColor;
      Battery->i_ImageID = i_ImageID;
      Battery_RedrawImage(Battery,Battery->i_ImageID,Battery->c_Color);
   }

   // Cap the displayed text at 3 chars
   if (Battery->i_BatteryLevel > 99)
      snprintf(Battery->s_Text, sizeof(Battery->s_Text), "%d", Battery->i_BatteryLevel);
   else
      snprintf(Battery->s_Text, sizeof(Battery->s_Text), "%d%%", Battery->i_BatteryLevel);
   if (m_b_Debug)
         printf("[BATT] Redrawing battery text");
   
   // Draw the battery's text
   text_layer_set_text_color(Battery->l_Text, TextColor);
   text_layer_set_text(Battery->l_Text, Battery->s_Text);
   layer_mark_dirty(text_layer_get_layer(Battery->l_Text));
   
}

// New battery data from the pebble is processed here
static void Battery_Handle_Pebble(BatteryChargeState charge_state) 
{
   // See if some data changed
   if ((m_BatteryPebble.i_BatteryLevel == charge_state.charge_percent) && (m_BatteryPebble.b_ChargingState == charge_state.is_charging))
   {
      //nothing changed
      return;
   }
   
   // Debug printout
   if (m_b_Debug)
      printf("[BATT] Pebble battery handler: %d %d",charge_state.charge_percent,(int)charge_state.is_charging);
   
   // Save the battery's new data
   m_BatteryPebble.i_BatteryLevel = charge_state.charge_percent;
   m_BatteryPebble.b_ChargingState = charge_state.is_charging;
   // And redraw its new data
   Battery_Redraw(&m_BatteryPebble);
}

// New battery data from the phone is processed here
void Battery_Handle_Phone(int i_BatteryLevel,bool b_ChargingState)
{
   // see if some data changed
   if ((m_BatteryPhone.i_BatteryLevel == i_BatteryLevel) && (m_BatteryPhone.b_ChargingState == b_ChargingState))
   {
      //nothing changed
      return;
   }
   // Debug printout
   if (m_b_Debug)
      printf("[BATT] Phone battery handler: %d %d",i_BatteryLevel,(int)b_ChargingState);
   
   // Display the phone's battery data which else would be hidden 
   show_PhoneBattery(true);
   
   // Save the battery's new data
   m_BatteryPhone.i_BatteryLevel = i_BatteryLevel;
   m_BatteryPhone.b_ChargingState = b_ChargingState;
   // And redraw its new data
   Battery_Redraw(&m_BatteryPhone);
}

// Redraw both batteries 
void Battery_RedrawAll()
{
   if (m_b_Debug)
      printf("[BATT] Redrawing everything");
   Battery_Redraw(&m_BatteryPhone);
   Battery_Redraw(&m_BatteryPebble);
}

// Init the battery layers and register to the pebbles battery service
void Battery_Init()
{
   if (m_b_Debug)
      printf("[BATT] Init");
   m_BatteryPebble.l_Text =  GetBatteryTextLayerPebble();
   m_BatteryPebble.l_Image = GetBatteryImageLayerPebble();
   m_BatteryPhone.l_Text =   GetBatteryTextLayerPhone();
   m_BatteryPhone.l_Image =  GetBatteryImageLayerPhone();
   show_PhoneBattery(false);
   battery_state_service_subscribe(Battery_Handle_Pebble);
   Battery_Handle_Pebble(battery_state_service_peek());
}

// Unregister from pebbles battery service
void Battery_Deinit()
{
   if (m_b_Debug)
      printf("[BATT] Deinit");
   battery_state_service_unsubscribe();
   
   // Destroy all ze thingz!
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