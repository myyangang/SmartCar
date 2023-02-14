/*
 * pid.c
 *
 *  Created on: 2023Äê2ÔÂ10ÈÕ
 *      Author: Yaner
 */
#include "pid.h"

void initPID(PIDVariable *pid,int32_t pCoef, int32_t iCoef, int32_t dCoef, int32_t target){
    memset(pid, 0, sizeof(PIDVariable));
    pid->pCoef = pCoef;
    pid->iCoef = iCoef;
    pid->dCoef = dCoef;
    pid->target = target;
}


int32_t updatePID(PIDVariable *pid){

    pid->error[0] = pid->target - pid->measurement;

    pid->pCorr = pid->pCoef * (pid->error[0] - pid->error[1]);
    pid->iCorr = pid->iCoef * pid->error[0];
    pid->dCorr = pid->dCoef * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);

    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->deltaOutput = pid->pCorr + pid->iCorr + pid->dCorr;

    return pid->deltaOutput;
    
}
