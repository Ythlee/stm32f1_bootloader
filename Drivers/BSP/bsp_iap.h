#ifndef __IAP_H
#define __IAP_H

#include "sys.h"

typedef void (*iapfun)(void); /* 定义一个函数类型的参数 */

#define FLASH_APP1_ADDR                                                                                                \
    0x08010000 /* 第一个应用程序起始地址(存放在内部FLASH)                                              \
                * 保留 0X08000000~0X08008FFF(36KB) 的空间为 Bootloader 使用                                    \
                */

void iap_load_app(uint32_t appxaddr);                                       /* 跳转到APP程序执行 */
void iap_write_appbin(uint32_t appxaddr, uint8_t *appbuf, uint32_t applen); /* 在指定地址开始,写入bin */

#endif
