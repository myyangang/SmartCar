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




#include "zf_common_headfile.h"
#include "SEEKFREE_18TFT.h"

//-------------------------------------------------------------------------------------------------------------------
//  ���º�����ʹ�����SPIͨ�ţ���Ƚ�Ӳ��SPI�����SPI���Ÿ���������ʹ��������ͨIO
//-------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeIndex_simspi(uint8_t dat)			//д����
{	
	uint8_t i=8;
	
    TFT_CS_SIMSPI(0);
	TFT_DC_SIMSPI(0);
	TFT_SCL_SIMSPI(0);
	
	while(i--)
	{
		if(dat&0x80){TFT_SDA_SIMSPI(1);}
		else{TFT_SDA_SIMSPI(0);}
		TFT_SCL_SIMSPI(1);
		
		TFT_SCL_SIMSPI(0);
		dat<<=1;
	}	
    TFT_CS_SIMSPI(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeData_simspi(uint8_t dat)			//д����
{
    uint8_t i=8;
	
    TFT_CS_SIMSPI(0);
	TFT_DC_SIMSPI(1);
	TFT_SCL_SIMSPI(0);
	while(i--)
	{
	  	if(dat&0x80){TFT_SDA_SIMSPI(1);}
	  	else{TFT_SDA_SIMSPI(0);}
	  	TFT_SCL_SIMSPI(1);
		
	  	TFT_SCL_SIMSPI(0);
	  	dat<<=1;
	}
    TFT_CS_SIMSPI(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeData_16bit_simspi(uint16_t dat)	//��Һ����дһ��16λ����
{
	uint8_t i=16;
	
    TFT_CS_SIMSPI(0);
    TFT_DC_SIMSPI(1);
    TFT_SCL_SIMSPI(0);
	
	while(i--)
	{
	  	if(dat&0x8000){TFT_SDA_SIMSPI(1);}
	  	else{TFT_SDA_SIMSPI(0);}
	  	TFT_SCL_SIMSPI(1);
		
	  	TFT_SCL_SIMSPI(0);
	  	dat<<=1;
	}
	
    TFT_CS_SIMSPI(1);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����������
//  @param      x_start     	����x��������
//  @param      y_start     	����y��������
//  @param      x_end       	����x������յ�
//  @param      y_end       	����y������յ�
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_set_region(0,0,10,10);// x��y����㶼��0���յ㶼��10
//-------------------------------------------------------------------------------------------------------------------
void lcd_set_region_simspi(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{	

    
#if (0 == TFT_DISPLAY_DIR || 1 == TFT_DISPLAY_DIR)
    lcd_writeIndex_simspi(0x2a);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8_t)(x_start+2));
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8_t)(x_end+2));

	lcd_writeIndex_simspi(0x2b);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8_t)(y_start+1));
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8_t)(y_end+1));

#elif(2 == TFT_DISPLAY_DIR || 3 == TFT_DISPLAY_DIR)
    lcd_writeIndex_simspi(0x2a);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8_t)(x_start+1));
	lcd_writeData_simspi(0x0);
	lcd_writeData_simspi((uint8_t)(x_end+1));

	lcd_writeIndex_simspi(0x2b);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8_t)(y_start+2));
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8_t)(y_end+2));

#endif
    
    lcd_writeIndex_simspi(0x2c);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����������
//  @param      color     		��ɫ����
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_clear(YELLOW);// ȫ������Ϊ��ɫ
//-------------------------------------------------------------------------------------------------------------------
void lcd_clear_simspi(int color)
{
 	uint8_t i,j;
	lcd_set_region_simspi(0,0,TFT_X_MAX-1,TFT_Y_MAX-1);
 	for (i=0;i<TFT_Y_MAX;i++)
    	for (j=0;j<TFT_X_MAX;j++)
        	lcd_writeData_16bit_simspi(color);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʼ��
//  @return     void
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_init_simspi(void)
{	
    gpio_init(TFT_SCL_SIMSPI_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(TFT_SDA_SIMSPI_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(TFT_REST_SIMSPI_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(TFT_DC_SIMSPI_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(TFT_CS_SIMSPI_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(TFT_BL_SIMSPI_PIN, GPO, 1, GPIO_PIN_CONFIG);
	
	
    TFT_REST_SIMSPI(0);
    system_delay_ms(10);
    TFT_REST_SIMSPI(1);
    system_delay_ms(120);
    lcd_writeIndex_simspi(0x11);
    system_delay_ms(120);

    lcd_writeIndex_simspi(0xB1); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    
    lcd_writeIndex_simspi(0xB2); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    
    lcd_writeIndex_simspi(0xB3); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    
    lcd_writeIndex_simspi(0xB4);
    lcd_writeData_simspi(0x07); 

    lcd_writeIndex_simspi(0xC0); 
    lcd_writeData_simspi(0xA2); 
    lcd_writeData_simspi(0x02); 
    lcd_writeData_simspi(0x84); 
    lcd_writeIndex_simspi(0xC1); 
    lcd_writeData_simspi(0xC5); 
    
    lcd_writeIndex_simspi(0xC2); 
    lcd_writeData_simspi(0x0A); 
    lcd_writeData_simspi(0x00); 
    
    lcd_writeIndex_simspi(0xC3); 
    lcd_writeData_simspi(0x8A); 
    lcd_writeData_simspi(0x2A); 
    lcd_writeIndex_simspi(0xC4); 
    lcd_writeData_simspi(0x8A); 
    lcd_writeData_simspi(0xEE); 
    
    lcd_writeIndex_simspi(0xC5);
    lcd_writeData_simspi(0x0E); 
    
    lcd_writeIndex_simspi(0x36);
    switch(TFT_DISPLAY_DIR)//y x v
    {
        case 0: lcd_writeData_simspi(1<<7 | 1<<6 | 0<<5);  break;  //����ģʽ
        case 1: lcd_writeData_simspi(0<<7 | 0<<6 | 0<<5);  break;  //����ģʽ  ��ת180
        case 2: lcd_writeData_simspi(1<<7 | 0<<6 | 1<<5);  break;  //����ģʽ
        case 3: lcd_writeData_simspi(0<<7 | 1<<6 | 1<<5);  break;  //����ģʽ  ��ת180
    }

    lcd_writeIndex_simspi(0xe0); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x1a); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x18); 
    lcd_writeData_simspi(0x2f); 
    lcd_writeData_simspi(0x28); 
    lcd_writeData_simspi(0x20); 
    lcd_writeData_simspi(0x22); 
    lcd_writeData_simspi(0x1f); 
    lcd_writeData_simspi(0x1b); 
    lcd_writeData_simspi(0x23); 
    lcd_writeData_simspi(0x37); 
    lcd_writeData_simspi(0x00); 	
    lcd_writeData_simspi(0x07); 
    lcd_writeData_simspi(0x02); 
    lcd_writeData_simspi(0x10); 
    
    lcd_writeIndex_simspi(0xe1); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x1b); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x17); 
    lcd_writeData_simspi(0x33); 
    lcd_writeData_simspi(0x2c); 
    lcd_writeData_simspi(0x29); 
    lcd_writeData_simspi(0x2e); 
    lcd_writeData_simspi(0x30); 
    lcd_writeData_simspi(0x30); 
    lcd_writeData_simspi(0x39); 
    lcd_writeData_simspi(0x3f); 
    lcd_writeData_simspi(0x00); 
    lcd_writeData_simspi(0x07); 
    lcd_writeData_simspi(0x03); 
    lcd_writeData_simspi(0x10);  
    
    lcd_writeIndex_simspi(0x2a);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x00+2);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x80+2);
    
    lcd_writeIndex_simspi(0x2b);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x00+3);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x80+3);
    
    lcd_writeIndex_simspi(0xF0); 
    lcd_writeData_simspi(0x01); 
    lcd_writeIndex_simspi(0xF6);
    lcd_writeData_simspi(0x00); 
    
    lcd_writeIndex_simspi(0x3A);
    lcd_writeData_simspi(0x05); 
    lcd_writeIndex_simspi(0x29);

    lcd_clear_simspi(WHITE);//ȫ��
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ������
//  @param      x     	        ����x��������
//  @param      y     	        ����y��������
//  @param      dat       	    ��Ҫ��ʾ����ɫ
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_drawpoint(0,0,RED);  //����0,0��һ����ɫ�ĵ�
//-------------------------------------------------------------------------------------------------------------------
void lcd_drawpoint_simspi(uint16_t x,uint16_t y,uint16_t color)
{
    lcd_set_region_simspi(x,y,x,y);
    lcd_writeData_16bit_simspi(color);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ�ַ�
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ���ַ�
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showchar(0,0,'x');//����0,0дһ���ַ�x
//-------------------------------------------------------------------------------------------------------------------
void lcd_showchar_simspi(uint16_t x,uint16_t y,const int8_t dat)
{
	uint8_t i,j;
	uint8_t temp;
    
	for(i=0; i<16; i++)
	{
		lcd_set_region_simspi(x,y+i,x+7,y+i);
		temp = tft_ascii[dat-32][i];//��32��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո���ascii�������32
		for(j=0; j<8; j++)
		{
			if(temp&0x01)	lcd_writeData_16bit_simspi(TFT_PENCOLOR);
			else			lcd_writeData_16bit_simspi(TFT_BGCOLOR);
			temp>>=1;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ�ַ���
//  @param      x     	        ����x��������  ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y��������  ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ���ַ���
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showstr(0,0,"seekfree");
//-------------------------------------------------------------------------------------------------------------------
void lcd_showstr_simspi(uint16_t x,uint16_t y,const int8_t dat[])
{
	uint16_t j;
	
	j = 0;
	while(dat[j] != '\0')
	{
		lcd_showchar_simspi(x+8*j,y*16,dat[j]);
		j++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ8λ�з���
//  @param      x     	        ����x��������  ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y��������  ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������int8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint8(0,0,x);//xΪint8����
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint8_simspi(uint16_t x,uint16_t y,int8_t dat)
{
	uint8_t a[3];
	uint8_t i;
	if(dat<0)
	{
		lcd_showchar_simspi(x,y*16,'-');
		dat = -dat;
	}
	else	lcd_showchar_simspi(x,y*16,' ');
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar_simspi((uint8_t)(x+(8*(i+1))), (uint8_t)(y*16),(int8_t)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ8λ�޷���
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������uint8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint8(0,0,x);//xΪuint8����
//-------------------------------------------------------------------------------------------------------------------
void lcd_showuint8_simspi(uint16_t x,uint16_t y,uint8_t dat)
{
	uint8_t a[3];
	uint8_t i;
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar_simspi((uint8_t)(x+(8*(i+1))), (uint8_t)(y*16),(int8_t)('0' + a[i]));
		i++;
	}
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ16λ�з���
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������int16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint16(0,0,x);//xΪint16����
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint16_simspi(uint16_t x,uint16_t y,int16_t dat)
{
	uint8_t a[5];
	uint8_t i;
	if(dat<0)
	{
		lcd_showchar_simspi(x,y*16,'-');
		dat = -dat;
	}
	else	lcd_showchar_simspi(x,y*16,' ');

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar_simspi((uint8_t)(x+(8*(i+1))), (uint8_t)(y*16),(int8_t)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ16λ�޷���
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������uint16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint16(0,0,x);//xΪuint16����
//-------------------------------------------------------------------------------------------------------------------
void lcd_showuint16_simspi(uint16_t x,uint16_t y,uint16_t dat)
{
	uint8_t a[5];
	uint8_t i;

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar_simspi((uint8_t)(x+(8*(i+1))), (uint8_t)(y*16),(int8_t)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ32λ�з���(ȥ������������Ч��0)
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������uint32
//  @param      num       	    ��Ҫ��ʾ��λ�� ���10λ  ������������
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint32(0,0,x,3);//x����Ϊint32 uint16 int16 uint8 int8����
//  Sample usage:               ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint32_simspi(uint16_t x,uint16_t y,int32_t dat,uint8_t num)
{
    int8_t    buff[34];
    uint8_t   length;
    
    if(10<num)      num = 10;
    
    num++;
    if(0>dat)   length = zf_sprintf( &buff[0],"%d",dat);//����
    else
    {
        buff[0] = ' ';
        length = zf_sprintf( &buff[1],"%d",dat);
        length++;
    }
    while(length < num)
    {
        buff[length] = ' ';
        length++;
    }
    buff[num] = '\0';

    lcd_showstr_simspi(x, y, buff);	//��ʾ����

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����ʾ������(ȥ������������Ч��0)
//  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
//  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
//  @param      dat       	    ��Ҫ��ʾ�ı�������������float��double
//  @param      num       	    ����λ��ʾ����   ���10λ  
//  @param      pointnum        С��λ��ʾ����   ���6λ
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showfloat(0,0,x,2,3);//��ʾ������   ������ʾ2λ   С����ʾ��λ
//  @note                       �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
//                              ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
//                              �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
//                              ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void lcd_showfloat_simspi(unsigned int x,unsigned int y,double dat,uint8_t num,uint8_t pointnum)
{
    uint8_t   length;
	int8_t    buff[34];
	int8_t    start,end,point;

	if(6<pointnum)  pointnum = 6;
    if(10<num)      num = 10;
        
    if(0>dat)   length = zf_sprintf( &buff[0],"%f",dat);//����
    else
    {
        length = zf_sprintf( &buff[1],"%f",dat);
        length++;
    }
    point = length - 7;         //����С����λ��
    start = point - num - 1;    //������ʼλ
    end = point + pointnum + 1; //�������λ
    while(0>start)//����λ����  ĩβӦ�����ո�
    {
        buff[end] = ' ';
        end++;
        start++;
    }
    
    if(0>dat)   buff[start] = '-';
    else        buff[start] = ' ';
    
    buff[end] = '\0';

    lcd_showstr_simspi(x, y, buff);	//��ʾ����
}


//-------------------------------------------------------------------------------------------------------------------
// @brief       TFT180 ��ʾ 8bit �Ҷ�ͼ�� ����ֵ����ֵ
// @param       x               ����x�������� ������Χ [0, tft180_x_max-1]
// @param       y               ����y�������� ������Χ [0, tft180_y_max-1]
// @param       *p              ͼ������ָ��
// @param       width           ͼ��ʵ�ʿ��
// @param       height          ͼ��ʵ�ʸ߶�
// @param       dis_width       ͼ����ʾ��� ������Χ [0, tft180_x_max]
// @param       dis_height      ͼ����ʾ�߶� ������Χ [0, tft180_y_max]
// @param       threshold       ��ֵ����ʾ��ֵ 0-��������ֵ��
// @return      void
// Sample usage:                lcd_show_gray_image(0,0,camera_buffer_addr,MT9V03X_W,MT9V03X_H,MT9V03X_W,MT9V03X_H,0);
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_gray_image (uint16_t x, uint16_t y, uint8_t *p, uint16_t width, uint16_t height, uint16_t dis_width, uint16_t dis_height, uint8_t threshold)
{
    zf_assert(x < tft180_x_max);
    zf_assert(y < tft180_y_max);

    uint32_t i = 0, j = 0;
    uint16_t color = 0,temp = 0;
    uint32_t width_index = 0, height_index = 0;

    lcd_set_region_simspi(x, y, x+dis_width-1, y+dis_height-1);                     // ������ʾ����

    for(j=0;j<dis_height;j++)
    {
        height_index = j*height/dis_height;
        for(i=0;i<dis_width;i++)
        {
            width_index = i*width/dis_width;
            temp = *(p+height_index*width+width_index);                         // ��ȡ���ص�
            if(threshold == 0)
            {
                color=(0x001f&((temp)>>3))<<11;
                color=color|(((0x003f)&((temp)>>2))<<5);
                color=color|(0x001f&((temp)>>3));
                lcd_writeData_16bit_simspi(color);
            }
            else if(temp < threshold)
                lcd_writeData_16bit_simspi(BLACK);
            else
                lcd_writeData_16bit_simspi(WHITE);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       TFT180 ��ʾһ����������
// @param       *curve          ��Ҫ�������ߵ�x������
// @param       y               y����ʼλ��
// @param       len             ����
// @param       color           ������ɫ
// @return      void
// Sample usage:                lcd_show_curve(r_edge,0,128,GREEN);
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_curve_y(unsigned char *curve,unsigned int y, unsigned char len,uint16_t color)
{
    int i;
    for (i = y; i < len; ++i) {
        lcd_drawpoint_simspi(*(curve+i), i, color);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       TFT180 ��ʾһ����������
// @param       *curve          ��Ҫ�������ߵ�y������
// @param       y               y����ʼλ��
// @param       len             ����
// @param       color           ������ɫ
// @return      void
// Sample usage:                lcd_show_curve(r_edge,0,128,GREEN);
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_curve_x(unsigned char *curve,unsigned int x, unsigned char len,uint16_t color)
{
    int i;
    for (i = x; i < len; ++i) {
        lcd_drawpoint_simspi(i, *(curve+i), color);
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       TFT180 ��ʾһһ�����
// @param       x          ��Ҫ���ĵ��x������
// @param       y               y����ʼλ��
// @param       color           ������ɫ
// @return      void
// Sample usage:                lcd_drawbigpoint(0,128,GREEN);
//-------------------------------------------------------------------------------------------------------------------
void lcd_drawbigpoint(unsigned char x,unsigned char y, uint16_t color)
{
    if (x<1) {
        x =1;
    }
    if (y<1) {
        y=1;
    }
    if (x>MT9V03X_DVP_W-2) {
        x=MT9V03X_DVP_W-2;
    }
    if (y>MT9V03X_DVP_H-2) {
        y=MT9V03X_DVP_H-2;
    }
    int i,j;
    for (i = -1; i < 2; ++i) {
        for (j = -1; j < 2; ++j) {
            lcd_drawpoint_simspi(x+i, y+j, color);
        }
    }

}
//-------------------------------------------------------------------------------------------------------------------
// @brief       TFT180 ��ʾһ��ֱy�����
// @param       y               y����ʼλ��
// @param       color           ������ɫ
// @return      void
// Sample usage:                lcd_show_stright_y(50,GREEN);
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_stright_y(unsigned char y, uint16_t color)
{
    int i;
    for (i = 0; i < MT9V03X_DVP_W; ++i) {
        lcd_drawpoint_simspi(i, y, color);
    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       TFT180 ��ʾ 8bit ѹ����ֵ��ͼ��(�����ѹ����
// @param       x               ����x�������� ������Χ [0, tft180_x_max-1]
// @param       y               ����y�������� ������Χ [0, tft180_y_max-1]
// @param       *p              ͼ������ָ��
// @param       width           ͼ��ʵ�ʿ��
// @param       height          ͼ��ʵ�ʸ߶�
// @param       dis_width       ͼ����ʾ��� ������Χ [0, tft180_x_max]
// @param       dis_height      ͼ����ʾ�߶� ������Χ [0, tft180_y_max]
// @param       threshold       ��ֵ����ʾ��ֵ 0-��������ֵ��
// @return      void
// Sample usage:                lcd_show_gray_image(0,0,camera_buffer_addr,MT9V03X_W,MT9V03X_H,MT9V03X_W,MT9V03X_H,0);
//-------------------------------------------------------------------------------------------------------------------
void lcd_show_compress_binary_image (uint16_t x, uint16_t y, uint8_t *p, uint16_t width, uint16_t height)
{
    zf_assert(x < tft180_x_max);
    zf_assert(y < tft180_y_max);

    uint32_t i = 0, j = 0, k;
    uint16_t temp = 0;
    uint32_t width_index = 0, height_index = 0;

    lcd_set_region_simspi(x, y, x+width-1, y+height-1);                     // ������ʾ����

    for(j=0;j<height;j++)
    {
        height_index = j;
        for(i=0;i<width/8;i++)
        {
            width_index = i;
            temp = *(p+height_index*(width/8)+width_index);                         // ��ȡ���ص�
            for (k = 0; k < 8; ++k) {
                if((temp&(1<<k)))
                    lcd_writeData_16bit_simspi(WHITE);
                else
                    lcd_writeData_16bit_simspi(BLACK);
            }

        }
    }
}


