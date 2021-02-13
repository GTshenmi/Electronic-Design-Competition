#ifndef _FILTER_H_
#define _FILTER_H_

typedef struct 
{
    //float LastP;//上次估算协方差 初始化值为0.02
    float P[2];//上次估算协方差 初始化值为0.02;当前估算协方差 初始化值为0
    float Out;//卡尔曼滤波器输出 初始化值为0
    float Gain;//卡尔曼增益 初始化值为0
    float Q;//过程噪声协方差 初始化值为0.001
    float R;//观测噪声协方差 初始化值为0.543
}KFP;//Kalman Filter parameter

float AvergeFilter(float *data,unsigned short len);
float MedianFilter(float i,float j,float k);
float MovingAverageFilter(float *data,unsigned short len,float newdata);
void  KalmanFilterInit(KFP *kfp,float R,float Q);
float KalmanFilter(KFP *kfp,float input);

#endif
