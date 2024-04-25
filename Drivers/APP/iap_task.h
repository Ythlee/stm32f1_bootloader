#ifndef __IAP_TASK_H__
#define __IAP_TASK_H__
#include "cmsis_os2.h"

#define IAP_EVENT_BIT_1 (1 << 1)

extern osThreadId_t iapTaskHandle;
extern const osThreadAttr_t iapTask_attributes;

void iapTask(void *argument);
#endif
