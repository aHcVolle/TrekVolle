var m_Battery;
var m_b_Battery_Availiable;

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



function Battery_InitSuccess(batteryManager) 
{
   // Assign batteryManager to globally 
   //   available `battery` variable.
   m_Battery = batteryManager;
   m_b_Battery_Availiable = true;
   Battery_GetData();
}

function Battery_InitFailure()
{
   m_b_Battery_Availiable = false;
}

function Battery_Init()
{
   if("getBattery" in navigator) 
   {
      // Request battery manager object.
      navigator.getBattery().then(Battery_InitSuccess, Battery_InitFailure);
   } 
   else 
   {
      // API is not supported, fail gracefully.
      console.log("Battery API not supported!");
   }
}

function Battery_GetData()
{   
   //console.log("Getting battery info...");
   //navigator.getBattery().level;
   if (m_b_Battery_Availiable && m_b_MessagingAvailiable)
   {
      var charging = 0;
      if (m_Battery.charging)
         charging = 1;
      var dictionary = 
             {
                'KEY_BATTERY_CHARGE': m_Battery.level * 100,
                'KEY_BATTERY_STATE': charging
             };
      
      // Send to Pebble
      Pebble.sendAppMessage(dictionary,function(e){},function(e){});
   }
}