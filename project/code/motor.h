/*
 * motor.h
 *
 *  Created on: 2023Äê2ÔÂ10ÈÕ
 *      Author: Yaner
 */

#ifndef CODE_MOTOR_H_
#define CODE_MOTOR_H_

#include "zf_common_headfile.h"
#include "pid.h"

typedef struct Motor{
    PIDVariable pid;
    uint32_t pwm;
    uint8_t direction;
    gpio_pin_enum dirPin;
    pwm_channel_enum pwmChannel;
}Motor;

void __updateMotorRotation(Motor *motor);
void initMotor(Motor *motor,int32_t pCoef, int32_t iCoef, int32_t dCoef, int32_t target, gpio_pin_enum dirPin, pwm_channel_enum pwmChannel);
void changeMotorRotation(Motor *motor, MathOperation operation, uint32_t offset);
void updateMotorPID(Motor *motor);

#endif /* CODE_MOTOR_H_ */
