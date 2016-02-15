#include "network.h"

BitmapLayer* m_Network_Image_Layer = NULL;
GBitmap* m_Network_Image;

bool m_b_Network_LastConnectionState;

void Network_Request()
{
      // Begin dictionary
     DictionaryIterator *iter;
     app_message_outbox_begin(&iter);
   
     // Add a key-value pair
     dict_write_uint8(iter, KEY_ONLINE, 0);
   
     // Send the message!
     app_message_outbox_send();
}

void Network_Redraw()
{
  
   GColor Color;
   if (m_b_Network_LastConnectionState)
   {
      Color = Color_Image;
   }
   else
   {
      Color = Color_Error;
   }     
   
   Redraw_Image(m_Network_Image_Layer,m_Network_Image,RESOURCE_ID_IMAGE_NETWORK,Color);
   
}

void Network_Handle_Reply(Tuple *network_tuple)
{
   bool b_Connected = (bool)network_tuple->value->int32;
   
   if (m_b_Network_LastConnectionState == b_Connected)
      return;
   
   m_b_Network_LastConnectionState = b_Connected;
   if (b_Connected && m_b_Network_VibrationEnabled)
   {
      vibes_short_pulse();  
   }
   else if (m_b_Network_VibrationEnabled)
   {
      vibes_double_pulse();
   }
   
  Network_Redraw();
}

void Network_Init()
{
   m_b_Network_LastConnectionState = true;
   m_Network_Image = NULL;
   m_Network_Image_Layer = GetNetworkImageLayer();
   Network_Redraw();
}

void Network_DeInit()
{
   if (m_Network_Image)
   {
      gbitmap_destroy(m_Network_Image);
      m_Network_Image = NULL;
   }         
}