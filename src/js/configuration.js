var ConfigVersion = '1_1';


Pebble.addEventListener('showConfiguration', function() 
{
   var url = 'https://rawgit.com/aHcVolle/TrekVolle/master/config/config_'+ConfigVersion+'.html';
  // var url = 'https://www.vllmr.eu/pebble/config/index.html';

   if (m_b_Debug)
         console.log("[JS:CONF] Sending to "+url);
   Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) 
{
   var configData = JSON.parse(decodeURIComponent(e.response));
   if (m_b_Debug)
         console.log("[JS:CONF] Got config data "+JSON.stringify(configData));

   var Color_Background = configData.Color_Background;
   var Color_Text = configData.Color_Text;
   var Color_Image = configData.Color_Image;
   var Color_Window = configData.Color_Window;
   var Color_Charging = configData.Color_Charging;
   var Color_Error = configData.Color_Error;
   var Color_BatteryLow = configData.Color_BatteryLow;
   
   var Weather_TemperatureCelcius = configData.Weather_TemperatureCelcius;
   var Weather_Refreshtime = configData.Weather_Refreshtime;
   var Weather_RetryUpdate = configData.Weather_RetryUpdate;
   
   var Clock_Clock24h = configData.Clock_Clock24h;
   var Clock_Datestyle_ddmmyy = configData.Clock_Datestyle_ddmmyy;
   var Clock_Datestyle_yymmdd = configData.Clock_Datestyle_yymmdd;
   var Clock_Datestyle_mmddyy = configData.Clock_Datestyle_mmddyy;
   
   var Bluetooth_VibrationEnabled = configData.Bluetooth_VibrationEnabled;
   
   var Network_RefreshTime = configData.Network_Refreshtime;
   var Network_VibrationEnabled = configData.Network_VibrationEnabled;
   
   //console.log('Color_Text: ' + Color_Text);
  
   var i_Color_Background = parseInt(Color_Background.substring(2), 16);
   var i_Color_Text = parseInt(Color_Text.substring(2), 16);
   var i_Color_Image = parseInt(Color_Image.substring(2), 16);
   var i_Color_Window = parseInt(Color_Window.substring(2), 16);
   var i_Color_Charging = parseInt(Color_Charging.substring(2), 16);
   var i_Color_Error = parseInt(Color_Error.substring(2), 16);
   var i_Color_BatteryLow = parseInt(Color_BatteryLow.substring(2), 16);
   
   var i_Weather_TemperatureCelcius = 1;
   if (Weather_TemperatureCelcius == "false")
      i_Weather_TemperatureCelcius = 0;
   var i_Weather_Refreshtime = parseInt(Weather_Refreshtime, 10);
   var i_Weather_RetryUpdate = 1;
   if (Weather_RetryUpdate == "false")
      i_Weather_RetryUpdate = 0;
   
   var i_Clock_Clock24h = 1;
   if (Clock_Clock24h == "false")
      i_Clock_Clock24h = 0;
   
   var i_Clock_Datestyle_ddmmyy = 1;
   if (Clock_Datestyle_ddmmyy == "false")
      i_Clock_Datestyle_ddmmyy = 0;
 
   var i_Clock_Datestyle_yymmdd = 1;
   if (Clock_Datestyle_yymmdd == "false")
      i_Clock_Datestyle_yymmdd = 0;

   var i_Clock_Datestyle_mmddyy = 1;
   if (Clock_Datestyle_mmddyy == "false")
      i_Clock_Datestyle_mmddyy = 0;
 
   
   var DATE_DD_MM_YY = 0;
   var DATE_YY_MM_DD = 1;
   var DATE_MM_DD_YY = 2;
   
   var i_Clock_Datestyle = 0;
   if (i_Clock_Datestyle_ddmmyy == 1)
      i_Clock_Datestyle = DATE_DD_MM_YY;
   else if (i_Clock_Datestyle_yymmdd == 1)
      i_Clock_Datestyle = DATE_YY_MM_DD;
   else if (i_Clock_Datestyle_mmddyy == 1)
      i_Clock_Datestyle = DATE_MM_DD_YY;
   
   var i_Bluetooth_VibrationEnabled = 1;
   if (Bluetooth_VibrationEnabled == "false")
      i_Bluetooth_VibrationEnabled = 0;
   
   var i_Network_VibrationEnabled = 1;
   if (Network_VibrationEnabled == "false")
      i_Network_VibrationEnabled = 0;
   var i_Network_RefreshTime = parseInt(Network_RefreshTime, 10);
   
   
   if (m_b_Debug)
   {
      console.log("[JS:CONF] Config: i_Color_Background "+i_Color_Background.toString());
      console.log("[JS:CONF] Config: i_Color_Text "+i_Color_Text.toString());
      console.log("[JS:CONF] Config: i_Color_Image "+i_Color_Image.toString());
      console.log("[JS:CONF] Config: i_Color_Window "+i_Color_Window.toString());
      console.log("[JS:CONF] Config: i_Color_Charging "+i_Color_Charging.toString());
      console.log("[JS:CONF] Config: i_Color_Error "+i_Color_Error.toString());
      console.log("[JS:CONF] Config: i_Color_BatteryLow "+i_Color_BatteryLow.toString());
      
      console.log("[JS:CONF] Config: i_Weather_TemperatureCelcius "+i_Weather_TemperatureCelcius.toString());
      console.log("[JS:CONF] Config: i_Weather_Refreshtime "+i_Weather_Refreshtime.toString());
      console.log("[JS:CONF] Config: i_Weather_RetryUpdate "+i_Weather_RetryUpdate.toString());
      
      console.log("[JS:CONF] Config: i_Clock_Clock24h "+i_Clock_Clock24h.toString());
      console.log("[JS:CONF] Config: i_Clock_Datestyle_ddmmyy "+i_Clock_Datestyle_ddmmyy.toString());
      console.log("[JS:CONF] Config: i_Clock_Datestyle_yymmdd "+i_Clock_Datestyle_yymmdd.toString());
      console.log("[JS:CONF] Config: i_Clock_Datestyle_mmddyy "+i_Clock_Datestyle_mmddyy.toString());
      console.log("[JS:CONF] Config: i_Clock_Datestyle "+i_Clock_Datestyle.toString());
      
      console.log("[JS:CONF] Config: i_Network_RefreshTime "+i_Network_RefreshTime.toString());
      console.log("[JS:CONF] Config: i_Network_VibrationEnabled "+i_Network_VibrationEnabled.toString());
      
      console.log("[JS:CONF] Config: i_Bluetooth_VibrationEnabled "+i_Bluetooth_VibrationEnabled.toString());
   }
  /* console.log('Color_Background_int: ' + Color_Background_int.toString());
   console.log('Color_Text_int: ' + Color_Text_int.toString());               
   console.log('Color_Image_int: ' + Color_Image_int.toString());
   console.log('Color_Window_int: ' + Color_Window_int.toString());
   console.log('Color_Charging_int: ' + Color_Charging_int.toString());
   console.log('Color_Error_int: ' + Color_Error_int.toString());
   console.log('Color_BatteryLow_int: ' + Color_BatteryLow_int.toString());*/
   
   var dictionary = 
       {
          'KEY_COLOR_BACKGROUND' : i_Color_Background,
          'KEY_COLOR_TEXT'       : i_Color_Text,
          'KEY_COLOR_IMAGE'      : i_Color_Image,
          'KEY_COLOR_WINDOW'     : i_Color_Window,
          'KEY_COLOR_CHARGING'   : i_Color_Charging,
          'KEY_COLOR_ERROR'      : i_Color_Error,
          'KEY_COLOR_BATTERYLOW' : i_Color_BatteryLow,
          'KEY_WEATHER_TEMPERATURECELCIUS' : i_Weather_TemperatureCelcius,
          'KEY_WEATHER_REFRESHTIME': i_Weather_Refreshtime,
          'KEY_WEATHER_RETRYUPDATE' : i_Weather_RetryUpdate,
          'KEY_CLOCK_CLOCK24H' : i_Clock_Clock24h,
          'KEY_CLOCK_DATESTYLE' : i_Clock_Datestyle,
          'KEY_NETWORK_REFRESHTIME' : i_Network_RefreshTime,          
          'KEY_NETWORK_VIBRATIONENABLED' : i_Network_VibrationEnabled,
          'KEY_BLUETOOTH_VIBRATIONENABLED' : i_Bluetooth_VibrationEnabled
          
       };

   // Send to watchapp
   Pebble.sendAppMessage(dictionary, function(){}, function(){});
});
