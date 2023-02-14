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

int main(void)
{
    interrupt_disable_all();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    //    mt9v03x_init_dvp();//����ͷ��ʼ��
// �˴���д�û�����(���磺�����ʼ�������)
    //ADC��ʼ��������adc_init(ADC_IN7_A7);


    gpio_init(LED_1_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(BEEP_PIN, GPO, 1, GPIO_PIN_CONFIG);
    system_delay_ms(500);
    gpio_set_level(BEEP_PIN, 0);

    interrupt_enable_all(0);            // ���ж������
    while(1)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���

        gpio_set_level(LED_1_PIN, 1);

        if(mt9v03x_finish_flag_dvp == 1)
        {
            old_image_use_flag = image_use_flag;
             mt9v03x_finish_flag_dvp = 0;
            //thershold_local = GetOSTU(image_fire);  //ʹ��ĳһ�ְ취�����ֵ
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
    }
}




