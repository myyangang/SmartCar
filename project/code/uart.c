/*
 * uart.c
 *
 *  Created on: 2023Äê2ÔÂ10ÈÕ
 *      Author: Yaner
 */

#include "zf_common_headfile.h"

void SCI_Send_Datas_original(uart_index_enum uart_num)
{
  int i,j;
  static unsigned short int send_data[3][4] = { { 0 }, { 0 }, { 0 } };
  short int checksum=0;
  unsigned char xorsum=0,high,low;

  send_data[0][0] = (unsigned short int)(0);
  send_data[0][1] = (unsigned short int)(0);
  send_data[0][2] = (unsigned short int)(0);
  send_data[0][3] = (unsigned short int)(0);

  send_data[1][0] = (unsigned short int)(0);
  send_data[1][1] = (unsigned short int)(0);
  send_data[1][2] = (unsigned short int)(0);
  send_data[1][3] = (unsigned short int)(0);

  send_data[2][0] = (unsigned short int)(0);
  send_data[2][1] = (unsigned short int)(0);
  send_data[2][2] = (unsigned short int)(0);
  send_data[2][3] = (unsigned short int)(0);

  uart_write_byte(uart_num, 'S');
  uart_write_byte(uart_num, 'T');
  for (i = 0; i < 3; i++)
    for (j = 0; j < 4; j++)
    {
      low=(unsigned char)(send_data[i][j] & 0x00ff);
      high=(unsigned char)(send_data[i][j] >> 8u);
      uart_write_byte(uart_num,low ); uart_write_byte(uart_num, high);
      checksum+=low; checksum+=high;
      xorsum^=low; xorsum^= high;
    }
  uart_write_byte(uart_num, (unsigned char)(checksum & 0x00ff));
  uart_write_byte(uart_num,xorsum);
}


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
        unsigned short int data_2_3){
  int i,j;
  static unsigned short int send_data[3][4] = { { 0 }, { 0 }, { 0 } };
  short int checksum=0;
  unsigned char xorsum=0,high,low;

  send_data[0][0] = (unsigned short int)(data_0_0);
  send_data[0][1] = (unsigned short int)(data_0_1);
  send_data[0][2] = (unsigned short int)(data_0_2);
  send_data[0][3] = (unsigned short int)(data_0_3);

  send_data[1][0] = (unsigned short int)(data_1_0);
  send_data[1][1] = (unsigned short int)(data_1_1);
  send_data[1][2] = (unsigned short int)(data_1_2);
  send_data[1][3] = (unsigned short int)(data_1_3);

  send_data[2][0] = (unsigned short int)(data_2_0);
  send_data[2][1] = (unsigned short int)(data_2_1);
  send_data[2][2] = (unsigned short int)(data_2_2);
  send_data[2][3] = (unsigned short int)(data_2_3);

  uart_write_byte(uart_num, 'S');
  uart_write_byte(uart_num, 'T');
  for (i = 0; i < 3; i++)
    for (j = 0; j < 4; j++)
    {
      low=(unsigned char)(send_data[i][j] & 0x00ff);
      high=(unsigned char)(send_data[i][j] >> 8u);
      uart_write_byte(uart_num,low ); uart_write_byte(uart_num, high);
      checksum+=low; checksum+=high;
      xorsum^=low; xorsum^= high;
    }
  uart_write_byte(uart_num, (unsigned char)(checksum & 0x00ff));
  uart_write_byte(uart_num,xorsum);
}
