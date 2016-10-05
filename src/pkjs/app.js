


var battery = require('./battery');
var network = require('./network');
var weather = require('./weather');
var configuration = require('./configuration');


var m_b_MessagingAvailable;
var m_b_Debug;

// Listen for when the watchface is opened
Pebble.addEventListener('ready', function(e) 
{
   m_b_Debug = true;   
   
   if (m_b_Debug)
         console.log("[JS:APP] JS ready...");
   
   // Configuration
   configuration.Init(m_b_Debug);
   
   // Init the network check
   network.SetDebug(m_b_Debug);
   
   // Init the messaging
   Messaging_Init();

   // Init the battery service
   battery.Init(m_b_Debug);
   
   // Init the weather
   weather.Init(m_b_Debug);

   // DoPong
   Messaging_DoPong();
   
});


function Messaging_DoPong()
{
   if ((typeof m_b_MessagingAvailable === "undefined") || (m_b_MessagingAvailable === false))
   {
      if (m_b_Debug)
         console.log("[JS:APP] Messaging is not yet initialized!");
      return;
   } 
   var dictionary ={'PINGPONG': 1};
   Pebble.sendAppMessage(dictionary,
                         function(e)
                         {
                            if (m_b_Debug)
                               console.log("[JS:APP] Sent message with ID " + e.data.transactionId);
                         },
                         function(e)
                         {
                            if (m_b_Debug)
                               console.log("[JS:APP] Could not send message with ID " + e.data.transactionId + " Error is: " + e.error);
                         });  
   
}

function Messaging_Init()
{
   if (m_b_Debug)
         console.log("[JS:APP] Messaging init...");
   
   m_b_MessagingAvailable = false;
   
   // Listen for when an AppMessage is received
   Pebble.addEventListener('appmessage',function(e) 
   {
      if (m_b_MessagingAvailable)
      {
         var b_Found = false;
         /*if ('WEATHER_LANGUAGE' in e.payload)
         {
            if (m_b_Debug)
               console.log("[JS:APP] Weather language set.");
            weather.SetLanguage(e.payload.value);
            b_Found = true;
         }*/
         if ('TEMPERATURE' in e.payload)
         {
            
            var Language = e.payload.TEMPERATURE.toString();
            if (m_b_Debug)
               console.log("[JS:APP] Weather info requested ..."+Language);
            weather.SetLanguage(Language);
            weather.SetMessaging(true);
            weather.GetData();
            b_Found = true;
         }
         if ('ONLINE' in e.payload)
         {
            if (m_b_Debug)
               console.log("[JS:APP] Online info requested...");
            network.GetData();
            b_Found = true;
         }
         if ('BATTERY_CHARGE' in e.payload)
         {
            if (m_b_Debug)
               console.log("[JS:APP] Battery info requested...");
            battery.GetData();
            b_Found = true;
         }
         if ('PINGPONG' in e.payload)
         {
             if (m_b_Debug)
               console.log("[JS:APP] Got Ping, lets pong");
            Messaging_DoPong();
            b_Found = true;
         }


         if (!b_Found && m_b_Debug)
               console.log("[JS:APP] Unkown info requested..." +e.payload.toString());

      }
   });
   
   m_b_MessagingAvailable = true;
   network.SetMessaging(true);
   weather.SetMessaging(true);
   if (m_b_Debug)
         console.log("[JS:APP] Messaging init done...");
}

