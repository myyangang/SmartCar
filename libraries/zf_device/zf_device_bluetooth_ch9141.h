/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             zf_device_bluetooth_ch9141
* @company          �ɶ���ɿƼ����޹�˾
* @author           ��ɿƼ�(QQ790875685)
* @version          �鿴doc��version�ļ� �汾˵��
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


#define BLUETOOTH_CH9141_NUMBER         1//����ģ�����
#define BLUETOOTH_CH9141_DEVICE_INFO_BUFFER \
{\
    {\
        UART_2,                         /* CH9141 ����ģ��1 ���ں�                                                                  */\
        115200,                         /* CH9141 ����ģ��1 ������                                                                  */\
        UART2_TX_D5,                    /* CH9141 ����ģ��1 ģ���RX ���� ���� ��Ƭ����TX ����          */\
        UART2_RX_D6,                    /* CH9141 ����ģ��1 ģ���TX ���� ���� ��Ƭ����RX ����          */\
        E10,                            /* CH9141 ����ģ��1 RTS����                                                             */\
        MASTER_MODE,                    /* CH9141 ����ģ��1 ģʽѡ��                                                              */\
        "A1:7B:19:26:3B:38,000000"      /* CH9141 ����ģ��1 �������ӵ��˺�������                                       */\
    },\
}



// ��ʱ����
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
    MASTER_NO_INIT = 0,        //����δ��ʼ��
    MASTER_SCANNING,           //����ɨ����
    MASTER_CONNECTING,         //����������
    MASTER_CONNECTED,          //����������
    MASTER_DISCONNECTED,       //�������ӶϿ�

    SLAVE_NO_INIT,         //�ӻ�δ��ʼ��
    SLAVE_OK_INIT,         //�ӻ���ɳ�ʼ��
    SLAVE_BROADCAST,       //�ӻ��㲥��
    SLAVE_BROADCAST_READY, //�ӻ�׼���㲥
    SLAVE_CONNECT_TIMEOUT, //�ӻ����ӳ�ʱ
    SLAVE_CONNECTED,       //�ӻ�������
    SLAVE_ERROR,           //�ӻ����ִ���
}ch9141_status_enum;

typedef enum
{
    BROADCAST_MODE = 0, //�㲥ģʽ
    MASTER_MODE,        //����ģʽ
    SLAVE_MODE,         //�ӻ�ģʽ
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



