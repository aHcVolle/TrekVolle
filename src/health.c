#include "health.h"

TextLayer* Layer_Steps_Text;

void GetMovementData(void)
{
   HealthMetric stepcount = HealthMetricStepCount;
   HealthMetric distance = HealthMetricWalkedDistanceMeters;
   time_t start = time_start_of_today();
   time_t end = time(NULL);
   
   // Check the metric has data available for today
   HealthServiceAccessibilityMask masksteps = health_service_metric_accessible(stepcount,start, end);
   int steps = 0;
   if(masksteps & HealthServiceAccessibilityMaskAvailable) 
   {
       // Data is available!
      steps = (int)health_service_sum_today(stepcount);
   } 
   HealthServiceAccessibilityMask maskdist = health_service_metric_accessible(distance,start, end);
   int dist = 0;
   if(maskdist & HealthServiceAccessibilityMaskAvailable) 
   {
       // Data is available!
      dist = (int)health_service_sum_today(distance);
   } 
   
   static char s_buffer[30];
   snprintf(s_buffer,sizeof(s_buffer),"%d %dm",steps,dist);
   
   text_layer_set_text(Layer_Steps_Text, s_buffer);
}

static void health_handler(HealthEventType event, void *context) {
  // Which type of event occured?
  switch(event) {
    case HealthEventSignificantUpdate:
      //APP_LOG(APP_LOG_LEVEL_INFO,"New HealthService HealthEventSignificantUpdate event");
      break;
    case HealthEventMovementUpdate:
      GetMovementData();
      break;
    case HealthEventSleepUpdate:
      //APP_LOG(APP_LOG_LEVEL_INFO,"New HealthService HealthEventSleepUpdate event");
      break;
  }
}

void InitHealth()
{
   Layer_Steps_Text = GetStepTextLayer();
   // Health
   health_service_events_subscribe(health_handler, NULL);
   
   GetMovementData();
}

void DeInitHealth()
{
   health_service_events_unsubscribe();
}