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


function Weather_DownloadData(RequestString )
{
   // Construct the OpenWeatherMap.org URL
  var url = 'http://api.openweathermap.org/data/2.5/weather?' + RequestString + '&appid=' + m_s_Weather_APIKey;
  
  if(typeof m_s_Weather_APIKey === "undefined")
  { 
     if (m_b_Debug)
        console.log("[JS:WTHR] Got no api key?");
     return;
  }
   
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
         } 
         else
         {
            if (m_b_Debug)
               console.log("[JS:WTHR] Weather data is borked!");
         }
         
         
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