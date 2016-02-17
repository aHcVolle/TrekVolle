var m_b_MessagingAvailable = false;
var m_b_Debug = true;

// dummytext
// Set the used OpenWeatherMap.org API key
// Please use your own if you copy this code
var m_s_Weather_APIKey = 'f06b4db6cb8de4768d84e8af5b20ae6d'; 

// Weather location types
var Weather_Location_Type_GeoLocation = 0;
var Weather_Location_Type_CityName = 1;
var Weather_Location_Type_CityID = 2;
// Var to store the location settings
var m_i_Weather_Location_StorageID = 0;
var m_s_Weather_Location_Name = '';
var m_i_Weather_Location_Type = Weather_Location_Type_GeoLocation;
// Variable to store if this is the first request
var m_b_Weather_FirstRequest = true;


// This will hold the battery manager object
var m_Battery;
// Simple var to save if the battery manager is available
var m_b_Battery_Available;


var ConfigVersion = '1_3';



// Listen for when the watchface is opened
Pebble.addEventListener('ready', function(e) 
{
   //m_b_MessagingAvailable = true;
   if (m_b_Debug)
         console.log("[JS:APP] JS ready...");
   
   Battery_Init();
   
   // Get the initial weather
   Weather_GetData();
});

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',function(e) 
{
   if (m_b_MessagingAvailable)
   {
      if ('KEY_TEMPERATURE' in e.payload)
      {
         if (m_b_Debug)
            console.log("[JS:APP] Weather info requested...");
         Weather_GetData();
      }
      else if ('KEY_ONLINE' in e.payload)
      {
         if (m_b_Debug)
            console.log("[JS:APP] Online info requested...");
         Network_GetData();
      }
      else if ('KEY_BATTERY_CHARGE' in e.payload)
      {
         if (m_b_Debug)
            console.log("[JS:APP] Battery info requested...");
         Battery_GetData();
      }
   }
});

var xhrRequest = function (url, type, callback) 
{
  if (m_b_Debug)
     console.log("[JS:APP] xhr request: " + url );
  var xhr = new XMLHttpRequest();
  xhr.onload = function () 
  {
     callback(this.responseText);
  };  
  xhr.timeout = 30000; 
  xhr.ontimeout = function () 
  {   
     if (m_b_Debug)
         console.log("[JS:APP] Request timed out...");
     Network_SendReply(false);
  }; 
  xhr.onerror = function () 
  { 
     if (m_b_Debug)
         console.log("[JS:APP] Request failed...");   
     Network_SendReply(false); 
  };  
  xhr.open(type, url);
  xhr.send();
   
};


navigator.getBattery().then(function(battery) 
{
  battery.addEventListener('chargingchange', function(){ updateChargeInfo();});
  function updateChargeInfo(){Battery_GetData();}

  battery.addEventListener('levelchange', function(){updateLevelInfo();});
  function updateLevelInfo(){Battery_GetData();}

  battery.addEventListener('chargingtimechange', function(){updateChargingInfo();});
  function updateChargingInfo(){Battery_GetData();}

  battery.addEventListener('dischargingtimechange', function(){updateDischargingInfo();});
  function updateDischargingInfo(){ Battery_GetData();} 
});



function Battery_InitSuccess(batteryManager) 
{
   // Assign batteryManager to globally 
   //   available `battery` variable.
   if (m_b_Debug)
         console.log("[JS:BATT] Init OK");
   m_Battery = batteryManager;
   m_b_Battery_Available = true;
   Battery_GetData();
}

function Battery_InitFailure()
{
   if (m_b_Debug)
         console.log("[JS:BATT] Init failed");
   m_b_Battery_Available = false;
}

function Battery_Init()
{
   if (m_b_Debug)
         console.log("[JS:BATT] Init...");
   if("getBattery" in navigator) 
   {
      // Request battery manager object.
      navigator.getBattery().then(Battery_InitSuccess, Battery_InitFailure);
   } 
   else 
   {
      // API is not supported, fail gracefully.
      console.log("[JS:BATT] Battery API not supported!");
   }
}

function Battery_GetData()
{   
   if (m_b_Battery_Available && m_b_MessagingAvailable)
   {
      if (m_b_Debug)
         console.log("[JS:BATT] Getting battery data");
      
      var charging = 0;
      if (m_Battery.charging)
         charging = 1;
      var dictionary = 
             {
                'KEY_BATTERY_CHARGE': m_Battery.level * 100,
                'KEY_BATTERY_STATE': charging
             };
      
      // Send to Pebble
      Pebble.sendAppMessage(dictionary,
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:BATT] Sent message with ID " + e.data.transactionId);
            },
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:BATT] Could not send message with ID " + e.data.transactionId + " Error is: " + e.error.message);
            });
   }
}

Pebble.addEventListener('showConfiguration', function() 
{
   var url = 'http://rawgit.com/aHcVolle/TrekVolle/master/config/config_'+ConfigVersion+'.html';
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
   var Weather_Location = configData.Weather_Location;
   
   var Clock_Clock24h = configData.Clock_Clock24h;
   var Clock_Sleep = configData.Clock_Sleep;
   var Clock_Datestyle_ddmmyy = configData.Clock_Datestyle_ddmmyy;
   var Clock_Datestyle_yymmdd = configData.Clock_Datestyle_yymmdd;
   var Clock_Datestyle_mmddyy = configData.Clock_Datestyle_mmddyy;
   
   var Bluetooth_VibrationEnabled = configData.Bluetooth_VibrationEnabled;
   
   var Network_RefreshTime = configData.Network_Refreshtime;
   var Network_VibrationEnabled = configData.Network_VibrationEnabled;
     
   var i_Color_Background = parseInt(Color_Background.substring(2), 16);
   var i_Color_Text = parseInt(Color_Text.substring(2), 16);
   var i_Color_Image = parseInt(Color_Image.substring(2), 16);
   var i_Color_Window = parseInt(Color_Window.substring(2), 16);
   var i_Color_Charging = parseInt(Color_Charging.substring(2), 16);
   var i_Color_Error = parseInt(Color_Error.substring(2), 16);
   var i_Color_BatteryLow = parseInt(Color_BatteryLow.substring(2), 16);
    
   var i_Weather_TemperatureCelcius = (Weather_TemperatureCelcius === 'true') ? 1 : 0;
   var i_Weather_Refreshtime = parseInt(Weather_Refreshtime, 10);
   var i_Weather_RetryUpdate = (Weather_RetryUpdate === 'true') ? 1 : 0;
   var b_Weather_Location_Changed = false;
   if (Weather_Location != m_s_Weather_Location_Name)
   {
      b_Weather_Location_Changed = true;
      Weather_SaveData(Weather_Location);
      Weather_LoadData();
   }
   
   
   var i_Clock_Clock24h = (Clock_Clock24h === 'true') ? 1 : 0;
   var i_Clock_Sleep = (Clock_Sleep === 'true') ? 1 : 0;
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
   
   var i_Bluetooth_VibrationEnabled = (Bluetooth_VibrationEnabled === 'true') ? 1 : 0;
  
   var i_Network_VibrationEnabled = (Network_VibrationEnabled === 'true') ? 1 : 0;
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
      console.log("[JS:CONF] Config:   Weather_Location "+m_s_Weather_Location_Name);
      
      console.log("[JS:CONF] Config: i_Clock_Clock24h "+i_Clock_Clock24h.toString());
      console.log("[JS:CONF] Config: i_Clock_Sleep "+i_Clock_Sleep.toString());
      console.log("[JS:CONF] Config: i_Clock_Datestyle_ddmmyy "+i_Clock_Datestyle_ddmmyy.toString());
      console.log("[JS:CONF] Config: i_Clock_Datestyle_yymmdd "+i_Clock_Datestyle_yymmdd.toString());
      console.log("[JS:CONF] Config: i_Clock_Datestyle_mmddyy "+i_Clock_Datestyle_mmddyy.toString());
      console.log("[JS:CONF] Config: i_Clock_Datestyle "+i_Clock_Datestyle.toString());
      
      console.log("[JS:CONF] Config: i_Network_RefreshTime "+i_Network_RefreshTime.toString());
      console.log("[JS:CONF] Config: i_Network_VibrationEnabled "+i_Network_VibrationEnabled.toString());
      
      console.log("[JS:CONF] Config: i_Bluetooth_VibrationEnabled "+i_Bluetooth_VibrationEnabled.toString());
   }
     
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
          'KEY_CLOCK_SLEEP' : i_Clock_Sleep,
          'KEY_CLOCK_DATESTYLE' : i_Clock_Datestyle,
          'KEY_NETWORK_REFRESHTIME' : i_Network_RefreshTime,          
          'KEY_NETWORK_VIBRATIONENABLED' : i_Network_VibrationEnabled,
          'KEY_BLUETOOTH_VIBRATIONENABLED' : i_Bluetooth_VibrationEnabled
          
       };

   // Send to watchapp
   Pebble.sendAppMessage(dictionary, function(){}, function(){});
   
   // Get weather data if location changed
   if (b_Weather_Location_Changed)
      Weather_GetData();
});


function Network_SendReply(b_IsConnected)
{
   if (m_b_MessagingAvailable)
   {
      // Debug printout
      if (m_b_Debug)
      {
         if (b_IsConnected)
            console.log("[JS:NET] Network check: OK");
         else
            console.log("[JS:NET] Network check: Failed");
      }   
      // Send message to pebble
      var dictionary ={'KEY_ONLINE': b_IsConnected ? 1 : 0};
   	Pebble.sendAppMessage(dictionary,
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:NET] Sent message with ID " + e.data.transactionId);
            },
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:NET] Could not send message with ID " + e.data.transactionId + " Error is: " + e.error.message);
            });  
   }
}

function Network_GetData()
{
   if (m_b_Debug)
         console.log("[JS:NET] Getting network data");
   
   // The easy way does not seem to work...
   //Network_SendReply(navigator.onLine);
   
   // Lets request a webpage.... 
   var url = 'https://rawgit.com/aHcVolle/TrekVolle/master/online.html';
   xhrRequest(url, 'GET', function(responseText) {Network_SendReply(true); });
   
}


function Weather_DownloadData(RequestString )
{
   // Construct the OpenWeatherMap.org URL
  var url = 'http://api.openweathermap.org/data/2.5/weather?' + RequestString + '&appid=' + m_s_Weather_APIKey;
   
  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', function(responseText) 
      {
         if (m_b_Debug)
            console.log("[JS:WTHR] Got weather data");
         
         // responseText contains a JSON object with weather info
         var json = JSON.parse(responseText);

         // Temperature in Kelvin requires adjustment
         var temperature = Math.round(json.main.temp - 273.15);
         //console.log('Temperature is ' + temperature);

         // Conditions
         var conditions = json.weather[0].main;      
         //console.log('Conditions are ' + conditions);

         // Icon
         var iconname = json.weather[0].icon;

         // Location
         var city = json.name;
         var country = json.sys.country;
         var location = city + ',' + country;

         // Assemble dictionary using our keys
         var dictionary = 
             {
                'KEY_TEMPERATURE': temperature,
                'KEY_CONDITIONS': conditions,
                'KEY_ICON': iconname,
                'KEY_LOCATION': location,
                'KEY_ONLINE': 1
             };

         // Send to Pebble
         Pebble.sendAppMessage(dictionary,
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:WTHR] Sent message with ID " + e.data.transactionId);
            },
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:WTHR] Could not send message with ID " + e.data.transactionId + " Error is: " + e.error.message);
            });
    });
}

function Weather_LocationSuccess(pos) 
{
   // Debug printout
   if (m_b_Debug)
         console.log("[JS:WTHR] Got location, getting weather data");
   Weather_DownloadData('lat=' + pos.coords.latitude + '&lon=' + pos.coords.longitude);
}
// A function to check if a variable is a number
function isNumeric(n) 
{
   return !isNaN(parseFloat(n)) && isFinite(n);
}

// Function to check what type of location we have
function Weather_GetLocationType(LocationName)
{
   if (m_b_Debug)
            console.log("[JS:WTHR] Checking location type of \"" + LocationName+"\"");
   

   // Lets see what type of var this is
   if ((LocationName === '') || (LocationName === null))
   {
      // Its empty -> use geolocation
      if (m_b_Debug)
            console.log("[JS:WTHR] Got geolocation type");
      return Weather_Location_Type_GeoLocation;
   }
   else if (isNumeric(LocationName))
   {
      // Its a number, so we have a city id
      if (m_b_Debug)
            console.log("[JS:WTHR] Got city id type");
      return Weather_Location_Type_CityID;
   }
   else
   {
      if (m_b_Debug)
            console.log("[JS:WTHR] Got city name type");
      return Weather_Location_Type_CityName;
   }  
}

function Weather_LocationError(err) 
{
   // We could not get the location....
   // Debug printout
   if (m_b_Debug)
      console.log("[JS:WTHR] Could not get location data");
}

function Weather_LoadData()
{
   if (m_b_Debug)
      console.log("[JS:WTHR] Loading weather data");
   // Check if there is some stored data
   if (localStorage.getItem(m_i_Weather_Location_StorageID) !== null)
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] Data found, loading");
      // There is some stored data, lets load it
      m_s_Weather_Location_Name = localStorage.getItem(m_i_Weather_Location_StorageID);
      m_i_Weather_Location_Type = Weather_GetLocationType(m_s_Weather_Location_Name);
   }
   else
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] No data found, using default values");
      // There is no stored data, lets use dafault values
      m_i_Weather_Location_Type = Weather_Location_Type_GeoLocation;
   }
}

function Weather_SaveData(LocationName)
{
   if (m_b_Debug)
      console.log("[JS:WTHR] Saving weather data \"" + LocationName +"\"");
   localStorage.setItem(m_i_Weather_Location_StorageID, LocationName);
}

function Weather_GetData() 
{
   // Check if this was the first weather request 
   if (m_b_Weather_FirstRequest)
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] First run, loading data");
      // Yes it was the first request 
      m_b_Weather_FirstRequest = false;
      // And load the data from storage
      Weather_LoadData();
      
   }
      
   if (m_b_MessagingAvailable)
   {
      // Lets see what type of location we have
      if (m_i_Weather_Location_Type == Weather_Location_Type_GeoLocation)
      {
         // Debug printout
         if (m_b_Debug)
            console.log("[JS:WTHR] Getting location");
         // Get Weather data based on location settings
         navigator.geolocation.getCurrentPosition(Weather_LocationSuccess,Weather_LocationError,{timeout: 15000, maximumAge: 60000});
      }
      else if (m_i_Weather_Location_Type == Weather_Location_Type_CityID)
      {
         if (m_b_Debug)
            console.log("[JS:WTHR] Getting weather with city id");
         Weather_DownloadData('id=' + m_s_Weather_Location_Name);
      }
      else if (m_i_Weather_Location_Type == Weather_Location_Type_CityName)
      {
         if (m_b_Debug)
            console.log("[JS:WTHR] Getting weather with city name");
         Weather_DownloadData('q=' + m_s_Weather_Location_Name);
      }
      else
      {
         
      }
   }
}
