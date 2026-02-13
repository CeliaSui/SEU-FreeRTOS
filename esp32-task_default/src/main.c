#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define BUFF_SIZE   2048

void app_main() 
{  
  char bufferStats[BUFF_SIZE];

  /* Retrieve task statistics */
  vTaskGetRunTimeStats(bufferStats);

  /* Display task statistics */
  printf("\nTask\t\tCycles\t\tCPU usage\n");
  printf("-----------------------------------------\n");
  printf("%s\n", bufferStats);  
}