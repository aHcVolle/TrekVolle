
// This will hold the battery manager object
var m_Battery;
// Simple var to save if the battery manager is available
var m_b_Battery_Available;



function Battery_GetData()
{   
   if (m_b_Battery_Available && m_b_MessagingAvailable)
   {
      if (m_b_Debug)
         console.log("[JS:BATT] Getting battery data");
      
      var charging = 0;
      if (m_Battery.charging)
         charging = 1;
      var dictionary = 
             {
                'KEY_BATTERY_CHARGE': m_Battery.level * 100,
                'KEY_BATTERY_STATE': charging
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
                  console.log("[JS:BATT] Could not send message with ID " + e.data.transactionId + " Error is: " + e.error.message);
            });
   }
}






function Battery_InitSuccess(batteryManager) 
{
   // Assign batteryManager to globally 
   //   available `battery` variable.
   if (m_b_Debug)
         console.log("[JS:BATT] Init OK");
   m_Battery = batteryManager;
   m_b_Battery_Available = true;
   Battery_GetData();
}

function Battery_InitFailure()
{
   if (m_b_Debug)
         console.log("[JS:BATT] Init failed");
   m_b_Battery_Available = false;
}

function Battery_Init()
{
   if (m_b_Debug)
         console.log("[JS:BATT] Init...");
   if("getBattery" in navigator) 
   {
      // Request battery manager object.
      
      navigator.getBattery().then(function(battery) 
      {
        battery.addEventListener('chargingchange', function(){ updateChargeInfo();});
        function updateChargeInfo(){Battery_GetData();}
      
        battery.addEventListener('levelchange', function(){updateLevelInfo();});
        function updateLevelInfo(){Battery_GetData();}
      
        battery.addEventListener('chargingtimechange', function(){updateChargingInfo();});
        function updateChargingInfo(){Battery_GetData();}
      
        battery.addEventListener('dischargingtimechange', function(){updateDischargingInfo();});
        function updateDischargingInfo(){ Battery_GetData();} 
      });
      
      navigator.getBattery().then(Battery_InitSuccess, Battery_InitFailure);
   } 
   else 
   {
      // API is not supported, fail gracefully.
      console.log("[JS:BATT] Battery API not supported!");
   }
}

function Battery_GetData()
{   
   if (m_b_Battery_Available && m_b_MessagingAvailable)
   {
      if (m_b_Debug)
         console.log("[JS:BATT] Getting battery data");
      
      var i_charging = m_Battery.charging ? 1 : 0;

      var dictionary = 
             {
                'KEY_BATTERY_CHARGE': m_Battery.level * 100,
                'KEY_BATTERY_STATE': i_charging
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
                  console.log("[JS:BATT] Could not send message with ID " + e.data.transactionId + " Error is: " + e.error.message);
            });
   }
}

