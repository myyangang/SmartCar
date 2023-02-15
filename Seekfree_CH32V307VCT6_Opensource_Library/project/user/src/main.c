/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             main
* @company          �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
* @version          �鿴doc��version�ļ� �汾˵��
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/



#include "zf_common_headfile.h"

#include "motor.h"
#include "servo.h"
#include "uart.h"

uint8_t OTSUThershold(uint8_t **image){

    uint8_t threshold = 0, threshold_temp = 0;
    float_t variance = 0, variance_temp = 0;

    uint8_t background_counter, foreground_counter;
    uint32_t background_grayScale, foreground_grayscale;
    float_t background_rate, foreground_rate;
    float_t background_grayScale_average, foreground_grayscale_average;

    for(threshold_temp = 0 ; threshold_temp < UINT8_MAX ; ++threshold_temp){ // TODO:�����ʵ���С��ֵ��ٷ�Χ
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
    interrupt_global_disable();         // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

        mt9v03x_init();//����ͷ��ʼ��
// �˴���д�û�����(���磺�����ʼ�������)
    //ADC��ʼ��������adc_init(ADC_IN7_A7);

    // ��ʼ��LED
    gpio_init(LED_1_PIN, GPO, 0, GPIO_PIN_CONFIG);

    // ��ʼ�����뿪��
    gpio_init(SW_1_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(SW_2_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(SW_3_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(SW_4_PIN, GPI, 1, GPI_PULL_UP);

    // ��ʼ����ť��Ӳ���ж�
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

    // ��ʼ��������
    gpio_init(BEEP_PIN, GPO, 0, GPIO_PIN_CONFIG);

    // ��ʼ������
    uart_init(UART_3, 9600, UART3_MAP0_TX_B10, UART3_MAP0_RX_B11);
    uart_rx_interrupt(UART_3, ENABLE);

    // ��ʼ������������
    Motor motor; initMotor(&motor, 10, 5, 2, 0);
    gpio_init(MOTOR_L_DIR_PIN, GPO, 0, GPIO_PIN_CONFIG); // 0�������
    gpio_init(MOTOR_R_DIR_PIN, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR_L_PWM_CHANNEL, 17000, 0);
    pwm_init(MOTOR_R_PWM_CHANNEL, 17000, 0);
    pwm_set_duty(MOTOR_L_PWM_CHANNEL, 0);
    pwm_set_duty(MOTOR_R_PWM_CHANNEL, 0);
    encoder_quad_init(TIM4_ENCOEDER, TIM4_ENCOEDER_MAP1_CH1_D12, TIM4_ENCOEDER_MAP1_CH2_D13);
    encoder_quad_init(TIM9_ENCOEDER, TIM9_ENCOEDER_MAP3_CH1_D9, TIM9_ENCOEDER_MAP3_CH2_D11);

    // ��ʼ����� TODO
    Servo servo; initServo(&servo, 10, 5, 2, 0, 250); // TODO:���PWM������
    pwm_init(SERVO_PWM_CHANNEL, 50, 250);
    pwm_set_duty(SERVO_PWM_CHANNEL, 250);


    // ��ʼ��LCD
    tft180_init();

    // ��ʼ����ʱ�ж�

    // ��ʼ������ͷ
//    dvp_gpio_init(
//            CAMERA_OUT_1, CAMERA_OUT_2, CAMERA_OUT_3, CAMERA_OUT_4,
//            CAMERA_OUT_5, CAMERA_OUT_6, CAMERA_OUT_7, CAMERA_OUT_8,
//            CAMERA_PCLK, MT9V03X_VSYNC_PIN_DVP, MT9V03X_HSYNC_PIN_DVP // TODO:??? VSYNC
//    );

    // ���ɷ�������ͷ��ֵ
    OTSUThershold((uint8_t**)mt9v03x_image);

    interrupt_global_enable(0);          // ���ж������
    while(1)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���

        motor.pid.measurement = (int32_t)encoder_get_count(TIM4_ENCOEDER);
        encoder_clear_count(TIM4_ENCOEDER);

        motor.direction = 0;
        motor.pwm = 0;

        changeServoRotation(&servo, ASSIGN, 3250);
        __updateServoRotation(&servo);

        __updateMotorRotation(&motor);

//        lcd_show_gray_image(0, 0, image_fire, MT9V03X_DVP_W, MT9V03X_DVP_H, tft180_x_max, tft180_y_max, 0);
//        lcd_show_gray_image(0, 0, image_fire, MT9V03X_DVP_W, MT9V03X_DVP_H, MT9V03X_DVP_W, MT9V03X_DVP_H, 150);
//        tft180_show_int(0, 0, 123456, 8);
        tft180_displayimage03x((const uint8 *)mt9v03x_image, 160, 128);
//        if(mt9v03x_finish_flag == 1)
//        {
//            old_image_use_flag = image_use_flag; image_debug_flag
//             mt9v03x_finish_flag_dvp = 0;
//            //thershold_local = GetOSTU(image_fire);  //ʹ��ĳһ�ְ취�����ֵ
//            //eight_neighbor(image_fire,thershold_local);//Ȼ�������ͼ��
//            if(old_image_use_flag != image_use_flag)
//            {
//              if(image_use_flag==1)//�ı仺����
//              {
//                  image_fire=camera_buffer_addr2;
//              }
//              else if(image_use_flag==2)
//              {
//                  image_fire=camera_buffer_addr;
//              }
//            }
//            else                        //˵������ִ�нϿ죬��ʱ��һ���ĳ��жϻ�δ��
//            {
//              if(image_use_flag==1)//�ı仺����
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




