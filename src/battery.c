#include "battery.h"



// Battery vars
struct BatteryData m_BatteryPhone = {NULL,NULL,999,false,true,{0,0,0,0,0},{0},-1};
struct BatteryData m_BatteryPebble = {NULL,NULL,999,false,true,{0,0,0,0,0},{0},-1};

// Redraw an battery image
void Battery_RedrawImage(struct BatteryData* Battery,int Image_ID,GColor Color)
{
   #ifdef DEBUG_BATTERY
      printf("[BATT][Battery_RedrawImage] Redrawing battery image");
   #endif
   Redraw_Image(Battery->p_ImageData,Image_ID,Color);
}

// Request the phone's battery state (not used anywhere but ....)
void Battery_RequestPhone()
{
   // Only do this if bluetooth is connected
   if (!m_b_Bluetooth_ConnectionState)
      return;
   
   // Only do this if the communication is already initialized
   if (!m_b_CommunicationIsInit)
      return;
   
   #ifdef DEBUG_BATTERY
      printf("[BATT][Battery_RequestPhone] Phone battery requested");
   #endif
   // Send the request
   Communication_Send(KEY_BATTERY_CHARGE);
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
      #ifdef DEBUG_BATTERY
         printf("[BATT][Battery_Redraw] Redrawing battery image");
      #endif
      Battery->c_Color = BatteryColor;
      Battery->i_ImageID = i_ImageID;
      Battery_RedrawImage(Battery,Battery->i_ImageID,Battery->c_Color);
   }

   // Cap the displayed text at 3 chars
   if (Battery->i_BatteryLevel > 99)
      snprintf(Battery->s_Text, sizeof(Battery->s_Text), "%d", Battery->i_BatteryLevel);
   else
      snprintf(Battery->s_Text, sizeof(Battery->s_Text), "%d%%", Battery->i_BatteryLevel);
   #ifdef DEBUG_BATTERY
         printf("[BATT][Battery_Redraw] Redrawing battery text");
   #endif
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
   #ifdef DEBUG_BATTERY
      printf("[BATT][Battery_Handle_Pebble] Pebble battery handler: %d %d",charge_state.charge_percent,(int)charge_state.is_charging);
   #endif
   // Save the battery's new data
   m_BatteryPebble.i_BatteryLevel = charge_state.charge_percent;
   m_BatteryPebble.b_ChargingState = charge_state.is_charging;
   // And redraw its new data
   Battery_Redraw(&m_BatteryPebble);
}

// New battery data from the phone is processed here
void Battery_Handle_Phone(int i_BatteryLevel,bool b_ChargingState)
{
   
   // Display the phone's battery data which else would be hidden 
   show_PhoneBattery(true);
   
   // see if some data changed
   if ((m_BatteryPhone.i_BatteryLevel == i_BatteryLevel) && (m_BatteryPhone.b_ChargingState == b_ChargingState))
   {
      //nothing changed
      return;
   }
   // Debug printout
   #ifdef DEBUG_BATTERY
      printf("[BATT][Battery_Handle_Phone] Phone battery handler: %d %d",i_BatteryLevel,(int)b_ChargingState);
   #endif
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
   #ifdef DEBUG_BATTERY
      printf("[BATT][Battery_RedrawAll] Redrawing everything");
   #endif
   // Redraw the pebble battery
   Battery_Redraw(&m_BatteryPebble);
   // Redraw the phone battery
   if ((m_BatteryPhone.p_ImageData != NULL) && (m_BatteryPhone.p_ImageData->thisLayer != NULL) && !layer_get_hidden((Layer *)m_BatteryPhone.p_ImageData->thisLayer))
      Battery_Redraw(&m_BatteryPhone);
}

// Init the battery layers and register to the pebbles battery service
void Battery_Init()
{
   #ifdef DEBUG_BATTERY
      printf("[BATT][Battery_Init] Init");
   #endif
   m_BatteryPebble.p_ImageData = &m_Image_BatteryPebble;
   m_BatteryPebble.l_Text =  GetBatteryTextLayerPebble();
   m_BatteryPhone.p_ImageData = &m_Image_BatteryPhone;
   m_BatteryPhone.l_Text =   GetBatteryTextLayerPhone();
   show_PhoneBattery(false);
   
   #ifdef DEBUG_BATTERY
      Battery_Handle_Phone(99,false);
   #endif
   
   
   battery_state_service_subscribe(Battery_Handle_Pebble);
   Battery_Handle_Pebble(battery_state_service_peek());
}

// Unregister from pebbles battery service
void Battery_Deinit()
{
   #ifdef DEBUG_BATTERY
      printf("[BATT][Battery_Deinit] Deinit");
   #endif
   battery_state_service_unsubscribe();      
}