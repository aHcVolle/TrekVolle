
// This will hold the battery manager object
var m_Battery;
// Simple var to save if the battery manager is available
var m_b_Battery_Available;
// Store the battery init status
var m_b_Battery_IsInit;

// debugging
var m_b_Debug;

function GetData()
{   
   // Did we init yet?
   if ((typeof m_b_Battery_IsInit === "undefined") || (m_b_Battery_IsInit === false))
   {
      if (m_b_Debug)
         console.log("[JS:BATT] Battery is not yet initialized!");
      return;
   }
   
   if (!m_b_Battery_Available)
      return;
   
   if (m_b_Debug)
         console.log("[JS:BATT] Getting battery data");
   
   
   

      
   var dictionary = 
       {
          'BATTERY_CHARGE': m_Battery.level * 100,
          'BATTERY_STATE': m_Battery.charging ? 1 : 0
       };

   // Send to Pebble
   Pebble.sendAppMessage(dictionary,
                         function(e)
                         {
                            if (m_b_Debug)
                               console.log("[JS:BATT] Sent message with ID " + e.data.transactionId);
                         },
                         function(e)
                         {
                            if (m_b_Debug)
                               console.log("[JS:BATT] Could not send message with ID " + e.data.transactionId + " Error is: " + e.error);
                         });
   
}

function InitSuccess(batteryManager) 
{
   // Assign batteryManager to globally 
   //   available `battery` variable.
   if (m_b_Debug)
         console.log("[JS:BATT] Init OK");
   m_Battery = batteryManager;
   m_b_Battery_Available = true;

}

function InitFailure()
{
   if (m_b_Debug)
         console.log("[JS:BATT] Init failed");
}

function Init(b_Debug)
{
   m_b_Debug = b_Debug;
   
   if (m_b_Debug)
         console.log("[JS:BATT] Init...");
   
   m_b_Battery_Available = false;
   
   
   if("getBattery" in navigator) 
   {
      // Request battery manager object.
      
      navigator.getBattery().then(function(battery) 
      {
        battery.addEventListener('chargingchange', function(){ updateChargeInfo();});
        function updateChargeInfo(){GetData();}
      
        battery.addEventListener('levelchange', function(){updateLevelInfo();});
        function updateLevelInfo(){GetData();}
      
        battery.addEventListener('chargingtimechange', function(){updateChargingInfo();});
        function updateChargingInfo(){GetData();}
      
        battery.addEventListener('dischargingtimechange', function(){updateDischargingInfo();});
        function updateDischargingInfo(){ GetData();} 
      });
      
      navigator.getBattery().then(InitSuccess, InitFailure);
   } 
   else 
   {
      // API is not supported, fail gracefully.
      if (m_b_Debug)
         console.log("[JS:BATT] Battery API not supported!");
   }
   
   m_b_Battery_IsInit = true;
   
}

module.exports.Init = Init;
module.exports.GetData = GetData;

