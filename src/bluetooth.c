#include "bluetooth.h"

// Used variables
BitmapLayer* m_Bluetooth_Image_Layer = NULL;
GBitmap* m_Bluetooth_Image = NULL;

// Redraw the bluetooth image
void Bluetooth_Redraw()
{
   // But only if the layer is already initialized
   if (m_Bluetooth_Image_Layer == NULL)
      return;
   
   // Debug printout
   if (m_b_Debug)
         printf("[BT] Redrawing");
   
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
   Redraw_Image(m_Bluetooth_Image_Layer,m_Bluetooth_Image,RESOURCE_ID_IMAGE_BLUETOOTH,Color);
}

// Bluetooth connection changes are processed here
static void Bluetooth_Handle(bool b_ConnectionState) 
{
   // Get out of here if there was no change
   if (m_b_Bluetooth_ConnectionState == b_ConnectionState)
      return;
   
   // Debug printout
   if (m_b_Debug)
         printf("[BT] BT handler");
   
   // Save the current state
   m_b_Bluetooth_ConnectionState = b_ConnectionState;
   
   bool b_Vibrate = m_b_Bluetooth_VibrationEnabled;
   if (m_b_Clock_Sleep && m_b_Clock_SleepEnabled)
   {
      if (m_b_Debug && b_Vibrate)
         printf("[BT] Blocked vibration due to sleep mode");
      b_Vibrate = false;
   }
      
   
   // Vibrate if the option is enabled
   if (b_ConnectionState && b_Vibrate)
   {
      if (m_b_Debug)
         printf("[BT] BT handler: Connection OK");
      vibes_short_pulse();
      //printf("BT connected");
   }
   else if (b_Vibrate)
   {
      if (m_b_Debug)
         printf("[BT] BT handler: Connection failed");
      vibes_double_pulse();
      //printf("BT disconnected");
   }
   
   // Redraw the bluetooth image
   Bluetooth_Redraw();
   // And check if we are online (will do nothing if bluetoth is disconnected)
   Network_Request();
}

// Init the bluetooth vars and register with the bluetooth connection service
void Bluetooth_Init()
{
   // Debug printout
   if (m_b_Debug)
         printf("[BT] Init");
   // Init vars
   m_b_Bluetooth_ConnectionState = true;
   m_Bluetooth_Image_Layer = NULL;
   m_Bluetooth_Image_Layer = GetBluetoothImageLayer();
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
   if (m_b_Debug)
         printf("[BT] Deinit");
   // Unregister from the bluetooth service
   connection_service_unsubscribe();
   
   // Kill all ze thingz!
   if (m_Bluetooth_Image)
   {
      gbitmap_destroy(m_Bluetooth_Image);
      m_Bluetooth_Image = NULL;
   }
}