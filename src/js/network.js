var m_b_LastOnlineCheck = false;

function Network_GetData()
{
   if (m_b_Debug)
         console.log("[JS:NET] Getting network data");
   
   if (m_b_LastOnlineCheck === false)
   {
      var dictionary ={'KEY_ONLINE': 0};
	  Pebble.sendAppMessage(dictionary,function(e){},function(e){});
   }
   m_b_LastOnlineCheck = false;
   // Construct URL
   var url = 'https://rawgit.com/aHcVolle/TrekVolle/master/online.html';
   
  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', 
    function(responseText) 
      {
          m_b_LastOnlineCheck = true;
          //console.log('Got an online reply!');
          var dictionary ={'KEY_ONLINE': 1};
		  Pebble.sendAppMessage(dictionary,function(e){},function(e){});
    });
   
}
