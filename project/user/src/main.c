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

int32_t getBlackLine(uint8_t image[MT9V03X_DVP_H][MT9V03X_DVP_W], uint8_t threshold){ // ִ��һ����Ҫ23ms

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

    for(threshold_temp = 0 ; threshold_temp < UINT8_MAX ; threshold_temp += 1){ // TODO:�����ʵ���С��ֵ��ٷ�Χ������Ԥ��ÿ�μ�2ʱ������޷����� < UINT8_MAX������ѭ��
        background_counter = 0; foreground_counter = 0;
        background_grayScale = 0; foreground_grayscale = 0;
        lcd_showuint8_simspi(0, 0, threshold_temp);
        for(int16_t i = 0 ; i < MT9V03X_DVP_H ; i += 2){ // TODO:�����Ż��ȼ�
            for(int16_t j = 0 ; j < MT9V03X_DVP_W ; j += 2){ // TODO:�����Ż��ȼ�
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
    double OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��;
    unsigned char MinValue, MaxValue;
    unsigned char Threshold = 0;
    unsigned int HistoGram[256];              //

    for (j = 0; j < 256; j++)  HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ

    for (j = 0; j < MT9V03X_DVP_H; j+=4)
    {
        for (i = 0; i < MT9V03X_DVP_W; i+=4)
        {
            HistoGram[*(tmImage+j*MT9V03X_DVP_W+i)]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //��ȡ��С�Ҷȵ�ֵ
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //��ȡ���Ҷȵ�ֵ

    Amount = MT9V03X_DVP_W *MT9V03X_DVP_H/16;
    PixelIntegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        PixelIntegral += HistoGram[j] * j;//�Ҷ�ֵ����
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];   //ǰ�����ص���
        PixelFore = Amount - PixelBack;         //�������ص���
        OmegaBack = (float)PixelBack / Amount;  //ǰ�����ذٷֱ�
        OmegaFore = (float)PixelFore / Amount;  //�������ذٷֱ�
        PixelIntegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
        PixelIntegralFore = PixelIntegral - PixelIntegralBack;  //�����Ҷ�ֵ
        MicroBack = (float)PixelIntegralBack / PixelBack;       //ǰ���ҶȰٷֱ�
        MicroFore = (float)PixelIntegralFore / PixelFore;       //�����ҶȰٷֱ�
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//������䷽��
        if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //���������ֵ;
}


int main(void)
{
    interrupt_disable_all();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    // ��ʼ������ͷ
    mt9v03x_init_dvp();

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
    uart_init(UART_3, 115200, UART3_TX_B10, UART3_RX_B11);
    uart_rx_interrupt(UART_3, ENABLE);

    // ��ʼ������������
//    initMotor(&motorLeft, 53, 5, 4, 0, MOTOR_L_DIR_PIN, MOTOR_L_PWM_CHANNEL);
//    initMotor(&motorRight, 72, 2, 10, 0, MOTOR_R_DIR_PIN, MOTOR_R_PWM_CHANNEL); // TODO:900תʱ������Ϊ����
//    gpio_init(MOTOR_L_DIR_PIN, GPO, 0, GPIO_PIN_CONFIG); // 0�������
//    gpio_init(MOTOR_R_DIR_PIN, GPO, 0, GPIO_PIN_CONFIG);
//    pwm_init(MOTOR_L_PWM_CHANNEL, 17000, 0);
//    pwm_init(MOTOR_R_PWM_CHANNEL, 17000, 0);
//    pwm_set_duty(MOTOR_L_PWM_CHANNEL, 0);
//    pwm_set_duty(MOTOR_R_PWM_CHANNEL, 0);
//    encoder_init_quad(TIM4_ENCOEDER, TIM4_CH1_ENCOEDER_D12, TIM4_CH2_ENCOEDER_D13);
//    encoder_init_quad(TIM9_ENCOEDER, TIM9_CH1_ENCOEDER_D9, TIM9_CH2_ENCOEDER_D11);
//    encoder_clean_count(TIM4_ENCOEDER);
//    encoder_clean_count(TIM9_ENCOEDER);
    //    encoder_init_quad(TIM9_ENCOEDER, TIM9_CH2_ENCOEDER_D11, TIM9_CH1_ENCOEDER_D9); // ����ʾ�����Ͻ�������������ͨ�����������ֵ��Ϊ0�������෴����

    // ��ʼ�����
//    initServo(&servo, 45, 4, 2, 0, SERVO_PWM_ACTUAL_MIDDLE); // ����������
//    pwm_init(SERVO_PWM_CHANNEL, 330, SERVO_PWM_ACTUAL_MIDDLE);
//    pwm_set_duty(SERVO_PWM_CHANNEL, servo.pwm);

    // ��ʼ��LCD
    lcd_init_simspi();

    // ��ʼ����ʱ�ж�
    pit_init_ms(TIM1_PIT, 10);

    // ��ʼ������ͷ
    mt9v03x_init_dvp();

//    uint8_t threshold = OTSUThershold(mt9v03x_image_dvp);
    uint8_t threshold = GetOSTU(image_fire);

    int16_t benchmarkCounter = 0;
    int32_t result = 0;

    interrupt_enable_all(0);            // ���ж������
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
//            thershold_local = GetOSTU(image_fire);  //ʹ��ĳһ�ְ취�����ֵ
            //eight_neighbor(image_fire,thershold_local);//Ȼ�������ͼ��

            if(old_image_use_flag != image_use_flag)
            {
              if(image_use_flag==1)//�ı仺����
              {
                  image_fire=camera_buffer_addr2;
              }
              else if(image_use_flag==2)
              {
                  image_fire=camera_buffer_addr;
              }
            }
            else                        //˵������ִ�нϿ죬��ʱ��һ���ĳ��жϻ�δ��
            {
              if(image_use_flag==1)//�ı仺����
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




