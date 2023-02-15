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

#include "motor.h"
#include "servo.h"
#include "uart.h"

uint16_t getBlackLine(uint8_t *image_fire, uint8_t threshold){

    uint8_t edgeCounter = 0; //表示连续的黑格子数目
    uint16_t leftEdge = 0, rightEdge = 0;
    bool leftEdgeFound = false, rightEdgeFound = false;
    for (uint16_t i = MT9V03X_W / 2 ; i <= MT9V03X_W ; ++i) {
        if(image_fire[100 * MT9V03X_W + i] >= threshold){
            ++edgeCounter;
        }else{
            edgeCounter = 0;
        }
        if(edgeCounter == 3){
            leftEdge = i;
            leftEdgeFound = true;
            break;
        }
    }
    edgeCounter = 0;
    for (uint16_t i = MT9V03X_W / 2 ; i >= 0 ; --i) {
        if(image_fire[100 * MT9V03X_W + i] >= threshold){
            ++edgeCounter;
        }else{
            edgeCounter = 0;
        }
        if(edgeCounter == 3){
            rightEdge = i;
            rightEdgeFound = true;
            break;
        }
    }
    return (leftEdge + rightEdge) >> 1;
}

uint8_t OTSUThershold(uint8_t **image){

    uint8_t threshold = 0, threshold_temp = 0;
    float_t variance = 0, variance_temp = 0;

    uint8_t background_counter, foreground_counter;
    uint32_t background_grayScale, foreground_grayscale;
    float_t background_rate, foreground_rate;
    float_t background_grayScale_average, foreground_grayscale_average;

    for(threshold_temp = 0 ; threshold_temp < UINT8_MAX ; ++threshold_temp){ // TODO:可以适当缩小阈值穷举范围
        background_counter = 0; foreground_counter = 0;
        background_grayScale = 0; foreground_grayscale = 0;
        for(uint16_t i = 0 ; i < MT9V03X_H ; ++i){
            for(uint16_t j = 0 ; j < MT9V03X_W ; ++j){
                if(image[i][j] >= threshold_temp){
                    foreground_grayscale += image[i][j];
                    ++foreground_counter;
                }else{
                    background_grayScale += image[i][j];
                    ++background_counter;
                }
            }
        }
        background_rate = (float_t)background_counter / MT9V03X_IMAGE_SIZE;
        foreground_rate = (float_t)foreground_counter / MT9V03X_IMAGE_SIZE;
        background_grayScale_average = (float_t)background_grayScale / MT9V03X_IMAGE_SIZE;
        foreground_grayscale_average = (float_t)foreground_grayscale / MT9V03X_IMAGE_SIZE;
        variance_temp = background_rate * foreground_rate * pow(background_grayScale_average - foreground_grayscale_average, 2);
        if(variance_temp > variance){
            variance = variance_temp;
            threshold = threshold_temp;
        }
    }

    return threshold;
}


int main(void)
{
    interrupt_global_disable();         // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    // 初始化摄像头
    mt9v03x_init();

    // 此处编写用户代码(例如：外设初始化代码等)
    //ADC初始化，例：adc_init(ADC_IN7_A7);

    // 初始化LED
    gpio_init(LED_1_PIN, GPO, 0, GPIO_PIN_CONFIG);

    // 初始化拨码开关
    gpio_init(SW_1_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(SW_2_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(SW_3_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(SW_4_PIN, GPI, 1, GPI_PULL_UP);

    // 初始化按钮与硬件中断
    gpio_init(BTN_1_PIN, GPI, 1, GPI_PULL_UP);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource6);
    EXTI_InitTypeDef EXIT_D6_INIT;
    EXIT_D6_INIT.EXTI_Line = EXTI_Line6;
    EXIT_D6_INIT.EXTI_Mode = EXTI_Mode_Interrupt;
    EXIT_D6_INIT.EXTI_Trigger = EXTI_Trigger_Falling;
    EXIT_D6_INIT.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXIT_D6_INIT);
    interrupt_set_priority(EXTI9_5_IRQn, 1); //?????TODO

    gpio_init(BTN_2_PIN, GPI, 1, GPI_PULL_UP);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource4);
    EXTI_InitTypeDef EXIT_D4_INIT;
    EXIT_D4_INIT.EXTI_Line = EXTI_Line4;
    EXIT_D4_INIT.EXTI_Mode = EXTI_Mode_Interrupt;
    EXIT_D4_INIT.EXTI_Trigger = EXTI_Trigger_Falling;
    EXIT_D4_INIT.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXIT_D4_INIT);
    interrupt_set_priority(EXTI9_5_IRQn, 1); //?????TODO

    interrupt_enable(EXTI9_5_IRQn);

    // 初始化蜂鸣器
    gpio_init(BEEP_PIN, GPO, 0, GPIO_PIN_CONFIG);

    // 初始化串口
    uart_init(UART_3, 9600, UART3_MAP0_TX_B10, UART3_MAP0_RX_B11);
    uart_rx_interrupt(UART_3, ENABLE);

    // 初始化电机与解码器
    Motor motor; initMotor(&motor, 10, 5, 2, 0);
    gpio_init(MOTOR_L_DIR_PIN, GPO, 0, GPIO_PIN_CONFIG); // 0代表后退
    gpio_init(MOTOR_R_DIR_PIN, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR_L_PWM_CHANNEL, 17000, 0);
    pwm_init(MOTOR_R_PWM_CHANNEL, 17000, 0);
    pwm_set_duty(MOTOR_L_PWM_CHANNEL, 0);
    pwm_set_duty(MOTOR_R_PWM_CHANNEL, 0);
    encoder_quad_init(TIM4_ENCOEDER, TIM4_ENCOEDER_MAP1_CH1_D12, TIM4_ENCOEDER_MAP1_CH2_D13);
    encoder_quad_init(TIM9_ENCOEDER, TIM9_ENCOEDER_MAP3_CH1_D9, TIM9_ENCOEDER_MAP3_CH2_D11);

    // 初始化舵机 TODO
    Servo servo; initServo(&servo, 10, 5, 2, 0, 250); // TODO:这个PWM靠谱吗?为什么只能朝一个方向转？
    pwm_init(SERVO_PWM_CHANNEL, 330, 250);
    pwm_set_duty(SERVO_PWM_CHANNEL, servo.pwm);


    // 初始化LCD
    tft180_set_dir(TFT180_CROSSWISE);
    tft180_init();
    tft180_show_string(0, 0, "mt9v03x init.");

    // 初始化定时中断



    // 大律法求摄像头阈值
    uint8_t threshold = OTSUThershold((uint8_t**)mt9v03x_image);

    interrupt_global_enable(0);          // 总中断最后开启
    while(1)
    {
        // 此处编写需要循环执行的代码

        motor.pid.measurement = (int32_t)encoder_get_count(TIM4_ENCOEDER);
        encoder_clear_count(TIM4_ENCOEDER);

        motor.direction = 0;
        motor.pwm = 1000;
//        __updateMotorRotation(&motor);
//        changeServoRotation(&servo, ASSIGN, 250);



//        lcd_show_gray_image(0, 0, image_fire, MT9V03X_DVP_W, MT9V03X_DVP_H, tft180_x_max, tft180_y_max, 0);
//        lcd_show_gray_image(0, 0, image_fire, MT9V03X_DVP_W, MT9V03X_DVP_H, MT9V03X_DVP_W, MT9V03X_DVP_H, 150);
//        tft180_show_int(0, 0, motor.pid.measurement, 8);
        //        tft180_show_int(0, 0, 123456, 8);
//        tft180_displayimage03x((uint8*)mt9v03x_image, 160, 128);
        if(mt9v03x_finish_flag)
        {
            tft180_displayimage03x((const uint8 *)mt9v03x_image, 160, 128);
//            tft180_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 160, 128, 0);
            mt9v03x_finish_flag = 0;
        }
//        tft180_show_gray_image(0, 0, (uint8*)mt9v03x_image, MT9V03X_W, MT9V03X_H, 160, 128, threshold);
//        if(mt9v03x_finish_flag == 1)
//        {
//            old_image_use_flag = image_use_flag; image_debug_flag
//             mt9v03x_finish_flag_dvp = 0;
//            //thershold_local = GetOSTU(image_fire);  //使用某一种办法获得阈值
//            //eight_neighbor(image_fire,thershold_local);//然后处理你的图像
//            if(old_image_use_flag != image_use_flag)
//            {
//              if(image_use_flag==1)//改变缓冲区
//              {
//                  image_fire=camera_buffer_addr2;
//              }
//              else if(image_use_flag==2)
//              {
//                  image_fire=camera_buffer_addr;
//              }
//            }
//            else                        //说明程序执行较快，此时下一场的场中断还未到
//            {
//              if(image_use_flag==1)//改变缓冲区
//              {
//                  image_fire=camera_buffer_addr;
//              }
//              else if(image_use_flag==2)
//              {
//                  image_fire=camera_buffer_addr2;
//              }
//            }
//        }
    }
}




