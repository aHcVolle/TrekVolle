#include "mainwindow.h"

GBitmap* m_Background_Image;

GBitmap* m_Steps_Image;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_background;
static GBitmap *s_res_image_bluetooth;
static GBitmap *s_res_image_weather_01;
static GFont s_res_roboto_bold_subset_49;
static GFont s_res_gothic_18_bold;
static GBitmap *s_res_image_steps;
static GBitmap *s_res_image_battery_high;
static GBitmap *s_res_image_network;
static BitmapLayer *Layer_Background_Image;
static BitmapLayer *Layer_Bluetooth_Image;
static BitmapLayer *Layer_Weather_Image;
static TextLayer *Layer_Time_Text;
static TextLayer *Layer_Weather_Text;
static BitmapLayer *Layer_Steps_Image;
static TextLayer *Layer_Day_Text;
static TextLayer *Layer_Steps_Text;
static TextLayer *Layer_Date_Text;
static BitmapLayer *Layer_Battery_Image_Pebble;
static BitmapLayer *Layer_Network_Image;
static TextLayer *Layer_Battery_Text_Pebble;
static BitmapLayer *Layer_Battery_Image_Phone;
static TextLayer *Layer_Battery_Text_Phone;

static void initialise_ui(void) 
{
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, 1);
  #endif
  
  s_res_image_background = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
  s_res_image_bluetooth = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BLUETOOTH);
  s_res_image_weather_01 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_WEATHER_01);
  s_res_roboto_bold_subset_49 = fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_image_steps = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_STEPS);
  s_res_image_battery_high = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_HIGH);
  s_res_image_network = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NETWORK);
  // Layer_Background_Image
  Layer_Background_Image = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(Layer_Background_Image, s_res_image_background);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Background_Image);
  
  // Layer_Bluetooth_Image
  Layer_Bluetooth_Image = bitmap_layer_create(GRect(126, 134, 16, 16));
  bitmap_layer_set_bitmap(Layer_Bluetooth_Image, s_res_image_bluetooth);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Bluetooth_Image);
  
  // Layer_Weather_Image
  Layer_Weather_Image = bitmap_layer_create(GRect(5, 98, 16, 16));
  bitmap_layer_set_bitmap(Layer_Weather_Image, s_res_image_weather_01);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Weather_Image);
  
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
  
  // Layer_Steps_Image
  Layer_Steps_Image = bitmap_layer_create(GRect(8, 152, 16, 16));
  bitmap_layer_set_bitmap(Layer_Steps_Image, s_res_image_steps);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Steps_Image);
  
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
  
  // Layer_Battery_Image_Pebble
  Layer_Battery_Image_Pebble = bitmap_layer_create(GRect(8, 134, 16, 16));
  bitmap_layer_set_bitmap(Layer_Battery_Image_Pebble, s_res_image_battery_high);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Battery_Image_Pebble);
  
  // Layer_Network_Image
  Layer_Network_Image = bitmap_layer_create(GRect(109, 134, 16, 16));
  bitmap_layer_set_bitmap(Layer_Network_Image, s_res_image_network);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Network_Image);
  
  // Layer_Battery_Text_Pebble
  Layer_Battery_Text_Pebble = text_layer_create(GRect(23, 130, 38, 20));
  text_layer_set_background_color(Layer_Battery_Text_Pebble, GColorClear);
  text_layer_set_text_color(Layer_Battery_Text_Pebble, GColorWhite);
  text_layer_set_text(Layer_Battery_Text_Pebble, "99%");
  text_layer_set_font(Layer_Battery_Text_Pebble, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Battery_Text_Pebble);
  
  // Layer_Battery_Image_Phone
  Layer_Battery_Image_Phone = bitmap_layer_create(GRect(58, 134, 16, 16));
  bitmap_layer_set_bitmap(Layer_Battery_Image_Phone, s_res_image_battery_high);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Battery_Image_Phone);
  
  // Layer_Battery_Text_Phone
  Layer_Battery_Text_Phone = text_layer_create(GRect(73, 130, 36, 20));
  text_layer_set_background_color(Layer_Battery_Text_Phone, GColorClear);
  text_layer_set_text_color(Layer_Battery_Text_Phone, GColorWhite);
  text_layer_set_text(Layer_Battery_Text_Phone, "99%");
  text_layer_set_font(Layer_Battery_Text_Phone, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Layer_Battery_Text_Phone);
}

static void destroy_ui(void) 
{
  window_destroy(s_window);
  bitmap_layer_destroy(Layer_Background_Image);
  bitmap_layer_destroy(Layer_Bluetooth_Image);
  bitmap_layer_destroy(Layer_Weather_Image);
  text_layer_destroy(Layer_Time_Text);
  text_layer_destroy(Layer_Weather_Text);
  bitmap_layer_destroy(Layer_Steps_Image);
  text_layer_destroy(Layer_Day_Text);
  text_layer_destroy(Layer_Steps_Text);
  text_layer_destroy(Layer_Date_Text);
  bitmap_layer_destroy(Layer_Battery_Image_Pebble);
  bitmap_layer_destroy(Layer_Network_Image);
  text_layer_destroy(Layer_Battery_Text_Pebble);
  bitmap_layer_destroy(Layer_Battery_Image_Phone);
  text_layer_destroy(Layer_Battery_Text_Phone);
  gbitmap_destroy(s_res_image_background);
  gbitmap_destroy(s_res_image_bluetooth);
  gbitmap_destroy(s_res_image_weather_01);
  gbitmap_destroy(s_res_image_steps);
  gbitmap_destroy(s_res_image_battery_high);
  gbitmap_destroy(s_res_image_network);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) 
{
  destroy_ui();
}

void show_mainwindow(void) 
{
  initialise_ui();
  LoadConfigFromStorage();
  
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_mainwindow(void) 
{
   SaveConfigToStorage();
   if (m_Background_Image)
   {
      gbitmap_destroy(m_Background_Image);
      m_Background_Image = NULL;
   }
      
   if (m_Steps_Image)
   {
      gbitmap_destroy(m_Steps_Image);
      m_Steps_Image = NULL;
   }      
      
  window_stack_remove(s_window, true);
}

void Redraw_Image(BitmapLayer* l_Image, GBitmap* Bitmap, int ImageID, GColor Color)
{
   if (l_Image == NULL)
      return;
   
   bitmap_layer_set_bitmap(l_Image, NULL);
   if (Bitmap)
   {
      gbitmap_destroy(Bitmap);
      Bitmap = NULL;
   }
   Bitmap = gbitmap_create_with_resource(ImageID);
   replace_gbitmap_color(GColorWhite, Color, Bitmap, NULL);
   replace_gbitmap_color(GColorBlack,  Color_Window, Bitmap, NULL);
   bitmap_layer_set_bitmap(l_Image, Bitmap);
   
   layer_mark_dirty(bitmap_layer_get_layer(l_Image));
}

void SetColor()
{
//   text_layer_set_background_color(Layer_Background_Color, Color_Window);
//   layer_mark_dirty(text_layer_get_layer(Layer_Background_Color));
   
   text_layer_set_text_color(Layer_Time_Text, Color_Text);
   layer_mark_dirty(text_layer_get_layer(Layer_Time_Text));
   text_layer_set_text_color(Layer_Weather_Text, Color_Text);
   layer_mark_dirty(text_layer_get_layer(Layer_Weather_Text));
   text_layer_set_text_color(Layer_Battery_Text_Phone, Color_Text);
   layer_mark_dirty(text_layer_get_layer(Layer_Battery_Text_Phone));
   text_layer_set_text_color(Layer_Battery_Text_Pebble, Color_Text);
   layer_mark_dirty(text_layer_get_layer(Layer_Battery_Text_Pebble));
   text_layer_set_text_color(Layer_Date_Text, Color_Text); 
   layer_mark_dirty(text_layer_get_layer(Layer_Date_Text));
   text_layer_set_text_color(Layer_Day_Text, Color_Text); 
   layer_mark_dirty(text_layer_get_layer(Layer_Day_Text));
   text_layer_set_text_color(Layer_Steps_Text, Color_Text);
   layer_mark_dirty(text_layer_get_layer(Layer_Steps_Text));
   
   Battery_RedrawAll();
   
   Redraw_Image(Layer_Steps_Image,m_Steps_Image,RESOURCE_ID_IMAGE_STEPS,Color_Image);
   Redraw_Image(Layer_Background_Image,m_Background_Image,RESOURCE_ID_IMAGE_BACKGROUND,Color_Background);
}

void show_PhoneBattery(bool show)
{
   layer_set_hidden((Layer *)Layer_Battery_Text_Phone, !show);
   layer_set_hidden((Layer *)Layer_Battery_Image_Phone, !show);
}

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

BitmapLayer * GetWeatherImageLayer()
{   return Layer_Weather_Image;}
BitmapLayer* GetBluetoothImageLayer()
{   return Layer_Bluetooth_Image;}
BitmapLayer* GetNetworkImageLayer()
{   return Layer_Network_Image;}
BitmapLayer* GetBatteryImageLayerPhone()
{   return Layer_Battery_Image_Phone;}
BitmapLayer* GetBatteryImageLayerPebble()
{   return Layer_Battery_Image_Pebble;}
