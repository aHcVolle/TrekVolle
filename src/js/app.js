var m_b_MessagingAvailable;
var m_b_Debug;

   
   

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


// Listen for when the watchface is opened
Pebble.addEventListener('ready', function(e) 
{
   m_b_Debug = false;   
   
   if (m_b_Debug)
         console.log("[JS:APP] JS ready...");
   
   // Init the messaging
   Messaging_Init();

   // Init the battery service
   Battery_Init();
   
   // Init the weather
   Weather_Init();

   // DoPong
   Messaging_DoPong()
   
});


function Messaging_DoPong()
{
   if ((typeof m_b_MessagingAvailable === "undefined") || (m_b_MessagingAvailable === false))
   {
      if (m_b_Debug)
         console.log("[JS:APP] Messaging is not yet initialized!");
      return;
   } 
   var dictionary ={'KEY_PINGPONG': 1};
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
         if ('KEY_TEMPERATURE' in e.payload)
         {
            if (m_b_Debug)
               console.log("[JS:APP] Weather info requested...");
            Weather_GetData();
            b_Found = true;
         }
         if ('KEY_ONLINE' in e.payload)
         {
            if (m_b_Debug)
               console.log("[JS:APP] Online info requested...");
            Network_GetData();
            b_Found = true;
         }
         if ('KEY_BATTERY_CHARGE' in e.payload)
         {
            if (m_b_Debug)
               console.log("[JS:APP] Battery info requested...");
            Battery_GetData();
            b_Found = true;
         }
         if ('KEY_PINGPONG' in e.payload)
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
   
}



