
Pebble.addEventListener('showConfiguration', function() {
  var url = 'https://rawgit.com/aHcVolle/TrekVolle/master/config/index.html';
  // var url = 'https://www.vllmr.eu/pebble/config/index.html';
  //console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) 
{
   var configData = JSON.parse(decodeURIComponent(e.response));
   console.log('Configuration page returned: ' + JSON.stringify(configData));

   var Color_Background = configData.Color_Background;
   var Color_Text = configData.Color_Text;
   var Color_Image = configData.Color_Image;
   var Color_Window = configData.Color_Window;
   var Color_Charging = configData.Color_Charging;
   var Color_Error = configData.Color_Error;
   var Color_BatteryLow = configData.Color_BatteryLow;
   var TemperatureInCelcius = configData.TemperatureInCelcius;
   var Clock24h = configData.Clock24h;
   var DateStyle = configData.DateStyle;
   var NetworkRefreshTime = configData.NetworkRefreshTime;
   var Bluetooth_VibrationEnabled = configData.Bluetooth_VibrationEnabled;
   var Network_VibrationEnabled = configData.Network_VibrationEnabled;

   //console.log('Color_Text: ' + Color_Text);
  
   var Color_Background_int = parseInt(Color_Background.substring(2), 16);
   var Color_Text_int = parseInt(Color_Text.substring(2), 16);
   var Color_Image_int = parseInt(Color_Image.substring(2), 16);
   var Color_Window_int = parseInt(Color_Window.substring(2), 16);
   var Color_Charging_int = parseInt(Color_Charging.substring(2), 16);
   var Color_Error_int = parseInt(Color_Error.substring(2), 16);
   var Color_BatteryLow_int = parseInt(Color_BatteryLow.substring(2), 16);
   
   var TemperatureInCelcius_int = 1;
   if (TemperatureInCelcius == "false")
      TemperatureInCelcius_int = 0;
   
   var Clock24h_int = 1;
   if (Clock24h == "false")
      Clock24h_int = 0;
   
   var i_Bluetooth_VibrationEnabled = 1;
   if (Bluetooth_VibrationEnabled == "false")
      i_Bluetooth_VibrationEnabled = 0;
   var i_Network_VibrationEnabled = 1;
   if (Network_VibrationEnabled == "false")
      i_Network_VibrationEnabled = 0;
   
   var DateStyle_int = parseInt(DateStyle, 10);
   var NetworkRefreshTime_int = parseInt(NetworkRefreshTime, 10);
   
  /* console.log('Color_Background_int: ' + Color_Background_int.toString());
   console.log('Color_Text_int: ' + Color_Text_int.toString());               
   console.log('Color_Image_int: ' + Color_Image_int.toString());
   console.log('Color_Window_int: ' + Color_Window_int.toString());
   console.log('Color_Charging_int: ' + Color_Charging_int.toString());
   console.log('Color_Error_int: ' + Color_Error_int.toString());
   console.log('Color_BatteryLow_int: ' + Color_BatteryLow_int.toString());*/
   
   var dictionary = 
       {
          'KEY_COLOR_BACKGROUND' : Color_Background_int,
          'KEY_COLOR_TEXT'       : Color_Text_int,
          'KEY_COLOR_IMAGE'      : Color_Image_int,
          'KEY_COLOR_WINDOW'     : Color_Window_int,
          'KEY_COLOR_CHARGING'   : Color_Charging_int,
          'KEY_COLOR_ERROR'      : Color_Error_int,
          'KEY_COLOR_BATTERYLOW' : Color_BatteryLow_int,
          'KEY_TEMPERATURE_CELCIUS' : TemperatureInCelcius_int,
          'KEY_CLOCK_24H' : Clock24h_int,
          'KEY_DATE_STYLE' : DateStyle_int,
          'KEY_NETWORK_REFRESHTIME' : NetworkRefreshTime_int,
          'KEY_BLUETOOTH_VIBRATIONENABLED' : i_Bluetooth_VibrationEnabled,
          'KEY_NETWORK_VIBRATIONENABLED' : i_Network_VibrationEnabled
          
       };

   // Send to watchapp
   Pebble.sendAppMessage(dictionary, function(){}, function(){});
});
