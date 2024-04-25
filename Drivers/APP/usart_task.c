#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
#include "usart.h"
#include "usart_task.h"
#include "string.h"
#include "stdio.h"
#include "bsp_norflash.h"
#include "iap_task.h"
#include "dev_uart.h"

osSemaphoreId_t usartSemaphoreHandle;
osSemaphoreAttr_t usartSemaphore_attributes = {
    .name = "usartSemaphore"};

osEventFlagsId_t usartEventFlagsHandle;
osEventFlagsAttr_t usartEventFlags_attributes = {
    .name = "usartEventFlags"};

osThreadId_t usartTaskHandle;
const osThreadAttr_t usartTask_attributes = {
    .name = "usartTask",
    .stack_size = 128 * 10,
    .priority = (osPriority_t)osPriorityNormal,
};

static uint16_t size = 0;
static uint8_t buf[1024];
uint32_t addr = 0;
void usartTask(void *argument)
{
    uint32_t flags;

    for (;;)
    {
        flags = osEventFlagsWait(usartEventFlagsHandle, USART_EVENT_BIT_0, osFlagsWaitAny, 0);
        if ((flags & USART_EVENT_BIT_0) == USART_EVENT_BIT_0)
        {

						size = uart_read(DEV_UART1, buf, 1024);
						uart_write(DEV_UART1, buf, size);
						W25QXX_Write(buf, addr, size);
						addr += size;
//			/* 将fifo数据拷贝到dma buf，并启动dma传输 */
//						uart_poll_dma_tx(DEV_UART1); 
            // if (osSemaphoreAcquire(usartSemaphoreHandle, 0) == osOK)
            // {
//                memset(buf, 0, sizeof(buf));
//                ringbuff_read(&ring_buff, buf, recvlen);
//                // W25QXX_Write(buf, addr, recvlen);
//                // addr += recvlen;
//                printf("%s", buf);
            // }
            // osSemaphoreRelease(usartSemaphoreHandle);
        }
        // else if((flags & IAP_EVENT_BIT_1) == IAP_EVENT_BIT_1)
        // {
        //     ringbuff_clear(&ring_buff);
        //     memset(buf, 0, sizeof(buf));
        //     ringbuff_read(&ring_buff, buf, recvlen);
        //     W25QXX_Write(buf, 0, recvlen);
        // }
        osDelay(10);
    }
}
