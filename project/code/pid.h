/*
 * pid.h
 *
 *  Created on: 2023Äê2ÔÂ10ÈÕ
 *      Author: Yaner
 */

#ifndef CODE_PID_H_
#define CODE_PID_H_

#include "zf_common_headfile.h"

typedef struct PIDVariable{
    int32_t pCorr, iCorr, dCorr;
    int32_t error[3];
    int32_t pCoef, iCoef, dCoef;
    int32_t target;
    int32_t measurement;
    int32_t deltaOutput;
}PIDVariable;

void initPID(PIDVariable *pid,int32_t pCoef, int32_t iCoef, int32_t dCoef, int32_t target);
int32_t updatePID(PIDVariable *pid);

#endif /* CODE_PID_H_ */
