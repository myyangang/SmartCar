/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             zf_device_wireless_uart
* @company          �ɶ���ɿƼ����޹�˾
* @author           ��ɿƼ�(QQ790875685)
* @version          �鿴doc��version�ļ� �汾˵��
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

#define WIRELESS_NUMBER         2//����ģ�����

#define WIRELESS_DEVICE_INFO_BUFFER \
{\
    {\
        UART_2,             /* ����ת����ģ��1 ���ں�                                                         */\
        115200,             /* ����ת����ģ��1 ������                                                         */\
        UART2_TX_D5,        /* ����ת����ģ��1 ģ���RX ���� ���� ��Ƭ����TX ���� */\
        UART2_RX_D6,        /* ����ת����ģ��1 ģ���TX ���� ���� ��Ƭ����RX ���� */\
        E10                 /* ����ת����ģ��1 RTS����                                                     */\
    }, \
    {\
        UART_7,             /* ����ת����ģ��2 ���ں�                                                         */\
        115200,             /* ����ת����ģ��2 ������                                                         */\
        UART7_TX_E12,       /* ����ת����ģ��2 ģ���RX ���� ���� ��Ƭ����TX ���� */\
        UART7_RX_E13,       /* ����ת����ģ��2 ģ���TX ���� ���� ��Ƭ����RX ���� */\
        E8                  /* ����ת����ģ��2 RTS����                                                     */\
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
