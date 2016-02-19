#include "mainwindow.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;

static GFont s_res_roboto_bold_subset_49;
static GFont s_res_gothic_18_bold;

static TextLayer *Layer_Time_Text;
static TextLayer *Layer_Weather_Text;
static TextLayer *Layer_Day_Text;
static TextLayer *Layer_Steps_Text;
static TextLayer *Layer_Date_Text;
static TextLayer *Layer_Battery_Text_Pebble;
static TextLayer *Layer_Battery_Text_Phone;



static void initialise_ui(void) 
{
   if (m_b_Debug)
         printf("[MAIN][initialise_ui] Creating window");
   s_window = window_create();
   window_set_background_color(s_window, GColorBlack);
   /*#ifndef PBL_SDK_3
   window_set_fullscreen(s_window, 1);
   #endif*/
   
   if (m_b_Debug)
         printf("[MAIN][initialise_ui] Creating fonts");
   s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
   s_res_roboto_bold_subset_49 = fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49);
   
   if (m_b_Debug)
         printf("[MAIN][initialise_ui] Creating image layers");
   
   // Layer_Background_Image
   m_Image_Background.thisLayer = bitmap_layer_create(GRect(0, 0, 144, 168));
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Background.thisLayer);
   //bitmap_layer_set_bitmap(Layer_Background_Image, s_res_image_background);
   //layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Background_Image);
   Redraw_Image(&m_Image_Background, RESOURCE_ID_IMAGE_BACKGROUND, GColorBlue);

   // Layer_Bluetooth_Image
   m_Image_Bluetooth.thisLayer = bitmap_layer_create(GRect(126, 134, 16, 16));
   //bitmap_layer_set_bitmap(Layer_Bluetooth_Image, s_res_image_bluetooth);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Bluetooth.thisLayer);
   Redraw_Image(&m_Image_Bluetooth, RESOURCE_ID_IMAGE_BLUETOOTH, GColorWhite);

   // Layer_Weather_Image
   m_Image_Weather.thisLayer = bitmap_layer_create(GRect(5, 98, 16, 16));
   //bitmap_layer_set_bitmap(Layer_Weather_Image, s_res_image_weather_01);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Weather.thisLayer);
   Redraw_Image(&m_Image_Weather, RESOURCE_ID_IMAGE_ERROR, GColorWhite);

   // Layer_Steps_Image
   m_Image_Steps.thisLayer = bitmap_layer_create(GRect(8, 152, 16, 16));
   //bitmap_layer_set_bitmap(Layer_Steps_Image, s_res_image_steps);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Steps.thisLayer);
   Redraw_Image(&m_Image_Steps, RESOURCE_ID_IMAGE_STEPS, GColorWhite);

   // Layer_Battery_Image_Pebble
   m_Image_BatteryPebble.thisLayer = bitmap_layer_create(GRect(8, 134, 16, 16));
   //bitmap_layer_set_bitmap(Layer_Battery_Image_Pebble, s_res_image_battery_high);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_BatteryPebble.thisLayer);
   Redraw_Image(&m_Image_BatteryPebble, RESOURCE_ID_IMAGE_BATTERY_HIGH, GColorWhite);

   // Layer_Battery_Image_Phone
   m_Image_BatteryPhone.thisLayer = bitmap_layer_create(GRect(58, 134, 16, 16));
   //bitmap_layer_set_bitmap(Layer_Battery_Image_Phone, s_res_image_battery_high);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_BatteryPhone.thisLayer);
   Redraw_Image(&m_Image_BatteryPhone, RESOURCE_ID_IMAGE_BATTERY_HIGH, GColorWhite);
   
   // Layer_Network_Image
   m_Image_Network.thisLayer = bitmap_layer_create(GRect(109, 134, 16, 16));
   //bitmap_layer_set_bitmap(Layer_Network_Image, s_res_image_network);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Network.thisLayer);
   Redraw_Image(&m_Image_Network, RESOURCE_ID_IMAGE_NETWORK, GColorWhite);
   
   
   
   if (m_b_Debug)
         printf("[MAIN][initialise_ui] Creating text layers");
   
   // Layer_Time_Text
   Layer_Time_Text = text_layer_create(GRect(0, 4, 144, 49));
   text_layer_set_background_color(Layer_Time_Text, GColorClear);
   text_layer_set_text_color(Layer_Time_Text, GColorWhite);
   text_layer_set_text(Layer_Time_Text, "30:80");
   text_layer_set_text_alignment(Layer_Time_Text, GTextAlignmentRight);
   text_layer_set_font(Layer_Time_Text, s_res_roboto_bold_subset_49);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Time_Text);

   // Layer_Weather_Text
   Layer_Weather_Text = text_layer_create(GRect(24, 93, 119, 22));
   text_layer_set_background_color(Layer_Weather_Text, GColorClear);
   text_layer_set_text_color(Layer_Weather_Text, GColorWhite);
   text_layer_set_text(Layer_Weather_Text, "Updating...");
   text_layer_set_font(Layer_Weather_Text, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Weather_Text);
   
   // Layer_Day_Text
   Layer_Day_Text = text_layer_create(GRect(0, 72, 144, 20));
   text_layer_set_background_color(Layer_Day_Text, GColorClear);
   text_layer_set_text_color(Layer_Day_Text, GColorWhite);
   text_layer_set_text(Layer_Day_Text, "D666 W88");
   text_layer_set_text_alignment(Layer_Day_Text, GTextAlignmentRight);
   text_layer_set_font(Layer_Day_Text, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Day_Text);

   // Layer_Steps_Text
   Layer_Steps_Text = text_layer_create(GRect(24, 147, 123, 20));
   text_layer_set_background_color(Layer_Steps_Text, GColorClear);
   text_layer_set_text_color(Layer_Steps_Text, GColorWhite);
   text_layer_set_text(Layer_Steps_Text, "9999, 9999m");
   text_layer_set_font(Layer_Steps_Text, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Steps_Text);

   // Layer_Date_Text
   Layer_Date_Text = text_layer_create(GRect(44, 50, 100, 20));
   text_layer_set_background_color(Layer_Date_Text, GColorClear);
   text_layer_set_text_color(Layer_Date_Text, GColorWhite);
   text_layer_set_text(Layer_Date_Text, "Sun,00.00.00");
   text_layer_set_text_alignment(Layer_Date_Text, GTextAlignmentRight);
   text_layer_set_font(Layer_Date_Text, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Date_Text);

   // Layer_Battery_Text_Pebble
   Layer_Battery_Text_Pebble = text_layer_create(GRect(23, 130, 38, 20));
   text_layer_set_background_color(Layer_Battery_Text_Pebble, GColorClear);
   text_layer_set_text_color(Layer_Battery_Text_Pebble, GColorWhite);
   text_layer_set_text(Layer_Battery_Text_Pebble, "99%");
   text_layer_set_font(Layer_Battery_Text_Pebble, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Battery_Text_Pebble);

   // Layer_Battery_Text_Phone
   Layer_Battery_Text_Phone = text_layer_create(GRect(73, 130, 36, 20));
   text_layer_set_background_color(Layer_Battery_Text_Phone, GColorClear);
   text_layer_set_text_color(Layer_Battery_Text_Phone, GColorWhite);
   text_layer_set_text(Layer_Battery_Text_Phone, "99%");
   text_layer_set_font(Layer_Battery_Text_Phone, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Battery_Text_Phone);
   
   if (m_b_Debug)
         printf("[MAIN][initialise_ui] Finished creating");
}

static void destroy_ui(void) 
{
   // Destroy all ze thingz
   window_destroy(s_window);

   text_layer_destroy(Layer_Time_Text);
   text_layer_destroy(Layer_Weather_Text);
   text_layer_destroy(Layer_Day_Text);
   text_layer_destroy(Layer_Steps_Text);
   text_layer_destroy(Layer_Date_Text);
   text_layer_destroy(Layer_Battery_Text_Pebble);
   text_layer_destroy(Layer_Battery_Text_Phone);

   bitmap_layer_destroy(m_Image_Background.thisLayer);
   bitmap_layer_destroy(m_Image_Bluetooth.thisLayer);
   bitmap_layer_destroy(m_Image_Weather.thisLayer);
   bitmap_layer_destroy(m_Image_Steps.thisLayer);
   bitmap_layer_destroy(m_Image_Network.thisLayer);
   bitmap_layer_destroy(m_Image_BatteryPhone.thisLayer);
   bitmap_layer_destroy(m_Image_BatteryPebble.thisLayer);

   gbitmap_destroy(m_Image_Background.thisBitmap);
   gbitmap_destroy(m_Image_Bluetooth.thisBitmap);
   gbitmap_destroy(m_Image_Weather.thisBitmap);
   gbitmap_destroy(m_Image_Steps.thisBitmap);
   gbitmap_destroy(m_Image_Network.thisBitmap);
   gbitmap_destroy(m_Image_BatteryPhone.thisBitmap);
   gbitmap_destroy(m_Image_BatteryPebble.thisBitmap);
   
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) 
{
  destroy_ui();
}

// Display the main window
void show_mainwindow(void) 
{
   // Init theui
   initialise_ui();
   // Load stored values
   LoadConfigFromStorage();

   window_set_window_handlers(s_window, (WindowHandlers) {
      .unload = handle_window_unload,
   });
   window_stack_push(s_window, true);
}

// Hide the main window
void hide_mainwindow(void) 
{
   // Save vars to the storage
   SaveConfigToStorage();

   
   // Free our PNG buffer
   if (ui_PNG_Loadbuffer != NULL)
      free(ui_PNG_Loadbuffer);
   
   // Kill the window
   window_stack_remove(s_window, true);
}

// Redraw the specified image
void Redraw_Image(struct ImageData* Image, int ImageID, GColor Color)
{
   // Get out of here if the image layer is not initialized
   if (Image->thisLayer == NULL)
      return;
   
   if (m_b_Debug)
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Start: L: %p B: %p R: %d",(int) heap_bytes_used(),(int) heap_bytes_free(),Image->thisLayer,Image->thisBitmap,ImageID );
   
   // Clear the image layer
   bitmap_layer_set_bitmap(Image->thisLayer, NULL);
   if (m_b_Debug)
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Layer is now NULL",(int) heap_bytes_used(),(int) heap_bytes_free() );   

   // Clear the image storage
   
   if (Image->thisBitmap)
   {
      gbitmap_destroy(Image->thisBitmap);
      Image->thisBitmap = NULL;
      
      if (m_b_Debug)
         printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Bitmap is destroyed",(int) heap_bytes_used(),(int) heap_bytes_free() );
    
   }
     
   memset(ui_PNG_Loadbuffer, 0, PNG_BUFFER_SIZE);
   if (m_b_Debug)
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Buffer is set to 0",(int) heap_bytes_used(),(int) heap_bytes_free() );
   
   // Create the image storage
   // Bitmap = gbitmap_create_with_resource(ImageID); // old style
   
   size_t mResource_size;
   mResource_size = resource_size(resource_get_handle(ImageID));
   if (m_b_Debug)
      printf("[MAIN][Redraw_Image] resource_size: %d", (int) mResource_size);
   if (m_b_Debug)
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Got resource size",(int) heap_bytes_used(),(int) heap_bytes_free() );
   size_t png_size;
   png_size = resource_load(resource_get_handle(ImageID),ui_PNG_Loadbuffer, mResource_size);
   if (m_b_Debug)
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Resource is loaded",(int) heap_bytes_used(),(int) heap_bytes_free() );
   
   Image->thisBitmap = gbitmap_create_from_png_data(ui_PNG_Loadbuffer, png_size);
   if (m_b_Debug)
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Bitmap is created",(int) heap_bytes_used(),(int) heap_bytes_free() );
   
   if (Image->thisBitmap == NULL)
   {
      if (m_b_Debug)
         printf("[MAIN][Redraw_Image] Could not create bitmap!!!");
      return;
   }
   
   
   #ifdef PBL_COLOR   
   // Replace white with the image color
   replace_gbitmap_color(GColorWhite, Color,Image->thisBitmap, NULL);
   if (m_b_Debug)
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Color 1 was replaced",(int) heap_bytes_used(),(int) heap_bytes_free() );
   
   // Replace black with the watchface background color
   replace_gbitmap_color(GColorBlack, Color_Window, Image->thisBitmap, NULL);
   
   if (m_b_Debug)
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Color 2 was replaced",(int) heap_bytes_used(),(int) heap_bytes_free() );
   
   if (m_b_Debug)
         printf("[MAIN][Redraw_Image] Color replaced.");
   #else
   layer_set_hidden((Layer *)Image->thisLayer, !gcolor_equal(Color,GColorWhite));
   if (m_b_Debug)
         printf("[MAIN][Redraw_Image] Mono set.");
   #endif
   
   
   // Set the image to the layer
   bitmap_layer_set_bitmap(Image->thisLayer, Image->thisBitmap);
   if (m_b_Debug)
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Set bitmap to layer",(int) heap_bytes_used(),(int) heap_bytes_free() );
   // Let the layer be redrawn
   layer_mark_dirty(bitmap_layer_get_layer(Image->thisLayer));
   if (m_b_Debug)
      printf("[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d End",(int) heap_bytes_used(), (int)heap_bytes_free() );
   
}

// Set all the text's color
void Color_SetTextColor()
{
   // Debug printout
   if (m_b_Debug)
         printf("[MAIN][Color_SetTextColor] Setting text color");
   // Set the text color
   text_layer_set_text_color(Layer_Time_Text, Color_Text);
   text_layer_set_text_color(Layer_Weather_Text, Color_Text);
   text_layer_set_text_color(Layer_Battery_Text_Phone, Color_Text);
   text_layer_set_text_color(Layer_Battery_Text_Pebble, Color_Text);
   text_layer_set_text_color(Layer_Date_Text, Color_Text); 
   text_layer_set_text_color(Layer_Day_Text, Color_Text); 
   text_layer_set_text_color(Layer_Steps_Text, Color_Text);
      
   layer_mark_dirty(text_layer_get_layer(Layer_Time_Text));
   layer_mark_dirty(text_layer_get_layer(Layer_Weather_Text));
   layer_mark_dirty(text_layer_get_layer(Layer_Battery_Text_Phone));
   layer_mark_dirty(text_layer_get_layer(Layer_Battery_Text_Pebble));
   layer_mark_dirty(text_layer_get_layer(Layer_Date_Text));
   layer_mark_dirty(text_layer_get_layer(Layer_Day_Text));
   layer_mark_dirty(text_layer_get_layer(Layer_Steps_Text));
}

// Set all the images color
void Color_SetImageColor()
{
   // Debug printout
   if (m_b_Debug)
         printf("[MAIN][Color_SetImageColor] Setting image color");
   // Redraw all the images
   Battery_RedrawAll();
   
   Redraw_Image(&m_Image_Steps,RESOURCE_ID_IMAGE_STEPS,Color_Image);
   Redraw_Image(&m_Image_Background,RESOURCE_ID_IMAGE_BACKGROUND,Color_Background);
}

// Display the phone battery's image
void show_PhoneBattery(bool show)
{
   
   // Set the layers hidden attribute
   if (layer_get_hidden((Layer *)Layer_Battery_Text_Phone) == show)
   {
      // Debug printout
      if (m_b_Debug)
         printf("[MAIN][show_PhoneBattery] Setting phone battery display hide status to %d",(int)!show);
      
      layer_set_hidden((Layer *)Layer_Battery_Text_Phone, !show);
      layer_set_hidden((Layer *)m_Image_BatteryPhone.thisLayer, !show);
   }   
   
}

// Return all the layer's pointers
TextLayer* GetTimeTextLayer()
{   return Layer_Time_Text;}
TextLayer* GetWeatherTextLayer()
{   return Layer_Weather_Text;}
TextLayer*  GetBatteryTextLayerPhone()
{   return Layer_Battery_Text_Phone;}
TextLayer*  GetBatteryTextLayerPebble()
{   return Layer_Battery_Text_Pebble;}
TextLayer* GetDateTextLayer()
{   return Layer_Date_Text;}
TextLayer*  GetDayTextLayer()
{   return Layer_Day_Text;}
TextLayer* GetStepTextLayer()
{   return Layer_Steps_Text;}
