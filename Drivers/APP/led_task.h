#ifndef __LED_TASK_H
#define __LED_TASK_H
#include "cmsis_os2.h"

extern osThreadId_t ledTaskHandle;
extern const osThreadAttr_t ledTask_attributes;

void ledTask(void *argument);

#endif
