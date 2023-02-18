/*
 * uart.h
 *
 *  Created on: 2023Äê2ÔÂ11ÈÕ
 *      Author: Yaner
 */

#ifndef CODE_UART_H_
#define CODE_UART_H_

void SCI_Send_Datas_original(uart_index_enum uart_num);
void SCI_Send_Datas(uart_index_enum uart_num,
        unsigned short int data_0_0,
        unsigned short int data_0_1,
        unsigned short int data_0_2,
        unsigned short int data_0_3,
        unsigned short int data_1_0,
        unsigned short int data_1_1,
        unsigned short int data_1_2,
        unsigned short int data_1_3,
        unsigned short int data_2_0,
        unsigned short int data_2_1,
        unsigned short int data_2_2,
        unsigned short int data_2_3);

#endif /* CODE_UART_H_ */
