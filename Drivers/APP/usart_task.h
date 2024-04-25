#ifndef __USART_TASK_H__
#define __USART_TASK_H__

#include "cmsis_os2.h"

#define USART_EVENT_BIT_0 (1 << 0)

extern uint32_t addr;

extern osSemaphoreId_t usartSemaphoreHandle;
extern osSemaphoreAttr_t usartSemaphore_attributes;

extern osEventFlagsId_t usartEventFlagsHandle;
extern osEventFlagsAttr_t usartEventFlags_attributes;

extern osThreadId_t usartTaskHandle;
extern const osThreadAttr_t usartTask_attributes;
void usartTask(void *argument);

#endif // __USART_TASK_H__
