#ifndef __KEY_TASK_H
#define __KEY_TASK_H

#include "cmsis_os2.h"

extern osMessageQueueId_t keyEventQueueHandle;

extern osThreadId_t keyTaskHandle;
extern const osThreadAttr_t keyTask_attributes;

extern osThreadId_t updateTaskHandle;
extern const osThreadAttr_t updateTask_attributes;

void keyTask(void *argument);
void updateTask(void *argument);

#endif
