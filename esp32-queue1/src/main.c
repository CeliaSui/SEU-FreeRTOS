#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "esp_log.h"

#define TASK_STACK_SIZE                 2048
#define TASK_ACQ_PRIORITY               5
#define TASK_DISP_PRIORITY              3

#define TEMPERATURE_QUEUE_LENGTH        10
#define TEMPERATURE_ACQ_RATE_MS         1000

static const char* TAG = "TempQueue";

void TemperatureAcquisition(void * queue);
void TemperatureDisplay(void * queue);

void app_main()
{
    QueueHandle_t xTempQueue = NULL;
    TaskHandle_t xHandleAcq = NULL;
    TaskHandle_t xHandleDisp = NULL;    
    
    xTempQueue = xQueueCreate(...);
    if (xTempQueue == NULL)
    {
        ESP_LOGE(TAG, "Error creating queue. Restarting...");
        exit(EXIT_FAILURE);                
    }

    xTaskCreate(...);
    configASSERT( xHandleAcq );
    ESP_LOGI(TAG, "[app_main] Task_Acq created.");

    xTaskCreate(...);
    configASSERT( xHandleDisp );
    ESP_LOGI(TAG, "[app_main] Task_Disp created.");

    /* Enter suspend state forever */
    vTaskSuspend(NULL);

    if (xHandleAcq != NULL)
    {
        vTaskDelete(xHandleAcq);
    }

    if (xHandleDisp != NULL)
    {
        vTaskDelete(xHandleDisp);
    }
}

void TemperatureAcquisition(void * queue)
{
    TickType_t xLastWakeTime;

    QueueHandle_t xQueue = ...;

    for (;;)
    {
        xLastWakeTime = xTaskGetTickCount();

        /* Simulate temperature reading. Any vaule in the range [1-30] */
        int temp_reading = esp_random() % 30 + 1;

        xQueueSendToBack(...);

        vTaskDelayUntil(&xLastWakeTime, TEMPERATURE_ACQ_RATE_MS / portTICK_PERIOD_MS);
    }
}

void TemperatureDisplay(void * queue)
{
    QueueHandle_t xQueue = ...;

    for (;;)
    {
        int received;

        BaseType_t xStatus = xQueueReceive(...);
        if (xStatus == pdPASS)
        {
            printf("Temperature measurement: %d°C\n", received);
        }
        else
        {
            ESP_LOGW(TAG, "Could not receive from the queue.");
        }
    }
}