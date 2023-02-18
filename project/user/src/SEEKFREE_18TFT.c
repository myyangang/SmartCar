/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		TFT
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 * @note		
					接线定义：
					------------------------------------ 
					模块管脚            单片机管脚
					SCL                 查看TFT_SCL宏定义的引脚     硬件SPI引脚不可随意切换
					SDA                 查看TFT_SDA宏定义的引脚     硬件SPI引脚不可随意切换
					RES                 查看REST_PIN宏定义的引脚    
					DC                  查看DC_PIN宏定义的引脚  
					CS                  查看TFT_CS宏定义的引脚      硬件SPI引脚不可随意切换
					
					电源引脚
					BL  3.3V电源（背光控制引脚，也可以接PWM来控制亮度）
					VCC 3.3V电源
					GND 电源地
					最大分辨率128*160
					------------------------------------ 

 ********************************************************************************************************************/




#include "zf_common_headfile.h"
#include "SEEKFREE_18TFT.h"

//-------------------------------------------------------------------------------------------------------------------
//  以下函数是使用软件SPI通信，相比较硬件SPI，软件SPI引脚更加灵活，可以使用任意普通IO
//-------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeIndex_simspi(uint8_t dat)			//写命令
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
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeData_simspi(uint8_t dat)			//写数据
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
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeData_16bit_simspi(uint16_t dat)	//向液晶屏写一个16位数据
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
//  @brief      液晶坐标设置
//  @param      x_start     	坐标x方向的起点
//  @param      y_start     	坐标y方向的起点
//  @param      x_end       	坐标x方向的终点
//  @param      y_end       	坐标y方向的终点
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_set_region(0,0,10,10);// x、y的起点都是0，终点都是10
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
//  @brief      液晶清屏函数
//  @param      color     		颜色设置
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_clear(YELLOW);// 全屏设置为黄色
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
//  @brief      液晶初始化
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
        case 0: lcd_writeData_simspi(1<<7 | 1<<6 | 0<<5);  break;  //竖屏模式
        case 1: lcd_writeData_simspi(0<<7 | 0<<6 | 0<<5);  break;  //竖屏模式  旋转180
        case 2: lcd_writeData_simspi(1<<7 | 0<<6 | 1<<5);  break;  //横屏模式
        case 3: lcd_writeData_simspi(0<<7 | 1<<6 | 1<<5);  break;  //横屏模式  旋转180
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

    lcd_clear_simspi(WHITE);//全白
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶画点
//  @param      x     	        坐标x方向的起点
//  @param      y     	        坐标y方向的起点
//  @param      dat       	    需要显示的颜色
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_drawpoint(0,0,RED);  //坐标0,0画一个红色的点
//-------------------------------------------------------------------------------------------------------------------
void lcd_drawpoint_simspi(uint16_t x,uint16_t y,uint16_t color)
{
    lcd_set_region_simspi(x,y,x,y);
    lcd_writeData_16bit_simspi(color);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的字符
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showchar(0,0,'x');//坐标0,0写一个字符x
//-------------------------------------------------------------------------------------------------------------------
void lcd_showchar_simspi(uint16_t x,uint16_t y,const int8_t dat)
{
	uint8_t i,j;
	uint8_t temp;
    
	for(i=0; i<16; i++)
	{
		lcd_set_region_simspi(x,y+i,x+7,y+i);
		temp = tft_ascii[dat-32][i];//减32因为是取模是从空格开始取得 空格在ascii中序号是32
		for(j=0; j<8; j++)
		{
			if(temp&0x01)	lcd_writeData_16bit_simspi(TFT_PENCOLOR);
			else			lcd_writeData_16bit_simspi(TFT_BGCOLOR);
			temp>>=1;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符串
//  @param      x     	        坐标x方向的起点  参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的字符串
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
//  @brief      液晶显示8位有符号
//  @param      x     	        坐标x方向的起点  参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint8(0,0,x);//x为int8类型
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
//  @brief      液晶显示8位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint8(0,0,x);//x为uint8类型
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
//  @brief      液晶显示16位有符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint16(0,0,x);//x为int16类型
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
//  @brief      液晶显示16位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint16(0,0,x);//x为uint16类型
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
//  @brief      液晶显示32位有符号(去除整数部分无效的0)
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint32
//  @param      num       	    需要显示的位数 最高10位  不包含正负号
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint32(0,0,x,3);//x可以为int32 uint16 int16 uint8 int8类型
//  Sample usage:               负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint32_simspi(uint16_t x,uint16_t y,int32_t dat,uint8_t num)
{
    int8_t    buff[34];
    uint8_t   length;
    
    if(10<num)      num = 10;
    
    num++;
    if(0>dat)   length = zf_sprintf( &buff[0],"%d",dat);//负数
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

    lcd_showstr_simspi(x, y, buff);	//显示数字

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示浮点数(去除整数部分无效的0)
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型float或double
//  @param      num       	    整数位显示长度   最高10位  
//  @param      pointnum        小数位显示长度   最高6位
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showfloat(0,0,x,2,3);//显示浮点数   整数显示2位   小数显示三位
//  @note                       特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//                              可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//                              有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//                              负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void lcd_showfloat_simspi(unsigned int x,unsigned int y,double dat,uint8_t num,uint8_t pointnum)
{
    uint8_t   length;
	int8_t    buff[34];
	int8_t    start,end,point;

	if(6<pointnum)  pointnum = 6;
    if(10<num)      num = 10;
        
    if(0>dat)   length = zf_sprintf( &buff[0],"%f",dat);//负数
    else
    {
        length = zf_sprintf( &buff[1],"%f",dat);
        length++;
    }
    point = length - 7;         //计算小数点位置
    start = point - num - 1;    //计算起始位
    end = point + pointnum + 1; //计算结束位
    while(0>start)//整数位不够  末尾应该填充空格
    {
        buff[end] = ' ';
        end++;
        start++;
    }
    
    if(0>dat)   buff[start] = '-';
    else        buff[start] = ' ';
    
    buff[end] = '\0';

    lcd_showstr_simspi(x, y, buff);	//显示数字
}


//-------------------------------------------------------------------------------------------------------------------
// @brief       TFT180 显示 8bit 灰度图像 带二值化阈值
// @param       x               坐标x方向的起点 参数范围 [0, tft180_x_max-1]
// @param       y               坐标y方向的起点 参数范围 [0, tft180_y_max-1]
// @param       *p              图像数组指针
// @param       width           图像实际宽度
// @param       height          图像实际高度
// @param       dis_width       图像显示宽度 参数范围 [0, tft180_x_max]
// @param       dis_height      图像显示高度 参数范围 [0, tft180_y_max]
// @param       threshold       二值化显示阈值 0-不开启二值化
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

    lcd_set_region_simspi(x, y, x+dis_width-1, y+dis_height-1);                     // 设置显示区域

    for(j=0;j<dis_height;j++)
    {
        height_index = j*height/dis_height;
        for(i=0;i<dis_width;i++)
        {
            width_index = i*width/dis_width;
            temp = *(p+height_index*width+width_index);                         // 读取像素点
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
// @brief       TFT180 显示一条弯曲的线
// @param       *curve          所要画的曲线的x轴坐标
// @param       y               y轴起始位置
// @param       len             长度
// @param       color           曲线颜色
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
// @brief       TFT180 显示一条弯曲的线
// @param       *curve          所要画的曲线的y轴坐标
// @param       y               y轴起始位置
// @param       len             长度
// @param       color           曲线颜色
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
// @brief       TFT180 显示一一个大点
// @param       x          所要画的点的x轴坐标
// @param       y               y轴起始位置
// @param       color           曲线颜色
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
// @brief       TFT180 显示一垂直y轴横线
// @param       y               y轴起始位置
// @param       color           曲线颜色
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
// @brief       TFT180 显示 8bit 压缩二值化图像(宽度上压缩）
// @param       x               坐标x方向的起点 参数范围 [0, tft180_x_max-1]
// @param       y               坐标y方向的起点 参数范围 [0, tft180_y_max-1]
// @param       *p              图像数组指针
// @param       width           图像实际宽度
// @param       height          图像实际高度
// @param       dis_width       图像显示宽度 参数范围 [0, tft180_x_max]
// @param       dis_height      图像显示高度 参数范围 [0, tft180_y_max]
// @param       threshold       二值化显示阈值 0-不开启二值化
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

    lcd_set_region_simspi(x, y, x+width-1, y+height-1);                     // 设置显示区域

    for(j=0;j<height;j++)
    {
        height_index = j;
        for(i=0;i<width/8;i++)
        {
            width_index = i;
            temp = *(p+height_index*(width/8)+width_index);                         // 读取像素点
            for (k = 0; k < 8; ++k) {
                if((temp&(1<<k)))
                    lcd_writeData_16bit_simspi(WHITE);
                else
                    lcd_writeData_16bit_simspi(BLACK);
            }

        }
    }
}


