#include "median_filter.h"
#include "math.h"

float MedianFilter(float i,float j,float k)
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

float SlidingMedianFilter(float i[4],float j[4],float k[4])
{
    float Value0[4]={0.0,0.0,0.0,0.0};
    float Value1[4] = {0.0,0.0,0.0,0.0};
    /*中值滤波*/
    for(int t=0;t<4;t++)
    {
      //1.取3次结果

      //2.取中值
      if (i[t] > j[t])
      {
          Value0[t] = i[t]; i[t] = j[t]; j[t] =  Value0[t];
      }
      if (k[t] > j[t]) 
          Value0[t] = j[t];
      else if(k[t] > i[t]) 
          Value0[t] = k[t]; 
      else 
          Value0[t] = i[t];         
    }
     /*滑动中值滤波*/   
    for(int t=0;t<4;t++)
    {
        for(int l=0;l<4;l++)
        {
            Value0[0]=Value0[1];
            Value0[1]=Value0[2];
            Value0[2]=Value0[3];         
        }
        //1.取3次A/D转换结果

        //2.取中值
        if (i[t] > j[t])
        {
            Value0[3] = i[t]; i[t] = j[t]; j[t] = Value0[3];
        }
        if (k[t] > j[t]) 
            Value0[3] = j[t];
        else if(k > i) 
            Value0[3] = k[t]; 
        else 
            Value0[3] = i[t];
        for(int l=0;l<4;l++)
        {
            Value1[t]+=Value0[l];
        }
        Value1[t]/=4;
    }
    return (float)((Value1[0]+Value1[1]+Value1[2]+Value1[3])/4); 
}

float F_SlidingMedianFilter(CollectFuncTypeDef (*CollectFunc)(),unsigned int delay_time)
{
    float Value0[4]={0.0,0.0,0.0,0.0};
    float Value1[4] = {0.0,0.0,0.0,0.0};
    /*中值滤波*/
    for(int t=0;t<4;t++)
    {

			Value0[t] = F_MedianFilter((*CollectFunc),delay_time);
        
    }
     /*滑动中值滤波*/   
    for(int t=0;t<4;t++)
    {
        for(int l=0;l<4;l++)
        {
            Value0[0]=Value0[1];
            Value0[1]=Value0[2];
            Value0[2]=Value0[3];         
        }
        //1.取3次A/D转换结果
				Value0[3] = F_MedianFilter((*CollectFunc),delay_time);
				
        for(int l=0;l<4;l++)
        {
            Value1[t]+=Value0[l];
        }
        Value1[t]/=4;
    }
    return (float)((Value1[0]+Value1[1]+Value1[2]+Value1[3])/4); 
}

float F_MedianFilter(CollectFuncTypeDef (*CollectFunc)(),unsigned int delay_time)
{
	 CollectFuncTypeDef i = 0;
	 CollectFuncTypeDef j = 0;
	 CollectFuncTypeDef k = 0;
	 CollectFuncTypeDef temp = 0;

#if 1	
	 if(delay_time == 0)
	 {
				i = (*CollectFunc)();
		    j = (*CollectFunc)();
		    k = (*CollectFunc)();
	 }
	 else
	 {
				i = (*CollectFunc)();
				MedianFilterDelay(delay_time);
		    j = (*CollectFunc)();
				MedianFilterDelay(delay_time);
		    k = (*CollectFunc)();
	 }
#else
	 if(delay_time == 0)
	 {
				i = CollectFunc();
		    j = CollectFunc();
		    k = CollectFunc();
	 }
	 else
	 {
				i = CollectFunc();
				MedianFilterDelay(delay_time);
		    j = CollectFunc();
				MedianFilterDelay(delay_time);
		    k = CollectFunc();
	 }
#endif
	 
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
    
    return temp*1.0; 
}

