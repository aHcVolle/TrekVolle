#include "mainwindow.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;

static GFont s_Font_Time;
static GFont s_Font_Text_Big;
#if defined(PBL_PLATFORM_CHALK)
   static GFont s_Font_Text_Small;
#endif

static TextLayer *Layer_TimeHour_Text;
static TextLayer *Layer_TimeMinute_Text;
static TextLayer *Layer_Weather_Text;
static TextLayer *Layer_Day_Text;
static TextLayer *Layer_Steps_Text;
#if defined(HAS_HEARTRATE)
static TextLayer *Layer_Heart_Text;
#endif
static TextLayer *Layer_Date_Text;
static TextLayer *Layer_Battery_Text_Pebble;
static TextLayer *Layer_Battery_Text_Phone;


void SetupTextLayer(TextLayer* TargetLayer,GColor BackgroundColor,GColor TextColor,char* Text,GTextAlignment Alignment,GFont Font)
{
   text_layer_set_background_color(TargetLayer, BackgroundColor);
   text_layer_set_text_color(TargetLayer, TextColor);
   text_layer_set_text(TargetLayer, Text);
   text_layer_set_text_alignment(TargetLayer, Alignment);
   text_layer_set_font(TargetLayer, Font);
}

static void initialise_ui(void) 
{
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Creating window");
   #endif
   s_window = window_create();
   window_set_background_color(s_window, GColorBlack);
   
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Creating fonts");
   #endif
   
   
   #if defined(PBL_PLATFORM_APLITE) || defined(PBL_PLATFORM_BASALT) || defined(PBL_PLATFORM_DIORITE)
      s_Font_Text_Big = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
      s_Font_Time = fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49);
   #elif defined(PBL_PLATFORM_CHALK)
      s_Font_Text_Big = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
      s_Font_Text_Small = fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD);
      s_Font_Time = fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49);
   #elif defined(PBL_PLATFORM_EMERY)
      s_Font_Text_Big = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
      s_Font_Time = fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49);
   #endif
   
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Creating layers");
   #endif
   
   #if defined(PBL_PLATFORM_APLITE) || defined(PBL_PLATFORM_BASALT) || defined(PBL_PLATFORM_DIORITE)
      m_Image_Background.thisLayer = bitmap_layer_create(GRect(0, 0, 144, 168));
      m_Image_Bluetooth.thisLayer = bitmap_layer_create(GRect(126, 134, ICON_SIZE, ICON_SIZE));
      m_Image_Weather.thisLayer = bitmap_layer_create(GRect(5, 98, ICON_SIZE, ICON_SIZE));
   
      #if defined(PBL_HEALTH)
         m_Image_Steps.thisLayer = bitmap_layer_create(GRect(6, 152, ICON_SIZE, ICON_SIZE));
         #if defined(HAS_HEARTRATE)
            m_Image_Heart.thisLayer = bitmap_layer_create(GRect(110, 156,ICON_SIZE/2, ICON_SIZE/2));
         #endif
      #endif
   
      m_Image_BatteryPebble.thisLayer = bitmap_layer_create(GRect(6, 134, ICON_SIZE, ICON_SIZE));
      m_Image_BatteryPhone.thisLayer = bitmap_layer_create(GRect(56, 134, ICON_SIZE, ICON_SIZE));
      m_Image_Network.thisLayer = bitmap_layer_create(GRect(109, 134, ICON_SIZE, ICON_SIZE));
   
      Layer_TimeHour_Text = text_layer_create(GRect(0, 4, 71, 49));
      Layer_TimeMinute_Text = text_layer_create(GRect(72, 4, 72, 49));
      Layer_Weather_Text = text_layer_create(GRect(24, 93, 144, 22));
      Layer_Day_Text = text_layer_create(GRect(0, 72, 144, 20));
      
      #if defined(PBL_HEALTH)
         Layer_Steps_Text = text_layer_create(GRect(21, 147, 110, 20));
         #if defined(HAS_HEARTRATE)
            Layer_Heart_Text = text_layer_create(GRect(120, 147, 110, 20));
         #endif
      #endif
   
      Layer_Date_Text = text_layer_create(GRect(0, 50, 144, 20));
      Layer_Battery_Text_Pebble = text_layer_create(GRect(19, 130, 38, 20));
      Layer_Battery_Text_Phone = text_layer_create(GRect(69, 130, 38, 20));
   
   #elif defined(PBL_PLATFORM_CHALK)
      m_Image_Background.thisLayer = bitmap_layer_create(GRect(0, 0, 180, 180));
      
      m_Image_Weather.thisLayer = bitmap_layer_create(GRect(5, 98, ICON_SIZE, ICON_SIZE));
   
      m_Image_BatteryPebble.thisLayer = bitmap_layer_create(GRect(28, 134, ICON_SIZE, ICON_SIZE));
      m_Image_BatteryPhone.thisLayer = bitmap_layer_create(GRect(78, 134, ICON_SIZE, ICON_SIZE));
      m_Image_Network.thisLayer = bitmap_layer_create(GRect(129, 134, ICON_SIZE, ICON_SIZE));
      m_Image_Bluetooth.thisLayer = bitmap_layer_create(GRect(144, 134, ICON_SIZE, ICON_SIZE));
   
      m_Image_Steps.thisLayer = bitmap_layer_create(GRect(49, 152, ICON_SIZE, ICON_SIZE));  
      
   
      Layer_TimeHour_Text = text_layer_create(GRect(0, 11, 85, 49));
      Layer_TimeMinute_Text = text_layer_create(GRect(86, 11, 90, 49));
      Layer_Date_Text = text_layer_create(GRect(44, 55, 100, 20));
      
      Layer_Day_Text = text_layer_create(GRect(0, 72, 177, 20));
      Layer_Weather_Text = text_layer_create(GRect(24, 93, 175, 22));
            
      Layer_Battery_Text_Pebble = text_layer_create(GRect(41, 130, 38, 20));
      Layer_Battery_Text_Phone = text_layer_create(GRect(91, 130, 38, 20));
      Layer_Steps_Text = text_layer_create(GRect(65, 151, 123, 20));

   #elif defined(PBL_PLATFORM_EMERY)
      m_Image_Background.thisLayer = bitmap_layer_create(GRect(0, 0, 200, 228));
      
      m_Image_Weather.thisLayer = bitmap_layer_create(GRect(5, 136, ICON_SIZE, ICON_SIZE));
   
      m_Image_BatteryPebble.thisLayer = bitmap_layer_create(GRect(10, 180, ICON_SIZE, ICON_SIZE));
      m_Image_BatteryPhone.thisLayer = bitmap_layer_create(GRect(80, 180, ICON_SIZE, ICON_SIZE));
      m_Image_Bluetooth.thisLayer = bitmap_layer_create(GRect(160, 180, ICON_SIZE, ICON_SIZE));
      m_Image_Network.thisLayer = bitmap_layer_create(GRect(180, 180, ICON_SIZE, ICON_SIZE));
   
      m_Image_Steps.thisLayer = bitmap_layer_create(GRect(10, 205, ICON_SIZE, ICON_SIZE));
      m_Image_Heart.thisLayer = bitmap_layer_create(GRect(140, 205, ICON_SIZE, ICON_SIZE));
      
   
      Layer_TimeHour_Text = text_layer_create(GRect(0, 4, 100, 49));
      Layer_TimeMinute_Text = text_layer_create(GRect(102, 4, 100, 49));
      Layer_Date_Text = text_layer_create(GRect(0, 54, 200, 28));
      Layer_Day_Text = text_layer_create(GRect(0, 99, 200, 28));
      Layer_Weather_Text = text_layer_create(GRect(26, 129, 144, 28));
      
      Layer_Battery_Text_Pebble = text_layer_create(GRect(30, 175, 60, 28));
      Layer_Battery_Text_Phone = text_layer_create(GRect(100, 175, 60, 28));
   
      Layer_Steps_Text = text_layer_create(GRect(30, 200, 110, 28));
      Layer_Heart_Text = text_layer_create(GRect(162, 200, 110, 28));
      
      
   
   #endif
   
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Setting up layers");
   #endif
   
   bitmap_layer_set_compositing_mode(m_Image_Background.thisLayer,GCompOpSet);
   bitmap_layer_set_compositing_mode(m_Image_Bluetooth.thisLayer,GCompOpSet);
   bitmap_layer_set_compositing_mode(m_Image_Weather.thisLayer,GCompOpSet);
   #if defined(PBL_HEALTH)
      bitmap_layer_set_compositing_mode(m_Image_Steps.thisLayer,GCompOpSet);
   #endif
   #if defined(HAS_HEARTRATE)
      bitmap_layer_set_compositing_mode(m_Image_Heart.thisLayer,GCompOpSet);
   #endif
   
   bitmap_layer_set_compositing_mode(m_Image_BatteryPebble.thisLayer,GCompOpSet);
   bitmap_layer_set_compositing_mode(m_Image_BatteryPhone.thisLayer,GCompOpSet);
   bitmap_layer_set_compositing_mode(m_Image_Network.thisLayer,GCompOpSet);
   
   SetupTextLayer(Layer_TimeHour_Text,GColorClear,GColorWhite,"",GTextAlignmentRight,s_Font_Time);
   SetupTextLayer(Layer_TimeMinute_Text,GColorClear,GColorWhite,"",GTextAlignmentLeft,s_Font_Time);
   SetupTextLayer(Layer_Weather_Text,GColorClear,GColorWhite,"Updating...",GTextAlignmentLeft,s_Font_Text_Big);
   SetupTextLayer(Layer_Day_Text,GColorClear,GColorWhite,"",GTextAlignmentRight,s_Font_Text_Big);
   #if defined(PBL_HEALTH)
      #if defined(PBL_PLATFORM_APLITE) || defined(PBL_PLATFORM_BASALT) || defined(PBL_PLATFORM_DIORITE)
         SetupTextLayer(Layer_Steps_Text,GColorClear,GColorWhite,"",GTextAlignmentLeft,s_Font_Text_Big);
         #if defined(HAS_HEARTRATE)
            SetupTextLayer(Layer_Heart_Text,GColorClear,GColorWhite,"",GTextAlignmentLeft,s_Font_Text_Big);
         #endif
      #elif defined(PBL_PLATFORM_CHALK)
         SetupTextLayer(Layer_Steps_Text,GColorClear,GColorWhite,"",GTextAlignmentLeft,s_Font_Text_Small);
      #elif defined(PBL_PLATFORM_EMERY)
         SetupTextLayer(Layer_Steps_Text,GColorClear,GColorWhite,"",GTextAlignmentLeft,s_Font_Text_Big);
         SetupTextLayer(Layer_Heart_Text,GColorClear,GColorWhite,"",GTextAlignmentLeft,s_Font_Text_Big);
      #endif
   #endif   
   SetupTextLayer(Layer_Date_Text,GColorClear,GColorWhite,"",GTextAlignmentRight,s_Font_Text_Big);
   SetupTextLayer(Layer_Battery_Text_Pebble,GColorClear,GColorWhite,"",GTextAlignmentLeft,s_Font_Text_Big);
   SetupTextLayer(Layer_Battery_Text_Phone,GColorClear,GColorWhite,"",GTextAlignmentLeft,s_Font_Text_Big);
      
   
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Add layers");
   #endif
   
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Background.thisLayer);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Bluetooth.thisLayer);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Weather.thisLayer);
   #if defined(PBL_HEALTH)
      layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Steps.thisLayer);
   #endif
   #if defined(HAS_HEARTRATE)
      layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Heart.thisLayer);
   #endif
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_BatteryPebble.thisLayer);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_BatteryPhone.thisLayer);
   layer_add_child(window_get_root_layer(s_window), (Layer *)m_Image_Network.thisLayer);
   
   
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_TimeHour_Text);   
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_TimeMinute_Text);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Weather_Text);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Day_Text);
   #if defined(PBL_HEALTH)
      layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Steps_Text);
   #endif
   #if defined(HAS_HEARTRATE)
      layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Heart_Text);
   #endif
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Date_Text);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Battery_Text_Pebble);
   layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Battery_Text_Phone);
   
   
   #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][initialise_ui] Finish image layers");
   #endif
   
   snprintf(m_Image_Background.s_Name,sizeof(m_Image_Background.s_Name),"BCKG");
   snprintf(m_Image_Bluetooth.s_Name,sizeof(m_Image_Bluetooth.s_Name),"BT");
   snprintf(m_Image_Weather.s_Name,sizeof(m_Image_Weather.s_Name),"WTHR");
   #if defined(PBL_HEALTH)
      snprintf(m_Image_Steps.s_Name,sizeof(m_Image_Steps.s_Name),"STPS");
   #endif
   #if defined(HAS_HEARTRATE)
      snprintf(m_Image_Heart.s_Name,sizeof(m_Image_Heart.s_Name),"HRT");
   #endif
   snprintf(m_Image_BatteryPebble.s_Name,sizeof(m_Image_BatteryPebble.s_Name),"BAT1");
   snprintf(m_Image_BatteryPhone.s_Name,sizeof(m_Image_BatteryPhone.s_Name),"BAT2");
   snprintf(m_Image_Network.s_Name,sizeof(m_Image_Network.s_Name),"NET");
    
     
   Redraw_Image(&m_Image_Background, RESOURCE_ID_IMAGE_BACKGROUND, GColorBlue);
   Redraw_Image(&m_Image_Bluetooth, RESOURCE_ID_IMAGE_BLUETOOTH, GColorWhite); 
   Redraw_Image(&m_Image_Weather, RESOURCE_ID_IMAGE_ERROR, GColorWhite);
   #if defined(PBL_HEALTH)
      Redraw_Image(&m_Image_Steps, RESOURCE_ID_IMAGE_STEPS, GColorWhite);
   #endif
   #if defined(HAS_HEARTRATE)
      Redraw_Image(&m_Image_Heart, RESOURCE_ID_IMAGE_HEART, GColorWhite); 
   #endif
   Redraw_Image(&m_Image_BatteryPebble, RESOURCE_ID_IMAGE_BATTERY_HIGH, GColorWhite);
   Redraw_Image(&m_Image_BatteryPhone, RESOURCE_ID_IMAGE_BATTERY_HIGH, GColorWhite);
   Redraw_Image(&m_Image_Network, RESOURCE_ID_IMAGE_NETWORK, GColorWhite);
   
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

void Refresh_Display(void)
{
   layer_mark_dirty(window_get_root_layer(s_window));
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
   //layer_mark_dirty(bitmap_layer_get_layer(Image->thisLayer));
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

   text_layer_set_text_color(Layer_Date_Text, Color_Text); 
   text_layer_set_text_color(Layer_Day_Text, Color_Text); 
   #if defined(PBL_HEALTH)
   text_layer_set_text_color(Layer_Steps_Text, Color_Text);
   #endif
   #if defined(HAS_HEARTRATE)
   text_layer_set_text_color(Layer_Heart_Text, Color_Text);
   #endif

   Refresh_Display();
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
   #if defined(HAS_HEARTRATE)
   Redraw_Image(&m_Image_Heart,RESOURCE_ID_IMAGE_HEART,Color_Image);
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

void show_ConnectionSymbols(bool show)
{
   // Set the layers hidden attribute
   if (layer_get_hidden((Layer *)m_Image_Network.thisLayer) == show)
   {
      // Debug printout
      #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][show_ConnectionSymbols] Setting network hide status to %d",(int)!show);
      #endif
      
      layer_set_hidden((Layer *)m_Image_Network.thisLayer, !show);
   }
   
   if (layer_get_hidden((Layer *)m_Image_Bluetooth.thisLayer) == show)
   {
      // Debug printout
      #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][show_ConnectionSymbols] Setting bluetooth hide status to %d",(int)!show);
      #endif
      
      layer_set_hidden((Layer *)m_Image_Bluetooth.thisLayer, !show);
   }
}

// Display the phone battery's image
void show_HeartRate(bool show)
{
   #if defined(HAS_HEARTRATE)
   // Set the layers hidden attribute
   if (layer_get_hidden((Layer *)Layer_Heart_Text) == show)
   {
      // Debug printout
      #ifdef DEBUG_MAINWINDOW
         printf("[MAIN][show_HeartRate] Setting heartrate display hide status to %d",(int)!show);
      #endif
      
      layer_set_hidden((Layer *)Layer_Heart_Text, !show);
      layer_set_hidden((Layer *)m_Image_Heart.thisLayer, !show);
   }   
   #endif
}


// Return all the layer's pointers
TextLayer* GetTimeHourTextLayer() {   return Layer_TimeHour_Text;}
TextLayer* GetTimeMinuteTextLayer() {   return Layer_TimeMinute_Text;}
TextLayer* GetWeatherTextLayer() {   return Layer_Weather_Text;}
TextLayer* GetBatteryTextLayerPhone() {   return Layer_Battery_Text_Phone;}
TextLayer* GetBatteryTextLayerPebble() {   return Layer_Battery_Text_Pebble;}
TextLayer* GetDateTextLayer() {   return Layer_Date_Text;}
TextLayer* GetDayTextLayer() {   return Layer_Day_Text;}
TextLayer* GetStepTextLayer() {   return Layer_Steps_Text;}
#if defined(HAS_HEARTRATE)
TextLayer* GetHeartTextLayer() {   return Layer_Heart_Text;}
#endif
