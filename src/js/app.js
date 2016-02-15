var m_b_MessagingAvailiable = false;

// Listen for when the watchface is opened
Pebble.addEventListener('ready', function(e) 
{
   m_b_MessagingAvailiable = true;
   // Get the initial online status
   //getOnline();
   
   Battery_Init();
   
   // Get the initial weather
   Weather_GetData();
});

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',function(e) 
{
   if ('KEY_TEMPERATURE' in e.payload)
   {
      //console.log("Getting Weather info...");
      Weather_GetData();
   }
   else if ('KEY_ONLINE' in e.payload)
   {
      //console.log("Getting Online info...");
      Network_GetData();
   }
   else if ('KEY_BATTERY_CHARGE' in e.payload)
   {
      Battery_GetData();
   }
   
});


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



