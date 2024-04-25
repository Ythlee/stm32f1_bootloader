#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
#include "bsp_led.h"
#include "stdio.h"
osThreadId_t ledTaskHandle;
const osThreadAttr_t ledTask_attributes = {
    .name = "ledTask",
    .stack_size = 128 * 1,
    .priority = (osPriority_t)osPriorityNormal,
};

void ledTask(void *argument)
{
    for (;;)
    {
        LED0_TOGGLE();
        osDelay(1000);
    }
}
