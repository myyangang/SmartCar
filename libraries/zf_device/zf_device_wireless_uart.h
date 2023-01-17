/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_wireless_uart
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note
********************************************************************************************************************/
#ifndef _zf_device_wireless_uart_h_
#define _zf_device_wireless_uart_h_


#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"

#define WIRELESS_NUMBER         2//蓝牙模块个数

#define WIRELESS_DEVICE_INFO_BUFFER \
{\
    {\
        UART_2,             /* 无线转串口模块1 串口号                                                         */\
        115200,             /* 无线转串口模块1 波特率                                                         */\
        UART2_TX_D5,        /* 无线转串口模块1 模块的RX 引脚 接入 单片机的TX 引脚 */\
        UART2_RX_D6,        /* 无线转串口模块1 模块的TX 引脚 接入 单片机的RX 引脚 */\
        E10                 /* 无线转串口模块1 RTS引脚                                                     */\
    }, \
    {\
        UART_7,             /* 无线转串口模块2 串口号                                                         */\
        115200,             /* 无线转串口模块2 波特率                                                         */\
        UART7_TX_E12,       /* 无线转串口模块2 模块的RX 引脚 接入 单片机的TX 引脚 */\
        UART7_RX_E13,       /* 无线转串口模块2 模块的TX 引脚 接入 单片机的RX 引脚 */\
        E8                  /* 无线转串口模块2 RTS引脚                                                     */\
    }\
}

typedef struct
{
    uart_index_enum uart_n;
    uint32_t uart_baud;
    uart_pin_enum tx_pin;
    uart_pin_enum rx_pin;
    gpio_pin_enum rts_pin;
}wireless_info_struct;




void        wireless_init      (void);
uint32_t    wireless_send_buff          (uart_index_enum uart_n, uint8_t *buff, uint32_t len);
void        wireless_uart_callback_ch1  (void);
void        wireless_uart_callback_ch2  (void);
#endif
