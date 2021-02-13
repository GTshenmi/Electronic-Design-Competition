#ifndef _MOTOR_SPEED_CTRL_H_
#define _MOTOR_SPEED_CTRL_H_
#include "include.h"

int16_t LeftMotorSpeedCtrlStrategy(int16_t TargetValue);
int16_t RightMotorSpeedCtrlStrategy(int16_t TargetValue);
int16_t LeftMotorSpeedCtrlDataProcessing(int16_t speed);
int16_t RightMotorSpeedCtrlDataProcessing(int16_t speed);

#endif