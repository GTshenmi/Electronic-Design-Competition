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
     /*Ԥ��Э����̣�
       kʱ��ϵͳ����Э���� = k-1ʱ�̵�ϵͳЭ���� + ��������Э����*/
     kfp->P[1] = kfp->P[0] + kfp->Q;
     
     /*���������淽�̣�
      ���������� = kʱ��ϵͳ����Э���� / ��kʱ��ϵͳ����Э���� + �۲�����Э���*/
     kfp->Gain = kfp->P[1] / (kfp->P[1] + kfp->R);
     
     /*��������ֵ���̣�
       kʱ��״̬����������ֵ = ״̬������Ԥ��ֵ + ���������� * ������ֵ - ״̬������Ԥ��ֵ��*/
     /*��һ�ε�Ԥ��ֵ������һ�ε����ֵ*/
     kfp->Out = kfp->Out + kfp->Gain * (input -kfp->Out);
     
     /*����Э�����:
       ���ε�ϵͳЭ����� kfp->P[0] Ϊ��һ������׼����*/
     kfp->P[0]  = (1-kfp->Gain) * kfp->P[1];
     return kfp->Out;
}
