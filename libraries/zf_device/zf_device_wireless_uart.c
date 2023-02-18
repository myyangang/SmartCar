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

#include "zf_device_type.h"
#include "zf_device_wireless_uart.h"

wireless_info_struct wireless_device_info[] = WIRELESS_DEVICE_INFO_BUFFER;
uint8_t wireless_rx_buffer[WIRELESS_NUMBER];
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ���ʼ��
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
void wireless_init(void)
{
    uint8_t i = 0;
    wireless_type = WIRELESS_UART;

    for(i = 0; i<WIRELESS_NUMBER; i++)
    {
        uart_init(wireless_device_info[i].uart_n, wireless_device_info[i].uart_baud, wireless_device_info[i].tx_pin, wireless_device_info[i].rx_pin);
        gpio_init(wireless_device_info[i].rts_pin, GPI, 1, GPI_PULL_UP);
        uart_rx_interrupt(wireless_device_info[i].uart_n, ENABLE);
    }

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�� ���ͺ���
//  @param      buff        ��Ҫ���͵����ݵ�ַ
//  @param      len         ���ͳ���
//  @return     uint32      ʣ��δ���͵��ֽ���
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint32_t wireless_send_buff(uart_index_enum uart_n, uint8_t *buff, uint32_t len)
{
    wireless_info_struct *temp_info = NULL;
    uint8_t i = 0;

    for(i = 0; i<WIRELESS_NUMBER; i++)
    {
        if(wireless_device_info[i].uart_n == uart_n)
        {
            temp_info = &wireless_device_info[i];
            break;
        }
    }

    while(len>30)
    {
        if(gpio_get_level(temp_info->rts_pin))
        {
            return len;//ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
        }
        //while(gpio_get(RTS_PIN));  //���RTSΪ�͵�ƽ���������������
        uart_write_buffer(temp_info->uart_n,buff,30);

        buff += 30; //��ַƫ��
        len -= 30;//����
    }

    if(gpio_get_level(temp_info->rts_pin))
    {
        return len;//ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
    }
    //while(gpio_get(RTS_PIN));  //���RTSΪ�͵�ƽ���������������
    uart_write_buffer(temp_info->uart_n,buff,len);//������������

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�� �����жϺ���
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       �ú�����ISR�ļ� ����2�жϳ��򱻵���
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_callback_ch1(void)
{
    // �ӵ�һ���ֽں�Ƭ���������˴���ͨ���ڴ˴���ȡwireless_rx_buffer����ȡ������
    wireless_rx_buffer[0] = ((USART_TypeDef*)uart_index[wireless_device_info[0].uart_n])->DATAR & 0x01FF;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�� �����жϺ���
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       �ú�����ISR�ļ� ����7�жϳ��򱻵���
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_callback_ch2(void)
{
    // �ӵ�һ���ֽں�Ƭ���������˴���ͨ���ڴ˴���ȡwireless_rx_buffer����ȡ������
    wireless_rx_buffer[1] = ((USART_TypeDef*)uart_index[wireless_device_info[1].uart_n])->DATAR & 0x01FF;

}


