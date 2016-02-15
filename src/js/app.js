var m_b_MessagingAvailiable = false;
var m_b_Debug = true;

// Listen for when the watchface is opened
Pebble.addEventListener('ready', function(e) 
{
   m_b_MessagingAvailiable = true;
   if (m_b_Debug)
         console.log("[JS:APP] JS ready...");
   
   Battery_Init();
   
   // Get the initial weather
   Weather_GetData();
});

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',function(e) 
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
  xhr.open(type, url);
  xhr.send();
};



