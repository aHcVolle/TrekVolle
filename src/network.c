#include "network.h"


BitmapLayer* m_Network_Image_Layer = NULL;
GBitmap* m_Network_Image = NULL;

void Network_Request()
{
   if (!m_b_Bluetooth_ConnectionState)
   {
      m_b_Network_ConnectionState = false;
      Network_Redraw();
      return;
   }
     
   if (m_b_Debug)
         printf("[NET] Connection request\n");
   
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
   if (m_b_Debug)
         printf("[NET] Redrawing\n");
   GColor Color;
   if (m_b_Network_ConnectionState)
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
   bool b_ConnectionState = (bool)network_tuple->value->int32;
   
   if (m_b_Network_ConnectionState == b_ConnectionState)
      return;
   
   if (m_b_Debug)
         printf("[NET] Handler\n");
   
   m_b_Network_ConnectionState = b_ConnectionState;
   if (m_b_Network_ConnectionState && m_b_Network_VibrationEnabled)
   {
      if (m_b_Debug)
         printf("[NET] Handler: Connection OK\n");
      vibes_short_pulse();  
   }
   else if (m_b_Network_VibrationEnabled)
   {
      if (m_b_Debug)
         printf("[NET] Handler: Connection failed\n");
      vibes_double_pulse();
   }
   
  Network_Redraw();
}

void Network_Init()
{
   if (m_b_Debug)
         printf("[NET] Init\n");
   m_b_Network_ConnectionState = true;
   m_Network_Image = NULL;
   m_Network_Image_Layer = GetNetworkImageLayer();
   Network_Redraw();
}

void Network_DeInit()
{
   if (m_b_Debug)
         printf("[NET] Deinit\n");
   if (m_Network_Image)
   {
      gbitmap_destroy(m_Network_Image);
      m_Network_Image = NULL;
   }         
}