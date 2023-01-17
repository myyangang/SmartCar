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

#include "zf_device_type.h"
#include "zf_device_wireless_uart.h"

wireless_info_struct wireless_device_info[] = WIRELESS_DEVICE_INFO_BUFFER;
uint8_t wireless_rx_buffer[WIRELESS_NUMBER];
//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块初始化
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
//  @brief      无线转串口模块 发送函数
//  @param      buff        需要发送的数据地址
//  @param      len         发送长度
//  @return     uint32      剩余未发送的字节数
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
            return len;//模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
        }
        //while(gpio_get(RTS_PIN));  //如果RTS为低电平，则继续发送数据
        uart_write_buffer(temp_info->uart_n,buff,30);

        buff += 30; //地址偏移
        len -= 30;//数量
    }

    if(gpio_get_level(temp_info->rts_pin))
    {
        return len;//模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
    }
    //while(gpio_get(RTS_PIN));  //如果RTS为低电平，则继续发送数据
    uart_write_buffer(temp_info->uart_n,buff,len);//发送最后的数据

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 串口中断函数
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       该函数在ISR文件 串口2中断程序被调用
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_callback_ch1(void)
{
    // 接到一个字节后单片机将会进入此处，通过在此处读取wireless_rx_buffer可以取走数据
    wireless_rx_buffer[0] = ((USART_TypeDef*)uart_index[wireless_device_info[0].uart_n])->DATAR & 0x01FF;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 串口中断函数
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       该函数在ISR文件 串口7中断程序被调用
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_callback_ch2(void)
{
    // 接到一个字节后单片机将会进入此处，通过在此处读取wireless_rx_buffer可以取走数据
    wireless_rx_buffer[1] = ((USART_TypeDef*)uart_index[wireless_device_info[1].uart_n])->DATAR & 0x01FF;

}


