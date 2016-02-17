
var ConfigVersion = '1_3';


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
   
   var dictionary = {};
   
   if(typeof configData.Color_Background !== "undefined")
   { 
      var Color_Background = configData.Color_Background;
      var i_Color_Background = parseInt(Color_Background.substring(2), 16);
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Color_Background "+i_Color_Background.toString());
      dictionary['KEY_COLOR_BACKGROUND'] = i_Color_Background;
   }
   
   if(typeof configData.Color_Text !== "undefined")
   { 
      var Color_Text = configData.Color_Text;
      var i_Color_Text = parseInt(Color_Text.substring(2), 16);
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Color_Text "+i_Color_Text.toString());
      dictionary['KEY_COLOR_TEXT'] = i_Color_Text;
   }
   
   if(typeof configData.Color_Image !== "undefined")
   { 
      var Color_Image = configData.Color_Image;
      var i_Color_Image = parseInt(Color_Image.substring(2), 16);
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Color_Image "+i_Color_Image.toString());
      dictionary['KEY_COLOR_IMAGE'] = i_Color_Image;
   }
   
   if(typeof configData.Color_Window !== "undefined")
   { 
      var Color_Window = configData.Color_Window;
      var i_Color_Window = parseInt(Color_Window.substring(2), 16);
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Color_Window "+i_Color_Window.toString());
      dictionary['KEY_COLOR_WINDOW'] = i_Color_Window;
   }
   
   if(typeof configData.Color_Charging !== "undefined")
   { 
      var Color_Charging = configData.Color_Charging;
      var i_Color_Charging = parseInt(Color_Charging.substring(2), 16);
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Color_Charging "+i_Color_Charging.toString());
      dictionary['KEY_COLOR_CHARGING'] = i_Color_Charging;
   }
   
   if(typeof configData.Color_Error !== "undefined")
   { 
      var Color_Error = configData.Color_Error;
      var i_Color_Error = parseInt(Color_Error.substring(2), 16);
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Color_Error "+i_Color_Error.toString());
      dictionary['KEY_COLOR_ERROR'] = i_Color_Error;
   }

   if(typeof configData.Color_BatteryLow !== "undefined")
   { 
      var Color_BatteryLow = configData.Color_BatteryLow;
      var i_Color_BatteryLow = parseInt(Color_BatteryLow.substring(2), 16);
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Color_BatteryLow "+i_Color_BatteryLow.toString());
      dictionary['KEY_COLOR_BATTERYLOW'] = i_Color_BatteryLow;
   }
   
   if(typeof configData.Weather_TemperatureCelcius !== "undefined")
   { 
      var Weather_TemperatureCelcius = configData.Weather_TemperatureCelcius;
      var i_Weather_TemperatureCelcius = (Weather_TemperatureCelcius === 'true') ? 1 : 0;
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Weather_TemperatureCelcius "+i_Weather_TemperatureCelcius.toString());
      dictionary['KEY_WEATHER_TEMPERATURECELCIUS'] = i_Weather_TemperatureCelcius;
   }
   
   if(typeof configData.Weather_Refreshtime !== "undefined")
   { 
      var Weather_Refreshtime = configData.Weather_Refreshtime;
      var i_Weather_Refreshtime = parseInt(Weather_Refreshtime, 10);
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Weather_Refreshtime "+i_Weather_Refreshtime.toString());
      dictionary['KEY_WEATHER_REFRESHTIME'] = i_Weather_Refreshtime;
   }

   if(typeof configData.Weather_RetryUpdate !== "undefined")
   { 
      var Weather_RetryUpdate = configData.Weather_RetryUpdate;
      var i_Weather_RetryUpdate = (Weather_RetryUpdate === 'true') ? 1 : 0;
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Weather_RetryUpdate "+i_Weather_RetryUpdate.toString());
      dictionary['KEY_WEATHER_RETRYUPDATE'] = i_Weather_RetryUpdate;
   }
   
   var b_Weather_Location_Changed = false;
   if(typeof configData.Weather_Location !== "undefined")
   { 
      var Weather_Location = configData.Weather_Location;
      b_Weather_Location_Changed = true;
      Weather_SaveData(Weather_Location);
      Weather_LoadData();
             
      if (m_b_Debug) console.log("[JS:CONF] Config:   Weather_Location \""+m_s_Weather_Location_Name+"\"");
   }
   
   if(typeof configData.Clock_Clock24h !== "undefined")
   { 
      var Clock_Clock24h = configData.Clock_Clock24h;
      var i_Clock_Clock24h = (Clock_Clock24h === 'true') ? 1 : 0;
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Clock_Clock24h "+i_Clock_Clock24h.toString());
      dictionary['KEY_CLOCK_CLOCK24H'] = i_Clock_Clock24h;
   }
   
   if(typeof configData.Clock_Sleep !== "undefined")
   { 
      var Clock_Sleep = configData.Clock_Sleep;
      var i_Clock_Sleep = (Clock_Sleep === 'true') ? 1 : 0;
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Clock_Sleep "+i_Clock_Sleep.toString());
      dictionary['KEY_CLOCK_SLEEP'] = i_Clock_Sleep;
   }
   
   if ((typeof configData.Clock_Datestyle_ddmmyy !== "undefined") && (typeof configData.Clock_Datestyle_yymmdd !== "undefined") && (typeof configData.Clock_Datestyle_mmddyy !== "undefined"))
   { 
      var Clock_Datestyle_ddmmyy = configData.Clock_Datestyle_ddmmyy;
      var Clock_Datestyle_yymmdd = configData.Clock_Datestyle_yymmdd;
      var Clock_Datestyle_mmddyy = configData.Clock_Datestyle_mmddyy;
      
      var i_Clock_Datestyle_ddmmyy = (Clock_Datestyle_ddmmyy === 'true') ? 1 : 0;
      var i_Clock_Datestyle_yymmdd = (Clock_Datestyle_yymmdd === 'true') ? 1 : 0;
      var i_Clock_Datestyle_mmddyy = (Clock_Datestyle_mmddyy === 'true') ? 1 : 0;
      
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
      
      
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Clock_Datestyle "+i_Clock_Datestyle.toString());
      dictionary['KEY_CLOCK_DATESTYLE'] = i_Clock_Datestyle;
   }
   
   if(typeof configData.Bluetooth_VibrationEnabled !== "undefined")
   { 
      var Bluetooth_VibrationEnabled = configData.Bluetooth_VibrationEnabled;
      var i_Bluetooth_VibrationEnabled = (Bluetooth_VibrationEnabled === 'true') ? 1 : 0;
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Bluetooth_VibrationEnabled "+i_Bluetooth_VibrationEnabled.toString());
      dictionary['KEY_BLUETOOTH_VIBRATIONENABLED'] = i_Bluetooth_VibrationEnabled;
   }
   
   if(typeof configData.Network_VibrationEnabled !== "undefined")
   { 
      var Network_VibrationEnabled = configData.Network_VibrationEnabled;
      var i_Network_VibrationEnabled = (Network_VibrationEnabled === 'true') ? 1 : 0;
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Network_VibrationEnabled "+i_Network_VibrationEnabled.toString());
      dictionary['KEY_NETWORK_VIBRATIONENABLED'] = i_Network_VibrationEnabled;
   }
  
   if(typeof configData.Network_RefreshTime !== "undefined")
   { 
      var Network_RefreshTime = configData.Network_RefreshTime;
      var i_Network_RefreshTime = parseInt(Network_RefreshTime, 10);
      if (m_b_Debug) console.log("[JS:CONF] Config: i_Network_RefreshTime "+i_Network_RefreshTime.toString());
      dictionary['KEY_NETWORK_REFRESHTIME'] = i_Network_RefreshTime;
   }
   
   // Send to watchapp
   Pebble.sendAppMessage(dictionary, function(){}, function(){});
   
   // Get weather data if location changed
   if (b_Weather_Location_Changed)
      Weather_GetData();
});