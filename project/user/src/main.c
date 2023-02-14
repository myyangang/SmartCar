/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             main
* @company          成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/



#include "zf_common_headfile.h"

int main(void)
{
    interrupt_disable_all();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    //    mt9v03x_init_dvp();//摄像头初始化
// 此处编写用户代码(例如：外设初始化代码等)
    //ADC初始化，例：adc_init(ADC_IN7_A7);


    gpio_init(LED_1_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(BEEP_PIN, GPO, 1, GPIO_PIN_CONFIG);
    system_delay_ms(500);
    gpio_set_level(BEEP_PIN, 0);

    interrupt_enable_all(0);            // 总中断最后开启
    while(1)
    {
        // 此处编写需要循环执行的代码

        gpio_set_level(LED_1_PIN, 1);

        if(mt9v03x_finish_flag_dvp == 1)
        {
            old_image_use_flag = image_use_flag;
             mt9v03x_finish_flag_dvp = 0;
            //thershold_local = GetOSTU(image_fire);  //使用某一种办法获得阈值
            //eight_neighbor(image_fire,thershold_local);//然后处理你的图像
            if(old_image_use_flag != image_use_flag)
            {
              if(image_use_flag==1)//改变缓冲区
              {
                  image_fire=camera_buffer_addr2;
              }
              else if(image_use_flag==2)
              {
                  image_fire=camera_buffer_addr;
              }
            }
            else                        //说明程序执行较快，此时下一场的场中断还未到
            {
              if(image_use_flag==1)//改变缓冲区
              {
                  image_fire=camera_buffer_addr;
              }
              else if(image_use_flag==2)
              {
                  image_fire=camera_buffer_addr2;
              }
            }
        }
    }
}




