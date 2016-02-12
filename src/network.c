#include "network.h"

BitmapLayer* Layer_Network_Image = NULL;
GBitmap *Image_Network;

int LastNETConnectionState;

void RequestNetwork()
{
      // Begin dictionary
     DictionaryIterator *iter;
     app_message_outbox_begin(&iter);
   
     // Add a key-value pair
     dict_write_uint8(iter, KEY_ONLINE, 0);
   
     // Send the message!
     app_message_outbox_send();
}

void RedrawNetworkImage()
{
   if (Layer_Network_Image == NULL)
      return;
   
   GColor Color;
   if (LastNETConnectionState)
   {
      Color = Color_Image;
   }
   else
   {
      Color = Color_Error;
   }     
   
   bitmap_layer_set_bitmap(Layer_Network_Image, NULL);
   if (Image_Network)
   {
      gbitmap_destroy(Image_Network);
      Image_Network = NULL;
   }      
   Image_Network = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NETWORK);
   replace_gbitmap_color(GColorWhite, Color, Image_Network, NULL);
   replace_gbitmap_color(GColorBlack,  Color_Window, Image_Network, NULL);
   bitmap_layer_set_bitmap(Layer_Network_Image, Image_Network);
   layer_mark_dirty(bitmap_layer_get_layer(Layer_Network_Image));
}

void HandleNetworkReply(Tuple *network_tuple)
{
   int i_Connected = (int)network_tuple->value->int32;
   
   if (LastNETConnectionState == i_Connected)
      return;
   
   LastNETConnectionState = i_Connected;
   if (i_Connected && m_b_Network_VibrationEnabled)
   {
      vibes_short_pulse();  
   }
   else if (m_b_Network_VibrationEnabled)
   {
      vibes_double_pulse();
   }
   
   RedrawNetworkImage();
}

void InitNetwork()
{
   LastNETConnectionState = 1;
   Image_Network = NULL;
   Layer_Network_Image = GetNetworkImageLayer();
   RedrawNetworkImage();
}

void DeInitNetwork()
{
   if (Image_Network)
   {
      gbitmap_destroy(Image_Network);
      Image_Network = NULL;
   }         
}