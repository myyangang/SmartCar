/*
 * servo.h
 *
 *  Created on: 2023Äê2ÔÂ10ÈÕ
 *      Author: Yaner
 */

#ifndef CODE_SERVO_H_
#define CODE_SERVO_H_

#include "zf_common_headfile.h"
#include "pid.h"

typedef struct Servo{
    PIDVariable pid;
    uint32_t pwm;
}Servo;

void __updateServoRotation(Servo *servo);
void initServo(Servo *servo, int32_t pCoef, int32_t iCoef, int32_t dCoef, int32_t target, uint32_t pwm);
void changeServoRotation(Servo *servo, MathOperation operation, uint32_t offset);
void updateServoPID(Servo *servo);

#endif /* CODE_SERVO_H_ */
