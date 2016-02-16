#include "network.h"

// Variables to store the layers
BitmapLayer* m_Network_Image_Layer = NULL;
GBitmap* m_Network_Image = NULL;

// Request a net work check
void Network_Request()
{
   // But only if we have a bluetooth connection
   if (!m_b_Bluetooth_ConnectionState)
   {
      m_b_Network_ConnectionState = false;
      Network_Redraw();
      return;
   }
   
   // Debug printout
   if (m_b_Debug)
         printf("[NET] Connection request");
   
   // Begin dictionary
   DictionaryIterator *iter;
   app_message_outbox_begin(&iter);

   // Add a key-value pair
   dict_write_uint8(iter, KEY_ONLINE, 0);

   // Send the message!
   app_message_outbox_send();
}

// Redraw the network image
void Network_Redraw()
{
   // Debug printout
   if (m_b_Debug)
         printf("[NET] Redrawing");
   
   // We're going to store the color here
   GColor Color;
   if (m_b_Network_ConnectionState)
   {
      Color = Color_Image;
   }
   else
   {
      Color = Color_Error;
   }     
   
   // Redraw the image
   Redraw_Image(m_Network_Image_Layer,m_Network_Image,RESOURCE_ID_IMAGE_NETWORK,Color);
   
}

// Handle network updates here
void Network_Handle_Reply(Tuple *network_tuple)
{
   // Save the net network state
   bool b_ConnectionState = (bool)network_tuple->value->int32;
   
   // Get out of here if there was no change
   if (m_b_Network_ConnectionState == b_ConnectionState)
      return;
   
   // Debug printout
   if (m_b_Debug)
         printf("[NET] Handler");
   
   // Save the new state
   m_b_Network_ConnectionState = b_ConnectionState;
   
   bool b_Vibrate = m_b_Network_VibrationEnabled;
   if (m_b_Clock_Sleep && m_b_Clock_SleepEnabled)
   {
      if (m_b_Debug && b_Vibrate)
         printf("[NET] Blocked vibration due to sleep mode");
      b_Vibrate = false;
   }
   
   // Vibrate if the user wants us to
   if (m_b_Network_ConnectionState && b_Vibrate)
   {
      if (m_b_Debug)
         printf("[NET] Handler: Connection OK");
      vibes_short_pulse();  
   }
   else if (b_Vibrate)
   {
      if (m_b_Debug)
         printf("[NET] Handler: Connection failed");
      vibes_double_pulse();
   }
   
   // Redraw the image
   Network_Redraw();
}

// Init the network variables
void Network_Init()
{
   // Debug printout
   if (m_b_Debug)
         printf("[NET] Init");
   // Init the vars
   m_b_Network_ConnectionState = true;
   m_Network_Image = NULL;
   m_Network_Image_Layer = GetNetworkImageLayer();
   // Redraw the image
   Network_Redraw();
}

// Deinitthe variables
void Network_DeInit()
{
   if (m_b_Debug)
         printf("[NET] Deinit");
   // Kill all ze thingz!
   if (m_Network_Image)
   {
      gbitmap_destroy(m_Network_Image);
      m_Network_Image = NULL;
   }         
}