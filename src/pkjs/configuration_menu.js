module.exports = [
  {
    "type": "heading",
    "defaultValue": "TrekVolle Configuration"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Colors"
      },
      {
        "type": "color",
        "messageKey": "COLOR_BACKGROUND",
        "defaultValue": "0x0055FF",
        "label": "Background Color"
      },
      {
        "type": "color",
        "messageKey": "COLOR_TEXT",
        "defaultValue": "0xFF5555",
        "label": "Text Color"
      },
      {
        "type": "color",
        "messageKey": "COLOR_IMAGE",
        "defaultValue": "0xFF5555",
        "label": "Image Color"
      },
      {
        "type": "color",
        "messageKey": "COLOR_WINDOW",
        "defaultValue": "0x000000",
        "label": "Window Color"
      },
      {
        "type": "color",
        "messageKey": "COLOR_CHARGING",
        "defaultValue": "0x00FF00",
        "label": "Charging Color"
      },
      {
        "type": "color",
        "messageKey": "COLOR_ERROR",
        "defaultValue": "0xFF0000",
        "label": "Error Color"
      },
      {
        "type": "color",
        "messageKey": "COLOR_BATTERYLOW",
        "defaultValue": "0xFF0000",
        "label": "Battery low Color"
      },
      {
        "type": "color",
        "messageKey": "COLOR_CLOCK_HOUR",
        "defaultValue": "0xFF5555",
        "label": "Clock hour Color"
      },
      {
        "type": "color",
        "messageKey": "COLOR_CLOCK_MIN",
        "defaultValue": "0xFF5555",
        "label": "Clock minute Color"
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Weather"
      },
      {
        "type": "toggle",
        "messageKey": "WEATHER_TEMPERATURECELCIUS",
        "label": "Temperature in Celcius",
        "description": "Fahrenheit if disabled.",
        "defaultValue": true
      },
      {
        "type": "toggle",
        "messageKey": "WEATHER_RETRYUPDATE",
        "label": "Retry weather update",
        "description": "if the last update failed.",
        "defaultValue": true
      },
      {
        "type": "slider",
        "messageKey": "WEATHER_REFRESHTIME",
        "defaultValue": 60,
        "label": "Weather refresh time",
        "description": "Time in minutes between weather requests.",
        "min": 1,
        "max": 99,
        "step": 1
      },
      {
        "type": "radiogroup",
        "messageKey": "WEATHER_PROVIDER",
        "label": "Weather provider",
        "defaultValue": "0",
        "options": [
          { 
            "label": "OpenWeatherMap", 
            "value": "0" 
          },
          { 
            "label": "Yahoo", 
            "value": "1" 
          },
          { 
            "label": "WeatherUnderground", 
            "value": "2" 
          },
          { 
            "label": "DarkSky", 
            "value": "3" 
          }
             
          ]
      },
      {
        "type": "input",
        "messageKey": "WEATHER_API_KEY",
        "description": "Enter your API key, leave blank to use the builtin.",
        "label": "Weather API key"
      },
      {
        "type": "input",
        "messageKey": "WEATHER_LOCATION",
        "description": "Enter your city, cityID, leave empty for geolocation.",
        "label": "Weather Location"
      },
      {
        "type": "toggle",
        "messageKey": "ACCELERATION_ENABLE",
        "label": "Switch between condition and location",
        "description": "when shaking your pebble.",
        "defaultValue": true
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Clock"
      },
      {
        "type": "radiogroup",
        "messageKey": "CLOCK_DATESTYLE",
        "label": "Date style",
        "defaultValue": "0",
        "options": [
          { 
            "label": "DD.MM.YY", 
            "value": "0" 
          },
          { 
            "label": "YY-MM-DD", 
            "value": "1" 
          },
          { 
            "label": "MM/DD/YY", 
            "value": "2" 
          }
             
          ]
      },
      {
        "type": "radiogroup",
        "messageKey": "CLOCK_DAYOFYEAR",
        "label": "Day of year style",
        "defaultValue": "0",
        "options": [
          { 
            "label": "Day of year", 
            "value": "0" 
          },
          { 
            "label": "Temperature minimum/maximum", 
            "value": "1" 
          }         
          ]
      },
      {
        "type": "toggle",
        "messageKey": "CLOCK_SLEEP",
        "label": "Sleep mode",
        "description": "If enabled, the watchapp will not virate during the set time.",
        "defaultValue": true
      },
      {
        "type": "input",
        "messageKey": "CLOCK_SLEEP_BEGIN",
        "description": "Enter the time the sleep time should begin.",
        "label": "Sleep begin",
        "attributes": {
            "placeholder": "00:00",
             "type": "time"
           }
      },
      {
        "type": "input",
        "messageKey": "CLOCK_SLEEP_END",
        "description": "Enter the time the sleep time should end.",
        "label": "Sleep end",
         "attributes": {
            "placeholder": "07:00",
             "type": "time"
           }
      }
   ]
      
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Connection"
      },
      {
        "type": "toggle",
        "messageKey": "NETWORK_VIBRATIONENABLED",
        "label": "Network vibrations",
        "description": "Vibrate on internet (dis)connect.",
        "defaultValue": true
      },
      {
        "type": "toggle",
        "messageKey": "BLUETOOTH_VIBRATIONENABLED",
        "label": "Bluetooth vibrations",
        "description": "Vibrate on bluetooth (dis)connect.",
        "defaultValue": true
      },
      {
        "type": "slider",
        "messageKey": "NETWORK_REFRESHTIME",
        "defaultValue": 60,
        "label": "Network refresh time",
        "description": "Time in minutes between network checks.",
        "min": 1,
        "max": 99,
        "step": 1
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Miscellaneous"
      },
      {
        "type": "slider",
        "messageKey": "BATTERY_SAVING_LEVEL",
        "defaultValue": 20,
        "label": "Battery saving level",
        "description": "Pebble battery level when battery saving should be active.",
        "min": 0,
        "max": 100,
        "step": 10
      },
      {
        "type": "slider",
        "messageKey": "SPORT_STEP_THRESHOLD",
        "defaultValue": 60,
        "label": "Minimum steps/minute",
        "description": "Minimum steps/minute for the sports tracker to activate.",
        "min": 0,
        "max": 200,
        "step": 1
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];
