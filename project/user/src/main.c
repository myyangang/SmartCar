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

Motor motor, motorLeft, motorRight;
Servo servo;

int16_t leftEdgeList[CAMERA_HEIGHT];
bool isLeftEdgeFound[CAMERA_HEIGHT];
bool isLeftEdgeMutated = false;

int16_t rightEdgeList[CAMERA_HEIGHT];
bool isRightEdgeFound[CAMERA_HEIGHT];
bool isRightEdgeMutated = false;

int16_t middleLineList[CAMERA_HEIGHT];

bool isBottomEdgeFound = false;
int16_t validMiddleLineCounter = 0;
int32_t measurement = 0;
int16_t allowLineAdd = 20;
int16_t searchStart = 0;

int32_t getBlackLine(uint8_t image[MT9V03X_DVP_H][MT9V03X_DVP_W], uint8_t threshold){ // 执行一次需要23ms

    isLeftEdgeMutated = false;
    isRightEdgeMutated = false;
    isBottomEdgeFound = false;
    measurement = 0;
    allowLineAdd = 20;
    searchStart = 0;

    for(int16_t i = 1 ; i < CAMERA_WIDTH - 2 ; CAMERA_WIDTH / 5){
        ;
    }
}
uint8_t OTSUThershold(uint8_t image[MT9V03X_DVP_H][MT9V03X_DVP_W]){

    uint8_t threshold = 0, threshold_temp = 0;
    float_t variance = 0, variance_temp = 0;

    uint32_t background_counter, foreground_counter;
    uint32_t background_grayScale, foreground_grayscale;
    float_t background_rate, foreground_rate;
    float_t background_grayScale_average, foreground_grayscale_average;

    for(threshold_temp = 0 ; threshold_temp < UINT8_MAX ; threshold_temp += 1){ // TODO:可以适当缩小阈值穷举范围，警惕预置每次加2时溢出，无法满足 < UINT8_MAX导致死循环
        background_counter = 0; foreground_counter = 0;
        background_grayScale = 0; foreground_grayscale = 0;
        lcd_showuint8_simspi(0, 0, threshold_temp);
        for(int16_t i = 0 ; i < MT9V03X_DVP_H ; i += 2){ // TODO:调整优化等级
            for(int16_t j = 0 ; j < MT9V03X_DVP_W ; j += 2){ // TODO:调整优化等级
                if(image[i][j] >= threshold_temp){
                    foreground_grayscale += image[i][j];
                    ++foreground_counter;
                }else{
                    background_grayScale += image[i][j];
                    ++background_counter;
                }
            }
        }
        background_rate = (float_t)background_counter / MT9V03X_IMAGE_SIZE_DVP;
        foreground_rate = (float_t)foreground_counter / MT9V03X_IMAGE_SIZE_DVP;
        background_grayScale_average = (float_t)background_grayScale / MT9V03X_IMAGE_SIZE_DVP;
        foreground_grayscale_average = (float_t)foreground_grayscale / MT9V03X_IMAGE_SIZE_DVP;
        variance_temp = background_rate * foreground_rate * pow(background_grayScale_average - foreground_grayscale_average, 2);
        if(variance_temp > variance){
            variance = variance_temp;
            threshold = threshold_temp;
        }
    }

    return threshold;
}

int GetOSTU(unsigned char *tmImage)
{
    unsigned int i,j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelIntegralBack = 0;
    unsigned long PixelIntegral = 0;
    signed long PixelIntegralFore = 0;
    signed long PixelFore = 0;
    double OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    unsigned char MinValue, MaxValue;
    unsigned char Threshold = 0;
    unsigned int HistoGram[256];              //

    for (j = 0; j < 256; j++)  HistoGram[j] = 0; //初始化灰度直方图

    for (j = 0; j < MT9V03X_DVP_H; j+=4)
    {
        for (i = 0; i < MT9V03X_DVP_W; i+=4)
        {
            HistoGram[*(tmImage+j*MT9V03X_DVP_W+i)]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //获取最大灰度的值

    Amount = MT9V03X_DVP_W *MT9V03X_DVP_H/16;
    PixelIntegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        PixelIntegral += HistoGram[j] * j;//灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];   //前景像素点数
        PixelFore = Amount - PixelBack;         //背景像素点数
        OmegaBack = (float)PixelBack / Amount;  //前景像素百分比
        OmegaFore = (float)PixelFore / Amount;  //背景像素百分比
        PixelIntegralBack += HistoGram[j] * j;  //前景灰度值
        PixelIntegralFore = PixelIntegral - PixelIntegralBack;  //背景灰度值
        MicroBack = (float)PixelIntegralBack / PixelBack;       //前景灰度百分比
        MicroFore = (float)PixelIntegralFore / PixelFore;       //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//计算类间方差
        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}


int main(void)
{
    interrupt_disable_all();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    // 初始化摄像头
    mt9v03x_init_dvp();

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
    uart_init(UART_3, 115200, UART3_TX_B10, UART3_RX_B11);
    uart_rx_interrupt(UART_3, ENABLE);

    // 初始化电机与解码器
//    initMotor(&motorLeft, 53, 5, 4, 0, MOTOR_L_DIR_PIN, MOTOR_L_PWM_CHANNEL);
//    initMotor(&motorRight, 72, 2, 10, 0, MOTOR_R_DIR_PIN, MOTOR_R_PWM_CHANNEL); // TODO:900转时抖动较为明显
//    gpio_init(MOTOR_L_DIR_PIN, GPO, 0, GPIO_PIN_CONFIG); // 0代表后退
//    gpio_init(MOTOR_R_DIR_PIN, GPO, 0, GPIO_PIN_CONFIG);
//    pwm_init(MOTOR_L_PWM_CHANNEL, 17000, 0);
//    pwm_init(MOTOR_R_PWM_CHANNEL, 17000, 0);
//    pwm_set_duty(MOTOR_L_PWM_CHANNEL, 0);
//    pwm_set_duty(MOTOR_R_PWM_CHANNEL, 0);
//    encoder_init_quad(TIM4_ENCOEDER, TIM4_CH1_ENCOEDER_D12, TIM4_CH2_ENCOEDER_D13);
//    encoder_init_quad(TIM9_ENCOEDER, TIM9_CH1_ENCOEDER_D9, TIM9_CH2_ENCOEDER_D11);
//    encoder_clean_count(TIM4_ENCOEDER);
//    encoder_clean_count(TIM9_ENCOEDER);
    //    encoder_init_quad(TIM9_ENCOEDER, TIM9_CH2_ENCOEDER_D11, TIM9_CH1_ENCOEDER_D9); // 错误示例：严禁交换两个测速通道，否则测量值恒为0而不是相反数！

    // 初始化舵机
//    initServo(&servo, 45, 4, 2, 0, SERVO_PWM_ACTUAL_MIDDLE); // 完美比例！
//    pwm_init(SERVO_PWM_CHANNEL, 330, SERVO_PWM_ACTUAL_MIDDLE);
//    pwm_set_duty(SERVO_PWM_CHANNEL, servo.pwm);

    // 初始化LCD
    lcd_init_simspi();

    // 初始化定时中断
    pit_init_ms(TIM1_PIT, 10);

    // 初始化摄像头
    mt9v03x_init_dvp();

//    uint8_t threshold = OTSUThershold(mt9v03x_image_dvp);
    uint8_t threshold = GetOSTU(image_fire);

    int16_t benchmarkCounter = 0;
    int32_t result = 0;

    interrupt_enable_all(0);            // 总中断最后开启
    while(1)
    {

//        lcd_show_gray_image(0, 0, image_fire, MT9V03X_DVP_W, MT9V03X_DVP_H, MT9V03X_DVP_W, MT9V03X_DVP_H, 30);
//        lcd_showint8_simspi(0, 0, 127);

//        result = getBlackLine(image_fire, 100);
//        benchmarkCounter++;
//        lcd_showint16_simspi(0, 0, benchmarkCounter);

        if(mt9v03x_finish_flag_dvp == 1){
            old_image_use_flag = image_use_flag;
             mt9v03x_finish_flag_dvp = 0;

             threshold = GetOSTU(image_fire);
//            thershold_local = GetOSTU(image_fire);  //使用某一种办法获得阈值
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
        lcd_show_gray_image(0, 0, image_fire, MT9V03X_DVP_W, MT9V03X_DVP_H, MT9V03X_DVP_W, MT9V03X_DVP_H, threshold);
        lcd_showint16_simspi(0, 0, getBlackLine(image_fire, threshold));
    }
}




