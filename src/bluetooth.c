#include "bluetooth.h"

BitmapLayer* m_Bluetooth_Image_Layer = NULL;
GBitmap* m_Bluetooth_Image = NULL;

bool m_b_Bluetooth_LastConnectionState;

void Bluetooth_Redraw()
{
   if (m_Bluetooth_Image_Layer == NULL)
      return;
   
   GColor Color;
   if (m_b_Bluetooth_LastConnectionState)
   {
      Color = Color_Image;
   }
   else
   {
      Color = Color_Error;
   }
   
   Redraw_Image(m_Bluetooth_Image_Layer,m_Bluetooth_Image,RESOURCE_ID_IMAGE_BLUETOOTH,Color);
}


static void Bluetooth_Handle(bool connected) 
{
   if (m_b_Bluetooth_LastConnectionState == connected)
      return;
   
   m_b_Bluetooth_LastConnectionState = connected;
   if (connected && m_b_Bluetooth_VibrationEnabled)
   {
      
      vibes_short_pulse();
      //printf("BT connected");
   }
   else if (m_b_Bluetooth_VibrationEnabled)
   {
      vibes_double_pulse();
      //printf("BT disconnected");
   }
   Bluetooth_Redraw();
}



void Bluetooth_Init()
{
   m_b_Bluetooth_LastConnectionState = true;
   m_Bluetooth_Image_Layer = NULL;
   m_Bluetooth_Image_Layer = GetBluetoothImageLayer();
   Bluetooth_Handle(connection_service_peek_pebble_app_connection());
   connection_service_subscribe((ConnectionHandlers) {.pebble_app_connection_handler = Bluetooth_Handle});
   Bluetooth_Redraw();
}

void Bluetooth_DeInit()
{
   connection_service_unsubscribe();
   if (m_Bluetooth_Image)
   {
      gbitmap_destroy(m_Bluetooth_Image);
      m_Bluetooth_Image = NULL;
   }
}