#include "health.h"

// Layer to display the health info
TextLayer* m_Health_Text_Layer;

// Get the data from the health service
void Health_GetMovementData(void)
{
   // Debug printout
   if (m_b_Debug)
         printf("[HEALTH] Getting data");
   
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
   
   // Buffer to store the health information
   static char s_HealthText[30];
   snprintf(s_HealthText,sizeof(s_HealthText),"%d %dm",Step_Count,Step_Distance);
   
   // And display the data
   text_layer_set_text(m_Health_Text_Layer, s_HealthText);
}

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
      if (m_b_Debug)
         printf("[HEALTH] Handler");
      // Request the new data
      Health_GetMovementData();
      break;
    case HealthEventSleepUpdate:
      // We don't use this
      break;
  }
}

// Init the vars and register with the health service
void Health_Init()
{
   // Debug printout
   if (m_b_Debug)
         printf("[HEALTH] Init");
   
   // Get the layer
   m_Health_Text_Layer = GetStepTextLayer();
   
   // Register with the service
   health_service_events_subscribe(Health_Handler, NULL);
   // Get the initial data
   Health_GetMovementData();
}

// Unregister from the service
void Health_DeInit()
{
   // Debug printout
   if (m_b_Debug)
         printf("[HEALTH] Deinit");
   // Unregister from the health service
   health_service_events_unsubscribe();
}