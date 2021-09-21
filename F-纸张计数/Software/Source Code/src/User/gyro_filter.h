#ifndef _GYRO_FILTER_H_
#define _GYRO_FILTER_H_


void Read_Acc();
void Read_Gyro();
void CalculateAccAngle();
void AttitudeCalculation();

void Yiorderfilter(void);
void kalmanfilter(float Gyro,float Accel);

#endif