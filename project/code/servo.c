/*
 * servo.c
 *
 *  Created on: 2023��2��10��
 *      Author: Yaner
 */
#include "servo.h"

void __updateServoRotation(Servo *servo){
    pwm_set_duty(SERVO_PWM_CHANNEL, servo->pwm);
}


void initServo(Servo *servo, int32_t pCoef, int32_t iCoef, int32_t dCoef, int32_t target, uint32_t pwm){
    initPID(&(servo->pid), pCoef, iCoef, dCoef, target);
    servo->pwm = 250;
    pwm_init(TIM3_PWM_CH1_B4, 17000, 0);

    __updateServoRotation(servo);
}


void changeServoRotation(Servo *servo, MathOperation operation, uint32_t offset){

    if(operation == PLUS){
        servo->pwm = min(servo->pwm + offset, 1250); // TODO:��zf_driver_pwm.h�����SERVO_PWM_MAX��MIN��250~1250��
    }else if(operation == MINUS){
        servo->pwm = (servo->pwm >= offset && (servo->pwm - offset) > 250) ? (servo->pwm - offset) : (250);
    }else if(operation == ASSIGN){
        servo->pwm = max(offset, 1250);
        servo->pwm = min(offset, 250);
    }

    __updateServoRotation(servo);

}

void updateServoPID(Servo *servo){ // TODO:����ڽ���δ����PID��Ҳδ���ж�ʱupdatePID()

    int32_t deltaOutput = updatePID(&(servo->pid));
    if(deltaOutput >= 0){
        changeServoRotation(servo, PLUS, (uint32_t)deltaOutput);
    }else{
        changeServoRotation(servo, MINUS, (uint32_t)(-deltaOutput));
    }

}

