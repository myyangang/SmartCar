/*
 * define.h
 *
 *  Created on: 2021��11��29��
 *      Author: Aphrodite Chaser
 */
/*
 * ע
 * ��
 * #define
 * ��
 * ʱ
 * ��
 * ��
 * ��
 * ��
 * ��
 * ��
 * ��
 * ��
 * ��
 * ��
 * ��
 * */
#include "zf_common_headfile.h"
#ifndef _DEFINE_H_
#define _DEFINE_H_

extern int temp_int;


extern uint8_t image_debug[MT9V03X_H][MT9V03X_W/8],image_debug_flag,threshold_now;//debugͼ�����ڵ�����

//adc
extern unsigned int adc_common[8], adc_L,adc_R, voltage_battery;

//����ͷ
enum StatusOfCircleFlagInOrOutMagnet{MagnetNull, MagnetFind};               //MagnetNullΪδ���ֵ���źţ�MagnetFindΪ���ֵ���ź�
enum StatusOfCircleFlagDirection{CircleNull,CircleLeft, CircleRight};       //CircleNullΪΪ�жϳ�����CircleLeftΪ�󻷣�CircleRightΪ�һ�
enum StatusOfCircleFlagRepairLine{RepairNull, RepairStart, RepairOver};     //RepairNullΪδ��ʼ���ߣ�RepairStartΪ��ʼ���ߣ�RepairOverΪ�������
enum StatusOfCircleFlagFixSteer{FixNull, FixStart, FixOver};                //FixNullΪδ�̶���ǣ�FixStartΪ��ʼ�̶���ǣ�FixOverΪ�̶������ɣ���ʼ����ѭ��
enum StatusOfCircleFlagPermmitFind{NoPermit, DoPermit};                     //NoPermitΪ�������ֻ�����DoPermitΪ�����ֻ���

typedef struct{
    enum StatusOfCircleFlagInOrOutMagnet    inMagnet;       //�뻷��ŷ��ֱ�־λ�����ֺ�ʼ�뻷
    enum StatusOfCircleFlagDirection        direction;      //���������־λ
    enum StatusOfCircleFlagRepairLine       repairLine;     //�뻷���߱�־λ
    enum StatusOfCircleFlagFixSteer         fixSteer;       //�����̶���Ǳ�־λ
    enum StatusOfCircleFlagInOrOutMagnet    outMagnet;      //������ŷ��ֱ�־λ
    enum StatusOfCircleFlagPermmitFind      permitFind;     //����ʼ��ŷ��ֱ�־λ
}CIRCLE_FLAG;       //������־λ�ṹ��

extern int frame,fream_count;
extern CIRCLE_FLAG circleFlag;
extern unsigned char cricle_out_count;
extern float cricle_angle_in,cricle_angle_out,cricle_delta_angle;
extern unsigned char sancha_flag,sancha_last_flag,sancha_in,right_find_flag,left_find_flag,distance_flag,sancha_allow,car_status;
extern float sancha_angle_in,sancha_angle_out,sancha_delta_angle;
extern float carport_angle_in,carport_angle_out,carport_delta_angle;
//����
extern unsigned char cheku_flag,cheku_in_flag,cheku_next_can_flag,carport_flag,carport_in_flag,carport_fix_flag,in_carport_way;
extern float cheku_angle_in,cheku_angle_out,cheku_delta_angle;
extern int cheku_distance;
//�µ�
extern unsigned char podao,podao_count,podao_yisi,baodi_flag,one_sancha_flag;
extern int Gyr_rad_Y_last,Gyr_rad_Y_count;
extern int Speedtemp;
extern uint8_t slow_flag;
extern int pid_normal,pid_near,podao_up,podao_down,podao_diff,left_adding,right_adding;
//���־���
#define SEND_ENABLE A7
extern int cricle_or_carport_distance,distance,tiaoshi_distance,cricle_distance,sudo,sudo2,sudo3,sudo4;

//ͨ��
extern unsigned char send_cricle_flag,send_cheku_flag,send_chuku_flag,send_ceju_flag,send_require;

//����
extern int sancha_distance;
#define SANCHA_DISTANCE_LIMIT 22000 //��������룬���������һ����ȥ
#define SANCHA_ADC_DOWN_LIMIT 1100  //����������ADCֵ��С�����ֵ������ȫ����������Խ��
#define SANCHA_ADC_UP_LIMIT 1800    //��������ADCֵ���������ֵ�������������ˣ����Խ��

// ��������
#define LED_1_PIN E2
#define BTN_1_PIN D6
#define BTN_2_PIN D4
#define SW_1_PIN B0
#define SW_2_PIN B7
#define SW_3_PIN E0
#define SW_4_PIN E1
#define BEEP_PIN D15
#define MOTOR_L_PWM_CHANNEL TIM10_PWM_MAP3_CH1_D1
#define MOTOR_R_PWM_CHANNEL TIM10_PWM_MAP3_CH3_D5
#define MOTOR_L_DIR_PIN C13
#define MOTOR_R_DIR_PIN A15
#define CAMERA_OUT_1 A9
#define CAMERA_OUT_2 A10
#define CAMERA_OUT_3 C8
#define CAMERA_OUT_4 C9
#define CAMERA_OUT_5 C11
#define CAMERA_OUT_6 B6
#define CAMERA_OUT_7 B8
#define CAMERA_OUT_8 B9
#define CAMERA_PCLK A6
#define CAMERA_TXD D2
#define CAMERA_RXD C12
#define CAMERA_HREF A4
#define CAMERA_HSYNC A5 // TODO
#define CAMERA_VSYNC A5 // TODO

#define SERVO_PWM_CHANNEL TIM2_PWM_MAP1_CH2_B3 // TODO:



typedef enum{
    PLUS, MINUS, ASSIGN, OPPOSE
}MathOperation;

#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))

#endif /* USER_DEFINE_H_ */
