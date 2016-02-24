#include "mainwindow.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;

static GFont s_res_roboto_bold_subset_49;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_14_bold;

static TextLayer *Layer_TimeHour_Text;
static TextLayer *Layer_TimeMinute_Text;
static TextLayer *Layer_Weather_Text;
static TextLayer *Layer_Day_Text;
static TextLayer *Layer_Steps_Text;
static TextLayer *Layer_Date_Text;
static TextLayer *Layer_Battery_Text_Pebble;
static TextLayer *Layer_Battery_Text_Phone;



static void initialise_ui(void) 
{
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Creating window");
   #endif
   s_window = window_create();
   window_set_background_color(s_window, GColorBlack);
   /*#ifndef PBL_SDK_3
   window_set_fullscreen(s_window, 1);
   #endif*/
   
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Creating fonts");
   #endif
   s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
   s_res_gothic_14_bold = fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD);
   s_res_roboto_bold_subset_49 = fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49);
   
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Creating image layers");
   #endif
   
   // Layer_Background_Image
   #if defined(PBL_RECT)
      m_Image_Background.thisLayer = bitmap_layer_create(GRect(0, 0, 144, 168));
   #elif defined(PBL_ROUND)
      m_Image_Background.thisLayer = bitmap_layer_create(GRect(0, 0, 180, 180));
   #endif
   bitmap_layer_set_compositing_mode(m_Image_Background.thisLayer,GCompOpSet);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Background.thisLayer);
   snprintf(m_Image_Background.s_Name,sizeof(m_Image_Background.s_Name),"BCKG");
   Redraw_Image(&m_Image_Background, RESOURCE_ID_IMAGE_BACKGROUND, GColorBlue);

   // Layer_Bluetooth_Image
   #if defined(PBL_RECT)
      m_Image_Bluetooth.thisLayer = bitmap_layer_create(GRect(126, 134, 16, 16));
   #elif defined(PBL_ROUND)
      m_Image_Bluetooth.thisLayer = bitmap_layer_create(GRect(140, 134, 16, 16));
   #endif
   bitmap_layer_set_compositing_mode(m_Image_Bluetooth.thisLayer,GCompOpSet);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Bluetooth.thisLayer);
   snprintf(m_Image_Bluetooth.s_Name,sizeof(m_Image_Bluetooth.s_Name),"BT");
   Redraw_Image(&m_Image_Bluetooth, RESOURCE_ID_IMAGE_BLUETOOTH, GColorWhite);

   // Layer_Weather_Image
   m_Image_Weather.thisLayer = bitmap_layer_create(GRect(5, 98, 16, 16));
   bitmap_layer_set_compositing_mode(m_Image_Weather.thisLayer,GCompOpSet);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Weather.thisLayer);
   snprintf(m_Image_Weather.s_Name,sizeof(m_Image_Weather.s_Name),"WTHR");
   Redraw_Image(&m_Image_Weather, RESOURCE_ID_IMAGE_ERROR, GColorWhite);

   // Layer_Steps_Image
   #if defined(PBL_HEALTH)
      #if defined(PBL_RECT)
         m_Image_Steps.thisLayer = bitmap_layer_create(GRect(8, 152, 16, 16));
      #elif defined(PBL_ROUND)
         m_Image_Steps.thisLayer = bitmap_layer_create(GRect(49, 152, 16, 16));
      #endif
      bitmap_layer_set_compositing_mode(m_Image_Steps.thisLayer,GCompOpSet);
      layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Steps.thisLayer);
      snprintf(m_Image_Steps.s_Name,sizeof(m_Image_Steps.s_Name),"STPS");
      Redraw_Image(&m_Image_Steps, RESOURCE_ID_IMAGE_STEPS, GColorWhite);
   #endif

   // Layer_Battery_Image_Pebble
   #if defined(PBL_RECT)
      m_Image_BatteryPebble.thisLayer = bitmap_layer_create(GRect(8, 134, 16, 16));
   #elif defined(PBL_ROUND)
      m_Image_BatteryPebble.thisLayer = bitmap_layer_create(GRect(28, 134, 16, 16));
   #endif
   bitmap_layer_set_compositing_mode(m_Image_BatteryPebble.thisLayer,GCompOpSet);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_BatteryPebble.thisLayer);
   snprintf(m_Image_BatteryPebble.s_Name,sizeof(m_Image_BatteryPebble.s_Name),"BAT1");
   Redraw_Image(&m_Image_BatteryPebble, RESOURCE_ID_IMAGE_BATTERY_HIGH, GColorWhite);

   // Layer_Battery_Image_Phone
   #if defined(PBL_RECT)
      m_Image_BatteryPhone.thisLayer = bitmap_layer_create(GRect(58, 134, 16, 16));
   #elif defined(PBL_ROUND)
      m_Image_BatteryPhone.thisLayer = bitmap_layer_create(GRect(72, 134, 16, 16));
   #endif
   bitmap_layer_set_compositing_mode(m_Image_BatteryPhone.thisLayer,GCompOpSet);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_BatteryPhone.thisLayer);
   snprintf(m_Image_BatteryPhone.s_Name,sizeof(m_Image_BatteryPhone.s_Name),"BAT2");
   Redraw_Image(&m_Image_BatteryPhone, RESOURCE_ID_IMAGE_BATTERY_HIGH, GColorWhite);
   
   // Layer_Network_Image
   #if defined(PBL_RECT)
      m_Image_Network.thisLayer = bitmap_layer_create(GRect(109, 134, 16, 16));
   #elif defined(PBL_ROUND)
      m_Image_Network.thisLayer = bitmap_layer_create(GRect(123, 134, 16, 16));
   #endif
   bitmap_layer_set_compositing_mode(m_Image_Network.thisLayer,GCompOpSet);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Network.thisLayer);
   snprintf(m_Image_Network.s_Name,sizeof(m_Image_Network.s_Name),"NET");
   Redraw_Image(&m_Image_Network, RESOURCE_ID_IMAGE_NETWORK, GColorWhite);
   
   
   
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Creating text layers");
   #endif
   
   // Layer_TimeHour_Text
   #if defined(PBL_RECT)
      Layer_TimeHour_Text = text_layer_create(GRect(0, 4, 71, 49));
   #elif defined(PBL_ROUND)
      Layer_TimeHour_Text = text_layer_create(GRect(0, 11, 85, 49));
   #endif
   text_layer_set_background_color(Layer_TimeHour_Text, GColorClear);
   text_layer_set_text_color(Layer_TimeHour_Text, GColorWhite);
   text_layer_set_text(Layer_TimeHour_Text, "30");
   text_layer_set_text_alignment(Layer_TimeHour_Text, GTextAlignmentRight);
   text_layer_set_font(Layer_TimeHour_Text, s_res_roboto_bold_subset_49);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_TimeHour_Text);
   
   // Layer_TimeMinute_Text
   #if defined(PBL_RECT)
      Layer_TimeMinute_Text = text_layer_create(GRect(72, 4, 72, 49));
   #elif defined(PBL_ROUND)
      Layer_TimeMinute_Text = text_layer_create(GRect(86, 11, 90, 49));
   #endif
   text_layer_set_background_color(Layer_TimeMinute_Text, GColorClear);
   text_layer_set_text_color(Layer_TimeMinute_Text, GColorWhite);
   text_layer_set_text(Layer_TimeMinute_Text, ":80");
   text_layer_set_text_alignment(Layer_TimeMinute_Text, GTextAlignmentLeft);
   text_layer_set_font(Layer_TimeMinute_Text, s_res_roboto_bold_subset_49);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_TimeMinute_Text);

   // Layer_Weather_Text
   #if defined(PBL_RECT)
      Layer_Weather_Text = text_layer_create(GRect(24, 93, 144, 22));
   #elif defined(PBL_ROUND)
      Layer_Weather_Text = text_layer_create(GRect(24, 93, 175, 22));
   #endif
   text_layer_set_background_color(Layer_Weather_Text, GColorClear);
   text_layer_set_text_color(Layer_Weather_Text, GColorWhite);
   text_layer_set_text(Layer_Weather_Text, "Updating...");
   text_layer_set_font(Layer_Weather_Text, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Weather_Text);
   
   // Layer_Day_Text
   #if defined(PBL_RECT)
      Layer_Day_Text = text_layer_create(GRect(0, 72, 144, 20));
   #elif defined(PBL_ROUND)
      Layer_Day_Text = text_layer_create(GRect(0, 72, 177, 20));
   #endif
   text_layer_set_background_color(Layer_Day_Text, GColorClear);
   text_layer_set_text_color(Layer_Day_Text, GColorWhite);
   text_layer_set_text(Layer_Day_Text, "D666 W88");
   text_layer_set_text_alignment(Layer_Day_Text, GTextAlignmentRight);
   text_layer_set_font(Layer_Day_Text, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Day_Text);

   // Layer_Steps_Text
   #if defined(PBL_HEALTH)
      #if defined(PBL_RECT)
         Layer_Steps_Text = text_layer_create(GRect(24, 147, 123, 20));
      #elif defined(PBL_ROUND)
         Layer_Steps_Text = text_layer_create(GRect(65, 151, 123, 20));
      #endif
      text_layer_set_background_color(Layer_Steps_Text, GColorClear);
      text_layer_set_text_color(Layer_Steps_Text, GColorWhite);
      text_layer_set_text(Layer_Steps_Text, "9999 9999m");
      #if defined(PBL_RECT)
         text_layer_set_font(Layer_Steps_Text, s_res_gothic_18_bold);
      #elif defined(PBL_ROUND)
         text_layer_set_font(Layer_Steps_Text, s_res_gothic_14_bold);
      #endif
      layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Steps_Text);
   #endif
   
   // Layer_Date_Text
   #if defined(PBL_RECT)
      Layer_Date_Text = text_layer_create(GRect(44, 50, 100, 20));
   #elif defined(PBL_ROUND)
      Layer_Date_Text = text_layer_create(GRect(44, 55, 100, 20));
   #endif
   text_layer_set_background_color(Layer_Date_Text, GColorClear);
   text_layer_set_text_color(Layer_Date_Text, GColorWhite);
   text_layer_set_text(Layer_Date_Text, "Sun,00.00.00");
   text_layer_set_text_alignment(Layer_Date_Text, GTextAlignmentRight);
   text_layer_set_font(Layer_Date_Text, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Date_Text);

   // Layer_Battery_Text_Pebble
   #if defined(PBL_RECT)
      Layer_Battery_Text_Pebble = text_layer_create(GRect(23, 130, 38, 20));
   #elif defined(PBL_ROUND)
      Layer_Battery_Text_Pebble = text_layer_create(GRect(43, 130, 38, 20));
   #endif
   text_layer_set_background_color(Layer_Battery_Text_Pebble, GColorClear);
   text_layer_set_text_color(Layer_Battery_Text_Pebble, GColorWhite);
   text_layer_set_text(Layer_Battery_Text_Pebble, "99%");
   text_layer_set_font(Layer_Battery_Text_Pebble, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Battery_Text_Pebble);

   // Layer_Battery_Text_Phone
   #if defined(PBL_RECT)
      Layer_Battery_Text_Phone = text_layer_create(GRect(73, 130, 36, 20));
   #elif defined(PBL_ROUND)
      Layer_Battery_Text_Phone = text_layer_create(GRect(87, 130, 36, 20));
   #endif
   text_layer_set_background_color(Layer_Battery_Text_Phone, GColorClear);
   text_layer_set_text_color(Layer_Battery_Text_Phone, GColorWhite);
   text_layer_set_text(Layer_Battery_Text_Phone, "99%");
   text_layer_set_font(Layer_Battery_Text_Phone, s_res_gothic_18_bold);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Battery_Text_Phone);
   
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Finished creating");
   #endif
}

static void destroy_ui(void) 
{
   

   text_layer_destroy(Layer_TimeHour_Text);
   text_layer_destroy(Layer_TimeMinute_Text);
   text_layer_destroy(Layer_Weather_Text);
   text_layer_destroy(Layer_Day_Text);
   #if defined(PBL_HEALTH)
      text_layer_destroy(Layer_Steps_Text);
   #endif
   text_layer_destroy(Layer_Date_Text);
   text_layer_destroy(Layer_Battery_Text_Pebble);
   text_layer_destroy(Layer_Battery_Text_Phone);

   bitmap_layer_destroy(m_Image_Background.thisLayer);
   bitmap_layer_destroy(m_Image_Bluetooth.thisLayer);
   bitmap_layer_destroy(m_Image_Weather.thisLayer);
   #if defined(PBL_HEALTH)
      bitmap_layer_destroy(m_Image_Steps.thisLayer);
   #endif
   bitmap_layer_destroy(m_Image_Network.thisLayer);
   bitmap_layer_destroy(m_Image_BatteryPhone.thisLayer);
   bitmap_layer_destroy(m_Image_BatteryPebble.thisLayer);

   gbitmap_destroy(m_Image_Background.thisBitmap);
   gbitmap_destroy(m_Image_Bluetooth.thisBitmap);
   gbitmap_destroy(m_Image_Weather.thisBitmap);
   #if defined(PBL_HEALTH)
      gbitmap_destroy(m_Image_Steps.thisBitmap);
   #endif
   gbitmap_destroy(m_Image_Network.thisBitmap);
   gbitmap_destroy(m_Image_BatteryPhone.thisBitmap);
   gbitmap_destroy(m_Image_BatteryPebble.thisBitmap);
   
   // Destroy all ze thingz
   window_destroy(s_window);
   
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
   #ifdef PBL_COLOR
   if (ui_PNG_Loadbuffer != NULL)
      free(ui_PNG_Loadbuffer);
   #endif
   
   // Kill the window
   window_stack_remove(s_window, true);
}

// Redraw the specified image
void Redraw_Image(struct ImageData* Image, int ImageID, GColor Color)
{
   // Get out of here if the image layer is not initialized
   if (Image->thisLayer == NULL)
   {
      #ifdef DEBUG_IMAGEREDRAW
         printf( "[MAIN][Redraw_Image] Will not draw on layer that is NULL");
      #endif
      return;
   }

   #ifdef DEBUG_IMAGEREDRAW
   printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Start: %s R: %d",(int) heap_bytes_used(),(int) heap_bytes_free(),Image->s_Name,ImageID );
   #endif

   // Clear the image layer
   bitmap_layer_set_bitmap(Image->thisLayer, NULL);

   #ifdef DEBUG_IMAGEREDRAW
   printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Layer is now NULL",(int) heap_bytes_used(),(int) heap_bytes_free() );   
   #endif

   // Clear the image storage
   if (Image->thisBitmap)
   {
      gbitmap_destroy(Image->thisBitmap);
      Image->thisBitmap = NULL;

      #ifdef DEBUG_IMAGEREDRAW
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Bitmap is destroyed",(int) heap_bytes_used(),(int) heap_bytes_free() );
      #endif
   }
   #ifdef PBL_COLOR
      // Set the buffer to 0's
      memset(ui_PNG_Loadbuffer, 0, PNG_BUFFER_SIZE);
   
      #ifdef DEBUG_IMAGEREDRAW
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Buffer is set to 0",(int) heap_bytes_used(),(int) heap_bytes_free() );
      #endif
   
      // Get the size of the resource
      size_t mResource_size;
      mResource_size = resource_size(resource_get_handle(ImageID));
      #ifdef DEBUG_IMAGEREDRAW
      printf("[MAIN][Redraw_Image] resource_size: %d", (int) mResource_size);
      #endif
      if (mResource_size == 0)
      {
         #ifdef DEBUG_IMAGEREDRAW
         printf("[MAIN][Redraw_Image] resource size of %d is 0!!!! ",ImageID);
         #endif
         return;
      }
   
      #ifdef DEBUG_IMAGEREDRAW
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Got resource size",(int) heap_bytes_used(),(int) heap_bytes_free() );
      #endif
   
   
      // Load the resource
      size_t png_size;
      png_size = resource_load(resource_get_handle(ImageID),ui_PNG_Loadbuffer, mResource_size);
      #ifdef DEBUG_IMAGEREDRAW
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Resource is loaded",(int) heap_bytes_used(),(int) heap_bytes_free() );
      #endif
   
      // Create the bitmap
      Image->thisBitmap = gbitmap_create_from_png_data(ui_PNG_Loadbuffer, png_size);
   #else
      Image->thisBitmap = gbitmap_create_with_resource(ImageID);
   #endif
   // Check if everything went fine
   if (Image->thisBitmap == NULL)
   {
      #ifdef DEBUG_IMAGEREDRAW
      printf("[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Could not create bitmap!!!",(int) heap_bytes_used(),(int) heap_bytes_free());
      #endif
      return;
   }
   #ifdef DEBUG_IMAGEREDRAW
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Bitmap is created",(int) heap_bytes_used(),(int) heap_bytes_free() );
   #endif
   
   #ifdef PBL_COLOR
      // Replace white with the image color
      replace_gbitmap_color(GColorWhite, Color,Image->thisBitmap, NULL);
   
      #ifdef DEBUG_IMAGEREDRAW
         printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Color 1 was replaced",(int) heap_bytes_used(),(int) heap_bytes_free() );
      #endif
   
      #ifdef DEBUG_IMAGEREDRAW
         printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Color 2 was replaced",(int) heap_bytes_used(),(int) heap_bytes_free() );
      #endif
   #else
      layer_set_hidden((Layer *)Image->thisLayer, gcolor_equal(Color,GColorBlack));
   #endif
   
   // Set the image to the layer
   bitmap_layer_set_bitmap(Image->thisLayer, Image->thisBitmap);
   #ifdef DEBUG_IMAGEREDRAW
      printf( "[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d Set bitmap to layer",(int) heap_bytes_used(),(int) heap_bytes_free() );
   #endif

   // Let the layer be redrawn
   layer_mark_dirty(bitmap_layer_get_layer(Image->thisLayer));
   #ifdef DEBUG_IMAGEREDRAW
      printf("[MAIN][Redraw_Image] Heap Used: %05d, Free: %05d End",(int) heap_bytes_used(), (int)heap_bytes_free() );
   #endif
}

// Set all the text's color
void Color_SetTextColor()
{
   // Debug printout
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][Color_SetTextColor] Setting text color");
   #endif
   
   // Set the windows background color
   window_set_background_color(s_window, Color_Window);
   
   // Set the text color
   text_layer_set_text_color(Layer_TimeHour_Text, Color_ClockHour);
   text_layer_set_text_color(Layer_TimeMinute_Text, Color_ClockMin);
   text_layer_set_text_color(Layer_Weather_Text, Color_Text);
   text_layer_set_text_color(Layer_Battery_Text_Phone, Color_Text);
   text_layer_set_text_color(Layer_Battery_Text_Pebble, Color_Text);
   text_layer_set_text_color(Layer_Date_Text, Color_Text); 
   text_layer_set_text_color(Layer_Day_Text, Color_Text); 
   #if defined(PBL_HEALTH)
   text_layer_set_text_color(Layer_Steps_Text, Color_Text);
   #endif
   layer_mark_dirty(text_layer_get_layer(Layer_TimeHour_Text));
   layer_mark_dirty(text_layer_get_layer(Layer_TimeMinute_Text));
   layer_mark_dirty(text_layer_get_layer(Layer_Weather_Text));
   layer_mark_dirty(text_layer_get_layer(Layer_Battery_Text_Phone));
   layer_mark_dirty(text_layer_get_layer(Layer_Battery_Text_Pebble));
   layer_mark_dirty(text_layer_get_layer(Layer_Date_Text));
   layer_mark_dirty(text_layer_get_layer(Layer_Day_Text));
   #if defined(PBL_HEALTH)
   layer_mark_dirty(text_layer_get_layer(Layer_Steps_Text));
   #endif
}

// Set all the images color
void Color_SetImageColor()
{
   // Debug printout
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][Color_SetImageColor] Setting image color");
   #endif
   
   // Set the windows background color
   window_set_background_color(s_window, Color_Window);
   
   // Redraw all the images
   Battery_RedrawAll();
   
   #if defined(PBL_HEALTH)
   Redraw_Image(&m_Image_Steps,RESOURCE_ID_IMAGE_STEPS,Color_Image);
   #endif
   Redraw_Image(&m_Image_Background,RESOURCE_ID_IMAGE_BACKGROUND,Color_Background);
}

// Display the phone battery's image
void show_PhoneBattery(bool show)
{
   
   // Set the layers hidden attribute
   if (layer_get_hidden((Layer *)Layer_Battery_Text_Phone) == show)
   {
      // Debug printout
      #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][show_PhoneBattery] Setting phone battery display hide status to %d",(int)!show);
      #endif
      
      layer_set_hidden((Layer *)Layer_Battery_Text_Phone, !show);
      layer_set_hidden((Layer *)m_Image_BatteryPhone.thisLayer, !show);
   }   
   
}

// Return all the layer's pointers
TextLayer* GetTimeHourTextLayer()
{   return Layer_TimeHour_Text;}
TextLayer* GetTimeMinuteTextLayer()
{   return Layer_TimeMinute_Text;}
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
