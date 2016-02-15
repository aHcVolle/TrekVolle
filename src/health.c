#include "health.h"

TextLayer* m_Health_Text_Layer;

void Health_GetMovementData(void)
{
   if (m_b_Debug)
         printf("[HEALTH] Getting data");
   
   HealthMetric Step_Metric_Count = HealthMetricStepCount;
   HealthMetric Step_Metric_Distance = HealthMetricWalkedDistanceMeters;
   time_t Step_Start = time_start_of_today();
   time_t Step_End = time(NULL);
   
   // Check the metric has data available for today
   HealthServiceAccessibilityMask Step_Metric_Count_Mask = health_service_metric_accessible(Step_Metric_Count,Step_Start, Step_End);
   int Step_Count = 0;
   if(Step_Metric_Count_Mask & HealthServiceAccessibilityMaskAvailable) 
   {
       // Data is available!
      Step_Count = (int)health_service_sum_today(Step_Metric_Count);
   } 
   HealthServiceAccessibilityMask Step_Metric_Distance_Mask = health_service_metric_accessible(Step_Metric_Distance,Step_Start, Step_End);
   int Step_Distance = 0;
   if(Step_Metric_Distance_Mask & HealthServiceAccessibilityMaskAvailable) 
   {
       // Data is available!
      Step_Distance = (int)health_service_sum_today(Step_Metric_Distance);
   } 
   
   static char s_HealthText[30];
   snprintf(s_HealthText,sizeof(s_HealthText),"%d %dm",Step_Count,Step_Distance);
   
   text_layer_set_text(m_Health_Text_Layer, s_HealthText);
}

static void Health_Handler(HealthEventType event, void *context) 
{
  // Which type of event occured?
  switch(event) {
    case HealthEventSignificantUpdate:
      //APP_LOG(APP_LOG_LEVEL_INFO,"New HealthService HealthEventSignificantUpdate event");
      break;
    case HealthEventMovementUpdate:
      if (m_b_Debug)
         printf("[HEALTH] Handler");
      Health_GetMovementData();
      break;
    case HealthEventSleepUpdate:
      //APP_LOG(APP_LOG_LEVEL_INFO,"New HealthService HealthEventSleepUpdate event");
      break;
  }
}

void Health_Init()
{
   if (m_b_Debug)
         printf("[HEALTH] Init");
   m_Health_Text_Layer = GetStepTextLayer();
   
   health_service_events_subscribe(Health_Handler, NULL);
   Health_GetMovementData();
}

void Health_DeInit()
{
   if (m_b_Debug)
         printf("[HEALTH] Deinit");
   health_service_events_unsubscribe();
}