#ifndef _FILTER_H_
#define _FILTER_H_

typedef struct 
{
    //float LastP;//�ϴι���Э���� ��ʼ��ֵΪ0.02
    float P[2];//�ϴι���Э���� ��ʼ��ֵΪ0.02;��ǰ����Э���� ��ʼ��ֵΪ0
    float Out;//�������˲������ ��ʼ��ֵΪ0
    float Gain;//���������� ��ʼ��ֵΪ0
    float Q;//��������Э���� ��ʼ��ֵΪ0.001
    float R;//�۲�����Э���� ��ʼ��ֵΪ0.543
}KFP;//Kalman Filter parameter

float AvergeFilter(float *data,unsigned short len);
float MedianFilter(float i,float j,float k);
float MovingAverageFilter(float *data,unsigned short len,float newdata);
void  KalmanFilterInit(KFP *kfp,float R,float Q);
float KalmanFilter(KFP *kfp,float input);

#endif
