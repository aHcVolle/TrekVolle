#include "bluetooth.h"

// Redraw the bluetooth image
void Bluetooth_Redraw()
{
   
   // Debug printout
   #ifdef DEBUG_BLUETOOTH
         printf("[BT][Bluetooth_Redraw] Redrawing");
   #endif
   // Variable to store the image color
   GColor Color;
   
   if (m_b_Bluetooth_ConnectionState)
   {
      Color = Color_Image;
   }
   else
   {
      Color = Color_Error;
   }
   // Redraw the image
   Redraw_Image(&m_Image_Bluetooth,RESOURCE_ID_IMAGE_BLUETOOTH,Color);
}

// Bluetooth connection changes are processed here
static void Bluetooth_Handle(bool b_ConnectionState) 
{
   // Get out of here if there was no change
   if (m_b_Bluetooth_ConnectionState == b_ConnectionState)
      return;
   
   // Debug printout
   #ifdef DEBUG_BLUETOOTH
         printf("[BT][Bluetooth_Handle] BT handler");
   #endif
   // Save the current state
   m_b_Bluetooth_ConnectionState = b_ConnectionState;
   
   bool b_Vibrate = m_b_Bluetooth_VibrationEnabled;
   if ((m_b_Clock_Sleep && m_b_Clock_SleepEnabled) || (m_b_BatterySavingActive))
   {
      #ifdef DEBUG_BLUETOOTH
      if (b_Vibrate)
         printf("[BT][Bluetooth_Handle] Blocked vibration due to sleep mode / battery saving");
      #endif
      b_Vibrate = false;
   }
      
   
   // Vibrate if the option is enabled
   if (b_ConnectionState && b_Vibrate)
   {
      #ifdef DEBUG_BLUETOOTH
         printf("[BT][Bluetooth_Handle] BT handler: Connection OK");
      #endif
      vibes_short_pulse();
      //printf("BT connected");
   }
   else if (b_Vibrate)
   {
      #ifdef DEBUG_BLUETOOTH
         printf("[BT][Bluetooth_Handle] BT handler: Connection failed");
      #endif
      vibes_double_pulse();
      //printf("BT disconnected");
   }
   
   
   // And check if we are online (will do nothing if bluetooth is disconnected)
   //Network_Request();
   
   if (b_ConnectionState)
   {
      //request a network update at the next clock tick
      m_i_Network_Counter = m_i_Network_RefreshTime;
   }
   else
   {
      // if there is no bt connection there can't be a network connection
      m_b_Network_ConnectionState = false;
      Network_Redraw();
   }
   
   // Redraw the bluetooth image
   Bluetooth_Redraw();
}

// Init the bluetooth vars and register with the bluetooth connection service
void Bluetooth_Init()
{
   // Debug printout
   #ifdef DEBUG_BLUETOOTH
         printf("[BT][Bluetooth_Init] Init");
   #endif
   // Init vars
   m_b_Bluetooth_ConnectionState = true;

   // Register to the service
   Bluetooth_Handle(connection_service_peek_pebble_app_connection());
   connection_service_subscribe((ConnectionHandlers) {.pebble_app_connection_handler = Bluetooth_Handle});
   // Draw the current bluetooth state
   Bluetooth_Redraw();
}

// Unregister from the bluetooth connection service
void Bluetooth_DeInit()
{
   // Debug printout
   #ifdef DEBUG_BLUETOOTH
         printf("[BT][Bluetooth_DeInit] Deinit");
   #endif
   // Unregister from the bluetooth service
   connection_service_unsubscribe();
   
   
}
