var Weather_APIKey = 'f06b4db6cb8de4768d84e8af5b20ae6d'; // Please use your own....

function Weather_LocationSuccess(pos) 
{
   if (m_b_Debug)
         console.log("[JS:WTHR] Got location, getting weather data");
   
  // Construct URL
  var url = 'http://api.openweathermap.org/data/2.5/weather?lat=' +
      pos.coords.latitude + '&lon=' + pos.coords.longitude + '&appid=' + Weather_APIKey;

  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', 
    function(responseText) 
      {
         if (m_b_Debug)
         console.log("[JS:WTHR] Got weather data");
         
          m_b_LastOnlineCheck = true;
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

function Weather_LocationError(err) 
{
  //console.log('Error requesting location!');
   if (m_b_Debug)
         console.log("[JS:WTHR] Could not get location data");
}

function Weather_GetData() 
{
   if (m_b_Debug)
         console.log("[JS:WTHR] Getting weather data");
   //console.log('JS: Requesting weather update...');
  navigator.geolocation.getCurrentPosition(
    Weather_LocationSuccess,
    Weather_LocationError,
    {timeout: 15000, maximumAge: 60000}
  );
}