/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
* @file             zf_common_function
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
 * @version         查看doc内version文件 版本说明
 * @Software        MounRiver Studio V1.51
 * @Target core     CH32V307VCT6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2021-11-25
 ********************************************************************************************************************/

#ifndef _zf_common_function_h_
#define _zf_common_function_h_

#include "stdint.h"
#include "stdarg.h"
#include "string.h"

//====================================================宏定义函数区====================================================
//-------------------------------------------------------------------------------------------------------------------
// @brief       绝对值函数 数据范围是 [-32767,32767]
// @param       dat             需要求绝对值的数
// @return      int             返回绝对值
// Sample usage:                dat = myabs(dat);                               // 将dat变成正数
//-------------------------------------------------------------------------------------------------------------------
#define     myabs(x)            ((x>=0)?(x):(-x))

//-------------------------------------------------------------------------------------------------------------------
// @brief       限幅 数据范围是 [-32768,32767]
// @param       x               被限幅的数据
// @param       y               限幅范围(数据会被限制在-y至+y之间)
// @return      int             限幅之后的数据
// Sample usage:                int dat = limit(500,300);                       // 数据被限制在-300至+300之间  因此返回的结果是300
//-------------------------------------------------------------------------------------------------------------------
#define     limit(x,y)          ((x>y)?(y):((x<-y)?(-y):(x)))

//-------------------------------------------------------------------------------------------------------------------
// @brief       双边限幅 数据范围是 [-32768,32767]
// @param       x               被限幅的数据
// @param       a               限幅范围左边界
// @param       b               限幅范围右边界
// @return      int             限幅之后的数据
// Sample usage:                int dat = limit_ab(500,-300,400);               //数据被限制在-300至+400之间  因此返回的结果是400
//-------------------------------------------------------------------------------------------------------------------
#define     limit_ab(x,a,b)     ((x<a)?(a):((x>b)?(b):(x)))
//====================================================宏定义函数区====================================================

//=====================================================常规函数区=====================================================
uint32_t    get_greatest_common_divisor     (uint32_t num1, uint32_t num2);
void        my_delay                        (volatile long t);
int32_t     str_to_int                      (char *str);
uint32_t    str_to_uint32                   (char *str);
void        int32_to_str                    (char *str, int32_t number);
void        uint32_to_str                   (char *str, uint32_t number);
float       str_to_float                    (char *str);
void        float_to_str                    (char *str, float number, uint8_t point_bit);
uint32_t    zf_sprintf                      (int8_t *buff, const int8_t *format, ...);
//=====================================================常规函数区=====================================================

#endif