var myAPIKey = 'f06b4db6cb8de4768d84e8af5b20ae6d';

var LastOnlineCheck = false;

var battery;
var batteryAvailiable;
var MessagingAvailiable = false;

Pebble.addEventListener('showConfiguration', function() {
  var url = 'https://rawgit.com/aHcVolle/TrekVolle/master/config/index.html';
  //console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) 
{
   var configData = JSON.parse(decodeURIComponent(e.response));
   //console.log('Configuration page returned: ' + JSON.stringify(configData));

   var Color_Background = configData.Color_Background;
   var Color_Text = configData.Color_Text;
   var Color_Image = configData.Color_Image;
   var Color_Window = configData.Color_Window;
   var Color_Charging = configData.Color_Charging;
   var Color_Error = configData.Color_Error;
   var Color_BatteryLow = configData.Color_BatteryLow;

   //console.log('Color_Text: ' + Color_Text);
  
   var Color_Background_int = parseInt(Color_Background.substring(2), 16);
   var Color_Text_int = parseInt(Color_Text.substring(2), 16);
   var Color_Image_int = parseInt(Color_Image.substring(2), 16);
   var Color_Window_int = parseInt(Color_Window.substring(2), 16);
   var Color_Charging_int = parseInt(Color_Charging.substring(2), 16);
   var Color_Error_int = parseInt(Color_Error.substring(2), 16);
   var Color_BatteryLow_int = parseInt(Color_BatteryLow.substring(2), 16);
   
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
          'KEY_COLOR_BATTERYLOW' : Color_BatteryLow_int
       };

   // Send to watchapp
   Pebble.sendAppMessage(dictionary, function(){}, function(){});
});


navigator.getBattery().then(function(battery) 
{
  battery.addEventListener('chargingchange', function(){ updateChargeInfo();});
  function updateChargeInfo(){getBattery();}

  battery.addEventListener('levelchange', function(){updateLevelInfo();});
  function updateLevelInfo(){getBattery();}

  battery.addEventListener('chargingtimechange', function(){updateChargingInfo();});
  function updateChargingInfo(){getBattery();}

  battery.addEventListener('dischargingtimechange', function(){updateDischargingInfo();});
  function updateDischargingInfo(){ getBattery();} 
});


function batterySuccess(batteryManager) 
{
   // Assign batteryManager to globally 
   //   available `battery` variable.
   battery = batteryManager;
   batteryAvailiable = true;
   getBattery();
}

function batteryFailure()
{
   batteryAvailiable = false;
}

// Listen for when the watchface is opened
Pebble.addEventListener('ready', function(e) 
{
   MessagingAvailiable = true;
   // Get the initial online status
   //getOnline();
   
   if("getBattery" in navigator) 
   {
      // Request battery manager object.
      navigator.getBattery().then(batterySuccess, batteryFailure);
   } 
   else 
   {
      // API is not supported, fail gracefully.
      console.log("Battery API not supported!");
   }
   
   // Get the initial weather
   getWeather();
});

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',function(e) 
{
   if ('KEY_TEMPERATURE' in e.payload)
   {
      //console.log("Getting Weather info...");
      getWeather();
   }
   else if ('KEY_ONLINE' in e.payload)
   {
      //console.log("Getting Online info...");
      getOnline();
   }
   else if ('KEY_BATTERY_CHARGE' in e.payload)
   {
      getBattery();
   }
   
});

function getBattery()
{
   
   //console.log("Getting battery info...");
   //navigator.getBattery().level;
   if (batteryAvailiable && MessagingAvailiable)
   {
      var charging = 0;
      if (battery.charging)
         charging = 1;
      var dictionary = 
             {
                'KEY_BATTERY_CHARGE': battery.level * 100,
                'KEY_BATTERY_STATE': charging
             };
      
      // Send to Pebble
      Pebble.sendAppMessage(dictionary,function(e){},function(e){});
   }
}

var xhrRequest = function (url, type, callback) 
{
  
  var xhr = new XMLHttpRequest();
  xhr.onload = function () 
     {
       callback(this.responseText);
     };  
  xhr.open(type, url);
  xhr.send();
  

};

function locationSuccess(pos) 
{
  
   
  // Construct URL
  var url = 'http://api.openweathermap.org/data/2.5/weather?lat=' +
      pos.coords.latitude + '&lon=' + pos.coords.longitude + '&appid=' + myAPIKey;

  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', 
    function(responseText) 
      {
          LastOnlineCheck = true;
          //console.log('JS: Received weather update...');
         
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
          var location = json.name;  

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
       Pebble.sendAppMessage(dictionary,function(e){},function(e){});
    });
}

function locationError(err) 
{
  //console.log('Error requesting location!');
}

function getWeather() 
{
   //console.log('JS: Requesting weather update...');
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}

function SendPebbleTimeOutMsg(value)
{
   var dictionary ={'KEY_ONLINE': value};
   Pebble.sendAppMessage(dictionary,function(e){},function(e){});
}

function getOnline()
{
   if (LastOnlineCheck === false)
   {
      SendPebbleTimeOutMsg(0);
   }
   LastOnlineCheck = false;
   // Construct URL
   var url = 'https://rawgit.com/aHcVolle/TrekVolle/master/online.html';
   
  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', 
    function(responseText) 
      {
          LastOnlineCheck = true;
          //console.log('Got an online reply!');
          SendPebbleTimeOutMsg(1);
    });
   
}

