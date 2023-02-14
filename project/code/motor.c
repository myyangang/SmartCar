/*
 * motor.c
 *
 *  Created on: 2023��2��10��
 *      Author: Yaner
 */
#include "motor.h"


void __updateMotorRotation(Motor *motor){
    pwm_set_duty(MOTOR_PWM_CHANNEL, motor->pwm);
    gpio_set_level(MOTOR_DIR_PIN, motor->direction);
}

void initMotor(Motor *motor,int32_t pCoef, int32_t iCoef, int32_t dCoef, int32_t target){
    initPID(&(motor->pid), pCoef, iCoef, dCoef, target);
    motor->direction = 0;
    motor->pwm = 0;
    __updateMotorRotation(motor);
}

void changeMotorRotation(Motor *motor, MathOperation operation, uint32_t offset){

    if(operation == PLUS){ // ���Ҫ��������ٶ�
        if(motor->direction == 1){ // �����ʱ����Ϊ��
            motor->pwm = min(motor->pwm + offset, PWM_DUTY_MAX); // TODO:PWM_DUTY_MAX�����ĳ���9000�����Ҷ����һ�����PWN���ֵ
        }else if(motor->direction == 0){ // �����ʱ����Ϊ��
            motor->direction = (offset >= motor->pwm);
            motor->pwm = (motor->direction) ? min(offset - motor->pwm, PWM_DUTY_MAX) : motor->pwm - offset;
        }
    }else if(operation == MINUS){ // ���Ҫ��������ٶ�
        if(motor->direction == 1){ // �����ʱ����Ϊ��
            motor->direction = (motor->pwm >= offset);
            motor->pwm = (motor->direction) ? motor->pwm - offset : min(offset - motor->pwm, PWM_DUTY_MAX);
        }else if(motor->direction == 0){ // �����ʱ����Ϊ��
            motor->pwm = min(motor->pwm + offset, PWM_DUTY_MAX);
        }
    }else if(operation == ASSIGN){
        motor->pwm = max(offset, PWM_DUTY_MAX);
    }else if(operation == OPPOSE){
        motor->direction = !(motor->direction);
    }

    __updateMotorRotation(motor);

}


void updateMotorPID(Motor *motor){

    int32_t deltaOutput = updatePID(&(motor->pid));
    if(deltaOutput >= 0){
        changeMotorRotation(motor, PLUS, (uint32_t)deltaOutput);
    }else{
        changeMotorRotation(motor, MINUS, (uint32_t)(-deltaOutput));
    }

}

