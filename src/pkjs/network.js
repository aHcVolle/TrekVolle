var m_b_Debug = false;
var m_b_MessagingAvailable = false; 

function SetDebug(b_Debug)
{
   m_b_Debug = b_Debug;
}

function SetMessaging(b_MessagingAvailable)
{
   m_b_MessagingAvailable = b_MessagingAvailable;
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
     SendReply(false);
  }; 
  xhr.onerror = function () 
  { 
     if (m_b_Debug)
         console.log("[JS:APP] Request failed...");   
     SendReply(false); 
  };  
  xhr.open(type, url);
  xhr.send();
   
};

function SendReply(b_IsConnected,m_b_Debug)
{
   if ((typeof m_b_MessagingAvailable === "undefined") || (m_b_MessagingAvailable === false))
   {
      if (m_b_Debug)
         console.log("[JS:NET] Messaging is not yet initialized!");
      return;
   } 
   

   // Debug printout
   if (m_b_Debug)
   {
      if (b_IsConnected)
         console.log("[JS:NET] Network check: OK");
      else
         console.log("[JS:NET] Network check: Failed");
   }   
   // Send message to pebble
   var dictionary ={'NETWORK_STATUS': b_IsConnected ? 1 : 0};
   Pebble.sendAppMessage(dictionary,
                         function(e)
                         {
                            if (m_b_Debug)
                               console.log("[JS:NET] Sent message with ID " + e.data.transactionId);
                         },
                         function(e)
                         {
                            if (m_b_Debug)
                               console.log("[JS:NET] Could not send message with ID " + e.data.transactionId + " Error is: " + e.error);
                         });  
   
}


function GetData(m_b_Debug)
{
   if ((typeof m_b_MessagingAvailable === "undefined") || (m_b_MessagingAvailable === false))
   {
      if (m_b_Debug)
         console.log("[JS:NET] Messaging is not yet initialized!");
      return;
   }    
   
   if (m_b_Debug)
         console.log("[JS:NET] Getting network data");
   
   // The easy way does not seem to work...
   //Network_SendReply(navigator.onLine);
   
   // Lets request a webpage.... 
   var url = 'https://rawgit.com/aHcVolle/TrekVolle/master/online.html';
   xhrRequest(url, 'GET', function(responseText) {SendReply(true); });
   
}


module.exports.SetDebug = SetDebug;
module.exports.SetMessaging = SetMessaging;
module.exports.GetData = GetData;
module.exports.SendReply = SendReply;
