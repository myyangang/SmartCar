/*
 * define.h
 *
 *  Created on: 2021年11月29日
 *      Author: Aphrodite Chaser
 */
/*
 * 注
 * 意
 * #define
 * 的
 * 时
 * 候
 * 变
 * 量
 * 两
 * 边
 * 加
 * 括
 * 号
 * ！
 * ！
 * ！
 * */
#include "zf_common_headfile.h"
#ifndef _DEFINE_H_
#define _DEFINE_H_

extern int temp_int;


extern uint8_t image_debug[MT9V03X_DVP_H][MT9V03X_DVP_W/8],image_debug_flag,threshold_now;//debug图像，用于调试误触
//adc
extern unsigned int adc_common[8], adc_L,adc_R, voltage_battery;

//按键拨码
#define sw1 D0
#define sw2 D1
#define sw3 D3
#define sw4 D4
#define BUT1 E4
#define BUT2 E3
//蜂鸣器
#define BEEP E10
//语音模块
#define VOICE1 C4
#define VOICE2 B0
#define VOICE3 B1

//LED
//#define LED1 E2
#define DIST_MIN 200
//摄像头
enum StatusOfCircleFlagInOrOutMagnet{MagnetNull, MagnetFind};               //MagnetNull为未发现电磁信号，MagnetFind为发现电磁信号
enum StatusOfCircleFlagDirection{CircleNull,CircleLeft, CircleRight};       //CircleNull为为判断出方向，CircleLeft为左环，CircleRight为右环
enum StatusOfCircleFlagRepairLine{RepairNull, RepairStart, RepairOver};     //RepairNull为未开始补线，RepairStart为开始补线，RepairOver为补线完成
enum StatusOfCircleFlagFixSteer{FixNull, FixStart, FixOver};                //FixNull为未固定打角，FixStart为开始固定打角，FixOver为固定打角完成，开始正常循迹
enum StatusOfCircleFlagPermmitFind{NoPermit, DoPermit};                     //NoPermit为不允许发现环岛，DoPermit为允许发现环岛

typedef struct{
    enum StatusOfCircleFlagInOrOutMagnet    inMagnet;       //入环电磁发现标志位，发现后开始入环
    enum StatusOfCircleFlagDirection        direction;      //环岛方向标志位
    enum StatusOfCircleFlagRepairLine       repairLine;     //入环补线标志位
    enum StatusOfCircleFlagFixSteer         fixSteer;       //出环固定打角标志位
    enum StatusOfCircleFlagInOrOutMagnet    outMagnet;      //出环电磁发现标志位
    enum StatusOfCircleFlagPermmitFind      permitFind;     //允许开始电磁发现标志位
}CIRCLE_FLAG;       //环岛标志位结构体

extern int frame,fream_count;
extern CIRCLE_FLAG circleFlag;
extern unsigned char cricle_out_count;
extern float cricle_angle_in,cricle_angle_out,cricle_delta_angle;
extern unsigned char sancha_flag,sancha_last_flag,sancha_in,right_find_flag,left_find_flag,distance_flag,sancha_allow,car_status;
extern float sancha_angle_in,sancha_angle_out,sancha_delta_angle;
extern float carport_angle_in,carport_angle_out,carport_delta_angle;
//车库
extern unsigned char cheku_flag,cheku_in_flag,cheku_next_can_flag,carport_flag,carport_in_flag,carport_fix_flag,in_carport_way;
extern float cheku_angle_in,cheku_angle_out,cheku_delta_angle;
extern int cheku_distance;
//坡道
extern unsigned char podao,podao_count,podao_yisi,baodi_flag,one_sancha_flag;
extern int Gyr_rad_Y_last,Gyr_rad_Y_count;
extern int Speedtemp;
extern uint8_t slow_flag;
extern int pid_normal,pid_near,podao_up,podao_down,podao_diff,left_adding,right_adding;
//各种距离
#define SEND_ENABLE A7
extern int cricle_or_carport_distance,distance,tiaoshi_distance,cricle_distance,sudo,sudo2,sudo3,sudo4;

//通信
extern unsigned char send_cricle_flag,send_cheku_flag,send_chuku_flag,send_ceju_flag,send_require;

//三叉
extern int sancha_distance;
#define SANCHA_DISTANCE_LIMIT 22000 //出三叉距离，超过这个就一定出去
#define SANCHA_ADC_DOWN_LIMIT 1100  //入三叉解除的ADC值，小于这个值代表完全进入三叉可以解除
#define SANCHA_ADC_UP_LIMIT 1800    //出三叉解除ADC值，大于这个值代表在三叉外了，可以解除



#endif /* USER_DEFINE_H_ */
