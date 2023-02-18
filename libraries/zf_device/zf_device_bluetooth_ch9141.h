/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_bluetooth_ch9141
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note
********************************************************************************************************************/
#ifndef _zf_device_bluetooth_ch9141_h_
#define _zf_device_bluetooth_ch9141_h_

#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"
#include "zf_driver_delay.h"
#include "zf_device_bluetooth_ch9141.h"


#define BLUETOOTH_CH9141_NUMBER         1//蓝牙模块个数
#define BLUETOOTH_CH9141_DEVICE_INFO_BUFFER \
{\
    {\
        UART_2,                         /* CH9141 蓝牙模块1 串口号                                                                  */\
        115200,                         /* CH9141 蓝牙模块1 波特率                                                                  */\
        UART2_TX_D5,                    /* CH9141 蓝牙模块1 模块的RX 引脚 接入 单片机的TX 引脚          */\
        UART2_RX_D6,                    /* CH9141 蓝牙模块1 模块的TX 引脚 接入 单片机的RX 引脚          */\
        E10,                            /* CH9141 蓝牙模块1 RTS引脚                                                             */\
        MASTER_MODE,                    /* CH9141 蓝牙模块1 模式选择                                                              */\
        "A1:7B:19:26:3B:38,000000"      /* CH9141 蓝牙模块1 主机连接的账号与密码                                       */\
    },\
}



// 超时设置
#define BLUETOOTH_CH9141_INIT_TIMEOUT                  5000

typedef enum
{
    TX_POWER_0DB = 0,   //0DB
    TX_POWER_1DB,       //1DB
    TX_POWER_2DB,       //2DB
    TX_POWER_3DB,       //3DB
    TX_POWER_4DB,       //4DB
    TX_POWER_MINUS_8DB, //-8DB
    TX_POWER_MINUS_14DB,//-14DB
    TX_POWER_MINUS_20DB,//-20DB
}ch9141_tx_power_enum;


typedef enum
{
    MASTER_NO_INIT = 0,        //主机未初始化
    MASTER_SCANNING,           //主机扫描中
    MASTER_CONNECTING,         //主机连接中
    MASTER_CONNECTED,          //主机已连接
    MASTER_DISCONNECTED,       //主机连接断开

    SLAVE_NO_INIT,         //从机未初始化
    SLAVE_OK_INIT,         //从机完成初始化
    SLAVE_BROADCAST,       //从机广播中
    SLAVE_BROADCAST_READY, //从机准备广播
    SLAVE_CONNECT_TIMEOUT, //从机连接超时
    SLAVE_CONNECTED,       //从机已连接
    SLAVE_ERROR,           //从机出现错误
}ch9141_status_enum;

typedef enum
{
    BROADCAST_MODE = 0, //广播模式
    MASTER_MODE,        //主机模式
    SLAVE_MODE,         //从机模式
}ch9141_mode_enum;


typedef struct
{
    uart_index_enum uart_n;
    uint32_t baud;
    uart_pin_enum tx_pin;
    uart_pin_enum rx_pin;
    gpio_pin_enum rts_pin;
    ch9141_mode_enum mode;
    int8_t *salve_mac_password;
}bluetooth_ch9141_info_struct;

extern uint8_t uart_flag;
extern uint8_t uart_data;

void bluetooth_ch9141_uart_callback_ch1(void);
void bluetooth_ch9141_uart_callback_ch2(void);
uint32_t bluetooth_ch9141_send_buff(uart_index_enum uart_n, uint8_t *buff, uint32_t len);
uint8_t bluetooth_ch9141_enter_at_mode(uart_index_enum uart_n);
uint8_t bluetooth_ch9141_exit_at_mode(uart_index_enum uart_n);
uint8_t bluetooth_ch9141_reset(uart_index_enum uart_n);
uint8_t bluetooth_ch9141_get_mac_address(uart_index_enum uart_n);
int16_t bluetooth_ch9141_get_rssi(uart_index_enum uart_n);
ch9141_status_enum bluetooth_ch9141_get_status(uart_index_enum uart_n, ch9141_mode_enum mode);
uint8_t bluetooth_ch9141_init(void);



#endif



