#include "median_filter.h"
#include "math.h"
#include "include.h"

void MedianFilterDelay(unsigned int ms) 
{
    systime.delay_ms(ms);
}

uint32_t FDC_SlidingMedianFilter(unsigned int delay_time)
{
    uint32_t Value0[4]={0,0,0,0};
    uint32_t Value1[4] = {0,0,0,0};
    /*中值滤波*/
    for(int t=0;t<4;t++)
    {

	Value0[t] = FDC_MedianFilter(delay_time);
        
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
        //1.取3次转换结果
	Value0[3] = FDC_MedianFilter(delay_time);
				
        for(int l=0;l<4;l++)
        {
            Value1[t]+=Value0[l];
        }
        Value1[t]/=4;
    }
    return (uint32_t)((Value1[0]+Value1[1]+Value1[2]+Value1[3])/4); 
}
uint32_t FDC_MedianFilter(unsigned int delay_time)
{
	 uint32_t i = 0;
	 uint32_t j = 0;
	 uint32_t k = 0;
	 uint32_t temp = 0;

	i = FDC_read_CHx(3);
	MedianFilterDelay(delay_time);
	j = FDC_read_CHx(3);
	MedianFilterDelay(delay_time);
	k = FDC_read_CHx(3);

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