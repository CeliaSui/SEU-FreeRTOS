#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include "esp_log.h"

#define TASK_STACK_SIZE                 2048
#define NUM_TASKS                       5
#define TASK_PRIORITY                   3
#define TASK_MAIN_PRIORITY              5

#define TASK_RUNNING_TIME_MS            5000

static const char* TAG = "Mutex";

struct TaskParam
{
    SemaphoreHandle_t xSemaphore;
    int taskID;
};
typedef struct TaskParam t_TaskParam;

void vTask(void * param);
void UseResource(int id);

void app_main()
{
    TaskHandle_t TaskHandles[NUM_TASKS];

    vTaskPrioritySet(NULL, TASK_MAIN_PRIORITY);

	/* Create binary semaphore */
    /* Create a binary semaphore to control access to the shared resource */
    /* Create a mutex to serialize access to the shared resource */
    SemaphoreHandle_t xMutex = xSemaphoreCreateMutex();
    if (xMutex == NULL)
    {
        ESP_LOGE(TAG, "[app_main] Error creating binary semaphore.");
        exit(EXIT_FAILURE);
    }
    ESP_LOGI(TAG, "[app_main] Binary semaphore created.");    

    for (int i = 0; i < NUM_TASKS; i++)
    {
        t_TaskParam param;
        /* Assign the task ID and semaphore to the task parameter */
        param.taskID = i;
        param.xSemaphore = xMutex;
        
        xTaskCreate(vTask, "Task", TASK_STACK_SIZE, (void *)&param, TASK_PRIORITY, &TaskHandles[i]);
        ESP_LOGI(TAG, "[app_main] Task %d created.", i);
    }

    /*
    https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/system/freertos.html#semaphore-api 
    xSemaphoreCreateBinary() is created in a state such that the semaphore must first be ‘given’ before it can be ‘taken’.
    */
   /* Give the semaphore initially so that the first task can take it */
    /*For mutex not necessary to do this manually*/
   // xSemaphoreGive(xSemaphore);    
    
    /* Wait TASK_RUNNING_TIME_MS ms */
    ESP_LOGI(TAG, "[app_main] Entering blocked state...");
    vTaskDelay(TASK_RUNNING_TIME_MS / portTICK_PERIOD_MS);

    for (int i = 0; i < NUM_TASKS; i++)
    {
        if (TaskHandles[i] != NULL)
        {
            vTaskDelete(TaskHandles[i]);
            ESP_LOGI(TAG, "[app_main] Task %d deleted.", i);
        }
    }

    /* Delete the semaphore */
    if (xMutex != NULL)
    {
        vSemaphoreDelete(xMutex);
        ESP_LOGI(TAG, "[app_main] Binary semaphore deleted.");
    }
}

void vTask(void * param)
{
    t_TaskParam TaskData = *(t_TaskParam *)param;

    for (;;)
    {
        ESP_LOGI(TAG, "[vTask] Task %d attempts to use resource...", TaskData.taskID);
        /* Wait for the semaphore */
        /* Take the semaphore (block indefinitely until available) */
        if (xSemaphoreTake(TaskData.xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            UseResource(TaskData.taskID);
            /* Signal the semaphore */
            /* Give the semaphore back so another task can use the resource */
            xSemaphoreGive(TaskData.xSemaphore);
        }
        else
        {
            ESP_LOGI(TAG, "[vTask] Cannot take the semaphore.");
        }
    }
}

void UseResource(int id)
{
    int wait_ms = esp_random() % 500;
    ESP_LOGI(TAG, "[UseResource] Using resource: Task %d", id);
    vTaskDelay(wait_ms / portTICK_PERIOD_MS);
}