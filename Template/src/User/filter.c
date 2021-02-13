#include "filter.h"
#include "math.h"

float FloatMedianFilter(float i,float j,float k)
{
    float temp;
	
    if (i > j)
    {
        temp = i; i = j; j = temp;
    }
    if (k > j) 
        temp = j;
    else if(k > i) 
        temp = k; 
    else 
        temp = i;
    
    return temp; 
}

float AvergeFilter(float *data,unsigned short len)
{
   double result = 0.0;
   
   for(int i = 0;i < len ;i++)
   {
     result += data[i]; 
   }
   
   result /= len;
   
   return result;
}

float MovingAverageFilter(float *data,unsigned short len,float newdata)
{
   double result = 0.0;
   
   for(int i = 0 ; i < len-1 ; i++)
   {
      data[i] = data[i+1];
   }
   
   data[len-1] = newdata;
   
   for(int i = 0 ;i < len ; i++)
   {
      result += data[i];
   }

   result /= (len*1.0);
   
   return result;
}

void KalmanFilterInit(KFP *kfp,float R,float Q)
{
   kfp->R = R;
   kfp->Q = Q;
   kfp->Out = 0.0;
   kfp->Gain = 0.0;
   kfp->P[0] = 0.0;
   kfp->P[1] = 0.0;
}

float KalmanFilter(KFP *kfp,float input)
{
     /*预测协方差方程：
       k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差*/
     kfp->P[1] = kfp->P[0] + kfp->Q;
     
     /*卡尔曼增益方程：
      卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）*/
     kfp->Gain = kfp->P[1] / (kfp->P[1] + kfp->R);
     
     /*更新最优值方程：
       k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）*/
     /*这一次的预测值就是上一次的输出值*/
     kfp->Out = kfp->Out + kfp->Gain * (input -kfp->Out);
     
     /*更新协方差方程:
       本次的系统协方差赋给 kfp->P[0] 为下一次运算准备。*/
     kfp->P[0]  = (1-kfp->Gain) * kfp->P[1];
     return kfp->Out;
}
