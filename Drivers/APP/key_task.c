#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
#include "bsp_key.h"
#include "stdio.h"
#include "usart_task.h"
#include "iap_task.h"

osMessageQueueId_t keyEventQueueHandle;

osThreadId_t keyTaskHandle;
const osThreadAttr_t keyTask_attributes = {
    .name = "keyTask",
    .stack_size = 128 * 1,
    .priority = (osPriority_t)osPriorityNormal1,
};

void keyTask(void *argument)
{
    uint8_t key_val = 0;

    for (;;)
    {
        key_val = key_scan(0);
        if (key_val)
        {
            osMessageQueuePut(keyEventQueueHandle, &key_val, NULL, 1);
        }
        osDelay(30);
    }
}

osThreadId_t updateTaskHandle;
const osThreadAttr_t updateTask_attributes = {
    .name = "updateTask",
    .stack_size = 128 * 1,
    .priority = (osPriority_t)osPriorityNormal,
};
void updateTask(void *argument)
{
    uint8_t key_val = 0;
    for (;;)
    {
        if (osMessageQueueGet(keyEventQueueHandle, &key_val, NULL, 0) == osOK)
        {
            switch (key_val)
            {
            case KEY0_PRES:
                printf("key0 pressed\r\n");
                break;
            case KEY1_PRES:
                printf("key1 pressed\r\n");
                break;
            case KEY2_PRES:
                printf("key2 pressed\r\n");
                break;
            case WKUP_PRES:
//                printf("wkup pressed\r\n");
                osEventFlagsSet(usartEventFlagsHandle, IAP_EVENT_BIT_1);
                break;

            default:
                break;
            }
        }
        osDelay(1);
    }
}
