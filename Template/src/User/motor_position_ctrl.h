#ifndef _MOTOR_POSITION_CTRL_H_
#define _MOTOR_POSITION_CTRL_H_
#include "include.h"


int16_t LeftMotorPositionCtrlStrategy(int16_t TargetValue);
int16_t RightMotorPositionCtrlStrategy(int16_t TargetValue);
int16_t RightMotorPositionCtrlDataProcessing(int16_t speed);
int16_t LeftMotorPositionCtrlDataProcessing(int16_t speed);



#endif