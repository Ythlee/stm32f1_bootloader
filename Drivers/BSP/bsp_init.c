#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_norflash.h"
#include "bsp_spi.h"
#include "bsp_stmflash.h"
#include "dev_uart.h"

void bsp_init(void)
{
	led_init();
	key_init();
	uart_device_init(DEV_UART1);
	W25QXX_Init();
}

