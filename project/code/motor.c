/*
 * motor.c
 *
 *  Created on: 2023��2��10��
 *      Author: Yaner
 */
#include "motor.h"


void __updateMotorRotation(Motor *motor){

    if(motor->pwm > MOTOR_PWM_MAX){
        gpio_set_level(BEEP_PIN, 1);
    }

    pwm_set_duty(motor->pwmChannel, (motor->direction) ? (MOTOR_PWM_MAX - motor->pwm) : motor->pwm);
    gpio_set_level(motor->dirPin, motor->direction);

}

void initMotor(Motor *motor,int32_t pCoef, int32_t iCoef, int32_t dCoef, int32_t target, gpio_pin_enum dirPin, pwm_channel_enum pwmChannel){
    initPID(&(motor->pid), pCoef, iCoef, dCoef, target);
    motor->direction = 0;
    motor->pwm = 0;
    motor->dirPin = dirPin;
    motor->pwmChannel = pwmChannel;
    __updateMotorRotation(motor);
}

void changeMotorRotation(Motor *motor, MathOperation operation, uint32_t offset){

    if(operation == PLUS){ // ���Ҫ��������ٶ�
        if(motor->direction == 1){ // �����ʱ����Ϊ��
            motor->pwm = min(motor->pwm + offset, MOTOR_PWM_MAX); // TODO:PWM_DUTY_MAX�����ĳ���9000�����Ҷ����һ�����PWN���ֵ
        }else if(motor->direction == 0){ // �����ʱ����Ϊ��
            motor->direction = (offset >= motor->pwm);
            motor->pwm = (motor->direction) ? min(offset - motor->pwm, MOTOR_PWM_MAX) : motor->pwm - offset;
        }
    }else if(operation == MINUS){ // ���Ҫ��������ٶ�
        if(motor->direction == 1){ // �����ʱ����Ϊ��
            motor->direction = (motor->pwm >= offset);
            motor->pwm = (motor->direction) ? (motor->pwm - offset) : min(offset - motor->pwm, MOTOR_PWM_MAX);
        }else if(motor->direction == 0){ // �����ʱ����Ϊ��
            motor->pwm = min(motor->pwm + offset, MOTOR_PWM_MAX);
        }
    }else if(operation == ASSIGN){
        motor->pwm = min(offset, MOTOR_PWM_MAX);
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

