/*
 * pid.c
 *
 *  Created on: 2023Äê2ÔÂ10ÈÕ
 *      Author: Yaner
 */
#include "pid.h"

void initPID(PIDVariable *pid,int32_t pCoef, int32_t iCoef, int32_t dCoef, int32_t target){
    pid->pCorr = 0; pid->iCorr = 0; pid->dCorr = 0;
    pid->error[0] = 0; pid->error[1] = 0; pid->error[2] = 0;
    pid->pCoef = pCoef; pid->iCoef = iCoef; pid->dCoef = dCoef;
    pid->target = target;
    pid->measurement = 0;
    pid->deltaOutput = 0;
}


int32_t updatePID(PIDVariable *pid){

    pid->error[0] = pid->target - pid->measurement;

    pid->pCorr = pid->pCoef  * (pid->error[0] - pid->error[1]) / 10.0;
    pid->iCorr = pid->iCoef  * pid->error[0] / 10.0;
    pid->dCorr = pid->dCoef  * (pid->error[0] - 2 * pid->error[1] + pid->error[2]) / 10.0;

    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->deltaOutput = pid->pCorr + pid->iCorr + pid->dCorr;

    return pid->deltaOutput;
    
}
