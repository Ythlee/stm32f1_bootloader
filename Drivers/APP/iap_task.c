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
#include "bsp_iap.h"
#include "dev_uart.h"

static void JumpToApplication(void) {
	uint32_t i = 0;
	void (*SysMemBootJump)(void);
	__IO uint32_t BootAddr = 0x8010000;

	__set_PRIMASK(1); 


	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;


	HAL_RCC_DeInit();


	for (i = 0; i < 8; i++) {
		NVIC->ICER[i] = 0xFFFFFFFF;
		NVIC->ICPR[i] = 0xFFFFFFFF;
	}

	SysMemBootJump = (void (*)(void)) (*((uint32_t*) (BootAddr + 4)));

	__set_MSP(*(uint32_t*) BootAddr);

	__set_CONTROL(0);

	SCB->VTOR = (0x8000000 | (0x10000 & (uint32_t) 0xFFFFFE00));
	SysMemBootJump();
}


osThreadId_t iapTaskHandle;

const osThreadAttr_t iapTask_attributes = {
    .name = "iapTask",
    .stack_size = 128 * 10,
    .priority = (osPriority_t)osPriorityNormal1,
};

uint8_t buff[1024];
void iapTask(void *argument)
{
    uint32_t flags;
    uint16_t pages;
    uint16_t remaining;
		uint16_t firmware_size;
    for (;;)
    {

        flags = osEventFlagsWait(usartEventFlagsHandle, IAP_EVENT_BIT_1, osFlagsWaitAny, osWaitForever);
        if ((flags & IAP_EVENT_BIT_1) == IAP_EVENT_BIT_1)
        {		
						firmware_size = s_UartTxRxCount[1];
            pages = firmware_size / 1024;
            remaining = firmware_size % 1024;
            for(int i = 0; i < pages; i++)
            {
                memset(buff, 0, sizeof(buff));
                W25QXX_Read(buff, i * 1024, 1024);
                iap_write_appbin(FLASH_APP1_ADDR + i * 1024, buff, 1024);
            }
            if(remaining)
            {
                memset(buff, 0, sizeof(buff));
                W25QXX_Read(buff, pages * 1024, remaining);
                iap_write_appbin(FLASH_APP1_ADDR + pages * 1024, buff, remaining);
            }
						printf("addr is %d\r\n",addr);
            printf("iap success and firmware_size is %d\r\n",firmware_size);
//						__set_CONTROL(0);				
//            iap_load_app(FLASH_APP1_ADDR);
						JumpToApplication();
        }
        osDelay(1000);
    }
}
