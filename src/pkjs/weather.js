// Credits for weather providers: gregoiresage
// Please use your own API keys if you copy this code
var m_s_Weather_OpenWeatherMap_Key; 
var m_s_Weather_WeatherUnderground_Key;
var m_s_Weather_DarkSky_Key;
var m_s_Weather_API_Key;
var m_s_Weather_Google_Location_Key;
var m_i_Weather_API_Key_StorageID;

var m_s_Weather_Language;
// Weather location types
var Weather_Location_Type_GeoLocation;
var Weather_Location_Type_CityName;
var Weather_Location_Type_CityID;
// Var to store the location settings
var m_i_Weather_Location_StorageID;
var m_s_Weather_Location_Name;
var m_i_Weather_Location_Type;
var m_s_Weather_Location_Current;
// Store the weather init status
var m_b_WeatherIsInit;

// Store the weather provider
var m_i_Weather_Provider;
var m_i_Weather_Provider_OpenWeatherMap = 0;
var m_i_Weather_Provider_Yahoo = 1;
var m_i_Weather_Provider_WeatherUnderground = 2;
var m_i_Weather_Provider_DarkSky = 3;
var m_i_Weather_Provider_StorageID;

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

function SetLanguage(Language)
{
   if ((Language === '') || (Language === null) || (typeof Language === "undefined"))
   {
      m_s_Weather_Language = 'en';
   }
   else if (Language ==='fr_FR')
   {
      m_s_Weather_Language = 'fr';
   }
   else if (Language ==='de_DE')
   {
      m_s_Weather_Language = 'de';
   }
   else if (Language ==='es_ES')
   {
      m_s_Weather_Language = 'es';
   }
   else if (Language ==='it_IT')
   {
      m_s_Weather_Language = 'it';
   }
   else if (Language ==='pt_PT')
   {
      m_s_Weather_Language = 'pt';
   }
   else if (Language ==='en_CN')
   {
      m_s_Weather_Language = 'zh_cn';
   }
   else if (Language ==='en_TW')
   {
      m_s_Weather_Language = 'zh_tw';
   }
   else
   {
      m_s_Weather_Language = 'en';
   }
}

function GetWeatherUndergroundLanguage()
{
   if (m_s_Weather_Language === 'de')
      return 'DL';
   else if (m_s_Weather_Language === 'es')
      return 'SP';
   else if (m_s_Weather_Language === 'pt')
      return 'BR';
   else if (m_s_Weather_Language === 'zh_cn')
      return 'CN';
   else if (m_s_Weather_Language === 'zh_tw')
      return 'TW';
   else
      return m_s_Weather_Language;
}

function GetDarkSkyLanguage()
{
   if (m_s_Weather_Language === 'zh_cn')
      return 'zh';
   else if (m_s_Weather_Language === 'zh_tw')
      return 'zh-tw';
   return m_s_Weather_Language;
}

function Init(b_Debug)
{
   m_b_Debug = false;//b_Debug;
   
   if (m_b_Debug)
         console.log("[JS:WTHR] Init");
   
   m_s_Weather_OpenWeatherMap_Key = 'f06b4db6cb8de4768d84e8af5b20ae6d'; 
   m_s_Weather_WeatherUnderground_Key = '8425b0c1109d22ef';
   m_s_Weather_DarkSky_Key = '24fef94865f6cb61a34c6172035970d8';
   m_s_Weather_API_Key = '';
   m_s_Weather_Google_Location_Key = 'AIzaSyAsUif3YCmxdoBtL7AsR9FizG38J9SXggI';
   
   
   Weather_Location_Type_GeoLocation = 0;
   Weather_Location_Type_CityName = 1;
   Weather_Location_Type_CityID = 2;
   
   m_i_Weather_Location_StorageID = 0;
   m_i_Weather_Provider_StorageID = 1;
   m_i_Weather_API_Key_StorageID  = 3;
   
   m_s_Weather_Location_Name = '';
   m_s_Weather_Language = 'en';
   m_i_Weather_Location_Type = Weather_Location_Type_GeoLocation;
   m_s_Weather_Location_Current = '';
   m_i_Weather_Provider = m_i_Weather_Provider_OpenWeatherMap;

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

function YahooImageToWeatherID(Image)
{
   switch(Image){
          case 31 :
          case 32 :
          case 33 :
          case 34 :
            return 2;
          case 29 :
          case 30 :
          case 44 :
            return 4;  
          case 8 :
          case 9 :
            return 9;  
          case 6 :
          case 10 :
          case 11 :
          case 12 :
          case 35 :
          case 40 :
            return 7;
          case 1 :
          case 3 :
          case 4 :
          case 37 :
          case 38 :
          case 39 :
          case 47 :
            return 10;
          case 5 :
          case 7 :
          case 13 :
          case 14 :
          case 15 :
          case 41 :
          case 42 :
          case 43 :
            return 11;
          case 20 :
            return 12;
          default : if (m_b_Debug)
                        console.log("[JS:WTHR:Y] Could not find weather icon for " + Image);
                    return 0;
        }
   
}

function GetYahooData(RequestString)
{
   // Construct the yahooapis.com URL
   var url = 'https://query.yahooapis.com/v1/public/yql?q=select location.city, item.condition, item.forecast from weather.forecast(1) ' + RequestString + ' and u=\'c\' &format=json';
   
   // Send request to OpenWeatherMap
   xhrRequest(url, 'GET', function(responseText) 
   {
      if (m_b_Debug)
         console.log("[JS:WTHR:Y] Got weather data");
      
      //if (m_b_Debug)
      //   console.log(responseText);
      
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
         
      if(typeof json.query !== "undefined")
      {
         // Temperature in Kelvin requires adjustment
         var temperature = Math.round(json.query.results.channel.item.condition.temp);
         console.log('Temperature is ' + temperature);
   
         // Conditions
         //var conditions = json.weather[0].main;      
         var conditions = json.query.results.channel.item.condition.text;      
         console.log('Conditions are ' + conditions);
            
         // MinMax
         var Temp_Min = Math.round(json.query.results.channel.item.forecast.low);
         var Temp_Max = Math.round(json.query.results.channel.item.forecast.high);
         console.log('MinMax ' + Temp_Min + ' ' +Temp_Max);
         // Icon
         var iconname = YahooImageToWeatherID(parseInt(json.query.results.channel.item.condition.code));
         console.log('Icon '+json.query.results.channel.item.condition.code + ' - ' + iconname);
         
         // Location
         var location = json.query.results.channel.location.city;
        
         
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
                  console.log("[JS:WTHR:Y] Sent message with ID " + e.data.transactionId);
            },
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:WTHR:Y] Could not send message with ID " + e.data.transactionId + " error: " + e.error);
            });
         
         
      } 
      else
      {
         if (m_b_Debug)
            console.log("[JS:WTHR:Y] Weather data is borked!");
      }

   });
}

function OpenWeatherMapImageToWeatherID(Image)
{
   if      (Image == '01n')
      return 1;
   else if (Image == '01d')
      return 2;
   else if (Image == '02n')
      return 3;
   else if (Image == '02d')
      return 4;
   else if (Image == '03n')
      return 5;
   else if (Image == '03d')
      return 5;
   else if (Image == '04n')
      return 6;
   else if (Image == '04d')
      return 6;
   else if (Image == '09n')
      return 7;
   else if (Image == '09d')
      return 7;
   else if (Image == '10n')
      return 8;
   else if (Image == '10d')
      return 9;
   else if (Image == '11n')
      return 10;
   else if (Image == '11d')
      return 10;
   else if (Image == '13n')
      return 11;
   else if (Image == '13d')
      return 11;
   else if (Image == '50n')
      return 12;
   else if (Image == '50d')
      return 12;
   else 
      return 0;
}

function GetOpenWeatherMapData(RequestString)
{
   
   // Construct the OpenWeatherMap.org URL
  var url = 'http://api.openweathermap.org/data/2.5/weather?' + RequestString + '&lang='+m_s_Weather_Language+'&appid=' + m_s_Weather_API_Key;
     
   
   // Send request to OpenWeatherMap
   xhrRequest(url, 'GET', function(responseText) 
   {
      if (m_b_Debug)
         console.log("[JS:WTHR:OWM] Got weather data");
      
      //if (m_b_Debug)
      //   console.log(responseText);
      
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
         
      if(typeof json.main !== "undefined")
      {
         // Temperature in Kelvin requires adjustment
         var temperature = Math.round(json.main.temp - 273.15);
         //console.log('Temperature is ' + temperature);
   
         // Conditions
         //var conditions = json.weather[0].main;      
         var conditions = json.weather[0].description;      
         //console.log('Conditions are ' + conditions);
            
         // MinMax
         var Temp_Min = Math.round(json.main.temp_min - 273.15);
         var Temp_Max = Math.round(json.main.temp_max - 273.15);
         // Icon
         var iconname = OpenWeatherMapImageToWeatherID(json.weather[0].icon);
   
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
                  console.log("[JS:WTHR:OWM] Sent message with ID " + e.data.transactionId);
            },
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:WTHR:OWM] Could not send message with ID " + e.data.transactionId + " error: " + e.error);
            });
      } 
      else
      {
         if (m_b_Debug)
            console.log("[JS:WTHR:OWM] Weather data is borked!");
      }
         
         
   });
}

function WeatherundergroundImageToWeatherID(Image)
{
   if(Image === 'clear')
   {
      return 2;
   }
   else if(Image === 'mostlyysunny' || Image === 'partlycloudy')
   {
      return 4;
   }
   else if(Image === 'partlysunny' || Image === 'mostlycloudy')
   {
      return 5;
   }
   else if(Image === 'cloudy')
   {
      return 6;
   }
   else if(Image === 'rain')
   {
      return 7;
   }
   else if(Image === 'tstorm')
   {
      return 10;
   }
   else if(Image === 'snow' || Image === 'sleet' || Image === 'flurries')
   {
      return 11;
   }
   else if(Image === 'fog' || Image === 'hazy')
   {
      return 12;
   }
   else 
   {
      return 0;
   }
}

function GetWeatherUndergroundData(RequestString)
{
   
   // Construct the wunderground.com URL
   var url = 'http://api.wunderground.com/api/' + m_s_Weather_API_Key + '/forecast/conditions/lang:'+GetWeatherUndergroundLanguage()+'/q/' + RequestString + '.json';
   
   // Send request to OpenWeatherMap
   xhrRequest(url, 'GET', function(responseText) 
   {
      if (m_b_Debug)
         console.log("[JS:WTHR:WU] Got weather data");
      
      //if (m_b_Debug)
      //   console.log(responseText);
      
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
      
      if(typeof json.current_observation !== "undefined")
      {
         // Temperature in Kelvin requires adjustment
         var temperature = Math.round(json.current_observation.temp_c);
         //console.log('Temperature is ' + temperature);
   
         // Conditions
         //var conditions = json.weather[0].main;      
         var conditions = json.current_observation.weather;      
         //console.log('Conditions are ' + conditions);
            
         // MinMax
         var Temp_Min = Math.round(json.forecast.simpleforecast.forecastday[0].low.celcius);
         var Temp_Max = Math.round(json.forecast.simpleforecast.forecastday[0].high.celcius);
         // Icon
         var iconname = WeatherundergroundImageToWeatherID(json.current_observation.icon);
   
         // Location
         var location = json.current_observation.display_location.full;
   
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
                  console.log("[JS:WTHR:WU] Sent message with ID " + e.data.transactionId);
            },
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:WTHR:WU] Could not send message with ID " + e.data.transactionId + " error: " + e.error);
            });
      } 
      else
      {
         if (m_b_Debug)
            console.log("[JS:WTHR:WU] Weather data is borked!");
      }
         
         
   });
}

function DarkSkyImageToWeatherID(Image)
{
   if(Image === 'clear-day')
   {
      return 2;
   }   
   else if (Image === 'clear-night')
   {
      return 1;         
   }
   else if (Image === 'partly-cloudy-day')
   {
      return 4;         
   }
   else if (Image === 'partly-cloudy-night')
   {
      return 3;         
   }
   else if (Image === 'cloudy')
   {
      return 5;         
   }
   else if (Image === 'rain')
   {
      return 7;         
   }
   else if (Image === 'thunderstorm')
   {
      return 10;         
   }
   else if (Image === 'snow' || Image === 'sleet')
   {
      return 11;         
   }
   else if (Image === 'fog')
   {
      return 12;         
   }
   return 0;
}

function GetDarkSkyData(RequestString)
{
   
   // Construct the darksky.net URL
   var url = 'https://api.darksky.net/forecast/' + m_s_Weather_API_Key + '/' + RequestString + '?exclude=minutely,hourly,alerts,flags&units=si&lang=' + GetDarkSkyLanguage();
   
   // Send request to OpenWeatherMap
   xhrRequest(url, 'GET', function(responseText) 
   {
      if (m_b_Debug)
         console.log("[JS:WTHR:DS] Got weather data");
      
      //if (m_b_Debug)
      //   console.log(responseText);
      
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
      
      if(typeof json.currently !== "undefined")
      {
         // Temperature in Kelvin requires adjustment
         var temperature = Math.round(json.currently.temperature);
         //console.log('Temperature is ' + temperature);
   
         // Conditions
         var conditions = json.currently.summary;      
         //console.log('Conditions are ' + conditions);
            
         // MinMax
         var Temp_Min = Math.round(json.daily.data[0].temperatureMin);
         var Temp_Max = Math.round(json.daily.data[0].temperatureMax);
         // Icon
         var iconname = DarkSkyImageToWeatherID(json.currently.icon);
   
        
         // Assemble dictionary using our keys
         var dictionary = 
         {
            'TEMPERATURE': temperature,
            'CONDITIONS': conditions,
            'ICON': iconname,
            'ONLINE': 1,
            'WEATHER_TEMPERATURE_MIN' : Temp_Min,
            'WEATHER_TEMPERATURE_MAX' : Temp_Max
         };
         OpenStreetMapGetCityByLoc(dictionary,RequestString);
           
      } 
      else
      {
         if (m_b_Debug)
            console.log("[JS:WTHR:DS] Weather data is borked!");
      }
         
         
   });
}

function OpenStreetMapGetByName(CityName)
{ 
   var url = 'https://nominatim.openstreetmap.org/search.php?format=json&limit=1&q='+CityName;
   xhrRequest(url, 'GET', function(responseText) 
   {
      if (m_b_Debug)
         console.log("[JS:WTHR:OSM] Got cityname data");
      
      //if (m_b_Debug)
      //   console.log(responseText);
      
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
      
      if (json.length > 0)
      {
         var lat = json[0].lat;
         var lon = json[0].lon;
         
         if (m_b_Debug)
            console.log("[JS:WTHR:OSM] " + lat + ',' + lon);
         
         GetDarkSkyData(lat + ',' + lon);
      }
      else
      {
         if (m_b_Debug)
            console.log("[JS:WTHR:OSM] No Location data");
         SendWeatherError('Unknown city');
      }
      
   });
}

function OpenStreetMapGetByID(CityID)
{ 
   var url = 'https://nominatim.openstreetmap.org/lookup?format=json&osm_ids=N'+CityID;
   xhrRequest(url, 'GET', function(responseText) 
   {
      if (m_b_Debug)
         console.log("[JS:WTHR:OSM] Got cityid data");
      
      //if (m_b_Debug)
      //   console.log(responseText);
      
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
      
      if (json.length > 0)
      {
         var lat = json[0].lat;
         var lon = json[0].lon;
         
         if (m_b_Debug)
            console.log("[JS:WTHR:OSM] " + lat + ',' + lon);
         
         GetDarkSkyData(lat + ',' + lon);
      }
      else
      {
         if (m_b_Debug)
            console.log("[JS:WTHR:OSM] No Location data");
         SendWeatherError('Unknown cityid');
      }
      
   });
}

function OpenStreetMapGetCityByLoc(dictionary,Location)
{
   var array = Location.split(',');
   
   // Construct the openstreetmap.org URL
   var url = 'http://nominatim.openstreetmap.org/reverse?format=json&lat=' + array[0] + '&lon=' + array[1];
   
   // Send request to OpenWeatherMap
   xhrRequest(url, 'GET', function(responseText) 
   {
      if (m_b_Debug)
         console.log("[JS:WTHR:OSM] Got location data");
      
      //if (m_b_Debug)
      //   console.log(responseText);
      
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
      
      if(typeof json.address !== "undefined")
      {
         var city = json.address.hamlet || json.address.village || json.address.town || json.address.city || json.address.county || '';
         if (m_b_Debug)
            console.log("[JS:WTHR:OSM] City: "+city);
         
         dictionary.LOCATION = city;
         
         
         // Send to Pebble
         Pebble.sendAppMessage(dictionary,
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:WTHR:DS] Sent message with ID " + e.data.transactionId);
            },
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:WTHR:DS] Could not send message with ID " + e.data.transactionId + " error: " + e.error);
            });
      }
      else
      {
         if (m_b_Debug)
            console.log("[JS:WTHR:OSM] Location data is borked!");
      }
      
   });
   return '';
}

function HandleLocation(lat,lon)
{
   // Debug printout
   if (m_b_Debug)
         console.log("[JS:WTHR] Got location, getting weather data");
   
   m_s_Weather_Location_Current = lat + ',' + lon;
   
   switch (parseInt(m_i_Weather_Provider))
   {
      case m_i_Weather_Provider_OpenWeatherMap: GetOpenWeatherMapData('lat=' + lat + '&lon=' + lon); break;
      case m_i_Weather_Provider_Yahoo: GetYahooData('where woeid in (select woeid from geo.places(1) where text=\'(' + lat + ',' + lon + ')\')'); break; 
      case m_i_Weather_Provider_WeatherUnderground: GetWeatherUndergroundData(lat + ',' + lon); break;          
      case m_i_Weather_Provider_DarkSky: GetDarkSkyData(lat + ',' + lon); break;
      default: if (m_b_Debug)
                  console.log("[JS:WTHR] Unknown weather provider \'" + m_i_Weather_Provider + "\'");
               SendWeatherError('No provider');
   }
}

function LocationSuccess(pos) 
{
   HandleLocation(pos.coords.latitude,pos.coords.longitude);
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
   
   if(err.code == err.PERMISSION_DENIED) 
   {
      if (m_b_Debug)
         console.log('Location access was denied by the user.');  
   } 
   else 
   {
      if (m_b_Debug)
         console.log('location error (' + err.code + '): ' + err.message);
   }
   
   // fallback to google location api
   GetGoogleLocation();
   
}

function GetGoogleLocation()
{
   var url = 'https://www.googleapis.com/geolocation/v1/geolocate?key=' + m_s_Weather_Google_Location_Key;
   
   xhrRequest(url, 'GET', function(responseText) 
   {
      if (m_b_Debug)
         console.log("[JS:WTHR:GL] Got location");
      
      if (m_b_Debug)
         console.log(responseText);
      
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
      
      if(typeof json.location !== "undefined")
      {
         var lat = json.location.lat;
         var lon = json.location.lon;
         if (m_b_Debug)
            console.log("[JS:WTHR:GL] Location: "+lat + "," + lat);
         HandleLocation(lat,lon);
      }
      else
      {
         // Return an error
         SendWeatherError('No location');
      }
   
   });
   // Return an error
   SendWeatherError('No location');
}

function SendWeatherError(Text)
{
   // Assemble dictionary using our keys
   var dictionary = 
       {
          'TEMPERATURE': -200,
          'CONDITIONS': Text,
          'ICON': "erroricon",
          'LOCATION': Text,
          'ONLINE': 1,
          'WEATHER_TEMPERATURE_MIN' : 0,
          'WEATHER_TEMPERATURE_MAX' : 0
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

function LoadData()
{
   if (m_b_Debug)
      console.log("[JS:WTHR] Loading weather data");
   // Check if there is some stored weather data
   if (localStorage.getItem(m_i_Weather_Location_StorageID) !== null)
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] Weather data found, loading");
      // There is some stored data, lets load it
      m_s_Weather_Location_Name = localStorage.getItem(m_i_Weather_Location_StorageID);
      m_i_Weather_Location_Type = GetLocationType(m_s_Weather_Location_Name);
   }
   else
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] No weather data found, using default values");
      // There is no stored data, lets use dafault values
      m_i_Weather_Location_Type = Weather_Location_Type_GeoLocation;
   }
   
   // Check if there is some stored provider data
   if (localStorage.getItem(m_i_Weather_Provider_StorageID) !== null)
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] Provider data found, loading");
      // There is some stored data, lets load it
      m_i_Weather_Provider = localStorage.getItem(m_i_Weather_Provider_StorageID);
   }
   else
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] No provider data found, using default values");
      // There is no stored data, lets use dafault values
      m_i_Weather_Provider = m_i_Weather_Provider_OpenWeatherMap;
   }
   
   // Check if there is some stored api key data
   if (localStorage.getItem(m_i_Weather_API_Key_StorageID) !== null)
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] API key found, loading");
      // There is some stored data, lets load it
      m_s_Weather_API_Key = localStorage.getItem(m_i_Weather_API_Key_StorageID);
   }
   else
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] No api key found, using default values");
      // There is no stored data, lets use dafault values
      m_s_Weather_API_Key = '';
   }
   
   if (m_s_Weather_API_Key === '')
   {
      switch (parseInt(m_i_Weather_Provider))
      {
         case m_i_Weather_Provider_OpenWeatherMap:     m_s_Weather_API_Key = m_s_Weather_OpenWeatherMap_Key; break;
         case m_i_Weather_Provider_WeatherUnderground: m_s_Weather_API_Key = m_s_Weather_WeatherUnderground_Key; break;
         case m_i_Weather_Provider_DarkSky:            m_s_Weather_API_Key = m_s_Weather_DarkSky_Key; break;
         default: m_s_Weather_API_Key = 'NoKey'; break;
      }
      
      if (m_b_Debug)
         console.log("[JS:WTHR] Using default api key " + m_s_Weather_API_Key + " for provider " + m_i_Weather_Provider);
   }
   else
   {
      if (m_b_Debug)
         console.log("[JS:WTHR] Using api key " + m_s_Weather_API_Key);
   }
   
}

function SaveLocation(LocationName)
{
   if (m_b_Debug)
      console.log("[JS:WTHR] Saving weather location \"" + LocationName +"\"");
   localStorage.setItem(m_i_Weather_Location_StorageID, LocationName);
}

function SaveProvider(Provider)
{
   if (m_b_Debug)
      console.log("[JS:WTHR] Saving weather provider \"" + Provider +"\"");
   localStorage.setItem(m_i_Weather_Provider_StorageID, Provider);
}

function SaveAPIKey(APIKey)
{
   if (m_b_Debug)
      console.log("[JS:WTHR] Saving weather api key \"" + APIKey +"\"");
   localStorage.setItem(m_i_Weather_API_Key_StorageID, APIKey);
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
         if ("geolocation" in navigator)
         {
            // Debug printout
            if (m_b_Debug)
               console.log("[JS:WTHR] Getting location");
            // Get Weather data based on location settings            
            navigator.geolocation.getCurrentPosition(LocationSuccess,LocationError,{timeout: 15000, maximumAge: 60000});
         }
         else
         {
            // Debug printout
            if (m_b_Debug)
               console.log("[JS:WTHR] geolocation not available!");
            // return an error
            SendWeatherError('No geolocation');
         }
         
         
      }
      else if (m_i_Weather_Location_Type == Weather_Location_Type_CityID)
      {
         if (m_b_Debug)
            console.log("[JS:WTHR] Getting weather with city id");
         
         switch (parseInt(m_i_Weather_Provider))
         {
            case m_i_Weather_Provider_OpenWeatherMap: GetOpenWeatherMapData('id=' + m_s_Weather_Location_Name); break;
            case m_i_Weather_Provider_Yahoo: GetYahooData('where woeid=' + m_s_Weather_Location_Name); break;
            case m_i_Weather_Provider_WeatherUnderground: GetWeatherUndergroundData(m_s_Weather_Location_Name); break;
            case m_i_Weather_Provider_DarkSky: OpenStreetMapGetByID(m_s_Weather_Location_Name); break;
            default: if (m_b_Debug)
                        console.log("[JS:WTHR] Unknown weather provider \'" + m_i_Weather_Provider + "\'");
                     SendWeatherError('No provider');
               
         }
      }
      else if (m_i_Weather_Location_Type == Weather_Location_Type_CityName)
      {
         if (m_b_Debug)
            console.log("[JS:WTHR] Getting weather with city name");
         
         switch (parseInt(m_i_Weather_Provider))
         {
            case m_i_Weather_Provider_OpenWeatherMap:  GetOpenWeatherMapData('q=' + m_s_Weather_Location_Name); break;
            case m_i_Weather_Provider_Yahoo: GetYahooData('where woeid in (select woeid from geo.places(1) where text=\'' + m_s_Weather_Location_Name +'\')'); break;
            case m_i_Weather_Provider_WeatherUnderground:  GetWeatherUndergroundData(m_s_Weather_Location_Name); break;
            case m_i_Weather_Provider_DarkSky : OpenStreetMapGetByName(m_s_Weather_Location_Name); break;
            default: if (m_b_Debug)
                        console.log("[JS:WTHR] Unknown weather provider \'" + m_i_Weather_Provider + "\'");
                     SendWeatherError('No provider');
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
module.exports.SaveLocation = SaveLocation;
module.exports.SaveProvider = SaveProvider;
module.exports.SaveAPIKey = SaveAPIKey;
module.exports.LoadData = LoadData;
module.exports.SetLanguage = SetLanguage;

