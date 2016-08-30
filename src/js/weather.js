// Set the used OpenWeatherMap.org API key
// Please use your own if you copy this code
var m_s_Weather_OpenWeatherMap_Key; 

// Weather location types
var Weather_Location_Type_GeoLocation;
var Weather_Location_Type_CityName;
var Weather_Location_Type_CityID;
// Var to store the location settings
var m_i_Weather_Location_StorageID;
var m_s_Weather_Location_Name;
var m_i_Weather_Location_Type;

// Store the weather init status
var m_b_WeatherIsInit;

// Store the weather provider
var m_i_Weather_Provider;

// Debugging
var m_b_Debug;
var m_b_MessagingAvailable; 

function SetMessaging(b_MessagingAvailable)
{
   m_b_MessagingAvailable = b_MessagingAvailable;
   if (m_b_Debug && m_b_MessagingAvailable)
      console.log("[JS:WTHR] Messaging enabled!");
   if (m_b_Debug && !m_b_MessagingAvailable)
      console.log("[JS:WTHR] Messaging disabled!");
}

function Init(b_Debug)
{
   m_b_Debug = b_Debug;
   
   if (m_b_Debug)
         console.log("[JS:WTHR] Init");
   
   m_s_Weather_OpenWeatherMap_Key = 'f06b4db6cb8de4768d84e8af5b20ae6d'; 
   
   Weather_Location_Type_GeoLocation = 0;
   Weather_Location_Type_CityName = 1;
   Weather_Location_Type_CityID = 2;
   
   m_i_Weather_Location_StorageID = 0;
   m_s_Weather_Location_Name = '';
   m_i_Weather_Location_Type = Weather_Location_Type_GeoLocation;
   
   m_i_Weather_Provider = 0;

   // And load the data from storage
   LoadData();
   
   
   m_b_WeatherIsInit = true;
   m_b_MessagingAvailable = false; 
}


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
     //SendReply(false);
  }; 
  xhr.onerror = function () 
  { 
     if (m_b_Debug)
         console.log("[JS:APP] Request failed...");   
     //SendReply(false); 
  };  
  xhr.open(type, url);
  xhr.send();
   
};

function GetOpenWeatherMapData(RequestString )
{
   // Construct the OpenWeatherMap.org URL
  var url = 'http://api.openweathermap.org/data/2.5/weather?' + RequestString + '&appid=' + m_s_Weather_OpenWeatherMap_Key;
     
   
   // Send request to OpenWeatherMap
   xhrRequest(url, 'GET', function(responseText) 
      {
         if (m_b_Debug)
            console.log("[JS:WTHR] Got weather data");
         
         // responseText contains a JSON object with weather info
         var json = JSON.parse(responseText);
         
         if(typeof json.main !== "undefined")
         {
           // Temperature in Kelvin requires adjustment
            var temperature = Math.round(json.main.temp - 273.15);
            //console.log('Temperature is ' + temperature);
   
            // Conditions
            var conditions = json.weather[0].main;      
            //console.log('Conditions are ' + conditions);
            
            // MinMax
            var Temp_Min = Math.round(json.main.temp_min - 273.15);
            var Temp_Max = Math.round(json.main.temp_max - 273.15);
            // Icon
            var iconname = json.weather[0].icon;
   
            // Location
            var city = json.name;
            var country = json.sys.country;
            var location = city + ',' + country;
   
            // Assemble dictionary using our keys
            var dictionary = 
                {
                   'TEMPERATURE': temperature,
                   'CONDITIONS': conditions,
                   'ICON': iconname,
                   'LOCATION': location,
                   'ONLINE': 1,
                   'WEATHER_TEMPERATURE_MIN' : Temp_Min,
                   'WEATHER_TEMPERATURE_MAX' : Temp_Max
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
                     console.log("[JS:WTHR] Could not send message with ID " + e.data.transactionId + " error: " + e.error);
               });
         } 
         else
         {
            if (m_b_Debug)
               console.log("[JS:WTHR] Weather data is borked!");
         }
         
         
    });
}

function GetYahooData(RequestString )
{
   // Construct the OpenWeatherMap.org URL
  var url = 'http://api.openweathermap.org/data/2.5/weather?' + RequestString + '&appid=' + m_s_Weather_OpenWeatherMap_Key;
     
   
   // Send request to OpenWeatherMap
   xhrRequest(url, 'GET', function(responseText) 
      {
         if (m_b_Debug)
            console.log("[JS:WTHR] Got weather data");
         
         // responseText contains a JSON object with weather info
         var json = JSON.parse(responseText);
         
         if(typeof json.main !== "undefined")
         {
           // Temperature in Kelvin requires adjustment
            var temperature = Math.round(json.main.temp - 273.15);
            //console.log('Temperature is ' + temperature);
   
            // Conditions
            var conditions = json.weather[0].main;      
            //console.log('Conditions are ' + conditions);
            
            // MinMax
            var Temp_Min = Math.round(json.main.temp_min - 273.15);
            var Temp_Max = Math.round(json.main.temp_max - 273.15);
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
                   'KEY_ONLINE': 1,
                   'KEY_WEATHER_TEMPERATURE_MIN' : Temp_Min,
                   'KEY_WEATHER_TEMPERATURE_MAX' : Temp_Max
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
                     console.log("[JS:WTHR] Could not send message with ID " + e.data.transactionId + " error: " + e.error);
               });
         } 
         else
         {
            if (m_b_Debug)
               console.log("[JS:WTHR] Weather data is borked!");
         }
         
         
    });
}

function LocationSuccess(pos) 
{
   // Debug printout
   if (m_b_Debug)
         console.log("[JS:WTHR] Got location, getting weather data");
   
   // OpenWeatherMap
   if (m_i_Weather_Provider === 0)
   {
      GetOpenWeatherMapData('lat=' + pos.coords.latitude + '&lon=' + pos.coords.longitude);
   }
   // Yahoo
   else if (m_i_Weather_Provider === 1)
   {
      GetYahooData();
   }
   // WeatherUnderground
   else if (m_i_Weather_Provider === 2)
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] Unknown weather provider");
   }
   
   
}
// A function to check if a variable is a number
function isNumeric(n) 
{
   return !isNaN(parseFloat(n)) && isFinite(n);
}

// Function to check what type of location we have
function GetLocationType(LocationName)
{
   if (m_b_Debug)
            console.log("[JS:WTHR] Checking location type of \"" + LocationName+"\"");
   

   // Lets see what type of var this is
   if ((LocationName === '') || (LocationName === null) || (typeof LocationName === "undefined"))
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

function LocationError(err) 
{
   // We could not get the location....
   // Debug printout
   if (m_b_Debug)
      console.log("[JS:WTHR] Could not get location data");
}

function LoadData()
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
      m_i_Weather_Location_Type = GetLocationType(m_s_Weather_Location_Name);
   }
   else
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] No data found, using default values");
      // There is no stored data, lets use dafault values
      m_i_Weather_Location_Type = Weather_Location_Type_GeoLocation;
   }
}

function SaveData(LocationName)
{
   if (m_b_Debug)
      console.log("[JS:WTHR] Saving weather data \"" + LocationName +"\"");
   localStorage.setItem(m_i_Weather_Location_StorageID, LocationName);
}

function GetData() 
{
   if ((typeof m_b_WeatherIsInit === "undefined") || (m_b_WeatherIsInit === false))
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] Weather is not yet initialized!");
      return;
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
         navigator.geolocation.getCurrentPosition(LocationSuccess,LocationError,{timeout: 15000, maximumAge: 60000});
      }
      else if (m_i_Weather_Location_Type == Weather_Location_Type_CityID)
      {
         if (m_b_Debug)
            console.log("[JS:WTHR] Getting weather with city id");
         
         // OpenWeatherMap
         if (m_i_Weather_Provider === 0)
         {
            GetOpenWeatherMapData('id=' + m_s_Weather_Location_Name);
         }
         // Yahoo
         else if (m_i_Weather_Provider === 1)
         {
            GetYahooData('https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20%3D%20'+m_s_Weather_Location_Name+'&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys');
         }
         // WeatherUnderground
         else if (m_i_Weather_Provider === 2)
         {
            
         }
      }
      else if (m_i_Weather_Location_Type == Weather_Location_Type_CityName)
      {
         if (m_b_Debug)
            console.log("[JS:WTHR] Getting weather with city name");
         
         // OpenWeatherMap
         if (m_i_Weather_Provider === 0)
         {
            GetOpenWeatherMapData('q=' + m_s_Weather_Location_Name);
         }
         // Yahoo
         else if (m_i_Weather_Provider === 1)
         {
            GetYahooData('https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22'+m_s_Weather_Location_Name+'%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys');
         }
         // WeatherUnderground
         else if (m_i_Weather_Provider === 2)
         {
            if (m_b_Debug)
               console.log("[JS:WTHR] Unknown weather provider");
         }
      }
      else
      {
         if (m_b_Debug)
            console.log("[JS:WTHR] Unknown location type!");
      }
   }
}

module.exports.SetMessaging = SetMessaging;
module.exports.Init = Init;
module.exports.GetData = GetData;
module.exports.SaveData = SaveData;
module.exports.LoadData = LoadData;
