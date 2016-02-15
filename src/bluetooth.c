#include "bluetooth.h"

BitmapLayer* m_Bluetooth_Image_Layer = NULL;
GBitmap* m_Bluetooth_Image = NULL;



void Bluetooth_Redraw()
{
   if (m_Bluetooth_Image_Layer == NULL)
      return;
   
   if (m_b_Debug)
         printf("[BT] Redrawing");
   
   GColor Color;
   if (m_b_Bluetooth_ConnectionState)
   {
      Color = Color_Image;
   }
   else
   {
      Color = Color_Error;
   }
   
   Redraw_Image(m_Bluetooth_Image_Layer,m_Bluetooth_Image,RESOURCE_ID_IMAGE_BLUETOOTH,Color);
}


static void Bluetooth_Handle(bool b_ConnectionState) 
{
   if (m_b_Bluetooth_ConnectionState == b_ConnectionState)
      return;
   
   if (m_b_Debug)
         printf("[BT] BT handler");
   
   m_b_Bluetooth_ConnectionState = b_ConnectionState;
   if (b_ConnectionState && m_b_Bluetooth_VibrationEnabled)
   {
      if (m_b_Debug)
         printf("[BT] BT handler: Connection OK");
      vibes_short_pulse();
      //printf("BT connected");
   }
   else if (m_b_Bluetooth_VibrationEnabled)
   {
      if (m_b_Debug)
         printf("[BT] BT handler: Connection failed");
      vibes_double_pulse();
      //printf("BT disconnected");
   }
   Bluetooth_Redraw();
   Network_Request();
}



void Bluetooth_Init()
{
   if (m_b_Debug)
         printf("[BT] Init");
   m_b_Bluetooth_ConnectionState = true;
   m_Bluetooth_Image_Layer = NULL;
   m_Bluetooth_Image_Layer = GetBluetoothImageLayer();
   Bluetooth_Handle(connection_service_peek_pebble_app_connection());
   connection_service_subscribe((ConnectionHandlers) {.pebble_app_connection_handler = Bluetooth_Handle});
   Bluetooth_Redraw();
}

void Bluetooth_DeInit()
{
   if (m_b_Debug)
         printf("[BT] Deinit");
   connection_service_unsubscribe();
   if (m_Bluetooth_Image)
   {
      gbitmap_destroy(m_Bluetooth_Image);
      m_Bluetooth_Image = NULL;
   }
}