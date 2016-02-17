function Network_SendReply(b_IsConnected)
{
   if (m_b_MessagingAvailable)
   {
      // Debug printout
      if (m_b_Debug)
      {
         if (b_IsConnected)
            console.log("[JS:NET] Network check: OK");
         else
            console.log("[JS:NET] Network check: Failed");
      }   
      // Send message to pebble
      var dictionary ={'KEY_ONLINE': b_IsConnected ? 1 : 0};
   	Pebble.sendAppMessage(dictionary,
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:NET] Sent message with ID " + e.data.transactionId);
            },
            function(e)
            {
               if (m_b_Debug)
                  console.log("[JS:NET] Could not send message with ID " + e.data.transactionId + " Error is: " + e.error.message);
            });  
   }
}


function Network_GetData()
{
   if (m_b_Debug)
         console.log("[JS:NET] Getting network data");
   
   // The easy way does not seem to work...
   //Network_SendReply(navigator.onLine);
   
   // Lets request a webpage.... 
   var url = 'https://rawgit.com/aHcVolle/TrekVolle/master/online.html';
   xhrRequest(url, 'GET', function(responseText) {Network_SendReply(true); });
   
}