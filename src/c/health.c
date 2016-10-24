#include "health.h"

// Layer to display the health info
TextLayer* m_Health_Movement_Text_Layer;
TextLayer* m_Health_Heart_Text_Layer;
#if defined(PBL_HEALTH)

// Get the data from the health service
void Health_GetMovementData(void)
{
   // Debug printout
   #ifdef DEBUG_HEALTH
         printf("[HEALTH][Health_GetData] Getting movement data");
   #endif
   
   // Get the step count and distance
   HealthMetric Step_Metric_Count = HealthMetricStepCount;
   HealthMetric Step_Metric_Distance = HealthMetricWalkedDistanceMeters;
   // Specify "today"
   time_t Step_Start = time_start_of_today();
   time_t Step_End = time(NULL);
   
   // Check if the metric has data available for today
   HealthServiceAccessibilityMask Step_Metric_Count_Mask = health_service_metric_accessible(Step_Metric_Count,Step_Start, Step_End);
   int Step_Count = 0;
   if(Step_Metric_Count_Mask & HealthServiceAccessibilityMaskAvailable) 
   {
       // Data is available, save it!
      Step_Count = (int)health_service_sum_today(Step_Metric_Count);
   } 
   // Filter data that is not from today
   HealthServiceAccessibilityMask Step_Metric_Distance_Mask = health_service_metric_accessible(Step_Metric_Distance,Step_Start, Step_End);
   int Step_Distance = 0;
   if(Step_Metric_Distance_Mask & HealthServiceAccessibilityMaskAvailable) 
   {
       // Data is available, save it!
      Step_Distance = (int)health_service_sum_today(Step_Metric_Distance);
   } 
   
   #ifdef DEBUG_STEPCOUNT
      Step_Count = 2030;
      Step_Distance = 2087;
   #endif
   
   // Buffer to store the health information
   static char s_HealthText[20];
   static char s_StepCountText[10];
   static char s_StepDistanceText[10];
   
   if (Step_Count > 100000)
   {
      int Step_Count_K = Step_Count / 1000;
      snprintf(s_StepCountText,sizeof(s_StepCountText),"%dk",Step_Count_K);
   }
   else if (Step_Count > 10000)
   {
      int Step_Count_K = Step_Count / 1000;
      int Step_Count_H = (Step_Count - (Step_Count_K * 1000)) / 100;
      snprintf(s_StepCountText,sizeof(s_StepCountText),"%d.%01dk",Step_Count_K,Step_Count_H);
   }
   else if (Step_Count > 1000)
   {
      int Step_Count_K = Step_Count / 1000;
      int Step_Count_H = (Step_Count - (Step_Count_K * 1000) ) / 10;
      
      snprintf(s_StepCountText,sizeof(s_StepCountText),"%d.%02dk",Step_Count_K,Step_Count_H);
   }
   else
   {
      snprintf(s_StepCountText,sizeof(s_StepCountText),"%d",Step_Count);
   }
   
   if (Step_Distance > 100000)
   {
      int Step_Distance_K = Step_Distance / 1000;
      snprintf(s_StepDistanceText,sizeof(s_StepDistanceText),"%dkm",Step_Distance_K);
   }
   else if (Step_Distance > 10000)
   {
      int Step_Distance_K = Step_Distance / 1000;
      int Step_Distance_H = (Step_Distance - (Step_Distance_K * 1000)) / 100;
      snprintf(s_StepDistanceText,sizeof(s_StepDistanceText),"%d.%01dkm",Step_Distance_K,Step_Distance_H);
   }
   else if (Step_Distance > 1000)
   {
      int Step_Distance_K = Step_Distance / 1000;
      int Step_Distance_H = (Step_Distance - (Step_Distance_K * 1000)) / 10;
      
      snprintf(s_StepDistanceText,sizeof(s_StepDistanceText),"%d.%02dkm",Step_Distance_K,Step_Distance_H);
   }
   else
   {
      snprintf(s_StepDistanceText,sizeof(s_StepDistanceText),"%dm",Step_Distance);
   }
   
   snprintf(s_HealthText,sizeof(s_HealthText),"%s %s",s_StepCountText,s_StepDistanceText);
   
   
   // And display the data
   text_layer_set_text(m_Health_Movement_Text_Layer, s_HealthText);
}

void Health_GetHeartRateData(void)
{
   #if defined(HAS_HEARTRATE)
   // Debug printout
   #ifdef DEBUG_HEALTH
         printf("[HEALTH][Health_GetData] Getting heartrate data");
   #endif
   
   int Heartrate = 0;
   
   HealthServiceAccessibilityMask hr = health_service_metric_accessible(HealthMetricHeartRateBPM, time_start_of_today(), time(NULL));
   if (hr & HealthServiceAccessibilityMaskAvailable) 
   {
      HealthValue val = health_service_peek_current_value(HealthMetricHeartRateBPM);
      Heartrate = (int)val;
   }
   
   #ifdef DEBUG_HEARTRATE
      Heartrate = 222;
   #endif
   
   if (Heartrate > 0) 
      show_HeartRate(true);
      
      
   // Buffer to store the heart information
   static char s_HeartText[30];
   snprintf(s_HeartText,sizeof(s_HeartText),"%d",Heartrate);
   
   // And display the data
   text_layer_set_text(m_Health_Heart_Text_Layer, s_HeartText);
   #endif
}

/*
// This will get called if there is new health data
static void Health_Handler(HealthEventType event, void *context) 
{
  // Which type of event occured?
  switch(event) {
    case HealthEventSignificantUpdate:
      // We don't use this
      break;
    case HealthEventMovementUpdate:
      // Debug printout
      #ifdef DEBUG_HEALTH
         printf("[HEALTH][Health_Handler] Movement");
     #endif
      // Request the new data
      Health_GetMovementData();
      break;
    case HealthEventSleepUpdate:
      // We don't use this
      break;
    case HealthEventMetricAlert:
      // we don't use this;
    case HealthEventHeartRateUpdate:
     // https://developer.pebble.com/docs/c/preview/Foundation/Event_Service/HealthService/
      #ifdef DEBUG_HEALTH
         printf("[HEALTH][Health_Handler] Heartrate");
      #endif
      Health_GetHeartRateData();
      break;
  }
}
*/
#endif

// Init the vars and register with the health service
void Health_Init()
{
   #if defined(PBL_HEALTH)
   // Debug printout
   #ifdef DEBUG_HEALTH
         printf("[HEALTH][Health_Init] Init");
   #endif
   
   // Get the layers
   m_Health_Movement_Text_Layer = GetStepTextLayer();
   #if defined(HAS_HEARTRATE)
   m_Health_Heart_Text_Layer = GetHeartTextLayer();
   #endif

   // Hide the heartrate layer
   show_HeartRate(false);
   
   #endif
   
   
}

// Unregister from the service
void Health_DeInit()
{
   #if defined(PBL_HEALTH)
   // Debug printout
   #ifdef DEBUG_HEALTH
         printf("[HEALTH][Health_DeInit] Deinit");
   #endif
   // Unregister from the health service
   health_service_events_unsubscribe();
   #endif
}