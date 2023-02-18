/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_camera
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note             
********************************************************************************************************************/

#include "zf_device_mt9v03x_dvp.h"
#include "zf_device_camera.h"
#include "zf_device_type.h"


//-------------------------------------------------------------------------------------------------------------------
// @brief       摄像头串口回调函数
// @param       void
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void camera_uart_handler (void)
{
    if(camera_type == CAMERA_BIN_UART)
    {
        // 小钻风暂不支持
        //ov7725_cof_uart_interrupt();
    }
    else if(camera_type == CAMERA_GRAYSCALE)
    {
        // 总钻风串口回调函数
        mt9v03x_uart_callback_dvp();
    }
    else if(camera_type == CAMERA_COLOR)
    {
        //凌瞳串口回调函数
        //scc8660_uart_callback();
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       摄像头场中断回调函数
// @param       void
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void camera_vsync_handler (void)
{

}

//-------------------------------------------------------------------------------------------------------------------
// @brief       摄像头采集完成DMA回调函数
// @param       void
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void camera_dma_handler (void)
{

}

//-------------------------------------------------------------------------------------------------------------------
// @brief       摄像头DVP接口回调函数
// @param       void
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void camera_dvp_handler(void)
{
    if(camera_type == CAMERA_COLOR)
    {
        //scc8660_dvp_vsync();
    }
    else if(camera_type == CAMERA_GRAYSCALE)
    {
        mt9v03x_dvp_handler();
    }
    else if(camera_type == CAMERA_BIN_UART)
    {
        //小钻风暂不支持
    }
}

