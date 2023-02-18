/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		TFT
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 * @note		
					���߶��壺
					------------------------------------ 
					ģ��ܽ�            ��Ƭ���ܽ�
					SCL                 �鿴TFT_SCL�궨�������     Ӳ��SPI���Ų��������л�
					SDA                 �鿴TFT_SDA�궨�������     Ӳ��SPI���Ų��������л�
					RES                 �鿴REST_PIN�궨�������    
					DC                  �鿴DC_PIN�궨�������  
					CS                  �鿴TFT_CS�궨�������      Ӳ��SPI���Ų��������л�
					
					��Դ����
					BL  3.3V��Դ������������ţ�Ҳ���Խ�PWM���������ȣ�
					VCC 3.3V��Դ
					GND ��Դ��
					���ֱ���128*160
					------------------------------------ 

 ********************************************************************************************************************/



#ifndef _SEEKFREE_18TFT_h
#define _SEEKFREE_18TFT_h
#include "zf_common_headfile.h"

//--------------------���SPI--------------------


#define	TFT_SCL_SIMSPI_PIN 		E11				//����SPI_SCK����
#define	TFT_SDA_SIMSPI_PIN		E9   			//����SPI_MOSI����
#define TFT_REST_SIMSPI_PIN  	E7				//���帴λ����
#define TFT_DC_SIMSPI_PIN	  	B1				//Һ������λ���Ŷ���
#define TFT_CS_SIMSPI_PIN	  	C5				//����SPI_CS����
#define TFT_BL_SIMSPI_PIN	  	D10				//Һ���������Ŷ���



#define	TFT_SCL_SIMSPI(x)	(x==1)?(gpio_set_level(TFT_SCL_SIMSPI_PIN,1)):(gpio_set_level(TFT_SCL_SIMSPI_PIN,0))
#define	TFT_SDA_SIMSPI(x)	(x==1)?(gpio_set_level(TFT_SDA_SIMSPI_PIN,1)):(gpio_set_level(TFT_SDA_SIMSPI_PIN,0))
#define TFT_REST_SIMSPI(x) 	(x==1)?(gpio_set_level(TFT_REST_SIMSPI_PIN,1)):(gpio_set_level(TFT_REST_SIMSPI_PIN,0))
#define TFT_DC_SIMSPI(x)   	(x==1)?(gpio_set_level(TFT_DC_SIMSPI_PIN,1)):(gpio_set_level(TFT_DC_SIMSPI_PIN,0))
#define TFT_CS_SIMSPI(x) 	(x==1)?(gpio_set_level(TFT_CS_SIMSPI_PIN,1)):(gpio_set_level(TFT_CS_SIMSPI_PIN,0))
#define TFT_BL_SIMSPI(x) 	(x==1)?(gpio_set_level(TFT_BL_SIMSPI_PIN,1)):(gpio_set_level(TFT_BL_SIMSPI_PIN,0))





//-----------------------------------------------    


//-------������ɫ��SEEKFREE_FONT.h�ļ��ж���----------
#define RED          	    0xF800	//��ɫ
#define BLUE         	    0x001F  //��ɫ
#define YELLOW       	    0xFFE0	//��ɫ
#define GREEN        	    0x07E0	//��ɫ
#define WHITE        	    0xFFFF	//��ɫ
#define BLACK        	    0x0000	//��ɫ
#define GRAY  			0X8430 	//��ɫ
#define BROWN 			0XBC40 	//��ɫ
#define PURPLE    		0XF81F	//��ɫ
#define PINK    		    0XFE19	//��ɫ



//����д�ֱʵ���ɫ
#define TFT_PENCOLOR    RED

//���屳����ɫ
#define TFT_BGCOLOR	    WHITE

     
     
//������ʾ����
//0 ����ģʽ
//1 ����ģʽ  ��ת180
//2 ����ģʽ
//3 ����ģʽ  ��ת180
#define TFT_DISPLAY_DIR 2

#if (0==TFT_DISPLAY_DIR || 1==TFT_DISPLAY_DIR)
	#define	TFT_X_MAX	128	//Һ��X�����
	#define TFT_Y_MAX	160 //Һ��Y�����
#elif (2==TFT_DISPLAY_DIR || 3==TFT_DISPLAY_DIR)
	#define	TFT_X_MAX	160	//Һ��X�����
	#define TFT_Y_MAX	128 //Һ��Y�����
#else
#error "TFT_DISPLAY_DIR �������"
     
#endif

//--------------------���SPI--------------------
void lcd_init_simspi(void);
void lcd_clear_simspi(int color);
void lcd_drawpoint_simspi(uint16_t x,uint16_t y,uint16_t color);
void lcd_showchar_simspi(uint16_t x,uint16_t y,const int8_t dat);
void lcd_showstr_simspi(uint16_t x,uint16_t y,const int8_t dat[]);
void lcd_showint8_simspi(uint16_t x,uint16_t y,int8_t dat);
void lcd_showuint8_simspi(uint16_t x,uint16_t y,uint8_t dat);
void lcd_showint16_simspi(uint16_t x,uint16_t y,int16_t dat);
void lcd_showuint16_simspi(uint16_t x,uint16_t y,uint16_t dat);
void lcd_showint32_simspi(uint16_t x,uint16_t y,int32_t dat,uint8_t num);
void lcd_showfloat_simspi(unsigned int x,unsigned int y,double dat,uint8_t num,uint8_t pointnum);

void lcd_show_gray_image (uint16_t x, uint16_t y, uint8_t *p, uint16_t width, uint16_t height, uint16_t dis_width, uint16_t dis_height, uint8_t threshold);
void lcd_writeData_16bit_simspi(uint16_t dat);   //��Һ����дһ��16λ����
void lcd_writeData_simspi(uint8_t dat);          //д����
void lcd_show_curve_y(unsigned char *curve,unsigned int y, unsigned char len,uint16_t color);
void lcd_show_curve_x(unsigned char *curve,unsigned int y, unsigned char len,uint16_t color);
void lcd_drawbigpoint(unsigned char x,unsigned char y, uint16_t color);
void lcd_show_stright_y(unsigned char y, uint16_t color);
void lcd_show_compress_binary_image (uint16_t x, uint16_t y, uint8_t *p, uint16_t width, uint16_t height);
//--------------------Ӳ��SPI--------------------



#endif
