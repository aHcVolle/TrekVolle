
var Clay = require('pebble-clay');
var clayConfig = require('./configuration_menu.js');
var messageKeys = require('message_keys');
var weather = require('./weather');
//var clayConfigAplite = require('./clayconfig.js');
var clay = new Clay(clayConfig, null, { autoHandleEvents: false });

var m_b_Debug;

function Init(b_Debug)
{
   m_b_Debug = b_Debug;
   
   if (m_b_Debug)
         console.log("[JS:CLAY] Init...");
}

Pebble.addEventListener('showConfiguration', function(e) {

  // This is an example of how you might load a different config based on platform.
  /*var platform = clay.meta.activeWatchInfo.platform || 'aplite';
  if (platform === 'aplite') {
    clay.config = clayConfig;//clayConfigAplite;
  }
*/
  Pebble.openURL(clay.generateUrl());
});


Pebble.addEventListener('webviewclosed', function(e) {
  if (e && !e.response) {
    return;
  }

  // Get the keys and values from each config item
  var dict = clay.getSettings(e.response);
  
  var Location = dict[messageKeys.WEATHER_LOCATION];
  if(typeof Location !== "undefined")
  { 
      weather.SaveData(Location);
      weather.LoadData();
      weather.GetData();
  }
   
   
   
  // Send settings values to watch side
  Pebble.sendAppMessage(dict, function(e) 
   {
    if (m_b_Debug)
         console.log("[JS:CLAY] Sending Data...");
  }, function(e) 
   {
    if (m_b_Debug)
         console.log("[JS:CLAY] Error sending data...");
    console.log(JSON.stringify(e));
  });
});


module.exports.Init = Init;
