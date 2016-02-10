#include "bluetooth.h"

BitmapLayer* Layer_Bluetooth_Image = NULL;
GBitmap *Image_Bluetooth;

bool LastBTConnectionState;

void RedrawBluetoothImage()
{
   if (Layer_Bluetooth_Image == NULL)
      return;
   
   GColor Color;
   if (LastBTConnectionState)
   {
      Color = Color_Image;
   }
   else
   {
      Color = Color_Error;
   }
   
   
   bitmap_layer_set_bitmap(Layer_Bluetooth_Image, NULL);
   if (Image_Bluetooth)
   {
      gbitmap_destroy(Image_Bluetooth);
      Image_Bluetooth = NULL;
   }
   Image_Bluetooth = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BLUETOOTH);
   replace_gbitmap_color(GColorWhite, Color, Image_Bluetooth, NULL);
   replace_gbitmap_color(GColorBlack,  Color_Window, Image_Bluetooth, NULL);
   bitmap_layer_set_bitmap(Layer_Bluetooth_Image, Image_Bluetooth);
   
   layer_mark_dirty(bitmap_layer_get_layer(Layer_Bluetooth_Image));
}


static void handle_bluetooth(bool connected) 
{
   if (LastBTConnectionState == connected)
      return;
   
   LastBTConnectionState = connected;
   if (connected)
   {
      vibes_short_pulse();
      //printf("BT connected");
   }
   else
   {
      vibes_double_pulse();
      //printf("BT disconnected");
   }
   RedrawBluetoothImage();
}



void InitBluetooth()
{
   LastBTConnectionState = true;
   Image_Bluetooth = NULL;
   Layer_Bluetooth_Image = GetBluetoothImageLayer();
   handle_bluetooth(connection_service_peek_pebble_app_connection());
   connection_service_subscribe((ConnectionHandlers) {.pebble_app_connection_handler = handle_bluetooth});
   RedrawBluetoothImage();
}

void DeInitBluetooth()
{
   connection_service_unsubscribe();
   if (Image_Bluetooth)
   {
      gbitmap_destroy(Image_Bluetooth);
      Image_Bluetooth = NULL;
   }
}